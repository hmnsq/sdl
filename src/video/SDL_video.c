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

#అన్తర్భావ "SDL_internal.h"

// The high-level video driver subsystem

#అన్తర్భావ "SDL_sysvideo.h"
#అన్తర్భావ "SDL_clipboard_c.h"
#అన్తర్భావ "SDL_egl_c.h"
#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_pixels_c.h"
#అన్తర్భావ "SDL_rect_c.h"
#అన్తర్భావ "SDL_video_c.h"
#అన్తర్భావ "../events/SDL_events_c.h"
#అన్తర్భావ "../SDL_hints_c.h"
#అన్తర్భావ "../SDL_properties_c.h"
#అన్తర్భావ "../timer/SDL_timer_c.h"
#అన్తర్భావ "../camera/SDL_camera_c.h"
#అన్తర్భావ "../render/SDL_sysrender.h"
#అన్తర్భావ "../main/SDL_main_callbacks.h"

#నిర్వచితమైతే SDL_VIDEO_OPENGL
#అన్తర్భావ <SDL3/SDL_opengl.h>
#అయితే_ముగింపు // SDL_VIDEO_OPENGL

#ఒకవేళ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#అన్తర్భావ <SDL3/SDL_opengles.h>
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ఒకవేళ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#అన్తర్భావ <SDL3/SDL_opengles2.h>
#అయితే_ముగింపు // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#నిర్వచితం_కాకపోతే GL_CONTEXT_RELEASE_BEHAVIOR
#నిర్వచించు GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#అయితే_ముగింపు

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#నిర్వచితం_కాకపోతే GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#నిర్వచించు GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#అయితే_ముగింపు

// This is always the same number between the various EXT/ARB/GLES extensions.
#నిర్వచితం_కాకపోతే GL_FRAMEBUFFER_SRGB
#నిర్వచించు GL_FRAMEBUFFER_SRGB 0x8DB9
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_PLATFORM_EMSCRIPTEN
#అన్తర్భావ <emscripten.h>
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_PLATFORM_3DS
#అన్తర్భావ <3ds.h>
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే GL_RGBA_FLOAT_బహుళకం_ARB
#నిర్వచించు GL_RGBA_FLOAT_బహుళకం_ARB 0x8820
#అయితే_ముగింపు /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
స్థిర VideoBootStrap *bootstrap[] = {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_వ్యక్తిగత
    &వ్యక్తిగత_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#అయితే_ముగింపు
    &X11_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#నిర్వచితమైతే SDL_ఆదానం_LINUXEV
    &DUMMY_evdev_bootstrap,
#అయితే_ముగింపు
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#అయితే_ముగింపు
    ఖాళీ
};

#నిర్వచించు CHECK_కిటికీ_MAGIC(కిటికీ, ఫలితం)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        తిరిగి ఫలితం;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(కిటికీ, SDL_OBJECT_TYPE_కిటికీ)) {     \
        SDL_సమితి_Error("Invalid window");                                 \
        తిరిగి ఫలితం;                                                  \
    }

#నిర్వచించు CHECK_DISPLAY_MAGIC(display, ఫలితం)                            \
    CHECK_PARAM(!display) {                                             \
        తిరిగి ఫలితం;                                                  \
    }                                                                   \

#నిర్వచించు CHECK_కిటికీ_NOT_POPUP(కిటికీ, ఫలితం)                          \
    CHECK_PARAM(SDL_కిటికీ_IS_POPUP(కిటికీ)) {                          \
        SDL_సమితి_Error("Operation invalid on popup windows");             \
        తిరిగి ఫలితం;                                                  \
    }

#ఒకవేళ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
బాహ్య bool Cocoa_Is_కిటికీ_లోపల_Fullscreen_Space(SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_Is_కిటికీ_లోపల_Fullscreen_Space_Transition(SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_సమితి_కిటికీ_Fullscreen_Space(SDL_కిటికీ *కిటికీ, bool state, bool blocking);
బాహ్య bool Cocoa_IsShowingModalDialog(SDL_కిటికీ *కిటికీ);
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_UIKIT
బాహ్య శూన్య SDL_UpdateLifecycleObserver(శూన్య);
#అయితే_ముగింపు

స్థిర శూన్య SDL_Check_కిటికీ_Display_మారింది(SDL_కిటికీ *కిటికీ);
స్థిర శూన్య SDL_Check_కిటికీ_Display_Scale_మారింది(SDL_కిటికీ *కిటికీ);
స్థిర శూన్య SDL_Check_కిటికీ_సురక్షిత_Area_మారింది(SDL_కిటికీ *కిటికీ);

// Convenience functions for reading driver flags
స్థిర bool SDL_బహుళకం_Switching_Emulated(SDL_VideoDevice *_this)
{
    ఒకవేళ (_this->device_caps & VIDEO_DEVICE_CAPS_బహుళకం_SWITCHING_EMULATED) {
        తిరిగి true;
    }
    తిరిగి false;
}

స్థిర bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    తిరిగి !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

స్థిర bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    తిరిగి !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

స్థిర bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    తిరిగి !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

స్థిర bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    తిరిగి !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

స్థిర bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    తిరిగి !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
స్థిర bool syncHint;

స్థిర శూన్య SDL_SyncHintWatcher(శూన్య *userdata, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *old_విలువ, స్థిరరాశి అక్షరం *new_విలువ)
{
    syncHint = SDL_GetStringBoolean(new_విలువ, false);
}

స్థిర శూన్య SDL_SyncIfRequired(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (syncHint) {
        SDL_Sync_కిటికీ(కిటికీ);
    }
}

స్థిర శూన్య SDL_Update_కిటికీ_Hierarchy(SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ)
{
    // Unlink the window from the existing parent.
    ఒకవేళ (కిటికీ->మాతృ) {
        ఒకవేళ (కిటికీ->తదుపరి_sibling) {
            కిటికీ->తదుపరి_sibling->prev_sibling = కిటికీ->prev_sibling;
        }
        ఒకవేళ (కిటికీ->prev_sibling) {
            కిటికీ->prev_sibling->తదుపరి_sibling = కిటికీ->తదుపరి_sibling;
        } లేకపోతే {
            కిటికీ->మాతృ->మొదటి_బిడ్డ = కిటికీ->తదుపరి_sibling;
        }

        కిటికీ->మాతృ = ఖాళీ;
    }

    ఒకవేళ (మాతృ) {
        కిటికీ->మాతృ = మాతృ;

        కిటికీ->తదుపరి_sibling = మాతృ->మొదటి_బిడ్డ;
        ఒకవేళ (మాతృ->మొదటి_బిడ్డ) {
            మాతృ->మొదటి_బిడ్డ->prev_sibling = కిటికీ;
        }
        మాతృ->మొదటి_బిడ్డ = కిటికీ;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#నిర్వచించు SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక "SDL.internal.window.texturedata"

రకనిర్వచనం నిర్మాణం
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    శూన్య *pixels;
    పూర్ణాంకం pitch;
    పూర్ణాంకం బైట్లు_చొప్పున_pixel;
} SDL_కిటికీ_Texture_దత్తాంశం;

స్థిర Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ఒకవేళ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !లక్ష్యం_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ఒకవేళ (_this->GL_CreateContext) {
        తిరిగి SDL_కిటికీ_OPENGL;
    }
#అయితే_ముగింపు
#ఒకవేళ defined(SDL_VIDEO_METAL) && (లక్ష్యం_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ఒకవేళ (_this->Metal_CreateView) {
        తిరిగి SDL_కిటికీ_METAL;
    }
#అయితే_ముగింపు
#ఒకవేళ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ఒకవేళ (SDL_strcmp(_this->name, "openvr") == 0) {
        తిరిగి SDL_కిటికీ_OPENGL;
    }
#అయితే_ముగింపు
    తిరిగి 0;
}

స్థిర bool SDL_Create_కిటికీ_Texture(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    SDL_కిటికీ_Texture_దత్తాంశం *దత్తాంశం = (SDL_కిటికీ_Texture_దత్తాంశం *)SDL_Get_సూచిక_Property(props, SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక, ఖాళీ);
    స్థిరరాశి bool transparent = (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) ? true : false;
    పూర్ణాంకం i;
    పూర్ణాంకం w, h;
    స్థిరరాశి SDL_PixelFormat *texture_formats;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    ఒకవేళ (!దత్తాంశం) {
        SDL_Renderer *renderer = ఖాళీ;
        స్థిరరాశి అక్షరం *render_driver = ఖాళీ;

        // See if there's a render driver being requested
        స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ఒకవేళ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ఒకవేళ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ఒకవేళ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ఖాళీ;
        }

        అక్షరం *render_driver_copy = ఖాళీ;
        ఒకవేళ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ఒకవేళ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                అక్షరం *prev = render_driver_copy;
                అక్షరం *ptr = prev;
                అయితే ((ptr = SDL_strchr(ptr, ',')) != ఖాళీ) {
                    *ptr = '\0';
                    స్థిరరాశి bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ఒకవేళ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } లేకపోతే {
                        ptr++;
                        prev = ptr;
                    }
                }

                ఒకవేళ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ఒకవేళ (render_driver) {
            renderer = SDL_CreateRenderer(కిటికీ, render_driver);
            SDL_free(render_driver_copy);
            ఒకవేళ (!renderer) {
                // The error for this specific renderer has already been set
                తిరిగి false;
            }
        } లేకపోతే {
            SDL_assert(render_driver_copy == ఖాళీ);
            స్థిరరాశి పూర్ణాంకం మొత్తం = SDL_Get_అంకె_Render_Drivers();
            కొరకు (i = 0; i < మొత్తం; ++i) {
                స్థిరరాశి అక్షరం *name = SDL_GetRenderDriver(i);
                ఒకవేళ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(కిటికీ, name);
                    ఒకవేళ (renderer) {
                        ఆపు; // this will work.
                    }
                }
            }
            ఒకవేళ (!renderer) {
                తిరిగి SDL_సమితి_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ఖాళీ); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        దత్తాంశం = (SDL_కిటికీ_Texture_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
        ఒకవేళ (!దత్తాంశం) {
            SDL_DestroyRenderer(renderer);
            తిరిగి false;
        }
        ఒకవేళ (!SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక, దత్తాంశం)) {
            SDL_DestroyRenderer(renderer);
            తిరిగి false;
        }

        దత్తాంశం->renderer = renderer;
    }

    texture_formats = (స్థిరరాశి SDL_PixelFormat *)SDL_Get_సూచిక_Property(SDL_GetRendererProperties(దత్తాంశం->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_సూచిక, ఖాళీ);
    ఒకవేళ (!texture_formats) {
        తిరిగి false;
    }

    // Free any old texture and pixel data
    ఒకవేళ (దత్తాంశం->texture) {
        SDL_DestroyTexture(దత్తాంశం->texture);
        దత్తాంశం->texture = ఖాళీ;
    }
    SDL_free(దత్తాంశం->pixels);
    దత్తాంశం->pixels = ఖాళీ;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    కొరకు (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ఒకవేళ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_బిట్టు(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_సూచీకృత(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            ఆపు;
        }
    }

    దత్తాంశం->texture = SDL_CreateTexture(దత్తాంశం->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    ఒకవేళ (!దత్తాంశం->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        తిరిగి false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_సమితి_Texture_Blend_బహుళకం(దత్తాంశం->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    దత్తాంశం->బైట్లు_చొప్పున_pixel = SDL_BYTESPERPIXEL(*format);
    దత్తాంశం->pitch = (((w * దత్తాంశం->బైట్లు_చొప్పున_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        స్థిరరాశి size_t allocsize = (size_t)h * దత్తాంశం->pitch;
        దత్తాంశం->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ఒకవేళ (!దత్తాంశం->pixels) {
            తిరిగి false;
        }
    }

    *pixels = దత్తాంశం->pixels;
    *pitch = దత్తాంశం->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_సమితి_Render_Viewport(దత్తాంశం->renderer, ఖాళీ);

    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Texture_VSync(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం vsync)
{
    SDL_కిటికీ_Texture_దత్తాంశం *దత్తాంశం;

    దత్తాంశం = (SDL_కిటికీ_Texture_దత్తాంశం *)SDL_Get_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక, ఖాళీ);
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }
    ఒకవేళ (!దత్తాంశం->renderer) {
        తిరిగి false;
    }
    తిరిగి SDL_సమితి_Render_VSync(దత్తాంశం->renderer, vsync);
}

స్థిర bool SDL_Get_కిటికీ_Texture_VSync(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *vsync)
{
    SDL_కిటికీ_Texture_దత్తాంశం *దత్తాంశం;

    దత్తాంశం = (SDL_కిటికీ_Texture_దత్తాంశం *)SDL_Get_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక, ఖాళీ);
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }
    ఒకవేళ (!దత్తాంశం->renderer) {
        తిరిగి false;
    }
    తిరిగి SDL_GetRenderVSync(దత్తాంశం->renderer, vsync);
}

స్థిర bool SDL_Update_కిటికీ_Texture(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    SDL_కిటికీ_Texture_దత్తాంశం *దత్తాంశం;
    SDL_Rect rect;
    శూన్య *src;
    పూర్ణాంకం w, h;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    దత్తాంశం = (SDL_కిటికీ_Texture_దత్తాంశం *)SDL_Get_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక, ఖాళీ);
    ఒకవేళ (!దత్తాంశం || !దత్తాంశం->texture) {
        తిరిగి SDL_సమితి_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ఒకవేళ (SDL_Get_పరిధి_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (శూన్య *)((Uint8 *)దత్తాంశం->pixels +
                       rect.y * దత్తాంశం->pitch +
                       rect.x * దత్తాంశం->బైట్లు_చొప్పున_pixel);
        ఒకవేళ (!SDL_UpdateTexture(దత్తాంశం->texture, &rect, src, దత్తాంశం->pitch)) {
            తిరిగి false;
        }

        ఒకవేళ (!SDL_RenderTexture(దత్తాంశం->renderer, దత్తాంశం->texture, ఖాళీ, ఖాళీ)) {
            తిరిగి false;
        }

        SDL_RenderPresent(దత్తాంశం->renderer);
    }
    తిరిగి true;
}

స్థిర శూన్య SDL_Destroy_కిటికీ_Texture(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    ఒకవేళ (SDL_HasProperty(props, SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక)) {
        SDL_కిటికీ_Texture_దత్తాంశం *దత్తాంశం = SDL_Get_సూచిక_Property(props, SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక, ఖాళీ);

        ఒకవేళ (దత్తాంశం->texture) {
            SDL_DestroyTexture(దత్తాంశం->texture);
        }
        ఒకవేళ (దత్తాంశం->renderer) {
            SDL_DestroyRenderer(దత్తాంశం->renderer);
        }
        SDL_free(దత్తాంశం->pixels);
        SDL_free(దత్తాంశం);

        SDL_ClearProperty(props, SDL_PROP_కిటికీ_TEXTUREDATA_సూచిక);
    }
}

స్థిర SDL_VideoDevice *_this = ఖాళీ;
స్థిర SDL_AtomicInt SDL_messagebox_లెక్క;

స్థిర పూర్ణాంకం SDLCALL cmpmodes(స్థిరరాశి శూన్య *A, స్థిరరాశి శూన్య *B)
{
    స్థిరరాశి SDL_Display_బహుళకం *a = (స్థిరరాశి SDL_Display_బహుళకం *)A;
    స్థిరరాశి SDL_Display_బహుళకం *b = (స్థిరరాశి SDL_Display_బహుళకం *)B;
    పూర్ణాంకం a_refresh_రేటు = (పూర్ణాంకం)(a->refresh_రేటు * 100);
    పూర్ణాంకం b_refresh_రేటు = (పూర్ణాంకం)(b->refresh_రేటు * 100);
    పూర్ణాంకం a_pixel_density = (పూర్ణాంకం)(a->pixel_density * 100);
    పూర్ణాంకం b_pixel_density = (పూర్ణాంకం)(b->pixel_density * 100);

    ఒకవేళ (a->w != b->w) {
        తిరిగి b->w - a->w;
    } లేకపోతే ఒకవేళ (a->h != b->h) {
        తిరిగి b->h - a->h;
    } లేకపోతే ఒకవేళ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        తిరిగి SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } లేకపోతే ఒకవేళ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        తిరిగి SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } లేకపోతే ఒకవేళ (a_refresh_రేటు != b_refresh_రేటు) {
        తిరిగి b_refresh_రేటు - a_refresh_రేటు;
    } లేకపోతే ఒకవేళ (a_pixel_density != b_pixel_density) {
        తిరిగి a_pixel_density - b_pixel_density;
    }
    తిరిగి 0;
}

bool SDL_UninitializedVideo(శూన్య)
{
    తిరిగి SDL_సమితి_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
స్థిర స్థిరరాశి VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

పూర్ణాంకం SDL_Get_అంకె_Video_Drivers(శూన్య)
{
    స్థిర పూర్ణాంకం అంకె_drivers = -1;

    ఒకవేళ (అంకె_drivers >= 0) {
        తిరిగి అంకె_drivers;
    }

    అంకె_drivers = 0;

    // Build a list of unique video drivers.
    కొరకు (పూర్ణాంకం i = 0; bootstrap[i] != ఖాళీ; ++i) {
        bool duplicate = false;
        కొరకు (పూర్ణాంకం j = 0; j < i; ++j) {
            ఒకవేళ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                ఆపు;
            }
        }

        ఒకవేళ (!duplicate) {
            deduped_bootstrap[అంకె_drivers++] = bootstrap[i];
        }
    }

    తిరిగి అంకె_drivers;
}

స్థిరరాశి అక్షరం *SDL_GetVideoDriver(పూర్ణాంకం సూచీ)
{
    CHECK_PARAM(సూచీ < 0 || సూచీ >= SDL_Get_అంకె_Video_Drivers()) {
        SDL_InvalidParamError("index");
        తిరిగి ఖాళీ;
    }
    తిరిగి deduped_bootstrap[సూచీ]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(స్థిరరాశి అక్షరం *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    పూర్ణాంకం i = 0;

    // Check to make sure we don't overwrite '_this'
    ఒకవేళ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ఒకవేళ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        వెళ్ళు pre_driver_error;
    }
    init_events = true;
    ఒకవేళ (!SDL_InitKeyboard()) {
        వెళ్ళు pre_driver_error;
    }
    init_keyboard = true;
    ఒకవేళ (!SDL_PreInitMouse()) {
        వెళ్ళు pre_driver_error;
    }
    init_mouse = true;
    ఒకవేళ (!SDL_InitTouch()) {
        వెళ్ళు pre_driver_error;
    }
    init_touch = true;
    ఒకవేళ (!SDL_InitPen()) {
        వెళ్ళు pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ఖాళీ;
#నిర్వచితమైతే SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ఒకవేళ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#అయితే_ముగింపు
    ఒకవేళ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ఒకవేళ (driver_name && *driver_name != 0) {
        స్థిరరాశి అక్షరం *driver_attempt = driver_name;
        అయితే (driver_attempt && *driver_attempt != 0 && !video) {
            స్థిరరాశి అక్షరం *driver_attempt_చివర = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_చివర) ? (driver_attempt_చివర - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            కొరకు (i = 0; bootstrap[i]; ++i) {
                ఒకవేళ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ఒకవేళ (video) {
                        ఆపు;
                    }
                }
            }

            driver_attempt = (driver_attempt_చివర) ? (driver_attempt_చివర + 1) : ఖాళీ;
        }
    } లేకపోతే {
        కొరకు (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ఒకవేళ (video) {
                ఆపు;
            }
        }
    }
    ఒకవేళ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } లేకపోతే {
        ఒకవేళ (driver_name) {
            SDL_సమితి_Error("%s not available", driver_name);
            వెళ్ళు pre_driver_error;
        }
        SDL_సమితి_Error("No available video device");
        వెళ్ళు pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ఖాళీ;
    SDL_GL_Reset_లక్షణాలు();

    // Initialize the video subsystem
    ఒకవేళ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        తిరిగి false;
    }

    // Make sure some displays were added
    ఒకవేళ (_this->అంకె_displays == 0) {
        SDL_QuitVideo();
        తిరిగి SDL_సమితి_Error("The video driver did not add any displays");
    }

    SDL_కూడు_Hint_Callback(SDL_HINT_VIDEO_SYNC_కిటికీ_OPERATIONS, SDL_SyncHintWatcher, ఖాళీ);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ఒకవేళ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    తిరిగి true;

pre_driver_error:
    SDL_assert(_this == ఖాళీ);
    ఒకవేళ (init_pen) {
        SDL_QuitPen();
    }
    ఒకవేళ (init_touch) {
        SDL_QuitTouch();
    }
    ఒకవేళ (init_mouse) {
        SDL_QuitMouse();
    }
    ఒకవేళ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ఒకవేళ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    తిరిగి false;
}

స్థిరరాశి అక్షరం *SDL_GetCurrentVideoDriver(శూన్య)
{
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    తిరిగి _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(శూన్య)
{
    తిరిగి _this;
}

bool SDL_OnVideoThread(శూన్య)
{
    తిరిగి (_this && SDL_GetCurrentThreadID() == _this->thread);
}

శూన్య SDL_సమితి_System_Theme(SDL_SystemTheme theme)
{
    ఒకవేళ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_మారింది_Event();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(శూన్య)
{
    ఒకవేళ (_this) {
        తిరిగి _this->system_theme;
    } లేకపోతే {
        తిరిగి SDL_SYSTEM_THEME_UNKNOWN;
    }
}

శూన్య SDL_UpdateDesktopBounds(శూన్య)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ఖాళీ);
    ఒకవేళ (displays) {
        కొరకు (పూర్ణాంకం i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ఒకవేళ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ఒకవేళ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } లేకపోతే {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

స్థిర శూన్య SDL_Finalize_Display_బహుళకం(SDL_Display_బహుళకం *బహుళకం)
{
    // Make sure all the fields are set up correctly
    ఒకవేళ (బహుళకం->pixel_density <= 0.0f) {
        బహుళకం->pixel_density = 1.0f;
    }

    ఒకవేళ (బహుళకం->refresh_రేటు_numerator > 0) {
        ఒకవేళ (బహుళకం->refresh_రేటు_denominator <= 0) {
            బహుళకం->refresh_రేటు_denominator = 1;
        }
        బహుళకం->refresh_రేటు = (దశాంశం)బహుళకం->refresh_రేటు_numerator / బహుళకం->refresh_రేటు_denominator;
    } లేకపోతే {
        SDL_CalculateFraction(బహుళకం->refresh_రేటు, &బహుళకం->refresh_రేటు_numerator, &బహుళకం->refresh_రేటు_denominator);
    }
    బహుళకం->refresh_రేటు = SDL_roundf(బహుళకం->refresh_రేటు * 100) / 100.0f;
}

SDL_DisplayID SDL_కూడు_Basic_Video_Display(స్థిరరాశి SDL_Display_బహుళకం *desktop_బహుళకం)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ఒకవేళ (desktop_బహుళకం) {
        SDL_memcpy(&display.desktop_బహుళకం, desktop_బహుళకం, పరిమాణం(display.desktop_బహుళకం));
    }
    తిరిగి SDL_కూడు_Video_Display(&display, false);
}

SDL_DisplayID SDL_కూడు_Video_Display(స్థిరరాశి SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    పూర్ణాంకం i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(పరిమాణం(*new_display));
    ఒకవేళ (!new_display) {
        తిరిగి 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->అంకె_displays + 1) * పరిమాణం(*displays));
    ఒకవేళ (!displays) {
        SDL_free(new_display);
        తిరిగి 0;
    }
    _this->displays = displays;
    _this->displays[_this->అంకె_displays++] = new_display;

    id = SDL_Get_తదుపరి_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ఒకవేళ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } లేకపోతే {
        అక్షరం name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ఒకవేళ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_బహుళకం.displayID = id;
    new_display->current_బహుళకం = &new_display->desktop_బహుళకం;
    SDL_Finalize_Display_బహుళకం(&new_display->desktop_బహుళకం);

    కొరకు (i = 0; i < new_display->అంకె_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_సమితి_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ఒకవేళ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    తిరిగి id;
}

శూన్య SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_కిటికీ *కిటికీ;

    // See if any windows have changed to the new display
    కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        SDL_Check_కిటికీ_Display_మారింది(కిటికీ);
    }
}

శూన్య SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

శూన్య SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    పూర్ణాంకం display_సూచీ = SDL_Get_Display_సూచీ(displayID);
    ఒకవేళ (display_సూచీ < 0) {
        తిరిగి;
    }

    display = _this->displays[display_సూచీ];

    ఒకవేళ (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_బహుళకం.అంతర్గత);
    display->desktop_బహుళకం.అంతర్గత = ఖాళీ;
    SDL_free(display->అంతర్గత);
    display->అంతర్గత = ఖాళీ;
    SDL_free(display);

    ఒకవేళ (display_సూచీ < (_this->అంకె_displays - 1)) {
        SDL_memmove(&_this->displays[display_సూచీ], &_this->displays[display_సూచీ + 1], (_this->అంకె_displays - display_సూచీ - 1) * పరిమాణం(_this->displays[display_సూచీ]));
    }
    --_this->అంకె_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(పూర్ణాంకం *లెక్క)
{
    పూర్ణాంకం i;
    SDL_DisplayID *displays;

    ఒకవేళ (!_this) {
        ఒకవేళ (లెక్క) {
            *లెక్క = 0;
        }

        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->అంకె_displays + 1) * పరిమాణం(*displays));
    ఒకవేళ (displays) {
        ఒకవేళ (లెక్క) {
            *లెక్క = _this->అంకె_displays;
        }

        కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } లేకపోతే {
        ఒకవేళ (లెక్క) {
            *లెక్క = 0;
        }
    }
    తిరిగి displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    పూర్ణాంకం display_సూచీ;

    display_సూచీ = SDL_Get_Display_సూచీ(displayID);
    ఒకవేళ (display_సూచీ < 0) {
        తిరిగి ఖాళీ;
    }
    తిరిగి _this->displays[display_సూచీ];
}

స్థిర SDL_DisplayID Get_Display_For_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        displayID = కిటికీ->current_fullscreen_బహుళకం.displayID;
    }

    ఒకవేళ (!displayID) {
        displayID = SDL_Get_Display_For_కిటికీ_Position(కిటికీ);
    }
    తిరిగి displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    తిరిగి SDL_GetVideoDisplay(Get_Display_For_కిటికీ(కిటికీ));
}

SDL_DisplayID SDL_GetPrimaryDisplay(శూన్య)
{
    ఒకవేళ (!_this || _this->అంకె_displays == 0) {
        SDL_UninitializedVideo();
        తిరిగి 0;
    }
    తిరిగి _this->displays[0]->id;
}

పూర్ణాంకం SDL_Get_Display_సూచీ(SDL_DisplayID displayID)
{
    పూర్ణాంకం display_సూచీ;

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి -1;
    }

    కొరకు (display_సూచీ = 0; display_సూచీ < _this->అంకె_displays; ++display_సూచీ) {
        ఒకవేళ (displayID == _this->displays[display_సూచీ]->id) {
            తిరిగి display_సూచీ;
        }
    }
    SDL_సమితి_Error("Invalid display");
    తిరిగి -1;
}

SDL_Display_దత్తాంశం *SDL_Get_Display_Driver_దత్తాంశం(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ఖాళీ);

    తిరిగి display->అంతర్గత;
}

SDL_Display_దత్తాంశం *SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    తిరిగి SDL_Get_Display_Driver_దత్తాంశం(Get_Display_For_కిటికీ(కిటికీ));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ఒకవేళ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    తిరిగి display->props;
}

స్థిరరాశి అక్షరం *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ఖాళీ);

    తిరిగి display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        తిరిగి SDL_InvalidParamError("rect");
    }

    ఒకవేళ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ఒకవేళ (_this->GetDisplayBounds(_this, display, rect)) {
            తిరిగి true;
        }
    }

    // Assume that the displays are left to right
    ఒకవేళ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } లేకపోతే {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_సూచీ(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_బహుళకం->w;
    rect->h = display->current_బహుళకం->h;
    తిరిగి true;
}

స్థిర పూర్ణాంకం ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    తిరిగి hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        తిరిగి SDL_InvalidParamError("rect");
    }

    ఒకవేళ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        తిరిగి true;
    }

    ఒకవేళ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ఒకవేళ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            తిరిగి true;
        }
    }

    // Oh well, just give the entire display bounds.
    తిరిగి SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ఒకవేళ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        తిరిగి display->natural_orientation;
    } లేకపోతే {
        // Default to landscape if the driver hasn't set it
        తిరిగి SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ఒకవేళ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        తిరిగి display->current_orientation;
    } లేకపోతే {
        // Default to landscape if the driver hasn't set it
        తిరిగి SDL_ORIENTATION_LANDSCAPE;
    }
}

శూన్య SDL_సమితి_Display_Content_Scale(SDL_VideoDisplay *display, దశాంశం scale)
{
    ఒకవేళ (scale != display->content_scale) {
        SDL_కిటికీ *కిటికీ;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_మారింది, 0, 0);

        // Check the windows on this display
        కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            ఒకవేళ (display->id == కిటికీ->displayID) {
                SDL_Check_కిటికీ_Display_Scale_మారింది(కిటికీ);
            }
        }
    }
}

దశాంశం SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    తిరిగి display->content_scale;
}

శూన్య SDL_సమితి_కిటికీ_HDRProperties(SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_HDROutputProperties *HDR, bool send_event)
{
    స్థిరరాశి SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ఒకవేళ (కిటికీ->HDR.HDR_headroom != HDR_clamped.HDR_headroom || కిటికీ->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID కిటికీ_props = SDL_Get_కిటికీ_Properties(కిటికీ);

        SDL_సమితి_Float_Property(కిటికీ_props, SDL_PROP_కిటికీ_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_సమితి_Float_Property(కిటికీ_props, SDL_PROP_కిటికీ_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_సమితి_Boolean_Property(కిటికీ_props, SDL_PROP_కిటికీ_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&కిటికీ->HDR, &HDR_clamped);

        ఒకవేళ (send_event) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_HDR_STATE_మారింది, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

శూన్య SDL_సమితి_Display_HDRProperties(SDL_VideoDisplay *display, స్థిరరాశి SDL_HDROutputProperties *HDR)
{
    స్థిరరాశి SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    స్థిరరాశి bool మారింది = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	ఒకవేళ (మారింది) {
		SDL_సమితి_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ఒకవేళ (మారింది && !SDL_DriverSendsHDRChanges(_this)) {
        కొరకు (SDL_కిటికీ *w = display->device->windows; w; w = w->తదుపరి) {
            ఒకవేళ (Get_Display_For_కిటికీ(w) == display->id) {
                SDL_సమితి_కిటికీ_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

స్థిర శూన్య SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ఒకవేళ (display->అంకె_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
స్థిర స్థిరరాశి SDL_Display_బహుళకం *SDL_Get_Fullscreen_బహుళకం_సరిపోలిక(స్థిరరాశి SDL_Display_బహుళకం *బహుళకం)
{
    SDL_VideoDisplay *display;
    SDL_Display_బహుళకం fullscreen_బహుళకం;

    ఒకవేళ (బహుళకం->w <= 0 || బహుళకం->h <= 0) {
        // Use the desktop mode
        తిరిగి ఖాళీ;
    }

    SDL_memcpy(&fullscreen_బహుళకం, బహుళకం, పరిమాణం(fullscreen_బహుళకం));
    ఒకవేళ (fullscreen_బహుళకం.displayID == 0) {
        fullscreen_బహుళకం.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_బహుళకం(&fullscreen_బహుళకం);

    బహుళకం = ఖాళీ;

    display = SDL_GetVideoDisplay(fullscreen_బహుళకం.displayID);
    ఒకవేళ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ఒకవేళ (!బహుళకం) {
            కొరకు (పూర్ణాంకం i = 0; i < display->అంకె_fullscreen_modes; ++i) {
                ఒకవేళ (SDL_memcmp(&fullscreen_బహుళకం, &display->fullscreen_modes[i], పరిమాణం(fullscreen_బహుళకం)) == 0) {
                    బహుళకం = &display->fullscreen_modes[i];
                    ఆపు;
                }
            }
        }

        // Search for a mode with the same characteristics
        ఒకవేళ (!బహుళకం) {
            కొరకు (పూర్ణాంకం i = 0; i < display->అంకె_fullscreen_modes; ++i) {
                ఒకవేళ (cmpmodes(&fullscreen_బహుళకం, &display->fullscreen_modes[i]) == 0) {
                    బహుళకం = &display->fullscreen_modes[i];
                    ఆపు;
                }
            }
        }
    }
    తిరిగి బహుళకం;
}

bool SDL_కూడు_Fullscreen_Display_బహుళకం(SDL_VideoDisplay *display, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_బహుళకం *modes;
    SDL_Display_బహుళకం new_బహుళకం;
    పూర్ణాంకం i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_బహుళకం, బహుళకం, పరిమాణం(new_బహుళకం));
    new_బహుళకం.displayID = display->id;
    SDL_Finalize_Display_బహుళకం(&new_బహుళకం);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->అంకె_fullscreen_modes;
    కొరకు (i = 0; i < nmodes; ++i) {
        ఒకవేళ (cmpmodes(&new_బహుళకం, &modes[i]) == 0) {
            తిరిగి false;
        }
    }

    // Go ahead and add the new mode
    ఒకవేళ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_బహుళకం *)SDL_malloc((display->max_fullscreen_modes + 32) * పరిమాణం(*modes));
        ఒకవేళ (!modes) {
            తిరిగి false;
        }

        ఒకవేళ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * పరిమాణం(*modes));
            కొరకు (i = 0; i < nmodes; ++i) {
                ఒకవేళ (display->current_బహుళకం == &display->fullscreen_modes[i]) {
                    display->current_బహుళకం = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->అంకె_fullscreen_modes++], &new_బహుళకం, పరిమాణం(new_బహుళకం));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->అంకె_fullscreen_modes,
              పరిమాణం(SDL_Display_బహుళకం), cmpmodes);

    తిరిగి true;
}

శూన్య SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    పూర్ణాంకం i;

    కొరకు (i = display->అంకె_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].అంతర్గత);
        display->fullscreen_modes[i].అంతర్గత = ఖాళీ;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ఖాళీ;
    display->అంకె_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_బహుళకం = &display->desktop_బహుళకం;
}

SDL_Display_బహుళకం **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, పూర్ణాంకం *లెక్క)
{
    పూర్ణాంకం i;
    పూర్ణాంకం అంకె_modes;
    SDL_Display_బహుళకం **ఫలితం;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ఒకవేళ (లెక్క) {
        *లెక్క = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ఖాళీ);

    SDL_UpdateFullscreenDisplayModes(display);

    అంకె_modes = display->అంకె_fullscreen_modes;
    ఫలితం = (SDL_Display_బహుళకం **)SDL_malloc((అంకె_modes + 1) * పరిమాణం(*ఫలితం) + అంకె_modes * పరిమాణం(**ఫలితం));
    ఒకవేళ (ఫలితం) {
        SDL_Display_బహుళకం *modes = (SDL_Display_బహుళకం *)((Uint8 *)ఫలితం + ((అంకె_modes + 1) * పరిమాణం(*ఫలితం)));
        ఒకవేళ (అంకె_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, అంకె_modes * పరిమాణం(*modes));
        }
        కొరకు (i = 0; i < అంకె_modes; ++i) {
            ఫలితం[i] = modes++;
        }
        ఫలితం[i] = ఖాళీ;

        ఒకవేళ (లెక్క) {
            *లెక్క = అంకె_modes;
        }
    } లేకపోతే {
        ఒకవేళ (లెక్క) {
            *లెక్క = 0;
        }
    }
    తిరిగి ఫలితం;
}

bool SDL_Get_Closest_Fullscreen_Display_బహుళకం(SDL_DisplayID displayID, పూర్ణాంకం w, పూర్ణాంకం h, దశాంశం refresh_రేటు, bool include_ఎగువ_density_modes, SDL_Display_బహుళకం *ఫలితం)
{
    CHECK_PARAM(!ఫలితం) {
        తిరిగి SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    స్థిరరాశి SDL_Display_బహుళకం *బహుళకం, *closest = ఖాళీ;
    దశాంశం aspect_నిష్పత్తి;
    పూర్ణాంకం i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(ఫలితం);

    CHECK_DISPLAY_MAGIC(display, false);

    ఒకవేళ (h > 0) {
        aspect_నిష్పత్తి = (దశాంశం)w / h;
    } లేకపోతే {
        aspect_నిష్పత్తి = 1.0f;
    }

    ఒకవేళ (refresh_రేటు == 0.0f) {
        refresh_రేటు = display->desktop_బహుళకం.refresh_రేటు;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    కొరకు (i = 0; i < display->అంకె_fullscreen_modes; ++i) {
        బహుళకం = &display->fullscreen_modes[i];

        ఒకవేళ (w > బహుళకం->w) {
            // Out of sorted modes large enough here
            ఆపు;
        }
        ఒకవేళ (h > బహుళకం->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            కొనసాగు;
        }
        ఒకవేళ (బహుళకం->pixel_density > 1.0f && !include_ఎగువ_density_modes) {
            కొనసాగు;
        }
        ఒకవేళ (closest) {
            దశాంశం current_aspect_నిష్పత్తి = (దశాంశం)బహుళకం->w / బహుళకం->h;
            దశాంశం closest_aspect_నిష్పత్తి = (దశాంశం)closest->w / closest->h;
            ఒకవేళ (SDL_fabsf(aspect_నిష్పత్తి - closest_aspect_నిష్పత్తి) < SDL_fabsf(aspect_నిష్పత్తి - current_aspect_నిష్పత్తి)) {
                // The mode we already found has a better aspect ratio match
                కొనసాగు;
            }

            ఒకవేళ (బహుళకం->w == closest->w && బహుళకం->h == closest->h) {
                ఒకవేళ (SDL_fabsf(closest->refresh_రేటు - refresh_రేటు) < SDL_fabsf(బహుళకం->refresh_రేటు - refresh_రేటు)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    కొనసాగు;
                }
                ఒకవేళ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(బహుళకం->format)) {
                    // Prefer the highest color depth
                    కొనసాగు;
                }
            }
        }

        closest = బహుళకం;
    }
    ఒకవేళ (!closest) {
        తిరిగి SDL_సమితి_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(ఫలితం, closest);

    తిరిగి true;
}

స్థిర bool Display_బహుళకం_మారింది(స్థిరరాశి SDL_Display_బహుళకం *old_బహుళకం, స్థిరరాశి SDL_Display_బహుళకం *new_బహుళకం)
{
    తిరిగి ((old_బహుళకం->displayID && old_బహుళకం->displayID != new_బహుళకం->displayID) ||
            (old_బహుళకం->format && old_బహుళకం->format != new_బహుళకం->format) ||
            (old_బహుళకం->w && old_బహుళకం->h && (old_బహుళకం->w != new_బహుళకం->w ||old_బహుళకం->h != new_బహుళకం->h)) ||
            (old_బహుళకం->pixel_density != 0.0f && old_బహుళకం->pixel_density != new_బహుళకం->pixel_density) ||
            (old_బహుళకం->refresh_రేటు != 0.0f && old_బహుళకం->refresh_రేటు != new_బహుళకం->refresh_రేటు));
}

శూన్య SDL_సమితి_Desktop_Display_బహుళకం(SDL_VideoDisplay *display, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_బహుళకం చివరి_బహుళకం;

    ఒకవేళ (display->fullscreen_చురుకైన) {
        // This is a temporary mode change, don't save the desktop mode
        తిరిగి;
    }

    SDL_copyp(&చివరి_బహుళకం, &display->desktop_బహుళకం);

    SDL_free(display->desktop_బహుళకం.అంతర్గత);
    SDL_copyp(&display->desktop_బహుళకం, బహుళకం);
    display->desktop_బహుళకం.displayID = display->id;
    SDL_Finalize_Display_బహుళకం(&display->desktop_బహుళకం);

    ఒకవేళ (Display_బహుళకం_మారింది(&చివరి_బహుళకం, &display->desktop_బహుళకం)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_బహుళకం_మారింది, బహుళకం->w, బహుళకం->h);
        ఒకవేళ (display->current_బహుళకం == &display->desktop_బహుళకం) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_బహుళకం_మారింది, బహుళకం->w, బహుళకం->h);
        }
    }
}

స్థిరరాశి SDL_Display_బహుళకం *SDL_Get_Desktop_Display_బహుళకం(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ఖాళీ);

    తిరిగి &display->desktop_బహుళకం;
}

శూన్య SDL_సమితి_Current_Display_బహుళకం(SDL_VideoDisplay *display, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_బహుళకం చివరి_బహుళకం;

    ఒకవేళ (display->current_బహుళకం) {
        SDL_copyp(&చివరి_బహుళకం, display->current_బహుళకం);
    } లేకపోతే {
        SDL_zero(చివరి_బహుళకం);
    }

    display->current_బహుళకం = బహుళకం;

    ఒకవేళ (Display_బహుళకం_మారింది(&చివరి_బహుళకం, బహుళకం)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_బహుళకం_మారింది, బహుళకం->w, బహుళకం->h);
    }
}

స్థిరరాశి SDL_Display_బహుళకం *SDL_Get_Current_Display_బహుళకం(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ఖాళీ);

    తిరిగి display->current_బహుళకం;
}

bool SDL_సమితి_Display_బహుళకం_For_Display(SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ఒకవేళ (SDL_బహుళకం_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        తిరిగి true;
    }

    ఒకవేళ (!బహుళకం) {
        బహుళకం = &display->desktop_బహుళకం;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#నిర్వచితం_కాకపోతే SDL_PLATFORM_RISCOS
    ఒకవేళ (బహుళకం == display->current_బహుళకం) {
        తిరిగి true;
    }
#అయితే_ముగింపు

    // Actually change the display mode
    ఒకవేళ (_this->సమితి_Display_బహుళకం) {
        bool ఫలితం;

        _this->setting_display_బహుళకం = true;
        ఫలితం = _this->సమితి_Display_బహుళకం(_this, display, బహుళకం);
        _this->setting_display_బహుళకం = false;
        ఒకవేళ (!ఫలితం) {
            తిరిగి false;
        }
    }

    SDL_సమితి_Current_Display_బహుళకం(display, బహుళకం);

    తిరిగి true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
స్థిర శూన్య SDL_Get_Closest_బిందువు_On_Rect(స్థిరరాశి SDL_Rect *rect, SDL_బిందువు *బిందువు)
{
    స్థిరరాశి పూర్ణాంకం కుడి = rect->x + rect->w - 1;
    స్థిరరాశి పూర్ణాంకం bottom = rect->y + rect->h - 1;

    ఒకవేళ (బిందువు->x < rect->x) {
        బిందువు->x = rect->x;
    } లేకపోతే ఒకవేళ (బిందువు->x > కుడి) {
        బిందువు->x = కుడి;
    }

    ఒకవేళ (బిందువు->y < rect->y) {
        బిందువు->y = rect->y;
    } లేకపోతే ఒకవేళ (బిందువు->y > bottom) {
        బిందువు->y = bottom;
    }
}

స్థిర SDL_DisplayID GetDisplayForRect(పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం w, పూర్ణాంకం h)
{
    పూర్ణాంకం i, dist;
    SDL_DisplayID closest = 0;
    పూర్ణాంకం closest_dist = 0x7FFFFFFF;
    SDL_బిందువు closest_బిందువు_on_display;
    SDL_బిందువు delta;
    SDL_బిందువు center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ఒకవేళ (_this) {
        కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ఒకవేళ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ఖాళీ)) {
                తిరిగి display->id;
            }

            // Snap window center to the display rect
            closest_బిందువు_on_display = center;
            SDL_Get_Closest_బిందువు_On_Rect(&display_rect, &closest_బిందువు_on_display);

            delta.x = center.x - closest_బిందువు_on_display.x;
            delta.y = center.y - closest_బిందువు_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ఒకవేళ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ఒకవేళ (closest == 0) {
        SDL_సమితి_Error("Couldn't find any displays");
    }

    తిరిగి closest;
}

శూన్య SDL_Relative_గమ్యం_Global_For_కిటికీ(SDL_కిటికీ *కిటికీ, పూర్ణాంకం rel_x, పూర్ణాంకం rel_y, పూర్ణాంకం *abs_x, పూర్ణాంకం *abs_y)
{
    SDL_కిటికీ *w;

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        // Calculate the total offset of the popup from the parents
        కొరకు (w = కిటికీ->మాతృ; w; w = w->మాతృ) {
            rel_x += w->x;
            rel_y += w->y;

            ఒకవేళ (!SDL_కిటికీ_IS_POPUP(w)) {
                ఆపు;
            }
        }
    }

    ఒకవేళ (abs_x) {
        *abs_x = rel_x;
    }
    ఒకవేళ (abs_y) {
        *abs_y = rel_y;
    }
}

శూన్య SDL_Global_గమ్యం_Relative_For_కిటికీ(SDL_కిటికీ *కిటికీ, పూర్ణాంకం abs_x, పూర్ణాంకం abs_y, పూర్ణాంకం *rel_x, పూర్ణాంకం *rel_y)
{
    SDL_కిటికీ *w;

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        // Convert absolute window coordinates to relative for a popup
        కొరకు (w = కిటికీ->మాతృ; w; w = w->మాతృ) {
            abs_x -= w->x;
            abs_y -= w->y;

            ఒకవేళ (!SDL_కిటికీ_IS_POPUP(w)) {
                ఆపు;
            }
        }
    }

    ఒకవేళ (rel_x) {
        *rel_x = abs_x;
    }
    ఒకవేళ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_Get_Display_For_బిందువు(స్థిరరాశి SDL_బిందువు *బిందువు)
{
    CHECK_PARAM(!బిందువు) {
        SDL_InvalidParamError("point");
        తిరిగి 0;
    }

    తిరిగి GetDisplayForRect(బిందువు->x, బిందువు->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(స్థిరరాశి SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        తిరిగి 0;
    }

    తిరిగి GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

స్థిర SDL_DisplayID GetDisplayAtOrigin(పూర్ణాంకం x, పూర్ణాంకం y)
{
    కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
        SDL_Rect rect;
        స్థిరరాశి SDL_DisplayID cur_id = _this->displays[i]->id;
        ఒకవేళ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ఒకవేళ (x == rect.x && y == rect.y) {
                తిరిగి cur_id;
            }
        }
    }

    తిరిగి 0;
}

SDL_DisplayID SDL_Get_Display_For_కిటికీ_Position(SDL_కిటికీ *కిటికీ)
{
    పూర్ణాంకం x, y;
    SDL_DisplayID displayID = 0;

    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    ఒకవేళ (_this->Get_Display_For_కిటికీ) {
        displayID = _this->Get_Display_For_కిటికీ(_this, కిటికీ);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, కిటికీ->x, కిటికీ->y, &x, &y);

    ఒకవేళ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } లేకపోతే {
            displayID = GetDisplayForRect(x, y, కిటికీ->w, కిటికీ->h);
        }
    }
    ఒకవేళ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    తిరిగి displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    SDL_DisplayID displayID = 0;

    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);

    // An explicit fullscreen display overrides all
    ఒకవేళ (కిటికీ->current_fullscreen_బహుళకం.displayID) {
        displayID = కిటికీ->current_fullscreen_బహుళకం.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ఒకవేళ (!displayID) {
        displayID = కిటికీ->pending_displayID;
    }
    ఒకవేళ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        స్థిరరాశి పూర్ణాంకం x = కిటికీ->చివరి_position_pending ? కిటికీ->pending.x : కిటికీ->x;
        స్థిరరాశి పూర్ణాంకం y = కిటికీ->చివరి_position_pending ? కిటికీ->pending.y : కిటికీ->y;
        స్థిరరాశి పూర్ణాంకం w = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : కిటికీ->w;
        స్థిరరాశి పూర్ణాంకం h = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : కిటికీ->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ఒకవేళ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ఒకవేళ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    తిరిగి SDL_GetVideoDisplay(displayID);
}

#నిర్వచించు SDL_PROP_SDL2_COMPAT_కిటికీ_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID కిటికీ_props = SDL_Get_కిటికీ_Properties(కిటికీ);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_కిటికీ(కిటికీ);
    ఒకవేళ (fs_display) {
        SDL_సమితి_సంఖ్య_Property(కిటికీ_props, SDL_PROP_SDL2_COMPAT_కిటికీ_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } లేకపోతే {
        SDL_ClearProperty(కిటికీ_props, SDL_PROP_SDL2_COMPAT_కిటికీ_PREFERRED_FULLSCREEN_DISPLAY);
    }

    తిరిగి Get_Display_For_కిటికీ(కిటికీ);
}

స్థిర శూన్య SDL_Check_కిటికీ_Display_మారింది(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (SDL_SendsDisplayChanges(_this)) {
        తిరిగి;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_కిటికీ_Position(కిటికీ);

    ఒకవేళ (displayID != కిటికీ->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect కిటికీ_rect;
        SDL_Rect old_overlap, new_overlap;

        ఒకవేళ (SDL_GetDisplayBounds(కిటికీ->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            కిటికీ_rect.x = కిటికీ->x;
            కిటికీ_rect.y = కిటికీ->y;
            కిటికీ_rect.w = కిటికీ->w;
            కిటికీ_rect.h = కిటికీ->h;

            ఒకవేళ (SDL_GetRectIntersection(&old_bounds, &కిటికీ_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &కిటికీ_rect, &new_overlap)) {
                పూర్ణాంకం old_area = old_overlap.w * old_overlap.h;
                పూర్ణాంకం new_area = new_overlap.w * new_overlap.h;
                దశాంశం new_overlap_నిష్పత్తి = (new_area / ((దశాంశం)old_area + new_area));
                ఒకవేళ (new_overlap_నిష్పత్తి < 0.80) {
                    తిరిగి;
                }
            }
        }
    }

    ఒకవేళ (displayID != కిటికీ->displayID) {
        పూర్ణాంకం i, display_సూచీ;

        // Sanity check our fullscreen windows
        display_సూచీ = SDL_Get_Display_సూచీ(displayID);
        కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ఒకవేళ (display->fullscreen_కిటికీ == కిటికీ) {
                ఒకవేళ (display_సూచీ != i) {
                    ఒకవేళ (display_సూచీ < 0) {
                        display_సూచీ = i;
                    } లేకపోతే {
                        SDL_VideoDisplay *new_display = _this->displays[display_సూచీ];

                        // The window was moved to a different display
                        ఒకవేళ (new_display->fullscreen_కిటికీ &&
                            new_display->fullscreen_కిటికీ != కిటికీ) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_కిటికీ(new_display->fullscreen_కిటికీ);
                        }
                        new_display->fullscreen_కిటికీ = కిటికీ;
                        display->fullscreen_కిటికీ = ఖాళీ;
                    }
                }
                ఆపు;
            }
        }

        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_DISPLAY_మారింది, (పూర్ణాంకం)displayID, 0);
    }
}

దశాంశం SDL_Get_కిటికీ_Pixel_Density(SDL_కిటికీ *కిటికీ)
{
    పూర్ణాంకం కిటికీ_w, కిటికీ_h, pixel_w, pixel_h;
    దశాంశం pixel_density = 1.0f;

    CHECK_కిటికీ_MAGIC(కిటికీ, 0.0f);

    ఒకవేళ (SDL_Get_కిటికీ_కొలత(కిటికీ, &కిటికీ_w, &కిటికీ_h) &&
        SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &pixel_w, &pixel_h)) {
        pixel_density = (దశాంశం)pixel_w / కిటికీ_w;
    }
    తిరిగి pixel_density;
}

దశాంశం SDL_Get_కిటికీ_Display_Scale(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0.0f);

    తిరిగి కిటికీ->display_scale;
}

స్థిర శూన్య SDL_Check_కిటికీ_Display_Scale_మారింది(SDL_కిటికీ *కిటికీ)
{
    దశాంశం display_scale;

    ఒకవేళ (_this->Get_కిటికీ_Content_Scale) {
        display_scale = _this->Get_కిటికీ_Content_Scale(_this, కిటికీ);
    } లేకపోతే {
        స్థిరరాశి దశాంశం pixel_density = SDL_Get_కిటికీ_Pixel_Density(కిటికీ);
        స్థిరరాశి దశాంశం content_scale = SDL_GetDisplayContentScale(కిటికీ->displayID);

        display_scale = pixel_density * content_scale;
    }

    ఒకవేళ (display_scale != కిటికీ->display_scale) {
        కిటికీ->display_scale = display_scale;
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_DISPLAY_SCALE_మారింది, 0, 0);
    }
}

bool SDL_Update_Fullscreen_బహుళకం(SDL_కిటికీ *కిటికీ, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ఖాళీ;
    SDL_Display_బహుళకం *బహుళకం = ఖాళీ;
    పూర్ణాంకం i;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    కిటికీ->fullscreen_exclusive = false;
    కిటికీ->update_fullscreen_on_display_మారింది = false;

    // If we are in the process of hiding don't go back to fullscreen
    ఒకవేళ (కిటికీ->is_destroying || కిటికీ->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ఒకవేళ (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_కిటికీ(కిటికీ);
        ఒకవేళ (!display) {
            // This should never happen, but it did...
            వెళ్ళు పూర్తి;
        }
    } లేకపోతే {
        కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
            display = _this->displays[i];
            ఒకవేళ (display->fullscreen_కిటికీ == కిటికీ) {
                ఆపు;
            }
        }
        ఒకవేళ (!display || i == _this->అంకె_displays) {
            // Already not fullscreen on any display
            display = ఖాళీ;
        }
    }

    ఒకవేళ (fullscreen) {
        బహుళకం = (SDL_Display_బహుళకం *)SDL_Get_కిటికీ_Fullscreen_బహుళకం(కిటికీ);
        ఒకవేళ (బహుళకం) {
            కిటికీ->fullscreen_exclusive = true;
        } లేకపోతే {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(కిటికీ->current_fullscreen_బహుళకం);
        }
    }

#ఒకవేళ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ఒకవేళ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ఒకవేళ (కిటికీ->is_destroying && !కిటికీ->చివరి_fullscreen_exclusive_display) {
            కిటికీ->fullscreen_exclusive = false;
            ఒకవేళ (display) {
                display->fullscreen_కిటికీ = ఖాళీ;
            }
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ఒకవేళ (fullscreen && Cocoa_Is_కిటికీ_లోపల_Fullscreen_Space(కిటికీ) && !కిటికీ->చివరి_fullscreen_exclusive_display && కిటికీ->fullscreen_exclusive) {
                ఒకవేళ (!Cocoa_సమితి_కిటికీ_Fullscreen_Space(కిటికీ, false, true)) {
                    వెళ్ళు error;
                }
            } లేకపోతే ఒకవేళ (fullscreen && కిటికీ->చివరి_fullscreen_exclusive_display && !కిటికీ->fullscreen_exclusive) {
                కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
                    SDL_VideoDisplay *చివరి_display = _this->displays[i];
                    ఒకవేళ (చివరి_display->fullscreen_కిటికీ == కిటికీ) {
                        SDL_సమితి_Display_బహుళకం_For_Display(చివరి_display, ఖాళీ);
                        ఒకవేళ (_this->సమితి_కిటికీ_Fullscreen) {
                            _this->సమితి_కిటికీ_Fullscreen(_this, కిటికీ, చివరి_display, false);
                        }
                        చివరి_display->fullscreen_కిటికీ = ఖాళీ;
                    }
                }
            }

            ఒకవేళ (Cocoa_సమితి_కిటికీ_Fullscreen_Space(కిటికీ, !!fullscreen, syncHint)) {
                వెళ్ళు పూర్తి;
            }
        }
    }
#అయితే_ముగింపు

    ఒకవేళ (display) {
        // Restore the video mode on other displays if needed
        కొరకు (i = 0; i < _this->అంకె_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ఒకవేళ (other != display && other->fullscreen_కిటికీ == కిటికీ) {
                SDL_సమితి_Display_బహుళకం_For_Display(other, ఖాళీ);
                other->fullscreen_కిటికీ = ఖాళీ;
            }
        }
    }

    ఒకవేళ (fullscreen) {
        పూర్ణాంకం బహుళకం_w = 0, బహుళకం_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ఒకవేళ (display->fullscreen_కిటికీ &&
            display->fullscreen_కిటికీ != కిటికీ) {
            SDL_Minimize_కిటికీ(display->fullscreen_కిటికీ);
        }

        display->fullscreen_చురుకైన = కిటికీ->fullscreen_exclusive;

        ఒకవేళ (!SDL_సమితి_Display_బహుళకం_For_Display(display, బహుళకం)) {
            వెళ్ళు error;
        }
        ఒకవేళ (commit) {
            SDL_Fullscreen_ఫలితం ret = SDL_FULLSCREEN_SUCCEEDED;
            ఒకవేళ (_this->సమితి_కిటికీ_Fullscreen) {
                ret = _this->సమితి_కిటికీ_Fullscreen(_this, కిటికీ, display, fullscreen);
            } లేకపోతే {
                resized = true;
            }

            ఒకవేళ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
                    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_ENTER_FULLSCREEN, 0, 0);
                }
            } లేకపోతే ఒకవేళ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_చురుకైన = false;
                వెళ్ళు error;
            }
        }

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
            display->fullscreen_కిటికీ = కిటికీ;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ఒకవేళ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ఒకవేళ (బహుళకం) {
                    బహుళకం_w = బహుళకం->w;
                    బహుళకం_h = బహుళకం->h;
                    SDL_GetDisplayBounds(బహుళకం->displayID, &displayRect);
                } లేకపోతే {
                    బహుళకం_w = display->desktop_బహుళకం.w;
                    బహుళకం_h = display->desktop_బహుళకం.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ఒకవేళ (కిటికీ->w != బహుళకం_w || కిటికీ->h != బహుళకం_h) {
                    resized = true;
                }

                SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, displayRect.x, displayRect.y);

                ఒకవేళ (resized) {
                    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, బహుళకం_w, బహుళకం_h);
                } లేకపోతే {
                    SDL_On_కిటికీ_Resized(కిటికీ);
                }
            }
        }
    } లేకపోతే {
        bool resized = false;

        // Restore the desktop mode
        ఒకవేళ (display) {
            display->fullscreen_చురుకైన = false;

            SDL_సమితి_Display_బహుళకం_For_Display(display, ఖాళీ);
        }
        ఒకవేళ (commit) {
            SDL_Fullscreen_ఫలితం ret = SDL_FULLSCREEN_SUCCEEDED;
            ఒకవేళ (_this->సమితి_కిటికీ_Fullscreen) {
                SDL_VideoDisplay *నిండిన_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_కిటికీ(కిటికీ);
                ఒకవేళ (నిండిన_screen_display) {
                    ret = _this->సమితి_కిటికీ_Fullscreen(_this, కిటికీ, నిండిన_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } లేకపోతే {
                resized = true;
            }

            ఒకవేళ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
                    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);
                }
            } లేకపోతే ఒకవేళ (ret == SDL_FULLSCREEN_FAILED) {
                వెళ్ళు error;
            }
        }

        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
            ఒకవేళ (display) {
                display->fullscreen_కిటికీ = ఖాళీ;
            }

            ఒకవేళ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, కిటికీ->windowed.x, కిటికీ->windowed.y);
                ఒకవేళ (resized) {
                    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ->windowed.w, కిటికీ->windowed.h);
                } లేకపోతే {
                    SDL_On_కిటికీ_Resized(కిటికీ);
                }
            }
        }
    }

పూర్తి:
    కిటికీ->చివరి_fullscreen_exclusive_display = display && (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && కిటికీ->fullscreen_exclusive ? display->id : 0;
    తిరిగి true;

error:
    ఒకవేళ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    తిరిగి false;
}

bool SDL_సమితి_కిటికీ_Fullscreen_బహుళకం(SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Display_బహుళకం *బహుళకం)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (బహుళకం) {
        ఒకవేళ (!SDL_Get_Fullscreen_బహుళకం_సరిపోలిక(బహుళకం)) {
            తిరిగి SDL_సమితి_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&కిటికీ->requested_fullscreen_బహుళకం, బహుళకం);
    } లేకపోతే {
        SDL_zero(కిటికీ->requested_fullscreen_బహుళకం);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&కిటికీ->current_fullscreen_బహుళకం, &కిటికీ->requested_fullscreen_బహుళకం);

#ఒకవేళ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ఒకవేళ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_కిటికీ_లోపల_Fullscreen_Space_Transition(కిటికీ)) {
        SDL_Sync_కిటికీ(కిటికీ);
    }
#అయితే_ముగింపు
    ఒకవేళ (SDL_కిటికీ_FULLSCREEN_VISIBLE(కిటికీ)) {
        SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(కిటికీ);
    }

    తిరిగి true;
}

స్థిరరాశి SDL_Display_బహుళకం *SDL_Get_కిటికీ_Fullscreen_బహుళకం(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, ఖాళీ);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        తిరిగి SDL_Get_Fullscreen_బహుళకం_సరిపోలిక(&కిటికీ->current_fullscreen_బహుళకం);
    } లేకపోతే {
        తిరిగి SDL_Get_Fullscreen_బహుళకం_సరిపోలిక(&కిటికీ->requested_fullscreen_బహుళకం);
    }
}

శూన్య *SDL_Get_కిటికీ_ICCProfile(SDL_కిటికీ *కిటికీ, size_t *కొలత)
{
    ఒకవేళ (!_this->Get_కిటికీ_ICCProfile) {
        SDL_Unsupported();
        తిరిగి ఖాళీ;
    }
    తిరిగి _this->Get_కిటికీ_ICCProfile(_this, కిటికీ, కొలత);
}

SDL_PixelFormat SDL_Get_కిటికీ_Pixel_Format(SDL_కిటికీ *కిటికీ)
{
    SDL_DisplayID displayID;
    స్థిరరాశి SDL_Display_బహుళకం *బహుళకం;

    CHECK_కిటికీ_MAGIC(కిటికీ, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_కిటికీ(కిటికీ);
    బహుళకం = SDL_Get_Current_Display_బహుళకం(displayID);
    ఒకవేళ (బహుళకం) {
        తిరిగి బహుళకం->format;
    } లేకపోతే {
        తిరిగి SDL_PIXELFORMAT_UNKNOWN;
    }
}

#నిర్వచించు CREATE_FLAGS \
    (SDL_కిటికీ_OPENGL | SDL_కిటికీ_BORDERLESS | SDL_కిటికీ_RESIZABLE | SDL_కిటికీ_ఎగువ_PIXEL_DENSITY | SDL_కిటికీ_ALWAYS_ON_శిఖరం | SDL_కిటికీ_POPUP_MENU | SDL_కిటికీ_UTILITY | SDL_కిటికీ_TOOLTIP | SDL_కిటికీ_VULKAN | SDL_కిటికీ_MINIMIZED | SDL_కిటికీ_METAL | SDL_కిటికీ_TRANSPARENT | SDL_కిటికీ_NOT_FOCUSABLE | SDL_కిటికీ_FILL_DOCUMENT)

స్థిర SDL_INLINE bool IsAcceptingDragAndDrop(శూన్య)
{
    ఒకవేళ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_పాఠ్యం)) {
        తిరిగి true;
    }
    తిరిగి false;
}

// prepare a newly-created window
స్థిర SDL_INLINE శూన్య PrepareDragAndDropSupport(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(కిటికీ, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
శూన్య SDL_ToggleDragAndDropSupport(శూన్య)
{
    ఒకవేళ (_this && _this->AcceptDragAndDrop) {
        స్థిరరాశి bool enable = IsAcceptingDragAndDrop();
        SDL_కిటికీ *కిటికీ;
        కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            _this->AcceptDragAndDrop(కిటికీ, enable);
        }
    }
}

SDL_కిటికీ ** SDLCALL SDL_GetWindows(పూర్ణాంకం *లెక్క)
{
    ఒకవేళ (లెక్క) {
        *లెక్క = 0;
    }

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }

    SDL_కిటికీ *కిటికీ;
    పూర్ణాంకం అంకె_added = 0;
    పూర్ణాంకం అంకె_windows = 0;
    కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        ++అంకె_windows;
    }

    SDL_కిటికీ **windows = (SDL_కిటికీ **)SDL_malloc((అంకె_windows + 1) * పరిమాణం(*windows));
    ఒకవేళ (!windows) {
        తిరిగి ఖాళీ;
    }

    కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        windows[అంకె_added++] = కిటికీ;
        ఒకవేళ (అంకె_added == అంకె_windows) {
            // Race condition? Multi-threading not supported, ignore it
            ఆపు;
        }
    }
    windows[అంకె_added] = ఖాళీ;

    ఒకవేళ (లెక్క) {
        *లెక్క = అంకె_added;
    }
    తిరిగి windows;
}

స్థిర శూన్య Apply_కిటికీ_Flags(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags)
{
    ఒకవేళ (!SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        ఒకవేళ (!(flags & (SDL_కిటికీ_MINIMIZED | SDL_కిటికీ_MAXIMIZED))) {
            SDL_Restore_కిటికీ(కిటికీ);
        }
        ఒకవేళ (flags & SDL_కిటికీ_MAXIMIZED) {
            SDL_Maximize_కిటికీ(కిటికీ);
        }

        SDL_సమితి_కిటికీ_Fullscreen(కిటికీ, (flags & SDL_కిటికీ_FULLSCREEN) != 0);

        ఒకవేళ (flags & SDL_కిటికీ_MINIMIZED) {
            SDL_Minimize_కిటికీ(కిటికీ);
        }

        ఒకవేళ (flags & SDL_కిటికీ_MODAL) {
            SDL_సమితి_కిటికీ_Modal(కిటికీ, true);
        }

        ఒకవేళ (flags & SDL_కిటికీ_MOUSE_GRABBED) {
            SDL_సమితి_కిటికీ_Mouse_Grab(కిటికీ, true);
        }
        ఒకవేళ (flags & SDL_కిటికీ_KEYBOARD_GRABBED) {
            SDL_సమితి_కిటికీ_Keyboard_Grab(కిటికీ, true);
        }
    }
}

స్థిర శూన్య SDL_ముగింపు_కిటికీ_Creation(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags)
{
    PrepareDragAndDropSupport(కిటికీ);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } లేకపోతే {
        Apply_కిటికీ_Flags(కిటికీ, flags);
        ఒకవేళ (!(flags & SDL_కిటికీ_HIDDEN)) {
            SDL_Show_కిటికీ(కిటికీ);
        }
    }

#ఒకవేళ defined(SDL_PLATFORM_LINUX)
    ఒకవేళ (!SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_సమితి_కిటికీ_పురోగతి_State(కిటికీ, SDL_పురోగతి_STATE_NONE);
        SDL_సమితి_కిటికీ_పురోగతి_విలువ(కిటికీ, 0.0f);
    }
#అయితే_ముగింపు
}

స్థిర bool SDL_ContextNotSupported(స్థిరరాశి అక్షరం *name)
{
    తిరిగి SDL_సమితి_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

స్థిర bool SDL_DllNotSupported(స్థిరరాశి అక్షరం *name)
{
    తిరిగి SDL_సమితి_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

స్థిర నిర్మాణం {
    స్థిరరాశి అక్షరం *property_name;
    SDL_కిటికీ_Flags flag;
    bool invert_విలువ;
} SDL_కిటికీ_Flag_Properties[] = {
    { SDL_PROP_కిటికీ_CREATE_ALWAYS_ON_శిఖరం_BOOLEAN,      SDL_కిటికీ_ALWAYS_ON_శిఖరం,       false },
    { SDL_PROP_కిటికీ_CREATE_BORDERLESS_BOOLEAN,         SDL_కిటికీ_BORDERLESS,          false },
    { SDL_PROP_కిటికీ_CREATE_FOCUSABLE_BOOLEAN,          SDL_కిటికీ_NOT_FOCUSABLE,       true },
    { SDL_PROP_కిటికీ_CREATE_FULLSCREEN_BOOLEAN,         SDL_కిటికీ_FULLSCREEN,          false },
    { SDL_PROP_కిటికీ_CREATE_HIDDEN_BOOLEAN,             SDL_కిటికీ_HIDDEN,              false },
    { SDL_PROP_కిటికీ_CREATE_ఎగువ_PIXEL_DENSITY_BOOLEAN, SDL_కిటికీ_ఎగువ_PIXEL_DENSITY,  false },
    { SDL_PROP_కిటికీ_CREATE_MAXIMIZED_BOOLEAN,          SDL_కిటికీ_MAXIMIZED,           false },
    { SDL_PROP_కిటికీ_CREATE_MENU_BOOLEAN,               SDL_కిటికీ_POPUP_MENU,          false },
    { SDL_PROP_కిటికీ_CREATE_METAL_BOOLEAN,              SDL_కిటికీ_METAL,               false },
    { SDL_PROP_కిటికీ_CREATE_MINIMIZED_BOOLEAN,          SDL_కిటికీ_MINIMIZED,           false },
    { SDL_PROP_కిటికీ_CREATE_MODAL_BOOLEAN,              SDL_కిటికీ_MODAL,               false },
    { SDL_PROP_కిటికీ_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_కిటికీ_MOUSE_GRABBED,       false },
    { SDL_PROP_కిటికీ_CREATE_OPENGL_BOOLEAN,             SDL_కిటికీ_OPENGL,              false },
    { SDL_PROP_కిటికీ_CREATE_RESIZABLE_BOOLEAN,          SDL_కిటికీ_RESIZABLE,           false },
    { SDL_PROP_కిటికీ_CREATE_TRANSPARENT_BOOLEAN,        SDL_కిటికీ_TRANSPARENT,         false },
    { SDL_PROP_కిటికీ_CREATE_TOOLTIP_BOOLEAN,            SDL_కిటికీ_TOOLTIP,             false },
    { SDL_PROP_కిటికీ_CREATE_UTILITY_BOOLEAN,            SDL_కిటికీ_UTILITY,             false },
    { SDL_PROP_కిటికీ_CREATE_VULKAN_BOOLEAN,             SDL_కిటికీ_VULKAN,              false }
};

స్థిర SDL_కిటికీ_Flags SDL_Get_కిటికీ_Flag_Properties(SDL_PropertiesID props)
{
    గుర్తులేని i;
    SDL_కిటికీ_Flags flags = (SDL_కిటికీ_Flags)SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_FLAGS_సంఖ్య, 0);

    కొరకు (i = 0; i < SDL_arraysize(SDL_కిటికీ_Flag_Properties); ++i) {
        ఒకవేళ (SDL_కిటికీ_Flag_Properties[i].invert_విలువ) {
            ఒకవేళ (!SDL_GetBooleanProperty(props, SDL_కిటికీ_Flag_Properties[i].property_name, true)) {
                flags |= SDL_కిటికీ_Flag_Properties[i].flag;
            }
        } లేకపోతే {
            ఒకవేళ (SDL_GetBooleanProperty(props, SDL_కిటికీ_Flag_Properties[i].property_name, false)) {
                flags |= SDL_కిటికీ_Flag_Properties[i].flag;
            }
        }
    }
    తిరిగి flags;
}

SDL_కిటికీ *SDL_Create_కిటికీ_With_Properties(SDL_PropertiesID props)
{
    SDL_కిటికీ *కిటికీ;
    స్థిరరాశి అక్షరం *title = SDL_GetStringProperty(props, SDL_PROP_కిటికీ_CREATE_TITLE_STRING, ఖాళీ);
    పూర్ణాంకం x = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_X_సంఖ్య, SDL_WINDOWPOS_UNDEFINED);
    పూర్ణాంకం y = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_Y_సంఖ్య, SDL_WINDOWPOS_UNDEFINED);
    పూర్ణాంకం w = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_వెడల్పు_సంఖ్య, 0);
    పూర్ణాంకం h = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_ఎత్తు_సంఖ్య, 0);
    SDL_కిటికీ *మాతృ = (SDL_కిటికీ *)SDL_Get_సూచిక_Property(props, SDL_PROP_కిటికీ_CREATE_మాతృ_సూచిక, ఖాళీ);
    SDL_కిటికీ_Flags flags = SDL_Get_కిటికీ_Flag_Properties(props);
    SDL_కిటికీ_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_కిటికీ_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ఒకవేళ (!_this) {
        // Initialize the video system if needed
        ఒకవేళ (!SDL_Init(SDL_INIT_VIDEO)) {
            తిరిగి ఖాళీ;
        }

        // Make clang-tidy happy
        ఒకవేళ (!_this) {
            తిరిగి ఖాళీ;
        }
    }

    ఒకవేళ ((flags & SDL_కిటికీ_MODAL) && !SDL_ObjectValid(మాతృ, SDL_OBJECT_TYPE_కిటికీ)) {
        SDL_సమితి_Error("Modal windows must specify a parent window");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ ((flags & (SDL_కిటికీ_TOOLTIP | SDL_కిటికీ_POPUP_MENU)) != 0) {
        ఒకవేళ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_కిటికీ_SUPPORT)) {
            SDL_Unsupported();
            తిరిగి ఖాళీ;
        }

        // Tooltip and popup menu window must specify a parent window
        ఒకవేళ (!SDL_ObjectValid(మాతృ, SDL_OBJECT_TYPE_కిటికీ)) {
            SDL_సమితి_Error("Tooltip and popup menu windows must specify a parent window");
            తిరిగి ఖాళీ;
        }

        // Remove invalid flags
        flags &= ~(SDL_కిటికీ_MINIMIZED | SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_కిటికీ_UTILITY | SDL_కిటికీ_TOOLTIP | SDL_కిటికీ_POPUP_MENU | SDL_కిటికీ_MODAL);
    ఒకవేళ (type_flags & (type_flags - 1)) {
        SDL_సమితి_Error("Conflicting window type flags specified: 0x%.8x", (గుర్తులేని పూర్ణాంకం)type_flags);
        తిరిగి ఖాళీ;
    }

    // Make sure the display list is up to date for window placement
    ఒకవేళ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ఒకవేళ (w < 1) {
        w = 1;
    }
    ఒకవేళ (h < 1) {
        h = 1;
    }

    ఒకవేళ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ఒకవేళ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } లేకపోతే ఒకవేళ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ఒకవేళ (displayID == 0 || SDL_Get_Display_సూచీ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ఒకవేళ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ఒకవేళ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ఒకవేళ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_కిటికీ_OPENGL | SDL_కిటికీ_METAL | SDL_కిటికీ_VULKAN);
    ఒకవేళ (graphics_flags & (graphics_flags - 1)) {
        SDL_సమితి_Error("Conflicting window graphics flags specified: 0x%.8x", (గుర్తులేని పూర్ణాంకం)graphics_flags);
        తిరిగి ఖాళీ;
    }

    // Some platforms have certain graphics backends enabled by default
    ఒకవేళ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ఒకవేళ (flags & SDL_కిటికీ_OPENGL) {
        ఒకవేళ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            తిరిగి ఖాళీ;
        }
        ఒకవేళ (!SDL_GL_ఎక్కించు_Library(ఖాళీ)) {
            తిరిగి ఖాళీ;
        }
    }

    ఒకవేళ (flags & SDL_కిటికీ_VULKAN) {
        ఒకవేళ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            తిరిగి ఖాళీ;
        }
        ఒకవేళ (!SDL_Vulkan_ఎక్కించు_Library(ఖాళీ)) {
            తిరిగి ఖాళీ;
        }
    }

    ఒకవేళ (flags & SDL_కిటికీ_METAL) {
        ఒకవేళ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            తిరిగి ఖాళీ;
        }
    }

    కిటికీ = (SDL_కిటికీ *)SDL_calloc(1, పరిమాణం(*కిటికీ));
    ఒకవేళ (!కిటికీ) {
        తిరిగి ఖాళీ;
    }
    SDL_సమితి_Object_Valid(కిటికీ, SDL_OBJECT_TYPE_కిటికీ, true);
    కిటికీ->id = SDL_Get_తదుపరి_Object_ID();
    కిటికీ->floating.x = కిటికీ->windowed.x = కిటికీ->x = x;
    కిటికీ->floating.y = కిటికీ->windowed.y = కిటికీ->y = y;
    కిటికీ->floating.w = కిటికీ->windowed.w = కిటికీ->w = w;
    కిటికీ->floating.h = కిటికీ->windowed.h = కిటికీ->h = h;
    కిటికీ->undefined_x = undefined_x;
    కిటికీ->undefined_y = undefined_y;
    కిటికీ->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_కిటికీ(కిటికీ);
    ఒకవేళ (display) {
        SDL_సమితి_కిటికీ_HDRProperties(కిటికీ, &display->HDR, false);
    }

    ఒకవేళ (flags & SDL_కిటికీ_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        కిటికీ->x = bounds.x;
        కిటికీ->y = bounds.y;
        కిటికీ->w = bounds.w;
        కిటికీ->h = bounds.h;
        కిటికీ->pending_flags |= SDL_కిటికీ_FULLSCREEN;
        flags |= SDL_కిటికీ_FULLSCREEN;
    }

    కిటికీ->flags = ((flags & CREATE_FLAGS) | SDL_కిటికీ_HIDDEN);
    కిటికీ->display_scale = 1.0f;
    కిటికీ->opacity = 1.0f;
    కిటికీ->తదుపరి = _this->windows;
    కిటికీ->is_destroying = false;
    కిటికీ->displayID = Get_Display_For_కిటికీ(కిటికీ);
    కిటికీ->external_graphics_context = external_graphics_context;
    కిటికీ->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_కిటికీ_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    ఒకవేళ (!_this->సమితి_కిటికీ_Fill_Document) {
        కిటికీ->flags &= ~SDL_కిటికీ_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ఒకవేళ (_this->windows) {
        _this->windows->prev = కిటికీ;
    }
    _this->windows = కిటికీ;

    // Set the parent before creation.
    SDL_Update_కిటికీ_Hierarchy(కిటికీ, మాతృ);

    ఒకవేళ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, కిటికీ, props)) {
        SDL_నెట్టు_Error();
        SDL_Destroy_కిటికీ(కిటికీ);
        SDL_తీయి_Error();
        తిరిగి ఖాళీ;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ఒకవేళ !defined(SDL_PLATFORM_WINDOWS)
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
        కిటికీ->flags &= ~SDL_కిటికీ_MINIMIZED;
    }
#అయితే_ముగింపు

    ఒకవేళ (title) {
        SDL_సమితి_కిటికీ_Title(కిటికీ, title);
    }
    SDL_ముగింపు_కిటికీ_Creation(కిటికీ, flags);

    // Make sure window pixel size is up to date
    SDL_Check_కిటికీ_Pixel_కొలత_మారింది(కిటికీ);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#అయితే_ముగింపు

    SDL_ClearError();

    తిరిగి కిటికీ;
}

SDL_కిటికీ *SDL_Create_కిటికీ(స్థిరరాశి అక్షరం *title, పూర్ణాంకం w, పూర్ణాంకం h, SDL_కిటికీ_Flags flags)
{
    SDL_కిటికీ *కిటికీ;
    SDL_PropertiesID props = SDL_CreateProperties();
    ఒకవేళ (title && *title) {
        SDL_సమితి_String_Property(props, SDL_PROP_కిటికీ_CREATE_TITLE_STRING, title);
    }
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_వెడల్పు_సంఖ్య, w);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_ఎత్తు_సంఖ్య, h);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_FLAGS_సంఖ్య, flags);
    కిటికీ = SDL_Create_కిటికీ_With_Properties(props);
    SDL_DestroyProperties(props);
    తిరిగి కిటికీ;
}

SDL_కిటికీ *SDL_Create_Popup_కిటికీ(SDL_కిటికీ *మాతృ, పూర్ణాంకం స్థానభ్రంశం_x, పూర్ణాంకం స్థానభ్రంశం_y, పూర్ణాంకం w, పూర్ణాంకం h, SDL_కిటికీ_Flags flags)
{
    SDL_కిటికీ *కిటికీ;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ఒకవేళ (!(flags & (SDL_కిటికీ_TOOLTIP | SDL_కిటికీ_POPUP_MENU))) {
        SDL_సమితి_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        తిరిగి ఖాళీ;
    }

    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_CREATE_మాతృ_సూచిక, మాతృ);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_X_సంఖ్య, స్థానభ్రంశం_x);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_Y_సంఖ్య, స్థానభ్రంశం_y);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_వెడల్పు_సంఖ్య, w);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_ఎత్తు_సంఖ్య, h);
    SDL_సమితి_సంఖ్య_Property(props, SDL_PROP_కిటికీ_CREATE_FLAGS_సంఖ్య, flags);
    కిటికీ = SDL_Create_కిటికీ_With_Properties(props);
    SDL_DestroyProperties(props);
    తిరిగి కిటికీ;
}

స్థిర bool SDL_Reconfigure_కిటికీ_అంతర్గత(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ఒకవేళ (!_this->Reconfigure_కిటికీ) {
        తిరిగి false;
    }

    స్థిరరాశి SDL_కిటికీ_Flags graphics_flags = flags & (SDL_కిటికీ_OPENGL | SDL_కిటికీ_METAL | SDL_కిటికీ_VULKAN);
    ఒకవేళ (graphics_flags & (graphics_flags - 1)) {
        తిరిగి SDL_సమితి_Error("Conflicting window flags specified");
    }

    ఒకవేళ ((flags & SDL_కిటికీ_OPENGL) && !_this->GL_CreateContext) {
        తిరిగి SDL_ContextNotSupported("OpenGL");
    }
    ఒకవేళ ((flags & SDL_కిటికీ_VULKAN) && !_this->Vulkan_CreateSurface) {
        తిరిగి SDL_ContextNotSupported("Vulkan");
    }
    ఒకవేళ ((flags & SDL_కిటికీ_METAL) && !_this->Metal_CreateView) {
        తిరిగి SDL_ContextNotSupported("Metal");
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ఒకవేళ (కిటికీ->flags & (SDL_కిటికీ_OPENGL | SDL_కిటికీ_METAL | SDL_కిటికీ_VULKAN)) {
            తిరిగి false;
        }
    } లేకపోతే {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ఒకవేళ (!_this->Reconfigure_కిటికీ(_this, కిటికీ, 0)) {
            తిరిగి false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        కిటికీ->flags &= ~(SDL_కిటికీ_OPENGL | SDL_కిటికీ_METAL | SDL_కిటికీ_VULKAN);
    }

    SDL_Destroy_కిటికీ_Surface(కిటికీ);

    ఒకవేళ (graphics_flags & SDL_కిటికీ_OPENGL) {
        loaded_opengl = SDL_GL_ఎక్కించు_Library(ఖాళీ);
        ఒకవేళ (!loaded_opengl) {
            తిరిగి false;
        }
    } లేకపోతే ఒకవేళ (graphics_flags & SDL_కిటికీ_VULKAN) {
        loaded_vulkan = SDL_Vulkan_ఎక్కించు_Library(ఖాళీ);
        ఒకవేళ (!loaded_vulkan) {
            తిరిగి false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ఒకవేళ (!_this->Reconfigure_కిటికీ(_this, కిటికీ, graphics_flags)) {
        ఒకవేళ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ఒకవేళ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        తిరిగి false;
    }

    కిటికీ->flags |= graphics_flags;

    తిరిగి true;
}

bool SDL_Recreate_కిటికీ(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_ఎక్కించు = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_ఎక్కించు = false;
    SDL_కిటికీ_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_కిటికీ_OPENGL | SDL_కిటికీ_METAL | SDL_కిటికీ_VULKAN);
    ఒకవేళ (graphics_flags & (graphics_flags - 1)) {
        తిరిగి SDL_సమితి_Error("Conflicting window flags specified");
    }

    ఒకవేళ ((flags & SDL_కిటికీ_OPENGL) && !_this->GL_CreateContext) {
        తిరిగి SDL_ContextNotSupported("OpenGL");
    }
    ఒకవేళ ((flags & SDL_కిటికీ_VULKAN) && !_this->Vulkan_CreateSurface) {
        తిరిగి SDL_ContextNotSupported("Vulkan");
    }
    ఒకవేళ ((flags & SDL_కిటికీ_METAL) && !_this->Metal_CreateView) {
        తిరిగి SDL_ContextNotSupported("Metal");
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_కిటికీ_EXTERNAL;
    } లేకపోతే {
        flags &= ~SDL_కిటికీ_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MODAL) {
        SDL_సమితి_కిటికీ_Modal(కిటికీ, false);
    }

    // Restore video mode, etc.
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
        స్థిరరాశి bool restore_on_show = కిటికీ->restore_on_show;
        SDL_Hide_కిటికీ(కిటికీ);
        కిటికీ->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_కిటికీ_Surface(కిటికీ);

    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_OPENGL) != (flags & SDL_కిటికీ_OPENGL)) {
        ఒకవేళ (flags & SDL_కిటికీ_OPENGL) {
            need_gl_ఎక్కించు = true;
        } లేకపోతే {
            need_gl_unload = true;
        }
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        need_gl_unload = true;
        need_gl_ఎక్కించు = true;
    }

    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_VULKAN) != (flags & SDL_కిటికీ_VULKAN)) {
        ఒకవేళ (flags & SDL_కిటికీ_VULKAN) {
            need_vulkan_ఎక్కించు = true;
        } లేకపోతే {
            need_vulkan_unload = true;
        }
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_ఎక్కించు = true;
    }

    ఒకవేళ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ఒకవేళ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ఒకవేళ (_this->Destroy_కిటికీ && !(flags & SDL_కిటికీ_EXTERNAL)) {
        _this->Destroy_కిటికీ(_this, కిటికీ);
    }

    ఒకవేళ (need_gl_ఎక్కించు) {
        ఒకవేళ (!SDL_GL_ఎక్కించు_Library(ఖాళీ)) {
            తిరిగి false;
        }
        loaded_opengl = true;
    }

    ఒకవేళ (need_vulkan_ఎక్కించు) {
        ఒకవేళ (!SDL_Vulkan_ఎక్కించు_Library(ఖాళీ)) {
            తిరిగి false;
        }
        loaded_vulkan = true;
    }

    కిటికీ->flags = ((flags & CREATE_FLAGS) | SDL_కిటికీ_HIDDEN);
    కిటికీ->is_destroying = false;

    ఒకవేళ (_this->CreateSDLWindow && !(flags & SDL_కిటికీ_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        కిటికీ->x = కిటికీ->windowed.x = కిటికీ->floating.x;
        కిటికీ->y = కిటికీ->windowed.y = కిటికీ->floating.y;
        కిటికీ->w = కిటికీ->windowed.w = కిటికీ->floating.w;
        కిటికీ->h = కిటికీ->windowed.h = కిటికీ->floating.h;

        ఒకవేళ (!_this->CreateSDLWindow(_this, కిటికీ, 0)) {
            ఒకవేళ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                కిటికీ->flags &= ~SDL_కిటికీ_OPENGL;
            }
            ఒకవేళ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                కిటికీ->flags &= ~SDL_కిటికీ_VULKAN;
            }
            తిరిగి false;
        }
    }

    ఒకవేళ (flags & SDL_కిటికీ_EXTERNAL) {
        కిటికీ->flags |= SDL_కిటికీ_EXTERNAL;
    }

    ఒకవేళ (_this->సమితి_కిటికీ_Title && కిటికీ->title) {
        _this->సమితి_కిటికీ_Title(_this, కిటికీ);
    }

    ఒకవేళ (_this->సమితి_కిటికీ_Icon && కిటికీ->icon) {
        _this->సమితి_కిటికీ_Icon(_this, కిటికీ, కిటికీ->icon);
    }

    ఒకవేళ (_this->సమితి_కిటికీ_Minimum_కొలత && (కిటికీ->min_w || కిటికీ->min_h)) {
        _this->సమితి_కిటికీ_Minimum_కొలత(_this, కిటికీ);
    }

    ఒకవేళ (_this->సమితి_కిటికీ_గరిష్ఠ_కొలత && (కిటికీ->max_w || కిటికీ->max_h)) {
        _this->సమితి_కిటికీ_గరిష్ఠ_కొలత(_this, కిటికీ);
    }

    ఒకవేళ (_this->సమితి_కిటికీ_Aspect_నిష్పత్తి && (కిటికీ->min_aspect > 0.0f || కిటికీ->max_aspect > 0.0f)) {
        _this->సమితి_కిటికీ_Aspect_నిష్పత్తి(_this, కిటికీ);
    }

    ఒకవేళ (కిటికీ->తగిలింది_test) {
        _this->సమితి_కిటికీ_తగిలింది_Test(కిటికీ, true);
    }

    SDL_ముగింపు_కిటికీ_Creation(కిటికీ, flags);

    తిరిగి true;
}

bool SDL_Reconfigure_కిటికీ(SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ఒకవేళ (!SDL_Reconfigure_కిటికీ_అంతర్గత(కిటికీ, flags)) {
        తిరిగి SDL_Recreate_కిటికీ(కిటికీ, flags);
    }

    తిరిగి true;
}

bool SDL_HasWindows(శూన్య)
{
    తిరిగి _this && _this->windows;
}

SDL_కిటికీ_ID SDL_Get_కిటికీ_ID(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    తిరిగి కిటికీ->id;
}

SDL_కిటికీ *SDL_Get_కిటికీ_From_ID(SDL_కిటికీ_ID id)
{
    SDL_కిటికీ *కిటికీ;

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (id) {
        కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            ఒకవేళ (కిటికీ->id == id) {
                తిరిగి కిటికీ;
            }
        }
    }
    SDL_సమితి_Error("Invalid window ID");
    తిరిగి ఖాళీ;
}

SDL_కిటికీ *SDL_Get_కిటికీ_మాతృ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);

    తిరిగి కిటికీ->మాతృ;
}

SDL_PropertiesID SDL_Get_కిటికీ_Properties(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    ఒకవేళ (కిటికీ->props == 0) {
        కిటికీ->props = SDL_CreateProperties();
    }
    తిరిగి కిటికీ->props;
}

SDL_కిటికీ_Flags SDL_Get_కిటికీ_Flags(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, 0);

    తిరిగి కిటికీ->flags | కిటికీ->pending_flags;
}

bool SDL_సమితి_కిటికీ_Title(SDL_కిటికీ *కిటికీ, స్థిరరాశి అక్షరం *title)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (title == కిటికీ->title) {
        తిరిగి true;
    }
    ఒకవేళ (!title) {
        title = "";
    }
    ఒకవేళ (కిటికీ->title && SDL_strcmp(title, కిటికీ->title) == 0) {
        తిరిగి true;
    }

    SDL_free(కిటికీ->title);

    కిటికీ->title = SDL_strdup(title);

    ఒకవేళ (_this->సమితి_కిటికీ_Title) {
        _this->సమితి_కిటికీ_Title(_this, కిటికీ);
    }
    తిరిగి true;
}

స్థిరరాశి అక్షరం *SDL_Get_కిటికీ_Title(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, "");

    తిరిగి కిటికీ->title ? కిటికీ->title : "";
}

bool SDL_సమితి_కిటికీ_Icon(SDL_కిటికీ *కిటికీ, SDL_Surface *icon)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    CHECK_PARAM(!icon) {
        తిరిగి SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(కిటికీ->icon);

    // Convert the icon into ARGB8888
    కిటికీ->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ఒకవేళ (!కిటికీ->icon) {
        తిరిగి false;
    }

    ఒకవేళ (!_this->సమితి_కిటికీ_Icon) {
        తిరిగి SDL_Unsupported();
    }

    తిరిగి _this->సమితి_కిటికీ_Icon(_this, కిటికీ, కిటికీ->icon);
}

bool SDL_సమితి_కిటికీ_Position(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y)
{
    SDL_DisplayID original_displayID;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    స్థిరరాశి పూర్ణాంకం w = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : కిటికీ->windowed.w;
    స్థిరరాశి పూర్ణాంకం h = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : కిటికీ->windowed.h;

    original_displayID = Get_Display_For_కిటికీ(కిటికీ);
    కిటికీ->pending_displayID = 0;

    ఒకవేళ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = కిటికీ->windowed.x;
    }
    ఒకవేళ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = కిటికీ->windowed.y;
    }
    ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } లేకపోతే ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ఒకవేళ (displayID == 0 || SDL_Get_Display_సూచీ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        కిటికీ->pending_displayID = displayID;

        SDL_zero(bounds);
        ఒకవేళ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ఒకవేళ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                తిరిగి false;
            }
        }
        ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ఒకవేళ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } లేకపోతే {
        /* See if the requested window position matches the origin of any displays and set
         * the pending fullscreen display ID if it does. This needs to be set early in case
         * the window is prevented from moving to the exact origin due to struts.
         */
        కిటికీ->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    కిటికీ->pending.x = x;
    కిటికీ->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    ఒకవేళ (!_this->Sync_కిటికీ && (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        కిటికీ->floating.x = కిటికీ->windowed.x = x;
        కిటికీ->floating.y = కిటికీ->windowed.y = y;
    }
    కిటికీ->undefined_x = false;
    కిటికీ->undefined_y = false;
    కిటికీ->చివరి_position_pending = true;

    ఒకవేళ (_this->సమితి_కిటికీ_Position) {
        స్థిరరాశి bool ఫలితం = _this->సమితి_కిటికీ_Position(_this, కిటికీ);
        ఒకవేళ (ఫలితం) {
            SDL_SyncIfRequired(కిటికీ);
        }
        తిరిగి ఫలితం;
    }

    తిరిగి SDL_Unsupported();
}

bool SDL_Get_కిటికీ_Position(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *x, పూర్ణాంకం *y)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

#నిర్వచితమైతే SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#లేకపోతే
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) != 0);
#అయితే_ముగింపు
    ఒకవేళ (use_display_origin) {
        SDL_DisplayID displayID;

        ఒకవేళ (x) {
            *x = 0;
        }
        ఒకవేళ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = Get_Display_For_కిటికీ(కిటికీ);
        ఒకవేళ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ఒకవేళ (x) {
                *x = bounds.x;
            }
            ఒకవేళ (y) {
                *y = bounds.y;
            }
        }
    } లేకపోతే {
        స్థిరరాశి bool use_pending = (కిటికీ->flags & SDL_కిటికీ_HIDDEN) && కిటికీ->చివరి_position_pending;
        ఒకవేళ (x) {
            *x = use_pending ? కిటికీ->pending.x : కిటికీ->x;
        }
        ఒకవేళ (y) {
            *y = use_pending ? కిటికీ->pending.y : కిటికీ->y;
        }
    }
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Bordered(SDL_కిటికీ *కిటికీ, bool bordered)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Bordered) {
        తిరిగి SDL_Unsupported();
    }

    స్థిరరాశి bool want = bordered;
    స్థిరరాశి bool have = !(కిటికీ->flags & SDL_కిటికీ_BORDERLESS);
    ఒకవేళ (want != have) {
        ఒకవేళ (want) {
            కిటికీ->flags &= ~SDL_కిటికీ_BORDERLESS;
        } లేకపోతే {
            కిటికీ->flags |= SDL_కిటికీ_BORDERLESS;
        }
        _this->సమితి_కిటికీ_Bordered(_this, కిటికీ, want);
    }

    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Resizable(SDL_కిటికీ *కిటికీ, bool resizable)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Resizable) {
        తిరిగి SDL_Unsupported();
    }

    స్థిరరాశి bool want = resizable;
    స్థిరరాశి bool have = ((కిటికీ->flags & SDL_కిటికీ_RESIZABLE) != 0);
    ఒకవేళ (want != have) {
        ఒకవేళ (want) {
            కిటికీ->flags |= SDL_కిటికీ_RESIZABLE;
        } లేకపోతే {
            కిటికీ->flags &= ~SDL_కిటికీ_RESIZABLE;
            SDL_copyp(&కిటికీ->windowed, &కిటికీ->floating);
        }
        _this->సమితి_కిటికీ_Resizable(_this, కిటికీ, want);
    }

    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Always_On_శిఖరం(SDL_కిటికీ *కిటికీ, bool on_శిఖరం)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Always_On_శిఖరం) {
        తిరిగి SDL_Unsupported();
    }

    స్థిరరాశి bool want = on_శిఖరం;
    స్థిరరాశి bool have = ((కిటికీ->flags & SDL_కిటికీ_ALWAYS_ON_శిఖరం) != 0);
    ఒకవేళ (want != have) {
        ఒకవేళ (want) {
            కిటికీ->flags |= SDL_కిటికీ_ALWAYS_ON_శిఖరం;
        } లేకపోతే {
            కిటికీ->flags &= ~SDL_కిటికీ_ALWAYS_ON_శిఖరం;
        }
        _this->సమితి_కిటికీ_Always_On_శిఖరం(_this, కిటికీ, want);
    }

    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం w, పూర్ణాంకం h)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    CHECK_PARAM(w <= 0) {
        తిరిగి SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        తిరిగి SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    దశాంశం new_aspect = w / (దశాంశం)h;
    ఒకవేళ (కిటికీ->max_aspect > 0.0f && new_aspect > కిటికీ->max_aspect) {
        w = (పూర్ణాంకం)SDL_roundf(h * కిటికీ->max_aspect);
    } లేకపోతే ఒకవేళ (కిటికీ->min_aspect > 0.0f && new_aspect < కిటికీ->min_aspect) {
        h = (పూర్ణాంకం)SDL_roundf(w / కిటికీ->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ఒకవేళ (కిటికీ->min_w && w < కిటికీ->min_w) {
        w = కిటికీ->min_w;
    }
    ఒకవేళ (కిటికీ->max_w && w > కిటికీ->max_w) {
        w = కిటికీ->max_w;
    }
    ఒకవేళ (కిటికీ->min_h && h < కిటికీ->min_h) {
        h = కిటికీ->min_h;
    }
    ఒకవేళ (కిటికీ->max_h && h > కిటికీ->max_h) {
        h = కిటికీ->max_h;
    }

    కిటికీ->చివరి_కొలత_pending = true;
    కిటికీ->pending.w = w;
    కిటికీ->pending.h = h;

    ఒకవేళ (_this->సమితి_కిటికీ_కొలత) {
        _this->సమితి_కిటికీ_కొలత(_this, కిటికీ);
        SDL_SyncIfRequired(కిటికీ);
    } లేకపోతే {
        తిరిగి SDL_Unsupported();
    }
    తిరిగి true;
}

bool SDL_Get_కిటికీ_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    ఒకవేళ (w) {
        *w = కిటికీ->w;
    }
    ఒకవేళ (h) {
        *h = కిటికీ->h;
    }
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Aspect_నిష్పత్తి(SDL_కిటికీ *కిటికీ, దశాంశం min_aspect, దశాంశం max_aspect)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    కిటికీ->min_aspect = min_aspect;
    కిటికీ->max_aspect = max_aspect;

    ఒకవేళ (_this->సమితి_కిటికీ_Aspect_నిష్పత్తి) {
        _this->సమితి_కిటికీ_Aspect_నిష్పత్తి(_this, కిటికీ);
    }

    // Ensure that window has the correct aspect ratio
    పూర్ణాంకం w = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : కిటికీ->floating.w;
    పూర్ణాంకం h = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : కిటికీ->floating.h;
    తిరిగి SDL_సమితి_కిటికీ_కొలత(కిటికీ, w, h);
}

bool SDL_Get_కిటికీ_Aspect_నిష్పత్తి(SDL_కిటికీ *కిటికీ, దశాంశం *min_aspect, దశాంశం *max_aspect)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (min_aspect) {
        *min_aspect = కిటికీ->min_aspect;
    }
    ఒకవేళ (max_aspect) {
        *max_aspect = కిటికీ->max_aspect;
    }
    తిరిగి true;
}

bool SDL_Get_కిటికీ_Borders_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *శిఖరం, పూర్ణాంకం *ఎడమ, పూర్ణాంకం *bottom, పూర్ణాంకం *కుడి)
{
    పూర్ణాంకం dummy = 0;

    ఒకవేళ (!శిఖరం) {
        శిఖరం = &dummy;
    }
    ఒకవేళ (!ఎడమ) {
        ఎడమ = &dummy;
    }
    ఒకవేళ (!కుడి) {
        కుడి = &dummy;
    }
    ఒకవేళ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *శిఖరం = *ఎడమ = *bottom = *కుడి = 0;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->Get_కిటికీ_Borders_కొలత) {
        తిరిగి SDL_Unsupported();
    }

    తిరిగి _this->Get_కిటికీ_Borders_కొలత(_this, కిటికీ, శిఖరం, ఎడమ, bottom, కుడి);
}

bool SDL_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    పూర్ణాంకం filter;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!w) {
        w = &filter;
    }

    ఒకవేళ (!h) {
        h = &filter;
    }

    ఒకవేళ (_this->Get_కిటికీ_కొలత_లోపల_Pixels) {
        _this->Get_కిటికీ_కొలత_లోపల_Pixels(_this, కిటికీ, w, h);
    } లేకపోతే {
        SDL_DisplayID displayID = Get_Display_For_కిటికీ(కిటికీ);
        స్థిరరాశి SDL_Display_బహుళకం *బహుళకం;

        SDL_Get_కిటికీ_కొలత(కిటికీ, w, h);

        ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && SDL_Get_కిటికీ_Fullscreen_బహుళకం(కిటికీ)) {
            బహుళకం = SDL_Get_Current_Display_బహుళకం(displayID);
        } లేకపోతే {
            బహుళకం = SDL_Get_Desktop_Display_బహుళకం(displayID);
        }
        ఒకవేళ (బహుళకం) {
            *w = (పూర్ణాంకం)SDL_ceilf(*w * బహుళకం->pixel_density);
            *h = (పూర్ణాంకం)SDL_ceilf(*h * బహుళకం->pixel_density);
        }
    }
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Minimum_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం min_w, పూర్ణాంకం min_h)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_PARAM(min_w < 0) {
        తిరిగి SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        తిరిగి SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((కిటికీ->max_w && min_w > కిటికీ->max_w) || (కిటికీ->max_h && min_h > కిటికీ->max_h)) {
        తిరిగి SDL_సమితి_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    కిటికీ->min_w = min_w;
    కిటికీ->min_h = min_h;

    ఒకవేళ (_this->సమితి_కిటికీ_Minimum_కొలత) {
        _this->సమితి_కిటికీ_Minimum_కొలత(_this, కిటికీ);
    }

    // Ensure that window is not smaller than minimal size
    పూర్ణాంకం w = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : కిటికీ->floating.w;
    పూర్ణాంకం h = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : కిటికీ->floating.h;
    తిరిగి SDL_సమితి_కిటికీ_కొలత(కిటికీ, w, h);
}

bool SDL_Get_కిటికీ_Minimum_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *min_w, పూర్ణాంకం *min_h)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    ఒకవేళ (min_w) {
        *min_w = కిటికీ->min_w;
    }
    ఒకవేళ (min_h) {
        *min_h = కిటికీ->min_h;
    }
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_గరిష్ఠ_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం max_w, పూర్ణాంకం max_h)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_PARAM(max_w < 0) {
        తిరిగి SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        తిరిగి SDL_InvalidParamError("max_h");
    }

    ఒకవేళ ((max_w && max_w < కిటికీ->min_w) ||
        (max_h && max_h < కిటికీ->min_h)) {
        తిరిగి SDL_సమితి_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    కిటికీ->max_w = max_w;
    కిటికీ->max_h = max_h;

    ఒకవేళ (_this->సమితి_కిటికీ_గరిష్ఠ_కొలత) {
        _this->సమితి_కిటికీ_గరిష్ఠ_కొలత(_this, కిటికీ);
    }

    // Ensure that window is not larger than maximal size
    పూర్ణాంకం w = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.w : కిటికీ->floating.w;
    పూర్ణాంకం h = కిటికీ->చివరి_కొలత_pending ? కిటికీ->pending.h : కిటికీ->floating.h;
    తిరిగి SDL_సమితి_కిటికీ_కొలత(కిటికీ, w, h);
}

bool SDL_Get_కిటికీ_గరిష్ఠ_కొలత(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *max_w, పూర్ణాంకం *max_h)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    ఒకవేళ (max_w) {
        *max_w = కిటికీ->max_w;
    }
    ఒకవేళ (max_h) {
        *max_h = కిటికీ->max_h;
    }
    తిరిగి true;
}

bool SDL_Show_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ *బిడ్డ;
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
        తిరిగి true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ఒకవేళ (కిటికీ->మాతృ && (కిటికీ->మాతృ->flags & SDL_కిటికీ_HIDDEN)) {
        కిటికీ->restore_on_show = true;
        తిరిగి true;
    }

    ఒకవేళ (_this->Show_కిటికీ) {
        _this->Show_కిటికీ(_this, కిటికీ);
    } లేకపోతే {
        SDL_సమితి_Mouse_Focus(కిటికీ);
        SDL_సమితి_Keyboard_Focus(కిటికీ);
    }
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);

    // Restore child windows
    కొరకు (బిడ్డ = కిటికీ->మొదటి_బిడ్డ; బిడ్డ; బిడ్డ = బిడ్డ->తదుపరి_sibling) {
        ఒకవేళ (!బిడ్డ->restore_on_show && (బిడ్డ->flags & SDL_కిటికీ_HIDDEN)) {
            ఆపు;
        }
        SDL_Show_కిటికీ(బిడ్డ);
        బిడ్డ->restore_on_show = false;
    }
    తిరిగి true;
}

bool SDL_Hide_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ *బిడ్డ;
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        కిటికీ->restore_on_show = false;
        తిరిగి true;
    }

    // Hide all child windows
    కొరకు (బిడ్డ = కిటికీ->మొదటి_బిడ్డ; బిడ్డ; బిడ్డ = బిడ్డ->తదుపరి_sibling) {
        ఒకవేళ (బిడ్డ->flags & SDL_కిటికీ_HIDDEN) {
            ఆపు;
        }
        SDL_Hide_కిటికీ(బిడ్డ);
        బిడ్డ->restore_on_show = true;
    }

    // Store the flags for restoration later.
    స్థిరరాశి SDL_కిటికీ_Flags pending_ముసుగు = (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_MINIMIZED | SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_KEYBOARD_GRABBED | SDL_కిటికీ_MOUSE_GRABBED);
    కిటికీ->pending_flags = (కిటికీ->flags & pending_ముసుగు);

    కిటికీ->is_hiding = true;
    ఒకవేళ (_this->Hide_కిటికీ) {
        _this->Hide_కిటికీ(_this, కిటికీ);
    } లేకపోతే {
        SDL_సమితి_Mouse_Focus(ఖాళీ);
        SDL_సమితి_Keyboard_Focus(ఖాళీ);
    }
    కిటికీ->is_hiding = false;
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_HIDDEN, 0, 0);
    తిరిగి true;
}

bool SDL_Raise_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        తిరిగి true;
    }
    ఒకవేళ (_this->Raise_కిటికీ) {
        _this->Raise_కిటికీ(_this, కిటికీ);
    }
    తిరిగి true;
}

bool SDL_Maximize_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->Maximize_కిటికీ) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
        తిరిగి SDL_సమితి_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        కిటికీ->pending_flags |= SDL_కిటికీ_MAXIMIZED;
        తిరిగి true;
    }

    _this->Maximize_కిటికీ(_this, కిటికీ);
    SDL_SyncIfRequired(కిటికీ);
    తిరిగి true;
}

bool SDL_Minimize_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->Minimize_కిటికీ) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        కిటికీ->pending_flags |= SDL_కిటికీ_MINIMIZED;
        తిరిగి true;
    }

    _this->Minimize_కిటికీ(_this, కిటికీ);
    SDL_SyncIfRequired(కిటికీ);
    తిరిగి true;
}

bool SDL_Restore_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->Restore_కిటికీ) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        కిటికీ->pending_flags &= ~(SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_MINIMIZED);
        తిరిగి true;
    }

    _this->Restore_కిటికీ(_this, కిటికీ);
    SDL_SyncIfRequired(కిటికీ);
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Fullscreen(SDL_కిటికీ *కిటికీ, bool fullscreen)
{
    bool ఫలితం;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        ఒకవేళ (fullscreen) {
            కిటికీ->pending_flags |= SDL_కిటికీ_FULLSCREEN;
        } లేకపోతే {
            కిటికీ->pending_flags &= ~SDL_కిటికీ_FULLSCREEN;
        }
        తిరిగి true;
    }

    ఒకవేళ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&కిటికీ->current_fullscreen_బహుళకం, &కిటికీ->requested_fullscreen_బహుళకం);
    }

    ఫలితం = SDL_Update_Fullscreen_బహుళకం(కిటికీ, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ఒకవేళ (!fullscreen || !ఫలితం) {
        // Clear the current fullscreen mode.
        SDL_zero(కిటికీ->current_fullscreen_బహుళకం);
    }

    ఒకవేళ (ఫలితం) {
        SDL_SyncIfRequired(కిటికీ);
    }

    తిరిగి ఫలితం;
}

bool SDL_Sync_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (_this->Sync_కిటికీ) {
        తిరిగి _this->Sync_కిటికీ(_this, కిటికీ);
    } లేకపోతే {
        తిరిగి true;
    }
}

స్థిర bool ShouldAttemptTextureFramebuffer(శూన్య)
{
    స్థిరరాశి అక్షరం *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ఒకవేళ (!_this->Create_కిటికీ_Framebuffer) {
        తిరిగి true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ఒకవేళ (hint && *hint) {
        ఒకవేళ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } లేకపోతే {
            attempt_texture_framebuffer = true;
        }
    } లేకపోతే {
        ఒకవేళ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } లేకపోతే {
            attempt_texture_framebuffer = false;
        }
    }
    తిరిగి attempt_texture_framebuffer;
}

స్థిర SDL_Surface *SDL_Create_కిటికీ_Framebuffer(SDL_కిటికీ *కిటికీ)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    శూన్య *pixels = ఖాళీ;
    పూర్ణాంకం pitch = 0;
    bool created_framebuffer = false;
    పూర్ణాంకం w, h;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ఒకవేళ (!_this->checked_texture_framebuffer) {
        ఒకవేళ (ShouldAttemptTextureFramebuffer()) {
            ఒకవేళ (!SDL_Create_కిటికీ_Texture(_this, కిటికీ, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } లేకపోతే {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_కిటికీ_Framebuffer = SDL_Create_కిటికీ_Texture;
                _this->సమితి_కిటికీ_Framebuffer_VSync = SDL_సమితి_కిటికీ_Texture_VSync;
                _this->Get_కిటికీ_Framebuffer_VSync = SDL_Get_కిటికీ_Texture_VSync;
                _this->Update_కిటికీ_Framebuffer = SDL_Update_కిటికీ_Texture;
                _this->Destroy_కిటికీ_Framebuffer = SDL_Destroy_కిటికీ_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    ఒకవేళ (!created_framebuffer) {
        ఒకవేళ (!_this->Create_కిటికీ_Framebuffer || !_this->Update_కిటికీ_Framebuffer) {
            SDL_సమితి_Error("Window framebuffer support not available");
            తిరిగి ఖాళీ;
        }

        ఒకవేళ (!_this->Create_కిటికీ_Framebuffer(_this, కిటికీ, &format, &pixels, &pitch)) {
            తిరిగి ఖాళీ;
        }
    }

    ఒకవేళ (కిటికీ->surface) {
        // We may have gone recursive and already created the surface
        తిరిగి కిటికీ->surface;
    }

    తిరిగి SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_కిటికీ_Has_Surface(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    తిరిగి కిటికీ->surface ? true : false;
}

SDL_Surface *SDL_Get_కిటికీ_Surface(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);

    ఒకవేళ (!కిటికీ->surface_valid) {
        ఒకవేళ (కిటికీ->surface) {
            కిటికీ->surface->అంతర్గత_flags &= ~SDL_అంతర్గత_SURFACE_DONTFREE;
            SDL_DestroySurface(కిటికీ->surface);
            కిటికీ->surface = ఖాళీ;
        }

        కిటికీ->surface = SDL_Create_కిటికీ_Framebuffer(కిటికీ);
        ఒకవేళ (కిటికీ->surface) {
            కిటికీ->surface_valid = true;
            కిటికీ->surface->అంతర్గత_flags |= SDL_అంతర్గత_SURFACE_DONTFREE;
        }
    }
    తిరిగి కిటికీ->surface;
}

bool SDL_సమితి_కిటికీ_Surface_VSync(SDL_కిటికీ *కిటికీ, పూర్ణాంకం vsync)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Framebuffer_VSync) {
        తిరిగి SDL_Unsupported();
    }
    తిరిగి _this->సమితి_కిటికీ_Framebuffer_VSync(_this, కిటికీ, vsync);
}

bool SDL_Get_కిటికీ_Surface_VSync(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *vsync)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->Get_కిటికీ_Framebuffer_VSync) {
        తిరిగి SDL_Unsupported();
    }
    తిరిగి _this->Get_కిటికీ_Framebuffer_VSync(_this, కిటికీ, vsync);
}

bool SDL_Update_కిటికీ_Surface(SDL_కిటికీ *కిటికీ)
{
    SDL_Rect నిండిన_rect;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    నిండిన_rect.x = 0;
    నిండిన_rect.y = 0;
    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &నిండిన_rect.w, &నిండిన_rect.h);

    తిరిగి SDL_Update_కిటికీ_Surface_Rects(కిటికీ, &నిండిన_rect, 1);
}

bool SDL_Update_కిటికీ_Surface_Rects(SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects,
                                 పూర్ణాంకం numrects)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!కిటికీ->surface_valid) {
        తిరిగి SDL_సమితి_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    తిరిగి _this->Update_కిటికీ_Framebuffer(_this, కిటికీ, rects, numrects);
}

bool SDL_Destroy_కిటికీ_Surface(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (కిటికీ->surface) {
        కిటికీ->surface->అంతర్గత_flags &= ~SDL_అంతర్గత_SURFACE_DONTFREE;
        SDL_DestroySurface(కిటికీ->surface);
        కిటికీ->surface = ఖాళీ;
        కిటికీ->surface_valid = false;
    }

    ఒకవేళ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ఒకవేళ (_this->Destroy_కిటికీ_Framebuffer) {
            _this->Destroy_కిటికీ_Framebuffer(_this, కిటికీ);
        }
    }
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Opacity(SDL_కిటికీ *కిటికీ, దశాంశం opacity)
{
    bool ఫలితం;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Opacity) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (opacity < 0.0f) {
        opacity = 0.0f;
    } లేకపోతే ఒకవేళ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    ఫలితం = _this->సమితి_కిటికీ_Opacity(_this, కిటికీ, opacity);
    ఒకవేళ (ఫలితం) {
        కిటికీ->opacity = opacity;
    }

    తిరిగి ఫలితం;
}

దశాంశం SDL_Get_కిటికీ_Opacity(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, -1.0f);

    తిరిగి కిటికీ->opacity;
}

bool SDL_సమితి_కిటికీ_మాతృ(SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (మాతృ) {
        CHECK_కిటికీ_MAGIC(మాతృ, false);
        CHECK_కిటికీ_NOT_POPUP(మాతృ, false);
    }

    ఒకవేళ (కిటికీ == మాతృ) {
        తిరిగి SDL_సమితి_Error("Cannot set the parent of a window to itself.");
    }

    ఒకవేళ (!_this->సమితి_కిటికీ_మాతృ) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MODAL) {
        తిరిగి SDL_సమితి_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ఒకవేళ (కిటికీ->మాతృ == మాతృ) {
        తిరిగి true;
    }

    స్థిరరాశి bool ret = _this->సమితి_కిటికీ_మాతృ(_this, కిటికీ, మాతృ);
    SDL_Update_కిటికీ_Hierarchy(కిటికీ, ret ? మాతృ : ఖాళీ);

    తిరిగి ret;
}

bool SDL_సమితి_కిటికీ_Modal(SDL_కిటికీ *కిటికీ, bool modal)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Modal) {
        తిరిగి SDL_Unsupported();
    }

    ఒకవేళ (modal) {
        ఒకవేళ (!కిటికీ->మాతృ) {
            తిరిగి SDL_సమితి_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        కిటికీ->flags |= SDL_కిటికీ_MODAL;
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MODAL) {
        కిటికీ->flags &= ~SDL_కిటికీ_MODAL;
    } లేకపోతే {
        తిరిగి true; // Already not modal, so nothing to do.
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        తిరిగి true;
    }

    తిరిగి _this->సమితి_కిటికీ_Modal(_this, కిటికీ, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_కిటికీ *కిటికీ, SDL_కిటికీ **new_focus)
{
    SDL_కిటికీ *focus = కిటికీ->మాతృ;
    bool సమితి_focus = !!(కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    అయితే (SDL_కిటికీ_IS_POPUP(focus) && ((focus->flags & SDL_కిటికీ_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->మాతృ;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ఒకవేళ (!సమితి_focus) {
            సమితి_focus = !!(focus->flags & SDL_కిటికీ_ఆదానం_FOCUS);
        }
    }

    *new_focus = focus;
    తిరిగి సమితి_focus;
}

bool SDL_ShouldFocusPopup(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ *toplevel_మాతృ;
    కొరకు (toplevel_మాతృ = కిటికీ->మాతృ; SDL_కిటికీ_IS_POPUP(toplevel_మాతృ); toplevel_మాతృ = toplevel_మాతృ->మాతృ) {
    }

    SDL_కిటికీ *current_focus = toplevel_మాతృ->keyboard_focus;
    bool దొరికింది_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_కిటికీ *w;
    కొరకు (w = current_focus; w != toplevel_మాతృ; w = w->మాతృ) {
        ఒకవేళ (w == కిటికీ) {
            దొరికింది_higher_focus = true;
            ఆపు;
        }
    }

    తిరిగి !దొరికింది_higher_focus || w == toplevel_మాతృ;
}

bool SDL_సమితి_కిటికీ_Focusable(SDL_కిటికీ *కిటికీ, bool focusable)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    స్థిరరాశి bool want = (focusable != false); // normalize the flag.
    స్థిరరాశి bool have = !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE);
    ఒకవేళ ((want != have) && (_this->సమితి_కిటికీ_Focusable)) {
        ఒకవేళ (want) {
            కిటికీ->flags &= ~SDL_కిటికీ_NOT_FOCUSABLE;
        } లేకపోతే {
            కిటికీ->flags |= SDL_కిటికీ_NOT_FOCUSABLE;
        }
        ఒకవేళ (!_this->సమితి_కిటికీ_Focusable(_this, కిటికీ, want)) {
            తిరిగి false;
        }
    }

    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Fill_Document(SDL_కిటికీ *కిటికీ, bool fill)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    స్థిరరాశి bool want = (fill != false); // normalize the flag.
    స్థిరరాశి bool have = ((కిటికీ->flags & SDL_కిటికీ_FILL_DOCUMENT) != 0);
    ఒకవేళ ((want != have) && (_this->సమితి_కిటికీ_Fill_Document)) {
        ఒకవేళ (!_this->సమితి_కిటికీ_Fill_Document(_this, కిటికీ, want)) {
            తిరిగి false;
        } లేకపోతే ఒకవేళ (want) {
            కిటికీ->flags |= SDL_కిటికీ_FILL_DOCUMENT;
        } లేకపోతే {
            కిటికీ->flags &= ~SDL_కిటికీ_FILL_DOCUMENT;
        }
    }

    తిరిగి true;
}

శూన్య SDL_Update_కిటికీ_Grab(SDL_కిటికీ *కిటికీ)
{
    bool keyboard_grabbed, mouse_grabbed;

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS) {
        ఒకవేళ (SDL_GetMouse()->relative_బహుళకం || (కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } లేకపోతే {
            mouse_grabbed = false;
        }

        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } లేకపోతే {
            keyboard_grabbed = false;
        }
    } లేకపోతే {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ఒకవేళ (mouse_grabbed || keyboard_grabbed) {
        ఒకవేళ (_this->grabbed_కిటికీ && (_this->grabbed_కిటికీ != కిటికీ)) {
            // stealing a grab from another window!
            _this->grabbed_కిటికీ->flags &= ~(SDL_కిటికీ_MOUSE_GRABBED | SDL_కిటికీ_KEYBOARD_GRABBED);
            ఒకవేళ (_this->సమితి_కిటికీ_Mouse_Grab) {
                _this->సమితి_కిటికీ_Mouse_Grab(_this, _this->grabbed_కిటికీ, false);
            }
            ఒకవేళ (_this->సమితి_కిటికీ_Keyboard_Grab) {
                _this->సమితి_కిటికీ_Keyboard_Grab(_this, _this->grabbed_కిటికీ, false);
            }
        }
        _this->grabbed_కిటికీ = కిటికీ;
    } లేకపోతే ఒకవేళ (_this->grabbed_కిటికీ == కిటికీ) {
        _this->grabbed_కిటికీ = ఖాళీ; // ungrabbing input.
    }

    ఒకవేళ (_this->సమితి_కిటికీ_Mouse_Grab) {
        ఒకవేళ (!_this->సమితి_కిటికీ_Mouse_Grab(_this, కిటికీ, mouse_grabbed)) {
            కిటికీ->flags &= ~SDL_కిటికీ_MOUSE_GRABBED;
        }
    }
    ఒకవేళ (_this->సమితి_కిటికీ_Keyboard_Grab) {
        ఒకవేళ (!_this->సమితి_కిటికీ_Keyboard_Grab(_this, కిటికీ, keyboard_grabbed)) {
            కిటికీ->flags &= ~SDL_కిటికీ_KEYBOARD_GRABBED;
        }
    }

    ఒకవేళ (_this->grabbed_కిటికీ && !(_this->grabbed_కిటికీ->flags & (SDL_కిటికీ_MOUSE_GRABBED | SDL_కిటికీ_KEYBOARD_GRABBED))) {
        _this->grabbed_కిటికీ = ఖాళీ;
    }
}

bool SDL_సమితి_కిటికీ_Keyboard_Grab(SDL_కిటికీ *కిటికీ, bool grabbed)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        ఒకవేళ (grabbed) {
            కిటికీ->pending_flags |= SDL_కిటికీ_KEYBOARD_GRABBED;
        } లేకపోతే {
            కిటికీ->pending_flags &= ~SDL_కిటికీ_KEYBOARD_GRABBED;
        }
        తిరిగి true;
    }

    ఒకవేళ (!!grabbed == !!(కిటికీ->flags & SDL_కిటికీ_KEYBOARD_GRABBED)) {
        తిరిగి true;
    }
    ఒకవేళ (grabbed) {
        కిటికీ->flags |= SDL_కిటికీ_KEYBOARD_GRABBED;
    } లేకపోతే {
        కిటికీ->flags &= ~SDL_కిటికీ_KEYBOARD_GRABBED;
    }
    SDL_Update_కిటికీ_Grab(కిటికీ);

    ఒకవేళ (grabbed && !(కిటికీ->flags & SDL_కిటికీ_KEYBOARD_GRABBED)) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool SDL_సమితి_కిటికీ_Mouse_Grab(SDL_కిటికీ *కిటికీ, bool grabbed)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        ఒకవేళ (grabbed) {
            కిటికీ->pending_flags |= SDL_కిటికీ_MOUSE_GRABBED;
        } లేకపోతే {
            కిటికీ->pending_flags &= ~SDL_కిటికీ_MOUSE_GRABBED;
        }
        తిరిగి true;
    }

    ఒకవేళ (!!grabbed == !!(కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED)) {
        తిరిగి true;
    }
    ఒకవేళ (grabbed) {
        కిటికీ->flags |= SDL_కిటికీ_MOUSE_GRABBED;
    } లేకపోతే {
        కిటికీ->flags &= ~SDL_కిటికీ_MOUSE_GRABBED;
    }
    SDL_Update_కిటికీ_Grab(కిటికీ);

    ఒకవేళ (grabbed && !(కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED)) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool SDL_Get_కిటికీ_Keyboard_Grab(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    తిరిగి కిటికీ == _this->grabbed_కిటికీ && (_this->grabbed_కిటికీ->flags & SDL_కిటికీ_KEYBOARD_GRABBED);
}

bool SDL_Get_కిటికీ_Mouse_Grab(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    తిరిగి కిటికీ == _this->grabbed_కిటికీ && (_this->grabbed_కిటికీ->flags & SDL_కిటికీ_MOUSE_GRABBED);
}

SDL_కిటికీ *SDL_Get_Grabbed_కిటికీ(శూన్య)
{
    ఒకవేళ (_this && _this->grabbed_కిటికీ &&
        (_this->grabbed_కిటికీ->flags & (SDL_కిటికీ_MOUSE_GRABBED | SDL_కిటికీ_KEYBOARD_GRABBED)) != 0) {
        తిరిగి _this->grabbed_కిటికీ;
    } లేకపోతే {
        తిరిగి ఖాళీ;
    }
}

bool SDL_సమితి_కిటికీ_Mouse_Rect(SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rect)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_Mouse_Rect) {
        తిరిగి SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ఒకవేళ (!rect) {
        rect = &zero;
    }

    ఒకవేళ (SDL_memcmp(&కిటికీ->mouse_rect, rect, పరిమాణం(*rect)) == 0) {
        తిరిగి true;
    }
    SDL_memcpy(&కిటికీ->mouse_rect, rect, పరిమాణం(*rect));

    తిరిగి _this->సమితి_కిటికీ_Mouse_Rect(_this, కిటికీ);
}

స్థిరరాశి SDL_Rect *SDL_Get_కిటికీ_Mouse_Rect(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);

    ఒకవేళ (SDL_Rect_ఖాళీలు(&కిటికీ->mouse_rect)) {
        తిరిగి ఖాళీ;
    } లేకపోతే {
        తిరిగి &కిటికీ->mouse_rect;
    }
}

bool SDL_సమితి_కిటికీ_Relative_Mouse_బహుళకం(SDL_కిటికీ *కిటికీ, bool enabled)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    ఒకవేళ (enabled == SDL_Get_కిటికీ_Relative_Mouse_బహుళకం(కిటికీ)) {
        తిరిగి true;
    }

    ఒకవేళ (enabled) {
        కిటికీ->flags |= SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం;
    } లేకపోతే {
        కిటికీ->flags &= ~SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం;
    }

    ఒకవేళ (!SDL_Update_Relative_Mouse_బహుళకం()) {
        ఒకవేళ (enabled) {
            కిటికీ->flags &= ~SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం;
        } లేకపోతే {
            కిటికీ->flags |= SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం;
        }
        తిరిగి false;
    }
    తిరిగి true;
}

bool SDL_Get_కిటికీ_Relative_Mouse_బహుళకం(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం) {
        తిరిగి true;
    } లేకపోతే {
        తిరిగి false;
    }
}

bool SDL_Flash_కిటికీ(SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (_this->Flash_కిటికీ) {
        తిరిగి _this->Flash_కిటికీ(_this, కిటికీ, operation);
    }

    తిరిగి SDL_Unsupported();
}

bool SDL_సమితి_కిటికీ_పురోగతి_State(SDL_కిటికీ *కిటికీ, SDL_పురోగతి_State state)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    CHECK_PARAM(state < SDL_పురోగతి_STATE_NONE || state > SDL_పురోగతి_STATE_ERROR) {
        తిరిగి SDL_InvalidParamError("state");
    }

    కిటికీ->పురోగతి_state = state;

    ఒకవేళ (_this->Apply_కిటికీ_పురోగతి) {
        ఒకవేళ (!_this->Apply_కిటికీ_పురోగతి(_this, కిటికీ)) {
            తిరిగి false;
        }
    }

    తిరిగి true;
}

SDL_పురోగతి_State SDL_Get_కిటికీ_పురోగతి_State(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, SDL_పురోగతి_STATE_INVALID);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, SDL_పురోగతి_STATE_INVALID);

    తిరిగి కిటికీ->పురోగతి_state;
}

bool SDL_సమితి_కిటికీ_పురోగతి_విలువ(SDL_కిటికీ *కిటికీ, దశాంశం విలువ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    విలువ = SDL_clamp(విలువ, 0.0f, 1.f);

    కిటికీ->పురోగతి_విలువ = విలువ;

    ఒకవేళ (_this->Apply_కిటికీ_పురోగతి) {
        ఒకవేళ (!_this->Apply_కిటికీ_పురోగతి(_this, కిటికీ)) {
            తిరిగి false;
        }
    }

    తిరిగి true;
}

దశాంశం SDL_Get_కిటికీ_పురోగతి_విలువ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, -1.0f);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, -1.0f);

    తిరిగి కిటికీ->పురోగతి_విలువ;
}

శూన్య SDL_On_కిటికీ_Shown(SDL_కిటికీ *కిటికీ)
{
    // Set window state if we have pending window flags cached
    Apply_కిటికీ_Flags(కిటికీ, కిటికీ->pending_flags);
    కిటికీ->pending_flags = 0;
}

శూన్య SDL_On_కిటికీ_Hidden(SDL_కిటికీ *కిటికీ)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    కిటికీ->pending_flags |= (కిటికీ->flags & (SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_LEAVE, false);
}

శూన్య SDL_On_కిటికీ_Display_మారింది(SDL_కిటికీ *కిటికీ)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    ఒకవేళ (కిటికీ->update_fullscreen_on_display_మారింది && (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
        స్థిరరాశి bool auto_బహుళకం_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_సరిపోలిక_EXCLUSIVE_బహుళకం_ON_MOVE, true);

        ఒకవేళ (auto_బహుళకం_switch && (కిటికీ->requested_fullscreen_బహుళకం.w != 0 || కిటికీ->requested_fullscreen_బహుళకం.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_కిటికీ_Position(కిటికీ);
            bool include_ఎగువ_density_modes = false;

            ఒకవేళ (కిటికీ->requested_fullscreen_బహుళకం.pixel_density > 1.0f) {
                include_ఎగువ_density_modes = true;
            }
            స్థిరరాశి bool దొరికింది_సరిపోలిక = SDL_Get_Closest_Fullscreen_Display_బహుళకం(displayID, కిటికీ->requested_fullscreen_బహుళకం.w, కిటికీ->requested_fullscreen_బహుళకం.h,
                                                                         కిటికీ->requested_fullscreen_బహుళకం.refresh_రేటు, include_ఎగువ_density_modes, &కిటికీ->current_fullscreen_బహుళకం);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ఒకవేళ (!దొరికింది_సరిపోలిక ||
                కిటికీ->requested_fullscreen_బహుళకం.w != కిటికీ->current_fullscreen_బహుళకం.w ||
                కిటికీ->requested_fullscreen_బహుళకం.h != కిటికీ->current_fullscreen_బహుళకం.h) {
                SDL_zero(కిటికీ->current_fullscreen_బహుళకం);
            }
        } లేకపోతే {
            SDL_zero(కిటికీ->current_fullscreen_బహుళకం);
        }

        ఒకవేళ (SDL_కిటికీ_FULLSCREEN_VISIBLE(కిటికీ)) {
            SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_కిటికీ_Pixel_కొలత_మారింది(కిటికీ);
}

శూన్య SDL_On_కిటికీ_Moved(SDL_కిటికీ *కిటికీ)
{
    SDL_Check_కిటికీ_Display_మారింది(కిటికీ);
}

శూన్య SDL_On_కిటికీ_Resized(SDL_కిటికీ *కిటికీ)
{
    SDL_Check_కిటికీ_Display_మారింది(కిటికీ);
    SDL_Check_కిటికీ_Pixel_కొలత_మారింది(కిటికీ);
    SDL_Check_కిటికీ_సురక్షిత_Area_మారింది(కిటికీ);

    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) && _this->Update_కిటికీ_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_సూచిక_Property(కిటికీ->props, SDL_PROP_కిటికీ_SHAPE_సూచిక, ఖాళీ);
        ఒకవేళ (surface) {
            _this->Update_కిటికీ_Shape(_this, కిటికీ, surface);
        }
    }
}

శూన్య SDL_Check_కిటికీ_Pixel_కొలత_మారింది(SDL_కిటికీ *కిటికీ)
{
    పూర్ణాంకం pixel_w = 0, pixel_h = 0;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &pixel_w, &pixel_h);
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_PIXEL_కొలత_మారింది, pixel_w, pixel_h);

    SDL_Check_కిటికీ_Display_Scale_మారింది(కిటికీ);
}

శూన్య SDL_On_కిటికీ_Pixel_కొలత_మారింది(SDL_కిటికీ *కిటికీ)
{
    కిటికీ->surface_valid = false;
}

శూన్య SDL_On_కిటికీ_సజీవ_Resize_Update(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } లేకపోతే {
        // Send an expose event so the application can redraw
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

స్థిర శూన్య SDL_Check_కిటికీ_సురక్షిత_Area_మారింది(SDL_కిటికీ *కిటికీ)
{
    SDL_Rect rect;

    rect.x = కిటికీ->సురక్షిత_inset_ఎడమ;
    rect.y = కిటికీ->సురక్షిత_inset_శిఖరం;
    rect.w = కిటికీ->w - (కిటికీ->సురక్షిత_inset_కుడి + కిటికీ->సురక్షిత_inset_ఎడమ);
    rect.h = కిటికీ->h - (కిటికీ->సురక్షిత_inset_శిఖరం + కిటికీ->సురక్షిత_inset_bottom);
    ఒకవేళ (SDL_memcmp(&rect, &కిటికీ->సురక్షిత_rect, పరిమాణం(rect)) != 0) {
        SDL_copyp(&కిటికీ->సురక్షిత_rect, &rect);
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_సురక్షిత_AREA_మారింది, 0, 0);
    }
}

శూన్య SDL_సమితి_కిటికీ_సురక్షిత_Area_Insets(SDL_కిటికీ *కిటికీ, పూర్ణాంకం ఎడమ, పూర్ణాంకం కుడి, పూర్ణాంకం శిఖరం, పూర్ణాంకం bottom)
{
    కిటికీ->సురక్షిత_inset_ఎడమ = ఎడమ;
    కిటికీ->సురక్షిత_inset_కుడి = కుడి;
    కిటికీ->సురక్షిత_inset_శిఖరం = శిఖరం;
    కిటికీ->సురక్షిత_inset_bottom = bottom;
    SDL_Check_కిటికీ_సురక్షిత_Area_మారింది(కిటికీ);
}

bool SDL_Get_కిటికీ_సురక్షిత_Area(SDL_కిటికీ *కిటికీ, SDL_Rect *rect)
{
    ఒకవేళ (rect) {
        SDL_zerop(rect);
    }

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (rect) {
        ఒకవేళ (SDL_Rect_ఖాళీలు(&కిటికీ->సురక్షిత_rect)) {
            rect->w = కిటికీ->w;
            rect->h = కిటికీ->h;
        } లేకపోతే {
            SDL_copyp(rect, &కిటికీ->సురక్షిత_rect);
        }
    }
    తిరిగి true;
}

శూన్య SDL_On_కిటికీ_Minimized(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

శూన్య SDL_On_కిటికీ_Maximized(SDL_కిటికీ *కిటికీ)
{
}

శూన్య SDL_On_కిటికీ_Restored(SDL_కిటికీ *కిటికీ)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

శూన్య SDL_On_కిటికీ_Enter(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (_this->On_కిటికీ_Enter) {
        _this->On_కిటికీ_Enter(_this, కిటికీ);
    }
    SDL_Update_Relative_Mouse_బహుళకం();
}

శూన్య SDL_On_కిటికీ_Leave(SDL_కిటికీ *కిటికీ)
{
    SDL_Update_Relative_Mouse_బహుళకం();
}

శూన్య SDL_On_కిటికీ_Focus_Gained(SDL_కిటికీ *కిటికీ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ఒకవేళ (mouse && mouse->relative_బహుళకం) {
        SDL_సమితి_Mouse_Focus(కిటికీ);
    }

    SDL_Update_కిటికీ_Grab(కిటికీ);
}

స్థిర bool SDL_ShouldMinimizeOnFocusLoss(SDL_కిటికీ *కిటికీ)
{
    స్థిరరాశి అక్షరం *hint;

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) || కిటికీ->is_destroying) {
        తిరిగి false;
    }

#ఒకవేళ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ఒకవేళ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ఒకవేళ (Cocoa_IsShowingModalDialog(కిటికీ)) {
            తిరిగి false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } లేకపోతే ఒకవేళ (Cocoa_Is_కిటికీ_లోపల_Fullscreen_Space(కిటికీ)) {
            తిరిగి false;
        }
    }
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_PLATFORM_ANDROID
    {
        బాహ్య bool Android_JNI_ShouldMinimizeOnFocusLoss(శూన్య);
        ఒకవేళ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            తిరిగి false;
        }
    }
#అయితే_ముగింపు

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ఒకవేళ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ఒకవేళ (కిటికీ->fullscreen_exclusive && !SDL_బహుళకం_Switching_Emulated(_this)) {
            తిరిగి true;
        } లేకపోతే {
            తిరిగి false;
        }
    }
    తిరిగి SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

శూన్య SDL_On_కిటికీ_Focus_కోల్పోయిన(SDL_కిటికీ *కిటికీ)
{
    SDL_Update_కిటికీ_Grab(కిటికీ);

    ఒకవేళ (SDL_ShouldMinimizeOnFocusLoss(కిటికీ)) {
        SDL_Minimize_కిటికీ(కిటికీ);
    }
}

SDL_కిటికీ *SDL_GetToplevelForKeyboardFocus(శూన్య)
{
    SDL_కిటికీ *focus = SDL_GetKeyboardFocus();

    ఒకవేళ (focus) {
        // Get the toplevel parent window.
        అయితే (focus->మాతృ) {
            focus = focus->మాతృ;
        }
    }

    తిరిగి focus;
}

bool SDL_కూడు_కిటికీ_Renderer(SDL_కిటికీ *కిటికీ, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(కిటికీ->renderers, (కిటికీ->అంకె_renderers + 1) * పరిమాణం(*renderers));
    ఒకవేళ (!renderers) {
        తిరిగి false;
    }

    కిటికీ->renderers = renderers;
    కిటికీ->renderers[కిటికీ->అంకె_renderers++] = renderer;

    SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_RENDERER_సూచిక, renderer);
    తిరిగి true;
}

శూన్య SDL_Remove_కిటికీ_Renderer(SDL_కిటికీ *కిటికీ, SDL_Renderer *renderer)
{
    కొరకు (పూర్ణాంకం i = 0; i < కిటికీ->అంకె_renderers; ++i) {
        ఒకవేళ (కిటికీ->renderers[i] == renderer) {
            ఒకవేళ (i < (కిటికీ->అంకె_renderers - 1)) {
                SDL_memmove(&కిటికీ->renderers[i], &కిటికీ->renderers[i + 1], (కిటికీ->అంకె_renderers - i - 1) * పరిమాణం(కిటికీ->renderers[i]));
            }
            --కిటికీ->అంకె_renderers;
            ఆపు;
        }
    }

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    ఒకవేళ (SDL_Get_సూచిక_Property(props, SDL_PROP_కిటికీ_RENDERER_సూచిక, ఖాళీ) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_కిటికీ_RENDERER_సూచిక);
    }
}

శూన్య SDL_Destroy_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ,);

    కిటికీ->is_destroying = true;

    // Destroy any child windows of this window
    అయితే (కిటికీ->మొదటి_బిడ్డ) {
        SDL_Destroy_కిటికీ(కిటికీ->మొదటి_బిడ్డ);
    }

    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_DESTROYED, 0, 0);

    SDL_Destroy_కిటికీ_Surface(కిటికీ);

    SDL_Renderer *renderer = SDL_GetRenderer(కిటికీ);
    ఒకవేళ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_LEAVE, true);
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
        SDL_Hide_కిటికీ(కిటికీ);
    }

    SDL_DestroyProperties(కిటికీ->పాఠ్యం_ఆదానం_props);

    SDL_Destroy_కిటికీ_Texture(_this, కిటికీ);
    SDL_DestroyProperties(కిటికీ->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ఒకవేళ (_this->సమితి_కిటికీ_Modal && (కిటికీ->flags & SDL_కిటికీ_MODAL)) {
        _this->సమితి_కిటికీ_Modal(_this, కిటికీ, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
        ఒకవేళ (_this->displays[i]->fullscreen_కిటికీ == కిటికీ) {
            _this->displays[i]->fullscreen_కిటికీ = ఖాళీ;
        }
    }

    // Make sure this window no longer has focus
    ఒకవేళ (SDL_GetKeyboardFocus() == కిటికీ) {
        SDL_సమితి_Keyboard_Focus(ఖాళీ);
    }
    ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ఒకవేళ (SDL_GetMouseFocus() == కిటికీ) {
        SDL_సమితి_Mouse_Focus(ఖాళీ);
    }

    // Make no context current if this is the current context window
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        ఒకవేళ (_this->current_glwin == కిటికీ) {
            SDL_GL_MakeCurrent(కిటికీ, ఖాళీ);
        }
    }

    ఒకవేళ (_this->Destroy_కిటికీ) {
        _this->Destroy_కిటికీ(_this, కిటికీ);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ఒకవేళ (_this->grabbed_కిటికీ == కిటికీ) {
        _this->grabbed_కిటికీ = ఖాళీ; // ungrabbing input.
    }

    ఒకవేళ (_this->current_glwin == కిటికీ) {
        _this->current_glwin = ఖాళీ;
    }

    SDL_Compare_And_మార్పిడి_Atomic_సూచిక(&_this->wakeup_కిటికీ, కిటికీ, ఖాళీ);

    // Now invalidate magic
    SDL_సమితి_Object_Valid(కిటికీ, SDL_OBJECT_TYPE_కిటికీ, false);

    // Free memory associated with the window
    SDL_free(కిటికీ->title);
    SDL_DestroySurface(కిటికీ->icon);

    // Unlink the window from its siblings.
    SDL_Update_కిటికీ_Hierarchy(కిటికీ, ఖాళీ);

    // Unlink the window from the global window list
    ఒకవేళ (కిటికీ->తదుపరి) {
        కిటికీ->తదుపరి->prev = కిటికీ->prev;
    }
    ఒకవేళ (కిటికీ->prev) {
        కిటికీ->prev->తదుపరి = కిటికీ->తదుపరి;
    } లేకపోతే {
        _this->windows = కిటికీ->తదుపరి;
    }

    SDL_free(కిటికీ->renderers);
    SDL_free(కిటికీ);

#నిర్వచితమైతే SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#అయితే_ముగింపు
}

bool SDL_ScreenSaverEnabled(శూన్య)
{
    ఒకవేళ (!_this) {
        తిరిగి true;
    }
    తిరిగి !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(శూన్య)
{
    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }
    ఒకవేళ (!_this->suspend_screensaver) {
        తిరిగి true;
    }
    _this->suspend_screensaver = false;
    ఒకవేళ (_this->SuspendScreenSaver) {
        తిరిగి _this->SuspendScreenSaver(_this);
    }

    తిరిగి SDL_Unsupported();
}

bool SDL_DisableScreenSaver(శూన్య)
{
    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }
    ఒకవేళ (_this->suspend_screensaver) {
        తిరిగి true;
    }
    _this->suspend_screensaver = true;
    ఒకవేళ (_this->SuspendScreenSaver) {
        తిరిగి _this->SuspendScreenSaver(_this);
    }

    తిరిగి SDL_Unsupported();
}

శూన్య SDL_QuitVideo(శూన్య)
{
    పూర్ణాంకం i;

    ఒకవేళ (!_this) {
        తిరిగి;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ఒకవేళ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#అయితే_ముగింపు
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    అయితే (_this->windows) {
        SDL_Destroy_కిటికీ(_this->windows);
    }

    ఒకవేళ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ఒకవేళ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    కొరకు (i = _this->అంకె_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->అంకె_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ఖాళీ;

    SDL_Cancel_Clipboard_దత్తాంశం(0);

    ఒకవేళ (_this->primary_selection_పాఠ్యం) {
        SDL_free(_this->primary_selection_పాఠ్యం);
        _this->primary_selection_పాఠ్యం = ఖాళీ;
    }
    _this->విడుదల(_this);
    _this = ఖాళీ;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_ఎక్కించు_Library(స్థిరరాశి అక్షరం *మార్గం)
{
    bool ఫలితం;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }
    ఒకవేళ (_this->gl_config.driver_loaded) {
        ఒకవేళ (మార్గం && SDL_strcmp(మార్గం, _this->gl_config.driver_మార్గం) != 0) {
            తిరిగి SDL_సమితి_Error("OpenGL library already loaded");
        }
        ఫలితం = true;
    } లేకపోతే {
        ఒకవేళ (!_this->GL_ఎక్కించు_Library) {
            తిరిగి SDL_DllNotSupported("OpenGL");
        }
        ఫలితం = _this->GL_ఎక్కించు_Library(_this, మార్గం);
    }
    ఒకవేళ (ఫలితం) {
        ++_this->gl_config.driver_loaded;
    } లేకపోతే {
        ఒకవేళ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    తిరిగి ఫలితం;
}

SDL_Function_సూచిక SDL_GL_Get_Proc_చిరునామా(స్థిరరాశి అక్షరం *proc)
{
    SDL_Function_సూచిక func;

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    func = ఖాళీ;
    ఒకవేళ (_this->GL_Get_Proc_చిరునామా) {
        ఒకవేళ (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_చిరునామా(_this, proc);
        } లేకపోతే {
            SDL_సమితి_Error("No GL driver has been loaded");
        }
    } లేకపోతే {
        SDL_సమితి_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    తిరిగి func;
}

SDL_Function_సూచిక SDL_EGL_Get_Proc_చిరునామా(స్థిరరాశి అక్షరం *proc)
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    SDL_Function_సూచిక func;

    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    func = ఖాళీ;

    ఒకవేళ (_this->egl_దత్తాంశం) {
        func = SDL_EGL_Get_Proc_చిరునామా_అంతర్గత(_this, proc);
    } లేకపోతే {
        SDL_సమితి_Error("No EGL library has been loaded");
    }

    తిరిగి func;
#లేకపోతే
    SDL_సమితి_Error("SDL was not built with EGL support");
    తిరిగి ఖాళీ;
#అయితే_ముగింపు
}

శూన్య SDL_GL_UnloadLibrary(శూన్య)
{
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి;
    }
    ఒకవేళ (_this->gl_config.driver_loaded > 0) {
        ఒకవేళ (--_this->gl_config.driver_loaded > 0) {
            తిరిగి;
        }
        ఒకవేళ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
రకనిర్వచనం GLenum (APIENTRY* PFNGLGETERRORPROC) (శూన్య);
రకనిర్వచనం శూన్య (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
రకనిర్వచనం స్థిరరాశి GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
రకనిర్వచనం శూన్య (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#నిర్వచితం_కాకపోతే SDL_VIDEO_OPENGL
రకనిర్వచనం స్థిరరాశి GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint సూచీ);
#అయితే_ముగింపు

స్థిర SDL_INLINE bool is_At_కనిష్ఠ_GL3(స్థిరరాశి అక్షరం *verstr)
{
    తిరిగి verstr && (SDL_atoi(verstr) >= 3);
}
#అయితే_ముగింపు // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(స్థిరరాశి అక్షరం *extension)
{
#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    స్థిరరాశి అక్షరం *extensions;
    స్థిరరాశి అక్షరం *ప్రారంభం;
    స్థిరరాశి అక్షరం *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ఒకవేళ (where || *extension == '\0') {
        తిరిగి false;
    }
    // See if there's a hint or environment variable override
    ప్రారంభం = SDL_GetHint(extension);
    ఒకవేళ (ప్రారంభం && *ప్రారంభం == '0') {
        తిరిగి false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_చిరునామా("glGetString");
    ఒకవేళ (!glGetStringFunc) {
        తిరిగి false;
    }

    ఒకవేళ (is_At_కనిష్ఠ_GL3((స్థిరరాశి అక్షరం *)glGetStringFunc(GL_సంస్కరణ))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint అంకె_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_చిరునామా("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_చిరునామా("glGetIntegerv");
        ఒకవేళ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            తిరిగి false;
        }

#నిర్వచితం_కాకపోతే GL_అంకె_EXTENSIONS
#నిర్వచించు GL_అంకె_EXTENSIONS 0x821D
#అయితే_ముగింపు
        glGetIntegervFunc(GL_అంకె_EXTENSIONS, &అంకె_exts);
        కొరకు (i = 0; i < అంకె_exts; i++) {
            స్థిరరాశి అక్షరం *thisext = (స్థిరరాశి అక్షరం *)glGetStringiFunc(GL_EXTENSIONS, i);
            ఒకవేళ (SDL_strcmp(thisext, extension) == 0) {
                తిరిగి true;
            }
        }

        తిరిగి false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (స్థిరరాశి అక్షరం *)glGetStringFunc(GL_EXTENSIONS);
    ఒకవేళ (!extensions) {
        తిరిగి false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    ప్రారంభం = extensions;

    కొరకు (;;) {
        where = SDL_strstr(ప్రారంభం, extension);
        ఒకవేళ (!where) {
            ఆపు;
        }

        terminator = where + SDL_strlen(extension);
        ఒకవేళ (where == extensions || *(where - 1) == ' ') {
            ఒకవేళ (*terminator == ' ' || *terminator == '\0') {
                తిరిగి true;
            }
        }

        ప్రారంభం = terminator;
    }
    తిరిగి false;
#లేకపోతే
    తిరిగి false;
#అయితే_ముగింపు
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
శూన్య SDL_GL_DeduceMaxSupportedESProfile(పూర్ణాంకం *major, పూర్ణాంకం *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ఒకవేళ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } లేకపోతే ఒకవేళ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } లేకపోతే ఒకవేళ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } లేకపోతే {
        *major = 2;
        *minor = 0;
    }
#అయితే_ముగింపు
}

శూన్య SDL_EGL_సమితి_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   శూన్య *userdata)
{
    ఒకవేళ (!_this) {
        తిరిగి;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

శూన్య SDL_GL_Reset_లక్షణాలు(శూన్య)
{
    ఒకవేళ (!_this) {
        తిరిగి;
    }

    _this->egl_platformattrib_callback = ఖాళీ;
    _this->egl_surfaceattrib_callback = ఖాళీ;
    _this->egl_contextattrib_callback = ఖాళీ;
    _this->egl_attrib_callback_userdata = ఖాళీ;

    _this->gl_config.red_కొలత = 8;
    _this->gl_config.green_కొలత = 8;
    _this->gl_config.blue_కొలత = 8;
    _this->gl_config.alpha_కొలత = 8;
    _this->gl_config.బఫరు_కొలత = 0;
    _this->gl_config.లోతు_కొలత = 16;
    _this->gl_config.stencil_కొలత = 0;
    _this->gl_config.double_బఫరు = 1;
    _this->gl_config.accum_red_కొలత = 0;
    _this->gl_config.accum_green_కొలత = 0;
    _this->gl_config.accum_blue_కొలత = 0;
    _this->gl_config.accum_alpha_కొలత = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#నిర్వచితమైతే SDL_VIDEO_OPENGL
    _this->gl_config.major_సంస్కరణ = 2;
    _this->gl_config.minor_సంస్కరణ = 1;
    _this->gl_config.profile_ముసుగు = 0;
#లేదావేళ defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_సంస్కరణ = 2;
    _this->gl_config.minor_సంస్కరణ = 0;
    _this->gl_config.profile_ముసుగు = SDL_GL_CONTEXT_PROFILE_ES;
#లేదావేళ defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_సంస్కరణ = 1;
    _this->gl_config.minor_సంస్కరణ = 1;
    _this->gl_config.profile_ముసుగు = SDL_GL_CONTEXT_PROFILE_ES;
#అయితే_ముగింపు

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    ఒకవేళ (_this->GL_సమితి_Default_Profile_Config) {
        _this->GL_సమితి_Default_Profile_Config(_this);
    }
}

bool SDL_GL_సమితి_Attribute(SDL_GLAttr attr, పూర్ణాంకం విలువ)
{
#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool ఫలితం;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }
    ఫలితం = true;
    ఎంపిక (attr) {
    స్థితి SDL_GL_RED_కొలత:
        _this->gl_config.red_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_GREEN_కొలత:
        _this->gl_config.green_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_BLUE_కొలత:
        _this->gl_config.blue_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_ALPHA_కొలత:
        _this->gl_config.alpha_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_బఫరు = విలువ;
        ఆపు;
    స్థితి SDL_GL_బఫరు_కొలత:
        _this->gl_config.బఫరు_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_లోతు_కొలత:
        _this->gl_config.లోతు_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_STENCIL_కొలత:
        _this->gl_config.stencil_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_ACCUM_RED_కొలత:
        _this->gl_config.accum_red_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_ACCUM_GREEN_కొలత:
        _this->gl_config.accum_green_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_ACCUM_BLUE_కొలత:
        _this->gl_config.accum_blue_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_ACCUM_ALPHA_కొలత:
        _this->gl_config.accum_alpha_కొలత = విలువ;
        ఆపు;
    స్థితి SDL_GL_STEREO:
        _this->gl_config.stereo = విలువ;
        ఆపు;
    స్థితి SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = విలువ;
        ఆపు;
    స్థితి SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = విలువ;
        ఆపు;
    స్థితి SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = విలువ;
        ఆపు;
    స్థితి SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = విలువ;
        ఆపు;
    స్థితి SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_MAJOR_సంస్కరణ:
        _this->gl_config.major_సంస్కరణ = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_MINOR_సంస్కరణ:
        _this->gl_config.minor_సంస్కరణ = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_FLAGS:
        ఒకవేళ (విలువ & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            ఫలితం = SDL_సమితి_Error("Unknown OpenGL context flag %d", విలువ);
            ఆపు;
        }
        _this->gl_config.flags = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_PROFILE_ముసుగు:
        ఒకవేళ (విలువ != 0 &&
            విలువ != SDL_GL_CONTEXT_PROFILE_CORE &&
            విలువ != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            విలువ != SDL_GL_CONTEXT_PROFILE_ES) {
            ఫలితం = SDL_సమితి_Error("Unknown OpenGL context profile %d", విలువ);
            ఆపు;
        }
        _this->gl_config.profile_ముసుగు = విలువ;
        ఆపు;
    స్థితి SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = విలువ;
        ఆపు;
    స్థితి SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = విలువ;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = విలువ;
        ఆపు;
    స్థితి SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = విలువ;
        ఆపు;
    అప్రమేయ:
        ఫలితం = SDL_సమితి_Error("Unknown OpenGL attribute");
        ఆపు;
    }
    తిరిగి ఫలితం;
#లేకపోతే
    తిరిగి SDL_Unsupported();
#అయితే_ముగింపు // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, పూర్ణాంకం *విలువ)
{
#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#నిర్వచితమైతే SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_వెనుక_ఎడమ;
    GLenum attachmentattrib = 0;
#అయితే_ముగింపు

    CHECK_PARAM(!విలువ) {
        తిరిగి SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *విలువ = 0;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    ఎంపిక (attr) {
    స్థితి SDL_GL_RED_కొలత:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_కొలత;
#అయితే_ముగింపు
        attrib = GL_RED_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_BLUE_కొలత:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_కొలత;
#అయితే_ముగింపు
        attrib = GL_BLUE_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_GREEN_కొలత:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_కొలత;
#అయితే_ముగింపు
        attrib = GL_GREEN_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_ALPHA_కొలత:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_కొలత;
#అయితే_ముగింపు
        attrib = GL_ALPHA_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_DOUBLEBUFFER:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        ఆపు;
#లేకపోతే
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *విలువ = _this->gl_config.double_బఫరు;
        తిరిగి true;
#అయితే_ముగింపు
    స్థితి SDL_GL_లోతు_కొలత:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attachment = GL_లోతు;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_లోతు_కొలత;
#అయితే_ముగింపు
        attrib = GL_లోతు_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_STENCIL_కొలత:
#నిర్వచితమైతే SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_కొలత;
#అయితే_ముగింపు
        attrib = GL_STENCIL_బిట్లు;
        ఆపు;
#నిర్వచితమైతే SDL_VIDEO_OPENGL
    స్థితి SDL_GL_ACCUM_RED_కొలత:
        attrib = GL_ACCUM_RED_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_ACCUM_GREEN_కొలత:
        attrib = GL_ACCUM_GREEN_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_ACCUM_BLUE_కొలత:
        attrib = GL_ACCUM_BLUE_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_ACCUM_ALPHA_కొలత:
        attrib = GL_ACCUM_ALPHA_బిట్లు;
        ఆపు;
    స్థితి SDL_GL_STEREO:
        attrib = GL_STEREO;
        ఆపు;
#లేకపోతే
    స్థితి SDL_GL_ACCUM_RED_కొలత:
    స్థితి SDL_GL_ACCUM_GREEN_కొలత:
    స్థితి SDL_GL_ACCUM_BLUE_కొలత:
    స్థితి SDL_GL_ACCUM_ALPHA_కొలత:
    స్థితి SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *విలువ = 0;
        తిరిగి true;
#అయితే_ముగింపు
    స్థితి SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        ఆపు;
    స్థితి SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        ఆపు;
    స్థితి SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        ఆపు;
    స్థితి SDL_GL_బఫరు_కొలత:
    {
        పూర్ణాంకం rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ఒకవేళ (!SDL_GL_GetAttribute(SDL_GL_RED_కొలత, &rsize)) {
            తిరిగి false;
        }
        ఒకవేళ (!SDL_GL_GetAttribute(SDL_GL_GREEN_కొలత, &gsize)) {
            తిరిగి false;
        }
        ఒకవేళ (!SDL_GL_GetAttribute(SDL_GL_BLUE_కొలత, &bsize)) {
            తిరిగి false;
        }
        ఒకవేళ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_కొలత, &asize)) {
            తిరిగి false;
        }

        *విలువ = rsize + gsize + bsize + asize;
        తిరిగి true;
    }
    స్థితి SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *విలువ = (_this->gl_config.accelerated != 0);
        తిరిగి true;
    }
    స్థితి SDL_GL_RETAINED_BACKING:
    {
        *విలువ = _this->gl_config.retained_backing;
        తిరిగి true;
    }
    స్థితి SDL_GL_CONTEXT_MAJOR_సంస్కరణ:
    {
        *విలువ = _this->gl_config.major_సంస్కరణ;
        తిరిగి true;
    }
    స్థితి SDL_GL_CONTEXT_MINOR_సంస్కరణ:
    {
        *విలువ = _this->gl_config.minor_సంస్కరణ;
        తిరిగి true;
    }
    స్థితి SDL_GL_CONTEXT_FLAGS:
    {
        *విలువ = _this->gl_config.flags;
        తిరిగి true;
    }
    స్థితి SDL_GL_CONTEXT_PROFILE_ముసుగు:
    {
        *విలువ = _this->gl_config.profile_ముసుగు;
        తిరిగి true;
    }
    స్థితి SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *విలువ = _this->gl_config.share_with_current_context;
        తిరిగి true;
    }
    స్థితి SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *విలువ = _this->gl_config.framebuffer_srgb_capable;
        తిరిగి true;
    }
    స్థితి SDL_GL_CONTEXT_NO_ERROR:
    {
        *విలువ = _this->gl_config.no_error;
        తిరిగి true;
    }
    స్థితి SDL_GL_EGL_PLATFORM:
    {
        *విలువ = _this->gl_config.egl_platform;
        తిరిగి true;
    }
    స్థితి SDL_GL_FLOATBUFFERS:
    {
        ఒకవేళ (_this->gl_config.HAS_GL_ARB_color_బఫరు_float) {
            attrib = GL_RGBA_FLOAT_బహుళకం_ARB;
            ఆపు;
        } లేకపోతే {
            తిరిగి 0;
        }
    }
    అప్రమేయ:
        తిరిగి SDL_సమితి_Error("Unknown OpenGL attribute");
    }

#నిర్వచితమైతే SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_చిరునామా("glGetString");
    ఒకవేళ (!glGetStringFunc) {
        తిరిగి false;
    }

    ఒకవేళ (attachmentattrib && is_At_కనిష్ఠ_GL3((స్థిరరాశి అక్షరం *)glGetStringFunc(GL_సంస్కరణ))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_చిరునామా("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_చిరునామా("glBindFramebuffer");
        ఒకవేళ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_చిరునామా("glGetFramebufferAttachmentParameteriv");
        ఒకవేళ (glGetFramebufferAttachmentParameterivFunc) {
            ఒకవేళ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ఒకవేళ (attachment == GL_లోతు || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ఒకవేళ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)విలువ);
            } లేకపోతే {
                *విలువ = 0;
            }
            ఒకవేళ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } లేకపోతే {
            తిరిగి false;
        }
    } లేకపోతే
#అయితే_ముగింపు
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_చిరునామా("glGetIntegerv");
        ఒకవేళ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)విలువ);
        } లేకపోతే {
            తిరిగి false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_చిరునామా("glGetError");
    ఒకవేళ (!glGetErrorFunc) {
        తిరిగి false;
    }

    error = glGetErrorFunc();
    ఒకవేళ (error != GL_NO_ERROR) {
        ఒకవేళ (error == GL_INVALID_ENUM) {
            తిరిగి SDL_సమితి_Error("OpenGL error: GL_INVALID_ENUM");
        } లేకపోతే ఒకవేళ (error == GL_INVALID_విలువ) {
            తిరిగి SDL_సమితి_Error("OpenGL error: GL_INVALID_VALUE");
        }
        తిరిగి SDL_సమితి_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ఒకవేళ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *విలువ = (*విలువ == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    తిరిగి true;
#లేకపోతే
    తిరిగి SDL_Unsupported();
#అయితే_ముగింపు // SDL_VIDEO_OPENGL
}

#నిర్వచించు NOT_AN_OPENGL_కిటికీ "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_కిటికీ *కిటికీ)
{
    SDL_GLContext ctx = ఖాళీ;
    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_OPENGL)) {
        SDL_సమితి_Error(NOT_AN_OPENGL_కిటికీ);
        తిరిగి ఖాళీ;
    }

#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    పూర్ణాంకం srgb_requested = -1;
    స్థిరరాశి అక్షరం *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ఒకవేళ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#అయితే_ముగింపు

    ctx = _this->GL_CreateContext(_this, కిటికీ);

    // Creating a context is assumed to make it current in the SDL driver.
    ఒకవేళ (ctx) {
        _this->current_glwin = కిటికీ;
        _this->current_glctx = ctx;
        SDL_సమితి_TLS(&_this->current_glwin_tls, కిటికీ, ఖాళీ);
        SDL_సమితి_TLS(&_this->current_glctx_tls, ctx, ఖాళీ);
    }

#ఒకవేళ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ఒకవేళ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_చిరునామా(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_చిరునామా("glGetString");
        ఒకవేళ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ఒకవేళ (_this->gl_config.profile_ముసుగు & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } లేకపోతే {
                supported = is_At_కనిష్ఠ_GL3((స్థిరరాశి అక్షరం *)glGetStringFunc(GL_సంస్కరణ)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ఒకవేళ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#అయితే_ముగింపు

    తిరిగి ctx;
}

bool SDL_GL_MakeCurrent(SDL_కిటికీ *కిటికీ, SDL_GLContext context)
{
    bool ఫలితం;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }

    ఒకవేళ (కిటికీ == SDL_GL_Get_Current_కిటికీ() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        తిరిగి true;
    }

    ఒకవేళ (!context) {
        కిటికీ = ఖాళీ;
    } లేకపోతే ఒకవేళ (కిటికీ) {
        CHECK_కిటికీ_MAGIC(కిటికీ, false);

        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_OPENGL)) {
            తిరిగి SDL_సమితి_Error(NOT_AN_OPENGL_కిటికీ);
        }
    } లేకపోతే ఒకవేళ (!_this->gl_allow_no_surface) {
        తిరిగి SDL_సమితి_Error("Use of OpenGL without a window is not supported on this platform");
    }

    ఫలితం = _this->GL_MakeCurrent(_this, కిటికీ, context);
    ఒకవేళ (ఫలితం) {
        _this->current_glwin = కిటికీ;
        _this->current_glctx = context;
        SDL_సమితి_TLS(&_this->current_glwin_tls, కిటికీ, ఖాళీ);
        SDL_సమితి_TLS(&_this->current_glctx_tls, context, ఖాళీ);
    }
    తిరిగి ఫలితం;
}

SDL_కిటికీ *SDL_GL_Get_Current_కిటికీ(శూన్య)
{
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    తిరిగి (SDL_కిటికీ *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(శూన్య)
{
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    తిరిగి (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(శూన్య)
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి EGL_NO_DISPLAY;
    }
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        SDL_సమితి_Error("There is no current EGL display");
        తిరిగి EGL_NO_DISPLAY;
    }
    తిరిగి _this->egl_దత్తాంశం->egl_display;
#లేకపోతే
    SDL_సమితి_Error("SDL was not built with EGL support");
    తిరిగి ఖాళీ;
#అయితే_ముగింపు
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(శూన్య)
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        SDL_సమితి_Error("There is no current EGL display");
        తిరిగి ఖాళీ;
    }
    తిరిగి _this->egl_దత్తాంశం->egl_config;
#లేకపోతే
    SDL_సమితి_Error("SDL was not built with EGL support");
    తిరిగి ఖాళీ;
#అయితే_ముగింపు
}

SDL_EGLConfig SDL_EGL_Get_కిటికీ_Surface(SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (!_this->egl_దత్తాంశం) {
        SDL_సమితి_Error("There is no current EGL display");
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (_this->GL_GetEGLSurface) {
        తిరిగి _this->GL_GetEGLSurface(_this, కిటికీ);
    }
    తిరిగి ఖాళీ;
#లేకపోతే
    SDL_సమితి_Error("SDL was not built with EGL support");
    తిరిగి ఖాళీ;
#అయితే_ముగింపు
}

bool SDL_GL_సమితి_మార్పిడి_Interval(పూర్ణాంకం interval)
{
    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    } లేకపోతే ఒకవేళ (SDL_GL_GetCurrentContext() == ఖాళీ) {
        తిరిగి SDL_సమితి_Error("No OpenGL context has been made current");
    } లేకపోతే ఒకవేళ (_this->GL_సమితి_మార్పిడి_Interval) {
        తిరిగి _this->GL_సమితి_మార్పిడి_Interval(_this, interval);
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_మార్పిడి_Interval(పూర్ణాంకం *interval)
{
    CHECK_PARAM(!interval) {
       తిరిగి SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ఒకవేళ (!_this) {
        తిరిగి SDL_సమితి_Error("no video driver");
    } లేకపోతే ఒకవేళ (SDL_GL_GetCurrentContext() == ఖాళీ) {
        తిరిగి SDL_సమితి_Error("no current context");
    } లేకపోతే ఒకవేళ (_this->GL_Get_మార్పిడి_Interval) {
        తిరిగి _this->GL_Get_మార్పిడి_Interval(_this, interval);
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("not implemented");
    }
}

bool SDL_GL_మార్పిడి_కిటికీ(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_OPENGL)) {
        తిరిగి SDL_సమితి_Error(NOT_AN_OPENGL_కిటికీ);
    }

    ఒకవేళ (SDL_GL_Get_Current_కిటికీ() != కిటికీ) {
        తిరిగి SDL_సమితి_Error("The specified window has not been made current");
    }

    తిరిగి _this->GL_మార్పిడి_కిటికీ(_this, కిటికీ);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        తిరిగి SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        తిరిగి SDL_InvalidParamError("context");
    }

    ఒకవేళ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ఖాళీ, ఖాళీ);
    }

    తిరిగి _this->GL_DestroyContext(_this, context);
}

#ఒకవేళ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
స్థిర శూన్య Create_ముసుగు_From_Color_కీలకం_Or_Alpha(SDL_Surface *icon, Uint8 *ముసుగు, పూర్ణాంకం flags)
{
    పూర్ణాంకం x, y;
    Uint32 colorkey;
#నిర్వచించు సమితి_MASKBIT(icon, x, y, ముసుగు) \
    ముసుగు[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    ఎంపిక (SDL_BYTESPERPIXEL(icon->format)) {
    స్థితి 1:
        {
            Uint8 *pixels;
            కొరకు (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                కొరకు (x = 0; x < icon->w; ++x) {
                    ఒకవేళ (*pixels++ == colorkey) {
                        సమితి_MASKBIT(icon, x, y, ముసుగు);
                    }
                }
            }
        }
        ఆపు;

    స్థితి 2:
        {
            Uint16 *pixels;
            కొరకు (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                కొరకు (x = 0; x < icon->w; ++x) {
                    ఒకవేళ ((flags & 1) && *pixels == colorkey) {
                        సమితి_MASKBIT(icon, x, y, ముసుగు);
                    } లేకపోతే ఒకవేళ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        సమితి_MASKBIT(icon, x, y, ముసుగు);
                    }
                    pixels++;
                }
            }
        }
        ఆపు;

    స్థితి 4:
        {
            Uint32 *pixels;
            కొరకు (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                కొరకు (x = 0; x < icon->w; ++x) {
                    ఒకవేళ ((flags & 1) && *pixels == colorkey) {
                        సమితి_MASKBIT(icon, x, y, ముసుగు);
                    } లేకపోతే ఒకవేళ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        సమితి_MASKBIT(icon, x, y, ముసుగు);
                    }
                    pixels++;
                }
            }
        }
        ఆపు;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
శూన్య SDL_WM_సమితి_Icon(SDL_Surface *icon, Uint8 *ముసుగు)
{
    ఒకవేళ (icon && _this->సమితి_Icon) {
        // Generate a mask if necessary, and create the icon!
        ఒకవేళ (ముసుగు == ఖాళీ) {
            పూర్ణాంకం ముసుగు_len = icon->h * (icon->w + 7) / 8;
            పూర్ణాంకం flags = 0;
            ముసుగు = (Uint8 *) SDL_malloc(ముసుగు_len);
            ఒకవేళ (ముసుగు == ఖాళీ) {
                తిరిగి;
            }
            SDL_memset(ముసుగు, ~0, ముసుగు_len);
            ఒకవేళ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ఒకవేళ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ఒకవేళ (flags) {
                Create_ముసుగు_From_Color_కీలకం_Or_Alpha(icon, ముసుగు, flags);
            }
            _this->సమితి_Icon(_this, icon, ముసుగు);
            SDL_free(ముసుగు);
        } లేకపోతే {
            _this->సమితి_Icon(_this, icon, ముసుగు);
        }
    }
}
#అయితే_ముగింపు

SDL_పాఠ్యం_ఆదానం_Type SDL_Get_పాఠ్యం_ఆదానం_Type(SDL_PropertiesID props)
{
    తిరిగి (SDL_పాఠ్యం_ఆదానం_Type)SDL_Get_సంఖ్య_Property(props, SDL_PROP_TEXTINPUT_TYPE_సంఖ్య, SDL_TEXTINPUT_TYPE_పాఠ్యం);
}

SDL_Capitalization SDL_Get_పాఠ్యం_ఆదానం_Capitalization(SDL_PropertiesID props)
{
    ఒకవేళ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_సంఖ్య)) {
        తిరిగి (SDL_Capitalization)SDL_Get_సంఖ్య_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_సంఖ్య, SDL_CAPITALIZE_NONE);
    }

    ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం:
        తిరిగి SDL_CAPITALIZE_SENTENCES;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_NAME:
        తిరిగి SDL_CAPITALIZE_పదాలు;
    అప్రమేయ:
        తిరిగి SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_పాఠ్యం_ఆదానం_Autocorrect(SDL_PropertiesID props)
{
    తిరిగి SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_పాఠ్యం_ఆదానం_Multiline(SDL_PropertiesID props)
{
    ఒకవేళ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        తిరిగి SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_RETURN_కీలకం_HIDES_IME, false)) {
        తిరిగి false;
    } లేకపోతే {
        తిరిగి true;
    }
}

స్థిర bool AutoShowingScreenKeyboard(శూన్య)
{
    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ఒకవేళ (!hint) {
        // This hint is currently only used by the X11 video driver
        ఒకవేళ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ఒకవేళ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        తిరిగి true;
    } లేకపోతే {
        తిరిగి false;
    }
}

bool SDL_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_కిటికీ *కిటికీ)
{
    తిరిగి SDL_ప్రారంభం_పాఠ్యం_ఆదానం_With_Properties(కిటికీ, 0);
}

bool SDL_ప్రారంభం_పాఠ్యం_ఆదానం_With_Properties(SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (కిటికీ->పాఠ్యం_ఆదానం_props) {
        SDL_DestroyProperties(కిటికీ->పాఠ్యం_ఆదానం_props);
        కిటికీ->పాఠ్యం_ఆదానం_props = 0;
    }

    ఒకవేళ (props) {
        కిటికీ->పాఠ్యం_ఆదానం_props = SDL_CreateProperties();
        ఒకవేళ (!కిటికీ->పాఠ్యం_ఆదానం_props) {
            తిరిగి false;
        }
        ఒకవేళ (!SDL_CopyProperties(props, కిటికీ->పాఠ్యం_ఆదానం_props)) {
            తిరిగి false;
        }
    }

    ఒకవేళ (_this->సమితి_పాఠ్యం_ఆదానం_Properties) {
        _this->సమితి_పాఠ్యం_ఆదానం_Properties(_this, కిటికీ, props);
    }

    ఒకవేళ (!కిటికీ->పాఠ్యం_ఆదానం_చురుకైన) {
        // Start the text input system
        ఒకవేళ (_this->ప్రారంభం_పాఠ్యం_ఆదానం) {
            ఒకవేళ (!_this->ప్రారంభం_పాఠ్యం_ఆదానం(_this, కిటికీ, props)) {
                తిరిగి false;
            }
        }
        కిటికీ->పాఠ్యం_ఆదానం_చురుకైన = true;
    }

    // Show the on-screen keyboard, if desired
    ఒకవేళ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(కిటికీ)) {
        ఒకవేళ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, కిటికీ, props);
        }
    }
    తిరిగి true;
}

bool SDL_పాఠ్యం_ఆదానం_చురుకైన(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    తిరిగి కిటికీ->పాఠ్యం_ఆదానం_చురుకైన;
}

bool SDL_Stop_పాఠ్యం_ఆదానం(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (కిటికీ->పాఠ్యం_ఆదానం_చురుకైన) {
        // Stop the text input system
        ఒకవేళ (_this->Stop_పాఠ్యం_ఆదానం) {
            _this->Stop_పాఠ్యం_ఆదానం(_this, కిటికీ);
        }
        కిటికీ->పాఠ్యం_ఆదానం_చురుకైన = false;
    }

    // Hide the on-screen keyboard, if desired
    ఒకవేళ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(కిటికీ)) {
        ఒకవేళ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, కిటికీ);
        }
    }
    తిరిగి true;
}

bool SDL_సమితి_పాఠ్యం_ఆదానం_Area(SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rect, పూర్ణాంకం cursor)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (rect) {
        SDL_copyp(&కిటికీ->పాఠ్యం_ఆదానం_rect, rect);
        కిటికీ->పాఠ్యం_ఆదానం_cursor = cursor;
    } లేకపోతే {
        SDL_zero(కిటికీ->పాఠ్యం_ఆదానం_rect);
        కిటికీ->పాఠ్యం_ఆదానం_cursor = 0;
    }

    ఒకవేళ (_this && _this->Update_పాఠ్యం_ఆదానం_Area) {
        ఒకవేళ (!_this->Update_పాఠ్యం_ఆదానం_Area(_this, కిటికీ)) {
            తిరిగి false;
        }
    }
    తిరిగి true;
}

bool SDL_Get_పాఠ్యం_ఆదానం_Area(SDL_కిటికీ *కిటికీ, SDL_Rect *rect, పూర్ణాంకం *cursor)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (rect) {
        SDL_copyp(rect, &కిటికీ->పాఠ్యం_ఆదానం_rect);
    }
    ఒకవేళ (cursor) {
        *cursor = కిటికీ->పాఠ్యం_ఆదానం_cursor;
    }
    తిరిగి true;
}

bool SDL_ClearComposition(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (_this->ClearComposition) {
        తిరిగి _this->ClearComposition(_this, కిటికీ);
    }
    తిరిగి true;
}

bool SDL_HasScreenKeyboardSupport(శూన్య)
{
    ఒకవేళ (_this && _this->HasScreenKeyboardSupport) {
        తిరిగి _this->HasScreenKeyboardSupport(_this);
    }
    తిరిగి false;
}

bool SDL_ScreenKeyboardShown(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    తిరిగి _this->screen_keyboard_shown;
}

శూన్య SDL_SendScreenKeyboardShown(శూన్య)
{
    ఒకవేళ (!_this || _this->screen_keyboard_shown) {
        తిరిగి;
    }

    _this->screen_keyboard_shown = true;

    ఒకవేళ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_నెట్టు_Event(&event);
    }
}

శూన్య SDL_SendScreenKeyboardHidden(శూన్య)
{
    ఒకవేళ (!_this || !_this->screen_keyboard_shown) {
        తిరిగి;
    }

    _this->screen_keyboard_shown = false;

    ఒకవేళ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_నెట్టు_Event(&event);
    }
}

పూర్ణాంకం SDL_Get_సందేశం_Box_లెక్క(శూన్య)
{
    తిరిగి SDL_GetAtomicInt(&SDL_messagebox_లెక్క);
}

bool SDL_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
    పూర్ణాంకం dummybutton;
    bool ఫలితం = false;
    bool show_cursor_prev;
    SDL_కిటికీ *current_కిటికీ;
    SDL_సందేశం_Box_దత్తాంశం mbdata;

    CHECK_PARAM(!messageboxdata) {
        తిరిగి SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        తిరిగి SDL_సమితి_Error("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    అక్షరం *titlecpy = ఖాళీ;
    అక్షరం *msgcpy = ఖాళీ;
    ఒకవేళ (messageboxdata->title) {
        స్థిరరాశి size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(అక్షరం, slen, &titleisstack);
        ఒకవేళ (!titlecpy) {
            తిరిగి false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ఒకవేళ (messageboxdata->సందేశం) {
        స్థిరరాశి size_t slen = SDL_strlen(messageboxdata->సందేశం) + 1;
        msgcpy = SDL_small_alloc(అక్షరం, slen, &msgisstack);
        ఒకవేళ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            తిరిగి false;
        }
        SDL_memcpy(msgcpy, messageboxdata->సందేశం, slen);
    }

    (శూన్య)SDL_AtomicIncRef(&SDL_messagebox_లెక్క);

    current_కిటికీ = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_సమితి_Relative_Mouse_బహుళకం(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    ఒకవేళ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, పరిమాణం(*messageboxdata));
    mbdata.title = titlecpy;
    ఒకవేళ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.సందేశం = msgcpy;
    ఒకవేళ (!mbdata.సందేశం) {
        mbdata.సందేశం = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ఒకవేళ (_this && _this->Show_సందేశం_Box) {
        ఫలితం = _this->Show_సందేశం_Box(_this, messageboxdata, buttonID);
    } లేకపోతే {
        // It's completely fine to call this function before video is initialized
        స్థిరరాశి అక్షరం *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ఒకవేళ (driver_name && *driver_name != 0) {
            స్థిరరాశి అక్షరం *driver_attempt = driver_name;
            అయితే (driver_attempt && (*driver_attempt != 0) && !ఫలితం) {
                స్థిరరాశి అక్షరం *driver_attempt_చివర = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_చివర) ? (driver_attempt_చివర - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                కొరకు (పూర్ణాంకం i = 0; bootstrap[i]; ++i) {
                    ఒకవేళ (bootstrap[i]->Show_సందేశం_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ఒకవేళ (bootstrap[i]->Show_సందేశం_Box(messageboxdata, buttonID)) {
                            ఫలితం = true;
                        }
                        ఆపు;
                    }
                }

                driver_attempt = (driver_attempt_చివర) ? (driver_attempt_చివర + 1) : ఖాళీ;
            }
        } లేకపోతే {
            కొరకు (పూర్ణాంకం i = 0; bootstrap[i]; ++i) {
                ఒకవేళ (bootstrap[i]->Show_సందేశం_Box && bootstrap[i]->Show_సందేశం_Box(messageboxdata, buttonID)) {
                    ఫలితం = true;
                    ఆపు;
                }
            }
        }
    }

    ఒకవేళ (!ఫలితం) {
        స్థిరరాశి అక్షరం *error = SDL_GetError();

        ఒకవేళ (!*error) {
            SDL_సమితి_Error("No message system available");
        }
    } లేకపోతే {
        SDL_ClearError();
    }

    (శూన్య)SDL_AtomicDecRef(&SDL_messagebox_లెక్క);

    ఒకవేళ (current_కిటికీ) {
        SDL_Raise_కిటికీ(current_కిటికీ);
    }

    ఒకవేళ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_బహుళకం();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    తిరిగి ఫలితం;
}

bool SDL_Show_Simple_సందేశం_Box(SDL_సందేశం_Box_Flags flags, స్థిరరాశి అక్షరం *title, స్థిరరాశి అక్షరం *సందేశం, SDL_కిటికీ *కిటికీ)
{
#ఒకవేళ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_కుడి;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_కుడి = gsp_Has_Gpu_కుడి();
    ఒకవేళ (!has_Gpu_కుడి)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_పాఠ్యం_మాట_WRAP, CFG_LANGUAGE_EN);
    error_పాఠ్యం(&errCnf, సందేశం);
    errorDisp(&errCnf);

    ఒకవేళ (!has_Gpu_కుడి)
        gfxExit();

    తిరిగి true;
#లేకపోతే
    SDL_సందేశం_Box_దత్తాంశం దత్తాంశం;
    SDL_సందేశం_Box_Button_దత్తాంశం button;

    SDL_zero(దత్తాంశం);
    దత్తాంశం.flags = flags;
    దత్తాంశం.title = title;
    దత్తాంశం.సందేశం = సందేశం;
    దత్తాంశం.numbuttons = 1;
    దత్తాంశం.buttons = &button;
    దత్తాంశం.కిటికీ = కిటికీ;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.పాఠ్యం = "OK";

    తిరిగి SDL_Show_సందేశం_Box(&దత్తాంశం, ఖాళీ);
#అయితే_ముగింపు
}

bool SDL_ShouldAllowTopmost(శూన్య)
{
    తిరిగి SDL_GetHintBoolean(SDL_HINT_కిటికీ_ALLOW_TOPMOST, true);
}

bool SDL_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);
    CHECK_కిటికీ_NOT_POPUP(కిటికీ, false);

    ఒకవేళ (_this->Show_కిటికీ_System_Menu) {
        _this->Show_కిటికీ_System_Menu(కిటికీ, x, y);
        తిరిగి true;
    }

    తిరిగి SDL_Unsupported();
}

bool SDL_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, SDL_తగిలింది_Test callback, శూన్య *callback_దత్తాంశం)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->సమితి_కిటికీ_తగిలింది_Test) {
        తిరిగి SDL_Unsupported();
    }

    కిటికీ->తగిలింది_test = callback;
    కిటికీ->తగిలింది_test_దత్తాంశం = callback_దత్తాంశం;

    తిరిగి _this->సమితి_కిటికీ_తగిలింది_Test(కిటికీ, callback != ఖాళీ);
}

bool SDL_సమితి_కిటికీ_Shape(SDL_కిటికీ *కిటికీ, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_TRANSPARENT)) {
        తిరిగి SDL_సమితి_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_కిటికీ_Properties(కిటికీ);
    ఒకవేళ (!props) {
        తిరిగి false;
    }

    ఒకవేళ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ఒకవేళ (!surface) {
            తిరిగి false;
        }
    } లేకపోతే {
        surface = ఖాళీ;
    }

    ఒకవేళ (!SDL_సమితి_Surface_Property(props, SDL_PROP_కిటికీ_SHAPE_సూచిక, surface)) {
        తిరిగి false;
    }

    ఒకవేళ (_this->Update_కిటికీ_Shape) {
        ఒకవేళ (!_this->Update_కిటికీ_Shape(_this, కిటికీ, surface)) {
            తిరిగి false;
        }
    }
    తిరిగి true;
}

/*
 * Functions used by iOS application delegates
 */
శూన్య SDL_OnApplicationWillTerminate(శూన్య)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

శూన్య SDL_On_Application_Did_Receive_జ్ఞాపకం_Warning(శూన్య)
{
    SDL_SendAppEvent(SDL_EVENT_దిగువ_జ్ఞాపకం);
}

శూన్య SDL_OnApplicationWillEnterBackground(శూన్య)
{
    ఒకవేళ (_this) {
        SDL_కిటికీ *కిటికీ;
        కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
        }
        SDL_సమితి_Keyboard_Focus(ఖాళీ);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

శూన్య SDL_OnApplicationDidEnterBackground(శూన్య)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

శూన్య SDL_OnApplicationWillEnterForeground(శూన్య)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

శూన్య SDL_OnApplicationDidEnterForeground(శూన్య)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    ఒకవేళ (_this) {
        SDL_కిటికీ *కిటికీ;
        కొరకు (కిటికీ = _this->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            SDL_సమితి_Keyboard_Focus(కిటికీ);
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
        }
    }
}

#నిర్వచించు NOT_A_VULKAN_కిటికీ "The specified window isn't a Vulkan window"

bool SDL_Vulkan_ఎక్కించు_Library(స్థిరరాశి అక్షరం *మార్గం)
{
    bool ఫలితం;

    ఒకవేళ (!_this) {
        తిరిగి SDL_UninitializedVideo();
    }
    ఒకవేళ (_this->vulkan_config.loader_loaded) {
        ఒకవేళ (మార్గం && SDL_strcmp(మార్గం, _this->vulkan_config.loader_మార్గం) != 0) {
            తిరిగి SDL_సమితి_Error("Vulkan loader library already loaded");
        }
        ఫలితం = true;
    } లేకపోతే {
        ఒకవేళ (!_this->Vulkan_ఎక్కించు_Library) {
            తిరిగి SDL_DllNotSupported("Vulkan");
        }
        ఫలితం = _this->Vulkan_ఎక్కించు_Library(_this, మార్గం);
    }
    ఒకవేళ (ఫలితం) {
        _this->vulkan_config.loader_loaded++;
    }
    తిరిగి ఫలితం;
}

SDL_Function_సూచిక SDL_Vulkan_GetVkGetInstanceProcAddr(శూన్య)
{
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (!_this->vulkan_config.loader_loaded) {
        SDL_సమితి_Error("No Vulkan loader has been loaded");
        తిరిగి ఖాళీ;
    }
    తిరిగి (SDL_Function_సూచిక)_this->vulkan_config.vkGetInstanceProcAddr;
}

శూన్య SDL_Vulkan_UnloadLibrary(శూన్య)
{
    ఒకవేళ (!_this) {
        SDL_UninitializedVideo();
        తిరిగి;
    }
    ఒకవేళ (_this->vulkan_config.loader_loaded > 0) {
        ఒకవేళ (--_this->vulkan_config.loader_loaded > 0) {
            తిరిగి;
        }
        ఒకవేళ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

అక్షరం స్థిరరాశి * స్థిరరాశి *SDL_Vulkan_GetInstanceExtensions(Uint32 *లెక్క)
{
    Uint32 tmpcount = 0;
    ఒకవేళ (!లెక్క) {
        లెక్క = &tmpcount;
    }

    ఒకవేళ (!_this->Vulkan_GetInstanceExtensions) {
        *లెక్క = 0;
        SDL_Unsupported();
        తిరిగి ఖాళీ;
    }

    తిరిగి _this->Vulkan_GetInstanceExtensions(_this, లెక్క);
}

bool SDL_Vulkan_CreateSurface(SDL_కిటికీ *కిటికీ,
                                  VkInstance instance,
                                  స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, false);

    ఒకవేళ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        తిరిగి false;
    }

    CHECK_PARAM(!instance) {
        తిరిగి SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_VULKAN)) {
        // No problem, we can convert to Vulkan
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
            కిటికీ->flags &= ~SDL_కిటికీ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_METAL) {
            కిటికీ->flags &= ~SDL_కిటికీ_METAL;
            // Nothing more to do for Metal.
        }
        ఒకవేళ (SDL_Vulkan_ఎక్కించు_Library(ఖాళీ)) {
            కిటికీ->flags |= SDL_కిటికీ_VULKAN;
        } లేకపోతే {
            తిరిగి SDL_సమితి_Error("failed to load Vulkan library");
        }
    }

    తిరిగి _this->Vulkan_CreateSurface(_this, కిటికీ, instance, allocator, surface);
}

శూన్య SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               స్థిరరాశి నిర్మాణం Vk_కేటాయింపు_Callbacks *allocator)
{
    ఒకవేళ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 వరుస_Family_సూచీ)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        తిరిగి false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        తిరిగి false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        తిరిగి false;
    }

    ఒకవేళ (_this->Vulkan_GetPresentationSupport) {
        తిరిగి _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, వరుస_Family_సూచీ);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    తిరిగి true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_కిటికీ *కిటికీ)
{
    CHECK_కిటికీ_MAGIC(కిటికీ, ఖాళీ);

    ఒకవేళ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_METAL)) {
        // No problem, we can convert to Metal
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
            కిటికీ->flags &= ~SDL_కిటికీ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_VULKAN) {
            కిటికీ->flags &= ~SDL_కిటికీ_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        కిటికీ->flags |= SDL_కిటికీ_METAL;
    }

    తిరిగి _this->Metal_CreateView(_this, కిటికీ);
}

శూన్య SDL_Metal_DestroyView(SDL_MetalView view)
{
    ఒకవేళ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

శూన్య *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ఒకవేళ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            తిరిగి ఖాళీ;
        }
        తిరిగి _this->Metal_GetLayer(_this, view);
    } లేకపోతే {
        SDL_సమితి_Error("Metal is not supported.");
        తిరిగి ఖాళీ;
    }
}

#ఒకవేళ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
స్థిరరాశి అక్షరం *SDL_GetCSSCursorName(SDL_SystemCursor id, స్థిరరాశి అక్షరం **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    ఎంపిక (id) {
    స్థితి SDL_SYSTEM_CURSOR_DEFAULT:
        తిరిగి "default";

    స్థితి SDL_SYSTEM_CURSOR_పాఠ్యం:
        తిరిగి "text";

    స్థితి SDL_SYSTEM_CURSOR_WAIT:
        తిరిగి "wait";

    స్థితి SDL_SYSTEM_CURSOR_CROSSHAIR:
        తిరిగి "crosshair";

    స్థితి SDL_SYSTEM_CURSOR_పురోగతి:
        తిరిగి "progress";

    స్థితి SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ఒకవేళ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        తిరిగి "nwse-resize";

    స్థితి SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ఒకవేళ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        తిరిగి "nesw-resize";

    స్థితి SDL_SYSTEM_CURSOR_EW_RESIZE:
        ఒకవేళ (fallback_name) {
            *fallback_name = "col-resize";
        }
        తిరిగి "ew-resize";

    స్థితి SDL_SYSTEM_CURSOR_NS_RESIZE:
        ఒకవేళ (fallback_name) {
            *fallback_name = "row-resize";
        }
        తిరిగి "ns-resize";

    స్థితి SDL_SYSTEM_CURSOR_MOVE:
        ఒకవేళ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        తిరిగి "move";

    స్థితి SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        తిరిగి "not-allowed";

    స్థితి SDL_SYSTEM_CURSOR_సూచిక:
        తిరిగి "pointer";

    స్థితి SDL_SYSTEM_CURSOR_NW_RESIZE:
        తిరిగి "nw-resize";

    స్థితి SDL_SYSTEM_CURSOR_N_RESIZE:
        తిరిగి "n-resize";

    స్థితి SDL_SYSTEM_CURSOR_NE_RESIZE:
        తిరిగి "ne-resize";

    స్థితి SDL_SYSTEM_CURSOR_E_RESIZE:
        తిరిగి "e-resize";

    స్థితి SDL_SYSTEM_CURSOR_SE_RESIZE:
        తిరిగి "se-resize";

    స్థితి SDL_SYSTEM_CURSOR_S_RESIZE:
        తిరిగి "s-resize";

    స్థితి SDL_SYSTEM_CURSOR_SW_RESIZE:
        తిరిగి "sw-resize";

    స్థితి SDL_SYSTEM_CURSOR_W_RESIZE:
        తిరిగి "w-resize";

    స్థితి SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        తిరిగి "context-menu";

    స్థితి SDL_SYSTEM_CURSOR_HELP:
        తిరిగి "help";

    స్థితి SDL_SYSTEM_CURSOR_CELL:
        తిరిగి "cell";

    స్థితి SDL_SYSTEM_CURSOR_VERTICAL_పాఠ్యం:
        తిరిగి "vertical-text";

    స్థితి SDL_SYSTEM_CURSOR_ALIAS:
        తిరిగి "alias";

    స్థితి SDL_SYSTEM_CURSOR_COPY:
        తిరిగి "copy";

    స్థితి SDL_SYSTEM_CURSOR_NO_DROP:
        తిరిగి "no-drop";

    స్థితి SDL_SYSTEM_CURSOR_GRAB:
        తిరిగి "grab";

    స్థితి SDL_SYSTEM_CURSOR_GRABBING:
        తిరిగి "grabbing";

    స్థితి SDL_SYSTEM_CURSOR_నిలువు_RESIZE:
        తిరిగి "col-resize";

    స్థితి SDL_SYSTEM_CURSOR_అడ్డువరుస_RESIZE:
        తిరిగి "row-resize";

    స్థితి SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ఒకవేళ (fallback_name) {
            *fallback_name = "move";
        }
        తిరిగి "all-scroll";

    స్థితి SDL_SYSTEM_CURSOR_ZOOM_లోపల:
        తిరిగి "zoom-in";

    స్థితి SDL_SYSTEM_CURSOR_ZOOM_బహిర్గతం:
        తిరిగి "zoom-out";

    అప్రమేయ:
        తిరిగి "default";
    }
}
#అయితే_ముగింపు

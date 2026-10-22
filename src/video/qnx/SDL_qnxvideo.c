/*
  Simple DirectMedia Layer
  Copyright (C) 2026 BlackBerry Limited

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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_qnx.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>

ਸਥਿਰ screen_context_t context;
ਸਥਿਰ screen_event_t   event;
ਸਥਿਰ bool video_initialized = false;

screen_context_t * getContext()
{
    ਵਾਪਸ &context;
}

screen_event_t * getEvent()
{
    ਵਾਪਸ &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ਸਥਿਰ bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_Display_ਅੰਕੜੇ      *display_ਅੰਕੜੇ;
    SDL_Display_ਬਹੁਲਕ      display_ਬਹੁਲਕ_2;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ  *display_ਬਹੁਲਕ_ਅੰਕੜੇ;

    ਪੂਰਨ ਮਾਪ[2];
    ਪੂਰਨ ਸੂਚਕਾਂਕ;
    ਪੂਰਨ display_ਗਿਣਤੀ;
    ਪੂਰਨ ਸਰਗਰਮ;

    screen_display_t *screen_display;

    ਜੇ (video_initialized) {
        ਵਾਪਸ true;
    }

    ਜੇ (screen_create_context(&context, 0) < 0) {
        ਵਾਪਸ false;
    }

    ਜੇ (screen_create_event(&event) < 0) {
        ਵਾਪਸ false;
    }

    /* start with no displays and increment as attached displays are found */
    ਜੇ (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_ਗਿਣਤੀ, &display_ਗਿਣਤੀ) < 0) {
        ਵਾਪਸ false;
    }

    screen_display = SDL_calloc(display_ਗਿਣਤੀ, ਆਕਾਰ(screen_display_t));
    ਜੇ (screen_display == ਨਿਰਾ) {
        ਵਾਪਸ false;
    }

    ਜੇ (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (ਖਾਲੀ **)screen_display) < 0) {
        ਵਾਪਸ false;
    }

    /* create SDL displays based on display info from the screen API */
    ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < display_ਗਿਣਤੀ; ਸੂਚਕਾਂਕ++) {
        ਸਰਗਰਮ = 0;
        ਜੇ (screen_get_display_property_iv(screen_display[ਸੂਚਕਾਂਕ], SCREEN_PROPERTY_ATTACHED, &ਸਰਗਰਮ) < 0) {
            SDL_free(screen_display);
            ਵਾਪਸ false;
        }

        ਜੇ (ਸਰਗਰਮ) {
            display_ਅੰਕੜੇ = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ));
            ਜੇ (display_ਅੰਕੜੇ == ਨਿਰਾ) {
                SDL_free(screen_display);
                ਵਾਪਸ false;
            }
            SDL_zerop(display_ਅੰਕੜੇ);

            ਜੇ (screen_get_display_property_iv(screen_display[ਸੂਚਕਾਂਕ], SCREEN_PROPERTY_ਮਾਪ, ਮਾਪ) < 0) {
                SDL_free(screen_display);
                SDL_free(display_ਅੰਕੜੇ);
                ਵਾਪਸ false;
            }

            display_ਬਹੁਲਕ_ਅੰਕੜੇ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
            ਜੇ (display_ਬਹੁਲਕ_ਅੰਕੜੇ == ਨਿਰਾ) {
                SDL_free(screen_display);
                SDL_free(display_ਅੰਕੜੇ);
                ਵਾਪਸ false;
            }
            SDL_zerop(display_ਬਹੁਲਕ_ਅੰਕੜੇ);

            SDL_zero(display);
            SDL_zero(display_ਬਹੁਲਕ_2);

            display_ਅੰਕੜੇ->screen_display = screen_display[ਸੂਚਕਾਂਕ];
            display.ਅੰਦਰੂਨੀ = (ਖਾਲੀ *)display_ਅੰਕੜੇ;

            display_ਬਹੁਲਕ_2.w = ਮਾਪ[0];
            display_ਬਹੁਲਕ_2.h = ਮਾਪ[1];
            display_ਬਹੁਲਕ_2.refresh_ਦਰ = 60;
            display_ਬਹੁਲਕ_2.pixel_density = 1.0;
            display_ਬਹੁਲਕ_2.ਅੰਦਰੂਨੀ = display_ਬਹੁਲਕ_ਅੰਕੜੇ;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_ਬਹੁਲਕ_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_display_ਬਹੁਲਕ.ਸੂਚਕਾਂਕ = SCREEN_DISPLAY_ਬਹੁਲਕ_PREFERRED_ਸੂਚਕਾਂਕ;

            // Added to current_mode when the display is added.
            display.desktop_ਬਹੁਲਕ = display_ਬਹੁਲਕ_2;

            ਜੇ (!SDL_ਜੋੜੋ_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_ਬਹੁਲਕ_ਅੰਕੜੇ);
                SDL_free(display_ਅੰਕੜੇ);
                ਵਾਪਸ false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_ਜੋੜੋ_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ਨਿਰਾ);
    SDL_ਜੋੜੋ_Mouse(SDL_DEFAULT_MOUSE_ID, ਨਿਰਾ);

    video_initialized = true;

    SDL_free(screen_display);

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ QNX_VideoQuit(SDL_VideoDevice *_this)
{
    ਜੇ (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ਸਥਿਰ bool QNX_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ       *impl;
    SDL_VideoDisplay     *display = ਨਿਰਾ;
    SDL_Display_ਅੰਕੜੇ      *display_ਅੰਕੜੇ = ਨਿਰਾ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ  *display_ਬਹੁਲਕ_ਅੰਕੜੇ = ਨਿਰਾ;

    ਪੂਰਨ             ਮਾਪ[2];
    ਪੂਰਨ             position[2];
    ਪੂਰਨ             numbufs;
    ਪੂਰਨ             format;
    ਪੂਰਨ             usage;
    ਪੂਰਨ             has_focus_i;

    impl = SDL_calloc(1, ਆਕਾਰ(*impl));
    ਜੇ (!impl) {
        ਵਾਪਸ false;
    }
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = impl;

    // Create a native window.
    ਜੇ (screen_create_ਖਿੜਕੀ(&impl->ਖਿੜਕੀ, context) < 0) {
        ਜਾਓ fail;
    }

    // Set the native window's size to match the SDL window.
    ਮਾਪ[0] = ਖਿੜਕੀ->w;
    ਮਾਪ[1] = ਖਿੜਕੀ->h;
    position[0] = ਖਿੜਕੀ->x;
    position[1] = ਖਿੜਕੀ->y;

    ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_ਮਾਪ, ਮਾਪ) < 0) {
        ਜਾਓ fail;
    }

    ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_ਸਰੋਤ_ਮਾਪ, ਮਾਪ) < 0) {
        ਜਾਓ fail;
    }

    ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_POSITION, position) < 0) {
        ਜਾਓ fail;
    }

    display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    SDL_assert(display != ਨਿਰਾ);
    SDL_assert(display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ != ਨਿਰਾ);
    display_ਬਹੁਲਕ_ਅੰਕੜੇ = display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ;

    // Create window buffer(s).
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            ਜਾਓ fail;
        }
    } ਨਹੀਂਤਾਂ {
        numbufs = 1;
    }

    // Create buffer(s).
    ਜੇ (screen_create_ਖਿੜਕੀ_buffers(impl->ਖਿੜਕੀ, numbufs>0?numbufs:1) < 0) {
        ਜਾਓ fail;
    }

    // Initialize EGL surface.
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)impl->ਖਿੜਕੀ);
        ਜੇ (impl->egl_surface == EGL_NO_SURFACE) {
            ਜਾਓ fail;
        }
        SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_QNX_SURFACE_ਸੂਚਕ, impl->egl_surface);
    }

    ਜੇ (screen_get_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_ਬਹੁਲਕ.format = screen_ਮੰਜ਼ਿਲ_Pixel_Format(format);
    display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_format = format;

    display_ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_ਅੰਕੜੇ != ਨਿਰਾ);

    // Get initial focus state. Fallback to true.
    ਜੇ(screen_get_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } ਨਹੀਂਤਾਂ {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_QNX_ਖਿੜਕੀ_ਸੂਚਕ, impl->ਖਿੜਕੀ);

    ਵਾਪਸ true;

fail:
    ਜੇ (impl->ਖਿੜਕੀ) {
        screen_destroy_ਖਿੜਕੀ(impl->ਖਿੜਕੀ);
    }
    ਜੇ (display_ਅੰਕੜੇ) {
        SDL_free(display_ਅੰਕੜੇ);
        display->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }

    SDL_free(impl);
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    ਵਾਪਸ false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ਸਥਿਰ bool QNX_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, SDL_PixelFormat * format,
                        ਖਾਲੀ ** pixels, ਪੂਰਨ *pitch)
{
    ਪੂਰਨ              ਬਫਰ_ਗਿਣਤੀ_2;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    screen_ਬਫਰ_t  *ਬਫਰ_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);

    ਜੇ (screen_get_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_ਬਫਰ_ਗਿਣਤੀ, &ਬਫਰ_ਗਿਣਤੀ_2) < 0) {
        ਵਾਪਸ false;
    }
    ਬਫਰ_2 = SDL_calloc(ਬਫਰ_ਗਿਣਤੀ_2, ਆਕਾਰ(screen_ਬਫਰ_t));

    // Get a pointer to the buffer's memory.
    ਜੇ (screen_get_ਖਿੜਕੀ_property_pv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_BUFFERS, (ਖਾਲੀ **)ਬਫਰ_2) < 0) {
        ਵਾਪਸ false;
    }

    ਜੇ (screen_get_ਬਫਰ_property_pv(*ਬਫਰ_2, SCREEN_PROPERTY_ਸੂਚਕ, pixels) < 0) {
        ਵਾਪਸ false;
    }

    // Set format and pitch.
    ਜੇ (screen_get_ਬਫਰ_property_iv(*ਬਫਰ_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ਵਾਪਸ false;
    }

    *format = display->desktop_ਬਹੁਲਕ.format;
    ਵਾਪਸ true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ਸਥਿਰ bool QNX_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects,
                        ਪੂਰਨ numrects)
{
    ਪੂਰਨ ਬਫਰ_ਗਿਣਤੀ_2, *rects_int;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    screen_ਬਫਰ_t *ਬਫਰ_2;

    ਜੇ (screen_get_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_ਬਫਰ_ਗਿਣਤੀ, &ਬਫਰ_ਗਿਣਤੀ_2) < 0) {
        ਵਾਪਸ false;
    }
    ਬਫਰ_2 = SDL_calloc(ਬਫਰ_ਗਿਣਤੀ_2, ਆਕਾਰ(screen_ਬਫਰ_t));

    ਜੇ (screen_get_ਖਿੜਕੀ_property_pv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_BUFFERS, (ਖਾਲੀ **)ਬਫਰ_2) < 0) {
        ਵਾਪਸ false;
    }

    ਜੇ(numrects>0){
        rects_int = SDL_calloc(4*numrects, ਆਕਾਰ(ਪੂਰਨ));

        ਲਈ(ਪੂਰਨ i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        ਜੇ(screen_post_ਖਿੜਕੀ(impl->ਖਿੜਕੀ, ਬਫਰ_2[0], numrects, rects_int, 0)) {
            ਵਾਪਸ false;
        }
        ਜੇ(screen_flush_context(context, 0)) {
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ SDL_Fullscreen_ਨਤੀਜਾ QNX_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ ਮਾਪ[2] = { 0, 0 };
    ਪੂਰਨ position[2] = { 0, 0 };

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && !fullscreen) {
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    }

    ਜੇ (fullscreen) {
        SDL_Rect bounds;

        ਜੇ (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ਵਾਪਸ SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        ਮਾਪ[0] = bounds.w;
        ਮਾਪ[1] = bounds.h;
    } ਨਹੀਂਤਾਂ {
        position[0] = ਖਿੜਕੀ->x;
        position[1] = ਖਿੜਕੀ->y;
        ਮਾਪ[0] = ਖਿੜਕੀ->w;
        ਮਾਪ[1] = ਖਿੜਕੀ->h;
    }

    ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SCREEN_PROPERTY_ਮਾਪ, ਮਾਪ) < 0) {
        ਵਾਪਸ SDL_FULLSCREEN_FAILED;
    }

    ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SCREEN_PROPERTY_ਸਰੋਤ_ਮਾਪ, ਮਾਪ) < 0) {
        ਵਾਪਸ SDL_FULLSCREEN_FAILED;
    }

    ਜੇ (screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SCREEN_PROPERTY_POSITION, position) < 0) {
        ਵਾਪਸ SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, fullscreen ? SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN : SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);

    ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
}

ਸਥਿਰ SDL_DisplayID QNX_Get_Display_For_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ  *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ;

    screen_display_t screen_display;

    ਜੇ (impl == ਨਿਰਾ) {
        ਵਾਪਸ 0;
    }

    ਜੇ (screen_get_ਖਿੜਕੀ_property_pv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_DISPLAY, (ਖਾਲੀ **)&screen_display) < 0) {
        ਵਾਪਸ 0;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; i++) {
        display_ਅੰਕੜੇ = _this->displays[i]->ਅੰਦਰੂਨੀ;
        ਜੇ (display_ਅੰਕੜੇ && (display_ਅੰਕੜੇ->screen_display == screen_display)) {
            ਵਾਪਸ _this->displays[i]->id;
        }
    }

    ਵਾਪਸ 0;
}

/**
 * Runs the main event loop.
 */
ਸਥਿਰ ਖਾਲੀ QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_ਖਿੜਕੀ      *ਖਿੜਕੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl;
    ਪੂਰਨ             type;
    ਪੂਰਨ             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        ਜੇ (screen_get_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            ਜਾਰੀ;
        }
        has_focus = (bool)has_focus_i;

        ਜੇ (impl->has_focus != has_focus) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, (has_focus ? SDL_EVENT_ਖਿੜਕੀ_FOCUS_GAINED : SDL_EVENT_ਖਿੜਕੀ_FOCUS_ਗੁਆਚਾ), 0, 0);
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, (has_focus ? SDL_EVENT_ਖਿੜਕੀ_MOUSE_ENTER : SDL_EVENT_ਖਿੜਕੀ_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
            SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
        }
    }

    ਲਈ (;;) {
        ਜੇ (screen_get_event(context, event, 0) < 0) {
            ਰੋਕੋ;
        }

        ਜੇ (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            ਰੋਕੋ;
        }

        ਜੇ (type == SCREEN_EVENT_NONE) {
            ਰੋਕੋ;
        }

        ਚੋਣ (type) {
        ਹਾਲਤ SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            ਰੋਕੋ;

        ਹਾਲਤ SCREEN_EVENT_ਸੂਚਕ:
            handle_ਸੂਚਕ_Event(event);
            ਰੋਕੋ;

        ਮੂਲ:
            ਰੋਕੋ;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ਸਥਿਰ ਖਾਲੀ QNX_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ             ਮਾਪ[2];

    ਮਾਪ[0] = ਖਿੜਕੀ->pending.w;
    ਮਾਪ[1] = ਖਿੜਕੀ->pending.h;

    ਜੇ (!(ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_MAXIMIZED))) {
        ਜੇ (screen_destroy_ਖਿੜਕੀ_buffers(impl->ਖਿੜਕੀ) < 0) {
            ਵਾਪਸ;
        }
        impl->resize = true;

        screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_ਮਾਪ, ਮਾਪ);
        screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_ਸਰੋਤ_ਮਾਪ, ਮਾਪ);

        screen_create_ਖਿੜਕੀ_buffers(impl->ਖਿੜਕੀ, (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) ? 2 : 1);
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ਸਥਿਰ ਖਾਲੀ QNX_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ ਪੂਰਨ       visible = 1;

    screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ਸਥਿਰ ਖਾਲੀ QNX_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ ਪੂਰਨ       visible = 0;

    screen_ਸੈੱਟ_ਖਿੜਕੀ_property_iv(impl->ਖਿੜਕੀ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ਸਥਿਰ ਖਾਲੀ QNX_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ   *impl = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_ਖਿੜਕੀ(impl->ਖਿੜਕੀ);
        ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ਸਥਿਰ ਖਾਲੀ QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ਸਥਿਰ SDL_VideoDevice *createDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    device->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_ਖਿੜਕੀ;
    device->Create_ਖਿੜਕੀ_Framebuffer = QNX_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = QNX_Update_ਖਿੜਕੀ_Framebuffer;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = QNX_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = QNX_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->Show_ਖਿੜਕੀ = QNX_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = QNX_Hide_ਖਿੜਕੀ;
    device->Get_Display_For_ਖਿੜਕੀ = QNX_Get_Display_For_ਖਿੜਕੀ;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#ਜੇ 0
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = QNX_ਸੈੱਟ_Display_ਬਹੁਲਕ;
#ਜੇ_ਅੰਤ
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_ਖਿੜਕੀ = QNX_Destroy_ਖਿੜਕੀ;

    device->GL_ਲੱਦੋ_Library = QNX_GLES_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = QNX_GLES_Get_Proc_ਪਤਾ;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = QNX_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = QNX_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = QNX_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_MakeCurrent = QNX_GLES_MakeCurrent;
    device->GL_DestroyContext = QNX_GLES_DeleteContext;
    device->GL_UnloadLibrary = QNX_GLES_UnloadLibrary;

    device->ਮੁਕਤ = QNX_DeleteDevice;

    ਵਾਪਸ device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ਨਿਰਾ, // no ShowMessageBox implementation
    false
};

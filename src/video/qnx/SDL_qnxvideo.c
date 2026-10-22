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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_qnx.h"

#ಅನ್ತರ್ಭಾವ <errno.h>

ಸ್ಥಿರ screen_context_t context;
ಸ್ಥಿರ screen_event_t   event;
ಸ್ಥಿರ bool video_initialized = false;

screen_context_t * getContext()
{
    ಹಿಂತಿರುಗಿ &context;
}

screen_event_t * getEvent()
{
    ಹಿಂತಿರುಗಿ &event;
}

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 */
ಸ್ಥಿರ bool QNX_VideoInit(SDL_VideoDevice *_this)
{
    SDL_VideoDisplay     display;
    SDL_Display_ದತ್ತಾಂಶ      *display_ದತ್ತಾಂಶ;
    SDL_Display_ಬಹುಲಕ      display_ಬಹುಲಕ_2;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ  *display_ಬಹುಲಕ_ದತ್ತಾಂಶ;

    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2[2];
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;
    ಪೂರ್ಣಾಂಕ display_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಂಕ ಸಕ್ರಿಯ;

    screen_display_t *screen_display;

    ಆದರೆ (video_initialized) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (screen_create_context(&context, 0) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (screen_create_event(&event) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    /* start with no displays and increment as attached displays are found */
    ಆದರೆ (screen_get_context_property_iv(context, SCREEN_PROPERTY_DISPLAY_ಎಣಿಕೆ, &display_ಎಣಿಕೆ) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    screen_display = SDL_calloc(display_ಎಣಿಕೆ, ಗಾತ್ರ(screen_display_t));
    ಆದರೆ (screen_display == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (screen_get_context_property_pv(context, SCREEN_PROPERTY_DISPLAYS, (ಶೂನ್ಯ **)screen_display) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    /* create SDL displays based on display info from the screen API */
    ಗಾಗಿ (ಸೂಚ್ಯಂಕ = 0; ಸೂಚ್ಯಂಕ < display_ಎಣಿಕೆ; ಸೂಚ್ಯಂಕ++) {
        ಸಕ್ರಿಯ = 0;
        ಆದರೆ (screen_get_display_property_iv(screen_display[ಸೂಚ್ಯಂಕ], SCREEN_PROPERTY_ATTACHED, &ಸಕ್ರಿಯ) < 0) {
            SDL_free(screen_display);
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (ಸಕ್ರಿಯ) {
            display_ದತ್ತಾಂಶ = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ));
            ಆದರೆ (display_ದತ್ತಾಂಶ == ಖಾಲಿ) {
                SDL_free(screen_display);
                ಹಿಂತಿರುಗಿ false;
            }
            SDL_zerop(display_ದತ್ತಾಂಶ);

            ಆದರೆ (screen_get_display_property_iv(screen_display[ಸೂಚ್ಯಂಕ], SCREEN_PROPERTY_ಗಾತ್ರ, ಗಾತ್ರ_2) < 0) {
                SDL_free(screen_display);
                SDL_free(display_ದತ್ತಾಂಶ);
                ಹಿಂತಿರುಗಿ false;
            }

            display_ಬಹುಲಕ_ದತ್ತಾಂಶ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
            ಆದರೆ (display_ಬಹುಲಕ_ದತ್ತಾಂಶ == ಖಾಲಿ) {
                SDL_free(screen_display);
                SDL_free(display_ದತ್ತಾಂಶ);
                ಹಿಂತಿರುಗಿ false;
            }
            SDL_zerop(display_ಬಹುಲಕ_ದತ್ತಾಂಶ);

            SDL_zero(display);
            SDL_zero(display_ಬಹುಲಕ_2);

            display_ದತ್ತಾಂಶ->screen_display = screen_display[ಸೂಚ್ಯಂಕ];
            display.ಆಂತರಿಕ = (ಶೂನ್ಯ *)display_ದತ್ತಾಂಶ;

            display_ಬಹುಲಕ_2.w = ಗಾತ್ರ_2[0];
            display_ಬಹುಲಕ_2.h = ಗಾತ್ರ_2[1];
            display_ಬಹುಲಕ_2.refresh_ದರ = 60;
            display_ಬಹುಲಕ_2.pixel_density = 1.0;
            display_ಬಹುಲಕ_2.ಆಂತರಿಕ = display_ಬಹುಲಕ_ದತ್ತಾಂಶ;
            // This is assigned later when the window is created. For now, use a
            // safe guess.
            display_ಬಹುಲಕ_2.format = SDL_PIXELFORMAT_RGBX8888;
            display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_format = SCREEN_FORMAT_RGBX8888;
            // Be able to revert to the default display mode despite not having
            // the actual object to refer to.
            display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_display_ಬಹುಲಕ.ಸೂಚ್ಯಂಕ = SCREEN_DISPLAY_ಬಹುಲಕ_PREFERRED_ಸೂಚ್ಯಂಕ;

            // Added to current_mode when the display is added.
            display.desktop_ಬಹುಲಕ = display_ಬಹುಲಕ_2;

            ಆದರೆ (!SDL_ಕೂಡಿಸು_Video_Display(&display, false)) {
                SDL_free(screen_display);
                SDL_free(display_ಬಹುಲಕ_ದತ್ತಾಂಶ);
                SDL_free(display_ದತ್ತಾಂಶ);
                ಹಿಂತಿರುಗಿ false;
            }
        }
    }

    initMouse(_this);

    // Assume we have a mouse and keyboard
    SDL_ಕೂಡಿಸು_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ಖಾಲಿ);
    SDL_ಕೂಡಿಸು_Mouse(SDL_DEFAULT_MOUSE_ID, ಖಾಲಿ);

    video_initialized = true;

    SDL_free(screen_display);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ QNX_VideoQuit(SDL_VideoDevice *_this)
{
    ಆದರೆ (video_initialized) {
        screen_destroy_event(event);
        screen_destroy_context(context);
        video_initialized = false;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 */
ಸ್ಥಿರ bool QNX_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ       *impl;
    SDL_VideoDisplay     *display = ಖಾಲಿ;
    SDL_Display_ದತ್ತಾಂಶ      *display_ದತ್ತಾಂಶ = ಖಾಲಿ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ  *display_ಬಹುಲಕ_ದತ್ತಾಂಶ = ಖಾಲಿ;

    ಪೂರ್ಣಾಂಕ             ಗಾತ್ರ_2[2];
    ಪೂರ್ಣಾಂಕ             position[2];
    ಪೂರ್ಣಾಂಕ             numbufs;
    ಪೂರ್ಣಾಂಕ             format;
    ಪೂರ್ಣಾಂಕ             usage;
    ಪೂರ್ಣಾಂಕ             has_focus_i;

    impl = SDL_calloc(1, ಗಾತ್ರ(*impl));
    ಆದರೆ (!impl) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಕಿಟಕಿ->ಆಂತರಿಕ = impl;

    // Create a native window.
    ಆದರೆ (screen_create_ಕಿಟಕಿ(&impl->ಕಿಟಕಿ, context) < 0) {
        ಹೋಗು fail;
    }

    // Set the native window's size to match the SDL window.
    ಗಾತ್ರ_2[0] = ಕಿಟಕಿ->w;
    ಗಾತ್ರ_2[1] = ಕಿಟಕಿ->h;
    position[0] = ಕಿಟಕಿ->x;
    position[1] = ಕಿಟಕಿ->y;

    ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_ಗಾತ್ರ, ಗಾತ್ರ_2) < 0) {
        ಹೋಗು fail;
    }

    ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_ಮೂಲ_ಗಾತ್ರ, ಗಾತ್ರ_2) < 0) {
        ಹೋಗು fail;
    }

    ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_POSITION, position) < 0) {
        ಹೋಗು fail;
    }

    display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    SDL_assert(display != ಖಾಲಿ);
    SDL_assert(display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ != ಖಾಲಿ);
    display_ಬಹುಲಕ_ದತ್ತಾಂಶ = display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ;

    // Create window buffer(s).
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        numbufs = 2;

        usage = SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_OPENGL_ES3;
        ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_USAGE, &usage) < 0) {
            ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        numbufs = 1;
    }

    // Create buffer(s).
    ಆದರೆ (screen_create_ಕಿಟಕಿ_buffers(impl->ಕಿಟಕಿ, numbufs>0?numbufs:1) < 0) {
        ಹೋಗು fail;
    }

    // Initialize EGL surface.
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        // The SDL_EGL_CreateSurface() function chooses the EGL config and
        // assigns the window the corresponding format.
        impl->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)impl->ಕಿಟಕಿ);
        ಆದರೆ (impl->egl_surface == EGL_NO_SURFACE) {
            ಹೋಗು fail;
        }
        SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_QNX_SURFACE_ಸೂಚಕ, impl->egl_surface);
    }

    ಆದರೆ (screen_get_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_FORMAT, &format) < 0) {
        format = display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_format;
    }

    // We now know what the pixel format is, so we need to provide it to the
    // right SDL APIs.
    display->desktop_ಬಹುಲಕ.format = screen_ಗಮ್ಯ_Pixel_Format(format);
    display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_format = format;

    display_ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    // Initialized in QNX_VideoInit()
    SDL_assert(display_ದತ್ತಾಂಶ != ಖಾಲಿ);

    // Get initial focus state. Fallback to true.
    ಆದರೆ(screen_get_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
        impl->has_focus = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        impl->has_focus = (bool)has_focus_i;
    }

    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_QNX_ಕಿಟಕಿ_ಸೂಚಕ, impl->ಕಿಟಕಿ);

    ಹಿಂತಿರುಗಿ true;

fail:
    ಆದರೆ (impl->ಕಿಟಕಿ) {
        screen_destroy_ಕಿಟಕಿ(impl->ಕಿಟಕಿ);
    }
    ಆದರೆ (display_ದತ್ತಾಂಶ) {
        SDL_free(display_ದತ್ತಾಂಶ);
        display->ಆಂತರಿಕ = ಖಾಲಿ;
    }

    SDL_free(impl);
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ false;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in QNX_CreateWindow().
 */
ಸ್ಥಿರ bool QNX_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, SDL_PixelFormat * format,
                        ಶೂನ್ಯ ** pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    ಪೂರ್ಣಾಂಕ              ಬಫರ್_ಎಣಿಕೆ_2;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    screen_ಬಫರ್_t  *ಬಫರ್_2;
    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);

    ಆದರೆ (screen_get_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_ಬಫರ್_ಎಣಿಕೆ, &ಬಫರ್_ಎಣಿಕೆ_2) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಬಫರ್_2 = SDL_calloc(ಬಫರ್_ಎಣಿಕೆ_2, ಗಾತ್ರ(screen_ಬಫರ್_t));

    // Get a pointer to the buffer's memory.
    ಆದರೆ (screen_get_ಕಿಟಕಿ_property_pv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_BUFFERS, (ಶೂನ್ಯ **)ಬಫರ್_2) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (screen_get_ಬಫರ್_property_pv(*ಬಫರ್_2, SCREEN_PROPERTY_ಸೂಚಕ, pixels) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Set format and pitch.
    ಆದರೆ (screen_get_ಬಫರ್_property_iv(*ಬಫರ್_2, SCREEN_PROPERTY_STRIDE, pitch) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    *format = display->desktop_ಬಹುಲಕ.format;
    ಹಿಂತಿರುಗಿ true;
}

/**
 * Informs the window manager that the window needs to be updated.
 */
ಸ್ಥಿರ bool QNX_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects,
                        ಪೂರ್ಣಾಂಕ numrects)
{
    ಪೂರ್ಣಾಂಕ ಬಫರ್_ಎಣಿಕೆ_2, *rects_int;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    screen_ಬಫರ್_t *ಬಫರ್_2;

    ಆದರೆ (screen_get_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_ಬಫರ್_ಎಣಿಕೆ, &ಬಫರ್_ಎಣಿಕೆ_2) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಬಫರ್_2 = SDL_calloc(ಬಫರ್_ಎಣಿಕೆ_2, ಗಾತ್ರ(screen_ಬಫರ್_t));

    ಆದರೆ (screen_get_ಕಿಟಕಿ_property_pv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_BUFFERS, (ಶೂನ್ಯ **)ಬಫರ್_2) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ(numrects>0){
        rects_int = SDL_calloc(4*numrects, ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ));

        ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < numrects; i++){
            rects_int[4*i]   = rects[i].x;
            rects_int[4*i+1] = rects[i].y;
            rects_int[4*i+2] = rects[i].w;
            rects_int[4*i+3] = rects[i].h;
        }

        ಆದರೆ(screen_post_ಕಿಟಕಿ(impl->ಕಿಟಕಿ, ಬಫರ್_2[0], numrects, rects_int, 0)) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ(screen_flush_context(context, 0)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ SDL_Fullscreen_ಫಲಿತಾಂಶ QNX_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2 = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2[2] = { 0, 0 };
    ಪೂರ್ಣಾಂಕ position[2] = { 0, 0 };

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && !fullscreen) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    }

    ಆದರೆ (fullscreen) {
        SDL_Rect bounds;

        ಆದರೆ (!QNX_GetDisplayBounds(_this, display, &bounds)) {
            ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
        }
        position[0] = bounds.x;
        position[1] = bounds.y;
        ಗಾತ್ರ_2[0] = bounds.w;
        ಗಾತ್ರ_2[1] = bounds.h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        position[0] = ಕಿಟಕಿ->x;
        position[1] = ಕಿಟಕಿ->y;
        ಗಾತ್ರ_2[0] = ಕಿಟಕಿ->w;
        ಗಾತ್ರ_2[1] = ಕಿಟಕಿ->h;
    }

    ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SCREEN_PROPERTY_ಗಾತ್ರ, ಗಾತ್ರ_2) < 0) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
    }

    ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SCREEN_PROPERTY_ಮೂಲ_ಗಾತ್ರ, ಗಾತ್ರ_2) < 0) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
    }

    ಆದರೆ (screen_ಗಣ_ಕಿಟಕಿ_property_iv(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕಿಟಕಿ, SCREEN_PROPERTY_POSITION, position) < 0) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
    }

    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, fullscreen ? SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN : SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);

    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
}

ಸ್ಥಿರ SDL_DisplayID QNX_Get_Display_For_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // We need this, otherwise SDL will fallback to the primary display, meaning
    // any data we store about the display will be inconveniently overwritten.
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ  *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ;

    screen_display_t screen_display;

    ಆದರೆ (impl == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (screen_get_ಕಿಟಕಿ_property_pv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_DISPLAY, (ಶೂನ್ಯ **)&screen_display) < 0) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; i++) {
        display_ದತ್ತಾಂಶ = _this->displays[i]->ಆಂತರಿಕ;
        ಆದರೆ (display_ದತ್ತಾಂಶ && (display_ದತ್ತಾಂಶ->screen_display == screen_display)) {
            ಹಿಂತಿರುಗಿ _this->displays[i]->id;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

/**
 * Runs the main event loop.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_PumpEvents(SDL_VideoDevice *_this)
{
    SDL_ಕಿಟಕಿ      *ಕಿಟಕಿ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl;
    ಪೂರ್ಣಾಂಕ             type;
    ಪೂರ್ಣಾಂಕ             has_focus_i;
    bool            has_focus;

    // Let apps know the state of focus.
    ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
        ಆದರೆ (screen_get_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_FOCUS, &has_focus_i) < 0){
            ಮುಂದುವರಿ;
        }
        has_focus = (bool)has_focus_i;

        ಆದರೆ (impl->has_focus != has_focus) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, (has_focus ? SDL_EVENT_ಕಿಟಕಿ_FOCUS_GAINED : SDL_EVENT_ಕಿಟಕಿ_FOCUS_ಕಳೆದುಹೋದ), 0, 0);
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, (has_focus ? SDL_EVENT_ಕಿಟಕಿ_MOUSE_ENTER : SDL_EVENT_ಕಿಟಕಿ_MOUSE_LEAVE), 0, 0);
            // Update the SDL mouse to track the window it's focused on.
            SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
            SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
        }
    }

    ಗಾಗಿ (;;) {
        ಆದರೆ (screen_get_event(context, event, 0) < 0) {
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type)
            < 0) {
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (type == SCREEN_EVENT_NONE) {
            ನಿಲ್ಲಿಸು;
        }

        ಆಯ್ಕೆ (type) {
        ಸ್ಥಿತಿ SCREEN_EVENT_KEYBOARD:
            handleKeyboardEvent(event);
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ SCREEN_EVENT_ಸೂಚಕ:
            handle_ಸೂಚಕ_Event(event);
            ನಿಲ್ಲಿಸು;

        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ             ಗಾತ್ರ_2[2];

    ಗಾತ್ರ_2[0] = ಕಿಟಕಿ->pending.w;
    ಗಾತ್ರ_2[1] = ಕಿಟಕಿ->pending.h;

    ಆದರೆ (!(ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_MAXIMIZED))) {
        ಆದರೆ (screen_destroy_ಕಿಟಕಿ_buffers(impl->ಕಿಟಕಿ) < 0) {
            ಹಿಂತಿರುಗಿ;
        }
        impl->resize = true;

        screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_ಗಾತ್ರ, ಗಾತ್ರ_2);
        screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_ಮೂಲ_ಗಾತ್ರ, ಗಾತ್ರ_2);

        screen_create_ಕಿಟಕಿ_buffers(impl->ಕಿಟಕಿ, (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) ? 2 : 1);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = false;
    }
}

/**
 * Makes the native window associated with the given SDL window visible.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ       visible = 1;

    screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Makes the native window associated with the given SDL window invisible.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ       visible = 0;

    screen_ಗಣ_ಕಿಟಕಿ_property_iv(impl->ಕಿಟಕಿ, SCREEN_PROPERTY_VISIBLE, &visible);
}

/**
 * Destroys the native window associated with the given SDL window.
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ   *impl = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (impl) {
        SDL_EGL_DestroySurface(_this, impl->egl_surface);
        screen_destroy_ಕಿಟಕಿ(impl->ಕಿಟಕಿ);
        ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
    }
}

/**
 * Frees the plugin object created by createDevice().
 */
ಸ್ಥಿರ ಶೂನ್ಯ QNX_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

/**
 * Creates the QNX video plugin used by SDL.
 */
ಸ್ಥಿರ SDL_VideoDevice *createDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    device->ಆಂತರಿಕ = ಖಾಲಿ;
    device->VideoInit = QNX_VideoInit;
    device->VideoQuit = QNX_VideoQuit;
    device->CreateSDLWindow = QNX_Create_ಕಿಟಕಿ;
    device->Create_ಕಿಟಕಿ_Framebuffer = QNX_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = QNX_Update_ಕಿಟಕಿ_Framebuffer;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = QNX_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = QNX_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->Show_ಕಿಟಕಿ = QNX_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = QNX_Hide_ಕಿಟಕಿ;
    device->Get_Display_For_ಕಿಟಕಿ = QNX_Get_Display_For_ಕಿಟಕಿ;
    device->GetDisplayBounds = QNX_GetDisplayBounds;
    device->GetDisplayModes = QNX_GetDisplayModes;
#ಆದರೆ 0
    device->ಗಣ_Display_ಬಹುಲಕ = QNX_ಗಣ_Display_ಬಹುಲಕ;
#ಆದರೆ_ಅಂತ್ಯ
    device->PumpEvents = QNX_PumpEvents;
    device->Destroy_ಕಿಟಕಿ = QNX_Destroy_ಕಿಟಕಿ;

    device->GL_ತುಂಬು_Library = QNX_GLES_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = QNX_GLES_Get_Proc_ವಿಳಾಸ;
    device->GL_CreateContext = QNX_GLES_CreateContext;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = QNX_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = QNX_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = QNX_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_MakeCurrent = QNX_GLES_MakeCurrent;
    device->GL_DestroyContext = QNX_GLES_DeleteContext;
    device->GL_UnloadLibrary = QNX_GLES_UnloadLibrary;

    device->ಬಿಡುಗಡೆ = QNX_DeleteDevice;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap QNX_bootstrap = {
    "qnx", "QNX Screen",
    createDevice,
    ಖಾಲಿ, // no ShowMessageBox implementation
    false
};

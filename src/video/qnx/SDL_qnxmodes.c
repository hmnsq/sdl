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
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_windowevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_qnx.h"

#ಅನ್ತರ್ಭಾವ <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_PixelFormat _format_map[] = {
    [SCREEN_FORMAT_RGBA4444] = SDL_PIXELFORMAT_RGBA4444,
    [SCREEN_FORMAT_RGBA5551] = SDL_PIXELFORMAT_RGBA5551,
    [SCREEN_FORMAT_RGB565] = SDL_PIXELFORMAT_RGB565,
    [SCREEN_FORMAT_RGBA8888] = SDL_PIXELFORMAT_RGBA8888,
    [SCREEN_FORMAT_RGBX8888] = SDL_PIXELFORMAT_RGBX8888,
    [SCREEN_FORMAT_NV12] = SDL_PIXELFORMAT_NV12,
    [SCREEN_FORMAT_YV12] = SDL_PIXELFORMAT_YV12,
    [SCREEN_FORMAT_UYVY] = SDL_PIXELFORMAT_UYVY,
    [SCREEN_FORMAT_YUY2] = SDL_PIXELFORMAT_YUY2,
    [SCREEN_FORMAT_YVYU] = SDL_PIXELFORMAT_YVYU,
    [SCREEN_FORMAT_P010] = SDL_PIXELFORMAT_P010,
    [SCREEN_FORMAT_BGRA8888] = SDL_PIXELFORMAT_BGRA8888,
    [SCREEN_FORMAT_BGRX8888] = SDL_PIXELFORMAT_BGRX8888,
};

SDL_PixelFormat screen_ಗಮ್ಯ_Pixel_Format(ಪೂರ್ಣಾಂಕ screen_format)
{
    ಆದರೆ ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ದತ್ತಾಂಶ     *display_ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ     display_ಬಹುಲಕ_2;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *display_ಬಹುಲಕ_ದತ್ತಾಂಶ;

    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;
    ಪೂರ್ಣಾಂಕ display_ಬಹುಲಕ_ಎಣಿಕೆ;

    screen_display_t      screen_display;
    screen_display_ಬಹುಲಕ_t *screen_display_modes;
    ಪೂರ್ಣಾಂಕ                   screen_format;
    ಪೂರ್ಣಾಂಕ                   screen_refresh_ದರ;

    ಆದರೆ (display_ದತ್ತಾಂಶ == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ false;
    }
    screen_display = display_ದತ್ತಾಂಶ->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    ಆದರೆ (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_ಬಹುಲಕ_ಎಣಿಕೆ, &display_ಬಹುಲಕ_ಎಣಿಕೆ) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    screen_display_modes = SDL_calloc(display_ಬಹುಲಕ_ಎಣಿಕೆ, ಗಾತ್ರ(screen_display_ಬಹುಲಕ_t));
    ಆದರೆ (screen_display_modes == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ(screen_get_display_modes(screen_display, display_ಬಹುಲಕ_ಎಣಿಕೆ, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        ಹಿಂತಿರುಗಿ false;
    }

    ಗಾಗಿ (ಸೂಚ್ಯಂಕ = 0; ಸೂಚ್ಯಂಕ < display_ಬಹುಲಕ_ಎಣಿಕೆ; ಸೂಚ್ಯಂಕ++) {
        display_ಬಹುಲಕ_ದತ್ತಾಂಶ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
        ಆದರೆ (display_ಬಹುಲಕ_ದತ್ತಾಂಶ == ಖಾಲಿ) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            ಹಿಂತಿರುಗಿ false;
        }

        SDL_zero(display_ಬಹುಲಕ_2);
        display_ಬಹುಲಕ_2.w = screen_display_modes[ಸೂಚ್ಯಂಕ].ಅಗಲ;
        display_ಬಹುಲಕ_2.h = screen_display_modes[ಸೂಚ್ಯಂಕ].ಎತ್ತರ;
        display_ಬಹುಲಕ_2.pixel_density = 1.0;
        display_ಬಹುಲಕ_2.ಆಂತರಿಕ = display_ಬಹುಲಕ_ದತ್ತಾಂಶ;

        ಆದರೆ (screen_display_modes[ಸೂಚ್ಯಂಕ].flags & SCREEN_DISPLAY_ಬಹುಲಕ_REFRESH_VALID) {
            screen_refresh_ದರ = screen_display_modes[ಸೂಚ್ಯಂಕ].refresh;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Fallback
            screen_refresh_ದರ = 60;
        }
        ಆದರೆ (screen_display_modes[ಸೂಚ್ಯಂಕ].flags & SCREEN_DISPLAY_ಬಹುಲಕ_FORMAT_VALID) {
            screen_format = screen_display_modes[ಸೂಚ್ಯಂಕ].format;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_ಬಹುಲಕ_2.refresh_ದರ = screen_refresh_ದರ;
        display_ಬಹುಲಕ_2.format = screen_ಗಮ್ಯ_Pixel_Format(screen_format);
        display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_format = screen_format;
        display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_display_ಬಹುಲಕ = screen_display_modes[ಸೂಚ್ಯಂಕ];

        // This op can fail if the mode already exists.
        SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &display_ಬಹುಲಕ_2);
    }

    SDL_free(screen_display_modes);

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ದತ್ತಾಂಶ     *display_ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *display_ಬಹುಲಕ_ದತ್ತಾಂಶ = ಬಹುಲಕ->ಆಂತರಿಕ;

    ಆದರೆ ((display_ದತ್ತಾಂಶ == ಖಾಲಿ) || (display_ಬಹುಲಕ_ದತ್ತಾಂಶ == ಖಾಲಿ)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    ಆದರೆ (screen_ಗಣ_display_property_iv(display_ದತ್ತಾಂಶ->screen_display,
        SCREEN_PROPERTY_ಬಹುಲಕ, (ಪೂರ್ಣಾಂಕ *)&display_ಬಹುಲಕ_ದತ್ತಾಂಶ->screen_display_ಬಹುಲಕ.ಸೂಚ್ಯಂಕ) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಹಿಂತಿರುಗಿ true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = display->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ             ಗಾತ್ರ_2[2] = { 0, 0 };

    ಆದರೆ (ದತ್ತಾಂಶ == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (screen_get_display_property_iv(ದತ್ತಾಂಶ->screen_display, SCREEN_PROPERTY_ಗಾತ್ರ, ಗಾತ್ರ_2) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = ಗಾತ್ರ_2[0];
    rect->h = ಗಾತ್ರ_2[1];
    ಹಿಂತಿರುಗಿ true;
}
#ಇಲ್ಲದಿದ್ದರೆ
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ಆದರೆ (display->current_ಬಹುಲಕ == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    ಆದರೆ (display->fullscreen_ಕಿಟಕಿ &&
        display->fullscreen_ಕಿಟಕಿ->fullscreen_exclusive &&
        display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w != 0 &&
        display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h != 0) {
        rect->w = display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w;
        rect->h = display->fullscreen_ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        rect->w = display->current_ಬಹುಲಕ->w;
        rect->h = display->current_ಬಹುಲಕ->h;
    }
    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ

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

#ضمن "SDL_internal.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_windowevents_c.h"
#ضمن "SDL_qnx.h"

#ضمن <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
ساكن ثابت SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screen_منزل_Pixel_Format(صحيح screen_format)
{
    إذا ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }

    أرجع _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_معلومات     *display_معلومات = display->دننی;
    SDL_Display_ډېرپېښ     display_ډېرپېښ_2;
    SDL_Display_ډېرپېښ_معلومات *display_ډېرپېښ_معلومات;

    صحيح شاخص;
    صحيح display_ډېرپېښ_شمېر;

    screen_display_t      screen_display;
    screen_display_ډېرپېښ_t *screen_display_modes;
    صحيح                   screen_format;
    صحيح                   screen_refresh_شرح;

    إذا (display_معلومات == عدم) {
        أرجع false;
    }
    screen_display = display_معلومات->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    إذا (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_ډېرپېښ_شمېر, &display_ډېرپېښ_شمېر) < 0) {
        أرجع false;
    }

    screen_display_modes = SDL_calloc(display_ډېرپېښ_شمېر, حجم(screen_display_ډېرپېښ_t));
    إذا (screen_display_modes == عدم) {
        أرجع false;
    }

    إذا(screen_get_display_modes(screen_display, display_ډېرپېښ_شمېر, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        أرجع false;
    }

    لكل (شاخص = 0; شاخص < display_ډېرپېښ_شمېر; شاخص++) {
        display_ډېرپېښ_معلومات = (SDL_Display_ډېرپېښ_معلومات *)SDL_calloc(1, حجم(SDL_Display_ډېرپېښ_معلومات));
        إذا (display_ډېرپېښ_معلومات == عدم) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            أرجع false;
        }

        SDL_zero(display_ډېرپېښ_2);
        display_ډېرپېښ_2.w = screen_display_modes[شاخص].پلنوالی;
        display_ډېرپېښ_2.h = screen_display_modes[شاخص].لوړوالی;
        display_ډېرپېښ_2.pixel_density = 1.0;
        display_ډېرپېښ_2.دننی = display_ډېرپېښ_معلومات;

        إذا (screen_display_modes[شاخص].flags & SCREEN_DISPLAY_ډېرپېښ_REFRESH_VALID) {
            screen_refresh_شرح = screen_display_modes[شاخص].refresh;
        } وإلا {
            // Fallback
            screen_refresh_شرح = 60;
        }
        إذا (screen_display_modes[شاخص].flags & SCREEN_DISPLAY_ډېرپېښ_FORMAT_VALID) {
            screen_format = screen_display_modes[شاخص].format;
        } وإلا {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_ډېرپېښ_2.refresh_شرح = screen_refresh_شرح;
        display_ډېرپېښ_2.format = screen_منزل_Pixel_Format(screen_format);
        display_ډېرپېښ_معلومات->screen_format = screen_format;
        display_ډېرپېښ_معلومات->screen_display_ډېرپېښ = screen_display_modes[شاخص];

        // This op can fail if the mode already exists.
        SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(display, &display_ډېرپېښ_2);
    }

    SDL_free(screen_display_modes);

    أرجع true;
}

#إذا 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Display_معلومات     *display_معلومات = display->دننی;
    SDL_Display_ډېرپېښ_معلومات *display_ډېرپېښ_معلومات = ډېرپېښ->دننی;

    إذا ((display_معلومات == عدم) || (display_ډېرپېښ_معلومات == عدم)) {
        أرجع false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    إذا (screen_سېټ_display_property_iv(display_معلومات->screen_display,
        SCREEN_PROPERTY_ډېرپېښ, (صحيح *)&display_ډېرپېښ_معلومات->screen_display_ډېرپېښ.شاخص) < 0) {
        أرجع false;
    }

    أرجع true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_معلومات *معلومات = display->دننی;
    صحيح             اندازه[2] = { 0, 0 };

    إذا (معلومات == عدم) {
        أرجع false;
    }

    إذا (screen_get_display_property_iv(معلومات->screen_display, SCREEN_PROPERTY_اندازه, اندازه) < 0) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = اندازه[0];
    rect->h = اندازه[1];
    أرجع true;
}
#وإلا
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    إذا (display->current_ډېرپېښ == عدم) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_کړکۍ &&
        display->fullscreen_کړکۍ->fullscreen_exclusive &&
        display->fullscreen_کړکۍ->current_fullscreen_ډېرپېښ.w != 0 &&
        display->fullscreen_کړکۍ->current_fullscreen_ډېرپېښ.h != 0) {
        rect->w = display->fullscreen_کړکۍ->current_fullscreen_ډېرپېښ.w;
        rect->h = display->fullscreen_کړکۍ->current_fullscreen_ډېرپېښ.h;
    } وإلا {
        rect->w = display->current_ډېرپېښ->w;
        rect->h = display->current_ډېرپېښ->h;
    }
    أرجع true;
}
#د_که_پای

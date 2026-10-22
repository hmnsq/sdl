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

SDL_PixelFormat screen_مقصد_Pixel_Format(صحيح screen_format)
{
    إذا ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }

    أرجع _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_داده     *display_داده = display->داخلی;
    SDL_Display_نما     display_نما_2;
    SDL_Display_نما_داده *display_نما_داده;

    صحيح شاخص;
    صحيح display_نما_شمار;

    screen_display_t      screen_display;
    screen_display_نما_t *screen_display_modes;
    صحيح                   screen_format;
    صحيح                   screen_refresh_نرخ;

    إذا (display_داده == عدم) {
        أرجع false;
    }
    screen_display = display_داده->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    إذا (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_نما_شمار, &display_نما_شمار) < 0) {
        أرجع false;
    }

    screen_display_modes = SDL_calloc(display_نما_شمار, حجم(screen_display_نما_t));
    إذا (screen_display_modes == عدم) {
        أرجع false;
    }

    إذا(screen_get_display_modes(screen_display, display_نما_شمار, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        أرجع false;
    }

    لكل (شاخص = 0; شاخص < display_نما_شمار; شاخص++) {
        display_نما_داده = (SDL_Display_نما_داده *)SDL_calloc(1, حجم(SDL_Display_نما_داده));
        إذا (display_نما_داده == عدم) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            أرجع false;
        }

        SDL_zero(display_نما_2);
        display_نما_2.w = screen_display_modes[شاخص].عرض;
        display_نما_2.h = screen_display_modes[شاخص].ارتفاع;
        display_نما_2.pixel_density = 1.0;
        display_نما_2.داخلی = display_نما_داده;

        إذا (screen_display_modes[شاخص].flags & SCREEN_DISPLAY_نما_REFRESH_VALID) {
            screen_refresh_نرخ = screen_display_modes[شاخص].refresh;
        } وإلا {
            // Fallback
            screen_refresh_نرخ = 60;
        }
        إذا (screen_display_modes[شاخص].flags & SCREEN_DISPLAY_نما_FORMAT_VALID) {
            screen_format = screen_display_modes[شاخص].format;
        } وإلا {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_نما_2.refresh_نرخ = screen_refresh_نرخ;
        display_نما_2.format = screen_مقصد_Pixel_Format(screen_format);
        display_نما_داده->screen_format = screen_format;
        display_نما_داده->screen_display_نما = screen_display_modes[شاخص];

        // This op can fail if the mode already exists.
        SDL_جمع_کن_Fullscreen_Display_نما(display, &display_نما_2);
    }

    SDL_free(screen_display_modes);

    أرجع true;
}

#إذا 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    SDL_Display_داده     *display_داده = display->داخلی;
    SDL_Display_نما_داده *display_نما_داده = نما->داخلی;

    إذا ((display_داده == عدم) || (display_نما_داده == عدم)) {
        أرجع false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    إذا (screen_مجموعه_display_property_iv(display_داده->screen_display,
        SCREEN_PROPERTY_نما, (صحيح *)&display_نما_داده->screen_display_نما.شاخص) < 0) {
        أرجع false;
    }

    أرجع true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_داده *داده = display->داخلی;
    صحيح             اندازه[2] = { 0, 0 };

    إذا (داده == عدم) {
        أرجع false;
    }

    إذا (screen_get_display_property_iv(داده->screen_display, SCREEN_PROPERTY_اندازه, اندازه) < 0) {
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
    إذا (display->current_نما == عدم) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_پنجره &&
        display->fullscreen_پنجره->fullscreen_exclusive &&
        display->fullscreen_پنجره->current_fullscreen_نما.w != 0 &&
        display->fullscreen_پنجره->current_fullscreen_نما.h != 0) {
        rect->w = display->fullscreen_پنجره->current_fullscreen_نما.w;
        rect->h = display->fullscreen_پنجره->current_fullscreen_نما.h;
    } وإلا {
        rect->w = display->current_نما->w;
        rect->h = display->current_نما->h;
    }
    أرجع true;
}
#پایان_اگر

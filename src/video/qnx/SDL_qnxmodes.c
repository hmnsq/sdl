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
    SDL_Display_انکڑے     *display_انکڑے = display->اندرونی;
    SDL_Display_منوال     display_منوال_2;
    SDL_Display_منوال_انکڑے *display_منوال_انکڑے;

    صحيح اشاریہ;
    صحيح display_منوال_گنتی;

    screen_display_t      screen_display;
    screen_display_منوال_t *screen_display_modes;
    صحيح                   screen_format;
    صحيح                   screen_refresh_شرح;

    إذا (display_انکڑے == عدم) {
        أرجع false;
    }
    screen_display = display_انکڑے->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    إذا (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_منوال_گنتی, &display_منوال_گنتی) < 0) {
        أرجع false;
    }

    screen_display_modes = SDL_calloc(display_منوال_گنتی, حجم(screen_display_منوال_t));
    إذا (screen_display_modes == عدم) {
        أرجع false;
    }

    إذا(screen_get_display_modes(screen_display, display_منوال_گنتی, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        أرجع false;
    }

    لكل (اشاریہ = 0; اشاریہ < display_منوال_گنتی; اشاریہ++) {
        display_منوال_انکڑے = (SDL_Display_منوال_انکڑے *)SDL_calloc(1, حجم(SDL_Display_منوال_انکڑے));
        إذا (display_منوال_انکڑے == عدم) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            أرجع false;
        }

        SDL_zero(display_منوال_2);
        display_منوال_2.w = screen_display_modes[اشاریہ].چوڑائی;
        display_منوال_2.h = screen_display_modes[اشاریہ].اچائی;
        display_منوال_2.pixel_density = 1.0;
        display_منوال_2.اندرونی = display_منوال_انکڑے;

        إذا (screen_display_modes[اشاریہ].flags & SCREEN_DISPLAY_منوال_REFRESH_VALID) {
            screen_refresh_شرح = screen_display_modes[اشاریہ].refresh;
        } وإلا {
            // Fallback
            screen_refresh_شرح = 60;
        }
        إذا (screen_display_modes[اشاریہ].flags & SCREEN_DISPLAY_منوال_FORMAT_VALID) {
            screen_format = screen_display_modes[اشاریہ].format;
        } وإلا {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_منوال_2.refresh_شرح = screen_refresh_شرح;
        display_منوال_2.format = screen_منزل_Pixel_Format(screen_format);
        display_منوال_انکڑے->screen_format = screen_format;
        display_منوال_انکڑے->screen_display_منوال = screen_display_modes[اشاریہ];

        // This op can fail if the mode already exists.
        SDL_جوڑو_Fullscreen_Display_منوال(display, &display_منوال_2);
    }

    SDL_free(screen_display_modes);

    أرجع true;
}

#إذا 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    SDL_Display_انکڑے     *display_انکڑے = display->اندرونی;
    SDL_Display_منوال_انکڑے *display_منوال_انکڑے = منوال->اندرونی;

    إذا ((display_انکڑے == عدم) || (display_منوال_انکڑے == عدم)) {
        أرجع false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    إذا (screen_سیٹ_display_property_iv(display_انکڑے->screen_display,
        SCREEN_PROPERTY_منوال, (صحيح *)&display_منوال_انکڑے->screen_display_منوال.اشاریہ) < 0) {
        أرجع false;
    }

    أرجع true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_انکڑے *انکڑے = display->اندرونی;
    صحيح             ناپ[2] = { 0, 0 };

    إذا (انکڑے == عدم) {
        أرجع false;
    }

    إذا (screen_get_display_property_iv(انکڑے->screen_display, SCREEN_PROPERTY_ناپ, ناپ) < 0) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = ناپ[0];
    rect->h = ناپ[1];
    أرجع true;
}
#وإلا
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    إذا (display->current_منوال == عدم) {
        أرجع false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    إذا (display->fullscreen_کھڑکی &&
        display->fullscreen_کھڑکی->fullscreen_exclusive &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.w != 0 &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.h != 0) {
        rect->w = display->fullscreen_کھڑکی->current_fullscreen_منوال.w;
        rect->h = display->fullscreen_کھڑکی->current_fullscreen_منوال.h;
    } وإلا {
        rect->w = display->current_منوال->w;
        rect->h = display->current_منوال->h;
    }
    أرجع true;
}
#جے_انت

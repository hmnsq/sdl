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

#شامل "SDL_internal.h"
#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_windowevents_c.h"
#شامل "SDL_qnx.h"

#شامل <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
ساکن ثابت SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screen_مقصد_Pixel_Format(صحیح screen_format)
{
    اگر ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        واپس SDL_PIXELFORMAT_UNKNOWN;
    }

    واپس _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ڈیٹا     *display_ڈیٹا = display->اندرونی_2;
    SDL_Display_منوال     display_منوال_2;
    SDL_Display_منوال_ڈیٹا *display_منوال_ڈیٹا;

    صحیح اشاریہ;
    صحیح display_منوال_گنتی;

    screen_display_t      screen_display;
    screen_display_منوال_t *screen_display_modes;
    صحیح                   screen_format;
    صحیح                   screen_refresh_شرح;

    اگر (display_ڈیٹا == تہی) {
        واپس false;
    }
    screen_display = display_ڈیٹا->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    اگر (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_منوال_گنتی, &display_منوال_گنتی) < 0) {
        واپس false;
    }

    screen_display_modes = SDL_calloc(display_منوال_گنتی, حجم(screen_display_منوال_t));
    اگر (screen_display_modes == تہی) {
        واپس false;
    }

    اگر(screen_get_display_modes(screen_display, display_منوال_گنتی, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        واپس false;
    }

    برائے (اشاریہ = 0; اشاریہ < display_منوال_گنتی; اشاریہ++) {
        display_منوال_ڈیٹا = (SDL_Display_منوال_ڈیٹا *)SDL_calloc(1, حجم(SDL_Display_منوال_ڈیٹا));
        اگر (display_منوال_ڈیٹا == تہی) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            واپس false;
        }

        SDL_zero(display_منوال_2);
        display_منوال_2.w = screen_display_modes[اشاریہ].چوڑائی;
        display_منوال_2.h = screen_display_modes[اشاریہ].اونچائی;
        display_منوال_2.pixel_density = 1.0;
        display_منوال_2.اندرونی_2 = display_منوال_ڈیٹا;

        اگر (screen_display_modes[اشاریہ].flags & SCREEN_DISPLAY_منوال_REFRESH_VALID) {
            screen_refresh_شرح = screen_display_modes[اشاریہ].refresh;
        } ورنہ {
            // Fallback
            screen_refresh_شرح = 60;
        }
        اگر (screen_display_modes[اشاریہ].flags & SCREEN_DISPLAY_منوال_FORMAT_VALID) {
            screen_format = screen_display_modes[اشاریہ].format;
        } ورنہ {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_منوال_2.refresh_شرح = screen_refresh_شرح;
        display_منوال_2.format = screen_مقصد_Pixel_Format(screen_format);
        display_منوال_ڈیٹا->screen_format = screen_format;
        display_منوال_ڈیٹا->screen_display_منوال = screen_display_modes[اشاریہ];

        // This op can fail if the mode already exists.
        SDL_جوڑو_Fullscreen_Display_منوال(display, &display_منوال_2);
    }

    SDL_free(screen_display_modes);

    واپس true;
}

#اگر 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    SDL_Display_ڈیٹا     *display_ڈیٹا = display->اندرونی_2;
    SDL_Display_منوال_ڈیٹا *display_منوال_ڈیٹا = منوال->اندرونی_2;

    اگر ((display_ڈیٹا == تہی) || (display_منوال_ڈیٹا == تہی)) {
        واپس false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    اگر (screen_سیٹ_display_property_iv(display_ڈیٹا->screen_display,
        SCREEN_PROPERTY_منوال, (صحیح *)&display_منوال_ڈیٹا->screen_display_منوال.اشاریہ) < 0) {
        واپس false;
    }

    واپس true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_ڈیٹا *ڈیٹا = display->اندرونی_2;
    صحیح             سائز[2] = { 0, 0 };

    اگر (ڈیٹا == تہی) {
        واپس false;
    }

    اگر (screen_get_display_property_iv(ڈیٹا->screen_display, SCREEN_PROPERTY_سائز, سائز) < 0) {
        واپس false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = سائز[0];
    rect->h = سائز[1];
    واپس true;
}
#ورنہ
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    اگر (display->current_منوال == تہی) {
        واپس false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    اگر (display->fullscreen_کھڑکی &&
        display->fullscreen_کھڑکی->fullscreen_exclusive &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.w != 0 &&
        display->fullscreen_کھڑکی->current_fullscreen_منوال.h != 0) {
        rect->w = display->fullscreen_کھڑکی->current_fullscreen_منوال.w;
        rect->h = display->fullscreen_کھڑکی->current_fullscreen_منوال.h;
    } ورنہ {
        rect->w = display->current_منوال->w;
        rect->h = display->current_منوال->h;
    }
    واپس true;
}
#اگر_ختم

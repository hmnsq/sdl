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

#অন্তর্ভাব "SDL_internal.h"
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_windowevents_c.h"
#অন্তর্ভাব "SDL_qnx.h"

#অন্তর্ভাব <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
স্থির ধ্রুবক SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screenToPixelFormat(পূর্ণসংখ্যা screen_format)
{
    যদি ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        ফেরত SDL_PIXELFORMAT_UNKNOWN;
    }

    ফেরত _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_তথ্য     *display_তথ্য = display->internal;
    SDL_DisplayMode     display_mode;
    SDL_Display_Mode_তথ্য *display_mode_তথ্য;

    পূর্ণসংখ্যা সূচক;
    পূর্ণসংখ্যা display_mode_গুনতি;

    screen_display_t      screen_display;
    screen_display_mode_t *screen_display_modes;
    পূর্ণসংখ্যা                   screen_format;
    পূর্ণসংখ্যা                   screen_refresh_rate;

    যদি (display_তথ্য == ফাঁকা) {
        ফেরত false;
    }
    screen_display = display_তথ্য->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    যদি (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_MODE_গুনতি, &display_mode_গুনতি) < 0) {
        ফেরত false;
    }

    screen_display_modes = SDL_calloc(display_mode_গুনতি, আকার(screen_display_mode_t));
    যদি (screen_display_modes == ফাঁকা) {
        ফেরত false;
    }

    যদি(screen_get_display_modes(screen_display, display_mode_গুনতি, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        ফেরত false;
    }

    জন্য (সূচক = 0; সূচক < display_mode_গুনতি; সূচক++) {
        display_mode_তথ্য = (SDL_Display_Mode_তথ্য *)SDL_calloc(1, আকার(SDL_Display_Mode_তথ্য));
        যদি (display_mode_তথ্য == ফাঁকা) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            ফেরত false;
        }

        SDL_zero(display_mode);
        display_mode.w = screen_display_modes[সূচক].width;
        display_mode.h = screen_display_modes[সূচক].height;
        display_mode.pixel_density = 1.0;
        display_mode.internal = display_mode_তথ্য;

        যদি (screen_display_modes[সূচক].flags & SCREEN_DISPLAY_MODE_REFRESH_VALID) {
            screen_refresh_rate = screen_display_modes[সূচক].refresh;
        } অন্যথা {
            // Fallback
            screen_refresh_rate = 60;
        }
        যদি (screen_display_modes[সূচক].flags & SCREEN_DISPLAY_MODE_FORMAT_VALID) {
            screen_format = screen_display_modes[সূচক].format;
        } অন্যথা {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_mode.refresh_rate = screen_refresh_rate;
        display_mode.format = screenToPixelFormat(screen_format);
        display_mode_তথ্য->screen_format = screen_format;
        display_mode_তথ্য->screen_display_mode = screen_display_modes[সূচক];

        // This op can fail if the mode already exists.
        SDL_AddFullscreenDisplayMode(display, &display_mode);
    }

    SDL_free(screen_display_modes);

    ফেরত true;
}

#যদি 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_Display_তথ্য     *display_তথ্য = display->internal;
    SDL_Display_Mode_তথ্য *display_mode_তথ্য = mode->internal;

    যদি ((display_তথ্য == ফাঁকা) || (display_mode_তথ্য == ফাঁকা)) {
        ফেরত false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    যদি (screen_set_display_property_iv(display_তথ্য->screen_display,
        SCREEN_PROPERTY_MODE, (পূর্ণসংখ্যা *)&display_mode_তথ্য->screen_display_mode.সূচক) < 0) {
        ফেরত false;
    }

    ফেরত true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_তথ্য *তথ্য = display->internal;
    পূর্ণসংখ্যা             আকার_2[2] = { 0, 0 };

    যদি (তথ্য == ফাঁকা) {
        ফেরত false;
    }

    যদি (screen_get_display_property_iv(তথ্য->screen_display, SCREEN_PROPERTY_আকার, আকার_2) < 0) {
        ফেরত false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = আকার_2[0];
    rect->h = আকার_2[1];
    ফেরত true;
}
#অন্যথা
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    যদি (display->current_mode == ফাঁকা) {
        ফেরত false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    যদি (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } অন্যথা {
        rect->w = display->current_mode->w;
        rect->h = display->current_mode->h;
    }
    ফেরত true;
}
#endif

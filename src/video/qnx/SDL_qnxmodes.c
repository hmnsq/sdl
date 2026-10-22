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

#અન્તર્ભાવ "SDL_internal.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_windowevents_c.h"
#અન્તર્ભાવ "SDL_qnx.h"

#અન્તર્ભાવ <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
સ્થિર અચલ SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screenToPixelFormat(પૂર્ણાંક screen_format)
{
    જો ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        પાછા SDL_PIXELFORMAT_UNKNOWN;
    }

    પાછા _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayData     *display_data = display->internal;
    SDL_DisplayMode     display_mode;
    SDL_DisplayModeData *display_mode_data;

    પૂર્ણાંક index;
    પૂર્ણાંક display_mode_ગણતરી;

    screen_display_t      screen_display;
    screen_display_mode_t *screen_display_modes;
    પૂર્ણાંક                   screen_format;
    પૂર્ણાંક                   screen_refresh_rate;

    જો (display_data == ખાલી) {
        પાછા false;
    }
    screen_display = display_data->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    જો (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_MODE_ગણતરી, &display_mode_ગણતરી) < 0) {
        પાછા false;
    }

    screen_display_modes = SDL_calloc(display_mode_ગણતરી, કદ(screen_display_mode_t));
    જો (screen_display_modes == ખાલી) {
        પાછા false;
    }

    જો(screen_get_display_modes(screen_display, display_mode_ગણતરી, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        પાછા false;
    }

    માટે (index = 0; index < display_mode_ગણતરી; index++) {
        display_mode_data = (SDL_DisplayModeData *)SDL_calloc(1, કદ(SDL_DisplayModeData));
        જો (display_mode_data == ખાલી) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            પાછા false;
        }

        SDL_zero(display_mode);
        display_mode.w = screen_display_modes[index].width;
        display_mode.h = screen_display_modes[index].height;
        display_mode.pixel_density = 1.0;
        display_mode.internal = display_mode_data;

        જો (screen_display_modes[index].flags & SCREEN_DISPLAY_MODE_REFRESH_VALID) {
            screen_refresh_rate = screen_display_modes[index].refresh;
        } નહીંતર {
            // Fallback
            screen_refresh_rate = 60;
        }
        જો (screen_display_modes[index].flags & SCREEN_DISPLAY_MODE_FORMAT_VALID) {
            screen_format = screen_display_modes[index].format;
        } નહીંતર {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_mode.refresh_rate = screen_refresh_rate;
        display_mode.format = screenToPixelFormat(screen_format);
        display_mode_data->screen_format = screen_format;
        display_mode_data->screen_display_mode = screen_display_modes[index];

        // This op can fail if the mode already exists.
        SDL_AddFullscreenDisplayMode(display, &display_mode);
    }

    SDL_free(screen_display_modes);

    પાછા true;
}

#જો 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_DisplayData     *display_data = display->internal;
    SDL_DisplayModeData *display_mode_data = mode->internal;

    જો ((display_data == ખાલી) || (display_mode_data == ખાલી)) {
        પાછા false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    જો (screen_set_display_property_iv(display_data->screen_display,
        SCREEN_PROPERTY_MODE, (પૂર્ણાંક *)&display_mode_data->screen_display_mode.index) < 0) {
        પાછા false;
    }

    પાછા true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_DisplayData *data = display->internal;
    પૂર્ણાંક             size[2] = { 0, 0 };

    જો (data == ખાલી) {
        પાછા false;
    }

    જો (screen_get_display_property_iv(data->screen_display, SCREEN_PROPERTY_SIZE, size) < 0) {
        પાછા false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = size[0];
    rect->h = size[1];
    પાછા true;
}
#નહીંતર
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    જો (display->current_mode == ખાલી) {
        પાછા false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    જો (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } નહીંતર {
        rect->w = display->current_mode->w;
        rect->h = display->current_mode->h;
    }
    પાછા true;
}
#endif

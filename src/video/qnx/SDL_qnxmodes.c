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

#समावेश "SDL_internal.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_windowevents_c.h"
#समावेश "SDL_qnx.h"

#समावेश <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
अटल स्थिर SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screenToPixelFormat(पूर्णांक screen_format)
{
    अगर ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        वापस SDL_PIXELFORMAT_UNKNOWN;
    }

    वापस _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_तथ्य     *display_तथ्य = display->internal;
    SDL_DisplayMode     display_mode;
    SDL_Display_Mode_तथ्य *display_mode_तथ्य;

    पूर्णांक सूचकांक;
    पूर्णांक display_mode_गिनती;

    screen_display_t      screen_display;
    screen_display_mode_t *screen_display_modes;
    पूर्णांक                   screen_format;
    पूर्णांक                   screen_refresh_rate;

    अगर (display_तथ्य == शून्य) {
        वापस false;
    }
    screen_display = display_तथ्य->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    अगर (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_MODE_गिनती, &display_mode_गिनती) < 0) {
        वापस false;
    }

    screen_display_modes = SDL_calloc(display_mode_गिनती, माप(screen_display_mode_t));
    अगर (screen_display_modes == शून्य) {
        वापस false;
    }

    अगर(screen_get_display_modes(screen_display, display_mode_गिनती, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        वापस false;
    }

    क्रम (सूचकांक = 0; सूचकांक < display_mode_गिनती; सूचकांक++) {
        display_mode_तथ्य = (SDL_Display_Mode_तथ्य *)SDL_calloc(1, माप(SDL_Display_Mode_तथ्य));
        अगर (display_mode_तथ्य == शून्य) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            वापस false;
        }

        SDL_zero(display_mode);
        display_mode.w = screen_display_modes[सूचकांक].width;
        display_mode.h = screen_display_modes[सूचकांक].height;
        display_mode.pixel_density = 1.0;
        display_mode.internal = display_mode_तथ्य;

        अगर (screen_display_modes[सूचकांक].flags & SCREEN_DISPLAY_MODE_REFRESH_VALID) {
            screen_refresh_rate = screen_display_modes[सूचकांक].refresh;
        } अन्यथा {
            // Fallback
            screen_refresh_rate = 60;
        }
        अगर (screen_display_modes[सूचकांक].flags & SCREEN_DISPLAY_MODE_FORMAT_VALID) {
            screen_format = screen_display_modes[सूचकांक].format;
        } अन्यथा {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_mode.refresh_rate = screen_refresh_rate;
        display_mode.format = screenToPixelFormat(screen_format);
        display_mode_तथ्य->screen_format = screen_format;
        display_mode_तथ्य->screen_display_mode = screen_display_modes[सूचकांक];

        // This op can fail if the mode already exists.
        SDL_AddFullscreenDisplayMode(display, &display_mode);
    }

    SDL_free(screen_display_modes);

    वापस true;
}

#अगर 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    SDL_Display_तथ्य     *display_तथ्य = display->internal;
    SDL_Display_Mode_तथ्य *display_mode_तथ्य = mode->internal;

    अगर ((display_तथ्य == शून्य) || (display_mode_तथ्य == शून्य)) {
        वापस false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    अगर (screen_set_display_property_iv(display_तथ्य->screen_display,
        SCREEN_PROPERTY_MODE, (पूर्णांक *)&display_mode_तथ्य->screen_display_mode.सूचकांक) < 0) {
        वापस false;
    }

    वापस true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_तथ्य *तथ्य = display->internal;
    पूर्णांक             आकार[2] = { 0, 0 };

    अगर (तथ्य == शून्य) {
        वापस false;
    }

    अगर (screen_get_display_property_iv(तथ्य->screen_display, SCREEN_PROPERTY_आकार, आकार) < 0) {
        वापस false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = आकार[0];
    rect->h = आकार[1];
    वापस true;
}
#अन्यथा
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    अगर (display->current_mode == शून्य) {
        वापस false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    अगर (display->fullscreen_window &&
        display->fullscreen_window->fullscreen_exclusive &&
        display->fullscreen_window->current_fullscreen_mode.w != 0 &&
        display->fullscreen_window->current_fullscreen_mode.h != 0) {
        rect->w = display->fullscreen_window->current_fullscreen_mode.w;
        rect->h = display->fullscreen_window->current_fullscreen_mode.h;
    } अन्यथा {
        rect->w = display->current_mode->w;
        rect->h = display->current_mode->h;
    }
    वापस true;
}
#पूर्ण_अगर

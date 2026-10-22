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

#अन्तर्भाव "SDL_internal.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_windowevents_c.h"
#अन्तर्भाव "SDL_qnx.h"

#अन्तर्भाव <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
स्थिर ध्रुव SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screen_गन्तव्यम्_Pixel_Format(पूर्णाङ्क screen_format)
{
    यदि ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
    }

    प्रत्यागम _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_दत्त     *display_दत्त = display->आन्तरिकम्;
    SDL_Display_बहुलकम्     display_बहुलकम्_2;
    SDL_Display_बहुलकम्_दत्त *display_बहुलकम्_दत्त;

    पूर्णाङ्क सूचकांक;
    पूर्णाङ्क display_बहुलकम्_गणनम्;

    screen_display_t      screen_display;
    screen_display_बहुलकम्_t *screen_display_modes;
    पूर्णाङ्क                   screen_format;
    पूर्णाङ्क                   screen_refresh_दरः;

    यदि (display_दत्त == रिक्त) {
        प्रत्यागम false;
    }
    screen_display = display_दत्त->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    यदि (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_बहुलकम्_गणनम्, &display_बहुलकम्_गणनम्) < 0) {
        प्रत्यागम false;
    }

    screen_display_modes = SDL_calloc(display_बहुलकम्_गणनम्, परिमाण(screen_display_बहुलकम्_t));
    यदि (screen_display_modes == रिक्त) {
        प्रत्यागम false;
    }

    यदि(screen_get_display_modes(screen_display, display_बहुलकम्_गणनम्, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        प्रत्यागम false;
    }

    प्रति (सूचकांक = 0; सूचकांक < display_बहुलकम्_गणनम्; सूचकांक++) {
        display_बहुलकम्_दत्त = (SDL_Display_बहुलकम्_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));
        यदि (display_बहुलकम्_दत्त == रिक्त) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            प्रत्यागम false;
        }

        SDL_zero(display_बहुलकम्_2);
        display_बहुलकम्_2.w = screen_display_modes[सूचकांक].विस्तारः;
        display_बहुलकम्_2.h = screen_display_modes[सूचकांक].height;
        display_बहुलकम्_2.pixel_density = 1.0;
        display_बहुलकम्_2.आन्तरिकम् = display_बहुलकम्_दत्त;

        यदि (screen_display_modes[सूचकांक].flags & SCREEN_DISPLAY_बहुलकम्_REFRESH_VALID) {
            screen_refresh_दरः = screen_display_modes[सूचकांक].refresh;
        } अन्यथा {
            // Fallback
            screen_refresh_दरः = 60;
        }
        यदि (screen_display_modes[सूचकांक].flags & SCREEN_DISPLAY_बहुलकम्_FORMAT_VALID) {
            screen_format = screen_display_modes[सूचकांक].format;
        } अन्यथा {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_बहुलकम्_2.refresh_दरः = screen_refresh_दरः;
        display_बहुलकम्_2.format = screen_गन्तव्यम्_Pixel_Format(screen_format);
        display_बहुलकम्_दत्त->screen_format = screen_format;
        display_बहुलकम्_दत्त->screen_display_बहुलकम् = screen_display_modes[सूचकांक];

        // This op can fail if the mode already exists.
        SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &display_बहुलकम्_2);
    }

    SDL_free(screen_display_modes);

    प्रत्यागम true;
}

#यदि 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_दत्त     *display_दत्त = display->आन्तरिकम्;
    SDL_Display_बहुलकम्_दत्त *display_बहुलकम्_दत्त = बहुलकम्->आन्तरिकम्;

    यदि ((display_दत्त == रिक्त) || (display_बहुलकम्_दत्त == रिक्त)) {
        प्रत्यागम false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    यदि (screen_समुच्चयः_display_property_iv(display_दत्त->screen_display,
        SCREEN_PROPERTY_बहुलकम्, (पूर्णाङ्क *)&display_बहुलकम्_दत्त->screen_display_बहुलकम्.सूचकांक) < 0) {
        प्रत्यागम false;
    }

    प्रत्यागम true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_दत्त *दत्त = display->आन्तरिकम्;
    पूर्णाङ्क             आकार[2] = { 0, 0 };

    यदि (दत्त == रिक्त) {
        प्रत्यागम false;
    }

    यदि (screen_get_display_property_iv(दत्त->screen_display, SCREEN_PROPERTY_आकार, आकार) < 0) {
        प्रत्यागम false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = आकार[0];
    rect->h = आकार[1];
    प्रत्यागम true;
}
#अन्यथा
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    यदि (display->current_बहुलकम् == रिक्त) {
        प्रत्यागम false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    यदि (display->fullscreen_गवाक्षः &&
        display->fullscreen_गवाक्षः->fullscreen_exclusive &&
        display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.w != 0 &&
        display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.h != 0) {
        rect->w = display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.w;
        rect->h = display->fullscreen_गवाक्षः->current_fullscreen_बहुलकम्.h;
    } अन्यथा {
        rect->w = display->current_बहुलकम्->w;
        rect->h = display->current_बहुलकम्->h;
    }
    प्रत्यागम true;
}
#यदि_अन्तः

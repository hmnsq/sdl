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

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_windowevents_c.h"
#అన్తర్భావ "SDL_qnx.h"

#అన్తర్భావ <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
స్థిర స్థిరరాశి SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screen_గమ్యం_Pixel_Format(పూర్ణాంకం screen_format)
{
    ఒకవేళ ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        తిరిగి SDL_PIXELFORMAT_UNKNOWN;
    }

    తిరిగి _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_దత్తాంశం     *display_దత్తాంశం = display->అంతర్గత;
    SDL_Display_బహుళకం     display_బహుళకం_2;
    SDL_Display_బహుళకం_దత్తాంశం *display_బహుళకం_దత్తాంశం;

    పూర్ణాంకం సూచీ;
    పూర్ణాంకం display_బహుళకం_లెక్క;

    screen_display_t      screen_display;
    screen_display_బహుళకం_t *screen_display_modes;
    పూర్ణాంకం                   screen_format;
    పూర్ణాంకం                   screen_refresh_రేటు;

    ఒకవేళ (display_దత్తాంశం == ఖాళీ) {
        తిరిగి false;
    }
    screen_display = display_దత్తాంశం->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    ఒకవేళ (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_బహుళకం_లెక్క, &display_బహుళకం_లెక్క) < 0) {
        తిరిగి false;
    }

    screen_display_modes = SDL_calloc(display_బహుళకం_లెక్క, పరిమాణం(screen_display_బహుళకం_t));
    ఒకవేళ (screen_display_modes == ఖాళీ) {
        తిరిగి false;
    }

    ఒకవేళ(screen_get_display_modes(screen_display, display_బహుళకం_లెక్క, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        తిరిగి false;
    }

    కొరకు (సూచీ = 0; సూచీ < display_బహుళకం_లెక్క; సూచీ++) {
        display_బహుళకం_దత్తాంశం = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
        ఒకవేళ (display_బహుళకం_దత్తాంశం == ఖాళీ) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            తిరిగి false;
        }

        SDL_zero(display_బహుళకం_2);
        display_బహుళకం_2.w = screen_display_modes[సూచీ].వెడల్పు;
        display_బహుళకం_2.h = screen_display_modes[సూచీ].ఎత్తు;
        display_బహుళకం_2.pixel_density = 1.0;
        display_బహుళకం_2.అంతర్గత = display_బహుళకం_దత్తాంశం;

        ఒకవేళ (screen_display_modes[సూచీ].flags & SCREEN_DISPLAY_బహుళకం_REFRESH_VALID) {
            screen_refresh_రేటు = screen_display_modes[సూచీ].refresh;
        } లేకపోతే {
            // Fallback
            screen_refresh_రేటు = 60;
        }
        ఒకవేళ (screen_display_modes[సూచీ].flags & SCREEN_DISPLAY_బహుళకం_FORMAT_VALID) {
            screen_format = screen_display_modes[సూచీ].format;
        } లేకపోతే {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_బహుళకం_2.refresh_రేటు = screen_refresh_రేటు;
        display_బహుళకం_2.format = screen_గమ్యం_Pixel_Format(screen_format);
        display_బహుళకం_దత్తాంశం->screen_format = screen_format;
        display_బహుళకం_దత్తాంశం->screen_display_బహుళకం = screen_display_modes[సూచీ];

        // This op can fail if the mode already exists.
        SDL_కూడు_Fullscreen_Display_బహుళకం(display, &display_బహుళకం_2);
    }

    SDL_free(screen_display_modes);

    తిరిగి true;
}

#ఒకవేళ 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Display_దత్తాంశం     *display_దత్తాంశం = display->అంతర్గత;
    SDL_Display_బహుళకం_దత్తాంశం *display_బహుళకం_దత్తాంశం = బహుళకం->అంతర్గత;

    ఒకవేళ ((display_దత్తాంశం == ఖాళీ) || (display_బహుళకం_దత్తాంశం == ఖాళీ)) {
        తిరిగి false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    ఒకవేళ (screen_సమితి_display_property_iv(display_దత్తాంశం->screen_display,
        SCREEN_PROPERTY_బహుళకం, (పూర్ణాంకం *)&display_బహుళకం_దత్తాంశం->screen_display_బహుళకం.సూచీ) < 0) {
        తిరిగి false;
    }

    తిరిగి true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_దత్తాంశం *దత్తాంశం = display->అంతర్గత;
    పూర్ణాంకం             కొలత[2] = { 0, 0 };

    ఒకవేళ (దత్తాంశం == ఖాళీ) {
        తిరిగి false;
    }

    ఒకవేళ (screen_get_display_property_iv(దత్తాంశం->screen_display, SCREEN_PROPERTY_కొలత, కొలత) < 0) {
        తిరిగి false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = కొలత[0];
    rect->h = కొలత[1];
    తిరిగి true;
}
#లేకపోతే
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ఒకవేళ (display->current_బహుళకం == ఖాళీ) {
        తిరిగి false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    ఒకవేళ (display->fullscreen_కిటికీ &&
        display->fullscreen_కిటికీ->fullscreen_exclusive &&
        display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.w != 0 &&
        display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.h != 0) {
        rect->w = display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.w;
        rect->h = display->fullscreen_కిటికీ->current_fullscreen_బహుళకం.h;
    } లేకపోతే {
        rect->w = display->current_బహుళకం->w;
        rect->h = display->current_బహుళకం->h;
    }
    తిరిగి true;
}
#అయితే_ముగింపు

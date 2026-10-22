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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_windowevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_qnx.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>

// All indices not already assigned will be zero'd to SDL_PIXELFORMAT_UNKNOWN.
ਸਥਿਰ ਅਚਲ SDL_PixelFormat _format_map[] = {
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

SDL_PixelFormat screen_ਮੰਜ਼ਿਲ_Pixel_Format(ਪੂਰਨ screen_format)
{
    ਜੇ ((screen_format < 0) || (screen_format >= SDL_arraysize(_format_map))) {
        ਵਾਪਸ SDL_PIXELFORMAT_UNKNOWN;
    }

    ਵਾਪਸ _format_map[screen_format];
}

bool QNX_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਅੰਕੜੇ     *display_ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ     display_ਬਹੁਲਕ_2;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *display_ਬਹੁਲਕ_ਅੰਕੜੇ;

    ਪੂਰਨ ਸੂਚਕਾਂਕ;
    ਪੂਰਨ display_ਬਹੁਲਕ_ਗਿਣਤੀ;

    screen_display_t      screen_display;
    screen_display_ਬਹੁਲਕ_t *screen_display_modes;
    ਪੂਰਨ                   screen_format;
    ਪੂਰਨ                   screen_refresh_ਦਰ;

    ਜੇ (display_ਅੰਕੜੇ == ਨਿਰਾ) {
        ਵਾਪਸ false;
    }
    screen_display = display_ਅੰਕੜੇ->screen_display;

    /* create SDL display imodes based on display mode info from the display */
    ਜੇ (screen_get_display_property_iv(screen_display, SCREEN_PROPERTY_ਬਹੁਲਕ_ਗਿਣਤੀ, &display_ਬਹੁਲਕ_ਗਿਣਤੀ) < 0) {
        ਵਾਪਸ false;
    }

    screen_display_modes = SDL_calloc(display_ਬਹੁਲਕ_ਗਿਣਤੀ, ਆਕਾਰ(screen_display_ਬਹੁਲਕ_t));
    ਜੇ (screen_display_modes == ਨਿਰਾ) {
        ਵਾਪਸ false;
    }

    ਜੇ(screen_get_display_modes(screen_display, display_ਬਹੁਲਕ_ਗਿਣਤੀ, screen_display_modes) < 0) {
        SDL_free(screen_display_modes);
        ਵਾਪਸ false;
    }

    ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < display_ਬਹੁਲਕ_ਗਿਣਤੀ; ਸੂਚਕਾਂਕ++) {
        display_ਬਹੁਲਕ_ਅੰਕੜੇ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
        ਜੇ (display_ਬਹੁਲਕ_ਅੰਕੜੇ == ਨਿਰਾ) {
            // Not much we can do about the objs we've already created at this point.
            SDL_free(screen_display_modes);
            ਵਾਪਸ false;
        }

        SDL_zero(display_ਬਹੁਲਕ_2);
        display_ਬਹੁਲਕ_2.w = screen_display_modes[ਸੂਚਕਾਂਕ].ਚੌੜਾਈ;
        display_ਬਹੁਲਕ_2.h = screen_display_modes[ਸੂਚਕਾਂਕ].ਉਚਾਈ;
        display_ਬਹੁਲਕ_2.pixel_density = 1.0;
        display_ਬਹੁਲਕ_2.ਅੰਦਰੂਨੀ = display_ਬਹੁਲਕ_ਅੰਕੜੇ;

        ਜੇ (screen_display_modes[ਸੂਚਕਾਂਕ].flags & SCREEN_DISPLAY_ਬਹੁਲਕ_REFRESH_VALID) {
            screen_refresh_ਦਰ = screen_display_modes[ਸੂਚਕਾਂਕ].refresh;
        } ਨਹੀਂਤਾਂ {
            // Fallback
            screen_refresh_ਦਰ = 60;
        }
        ਜੇ (screen_display_modes[ਸੂਚਕਾਂਕ].flags & SCREEN_DISPLAY_ਬਹੁਲਕ_FORMAT_VALID) {
            screen_format = screen_display_modes[ਸੂਚਕਾਂਕ].format;
        } ਨਹੀਂਤਾਂ {
            // Fallback
            screen_format = SCREEN_FORMAT_RGBX8888;
        }
        display_ਬਹੁਲਕ_2.refresh_ਦਰ = screen_refresh_ਦਰ;
        display_ਬਹੁਲਕ_2.format = screen_ਮੰਜ਼ਿਲ_Pixel_Format(screen_format);
        display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_format = screen_format;
        display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_display_ਬਹੁਲਕ = screen_display_modes[ਸੂਚਕਾਂਕ];

        // This op can fail if the mode already exists.
        SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &display_ਬਹੁਲਕ_2);
    }

    SDL_free(screen_display_modes);

    ਵਾਪਸ true;
}

#ਜੇ 0
// FIXME: This seems to invalidate the screen_display_t, causing issues with the
// (get|set)_display_property_*() apis. For now, mode switching is emulated
// instead.
bool QNX_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਅੰਕੜੇ     *display_ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *display_ਬਹੁਲਕ_ਅੰਕੜੇ = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;

    ਜੇ ((display_ਅੰਕੜੇ == ਨਿਰਾ) || (display_ਬਹੁਲਕ_ਅੰਕੜੇ == ਨਿਰਾ)) {
        ਵਾਪਸ false;
    }

    // TODO: May need to call glInitConfig and screen_create_window_buffers.
    ਜੇ (screen_ਸੈੱਟ_display_property_iv(display_ਅੰਕੜੇ->screen_display,
        SCREEN_PROPERTY_ਬਹੁਲਕ, (ਪੂਰਨ *)&display_ਬਹੁਲਕ_ਅੰਕੜੇ->screen_display_ਬਹੁਲਕ.ਸੂਚਕਾਂਕ) < 0) {
        ਵਾਪਸ false;
    }

    ਵਾਪਸ true;
}

bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = display->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ             ਮਾਪ[2] = { 0, 0 };

    ਜੇ (ਅੰਕੜੇ == ਨਿਰਾ) {
        ਵਾਪਸ false;
    }

    ਜੇ (screen_get_display_property_iv(ਅੰਕੜੇ->screen_display, SCREEN_PROPERTY_ਮਾਪ, ਮਾਪ) < 0) {
        ਵਾਪਸ false;
    }

    rect->x = 0;
    rect->y = 0;
    rect->w = ਮਾਪ[0];
    rect->h = ਮਾਪ[1];
    ਵਾਪਸ true;
}
#ਨਹੀਂਤਾਂ
bool QNX_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    ਜੇ (display->current_ਬਹੁਲਕ == ਨਿਰਾ) {
        ਵਾਪਸ false;
    }

    rect->x = 0;
    rect->y = 0;

    // When an emulated, exclusive fullscreen window has focus, treat the mode dimensions as the display bounds.
    ਜੇ (display->fullscreen_ਖਿੜਕੀ &&
        display->fullscreen_ਖਿੜਕੀ->fullscreen_exclusive &&
        display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w != 0 &&
        display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h != 0) {
        rect->w = display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w;
        rect->h = display->fullscreen_ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h;
    } ਨਹੀਂਤਾਂ {
        rect->w = display->current_ਬਹੁਲਕ->w;
        rect->h = display->current_ਬਹੁਲਕ->h;
    }
    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ

/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#அந்தர்பாவ "SDL_windowsvideo.h"
#அந்தர்பாவ "SDL_windowsshape.h"


நிலையான வெறுமை AddRegion(HRGN *mask, முழு x1, முழு y1, முழு x2, முழு y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    எனில் (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } இல்லையெனில் {
        *mask = region;
    }
}

நிலையான HRGN GenerateSpanListRegion(SDL_Surface *shape, முழு offset_x, முழு offset_y)
{
    HRGN mask = வெற்று;
    முழு x, y;
    முழு span_start = -1;

    க்கு (y = 0; y < shape->h; ++y) {
        மாறிலி Uint8 *a = (மாறிலி Uint8 *)shape->pixels + y * shape->pitch;
        க்கு (x = 0; x < shape->w; ++x) {
            எனில் (*a == SDL_ALPHA_TRANSPARENT) {
                எனில் (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } இல்லையெனில் {
                எனில் (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        எனில் (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    திரும்பு mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = வெற்று;

    // Generate a set of spans for the region
    எனில் (shape) {
        SDL_Surface *stretched = வெற்று;
        RECT rect;

        எனில் (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            எனில் (!stretched) {
                திரும்பு false;
            }
            எனில் (!SDL_StretchSurface(shape, வெற்று, stretched, வெற்று, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                திரும்பு false;
            }
            shape = stretched;
        }

        rect.உச்சி = 0;
        rect.இடது = 0;
        rect.bottom = 0;
        rect.வலது = 0;
        எனில் (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.இடது, -rect.உச்சி);

        எனில் (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.இடது + shape->w + rect.வலது + 1, -rect.உச்சி + 1);
            // left
            AddRegion(&mask, 0, -rect.உச்சி, -rect.இடது + 1, -rect.உச்சி + shape->h + 1);
            // right
            AddRegion(&mask, -rect.இடது + shape->w, -rect.உச்சி, -rect.இடது + shape->w + rect.வலது + 1, -rect.உச்சி + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.உச்சி + shape->h, -rect.இடது + shape->w + rect.வலது + 1, -rect.உச்சி + shape->h + rect.bottom + 1);
        }

        எனில் (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    எனில் (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        திரும்பு WIN_SetError("SetWindowRgn failed");
    }
    திரும்பு true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsshape.h"


ساكن فراغ AddRegion(HRGN *mask, صحيح x1, صحيح y1, صحيح x2, صحيح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    إذا (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } وإلا {
        *mask = region;
    }
}

ساكن HRGN GenerateSpanListRegion(SDL_Surface *shape, صحيح offset_x, صحيح offset_y)
{
    HRGN mask = عدم;
    صحيح x, y;
    صحيح span_start = -1;

    لكل (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        لكل (x = 0; x < shape->w; ++x) {
            إذا (*a == SDL_ALPHA_TRANSPARENT) {
                إذا (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } وإلا {
                إذا (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        إذا (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    أرجع mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = عدم;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        RECT rect;

        إذا (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            إذا (!stretched) {
                أرجع false;
            }
            إذا (!SDL_StretchSurface(shape, عدم, stretched, عدم, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                أرجع false;
            }
            shape = stretched;
        }

        rect.اتس = 0;
        rect.کيري = 0;
        rect.bottom = 0;
        rect.کانن = 0;
        إذا (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.کيري, -rect.اتس);

        إذا (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.کيري + shape->w + rect.کانن + 1, -rect.اتس + 1);
            // left
            AddRegion(&mask, 0, -rect.اتس, -rect.کيري + 1, -rect.اتس + shape->h + 1);
            // right
            AddRegion(&mask, -rect.کيري + shape->w, -rect.اتس, -rect.کيري + shape->w + rect.کانن + 1, -rect.اتس + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.اتس + shape->h, -rect.کيري + shape->w + rect.کانن + 1, -rect.اتس + shape->h + rect.bottom + 1);
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    إذا (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        أرجع WIN_SetError("SetWindowRgn failed");
    }
    أرجع true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

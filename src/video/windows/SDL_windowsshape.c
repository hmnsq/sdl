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
#include "SDL_internal.h"

#ꦪꦼꦤ꧀ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#include "SDL_windowsvideo.h"
#include "SDL_windowsshape.h"


static void AddRegion(HRGN *mask, puur_naa_nka x1, puur_naa_nka y1, puur_naa_nka x2, puur_naa_nka y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ꦪꦼꦤ꧀ (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } ꦭꦶꦪ {
        *mask = region;
    }
}

static HRGN GenerateSpanListRegion(SDL_Surface *shape, puur_naa_nka offset_x, puur_naa_nka offset_y)
{
    HRGN mask = NULL;
    puur_naa_nka x, y;
    puur_naa_nka span_start = -1;

    ꦏꦁꦒꦺꦴ (y = 0; y < shape->h; ++y) {
        const Uint8 *a = (const Uint8 *)shape->pixels + y * shape->pitch;
        ꦏꦁꦒꦺꦴ (x = 0; x < shape->w; ++x) {
            ꦪꦼꦤ꧀ (*a == SDL_ALPHA_TRANSPARENT) {
                ꦪꦼꦤ꧀ (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } ꦭꦶꦪ {
                ꦪꦼꦤ꧀ (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        ꦪꦼꦤ꧀ (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    ꦮꦭꦶ mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = NULL;

    // Generate a set of spans for the region
    ꦪꦼꦤ꧀ (shape) {
        SDL_Surface *stretched = NULL;
        RECT rect;

        ꦪꦼꦤ꧀ (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            ꦪꦼꦤ꧀ (!stretched) {
                ꦮꦭꦶ false;
            }
            ꦪꦼꦤ꧀ (!SDL_StretchSurface(shape, NULL, stretched, NULL, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                ꦮꦭꦶ false;
            }
            shape = stretched;
        }

        rect.top = 0;
        rect.left = 0;
        rect.bottom = 0;
        rect.right = 0;
        ꦪꦼꦤ꧀ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.left, -rect.top);

        ꦪꦼꦤ꧀ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.left + shape->w + rect.right + 1, -rect.top + 1);
            // left
            AddRegion(&mask, 0, -rect.top, -rect.left + 1, -rect.top + shape->h + 1);
            // right
            AddRegion(&mask, -rect.left + shape->w, -rect.top, -rect.left + shape->w + rect.right + 1, -rect.top + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.top + shape->h, -rect.left + shape->w + rect.right + 1, -rect.top + shape->h + rect.bottom + 1);
        }

        ꦪꦼꦤ꧀ (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ꦪꦼꦤ꧀ (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        ꦮꦭꦶ WIN_SetError("SetWindowRgn failed");
    }
    ꦮꦭꦶ true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

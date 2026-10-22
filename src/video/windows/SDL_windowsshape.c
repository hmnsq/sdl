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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#અન્તર્ભાવ "SDL_windowsvideo.h"
#અન્તર્ભાવ "SDL_windowsshape.h"


સ્થિર શૂન્ય AddRegion(HRGN *mask, પૂર્ણાંક x1, પૂર્ણાંક y1, પૂર્ણાંક x2, પૂર્ણાંક y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    જો (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } નહીંતર {
        *mask = region;
    }
}

સ્થિર HRGN GenerateSpanListRegion(SDL_Surface *shape, પૂર્ણાંક offset_x, પૂર્ણાંક offset_y)
{
    HRGN mask = ખાલી;
    પૂર્ણાંક x, y;
    પૂર્ણાંક span_start = -1;

    માટે (y = 0; y < shape->h; ++y) {
        અચલ Uint8 *a = (અચલ Uint8 *)shape->pixels + y * shape->pitch;
        માટે (x = 0; x < shape->w; ++x) {
            જો (*a == SDL_ALPHA_TRANSPARENT) {
                જો (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } નહીંતર {
                જો (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        જો (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    પાછા mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = ખાલી;

    // Generate a set of spans for the region
    જો (shape) {
        SDL_Surface *stretched = ખાલી;
        RECT rect;

        જો (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            જો (!stretched) {
                પાછા false;
            }
            જો (!SDL_StretchSurface(shape, ખાલી, stretched, ખાલી, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                પાછા false;
            }
            shape = stretched;
        }

        rect.ટોચ = 0;
        rect.ડાબું = 0;
        rect.bottom = 0;
        rect.જમણું = 0;
        જો (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.ડાબું, -rect.ટોચ);

        જો (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.ડાબું + shape->w + rect.જમણું + 1, -rect.ટોચ + 1);
            // left
            AddRegion(&mask, 0, -rect.ટોચ, -rect.ડાબું + 1, -rect.ટોચ + shape->h + 1);
            // right
            AddRegion(&mask, -rect.ડાબું + shape->w, -rect.ટોચ, -rect.ડાબું + shape->w + rect.જમણું + 1, -rect.ટોચ + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.ટોચ + shape->h, -rect.ડાબું + shape->w + rect.જમણું + 1, -rect.ટોચ + shape->h + rect.bottom + 1);
        }

        જો (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    જો (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        પાછા WIN_SetError("SetWindowRgn failed");
    }
    પાછા true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

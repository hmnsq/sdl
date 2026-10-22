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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಯದಿ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsshape.h"


ಸ್ಥಿರ ಶೂನ್ಯ AddRegion(HRGN *mask, ಪೂರ್ಣಾಙ್ಕ x1, ಪೂರ್ಣಾಙ್ಕ y1, ಪೂರ್ಣಾಙ್ಕ x2, ಪೂರ್ಣಾಙ್ಕ y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ಯದಿ (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } ಅನ್ಯಥಾ {
        *mask = region;
    }
}

ಸ್ಥಿರ HRGN GenerateSpanListRegion(SDL_Surface *shape, ಪೂರ್ಣಾಙ್ಕ offset_x, ಪೂರ್ಣಾಙ್ಕ offset_y)
{
    HRGN mask = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ x, y;
    ಪೂರ್ಣಾಙ್ಕ span_start = -1;

    ಪ್ರತಿ (y = 0; y < shape->h; ++y) {
        ಧ್ರುವ Uint8 *a = (ಧ್ರುವ Uint8 *)shape->pixels + y * shape->pitch;
        ಪ್ರತಿ (x = 0; x < shape->w; ++x) {
            ಯದಿ (*a == SDL_ALPHA_TRANSPARENT) {
                ಯದಿ (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } ಅನ್ಯಥಾ {
                ಯದಿ (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        ಯದಿ (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    ಪ್ರತ್ಯಾಗಮ mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = ರಿಕ್ತ;

    // Generate a set of spans for the region
    ಯದಿ (shape) {
        SDL_Surface *stretched = ರಿಕ್ತ;
        RECT rect;

        ಯದಿ (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            ಯದಿ (!stretched) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            ಯದಿ (!SDL_StretchSurface(shape, ರಿಕ್ತ, stretched, ರಿಕ್ತ, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                ಪ್ರತ್ಯಾಗಮ false;
            }
            shape = stretched;
        }

        rect.ತುದಿ = 0;
        rect.ಎಡ = 0;
        rect.bottom = 0;
        rect.ಬಲ = 0;
        ಯದಿ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.ಎಡ, -rect.ತುದಿ);

        ಯದಿ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.ಎಡ + shape->w + rect.ಬಲ + 1, -rect.ತುದಿ + 1);
            // left
            AddRegion(&mask, 0, -rect.ತುದಿ, -rect.ಎಡ + 1, -rect.ತುದಿ + shape->h + 1);
            // right
            AddRegion(&mask, -rect.ಎಡ + shape->w, -rect.ತುದಿ, -rect.ಎಡ + shape->w + rect.ಬಲ + 1, -rect.ತುದಿ + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.ತುದಿ + shape->h, -rect.ಎಡ + shape->w + rect.ಬಲ + 1, -rect.ತುದಿ + shape->h + rect.bottom + 1);
        }

        ಯದಿ (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ಯದಿ (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        ಪ್ರತ್ಯಾಗಮ WIN_SetError("SetWindowRgn failed");
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

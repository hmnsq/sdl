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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ଅନ୍ତର୍ଭାଵ "SDL_windowsvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_windowsshape.h"


ସ୍ଥିର ଶୂନ୍ୟ AddRegion(HRGN *mask, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ଯଦି (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } ଅନ୍ୟଥା {
        *mask = region;
    }
}

ସ୍ଥିର HRGN GenerateSpanListRegion(SDL_Surface *shape, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_y)
{
    HRGN mask = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା span_start = -1;

    ପାଇଁ (y = 0; y < shape->h; ++y) {
        ଅଚଳ Uint8 *a = (ଅଚଳ Uint8 *)shape->pixels + y * shape->pitch;
        ପାଇଁ (x = 0; x < shape->w; ++x) {
            ଯଦି (*a == SDL_ALPHA_TRANSPARENT) {
                ଯଦି (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } ଅନ୍ୟଥା {
                ଯଦି (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        ଯଦି (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    ଫେରନ୍ତୁ mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = ଖାଲି;

    // Generate a set of spans for the region
    ଯଦି (shape) {
        SDL_Surface *stretched = ଖାଲି;
        RECT rect;

        ଯଦି (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            ଯଦି (!stretched) {
                ଫେରନ୍ତୁ false;
            }
            ଯଦି (!SDL_StretchSurface(shape, ଖାଲି, stretched, ଖାଲି, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                ଫେରନ୍ତୁ false;
            }
            shape = stretched;
        }

        rect.ଶୀର୍ଷ = 0;
        rect.ବାମ = 0;
        rect.bottom = 0;
        rect.ଡାହାଣ = 0;
        ଯଦି (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.ବାମ, -rect.ଶୀର୍ଷ);

        ଯଦି (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.ବାମ + shape->w + rect.ଡାହାଣ + 1, -rect.ଶୀର୍ଷ + 1);
            // left
            AddRegion(&mask, 0, -rect.ଶୀର୍ଷ, -rect.ବାମ + 1, -rect.ଶୀର୍ଷ + shape->h + 1);
            // right
            AddRegion(&mask, -rect.ବାମ + shape->w, -rect.ଶୀର୍ଷ, -rect.ବାମ + shape->w + rect.ଡାହାଣ + 1, -rect.ଶୀର୍ଷ + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.ଶୀର୍ଷ + shape->h, -rect.ବାମ + shape->w + rect.ଡାହାଣ + 1, -rect.ଶୀର୍ଷ + shape->h + rect.bottom + 1);
        }

        ଯଦି (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ଯଦି (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        ଫେରନ୍ତୁ WIN_SetError("SetWindowRgn failed");
    }
    ଫେରନ୍ତୁ true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#অন্তর্ভাব "SDL_windowsvideo.h"
#অন্তর্ভাব "SDL_windowsshape.h"


স্থির শূন্য AddRegion(HRGN *mask, পূর্ণাঙ্ক x1, পূর্ণাঙ্ক y1, পূর্ণাঙ্ক x2, পূর্ণাঙ্ক y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    যদি (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } অন্যথা {
        *mask = region;
    }
}

স্থির HRGN GenerateSpanListRegion(SDL_Surface *shape, পূর্ণাঙ্ক offset_x, পূর্ণাঙ্ক offset_y)
{
    HRGN mask = রিক্ত;
    পূর্ণাঙ্ক x, y;
    পূর্ণাঙ্ক span_start = -1;

    প্রতি (y = 0; y < shape->h; ++y) {
        ধ্রুব Uint8 *a = (ধ্রুব Uint8 *)shape->pixels + y * shape->pitch;
        প্রতি (x = 0; x < shape->w; ++x) {
            যদি (*a == SDL_ALPHA_TRANSPARENT) {
                যদি (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } অন্যথা {
                যদি (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        যদি (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    প্রত্যাগম mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = রিক্ত;

    // Generate a set of spans for the region
    যদি (shape) {
        SDL_Surface *stretched = রিক্ত;
        RECT rect;

        যদি (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            যদি (!stretched) {
                প্রত্যাগম false;
            }
            যদি (!SDL_StretchSurface(shape, রিক্ত, stretched, রিক্ত, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                প্রত্যাগম false;
            }
            shape = stretched;
        }

        rect.শীর্ষ = 0;
        rect.বাম = 0;
        rect.bottom = 0;
        rect.ডান = 0;
        যদি (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.বাম, -rect.শীর্ষ);

        যদি (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.বাম + shape->w + rect.ডান + 1, -rect.শীর্ষ + 1);
            // left
            AddRegion(&mask, 0, -rect.শীর্ষ, -rect.বাম + 1, -rect.শীর্ষ + shape->h + 1);
            // right
            AddRegion(&mask, -rect.বাম + shape->w, -rect.শীর্ষ, -rect.বাম + shape->w + rect.ডান + 1, -rect.শীর্ষ + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.শীর্ষ + shape->h, -rect.বাম + shape->w + rect.ডান + 1, -rect.শীর্ষ + shape->h + rect.bottom + 1);
        }

        যদি (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    যদি (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        প্রত্যাগম WIN_SetError("SetWindowRgn failed");
    }
    প্রত্যাগম true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

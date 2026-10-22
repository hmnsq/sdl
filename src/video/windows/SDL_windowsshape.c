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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowsshape.h"


ایستا تهی AddRegion(HRGN *mask, صحیح x1, صحیح y1, صحیح x2, صحیح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    اگر (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } وگرنه {
        *mask = region;
    }
}

ایستا HRGN GenerateSpanListRegion(SDL_Surface *shape, صحیح offset_x, صحیح offset_y)
{
    HRGN mask = پوچ;
    صحیح x, y;
    صحیح span_start = -1;

    برای (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        برای (x = 0; x < shape->w; ++x) {
            اگر (*a == SDL_ALPHA_TRANSPARENT) {
                اگر (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } وگرنه {
                اگر (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        اگر (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    بازگشت mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = پوچ;

    // Generate a set of spans for the region
    اگر (shape) {
        SDL_Surface *stretched = پوچ;
        RECT rect;

        اگر (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            اگر (!stretched) {
                بازگشت false;
            }
            اگر (!SDL_StretchSurface(shape, پوچ, stretched, پوچ, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                بازگشت false;
            }
            shape = stretched;
        }

        rect.بالاترین = 0;
        rect.چپ = 0;
        rect.bottom = 0;
        rect.راست = 0;
        اگر (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.چپ, -rect.بالاترین);

        اگر (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.چپ + shape->w + rect.راست + 1, -rect.بالاترین + 1);
            // left
            AddRegion(&mask, 0, -rect.بالاترین, -rect.چپ + 1, -rect.بالاترین + shape->h + 1);
            // right
            AddRegion(&mask, -rect.چپ + shape->w, -rect.بالاترین, -rect.چپ + shape->w + rect.راست + 1, -rect.بالاترین + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.بالاترین + shape->h, -rect.چپ + shape->w + rect.راست + 1, -rect.بالاترین + shape->h + rect.bottom + 1);
        }

        اگر (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    اگر (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        بازگشت WIN_SetError("SetWindowRgn failed");
    }
    بازگشت true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

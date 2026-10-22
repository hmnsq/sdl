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

#ถ้า defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#include "SDL_windowsvideo.h"
#include "SDL_windowsshape.h"


static void AddRegion(HRGN *mask, จำนวนเต็ม x1, จำนวนเต็ม y1, จำนวนเต็ม x2, จำนวนเต็ม y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ถ้า (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } มิฉะนั้น {
        *mask = region;
    }
}

static HRGN GenerateSpanListRegion(SDL_Surface *shape, จำนวนเต็ม offset_x, จำนวนเต็ม offset_y)
{
    HRGN mask = NULL;
    จำนวนเต็ม x, y;
    จำนวนเต็ม span_start = -1;

    สำหรับ (y = 0; y < shape->h; ++y) {
        const Uint8 *a = (const Uint8 *)shape->pixels + y * shape->pitch;
        สำหรับ (x = 0; x < shape->w; ++x) {
            ถ้า (*a == SDL_ALPHA_TRANSPARENT) {
                ถ้า (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } มิฉะนั้น {
                ถ้า (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        ถ้า (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    คืน mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = NULL;

    // Generate a set of spans for the region
    ถ้า (shape) {
        SDL_Surface *stretched = NULL;
        RECT rect;

        ถ้า (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            ถ้า (!stretched) {
                คืน false;
            }
            ถ้า (!SDL_StretchSurface(shape, NULL, stretched, NULL, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                คืน false;
            }
            shape = stretched;
        }

        rect.top = 0;
        rect.left = 0;
        rect.bottom = 0;
        rect.right = 0;
        ถ้า (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.left, -rect.top);

        ถ้า (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
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

        ถ้า (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ถ้า (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        คืน WIN_SetError("SetWindowRgn failed");
    }
    คืน true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

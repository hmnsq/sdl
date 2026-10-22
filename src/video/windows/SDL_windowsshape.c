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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowsshape.h"


अटल व्योम AddRegion(HRGN *mask, पूर्णांक x1, पूर्णांक y1, पूर्णांक x2, पूर्णांक y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    अगर (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } अन्यथा {
        *mask = region;
    }
}

अटल HRGN GenerateSpanListRegion(SDL_Surface *shape, पूर्णांक offset_x, पूर्णांक offset_y)
{
    HRGN mask = शून्य;
    पूर्णांक x, y;
    पूर्णांक span_start = -1;

    क्रम (y = 0; y < shape->h; ++y) {
        स्थिर Uint8 *a = (स्थिर Uint8 *)shape->pixels + y * shape->pitch;
        क्रम (x = 0; x < shape->w; ++x) {
            अगर (*a == SDL_ALPHA_TRANSPARENT) {
                अगर (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } अन्यथा {
                अगर (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        अगर (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    वापस mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HRGN mask = शून्य;

    // Generate a set of spans for the region
    अगर (shape) {
        SDL_Surface *stretched = शून्य;
        RECT rect;

        अगर (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            अगर (!stretched) {
                वापस false;
            }
            अगर (!SDL_StretchSurface(shape, शून्य, stretched, शून्य, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                वापस false;
            }
            shape = stretched;
        }

        rect.शीर्ष = 0;
        rect.बायाँ = 0;
        rect.bottom = 0;
        rect.दायाँ = 0;
        अगर (!(SDL_GetWindowFlags(तथ्य->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(तथ्य->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.बायाँ, -rect.शीर्ष);

        अगर (!(SDL_GetWindowFlags(तथ्य->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.बायाँ + shape->w + rect.दायाँ + 1, -rect.शीर्ष + 1);
            // left
            AddRegion(&mask, 0, -rect.शीर्ष, -rect.बायाँ + 1, -rect.शीर्ष + shape->h + 1);
            // right
            AddRegion(&mask, -rect.बायाँ + shape->w, -rect.शीर्ष, -rect.बायाँ + shape->w + rect.दायाँ + 1, -rect.शीर्ष + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.शीर्ष + shape->h, -rect.बायाँ + shape->w + rect.दायाँ + 1, -rect.शीर्ष + shape->h + rect.bottom + 1);
        }

        अगर (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    अगर (!SetWindowRgn(तथ्य->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        वापस WIN_SetError("SetWindowRgn failed");
    }
    वापस true;
}

#पूर्ण_अगर // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowsshape.h"


स्थिर शून्य AddRegion(HRGN *mask, पूर्णाङ्क x1, पूर्णाङ्क y1, पूर्णाङ्क x2, पूर्णाङ्क y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    यदि (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } अन्यथा {
        *mask = region;
    }
}

स्थिर HRGN GenerateSpanListRegion(SDL_Surface *shape, पूर्णाङ्क offset_x, पूर्णाङ्क offset_y)
{
    HRGN mask = रिक्त;
    पूर्णाङ्क x, y;
    पूर्णाङ्क span_start = -1;

    लागि (y = 0; y < shape->h; ++y) {
        अचर Uint8 *a = (अचर Uint8 *)shape->pixels + y * shape->pitch;
        लागि (x = 0; x < shape->w; ++x) {
            यदि (*a == SDL_ALPHA_TRANSPARENT) {
                यदि (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } अन्यथा {
                यदि (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        यदि (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    फर्काऊ mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = रिक्त;

    // Generate a set of spans for the region
    यदि (shape) {
        SDL_Surface *stretched = रिक्त;
        RECT rect;

        यदि (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            यदि (!stretched) {
                फर्काऊ false;
            }
            यदि (!SDL_StretchSurface(shape, रिक्त, stretched, रिक्त, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                फर्काऊ false;
            }
            shape = stretched;
        }

        rect.शीर्ष = 0;
        rect.बायाँ = 0;
        rect.bottom = 0;
        rect.दायाँ = 0;
        यदि (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.बायाँ, -rect.शीर्ष);

        यदि (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
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

        यदि (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    यदि (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        फर्काऊ WIN_SetError("SetWindowRgn failed");
    }
    फर्काऊ true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

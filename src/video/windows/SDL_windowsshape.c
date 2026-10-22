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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "SDL_windowsshape.h"


സ്ഥിതം ശൂന്യം AddRegion(HRGN *mask, പൂർണ്ണസംഖ്യ x1, പൂർണ്ണസംഖ്യ y1, പൂർണ്ണസംഖ്യ x2, പൂർണ്ണസംഖ്യ y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    എങ്കിൽ (*mask) {
        CombineRgn(*mask, *mask, region, RGN_OR);
        DeleteObject(region);
    } അല്ലെങ്കിൽ {
        *mask = region;
    }
}

സ്ഥിതം HRGN GenerateSpanListRegion(SDL_Surface *shape, പൂർണ്ണസംഖ്യ offset_x, പൂർണ്ണസംഖ്യ offset_y)
{
    HRGN mask = ശൂന്യ;
    പൂർണ്ണസംഖ്യ x, y;
    പൂർണ്ണസംഖ്യ span_start = -1;

    വേണ്ടി (y = 0; y < shape->h; ++y) {
        സ്ഥിരം Uint8 *a = (സ്ഥിരം Uint8 *)shape->pixels + y * shape->pitch;
        വേണ്ടി (x = 0; x < shape->w; ++x) {
            എങ്കിൽ (*a == SDL_ALPHA_TRANSPARENT) {
                എങ്കിൽ (span_start != -1) {
                    AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
                    span_start = -1;
                }
            } അല്ലെങ്കിൽ {
                എങ്കിൽ (span_start == -1) {
                    span_start = x;
                }
            }
            a += 4;
        }
        എങ്കിൽ (span_start != -1) {
            // Add the final span
            AddRegion(&mask, offset_x + span_start, offset_y + y, offset_x + x, offset_y + y + 1);
            span_start = -1;
        }
    }
    തിരികെ mask;
}

bool WIN_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    SDL_WindowData *data = window->internal;
    HRGN mask = ശൂന്യ;

    // Generate a set of spans for the region
    എങ്കിൽ (shape) {
        SDL_Surface *stretched = ശൂന്യ;
        RECT rect;

        എങ്കിൽ (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            എങ്കിൽ (!stretched) {
                തിരികെ false;
            }
            എങ്കിൽ (!SDL_StretchSurface(shape, ശൂന്യ, stretched, ശൂന്യ, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                തിരികെ false;
            }
            shape = stretched;
        }

        rect.മുകൾ = 0;
        rect.ഇടത് = 0;
        rect.bottom = 0;
        rect.വലത് = 0;
        എങ്കിൽ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            WIN_AdjustWindowRectForHWND(data->hwnd, &rect, 0);
        }

        mask = GenerateSpanListRegion(shape, -rect.ഇടത്, -rect.മുകൾ);

        എങ്കിൽ (!(SDL_GetWindowFlags(data->window) & SDL_WINDOW_BORDERLESS)) {
            // Add the window borders
            // top
            AddRegion(&mask, 0, 0, -rect.ഇടത് + shape->w + rect.വലത് + 1, -rect.മുകൾ + 1);
            // left
            AddRegion(&mask, 0, -rect.മുകൾ, -rect.ഇടത് + 1, -rect.മുകൾ + shape->h + 1);
            // right
            AddRegion(&mask, -rect.ഇടത് + shape->w, -rect.മുകൾ, -rect.ഇടത് + shape->w + rect.വലത് + 1, -rect.മുകൾ + shape->h + 1);
            // bottom
            AddRegion(&mask, 0, -rect.മുകൾ + shape->h, -rect.ഇടത് + shape->w + rect.വലത് + 1, -rect.മുകൾ + shape->h + rect.bottom + 1);
        }

        എങ്കിൽ (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    എങ്കിൽ (!SetWindowRgn(data->hwnd, mask, TRUE)) {
        DeleteObject(mask);
        തിരികെ WIN_SetError("SetWindowRgn failed");
    }
    തിരികെ true;
}

#endif // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

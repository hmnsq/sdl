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


स्थिर शून्य सङ्कलय_Region(HRGN *आवरणम्, पूर्णाङ्क x1, पूर्णाङ्क y1, पूर्णाङ्क x2, पूर्णाङ्क y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    यदि (*आवरणम्) {
        CombineRgn(*आवरणम्, *आवरणम्, region, RGN_OR);
        DeleteObject(region);
    } अन्यथा {
        *आवरणम् = region;
    }
}

स्थिर HRGN Generate_विस्तृतिः_List_Region(SDL_Surface *shape, पूर्णाङ्क विस्थापनम्_x, पूर्णाङ्क विस्थापनम्_y)
{
    HRGN आवरणम् = रिक्त;
    पूर्णाङ्क x, y;
    पूर्णाङ्क विस्तृतिः_start = -1;

    प्रति (y = 0; y < shape->h; ++y) {
        ध्रुव Uint8 *a = (ध्रुव Uint8 *)shape->pixels + y * shape->pitch;
        प्रति (x = 0; x < shape->w; ++x) {
            यदि (*a == SDL_ALPHA_TRANSPARENT) {
                यदि (विस्तृतिः_start != -1) {
                    सङ्कलय_Region(&आवरणम्, विस्थापनम्_x + विस्तृतिः_start, विस्थापनम्_y + y, विस्थापनम्_x + x, विस्थापनम्_y + y + 1);
                    विस्तृतिः_start = -1;
                }
            } अन्यथा {
                यदि (विस्तृतिः_start == -1) {
                    विस्तृतिः_start = x;
                }
            }
            a += 4;
        }
        यदि (विस्तृतिः_start != -1) {
            // Add the final span
            सङ्कलय_Region(&आवरणम्, विस्थापनम्_x + विस्तृतिः_start, विस्थापनम्_y + y, विस्थापनम्_x + x, विस्थापनम्_y + y + 1);
            विस्तृतिः_start = -1;
        }
    }
    प्रत्यागम आवरणम्;
}

bool WIN_Update_गवाक्षः_Shape(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *shape)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HRGN आवरणम् = रिक्त;

    // Generate a set of spans for the region
    यदि (shape) {
        SDL_Surface *stretched = रिक्त;
        RECT rect;

        यदि (shape->w != गवाक्षः->w || shape->h != गवाक्षः->h) {
            stretched = SDL_CreateSurfaceUninitialized(गवाक्षः->w, गवाक्षः->h, SDL_PIXELFORMAT_ARGB32);
            यदि (!stretched) {
                प्रत्यागम false;
            }
            यदि (!SDL_StretchSurface(shape, रिक्त, stretched, रिक्त, SDL_SCALEMODE_रैखिकम्)) {
                SDL_DestroySurface(stretched);
                प्रत्यागम false;
            }
            shape = stretched;
        }

        rect.शिखरम् = 0;
        rect.वामः = 0;
        rect.bottom = 0;
        rect.दक्षिणः = 0;
        यदि (!(SDL_Get_गवाक्षः_Flags(दत्त->गवाक्षः) & SDL_गवाक्षः_BORDERLESS)) {
            WIN_Adjust_गवाक्षः_Rect_For_HWND(दत्त->hwnd, &rect, 0);
        }

        आवरणम् = Generate_विस्तृतिः_List_Region(shape, -rect.वामः, -rect.शिखरम्);

        यदि (!(SDL_Get_गवाक्षः_Flags(दत्त->गवाक्षः) & SDL_गवाक्षः_BORDERLESS)) {
            // Add the window borders
            // top
            सङ्कलय_Region(&आवरणम्, 0, 0, -rect.वामः + shape->w + rect.दक्षिणः + 1, -rect.शिखरम् + 1);
            // left
            सङ्कलय_Region(&आवरणम्, 0, -rect.शिखरम्, -rect.वामः + 1, -rect.शिखरम् + shape->h + 1);
            // right
            सङ्कलय_Region(&आवरणम्, -rect.वामः + shape->w, -rect.शिखरम्, -rect.वामः + shape->w + rect.दक्षिणः + 1, -rect.शिखरम् + shape->h + 1);
            // bottom
            सङ्कलय_Region(&आवरणम्, 0, -rect.शिखरम् + shape->h, -rect.वामः + shape->w + rect.दक्षिणः + 1, -rect.शिखरम् + shape->h + rect.bottom + 1);
        }

        यदि (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    यदि (!समुच्चयः_गवाक्षः_Rgn(दत्त->hwnd, आवरणम्, TRUE)) {
        DeleteObject(आवरणम्);
        प्रत्यागम WIN_समुच्चयः_Error("SetWindowRgn failed");
    }
    प्रत्यागम true;
}

#यदि_अन्तः // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

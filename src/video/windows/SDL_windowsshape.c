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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsshape.h"


ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Region(HRGN *ಮುಖವಾಡ, ಪೂರ್ಣಾಂಕ x1, ಪೂರ್ಣಾಂಕ y1, ಪೂರ್ಣಾಂಕ x2, ಪೂರ್ಣಾಂಕ y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ಆದರೆ (*ಮುಖವಾಡ) {
        CombineRgn(*ಮುಖವಾಡ, *ಮುಖವಾಡ, region, RGN_OR);
        DeleteObject(region);
    } ಇಲ್ಲದಿದ್ದರೆ {
        *ಮುಖವಾಡ = region;
    }
}

ಸ್ಥಿರ HRGN Generate_ಹರವು_List_Region(SDL_Surface *shape, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_x, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_y)
{
    HRGN ಮುಖವಾಡ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ x, y;
    ಪೂರ್ಣಾಂಕ ಹರವು_ಆರಂಭ = -1;

    ಗಾಗಿ (y = 0; y < shape->h; ++y) {
        ಸ್ಥಿರಾಂಕ Uint8 *a = (ಸ್ಥಿರಾಂಕ Uint8 *)shape->pixels + y * shape->pitch;
        ಗಾಗಿ (x = 0; x < shape->w; ++x) {
            ಆದರೆ (*a == SDL_ALPHA_TRANSPARENT) {
                ಆದರೆ (ಹರವು_ಆರಂಭ != -1) {
                    ಕೂಡಿಸು_Region(&ಮುಖವಾಡ, ಸ್ಥಾನಾಂತರ_x + ಹರವು_ಆರಂಭ, ಸ್ಥಾನಾಂತರ_y + y, ಸ್ಥಾನಾಂತರ_x + x, ಸ್ಥಾನಾಂತರ_y + y + 1);
                    ಹರವು_ಆರಂಭ = -1;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (ಹರವು_ಆರಂಭ == -1) {
                    ಹರವು_ಆರಂಭ = x;
                }
            }
            a += 4;
        }
        ಆದರೆ (ಹರವು_ಆರಂಭ != -1) {
            // Add the final span
            ಕೂಡಿಸು_Region(&ಮುಖವಾಡ, ಸ್ಥಾನಾಂತರ_x + ಹರವು_ಆರಂಭ, ಸ್ಥಾನಾಂತರ_y + y, ಸ್ಥಾನಾಂತರ_x + x, ಸ್ಥಾನಾಂತರ_y + y + 1);
            ಹರವು_ಆರಂಭ = -1;
        }
    }
    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ;
}

bool WIN_Update_ಕಿಟಕಿ_Shape(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *shape)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HRGN ಮುಖವಾಡ = ಖಾಲಿ;

    // Generate a set of spans for the region
    ಆದರೆ (shape) {
        SDL_Surface *stretched = ಖಾಲಿ;
        RECT rect;

        ಆದರೆ (shape->w != ಕಿಟಕಿ->w || shape->h != ಕಿಟಕಿ->h) {
            stretched = SDL_CreateSurfaceUninitialized(ಕಿಟಕಿ->w, ಕಿಟಕಿ->h, SDL_PIXELFORMAT_ARGB32);
            ಆದರೆ (!stretched) {
                ಹಿಂತಿರುಗಿ false;
            }
            ಆದರೆ (!SDL_StretchSurface(shape, ಖಾಲಿ, stretched, ಖಾಲಿ, SDL_SCALEMODE_ರೇಖೀಯ)) {
                SDL_DestroySurface(stretched);
                ಹಿಂತಿರುಗಿ false;
            }
            shape = stretched;
        }

        rect.ತುದಿ = 0;
        rect.ಎಡ = 0;
        rect.bottom = 0;
        rect.ಬಲ = 0;
        ಆದರೆ (!(SDL_Get_ಕಿಟಕಿ_Flags(ದತ್ತಾಂಶ->ಕಿಟಕಿ) & SDL_ಕಿಟಕಿ_BORDERLESS)) {
            WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(ದತ್ತಾಂಶ->hwnd, &rect, 0);
        }

        ಮುಖವಾಡ = Generate_ಹರವು_List_Region(shape, -rect.ಎಡ, -rect.ತುದಿ);

        ಆದರೆ (!(SDL_Get_ಕಿಟಕಿ_Flags(ದತ್ತಾಂಶ->ಕಿಟಕಿ) & SDL_ಕಿಟಕಿ_BORDERLESS)) {
            // Add the window borders
            // top
            ಕೂಡಿಸು_Region(&ಮುಖವಾಡ, 0, 0, -rect.ಎಡ + shape->w + rect.ಬಲ + 1, -rect.ತುದಿ + 1);
            // left
            ಕೂಡಿಸು_Region(&ಮುಖವಾಡ, 0, -rect.ತುದಿ, -rect.ಎಡ + 1, -rect.ತುದಿ + shape->h + 1);
            // right
            ಕೂಡಿಸು_Region(&ಮುಖವಾಡ, -rect.ಎಡ + shape->w, -rect.ತುದಿ, -rect.ಎಡ + shape->w + rect.ಬಲ + 1, -rect.ತುದಿ + shape->h + 1);
            // bottom
            ಕೂಡಿಸು_Region(&ಮುಖವಾಡ, 0, -rect.ತುದಿ + shape->h, -rect.ಎಡ + shape->w + rect.ಬಲ + 1, -rect.ತುದಿ + shape->h + rect.bottom + 1);
        }

        ಆದರೆ (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ಆದರೆ (!ಗಣ_ಕಿಟಕಿ_Rgn(ದತ್ತಾಂಶ->hwnd, ಮುಖವಾಡ, TRUE)) {
        DeleteObject(ಮುಖವಾಡ);
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("SetWindowRgn failed");
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsshape.h"


ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Region(HRGN *ਨਕਾਬ, ਪੂਰਨ x1, ਪੂਰਨ y1, ਪੂਰਨ x2, ਪੂਰਨ y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ਜੇ (*ਨਕਾਬ) {
        CombineRgn(*ਨਕਾਬ, *ਨਕਾਬ, region, RGN_OR);
        DeleteObject(region);
    } ਨਹੀਂਤਾਂ {
        *ਨਕਾਬ = region;
    }
}

ਸਥਿਰ HRGN Generate_ਵਿਸਤਾਰ_List_Region(SDL_Surface *shape, ਪੂਰਨ ਵਿੱਥ_x, ਪੂਰਨ ਵਿੱਥ_y)
{
    HRGN ਨਕਾਬ = ਨਿਰਾ;
    ਪੂਰਨ x, y;
    ਪੂਰਨ ਵਿਸਤਾਰ_ਸ਼ੁਰੂ = -1;

    ਲਈ (y = 0; y < shape->h; ++y) {
        ਅਚਲ Uint8 *a = (ਅਚਲ Uint8 *)shape->pixels + y * shape->pitch;
        ਲਈ (x = 0; x < shape->w; ++x) {
            ਜੇ (*a == SDL_ALPHA_TRANSPARENT) {
                ਜੇ (ਵਿਸਤਾਰ_ਸ਼ੁਰੂ != -1) {
                    ਜੋੜੋ_Region(&ਨਕਾਬ, ਵਿੱਥ_x + ਵਿਸਤਾਰ_ਸ਼ੁਰੂ, ਵਿੱਥ_y + y, ਵਿੱਥ_x + x, ਵਿੱਥ_y + y + 1);
                    ਵਿਸਤਾਰ_ਸ਼ੁਰੂ = -1;
                }
            } ਨਹੀਂਤਾਂ {
                ਜੇ (ਵਿਸਤਾਰ_ਸ਼ੁਰੂ == -1) {
                    ਵਿਸਤਾਰ_ਸ਼ੁਰੂ = x;
                }
            }
            a += 4;
        }
        ਜੇ (ਵਿਸਤਾਰ_ਸ਼ੁਰੂ != -1) {
            // Add the final span
            ਜੋੜੋ_Region(&ਨਕਾਬ, ਵਿੱਥ_x + ਵਿਸਤਾਰ_ਸ਼ੁਰੂ, ਵਿੱਥ_y + y, ਵਿੱਥ_x + x, ਵਿੱਥ_y + y + 1);
            ਵਿਸਤਾਰ_ਸ਼ੁਰੂ = -1;
        }
    }
    ਵਾਪਸ ਨਕਾਬ;
}

bool WIN_Update_ਖਿੜਕੀ_Shape(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *shape)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HRGN ਨਕਾਬ = ਨਿਰਾ;

    // Generate a set of spans for the region
    ਜੇ (shape) {
        SDL_Surface *stretched = ਨਿਰਾ;
        RECT rect;

        ਜੇ (shape->w != ਖਿੜਕੀ->w || shape->h != ਖਿੜਕੀ->h) {
            stretched = SDL_CreateSurfaceUninitialized(ਖਿੜਕੀ->w, ਖਿੜਕੀ->h, SDL_PIXELFORMAT_ARGB32);
            ਜੇ (!stretched) {
                ਵਾਪਸ false;
            }
            ਜੇ (!SDL_StretchSurface(shape, ਨਿਰਾ, stretched, ਨਿਰਾ, SDL_SCALEMODE_ਰੇਖਿਕ)) {
                SDL_DestroySurface(stretched);
                ਵਾਪਸ false;
            }
            shape = stretched;
        }

        rect.ਸਿਖਰ = 0;
        rect.ਖੱਬਾ = 0;
        rect.bottom = 0;
        rect.ਸੱਜਾ = 0;
        ਜੇ (!(SDL_Get_ਖਿੜਕੀ_Flags(ਅੰਕੜੇ->ਖਿੜਕੀ) & SDL_ਖਿੜਕੀ_BORDERLESS)) {
            WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(ਅੰਕੜੇ->hwnd, &rect, 0);
        }

        ਨਕਾਬ = Generate_ਵਿਸਤਾਰ_List_Region(shape, -rect.ਖੱਬਾ, -rect.ਸਿਖਰ);

        ਜੇ (!(SDL_Get_ਖਿੜਕੀ_Flags(ਅੰਕੜੇ->ਖਿੜਕੀ) & SDL_ਖਿੜਕੀ_BORDERLESS)) {
            // Add the window borders
            // top
            ਜੋੜੋ_Region(&ਨਕਾਬ, 0, 0, -rect.ਖੱਬਾ + shape->w + rect.ਸੱਜਾ + 1, -rect.ਸਿਖਰ + 1);
            // left
            ਜੋੜੋ_Region(&ਨਕਾਬ, 0, -rect.ਸਿਖਰ, -rect.ਖੱਬਾ + 1, -rect.ਸਿਖਰ + shape->h + 1);
            // right
            ਜੋੜੋ_Region(&ਨਕਾਬ, -rect.ਖੱਬਾ + shape->w, -rect.ਸਿਖਰ, -rect.ਖੱਬਾ + shape->w + rect.ਸੱਜਾ + 1, -rect.ਸਿਖਰ + shape->h + 1);
            // bottom
            ਜੋੜੋ_Region(&ਨਕਾਬ, 0, -rect.ਸਿਖਰ + shape->h, -rect.ਖੱਬਾ + shape->w + rect.ਸੱਜਾ + 1, -rect.ਸਿਖਰ + shape->h + rect.bottom + 1);
        }

        ਜੇ (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ਜੇ (!ਸੈੱਟ_ਖਿੜਕੀ_Rgn(ਅੰਕੜੇ->hwnd, ਨਕਾਬ, TRUE)) {
        DeleteObject(ਨਕਾਬ);
        ਵਾਪਸ WIN_ਸੈੱਟ_Error("SetWindowRgn failed");
    }
    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

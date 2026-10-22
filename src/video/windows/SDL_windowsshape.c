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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsshape.h"


ساكن فراغ جوڙيو_Region(HRGN *نقاب, صحيح x1, صحيح y1, صحيح x2, صحيح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    إذا (*نقاب) {
        CombineRgn(*نقاب, *نقاب, region, RGN_OR);
        DeleteObject(region);
    } وإلا {
        *نقاب = region;
    }
}

ساكن HRGN Generate_وسعت_List_Region(SDL_Surface *shape, صحيح وٿي_x, صحيح وٿي_y)
{
    HRGN نقاب = عدم;
    صحيح x, y;
    صحيح وسعت_شروعات = -1;

    لكل (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        لكل (x = 0; x < shape->w; ++x) {
            إذا (*a == SDL_ALPHA_TRANSPARENT) {
                إذا (وسعت_شروعات != -1) {
                    جوڙيو_Region(&نقاب, وٿي_x + وسعت_شروعات, وٿي_y + y, وٿي_x + x, وٿي_y + y + 1);
                    وسعت_شروعات = -1;
                }
            } وإلا {
                إذا (وسعت_شروعات == -1) {
                    وسعت_شروعات = x;
                }
            }
            a += 4;
        }
        إذا (وسعت_شروعات != -1) {
            // Add the final span
            جوڙيو_Region(&نقاب, وٿي_x + وسعت_شروعات, وٿي_y + y, وٿي_x + x, وٿي_y + y + 1);
            وسعت_شروعات = -1;
        }
    }
    أرجع نقاب;
}

bool WIN_Update_دري_Shape(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *shape)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    HRGN نقاب = عدم;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        RECT rect;

        إذا (shape->w != دري->w || shape->h != دري->h) {
            stretched = SDL_CreateSurfaceUninitialized(دري->w, دري->h, SDL_PIXELFORMAT_ARGB32);
            إذا (!stretched) {
                أرجع false;
            }
            إذا (!SDL_StretchSurface(shape, عدم, stretched, عدم, SDL_SCALEMODE_لڪيري)) {
                SDL_DestroySurface(stretched);
                أرجع false;
            }
            shape = stretched;
        }

        rect.چوٽي = 0;
        rect.کاٻو = 0;
        rect.bottom = 0;
        rect.ساڄو = 0;
        إذا (!(SDL_Get_دري_Flags(معلومات->دري) & SDL_دري_BORDERLESS)) {
            WIN_Adjust_دري_Rect_For_HWND(معلومات->hwnd, &rect, 0);
        }

        نقاب = Generate_وسعت_List_Region(shape, -rect.کاٻو, -rect.چوٽي);

        إذا (!(SDL_Get_دري_Flags(معلومات->دري) & SDL_دري_BORDERLESS)) {
            // Add the window borders
            // top
            جوڙيو_Region(&نقاب, 0, 0, -rect.کاٻو + shape->w + rect.ساڄو + 1, -rect.چوٽي + 1);
            // left
            جوڙيو_Region(&نقاب, 0, -rect.چوٽي, -rect.کاٻو + 1, -rect.چوٽي + shape->h + 1);
            // right
            جوڙيو_Region(&نقاب, -rect.کاٻو + shape->w, -rect.چوٽي, -rect.کاٻو + shape->w + rect.ساڄو + 1, -rect.چوٽي + shape->h + 1);
            // bottom
            جوڙيو_Region(&نقاب, 0, -rect.چوٽي + shape->h, -rect.کاٻو + shape->w + rect.ساڄو + 1, -rect.چوٽي + shape->h + rect.bottom + 1);
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    إذا (!سيٽ_دري_Rgn(معلومات->hwnd, نقاب, TRUE)) {
        DeleteObject(نقاب);
        أرجع WIN_سيٽ_Error("SetWindowRgn failed");
    }
    أرجع true;
}

#جيڪڏهن_پورو // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

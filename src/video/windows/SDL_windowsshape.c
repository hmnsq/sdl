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


ساكن فراغ جوڑو_Region(HRGN *نقاب, صحيح x1, صحيح y1, صحيح x2, صحيح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    إذا (*نقاب) {
        CombineRgn(*نقاب, *نقاب, region, RGN_OR);
        DeleteObject(region);
    } وإلا {
        *نقاب = region;
    }
}

ساكن HRGN Generate_وسعت_List_Region(SDL_Surface *shape, صحيح وتھ_x, صحيح وتھ_y)
{
    HRGN نقاب = عدم;
    صحيح x, y;
    صحيح وسعت_شروع = -1;

    لكل (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        لكل (x = 0; x < shape->w; ++x) {
            إذا (*a == SDL_ALPHA_TRANSPARENT) {
                إذا (وسعت_شروع != -1) {
                    جوڑو_Region(&نقاب, وتھ_x + وسعت_شروع, وتھ_y + y, وتھ_x + x, وتھ_y + y + 1);
                    وسعت_شروع = -1;
                }
            } وإلا {
                إذا (وسعت_شروع == -1) {
                    وسعت_شروع = x;
                }
            }
            a += 4;
        }
        إذا (وسعت_شروع != -1) {
            // Add the final span
            جوڑو_Region(&نقاب, وتھ_x + وسعت_شروع, وتھ_y + y, وتھ_x + x, وتھ_y + y + 1);
            وسعت_شروع = -1;
        }
    }
    أرجع نقاب;
}

bool WIN_Update_کھڑکی_Shape(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *shape)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HRGN نقاب = عدم;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        RECT rect;

        إذا (shape->w != کھڑکی->w || shape->h != کھڑکی->h) {
            stretched = SDL_CreateSurfaceUninitialized(کھڑکی->w, کھڑکی->h, SDL_PIXELFORMAT_ARGB32);
            إذا (!stretched) {
                أرجع false;
            }
            إذا (!SDL_StretchSurface(shape, عدم, stretched, عدم, SDL_SCALEMODE_خطی)) {
                SDL_DestroySurface(stretched);
                أرجع false;
            }
            shape = stretched;
        }

        rect.چوٹی = 0;
        rect.بایاں = 0;
        rect.bottom = 0;
        rect.دایاں = 0;
        إذا (!(SDL_Get_کھڑکی_Flags(انکڑے->کھڑکی) & SDL_کھڑکی_BORDERLESS)) {
            WIN_Adjust_کھڑکی_Rect_For_HWND(انکڑے->hwnd, &rect, 0);
        }

        نقاب = Generate_وسعت_List_Region(shape, -rect.بایاں, -rect.چوٹی);

        إذا (!(SDL_Get_کھڑکی_Flags(انکڑے->کھڑکی) & SDL_کھڑکی_BORDERLESS)) {
            // Add the window borders
            // top
            جوڑو_Region(&نقاب, 0, 0, -rect.بایاں + shape->w + rect.دایاں + 1, -rect.چوٹی + 1);
            // left
            جوڑو_Region(&نقاب, 0, -rect.چوٹی, -rect.بایاں + 1, -rect.چوٹی + shape->h + 1);
            // right
            جوڑو_Region(&نقاب, -rect.بایاں + shape->w, -rect.چوٹی, -rect.بایاں + shape->w + rect.دایاں + 1, -rect.چوٹی + shape->h + 1);
            // bottom
            جوڑو_Region(&نقاب, 0, -rect.چوٹی + shape->h, -rect.بایاں + shape->w + rect.دایاں + 1, -rect.چوٹی + shape->h + rect.bottom + 1);
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    إذا (!سیٹ_کھڑکی_Rgn(انکڑے->hwnd, نقاب, TRUE)) {
        DeleteObject(نقاب);
        أرجع WIN_سیٹ_Error("SetWindowRgn failed");
    }
    أرجع true;
}

#جے_انت // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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


ساكن فراغ جمع_کن_Region(HRGN *ماسک, صحيح x1, صحيح y1, صحيح x2, صحيح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    إذا (*ماسک) {
        CombineRgn(*ماسک, *ماسک, region, RGN_OR);
        DeleteObject(region);
    } وإلا {
        *ماسک = region;
    }
}

ساكن HRGN Generate_بازه_List_Region(SDL_Surface *shape, صحيح جابه_جایی_x, صحيح جابه_جایی_y)
{
    HRGN ماسک = عدم;
    صحيح x, y;
    صحيح بازه_شروع = -1;

    لكل (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        لكل (x = 0; x < shape->w; ++x) {
            إذا (*a == SDL_ALPHA_TRANSPARENT) {
                إذا (بازه_شروع != -1) {
                    جمع_کن_Region(&ماسک, جابه_جایی_x + بازه_شروع, جابه_جایی_y + y, جابه_جایی_x + x, جابه_جایی_y + y + 1);
                    بازه_شروع = -1;
                }
            } وإلا {
                إذا (بازه_شروع == -1) {
                    بازه_شروع = x;
                }
            }
            a += 4;
        }
        إذا (بازه_شروع != -1) {
            // Add the final span
            جمع_کن_Region(&ماسک, جابه_جایی_x + بازه_شروع, جابه_جایی_y + y, جابه_جایی_x + x, جابه_جایی_y + y + 1);
            بازه_شروع = -1;
        }
    }
    أرجع ماسک;
}

bool WIN_Update_پنجره_Shape(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *shape)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HRGN ماسک = عدم;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        RECT rect;

        إذا (shape->w != پنجره->w || shape->h != پنجره->h) {
            stretched = SDL_CreateSurfaceUninitialized(پنجره->w, پنجره->h, SDL_PIXELFORMAT_ARGB32);
            إذا (!stretched) {
                أرجع false;
            }
            إذا (!SDL_StretchSurface(shape, عدم, stretched, عدم, SDL_SCALEMODE_خطی)) {
                SDL_DestroySurface(stretched);
                أرجع false;
            }
            shape = stretched;
        }

        rect.بالاترین = 0;
        rect.چپ = 0;
        rect.bottom = 0;
        rect.راست = 0;
        إذا (!(SDL_Get_پنجره_Flags(داده->پنجره) & SDL_پنجره_BORDERLESS)) {
            WIN_Adjust_پنجره_Rect_For_HWND(داده->hwnd, &rect, 0);
        }

        ماسک = Generate_بازه_List_Region(shape, -rect.چپ, -rect.بالاترین);

        إذا (!(SDL_Get_پنجره_Flags(داده->پنجره) & SDL_پنجره_BORDERLESS)) {
            // Add the window borders
            // top
            جمع_کن_Region(&ماسک, 0, 0, -rect.چپ + shape->w + rect.راست + 1, -rect.بالاترین + 1);
            // left
            جمع_کن_Region(&ماسک, 0, -rect.بالاترین, -rect.چپ + 1, -rect.بالاترین + shape->h + 1);
            // right
            جمع_کن_Region(&ماسک, -rect.چپ + shape->w, -rect.بالاترین, -rect.چپ + shape->w + rect.راست + 1, -rect.بالاترین + shape->h + 1);
            // bottom
            جمع_کن_Region(&ماسک, 0, -rect.بالاترین + shape->h, -rect.چپ + shape->w + rect.راست + 1, -rect.بالاترین + shape->h + rect.bottom + 1);
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    إذا (!مجموعه_پنجره_Rgn(داده->hwnd, ماسک, TRUE)) {
        DeleteObject(ماسک);
        أرجع WIN_مجموعه_Error("SetWindowRgn failed");
    }
    أرجع true;
}

#پایان_اگر // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

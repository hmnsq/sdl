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


ساكن فراغ جمع_کړه_Region(HRGN *ماسک, صحيح x1, صحيح y1, صحيح x2, صحيح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    إذا (*ماسک) {
        CombineRgn(*ماسک, *ماسک, region, RGN_OR);
        DeleteObject(region);
    } وإلا {
        *ماسک = region;
    }
}

ساكن HRGN Generate_پراختیا_List_Region(SDL_Surface *shape, صحيح دننه_واټن_x, صحيح دننه_واټن_y)
{
    HRGN ماسک = عدم;
    صحيح x, y;
    صحيح پراختیا_پیل = -1;

    لكل (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        لكل (x = 0; x < shape->w; ++x) {
            إذا (*a == SDL_ALPHA_TRANSPARENT) {
                إذا (پراختیا_پیل != -1) {
                    جمع_کړه_Region(&ماسک, دننه_واټن_x + پراختیا_پیل, دننه_واټن_y + y, دننه_واټن_x + x, دننه_واټن_y + y + 1);
                    پراختیا_پیل = -1;
                }
            } وإلا {
                إذا (پراختیا_پیل == -1) {
                    پراختیا_پیل = x;
                }
            }
            a += 4;
        }
        إذا (پراختیا_پیل != -1) {
            // Add the final span
            جمع_کړه_Region(&ماسک, دننه_واټن_x + پراختیا_پیل, دننه_واټن_y + y, دننه_واټن_x + x, دننه_واټن_y + y + 1);
            پراختیا_پیل = -1;
        }
    }
    أرجع ماسک;
}

bool WIN_Update_کړکۍ_Shape(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *shape)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HRGN ماسک = عدم;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        RECT rect;

        إذا (shape->w != کړکۍ->w || shape->h != کړکۍ->h) {
            stretched = SDL_CreateSurfaceUninitialized(کړکۍ->w, کړکۍ->h, SDL_PIXELFORMAT_ARGB32);
            إذا (!stretched) {
                أرجع false;
            }
            إذا (!SDL_StretchSurface(shape, عدم, stretched, عدم, SDL_SCALEMODE_خطي)) {
                SDL_DestroySurface(stretched);
                أرجع false;
            }
            shape = stretched;
        }

        rect.سر = 0;
        rect.کیڼ = 0;
        rect.bottom = 0;
        rect.ښی = 0;
        إذا (!(SDL_Get_کړکۍ_Flags(معلومات->کړکۍ) & SDL_کړکۍ_BORDERLESS)) {
            WIN_Adjust_کړکۍ_Rect_For_HWND(معلومات->hwnd, &rect, 0);
        }

        ماسک = Generate_پراختیا_List_Region(shape, -rect.کیڼ, -rect.سر);

        إذا (!(SDL_Get_کړکۍ_Flags(معلومات->کړکۍ) & SDL_کړکۍ_BORDERLESS)) {
            // Add the window borders
            // top
            جمع_کړه_Region(&ماسک, 0, 0, -rect.کیڼ + shape->w + rect.ښی + 1, -rect.سر + 1);
            // left
            جمع_کړه_Region(&ماسک, 0, -rect.سر, -rect.کیڼ + 1, -rect.سر + shape->h + 1);
            // right
            جمع_کړه_Region(&ماسک, -rect.کیڼ + shape->w, -rect.سر, -rect.کیڼ + shape->w + rect.ښی + 1, -rect.سر + shape->h + 1);
            // bottom
            جمع_کړه_Region(&ماسک, 0, -rect.سر + shape->h, -rect.کیڼ + shape->w + rect.ښی + 1, -rect.سر + shape->h + rect.bottom + 1);
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    إذا (!سېټ_کړکۍ_Rgn(معلومات->hwnd, ماسک, TRUE)) {
        DeleteObject(ماسک);
        أرجع WIN_سېټ_Error("SetWindowRgn failed");
    }
    أرجع true;
}

#د_که_پای // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

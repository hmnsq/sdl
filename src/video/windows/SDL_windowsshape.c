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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowsshape.h"


ساکن خالی جوڑو_Region(HRGN *نقاب, صحیح x1, صحیح y1, صحیح x2, صحیح y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    اگر (*نقاب) {
        CombineRgn(*نقاب, *نقاب, region, RGN_OR);
        DeleteObject(region);
    } ورنہ {
        *نقاب = region;
    }
}

ساکن HRGN Generate_وسعت_List_Region(SDL_Surface *shape, صحیح انحراف_x, صحیح انحراف_y)
{
    HRGN نقاب = تہی;
    صحیح x, y;
    صحیح وسعت_آغاز = -1;

    برائے (y = 0; y < shape->h; ++y) {
        ثابت Uint8 *a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
        برائے (x = 0; x < shape->w; ++x) {
            اگر (*a == SDL_ALPHA_TRANSPARENT) {
                اگر (وسعت_آغاز != -1) {
                    جوڑو_Region(&نقاب, انحراف_x + وسعت_آغاز, انحراف_y + y, انحراف_x + x, انحراف_y + y + 1);
                    وسعت_آغاز = -1;
                }
            } ورنہ {
                اگر (وسعت_آغاز == -1) {
                    وسعت_آغاز = x;
                }
            }
            a += 4;
        }
        اگر (وسعت_آغاز != -1) {
            // Add the final span
            جوڑو_Region(&نقاب, انحراف_x + وسعت_آغاز, انحراف_y + y, انحراف_x + x, انحراف_y + y + 1);
            وسعت_آغاز = -1;
        }
    }
    واپس نقاب;
}

bool WIN_Update_کھڑکی_Shape(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *shape)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    HRGN نقاب = تہی;

    // Generate a set of spans for the region
    اگر (shape) {
        SDL_Surface *stretched = تہی;
        RECT rect;

        اگر (shape->w != کھڑکی->w || shape->h != کھڑکی->h) {
            stretched = SDL_CreateSurfaceUninitialized(کھڑکی->w, کھڑکی->h, SDL_PIXELFORMAT_ARGB32);
            اگر (!stretched) {
                واپس false;
            }
            اگر (!SDL_StretchSurface(shape, تہی, stretched, تہی, SDL_SCALEMODE_خطی)) {
                SDL_DestroySurface(stretched);
                واپس false;
            }
            shape = stretched;
        }

        rect.چوٹی = 0;
        rect.بایاں = 0;
        rect.bottom = 0;
        rect.دایاں = 0;
        اگر (!(SDL_Get_کھڑکی_Flags(ڈیٹا->کھڑکی) & SDL_کھڑکی_BORDERLESS)) {
            WIN_Adjust_کھڑکی_Rect_For_HWND(ڈیٹا->hwnd, &rect, 0);
        }

        نقاب = Generate_وسعت_List_Region(shape, -rect.بایاں, -rect.چوٹی);

        اگر (!(SDL_Get_کھڑکی_Flags(ڈیٹا->کھڑکی) & SDL_کھڑکی_BORDERLESS)) {
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

        اگر (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    اگر (!سیٹ_کھڑکی_Rgn(ڈیٹا->hwnd, نقاب, TRUE)) {
        DeleteObject(نقاب);
        واپس WIN_سیٹ_Error("SetWindowRgn failed");
    }
    واپس true;
}

#اگر_ختم // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

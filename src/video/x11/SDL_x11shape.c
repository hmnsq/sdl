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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11shape.h"


#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
ساكن Uint8 *Generate_Shape_نقاب(SDL_Surface *shape)
{
    صحيح x, y;
    ثابت size_t ppb = 8;
    ثابت size_t بائٹاں_فی_scanline = (shape->w + (ppb - 1)) / ppb;
    ثابت Uint8 *a;
    Uint8 *نقاب;
    Uint8 *نقاب_scanline;
    Uint8 نقاب_قدر;

    نقاب = (Uint8 *)SDL_calloc(1, shape->h * بائٹاں_فی_scanline);
    إذا (نقاب) {
        لكل (y = 0; y < shape->h; y++) {
            a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
            نقاب_scanline = نقاب + y * بائٹاں_فی_scanline;
            لكل (x = 0; x < shape->w; x++) {
                نقاب_قدر = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                نقاب_scanline[x / ppb] |= نقاب_قدر << (x % ppb);
                a += 4;
            }
        }
    }
    أرجع نقاب;
}
#جے_انت // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_Update_کھڑکی_Shape(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *shape)
{
    bool نتیجہ = false;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_کھڑکی_انکڑے *windowdata = کھڑکی->اندرونی;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        Uint8 *نقاب;
        Pixmap pixmap;

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

        نقاب = Generate_Shape_نقاب(shape);
        إذا (نقاب) {
            pixmap = X11_XCreate_Bitmap_From_انکڑے(windowdata->videodata->display, windowdata->xwindow, (ثابت حرف *)نقاب, shape->w, shape->h);
            X11_XShape_Combine_نقاب(windowdata->videodata->display, windowdata->xwindow, Shape_داخلہ, 0, 0, pixmap, Shape_سیٹ);
            SDL_free(نقاب);

            نتیجہ = true;
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    } وإلا {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.چوڑائی = کھڑکی->w;
        rect.اچائی = کھڑکی->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_داخلہ, 0, 0, region, Shape_سیٹ);
        X11_XDestroyRegion(region);
        نتیجہ = true;
    }
#جے_انت // SDL_VIDEO_DRIVER_X11_XSHAPE

    أرجع نتیجہ;
}

#جے_انت // SDL_VIDEO_DRIVER_X11

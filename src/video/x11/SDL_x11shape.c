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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11shape.h"


#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSHAPE
ساكن Uint8 *Generate_Shape_ماسک(SDL_Surface *shape)
{
    صحيح x, y;
    ثابت size_t ppb = 8;
    ثابت size_t بایتها_در_هر_scanline = (shape->w + (ppb - 1)) / ppb;
    ثابت Uint8 *a;
    Uint8 *ماسک;
    Uint8 *ماسک_scanline;
    Uint8 ماسک_مقدار;

    ماسک = (Uint8 *)SDL_calloc(1, shape->h * بایتها_در_هر_scanline);
    إذا (ماسک) {
        لكل (y = 0; y < shape->h; y++) {
            a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
            ماسک_scanline = ماسک + y * بایتها_در_هر_scanline;
            لكل (x = 0; x < shape->w; x++) {
                ماسک_مقدار = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                ماسک_scanline[x / ppb] |= ماسک_مقدار << (x % ppb);
                a += 4;
            }
        }
    }
    أرجع ماسک;
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_Update_پنجره_Shape(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *shape)
{
    bool نتیجه = false;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_پنجره_داده *windowdata = پنجره->داخلی;

    // Generate a set of spans for the region
    إذا (shape) {
        SDL_Surface *stretched = عدم;
        Uint8 *ماسک;
        Pixmap pixmap;

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

        ماسک = Generate_Shape_ماسک(shape);
        إذا (ماسک) {
            pixmap = X11_XCreate_Bitmap_From_داده(windowdata->videodata->display, windowdata->xwindow, (ثابت حرف *)ماسک, shape->w, shape->h);
            X11_XShape_Combine_ماسک(windowdata->videodata->display, windowdata->xwindow, Shape_درون_داد, 0, 0, pixmap, Shape_مجموعه);
            SDL_free(ماسک);

            نتیجه = true;
        }

        إذا (stretched) {
            SDL_DestroySurface(stretched);
        }
    } وإلا {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.عرض = پنجره->w;
        rect.ارتفاع = پنجره->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_درون_داد, 0, 0, region, Shape_مجموعه);
        X11_XDestroyRegion(region);
        نتیجه = true;
    }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XSHAPE

    أرجع نتیجه;
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11

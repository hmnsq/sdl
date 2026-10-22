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

#ifdef SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11video.h"
#شامل "SDL_x11shape.h"


#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
ایستا Uint8 *GenerateShapeMask(SDL_Surface *shape)
{
    صحیح x, y;
    ثابت size_t ppb = 8;
    ثابت size_t bytes_per_scanline = (shape->w + (ppb - 1)) / ppb;
    ثابت Uint8 *a;
    Uint8 *mask;
    Uint8 *mask_scanline;
    Uint8 mask_مقدار;

    mask = (Uint8 *)SDL_calloc(1, shape->h * bytes_per_scanline);
    اگر (mask) {
        برای (y = 0; y < shape->h; y++) {
            a = (ثابت Uint8 *)shape->pixels + y * shape->pitch;
            mask_scanline = mask + y * bytes_per_scanline;
            برای (x = 0; x < shape->w; x++) {
                mask_مقدار = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                mask_scanline[x / ppb] |= mask_مقدار << (x % ppb);
                a += 4;
            }
        }
    }
    بازگشت mask;
}
#endif // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    bool result = false;

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_WindowData *windowdata = window->internal;

    // Generate a set of spans for the region
    اگر (shape) {
        SDL_Surface *stretched = پوچ;
        Uint8 *mask;
        Pixmap pixmap;

        اگر (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            اگر (!stretched) {
                بازگشت false;
            }
            اگر (!SDL_StretchSurface(shape, پوچ, stretched, پوچ, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                بازگشت false;
            }
            shape = stretched;
        }

        mask = GenerateShapeMask(shape);
        اگر (mask) {
            pixmap = X11_XCreateBitmapFromData(windowdata->videodata->display, windowdata->xwindow, (ثابت نویسه *)mask, shape->w, shape->h);
            X11_XShapeCombineMask(windowdata->videodata->display, windowdata->xwindow, Shape_درون_داد, 0, 0, pixmap, ShapeSet);
            SDL_free(mask);

            result = true;
        }

        اگر (stretched) {
            SDL_DestroySurface(stretched);
        }
    } وگرنه {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.width = window->w;
        rect.height = window->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_درون_داد, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
        result = true;
    }
#endif // SDL_VIDEO_DRIVER_X11_XSHAPE

    بازگشت result;
}

#endif // SDL_VIDEO_DRIVER_X11

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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11shape.h"


#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
நிலையான Uint8 *GenerateShapeMask(SDL_Surface *shape)
{
    முழு x, y;
    மாறிலி size_t ppb = 8;
    மாறிலி size_t bytes_per_scanline = (shape->w + (ppb - 1)) / ppb;
    மாறிலி Uint8 *a;
    Uint8 *mask;
    Uint8 *mask_scanline;
    Uint8 mask_மதிப்பு;

    mask = (Uint8 *)SDL_calloc(1, shape->h * bytes_per_scanline);
    எனில் (mask) {
        க்கு (y = 0; y < shape->h; y++) {
            a = (மாறிலி Uint8 *)shape->pixels + y * shape->pitch;
            mask_scanline = mask + y * bytes_per_scanline;
            க்கு (x = 0; x < shape->w; x++) {
                mask_மதிப்பு = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                mask_scanline[x / ppb] |= mask_மதிப்பு << (x % ppb);
                a += 4;
            }
        }
    }
    திரும்பு mask;
}
#endif // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    bool result = false;

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_WindowData *windowdata = window->internal;

    // Generate a set of spans for the region
    எனில் (shape) {
        SDL_Surface *stretched = வெற்று;
        Uint8 *mask;
        Pixmap pixmap;

        எனில் (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            எனில் (!stretched) {
                திரும்பு false;
            }
            எனில் (!SDL_StretchSurface(shape, வெற்று, stretched, வெற்று, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                திரும்பு false;
            }
            shape = stretched;
        }

        mask = GenerateShapeMask(shape);
        எனில் (mask) {
            pixmap = X11_XCreateBitmapFromData(windowdata->videodata->display, windowdata->xwindow, (மாறிலி எழுத்து *)mask, shape->w, shape->h);
            X11_XShapeCombineMask(windowdata->videodata->display, windowdata->xwindow, Shape_உள்ளீடு, 0, 0, pixmap, ShapeSet);
            SDL_free(mask);

            result = true;
        }

        எனில் (stretched) {
            SDL_DestroySurface(stretched);
        }
    } இல்லையெனில் {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.width = window->w;
        rect.height = window->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_உள்ளீடு, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
        result = true;
    }
#endif // SDL_VIDEO_DRIVER_X11_XSHAPE

    திரும்பு result;
}

#endif // SDL_VIDEO_DRIVER_X11

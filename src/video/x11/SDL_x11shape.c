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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11shape.h"


#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
स्थिर Uint8 *GenerateShapeMask(SDL_Surface *shape)
{
    पूर्णांक x, y;
    स्थिरांक माप_प्रकार ppb = 8;
    स्थिरांक माप_प्रकार bytes_per_scanline = (shape->w + (ppb - 1)) / ppb;
    स्थिरांक Uint8 *a;
    Uint8 *mask;
    Uint8 *mask_scanline;
    Uint8 mask_मूल्य;

    mask = (Uint8 *)SDL_calloc(1, shape->h * bytes_per_scanline);
    जर (mask) {
        साठी (y = 0; y < shape->h; y++) {
            a = (स्थिरांक Uint8 *)shape->pixels + y * shape->pitch;
            mask_scanline = mask + y * bytes_per_scanline;
            साठी (x = 0; x < shape->w; x++) {
                mask_मूल्य = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                mask_scanline[x / ppb] |= mask_मूल्य << (x % ppb);
                a += 4;
            }
        }
    }
    परत mask;
}
#endif // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    bool result = false;

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_WindowData *windowdata = window->internal;

    // Generate a set of spans for the region
    जर (shape) {
        SDL_Surface *stretched = रिक्त;
        Uint8 *mask;
        Pixmap pixmap;

        जर (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            जर (!stretched) {
                परत false;
            }
            जर (!SDL_StretchSurface(shape, रिक्त, stretched, रिक्त, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                परत false;
            }
            shape = stretched;
        }

        mask = GenerateShapeMask(shape);
        जर (mask) {
            pixmap = X11_XCreateBitmapFromData(windowdata->videodata->display, windowdata->xwindow, (स्थिरांक अक्षर *)mask, shape->w, shape->h);
            X11_XShapeCombineMask(windowdata->videodata->display, windowdata->xwindow, Shape_आदान, 0, 0, pixmap, ShapeSet);
            SDL_free(mask);

            result = true;
        }

        जर (stretched) {
            SDL_DestroySurface(stretched);
        }
    } अन्यथा {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.width = window->w;
        rect.height = window->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_आदान, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
        result = true;
    }
#endif // SDL_VIDEO_DRIVER_X11_XSHAPE

    परत result;
}

#endif // SDL_VIDEO_DRIVER_X11

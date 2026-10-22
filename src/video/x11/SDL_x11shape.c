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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11shape.h"


#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSHAPE
अटल Uint8 *GenerateShapeMask(SDL_Surface *shape)
{
    पूर्णांक x, y;
    स्थिर माप_प्रकार ppb = 8;
    स्थिर माप_प्रकार bytes_per_scanline = (shape->w + (ppb - 1)) / ppb;
    स्थिर Uint8 *a;
    Uint8 *mask;
    Uint8 *mask_scanline;
    Uint8 mask_मूल्य;

    mask = (Uint8 *)SDL_calloc(1, shape->h * bytes_per_scanline);
    अगर (mask) {
        क्रम (y = 0; y < shape->h; y++) {
            a = (स्थिर Uint8 *)shape->pixels + y * shape->pitch;
            mask_scanline = mask + y * bytes_per_scanline;
            क्रम (x = 0; x < shape->w; x++) {
                mask_मूल्य = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                mask_scanline[x / ppb] |= mask_मूल्य << (x % ppb);
                a += 4;
            }
        }
    }
    वापस mask;
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_UpdateWindowShape(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *shape)
{
    bool परिणाम = false;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_Window_तथ्य *windowdata = window->internal;

    // Generate a set of spans for the region
    अगर (shape) {
        SDL_Surface *stretched = शून्य;
        Uint8 *mask;
        Pixmap pixmap;

        अगर (shape->w != window->w || shape->h != window->h) {
            stretched = SDL_CreateSurfaceUninitialized(window->w, window->h, SDL_PIXELFORMAT_ARGB32);
            अगर (!stretched) {
                वापस false;
            }
            अगर (!SDL_StretchSurface(shape, शून्य, stretched, शून्य, SDL_SCALEMODE_LINEAR)) {
                SDL_DestroySurface(stretched);
                वापस false;
            }
            shape = stretched;
        }

        mask = GenerateShapeMask(shape);
        अगर (mask) {
            pixmap = X11_XCreate_Bitmap_From_तथ्य(windowdata->videodata->display, windowdata->xwindow, (स्थिर अक्षर *)mask, shape->w, shape->h);
            X11_XShapeCombineMask(windowdata->videodata->display, windowdata->xwindow, Shape_निवेश, 0, 0, pixmap, ShapeSet);
            SDL_free(mask);

            परिणाम = true;
        }

        अगर (stretched) {
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
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_निवेश, 0, 0, region, ShapeSet);
        X11_XDestroyRegion(region);
        परिणाम = true;
    }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XSHAPE

    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11

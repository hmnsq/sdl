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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11shape.h"


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSHAPE
ਸਥਿਰ Uint8 *Generate_Shape_ਨਕਾਬ(SDL_Surface *shape)
{
    ਪੂਰਨ x, y;
    ਅਚਲ size_t ppb = 8;
    ਅਚਲ size_t ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_scanline = (shape->w + (ppb - 1)) / ppb;
    ਅਚਲ Uint8 *a;
    Uint8 *ਨਕਾਬ;
    Uint8 *ਨਕਾਬ_scanline;
    Uint8 ਨਕਾਬ_ਮੁੱਲ;

    ਨਕਾਬ = (Uint8 *)SDL_calloc(1, shape->h * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_scanline);
    ਜੇ (ਨਕਾਬ) {
        ਲਈ (y = 0; y < shape->h; y++) {
            a = (ਅਚਲ Uint8 *)shape->pixels + y * shape->pitch;
            ਨਕਾਬ_scanline = ਨਕਾਬ + y * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_scanline;
            ਲਈ (x = 0; x < shape->w; x++) {
                ਨਕਾਬ_ਮੁੱਲ = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                ਨਕਾਬ_scanline[x / ppb] |= ਨਕਾਬ_ਮੁੱਲ << (x % ppb);
                a += 4;
            }
        }
    }
    ਵਾਪਸ ਨਕਾਬ;
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_Update_ਖਿੜਕੀ_Shape(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *shape)
{
    bool ਨਤੀਜਾ = false;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // Generate a set of spans for the region
    ਜੇ (shape) {
        SDL_Surface *stretched = ਨਿਰਾ;
        Uint8 *ਨਕਾਬ;
        Pixmap pixmap;

        ਜੇ (shape->w != ਖਿੜਕੀ->w || shape->h != ਖਿੜਕੀ->h) {
            stretched = SDL_CreateSurfaceUninitialized(ਖਿੜਕੀ->w, ਖਿੜਕੀ->h, SDL_PIXELFORMAT_ARGB32);
            ਜੇ (!stretched) {
                ਵਾਪਸ false;
            }
            ਜੇ (!SDL_StretchSurface(shape, ਨਿਰਾ, stretched, ਨਿਰਾ, SDL_SCALEMODE_ਰੇਖਿਕ)) {
                SDL_DestroySurface(stretched);
                ਵਾਪਸ false;
            }
            shape = stretched;
        }

        ਨਕਾਬ = Generate_Shape_ਨਕਾਬ(shape);
        ਜੇ (ਨਕਾਬ) {
            pixmap = X11_XCreate_Bitmap_From_ਅੰਕੜੇ(windowdata->videodata->display, windowdata->xwindow, (ਅਚਲ ਅੱਖਰ *)ਨਕਾਬ, shape->w, shape->h);
            X11_XShape_Combine_ਨਕਾਬ(windowdata->videodata->display, windowdata->xwindow, Shape_ਨਿਵੇਸ਼, 0, 0, pixmap, Shape_ਸੈੱਟ);
            SDL_free(ਨਕਾਬ);

            ਨਤੀਜਾ = true;
        }

        ਜੇ (stretched) {
            SDL_DestroySurface(stretched);
        }
    } ਨਹੀਂਤਾਂ {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.ਚੌੜਾਈ = ਖਿੜਕੀ->w;
        rect.ਉਚਾਈ = ਖਿੜਕੀ->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_ਨਿਵੇਸ਼, 0, 0, region, Shape_ਸੈੱਟ);
        X11_XDestroyRegion(region);
        ਨਤੀਜਾ = true;
    }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XSHAPE

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11

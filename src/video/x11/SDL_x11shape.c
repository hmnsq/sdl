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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11shape.h"


#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSHAPE
స్థిర Uint8 *Generate_Shape_ముసుగు(SDL_Surface *shape)
{
    పూర్ణాంకం x, y;
    స్థిరరాశి size_t ppb = 8;
    స్థిరరాశి size_t బైట్లు_చొప్పున_scanline = (shape->w + (ppb - 1)) / ppb;
    స్థిరరాశి Uint8 *a;
    Uint8 *ముసుగు;
    Uint8 *ముసుగు_scanline;
    Uint8 ముసుగు_విలువ;

    ముసుగు = (Uint8 *)SDL_calloc(1, shape->h * బైట్లు_చొప్పున_scanline);
    ఒకవేళ (ముసుగు) {
        కొరకు (y = 0; y < shape->h; y++) {
            a = (స్థిరరాశి Uint8 *)shape->pixels + y * shape->pitch;
            ముసుగు_scanline = ముసుగు + y * బైట్లు_చొప్పున_scanline;
            కొరకు (x = 0; x < shape->w; x++) {
                ముసుగు_విలువ = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                ముసుగు_scanline[x / ppb] |= ముసుగు_విలువ << (x % ppb);
                a += 4;
            }
        }
    }
    తిరిగి ముసుగు;
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_Update_కిటికీ_Shape(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *shape)
{
    bool ఫలితం = false;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_కిటికీ_దత్తాంశం *windowdata = కిటికీ->అంతర్గత;

    // Generate a set of spans for the region
    ఒకవేళ (shape) {
        SDL_Surface *stretched = ఖాళీ;
        Uint8 *ముసుగు;
        Pixmap pixmap;

        ఒకవేళ (shape->w != కిటికీ->w || shape->h != కిటికీ->h) {
            stretched = SDL_CreateSurfaceUninitialized(కిటికీ->w, కిటికీ->h, SDL_PIXELFORMAT_ARGB32);
            ఒకవేళ (!stretched) {
                తిరిగి false;
            }
            ఒకవేళ (!SDL_StretchSurface(shape, ఖాళీ, stretched, ఖాళీ, SDL_SCALEMODE_రేఖీయ)) {
                SDL_DestroySurface(stretched);
                తిరిగి false;
            }
            shape = stretched;
        }

        ముసుగు = Generate_Shape_ముసుగు(shape);
        ఒకవేళ (ముసుగు) {
            pixmap = X11_XCreate_Bitmap_From_దత్తాంశం(windowdata->videodata->display, windowdata->xwindow, (స్థిరరాశి అక్షరం *)ముసుగు, shape->w, shape->h);
            X11_XShape_Combine_ముసుగు(windowdata->videodata->display, windowdata->xwindow, Shape_ఆదానం, 0, 0, pixmap, Shape_సమితి);
            SDL_free(ముసుగు);

            ఫలితం = true;
        }

        ఒకవేళ (stretched) {
            SDL_DestroySurface(stretched);
        }
    } లేకపోతే {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.వెడల్పు = కిటికీ->w;
        rect.ఎత్తు = కిటికీ->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_ఆదానం, 0, 0, region, Shape_సమితి);
        X11_XDestroyRegion(region);
        ఫలితం = true;
    }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XSHAPE

    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11

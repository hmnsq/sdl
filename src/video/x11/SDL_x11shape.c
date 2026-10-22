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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11shape.h"


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSHAPE
ಸ್ಥಿರ Uint8 *Generate_Shape_ಮುಖವಾಡ(SDL_Surface *shape)
{
    ಪೂರ್ಣಾಂಕ x, y;
    ಸ್ಥಿರಾಂಕ size_t ppb = 8;
    ಸ್ಥಿರಾಂಕ size_t ಬೈಟುಗಳು_ಪ್ರತಿ_scanline = (shape->w + (ppb - 1)) / ppb;
    ಸ್ಥಿರಾಂಕ Uint8 *a;
    Uint8 *ಮುಖವಾಡ;
    Uint8 *ಮುಖವಾಡ_scanline;
    Uint8 ಮುಖವಾಡ_ಮೌಲ್ಯ;

    ಮುಖವಾಡ = (Uint8 *)SDL_calloc(1, shape->h * ಬೈಟುಗಳು_ಪ್ರತಿ_scanline);
    ಆದರೆ (ಮುಖವಾಡ) {
        ಗಾಗಿ (y = 0; y < shape->h; y++) {
            a = (ಸ್ಥಿರಾಂಕ Uint8 *)shape->pixels + y * shape->pitch;
            ಮುಖವಾಡ_scanline = ಮುಖವಾಡ + y * ಬೈಟುಗಳು_ಪ್ರತಿ_scanline;
            ಗಾಗಿ (x = 0; x < shape->w; x++) {
                ಮುಖವಾಡ_ಮೌಲ್ಯ = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                ಮುಖವಾಡ_scanline[x / ppb] |= ಮುಖವಾಡ_ಮೌಲ್ಯ << (x % ppb);
                a += 4;
            }
        }
    }
    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_Update_ಕಿಟಕಿ_Shape(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *shape)
{
    bool ಫಲಿತಾಂಶ = false;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // Generate a set of spans for the region
    ಆದರೆ (shape) {
        SDL_Surface *stretched = ಖಾಲಿ;
        Uint8 *ಮುಖವಾಡ;
        Pixmap pixmap;

        ಆದರೆ (shape->w != ಕಿಟಕಿ->w || shape->h != ಕಿಟಕಿ->h) {
            stretched = SDL_CreateSurfaceUninitialized(ಕಿಟಕಿ->w, ಕಿಟಕಿ->h, SDL_PIXELFORMAT_ARGB32);
            ಆದರೆ (!stretched) {
                ಹಿಂತಿರುಗಿ false;
            }
            ಆದರೆ (!SDL_StretchSurface(shape, ಖಾಲಿ, stretched, ಖಾಲಿ, SDL_SCALEMODE_ರೇಖೀಯ)) {
                SDL_DestroySurface(stretched);
                ಹಿಂತಿರುಗಿ false;
            }
            shape = stretched;
        }

        ಮುಖವಾಡ = Generate_Shape_ಮುಖವಾಡ(shape);
        ಆದರೆ (ಮುಖವಾಡ) {
            pixmap = X11_XCreate_Bitmap_From_ದತ್ತಾಂಶ(windowdata->videodata->display, windowdata->xwindow, (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)ಮುಖವಾಡ, shape->w, shape->h);
            X11_XShape_Combine_ಮುಖವಾಡ(windowdata->videodata->display, windowdata->xwindow, Shape_ಒಳಹರಿವು, 0, 0, pixmap, Shape_ಗಣ);
            SDL_free(ಮುಖವಾಡ);

            ಫಲಿತಾಂಶ = true;
        }

        ಆದರೆ (stretched) {
            SDL_DestroySurface(stretched);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.ಅಗಲ = ಕಿಟಕಿ->w;
        rect.ಎತ್ತರ = ಕಿಟಕಿ->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_ಒಳಹರಿವು, 0, 0, region, Shape_ಗಣ);
        X11_XDestroyRegion(region);
        ಫಲಿತಾಂಶ = true;
    }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XSHAPE

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11

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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11shape.h"


#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSHAPE
स्थिर Uint8 *Generate_Shape_आवरणम्(SDL_Surface *shape)
{
    पूर्णाङ्क x, y;
    ध्रुव size_t ppb = 8;
    ध्रुव size_t अष्टकानि_प्रत्येकम्_scanline = (shape->w + (ppb - 1)) / ppb;
    ध्रुव Uint8 *a;
    Uint8 *आवरणम्;
    Uint8 *आवरणम्_scanline;
    Uint8 आवरणम्_मानम्;

    आवरणम् = (Uint8 *)SDL_calloc(1, shape->h * अष्टकानि_प्रत्येकम्_scanline);
    यदि (आवरणम्) {
        प्रति (y = 0; y < shape->h; y++) {
            a = (ध्रुव Uint8 *)shape->pixels + y * shape->pitch;
            आवरणम्_scanline = आवरणम् + y * अष्टकानि_प्रत्येकम्_scanline;
            प्रति (x = 0; x < shape->w; x++) {
                आवरणम्_मानम् = (*a == SDL_ALPHA_TRANSPARENT) ? 0 : 1;
                आवरणम्_scanline[x / ppb] |= आवरणम्_मानम् << (x % ppb);
                a += 4;
            }
        }
    }
    प्रत्यागम आवरणम्;
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XSHAPE

bool X11_Update_गवाक्षः_Shape(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *shape)
{
    bool परिणाम = false;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSHAPE
    SDL_गवाक्षः_दत्त *windowdata = गवाक्षः->आन्तरिकम्;

    // Generate a set of spans for the region
    यदि (shape) {
        SDL_Surface *stretched = रिक्त;
        Uint8 *आवरणम्;
        Pixmap pixmap;

        यदि (shape->w != गवाक्षः->w || shape->h != गवाक्षः->h) {
            stretched = SDL_CreateSurfaceUninitialized(गवाक्षः->w, गवाक्षः->h, SDL_PIXELFORMAT_ARGB32);
            यदि (!stretched) {
                प्रत्यागम false;
            }
            यदि (!SDL_StretchSurface(shape, रिक्त, stretched, रिक्त, SDL_SCALEMODE_रैखिकम्)) {
                SDL_DestroySurface(stretched);
                प्रत्यागम false;
            }
            shape = stretched;
        }

        आवरणम् = Generate_Shape_आवरणम्(shape);
        यदि (आवरणम्) {
            pixmap = X11_XCreate_Bitmap_From_दत्त(windowdata->videodata->display, windowdata->xwindow, (ध्रुव वर्ण *)आवरणम्, shape->w, shape->h);
            X11_XShape_Combine_आवरणम्(windowdata->videodata->display, windowdata->xwindow, Shape_निवेशः, 0, 0, pixmap, Shape_समुच्चयः);
            SDL_free(आवरणम्);

            परिणाम = true;
        }

        यदि (stretched) {
            SDL_DestroySurface(stretched);
        }
    } अन्यथा {
        Region region = X11_XCreateRegion();
        XRectangle rect;

        rect.x = 0;
        rect.y = 0;
        rect.विस्तारः = गवाक्षः->w;
        rect.height = गवाक्षः->h;
        X11_XUnionRectWithRegion(&rect, region, region);
        X11_XShapeCombineRegion(windowdata->videodata->display, windowdata->xwindow, Shape_निवेशः, 0, 0, region, Shape_समुच्चयः);
        X11_XDestroyRegion(region);
        परिणाम = true;
    }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XSHAPE

    प्रत्यागम परिणाम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11

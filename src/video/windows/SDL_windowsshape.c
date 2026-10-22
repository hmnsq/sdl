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

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowsshape.h"


స్థిర శూన్య కూడు_Region(HRGN *ముసుగు, పూర్ణాంకం x1, పూర్ణాంకం y1, పూర్ణాంకం x2, పూర్ణాంకం y2)
{
    HRGN region = CreateRectRgn(x1, y1, x2, y2);
    ఒకవేళ (*ముసుగు) {
        CombineRgn(*ముసుగు, *ముసుగు, region, RGN_OR);
        DeleteObject(region);
    } లేకపోతే {
        *ముసుగు = region;
    }
}

స్థిర HRGN Generate_పరిధి_List_Region(SDL_Surface *shape, పూర్ణాంకం స్థానభ్రంశం_x, పూర్ణాంకం స్థానభ్రంశం_y)
{
    HRGN ముసుగు = ఖాళీ;
    పూర్ణాంకం x, y;
    పూర్ణాంకం పరిధి_ప్రారంభం = -1;

    కొరకు (y = 0; y < shape->h; ++y) {
        స్థిరరాశి Uint8 *a = (స్థిరరాశి Uint8 *)shape->pixels + y * shape->pitch;
        కొరకు (x = 0; x < shape->w; ++x) {
            ఒకవేళ (*a == SDL_ALPHA_TRANSPARENT) {
                ఒకవేళ (పరిధి_ప్రారంభం != -1) {
                    కూడు_Region(&ముసుగు, స్థానభ్రంశం_x + పరిధి_ప్రారంభం, స్థానభ్రంశం_y + y, స్థానభ్రంశం_x + x, స్థానభ్రంశం_y + y + 1);
                    పరిధి_ప్రారంభం = -1;
                }
            } లేకపోతే {
                ఒకవేళ (పరిధి_ప్రారంభం == -1) {
                    పరిధి_ప్రారంభం = x;
                }
            }
            a += 4;
        }
        ఒకవేళ (పరిధి_ప్రారంభం != -1) {
            // Add the final span
            కూడు_Region(&ముసుగు, స్థానభ్రంశం_x + పరిధి_ప్రారంభం, స్థానభ్రంశం_y + y, స్థానభ్రంశం_x + x, స్థానభ్రంశం_y + y + 1);
            పరిధి_ప్రారంభం = -1;
        }
    }
    తిరిగి ముసుగు;
}

bool WIN_Update_కిటికీ_Shape(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *shape)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HRGN ముసుగు = ఖాళీ;

    // Generate a set of spans for the region
    ఒకవేళ (shape) {
        SDL_Surface *stretched = ఖాళీ;
        RECT rect;

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

        rect.శిఖరం = 0;
        rect.ఎడమ = 0;
        rect.bottom = 0;
        rect.కుడి = 0;
        ఒకవేళ (!(SDL_Get_కిటికీ_Flags(దత్తాంశం->కిటికీ) & SDL_కిటికీ_BORDERLESS)) {
            WIN_Adjust_కిటికీ_Rect_For_HWND(దత్తాంశం->hwnd, &rect, 0);
        }

        ముసుగు = Generate_పరిధి_List_Region(shape, -rect.ఎడమ, -rect.శిఖరం);

        ఒకవేళ (!(SDL_Get_కిటికీ_Flags(దత్తాంశం->కిటికీ) & SDL_కిటికీ_BORDERLESS)) {
            // Add the window borders
            // top
            కూడు_Region(&ముసుగు, 0, 0, -rect.ఎడమ + shape->w + rect.కుడి + 1, -rect.శిఖరం + 1);
            // left
            కూడు_Region(&ముసుగు, 0, -rect.శిఖరం, -rect.ఎడమ + 1, -rect.శిఖరం + shape->h + 1);
            // right
            కూడు_Region(&ముసుగు, -rect.ఎడమ + shape->w, -rect.శిఖరం, -rect.ఎడమ + shape->w + rect.కుడి + 1, -rect.శిఖరం + shape->h + 1);
            // bottom
            కూడు_Region(&ముసుగు, 0, -rect.శిఖరం + shape->h, -rect.ఎడమ + shape->w + rect.కుడి + 1, -rect.శిఖరం + shape->h + rect.bottom + 1);
        }

        ఒకవేళ (stretched) {
            SDL_DestroySurface(stretched);
        }
    }
    ఒకవేళ (!సమితి_కిటికీ_Rgn(దత్తాంశం->hwnd, ముసుగు, TRUE)) {
        DeleteObject(ముసుగు);
        తిరిగి WIN_సమితి_Error("SetWindowRgn failed");
    }
    తిరిగి true;
}

#అయితే_ముగింపు // defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_GetSpanEnclosingRect(પૂર્ણાંક width, પૂર્ણાંક height,
                         પૂર્ણાંક numrects, અચલ SDL_Rect *rects, SDL_Rect *span)
{
    પૂર્ણાંક i;
    પૂર્ણાંક span_y1, span_y2;
    પૂર્ણાંક rect_y1, rect_y2;

    CHECK_PARAM(width < 1) {
        SDL_InvalidParamError("width");
        પાછા false;
    }
    CHECK_PARAM(height < 1) {
        SDL_InvalidParamError("height");
        પાછા false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        પાછા false;
    }
    CHECK_PARAM(!span) {
        SDL_InvalidParamError("span");
        પાછા false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        પાછા false;
    }

    // Initialize to empty rect
    span_y1 = height;
    span_y2 = 0;

    માટે (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        જો (rect_y1 < 0) {
            span_y1 = 0;
        } નહીંતર જો (rect_y1 < span_y1) {
            span_y1 = rect_y1;
        }
        જો (rect_y2 > height) {
            span_y2 = height;
        } નહીંતર જો (rect_y2 > span_y2) {
            span_y2 = rect_y2;
        }
    }
    જો (span_y2 > span_y1) {
        span->x = 0;
        span->y = span_y1;
        span->w = width;
        span->h = (span_y2 - span_y1);
        પાછા true;
    }
    પાછા false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#define CODE_BOTTOM 1
#define CODE_ટોચ    2
#define CODE_ડાબું   4
#define CODE_જમણું  8

// Same code twice, for float and int versions...
#define RECTTYPE                 SDL_Rect
#define POINTTYPE                SDL_Point
#define SCALARTYPE               પૂર્ણાંક
#define BIGSCALARTYPE            Sint64
#define COMPUTEOUTCODE           ComputeOutCode
#define ENCLOSEPOINTS_EPSILON    1
#define SDL_RECT_CAN_OVERFLOW    SDL_RectCanOverflow
#define SDL_HASINTERSECTION      SDL_HasRectIntersection
#define SDL_INTERSECTRECT        SDL_GetRectIntersection
#define SDL_RECTEMPTY            SDL_RectEmpty
#define SDL_UNIONRECT            SDL_GetRectUnion
#define SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#define SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_લીટી_Intersection
#અન્તર્ભાવ "SDL_rect_impl.h"

#define RECTTYPE                 SDL_FRect
#define POINTTYPE                SDL_FPoint
#define SCALARTYPE               દશાંશ
#define BIGSCALARTYPE            દ્વિગુણ
#define COMPUTEOUTCODE           ComputeOutCodeFloat
#define ENCLOSEPOINTS_EPSILON    0.0f
#define SDL_RECT_CAN_OVERFLOW    SDL_RectCanOverflowFloat
#define SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#define SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#define SDL_RECTEMPTY            SDL_RectEmptyFloat
#define SDL_UNIONRECT            SDL_GetRectUnionFloat
#define SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#define SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_લીટી_Intersection_Float
#અન્તર્ભાવ "SDL_rect_impl.h"

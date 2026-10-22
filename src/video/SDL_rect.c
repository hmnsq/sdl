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

#समावेश "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_GetSpanEnclosingRect(पूर्णांक width, पूर्णांक height,
                         पूर्णांक numrects, स्थिर SDL_Rect *rects, SDL_Rect *span)
{
    पूर्णांक i;
    पूर्णांक span_y1, span_y2;
    पूर्णांक rect_y1, rect_y2;

    CHECK_PARAM(width < 1) {
        SDL_InvalidParamError("width");
        वापस false;
    }
    CHECK_PARAM(height < 1) {
        SDL_InvalidParamError("height");
        वापस false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        वापस false;
    }
    CHECK_PARAM(!span) {
        SDL_InvalidParamError("span");
        वापस false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        वापस false;
    }

    // Initialize to empty rect
    span_y1 = height;
    span_y2 = 0;

    क्रम (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        अगर (rect_y1 < 0) {
            span_y1 = 0;
        } अन्यथा अगर (rect_y1 < span_y1) {
            span_y1 = rect_y1;
        }
        अगर (rect_y2 > height) {
            span_y2 = height;
        } अन्यथा अगर (rect_y2 > span_y2) {
            span_y2 = rect_y2;
        }
    }
    अगर (span_y2 > span_y1) {
        span->x = 0;
        span->y = span_y1;
        span->w = width;
        span->h = (span_y2 - span_y1);
        वापस true;
    }
    वापस false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#घोषणा CODE_BOTTOM 1
#घोषणा CODE_शीर्ष    2
#घोषणा CODE_बायाँ   4
#घोषणा CODE_दायाँ  8

// Same code twice, for float and int versions...
#घोषणा RECTTYPE                 SDL_Rect
#घोषणा POINTTYPE                SDL_Point
#घोषणा SCALARTYPE               पूर्णांक
#घोषणा BIGSCALARTYPE            Sint64
#घोषणा COMPUTEOUTCODE           ComputeOutCode
#घोषणा ENCLOSEPOINTS_EPSILON    1
#घोषणा SDL_RECT_CAN_OVERFLOW    SDL_RectCanOverflow
#घोषणा SDL_HASINTERSECTION      SDL_HasRectIntersection
#घोषणा SDL_INTERSECTRECT        SDL_GetRectIntersection
#घोषणा SDL_RECTEMPTY            SDL_RectEmpty
#घोषणा SDL_UNIONRECT            SDL_GetRectUnion
#घोषणा SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#घोषणा SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_पंक्ति_Intersection
#समावेश "SDL_rect_impl.h"

#घोषणा RECTTYPE                 SDL_FRect
#घोषणा POINTTYPE                SDL_FPoint
#घोषणा SCALARTYPE               भग्न
#घोषणा BIGSCALARTYPE            द्विगुन
#घोषणा COMPUTEOUTCODE           ComputeOutCodeFloat
#घोषणा ENCLOSEPOINTS_EPSILON    0.0f
#घोषणा SDL_RECT_CAN_OVERFLOW    SDL_RectCanOverflowFloat
#घोषणा SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#घोषणा SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#घोषणा SDL_RECTEMPTY            SDL_RectEmptyFloat
#घोषणा SDL_UNIONRECT            SDL_GetRectUnionFloat
#घोषणा SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#घोषणा SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_पंक्ति_Intersection_Float
#समावेश "SDL_rect_impl.h"

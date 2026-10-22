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

#అన్తర్భావ "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_Get_పరిధి_Enclosing_Rect(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                         పూర్ణాంకం numrects, స్థిరరాశి SDL_Rect *rects, SDL_Rect *పరిధి)
{
    పూర్ణాంకం i;
    పూర్ణాంకం పరిధి_y1, పరిధి_y2;
    పూర్ణాంకం rect_y1, rect_y2;

    CHECK_PARAM(వెడల్పు < 1) {
        SDL_InvalidParamError("width");
        తిరిగి false;
    }
    CHECK_PARAM(ఎత్తు < 1) {
        SDL_InvalidParamError("height");
        తిరిగి false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        తిరిగి false;
    }
    CHECK_PARAM(!పరిధి) {
        SDL_InvalidParamError("span");
        తిరిగి false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        తిరిగి false;
    }

    // Initialize to empty rect
    పరిధి_y1 = ఎత్తు;
    పరిధి_y2 = 0;

    కొరకు (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        ఒకవేళ (rect_y1 < 0) {
            పరిధి_y1 = 0;
        } లేకపోతే ఒకవేళ (rect_y1 < పరిధి_y1) {
            పరిధి_y1 = rect_y1;
        }
        ఒకవేళ (rect_y2 > ఎత్తు) {
            పరిధి_y2 = ఎత్తు;
        } లేకపోతే ఒకవేళ (rect_y2 > పరిధి_y2) {
            పరిధి_y2 = rect_y2;
        }
    }
    ఒకవేళ (పరిధి_y2 > పరిధి_y1) {
        పరిధి->x = 0;
        పరిధి->y = పరిధి_y1;
        పరిధి->w = వెడల్పు;
        పరిధి->h = (పరిధి_y2 - పరిధి_y1);
        తిరిగి true;
    }
    తిరిగి false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#నిర్వచించు సంకేతం_BOTTOM 1
#నిర్వచించు సంకేతం_శిఖరం    2
#నిర్వచించు సంకేతం_ఎడమ   4
#నిర్వచించు సంకేతం_కుడి  8

// Same code twice, for float and int versions...
#నిర్వచించు RECTTYPE                 SDL_Rect
#నిర్వచించు POINTTYPE                SDL_బిందువు
#నిర్వచించు SCALARTYPE               పూర్ణాంకం
#నిర్వచించు BIGSCALARTYPE            Sint64
#నిర్వచించు COMPUTEOUTCODE           Compute_బహిర్గతం_సంకేతం
#నిర్వచించు ENCLOSEPOINTS_EPSILON    1
#నిర్వచించు SDL_RECT_CAN_అధికప్రవాహం    SDL_Rect_Can_అధికప్రవాహం
#నిర్వచించు SDL_HASINTERSECTION      SDL_HasRectIntersection
#నిర్వచించు SDL_INTERSECTRECT        SDL_GetRectIntersection
#నిర్వచించు SDL_RECTEMPTY            SDL_Rect_ఖాళీలు
#నిర్వచించు SDL_UNIONRECT            SDL_GetRectUnion
#నిర్వచించు SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#నిర్వచించు SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_పంక్తి_Intersection
#అన్తర్భావ "SDL_rect_impl.h"

#నిర్వచించు RECTTYPE                 SDL_FRect
#నిర్వచించు POINTTYPE                SDL_FPoint
#నిర్వచించు SCALARTYPE               దశాంశం
#నిర్వచించు BIGSCALARTYPE            ద్విగుణ
#నిర్వచించు COMPUTEOUTCODE           Compute_బహిర్గతం_సంకేతం_Float
#నిర్వచించు ENCLOSEPOINTS_EPSILON    0.0f
#నిర్వచించు SDL_RECT_CAN_అధికప్రవాహం    SDL_Rect_Can_అధికప్రవాహం_Float
#నిర్వచించు SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#నిర్వచించు SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#నిర్వచించు SDL_RECTEMPTY            SDL_Rect_ఖాళీలు_Float
#నిర్వచించు SDL_UNIONRECT            SDL_GetRectUnionFloat
#నిర్వచించు SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#నిర్వచించు SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_పంక్తి_Intersection_Float
#అన్తర్భావ "SDL_rect_impl.h"

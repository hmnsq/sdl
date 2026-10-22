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
#ضمن "SDL_internal.h"

#ضمن "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_Get_پراختیا_Enclosing_Rect(صحيح پلنوالی, صحيح لوړوالی,
                         صحيح numrects, ثابت SDL_Rect *rects, SDL_Rect *پراختیا)
{
    صحيح i;
    صحيح پراختیا_y1, پراختیا_y2;
    صحيح rect_y1, rect_y2;

    CHECK_PARAM(پلنوالی < 1) {
        SDL_InvalidParamError("width");
        أرجع false;
    }
    CHECK_PARAM(لوړوالی < 1) {
        SDL_InvalidParamError("height");
        أرجع false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        أرجع false;
    }
    CHECK_PARAM(!پراختیا) {
        SDL_InvalidParamError("span");
        أرجع false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        أرجع false;
    }

    // Initialize to empty rect
    پراختیا_y1 = لوړوالی;
    پراختیا_y2 = 0;

    لكل (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        إذا (rect_y1 < 0) {
            پراختیا_y1 = 0;
        } وإلا إذا (rect_y1 < پراختیا_y1) {
            پراختیا_y1 = rect_y1;
        }
        إذا (rect_y2 > لوړوالی) {
            پراختیا_y2 = لوړوالی;
        } وإلا إذا (rect_y2 > پراختیا_y2) {
            پراختیا_y2 = rect_y2;
        }
    }
    إذا (پراختیا_y2 > پراختیا_y1) {
        پراختیا->x = 0;
        پراختیا->y = پراختیا_y1;
        پراختیا->w = پلنوالی;
        پراختیا->h = (پراختیا_y2 - پراختیا_y1);
        أرجع true;
    }
    أرجع false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#تعریف_کړه کوډ_BOTTOM 1
#تعریف_کړه کوډ_سر    2
#تعریف_کړه کوډ_کیڼ   4
#تعریف_کړه کوډ_ښی  8

// Same code twice, for float and int versions...
#تعریف_کړه RECTTYPE                 SDL_Rect
#تعریف_کړه POINTTYPE                SDL_ټکی
#تعریف_کړه SCALARTYPE               صحيح
#تعریف_کړه BIGSCALARTYPE            Sint64
#تعریف_کړه COMPUTEOUTCODE           Compute_بهر_کوډ
#تعریف_کړه ENCLOSEPOINTS_EPSILON    1
#تعریف_کړه SDL_RECT_CAN_ډکېدنه    SDL_Rect_Can_ډکېدنه
#تعریف_کړه SDL_HASINTERSECTION      SDL_HasRectIntersection
#تعریف_کړه SDL_INTERSECTRECT        SDL_GetRectIntersection
#تعریف_کړه SDL_RECTEMPTY            SDL_Rect_تشه
#تعریف_کړه SDL_UNIONRECT            SDL_GetRectUnion
#تعریف_کړه SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#تعریف_کړه SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_کرښه_Intersection
#ضمن "SDL_rect_impl.h"

#تعریف_کړه RECTTYPE                 SDL_FRect
#تعریف_کړه POINTTYPE                SDL_FPoint
#تعریف_کړه SCALARTYPE               عائم
#تعریف_کړه BIGSCALARTYPE            مزدوج
#تعریف_کړه COMPUTEOUTCODE           Compute_بهر_کوډ_Float
#تعریف_کړه ENCLOSEPOINTS_EPSILON    0.0f
#تعریف_کړه SDL_RECT_CAN_ډکېدنه    SDL_Rect_Can_ډکېدنه_Float
#تعریف_کړه SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#تعریف_کړه SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#تعریف_کړه SDL_RECTEMPTY            SDL_Rect_تشه_Float
#تعریف_کړه SDL_UNIONRECT            SDL_GetRectUnionFloat
#تعریف_کړه SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#تعریف_کړه SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_کرښه_Intersection_Float
#ضمن "SDL_rect_impl.h"

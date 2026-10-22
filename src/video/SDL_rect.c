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
bool SDL_Get_بازه_Enclosing_Rect(صحيح عرض, صحيح ارتفاع,
                         صحيح numrects, ثابت SDL_Rect *rects, SDL_Rect *بازه)
{
    صحيح i;
    صحيح بازه_y1, بازه_y2;
    صحيح rect_y1, rect_y2;

    CHECK_PARAM(عرض < 1) {
        SDL_InvalidParamError("width");
        أرجع false;
    }
    CHECK_PARAM(ارتفاع < 1) {
        SDL_InvalidParamError("height");
        أرجع false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        أرجع false;
    }
    CHECK_PARAM(!بازه) {
        SDL_InvalidParamError("span");
        أرجع false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        أرجع false;
    }

    // Initialize to empty rect
    بازه_y1 = ارتفاع;
    بازه_y2 = 0;

    لكل (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        إذا (rect_y1 < 0) {
            بازه_y1 = 0;
        } وإلا إذا (rect_y1 < بازه_y1) {
            بازه_y1 = rect_y1;
        }
        إذا (rect_y2 > ارتفاع) {
            بازه_y2 = ارتفاع;
        } وإلا إذا (rect_y2 > بازه_y2) {
            بازه_y2 = rect_y2;
        }
    }
    إذا (بازه_y2 > بازه_y1) {
        بازه->x = 0;
        بازه->y = بازه_y1;
        بازه->w = عرض;
        بازه->h = (بازه_y2 - بازه_y1);
        أرجع true;
    }
    أرجع false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#تعریف_کن کد_BOTTOM 1
#تعریف_کن کد_بالاترین    2
#تعریف_کن کد_چپ   4
#تعریف_کن کد_راست  8

// Same code twice, for float and int versions...
#تعریف_کن RECTTYPE                 SDL_Rect
#تعریف_کن POINTTYPE                SDL_نقطه
#تعریف_کن SCALARTYPE               صحيح
#تعریف_کن BIGSCALARTYPE            Sint64
#تعریف_کن COMPUTEOUTCODE           Compute_بیرون_کد
#تعریف_کن ENCLOSEPOINTS_EPSILON    1
#تعریف_کن SDL_RECT_CAN_سرریز    SDL_Rect_Can_سرریز
#تعریف_کن SDL_HASINTERSECTION      SDL_HasRectIntersection
#تعریف_کن SDL_INTERSECTRECT        SDL_GetRectIntersection
#تعریف_کن SDL_RECTEMPTY            SDL_Rect_خالی
#تعریف_کن SDL_UNIONRECT            SDL_GetRectUnion
#تعریف_کن SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#تعریف_کن SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سطر_Intersection
#ضمن "SDL_rect_impl.h"

#تعریف_کن RECTTYPE                 SDL_FRect
#تعریف_کن POINTTYPE                SDL_FPoint
#تعریف_کن SCALARTYPE               عائم
#تعریف_کن BIGSCALARTYPE            مزدوج
#تعریف_کن COMPUTEOUTCODE           Compute_بیرون_کد_Float
#تعریف_کن ENCLOSEPOINTS_EPSILON    0.0f
#تعریف_کن SDL_RECT_CAN_سرریز    SDL_Rect_Can_سرریز_Float
#تعریف_کن SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#تعریف_کن SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#تعریف_کن SDL_RECTEMPTY            SDL_Rect_خالی_Float
#تعریف_کن SDL_UNIONRECT            SDL_GetRectUnionFloat
#تعریف_کن SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#تعریف_کن SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سطر_Intersection_Float
#ضمن "SDL_rect_impl.h"

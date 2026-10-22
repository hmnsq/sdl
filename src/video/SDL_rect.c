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
bool SDL_Get_وسعت_Enclosing_Rect(صحيح چوڑائی, صحيح اچائی,
                         صحيح numrects, ثابت SDL_Rect *rects, SDL_Rect *وسعت)
{
    صحيح i;
    صحيح وسعت_y1, وسعت_y2;
    صحيح rect_y1, rect_y2;

    CHECK_PARAM(چوڑائی < 1) {
        SDL_InvalidParamError("width");
        أرجع false;
    }
    CHECK_PARAM(اچائی < 1) {
        SDL_InvalidParamError("height");
        أرجع false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        أرجع false;
    }
    CHECK_PARAM(!وسعت) {
        SDL_InvalidParamError("span");
        أرجع false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        أرجع false;
    }

    // Initialize to empty rect
    وسعت_y1 = اچائی;
    وسعت_y2 = 0;

    لكل (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        إذا (rect_y1 < 0) {
            وسعت_y1 = 0;
        } وإلا إذا (rect_y1 < وسعت_y1) {
            وسعت_y1 = rect_y1;
        }
        إذا (rect_y2 > اچائی) {
            وسعت_y2 = اچائی;
        } وإلا إذا (rect_y2 > وسعت_y2) {
            وسعت_y2 = rect_y2;
        }
    }
    إذا (وسعت_y2 > وسعت_y1) {
        وسعت->x = 0;
        وسعت->y = وسعت_y1;
        وسعت->w = چوڑائی;
        وسعت->h = (وسعت_y2 - وسعت_y1);
        أرجع true;
    }
    أرجع false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#تعریف_کرو کوڈ_BOTTOM 1
#تعریف_کرو کوڈ_چوٹی    2
#تعریف_کرو کوڈ_بایاں   4
#تعریف_کرو کوڈ_دایاں  8

// Same code twice, for float and int versions...
#تعریف_کرو RECTTYPE                 SDL_Rect
#تعریف_کرو POINTTYPE                SDL_نقطہ
#تعریف_کرو SCALARTYPE               صحيح
#تعریف_کرو BIGSCALARTYPE            Sint64
#تعریف_کرو COMPUTEOUTCODE           Compute_باہرلا_کوڈ
#تعریف_کرو ENCLOSEPOINTS_EPSILON    1
#تعریف_کرو SDL_RECT_CAN_حد_توں_ودھ    SDL_Rect_Can_حد_توں_ودھ
#تعریف_کرو SDL_HASINTERSECTION      SDL_HasRectIntersection
#تعریف_کرو SDL_INTERSECTRECT        SDL_GetRectIntersection
#تعریف_کرو SDL_RECTEMPTY            SDL_Rect_خالی_تھاواں
#تعریف_کرو SDL_UNIONRECT            SDL_GetRectUnion
#تعریف_کرو SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#تعریف_کرو SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سطر_Intersection
#ضمن "SDL_rect_impl.h"

#تعریف_کرو RECTTYPE                 SDL_FRect
#تعریف_کرو POINTTYPE                SDL_FPoint
#تعریف_کرو SCALARTYPE               عائم
#تعریف_کرو BIGSCALARTYPE            مزدوج
#تعریف_کرو COMPUTEOUTCODE           Compute_باہرلا_کوڈ_Float
#تعریف_کرو ENCLOSEPOINTS_EPSILON    0.0f
#تعریف_کرو SDL_RECT_CAN_حد_توں_ودھ    SDL_Rect_Can_حد_توں_ودھ_Float
#تعریف_کرو SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#تعریف_کرو SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#تعریف_کرو SDL_RECTEMPTY            SDL_Rect_خالی_تھاواں_Float
#تعریف_کرو SDL_UNIONRECT            SDL_GetRectUnionFloat
#تعریف_کرو SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#تعریف_کرو SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سطر_Intersection_Float
#ضمن "SDL_rect_impl.h"

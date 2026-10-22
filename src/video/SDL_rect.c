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
bool SDL_Get_وسعت_Enclosing_Rect(صحيح ويڪر, صحيح اوچائي,
                         صحيح numrects, ثابت SDL_Rect *rects, SDL_Rect *وسعت)
{
    صحيح i;
    صحيح وسعت_y1, وسعت_y2;
    صحيح rect_y1, rect_y2;

    CHECK_PARAM(ويڪر < 1) {
        SDL_InvalidParamError("width");
        أرجع false;
    }
    CHECK_PARAM(اوچائي < 1) {
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
    وسعت_y1 = اوچائي;
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
        إذا (rect_y2 > اوچائي) {
            وسعت_y2 = اوچائي;
        } وإلا إذا (rect_y2 > وسعت_y2) {
            وسعت_y2 = rect_y2;
        }
    }
    إذا (وسعت_y2 > وسعت_y1) {
        وسعت->x = 0;
        وسعت->y = وسعت_y1;
        وسعت->w = ويڪر;
        وسعت->h = (وسعت_y2 - وسعت_y1);
        أرجع true;
    }
    أرجع false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#وصف_ڪريو ڪوڊ_BOTTOM 1
#وصف_ڪريو ڪوڊ_چوٽي    2
#وصف_ڪريو ڪوڊ_کاٻو   4
#وصف_ڪريو ڪوڊ_ساڄو  8

// Same code twice, for float and int versions...
#وصف_ڪريو RECTTYPE                 SDL_Rect
#وصف_ڪريو POINTTYPE                SDL_نقطو
#وصف_ڪريو SCALARTYPE               صحيح
#وصف_ڪريو BIGSCALARTYPE            Sint64
#وصف_ڪريو COMPUTEOUTCODE           Compute_ٻاهريون_ڪوڊ
#وصف_ڪريو ENCLOSEPOINTS_EPSILON    1
#وصف_ڪريو SDL_RECT_CAN_حد_کان_مٿي    SDL_Rect_Can_حد_کان_مٿي
#وصف_ڪريو SDL_HASINTERSECTION      SDL_HasRectIntersection
#وصف_ڪريو SDL_INTERSECTRECT        SDL_GetRectIntersection
#وصف_ڪريو SDL_RECTEMPTY            SDL_Rect_خالي_جايون
#وصف_ڪريو SDL_UNIONRECT            SDL_GetRectUnion
#وصف_ڪريو SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#وصف_ڪريو SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سٽ_Intersection
#ضمن "SDL_rect_impl.h"

#وصف_ڪريو RECTTYPE                 SDL_FRect
#وصف_ڪريو POINTTYPE                SDL_FPoint
#وصف_ڪريو SCALARTYPE               عائم
#وصف_ڪريو BIGSCALARTYPE            مزدوج
#وصف_ڪريو COMPUTEOUTCODE           Compute_ٻاهريون_ڪوڊ_Float
#وصف_ڪريو ENCLOSEPOINTS_EPSILON    0.0f
#وصف_ڪريو SDL_RECT_CAN_حد_کان_مٿي    SDL_Rect_Can_حد_کان_مٿي_Float
#وصف_ڪريو SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#وصف_ڪريو SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#وصف_ڪريو SDL_RECTEMPTY            SDL_Rect_خالي_جايون_Float
#وصف_ڪريو SDL_UNIONRECT            SDL_GetRectUnionFloat
#وصف_ڪريو SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#وصف_ڪريو SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سٽ_Intersection_Float
#ضمن "SDL_rect_impl.h"

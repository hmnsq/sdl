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
#شامل "SDL_internal.h"

#شامل "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_Get_وسعت_Enclosing_Rect(صحیح چوڑائی, صحیح اونچائی,
                         صحیح numrects, ثابت SDL_Rect *rects, SDL_Rect *وسعت)
{
    صحیح i;
    صحیح وسعت_y1, وسعت_y2;
    صحیح rect_y1, rect_y2;

    CHECK_PARAM(چوڑائی < 1) {
        SDL_InvalidParamError("width");
        واپس false;
    }
    CHECK_PARAM(اونچائی < 1) {
        SDL_InvalidParamError("height");
        واپس false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        واپس false;
    }
    CHECK_PARAM(!وسعت) {
        SDL_InvalidParamError("span");
        واپس false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        واپس false;
    }

    // Initialize to empty rect
    وسعت_y1 = اونچائی;
    وسعت_y2 = 0;

    برائے (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        اگر (rect_y1 < 0) {
            وسعت_y1 = 0;
        } ورنہ اگر (rect_y1 < وسعت_y1) {
            وسعت_y1 = rect_y1;
        }
        اگر (rect_y2 > اونچائی) {
            وسعت_y2 = اونچائی;
        } ورنہ اگر (rect_y2 > وسعت_y2) {
            وسعت_y2 = rect_y2;
        }
    }
    اگر (وسعت_y2 > وسعت_y1) {
        وسعت->x = 0;
        وسعت->y = وسعت_y1;
        وسعت->w = چوڑائی;
        وسعت->h = (وسعت_y2 - وسعت_y1);
        واپس true;
    }
    واپس false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#تعریف_کرو رمز_BOTTOM 1
#تعریف_کرو رمز_چوٹی    2
#تعریف_کرو رمز_بایاں   4
#تعریف_کرو رمز_دایاں  8

// Same code twice, for float and int versions...
#تعریف_کرو RECTTYPE                 SDL_Rect
#تعریف_کرو POINTTYPE                SDL_نقطہ
#تعریف_کرو SCALARTYPE               صحیح
#تعریف_کرو BIGSCALARTYPE            Sint64
#تعریف_کرو COMPUTEOUTCODE           Compute_برآمد_رمز
#تعریف_کرو ENCLOSEPOINTS_EPSILON    1
#تعریف_کرو SDL_RECT_CAN_حد_سے_تجاوز    SDL_Rect_Can_حد_سے_تجاوز
#تعریف_کرو SDL_HASINTERSECTION      SDL_HasRectIntersection
#تعریف_کرو SDL_INTERSECTRECT        SDL_GetRectIntersection
#تعریف_کرو SDL_RECTEMPTY            SDL_Rect_خالی_خانے
#تعریف_کرو SDL_UNIONRECT            SDL_GetRectUnion
#تعریف_کرو SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#تعریف_کرو SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سطر_Intersection
#شامل "SDL_rect_impl.h"

#تعریف_کرو RECTTYPE                 SDL_FRect
#تعریف_کرو POINTTYPE                SDL_FPoint
#تعریف_کرو SCALARTYPE               اعشاری
#تعریف_کرو BIGSCALARTYPE            دوہرا
#تعریف_کرو COMPUTEOUTCODE           Compute_برآمد_رمز_Float
#تعریف_کرو ENCLOSEPOINTS_EPSILON    0.0f
#تعریف_کرو SDL_RECT_CAN_حد_سے_تجاوز    SDL_Rect_Can_حد_سے_تجاوز_Float
#تعریف_کرو SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#تعریف_کرو SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#تعریف_کرو SDL_RECTEMPTY            SDL_Rect_خالی_خانے_Float
#تعریف_کرو SDL_UNIONRECT            SDL_GetRectUnionFloat
#تعریف_کرو SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#تعریف_کرو SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_سطر_Intersection_Float
#شامل "SDL_rect_impl.h"

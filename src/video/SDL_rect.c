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

#अन्तर्भाव "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_Get_विस्तृतिः_Enclosing_Rect(पूर्णाङ्क विस्तारः, पूर्णाङ्क height,
                         पूर्णाङ्क numrects, ध्रुव SDL_Rect *rects, SDL_Rect *विस्तृतिः)
{
    पूर्णाङ्क i;
    पूर्णाङ्क विस्तृतिः_y1, विस्तृतिः_y2;
    पूर्णाङ्क rect_y1, rect_y2;

    CHECK_PARAM(विस्तारः < 1) {
        SDL_InvalidParamError("width");
        प्रत्यागम false;
    }
    CHECK_PARAM(height < 1) {
        SDL_InvalidParamError("height");
        प्रत्यागम false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        प्रत्यागम false;
    }
    CHECK_PARAM(!विस्तृतिः) {
        SDL_InvalidParamError("span");
        प्रत्यागम false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        प्रत्यागम false;
    }

    // Initialize to empty rect
    विस्तृतिः_y1 = height;
    विस्तृतिः_y2 = 0;

    प्रति (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        यदि (rect_y1 < 0) {
            विस्तृतिः_y1 = 0;
        } अन्यथा यदि (rect_y1 < विस्तृतिः_y1) {
            विस्तृतिः_y1 = rect_y1;
        }
        यदि (rect_y2 > height) {
            विस्तृतिः_y2 = height;
        } अन्यथा यदि (rect_y2 > विस्तृतिः_y2) {
            विस्तृतिः_y2 = rect_y2;
        }
    }
    यदि (विस्तृतिः_y2 > विस्तृतिः_y1) {
        विस्तृतिः->x = 0;
        विस्तृतिः->y = विस्तृतिः_y1;
        विस्तृतिः->w = विस्तारः;
        विस्तृतिः->h = (विस्तृतिः_y2 - विस्तृतिः_y1);
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#परिभाषय संहिता_BOTTOM 1
#परिभाषय संहिता_शिखरम्    2
#परिभाषय संहिता_वामः   4
#परिभाषय संहिता_दक्षिणः  8

// Same code twice, for float and int versions...
#परिभाषय RECTTYPE                 SDL_Rect
#परिभाषय POINTTYPE                SDL_Point
#परिभाषय SCALARTYPE               पूर्णाङ्क
#परिभाषय BIGSCALARTYPE            Sint64
#परिभाषय COMPUTEOUTCODE           Compute_बहिर्गमनम्_संहिता
#परिभाषय ENCLOSEPOINTS_EPSILON    1
#परिभाषय SDL_RECT_CAN_अतिप्रवाहः    SDL_Rect_Can_अतिप्रवाहः
#परिभाषय SDL_HASINTERSECTION      SDL_HasRectIntersection
#परिभाषय SDL_INTERSECTRECT        SDL_GetRectIntersection
#परिभाषय SDL_RECTEMPTY            SDL_Rect_रिक्तानि
#परिभाषय SDL_UNIONRECT            SDL_GetRectUnion
#परिभाषय SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#परिभाषय SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_पङ्क्तिः_Intersection
#अन्तर्भाव "SDL_rect_impl.h"

#परिभाषय RECTTYPE                 SDL_FRect
#परिभाषय POINTTYPE                SDL_FPoint
#परिभाषय SCALARTYPE               भिन्न
#परिभाषय BIGSCALARTYPE            द्विगुण
#परिभाषय COMPUTEOUTCODE           Compute_बहिर्गमनम्_संहिता_Float
#परिभाषय ENCLOSEPOINTS_EPSILON    0.0f
#परिभाषय SDL_RECT_CAN_अतिप्रवाहः    SDL_Rect_Can_अतिप्रवाहः_Float
#परिभाषय SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#परिभाषय SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#परिभाषय SDL_RECTEMPTY            SDL_Rect_रिक्तानि_Float
#परिभाषय SDL_UNIONRECT            SDL_GetRectUnionFloat
#परिभाषय SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#परिभाषय SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_पङ्क्तिः_Intersection_Float
#अन्तर्भाव "SDL_rect_impl.h"

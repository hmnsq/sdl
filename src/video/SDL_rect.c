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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_Get_ਵਿਸਤਾਰ_Enclosing_Rect(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                         ਪੂਰਨ numrects, ਅਚਲ SDL_Rect *rects, SDL_Rect *ਵਿਸਤਾਰ)
{
    ਪੂਰਨ i;
    ਪੂਰਨ ਵਿਸਤਾਰ_y1, ਵਿਸਤਾਰ_y2;
    ਪੂਰਨ rect_y1, rect_y2;

    CHECK_PARAM(ਚੌੜਾਈ < 1) {
        SDL_InvalidParamError("width");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(ਉਚਾਈ < 1) {
        SDL_InvalidParamError("height");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!ਵਿਸਤਾਰ) {
        SDL_InvalidParamError("span");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        ਵਾਪਸ false;
    }

    // Initialize to empty rect
    ਵਿਸਤਾਰ_y1 = ਉਚਾਈ;
    ਵਿਸਤਾਰ_y2 = 0;

    ਲਈ (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        ਜੇ (rect_y1 < 0) {
            ਵਿਸਤਾਰ_y1 = 0;
        } ਨਹੀਂਤਾਂ ਜੇ (rect_y1 < ਵਿਸਤਾਰ_y1) {
            ਵਿਸਤਾਰ_y1 = rect_y1;
        }
        ਜੇ (rect_y2 > ਉਚਾਈ) {
            ਵਿਸਤਾਰ_y2 = ਉਚਾਈ;
        } ਨਹੀਂਤਾਂ ਜੇ (rect_y2 > ਵਿਸਤਾਰ_y2) {
            ਵਿਸਤਾਰ_y2 = rect_y2;
        }
    }
    ਜੇ (ਵਿਸਤਾਰ_y2 > ਵਿਸਤਾਰ_y1) {
        ਵਿਸਤਾਰ->x = 0;
        ਵਿਸਤਾਰ->y = ਵਿਸਤਾਰ_y1;
        ਵਿਸਤਾਰ->w = ਚੌੜਾਈ;
        ਵਿਸਤਾਰ->h = (ਵਿਸਤਾਰ_y2 - ਵਿਸਤਾਰ_y1);
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੋਡ_BOTTOM 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੋਡ_ਸਿਖਰ    2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੋਡ_ਖੱਬਾ   4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੋਡ_ਸੱਜਾ  8

// Same code twice, for float and int versions...
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RECTTYPE                 SDL_Rect
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POINTTYPE                SDL_ਬਿੰਦੂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCALARTYPE               ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BIGSCALARTYPE            Sint64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COMPUTEOUTCODE           Compute_ਬਾਹਰਲਾ_ਕੋਡ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENCLOSEPOINTS_EPSILON    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_RECT_CAN_ਉਛਾਲ    SDL_Rect_Can_ਉਛਾਲ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_HASINTERSECTION      SDL_HasRectIntersection
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_INTERSECTRECT        SDL_GetRectIntersection
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_RECTEMPTY            SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_UNIONRECT            SDL_GetRectUnion
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_ਸਤਰ_Intersection
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rect_impl.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RECTTYPE                 SDL_FRect
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POINTTYPE                SDL_FPoint
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCALARTYPE               ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BIGSCALARTYPE            ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COMPUTEOUTCODE           Compute_ਬਾਹਰਲਾ_ਕੋਡ_Float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENCLOSEPOINTS_EPSILON    0.0f
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_RECT_CAN_ਉਛਾਲ    SDL_Rect_Can_ਉਛਾਲ_Float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_RECTEMPTY            SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ_Float
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_UNIONRECT            SDL_GetRectUnionFloat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_ਸਤਰ_Intersection_Float
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rect_impl.h"

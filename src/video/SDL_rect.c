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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_rect_c.h"

/* There's no float version of this at the moment, because it's not a public API
   and internally we only need the int version. */
bool SDL_Get_ಹರವು_Enclosing_Rect(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ,
                         ಪೂರ್ಣಾಂಕ numrects, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, SDL_Rect *ಹರವು)
{
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ ಹರವು_y1, ಹರವು_y2;
    ಪೂರ್ಣಾಂಕ rect_y1, rect_y2;

    CHECK_PARAM(ಅಗಲ < 1) {
        SDL_InvalidParamError("width");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(ಎತ್ತರ < 1) {
        SDL_InvalidParamError("height");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!rects) {
        SDL_InvalidParamError("rects");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!ಹರವು) {
        SDL_InvalidParamError("span");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(numrects < 1) {
        SDL_InvalidParamError("numrects");
        ಹಿಂತಿರುಗಿ false;
    }

    // Initialize to empty rect
    ಹರವು_y1 = ಎತ್ತರ;
    ಹರವು_y2 = 0;

    ಗಾಗಿ (i = 0; i < numrects; ++i) {
        rect_y1 = rects[i].y;
        rect_y2 = rect_y1 + rects[i].h;

        // Clip out of bounds rectangles, and expand span rect
        ಆದರೆ (rect_y1 < 0) {
            ಹರವು_y1 = 0;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rect_y1 < ಹರವು_y1) {
            ಹರವು_y1 = rect_y1;
        }
        ಆದರೆ (rect_y2 > ಎತ್ತರ) {
            ಹರವು_y2 = ಎತ್ತರ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rect_y2 > ಹರವು_y2) {
            ಹರವು_y2 = rect_y2;
        }
    }
    ಆದರೆ (ಹರವು_y2 > ಹರವು_y1) {
        ಹರವು->x = 0;
        ಹರವು->y = ಹರವು_y1;
        ಹರವು->w = ಅಗಲ;
        ಹರವು->h = (ಹರವು_y2 - ಹರವು_y1);
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

// For use with the Cohen-Sutherland algorithm for line clipping, in SDL_rect_impl.h
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಂಕೇತ_BOTTOM 1
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಂಕೇತ_ತುದಿ    2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಂಕೇತ_ಎಡ   4
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಂಕೇತ_ಬಲ  8

// Same code twice, for float and int versions...
#ವ್ಯಾಖ್ಯಾನಿಸು RECTTYPE                 SDL_Rect
#ವ್ಯಾಖ್ಯಾನಿಸು POINTTYPE                SDL_ಬಿಂದು
#ವ್ಯಾಖ್ಯಾನಿಸು SCALARTYPE               ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು BIGSCALARTYPE            Sint64
#ವ್ಯಾಖ್ಯಾನಿಸು COMPUTEOUTCODE           Compute_ಹೊರಹೋಗು_ಸಂಕೇತ
#ವ್ಯಾಖ್ಯಾನಿಸು ENCLOSEPOINTS_EPSILON    1
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ    SDL_Rect_Can_ಅತಿಪ್ರವಾಹ
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_HASINTERSECTION      SDL_HasRectIntersection
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_INTERSECTRECT        SDL_GetRectIntersection
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_RECTEMPTY            SDL_Rect_ಖಾಲಿಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_UNIONRECT            SDL_GetRectUnion
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPoints
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_ಸಾಲು_Intersection
#ಅನ್ತರ್ಭಾವ "SDL_rect_impl.h"

#ವ್ಯಾಖ್ಯಾನಿಸು RECTTYPE                 SDL_FRect
#ವ್ಯಾಖ್ಯಾನಿಸು POINTTYPE                SDL_FPoint
#ವ್ಯಾಖ್ಯಾನಿಸು SCALARTYPE               ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು BIGSCALARTYPE            ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು COMPUTEOUTCODE           Compute_ಹೊರಹೋಗು_ಸಂಕೇತ_Float
#ವ್ಯಾಖ್ಯಾನಿಸು ENCLOSEPOINTS_EPSILON    0.0f
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ    SDL_Rect_Can_ಅತಿಪ್ರವಾಹ_Float
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_HASINTERSECTION      SDL_HasRectIntersectionFloat
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_INTERSECTRECT        SDL_GetRectIntersectionFloat
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_RECTEMPTY            SDL_Rect_ಖಾಲಿಗಳು_Float
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_UNIONRECT            SDL_GetRectUnionFloat
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ENCLOSEPOINTS        SDL_GetRectEnclosingPointsFloat
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_INTERSECTRECTANDLINE SDL_Get_Rect_And_ಸಾಲು_Intersection_Float
#ಅನ್ತರ್ಭಾವ "SDL_rect_impl.h"

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

// This file is #included twice to support int and float versions with the same code.

ಸ್ಥಿರ bool SDL_RECT_CAN_OVERFLOW(ಧ್ರುವ RECTTYPE *rect)
{
    ಯದಿ (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool SDL_HASINTERSECTION(ಧ್ರುವ RECTTYPE *A, ಧ್ರುವ RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ಯದಿ (Bmin > Amin) {
        Amin = Bmin;
    }
    ಯದಿ (Bmax < Amax) {
        Amax = Bmax;
    }
    ಯದಿ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ಯದಿ (Bmin > Amin) {
        Amin = Bmin;
    }
    ಯದಿ (Bmax < Amax) {
        Amax = Bmax;
    }
    ಯದಿ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_INTERSECTRECT(ಧ್ರುವ RECTTYPE *A, ಧ್ರುವ RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ಯದಿ (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    ಯದಿ (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ಯದಿ (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    ಯದಿ (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    ಪ್ರತ್ಯಾಗಮ !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(ಧ್ರುವ RECTTYPE *A, ಧ್ರುವ RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("result");
    }

    ಯದಿ (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        ಯದಿ (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } ಅನ್ಯಥಾ { // A empty, B not empty
            *result = *B;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ಯದಿ (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    ಯದಿ (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ಯದಿ (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    ಯದಿ (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_ENCLOSEPOINTS(ಧ್ರುವ POINTTYPE *points, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, ಧ್ರುವ RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    ಪೂರ್ಣಾಙ್ಕ i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(ಎಣಿಕೆ < 1) {
        SDL_InvalidParamError("count");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (clip) {
        bool added = false;
        ಧ್ರುವ SCALARTYPE clip_minx = clip->x;
        ಧ್ರುವ SCALARTYPE clip_miny = clip->y;
        ಧ್ರುವ SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ಧ್ರುವ SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        ಯದಿ (SDL_RECTEMPTY(clip)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        ಪ್ರತಿ (i = 0; i < ಎಣಿಕೆ; ++i) {
            x = points[i].x;
            y = points[i].y;

            ಯದಿ (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                ಅನುವರ್ತ;
            }
            ಯದಿ (!added) {
                // Special case: if no result was requested, we are done
                ಯದಿ (!result) {
                    ಪ್ರತ್ಯಾಗಮ true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                ಅನುವರ್ತ;
            }
            ಯದಿ (x < minx) {
                minx = x;
            } ಅನ್ಯಥಾ ಯದಿ (x > maxx) {
                maxx = x;
            }
            ಯದಿ (y < miny) {
                miny = y;
            } ಅನ್ಯಥಾ ಯದಿ (y > maxy) {
                maxy = y;
            }
        }
        ಯದಿ (!added) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        // Special case: if no result was requested, we are done
        ಯದಿ (!result) {
            ಪ್ರತ್ಯಾಗಮ true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        ಪ್ರತಿ (i = 1; i < ಎಣಿಕೆ; ++i) {
            x = points[i].x;
            y = points[i].y;

            ಯದಿ (x < minx) {
                minx = x;
            } ಅನ್ಯಥಾ ಯದಿ (x > maxx) {
                maxx = x;
            }
            ಯದಿ (y < miny) {
                miny = y;
            } ಅನ್ಯಥಾ ಯದಿ (y > maxy) {
                maxy = y;
            }
        }
    }

    ಯದಿ (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

// Use the Cohen-Sutherland algorithm for line clipping
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ COMPUTEOUTCODE(ಧ್ರುವ RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    ಪೂರ್ಣಾಙ್ಕ code = 0;
    ಯದಿ (y < rect->y) {
        code |= CODE_ತುದಿ;
    } ಅನ್ಯಥಾ ಯದಿ (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    ಯದಿ (x < rect->x) {
        code |= CODE_ಎಡ;
    } ಅನ್ಯಥಾ ಯದಿ (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_ಬಲ;
    }
    ಪ್ರತ್ಯಾಗಮ code;
}

bool SDL_INTERSECTRECTANDLINE(ಧ್ರುವ RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    ಪೂರ್ಣಾಙ್ಕ outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (SDL_RECTEMPTY(rect)) {
        ಪ್ರತ್ಯಾಗಮ false; // Special case for empty rect
    }

    x1 = *X1;
    y1 = *Y1;
    x2 = *X2;
    y2 = *Y2;
    rectx1 = rect->x;
    recty1 = rect->y;
    rectx2 = rect->x + rect->w - ENCLOSEPOINTS_EPSILON;
    recty2 = rect->y + rect->h - ENCLOSEPOINTS_EPSILON;

    // Check to see if entire line is inside rect
    ಯದಿ (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // Check to see if entire line is to one side of rect
    ಯದಿ ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (y1 == y2) { // Horizontal line, easy to clip
        ಯದಿ (x1 < rectx1) {
            *X1 = rectx1;
        } ಅನ್ಯಥಾ ಯದಿ (x1 > rectx2) {
            *X1 = rectx2;
        }
        ಯದಿ (x2 < rectx1) {
            *X2 = rectx1;
        } ಅನ್ಯಥಾ ಯದಿ (x2 > rectx2) {
            *X2 = rectx2;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (x1 == x2) { // Vertical line, easy to clip
        ಯದಿ (y1 < recty1) {
            *Y1 = recty1;
        } ಅನ್ಯಥಾ ಯದಿ (y1 > recty2) {
            *Y1 = recty2;
        }
        ಯದಿ (y2 < recty1) {
            *Y2 = recty1;
        } ಅನ್ಯಥಾ ಯದಿ (y2 > recty2) {
            *Y2 = recty2;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    ಯಾವತ್ (outcode1 || outcode2) {
        ಯದಿ (outcode1 & outcode2) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        ಯದಿ (outcode1) {
            ಯದಿ (outcode1 & CODE_ತುದಿ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಅನ್ಯಥಾ ಯದಿ (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಅನ್ಯಥಾ ಯದಿ (outcode1 & CODE_ಎಡ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ಅನ್ಯಥಾ ಯದಿ (outcode1 & CODE_ಬಲ) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } ಅನ್ಯಥಾ {
            ಯದಿ (outcode2 & CODE_ತುದಿ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಅನ್ಯಥಾ ಯದಿ (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಅನ್ಯಥಾ ಯದಿ (outcode2 & CODE_ಎಡ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ಅನ್ಯಥಾ ಯದಿ (outcode2 & CODE_ಬಲ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-39b114.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x2 = x;
            y2 = y;
            outcode2 = COMPUTEOUTCODE(rect, x, y);
        }
    }
    *X1 = x1;
    *Y1 = y1;
    *X2 = x2;
    *Y2 = y2;
    ಪ್ರತ್ಯಾಗಮ true;
}

#undef RECTTYPE
#undef POINTTYPE
#undef SCALARTYPE
#undef BIGSCALARTYPE
#undef COMPUTEOUTCODE
#undef ENCLOSEPOINTS_EPSILON
#undef SDL_RECT_CAN_OVERFLOW
#undef SDL_HASINTERSECTION
#undef SDL_INTERSECTRECT
#undef SDL_RECTEMPTY
#undef SDL_UNIONRECT
#undef SDL_ENCLOSEPOINTS
#undef SDL_INTERSECTRECTANDLINE

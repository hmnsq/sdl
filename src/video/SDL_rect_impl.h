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

ସ୍ଥିର bool SDL_RECT_CAN_OVERFLOW(ଅଚଳ RECTTYPE *rect)
{
    ଯଦି (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

bool SDL_HASINTERSECTION(ଅଚଳ RECTTYPE *A, ଅଚଳ RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        ଫେରନ୍ତୁ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ଯଦି (Bmin > Amin) {
        Amin = Bmin;
    }
    ଯଦି (Bmax < Amax) {
        Amax = Bmax;
    }
    ଯଦି ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ଫେରନ୍ତୁ false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ଯଦି (Bmin > Amin) {
        Amin = Bmin;
    }
    ଯଦି (Bmax < Amax) {
        Amax = Bmax;
    }
    ଯଦି ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_INTERSECTRECT(ଅଚଳ RECTTYPE *A, ଅଚଳ RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        ଫେରନ୍ତୁ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ଯଦି (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    ଯଦି (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ଯଦି (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    ଯଦି (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    ଫେରନ୍ତୁ !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(ଅଚଳ RECTTYPE *A, ଅଚଳ RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        ଫେରନ୍ତୁ SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("result");
    }

    ଯଦି (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        ଯଦି (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } ଅନ୍ୟଥା { // A empty, B not empty
            *result = *B;
        }
        ଫେରନ୍ତୁ true;
    } ଅନ୍ୟଥା ଯଦି (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        ଫେରନ୍ତୁ true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ଯଦି (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    ଯଦି (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ଯଦି (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    ଯଦି (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    ଫେରନ୍ତୁ true;
}

bool SDL_ENCLOSEPOINTS(ଅଚଳ POINTTYPE *points, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, ଅଚଳ RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(ଗଣନା_2 < 1) {
        SDL_InvalidParamError("count");
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (clip) {
        bool added = false;
        ଅଚଳ SCALARTYPE clip_minx = clip->x;
        ଅଚଳ SCALARTYPE clip_miny = clip->y;
        ଅଚଳ SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ଅଚଳ SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        ଯଦି (SDL_RECTEMPTY(clip)) {
            ଫେରନ୍ତୁ false;
        }

        ପାଇଁ (i = 0; i < ଗଣନା_2; ++i) {
            x = points[i].x;
            y = points[i].y;

            ଯଦି (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                ଜାରି;
            }
            ଯଦି (!added) {
                // Special case: if no result was requested, we are done
                ଯଦି (!result) {
                    ଫେରନ୍ତୁ true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                ଜାରି;
            }
            ଯଦି (x < minx) {
                minx = x;
            } ଅନ୍ୟଥା ଯଦି (x > maxx) {
                maxx = x;
            }
            ଯଦି (y < miny) {
                miny = y;
            } ଅନ୍ୟଥା ଯଦି (y > maxy) {
                maxy = y;
            }
        }
        ଯଦି (!added) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        // Special case: if no result was requested, we are done
        ଯଦି (!result) {
            ଫେରନ୍ତୁ true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        ପାଇଁ (i = 1; i < ଗଣନା_2; ++i) {
            x = points[i].x;
            y = points[i].y;

            ଯଦି (x < minx) {
                minx = x;
            } ଅନ୍ୟଥା ଯଦି (x > maxx) {
                maxx = x;
            }
            ଯଦି (y < miny) {
                miny = y;
            } ଅନ୍ୟଥା ଯଦି (y > maxy) {
                maxy = y;
            }
        }
    }

    ଯଦି (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    ଫେରନ୍ତୁ true;
}

// Use the Cohen-Sutherland algorithm for line clipping
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା COMPUTEOUTCODE(ଅଚଳ RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା code = 0;
    ଯଦି (y < rect->y) {
        code |= CODE_ଶୀର୍ଷ;
    } ଅନ୍ୟଥା ଯଦି (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    ଯଦି (x < rect->x) {
        code |= CODE_ବାମ;
    } ଅନ୍ୟଥା ଯଦି (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_ଡାହାଣ;
    }
    ଫେରନ୍ତୁ code;
}

bool SDL_INTERSECTRECTANDLINE(ଅଚଳ RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (SDL_RECTEMPTY(rect)) {
        ଫେରନ୍ତୁ false; // Special case for empty rect
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
    ଯଦି (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        ଫେରନ୍ତୁ true;
    }

    // Check to see if entire line is to one side of rect
    ଯଦି ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (y1 == y2) { // Horizontal line, easy to clip
        ଯଦି (x1 < rectx1) {
            *X1 = rectx1;
        } ଅନ୍ୟଥା ଯଦି (x1 > rectx2) {
            *X1 = rectx2;
        }
        ଯଦି (x2 < rectx1) {
            *X2 = rectx1;
        } ଅନ୍ୟଥା ଯଦି (x2 > rectx2) {
            *X2 = rectx2;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (x1 == x2) { // Vertical line, easy to clip
        ଯଦି (y1 < recty1) {
            *Y1 = recty1;
        } ଅନ୍ୟଥା ଯଦି (y1 > recty2) {
            *Y1 = recty2;
        }
        ଯଦି (y2 < recty1) {
            *Y2 = recty1;
        } ଅନ୍ୟଥା ଯଦି (y2 > recty2) {
            *Y2 = recty2;
        }
        ଫେରନ୍ତୁ true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    ଯେତେବେଳେ (outcode1 || outcode2) {
        ଯଦି (outcode1 & outcode2) {
            ଫେରନ୍ତୁ false;
        }

        ଯଦି (outcode1) {
            ଯଦି (outcode1 & CODE_ଶୀର୍ଷ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ଅନ୍ୟଥା ଯଦି (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ଅନ୍ୟଥା ଯଦି (outcode1 & CODE_ବାମ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ଅନ୍ୟଥା ଯଦି (outcode1 & CODE_ଡାହାଣ) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } ଅନ୍ୟଥା {
            ଯଦି (outcode2 & CODE_ଶୀର୍ଷ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ଅନ୍ୟଥା ଯଦି (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ଅନ୍ୟଥା ଯଦି (outcode2 & CODE_ବାମ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ଅନ୍ୟଥା ଯଦି (outcode2 & CODE_ଡାହାଣ) {
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
    ଫେରନ୍ତୁ true;
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

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

ساكن bool SDL_RECT_CAN_OVERFLOW(ثابت RECTTYPE *rect)
{
    إذا (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        أرجع true;
    }
    أرجع false;
}

bool SDL_HASINTERSECTION(ثابت RECTTYPE *A, ثابت RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        أرجع false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        أرجع false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        أرجع false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    إذا (Bmin > Amin) {
        Amin = Bmin;
    }
    إذا (Bmax < Amax) {
        Amax = Bmax;
    }
    إذا ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        أرجع false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    إذا (Bmin > Amin) {
        Amin = Bmin;
    }
    إذا (Bmax < Amax) {
        Amax = Bmax;
    }
    إذا ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_INTERSECTRECT(ثابت RECTTYPE *A, ثابت RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        أرجع false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        أرجع false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        أرجع false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        أرجع false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    إذا (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    إذا (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    إذا (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    إذا (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    أرجع !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(ثابت RECTTYPE *A, ثابت RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        أرجع SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        أرجع SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        أرجع SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        أرجع SDL_InvalidParamError("result");
    }

    إذا (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        إذا (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } وإلا { // A empty, B not empty
            *result = *B;
        }
        أرجع true;
    } وإلا إذا (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        أرجع true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    إذا (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    إذا (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    إذا (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    إذا (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    أرجع true;
}

bool SDL_ENCLOSEPOINTS(ثابت POINTTYPE *points, صحيح كدي, ثابت RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    صحيح i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        أرجع false;
    }
    CHECK_PARAM(كدي < 1) {
        SDL_InvalidParamError("count");
        أرجع false;
    }

    إذا (clip) {
        bool added = false;
        ثابت SCALARTYPE clip_minx = clip->x;
        ثابت SCALARTYPE clip_miny = clip->y;
        ثابت SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ثابت SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        إذا (SDL_RECTEMPTY(clip)) {
            أرجع false;
        }

        لكل (i = 0; i < كدي; ++i) {
            x = points[i].x;
            y = points[i].y;

            إذا (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                استمر;
            }
            إذا (!added) {
                // Special case: if no result was requested, we are done
                إذا (!result) {
                    أرجع true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                استمر;
            }
            إذا (x < minx) {
                minx = x;
            } وإلا إذا (x > maxx) {
                maxx = x;
            }
            إذا (y < miny) {
                miny = y;
            } وإلا إذا (y > maxy) {
                maxy = y;
            }
        }
        إذا (!added) {
            أرجع false;
        }
    } وإلا {
        // Special case: if no result was requested, we are done
        إذا (!result) {
            أرجع true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        لكل (i = 1; i < كدي; ++i) {
            x = points[i].x;
            y = points[i].y;

            إذا (x < minx) {
                minx = x;
            } وإلا إذا (x > maxx) {
                maxx = x;
            }
            إذا (y < miny) {
                miny = y;
            } وإلا إذا (y > maxy) {
                maxy = y;
            }
        }
    }

    إذا (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    أرجع true;
}

// Use the Cohen-Sutherland algorithm for line clipping
ساكن صحيح COMPUTEOUTCODE(ثابت RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    صحيح code = 0;
    إذا (y < rect->y) {
        code |= CODE_كولي;
    } وإلا إذا (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    إذا (x < rect->x) {
        code |= CODE_هغو;
    } وإلا إذا (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_دام;
    }
    أرجع code;
}

bool SDL_INTERSECTRECTANDLINE(ثابت RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    صحيح outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        أرجع false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        أرجع false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        أرجع false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        أرجع false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        أرجع false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        أرجع false;
    }

    إذا (SDL_RECTEMPTY(rect)) {
        أرجع false; // Special case for empty rect
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
    إذا (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        أرجع true;
    }

    // Check to see if entire line is to one side of rect
    إذا ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        أرجع false;
    }

    إذا (y1 == y2) { // Horizontal line, easy to clip
        إذا (x1 < rectx1) {
            *X1 = rectx1;
        } وإلا إذا (x1 > rectx2) {
            *X1 = rectx2;
        }
        إذا (x2 < rectx1) {
            *X2 = rectx1;
        } وإلا إذا (x2 > rectx2) {
            *X2 = rectx2;
        }
        أرجع true;
    }

    إذا (x1 == x2) { // Vertical line, easy to clip
        إذا (y1 < recty1) {
            *Y1 = recty1;
        } وإلا إذا (y1 > recty2) {
            *Y1 = recty2;
        }
        إذا (y2 < recty1) {
            *Y2 = recty1;
        } وإلا إذا (y2 > recty2) {
            *Y2 = recty2;
        }
        أرجع true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    طالما (outcode1 || outcode2) {
        إذا (outcode1 & outcode2) {
            أرجع false;
        }

        إذا (outcode1) {
            إذا (outcode1 & CODE_كولي) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وإلا إذا (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وإلا إذا (outcode1 & CODE_هغو) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } وإلا إذا (outcode1 & CODE_دام) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } وإلا {
            إذا (outcode2 & CODE_كولي) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وإلا إذا (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وإلا إذا (outcode2 & CODE_هغو) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } وإلا إذا (outcode2 & CODE_دام) {
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
    أرجع true;
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

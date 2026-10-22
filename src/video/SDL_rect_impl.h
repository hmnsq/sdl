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

ایستا bool SDL_RECT_CAN_OVERFLOW(ثابت RECTTYPE *rect)
{
    اگر (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        بازگشت true;
    }
    بازگشت false;
}

bool SDL_HASINTERSECTION(ثابت RECTTYPE *A, ثابت RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        بازگشت false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        بازگشت false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        بازگشت false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    اگر (Bmin > Amin) {
        Amin = Bmin;
    }
    اگر (Bmax < Amax) {
        Amax = Bmax;
    }
    اگر ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        بازگشت false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    اگر (Bmin > Amin) {
        Amin = Bmin;
    }
    اگر (Bmax < Amax) {
        Amax = Bmax;
    }
    اگر ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        بازگشت false;
    }
    بازگشت true;
}

bool SDL_INTERSECTRECT(ثابت RECTTYPE *A, ثابت RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        بازگشت false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        بازگشت false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        بازگشت false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        بازگشت false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    اگر (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    اگر (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    اگر (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    اگر (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    بازگشت !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(ثابت RECTTYPE *A, ثابت RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        بازگشت SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        بازگشت SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        بازگشت SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        بازگشت SDL_InvalidParamError("result");
    }

    اگر (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        اگر (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } وگرنه { // A empty, B not empty
            *result = *B;
        }
        بازگشت true;
    } وگرنه اگر (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        بازگشت true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    اگر (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    اگر (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    اگر (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    اگر (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    بازگشت true;
}

bool SDL_ENCLOSEPOINTS(ثابت POINTTYPE *points, صحیح شمار, ثابت RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    صحیح i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        بازگشت false;
    }
    CHECK_PARAM(شمار < 1) {
        SDL_InvalidParamError("count");
        بازگشت false;
    }

    اگر (clip) {
        bool added = false;
        ثابت SCALARTYPE clip_minx = clip->x;
        ثابت SCALARTYPE clip_miny = clip->y;
        ثابت SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ثابت SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        اگر (SDL_RECTEMPTY(clip)) {
            بازگشت false;
        }

        برای (i = 0; i < شمار; ++i) {
            x = points[i].x;
            y = points[i].y;

            اگر (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                ادامه;
            }
            اگر (!added) {
                // Special case: if no result was requested, we are done
                اگر (!result) {
                    بازگشت true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                ادامه;
            }
            اگر (x < minx) {
                minx = x;
            } وگرنه اگر (x > maxx) {
                maxx = x;
            }
            اگر (y < miny) {
                miny = y;
            } وگرنه اگر (y > maxy) {
                maxy = y;
            }
        }
        اگر (!added) {
            بازگشت false;
        }
    } وگرنه {
        // Special case: if no result was requested, we are done
        اگر (!result) {
            بازگشت true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        برای (i = 1; i < شمار; ++i) {
            x = points[i].x;
            y = points[i].y;

            اگر (x < minx) {
                minx = x;
            } وگرنه اگر (x > maxx) {
                maxx = x;
            }
            اگر (y < miny) {
                miny = y;
            } وگرنه اگر (y > maxy) {
                maxy = y;
            }
        }
    }

    اگر (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    بازگشت true;
}

// Use the Cohen-Sutherland algorithm for line clipping
ایستا صحیح COMPUTEOUTCODE(ثابت RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    صحیح code = 0;
    اگر (y < rect->y) {
        code |= CODE_بالاترین;
    } وگرنه اگر (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    اگر (x < rect->x) {
        code |= CODE_چپ;
    } وگرنه اگر (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_راست;
    }
    بازگشت code;
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
    صحیح outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        بازگشت false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        بازگشت false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        بازگشت false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        بازگشت false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        بازگشت false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        بازگشت false;
    }

    اگر (SDL_RECTEMPTY(rect)) {
        بازگشت false; // Special case for empty rect
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
    اگر (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        بازگشت true;
    }

    // Check to see if entire line is to one side of rect
    اگر ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        بازگشت false;
    }

    اگر (y1 == y2) { // Horizontal line, easy to clip
        اگر (x1 < rectx1) {
            *X1 = rectx1;
        } وگرنه اگر (x1 > rectx2) {
            *X1 = rectx2;
        }
        اگر (x2 < rectx1) {
            *X2 = rectx1;
        } وگرنه اگر (x2 > rectx2) {
            *X2 = rectx2;
        }
        بازگشت true;
    }

    اگر (x1 == x2) { // Vertical line, easy to clip
        اگر (y1 < recty1) {
            *Y1 = recty1;
        } وگرنه اگر (y1 > recty2) {
            *Y1 = recty2;
        }
        اگر (y2 < recty1) {
            *Y2 = recty1;
        } وگرنه اگر (y2 > recty2) {
            *Y2 = recty2;
        }
        بازگشت true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    وقتی (outcode1 || outcode2) {
        اگر (outcode1 & outcode2) {
            بازگشت false;
        }

        اگر (outcode1) {
            اگر (outcode1 & CODE_بالاترین) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وگرنه اگر (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وگرنه اگر (outcode1 & CODE_چپ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } وگرنه اگر (outcode1 & CODE_راست) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } وگرنه {
            اگر (outcode2 & CODE_بالاترین) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وگرنه اگر (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } وگرنه اگر (outcode2 & CODE_چپ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } وگرنه اگر (outcode2 & CODE_راست) {
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
    بازگشت true;
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

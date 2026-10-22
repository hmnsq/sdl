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

স্থির bool SDL_RECT_CAN_OVERFLOW(ধ্রুব RECTTYPE *rect)
{
    যদি (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        প্রত্যাগম true;
    }
    প্রত্যাগম false;
}

bool SDL_HASINTERSECTION(ধ্রুব RECTTYPE *A, ধ্রুব RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        প্রত্যাগম false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        প্রত্যাগম false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    যদি (Bmin > Amin) {
        Amin = Bmin;
    }
    যদি (Bmax < Amax) {
        Amax = Bmax;
    }
    যদি ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        প্রত্যাগম false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    যদি (Bmin > Amin) {
        Amin = Bmin;
    }
    যদি (Bmax < Amax) {
        Amax = Bmax;
    }
    যদি ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

bool SDL_INTERSECTRECT(ধ্রুব RECTTYPE *A, ধ্রুব RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        প্রত্যাগম false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        প্রত্যাগম false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    যদি (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    যদি (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    যদি (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    যদি (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    প্রত্যাগম !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(ধ্রুব RECTTYPE *A, ধ্রুব RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        প্রত্যাগম SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        প্রত্যাগম SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        প্রত্যাগম SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        প্রত্যাগম SDL_InvalidParamError("result");
    }

    যদি (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        যদি (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } অন্যথা { // A empty, B not empty
            *result = *B;
        }
        প্রত্যাগম true;
    } অন্যথা যদি (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        প্রত্যাগম true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    যদি (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    যদি (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    যদি (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    যদি (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    প্রত্যাগম true;
}

bool SDL_ENCLOSEPOINTS(ধ্রুব POINTTYPE *points, পূর্ণাঙ্ক গুনতি, ধ্রুব RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    পূর্ণাঙ্ক i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        প্রত্যাগম false;
    }
    CHECK_PARAM(গুনতি < 1) {
        SDL_InvalidParamError("count");
        প্রত্যাগম false;
    }

    যদি (clip) {
        bool added = false;
        ধ্রুব SCALARTYPE clip_minx = clip->x;
        ধ্রুব SCALARTYPE clip_miny = clip->y;
        ধ্রুব SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ধ্রুব SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        যদি (SDL_RECTEMPTY(clip)) {
            প্রত্যাগম false;
        }

        প্রতি (i = 0; i < গুনতি; ++i) {
            x = points[i].x;
            y = points[i].y;

            যদি (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                অনুবর্ত;
            }
            যদি (!added) {
                // Special case: if no result was requested, we are done
                যদি (!result) {
                    প্রত্যাগম true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                অনুবর্ত;
            }
            যদি (x < minx) {
                minx = x;
            } অন্যথা যদি (x > maxx) {
                maxx = x;
            }
            যদি (y < miny) {
                miny = y;
            } অন্যথা যদি (y > maxy) {
                maxy = y;
            }
        }
        যদি (!added) {
            প্রত্যাগম false;
        }
    } অন্যথা {
        // Special case: if no result was requested, we are done
        যদি (!result) {
            প্রত্যাগম true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        প্রতি (i = 1; i < গুনতি; ++i) {
            x = points[i].x;
            y = points[i].y;

            যদি (x < minx) {
                minx = x;
            } অন্যথা যদি (x > maxx) {
                maxx = x;
            }
            যদি (y < miny) {
                miny = y;
            } অন্যথা যদি (y > maxy) {
                maxy = y;
            }
        }
    }

    যদি (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    প্রত্যাগম true;
}

// Use the Cohen-Sutherland algorithm for line clipping
স্থির পূর্ণাঙ্ক COMPUTEOUTCODE(ধ্রুব RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    পূর্ণাঙ্ক code = 0;
    যদি (y < rect->y) {
        code |= CODE_শীর্ষ;
    } অন্যথা যদি (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    যদি (x < rect->x) {
        code |= CODE_বাম;
    } অন্যথা যদি (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_ডান;
    }
    প্রত্যাগম code;
}

bool SDL_INTERSECTRECTANDLINE(ধ্রুব RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    পূর্ণাঙ্ক outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        প্রত্যাগম false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        প্রত্যাগম false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        প্রত্যাগম false;
    }

    যদি (SDL_RECTEMPTY(rect)) {
        প্রত্যাগম false; // Special case for empty rect
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
    যদি (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        প্রত্যাগম true;
    }

    // Check to see if entire line is to one side of rect
    যদি ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        প্রত্যাগম false;
    }

    যদি (y1 == y2) { // Horizontal line, easy to clip
        যদি (x1 < rectx1) {
            *X1 = rectx1;
        } অন্যথা যদি (x1 > rectx2) {
            *X1 = rectx2;
        }
        যদি (x2 < rectx1) {
            *X2 = rectx1;
        } অন্যথা যদি (x2 > rectx2) {
            *X2 = rectx2;
        }
        প্রত্যাগম true;
    }

    যদি (x1 == x2) { // Vertical line, easy to clip
        যদি (y1 < recty1) {
            *Y1 = recty1;
        } অন্যথা যদি (y1 > recty2) {
            *Y1 = recty2;
        }
        যদি (y2 < recty1) {
            *Y2 = recty1;
        } অন্যথা যদি (y2 > recty2) {
            *Y2 = recty2;
        }
        প্রত্যাগম true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    যাবত্ (outcode1 || outcode2) {
        যদি (outcode1 & outcode2) {
            প্রত্যাগম false;
        }

        যদি (outcode1) {
            যদি (outcode1 & CODE_শীর্ষ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } অন্যথা যদি (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } অন্যথা যদি (outcode1 & CODE_বাম) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } অন্যথা যদি (outcode1 & CODE_ডান) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } অন্যথা {
            যদি (outcode2 & CODE_শীর্ষ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } অন্যথা যদি (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } অন্যথা যদি (outcode2 & CODE_বাম) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } অন্যথা যদি (outcode2 & CODE_ডান) {
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
    প্রত্যাগম true;
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

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

स्थिर bool SDL_RECT_CAN_OVERFLOW(अचर RECTTYPE *rect)
{
    यदि (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        फर्काऊ true;
    }
    फर्काऊ false;
}

bool SDL_HASINTERSECTION(अचर RECTTYPE *A, अचर RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        फर्काऊ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        फर्काऊ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        फर्काऊ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    यदि (Bmin > Amin) {
        Amin = Bmin;
    }
    यदि (Bmax < Amax) {
        Amax = Bmax;
    }
    यदि ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        फर्काऊ false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    यदि (Bmin > Amin) {
        Amin = Bmin;
    }
    यदि (Bmax < Amax) {
        Amax = Bmax;
    }
    यदि ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        फर्काऊ false;
    }
    फर्काऊ true;
}

bool SDL_INTERSECTRECT(अचर RECTTYPE *A, अचर RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        फर्काऊ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        फर्काऊ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        फर्काऊ false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        फर्काऊ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    यदि (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    यदि (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    यदि (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    यदि (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    फर्काऊ !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(अचर RECTTYPE *A, अचर RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        फर्काऊ SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        फर्काऊ SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        फर्काऊ SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        फर्काऊ SDL_InvalidParamError("result");
    }

    यदि (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        यदि (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } अन्यथा { // A empty, B not empty
            *result = *B;
        }
        फर्काऊ true;
    } अन्यथा यदि (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        फर्काऊ true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    यदि (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    यदि (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    यदि (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    यदि (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    फर्काऊ true;
}

bool SDL_ENCLOSEPOINTS(अचर POINTTYPE *points, पूर्णाङ्क गन्ती, अचर RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    पूर्णाङ्क i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        फर्काऊ false;
    }
    CHECK_PARAM(गन्ती < 1) {
        SDL_InvalidParamError("count");
        फर्काऊ false;
    }

    यदि (clip) {
        bool added = false;
        अचर SCALARTYPE clip_minx = clip->x;
        अचर SCALARTYPE clip_miny = clip->y;
        अचर SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        अचर SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        यदि (SDL_RECTEMPTY(clip)) {
            फर्काऊ false;
        }

        लागि (i = 0; i < गन्ती; ++i) {
            x = points[i].x;
            y = points[i].y;

            यदि (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                जारी;
            }
            यदि (!added) {
                // Special case: if no result was requested, we are done
                यदि (!result) {
                    फर्काऊ true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                जारी;
            }
            यदि (x < minx) {
                minx = x;
            } अन्यथा यदि (x > maxx) {
                maxx = x;
            }
            यदि (y < miny) {
                miny = y;
            } अन्यथा यदि (y > maxy) {
                maxy = y;
            }
        }
        यदि (!added) {
            फर्काऊ false;
        }
    } अन्यथा {
        // Special case: if no result was requested, we are done
        यदि (!result) {
            फर्काऊ true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        लागि (i = 1; i < गन्ती; ++i) {
            x = points[i].x;
            y = points[i].y;

            यदि (x < minx) {
                minx = x;
            } अन्यथा यदि (x > maxx) {
                maxx = x;
            }
            यदि (y < miny) {
                miny = y;
            } अन्यथा यदि (y > maxy) {
                maxy = y;
            }
        }
    }

    यदि (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    फर्काऊ true;
}

// Use the Cohen-Sutherland algorithm for line clipping
स्थिर पूर्णाङ्क COMPUTEOUTCODE(अचर RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    पूर्णाङ्क code = 0;
    यदि (y < rect->y) {
        code |= CODE_शीर्ष;
    } अन्यथा यदि (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    यदि (x < rect->x) {
        code |= CODE_बायाँ;
    } अन्यथा यदि (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_दायाँ;
    }
    फर्काऊ code;
}

bool SDL_INTERSECTRECTANDLINE(अचर RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    पूर्णाङ्क outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        फर्काऊ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        फर्काऊ false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        फर्काऊ false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        फर्काऊ false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        फर्काऊ false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        फर्काऊ false;
    }

    यदि (SDL_RECTEMPTY(rect)) {
        फर्काऊ false; // Special case for empty rect
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
    यदि (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        फर्काऊ true;
    }

    // Check to see if entire line is to one side of rect
    यदि ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        फर्काऊ false;
    }

    यदि (y1 == y2) { // Horizontal line, easy to clip
        यदि (x1 < rectx1) {
            *X1 = rectx1;
        } अन्यथा यदि (x1 > rectx2) {
            *X1 = rectx2;
        }
        यदि (x2 < rectx1) {
            *X2 = rectx1;
        } अन्यथा यदि (x2 > rectx2) {
            *X2 = rectx2;
        }
        फर्काऊ true;
    }

    यदि (x1 == x2) { // Vertical line, easy to clip
        यदि (y1 < recty1) {
            *Y1 = recty1;
        } अन्यथा यदि (y1 > recty2) {
            *Y1 = recty2;
        }
        यदि (y2 < recty1) {
            *Y2 = recty1;
        } अन्यथा यदि (y2 > recty2) {
            *Y2 = recty2;
        }
        फर्काऊ true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    जबसम्म (outcode1 || outcode2) {
        यदि (outcode1 & outcode2) {
            फर्काऊ false;
        }

        यदि (outcode1) {
            यदि (outcode1 & CODE_शीर्ष) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा यदि (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा यदि (outcode1 & CODE_बायाँ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } अन्यथा यदि (outcode1 & CODE_दायाँ) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } अन्यथा {
            यदि (outcode2 & CODE_शीर्ष) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा यदि (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा यदि (outcode2 & CODE_बायाँ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } अन्यथा यदि (outcode2 & CODE_दायाँ) {
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
    फर्काऊ true;
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

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

स्थिर bool SDL_RECT_CAN_OVERFLOW(ध्रुव RECTTYPE *rect)
{
    सचे (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

bool SDL_HASINTERSECTION(ध्रुव RECTTYPE *A, ध्रुव RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        पटिनिवत्त false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        पटिनिवत्त false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    सचे (Bmin > Amin) {
        Amin = Bmin;
    }
    सचे (Bmax < Amax) {
        Amax = Bmax;
    }
    सचे ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        पटिनिवत्त false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    सचे (Bmin > Amin) {
        Amin = Bmin;
    }
    सचे (Bmax < Amax) {
        Amax = Bmax;
    }
    सचे ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

bool SDL_INTERSECTRECT(ध्रुव RECTTYPE *A, ध्रुव RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        पटिनिवत्त false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        पटिनिवत्त false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    सचे (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    सचे (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    सचे (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    सचे (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    पटिनिवत्त !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(ध्रुव RECTTYPE *A, ध्रुव RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        पटिनिवत्त SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        पटिनिवत्त SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        पटिनिवत्त SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        पटिनिवत्त SDL_InvalidParamError("result");
    }

    सचे (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        सचे (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } अञ्ञथा { // A empty, B not empty
            *result = *B;
        }
        पटिनिवत्त true;
    } अञ्ञथा सचे (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        पटिनिवत्त true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    सचे (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    सचे (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    सचे (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    सचे (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    पटिनिवत्त true;
}

bool SDL_ENCLOSEPOINTS(ध्रुव POINTTYPE *points, पूर्णाङ्क गणनम्, ध्रुव RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    पूर्णाङ्क i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        पटिनिवत्त false;
    }
    CHECK_PARAM(गणनम् < 1) {
        SDL_InvalidParamError("count");
        पटिनिवत्त false;
    }

    सचे (clip) {
        bool added = false;
        ध्रुव SCALARTYPE clip_minx = clip->x;
        ध्रुव SCALARTYPE clip_miny = clip->y;
        ध्रुव SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ध्रुव SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        सचे (SDL_RECTEMPTY(clip)) {
            पटिनिवत्त false;
        }

        अत्थाय (i = 0; i < गणनम्; ++i) {
            x = points[i].x;
            y = points[i].y;

            सचे (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                अनुवर्त;
            }
            सचे (!added) {
                // Special case: if no result was requested, we are done
                सचे (!result) {
                    पटिनिवत्त true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                अनुवर्त;
            }
            सचे (x < minx) {
                minx = x;
            } अञ्ञथा सचे (x > maxx) {
                maxx = x;
            }
            सचे (y < miny) {
                miny = y;
            } अञ्ञथा सचे (y > maxy) {
                maxy = y;
            }
        }
        सचे (!added) {
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        // Special case: if no result was requested, we are done
        सचे (!result) {
            पटिनिवत्त true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        अत्थाय (i = 1; i < गणनम्; ++i) {
            x = points[i].x;
            y = points[i].y;

            सचे (x < minx) {
                minx = x;
            } अञ्ञथा सचे (x > maxx) {
                maxx = x;
            }
            सचे (y < miny) {
                miny = y;
            } अञ्ञथा सचे (y > maxy) {
                maxy = y;
            }
        }
    }

    सचे (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    पटिनिवत्त true;
}

// Use the Cohen-Sutherland algorithm for line clipping
स्थिर पूर्णाङ्क COMPUTEOUTCODE(ध्रुव RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    पूर्णाङ्क code = 0;
    सचे (y < rect->y) {
        code |= CODE_शिखरम्;
    } अञ्ञथा सचे (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    सचे (x < rect->x) {
        code |= CODE_वामः;
    } अञ्ञथा सचे (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_दक्षिणः;
    }
    पटिनिवत्त code;
}

bool SDL_INTERSECTRECTANDLINE(ध्रुव RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
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
        पटिनिवत्त false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        पटिनिवत्त false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        पटिनिवत्त false;
    }

    सचे (SDL_RECTEMPTY(rect)) {
        पटिनिवत्त false; // Special case for empty rect
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
    सचे (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        पटिनिवत्त true;
    }

    // Check to see if entire line is to one side of rect
    सचे ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        पटिनिवत्त false;
    }

    सचे (y1 == y2) { // Horizontal line, easy to clip
        सचे (x1 < rectx1) {
            *X1 = rectx1;
        } अञ्ञथा सचे (x1 > rectx2) {
            *X1 = rectx2;
        }
        सचे (x2 < rectx1) {
            *X2 = rectx1;
        } अञ्ञथा सचे (x2 > rectx2) {
            *X2 = rectx2;
        }
        पटिनिवत्त true;
    }

    सचे (x1 == x2) { // Vertical line, easy to clip
        सचे (y1 < recty1) {
            *Y1 = recty1;
        } अञ्ञथा सचे (y1 > recty2) {
            *Y1 = recty2;
        }
        सचे (y2 < recty1) {
            *Y2 = recty1;
        } अञ्ञथा सचे (y2 > recty2) {
            *Y2 = recty2;
        }
        पटिनिवत्त true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    याव (outcode1 || outcode2) {
        सचे (outcode1 & outcode2) {
            पटिनिवत्त false;
        }

        सचे (outcode1) {
            सचे (outcode1 & CODE_शिखरम्) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अञ्ञथा सचे (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अञ्ञथा सचे (outcode1 & CODE_वामः) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } अञ्ञथा सचे (outcode1 & CODE_दक्षिणः) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } अञ्ञथा {
            सचे (outcode2 & CODE_शिखरम्) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अञ्ञथा सचे (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अञ्ञथा सचे (outcode2 & CODE_वामः) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } अञ्ञथा सचे (outcode2 & CODE_दक्षिणः) {
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
    पटिनिवत्त true;
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

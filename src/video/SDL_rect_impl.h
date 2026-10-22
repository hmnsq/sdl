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

સ્થિર bool SDL_RECT_CAN_OVERFLOW(અચલ RECTTYPE *rect)
{
    જો (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        પાછા true;
    }
    પાછા false;
}

bool SDL_HASINTERSECTION(અચલ RECTTYPE *A, અચલ RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        પાછા false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        પાછા false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        પાછા false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    જો (Bmin > Amin) {
        Amin = Bmin;
    }
    જો (Bmax < Amax) {
        Amax = Bmax;
    }
    જો ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        પાછા false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    જો (Bmin > Amin) {
        Amin = Bmin;
    }
    જો (Bmax < Amax) {
        Amax = Bmax;
    }
    જો ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        પાછા false;
    }
    પાછા true;
}

bool SDL_INTERSECTRECT(અચલ RECTTYPE *A, અચલ RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        પાછા false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        પાછા false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        પાછા false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        પાછા false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    જો (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    જો (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    જો (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    જો (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    પાછા !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(અચલ RECTTYPE *A, અચલ RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        પાછા SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        પાછા SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        પાછા SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        પાછા SDL_InvalidParamError("result");
    }

    જો (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        જો (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } નહીંતર { // A empty, B not empty
            *result = *B;
        }
        પાછા true;
    } નહીંતર જો (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        પાછા true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    જો (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    જો (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    જો (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    જો (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    પાછા true;
}

bool SDL_ENCLOSEPOINTS(અચલ POINTTYPE *points, પૂર્ણાંક ગણતરી, અચલ RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    પૂર્ણાંક i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        પાછા false;
    }
    CHECK_PARAM(ગણતરી < 1) {
        SDL_InvalidParamError("count");
        પાછા false;
    }

    જો (clip) {
        bool added = false;
        અચલ SCALARTYPE clip_minx = clip->x;
        અચલ SCALARTYPE clip_miny = clip->y;
        અચલ SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        અચલ SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        જો (SDL_RECTEMPTY(clip)) {
            પાછા false;
        }

        માટે (i = 0; i < ગણતરી; ++i) {
            x = points[i].x;
            y = points[i].y;

            જો (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                ચાલુ;
            }
            જો (!added) {
                // Special case: if no result was requested, we are done
                જો (!result) {
                    પાછા true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                ચાલુ;
            }
            જો (x < minx) {
                minx = x;
            } નહીંતર જો (x > maxx) {
                maxx = x;
            }
            જો (y < miny) {
                miny = y;
            } નહીંતર જો (y > maxy) {
                maxy = y;
            }
        }
        જો (!added) {
            પાછા false;
        }
    } નહીંતર {
        // Special case: if no result was requested, we are done
        જો (!result) {
            પાછા true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        માટે (i = 1; i < ગણતરી; ++i) {
            x = points[i].x;
            y = points[i].y;

            જો (x < minx) {
                minx = x;
            } નહીંતર જો (x > maxx) {
                maxx = x;
            }
            જો (y < miny) {
                miny = y;
            } નહીંતર જો (y > maxy) {
                maxy = y;
            }
        }
    }

    જો (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    પાછા true;
}

// Use the Cohen-Sutherland algorithm for line clipping
સ્થિર પૂર્ણાંક COMPUTEOUTCODE(અચલ RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    પૂર્ણાંક code = 0;
    જો (y < rect->y) {
        code |= CODE_ટોચ;
    } નહીંતર જો (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    જો (x < rect->x) {
        code |= CODE_ડાબું;
    } નહીંતર જો (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_જમણું;
    }
    પાછા code;
}

bool SDL_INTERSECTRECTANDLINE(અચલ RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    પૂર્ણાંક outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        પાછા false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        પાછા false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        પાછા false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        પાછા false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        પાછા false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        પાછા false;
    }

    જો (SDL_RECTEMPTY(rect)) {
        પાછા false; // Special case for empty rect
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
    જો (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        પાછા true;
    }

    // Check to see if entire line is to one side of rect
    જો ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        પાછા false;
    }

    જો (y1 == y2) { // Horizontal line, easy to clip
        જો (x1 < rectx1) {
            *X1 = rectx1;
        } નહીંતર જો (x1 > rectx2) {
            *X1 = rectx2;
        }
        જો (x2 < rectx1) {
            *X2 = rectx1;
        } નહીંતર જો (x2 > rectx2) {
            *X2 = rectx2;
        }
        પાછા true;
    }

    જો (x1 == x2) { // Vertical line, easy to clip
        જો (y1 < recty1) {
            *Y1 = recty1;
        } નહીંતર જો (y1 > recty2) {
            *Y1 = recty2;
        }
        જો (y2 < recty1) {
            *Y2 = recty1;
        } નહીંતર જો (y2 > recty2) {
            *Y2 = recty2;
        }
        પાછા true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    જ્યારે (outcode1 || outcode2) {
        જો (outcode1 & outcode2) {
            પાછા false;
        }

        જો (outcode1) {
            જો (outcode1 & CODE_ટોચ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } નહીંતર જો (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } નહીંતર જો (outcode1 & CODE_ડાબું) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } નહીંતર જો (outcode1 & CODE_જમણું) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } નહીંતર {
            જો (outcode2 & CODE_ટોચ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } નહીંતર જો (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } નહીંતર જો (outcode2 & CODE_ડાબું) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } નહીંતર જો (outcode2 & CODE_જમણું) {
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
    પાછા true;
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

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

நிலையான bool SDL_RECT_CAN_OVERFLOW(மாறிலி RECTTYPE *rect)
{
    எனில் (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        திரும்பு true;
    }
    திரும்பு false;
}

bool SDL_HASINTERSECTION(மாறிலி RECTTYPE *A, மாறிலி RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        திரும்பு false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        திரும்பு false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        திரும்பு false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    எனில் (Bmin > Amin) {
        Amin = Bmin;
    }
    எனில் (Bmax < Amax) {
        Amax = Bmax;
    }
    எனில் ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        திரும்பு false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    எனில் (Bmin > Amin) {
        Amin = Bmin;
    }
    எனில் (Bmax < Amax) {
        Amax = Bmax;
    }
    எனில் ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool SDL_INTERSECTRECT(மாறிலி RECTTYPE *A, மாறிலி RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        திரும்பு false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        திரும்பு false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        திரும்பு false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        திரும்பு false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    எனில் (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    எனில் (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    எனில் (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    எனில் (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    திரும்பு !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(மாறிலி RECTTYPE *A, மாறிலி RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        திரும்பு SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        திரும்பு SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        திரும்பு SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        திரும்பு SDL_InvalidParamError("result");
    }

    எனில் (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        எனில் (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } இல்லையெனில் { // A empty, B not empty
            *result = *B;
        }
        திரும்பு true;
    } இல்லையெனில் எனில் (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        திரும்பு true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    எனில் (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    எனில் (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    எனில் (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    எனில் (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    திரும்பு true;
}

bool SDL_ENCLOSEPOINTS(மாறிலி POINTTYPE *points, முழு மொத்தம், மாறிலி RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    முழு i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        திரும்பு false;
    }
    CHECK_PARAM(மொத்தம் < 1) {
        SDL_InvalidParamError("count");
        திரும்பு false;
    }

    எனில் (clip) {
        bool added = false;
        மாறிலி SCALARTYPE clip_minx = clip->x;
        மாறிலி SCALARTYPE clip_miny = clip->y;
        மாறிலி SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        மாறிலி SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        எனில் (SDL_RECTEMPTY(clip)) {
            திரும்பு false;
        }

        க்கு (i = 0; i < மொத்தம்; ++i) {
            x = points[i].x;
            y = points[i].y;

            எனில் (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                தொடர்;
            }
            எனில் (!added) {
                // Special case: if no result was requested, we are done
                எனில் (!result) {
                    திரும்பு true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                தொடர்;
            }
            எனில் (x < minx) {
                minx = x;
            } இல்லையெனில் எனில் (x > maxx) {
                maxx = x;
            }
            எனில் (y < miny) {
                miny = y;
            } இல்லையெனில் எனில் (y > maxy) {
                maxy = y;
            }
        }
        எனில் (!added) {
            திரும்பு false;
        }
    } இல்லையெனில் {
        // Special case: if no result was requested, we are done
        எனில் (!result) {
            திரும்பு true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        க்கு (i = 1; i < மொத்தம்; ++i) {
            x = points[i].x;
            y = points[i].y;

            எனில் (x < minx) {
                minx = x;
            } இல்லையெனில் எனில் (x > maxx) {
                maxx = x;
            }
            எனில் (y < miny) {
                miny = y;
            } இல்லையெனில் எனில் (y > maxy) {
                maxy = y;
            }
        }
    }

    எனில் (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    திரும்பு true;
}

// Use the Cohen-Sutherland algorithm for line clipping
நிலையான முழு COMPUTEOUTCODE(மாறிலி RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    முழு code = 0;
    எனில் (y < rect->y) {
        code |= CODE_உச்சி;
    } இல்லையெனில் எனில் (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    எனில் (x < rect->x) {
        code |= CODE_இடது;
    } இல்லையெனில் எனில் (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_வலது;
    }
    திரும்பு code;
}

bool SDL_INTERSECTRECTANDLINE(மாறிலி RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    முழு outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        திரும்பு false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        திரும்பு false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        திரும்பு false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        திரும்பு false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        திரும்பு false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        திரும்பு false;
    }

    எனில் (SDL_RECTEMPTY(rect)) {
        திரும்பு false; // Special case for empty rect
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
    எனில் (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        திரும்பு true;
    }

    // Check to see if entire line is to one side of rect
    எனில் ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        திரும்பு false;
    }

    எனில் (y1 == y2) { // Horizontal line, easy to clip
        எனில் (x1 < rectx1) {
            *X1 = rectx1;
        } இல்லையெனில் எனில் (x1 > rectx2) {
            *X1 = rectx2;
        }
        எனில் (x2 < rectx1) {
            *X2 = rectx1;
        } இல்லையெனில் எனில் (x2 > rectx2) {
            *X2 = rectx2;
        }
        திரும்பு true;
    }

    எனில் (x1 == x2) { // Vertical line, easy to clip
        எனில் (y1 < recty1) {
            *Y1 = recty1;
        } இல்லையெனில் எனில் (y1 > recty2) {
            *Y1 = recty2;
        }
        எனில் (y2 < recty1) {
            *Y2 = recty1;
        } இல்லையெனில் எனில் (y2 > recty2) {
            *Y2 = recty2;
        }
        திரும்பு true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    போது (outcode1 || outcode2) {
        எனில் (outcode1 & outcode2) {
            திரும்பு false;
        }

        எனில் (outcode1) {
            எனில் (outcode1 & CODE_உச்சி) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } இல்லையெனில் எனில் (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } இல்லையெனில் எனில் (outcode1 & CODE_இடது) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } இல்லையெனில் எனில் (outcode1 & CODE_வலது) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } இல்லையெனில் {
            எனில் (outcode2 & CODE_உச்சி) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } இல்லையெனில் எனில் (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } இல்லையெனில் எனில் (outcode2 & CODE_இடது) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } இல்லையெனில் எனில் (outcode2 & CODE_வலது) {
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
    திரும்பு true;
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

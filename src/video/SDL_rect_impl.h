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

സ്ഥിതം bool SDL_RECT_CAN_OVERFLOW(സ്ഥിരം RECTTYPE *rect)
{
    എങ്കിൽ (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        തിരികെ true;
    }
    തിരികെ false;
}

bool SDL_HASINTERSECTION(സ്ഥിരം RECTTYPE *A, സ്ഥിരം RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        തിരികെ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        തിരികെ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        തിരികെ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    എങ്കിൽ (Bmin > Amin) {
        Amin = Bmin;
    }
    എങ്കിൽ (Bmax < Amax) {
        Amax = Bmax;
    }
    എങ്കിൽ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        തിരികെ false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    എങ്കിൽ (Bmin > Amin) {
        Amin = Bmin;
    }
    എങ്കിൽ (Bmax < Amax) {
        Amax = Bmax;
    }
    എങ്കിൽ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        തിരികെ false;
    }
    തിരികെ true;
}

bool SDL_INTERSECTRECT(സ്ഥിരം RECTTYPE *A, സ്ഥിരം RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        തിരികെ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        തിരികെ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        തിരികെ false;
    }
    CHECK_PARAM(!result) {
        SDL_InvalidParamError("result");
        തിരികെ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    എങ്കിൽ (Bmin > Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    എങ്കിൽ (Bmax < Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    എങ്കിൽ (Bmin > Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    എങ്കിൽ (Bmax < Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;

    തിരികെ !SDL_RECTEMPTY(result);
}

bool SDL_UNIONRECT(സ്ഥിരം RECTTYPE *A, സ്ഥിരം RECTTYPE *B, RECTTYPE *result)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        തിരികെ SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        തിരികെ SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        തിരികെ SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!result) {
        തിരികെ SDL_InvalidParamError("result");
    }

    എങ്കിൽ (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        എങ്കിൽ (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(result);
        } അല്ലെങ്കിൽ { // A empty, B not empty
            *result = *B;
        }
        തിരികെ true;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *result = *A;
        തിരികെ true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    എങ്കിൽ (Bmin < Amin) {
        Amin = Bmin;
    }
    result->x = Amin;
    എങ്കിൽ (Bmax > Amax) {
        Amax = Bmax;
    }
    result->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    എങ്കിൽ (Bmin < Amin) {
        Amin = Bmin;
    }
    result->y = Amin;
    എങ്കിൽ (Bmax > Amax) {
        Amax = Bmax;
    }
    result->h = Amax - Amin;
    തിരികെ true;
}

bool SDL_ENCLOSEPOINTS(സ്ഥിരം POINTTYPE *points, പൂർണ്ണസംഖ്യ എണ്ണം, സ്ഥിരം RECTTYPE *clip, RECTTYPE *result)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    പൂർണ്ണസംഖ്യ i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        തിരികെ false;
    }
    CHECK_PARAM(എണ്ണം < 1) {
        SDL_InvalidParamError("count");
        തിരികെ false;
    }

    എങ്കിൽ (clip) {
        bool added = false;
        സ്ഥിരം SCALARTYPE clip_minx = clip->x;
        സ്ഥിരം SCALARTYPE clip_miny = clip->y;
        സ്ഥിരം SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        സ്ഥിരം SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        എങ്കിൽ (SDL_RECTEMPTY(clip)) {
            തിരികെ false;
        }

        വേണ്ടി (i = 0; i < എണ്ണം; ++i) {
            x = points[i].x;
            y = points[i].y;

            എങ്കിൽ (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                തുടരുക;
            }
            എങ്കിൽ (!added) {
                // Special case: if no result was requested, we are done
                എങ്കിൽ (!result) {
                    തിരികെ true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                തുടരുക;
            }
            എങ്കിൽ (x < minx) {
                minx = x;
            } അല്ലെങ്കിൽ എങ്കിൽ (x > maxx) {
                maxx = x;
            }
            എങ്കിൽ (y < miny) {
                miny = y;
            } അല്ലെങ്കിൽ എങ്കിൽ (y > maxy) {
                maxy = y;
            }
        }
        എങ്കിൽ (!added) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        // Special case: if no result was requested, we are done
        എങ്കിൽ (!result) {
            തിരികെ true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        വേണ്ടി (i = 1; i < എണ്ണം; ++i) {
            x = points[i].x;
            y = points[i].y;

            എങ്കിൽ (x < minx) {
                minx = x;
            } അല്ലെങ്കിൽ എങ്കിൽ (x > maxx) {
                maxx = x;
            }
            എങ്കിൽ (y < miny) {
                miny = y;
            } അല്ലെങ്കിൽ എങ്കിൽ (y > maxy) {
                maxy = y;
            }
        }
    }

    എങ്കിൽ (result) {
        result->x = minx;
        result->y = miny;
        result->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        result->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    തിരികെ true;
}

// Use the Cohen-Sutherland algorithm for line clipping
സ്ഥിതം പൂർണ്ണസംഖ്യ COMPUTEOUTCODE(സ്ഥിരം RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    പൂർണ്ണസംഖ്യ code = 0;
    എങ്കിൽ (y < rect->y) {
        code |= CODE_മുകൾ;
    } അല്ലെങ്കിൽ എങ്കിൽ (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    എങ്കിൽ (x < rect->x) {
        code |= CODE_ഇടത്;
    } അല്ലെങ്കിൽ എങ്കിൽ (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_വലത്;
    }
    തിരികെ code;
}

bool SDL_INTERSECTRECTANDLINE(സ്ഥിരം RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    പൂർണ്ണസംഖ്യ outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        തിരികെ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        തിരികെ false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        തിരികെ false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        തിരികെ false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        തിരികെ false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        തിരികെ false;
    }

    എങ്കിൽ (SDL_RECTEMPTY(rect)) {
        തിരികെ false; // Special case for empty rect
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
    എങ്കിൽ (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        തിരികെ true;
    }

    // Check to see if entire line is to one side of rect
    എങ്കിൽ ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        തിരികെ false;
    }

    എങ്കിൽ (y1 == y2) { // Horizontal line, easy to clip
        എങ്കിൽ (x1 < rectx1) {
            *X1 = rectx1;
        } അല്ലെങ്കിൽ എങ്കിൽ (x1 > rectx2) {
            *X1 = rectx2;
        }
        എങ്കിൽ (x2 < rectx1) {
            *X2 = rectx1;
        } അല്ലെങ്കിൽ എങ്കിൽ (x2 > rectx2) {
            *X2 = rectx2;
        }
        തിരികെ true;
    }

    എങ്കിൽ (x1 == x2) { // Vertical line, easy to clip
        എങ്കിൽ (y1 < recty1) {
            *Y1 = recty1;
        } അല്ലെങ്കിൽ എങ്കിൽ (y1 > recty2) {
            *Y1 = recty2;
        }
        എങ്കിൽ (y2 < recty1) {
            *Y2 = recty1;
        } അല്ലെങ്കിൽ എങ്കിൽ (y2 > recty2) {
            *Y2 = recty2;
        }
        തിരികെ true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    ആകുമ്പോൾ (outcode1 || outcode2) {
        എങ്കിൽ (outcode1 & outcode2) {
            തിരികെ false;
        }

        എങ്കിൽ (outcode1) {
            എങ്കിൽ (outcode1 & CODE_മുകൾ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } അല്ലെങ്കിൽ എങ്കിൽ (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } അല്ലെങ്കിൽ എങ്കിൽ (outcode1 & CODE_ഇടത്) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } അല്ലെങ്കിൽ എങ്കിൽ (outcode1 & CODE_വലത്) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (outcode2 & CODE_മുകൾ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } അല്ലെങ്കിൽ എങ്കിൽ (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } അല്ലെങ്കിൽ എങ്കിൽ (outcode2 & CODE_ഇടത്) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } അല്ലെങ്കിൽ എങ്കിൽ (outcode2 & CODE_വലത്) {
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
    തിരികെ true;
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

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

ਸਥਿਰ bool SDL_RECT_CAN_ਉਛਾਲ(ਅਚਲ RECTTYPE *rect)
{
    ਜੇ (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

bool SDL_HASINTERSECTION(ਅਚਲ RECTTYPE *A, ਅਚਲ RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_ਉਛਾਲ(A) || SDL_RECT_CAN_ਉਛਾਲ(B)) {
        SDL_ਸੈੱਟ_Error("Potential rect math overflow");
        ਵਾਪਸ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ਜੇ (Bmin > Amin) {
        Amin = Bmin;
    }
    ਜੇ (Bmax < Amax) {
        Amax = Bmax;
    }
    ਜੇ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ਵਾਪਸ false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ਜੇ (Bmin > Amin) {
        Amin = Bmin;
    }
    ਜੇ (Bmax < Amax) {
        Amax = Bmax;
    }
    ਜੇ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool SDL_INTERSECTRECT(ਅਚਲ RECTTYPE *A, ਅਚਲ RECTTYPE *B, RECTTYPE *ਨਤੀਜਾ)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_ਉਛਾਲ(A) || SDL_RECT_CAN_ਉਛਾਲ(B)) {
        SDL_ਸੈੱਟ_Error("Potential rect math overflow");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!ਨਤੀਜਾ) {
        SDL_InvalidParamError("result");
        ਵਾਪਸ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ਜੇ (Bmin > Amin) {
        Amin = Bmin;
    }
    ਨਤੀਜਾ->x = Amin;
    ਜੇ (Bmax < Amax) {
        Amax = Bmax;
    }
    ਨਤੀਜਾ->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ਜੇ (Bmin > Amin) {
        Amin = Bmin;
    }
    ਨਤੀਜਾ->y = Amin;
    ਜੇ (Bmax < Amax) {
        Amax = Bmax;
    }
    ਨਤੀਜਾ->h = Amax - Amin;

    ਵਾਪਸ !SDL_RECTEMPTY(ਨਤੀਜਾ);
}

bool SDL_UNIONRECT(ਅਚਲ RECTTYPE *A, ਅਚਲ RECTTYPE *B, RECTTYPE *ਨਤੀਜਾ)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        ਵਾਪਸ SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        ਵਾਪਸ SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_ਉਛਾਲ(A) || SDL_RECT_CAN_ਉਛਾਲ(B)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Potential rect math overflow");
    }
    CHECK_PARAM(!ਨਤੀਜਾ) {
        ਵਾਪਸ SDL_InvalidParamError("result");
    }

    ਜੇ (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        ਜੇ (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(ਨਤੀਜਾ);
        } ਨਹੀਂਤਾਂ { // A empty, B not empty
            *ਨਤੀਜਾ = *B;
        }
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *ਨਤੀਜਾ = *A;
        ਵਾਪਸ true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ਜੇ (Bmin < Amin) {
        Amin = Bmin;
    }
    ਨਤੀਜਾ->x = Amin;
    ਜੇ (Bmax > Amax) {
        Amax = Bmax;
    }
    ਨਤੀਜਾ->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ਜੇ (Bmin < Amin) {
        Amin = Bmin;
    }
    ਨਤੀਜਾ->y = Amin;
    ਜੇ (Bmax > Amax) {
        Amax = Bmax;
    }
    ਨਤੀਜਾ->h = Amax - Amin;
    ਵਾਪਸ true;
}

bool SDL_ENCLOSEPOINTS(ਅਚਲ POINTTYPE *points, ਪੂਰਨ ਗਿਣਤੀ_2, ਅਚਲ RECTTYPE *clip, RECTTYPE *ਨਤੀਜਾ)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    ਪੂਰਨ i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(ਗਿਣਤੀ_2 < 1) {
        SDL_InvalidParamError("count");
        ਵਾਪਸ false;
    }

    ਜੇ (clip) {
        bool added = false;
        ਅਚਲ SCALARTYPE clip_minx = clip->x;
        ਅਚਲ SCALARTYPE clip_miny = clip->y;
        ਅਚਲ SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ਅਚਲ SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        ਜੇ (SDL_RECTEMPTY(clip)) {
            ਵਾਪਸ false;
        }

        ਲਈ (i = 0; i < ਗਿਣਤੀ_2; ++i) {
            x = points[i].x;
            y = points[i].y;

            ਜੇ (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                ਜਾਰੀ;
            }
            ਜੇ (!added) {
                // Special case: if no result was requested, we are done
                ਜੇ (!ਨਤੀਜਾ) {
                    ਵਾਪਸ true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                ਜਾਰੀ;
            }
            ਜੇ (x < minx) {
                minx = x;
            } ਨਹੀਂਤਾਂ ਜੇ (x > maxx) {
                maxx = x;
            }
            ਜੇ (y < miny) {
                miny = y;
            } ਨਹੀਂਤਾਂ ਜੇ (y > maxy) {
                maxy = y;
            }
        }
        ਜੇ (!added) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        // Special case: if no result was requested, we are done
        ਜੇ (!ਨਤੀਜਾ) {
            ਵਾਪਸ true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        ਲਈ (i = 1; i < ਗਿਣਤੀ_2; ++i) {
            x = points[i].x;
            y = points[i].y;

            ਜੇ (x < minx) {
                minx = x;
            } ਨਹੀਂਤਾਂ ਜੇ (x > maxx) {
                maxx = x;
            }
            ਜੇ (y < miny) {
                miny = y;
            } ਨਹੀਂਤਾਂ ਜੇ (y > maxy) {
                maxy = y;
            }
        }
    }

    ਜੇ (ਨਤੀਜਾ) {
        ਨਤੀਜਾ->x = minx;
        ਨਤੀਜਾ->y = miny;
        ਨਤੀਜਾ->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        ਨਤੀਜਾ->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    ਵਾਪਸ true;
}

// Use the Cohen-Sutherland algorithm for line clipping
ਸਥਿਰ ਪੂਰਨ COMPUTEOUTCODE(ਅਚਲ RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    ਪੂਰਨ ਕੋਡ = 0;
    ਜੇ (y < rect->y) {
        ਕੋਡ |= ਕੋਡ_ਸਿਖਰ;
    } ਨਹੀਂਤਾਂ ਜੇ (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        ਕੋਡ |= ਕੋਡ_BOTTOM;
    }
    ਜੇ (x < rect->x) {
        ਕੋਡ |= ਕੋਡ_ਖੱਬਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        ਕੋਡ |= ਕੋਡ_ਸੱਜਾ;
    }
    ਵਾਪਸ ਕੋਡ;
}

bool SDL_INTERSECTRECTANDLINE(ਅਚਲ RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    ਪੂਰਨ outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_ਉਛਾਲ(rect)) {
        SDL_ਸੈੱਟ_Error("Potential rect math overflow");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        ਵਾਪਸ false;
    }

    ਜੇ (SDL_RECTEMPTY(rect)) {
        ਵਾਪਸ false; // Special case for empty rect
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
    ਜੇ (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        ਵਾਪਸ true;
    }

    // Check to see if entire line is to one side of rect
    ਜੇ ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        ਵਾਪਸ false;
    }

    ਜੇ (y1 == y2) { // Horizontal line, easy to clip
        ਜੇ (x1 < rectx1) {
            *X1 = rectx1;
        } ਨਹੀਂਤਾਂ ਜੇ (x1 > rectx2) {
            *X1 = rectx2;
        }
        ਜੇ (x2 < rectx1) {
            *X2 = rectx1;
        } ਨਹੀਂਤਾਂ ਜੇ (x2 > rectx2) {
            *X2 = rectx2;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (x1 == x2) { // Vertical line, easy to clip
        ਜੇ (y1 < recty1) {
            *Y1 = recty1;
        } ਨਹੀਂਤਾਂ ਜੇ (y1 > recty2) {
            *Y1 = recty2;
        }
        ਜੇ (y2 < recty1) {
            *Y2 = recty1;
        } ਨਹੀਂਤਾਂ ਜੇ (y2 > recty2) {
            *Y2 = recty2;
        }
        ਵਾਪਸ true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    ਜਦੋਂ (outcode1 || outcode2) {
        ਜੇ (outcode1 & outcode2) {
            ਵਾਪਸ false;
        }

        ਜੇ (outcode1) {
            ਜੇ (outcode1 & ਕੋਡ_ਸਿਖਰ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ਨਹੀਂਤਾਂ ਜੇ (outcode1 & ਕੋਡ_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ਨਹੀਂਤਾਂ ਜੇ (outcode1 & ਕੋਡ_ਖੱਬਾ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ਨਹੀਂਤਾਂ ਜੇ (outcode1 & ਕੋਡ_ਸੱਜਾ) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (outcode2 & ਕੋਡ_ਸਿਖਰ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ਨਹੀਂਤਾਂ ਜੇ (outcode2 & ਕੋਡ_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ਨਹੀਂਤਾਂ ਜੇ (outcode2 & ਕੋਡ_ਖੱਬਾ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ਨਹੀਂਤਾਂ ਜੇ (outcode2 & ਕੋਡ_ਸੱਜਾ) {
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
    ਵਾਪਸ true;
}

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ RECTTYPE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ POINTTYPE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SCALARTYPE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ BIGSCALARTYPE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ COMPUTEOUTCODE
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ENCLOSEPOINTS_EPSILON
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_RECT_CAN_ਉਛਾਲ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_HASINTERSECTION
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_INTERSECTRECT
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_RECTEMPTY
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_UNIONRECT
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_ENCLOSEPOINTS
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_INTERSECTRECTANDLINE

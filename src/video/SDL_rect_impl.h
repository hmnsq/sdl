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

ಸ್ಥಿರ bool SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(ಸ್ಥಿರಾಂಕ RECTTYPE *rect)
{
    ಆದರೆ (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

bool SDL_HASINTERSECTION(ಸ್ಥಿರಾಂಕ RECTTYPE *A, ಸ್ಥಿರಾಂಕ RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(A) || SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(B)) {
        SDL_ಗಣ_Error("Potential rect math overflow");
        ಹಿಂತಿರುಗಿ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ಆದರೆ (Bmin > Amin) {
        Amin = Bmin;
    }
    ಆದರೆ (Bmax < Amax) {
        Amax = Bmax;
    }
    ಆದರೆ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ಹಿಂತಿರುಗಿ false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ಆದರೆ (Bmin > Amin) {
        Amin = Bmin;
    }
    ಆದರೆ (Bmax < Amax) {
        Amax = Bmax;
    }
    ಆದರೆ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_INTERSECTRECT(ಸ್ಥಿರಾಂಕ RECTTYPE *A, ಸ್ಥಿರಾಂಕ RECTTYPE *B, RECTTYPE *ಫಲಿತಾಂಶ)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(A) || SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(B)) {
        SDL_ಗಣ_Error("Potential rect math overflow");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!ಫಲಿತಾಂಶ) {
        SDL_InvalidParamError("result");
        ಹಿಂತಿರುಗಿ false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ಆದರೆ (Bmin > Amin) {
        Amin = Bmin;
    }
    ಫಲಿತಾಂಶ->x = Amin;
    ಆದರೆ (Bmax < Amax) {
        Amax = Bmax;
    }
    ಫಲಿತಾಂಶ->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ಆದರೆ (Bmin > Amin) {
        Amin = Bmin;
    }
    ಫಲಿತಾಂಶ->y = Amin;
    ಆದರೆ (Bmax < Amax) {
        Amax = Bmax;
    }
    ಫಲಿತಾಂಶ->h = Amax - Amin;

    ಹಿಂತಿರುಗಿ !SDL_RECTEMPTY(ಫಲಿತಾಂಶ);
}

bool SDL_UNIONRECT(ಸ್ಥಿರಾಂಕ RECTTYPE *A, ಸ್ಥಿರಾಂಕ RECTTYPE *B, RECTTYPE *ಫಲಿತಾಂಶ)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(A) || SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(B)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Potential rect math overflow");
    }
    CHECK_PARAM(!ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("result");
    }

    ಆದರೆ (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        ಆದರೆ (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(ಫಲಿತಾಂಶ);
        } ಇಲ್ಲದಿದ್ದರೆ { // A empty, B not empty
            *ಫಲಿತಾಂಶ = *B;
        }
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *ಫಲಿತಾಂಶ = *A;
        ಹಿಂತಿರುಗಿ true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ಆದರೆ (Bmin < Amin) {
        Amin = Bmin;
    }
    ಫಲಿತಾಂಶ->x = Amin;
    ಆದರೆ (Bmax > Amax) {
        Amax = Bmax;
    }
    ಫಲಿತಾಂಶ->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ಆದರೆ (Bmin < Amin) {
        Amin = Bmin;
    }
    ಫಲಿತಾಂಶ->y = Amin;
    ಆದರೆ (Bmax > Amax) {
        Amax = Bmax;
    }
    ಫಲಿತಾಂಶ->h = Amax - Amin;
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ENCLOSEPOINTS(ಸ್ಥಿರಾಂಕ POINTTYPE *points, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಸ್ಥಿರಾಂಕ RECTTYPE *clip, RECTTYPE *ಫಲಿತಾಂಶ)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    ಪೂರ್ಣಾಂಕ i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(ಎಣಿಕೆ_2 < 1) {
        SDL_InvalidParamError("count");
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (clip) {
        bool added = false;
        ಸ್ಥಿರಾಂಕ SCALARTYPE clip_minx = clip->x;
        ಸ್ಥಿರಾಂಕ SCALARTYPE clip_miny = clip->y;
        ಸ್ಥಿರಾಂಕ SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        ಸ್ಥಿರಾಂಕ SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        ಆದರೆ (SDL_RECTEMPTY(clip)) {
            ಹಿಂತಿರುಗಿ false;
        }

        ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2; ++i) {
            x = points[i].x;
            y = points[i].y;

            ಆದರೆ (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                ಮುಂದುವರಿ;
            }
            ಆದರೆ (!added) {
                // Special case: if no result was requested, we are done
                ಆದರೆ (!ಫಲಿತಾಂಶ) {
                    ಹಿಂತಿರುಗಿ true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                ಮುಂದುವರಿ;
            }
            ಆದರೆ (x < minx) {
                minx = x;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x > maxx) {
                maxx = x;
            }
            ಆದರೆ (y < miny) {
                miny = y;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (y > maxy) {
                maxy = y;
            }
        }
        ಆದರೆ (!added) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Special case: if no result was requested, we are done
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            ಹಿಂತಿರುಗಿ true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        ಗಾಗಿ (i = 1; i < ಎಣಿಕೆ_2; ++i) {
            x = points[i].x;
            y = points[i].y;

            ಆದರೆ (x < minx) {
                minx = x;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x > maxx) {
                maxx = x;
            }
            ಆದರೆ (y < miny) {
                miny = y;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (y > maxy) {
                maxy = y;
            }
        }
    }

    ಆದರೆ (ಫಲಿತಾಂಶ) {
        ಫಲಿತಾಂಶ->x = minx;
        ಫಲಿತಾಂಶ->y = miny;
        ಫಲಿತಾಂಶ->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        ಫಲಿತಾಂಶ->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    ಹಿಂತಿರುಗಿ true;
}

// Use the Cohen-Sutherland algorithm for line clipping
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ COMPUTEOUTCODE(ಸ್ಥಿರಾಂಕ RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    ಪೂರ್ಣಾಂಕ ಸಂಕೇತ_2 = 0;
    ಆದರೆ (y < rect->y) {
        ಸಂಕೇತ_2 |= ಸಂಕೇತ_ತುದಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        ಸಂಕೇತ_2 |= ಸಂಕೇತ_BOTTOM;
    }
    ಆದರೆ (x < rect->x) {
        ಸಂಕೇತ_2 |= ಸಂಕೇತ_ಎಡ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        ಸಂಕೇತ_2 |= ಸಂಕೇತ_ಬಲ;
    }
    ಹಿಂತಿರುಗಿ ಸಂಕೇತ_2;
}

bool SDL_INTERSECTRECTANDLINE(ಸ್ಥಿರಾಂಕ RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    ಪೂರ್ಣಾಂಕ outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ(rect)) {
        SDL_ಗಣ_Error("Potential rect math overflow");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (SDL_RECTEMPTY(rect)) {
        ಹಿಂತಿರುಗಿ false; // Special case for empty rect
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
    ಆದರೆ (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        ಹಿಂತಿರುಗಿ true;
    }

    // Check to see if entire line is to one side of rect
    ಆದರೆ ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (y1 == y2) { // Horizontal line, easy to clip
        ಆದರೆ (x1 < rectx1) {
            *X1 = rectx1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x1 > rectx2) {
            *X1 = rectx2;
        }
        ಆದರೆ (x2 < rectx1) {
            *X2 = rectx1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x2 > rectx2) {
            *X2 = rectx2;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (x1 == x2) { // Vertical line, easy to clip
        ಆದರೆ (y1 < recty1) {
            *Y1 = recty1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (y1 > recty2) {
            *Y1 = recty2;
        }
        ಆದರೆ (y2 < recty1) {
            *Y2 = recty1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (y2 > recty2) {
            *Y2 = recty2;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    ಆಗ (outcode1 || outcode2) {
        ಆದರೆ (outcode1 & outcode2) {
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (outcode1) {
            ಆದರೆ (outcode1 & ಸಂಕೇತ_ತುದಿ) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (outcode1 & ಸಂಕೇತ_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (outcode1 & ಸಂಕೇತ_ಎಡ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (outcode1 & ಸಂಕೇತ_ಬಲ) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (outcode2 & ಸಂಕೇತ_ತುದಿ) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (outcode2 & ಸಂಕೇತ_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (outcode2 & ಸಂಕೇತ_ಎಡ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (outcode2 & ಸಂಕೇತ_ಬಲ) {
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
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು RECTTYPE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು POINTTYPE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SCALARTYPE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು BIGSCALARTYPE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು COMPUTEOUTCODE
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ENCLOSEPOINTS_EPSILON
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_RECT_CAN_ಅತಿಪ್ರವಾಹ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_HASINTERSECTION
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_INTERSECTRECT
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_RECTEMPTY
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_UNIONRECT
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_ENCLOSEPOINTS
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_INTERSECTRECTANDLINE

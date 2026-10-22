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

స్థిర bool SDL_RECT_CAN_అధికప్రవాహం(స్థిరరాశి RECTTYPE *rect)
{
    ఒకవేళ (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        తిరిగి true;
    }
    తిరిగి false;
}

bool SDL_HASINTERSECTION(స్థిరరాశి RECTTYPE *A, స్థిరరాశి RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        తిరిగి false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        తిరిగి false;
    }
    CHECK_PARAM(SDL_RECT_CAN_అధికప్రవాహం(A) || SDL_RECT_CAN_అధికప్రవాహం(B)) {
        SDL_సమితి_Error("Potential rect math overflow");
        తిరిగి false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ఒకవేళ (Bmin > Amin) {
        Amin = Bmin;
    }
    ఒకవేళ (Bmax < Amax) {
        Amax = Bmax;
    }
    ఒకవేళ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        తిరిగి false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ఒకవేళ (Bmin > Amin) {
        Amin = Bmin;
    }
    ఒకవేళ (Bmax < Amax) {
        Amax = Bmax;
    }
    ఒకవేళ ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool SDL_INTERSECTRECT(స్థిరరాశి RECTTYPE *A, స్థిరరాశి RECTTYPE *B, RECTTYPE *ఫలితం)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        తిరిగి false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        తిరిగి false;
    }
    CHECK_PARAM(SDL_RECT_CAN_అధికప్రవాహం(A) || SDL_RECT_CAN_అధికప్రవాహం(B)) {
        SDL_సమితి_Error("Potential rect math overflow");
        తిరిగి false;
    }
    CHECK_PARAM(!ఫలితం) {
        SDL_InvalidParamError("result");
        తిరిగి false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ఒకవేళ (Bmin > Amin) {
        Amin = Bmin;
    }
    ఫలితం->x = Amin;
    ఒకవేళ (Bmax < Amax) {
        Amax = Bmax;
    }
    ఫలితం->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ఒకవేళ (Bmin > Amin) {
        Amin = Bmin;
    }
    ఫలితం->y = Amin;
    ఒకవేళ (Bmax < Amax) {
        Amax = Bmax;
    }
    ఫలితం->h = Amax - Amin;

    తిరిగి !SDL_RECTEMPTY(ఫలితం);
}

bool SDL_UNIONRECT(స్థిరరాశి RECTTYPE *A, స్థిరరాశి RECTTYPE *B, RECTTYPE *ఫలితం)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        తిరిగి SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        తిరిగి SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_అధికప్రవాహం(A) || SDL_RECT_CAN_అధికప్రవాహం(B)) {
        తిరిగి SDL_సమితి_Error("Potential rect math overflow");
    }
    CHECK_PARAM(!ఫలితం) {
        తిరిగి SDL_InvalidParamError("result");
    }

    ఒకవేళ (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        ఒకవేళ (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(ఫలితం);
        } లేకపోతే { // A empty, B not empty
            *ఫలితం = *B;
        }
        తిరిగి true;
    } లేకపోతే ఒకవేళ (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *ఫలితం = *A;
        తిరిగి true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    ఒకవేళ (Bmin < Amin) {
        Amin = Bmin;
    }
    ఫలితం->x = Amin;
    ఒకవేళ (Bmax > Amax) {
        Amax = Bmax;
    }
    ఫలితం->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    ఒకవేళ (Bmin < Amin) {
        Amin = Bmin;
    }
    ఫలితం->y = Amin;
    ఒకవేళ (Bmax > Amax) {
        Amax = Bmax;
    }
    ఫలితం->h = Amax - Amin;
    తిరిగి true;
}

bool SDL_ENCLOSEPOINTS(స్థిరరాశి POINTTYPE *points, పూర్ణాంకం లెక్క, స్థిరరాశి RECTTYPE *clip, RECTTYPE *ఫలితం)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    పూర్ణాంకం i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        తిరిగి false;
    }
    CHECK_PARAM(లెక్క < 1) {
        SDL_InvalidParamError("count");
        తిరిగి false;
    }

    ఒకవేళ (clip) {
        bool added = false;
        స్థిరరాశి SCALARTYPE clip_minx = clip->x;
        స్థిరరాశి SCALARTYPE clip_miny = clip->y;
        స్థిరరాశి SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        స్థిరరాశి SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        ఒకవేళ (SDL_RECTEMPTY(clip)) {
            తిరిగి false;
        }

        కొరకు (i = 0; i < లెక్క; ++i) {
            x = points[i].x;
            y = points[i].y;

            ఒకవేళ (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                కొనసాగు;
            }
            ఒకవేళ (!added) {
                // Special case: if no result was requested, we are done
                ఒకవేళ (!ఫలితం) {
                    తిరిగి true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                కొనసాగు;
            }
            ఒకవేళ (x < minx) {
                minx = x;
            } లేకపోతే ఒకవేళ (x > maxx) {
                maxx = x;
            }
            ఒకవేళ (y < miny) {
                miny = y;
            } లేకపోతే ఒకవేళ (y > maxy) {
                maxy = y;
            }
        }
        ఒకవేళ (!added) {
            తిరిగి false;
        }
    } లేకపోతే {
        // Special case: if no result was requested, we are done
        ఒకవేళ (!ఫలితం) {
            తిరిగి true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        కొరకు (i = 1; i < లెక్క; ++i) {
            x = points[i].x;
            y = points[i].y;

            ఒకవేళ (x < minx) {
                minx = x;
            } లేకపోతే ఒకవేళ (x > maxx) {
                maxx = x;
            }
            ఒకవేళ (y < miny) {
                miny = y;
            } లేకపోతే ఒకవేళ (y > maxy) {
                maxy = y;
            }
        }
    }

    ఒకవేళ (ఫలితం) {
        ఫలితం->x = minx;
        ఫలితం->y = miny;
        ఫలితం->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        ఫలితం->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    తిరిగి true;
}

// Use the Cohen-Sutherland algorithm for line clipping
స్థిర పూర్ణాంకం COMPUTEOUTCODE(స్థిరరాశి RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    పూర్ణాంకం సంకేతం_2 = 0;
    ఒకవేళ (y < rect->y) {
        సంకేతం_2 |= సంకేతం_శిఖరం;
    } లేకపోతే ఒకవేళ (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        సంకేతం_2 |= సంకేతం_BOTTOM;
    }
    ఒకవేళ (x < rect->x) {
        సంకేతం_2 |= సంకేతం_ఎడమ;
    } లేకపోతే ఒకవేళ (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        సంకేతం_2 |= సంకేతం_కుడి;
    }
    తిరిగి సంకేతం_2;
}

bool SDL_INTERSECTRECTANDLINE(స్థిరరాశి RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    పూర్ణాంకం outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        తిరిగి false;
    }
    CHECK_PARAM(SDL_RECT_CAN_అధికప్రవాహం(rect)) {
        SDL_సమితి_Error("Potential rect math overflow");
        తిరిగి false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        తిరిగి false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        తిరిగి false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        తిరిగి false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        తిరిగి false;
    }

    ఒకవేళ (SDL_RECTEMPTY(rect)) {
        తిరిగి false; // Special case for empty rect
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
    ఒకవేళ (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        తిరిగి true;
    }

    // Check to see if entire line is to one side of rect
    ఒకవేళ ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        తిరిగి false;
    }

    ఒకవేళ (y1 == y2) { // Horizontal line, easy to clip
        ఒకవేళ (x1 < rectx1) {
            *X1 = rectx1;
        } లేకపోతే ఒకవేళ (x1 > rectx2) {
            *X1 = rectx2;
        }
        ఒకవేళ (x2 < rectx1) {
            *X2 = rectx1;
        } లేకపోతే ఒకవేళ (x2 > rectx2) {
            *X2 = rectx2;
        }
        తిరిగి true;
    }

    ఒకవేళ (x1 == x2) { // Vertical line, easy to clip
        ఒకవేళ (y1 < recty1) {
            *Y1 = recty1;
        } లేకపోతే ఒకవేళ (y1 > recty2) {
            *Y1 = recty2;
        }
        ఒకవేళ (y2 < recty1) {
            *Y2 = recty1;
        } లేకపోతే ఒకవేళ (y2 > recty2) {
            *Y2 = recty2;
        }
        తిరిగి true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    అయితే (outcode1 || outcode2) {
        ఒకవేళ (outcode1 & outcode2) {
            తిరిగి false;
        }

        ఒకవేళ (outcode1) {
            ఒకవేళ (outcode1 & సంకేతం_శిఖరం) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } లేకపోతే ఒకవేళ (outcode1 & సంకేతం_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } లేకపోతే ఒకవేళ (outcode1 & సంకేతం_ఎడమ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } లేకపోతే ఒకవేళ (outcode1 & సంకేతం_కుడి) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } లేకపోతే {
            ఒకవేళ (outcode2 & సంకేతం_శిఖరం) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } లేకపోతే ఒకవేళ (outcode2 & సంకేతం_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } లేకపోతే ఒకవేళ (outcode2 & సంకేతం_ఎడమ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } లేకపోతే ఒకవేళ (outcode2 & సంకేతం_కుడి) {
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
    తిరిగి true;
}

#నిర్వచనం_రద్దు RECTTYPE
#నిర్వచనం_రద్దు POINTTYPE
#నిర్వచనం_రద్దు SCALARTYPE
#నిర్వచనం_రద్దు BIGSCALARTYPE
#నిర్వచనం_రద్దు COMPUTEOUTCODE
#నిర్వచనం_రద్దు ENCLOSEPOINTS_EPSILON
#నిర్వచనం_రద్దు SDL_RECT_CAN_అధికప్రవాహం
#నిర్వచనం_రద్దు SDL_HASINTERSECTION
#నిర్వచనం_రద్దు SDL_INTERSECTRECT
#నిర్వచనం_రద్దు SDL_RECTEMPTY
#నిర్వచనం_రద్దు SDL_UNIONRECT
#నిర్వచనం_రద్దు SDL_ENCLOSEPOINTS
#నిర్వచనం_రద్దు SDL_INTERSECTRECTANDLINE

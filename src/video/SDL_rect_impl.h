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

अटल bool SDL_RECT_CAN_OVERFLOW(स्थिर RECTTYPE *rect)
{
    अगर (rect->x <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->x >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->y <= (SCALARTYPE)(SDL_MIN_SINT32 / 2) ||
        rect->y >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->w >= (SCALARTYPE)(SDL_MAX_SINT32 / 2) ||
        rect->h >= (SCALARTYPE)(SDL_MAX_SINT32 / 2)) {
        वापस true;
    }
    वापस false;
}

bool SDL_HASINTERSECTION(स्थिर RECTTYPE *A, स्थिर RECTTYPE *B)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        वापस false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        वापस false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        वापस false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    अगर (Bmin > Amin) {
        Amin = Bmin;
    }
    अगर (Bmax < Amax) {
        Amax = Bmax;
    }
    अगर ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        वापस false;
    }
    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    अगर (Bmin > Amin) {
        Amin = Bmin;
    }
    अगर (Bmax < Amax) {
        Amax = Bmax;
    }
    अगर ((Amax - ENCLOSEPOINTS_EPSILON) < Amin) {
        वापस false;
    }
    वापस true;
}

bool SDL_INTERSECTRECT(स्थिर RECTTYPE *A, स्थिर RECTTYPE *B, RECTTYPE *परिणाम)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        SDL_InvalidParamError("A");
        वापस false;
    }
    CHECK_PARAM(!B) {
        SDL_InvalidParamError("B");
        वापस false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        SDL_SetError("Potential rect math overflow");
        वापस false;
    }
    CHECK_PARAM(!परिणाम) {
        SDL_InvalidParamError("result");
        वापस false;
    }

    // Horizontal intersection
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    अगर (Bmin > Amin) {
        Amin = Bmin;
    }
    परिणाम->x = Amin;
    अगर (Bmax < Amax) {
        Amax = Bmax;
    }
    परिणाम->w = Amax - Amin;

    // Vertical intersection
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    अगर (Bmin > Amin) {
        Amin = Bmin;
    }
    परिणाम->y = Amin;
    अगर (Bmax < Amax) {
        Amax = Bmax;
    }
    परिणाम->h = Amax - Amin;

    वापस !SDL_RECTEMPTY(परिणाम);
}

bool SDL_UNIONRECT(स्थिर RECTTYPE *A, स्थिर RECTTYPE *B, RECTTYPE *परिणाम)
{
    SCALARTYPE Amin, Amax, Bmin, Bmax;

    CHECK_PARAM(!A) {
        वापस SDL_InvalidParamError("A");
    }
    CHECK_PARAM(!B) {
        वापस SDL_InvalidParamError("B");
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(A) || SDL_RECT_CAN_OVERFLOW(B)) {
        वापस SDL_SetError("Potential rect math overflow");
    }
    CHECK_PARAM(!परिणाम) {
        वापस SDL_InvalidParamError("result");
    }

    अगर (SDL_RECTEMPTY(A)) { // Special cases for empty Rects
        अगर (SDL_RECTEMPTY(B)) {    // A and B empty
            SDL_zerop(परिणाम);
        } अन्यथा { // A empty, B not empty
            *परिणाम = *B;
        }
        वापस true;
    } अन्यथा अगर (SDL_RECTEMPTY(B)) { // A not empty, B empty
        *परिणाम = *A;
        वापस true;
    }

    // Horizontal union
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    अगर (Bmin < Amin) {
        Amin = Bmin;
    }
    परिणाम->x = Amin;
    अगर (Bmax > Amax) {
        Amax = Bmax;
    }
    परिणाम->w = Amax - Amin;

    // Vertical union
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    अगर (Bmin < Amin) {
        Amin = Bmin;
    }
    परिणाम->y = Amin;
    अगर (Bmax > Amax) {
        Amax = Bmax;
    }
    परिणाम->h = Amax - Amin;
    वापस true;
}

bool SDL_ENCLOSEPOINTS(स्थिर POINTTYPE *points, पूर्णांक गिनती, स्थिर RECTTYPE *clip, RECTTYPE *परिणाम)
{
    SCALARTYPE minx = 0;
    SCALARTYPE miny = 0;
    SCALARTYPE maxx = 0;
    SCALARTYPE maxy = 0;
    SCALARTYPE x, y;
    पूर्णांक i;

    CHECK_PARAM(!points) {
        SDL_InvalidParamError("points");
        वापस false;
    }
    CHECK_PARAM(गिनती < 1) {
        SDL_InvalidParamError("count");
        वापस false;
    }

    अगर (clip) {
        bool added = false;
        स्थिर SCALARTYPE clip_minx = clip->x;
        स्थिर SCALARTYPE clip_miny = clip->y;
        स्थिर SCALARTYPE clip_maxx = clip->x + clip->w - ENCLOSEPOINTS_EPSILON;
        स्थिर SCALARTYPE clip_maxy = clip->y + clip->h - ENCLOSEPOINTS_EPSILON;

        // Special case for empty rectangle
        अगर (SDL_RECTEMPTY(clip)) {
            वापस false;
        }

        क्रम (i = 0; i < गिनती; ++i) {
            x = points[i].x;
            y = points[i].y;

            अगर (x < clip_minx || x > clip_maxx ||
                y < clip_miny || y > clip_maxy) {
                जारी;
            }
            अगर (!added) {
                // Special case: if no result was requested, we are done
                अगर (!परिणाम) {
                    वापस true;
                }

                // First point added
                minx = maxx = x;
                miny = maxy = y;
                added = true;
                जारी;
            }
            अगर (x < minx) {
                minx = x;
            } अन्यथा अगर (x > maxx) {
                maxx = x;
            }
            अगर (y < miny) {
                miny = y;
            } अन्यथा अगर (y > maxy) {
                maxy = y;
            }
        }
        अगर (!added) {
            वापस false;
        }
    } अन्यथा {
        // Special case: if no result was requested, we are done
        अगर (!परिणाम) {
            वापस true;
        }

        // No clipping, always add the first point
        minx = maxx = points[0].x;
        miny = maxy = points[0].y;

        क्रम (i = 1; i < गिनती; ++i) {
            x = points[i].x;
            y = points[i].y;

            अगर (x < minx) {
                minx = x;
            } अन्यथा अगर (x > maxx) {
                maxx = x;
            }
            अगर (y < miny) {
                miny = y;
            } अन्यथा अगर (y > maxy) {
                maxy = y;
            }
        }
    }

    अगर (परिणाम) {
        परिणाम->x = minx;
        परिणाम->y = miny;
        परिणाम->w = (maxx - minx) + ENCLOSEPOINTS_EPSILON;
        परिणाम->h = (maxy - miny) + ENCLOSEPOINTS_EPSILON;
    }
    वापस true;
}

// Use the Cohen-Sutherland algorithm for line clipping
अटल पूर्णांक COMPUTEOUTCODE(स्थिर RECTTYPE *rect, SCALARTYPE x, SCALARTYPE y)
{
    पूर्णांक code = 0;
    अगर (y < rect->y) {
        code |= CODE_शीर्ष;
    } अन्यथा अगर (y > (rect->y + rect->h - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_BOTTOM;
    }
    अगर (x < rect->x) {
        code |= CODE_बायाँ;
    } अन्यथा अगर (x > (rect->x + rect->w - ENCLOSEPOINTS_EPSILON)) {
        code |= CODE_दायाँ;
    }
    वापस code;
}

bool SDL_INTERSECTRECTANDLINE(स्थिर RECTTYPE *rect, SCALARTYPE *X1, SCALARTYPE *Y1, SCALARTYPE *X2, SCALARTYPE *Y2)
{
    SCALARTYPE x = 0;
    SCALARTYPE y = 0;
    SCALARTYPE x1, y1;
    SCALARTYPE x2, y2;
    SCALARTYPE rectx1;
    SCALARTYPE recty1;
    SCALARTYPE rectx2;
    SCALARTYPE recty2;
    पूर्णांक outcode1, outcode2;

    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        वापस false;
    }
    CHECK_PARAM(SDL_RECT_CAN_OVERFLOW(rect)) {
        SDL_SetError("Potential rect math overflow");
        वापस false;
    }
    CHECK_PARAM(!X1) {
        SDL_InvalidParamError("X1");
        वापस false;
    }
    CHECK_PARAM(!Y1) {
        SDL_InvalidParamError("Y1");
        वापस false;
    }
    CHECK_PARAM(!X2) {
        SDL_InvalidParamError("X2");
        वापस false;
    }
    CHECK_PARAM(!Y2) {
        SDL_InvalidParamError("Y2");
        वापस false;
    }

    अगर (SDL_RECTEMPTY(rect)) {
        वापस false; // Special case for empty rect
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
    अगर (x1 >= rectx1 && x1 <= rectx2 && x2 >= rectx1 && x2 <= rectx2 &&
        y1 >= recty1 && y1 <= recty2 && y2 >= recty1 && y2 <= recty2) {
        वापस true;
    }

    // Check to see if entire line is to one side of rect
    अगर ((x1 < rectx1 && x2 < rectx1) || (x1 > rectx2 && x2 > rectx2) ||
        (y1 < recty1 && y2 < recty1) || (y1 > recty2 && y2 > recty2)) {
        वापस false;
    }

    अगर (y1 == y2) { // Horizontal line, easy to clip
        अगर (x1 < rectx1) {
            *X1 = rectx1;
        } अन्यथा अगर (x1 > rectx2) {
            *X1 = rectx2;
        }
        अगर (x2 < rectx1) {
            *X2 = rectx1;
        } अन्यथा अगर (x2 > rectx2) {
            *X2 = rectx2;
        }
        वापस true;
    }

    अगर (x1 == x2) { // Vertical line, easy to clip
        अगर (y1 < recty1) {
            *Y1 = recty1;
        } अन्यथा अगर (y1 > recty2) {
            *Y1 = recty2;
        }
        अगर (y2 < recty1) {
            *Y2 = recty1;
        } अन्यथा अगर (y2 > recty2) {
            *Y2 = recty2;
        }
        वापस true;
    }

    // More complicated Cohen-Sutherland algorithm
    outcode1 = COMPUTEOUTCODE(rect, x1, y1);
    outcode2 = COMPUTEOUTCODE(rect, x2, y2);
    जबतक (outcode1 || outcode2) {
        अगर (outcode1 & outcode2) {
            वापस false;
        }

        अगर (outcode1) {
            अगर (outcode1 & CODE_शीर्ष) {
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा अगर (outcode1 & CODE_BOTTOM) {
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा अगर (outcode1 & CODE_बायाँ) {
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } अन्यथा अगर (outcode1 & CODE_दायाँ) {
                x = rectx2;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            }
            x1 = x;
            y1 = y;
            outcode1 = COMPUTEOUTCODE(rect, x, y);
        } अन्यथा {
            अगर (outcode2 & CODE_शीर्ष) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty1;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा अगर (outcode2 & CODE_BOTTOM) {
                SDL_assert(y2 != y1); // if equal: division by zero.
                y = recty2;
                x = (SCALARTYPE) (x1 + ((BIGSCALARTYPE)(x2 - x1) * (y - y1)) / (y2 - y1));
            } अन्यथा अगर (outcode2 & CODE_बायाँ) {
                /* If this assertion ever fires, here's the static analysis that warned about it:
                   http://buildbot.libsdl.org/sdl-static-analysis/sdl-macosx-static-analysis/sdl-macosx-static-analysis-1101/report-b0d01a.html#EndPath */
                SDL_assert(x2 != x1); // if equal: division by zero.
                x = rectx1;
                y = (SCALARTYPE) (y1 + ((BIGSCALARTYPE)(y2 - y1) * (x - x1)) / (x2 - x1));
            } अन्यथा अगर (outcode2 & CODE_दायाँ) {
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
    वापस true;
}

#अघोषित RECTTYPE
#अघोषित POINTTYPE
#अघोषित SCALARTYPE
#अघोषित BIGSCALARTYPE
#अघोषित COMPUTEOUTCODE
#अघोषित ENCLOSEPOINTS_EPSILON
#अघोषित SDL_RECT_CAN_OVERFLOW
#अघोषित SDL_HASINTERSECTION
#अघोषित SDL_INTERSECTRECT
#अघोषित SDL_RECTEMPTY
#अघोषित SDL_UNIONRECT
#अघोषित SDL_ENCLOSEPOINTS
#अघोषित SDL_INTERSECTRECTANDLINE

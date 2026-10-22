/*

SDL_rotate.c: rotates 32bit or 8bit surfaces

Shamelessly stolen from SDL_gfx by Andreas Schiffler. Original copyright follows:

Copyright (C) 2001-2011  Andreas Schiffler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
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

   3. This notice may not be removed or altered from any source
   distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net

*/
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_rotate.h"

// ---- Internally used structures

/**
A 32 bit RGBA pixel.
*/
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ tColorRGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} tColorRGBA;

/**
A 8bit Y/palette pixel.
*/
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ tColorY
{
    Uint8 y;
} tColorY;

/**
Number of guard rows added to destination surfaces.

This is a simple but effective workaround for observed issues.
These rows allocate extra memory and are then hidden from the surface.
Rows are added to the end of destination surfaces when they are allocated.
This catches any potential overflows which seem to happen with
just the right src image dimensions and scale/rotation and can lead
to a situation where the program can segfault.
*/
#ವ್ಯಾಖ್ಯಾನಿಸು GUARD_ಅಡ್ಡಸಾಲುಗಳು (2)

/**
Returns colorkey info for a surface
*/
ಸ್ಥಿರ Uint32 get_colorkey(SDL_Surface *src)
{
    Uint32 ಕೀಲಿ = 0;
    ಆದರೆ (SDL_Surface_Has_Color_ಕೀಲಿ(src)) {
        SDL_Get_Surface_Color_ಕೀಲಿ(src, &ಕೀಲಿ);
    }
    ಹಿಂತಿರುಗಿ ಕೀಲಿ;
}

// rotate (sx, sy) by (angle, center) into (dx, dy)
ಸ್ಥಿರ ಶೂನ್ಯ rotate(ದ್ವಿಗುಣ sx, ದ್ವಿಗುಣ sy, ದ್ವಿಗುಣ sinangle, ದ್ವಿಗುಣ cosangle, ಸ್ಥಿರಾಂಕ SDL_FPoint *center, ದ್ವಿಗುಣ *dx, ದ್ವಿಗುಣ *dy)
{
    sx -= center->x;
    sy -= center->y;

    *dx = cosangle * sx - sinangle * sy;
    *dy = sinangle * sx + cosangle * sy;

    *dx += center->x;
    *dy += center->y;
}

/**
Internal target surface sizing function for rotations with trig result return.

\param width The source surface width.
\param height The source surface height.
\param angle The angle to rotate in degrees.
\param center The center of ratation
\param rect_dest Bounding box of rotated rectangle
\param cangle The sine of the angle
\param sangle The cosine of the angle

*/
ಶೂನ್ಯ SDLgfx_rotozoom_Surface_ಗಾತ್ರ_Trig(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ದ್ವಿಗುಣ angle, ಸ್ಥಿರಾಂಕ SDL_FPoint *center,
                                    SDL_Rect *rect_dest, ದ್ವಿಗುಣ *cangle, ದ್ವಿಗುಣ *sangle)
{
    ಪೂರ್ಣಾಂಕ minx, maxx, miny, maxy;
    ದ್ವಿಗುಣ radangle;
    ದ್ವಿಗುಣ x0, x1, x2, x3;
    ದ್ವಿಗುಣ y0, y1, y2, y3;
    ದ್ವಿಗುಣ sinangle;
    ದ್ವಿಗುಣ cosangle;

    radangle = angle * (SDL_PI_D / 180.0);
    sinangle = SDL_sin(radangle);
    cosangle = SDL_cos(radangle);

    /*
     * Determine destination width and height by rotating a source box, at pixel center
     */
    rotate(0.5, 0.5, sinangle, cosangle, center, &x0, &y0);
    rotate(ಅಗಲ - 0.5, 0.5, sinangle, cosangle, center, &x1, &y1);
    rotate(0.5, ಎತ್ತರ - 0.5, sinangle, cosangle, center, &x2, &y2);
    rotate(ಅಗಲ - 0.5, ಎತ್ತರ - 0.5, sinangle, cosangle, center, &x3, &y3);

    minx = (ಪೂರ್ಣಾಂಕ)SDL_floor(SDL_min(SDL_min(x0, x1), SDL_min(x2, x3)));
    maxx = (ಪೂರ್ಣಾಂಕ)SDL_ceil(SDL_max(SDL_max(x0, x1), SDL_max(x2, x3)));

    miny = (ಪೂರ್ಣಾಂಕ)SDL_floor(SDL_min(SDL_min(y0, y1), SDL_min(y2, y3)));
    maxy = (ಪೂರ್ಣಾಂಕ)SDL_ceil(SDL_max(SDL_max(y0, y1), SDL_max(y2, y3)));

    rect_dest->w = maxx - minx;
    rect_dest->h = maxy - miny;
    rect_dest->x = minx;
    rect_dest->y = miny;

    // reverse the angle because our rotations are clockwise
    *sangle = -sinangle;
    *cangle = cosangle;

    {
        // The trig code below gets the wrong size (due to FP inaccuracy?) when angle is a multiple of 90 degrees
        ಪೂರ್ಣಾಂಕ angle90 = (ಪೂರ್ಣಾಂಕ)(angle / 90);
        ಆದರೆ (angle90 == angle / 90) { // if the angle is a multiple of 90 degrees
            angle90 %= 4;
            ಆದರೆ (angle90 < 0) {
                angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
            }

            ಆದರೆ (angle90 & 1) {
                rect_dest->w = ಎತ್ತರ;
                rect_dest->h = ಅಗಲ;
                *cangle = 0;
                *sangle = angle90 == 1 ? -1 : 1; // reversed because our rotations are clockwise
            } ಇಲ್ಲದಿದ್ದರೆ {
                rect_dest->w = ಅಗಲ;
                rect_dest->h = ಎತ್ತರ;
                *cangle = angle90 == 0 ? 1 : -1;
                *sangle = 0;
            }
        }
    }
}

// Computes source pointer X/Y increments for a rotation that's a multiple of 90 degrees.
ಸ್ಥಿರ ಶೂನ್ಯ compute_ಮೂಲ_Increments90(SDL_Surface *src, ಪೂರ್ಣಾಂಕ bpp, ಪೂರ್ಣಾಂಕ angle, ಪೂರ್ಣಾಂಕ flipx, ಪೂರ್ಣಾಂಕ flipy,
                                      ಪೂರ್ಣಾಂಕ *sincx, ಪೂರ್ಣಾಂಕ *sincy, ಪೂರ್ಣಾಂಕ *signx, ಪೂರ್ಣಾಂಕ *signy)
{
    ಪೂರ್ಣಾಂಕ pitch = flipy ? -src->pitch : src->pitch;
    ಆದರೆ (flipx) {
        bpp = -bpp;
    }
    ಆಯ್ಕೆ (angle) { // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
    ಸ್ಥಿತಿ 0:
        *sincx = bpp;
        *sincy = pitch - src->w * *sincx;
        *signx = *signy = 1;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 1:
        *sincx = -pitch;
        *sincy = bpp - *sincx * src->h;
        *signx = 1;
        *signy = -1;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
        *sincx = -bpp;
        *sincy = -src->w * *sincx - pitch;
        *signx = *signy = -1;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
    ಪೂರ್ವನಿಯೋಜಿತ:
        *sincx = pitch;
        *sincy = -*sincx * src->h - bpp;
        *signx = -1;
        *signy = 1;
        ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (flipx) {
        *signx = -*signx;
    }
    ಆದರೆ (flipy) {
        *signy = -*signy;
    }
}

// Performs a relatively fast rotation/flip when the angle is a multiple of 90 degrees.
#ವ್ಯಾಖ್ಯಾನಿಸು TRANSFORM_SURFACE_90(pixelType)                                                                     \
    ಪೂರ್ಣಾಂಕ dy, dincy = dst->pitch - dst->w * ಗಾತ್ರ(pixelType), sincx, sincy, signx, signy;                    \
    Uint8 *sp = (Uint8 *)src->pixels, *dp = (Uint8 *)dst->pixels, *de;                                      \
                                                                                                            \
    compute_ಮೂಲ_Increments90(src, ಗಾತ್ರ(pixelType), angle, flipx, flipy, &sincx, &sincy, &signx, &signy); \
    ಆದರೆ (signx < 0)                                                                                          \
        sp += (src->w - 1) * ಗಾತ್ರ(pixelType);                                                             \
    ಆದರೆ (signy < 0)                                                                                          \
        sp += (src->h - 1) * src->pitch;                                                                    \
                                                                                                            \
    ಗಾಗಿ (dy = 0; dy < dst->h; sp += sincy, dp += dincy, dy++) {                                             \
        ಆದರೆ (sincx == ಗಾತ್ರ(pixelType)) { /* if advancing src and dest equally, use SDL_memcpy */           \
            SDL_memcpy(dp, sp, dst->w * ಗಾತ್ರ(pixelType));                                                 \
            sp += dst->w * ಗಾತ್ರ(pixelType);                                                               \
            dp += dst->w * ಗಾತ್ರ(pixelType);                                                               \
        } ಇಲ್ಲದಿದ್ದರೆ {                                                                                            \
            ಗಾಗಿ (de = dp + dst->w * ಗಾತ್ರ(pixelType); dp != de; sp += sincx, dp += ಗಾತ್ರ(pixelType)) {    \
                *(pixelType *)dp = *(pixelType *)sp;                                                        \
            }                                                                                               \
        }                                                                                                   \
    }

ಸ್ಥಿರ ಶೂನ್ಯ transformSurfaceRGBA90(SDL_Surface *src, SDL_Surface *dst, ಪೂರ್ಣಾಂಕ angle, ಪೂರ್ಣಾಂಕ flipx, ಪೂರ್ಣಾಂಕ flipy)
{
    TRANSFORM_SURFACE_90(tColorRGBA);
}

ಸ್ಥಿರ ಶೂನ್ಯ transformSurfaceY90(SDL_Surface *src, SDL_Surface *dst, ಪೂರ್ಣಾಂಕ angle, ಪೂರ್ಣಾಂಕ flipx, ಪೂರ್ಣಾಂಕ flipy)
{
    TRANSFORM_SURFACE_90(tColorY);
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು TRANSFORM_SURFACE_90

/**
Internal 32 bit rotozoomer with optional anti-aliasing.

Rotates and zooms 32 bit RGBA/ABGR 'src' surface to 'dst' surface based on the control
parameters by scanning the destination surface and applying optionally anti-aliasing
by bilinear interpolation.
Assumes src and dst surfaces are of 32 bit depth.
Assumes dst surface was allocated with the correct dimensions.

\param src Source surface.
\param dst Destination surface.
\param isin Integer version of sine of angle.
\param icos Integer version of cosine of angle.
\param flipx Flag indicating horizontal mirroring should be applied.
\param flipy Flag indicating vertical mirroring should be applied.
\param smooth Flag indicating anti-aliasing should be used.
\param rect_dest destination coordinates
\param center true center.
*/
ಸ್ಥಿರ ಶೂನ್ಯ transformSurfaceRGBA(SDL_Surface *src, SDL_Surface *dst, ಪೂರ್ಣಾಂಕ isin, ಪೂರ್ಣಾಂಕ icos,
                                 ಪೂರ್ಣಾಂಕ flipx, ಪೂರ್ಣಾಂಕ flipy, ಪೂರ್ಣಾಂಕ smooth,
                                 ಸ್ಥಿರಾಂಕ SDL_Rect *rect_dest,
                                 ಸ್ಥಿರಾಂಕ SDL_FPoint *center)
{
    ಪೂರ್ಣಾಂಕ sw, sh;
    ಪೂರ್ಣಾಂಕ cx, cy;
    tColorRGBA c00, c01, c10, c11, cswap;
    tColorRGBA *pc, *sp;
    ಪೂರ್ಣಾಂಕ gap;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ fp_half = (1 << 15);

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorRGBA *)dst->pixels;
    gap = dst->pitch - dst->w * 4;
    cx = (ಪೂರ್ಣಾಂಕ)(center->x * 65536.0);
    cy = (ಪೂರ್ಣಾಂಕ)(center->y * 65536.0);

    /*
     * Switch between interpolating and non-interpolating code
     */
    ಆದರೆ (smooth) {
        ಪೂರ್ಣಾಂಕ y;
        ಗಾಗಿ (y = 0; y < dst->h; y++) {
            ಪೂರ್ಣಾಂಕ x;
            ದ್ವಿಗುಣ src_x = ((ದ್ವಿಗುಣ)rect_dest->x + 0 + 0.5 - center->x);
            ದ್ವಿಗುಣ src_y = ((ದ್ವಿಗುಣ)rect_dest->y + y + 0.5 - center->y);
            ಪೂರ್ಣಾಂಕ sdx = (ಪೂರ್ಣಾಂಕ)((icos * src_x - isin * src_y) + cx - fp_half);
            ಪೂರ್ಣಾಂಕ sdy = (ಪೂರ್ಣಾಂಕ)((isin * src_x + icos * src_y) + cy - fp_half);
            ಗಾಗಿ (x = 0; x < dst->w; x++) {
                ಪೂರ್ಣಾಂಕ dx = (sdx >> 16);
                ಪೂರ್ಣಾಂಕ dy = (sdy >> 16);
                ಆದರೆ (flipx) {
                    dx = sw - dx;
                }
                ಆದರೆ (flipy) {
                    dy = sh - dy;
                }
                ಆದರೆ ((dx > -1) && (dy > -1) && (dx < (src->w - 1)) && (dy < (src->h - 1))) {
                    ಪೂರ್ಣಾಂಕ ex, ey;
                    ಪೂರ್ಣಾಂಕ t1, t2;
                    sp = (tColorRGBA *)((Uint8 *)src->pixels + src->pitch * dy) + dx;
                    c00 = *sp;
                    sp += 1;
                    c01 = *sp;
                    sp += (src->pitch / 4);
                    c11 = *sp;
                    sp -= 1;
                    c10 = *sp;
                    ಆದರೆ (flipx) {
                        cswap = c00;
                        c00 = c01;
                        c01 = cswap;
                        cswap = c10;
                        c10 = c11;
                        c11 = cswap;
                    }
                    ಆದರೆ (flipy) {
                        cswap = c00;
                        c00 = c10;
                        c10 = cswap;
                        cswap = c01;
                        c01 = c11;
                        c11 = cswap;
                    }
                    /*
                     * Interpolate colors
                     */
                    ex = (sdx & 0xffff);
                    ey = (sdy & 0xffff);
                    t1 = ((((c01.r - c00.r) * ex) >> 16) + c00.r) & 0xff;
                    t2 = ((((c11.r - c10.r) * ex) >> 16) + c10.r) & 0xff;
                    pc->r = (Uint8)((((t2 - t1) * ey) >> 16) + t1);
                    t1 = ((((c01.g - c00.g) * ex) >> 16) + c00.g) & 0xff;
                    t2 = ((((c11.g - c10.g) * ex) >> 16) + c10.g) & 0xff;
                    pc->g = (Uint8)((((t2 - t1) * ey) >> 16) + t1);
                    t1 = ((((c01.b - c00.b) * ex) >> 16) + c00.b) & 0xff;
                    t2 = ((((c11.b - c10.b) * ex) >> 16) + c10.b) & 0xff;
                    pc->b = (Uint8)((((t2 - t1) * ey) >> 16) + t1);
                    t1 = ((((c01.a - c00.a) * ex) >> 16) + c00.a) & 0xff;
                    t2 = ((((c11.a - c10.a) * ex) >> 16) + c10.a) & 0xff;
                    pc->a = (Uint8)((((t2 - t1) * ey) >> 16) + t1);
                }
                sdx += icos;
                sdy += isin;
                pc++;
            }
            pc = (tColorRGBA *)((Uint8 *)pc + gap);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ y;
        ಗಾಗಿ (y = 0; y < dst->h; y++) {
            ಪೂರ್ಣಾಂಕ x;
            ದ್ವಿಗುಣ src_x = ((ದ್ವಿಗುಣ)rect_dest->x + 0 + 0.5 - center->x);
            ದ್ವಿಗುಣ src_y = ((ದ್ವಿಗುಣ)rect_dest->y + y + 0.5 - center->y);
            ಪೂರ್ಣಾಂಕ sdx = (ಪೂರ್ಣಾಂಕ)((icos * src_x - isin * src_y) + cx - fp_half);
            ಪೂರ್ಣಾಂಕ sdy = (ಪೂರ್ಣಾಂಕ)((isin * src_x + icos * src_y) + cy - fp_half);
            ಗಾಗಿ (x = 0; x < dst->w; x++) {
                ಪೂರ್ಣಾಂಕ dx = (sdx >> 16);
                ಪೂರ್ಣಾಂಕ dy = (sdy >> 16);
                ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)dx < (ಚಿಹ್ನೆರಹಿತ)src->w && (ಚಿಹ್ನೆರಹಿತ)dy < (ಚಿಹ್ನೆರಹಿತ)src->h) {
                    ಆದರೆ (flipx) {
                        dx = sw - dx;
                    }
                    ಆದರೆ (flipy) {
                        dy = sh - dy;
                    }
                    *pc = *((tColorRGBA *)((Uint8 *)src->pixels + src->pitch * dy) + dx);
                }
                sdx += icos;
                sdy += isin;
                pc++;
            }
            pc = (tColorRGBA *)((Uint8 *)pc + gap);
        }
    }
}

/**

Rotates and zooms 8 bit palette/Y 'src' surface to 'dst' surface without smoothing.

Rotates and zooms 8 bit RGBA/ABGR 'src' surface to 'dst' surface based on the control
parameters by scanning the destination surface.
Assumes src and dst surfaces are of 8 bit depth.
Assumes dst surface was allocated with the correct dimensions.

\param src Source surface.
\param dst Destination surface.
\param isin Integer version of sine of angle.
\param icos Integer version of cosine of angle.
\param flipx Flag indicating horizontal mirroring should be applied.
\param flipy Flag indicating vertical mirroring should be applied.
\param rect_dest destination coordinates
\param center true center.
*/
ಸ್ಥಿರ ಶೂನ್ಯ transformSurfaceY(SDL_Surface *src, SDL_Surface *dst, ಪೂರ್ಣಾಂಕ isin, ಪೂರ್ಣಾಂಕ icos, ಪೂರ್ಣಾಂಕ flipx, ಪೂರ್ಣಾಂಕ flipy,
                              ಸ್ಥಿರಾಂಕ SDL_Rect *rect_dest,
                              ಸ್ಥಿರಾಂಕ SDL_FPoint *center)
{
    ಪೂರ್ಣಾಂಕ sw, sh;
    ಪೂರ್ಣಾಂಕ cx, cy;
    tColorY *pc;
    ಪೂರ್ಣಾಂಕ gap;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ fp_half = (1 << 15);
    ಪೂರ್ಣಾಂಕ y;

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorY *)dst->pixels;
    gap = dst->pitch - dst->w;
    cx = (ಪೂರ್ಣಾಂಕ)(center->x * 65536.0);
    cy = (ಪೂರ್ಣಾಂಕ)(center->y * 65536.0);

    /*
     * Clear surface to colorkey
     */
    SDL_memset(pc, (ಪೂರ್ಣಾಂಕ)(get_colorkey(src) & 0xff), (size_t)dst->pitch * dst->h);
    /*
     * Iterate through destination surface
     */
    ಗಾಗಿ (y = 0; y < dst->h; y++) {
        ಪೂರ್ಣಾಂಕ x;
        ದ್ವಿಗುಣ src_x = ((ದ್ವಿಗುಣ)rect_dest->x + 0 + 0.5 - center->x);
        ದ್ವಿಗುಣ src_y = ((ದ್ವಿಗುಣ)rect_dest->y + y + 0.5 - center->y);
        ಪೂರ್ಣಾಂಕ sdx = (ಪೂರ್ಣಾಂಕ)((icos * src_x - isin * src_y) + cx - fp_half);
        ಪೂರ್ಣಾಂಕ sdy = (ಪೂರ್ಣಾಂಕ)((isin * src_x + icos * src_y) + cy - fp_half);
        ಗಾಗಿ (x = 0; x < dst->w; x++) {
            ಪೂರ್ಣಾಂಕ dx = (sdx >> 16);
            ಪೂರ್ಣಾಂಕ dy = (sdy >> 16);
            ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)dx < (ಚಿಹ್ನೆರಹಿತ)src->w && (ಚಿಹ್ನೆರಹಿತ)dy < (ಚಿಹ್ನೆರಹಿತ)src->h) {
                ಆದರೆ (flipx) {
                    dx = sw - dx;
                }
                ಆದರೆ (flipy) {
                    dy = sh - dy;
                }
                *pc = *((tColorY *)src->pixels + src->pitch * dy + dx);
            }
            sdx += icos;
            sdy += isin;
            pc++;
        }
        pc += gap;
    }
}

/**
Rotates and zooms a surface with different horizontal and vertival scaling factors and optional anti-aliasing.

Rotates a 32-bit or 8-bit 'src' surface to newly created 'dst' surface.
'angle' is the rotation in degrees, 'center' the rotation center. If 'smooth' is set
then the destination 32-bit surface is anti-aliased. 8-bit surfaces must have a colorkey. 32-bit
surfaces must have a 8888 layout with red, green, blue and alpha masks (any ordering goes).
The blend mode of the 'src' surface has some effects on generation of the 'dst' surface: The NONE
mode will set the BLEND mode on the 'dst' surface. The MOD mode either generates a white 'dst'
surface and sets the colorkey or fills the it with the colorkey before copying the pixels.
When using the NONE and MOD modes, color and alpha modulation must be applied before using this function.

\param src The surface to rotozoom.
\param angle The angle to rotate in degrees.
\param smooth Antialiasing flag; set to SMOOTHING_ON to enable.
\param flipx Set to 1 to flip the image horizontally
\param flipy Set to 1 to flip the image vertically
\param rect_dest The destination rect bounding box
\param cangle The angle cosine
\param sangle The angle sine
\param center The true coordinate of the center of rotation
\return The new rotated surface.

*/

SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, ದ್ವಿಗುಣ angle, ಪೂರ್ಣಾಂಕ smooth, ಪೂರ್ಣಾಂಕ flipx, ಪೂರ್ಣಾಂಕ flipy,
                     ಸ್ಥಿರಾಂಕ SDL_Rect *rect_dest, ದ್ವಿಗುಣ cangle, ದ್ವಿಗುಣ sangle, ಸ್ಥಿರಾಂಕ SDL_FPoint *center)
{
    SDL_Surface *rz_dst;
    ಪೂರ್ಣಾಂಕ is8bit, angle90;
    SDL_Blend_ಬಹುಲಕ blendmode;
    Uint32 colorkey = 0;
    bool color_ಕೀಲಿ_ಲಭ್ಯ = false;
    ದ್ವಿಗುಣ sangleinv, cangleinv;

    // Sanity check
    ಆದರೆ (!SDL_SurfaceValid(src)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (SDL_Surface_Has_Color_ಕೀಲಿ(src)) {
        ಆದರೆ (SDL_Get_Surface_Color_ಕೀಲಿ(src, &colorkey)) {
            color_ಕೀಲಿ_ಲಭ್ಯ = true;
        }
    }
    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    is8bit = (src->format == SDL_PIXELFORMAT_INDEX8) && color_ಕೀಲಿ_ಲಭ್ಯ;
    ಆದರೆ (!is8bit &&
        !(SDL_BITSPERPIXEL(src->format) == 32 && SDL_PIXELLAYOUT(src->format) == SDL_PACKEDLAYOUT_8888)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Calculate target factors from sine/cosine and zoom
    sangleinv = sangle * 65536.0;
    cangleinv = cangle * 65536.0;

    // Alloc space to completely contain the rotated surface
    rz_dst = ಖಾಲಿ;
    ಆದರೆ (is8bit) {
        // Target surface is 8 bit
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_ಅಡ್ಡಸಾಲುಗಳು, src->format);
        ಆದರೆ (rz_dst) {
            SDL_ಗಣ_Surface_Palette(rz_dst, src->palette);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Target surface is 32 bit with source RGBA ordering
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_ಅಡ್ಡಸಾಲುಗಳು, src->format);
    }

    // Check target
    ಆದರೆ (!rz_dst) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Adjust for guard rows
    rz_dst->h = rect_dest->h;

    SDL_Get_Surface_Blend_ಬಹುಲಕ(src, &blendmode);

    ಆದರೆ (color_ಕೀಲಿ_ಲಭ್ಯ) {
        // If available, the colorkey will be used to discard the pixels that are outside of the rotated area.
        SDL_ಗಣ_Surface_Color_ಕೀಲಿ(rz_dst, true, colorkey);
        SDL_FillSurfaceRect(rz_dst, ಖಾಲಿ, colorkey);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (blendmode == SDL_BLENDMODE_NONE) {
        blendmode = SDL_BLENDMODE_BLEND;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (blendmode == SDL_BLENDMODE_MOD || blendmode == SDL_BLENDMODE_MUL) {
        /* Without a colorkey, the target texture has to be white for the MOD and MUL blend mode so
         * that the pixels outside the rotated area don't affect the destination surface.
         */
        colorkey = SDL_MapSurfaceRGBA(rz_dst, 255, 255, 255, 0);
        SDL_FillSurfaceRect(rz_dst, ಖಾಲಿ, colorkey);
        /* Setting a white colorkey for the destination surface makes the final blit discard
         * all pixels outside of the rotated area. This doesn't interfere with anything because
         * white pixels are already a no-op and the MOD blend mode does not interact with alpha.
         */
        SDL_ಗಣ_Surface_Color_ಕೀಲಿ(rz_dst, true, colorkey);
    }

    SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(rz_dst, blendmode);

    // Lock source surface
    ಆದರೆ (SDL_MUSTLOCK(src)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(src)) {
            SDL_DestroySurface(rz_dst);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    /* check if the rotation is a multiple of 90 degrees so we can take a fast path and also somewhat reduce
     * the off-by-one problem in transformSurfaceRGBA that expresses itself when the rotation is near
     * multiples of 90 degrees.
     */
    angle90 = (ಪೂರ್ಣಾಂಕ)(angle / 90);
    ಆದರೆ (angle90 == angle / 90) {
        angle90 %= 4;
        ಆದರೆ (angle90 < 0) {
            angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
        }

    } ಇಲ್ಲದಿದ್ದರೆ {
        angle90 = -1;
    }

    ಆದರೆ (is8bit) {
        // Call the 8-bit transformation routine to do the rotation
        ಆದರೆ (angle90 >= 0) {
            transformSurfaceY90(src, rz_dst, angle90, flipx, flipy);
        } ಇಲ್ಲದಿದ್ದರೆ {
            transformSurfaceY(src, rz_dst, (ಪೂರ್ಣಾಂಕ)sangleinv, (ಪೂರ್ಣಾಂಕ)cangleinv,
                              flipx, flipy, rect_dest, center);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Call the 32-bit transformation routine to do the rotation
        ಆದರೆ (angle90 >= 0) {
            transformSurfaceRGBA90(src, rz_dst, angle90, flipx, flipy);
        } ಇಲ್ಲದಿದ್ದರೆ {
            transformSurfaceRGBA(src, rz_dst, (ಪೂರ್ಣಾಂಕ)sangleinv, (ಪೂರ್ಣಾಂಕ)cangleinv,
                                 flipx, flipy, smooth, rect_dest, center);
        }
    }

    // Unlock source surface
    ಆದರೆ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }

    // Return rotated surface
    ಹಿಂತಿರುಗಿ rz_dst;
}


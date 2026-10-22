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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_rotate.h"

// ---- Internally used structures

/**
A 32 bit RGBA pixel.
*/
రకనిర్వచనం నిర్మాణం tColorRGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} tColorRGBA;

/**
A 8bit Y/palette pixel.
*/
రకనిర్వచనం నిర్మాణం tColorY
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
#నిర్వచించు GUARD_అడ్డువరుసలు (2)

/**
Returns colorkey info for a surface
*/
స్థిర Uint32 get_colorkey(SDL_Surface *src)
{
    Uint32 కీలకం = 0;
    ఒకవేళ (SDL_Surface_Has_Color_కీలకం(src)) {
        SDL_Get_Surface_Color_కీలకం(src, &కీలకం);
    }
    తిరిగి కీలకం;
}

// rotate (sx, sy) by (angle, center) into (dx, dy)
స్థిర శూన్య rotate(ద్విగుణ sx, ద్విగుణ sy, ద్విగుణ sinangle, ద్విగుణ cosangle, స్థిరరాశి SDL_FPoint *center, ద్విగుణ *dx, ద్విగుణ *dy)
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
శూన్య SDLgfx_rotozoom_Surface_కొలత_Trig(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, ద్విగుణ angle, స్థిరరాశి SDL_FPoint *center,
                                    SDL_Rect *rect_dest, ద్విగుణ *cangle, ద్విగుణ *sangle)
{
    పూర్ణాంకం minx, maxx, miny, maxy;
    ద్విగుణ radangle;
    ద్విగుణ x0, x1, x2, x3;
    ద్విగుణ y0, y1, y2, y3;
    ద్విగుణ sinangle;
    ద్విగుణ cosangle;

    radangle = angle * (SDL_PI_D / 180.0);
    sinangle = SDL_sin(radangle);
    cosangle = SDL_cos(radangle);

    /*
     * Determine destination width and height by rotating a source box, at pixel center
     */
    rotate(0.5, 0.5, sinangle, cosangle, center, &x0, &y0);
    rotate(వెడల్పు - 0.5, 0.5, sinangle, cosangle, center, &x1, &y1);
    rotate(0.5, ఎత్తు - 0.5, sinangle, cosangle, center, &x2, &y2);
    rotate(వెడల్పు - 0.5, ఎత్తు - 0.5, sinangle, cosangle, center, &x3, &y3);

    minx = (పూర్ణాంకం)SDL_floor(SDL_min(SDL_min(x0, x1), SDL_min(x2, x3)));
    maxx = (పూర్ణాంకం)SDL_ceil(SDL_max(SDL_max(x0, x1), SDL_max(x2, x3)));

    miny = (పూర్ణాంకం)SDL_floor(SDL_min(SDL_min(y0, y1), SDL_min(y2, y3)));
    maxy = (పూర్ణాంకం)SDL_ceil(SDL_max(SDL_max(y0, y1), SDL_max(y2, y3)));

    rect_dest->w = maxx - minx;
    rect_dest->h = maxy - miny;
    rect_dest->x = minx;
    rect_dest->y = miny;

    // reverse the angle because our rotations are clockwise
    *sangle = -sinangle;
    *cangle = cosangle;

    {
        // The trig code below gets the wrong size (due to FP inaccuracy?) when angle is a multiple of 90 degrees
        పూర్ణాంకం angle90 = (పూర్ణాంకం)(angle / 90);
        ఒకవేళ (angle90 == angle / 90) { // if the angle is a multiple of 90 degrees
            angle90 %= 4;
            ఒకవేళ (angle90 < 0) {
                angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
            }

            ఒకవేళ (angle90 & 1) {
                rect_dest->w = ఎత్తు;
                rect_dest->h = వెడల్పు;
                *cangle = 0;
                *sangle = angle90 == 1 ? -1 : 1; // reversed because our rotations are clockwise
            } లేకపోతే {
                rect_dest->w = వెడల్పు;
                rect_dest->h = ఎత్తు;
                *cangle = angle90 == 0 ? 1 : -1;
                *sangle = 0;
            }
        }
    }
}

// Computes source pointer X/Y increments for a rotation that's a multiple of 90 degrees.
స్థిర శూన్య compute_ఆధారం_Increments90(SDL_Surface *src, పూర్ణాంకం bpp, పూర్ణాంకం angle, పూర్ణాంకం flipx, పూర్ణాంకం flipy,
                                      పూర్ణాంకం *sincx, పూర్ణాంకం *sincy, పూర్ణాంకం *signx, పూర్ణాంకం *signy)
{
    పూర్ణాంకం pitch = flipy ? -src->pitch : src->pitch;
    ఒకవేళ (flipx) {
        bpp = -bpp;
    }
    ఎంపిక (angle) { // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
    స్థితి 0:
        *sincx = bpp;
        *sincy = pitch - src->w * *sincx;
        *signx = *signy = 1;
        ఆపు;
    స్థితి 1:
        *sincx = -pitch;
        *sincy = bpp - *sincx * src->h;
        *signx = 1;
        *signy = -1;
        ఆపు;
    స్థితి 2:
        *sincx = -bpp;
        *sincy = -src->w * *sincx - pitch;
        *signx = *signy = -1;
        ఆపు;
    స్థితి 3:
    అప్రమేయ:
        *sincx = pitch;
        *sincy = -*sincx * src->h - bpp;
        *signx = -1;
        *signy = 1;
        ఆపు;
    }
    ఒకవేళ (flipx) {
        *signx = -*signx;
    }
    ఒకవేళ (flipy) {
        *signy = -*signy;
    }
}

// Performs a relatively fast rotation/flip when the angle is a multiple of 90 degrees.
#నిర్వచించు TRANSFORM_SURFACE_90(pixelType)                                                                     \
    పూర్ణాంకం dy, dincy = dst->pitch - dst->w * పరిమాణం(pixelType), sincx, sincy, signx, signy;                    \
    Uint8 *sp = (Uint8 *)src->pixels, *dp = (Uint8 *)dst->pixels, *de;                                      \
                                                                                                            \
    compute_ఆధారం_Increments90(src, పరిమాణం(pixelType), angle, flipx, flipy, &sincx, &sincy, &signx, &signy); \
    ఒకవేళ (signx < 0)                                                                                          \
        sp += (src->w - 1) * పరిమాణం(pixelType);                                                             \
    ఒకవేళ (signy < 0)                                                                                          \
        sp += (src->h - 1) * src->pitch;                                                                    \
                                                                                                            \
    కొరకు (dy = 0; dy < dst->h; sp += sincy, dp += dincy, dy++) {                                             \
        ఒకవేళ (sincx == పరిమాణం(pixelType)) { /* if advancing src and dest equally, use SDL_memcpy */           \
            SDL_memcpy(dp, sp, dst->w * పరిమాణం(pixelType));                                                 \
            sp += dst->w * పరిమాణం(pixelType);                                                               \
            dp += dst->w * పరిమాణం(pixelType);                                                               \
        } లేకపోతే {                                                                                            \
            కొరకు (de = dp + dst->w * పరిమాణం(pixelType); dp != de; sp += sincx, dp += పరిమాణం(pixelType)) {    \
                *(pixelType *)dp = *(pixelType *)sp;                                                        \
            }                                                                                               \
        }                                                                                                   \
    }

స్థిర శూన్య transformSurfaceRGBA90(SDL_Surface *src, SDL_Surface *dst, పూర్ణాంకం angle, పూర్ణాంకం flipx, పూర్ణాంకం flipy)
{
    TRANSFORM_SURFACE_90(tColorRGBA);
}

స్థిర శూన్య transformSurfaceY90(SDL_Surface *src, SDL_Surface *dst, పూర్ణాంకం angle, పూర్ణాంకం flipx, పూర్ణాంకం flipy)
{
    TRANSFORM_SURFACE_90(tColorY);
}

#నిర్వచనం_రద్దు TRANSFORM_SURFACE_90

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
స్థిర శూన్య transformSurfaceRGBA(SDL_Surface *src, SDL_Surface *dst, పూర్ణాంకం isin, పూర్ణాంకం icos,
                                 పూర్ణాంకం flipx, పూర్ణాంకం flipy, పూర్ణాంకం smooth,
                                 స్థిరరాశి SDL_Rect *rect_dest,
                                 స్థిరరాశి SDL_FPoint *center)
{
    పూర్ణాంకం sw, sh;
    పూర్ణాంకం cx, cy;
    tColorRGBA c00, c01, c10, c11, cswap;
    tColorRGBA *pc, *sp;
    పూర్ణాంకం gap;
    స్థిరరాశి పూర్ణాంకం fp_half = (1 << 15);

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorRGBA *)dst->pixels;
    gap = dst->pitch - dst->w * 4;
    cx = (పూర్ణాంకం)(center->x * 65536.0);
    cy = (పూర్ణాంకం)(center->y * 65536.0);

    /*
     * Switch between interpolating and non-interpolating code
     */
    ఒకవేళ (smooth) {
        పూర్ణాంకం y;
        కొరకు (y = 0; y < dst->h; y++) {
            పూర్ణాంకం x;
            ద్విగుణ src_x = ((ద్విగుణ)rect_dest->x + 0 + 0.5 - center->x);
            ద్విగుణ src_y = ((ద్విగుణ)rect_dest->y + y + 0.5 - center->y);
            పూర్ణాంకం sdx = (పూర్ణాంకం)((icos * src_x - isin * src_y) + cx - fp_half);
            పూర్ణాంకం sdy = (పూర్ణాంకం)((isin * src_x + icos * src_y) + cy - fp_half);
            కొరకు (x = 0; x < dst->w; x++) {
                పూర్ణాంకం dx = (sdx >> 16);
                పూర్ణాంకం dy = (sdy >> 16);
                ఒకవేళ (flipx) {
                    dx = sw - dx;
                }
                ఒకవేళ (flipy) {
                    dy = sh - dy;
                }
                ఒకవేళ ((dx > -1) && (dy > -1) && (dx < (src->w - 1)) && (dy < (src->h - 1))) {
                    పూర్ణాంకం ex, ey;
                    పూర్ణాంకం t1, t2;
                    sp = (tColorRGBA *)((Uint8 *)src->pixels + src->pitch * dy) + dx;
                    c00 = *sp;
                    sp += 1;
                    c01 = *sp;
                    sp += (src->pitch / 4);
                    c11 = *sp;
                    sp -= 1;
                    c10 = *sp;
                    ఒకవేళ (flipx) {
                        cswap = c00;
                        c00 = c01;
                        c01 = cswap;
                        cswap = c10;
                        c10 = c11;
                        c11 = cswap;
                    }
                    ఒకవేళ (flipy) {
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
    } లేకపోతే {
        పూర్ణాంకం y;
        కొరకు (y = 0; y < dst->h; y++) {
            పూర్ణాంకం x;
            ద్విగుణ src_x = ((ద్విగుణ)rect_dest->x + 0 + 0.5 - center->x);
            ద్విగుణ src_y = ((ద్విగుణ)rect_dest->y + y + 0.5 - center->y);
            పూర్ణాంకం sdx = (పూర్ణాంకం)((icos * src_x - isin * src_y) + cx - fp_half);
            పూర్ణాంకం sdy = (పూర్ణాంకం)((isin * src_x + icos * src_y) + cy - fp_half);
            కొరకు (x = 0; x < dst->w; x++) {
                పూర్ణాంకం dx = (sdx >> 16);
                పూర్ణాంకం dy = (sdy >> 16);
                ఒకవేళ ((గుర్తులేని)dx < (గుర్తులేని)src->w && (గుర్తులేని)dy < (గుర్తులేని)src->h) {
                    ఒకవేళ (flipx) {
                        dx = sw - dx;
                    }
                    ఒకవేళ (flipy) {
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
స్థిర శూన్య transformSurfaceY(SDL_Surface *src, SDL_Surface *dst, పూర్ణాంకం isin, పూర్ణాంకం icos, పూర్ణాంకం flipx, పూర్ణాంకం flipy,
                              స్థిరరాశి SDL_Rect *rect_dest,
                              స్థిరరాశి SDL_FPoint *center)
{
    పూర్ణాంకం sw, sh;
    పూర్ణాంకం cx, cy;
    tColorY *pc;
    పూర్ణాంకం gap;
    స్థిరరాశి పూర్ణాంకం fp_half = (1 << 15);
    పూర్ణాంకం y;

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorY *)dst->pixels;
    gap = dst->pitch - dst->w;
    cx = (పూర్ణాంకం)(center->x * 65536.0);
    cy = (పూర్ణాంకం)(center->y * 65536.0);

    /*
     * Clear surface to colorkey
     */
    SDL_memset(pc, (పూర్ణాంకం)(get_colorkey(src) & 0xff), (size_t)dst->pitch * dst->h);
    /*
     * Iterate through destination surface
     */
    కొరకు (y = 0; y < dst->h; y++) {
        పూర్ణాంకం x;
        ద్విగుణ src_x = ((ద్విగుణ)rect_dest->x + 0 + 0.5 - center->x);
        ద్విగుణ src_y = ((ద్విగుణ)rect_dest->y + y + 0.5 - center->y);
        పూర్ణాంకం sdx = (పూర్ణాంకం)((icos * src_x - isin * src_y) + cx - fp_half);
        పూర్ణాంకం sdy = (పూర్ణాంకం)((isin * src_x + icos * src_y) + cy - fp_half);
        కొరకు (x = 0; x < dst->w; x++) {
            పూర్ణాంకం dx = (sdx >> 16);
            పూర్ణాంకం dy = (sdy >> 16);
            ఒకవేళ ((గుర్తులేని)dx < (గుర్తులేని)src->w && (గుర్తులేని)dy < (గుర్తులేని)src->h) {
                ఒకవేళ (flipx) {
                    dx = sw - dx;
                }
                ఒకవేళ (flipy) {
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

SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, ద్విగుణ angle, పూర్ణాంకం smooth, పూర్ణాంకం flipx, పూర్ణాంకం flipy,
                     స్థిరరాశి SDL_Rect *rect_dest, ద్విగుణ cangle, ద్విగుణ sangle, స్థిరరాశి SDL_FPoint *center)
{
    SDL_Surface *rz_dst;
    పూర్ణాంకం is8bit, angle90;
    SDL_Blend_బహుళకం blendmode;
    Uint32 colorkey = 0;
    bool color_కీలకం_అందుబాటు = false;
    ద్విగుణ sangleinv, cangleinv;

    // Sanity check
    ఒకవేళ (!SDL_SurfaceValid(src)) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (SDL_Surface_Has_Color_కీలకం(src)) {
        ఒకవేళ (SDL_Get_Surface_Color_కీలకం(src, &colorkey)) {
            color_కీలకం_అందుబాటు = true;
        }
    }
    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    is8bit = (src->format == SDL_PIXELFORMAT_INDEX8) && color_కీలకం_అందుబాటు;
    ఒకవేళ (!is8bit &&
        !(SDL_BITSPERPIXEL(src->format) == 32 && SDL_PIXELLAYOUT(src->format) == SDL_PACKEDLAYOUT_8888)) {
        తిరిగి ఖాళీ;
    }

    // Calculate target factors from sine/cosine and zoom
    sangleinv = sangle * 65536.0;
    cangleinv = cangle * 65536.0;

    // Alloc space to completely contain the rotated surface
    rz_dst = ఖాళీ;
    ఒకవేళ (is8bit) {
        // Target surface is 8 bit
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_అడ్డువరుసలు, src->format);
        ఒకవేళ (rz_dst) {
            SDL_సమితి_Surface_Palette(rz_dst, src->palette);
        }
    } లేకపోతే {
        // Target surface is 32 bit with source RGBA ordering
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_అడ్డువరుసలు, src->format);
    }

    // Check target
    ఒకవేళ (!rz_dst) {
        తిరిగి ఖాళీ;
    }

    // Adjust for guard rows
    rz_dst->h = rect_dest->h;

    SDL_Get_Surface_Blend_బహుళకం(src, &blendmode);

    ఒకవేళ (color_కీలకం_అందుబాటు) {
        // If available, the colorkey will be used to discard the pixels that are outside of the rotated area.
        SDL_సమితి_Surface_Color_కీలకం(rz_dst, true, colorkey);
        SDL_FillSurfaceRect(rz_dst, ఖాళీ, colorkey);
    } లేకపోతే ఒకవేళ (blendmode == SDL_BLENDMODE_NONE) {
        blendmode = SDL_BLENDMODE_BLEND;
    } లేకపోతే ఒకవేళ (blendmode == SDL_BLENDMODE_MOD || blendmode == SDL_BLENDMODE_MUL) {
        /* Without a colorkey, the target texture has to be white for the MOD and MUL blend mode so
         * that the pixels outside the rotated area don't affect the destination surface.
         */
        colorkey = SDL_MapSurfaceRGBA(rz_dst, 255, 255, 255, 0);
        SDL_FillSurfaceRect(rz_dst, ఖాళీ, colorkey);
        /* Setting a white colorkey for the destination surface makes the final blit discard
         * all pixels outside of the rotated area. This doesn't interfere with anything because
         * white pixels are already a no-op and the MOD blend mode does not interact with alpha.
         */
        SDL_సమితి_Surface_Color_కీలకం(rz_dst, true, colorkey);
    }

    SDL_సమితి_Surface_Blend_బహుళకం(rz_dst, blendmode);

    // Lock source surface
    ఒకవేళ (SDL_MUSTLOCK(src)) {
        ఒకవేళ (!SDL_తాళం_Surface(src)) {
            SDL_DestroySurface(rz_dst);
            తిరిగి ఖాళీ;
        }
    }

    /* check if the rotation is a multiple of 90 degrees so we can take a fast path and also somewhat reduce
     * the off-by-one problem in transformSurfaceRGBA that expresses itself when the rotation is near
     * multiples of 90 degrees.
     */
    angle90 = (పూర్ణాంకం)(angle / 90);
    ఒకవేళ (angle90 == angle / 90) {
        angle90 %= 4;
        ఒకవేళ (angle90 < 0) {
            angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
        }

    } లేకపోతే {
        angle90 = -1;
    }

    ఒకవేళ (is8bit) {
        // Call the 8-bit transformation routine to do the rotation
        ఒకవేళ (angle90 >= 0) {
            transformSurfaceY90(src, rz_dst, angle90, flipx, flipy);
        } లేకపోతే {
            transformSurfaceY(src, rz_dst, (పూర్ణాంకం)sangleinv, (పూర్ణాంకం)cangleinv,
                              flipx, flipy, rect_dest, center);
        }
    } లేకపోతే {
        // Call the 32-bit transformation routine to do the rotation
        ఒకవేళ (angle90 >= 0) {
            transformSurfaceRGBA90(src, rz_dst, angle90, flipx, flipy);
        } లేకపోతే {
            transformSurfaceRGBA(src, rz_dst, (పూర్ణాంకం)sangleinv, (పూర్ణాంకం)cangleinv,
                                 flipx, flipy, smooth, rect_dest, center);
        }
    }

    // Unlock source surface
    ఒకవేళ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }

    // Return rotated surface
    తిరిగి rz_dst;
}


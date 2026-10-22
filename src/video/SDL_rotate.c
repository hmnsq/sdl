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
#شامل "SDL_internal.h"

#شامل "SDL_surface_c.h"
#شامل "SDL_rotate.h"

// ---- Internally used structures

/**
A 32 bit RGBA pixel.
*/
قسمتعریف ساخت tColorRGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} tColorRGBA;

/**
A 8bit Y/palette pixel.
*/
قسمتعریف ساخت tColorY
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
#تعریف_کرو GUARD_صفیں (2)

/**
Returns colorkey info for a surface
*/
ساکن Uint32 get_colorkey(SDL_Surface *src)
{
    Uint32 کلید = 0;
    اگر (SDL_Surface_Has_Color_کلید(src)) {
        SDL_Get_Surface_Color_کلید(src, &کلید);
    }
    واپس کلید;
}

// rotate (sx, sy) by (angle, center) into (dx, dy)
ساکن خالی rotate(دوہرا sx, دوہرا sy, دوہرا sinangle, دوہرا cosangle, ثابت SDL_FPoint *center, دوہرا *dx, دوہرا *dy)
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
خالی SDLgfx_rotozoom_Surface_سائز_Trig(صحیح چوڑائی, صحیح اونچائی, دوہرا angle, ثابت SDL_FPoint *center,
                                    SDL_Rect *rect_dest, دوہرا *cangle, دوہرا *sangle)
{
    صحیح minx, maxx, miny, maxy;
    دوہرا radangle;
    دوہرا x0, x1, x2, x3;
    دوہرا y0, y1, y2, y3;
    دوہرا sinangle;
    دوہرا cosangle;

    radangle = angle * (SDL_PI_D / 180.0);
    sinangle = SDL_sin(radangle);
    cosangle = SDL_cos(radangle);

    /*
     * Determine destination width and height by rotating a source box, at pixel center
     */
    rotate(0.5, 0.5, sinangle, cosangle, center, &x0, &y0);
    rotate(چوڑائی - 0.5, 0.5, sinangle, cosangle, center, &x1, &y1);
    rotate(0.5, اونچائی - 0.5, sinangle, cosangle, center, &x2, &y2);
    rotate(چوڑائی - 0.5, اونچائی - 0.5, sinangle, cosangle, center, &x3, &y3);

    minx = (صحیح)SDL_floor(SDL_min(SDL_min(x0, x1), SDL_min(x2, x3)));
    maxx = (صحیح)SDL_ceil(SDL_max(SDL_max(x0, x1), SDL_max(x2, x3)));

    miny = (صحیح)SDL_floor(SDL_min(SDL_min(y0, y1), SDL_min(y2, y3)));
    maxy = (صحیح)SDL_ceil(SDL_max(SDL_max(y0, y1), SDL_max(y2, y3)));

    rect_dest->w = maxx - minx;
    rect_dest->h = maxy - miny;
    rect_dest->x = minx;
    rect_dest->y = miny;

    // reverse the angle because our rotations are clockwise
    *sangle = -sinangle;
    *cangle = cosangle;

    {
        // The trig code below gets the wrong size (due to FP inaccuracy?) when angle is a multiple of 90 degrees
        صحیح angle90 = (صحیح)(angle / 90);
        اگر (angle90 == angle / 90) { // if the angle is a multiple of 90 degrees
            angle90 %= 4;
            اگر (angle90 < 0) {
                angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
            }

            اگر (angle90 & 1) {
                rect_dest->w = اونچائی;
                rect_dest->h = چوڑائی;
                *cangle = 0;
                *sangle = angle90 == 1 ? -1 : 1; // reversed because our rotations are clockwise
            } ورنہ {
                rect_dest->w = چوڑائی;
                rect_dest->h = اونچائی;
                *cangle = angle90 == 0 ? 1 : -1;
                *sangle = 0;
            }
        }
    }
}

// Computes source pointer X/Y increments for a rotation that's a multiple of 90 degrees.
ساکن خالی compute_ماخذ_Increments90(SDL_Surface *src, صحیح bpp, صحیح angle, صحیح flipx, صحیح flipy,
                                      صحیح *sincx, صحیح *sincy, صحیح *signx, صحیح *signy)
{
    صحیح pitch = flipy ? -src->pitch : src->pitch;
    اگر (flipx) {
        bpp = -bpp;
    }
    انتخاب (angle) { // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
    حالت 0:
        *sincx = bpp;
        *sincy = pitch - src->w * *sincx;
        *signx = *signy = 1;
        توڑو;
    حالت 1:
        *sincx = -pitch;
        *sincy = bpp - *sincx * src->h;
        *signx = 1;
        *signy = -1;
        توڑو;
    حالت 2:
        *sincx = -bpp;
        *sincy = -src->w * *sincx - pitch;
        *signx = *signy = -1;
        توڑو;
    حالت 3:
    طےشدہ:
        *sincx = pitch;
        *sincy = -*sincx * src->h - bpp;
        *signx = -1;
        *signy = 1;
        توڑو;
    }
    اگر (flipx) {
        *signx = -*signx;
    }
    اگر (flipy) {
        *signy = -*signy;
    }
}

// Performs a relatively fast rotation/flip when the angle is a multiple of 90 degrees.
#تعریف_کرو TRANSFORM_SURFACE_90(pixelType)                                                                     \
    صحیح dy, dincy = dst->pitch - dst->w * حجم(pixelType), sincx, sincy, signx, signy;                    \
    Uint8 *sp = (Uint8 *)src->pixels, *dp = (Uint8 *)dst->pixels, *de;                                      \
                                                                                                            \
    compute_ماخذ_Increments90(src, حجم(pixelType), angle, flipx, flipy, &sincx, &sincy, &signx, &signy); \
    اگر (signx < 0)                                                                                          \
        sp += (src->w - 1) * حجم(pixelType);                                                             \
    اگر (signy < 0)                                                                                          \
        sp += (src->h - 1) * src->pitch;                                                                    \
                                                                                                            \
    برائے (dy = 0; dy < dst->h; sp += sincy, dp += dincy, dy++) {                                             \
        اگر (sincx == حجم(pixelType)) { /* if advancing src and dest equally, use SDL_memcpy */           \
            SDL_memcpy(dp, sp, dst->w * حجم(pixelType));                                                 \
            sp += dst->w * حجم(pixelType);                                                               \
            dp += dst->w * حجم(pixelType);                                                               \
        } ورنہ {                                                                                            \
            برائے (de = dp + dst->w * حجم(pixelType); dp != de; sp += sincx, dp += حجم(pixelType)) {    \
                *(pixelType *)dp = *(pixelType *)sp;                                                        \
            }                                                                                               \
        }                                                                                                   \
    }

ساکن خالی transformSurfaceRGBA90(SDL_Surface *src, SDL_Surface *dst, صحیح angle, صحیح flipx, صحیح flipy)
{
    TRANSFORM_SURFACE_90(tColorRGBA);
}

ساکن خالی transformSurfaceY90(SDL_Surface *src, SDL_Surface *dst, صحیح angle, صحیح flipx, صحیح flipy)
{
    TRANSFORM_SURFACE_90(tColorY);
}

#تعریف_منسوخ TRANSFORM_SURFACE_90

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
ساکن خالی transformSurfaceRGBA(SDL_Surface *src, SDL_Surface *dst, صحیح isin, صحیح icos,
                                 صحیح flipx, صحیح flipy, صحیح smooth,
                                 ثابت SDL_Rect *rect_dest,
                                 ثابت SDL_FPoint *center)
{
    صحیح sw, sh;
    صحیح cx, cy;
    tColorRGBA c00, c01, c10, c11, cswap;
    tColorRGBA *pc, *sp;
    صحیح gap;
    ثابت صحیح fp_half = (1 << 15);

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorRGBA *)dst->pixels;
    gap = dst->pitch - dst->w * 4;
    cx = (صحیح)(center->x * 65536.0);
    cy = (صحیح)(center->y * 65536.0);

    /*
     * Switch between interpolating and non-interpolating code
     */
    اگر (smooth) {
        صحیح y;
        برائے (y = 0; y < dst->h; y++) {
            صحیح x;
            دوہرا src_x = ((دوہرا)rect_dest->x + 0 + 0.5 - center->x);
            دوہرا src_y = ((دوہرا)rect_dest->y + y + 0.5 - center->y);
            صحیح sdx = (صحیح)((icos * src_x - isin * src_y) + cx - fp_half);
            صحیح sdy = (صحیح)((isin * src_x + icos * src_y) + cy - fp_half);
            برائے (x = 0; x < dst->w; x++) {
                صحیح dx = (sdx >> 16);
                صحیح dy = (sdy >> 16);
                اگر (flipx) {
                    dx = sw - dx;
                }
                اگر (flipy) {
                    dy = sh - dy;
                }
                اگر ((dx > -1) && (dy > -1) && (dx < (src->w - 1)) && (dy < (src->h - 1))) {
                    صحیح ex, ey;
                    صحیح t1, t2;
                    sp = (tColorRGBA *)((Uint8 *)src->pixels + src->pitch * dy) + dx;
                    c00 = *sp;
                    sp += 1;
                    c01 = *sp;
                    sp += (src->pitch / 4);
                    c11 = *sp;
                    sp -= 1;
                    c10 = *sp;
                    اگر (flipx) {
                        cswap = c00;
                        c00 = c01;
                        c01 = cswap;
                        cswap = c10;
                        c10 = c11;
                        c11 = cswap;
                    }
                    اگر (flipy) {
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
    } ورنہ {
        صحیح y;
        برائے (y = 0; y < dst->h; y++) {
            صحیح x;
            دوہرا src_x = ((دوہرا)rect_dest->x + 0 + 0.5 - center->x);
            دوہرا src_y = ((دوہرا)rect_dest->y + y + 0.5 - center->y);
            صحیح sdx = (صحیح)((icos * src_x - isin * src_y) + cx - fp_half);
            صحیح sdy = (صحیح)((isin * src_x + icos * src_y) + cy - fp_half);
            برائے (x = 0; x < dst->w; x++) {
                صحیح dx = (sdx >> 16);
                صحیح dy = (sdy >> 16);
                اگر ((غیرعلامتی)dx < (غیرعلامتی)src->w && (غیرعلامتی)dy < (غیرعلامتی)src->h) {
                    اگر (flipx) {
                        dx = sw - dx;
                    }
                    اگر (flipy) {
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
ساکن خالی transformSurfaceY(SDL_Surface *src, SDL_Surface *dst, صحیح isin, صحیح icos, صحیح flipx, صحیح flipy,
                              ثابت SDL_Rect *rect_dest,
                              ثابت SDL_FPoint *center)
{
    صحیح sw, sh;
    صحیح cx, cy;
    tColorY *pc;
    صحیح gap;
    ثابت صحیح fp_half = (1 << 15);
    صحیح y;

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorY *)dst->pixels;
    gap = dst->pitch - dst->w;
    cx = (صحیح)(center->x * 65536.0);
    cy = (صحیح)(center->y * 65536.0);

    /*
     * Clear surface to colorkey
     */
    SDL_memset(pc, (صحیح)(get_colorkey(src) & 0xff), (size_t)dst->pitch * dst->h);
    /*
     * Iterate through destination surface
     */
    برائے (y = 0; y < dst->h; y++) {
        صحیح x;
        دوہرا src_x = ((دوہرا)rect_dest->x + 0 + 0.5 - center->x);
        دوہرا src_y = ((دوہرا)rect_dest->y + y + 0.5 - center->y);
        صحیح sdx = (صحیح)((icos * src_x - isin * src_y) + cx - fp_half);
        صحیح sdy = (صحیح)((isin * src_x + icos * src_y) + cy - fp_half);
        برائے (x = 0; x < dst->w; x++) {
            صحیح dx = (sdx >> 16);
            صحیح dy = (sdy >> 16);
            اگر ((غیرعلامتی)dx < (غیرعلامتی)src->w && (غیرعلامتی)dy < (غیرعلامتی)src->h) {
                اگر (flipx) {
                    dx = sw - dx;
                }
                اگر (flipy) {
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

SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, دوہرا angle, صحیح smooth, صحیح flipx, صحیح flipy,
                     ثابت SDL_Rect *rect_dest, دوہرا cangle, دوہرا sangle, ثابت SDL_FPoint *center)
{
    SDL_Surface *rz_dst;
    صحیح is8bit, angle90;
    SDL_Blend_منوال blendmode;
    Uint32 colorkey = 0;
    bool color_کلید_دستیاب = false;
    دوہرا sangleinv, cangleinv;

    // Sanity check
    اگر (!SDL_SurfaceValid(src)) {
        واپس تہی;
    }

    اگر (SDL_Surface_Has_Color_کلید(src)) {
        اگر (SDL_Get_Surface_Color_کلید(src, &colorkey)) {
            color_کلید_دستیاب = true;
        }
    }
    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    is8bit = (src->format == SDL_PIXELFORMAT_INDEX8) && color_کلید_دستیاب;
    اگر (!is8bit &&
        !(SDL_BITSPERPIXEL(src->format) == 32 && SDL_PIXELLAYOUT(src->format) == SDL_PACKEDLAYOUT_8888)) {
        واپس تہی;
    }

    // Calculate target factors from sine/cosine and zoom
    sangleinv = sangle * 65536.0;
    cangleinv = cangle * 65536.0;

    // Alloc space to completely contain the rotated surface
    rz_dst = تہی;
    اگر (is8bit) {
        // Target surface is 8 bit
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_صفیں, src->format);
        اگر (rz_dst) {
            SDL_سیٹ_Surface_Palette(rz_dst, src->palette);
        }
    } ورنہ {
        // Target surface is 32 bit with source RGBA ordering
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_صفیں, src->format);
    }

    // Check target
    اگر (!rz_dst) {
        واپس تہی;
    }

    // Adjust for guard rows
    rz_dst->h = rect_dest->h;

    SDL_Get_Surface_Blend_منوال(src, &blendmode);

    اگر (color_کلید_دستیاب) {
        // If available, the colorkey will be used to discard the pixels that are outside of the rotated area.
        SDL_سیٹ_Surface_Color_کلید(rz_dst, true, colorkey);
        SDL_FillSurfaceRect(rz_dst, تہی, colorkey);
    } ورنہ اگر (blendmode == SDL_BLENDMODE_NONE) {
        blendmode = SDL_BLENDMODE_BLEND;
    } ورنہ اگر (blendmode == SDL_BLENDMODE_MOD || blendmode == SDL_BLENDMODE_MUL) {
        /* Without a colorkey, the target texture has to be white for the MOD and MUL blend mode so
         * that the pixels outside the rotated area don't affect the destination surface.
         */
        colorkey = SDL_MapSurfaceRGBA(rz_dst, 255, 255, 255, 0);
        SDL_FillSurfaceRect(rz_dst, تہی, colorkey);
        /* Setting a white colorkey for the destination surface makes the final blit discard
         * all pixels outside of the rotated area. This doesn't interfere with anything because
         * white pixels are already a no-op and the MOD blend mode does not interact with alpha.
         */
        SDL_سیٹ_Surface_Color_کلید(rz_dst, true, colorkey);
    }

    SDL_سیٹ_Surface_Blend_منوال(rz_dst, blendmode);

    // Lock source surface
    اگر (SDL_MUSTLOCK(src)) {
        اگر (!SDL_تالا_Surface(src)) {
            SDL_DestroySurface(rz_dst);
            واپس تہی;
        }
    }

    /* check if the rotation is a multiple of 90 degrees so we can take a fast path and also somewhat reduce
     * the off-by-one problem in transformSurfaceRGBA that expresses itself when the rotation is near
     * multiples of 90 degrees.
     */
    angle90 = (صحیح)(angle / 90);
    اگر (angle90 == angle / 90) {
        angle90 %= 4;
        اگر (angle90 < 0) {
            angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
        }

    } ورنہ {
        angle90 = -1;
    }

    اگر (is8bit) {
        // Call the 8-bit transformation routine to do the rotation
        اگر (angle90 >= 0) {
            transformSurfaceY90(src, rz_dst, angle90, flipx, flipy);
        } ورنہ {
            transformSurfaceY(src, rz_dst, (صحیح)sangleinv, (صحیح)cangleinv,
                              flipx, flipy, rect_dest, center);
        }
    } ورنہ {
        // Call the 32-bit transformation routine to do the rotation
        اگر (angle90 >= 0) {
            transformSurfaceRGBA90(src, rz_dst, angle90, flipx, flipy);
        } ورنہ {
            transformSurfaceRGBA(src, rz_dst, (صحیح)sangleinv, (صحیح)cangleinv,
                                 flipx, flipy, smooth, rect_dest, center);
        }
    }

    // Unlock source surface
    اگر (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }

    // Return rotated surface
    واپس rz_dst;
}


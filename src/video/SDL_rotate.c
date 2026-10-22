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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_surface_c.h"
#അന്തര്ഭാവ "SDL_rotate.h"

// ---- Internally used structures

/**
A 32 bit RGBA pixel.
*/
തരനിർവചനം ഘടന tColorRGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} tColorRGBA;

/**
A 8bit Y/palette pixel.
*/
തരനിർവചനം ഘടന tColorY
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
#define GUARD_ROWS (2)

/**
Returns colorkey info for a surface
*/
സ്ഥിതം Uint32 get_colorkey(SDL_Surface *src)
{
    Uint32 താക്കോൽ = 0;
    എങ്കിൽ (SDL_Surface_Has_Color_താക്കോൽ(src)) {
        SDL_Get_Surface_Color_താക്കോൽ(src, &താക്കോൽ);
    }
    തിരികെ താക്കോൽ;
}

// rotate (sx, sy) by (angle, center) into (dx, dy)
സ്ഥിതം ശൂന്യം rotate(ഇരട്ട sx, ഇരട്ട sy, ഇരട്ട sinangle, ഇരട്ട cosangle, സ്ഥിരം SDL_FPoint *center, ഇരട്ട *dx, ഇരട്ട *dy)
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
ശൂന്യം SDLgfx_rotozoomSurfaceSizeTrig(പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, ഇരട്ട angle, സ്ഥിരം SDL_FPoint *center,
                                    SDL_Rect *rect_dest, ഇരട്ട *cangle, ഇരട്ട *sangle)
{
    പൂർണ്ണസംഖ്യ minx, maxx, miny, maxy;
    ഇരട്ട radangle;
    ഇരട്ട x0, x1, x2, x3;
    ഇരട്ട y0, y1, y2, y3;
    ഇരട്ട sinangle;
    ഇരട്ട cosangle;

    radangle = angle * (SDL_PI_D / 180.0);
    sinangle = SDL_sin(radangle);
    cosangle = SDL_cos(radangle);

    /*
     * Determine destination width and height by rotating a source box, at pixel center
     */
    rotate(0.5, 0.5, sinangle, cosangle, center, &x0, &y0);
    rotate(width - 0.5, 0.5, sinangle, cosangle, center, &x1, &y1);
    rotate(0.5, height - 0.5, sinangle, cosangle, center, &x2, &y2);
    rotate(width - 0.5, height - 0.5, sinangle, cosangle, center, &x3, &y3);

    minx = (പൂർണ്ണസംഖ്യ)SDL_floor(SDL_min(SDL_min(x0, x1), SDL_min(x2, x3)));
    maxx = (പൂർണ്ണസംഖ്യ)SDL_ceil(SDL_max(SDL_max(x0, x1), SDL_max(x2, x3)));

    miny = (പൂർണ്ണസംഖ്യ)SDL_floor(SDL_min(SDL_min(y0, y1), SDL_min(y2, y3)));
    maxy = (പൂർണ്ണസംഖ്യ)SDL_ceil(SDL_max(SDL_max(y0, y1), SDL_max(y2, y3)));

    rect_dest->w = maxx - minx;
    rect_dest->h = maxy - miny;
    rect_dest->x = minx;
    rect_dest->y = miny;

    // reverse the angle because our rotations are clockwise
    *sangle = -sinangle;
    *cangle = cosangle;

    {
        // The trig code below gets the wrong size (due to FP inaccuracy?) when angle is a multiple of 90 degrees
        പൂർണ്ണസംഖ്യ angle90 = (പൂർണ്ണസംഖ്യ)(angle / 90);
        എങ്കിൽ (angle90 == angle / 90) { // if the angle is a multiple of 90 degrees
            angle90 %= 4;
            എങ്കിൽ (angle90 < 0) {
                angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
            }

            എങ്കിൽ (angle90 & 1) {
                rect_dest->w = height;
                rect_dest->h = width;
                *cangle = 0;
                *sangle = angle90 == 1 ? -1 : 1; // reversed because our rotations are clockwise
            } അല്ലെങ്കിൽ {
                rect_dest->w = width;
                rect_dest->h = height;
                *cangle = angle90 == 0 ? 1 : -1;
                *sangle = 0;
            }
        }
    }
}

// Computes source pointer X/Y increments for a rotation that's a multiple of 90 degrees.
സ്ഥിതം ശൂന്യം computeSourceIncrements90(SDL_Surface *src, പൂർണ്ണസംഖ്യ bpp, പൂർണ്ണസംഖ്യ angle, പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy,
                                      പൂർണ്ണസംഖ്യ *sincx, പൂർണ്ണസംഖ്യ *sincy, പൂർണ്ണസംഖ്യ *signx, പൂർണ്ണസംഖ്യ *signy)
{
    പൂർണ്ണസംഖ്യ pitch = flipy ? -src->pitch : src->pitch;
    എങ്കിൽ (flipx) {
        bpp = -bpp;
    }
    തിരഞ്ഞെടുപ്പ് (angle) { // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
    അവസ്ഥ 0:
        *sincx = bpp;
        *sincy = pitch - src->w * *sincx;
        *signx = *signy = 1;
        നിർത്തുക;
    അവസ്ഥ 1:
        *sincx = -pitch;
        *sincy = bpp - *sincx * src->h;
        *signx = 1;
        *signy = -1;
        നിർത്തുക;
    അവസ്ഥ 2:
        *sincx = -bpp;
        *sincy = -src->w * *sincx - pitch;
        *signx = *signy = -1;
        നിർത്തുക;
    അവസ്ഥ 3:
    സ്ഥിരസ്ഥിതി:
        *sincx = pitch;
        *sincy = -*sincx * src->h - bpp;
        *signx = -1;
        *signy = 1;
        നിർത്തുക;
    }
    എങ്കിൽ (flipx) {
        *signx = -*signx;
    }
    എങ്കിൽ (flipy) {
        *signy = -*signy;
    }
}

// Performs a relatively fast rotation/flip when the angle is a multiple of 90 degrees.
#define TRANSFORM_SURFACE_90(pixelType)                                                                     \
    പൂർണ്ണസംഖ്യ dy, dincy = dst->pitch - dst->w * വലുപ്പം(pixelType), sincx, sincy, signx, signy;                    \
    Uint8 *sp = (Uint8 *)src->pixels, *dp = (Uint8 *)dst->pixels, *de;                                      \
                                                                                                            \
    computeSourceIncrements90(src, വലുപ്പം(pixelType), angle, flipx, flipy, &sincx, &sincy, &signx, &signy); \
    എങ്കിൽ (signx < 0)                                                                                          \
        sp += (src->w - 1) * വലുപ്പം(pixelType);                                                             \
    എങ്കിൽ (signy < 0)                                                                                          \
        sp += (src->h - 1) * src->pitch;                                                                    \
                                                                                                            \
    വേണ്ടി (dy = 0; dy < dst->h; sp += sincy, dp += dincy, dy++) {                                             \
        എങ്കിൽ (sincx == വലുപ്പം(pixelType)) { /* if advancing src and dest equally, use SDL_memcpy */           \
            SDL_memcpy(dp, sp, dst->w * വലുപ്പം(pixelType));                                                 \
            sp += dst->w * വലുപ്പം(pixelType);                                                               \
            dp += dst->w * വലുപ്പം(pixelType);                                                               \
        } അല്ലെങ്കിൽ {                                                                                            \
            വേണ്ടി (de = dp + dst->w * വലുപ്പം(pixelType); dp != de; sp += sincx, dp += വലുപ്പം(pixelType)) {    \
                *(pixelType *)dp = *(pixelType *)sp;                                                        \
            }                                                                                               \
        }                                                                                                   \
    }

സ്ഥിതം ശൂന്യം transformSurfaceRGBA90(SDL_Surface *src, SDL_Surface *dst, പൂർണ്ണസംഖ്യ angle, പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy)
{
    TRANSFORM_SURFACE_90(tColorRGBA);
}

സ്ഥിതം ശൂന്യം transformSurfaceY90(SDL_Surface *src, SDL_Surface *dst, പൂർണ്ണസംഖ്യ angle, പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy)
{
    TRANSFORM_SURFACE_90(tColorY);
}

#undef TRANSFORM_SURFACE_90

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
സ്ഥിതം ശൂന്യം transformSurfaceRGBA(SDL_Surface *src, SDL_Surface *dst, പൂർണ്ണസംഖ്യ isin, പൂർണ്ണസംഖ്യ icos,
                                 പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy, പൂർണ്ണസംഖ്യ smooth,
                                 സ്ഥിരം SDL_Rect *rect_dest,
                                 സ്ഥിരം SDL_FPoint *center)
{
    പൂർണ്ണസംഖ്യ sw, sh;
    പൂർണ്ണസംഖ്യ cx, cy;
    tColorRGBA c00, c01, c10, c11, cswap;
    tColorRGBA *pc, *sp;
    പൂർണ്ണസംഖ്യ gap;
    സ്ഥിരം പൂർണ്ണസംഖ്യ fp_half = (1 << 15);

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorRGBA *)dst->pixels;
    gap = dst->pitch - dst->w * 4;
    cx = (പൂർണ്ണസംഖ്യ)(center->x * 65536.0);
    cy = (പൂർണ്ണസംഖ്യ)(center->y * 65536.0);

    /*
     * Switch between interpolating and non-interpolating code
     */
    എങ്കിൽ (smooth) {
        പൂർണ്ണസംഖ്യ y;
        വേണ്ടി (y = 0; y < dst->h; y++) {
            പൂർണ്ണസംഖ്യ x;
            ഇരട്ട src_x = ((ഇരട്ട)rect_dest->x + 0 + 0.5 - center->x);
            ഇരട്ട src_y = ((ഇരട്ട)rect_dest->y + y + 0.5 - center->y);
            പൂർണ്ണസംഖ്യ sdx = (പൂർണ്ണസംഖ്യ)((icos * src_x - isin * src_y) + cx - fp_half);
            പൂർണ്ണസംഖ്യ sdy = (പൂർണ്ണസംഖ്യ)((isin * src_x + icos * src_y) + cy - fp_half);
            വേണ്ടി (x = 0; x < dst->w; x++) {
                പൂർണ്ണസംഖ്യ dx = (sdx >> 16);
                പൂർണ്ണസംഖ്യ dy = (sdy >> 16);
                എങ്കിൽ (flipx) {
                    dx = sw - dx;
                }
                എങ്കിൽ (flipy) {
                    dy = sh - dy;
                }
                എങ്കിൽ ((dx > -1) && (dy > -1) && (dx < (src->w - 1)) && (dy < (src->h - 1))) {
                    പൂർണ്ണസംഖ്യ ex, ey;
                    പൂർണ്ണസംഖ്യ t1, t2;
                    sp = (tColorRGBA *)((Uint8 *)src->pixels + src->pitch * dy) + dx;
                    c00 = *sp;
                    sp += 1;
                    c01 = *sp;
                    sp += (src->pitch / 4);
                    c11 = *sp;
                    sp -= 1;
                    c10 = *sp;
                    എങ്കിൽ (flipx) {
                        cswap = c00;
                        c00 = c01;
                        c01 = cswap;
                        cswap = c10;
                        c10 = c11;
                        c11 = cswap;
                    }
                    എങ്കിൽ (flipy) {
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
    } അല്ലെങ്കിൽ {
        പൂർണ്ണസംഖ്യ y;
        വേണ്ടി (y = 0; y < dst->h; y++) {
            പൂർണ്ണസംഖ്യ x;
            ഇരട്ട src_x = ((ഇരട്ട)rect_dest->x + 0 + 0.5 - center->x);
            ഇരട്ട src_y = ((ഇരട്ട)rect_dest->y + y + 0.5 - center->y);
            പൂർണ്ണസംഖ്യ sdx = (പൂർണ്ണസംഖ്യ)((icos * src_x - isin * src_y) + cx - fp_half);
            പൂർണ്ണസംഖ്യ sdy = (പൂർണ്ണസംഖ്യ)((isin * src_x + icos * src_y) + cy - fp_half);
            വേണ്ടി (x = 0; x < dst->w; x++) {
                പൂർണ്ണസംഖ്യ dx = (sdx >> 16);
                പൂർണ്ണസംഖ്യ dy = (sdy >> 16);
                എങ്കിൽ ((unsigned)dx < (unsigned)src->w && (unsigned)dy < (unsigned)src->h) {
                    എങ്കിൽ (flipx) {
                        dx = sw - dx;
                    }
                    എങ്കിൽ (flipy) {
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
സ്ഥിതം ശൂന്യം transformSurfaceY(SDL_Surface *src, SDL_Surface *dst, പൂർണ്ണസംഖ്യ isin, പൂർണ്ണസംഖ്യ icos, പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy,
                              സ്ഥിരം SDL_Rect *rect_dest,
                              സ്ഥിരം SDL_FPoint *center)
{
    പൂർണ്ണസംഖ്യ sw, sh;
    പൂർണ്ണസംഖ്യ cx, cy;
    tColorY *pc;
    പൂർണ്ണസംഖ്യ gap;
    സ്ഥിരം പൂർണ്ണസംഖ്യ fp_half = (1 << 15);
    പൂർണ്ണസംഖ്യ y;

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorY *)dst->pixels;
    gap = dst->pitch - dst->w;
    cx = (പൂർണ്ണസംഖ്യ)(center->x * 65536.0);
    cy = (പൂർണ്ണസംഖ്യ)(center->y * 65536.0);

    /*
     * Clear surface to colorkey
     */
    SDL_memset(pc, (പൂർണ്ണസംഖ്യ)(get_colorkey(src) & 0xff), (size_t)dst->pitch * dst->h);
    /*
     * Iterate through destination surface
     */
    വേണ്ടി (y = 0; y < dst->h; y++) {
        പൂർണ്ണസംഖ്യ x;
        ഇരട്ട src_x = ((ഇരട്ട)rect_dest->x + 0 + 0.5 - center->x);
        ഇരട്ട src_y = ((ഇരട്ട)rect_dest->y + y + 0.5 - center->y);
        പൂർണ്ണസംഖ്യ sdx = (പൂർണ്ണസംഖ്യ)((icos * src_x - isin * src_y) + cx - fp_half);
        പൂർണ്ണസംഖ്യ sdy = (പൂർണ്ണസംഖ്യ)((isin * src_x + icos * src_y) + cy - fp_half);
        വേണ്ടി (x = 0; x < dst->w; x++) {
            പൂർണ്ണസംഖ്യ dx = (sdx >> 16);
            പൂർണ്ണസംഖ്യ dy = (sdy >> 16);
            എങ്കിൽ ((unsigned)dx < (unsigned)src->w && (unsigned)dy < (unsigned)src->h) {
                എങ്കിൽ (flipx) {
                    dx = sw - dx;
                }
                എങ്കിൽ (flipy) {
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

SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, ഇരട്ട angle, പൂർണ്ണസംഖ്യ smooth, പൂർണ്ണസംഖ്യ flipx, പൂർണ്ണസംഖ്യ flipy,
                     സ്ഥിരം SDL_Rect *rect_dest, ഇരട്ട cangle, ഇരട്ട sangle, സ്ഥിരം SDL_FPoint *center)
{
    SDL_Surface *rz_dst;
    പൂർണ്ണസംഖ്യ is8bit, angle90;
    SDL_BlendMode blendmode;
    Uint32 colorkey = 0;
    bool color_താക്കോൽ_Available = false;
    ഇരട്ട sangleinv, cangleinv;

    // Sanity check
    എങ്കിൽ (!SDL_SurfaceValid(src)) {
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (SDL_Surface_Has_Color_താക്കോൽ(src)) {
        എങ്കിൽ (SDL_Get_Surface_Color_താക്കോൽ(src, &colorkey)) {
            color_താക്കോൽ_Available = true;
        }
    }
    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    is8bit = (src->format == SDL_PIXELFORMAT_INDEX8) && color_താക്കോൽ_Available;
    എങ്കിൽ (!is8bit &&
        !(SDL_BITSPERPIXEL(src->format) == 32 && SDL_PIXELLAYOUT(src->format) == SDL_PACKEDLAYOUT_8888)) {
        തിരികെ ശൂന്യ;
    }

    // Calculate target factors from sine/cosine and zoom
    sangleinv = sangle * 65536.0;
    cangleinv = cangle * 65536.0;

    // Alloc space to completely contain the rotated surface
    rz_dst = ശൂന്യ;
    എങ്കിൽ (is8bit) {
        // Target surface is 8 bit
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_ROWS, src->format);
        എങ്കിൽ (rz_dst) {
            SDL_SetSurfacePalette(rz_dst, src->palette);
        }
    } അല്ലെങ്കിൽ {
        // Target surface is 32 bit with source RGBA ordering
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_ROWS, src->format);
    }

    // Check target
    എങ്കിൽ (!rz_dst) {
        തിരികെ ശൂന്യ;
    }

    // Adjust for guard rows
    rz_dst->h = rect_dest->h;

    SDL_GetSurfaceBlendMode(src, &blendmode);

    എങ്കിൽ (color_താക്കോൽ_Available) {
        // If available, the colorkey will be used to discard the pixels that are outside of the rotated area.
        SDL_Set_Surface_Color_താക്കോൽ(rz_dst, true, colorkey);
        SDL_FillSurfaceRect(rz_dst, ശൂന്യ, colorkey);
    } അല്ലെങ്കിൽ എങ്കിൽ (blendmode == SDL_BLENDMODE_NONE) {
        blendmode = SDL_BLENDMODE_BLEND;
    } അല്ലെങ്കിൽ എങ്കിൽ (blendmode == SDL_BLENDMODE_MOD || blendmode == SDL_BLENDMODE_MUL) {
        /* Without a colorkey, the target texture has to be white for the MOD and MUL blend mode so
         * that the pixels outside the rotated area don't affect the destination surface.
         */
        colorkey = SDL_MapSurfaceRGBA(rz_dst, 255, 255, 255, 0);
        SDL_FillSurfaceRect(rz_dst, ശൂന്യ, colorkey);
        /* Setting a white colorkey for the destination surface makes the final blit discard
         * all pixels outside of the rotated area. This doesn't interfere with anything because
         * white pixels are already a no-op and the MOD blend mode does not interact with alpha.
         */
        SDL_Set_Surface_Color_താക്കോൽ(rz_dst, true, colorkey);
    }

    SDL_SetSurfaceBlendMode(rz_dst, blendmode);

    // Lock source surface
    എങ്കിൽ (SDL_MUSTLOCK(src)) {
        എങ്കിൽ (!SDL_LockSurface(src)) {
            SDL_DestroySurface(rz_dst);
            തിരികെ ശൂന്യ;
        }
    }

    /* check if the rotation is a multiple of 90 degrees so we can take a fast path and also somewhat reduce
     * the off-by-one problem in transformSurfaceRGBA that expresses itself when the rotation is near
     * multiples of 90 degrees.
     */
    angle90 = (പൂർണ്ണസംഖ്യ)(angle / 90);
    എങ്കിൽ (angle90 == angle / 90) {
        angle90 %= 4;
        എങ്കിൽ (angle90 < 0) {
            angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
        }

    } അല്ലെങ്കിൽ {
        angle90 = -1;
    }

    എങ്കിൽ (is8bit) {
        // Call the 8-bit transformation routine to do the rotation
        എങ്കിൽ (angle90 >= 0) {
            transformSurfaceY90(src, rz_dst, angle90, flipx, flipy);
        } അല്ലെങ്കിൽ {
            transformSurfaceY(src, rz_dst, (പൂർണ്ണസംഖ്യ)sangleinv, (പൂർണ്ണസംഖ്യ)cangleinv,
                              flipx, flipy, rect_dest, center);
        }
    } അല്ലെങ്കിൽ {
        // Call the 32-bit transformation routine to do the rotation
        എങ്കിൽ (angle90 >= 0) {
            transformSurfaceRGBA90(src, rz_dst, angle90, flipx, flipy);
        } അല്ലെങ്കിൽ {
            transformSurfaceRGBA(src, rz_dst, (പൂർണ്ണസംഖ്യ)sangleinv, (പൂർണ്ണസംഖ്യ)cangleinv,
                                 flipx, flipy, smooth, rect_dest, center);
        }
    }

    // Unlock source surface
    എങ്കിൽ (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }

    // Return rotated surface
    തിരികെ rz_dst;
}


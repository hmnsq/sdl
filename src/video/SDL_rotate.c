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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_rotate.h"

// ---- Internally used structures

/**
A 32 bit RGBA pixel.
*/
प्रकारव्याख्या संरचना tColorRGBA
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} tColorRGBA;

/**
A 8bit Y/palette pixel.
*/
प्रकारव्याख्या संरचना tColorY
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
स्थिर Uint32 get_colorkey(SDL_Surface *src)
{
    Uint32 किल्ली = 0;
    जर (SDL_Surface_Has_Color_किल्ली(src)) {
        SDL_Get_Surface_Color_किल्ली(src, &किल्ली);
    }
    परत किल्ली;
}

// rotate (sx, sy) by (angle, center) into (dx, dy)
स्थिर शून्य rotate(द्विगुण sx, द्विगुण sy, द्विगुण sinangle, द्विगुण cosangle, स्थिरांक SDL_FPoint *center, द्विगुण *dx, द्विगुण *dy)
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
शून्य SDLgfx_rotozoomSurfaceSizeTrig(पूर्णांक width, पूर्णांक height, द्विगुण angle, स्थिरांक SDL_FPoint *center,
                                    SDL_Rect *rect_dest, द्विगुण *cangle, द्विगुण *sangle)
{
    पूर्णांक minx, maxx, miny, maxy;
    द्विगुण radangle;
    द्विगुण x0, x1, x2, x3;
    द्विगुण y0, y1, y2, y3;
    द्विगुण sinangle;
    द्विगुण cosangle;

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

    minx = (पूर्णांक)SDL_floor(SDL_min(SDL_min(x0, x1), SDL_min(x2, x3)));
    maxx = (पूर्णांक)SDL_ceil(SDL_max(SDL_max(x0, x1), SDL_max(x2, x3)));

    miny = (पूर्णांक)SDL_floor(SDL_min(SDL_min(y0, y1), SDL_min(y2, y3)));
    maxy = (पूर्णांक)SDL_ceil(SDL_max(SDL_max(y0, y1), SDL_max(y2, y3)));

    rect_dest->w = maxx - minx;
    rect_dest->h = maxy - miny;
    rect_dest->x = minx;
    rect_dest->y = miny;

    // reverse the angle because our rotations are clockwise
    *sangle = -sinangle;
    *cangle = cosangle;

    {
        // The trig code below gets the wrong size (due to FP inaccuracy?) when angle is a multiple of 90 degrees
        पूर्णांक angle90 = (पूर्णांक)(angle / 90);
        जर (angle90 == angle / 90) { // if the angle is a multiple of 90 degrees
            angle90 %= 4;
            जर (angle90 < 0) {
                angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
            }

            जर (angle90 & 1) {
                rect_dest->w = height;
                rect_dest->h = width;
                *cangle = 0;
                *sangle = angle90 == 1 ? -1 : 1; // reversed because our rotations are clockwise
            } अन्यथा {
                rect_dest->w = width;
                rect_dest->h = height;
                *cangle = angle90 == 0 ? 1 : -1;
                *sangle = 0;
            }
        }
    }
}

// Computes source pointer X/Y increments for a rotation that's a multiple of 90 degrees.
स्थिर शून्य computeSourceIncrements90(SDL_Surface *src, पूर्णांक bpp, पूर्णांक angle, पूर्णांक flipx, पूर्णांक flipy,
                                      पूर्णांक *sincx, पूर्णांक *sincy, पूर्णांक *signx, पूर्णांक *signy)
{
    पूर्णांक pitch = flipy ? -src->pitch : src->pitch;
    जर (flipx) {
        bpp = -bpp;
    }
    निवड (angle) { // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
    स्थिती 0:
        *sincx = bpp;
        *sincy = pitch - src->w * *sincx;
        *signx = *signy = 1;
        थांबा;
    स्थिती 1:
        *sincx = -pitch;
        *sincy = bpp - *sincx * src->h;
        *signx = 1;
        *signy = -1;
        थांबा;
    स्थिती 2:
        *sincx = -bpp;
        *sincy = -src->w * *sincx - pitch;
        *signx = *signy = -1;
        थांबा;
    स्थिती 3:
    पूर्वनिर्धारित:
        *sincx = pitch;
        *sincy = -*sincx * src->h - bpp;
        *signx = -1;
        *signy = 1;
        थांबा;
    }
    जर (flipx) {
        *signx = -*signx;
    }
    जर (flipy) {
        *signy = -*signy;
    }
}

// Performs a relatively fast rotation/flip when the angle is a multiple of 90 degrees.
#define TRANSFORM_SURFACE_90(pixelType)                                                                     \
    पूर्णांक dy, dincy = dst->pitch - dst->w * आकार(pixelType), sincx, sincy, signx, signy;                    \
    Uint8 *sp = (Uint8 *)src->pixels, *dp = (Uint8 *)dst->pixels, *de;                                      \
                                                                                                            \
    computeSourceIncrements90(src, आकार(pixelType), angle, flipx, flipy, &sincx, &sincy, &signx, &signy); \
    जर (signx < 0)                                                                                          \
        sp += (src->w - 1) * आकार(pixelType);                                                             \
    जर (signy < 0)                                                                                          \
        sp += (src->h - 1) * src->pitch;                                                                    \
                                                                                                            \
    साठी (dy = 0; dy < dst->h; sp += sincy, dp += dincy, dy++) {                                             \
        जर (sincx == आकार(pixelType)) { /* if advancing src and dest equally, use SDL_memcpy */           \
            SDL_memcpy(dp, sp, dst->w * आकार(pixelType));                                                 \
            sp += dst->w * आकार(pixelType);                                                               \
            dp += dst->w * आकार(pixelType);                                                               \
        } अन्यथा {                                                                                            \
            साठी (de = dp + dst->w * आकार(pixelType); dp != de; sp += sincx, dp += आकार(pixelType)) {    \
                *(pixelType *)dp = *(pixelType *)sp;                                                        \
            }                                                                                               \
        }                                                                                                   \
    }

स्थिर शून्य transformSurfaceRGBA90(SDL_Surface *src, SDL_Surface *dst, पूर्णांक angle, पूर्णांक flipx, पूर्णांक flipy)
{
    TRANSFORM_SURFACE_90(tColorRGBA);
}

स्थिर शून्य transformSurfaceY90(SDL_Surface *src, SDL_Surface *dst, पूर्णांक angle, पूर्णांक flipx, पूर्णांक flipy)
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
स्थिर शून्य transformSurfaceRGBA(SDL_Surface *src, SDL_Surface *dst, पूर्णांक isin, पूर्णांक icos,
                                 पूर्णांक flipx, पूर्णांक flipy, पूर्णांक smooth,
                                 स्थिरांक SDL_Rect *rect_dest,
                                 स्थिरांक SDL_FPoint *center)
{
    पूर्णांक sw, sh;
    पूर्णांक cx, cy;
    tColorRGBA c00, c01, c10, c11, cswap;
    tColorRGBA *pc, *sp;
    पूर्णांक gap;
    स्थिरांक पूर्णांक fp_half = (1 << 15);

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorRGBA *)dst->pixels;
    gap = dst->pitch - dst->w * 4;
    cx = (पूर्णांक)(center->x * 65536.0);
    cy = (पूर्णांक)(center->y * 65536.0);

    /*
     * Switch between interpolating and non-interpolating code
     */
    जर (smooth) {
        पूर्णांक y;
        साठी (y = 0; y < dst->h; y++) {
            पूर्णांक x;
            द्विगुण src_x = ((द्विगुण)rect_dest->x + 0 + 0.5 - center->x);
            द्विगुण src_y = ((द्विगुण)rect_dest->y + y + 0.5 - center->y);
            पूर्णांक sdx = (पूर्णांक)((icos * src_x - isin * src_y) + cx - fp_half);
            पूर्णांक sdy = (पूर्णांक)((isin * src_x + icos * src_y) + cy - fp_half);
            साठी (x = 0; x < dst->w; x++) {
                पूर्णांक dx = (sdx >> 16);
                पूर्णांक dy = (sdy >> 16);
                जर (flipx) {
                    dx = sw - dx;
                }
                जर (flipy) {
                    dy = sh - dy;
                }
                जर ((dx > -1) && (dy > -1) && (dx < (src->w - 1)) && (dy < (src->h - 1))) {
                    पूर्णांक ex, ey;
                    पूर्णांक t1, t2;
                    sp = (tColorRGBA *)((Uint8 *)src->pixels + src->pitch * dy) + dx;
                    c00 = *sp;
                    sp += 1;
                    c01 = *sp;
                    sp += (src->pitch / 4);
                    c11 = *sp;
                    sp -= 1;
                    c10 = *sp;
                    जर (flipx) {
                        cswap = c00;
                        c00 = c01;
                        c01 = cswap;
                        cswap = c10;
                        c10 = c11;
                        c11 = cswap;
                    }
                    जर (flipy) {
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
    } अन्यथा {
        पूर्णांक y;
        साठी (y = 0; y < dst->h; y++) {
            पूर्णांक x;
            द्विगुण src_x = ((द्विगुण)rect_dest->x + 0 + 0.5 - center->x);
            द्विगुण src_y = ((द्विगुण)rect_dest->y + y + 0.5 - center->y);
            पूर्णांक sdx = (पूर्णांक)((icos * src_x - isin * src_y) + cx - fp_half);
            पूर्णांक sdy = (पूर्णांक)((isin * src_x + icos * src_y) + cy - fp_half);
            साठी (x = 0; x < dst->w; x++) {
                पूर्णांक dx = (sdx >> 16);
                पूर्णांक dy = (sdy >> 16);
                जर ((अचिन्हित)dx < (अचिन्हित)src->w && (अचिन्हित)dy < (अचिन्हित)src->h) {
                    जर (flipx) {
                        dx = sw - dx;
                    }
                    जर (flipy) {
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
स्थिर शून्य transformSurfaceY(SDL_Surface *src, SDL_Surface *dst, पूर्णांक isin, पूर्णांक icos, पूर्णांक flipx, पूर्णांक flipy,
                              स्थिरांक SDL_Rect *rect_dest,
                              स्थिरांक SDL_FPoint *center)
{
    पूर्णांक sw, sh;
    पूर्णांक cx, cy;
    tColorY *pc;
    पूर्णांक gap;
    स्थिरांक पूर्णांक fp_half = (1 << 15);
    पूर्णांक y;

    /*
     * Variable setup
     */
    sw = src->w - 1;
    sh = src->h - 1;
    pc = (tColorY *)dst->pixels;
    gap = dst->pitch - dst->w;
    cx = (पूर्णांक)(center->x * 65536.0);
    cy = (पूर्णांक)(center->y * 65536.0);

    /*
     * Clear surface to colorkey
     */
    SDL_memset(pc, (पूर्णांक)(get_colorkey(src) & 0xff), (माप_प्रकार)dst->pitch * dst->h);
    /*
     * Iterate through destination surface
     */
    साठी (y = 0; y < dst->h; y++) {
        पूर्णांक x;
        द्विगुण src_x = ((द्विगुण)rect_dest->x + 0 + 0.5 - center->x);
        द्विगुण src_y = ((द्विगुण)rect_dest->y + y + 0.5 - center->y);
        पूर्णांक sdx = (पूर्णांक)((icos * src_x - isin * src_y) + cx - fp_half);
        पूर्णांक sdy = (पूर्णांक)((isin * src_x + icos * src_y) + cy - fp_half);
        साठी (x = 0; x < dst->w; x++) {
            पूर्णांक dx = (sdx >> 16);
            पूर्णांक dy = (sdy >> 16);
            जर ((अचिन्हित)dx < (अचिन्हित)src->w && (अचिन्हित)dy < (अचिन्हित)src->h) {
                जर (flipx) {
                    dx = sw - dx;
                }
                जर (flipy) {
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

SDL_Surface *SDLgfx_rotateSurface(SDL_Surface *src, द्विगुण angle, पूर्णांक smooth, पूर्णांक flipx, पूर्णांक flipy,
                     स्थिरांक SDL_Rect *rect_dest, द्विगुण cangle, द्विगुण sangle, स्थिरांक SDL_FPoint *center)
{
    SDL_Surface *rz_dst;
    पूर्णांक is8bit, angle90;
    SDL_BlendMode blendmode;
    Uint32 colorkey = 0;
    bool color_किल्ली_Available = false;
    द्विगुण sangleinv, cangleinv;

    // Sanity check
    जर (!SDL_SurfaceValid(src)) {
        परत रिक्त;
    }

    जर (SDL_Surface_Has_Color_किल्ली(src)) {
        जर (SDL_Get_Surface_Color_किल्ली(src, &colorkey)) {
            color_किल्ली_Available = true;
        }
    }
    // This function requires a 32-bit surface or 8-bit surface with a colorkey
    is8bit = (src->format == SDL_PIXELFORMAT_INDEX8) && color_किल्ली_Available;
    जर (!is8bit &&
        !(SDL_BITSPERPIXEL(src->format) == 32 && SDL_PIXELLAYOUT(src->format) == SDL_PACKEDLAYOUT_8888)) {
        परत रिक्त;
    }

    // Calculate target factors from sine/cosine and zoom
    sangleinv = sangle * 65536.0;
    cangleinv = cangle * 65536.0;

    // Alloc space to completely contain the rotated surface
    rz_dst = रिक्त;
    जर (is8bit) {
        // Target surface is 8 bit
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_ROWS, src->format);
        जर (rz_dst) {
            SDL_SetSurfacePalette(rz_dst, src->palette);
        }
    } अन्यथा {
        // Target surface is 32 bit with source RGBA ordering
        rz_dst = SDL_CreateSurfaceZeroed(rect_dest->w, rect_dest->h + GUARD_ROWS, src->format);
    }

    // Check target
    जर (!rz_dst) {
        परत रिक्त;
    }

    // Adjust for guard rows
    rz_dst->h = rect_dest->h;

    SDL_GetSurfaceBlendMode(src, &blendmode);

    जर (color_किल्ली_Available) {
        // If available, the colorkey will be used to discard the pixels that are outside of the rotated area.
        SDL_Set_Surface_Color_किल्ली(rz_dst, true, colorkey);
        SDL_FillSurfaceRect(rz_dst, रिक्त, colorkey);
    } अन्यथा जर (blendmode == SDL_BLENDMODE_NONE) {
        blendmode = SDL_BLENDMODE_BLEND;
    } अन्यथा जर (blendmode == SDL_BLENDMODE_MOD || blendmode == SDL_BLENDMODE_MUL) {
        /* Without a colorkey, the target texture has to be white for the MOD and MUL blend mode so
         * that the pixels outside the rotated area don't affect the destination surface.
         */
        colorkey = SDL_MapSurfaceRGBA(rz_dst, 255, 255, 255, 0);
        SDL_FillSurfaceRect(rz_dst, रिक्त, colorkey);
        /* Setting a white colorkey for the destination surface makes the final blit discard
         * all pixels outside of the rotated area. This doesn't interfere with anything because
         * white pixels are already a no-op and the MOD blend mode does not interact with alpha.
         */
        SDL_Set_Surface_Color_किल्ली(rz_dst, true, colorkey);
    }

    SDL_SetSurfaceBlendMode(rz_dst, blendmode);

    // Lock source surface
    जर (SDL_MUSTLOCK(src)) {
        जर (!SDL_LockSurface(src)) {
            SDL_DestroySurface(rz_dst);
            परत रिक्त;
        }
    }

    /* check if the rotation is a multiple of 90 degrees so we can take a fast path and also somewhat reduce
     * the off-by-one problem in transformSurfaceRGBA that expresses itself when the rotation is near
     * multiples of 90 degrees.
     */
    angle90 = (पूर्णांक)(angle / 90);
    जर (angle90 == angle / 90) {
        angle90 %= 4;
        जर (angle90 < 0) {
            angle90 += 4; // 0:0 deg, 1:90 deg, 2:180 deg, 3:270 deg
        }

    } अन्यथा {
        angle90 = -1;
    }

    जर (is8bit) {
        // Call the 8-bit transformation routine to do the rotation
        जर (angle90 >= 0) {
            transformSurfaceY90(src, rz_dst, angle90, flipx, flipy);
        } अन्यथा {
            transformSurfaceY(src, rz_dst, (पूर्णांक)sangleinv, (पूर्णांक)cangleinv,
                              flipx, flipy, rect_dest, center);
        }
    } अन्यथा {
        // Call the 32-bit transformation routine to do the rotation
        जर (angle90 >= 0) {
            transformSurfaceRGBA90(src, rz_dst, angle90, flipx, flipy);
        } अन्यथा {
            transformSurfaceRGBA(src, rz_dst, (पूर्णांक)sangleinv, (पूर्णांक)cangleinv,
                                 flipx, flipy, smooth, rect_dest, center);
        }
    }

    // Unlock source surface
    जर (SDL_MUSTLOCK(src)) {
        SDL_UnlockSurface(src);
    }

    // Return rotated surface
    परत rz_dst;
}


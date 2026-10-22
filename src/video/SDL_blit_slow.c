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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_blit_slow.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    Slow_Blit_Pixel_Access_10_ಬಿಟ್,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

ಸ್ಥಿರ SlowBlitPixelAccess Get_Pixel_Access_ವಿಧಾನ(SDL_PixelFormat format)
{
    ಆದರೆ (SDL_BYTESPERPIXEL(format) > 4) {
        ಹಿಂತಿರುಗಿ SlowBlitPixelAccess_Large;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(format)) {
        ಹಿಂತಿರುಗಿ Slow_Blit_Pixel_Access_10_ಬಿಟ್;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == SDL_PIXELFORMAT_INDEX8) {
        ಹಿಂತಿರುಗಿ SlowBlitPixelAccess_Index8;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_ALPHA(format)) {
        ಹಿಂತಿರುಗಿ SlowBlitPixelAccess_RGBA;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
ಶೂನ್ಯ SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ flags = info->flags;
    ಸ್ಥಿರಾಂಕ Uint32 modulateR = info->r;
    ಸ್ಥಿರಾಂಕ Uint32 modulateG = info->g;
    ಸ್ಥಿರಾಂಕ Uint32 modulateB = info->b;
    ಸ್ಥಿರಾಂಕ Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *src_pal = info->src_pal;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_ಕೋಷ್ಟಕ *palette_map = info->palette_map;
    ಪೂರ್ಣಾಂಕ srcbpp = src_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಪೂರ್ಣಾಂಕ dstbpp = dst_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 ಕೊನೆಯ_pixel = 0;
    Uint8 ಕೊನೆಯ_ಸೂಚ್ಯಂಕ = 0;

    src_access = Get_Pixel_Access_ವಿಧಾನ(src_fmt->format);
    dst_access = Get_Pixel_Access_ವಿಧಾನ(dst_fmt->format);
    ಆದರೆ (dst_access == SlowBlitPixelAccess_Index8) {
        ಕೊನೆಯ_ಸೂಚ್ಯಂಕ = SDL_LookupRGBAColor(palette_map, ಕೊನೆಯ_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    ಆಗ (info->dst_h--) {
        Uint8 *src = ಖಾಲಿ;
        Uint8 *dst = info->dst;
        ಪೂರ್ಣಾಂಕ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ಆಗ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ಆಯ್ಕೆ (src_access) {
            ಸ್ಥಿತಿ SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ Slow_Blit_Pixel_Access_10_ಬಿಟ್:
                srcpixel = *((Uint32 *)(src));
                ಆಯ್ಕೆ (src_fmt->format) {
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ನಿಲ್ಲಿಸು;
                ಪೂರ್ವನಿಯೋಜಿತ:
                    ನಿಲ್ಲಿಸು;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                ಆದರೆ (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                ಆದರೆ ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    ಮುಂದುವರಿ;
                }
            }
            ಆದರೆ (flags & SDL_COPY_BLEND_ಮುಖವಾಡ) {
                ಆಯ್ಕೆ (dst_access) {
                ಸ್ಥಿತಿ SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ Slow_Blit_Pixel_Access_10_ಬಿಟ್:
                    dstpixel = *((Uint32 *)(dst));
                    ಆಯ್ಕೆ (dst_fmt->format) {
                    ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ನಿಲ್ಲಿಸು;
                    ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ನಿಲ್ಲಿಸು;
                    ಪೂರ್ವನಿಯೋಜಿತ:
                        ನಿಲ್ಲಿಸು;
                    }
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    ನಿಲ್ಲಿಸು;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                // don't care
            }

            ಆದರೆ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ಆದರೆ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ಆದರೆ (flags & (SDL_COPY_BLEND | SDL_COPY_ಕೂಡಿಸು)) {
                ಆದರೆ (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            ಆಯ್ಕೆ (flags & SDL_COPY_BLEND_ಮುಖವಾಡ) {
            ಸ್ಥಿತಿ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                ಆದರೆ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                ಆದರೆ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                ಆದರೆ (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ಆದರೆ (dstA > 255) {
                    dstA = 255;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_ಕೂಡಿಸು:
            ಸ್ಥಿತಿ SDL_COPY_ಕೂಡಿಸು_PREMULTIPLIED:
                dstR = srcR + dstR;
                ಆದರೆ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                ಆದರೆ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                ಆದರೆ (dstB > 255) {
                    dstB = 255;
                }
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                ಆದರೆ (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                ಆದರೆ (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                ಆದರೆ (dstB > 255) {
                    dstB = 255;
                }
                ನಿಲ್ಲಿಸು;
            }

            ಆಯ್ಕೆ (dst_access) {
            ಸ್ಥಿತಿ SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                ಆದರೆ (dstpixel != ಕೊನೆಯ_pixel) {
                    ಕೊನೆಯ_pixel = dstpixel;
                    ಕೊನೆಯ_ಸೂಚ್ಯಂಕ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = ಕೊನೆಯ_ಸೂಚ್ಯಂಕ;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ Slow_Blit_Pixel_Access_10_ಬಿಟ್:
            {
                Uint32 pixelvalue;
                ಆಯ್ಕೆ (dst_fmt->format) {
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ನಿಲ್ಲಿಸು;
                ಪೂರ್ವನಿಯೋಜಿತ:
                    pixelvalue = 0;
                    ನಿಲ್ಲಿಸು;
                }
                *(Uint32 *)dst = pixelvalue;
                ನಿಲ್ಲಿಸು;
            }
            ಸ್ಥಿತಿ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ನಿಲ್ಲಿಸು;
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}

/* Convert from F16 to float
 * Public domain implementation from https://gist.github.com/rygorous/2144712
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ
{
    Uint32 u;
    ದಶಮಾಂಶ f;
    ರಚನೆ
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning(ತಳ್ಳು)
#ಸೂಚನೆ warning(disable:4214)
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ
{
    Uint16 u;
    ರಚನೆ
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning(ತೆಗೆ)
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ದಶಮಾಂಶ half_ಗಮ್ಯ_float(Uint16 un_ಮೌಲ್ಯ)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FP32 magic = { (254 - 15) << 23 };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_ಮೌಲ್ಯ;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    ಆದರೆ (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    ಹಿಂತಿರುಗಿ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
ಸ್ಥಿರ Uint16 float_ಗಮ್ಯ_half(ದಶಮಾಂಶ a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, ಗಾತ್ರ(ia));

    ir = (ia >> 16) & 0x8000;
    ಆದರೆ ((ia & 0x7f800000) == 0x7f800000) {
        ಆದರೆ ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } ಇಲ್ಲದಿದ್ದರೆ {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ia & 0x7f800000) >= 0x33000000) {
        ಪೂರ್ಣಾಂಕ ಸರಿಸು = (ಪೂರ್ಣಾಂಕ)((ia >> 23) & 0xff) - 127;
        ಆದರೆ (ಸರಿಸು > 15) {
            ir |= 0x7c00; // infinity
        } ಇಲ್ಲದಿದ್ದರೆ {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            ಆದರೆ (ಸರಿಸು < -14) { // denormal
                ir |= ia >> (-1 - ಸರಿಸು);
                ia = ia << (32 - (-1 - ಸರಿಸು));
            } ಇಲ್ಲದಿದ್ದರೆ { //ಸಾಮಾನ್ಯ
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + ಸರಿಸು) << 10);
            }
            // IEEE-754 round to nearest of even
            ಆದರೆ ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    ಹಿಂತಿರುಗಿ ir;
}

ಸ್ಥಿರ ಶೂನ್ಯ ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt, ಸ್ಥಿರಾಂಕ SDL_Palette *pal, SDL_Colorspace colorspace, ದಶಮಾಂಶ SDR_white_ಬಿಂದು,
                           ದಶಮಾಂಶ *ಹೊರಹೋಗು_R, ದಶಮಾಂಶ *ಹೊರಹೋಗು_G, ದಶಮಾಂಶ *ಹೊರಹೋಗು_B, ದಶಮಾಂಶ *ಹೊರಹೋಗು_A)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    ದಶಮಾಂಶ fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    ದಶಮಾಂಶ v[4];

    ಆಯ್ಕೆ (access) {
    ಸ್ಥಿತಿ SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (ದಶಮಾಂಶ)pal->colors[pixelvalue].r / 255.0f;
        fG = (ದಶಮಾಂಶ)pal->colors[pixelvalue].g / 255.0f;
        fB = (ದಶಮಾಂಶ)pal->colors[pixelvalue].b / 255.0f;
        fA = (ದಶಮಾಂಶ)pal->colors[pixelvalue].a / 255.0f;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel, fmt, pixelvalue, R, G, B);
        fR = (ದಶಮಾಂಶ)R / 255.0f;
        fG = (ದಶಮಾಂಶ)G / 255.0f;
        fB = (ದಶಮಾಂಶ)B / 255.0f;
        fA = 1.0f;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (ದಶಮಾಂಶ)R / 255.0f;
        fG = (ದಶಮಾಂಶ)G / 255.0f;
        fB = (ದಶಮಾಂಶ)B / 255.0f;
        fA = (ದಶಮಾಂಶ)A / 255.0f;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ Slow_Blit_Pixel_Access_10_ಬಿಟ್:
        pixelvalue = *((Uint32 *)pixels);
        ಆಯ್ಕೆ (fmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            fR = fG = fB = fA = 0.0f;
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SlowBlitPixelAccess_Large:
        ಆಯ್ಕೆ (SDL_PIXELTYPE(fmt->format)) {
        ಸ್ಥಿತಿ SDL_PIXELTYPE_ARRAYU16:
            v[0] = (ದಶಮಾಂಶ)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (ದಶಮಾಂಶ)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (ದಶಮಾಂಶ)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            ಆದರೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 8) {
                v[3] = (ದಶಮಾಂಶ)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } ಇಲ್ಲದಿದ್ದರೆ {
                v[3] = 1.0f;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_ಗಮ್ಯ_float(((Uint16 *)pixels)[0]);
            v[1] = half_ಗಮ್ಯ_float(((Uint16 *)pixels)[1]);
            v[2] = half_ಗಮ್ಯ_float(((Uint16 *)pixels)[2]);
            ಆದರೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 8) {
                v[3] = half_ಗಮ್ಯ_float(((Uint16 *)pixels)[3]);
            } ಇಲ್ಲದಿದ್ದರೆ {
                v[3] = 1.0f;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((ದಶಮಾಂಶ *)pixels)[0];
            v[1] = ((ದಶಮಾಂಶ *)pixels)[1];
            v[2] = ((ದಶಮಾಂಶ *)pixels)[2];
            ಆದರೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 16) {
                v[3] = ((ದಶಮಾಂಶ *)pixels)[3];
            } ಇಲ್ಲದಿದ್ದರೆ {
                v[3] = 1.0f;
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ನಿಲ್ಲಿಸು;
        }
        ಆಯ್ಕೆ (SDL_PIXELORDER(fmt->format)) {
        ಸ್ಥಿತಿ SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    ಆಯ್ಕೆ (SDL_COLORSPACETRANSFER(colorspace)) {
    ಸ್ಥಿತಿ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBto_ರೇಖೀಯ(fR);
        fG = SDL_s_RGBto_ರೇಖೀಯ(fG);
        fB = SDL_s_RGBto_ರೇಖೀಯ(fB);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_ಬಿಂದು;
        fG = SDL_PQtoNits(fG) / SDR_white_ಬಿಂದು;
        fB = SDL_PQtoNits(fB) / SDR_white_ಬಿಂದು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TRANSFER_CHARACTERISTICS_ರೇಖೀಯ:
        fR /= SDR_white_ಬಿಂದು;
        fG /= SDR_white_ಬಿಂದು;
        fB /= SDR_white_ಬಿಂದು;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // Unknown, leave it alone
        ನಿಲ್ಲಿಸು;
    }

    *ಹೊರಹೋಗು_R = fR;
    *ಹೊರಹೋಗು_G = fG;
    *ಹೊರಹೋಗು_B = fB;
    *ಹೊರಹೋಗು_A = fA;
}

ಸ್ಥಿರ ಶೂನ್ಯ WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, ದಶಮಾಂಶ SDR_white_ಬಿಂದು,
                            ದಶಮಾಂಶ fR, ದಶಮಾಂಶ fG, ದಶಮಾಂಶ fB, ದಶಮಾಂಶ fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    ದಶಮಾಂಶ v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    ಆಯ್ಕೆ (SDL_COLORSPACETRANSFER(colorspace)) {
    ಸ್ಥಿತಿ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBfrom_ರೇಖೀಯ(fR);
        fG = SDL_s_RGBfrom_ರೇಖೀಯ(fG);
        fB = SDL_s_RGBfrom_ರೇಖೀಯ(fB);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_ಬಿಂದು);
        fG = SDL_PQfromNits(fG * SDR_white_ಬಿಂದು);
        fB = SDL_PQfromNits(fB * SDR_white_ಬಿಂದು);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TRANSFER_CHARACTERISTICS_ರೇಖೀಯ:
        fR *= SDR_white_ಬಿಂದು;
        fG *= SDR_white_ಬಿಂದು;
        fB *= SDR_white_ಬಿಂದು;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        // Unknown, leave it alone
        ನಿಲ್ಲಿಸು;
    }

    ಆಯ್ಕೆ (access) {
    ಸ್ಥಿತಿ SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel, fmt, R, G, B);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel, fmt, R, G, B, A);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ Slow_Blit_Pixel_Access_10_ಬಿಟ್:
    {
        ಆಯ್ಕೆ (fmt->format) {
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            pixelvalue = 0;
            ನಿಲ್ಲಿಸು;
        }
        *(Uint32 *)pixels = pixelvalue;
        ನಿಲ್ಲಿಸು;
    }
    ಸ್ಥಿತಿ SlowBlitPixelAccess_Large:
        ಆಯ್ಕೆ (SDL_PIXELORDER(fmt->format)) {
        ಸ್ಥಿತಿ SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ನಿಲ್ಲಿಸು;
        }
        ಆಯ್ಕೆ (SDL_PIXELTYPE(fmt->format)) {
        ಸ್ಥಿತಿ SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ಆದರೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_ಗಮ್ಯ_half(v[0]);
            ((Uint16 *)pixels)[1] = float_ಗಮ್ಯ_half(v[1]);
            ((Uint16 *)pixels)[2] = float_ಗಮ್ಯ_half(v[2]);
            ಆದರೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_ಗಮ್ಯ_half(v[3]);
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_PIXELTYPE_ARRAYF32:
            ((ದಶಮಾಂಶ *)pixels)[0] = v[0];
            ((ದಶಮಾಂಶ *)pixels)[1] = v[1];
            ((ದಶಮಾಂಶ *)pixels)[2] = v[2];
            ಆದರೆ (fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel == 16) {
                ((ದಶಮಾಂಶ *)pixels)[3] = v[3];
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            // Unknown array type
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    }
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_ರೇಖೀಯ,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_TonemapOperator op;

    ಒಕ್ಕೂಟ {
        ರಚನೆ {
            ದಶಮಾಂಶ scale;
        } ರೇಖೀಯ;

        ರಚನೆ {
            ದಶಮಾಂಶ a;
            ದಶಮಾಂಶ b;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *color_primaries_ಮಾತೃಕೆ;
        } chrome;

    } ದತ್ತಾಂಶ;

} SDL_TonemapContext;

ಸ್ಥಿರ ಶೂನ್ಯ Tonemap_ರೇಖೀಯ(ದಶಮಾಂಶ *r, ದಶಮಾಂಶ *g, ದಶಮಾಂಶ *b, ದಶಮಾಂಶ scale)
{
    *r *= scale;
    *g *= scale;
    *b *= scale;
}

/* This uses the same tonemapping algorithm developed by Google for Chrome:
 * https://colab.research.google.com/drive/1hI10nq6L6ru_UFvz7-f7xQaQp0qarz_K
 *
 * Essentially, you use the source headroom and the destination headroom
 * to calculate scaling factors:
 *  tonemap_a = (dst_headroom / (src_headroom * src_headroom));
 *  tonemap_b = (1.0f / dst_headroom);
 *
 * Then you normalize your source color by the HDR whitepoint,
 * and calculate a final scaling factor in BT.2020 colorspace.
 */
ಸ್ಥಿರ ಶೂನ್ಯ TonemapChrome(ದಶಮಾಂಶ *r, ದಶಮಾಂಶ *g, ದಶಮಾಂಶ *b, ದಶಮಾಂಶ tonemap_a, ದಶಮಾಂಶ tonemap_b)
{
    ದಶಮಾಂಶ v1 = *r;
    ದಶಮಾಂಶ v2 = *g;
    ದಶಮಾಂಶ v3 = *b;
    ದಶಮಾಂಶ vmax = SDL_max(v1, SDL_max(v2, v3));

    ಆದರೆ (vmax > 0.0f) {
        ದಶಮಾಂಶ scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        Tonemap_ರೇಖೀಯ(r, g, b, scale);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ApplyTonemap(SDL_TonemapContext *ctx, ದಶಮಾಂಶ *r, ದಶಮಾಂಶ *g, ದಶಮಾಂಶ *b)
{
    ಆಯ್ಕೆ (ctx->op) {
    ಸ್ಥಿತಿ SDL_TONEMAP_ರೇಖೀಯ:
        Tonemap_ರೇಖೀಯ(r, g, b, ctx->ದತ್ತಾಂಶ.ರೇಖೀಯ.scale);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TONEMAP_CHROME:
        ಆದರೆ (ctx->ದತ್ತಾಂಶ.chrome.color_primaries_ಮಾತೃಕೆ) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->ದತ್ತಾಂಶ.chrome.color_primaries_ಮಾತೃಕೆ);
        }
        TonemapChrome(r, g, b, ctx->ದತ್ತಾಂಶ.chrome.a, ctx->ದತ್ತಾಂಶ.chrome.b);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
ಶೂನ್ಯ SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ flags = info->flags;
    ಸ್ಥಿರಾಂಕ Uint32 modulateR = info->r;
    ಸ್ಥಿರಾಂಕ Uint32 modulateG = info->g;
    ಸ್ಥಿರಾಂಕ Uint32 modulateB = info->b;
    ಸ್ಥಿರಾಂಕ Uint32 modulateA = info->a;
    ದಶಮಾಂಶ srcR, srcG, srcB, srcA;
    ದಶಮಾಂಶ dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *src_pal = info->src_pal;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_ಕೋಷ್ಟಕ *palette_map = info->palette_map;
    ಪೂರ್ಣಾಂಕ srcbpp = src_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    ಪೂರ್ಣಾಂಕ dstbpp = dst_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *color_primaries_ಮಾತೃಕೆ = ಖಾಲಿ;
    ದಶಮಾಂಶ src_white_ಬಿಂದು;
    ದಶಮಾಂಶ dst_white_ಬಿಂದು;
    ದಶಮಾಂಶ dst_headroom;
    ದಶಮಾಂಶ src_headroom;
    SDL_TonemapContext tonemap;
    Uint32 ಕೊನೆಯ_pixel = 0;
    Uint8 ಕೊನೆಯ_ಸೂಚ್ಯಂಕ = 0;

    src_colorspace = info->src_surface->colorspace;
    dst_colorspace = info->dst_surface->colorspace;
    src_primaries = SDL_COLORSPACEPRIMARIES(src_colorspace);
    dst_primaries = SDL_COLORSPACEPRIMARIES(dst_colorspace);

    src_white_ಬಿಂದು = SDL_Get_Surface_SDRWhite_ಬಿಂದು(info->src_surface, src_colorspace);
    dst_white_ಬಿಂದು = SDL_Get_Surface_SDRWhite_ಬಿಂದು(info->dst_surface, dst_colorspace);
    src_headroom = SDL_GetSurfaceHDRHeadroom(info->src_surface, src_colorspace);
    dst_headroom = SDL_GetSurfaceHDRHeadroom(info->dst_surface, dst_colorspace);
    ಆದರೆ (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_ಗಣ_Float_Property(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    ಆದರೆ (src_headroom > dst_headroom) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ಖಾಲಿ);
        ಆದರೆ (tonemap_operator) {
            ಆದರೆ (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_ರೇಖೀಯ;
                tonemap.ದತ್ತಾಂಶ.ರೇಖೀಯ.scale = (ದಶಮಾಂಶ)SDL_atof(tonemap_operator + 2);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        ಆದರೆ (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.ದತ್ತಾಂಶ.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.ದತ್ತಾಂಶ.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.ದತ್ತಾಂಶ.chrome.color_primaries_ಮಾತೃಕೆ = SDL_Get_Color_Primaries_Conversion_ಮಾತೃಕೆ(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            ಆದರೆ (tonemap.ದತ್ತಾಂಶ.chrome.color_primaries_ಮಾತೃಕೆ) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    ಆದರೆ (src_primaries != dst_primaries) {
        color_primaries_ಮಾತೃಕೆ = SDL_Get_Color_Primaries_Conversion_ಮಾತೃಕೆ(src_primaries, dst_primaries);
    }

    src_access = Get_Pixel_Access_ವಿಧಾನ(src_fmt->format);
    dst_access = Get_Pixel_Access_ವಿಧಾನ(dst_fmt->format);
    ಆದರೆ (dst_access == SlowBlitPixelAccess_Index8) {
        ಕೊನೆಯ_ಸೂಚ್ಯಂಕ = SDL_LookupRGBAColor(palette_map, ಕೊನೆಯ_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    ಆಗ (info->dst_h--) {
        Uint8 *src = ಖಾಲಿ;
        Uint8 *dst = info->dst;
        ಪೂರ್ಣಾಂಕ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ಆಗ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_ಬಿಂದು, &srcR, &srcG, &srcB, &srcA);

            ಆದರೆ (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            ಆದರೆ (color_primaries_ಮಾತೃಕೆ) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_ಮಾತೃಕೆ);
            }

            ಆದರೆ (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            ಆದರೆ ((flags & (SDL_COPY_BLEND | SDL_COPY_ಕೂಡಿಸು | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_ಬಿಂದು, &dstR, &dstG, &dstB, &dstA);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            ಆದರೆ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ಆದರೆ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ಆದರೆ (flags & (SDL_COPY_BLEND | SDL_COPY_ಕೂಡಿಸು)) {
                ಆದರೆ (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            ಆಯ್ಕೆ (flags & (SDL_COPY_BLEND | SDL_COPY_ಕೂಡಿಸು | SDL_COPY_MOD | SDL_COPY_MUL)) {
            ಸ್ಥಿತಿ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_ಕೂಡಿಸು:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_ರೇಖೀಯ(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_ರೇಖೀಯ(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_ರೇಖೀಯ(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                ಆದರೆ (dstpixel != ಕೊನೆಯ_pixel) {
                    ಕೊನೆಯ_pixel = dstpixel;
                    ಕೊನೆಯ_ಸೂಚ್ಯಂಕ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = ಕೊನೆಯ_ಸೂಚ್ಯಂಕ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_ಬಿಂದು, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


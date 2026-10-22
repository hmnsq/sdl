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

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

ಸ್ಥಿರ SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    ಯದಿ (SDL_BYTESPERPIXEL(format) > 4) {
        ಪ್ರತ್ಯಾಗಮ SlowBlitPixelAccess_Large;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_10BIT(format)) {
        ಪ್ರತ್ಯಾಗಮ SlowBlitPixelAccess_10Bit;
    } ಅನ್ಯಥಾ ಯದಿ (format == SDL_PIXELFORMAT_INDEX8) {
        ಪ್ರತ್ಯಾಗಮ SlowBlitPixelAccess_Index8;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_ISPIXELFORMAT_ALPHA(format)) {
        ಪ್ರತ್ಯಾಗಮ SlowBlitPixelAccess_RGBA;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
ಶೂನ್ಯ SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ flags = info->flags;
    ಧ್ರುವ Uint32 modulateR = info->r;
    ಧ್ರುವ Uint32 modulateG = info->g;
    ಧ್ರುವ Uint32 modulateB = info->b;
    ಧ್ರುವ Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ಧ್ರುವ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ಧ್ರುವ SDL_Palette *src_pal = info->src_pal;
    ಧ್ರುವ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ಧ್ರುವ SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    ಪೂರ್ಣಾಙ್ಕ srcbpp = src_fmt->bytes_per_pixel;
    ಪೂರ್ಣಾಙ್ಕ dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    ಯದಿ (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    ಯಾವತ್ (info->dst_h--) {
        Uint8 *src = ರಿಕ್ತ;
        Uint8 *dst = info->dst;
        ಪೂರ್ಣಾಙ್ಕ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ಯಾವತ್ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ವಿಕಲ್ಪ (src_access) {
            ಪಕ್ಷ SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                ವಿಕಲ್ಪ (src_fmt->format) {
                ಪಕ್ಷ SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ಭಙ್ಗ;
                ಪಕ್ಷ SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ಭಙ್ಗ;
                ಪಕ್ಷ SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ಭಙ್ಗ;
                ಪಕ್ಷ SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ಭಙ್ಗ;
                ಸ್ವಭಾವ:
                    ಭಙ್ಗ;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ಭಙ್ಗ;
            }

            ಯದಿ (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                ಯದಿ (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                ಯದಿ ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    ಅನುವರ್ತ;
                }
            }
            ಯದಿ (flags & SDL_COPY_BLEND_MASK) {
                ವಿಕಲ್ಪ (dst_access) {
                ಪಕ್ಷ SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    ಭಙ್ಗ;
                ಪಕ್ಷ SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    ಭಙ್ಗ;
                ಪಕ್ಷ SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    ಭಙ್ಗ;
                ಪಕ್ಷ SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    ವಿಕಲ್ಪ (dst_fmt->format) {
                    ಪಕ್ಷ SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ಭಙ್ಗ;
                    ಪಕ್ಷ SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ಭಙ್ಗ;
                    ಪಕ್ಷ SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ಭಙ್ಗ;
                    ಪಕ್ಷ SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ಭಙ್ಗ;
                    ಸ್ವಭಾವ:
                        ಭಙ್ಗ;
                    }
                    ಭಙ್ಗ;
                ಪಕ್ಷ SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    ಭಙ್ಗ;
                }
            } ಅನ್ಯಥಾ {
                // don't care
            }

            ಯದಿ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ಯದಿ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ಯದಿ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                ಯದಿ (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            ವಿಕಲ್ಪ (flags & SDL_COPY_BLEND_MASK) {
            ಪಕ್ಷ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                ಯದಿ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                ಯದಿ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                ಯದಿ (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ಯದಿ (dstA > 255) {
                    dstA = 255;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_ADD:
            ಪಕ್ಷ SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                ಯದಿ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                ಯದಿ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                ಯದಿ (dstB > 255) {
                    dstB = 255;
                }
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                ಯದಿ (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                ಯದಿ (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                ಯದಿ (dstB > 255) {
                    dstB = 255;
                }
                ಭಙ್ಗ;
            }

            ವಿಕಲ್ಪ (dst_access) {
            ಪಕ್ಷ SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                ಯದಿ (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                ಭಙ್ಗ;
            ಪಕ್ಷ SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                ವಿಕಲ್ಪ (dst_fmt->format) {
                ಪಕ್ಷ SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ಪಕ್ಷ SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ಭಙ್ಗ;
                ಪಕ್ಷ SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ಪಕ್ಷ SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ಭಙ್ಗ;
                ಸ್ವಭಾವ:
                    pixelvalue = 0;
                    ಭಙ್ಗ;
                }
                *(Uint32 *)dst = pixelvalue;
                ಭಙ್ಗ;
            }
            ಪಕ್ಷ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ಭಙ್ಗ;
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
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಙ್ಘ
{
    Uint32 u;
    ಭಿನ್ನ f;
    ಸಂರಚನಾ
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(ತಳ್ಳು)
#pragma warning(disable:4214)
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಙ್ಘ
{
    Uint16 u;
    ಸಂರಚನಾ
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(ತೆಗೆ)
#endif

ಸ್ಥಿರ ಭಿನ್ನ half_to_float(Uint16 un_ಮೌಲ್ಯ)
{
    ಸ್ಥಿರ ಧ್ರುವ FP32 magic = { (254 - 15) << 23 };
    ಸ್ಥಿರ ಧ್ರುವ FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_ಮೌಲ್ಯ;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    ಯದಿ (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    ಪ್ರತ್ಯಾಗಮ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
ಸ್ಥಿರ Uint16 float_to_half(ಭಿನ್ನ a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, ಪರಿಮಾಣ(ia));

    ir = (ia >> 16) & 0x8000;
    ಯದಿ ((ia & 0x7f800000) == 0x7f800000) {
        ಯದಿ ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } ಅನ್ಯಥಾ {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } ಅನ್ಯಥಾ ಯದಿ ((ia & 0x7f800000) >= 0x33000000) {
        ಪೂರ್ಣಾಙ್ಕ shift = (ಪೂರ್ಣಾಙ್ಕ)((ia >> 23) & 0xff) - 127;
        ಯದಿ (shift > 15) {
            ir |= 0x7c00; // infinity
        } ಅನ್ಯಥಾ {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            ಯದಿ (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } ಅನ್ಯಥಾ { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            ಯದಿ ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ ir;
}

ಸ್ಥಿರ ಶೂನ್ಯ ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ಧ್ರುವ SDL_PixelFormatDetails *fmt, ಧ್ರುವ SDL_Palette *pal, SDL_Colorspace colorspace, ಭಿನ್ನ SDR_white_point,
                           ಭಿನ್ನ *outR, ಭಿನ್ನ *outG, ಭಿನ್ನ *outB, ಭಿನ್ನ *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    ಭಿನ್ನ fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    ಭಿನ್ನ v[4];

    ವಿಕಲ್ಪ (access) {
    ಪಕ್ಷ SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (ಭಿನ್ನ)pal->colors[pixelvalue].r / 255.0f;
        fG = (ಭಿನ್ನ)pal->colors[pixelvalue].g / 255.0f;
        fB = (ಭಿನ್ನ)pal->colors[pixelvalue].b / 255.0f;
        fA = (ಭಿನ್ನ)pal->colors[pixelvalue].a / 255.0f;
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (ಭಿನ್ನ)R / 255.0f;
        fG = (ಭಿನ್ನ)G / 255.0f;
        fB = (ಭಿನ್ನ)B / 255.0f;
        fA = 1.0f;
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (ಭಿನ್ನ)R / 255.0f;
        fG = (ಭಿನ್ನ)G / 255.0f;
        fB = (ಭಿನ್ನ)B / 255.0f;
        fA = (ಭಿನ್ನ)A / 255.0f;
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        ವಿಕಲ್ಪ (fmt->format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            fR = fG = fB = fA = 0.0f;
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_Large:
        ವಿಕಲ್ಪ (SDL_PIXELTYPE(fmt->format)) {
        ಪಕ್ಷ SDL_PIXELTYPE_ARRAYU16:
            v[0] = (ಭಿನ್ನ)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (ಭಿನ್ನ)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (ಭಿನ್ನ)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            ಯದಿ (fmt->bytes_per_pixel == 8) {
                v[3] = (ಭಿನ್ನ)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } ಅನ್ಯಥಾ {
                v[3] = 1.0f;
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            ಯದಿ (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } ಅನ್ಯಥಾ {
                v[3] = 1.0f;
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((ಭಿನ್ನ *)pixels)[0];
            v[1] = ((ಭಿನ್ನ *)pixels)[1];
            v[2] = ((ಭಿನ್ನ *)pixels)[2];
            ಯದಿ (fmt->bytes_per_pixel == 16) {
                v[3] = ((ಭಿನ್ನ *)pixels)[3];
            } ಅನ್ಯಥಾ {
                v[3] = 1.0f;
            }
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ಭಙ್ಗ;
        }
        ವಿಕಲ್ಪ (SDL_PIXELORDER(fmt->format)) {
        ಪಕ್ಷ SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    ವಿಕಲ್ಪ (SDL_COLORSPACETRANSFER(colorspace)) {
    ಪಕ್ಷ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        // Unknown, leave it alone
        ಭಙ್ಗ;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

ಸ್ಥಿರ ಶೂನ್ಯ WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ಧ್ರುವ SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, ಭಿನ್ನ SDR_white_point,
                            ಭಿನ್ನ fR, ಭಿನ್ನ fG, ಭಿನ್ನ fB, ಭಿನ್ನ fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    ಭಿನ್ನ v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    ವಿಕಲ್ಪ (SDL_COLORSPACETRANSFER(colorspace)) {
    ಪಕ್ಷ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        // Unknown, leave it alone
        ಭಙ್ಗ;
    }

    ವಿಕಲ್ಪ (access) {
    ಪಕ್ಷ SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        ಭಙ್ಗ;
    ಪಕ್ಷ SlowBlitPixelAccess_10Bit:
    {
        ವಿಕಲ್ಪ (fmt->format) {
        ಪಕ್ಷ SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ಪಕ್ಷ SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ಪಕ್ಷ SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            pixelvalue = 0;
            ಭಙ್ಗ;
        }
        *(Uint32 *)pixels = pixelvalue;
        ಭಙ್ಗ;
    }
    ಪಕ್ಷ SlowBlitPixelAccess_Large:
        ವಿಕಲ್ಪ (SDL_PIXELORDER(fmt->format)) {
        ಪಕ್ಷ SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ಭಙ್ಗ;
        }
        ವಿಕಲ್ಪ (SDL_PIXELTYPE(fmt->format)) {
        ಪಕ್ಷ SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ಯದಿ (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            ಯದಿ (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_PIXELTYPE_ARRAYF32:
            ((ಭಿನ್ನ *)pixels)[0] = v[0];
            ((ಭಿನ್ನ *)pixels)[1] = v[1];
            ((ಭಿನ್ನ *)pixels)[2] = v[2];
            ಯದಿ (fmt->bytes_per_pixel == 16) {
                ((ಭಿನ್ನ *)pixels)[3] = v[3];
            }
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            // Unknown array type
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;
    }
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    SDL_TonemapOperator op;

    ಸಙ್ಘ {
        ಸಂರಚನಾ {
            ಭಿನ್ನ scale;
        } linear;

        ಸಂರಚನಾ {
            ಭಿನ್ನ a;
            ಭಿನ್ನ b;
            ಧ್ರುವ ಭಿನ್ನ *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

ಸ್ಥಿರ ಶೂನ್ಯ TonemapLinear(ಭಿನ್ನ *r, ಭಿನ್ನ *g, ಭಿನ್ನ *b, ಭಿನ್ನ scale)
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
ಸ್ಥಿರ ಶೂನ್ಯ TonemapChrome(ಭಿನ್ನ *r, ಭಿನ್ನ *g, ಭಿನ್ನ *b, ಭಿನ್ನ tonemap_a, ಭಿನ್ನ tonemap_b)
{
    ಭಿನ್ನ v1 = *r;
    ಭಿನ್ನ v2 = *g;
    ಭಿನ್ನ v3 = *b;
    ಭಿನ್ನ vmax = SDL_max(v1, SDL_max(v2, v3));

    ಯದಿ (vmax > 0.0f) {
        ಭಿನ್ನ scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ApplyTonemap(SDL_TonemapContext *ctx, ಭಿನ್ನ *r, ಭಿನ್ನ *g, ಭಿನ್ನ *b)
{
    ವಿಕಲ್ಪ (ctx->op) {
    ಪಕ್ಷ SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TONEMAP_CHROME:
        ಯದಿ (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
ಶೂನ್ಯ SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ flags = info->flags;
    ಧ್ರುವ Uint32 modulateR = info->r;
    ಧ್ರುವ Uint32 modulateG = info->g;
    ಧ್ರುವ Uint32 modulateB = info->b;
    ಧ್ರುವ Uint32 modulateA = info->a;
    ಭಿನ್ನ srcR, srcG, srcB, srcA;
    ಭಿನ್ನ dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ಧ್ರುವ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ಧ್ರುವ SDL_Palette *src_pal = info->src_pal;
    ಧ್ರುವ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ಧ್ರುವ SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    ಪೂರ್ಣಾಙ್ಕ srcbpp = src_fmt->bytes_per_pixel;
    ಪೂರ್ಣಾಙ್ಕ dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ಧ್ರುವ ಭಿನ್ನ *color_primaries_matrix = ರಿಕ್ತ;
    ಭಿನ್ನ src_white_point;
    ಭಿನ್ನ dst_white_point;
    ಭಿನ್ನ dst_headroom;
    ಭಿನ್ನ src_headroom;
    SDL_TonemapContext tonemap;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_colorspace = info->src_surface->colorspace;
    dst_colorspace = info->dst_surface->colorspace;
    src_primaries = SDL_COLORSPACEPRIMARIES(src_colorspace);
    dst_primaries = SDL_COLORSPACEPRIMARIES(dst_colorspace);

    src_white_point = SDL_GetSurfaceSDRWhitePoint(info->src_surface, src_colorspace);
    dst_white_point = SDL_GetSurfaceSDRWhitePoint(info->dst_surface, dst_colorspace);
    src_headroom = SDL_GetSurfaceHDRHeadroom(info->src_surface, src_colorspace);
    dst_headroom = SDL_GetSurfaceHDRHeadroom(info->dst_surface, dst_colorspace);
    ಯದಿ (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    ಯದಿ (src_headroom > dst_headroom) {
        ಧ್ರುವ ವರ್ಣ *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ರಿಕ್ತ);
        ಯದಿ (tonemap_operator) {
            ಯದಿ (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (ಭಿನ್ನ)SDL_atof(tonemap_operator + 2);
            } ಅನ್ಯಥಾ ಯದಿ (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } ಅನ್ಯಥಾ ಯದಿ (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } ಅನ್ಯಥಾ {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        ಯದಿ (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            ಯದಿ (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    ಯದಿ (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    ಯದಿ (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    ಯಾವತ್ (info->dst_h--) {
        Uint8 *src = ರಿಕ್ತ;
        Uint8 *dst = info->dst;
        ಪೂರ್ಣಾಙ್ಕ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ಯಾವತ್ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            ಯದಿ (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            ಯದಿ (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            ಯದಿ (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            ಯದಿ ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } ಅನ್ಯಥಾ {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            ಯದಿ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ಯದಿ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ಯದಿ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                ಯದಿ (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            ವಿಕಲ್ಪ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            ಪಕ್ಷ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                ಭಙ್ಗ;
            }

            ಯದಿ (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                ಯದಿ (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
            } ಅನ್ಯಥಾ {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


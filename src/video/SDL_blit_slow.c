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
#ضمن "SDL_internal.h"

#ضمن "SDL_surface_c.h"
#ضمن "SDL_blit_slow.h"
#ضمن "SDL_pixels_c.h"

تعريفنوع تعداد
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

ساكن SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    إذا (SDL_BYTESPERPIXEL(format) > 4) {
        أرجع SlowBlitPixelAccess_Large;
    } وإلا إذا (SDL_ISPIXELFORMAT_10BIT(format)) {
        أرجع SlowBlitPixelAccess_10Bit;
    } وإلا إذا (format == SDL_PIXELFORMAT_INDEX8) {
        أرجع SlowBlitPixelAccess_Index8;
    } وإلا إذا (SDL_ISPIXELFORMAT_ALPHA(format)) {
        أرجع SlowBlitPixelAccess_RGBA;
    } وإلا {
        أرجع SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
فراغ SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ثابت صحيح flags = info->flags;
    ثابت Uint32 modulateR = info->r;
    ثابت Uint32 modulateG = info->g;
    ثابت Uint32 modulateB = info->b;
    ثابت Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ثابت SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ثابت SDL_Palette *src_pal = info->src_pal;
    ثابت SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ثابت SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    صحيح srcbpp = src_fmt->bytes_per_pixel;
    صحيح dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    إذا (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    طالما (info->dst_h--) {
        Uint8 *src = عدم;
        Uint8 *dst = info->dst;
        صحيح n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        طالما (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            بدل (src_access) {
            حالة SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                اكسر;
            حالة SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                اكسر;
            حالة SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                اكسر;
            حالة SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                بدل (src_fmt->format) {
                حالة SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    اكسر;
                حالة SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    اكسر;
                حالة SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    اكسر;
                حالة SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    اكسر;
                افتراضي:
                    اكسر;
                }
                اكسر;
            حالة SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                اكسر;
            }

            إذا (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                إذا (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                إذا ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    استمر;
                }
            }
            إذا (flags & SDL_COPY_BLEND_MASK) {
                بدل (dst_access) {
                حالة SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    اكسر;
                حالة SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    اكسر;
                حالة SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    اكسر;
                حالة SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    بدل (dst_fmt->format) {
                    حالة SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        اكسر;
                    حالة SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        اكسر;
                    حالة SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        اكسر;
                    حالة SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        اكسر;
                    افتراضي:
                        اكسر;
                    }
                    اكسر;
                حالة SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    اكسر;
                }
            } وإلا {
                // don't care
            }

            إذا (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            إذا (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            إذا (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                إذا (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            بدل (flags & SDL_COPY_BLEND_MASK) {
            حالة 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                اكسر;
            حالة SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                اكسر;
            حالة SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                إذا (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                إذا (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                إذا (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                إذا (dstA > 255) {
                    dstA = 255;
                }
                اكسر;
            حالة SDL_COPY_ADD:
            حالة SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                إذا (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                إذا (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                إذا (dstB > 255) {
                    dstB = 255;
                }
                اكسر;
            حالة SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                اكسر;
            حالة SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                إذا (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                إذا (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                إذا (dstB > 255) {
                    dstB = 255;
                }
                اكسر;
            }

            بدل (dst_access) {
            حالة SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                إذا (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                اكسر;
            حالة SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                اكسر;
            حالة SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                اكسر;
            حالة SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                بدل (dst_fmt->format) {
                حالة SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                حالة SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    اكسر;
                حالة SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                حالة SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    اكسر;
                افتراضي:
                    pixelvalue = 0;
                    اكسر;
                }
                *(Uint32 *)dst = pixelvalue;
                اكسر;
            }
            حالة SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                اكسر;
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
تعريفنوع اتحاد
{
    Uint32 u;
    عائم f;
    بنية
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(ئىتتىرىش)
#pragma warning(disable:4214)
#endif

تعريفنوع اتحاد
{
    Uint16 u;
    بنية
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(چىقىرىش)
#endif

ساكن عائم half_to_float(Uint16 un_قىممەت)
{
    ساكن ثابت FP32 magic = { (254 - 15) << 23 };
    ساكن ثابت FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_قىممەت;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    إذا (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    أرجع o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
ساكن Uint16 float_to_half(عائم a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, حجم(ia));

    ir = (ia >> 16) & 0x8000;
    إذا ((ia & 0x7f800000) == 0x7f800000) {
        إذا ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } وإلا {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } وإلا إذا ((ia & 0x7f800000) >= 0x33000000) {
        صحيح shift = (صحيح)((ia >> 23) & 0xff) - 127;
        إذا (shift > 15) {
            ir |= 0x7c00; // infinity
        } وإلا {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            إذا (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } وإلا { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            إذا ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    أرجع ir;
}

ساكن فراغ ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ثابت SDL_PixelFormatDetails *fmt, ثابت SDL_Palette *pal, SDL_Colorspace colorspace, عائم SDR_white_point,
                           عائم *outR, عائم *outG, عائم *outB, عائم *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    عائم fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    عائم v[4];

    بدل (access) {
    حالة SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (عائم)pal->colors[pixelvalue].r / 255.0f;
        fG = (عائم)pal->colors[pixelvalue].g / 255.0f;
        fB = (عائم)pal->colors[pixelvalue].b / 255.0f;
        fA = (عائم)pal->colors[pixelvalue].a / 255.0f;
        اكسر;
    حالة SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (عائم)R / 255.0f;
        fG = (عائم)G / 255.0f;
        fB = (عائم)B / 255.0f;
        fA = 1.0f;
        اكسر;
    حالة SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (عائم)R / 255.0f;
        fG = (عائم)G / 255.0f;
        fB = (عائم)B / 255.0f;
        fA = (عائم)A / 255.0f;
        اكسر;
    حالة SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        بدل (fmt->format) {
        حالة SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            اكسر;
        حالة SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            اكسر;
        حالة SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            اكسر;
        حالة SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            اكسر;
        افتراضي:
            fR = fG = fB = fA = 0.0f;
            اكسر;
        }
        اكسر;
    حالة SlowBlitPixelAccess_Large:
        بدل (SDL_PIXELTYPE(fmt->format)) {
        حالة SDL_PIXELTYPE_ARRAYU16:
            v[0] = (عائم)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (عائم)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (عائم)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            إذا (fmt->bytes_per_pixel == 8) {
                v[3] = (عائم)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } وإلا {
                v[3] = 1.0f;
            }
            اكسر;
        حالة SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            إذا (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } وإلا {
                v[3] = 1.0f;
            }
            اكسر;
        حالة SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((عائم *)pixels)[0];
            v[1] = ((عائم *)pixels)[1];
            v[2] = ((عائم *)pixels)[2];
            إذا (fmt->bytes_per_pixel == 16) {
                v[3] = ((عائم *)pixels)[3];
            } وإلا {
                v[3] = 1.0f;
            }
            اكسر;
        افتراضي:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            اكسر;
        }
        بدل (SDL_PIXELORDER(fmt->format)) {
        حالة SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            اكسر;
        حالة SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            اكسر;
        حالة SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            اكسر;
        حالة SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            اكسر;
        حالة SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            اكسر;
        حالة SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            اكسر;
        افتراضي:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            اكسر;
        }
        اكسر;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    بدل (SDL_COLORSPACETRANSFER(colorspace)) {
    حالة SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        اكسر;
    حالة SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        اكسر;
    حالة SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        اكسر;
    افتراضي:
        // Unknown, leave it alone
        اكسر;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

ساكن فراغ WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ثابت SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, عائم SDR_white_point,
                            عائم fR, عائم fG, عائم fB, عائم fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    عائم v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    بدل (SDL_COLORSPACETRANSFER(colorspace)) {
    حالة SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        اكسر;
    حالة SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        اكسر;
    حالة SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        اكسر;
    افتراضي:
        // Unknown, leave it alone
        اكسر;
    }

    بدل (access) {
    حالة SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        اكسر;
    حالة SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        اكسر;
    حالة SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        اكسر;
    حالة SlowBlitPixelAccess_10Bit:
    {
        بدل (fmt->format) {
        حالة SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        حالة SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            اكسر;
        حالة SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        حالة SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            اكسر;
        افتراضي:
            pixelvalue = 0;
            اكسر;
        }
        *(Uint32 *)pixels = pixelvalue;
        اكسر;
    }
    حالة SlowBlitPixelAccess_Large:
        بدل (SDL_PIXELORDER(fmt->format)) {
        حالة SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            اكسر;
        حالة SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            اكسر;
        حالة SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            اكسر;
        حالة SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            اكسر;
        حالة SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            اكسر;
        حالة SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            اكسر;
        افتراضي:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            اكسر;
        }
        بدل (SDL_PIXELTYPE(fmt->format)) {
        حالة SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            إذا (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            اكسر;
        حالة SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            إذا (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            اكسر;
        حالة SDL_PIXELTYPE_ARRAYF32:
            ((عائم *)pixels)[0] = v[0];
            ((عائم *)pixels)[1] = v[1];
            ((عائم *)pixels)[2] = v[2];
            إذا (fmt->bytes_per_pixel == 16) {
                ((عائم *)pixels)[3] = v[3];
            }
            اكسر;
        افتراضي:
            // Unknown array type
            اكسر;
        }
        اكسر;
    }
}

تعريفنوع تعداد
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

تعريفنوع بنية
{
    SDL_TonemapOperator op;

    اتحاد {
        بنية {
            عائم scale;
        } linear;

        بنية {
            عائم a;
            عائم b;
            ثابت عائم *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

ساكن فراغ TonemapLinear(عائم *r, عائم *g, عائم *b, عائم scale)
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
ساكن فراغ TonemapChrome(عائم *r, عائم *g, عائم *b, عائم tonemap_a, عائم tonemap_b)
{
    عائم v1 = *r;
    عائم v2 = *g;
    عائم v3 = *b;
    عائم vmax = SDL_max(v1, SDL_max(v2, v3));

    إذا (vmax > 0.0f) {
        عائم scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

ساكن فراغ ApplyTonemap(SDL_TonemapContext *ctx, عائم *r, عائم *g, عائم *b)
{
    بدل (ctx->op) {
    حالة SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        اكسر;
    حالة SDL_TONEMAP_CHROME:
        إذا (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        اكسر;
    افتراضي:
        اكسر;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
فراغ SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ثابت صحيح flags = info->flags;
    ثابت Uint32 modulateR = info->r;
    ثابت Uint32 modulateG = info->g;
    ثابت Uint32 modulateB = info->b;
    ثابت Uint32 modulateA = info->a;
    عائم srcR, srcG, srcB, srcA;
    عائم dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ثابت SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ثابت SDL_Palette *src_pal = info->src_pal;
    ثابت SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ثابت SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    صحيح srcbpp = src_fmt->bytes_per_pixel;
    صحيح dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ثابت عائم *color_primaries_matrix = عدم;
    عائم src_white_point;
    عائم dst_white_point;
    عائم dst_headroom;
    عائم src_headroom;
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
    إذا (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    إذا (src_headroom > dst_headroom) {
        ثابت حرف *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, عدم);
        إذا (tonemap_operator) {
            إذا (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (عائم)SDL_atof(tonemap_operator + 2);
            } وإلا إذا (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } وإلا إذا (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } وإلا {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        إذا (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            إذا (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    إذا (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    إذا (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    طالما (info->dst_h--) {
        Uint8 *src = عدم;
        Uint8 *dst = info->dst;
        صحيح n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        طالما (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            إذا (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            إذا (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            إذا (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            إذا ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } وإلا {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            إذا (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            إذا (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            إذا (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                إذا (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            بدل (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            حالة 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                اكسر;
            حالة SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                اكسر;
            حالة SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                اكسر;
            حالة SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                اكسر;
            حالة SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                اكسر;
            }

            إذا (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                إذا (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
            } وإلا {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


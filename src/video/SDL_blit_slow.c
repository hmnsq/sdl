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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_surface_c.h"
#অন্তর্ভাব "SDL_blit_slow.h"
#অন্তর্ভাব "SDL_pixels_c.h"

প্রকারলেখ গণনা
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

স্থির SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    যদি (SDL_BYTESPERPIXEL(format) > 4) {
        ফেরত SlowBlitPixelAccess_Large;
    } অন্যথা যদি (SDL_ISPIXELFORMAT_10BIT(format)) {
        ফেরত SlowBlitPixelAccess_10Bit;
    } অন্যথা যদি (format == SDL_PIXELFORMAT_INDEX8) {
        ফেরত SlowBlitPixelAccess_Index8;
    } অন্যথা যদি (SDL_ISPIXELFORMAT_ALPHA(format)) {
        ফেরত SlowBlitPixelAccess_RGBA;
    } অন্যথা {
        ফেরত SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
শূন্য SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ধ্রুবক পূর্ণসংখ্যা flags = info->flags;
    ধ্রুবক Uint32 modulateR = info->r;
    ধ্রুবক Uint32 modulateG = info->g;
    ধ্রুবক Uint32 modulateB = info->b;
    ধ্রুবক Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ধ্রুবক SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ধ্রুবক SDL_Palette *src_pal = info->src_pal;
    ধ্রুবক SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ধ্রুবক SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    পূর্ণসংখ্যা srcbpp = src_fmt->bytes_per_pixel;
    পূর্ণসংখ্যা dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_সূচক = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    যদি (dst_access == SlowBlitPixelAccess_Index8) {
        last_সূচক = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    যখন (info->dst_h--) {
        Uint8 *src = ফাঁকা;
        Uint8 *dst = info->dst;
        পূর্ণসংখ্যা n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        যখন (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            নির্বাচন (src_access) {
            ক্ষেত্র SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                নির্বাচন (src_fmt->format) {
                ক্ষেত্র SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    বিরতি;
                ক্ষেত্র SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    বিরতি;
                ক্ষেত্র SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    বিরতি;
                ক্ষেত্র SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    বিরতি;
                পূর্বনির্ধারিত:
                    বিরতি;
                }
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                বিরতি;
            }

            যদি (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                যদি (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                যদি ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    চালু;
                }
            }
            যদি (flags & SDL_COPY_BLEND_MASK) {
                নির্বাচন (dst_access) {
                ক্ষেত্র SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    বিরতি;
                ক্ষেত্র SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    বিরতি;
                ক্ষেত্র SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    বিরতি;
                ক্ষেত্র SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    নির্বাচন (dst_fmt->format) {
                    ক্ষেত্র SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        বিরতি;
                    ক্ষেত্র SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        বিরতি;
                    ক্ষেত্র SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        বিরতি;
                    ক্ষেত্র SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        বিরতি;
                    পূর্বনির্ধারিত:
                        বিরতি;
                    }
                    বিরতি;
                ক্ষেত্র SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    বিরতি;
                }
            } অন্যথা {
                // don't care
            }

            যদি (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            যদি (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            যদি (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                যদি (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            নির্বাচন (flags & SDL_COPY_BLEND_MASK) {
            ক্ষেত্র 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                বিরতি;
            ক্ষেত্র SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                বিরতি;
            ক্ষেত্র SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                যদি (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                যদি (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                যদি (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                যদি (dstA > 255) {
                    dstA = 255;
                }
                বিরতি;
            ক্ষেত্র SDL_COPY_ADD:
            ক্ষেত্র SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                যদি (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                যদি (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                যদি (dstB > 255) {
                    dstB = 255;
                }
                বিরতি;
            ক্ষেত্র SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                বিরতি;
            ক্ষেত্র SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                যদি (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                যদি (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                যদি (dstB > 255) {
                    dstB = 255;
                }
                বিরতি;
            }

            নির্বাচন (dst_access) {
            ক্ষেত্র SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                যদি (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_সূচক = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_সূচক;
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                বিরতি;
            ক্ষেত্র SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                নির্বাচন (dst_fmt->format) {
                ক্ষেত্র SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ক্ষেত্র SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    বিরতি;
                ক্ষেত্র SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ক্ষেত্র SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    বিরতি;
                পূর্বনির্ধারিত:
                    pixelvalue = 0;
                    বিরতি;
                }
                *(Uint32 *)dst = pixelvalue;
                বিরতি;
            }
            ক্ষেত্র SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                বিরতি;
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
প্রকারলেখ সংঘ
{
    Uint32 u;
    দশমিক f;
    কাঠামো
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(ঠেলো)
#pragma warning(disable:4214)
#endif

প্রকারলেখ সংঘ
{
    Uint16 u;
    কাঠামো
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(বের_করো)
#endif

স্থির দশমিক half_to_float(Uint16 un_মান)
{
    স্থির ধ্রুবক FP32 magic = { (254 - 15) << 23 };
    স্থির ধ্রুবক FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_মান;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    যদি (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    ফেরত o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
স্থির Uint16 float_to_half(দশমিক a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, আকার(ia));

    ir = (ia >> 16) & 0x8000;
    যদি ((ia & 0x7f800000) == 0x7f800000) {
        যদি ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } অন্যথা {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } অন্যথা যদি ((ia & 0x7f800000) >= 0x33000000) {
        পূর্ণসংখ্যা shift = (পূর্ণসংখ্যা)((ia >> 23) & 0xff) - 127;
        যদি (shift > 15) {
            ir |= 0x7c00; // infinity
        } অন্যথা {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            যদি (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } অন্যথা { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            যদি ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    ফেরত ir;
}

স্থির শূন্য ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ধ্রুবক SDL_PixelFormatDetails *fmt, ধ্রুবক SDL_Palette *pal, SDL_Colorspace colorspace, দশমিক SDR_white_point,
                           দশমিক *outR, দশমিক *outG, দশমিক *outB, দশমিক *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    দশমিক fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    দশমিক v[4];

    নির্বাচন (access) {
    ক্ষেত্র SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (দশমিক)pal->colors[pixelvalue].r / 255.0f;
        fG = (দশমিক)pal->colors[pixelvalue].g / 255.0f;
        fB = (দশমিক)pal->colors[pixelvalue].b / 255.0f;
        fA = (দশমিক)pal->colors[pixelvalue].a / 255.0f;
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (দশমিক)R / 255.0f;
        fG = (দশমিক)G / 255.0f;
        fB = (দশমিক)B / 255.0f;
        fA = 1.0f;
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (দশমিক)R / 255.0f;
        fG = (দশমিক)G / 255.0f;
        fB = (দশমিক)B / 255.0f;
        fA = (দশমিক)A / 255.0f;
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        নির্বাচন (fmt->format) {
        ক্ষেত্র SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            বিরতি;
        ক্ষেত্র SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            বিরতি;
        ক্ষেত্র SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            বিরতি;
        ক্ষেত্র SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            বিরতি;
        পূর্বনির্ধারিত:
            fR = fG = fB = fA = 0.0f;
            বিরতি;
        }
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_Large:
        নির্বাচন (SDL_PIXELTYPE(fmt->format)) {
        ক্ষেত্র SDL_PIXELTYPE_ARRAYU16:
            v[0] = (দশমিক)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (দশমিক)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (দশমিক)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            যদি (fmt->bytes_per_pixel == 8) {
                v[3] = (দশমিক)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } অন্যথা {
                v[3] = 1.0f;
            }
            বিরতি;
        ক্ষেত্র SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            যদি (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } অন্যথা {
                v[3] = 1.0f;
            }
            বিরতি;
        ক্ষেত্র SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((দশমিক *)pixels)[0];
            v[1] = ((দশমিক *)pixels)[1];
            v[2] = ((দশমিক *)pixels)[2];
            যদি (fmt->bytes_per_pixel == 16) {
                v[3] = ((দশমিক *)pixels)[3];
            } অন্যথা {
                v[3] = 1.0f;
            }
            বিরতি;
        পূর্বনির্ধারিত:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            বিরতি;
        }
        নির্বাচন (SDL_PIXELORDER(fmt->format)) {
        ক্ষেত্র SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            বিরতি;
        পূর্বনির্ধারিত:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            বিরতি;
        }
        বিরতি;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    নির্বাচন (SDL_COLORSPACETRANSFER(colorspace)) {
    ক্ষেত্র SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        বিরতি;
    ক্ষেত্র SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        বিরতি;
    ক্ষেত্র SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        বিরতি;
    পূর্বনির্ধারিত:
        // Unknown, leave it alone
        বিরতি;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

স্থির শূন্য WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ধ্রুবক SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, দশমিক SDR_white_point,
                            দশমিক fR, দশমিক fG, দশমিক fB, দশমিক fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    দশমিক v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    নির্বাচন (SDL_COLORSPACETRANSFER(colorspace)) {
    ক্ষেত্র SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        বিরতি;
    ক্ষেত্র SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        বিরতি;
    ক্ষেত্র SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        বিরতি;
    পূর্বনির্ধারিত:
        // Unknown, leave it alone
        বিরতি;
    }

    নির্বাচন (access) {
    ক্ষেত্র SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        বিরতি;
    ক্ষেত্র SlowBlitPixelAccess_10Bit:
    {
        নির্বাচন (fmt->format) {
        ক্ষেত্র SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ক্ষেত্র SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            বিরতি;
        ক্ষেত্র SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ক্ষেত্র SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            বিরতি;
        পূর্বনির্ধারিত:
            pixelvalue = 0;
            বিরতি;
        }
        *(Uint32 *)pixels = pixelvalue;
        বিরতি;
    }
    ক্ষেত্র SlowBlitPixelAccess_Large:
        নির্বাচন (SDL_PIXELORDER(fmt->format)) {
        ক্ষেত্র SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            বিরতি;
        ক্ষেত্র SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            বিরতি;
        পূর্বনির্ধারিত:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            বিরতি;
        }
        নির্বাচন (SDL_PIXELTYPE(fmt->format)) {
        ক্ষেত্র SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            যদি (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            বিরতি;
        ক্ষেত্র SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            যদি (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            বিরতি;
        ক্ষেত্র SDL_PIXELTYPE_ARRAYF32:
            ((দশমিক *)pixels)[0] = v[0];
            ((দশমিক *)pixels)[1] = v[1];
            ((দশমিক *)pixels)[2] = v[2];
            যদি (fmt->bytes_per_pixel == 16) {
                ((দশমিক *)pixels)[3] = v[3];
            }
            বিরতি;
        পূর্বনির্ধারিত:
            // Unknown array type
            বিরতি;
        }
        বিরতি;
    }
}

প্রকারলেখ গণনা
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

প্রকারলেখ কাঠামো
{
    SDL_TonemapOperator op;

    সংঘ {
        কাঠামো {
            দশমিক scale;
        } linear;

        কাঠামো {
            দশমিক a;
            দশমিক b;
            ধ্রুবক দশমিক *color_primaries_matrix;
        } chrome;

    } তথ্য;

} SDL_TonemapContext;

স্থির শূন্য TonemapLinear(দশমিক *r, দশমিক *g, দশমিক *b, দশমিক scale)
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
স্থির শূন্য TonemapChrome(দশমিক *r, দশমিক *g, দশমিক *b, দশমিক tonemap_a, দশমিক tonemap_b)
{
    দশমিক v1 = *r;
    দশমিক v2 = *g;
    দশমিক v3 = *b;
    দশমিক vmax = SDL_max(v1, SDL_max(v2, v3));

    যদি (vmax > 0.0f) {
        দশমিক scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

স্থির শূন্য ApplyTonemap(SDL_TonemapContext *ctx, দশমিক *r, দশমিক *g, দশমিক *b)
{
    নির্বাচন (ctx->op) {
    ক্ষেত্র SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->তথ্য.linear.scale);
        বিরতি;
    ক্ষেত্র SDL_TONEMAP_CHROME:
        যদি (ctx->তথ্য.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->তথ্য.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->তথ্য.chrome.a, ctx->তথ্য.chrome.b);
        বিরতি;
    পূর্বনির্ধারিত:
        বিরতি;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
শূন্য SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ধ্রুবক পূর্ণসংখ্যা flags = info->flags;
    ধ্রুবক Uint32 modulateR = info->r;
    ধ্রুবক Uint32 modulateG = info->g;
    ধ্রুবক Uint32 modulateB = info->b;
    ধ্রুবক Uint32 modulateA = info->a;
    দশমিক srcR, srcG, srcB, srcA;
    দশমিক dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ধ্রুবক SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ধ্রুবক SDL_Palette *src_pal = info->src_pal;
    ধ্রুবক SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ধ্রুবক SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    পূর্ণসংখ্যা srcbpp = src_fmt->bytes_per_pixel;
    পূর্ণসংখ্যা dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ধ্রুবক দশমিক *color_primaries_matrix = ফাঁকা;
    দশমিক src_white_point;
    দশমিক dst_white_point;
    দশমিক dst_headroom;
    দশমিক src_headroom;
    SDL_TonemapContext tonemap;
    Uint32 last_pixel = 0;
    Uint8 last_সূচক = 0;

    src_colorspace = info->src_surface->colorspace;
    dst_colorspace = info->dst_surface->colorspace;
    src_primaries = SDL_COLORSPACEPRIMARIES(src_colorspace);
    dst_primaries = SDL_COLORSPACEPRIMARIES(dst_colorspace);

    src_white_point = SDL_GetSurfaceSDRWhitePoint(info->src_surface, src_colorspace);
    dst_white_point = SDL_GetSurfaceSDRWhitePoint(info->dst_surface, dst_colorspace);
    src_headroom = SDL_GetSurfaceHDRHeadroom(info->src_surface, src_colorspace);
    dst_headroom = SDL_GetSurfaceHDRHeadroom(info->dst_surface, dst_colorspace);
    যদি (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    যদি (src_headroom > dst_headroom) {
        ধ্রুবক অক্ষর *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ফাঁকা);
        যদি (tonemap_operator) {
            যদি (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.তথ্য.linear.scale = (দশমিক)SDL_atof(tonemap_operator + 2);
            } অন্যথা যদি (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } অন্যথা যদি (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } অন্যথা {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        যদি (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.তথ্য.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.তথ্য.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.তথ্য.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            যদি (tonemap.তথ্য.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    যদি (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    যদি (dst_access == SlowBlitPixelAccess_Index8) {
        last_সূচক = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    যখন (info->dst_h--) {
        Uint8 *src = ফাঁকা;
        Uint8 *dst = info->dst;
        পূর্ণসংখ্যা n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        যখন (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            যদি (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            যদি (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            যদি (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            যদি ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } অন্যথা {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            যদি (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            যদি (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            যদি (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                যদি (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            নির্বাচন (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            ক্ষেত্র 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                বিরতি;
            ক্ষেত্র SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                বিরতি;
            ক্ষেত্র SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                বিরতি;
            ক্ষেত্র SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                বিরতি;
            ক্ষেত্র SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                বিরতি;
            }

            যদি (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                যদি (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_সূচক = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_সূচক;
            } অন্যথা {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


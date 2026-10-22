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
#شامل "SDL_internal.h"

#شامل "SDL_surface_c.h"
#شامل "SDL_blit_slow.h"
#شامل "SDL_pixels_c.h"

قسمتعریف شمار
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

ساکن SlowBlitPixelAccess Get_Pixel_Access_طریقہ(SDL_PixelFormat format)
{
    اگر (SDL_BYTESPERPIXEL(format) > 4) {
        واپس SlowBlitPixelAccess_Large;
    } ورنہ اگر (SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(format)) {
        واپس Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ;
    } ورنہ اگر (format == SDL_PIXELFORMAT_INDEX8) {
        واپس SlowBlitPixelAccess_Index8;
    } ورنہ اگر (SDL_ISPIXELFORMAT_ALPHA(format)) {
        واپس SlowBlitPixelAccess_RGBA;
    } ورنہ {
        واپس SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
خالی SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ثابت صحیح flags = info->flags;
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
    SDL_Hash_جدول *palette_map = info->palette_map;
    صحیح srcbpp = src_fmt->بائٹیں_فی_pixel;
    صحیح dstbpp = dst_fmt->بائٹیں_فی_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 آخری_pixel = 0;
    Uint8 آخری_اشاریہ = 0;

    src_access = Get_Pixel_Access_طریقہ(src_fmt->format);
    dst_access = Get_Pixel_Access_طریقہ(dst_fmt->format);
    اگر (dst_access == SlowBlitPixelAccess_Index8) {
        آخری_اشاریہ = SDL_LookupRGBAColor(palette_map, آخری_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    جب (info->dst_h--) {
        Uint8 *src = تہی;
        Uint8 *dst = info->dst;
        صحیح n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        جب (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            انتخاب (src_access) {
            حالت SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                توڑو;
            حالت SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                توڑو;
            حالت SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                توڑو;
            حالت Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ:
                srcpixel = *((Uint32 *)(src));
                انتخاب (src_fmt->format) {
                حالت SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    توڑو;
                حالت SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    توڑو;
                حالت SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    توڑو;
                حالت SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    توڑو;
                طےشدہ:
                    توڑو;
                }
                توڑو;
            حالت SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                توڑو;
            }

            اگر (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                اگر (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                اگر ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    جاری;
                }
            }
            اگر (flags & SDL_COPY_BLEND_نقاب) {
                انتخاب (dst_access) {
                حالت SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    توڑو;
                حالت SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    توڑو;
                حالت SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    توڑو;
                حالت Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ:
                    dstpixel = *((Uint32 *)(dst));
                    انتخاب (dst_fmt->format) {
                    حالت SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        توڑو;
                    حالت SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        توڑو;
                    حالت SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        توڑو;
                    حالت SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        توڑو;
                    طےشدہ:
                        توڑو;
                    }
                    توڑو;
                حالت SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    توڑو;
                }
            } ورنہ {
                // don't care
            }

            اگر (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            اگر (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            اگر (flags & (SDL_COPY_BLEND | SDL_COPY_جوڑو)) {
                اگر (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            انتخاب (flags & SDL_COPY_BLEND_نقاب) {
            حالت 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                توڑو;
            حالت SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                توڑو;
            حالت SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                اگر (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                اگر (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                اگر (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                اگر (dstA > 255) {
                    dstA = 255;
                }
                توڑو;
            حالت SDL_COPY_جوڑو:
            حالت SDL_COPY_جوڑو_PREMULTIPLIED:
                dstR = srcR + dstR;
                اگر (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                اگر (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                اگر (dstB > 255) {
                    dstB = 255;
                }
                توڑو;
            حالت SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                توڑو;
            حالت SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                اگر (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                اگر (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                اگر (dstB > 255) {
                    dstB = 255;
                }
                توڑو;
            }

            انتخاب (dst_access) {
            حالت SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                اگر (dstpixel != آخری_pixel) {
                    آخری_pixel = dstpixel;
                    آخری_اشاریہ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = آخری_اشاریہ;
                توڑو;
            حالت SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                توڑو;
            حالت SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                توڑو;
            حالت Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ:
            {
                Uint32 pixelvalue;
                انتخاب (dst_fmt->format) {
                حالت SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                حالت SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    توڑو;
                حالت SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                حالت SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    توڑو;
                طےشدہ:
                    pixelvalue = 0;
                    توڑو;
                }
                *(Uint32 *)dst = pixelvalue;
                توڑو;
            }
            حالت SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                توڑو;
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
قسمتعریف اتحاد
{
    Uint32 u;
    اعشاری f;
    ساخت
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning(ڈالو)
#ہدایت warning(disable:4214)
#اگر_ختم

قسمتعریف اتحاد
{
    Uint16 u;
    ساخت
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning(نکالو)
#اگر_ختم

ساکن اعشاری half_مقصد_float(Uint16 un_قدر)
{
    ساکن ثابت FP32 magic = { (254 - 15) << 23 };
    ساکن ثابت FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_قدر;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    اگر (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    واپس o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
ساکن Uint16 float_مقصد_half(اعشاری a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, حجم(ia));

    ir = (ia >> 16) & 0x8000;
    اگر ((ia & 0x7f800000) == 0x7f800000) {
        اگر ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } ورنہ {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } ورنہ اگر ((ia & 0x7f800000) >= 0x33000000) {
        صحیح سرکاؤ = (صحیح)((ia >> 23) & 0xff) - 127;
        اگر (سرکاؤ > 15) {
            ir |= 0x7c00; // infinity
        } ورنہ {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            اگر (سرکاؤ < -14) { // denormal
                ir |= ia >> (-1 - سرکاؤ);
                ia = ia << (32 - (-1 - سرکاؤ));
            } ورنہ { //معمول
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + سرکاؤ) << 10);
            }
            // IEEE-754 round to nearest of even
            اگر ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    واپس ir;
}

ساکن خالی ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ثابت SDL_PixelFormatDetails *fmt, ثابت SDL_Palette *pal, SDL_Colorspace colorspace, اعشاری SDR_white_نقطہ,
                           اعشاری *برآمد_R, اعشاری *برآمد_G, اعشاری *برآمد_B, اعشاری *برآمد_A)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    اعشاری fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    اعشاری v[4];

    انتخاب (access) {
    حالت SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (اعشاری)pal->colors[pixelvalue].r / 255.0f;
        fG = (اعشاری)pal->colors[pixelvalue].g / 255.0f;
        fB = (اعشاری)pal->colors[pixelvalue].b / 255.0f;
        fA = (اعشاری)pal->colors[pixelvalue].a / 255.0f;
        توڑو;
    حالت SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->بائٹیں_فی_pixel, fmt, pixelvalue, R, G, B);
        fR = (اعشاری)R / 255.0f;
        fG = (اعشاری)G / 255.0f;
        fB = (اعشاری)B / 255.0f;
        fA = 1.0f;
        توڑو;
    حالت SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->بائٹیں_فی_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (اعشاری)R / 255.0f;
        fG = (اعشاری)G / 255.0f;
        fB = (اعشاری)B / 255.0f;
        fA = (اعشاری)A / 255.0f;
        توڑو;
    حالت Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ:
        pixelvalue = *((Uint32 *)pixels);
        انتخاب (fmt->format) {
        حالت SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            توڑو;
        حالت SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            توڑو;
        حالت SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            توڑو;
        حالت SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            توڑو;
        طےشدہ:
            fR = fG = fB = fA = 0.0f;
            توڑو;
        }
        توڑو;
    حالت SlowBlitPixelAccess_Large:
        انتخاب (SDL_PIXELTYPE(fmt->format)) {
        حالت SDL_PIXELTYPE_ARRAYU16:
            v[0] = (اعشاری)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (اعشاری)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (اعشاری)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            اگر (fmt->بائٹیں_فی_pixel == 8) {
                v[3] = (اعشاری)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } ورنہ {
                v[3] = 1.0f;
            }
            توڑو;
        حالت SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_مقصد_float(((Uint16 *)pixels)[0]);
            v[1] = half_مقصد_float(((Uint16 *)pixels)[1]);
            v[2] = half_مقصد_float(((Uint16 *)pixels)[2]);
            اگر (fmt->بائٹیں_فی_pixel == 8) {
                v[3] = half_مقصد_float(((Uint16 *)pixels)[3]);
            } ورنہ {
                v[3] = 1.0f;
            }
            توڑو;
        حالت SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((اعشاری *)pixels)[0];
            v[1] = ((اعشاری *)pixels)[1];
            v[2] = ((اعشاری *)pixels)[2];
            اگر (fmt->بائٹیں_فی_pixel == 16) {
                v[3] = ((اعشاری *)pixels)[3];
            } ورنہ {
                v[3] = 1.0f;
            }
            توڑو;
        طےشدہ:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            توڑو;
        }
        انتخاب (SDL_PIXELORDER(fmt->format)) {
        حالت SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            توڑو;
        حالت SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            توڑو;
        حالت SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            توڑو;
        حالت SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            توڑو;
        حالت SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            توڑو;
        حالت SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            توڑو;
        طےشدہ:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            توڑو;
        }
        توڑو;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    انتخاب (SDL_COLORSPACETRANSFER(colorspace)) {
    حالت SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBto_خطی(fR);
        fG = SDL_s_RGBto_خطی(fG);
        fB = SDL_s_RGBto_خطی(fB);
        توڑو;
    حالت SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_نقطہ;
        fG = SDL_PQtoNits(fG) / SDR_white_نقطہ;
        fB = SDL_PQtoNits(fB) / SDR_white_نقطہ;
        توڑو;
    حالت SDL_TRANSFER_CHARACTERISTICS_خطی:
        fR /= SDR_white_نقطہ;
        fG /= SDR_white_نقطہ;
        fB /= SDR_white_نقطہ;
        توڑو;
    طےشدہ:
        // Unknown, leave it alone
        توڑو;
    }

    *برآمد_R = fR;
    *برآمد_G = fG;
    *برآمد_B = fB;
    *برآمد_A = fA;
}

ساکن خالی WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ثابت SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, اعشاری SDR_white_نقطہ,
                            اعشاری fR, اعشاری fG, اعشاری fB, اعشاری fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    اعشاری v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    انتخاب (SDL_COLORSPACETRANSFER(colorspace)) {
    حالت SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBfrom_خطی(fR);
        fG = SDL_s_RGBfrom_خطی(fG);
        fB = SDL_s_RGBfrom_خطی(fB);
        توڑو;
    حالت SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_نقطہ);
        fG = SDL_PQfromNits(fG * SDR_white_نقطہ);
        fB = SDL_PQfromNits(fB * SDR_white_نقطہ);
        توڑو;
    حالت SDL_TRANSFER_CHARACTERISTICS_خطی:
        fR *= SDR_white_نقطہ;
        fG *= SDR_white_نقطہ;
        fB *= SDR_white_نقطہ;
        توڑو;
    طےشدہ:
        // Unknown, leave it alone
        توڑو;
    }

    انتخاب (access) {
    حالت SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        توڑو;
    حالت SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->بائٹیں_فی_pixel, fmt, R, G, B);
        توڑو;
    حالت SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->بائٹیں_فی_pixel, fmt, R, G, B, A);
        توڑو;
    حالت Slow_Blit_Pixel_Access_10_ثنائی_ہندسہ:
    {
        انتخاب (fmt->format) {
        حالت SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        حالت SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            توڑو;
        حالت SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        حالت SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            توڑو;
        طےشدہ:
            pixelvalue = 0;
            توڑو;
        }
        *(Uint32 *)pixels = pixelvalue;
        توڑو;
    }
    حالت SlowBlitPixelAccess_Large:
        انتخاب (SDL_PIXELORDER(fmt->format)) {
        حالت SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            توڑو;
        حالت SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            توڑو;
        حالت SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            توڑو;
        حالت SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            توڑو;
        حالت SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            توڑو;
        حالت SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            توڑو;
        طےشدہ:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            توڑو;
        }
        انتخاب (SDL_PIXELTYPE(fmt->format)) {
        حالت SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            اگر (fmt->بائٹیں_فی_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            توڑو;
        حالت SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_مقصد_half(v[0]);
            ((Uint16 *)pixels)[1] = float_مقصد_half(v[1]);
            ((Uint16 *)pixels)[2] = float_مقصد_half(v[2]);
            اگر (fmt->بائٹیں_فی_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_مقصد_half(v[3]);
            }
            توڑو;
        حالت SDL_PIXELTYPE_ARRAYF32:
            ((اعشاری *)pixels)[0] = v[0];
            ((اعشاری *)pixels)[1] = v[1];
            ((اعشاری *)pixels)[2] = v[2];
            اگر (fmt->بائٹیں_فی_pixel == 16) {
                ((اعشاری *)pixels)[3] = v[3];
            }
            توڑو;
        طےشدہ:
            // Unknown array type
            توڑو;
        }
        توڑو;
    }
}

قسمتعریف شمار
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_خطی,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

قسمتعریف ساخت
{
    SDL_TonemapOperator op;

    اتحاد {
        ساخت {
            اعشاری scale;
        } خطی;

        ساخت {
            اعشاری a;
            اعشاری b;
            ثابت اعشاری *color_primaries_میٹرکس;
        } chrome;

    } ڈیٹا;

} SDL_TonemapContext;

ساکن خالی Tonemap_خطی(اعشاری *r, اعشاری *g, اعشاری *b, اعشاری scale)
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
ساکن خالی TonemapChrome(اعشاری *r, اعشاری *g, اعشاری *b, اعشاری tonemap_a, اعشاری tonemap_b)
{
    اعشاری v1 = *r;
    اعشاری v2 = *g;
    اعشاری v3 = *b;
    اعشاری vmax = SDL_max(v1, SDL_max(v2, v3));

    اگر (vmax > 0.0f) {
        اعشاری scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        Tonemap_خطی(r, g, b, scale);
    }
}

ساکن خالی ApplyTonemap(SDL_TonemapContext *ctx, اعشاری *r, اعشاری *g, اعشاری *b)
{
    انتخاب (ctx->op) {
    حالت SDL_TONEMAP_خطی:
        Tonemap_خطی(r, g, b, ctx->ڈیٹا.خطی.scale);
        توڑو;
    حالت SDL_TONEMAP_CHROME:
        اگر (ctx->ڈیٹا.chrome.color_primaries_میٹرکس) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->ڈیٹا.chrome.color_primaries_میٹرکس);
        }
        TonemapChrome(r, g, b, ctx->ڈیٹا.chrome.a, ctx->ڈیٹا.chrome.b);
        توڑو;
    طےشدہ:
        توڑو;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
خالی SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ثابت صحیح flags = info->flags;
    ثابت Uint32 modulateR = info->r;
    ثابت Uint32 modulateG = info->g;
    ثابت Uint32 modulateB = info->b;
    ثابت Uint32 modulateA = info->a;
    اعشاری srcR, srcG, srcB, srcA;
    اعشاری dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ثابت SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ثابت SDL_Palette *src_pal = info->src_pal;
    ثابت SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ثابت SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_جدول *palette_map = info->palette_map;
    صحیح srcbpp = src_fmt->بائٹیں_فی_pixel;
    صحیح dstbpp = dst_fmt->بائٹیں_فی_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ثابت اعشاری *color_primaries_میٹرکس = تہی;
    اعشاری src_white_نقطہ;
    اعشاری dst_white_نقطہ;
    اعشاری dst_headroom;
    اعشاری src_headroom;
    SDL_TonemapContext tonemap;
    Uint32 آخری_pixel = 0;
    Uint8 آخری_اشاریہ = 0;

    src_colorspace = info->src_surface->colorspace;
    dst_colorspace = info->dst_surface->colorspace;
    src_primaries = SDL_COLORSPACEPRIMARIES(src_colorspace);
    dst_primaries = SDL_COLORSPACEPRIMARIES(dst_colorspace);

    src_white_نقطہ = SDL_Get_Surface_SDRWhite_نقطہ(info->src_surface, src_colorspace);
    dst_white_نقطہ = SDL_Get_Surface_SDRWhite_نقطہ(info->dst_surface, dst_colorspace);
    src_headroom = SDL_GetSurfaceHDRHeadroom(info->src_surface, src_colorspace);
    dst_headroom = SDL_GetSurfaceHDRHeadroom(info->dst_surface, dst_colorspace);
    اگر (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_سیٹ_Float_Property(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    اگر (src_headroom > dst_headroom) {
        ثابت حرف *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, تہی);
        اگر (tonemap_operator) {
            اگر (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_خطی;
                tonemap.ڈیٹا.خطی.scale = (اعشاری)SDL_atof(tonemap_operator + 2);
            } ورنہ اگر (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } ورنہ اگر (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } ورنہ {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        اگر (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.ڈیٹا.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.ڈیٹا.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.ڈیٹا.chrome.color_primaries_میٹرکس = SDL_Get_Color_Primaries_Conversion_میٹرکس(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            اگر (tonemap.ڈیٹا.chrome.color_primaries_میٹرکس) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    اگر (src_primaries != dst_primaries) {
        color_primaries_میٹرکس = SDL_Get_Color_Primaries_Conversion_میٹرکس(src_primaries, dst_primaries);
    }

    src_access = Get_Pixel_Access_طریقہ(src_fmt->format);
    dst_access = Get_Pixel_Access_طریقہ(dst_fmt->format);
    اگر (dst_access == SlowBlitPixelAccess_Index8) {
        آخری_اشاریہ = SDL_LookupRGBAColor(palette_map, آخری_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    جب (info->dst_h--) {
        Uint8 *src = تہی;
        Uint8 *dst = info->dst;
        صحیح n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        جب (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_نقطہ, &srcR, &srcG, &srcB, &srcA);

            اگر (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            اگر (color_primaries_میٹرکس) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_میٹرکس);
            }

            اگر (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            اگر ((flags & (SDL_COPY_BLEND | SDL_COPY_جوڑو | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_نقطہ, &dstR, &dstG, &dstB, &dstA);
            } ورنہ {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            اگر (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            اگر (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            اگر (flags & (SDL_COPY_BLEND | SDL_COPY_جوڑو)) {
                اگر (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            انتخاب (flags & (SDL_COPY_BLEND | SDL_COPY_جوڑو | SDL_COPY_MOD | SDL_COPY_MUL)) {
            حالت 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                توڑو;
            حالت SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                توڑو;
            حالت SDL_COPY_جوڑو:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                توڑو;
            حالت SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                توڑو;
            حالت SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                توڑو;
            }

            اگر (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_خطی(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_خطی(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_خطی(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                اگر (dstpixel != آخری_pixel) {
                    آخری_pixel = dstpixel;
                    آخری_اشاریہ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = آخری_اشاریہ;
            } ورنہ {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_نقطہ, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


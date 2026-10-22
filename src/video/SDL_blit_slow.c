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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_blit_slow.h"
#अन्तर्भाव "SDL_pixels_c.h"

प्रकारनिर्देश गणना
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

स्थिर SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    यदि (SDL_BYTESPERPIXEL(format) > 4) {
        फर्काऊ SlowBlitPixelAccess_Large;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_10BIT(format)) {
        फर्काऊ SlowBlitPixelAccess_10Bit;
    } अन्यथा यदि (format == SDL_PIXELFORMAT_INDEX8) {
        फर्काऊ SlowBlitPixelAccess_Index8;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_ALPHA(format)) {
        फर्काऊ SlowBlitPixelAccess_RGBA;
    } अन्यथा {
        फर्काऊ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
शून्य SDL_Blit_Slow(SDL_BlitInfo *info)
{
    अचर पूर्णाङ्क flags = info->flags;
    अचर Uint32 modulateR = info->r;
    अचर Uint32 modulateG = info->g;
    अचर Uint32 modulateB = info->b;
    अचर Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    अचर SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    अचर SDL_Palette *src_pal = info->src_pal;
    अचर SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    अचर SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    पूर्णाङ्क srcbpp = src_fmt->bytes_per_pixel;
    पूर्णाङ्क dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    यदि (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    जबसम्म (info->dst_h--) {
        Uint8 *src = रिक्त;
        Uint8 *dst = info->dst;
        पूर्णाङ्क n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        जबसम्म (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            विकल्प (src_access) {
            पक्ष SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                रोक;
            पक्ष SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                रोक;
            पक्ष SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                रोक;
            पक्ष SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                विकल्प (src_fmt->format) {
                पक्ष SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    रोक;
                पक्ष SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    रोक;
                पक्ष SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    रोक;
                पक्ष SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    रोक;
                स्वभाव:
                    रोक;
                }
                रोक;
            पक्ष SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                रोक;
            }

            यदि (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                यदि (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                यदि ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    जारी;
                }
            }
            यदि (flags & SDL_COPY_BLEND_MASK) {
                विकल्प (dst_access) {
                पक्ष SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    रोक;
                पक्ष SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    रोक;
                पक्ष SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    रोक;
                पक्ष SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    विकल्प (dst_fmt->format) {
                    पक्ष SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        रोक;
                    पक्ष SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        रोक;
                    पक्ष SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        रोक;
                    पक्ष SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        रोक;
                    स्वभाव:
                        रोक;
                    }
                    रोक;
                पक्ष SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    रोक;
                }
            } अन्यथा {
                // don't care
            }

            यदि (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            यदि (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            यदि (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                यदि (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            विकल्प (flags & SDL_COPY_BLEND_MASK) {
            पक्ष 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                रोक;
            पक्ष SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                रोक;
            पक्ष SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                यदि (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                यदि (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                यदि (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                यदि (dstA > 255) {
                    dstA = 255;
                }
                रोक;
            पक्ष SDL_COPY_ADD:
            पक्ष SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                यदि (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                यदि (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                यदि (dstB > 255) {
                    dstB = 255;
                }
                रोक;
            पक्ष SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                रोक;
            पक्ष SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                यदि (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                यदि (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                यदि (dstB > 255) {
                    dstB = 255;
                }
                रोक;
            }

            विकल्प (dst_access) {
            पक्ष SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                यदि (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                रोक;
            पक्ष SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                रोक;
            पक्ष SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                रोक;
            पक्ष SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                विकल्प (dst_fmt->format) {
                पक्ष SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                पक्ष SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    रोक;
                पक्ष SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                पक्ष SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    रोक;
                स्वभाव:
                    pixelvalue = 0;
                    रोक;
                }
                *(Uint32 *)dst = pixelvalue;
                रोक;
            }
            पक्ष SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                रोक;
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
प्रकारनिर्देश सङ्घ
{
    Uint32 u;
    भिन्न f;
    संरचना
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(थप)
#pragma warning(disable:4214)
#endif

प्रकारनिर्देश सङ्घ
{
    Uint16 u;
    संरचना
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(झिक)
#endif

स्थिर भिन्न half_to_float(Uint16 un_मान)
{
    स्थिर अचर FP32 magic = { (254 - 15) << 23 };
    स्थिर अचर FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_मान;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    यदि (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    फर्काऊ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
स्थिर Uint16 float_to_half(भिन्न a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, परिमाण(ia));

    ir = (ia >> 16) & 0x8000;
    यदि ((ia & 0x7f800000) == 0x7f800000) {
        यदि ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } अन्यथा {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } अन्यथा यदि ((ia & 0x7f800000) >= 0x33000000) {
        पूर्णाङ्क shift = (पूर्णाङ्क)((ia >> 23) & 0xff) - 127;
        यदि (shift > 15) {
            ir |= 0x7c00; // infinity
        } अन्यथा {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            यदि (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } अन्यथा { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            यदि ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    फर्काऊ ir;
}

स्थिर शून्य ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, अचर SDL_PixelFormatDetails *fmt, अचर SDL_Palette *pal, SDL_Colorspace colorspace, भिन्न SDR_white_point,
                           भिन्न *outR, भिन्न *outG, भिन्न *outB, भिन्न *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    भिन्न fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    भिन्न v[4];

    विकल्प (access) {
    पक्ष SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (भिन्न)pal->colors[pixelvalue].r / 255.0f;
        fG = (भिन्न)pal->colors[pixelvalue].g / 255.0f;
        fB = (भिन्न)pal->colors[pixelvalue].b / 255.0f;
        fA = (भिन्न)pal->colors[pixelvalue].a / 255.0f;
        रोक;
    पक्ष SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (भिन्न)R / 255.0f;
        fG = (भिन्न)G / 255.0f;
        fB = (भिन्न)B / 255.0f;
        fA = 1.0f;
        रोक;
    पक्ष SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (भिन्न)R / 255.0f;
        fG = (भिन्न)G / 255.0f;
        fB = (भिन्न)B / 255.0f;
        fA = (भिन्न)A / 255.0f;
        रोक;
    पक्ष SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        विकल्प (fmt->format) {
        पक्ष SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            रोक;
        पक्ष SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            रोक;
        पक्ष SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            रोक;
        पक्ष SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            रोक;
        स्वभाव:
            fR = fG = fB = fA = 0.0f;
            रोक;
        }
        रोक;
    पक्ष SlowBlitPixelAccess_Large:
        विकल्प (SDL_PIXELTYPE(fmt->format)) {
        पक्ष SDL_PIXELTYPE_ARRAYU16:
            v[0] = (भिन्न)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (भिन्न)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (भिन्न)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            यदि (fmt->bytes_per_pixel == 8) {
                v[3] = (भिन्न)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } अन्यथा {
                v[3] = 1.0f;
            }
            रोक;
        पक्ष SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            यदि (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } अन्यथा {
                v[3] = 1.0f;
            }
            रोक;
        पक्ष SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((भिन्न *)pixels)[0];
            v[1] = ((भिन्न *)pixels)[1];
            v[2] = ((भिन्न *)pixels)[2];
            यदि (fmt->bytes_per_pixel == 16) {
                v[3] = ((भिन्न *)pixels)[3];
            } अन्यथा {
                v[3] = 1.0f;
            }
            रोक;
        स्वभाव:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            रोक;
        }
        विकल्प (SDL_PIXELORDER(fmt->format)) {
        पक्ष SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            रोक;
        पक्ष SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            रोक;
        पक्ष SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            रोक;
        पक्ष SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            रोक;
        पक्ष SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            रोक;
        पक्ष SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            रोक;
        स्वभाव:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            रोक;
        }
        रोक;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    विकल्प (SDL_COLORSPACETRANSFER(colorspace)) {
    पक्ष SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        रोक;
    पक्ष SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        रोक;
    पक्ष SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        रोक;
    स्वभाव:
        // Unknown, leave it alone
        रोक;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

स्थिर शून्य WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, अचर SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, भिन्न SDR_white_point,
                            भिन्न fR, भिन्न fG, भिन्न fB, भिन्न fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    भिन्न v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    विकल्प (SDL_COLORSPACETRANSFER(colorspace)) {
    पक्ष SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        रोक;
    पक्ष SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        रोक;
    पक्ष SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        रोक;
    स्वभाव:
        // Unknown, leave it alone
        रोक;
    }

    विकल्प (access) {
    पक्ष SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        रोक;
    पक्ष SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        रोक;
    पक्ष SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        रोक;
    पक्ष SlowBlitPixelAccess_10Bit:
    {
        विकल्प (fmt->format) {
        पक्ष SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        पक्ष SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            रोक;
        पक्ष SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        पक्ष SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            रोक;
        स्वभाव:
            pixelvalue = 0;
            रोक;
        }
        *(Uint32 *)pixels = pixelvalue;
        रोक;
    }
    पक्ष SlowBlitPixelAccess_Large:
        विकल्प (SDL_PIXELORDER(fmt->format)) {
        पक्ष SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            रोक;
        पक्ष SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            रोक;
        पक्ष SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            रोक;
        पक्ष SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            रोक;
        पक्ष SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            रोक;
        पक्ष SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            रोक;
        स्वभाव:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            रोक;
        }
        विकल्प (SDL_PIXELTYPE(fmt->format)) {
        पक्ष SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            यदि (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            रोक;
        पक्ष SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            यदि (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            रोक;
        पक्ष SDL_PIXELTYPE_ARRAYF32:
            ((भिन्न *)pixels)[0] = v[0];
            ((भिन्न *)pixels)[1] = v[1];
            ((भिन्न *)pixels)[2] = v[2];
            यदि (fmt->bytes_per_pixel == 16) {
                ((भिन्न *)pixels)[3] = v[3];
            }
            रोक;
        स्वभाव:
            // Unknown array type
            रोक;
        }
        रोक;
    }
}

प्रकारनिर्देश गणना
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

प्रकारनिर्देश संरचना
{
    SDL_TonemapOperator op;

    सङ्घ {
        संरचना {
            भिन्न scale;
        } linear;

        संरचना {
            भिन्न a;
            भिन्न b;
            अचर भिन्न *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

स्थिर शून्य TonemapLinear(भिन्न *r, भिन्न *g, भिन्न *b, भिन्न scale)
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
स्थिर शून्य TonemapChrome(भिन्न *r, भिन्न *g, भिन्न *b, भिन्न tonemap_a, भिन्न tonemap_b)
{
    भिन्न v1 = *r;
    भिन्न v2 = *g;
    भिन्न v3 = *b;
    भिन्न vmax = SDL_max(v1, SDL_max(v2, v3));

    यदि (vmax > 0.0f) {
        भिन्न scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

स्थिर शून्य ApplyTonemap(SDL_TonemapContext *ctx, भिन्न *r, भिन्न *g, भिन्न *b)
{
    विकल्प (ctx->op) {
    पक्ष SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        रोक;
    पक्ष SDL_TONEMAP_CHROME:
        यदि (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        रोक;
    स्वभाव:
        रोक;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
शून्य SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    अचर पूर्णाङ्क flags = info->flags;
    अचर Uint32 modulateR = info->r;
    अचर Uint32 modulateG = info->g;
    अचर Uint32 modulateB = info->b;
    अचर Uint32 modulateA = info->a;
    भिन्न srcR, srcG, srcB, srcA;
    भिन्न dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    अचर SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    अचर SDL_Palette *src_pal = info->src_pal;
    अचर SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    अचर SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    पूर्णाङ्क srcbpp = src_fmt->bytes_per_pixel;
    पूर्णाङ्क dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    अचर भिन्न *color_primaries_matrix = रिक्त;
    भिन्न src_white_point;
    भिन्न dst_white_point;
    भिन्न dst_headroom;
    भिन्न src_headroom;
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
    यदि (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    यदि (src_headroom > dst_headroom) {
        अचर वर्ण *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, रिक्त);
        यदि (tonemap_operator) {
            यदि (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (भिन्न)SDL_atof(tonemap_operator + 2);
            } अन्यथा यदि (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } अन्यथा यदि (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } अन्यथा {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        यदि (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            यदि (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    यदि (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    यदि (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    जबसम्म (info->dst_h--) {
        Uint8 *src = रिक्त;
        Uint8 *dst = info->dst;
        पूर्णाङ्क n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        जबसम्म (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            यदि (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            यदि (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            यदि (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            यदि ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } अन्यथा {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            यदि (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            यदि (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            यदि (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                यदि (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            विकल्प (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            पक्ष 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                रोक;
            पक्ष SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                रोक;
            पक्ष SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                रोक;
            पक्ष SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                रोक;
            पक्ष SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                रोक;
            }

            यदि (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                यदि (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
            } अन्यथा {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


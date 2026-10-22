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
#అన్తర్భావ "SDL_internal.h"

#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_blit_slow.h"
#అన్తర్భావ "SDL_pixels_c.h"

రకనిర్వచనం గణన
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    Slow_Blit_Pixel_Access_10_బిట్టు,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

స్థిర SlowBlitPixelAccess Get_Pixel_Access_పద్ధతి(SDL_PixelFormat format)
{
    ఒకవేళ (SDL_BYTESPERPIXEL(format) > 4) {
        తిరిగి SlowBlitPixelAccess_Large;
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_10_బిట్టు(format)) {
        తిరిగి Slow_Blit_Pixel_Access_10_బిట్టు;
    } లేకపోతే ఒకవేళ (format == SDL_PIXELFORMAT_INDEX8) {
        తిరిగి SlowBlitPixelAccess_Index8;
    } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_ALPHA(format)) {
        తిరిగి SlowBlitPixelAccess_RGBA;
    } లేకపోతే {
        తిరిగి SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
శూన్య SDL_Blit_Slow(SDL_BlitInfo *info)
{
    స్థిరరాశి పూర్ణాంకం flags = info->flags;
    స్థిరరాశి Uint32 modulateR = info->r;
    స్థిరరాశి Uint32 modulateG = info->g;
    స్థిరరాశి Uint32 modulateB = info->b;
    స్థిరరాశి Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    స్థిరరాశి SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    స్థిరరాశి SDL_Palette *src_pal = info->src_pal;
    స్థిరరాశి SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    స్థిరరాశి SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_పట్టిక *palette_map = info->palette_map;
    పూర్ణాంకం srcbpp = src_fmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dst_fmt->బైట్లు_చొప్పున_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 చివరి_pixel = 0;
    Uint8 చివరి_సూచీ = 0;

    src_access = Get_Pixel_Access_పద్ధతి(src_fmt->format);
    dst_access = Get_Pixel_Access_పద్ధతి(dst_fmt->format);
    ఒకవేళ (dst_access == SlowBlitPixelAccess_Index8) {
        చివరి_సూచీ = SDL_LookupRGBAColor(palette_map, చివరి_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    అయితే (info->dst_h--) {
        Uint8 *src = ఖాళీ;
        Uint8 *dst = info->dst;
        పూర్ణాంకం n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        అయితే (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ఎంపిక (src_access) {
            స్థితి SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                ఆపు;
            స్థితి SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                ఆపు;
            స్థితి SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                ఆపు;
            స్థితి Slow_Blit_Pixel_Access_10_బిట్టు:
                srcpixel = *((Uint32 *)(src));
                ఎంపిక (src_fmt->format) {
                స్థితి SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ఆపు;
                స్థితి SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ఆపు;
                స్థితి SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ఆపు;
                స్థితి SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ఆపు;
                అప్రమేయ:
                    ఆపు;
                }
                ఆపు;
            స్థితి SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ఆపు;
            }

            ఒకవేళ (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                ఒకవేళ (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                ఒకవేళ ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    కొనసాగు;
                }
            }
            ఒకవేళ (flags & SDL_COPY_BLEND_ముసుగు) {
                ఎంపిక (dst_access) {
                స్థితి SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    ఆపు;
                స్థితి SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    ఆపు;
                స్థితి SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    ఆపు;
                స్థితి Slow_Blit_Pixel_Access_10_బిట్టు:
                    dstpixel = *((Uint32 *)(dst));
                    ఎంపిక (dst_fmt->format) {
                    స్థితి SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ఆపు;
                    స్థితి SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ఆపు;
                    స్థితి SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ఆపు;
                    స్థితి SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ఆపు;
                    అప్రమేయ:
                        ఆపు;
                    }
                    ఆపు;
                స్థితి SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    ఆపు;
                }
            } లేకపోతే {
                // don't care
            }

            ఒకవేళ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ఒకవేళ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ఒకవేళ (flags & (SDL_COPY_BLEND | SDL_COPY_కూడు)) {
                ఒకవేళ (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            ఎంపిక (flags & SDL_COPY_BLEND_ముసుగు) {
            స్థితి 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ఆపు;
            స్థితి SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ఆపు;
            స్థితి SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                ఒకవేళ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                ఒకవేళ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                ఒకవేళ (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ఒకవేళ (dstA > 255) {
                    dstA = 255;
                }
                ఆపు;
            స్థితి SDL_COPY_కూడు:
            స్థితి SDL_COPY_కూడు_PREMULTIPLIED:
                dstR = srcR + dstR;
                ఒకవేళ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                ఒకవేళ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                ఒకవేళ (dstB > 255) {
                    dstB = 255;
                }
                ఆపు;
            స్థితి SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                ఆపు;
            స్థితి SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                ఒకవేళ (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                ఒకవేళ (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                ఒకవేళ (dstB > 255) {
                    dstB = 255;
                }
                ఆపు;
            }

            ఎంపిక (dst_access) {
            స్థితి SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                ఒకవేళ (dstpixel != చివరి_pixel) {
                    చివరి_pixel = dstpixel;
                    చివరి_సూచీ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = చివరి_సూచీ;
                ఆపు;
            స్థితి SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                ఆపు;
            స్థితి SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                ఆపు;
            స్థితి Slow_Blit_Pixel_Access_10_బిట్టు:
            {
                Uint32 pixelvalue;
                ఎంపిక (dst_fmt->format) {
                స్థితి SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                స్థితి SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ఆపు;
                స్థితి SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                స్థితి SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ఆపు;
                అప్రమేయ:
                    pixelvalue = 0;
                    ఆపు;
                }
                *(Uint32 *)dst = pixelvalue;
                ఆపు;
            }
            స్థితి SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ఆపు;
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
రకనిర్వచనం సంఘం
{
    Uint32 u;
    దశాంశం f;
    నిర్మాణం
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#నిర్వచితమైతే _MSC_VER
#సూచన warning(నెట్టు)
#సూచన warning(disable:4214)
#అయితే_ముగింపు

రకనిర్వచనం సంఘం
{
    Uint16 u;
    నిర్మాణం
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#నిర్వచితమైతే _MSC_VER
#సూచన warning(తీయి)
#అయితే_ముగింపు

స్థిర దశాంశం half_గమ్యం_float(Uint16 un_విలువ)
{
    స్థిర స్థిరరాశి FP32 magic = { (254 - 15) << 23 };
    స్థిర స్థిరరాశి FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_విలువ;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    ఒకవేళ (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    తిరిగి o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
స్థిర Uint16 float_గమ్యం_half(దశాంశం a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, పరిమాణం(ia));

    ir = (ia >> 16) & 0x8000;
    ఒకవేళ ((ia & 0x7f800000) == 0x7f800000) {
        ఒకవేళ ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } లేకపోతే {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } లేకపోతే ఒకవేళ ((ia & 0x7f800000) >= 0x33000000) {
        పూర్ణాంకం జరుపు = (పూర్ణాంకం)((ia >> 23) & 0xff) - 127;
        ఒకవేళ (జరుపు > 15) {
            ir |= 0x7c00; // infinity
        } లేకపోతే {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            ఒకవేళ (జరుపు < -14) { // denormal
                ir |= ia >> (-1 - జరుపు);
                ia = ia << (32 - (-1 - జరుపు));
            } లేకపోతే { //సాధారణ
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + జరుపు) << 10);
            }
            // IEEE-754 round to nearest of even
            ఒకవేళ ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    తిరిగి ir;
}

స్థిర శూన్య ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, స్థిరరాశి SDL_PixelFormatDetails *fmt, స్థిరరాశి SDL_Palette *pal, SDL_Colorspace colorspace, దశాంశం SDR_white_బిందువు,
                           దశాంశం *బహిర్గతం_R, దశాంశం *బహిర్గతం_G, దశాంశం *బహిర్గతం_B, దశాంశం *బహిర్గతం_A)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    దశాంశం fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    దశాంశం v[4];

    ఎంపిక (access) {
    స్థితి SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (దశాంశం)pal->colors[pixelvalue].r / 255.0f;
        fG = (దశాంశం)pal->colors[pixelvalue].g / 255.0f;
        fB = (దశాంశం)pal->colors[pixelvalue].b / 255.0f;
        fA = (దశాంశం)pal->colors[pixelvalue].a / 255.0f;
        ఆపు;
    స్థితి SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->బైట్లు_చొప్పున_pixel, fmt, pixelvalue, R, G, B);
        fR = (దశాంశం)R / 255.0f;
        fG = (దశాంశం)G / 255.0f;
        fB = (దశాంశం)B / 255.0f;
        fA = 1.0f;
        ఆపు;
    స్థితి SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->బైట్లు_చొప్పున_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (దశాంశం)R / 255.0f;
        fG = (దశాంశం)G / 255.0f;
        fB = (దశాంశం)B / 255.0f;
        fA = (దశాంశం)A / 255.0f;
        ఆపు;
    స్థితి Slow_Blit_Pixel_Access_10_బిట్టు:
        pixelvalue = *((Uint32 *)pixels);
        ఎంపిక (fmt->format) {
        స్థితి SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ఆపు;
        స్థితి SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ఆపు;
        స్థితి SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            ఆపు;
        స్థితి SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            ఆపు;
        అప్రమేయ:
            fR = fG = fB = fA = 0.0f;
            ఆపు;
        }
        ఆపు;
    స్థితి SlowBlitPixelAccess_Large:
        ఎంపిక (SDL_PIXELTYPE(fmt->format)) {
        స్థితి SDL_PIXELTYPE_ARRAYU16:
            v[0] = (దశాంశం)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (దశాంశం)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (దశాంశం)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            ఒకవేళ (fmt->బైట్లు_చొప్పున_pixel == 8) {
                v[3] = (దశాంశం)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } లేకపోతే {
                v[3] = 1.0f;
            }
            ఆపు;
        స్థితి SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_గమ్యం_float(((Uint16 *)pixels)[0]);
            v[1] = half_గమ్యం_float(((Uint16 *)pixels)[1]);
            v[2] = half_గమ్యం_float(((Uint16 *)pixels)[2]);
            ఒకవేళ (fmt->బైట్లు_చొప్పున_pixel == 8) {
                v[3] = half_గమ్యం_float(((Uint16 *)pixels)[3]);
            } లేకపోతే {
                v[3] = 1.0f;
            }
            ఆపు;
        స్థితి SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((దశాంశం *)pixels)[0];
            v[1] = ((దశాంశం *)pixels)[1];
            v[2] = ((దశాంశం *)pixels)[2];
            ఒకవేళ (fmt->బైట్లు_చొప్పున_pixel == 16) {
                v[3] = ((దశాంశం *)pixels)[3];
            } లేకపోతే {
                v[3] = 1.0f;
            }
            ఆపు;
        అప్రమేయ:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ఆపు;
        }
        ఎంపిక (SDL_PIXELORDER(fmt->format)) {
        స్థితి SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            ఆపు;
        స్థితి SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            ఆపు;
        స్థితి SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            ఆపు;
        స్థితి SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            ఆపు;
        స్థితి SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            ఆపు;
        స్థితి SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            ఆపు;
        అప్రమేయ:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            ఆపు;
        }
        ఆపు;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    ఎంపిక (SDL_COLORSPACETRANSFER(colorspace)) {
    స్థితి SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBto_రేఖీయ(fR);
        fG = SDL_s_RGBto_రేఖీయ(fG);
        fB = SDL_s_RGBto_రేఖీయ(fB);
        ఆపు;
    స్థితి SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_బిందువు;
        fG = SDL_PQtoNits(fG) / SDR_white_బిందువు;
        fB = SDL_PQtoNits(fB) / SDR_white_బిందువు;
        ఆపు;
    స్థితి SDL_TRANSFER_CHARACTERISTICS_రేఖీయ:
        fR /= SDR_white_బిందువు;
        fG /= SDR_white_బిందువు;
        fB /= SDR_white_బిందువు;
        ఆపు;
    అప్రమేయ:
        // Unknown, leave it alone
        ఆపు;
    }

    *బహిర్గతం_R = fR;
    *బహిర్గతం_G = fG;
    *బహిర్గతం_B = fB;
    *బహిర్గతం_A = fA;
}

స్థిర శూన్య WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, స్థిరరాశి SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, దశాంశం SDR_white_బిందువు,
                            దశాంశం fR, దశాంశం fG, దశాంశం fB, దశాంశం fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    దశాంశం v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    ఎంపిక (SDL_COLORSPACETRANSFER(colorspace)) {
    స్థితి SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBfrom_రేఖీయ(fR);
        fG = SDL_s_RGBfrom_రేఖీయ(fG);
        fB = SDL_s_RGBfrom_రేఖీయ(fB);
        ఆపు;
    స్థితి SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_బిందువు);
        fG = SDL_PQfromNits(fG * SDR_white_బిందువు);
        fB = SDL_PQfromNits(fB * SDR_white_బిందువు);
        ఆపు;
    స్థితి SDL_TRANSFER_CHARACTERISTICS_రేఖీయ:
        fR *= SDR_white_బిందువు;
        fG *= SDR_white_బిందువు;
        fB *= SDR_white_బిందువు;
        ఆపు;
    అప్రమేయ:
        // Unknown, leave it alone
        ఆపు;
    }

    ఎంపిక (access) {
    స్థితి SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        ఆపు;
    స్థితి SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->బైట్లు_చొప్పున_pixel, fmt, R, G, B);
        ఆపు;
    స్థితి SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->బైట్లు_చొప్పున_pixel, fmt, R, G, B, A);
        ఆపు;
    స్థితి Slow_Blit_Pixel_Access_10_బిట్టు:
    {
        ఎంపిక (fmt->format) {
        స్థితి SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        స్థితి SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ఆపు;
        స్థితి SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        స్థితి SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ఆపు;
        అప్రమేయ:
            pixelvalue = 0;
            ఆపు;
        }
        *(Uint32 *)pixels = pixelvalue;
        ఆపు;
    }
    స్థితి SlowBlitPixelAccess_Large:
        ఎంపిక (SDL_PIXELORDER(fmt->format)) {
        స్థితి SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            ఆపు;
        స్థితి SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            ఆపు;
        స్థితి SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            ఆపు;
        స్థితి SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            ఆపు;
        స్థితి SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            ఆపు;
        స్థితి SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            ఆపు;
        అప్రమేయ:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ఆపు;
        }
        ఎంపిక (SDL_PIXELTYPE(fmt->format)) {
        స్థితి SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ఒకవేళ (fmt->బైట్లు_చొప్పున_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            ఆపు;
        స్థితి SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_గమ్యం_half(v[0]);
            ((Uint16 *)pixels)[1] = float_గమ్యం_half(v[1]);
            ((Uint16 *)pixels)[2] = float_గమ్యం_half(v[2]);
            ఒకవేళ (fmt->బైట్లు_చొప్పున_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_గమ్యం_half(v[3]);
            }
            ఆపు;
        స్థితి SDL_PIXELTYPE_ARRAYF32:
            ((దశాంశం *)pixels)[0] = v[0];
            ((దశాంశం *)pixels)[1] = v[1];
            ((దశాంశం *)pixels)[2] = v[2];
            ఒకవేళ (fmt->బైట్లు_చొప్పున_pixel == 16) {
                ((దశాంశం *)pixels)[3] = v[3];
            }
            ఆపు;
        అప్రమేయ:
            // Unknown array type
            ఆపు;
        }
        ఆపు;
    }
}

రకనిర్వచనం గణన
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_రేఖీయ,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

రకనిర్వచనం నిర్మాణం
{
    SDL_TonemapOperator op;

    సంఘం {
        నిర్మాణం {
            దశాంశం scale;
        } రేఖీయ;

        నిర్మాణం {
            దశాంశం a;
            దశాంశం b;
            స్థిరరాశి దశాంశం *color_primaries_మాతృక;
        } chrome;

    } దత్తాంశం;

} SDL_TonemapContext;

స్థిర శూన్య Tonemap_రేఖీయ(దశాంశం *r, దశాంశం *g, దశాంశం *b, దశాంశం scale)
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
స్థిర శూన్య TonemapChrome(దశాంశం *r, దశాంశం *g, దశాంశం *b, దశాంశం tonemap_a, దశాంశం tonemap_b)
{
    దశాంశం v1 = *r;
    దశాంశం v2 = *g;
    దశాంశం v3 = *b;
    దశాంశం vmax = SDL_max(v1, SDL_max(v2, v3));

    ఒకవేళ (vmax > 0.0f) {
        దశాంశం scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        Tonemap_రేఖీయ(r, g, b, scale);
    }
}

స్థిర శూన్య ApplyTonemap(SDL_TonemapContext *ctx, దశాంశం *r, దశాంశం *g, దశాంశం *b)
{
    ఎంపిక (ctx->op) {
    స్థితి SDL_TONEMAP_రేఖీయ:
        Tonemap_రేఖీయ(r, g, b, ctx->దత్తాంశం.రేఖీయ.scale);
        ఆపు;
    స్థితి SDL_TONEMAP_CHROME:
        ఒకవేళ (ctx->దత్తాంశం.chrome.color_primaries_మాతృక) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->దత్తాంశం.chrome.color_primaries_మాతృక);
        }
        TonemapChrome(r, g, b, ctx->దత్తాంశం.chrome.a, ctx->దత్తాంశం.chrome.b);
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
శూన్య SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    స్థిరరాశి పూర్ణాంకం flags = info->flags;
    స్థిరరాశి Uint32 modulateR = info->r;
    స్థిరరాశి Uint32 modulateG = info->g;
    స్థిరరాశి Uint32 modulateB = info->b;
    స్థిరరాశి Uint32 modulateA = info->a;
    దశాంశం srcR, srcG, srcB, srcA;
    దశాంశం dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    స్థిరరాశి SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    స్థిరరాశి SDL_Palette *src_pal = info->src_pal;
    స్థిరరాశి SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    స్థిరరాశి SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_పట్టిక *palette_map = info->palette_map;
    పూర్ణాంకం srcbpp = src_fmt->బైట్లు_చొప్పున_pixel;
    పూర్ణాంకం dstbpp = dst_fmt->బైట్లు_చొప్పున_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    స్థిరరాశి దశాంశం *color_primaries_మాతృక = ఖాళీ;
    దశాంశం src_white_బిందువు;
    దశాంశం dst_white_బిందువు;
    దశాంశం dst_headroom;
    దశాంశం src_headroom;
    SDL_TonemapContext tonemap;
    Uint32 చివరి_pixel = 0;
    Uint8 చివరి_సూచీ = 0;

    src_colorspace = info->src_surface->colorspace;
    dst_colorspace = info->dst_surface->colorspace;
    src_primaries = SDL_COLORSPACEPRIMARIES(src_colorspace);
    dst_primaries = SDL_COLORSPACEPRIMARIES(dst_colorspace);

    src_white_బిందువు = SDL_Get_Surface_SDRWhite_బిందువు(info->src_surface, src_colorspace);
    dst_white_బిందువు = SDL_Get_Surface_SDRWhite_బిందువు(info->dst_surface, dst_colorspace);
    src_headroom = SDL_GetSurfaceHDRHeadroom(info->src_surface, src_colorspace);
    dst_headroom = SDL_GetSurfaceHDRHeadroom(info->dst_surface, dst_colorspace);
    ఒకవేళ (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_సమితి_Float_Property(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    ఒకవేళ (src_headroom > dst_headroom) {
        స్థిరరాశి అక్షరం *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ఖాళీ);
        ఒకవేళ (tonemap_operator) {
            ఒకవేళ (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_రేఖీయ;
                tonemap.దత్తాంశం.రేఖీయ.scale = (దశాంశం)SDL_atof(tonemap_operator + 2);
            } లేకపోతే ఒకవేళ (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } లేకపోతే ఒకవేళ (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } లేకపోతే {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        ఒకవేళ (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.దత్తాంశం.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.దత్తాంశం.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.దత్తాంశం.chrome.color_primaries_మాతృక = SDL_Get_Color_Primaries_Conversion_మాతృక(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            ఒకవేళ (tonemap.దత్తాంశం.chrome.color_primaries_మాతృక) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    ఒకవేళ (src_primaries != dst_primaries) {
        color_primaries_మాతృక = SDL_Get_Color_Primaries_Conversion_మాతృక(src_primaries, dst_primaries);
    }

    src_access = Get_Pixel_Access_పద్ధతి(src_fmt->format);
    dst_access = Get_Pixel_Access_పద్ధతి(dst_fmt->format);
    ఒకవేళ (dst_access == SlowBlitPixelAccess_Index8) {
        చివరి_సూచీ = SDL_LookupRGBAColor(palette_map, చివరి_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    అయితే (info->dst_h--) {
        Uint8 *src = ఖాళీ;
        Uint8 *dst = info->dst;
        పూర్ణాంకం n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        అయితే (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_బిందువు, &srcR, &srcG, &srcB, &srcA);

            ఒకవేళ (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            ఒకవేళ (color_primaries_మాతృక) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_మాతృక);
            }

            ఒకవేళ (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            ఒకవేళ ((flags & (SDL_COPY_BLEND | SDL_COPY_కూడు | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_బిందువు, &dstR, &dstG, &dstB, &dstA);
            } లేకపోతే {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            ఒకవేళ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ఒకవేళ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ఒకవేళ (flags & (SDL_COPY_BLEND | SDL_COPY_కూడు)) {
                ఒకవేళ (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            ఎంపిక (flags & (SDL_COPY_BLEND | SDL_COPY_కూడు | SDL_COPY_MOD | SDL_COPY_MUL)) {
            స్థితి 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ఆపు;
            స్థితి SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                ఆపు;
            స్థితి SDL_COPY_కూడు:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                ఆపు;
            స్థితి SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                ఆపు;
            స్థితి SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                ఆపు;
            }

            ఒకవేళ (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_రేఖీయ(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_రేఖీయ(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_రేఖీయ(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                ఒకవేళ (dstpixel != చివరి_pixel) {
                    చివరి_pixel = dstpixel;
                    చివరి_సూచీ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = చివరి_సూచీ;
            } లేకపోతే {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_బిందువు, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


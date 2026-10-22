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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_blit_slow.h"
#ଅନ୍ତର୍ଭାଵ "SDL_pixels_c.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

ସ୍ଥିର SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    ଯଦି (SDL_BYTESPERPIXEL(format) > 4) {
        ଫେରନ୍ତୁ SlowBlitPixelAccess_Large;
    } ଅନ୍ୟଥା ଯଦି (SDL_ISPIXELFORMAT_10BIT(format)) {
        ଫେରନ୍ତୁ SlowBlitPixelAccess_10Bit;
    } ଅନ୍ୟଥା ଯଦି (format == SDL_PIXELFORMAT_INDEX8) {
        ଫେରନ୍ତୁ SlowBlitPixelAccess_Index8;
    } ଅନ୍ୟଥା ଯଦି (SDL_ISPIXELFORMAT_ALPHA(format)) {
        ଫେରନ୍ତୁ SlowBlitPixelAccess_RGBA;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
ଶୂନ୍ୟ SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = info->flags;
    ଅଚଳ Uint32 modulateR = info->r;
    ଅଚଳ Uint32 modulateG = info->g;
    ଅଚଳ Uint32 modulateB = info->b;
    ଅଚଳ Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ଅଚଳ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ଅଚଳ SDL_Palette *src_pal = info->src_pal;
    ଅଚଳ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ଅଚଳ SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcbpp = src_fmt->bytes_per_pixel;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    ଯଦି (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    ଯେତେବେଳେ (info->dst_h--) {
        Uint8 *src = ଖାଲି;
        Uint8 *dst = info->dst;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ଯେତେବେଳେ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ବାଛ (src_access) {
            ସ୍ଥିତି SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                ବାଛ (src_fmt->format) {
                ସ୍ଥିତି SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ଭାଙ୍ଗ;
                ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                    ଭାଙ୍ଗ;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ଭାଙ୍ଗ;
            }

            ଯଦି (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                ଯଦି (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                ଯଦି ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    ଜାରି;
                }
            }
            ଯଦି (flags & SDL_COPY_BLEND_MASK) {
                ବାଛ (dst_access) {
                ସ୍ଥିତି SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    ବାଛ (dst_fmt->format) {
                    ସ୍ଥିତି SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ଭାଙ୍ଗ;
                    ସ୍ଥିତି SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ଭାଙ୍ଗ;
                    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                        ଭାଙ୍ଗ;
                    }
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    ଭାଙ୍ଗ;
                }
            } ଅନ୍ୟଥା {
                // don't care
            }

            ଯଦି (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ଯଦି (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ଯଦି (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                ଯଦି (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            ବାଛ (flags & SDL_COPY_BLEND_MASK) {
            ସ୍ଥିତି 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                ଯଦି (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                ଯଦି (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                ଯଦି (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ଯଦି (dstA > 255) {
                    dstA = 255;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_ADD:
            ସ୍ଥିତି SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                ଯଦି (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                ଯଦି (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                ଯଦି (dstB > 255) {
                    dstB = 255;
                }
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                ଯଦି (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                ଯଦି (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                ଯଦି (dstB > 255) {
                    dstB = 255;
                }
                ଭାଙ୍ଗ;
            }

            ବାଛ (dst_access) {
            ସ୍ଥିତି SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                ଯଦି (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                ବାଛ (dst_fmt->format) {
                ସ୍ଥିତି SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ସ୍ଥିତି SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ଭାଙ୍ଗ;
                ସ୍ଥିତି SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ସ୍ଥିତି SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ଭାଙ୍ଗ;
                ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                    pixelvalue = 0;
                    ଭାଙ୍ଗ;
                }
                *(Uint32 *)dst = pixelvalue;
                ଭାଙ୍ଗ;
            }
            ସ୍ଥିତି SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ଭାଙ୍ଗ;
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
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂଘ
{
    Uint32 u;
    ଦଶମିକ f;
    ସଂରଚନା
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(ଠେଲ)
#pragma warning(disable:4214)
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂଘ
{
    Uint16 u;
    ସଂରଚନା
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(କାଢ଼)
#endif

ସ୍ଥିର ଦଶମିକ half_to_float(Uint16 un_ମୂଲ୍ୟ)
{
    ସ୍ଥିର ଅଚଳ FP32 magic = { (254 - 15) << 23 };
    ସ୍ଥିର ଅଚଳ FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_ମୂଲ୍ୟ;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    ଯଦି (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    ଫେରନ୍ତୁ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
ସ୍ଥିର Uint16 float_to_half(ଦଶମିକ a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, ଆକାର(ia));

    ir = (ia >> 16) & 0x8000;
    ଯଦି ((ia & 0x7f800000) == 0x7f800000) {
        ଯଦି ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } ଅନ୍ୟଥା {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } ଅନ୍ୟଥା ଯଦି ((ia & 0x7f800000) >= 0x33000000) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((ia >> 23) & 0xff) - 127;
        ଯଦି (shift > 15) {
            ir |= 0x7c00; // infinity
        } ଅନ୍ୟଥା {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            ଯଦି (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } ଅନ୍ୟଥା { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            ଯଦି ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    ଫେରନ୍ତୁ ir;
}

ସ୍ଥିର ଶୂନ୍ୟ ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ଅଚଳ SDL_PixelFormatDetails *fmt, ଅଚଳ SDL_Palette *pal, SDL_Colorspace colorspace, ଦଶମିକ SDR_white_point,
                           ଦଶମିକ *outR, ଦଶମିକ *outG, ଦଶମିକ *outB, ଦଶମିକ *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    ଦଶମିକ fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    ଦଶମିକ v[4];

    ବାଛ (access) {
    ସ୍ଥିତି SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (ଦଶମିକ)pal->colors[pixelvalue].r / 255.0f;
        fG = (ଦଶମିକ)pal->colors[pixelvalue].g / 255.0f;
        fB = (ଦଶମିକ)pal->colors[pixelvalue].b / 255.0f;
        fA = (ଦଶମିକ)pal->colors[pixelvalue].a / 255.0f;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (ଦଶମିକ)R / 255.0f;
        fG = (ଦଶମିକ)G / 255.0f;
        fB = (ଦଶମିକ)B / 255.0f;
        fA = 1.0f;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (ଦଶମିକ)R / 255.0f;
        fG = (ଦଶମିକ)G / 255.0f;
        fB = (ଦଶମିକ)B / 255.0f;
        fA = (ଦଶମିକ)A / 255.0f;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        ବାଛ (fmt->format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            fR = fG = fB = fA = 0.0f;
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_Large:
        ବାଛ (SDL_PIXELTYPE(fmt->format)) {
        ସ୍ଥିତି SDL_PIXELTYPE_ARRAYU16:
            v[0] = (ଦଶମିକ)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (ଦଶମିକ)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (ଦଶମିକ)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            ଯଦି (fmt->bytes_per_pixel == 8) {
                v[3] = (ଦଶମିକ)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } ଅନ୍ୟଥା {
                v[3] = 1.0f;
            }
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            ଯଦି (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } ଅନ୍ୟଥା {
                v[3] = 1.0f;
            }
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((ଦଶମିକ *)pixels)[0];
            v[1] = ((ଦଶମିକ *)pixels)[1];
            v[2] = ((ଦଶମିକ *)pixels)[2];
            ଯଦି (fmt->bytes_per_pixel == 16) {
                v[3] = ((ଦଶମିକ *)pixels)[3];
            } ଅନ୍ୟଥା {
                v[3] = 1.0f;
            }
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ଭାଙ୍ଗ;
        }
        ବାଛ (SDL_PIXELORDER(fmt->format)) {
        ସ୍ଥିତି SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    ବାଛ (SDL_COLORSPACETRANSFER(colorspace)) {
    ସ୍ଥିତି SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        // Unknown, leave it alone
        ଭାଙ୍ଗ;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

ସ୍ଥିର ଶୂନ୍ୟ WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ଅଚଳ SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, ଦଶମିକ SDR_white_point,
                            ଦଶମିକ fR, ଦଶମିକ fG, ଦଶମିକ fB, ଦଶମିକ fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    ଦଶମିକ v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    ବାଛ (SDL_COLORSPACETRANSFER(colorspace)) {
    ସ୍ଥିତି SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        // Unknown, leave it alone
        ଭାଙ୍ଗ;
    }

    ବାଛ (access) {
    ସ୍ଥିତି SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SlowBlitPixelAccess_10Bit:
    {
        ବାଛ (fmt->format) {
        ସ୍ଥିତି SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ସ୍ଥିତି SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ସ୍ଥିତି SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            pixelvalue = 0;
            ଭାଙ୍ଗ;
        }
        *(Uint32 *)pixels = pixelvalue;
        ଭାଙ୍ଗ;
    }
    ସ୍ଥିତି SlowBlitPixelAccess_Large:
        ବାଛ (SDL_PIXELORDER(fmt->format)) {
        ସ୍ଥିତି SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ଭାଙ୍ଗ;
        }
        ବାଛ (SDL_PIXELTYPE(fmt->format)) {
        ସ୍ଥିତି SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ଯଦି (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            ଯଦି (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_PIXELTYPE_ARRAYF32:
            ((ଦଶମିକ *)pixels)[0] = v[0];
            ((ଦଶମିକ *)pixels)[1] = v[1];
            ((ଦଶମିକ *)pixels)[2] = v[2];
            ଯଦି (fmt->bytes_per_pixel == 16) {
                ((ଦଶମିକ *)pixels)[3] = v[3];
            }
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            // Unknown array type
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;
    }
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    SDL_TonemapOperator op;

    ସଂଘ {
        ସଂରଚନା {
            ଦଶମିକ scale;
        } linear;

        ସଂରଚନା {
            ଦଶମିକ a;
            ଦଶମିକ b;
            ଅଚଳ ଦଶମିକ *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

ସ୍ଥିର ଶୂନ୍ୟ TonemapLinear(ଦଶମିକ *r, ଦଶମିକ *g, ଦଶମିକ *b, ଦଶମିକ scale)
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
ସ୍ଥିର ଶୂନ୍ୟ TonemapChrome(ଦଶମିକ *r, ଦଶମିକ *g, ଦଶମିକ *b, ଦଶମିକ tonemap_a, ଦଶମିକ tonemap_b)
{
    ଦଶମିକ v1 = *r;
    ଦଶମିକ v2 = *g;
    ଦଶମିକ v3 = *b;
    ଦଶମିକ vmax = SDL_max(v1, SDL_max(v2, v3));

    ଯଦି (vmax > 0.0f) {
        ଦଶମିକ scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ ApplyTonemap(SDL_TonemapContext *ctx, ଦଶମିକ *r, ଦଶମିକ *g, ଦଶମିକ *b)
{
    ବାଛ (ctx->op) {
    ସ୍ଥିତି SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TONEMAP_CHROME:
        ଯଦି (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
ଶୂନ୍ୟ SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = info->flags;
    ଅଚଳ Uint32 modulateR = info->r;
    ଅଚଳ Uint32 modulateG = info->g;
    ଅଚଳ Uint32 modulateB = info->b;
    ଅଚଳ Uint32 modulateA = info->a;
    ଦଶମିକ srcR, srcG, srcB, srcA;
    ଦଶମିକ dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ଅଚଳ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ଅଚଳ SDL_Palette *src_pal = info->src_pal;
    ଅଚଳ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ଅଚଳ SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcbpp = src_fmt->bytes_per_pixel;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ଅଚଳ ଦଶମିକ *color_primaries_matrix = ଖାଲି;
    ଦଶମିକ src_white_point;
    ଦଶମିକ dst_white_point;
    ଦଶମିକ dst_headroom;
    ଦଶମିକ src_headroom;
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
    ଯଦି (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    ଯଦି (src_headroom > dst_headroom) {
        ଅଚଳ ଅକ୍ଷର *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ଖାଲି);
        ଯଦି (tonemap_operator) {
            ଯଦି (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (ଦଶମିକ)SDL_atof(tonemap_operator + 2);
            } ଅନ୍ୟଥା ଯଦି (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } ଅନ୍ୟଥା ଯଦି (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } ଅନ୍ୟଥା {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        ଯଦି (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            ଯଦି (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    ଯଦି (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    ଯଦି (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    ଯେତେବେଳେ (info->dst_h--) {
        Uint8 *src = ଖାଲି;
        Uint8 *dst = info->dst;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ଯେତେବେଳେ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            ଯଦି (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            ଯଦି (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            ଯଦି (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            ଯଦି ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } ଅନ୍ୟଥା {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            ଯଦି (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ଯଦି (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ଯଦି (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                ଯଦି (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            ବାଛ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            ସ୍ଥିତି 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                ଭାଙ୍ଗ;
            }

            ଯଦି (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                ଯଦି (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
            } ଅନ୍ୟଥା {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


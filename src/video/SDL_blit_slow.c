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
#include "SDL_internal.h"

#include "SDL_surface_c.h"
#include "SDL_blit_slow.h"
#include "SDL_pixels_c.h"

typedef ga_nanaa
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

static SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    ᨀᨘ (SDL_BYTESPERPIXEL(format) > 4) {
        ᨀᨘᨒ SlowBlitPixelAccess_Large;
    } ᨀᨘᨁ ᨀᨘ (SDL_ISPIXELFORMAT_10BIT(format)) {
        ᨀᨘᨒ SlowBlitPixelAccess_10Bit;
    } ᨀᨘᨁ ᨀᨘ (format == SDL_PIXELFORMAT_INDEX8) {
        ᨀᨘᨒ SlowBlitPixelAccess_Index8;
    } ᨀᨘᨁ ᨀᨘ (SDL_ISPIXELFORMAT_ALPHA(format)) {
        ᨀᨘᨒ SlowBlitPixelAccess_RGBA;
    } ᨀᨘᨁ {
        ᨀᨘᨒ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
void SDL_Blit_Slow(SDL_BlitInfo *info)
{
    const puur_naa_nka flags = info->flags;
    const Uint32 modulateR = info->r;
    const Uint32 modulateG = info->g;
    const Uint32 modulateB = info->b;
    const Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    const SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    const SDL_Palette *src_pal = info->src_pal;
    const SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    const SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    puur_naa_nka srcbpp = src_fmt->bytes_per_pixel;
    puur_naa_nka dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    ᨀᨘ (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    ᨀᨛ (info->dst_h--) {
        Uint8 *src = NULL;
        Uint8 *dst = info->dst;
        puur_naa_nka n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ᨀᨛ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            switch (src_access) {
            pak_sa SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                bha_nga;
            pak_sa SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                bha_nga;
            pak_sa SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                bha_nga;
            pak_sa SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                switch (src_fmt->format) {
                pak_sa SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    bha_nga;
                pak_sa SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    bha_nga;
                pak_sa SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    bha_nga;
                pak_sa SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    bha_nga;
                default:
                    bha_nga;
                }
                bha_nga;
            pak_sa SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                bha_nga;
            }

            ᨀᨘ (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                ᨀᨘ (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                ᨀᨘ ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    continue;
                }
            }
            ᨀᨘ (flags & SDL_COPY_BLEND_MASK) {
                switch (dst_access) {
                pak_sa SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    bha_nga;
                pak_sa SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    bha_nga;
                pak_sa SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    bha_nga;
                pak_sa SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    switch (dst_fmt->format) {
                    pak_sa SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        bha_nga;
                    pak_sa SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        bha_nga;
                    pak_sa SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        bha_nga;
                    pak_sa SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        bha_nga;
                    default:
                        bha_nga;
                    }
                    bha_nga;
                pak_sa SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    bha_nga;
                }
            } ᨀᨘᨁ {
                // don't care
            }

            ᨀᨘ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ᨀᨘ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ᨀᨘ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                ᨀᨘ (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            switch (flags & SDL_COPY_BLEND_MASK) {
            pak_sa 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                bha_nga;
            pak_sa SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                bha_nga;
            pak_sa SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                ᨀᨘ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                ᨀᨘ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                ᨀᨘ (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ᨀᨘ (dstA > 255) {
                    dstA = 255;
                }
                bha_nga;
            pak_sa SDL_COPY_ADD:
            pak_sa SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                ᨀᨘ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                ᨀᨘ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                ᨀᨘ (dstB > 255) {
                    dstB = 255;
                }
                bha_nga;
            pak_sa SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                bha_nga;
            pak_sa SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                ᨀᨘ (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                ᨀᨘ (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                ᨀᨘ (dstB > 255) {
                    dstB = 255;
                }
                bha_nga;
            }

            switch (dst_access) {
            pak_sa SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                ᨀᨘ (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                bha_nga;
            pak_sa SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                bha_nga;
            pak_sa SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                bha_nga;
            pak_sa SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                switch (dst_fmt->format) {
                pak_sa SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                pak_sa SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    bha_nga;
                pak_sa SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                pak_sa SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    bha_nga;
                default:
                    pixelvalue = 0;
                    bha_nga;
                }
                *(Uint32 *)dst = pixelvalue;
                bha_nga;
            }
            pak_sa SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                bha_nga;
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
typedef sa_ngha
{
    Uint32 u;
    float f;
    sa_nracanaa
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4214)
#endif

typedef sa_ngha
{
    Uint16 u;
    sa_nracanaa
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(pop)
#endif

static float half_to_float(Uint16 unValue)
{
    static const FP32 magic = { (254 - 15) << 23 };
    static const FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = unValue;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    ᨀᨘ (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    ᨀᨘᨒ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
static Uint16 float_to_half(float a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, parimaa_na(ia));

    ir = (ia >> 16) & 0x8000;
    ᨀᨘ ((ia & 0x7f800000) == 0x7f800000) {
        ᨀᨘ ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } ᨀᨘᨁ {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } ᨀᨘᨁ ᨀᨘ ((ia & 0x7f800000) >= 0x33000000) {
        puur_naa_nka shift = (puur_naa_nka)((ia >> 23) & 0xff) - 127;
        ᨀᨘ (shift > 15) {
            ir |= 0x7c00; // infinity
        } ᨀᨘᨁ {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            ᨀᨘ (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } ᨀᨘᨁ { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            ᨀᨘ ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    ᨀᨘᨒ ir;
}

static void ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, const SDL_PixelFormatDetails *fmt, const SDL_Palette *pal, SDL_Colorspace colorspace, float SDR_white_point,
                           float *outR, float *outG, float *outB, float *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    float fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    float v[4];

    switch (access) {
    pak_sa SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (float)pal->colors[pixelvalue].r / 255.0f;
        fG = (float)pal->colors[pixelvalue].g / 255.0f;
        fB = (float)pal->colors[pixelvalue].b / 255.0f;
        fA = (float)pal->colors[pixelvalue].a / 255.0f;
        bha_nga;
    pak_sa SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (float)R / 255.0f;
        fG = (float)G / 255.0f;
        fB = (float)B / 255.0f;
        fA = 1.0f;
        bha_nga;
    pak_sa SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (float)R / 255.0f;
        fG = (float)G / 255.0f;
        fB = (float)B / 255.0f;
        fA = (float)A / 255.0f;
        bha_nga;
    pak_sa SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        switch (fmt->format) {
        pak_sa SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            bha_nga;
        pak_sa SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            bha_nga;
        pak_sa SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            bha_nga;
        pak_sa SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            bha_nga;
        default:
            fR = fG = fB = fA = 0.0f;
            bha_nga;
        }
        bha_nga;
    pak_sa SlowBlitPixelAccess_Large:
        switch (SDL_PIXELTYPE(fmt->format)) {
        pak_sa SDL_PIXELTYPE_ARRAYU16:
            v[0] = (float)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (float)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (float)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            ᨀᨘ (fmt->bytes_per_pixel == 8) {
                v[3] = (float)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } ᨀᨘᨁ {
                v[3] = 1.0f;
            }
            bha_nga;
        pak_sa SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            ᨀᨘ (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } ᨀᨘᨁ {
                v[3] = 1.0f;
            }
            bha_nga;
        pak_sa SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((float *)pixels)[0];
            v[1] = ((float *)pixels)[1];
            v[2] = ((float *)pixels)[2];
            ᨀᨘ (fmt->bytes_per_pixel == 16) {
                v[3] = ((float *)pixels)[3];
            } ᨀᨘᨁ {
                v[3] = 1.0f;
            }
            bha_nga;
        default:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            bha_nga;
        }
        switch (SDL_PIXELORDER(fmt->format)) {
        pak_sa SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            bha_nga;
        pak_sa SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            bha_nga;
        pak_sa SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            bha_nga;
        pak_sa SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            bha_nga;
        pak_sa SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            bha_nga;
        pak_sa SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            bha_nga;
        default:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            bha_nga;
        }
        bha_nga;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    switch (SDL_COLORSPACETRANSFER(colorspace)) {
    pak_sa SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        bha_nga;
    pak_sa SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        bha_nga;
    pak_sa SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        bha_nga;
    default:
        // Unknown, leave it alone
        bha_nga;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

static void WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, const SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, float SDR_white_point,
                            float fR, float fG, float fB, float fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    float v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    switch (SDL_COLORSPACETRANSFER(colorspace)) {
    pak_sa SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        bha_nga;
    pak_sa SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        bha_nga;
    pak_sa SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        bha_nga;
    default:
        // Unknown, leave it alone
        bha_nga;
    }

    switch (access) {
    pak_sa SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        bha_nga;
    pak_sa SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        bha_nga;
    pak_sa SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        bha_nga;
    pak_sa SlowBlitPixelAccess_10Bit:
    {
        switch (fmt->format) {
        pak_sa SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        pak_sa SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            bha_nga;
        pak_sa SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        pak_sa SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            bha_nga;
        default:
            pixelvalue = 0;
            bha_nga;
        }
        *(Uint32 *)pixels = pixelvalue;
        bha_nga;
    }
    pak_sa SlowBlitPixelAccess_Large:
        switch (SDL_PIXELORDER(fmt->format)) {
        pak_sa SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            bha_nga;
        pak_sa SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            bha_nga;
        pak_sa SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            bha_nga;
        pak_sa SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            bha_nga;
        pak_sa SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            bha_nga;
        pak_sa SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            bha_nga;
        default:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            bha_nga;
        }
        switch (SDL_PIXELTYPE(fmt->format)) {
        pak_sa SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ᨀᨘ (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            bha_nga;
        pak_sa SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            ᨀᨘ (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            bha_nga;
        pak_sa SDL_PIXELTYPE_ARRAYF32:
            ((float *)pixels)[0] = v[0];
            ((float *)pixels)[1] = v[1];
            ((float *)pixels)[2] = v[2];
            ᨀᨘ (fmt->bytes_per_pixel == 16) {
                ((float *)pixels)[3] = v[3];
            }
            bha_nga;
        default:
            // Unknown array type
            bha_nga;
        }
        bha_nga;
    }
}

typedef ga_nanaa
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

typedef sa_nracanaa
{
    SDL_TonemapOperator op;

    sa_ngha {
        sa_nracanaa {
            float scale;
        } linear;

        sa_nracanaa {
            float a;
            float b;
            const float *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

static void TonemapLinear(float *r, float *g, float *b, float scale)
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
static void TonemapChrome(float *r, float *g, float *b, float tonemap_a, float tonemap_b)
{
    float v1 = *r;
    float v2 = *g;
    float v3 = *b;
    float vmax = SDL_max(v1, SDL_max(v2, v3));

    ᨀᨘ (vmax > 0.0f) {
        float scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

static void ApplyTonemap(SDL_TonemapContext *ctx, float *r, float *g, float *b)
{
    switch (ctx->op) {
    pak_sa SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        bha_nga;
    pak_sa SDL_TONEMAP_CHROME:
        ᨀᨘ (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        bha_nga;
    default:
        bha_nga;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
void SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    const puur_naa_nka flags = info->flags;
    const Uint32 modulateR = info->r;
    const Uint32 modulateG = info->g;
    const Uint32 modulateB = info->b;
    const Uint32 modulateA = info->a;
    float srcR, srcG, srcB, srcA;
    float dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    const SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    const SDL_Palette *src_pal = info->src_pal;
    const SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    const SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    puur_naa_nka srcbpp = src_fmt->bytes_per_pixel;
    puur_naa_nka dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    const float *color_primaries_matrix = NULL;
    float src_white_point;
    float dst_white_point;
    float dst_headroom;
    float src_headroom;
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
    ᨀᨘ (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    ᨀᨘ (src_headroom > dst_headroom) {
        const var_na *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, NULL);
        ᨀᨘ (tonemap_operator) {
            ᨀᨘ (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (float)SDL_atof(tonemap_operator + 2);
            } ᨀᨘᨁ ᨀᨘ (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } ᨀᨘᨁ ᨀᨘ (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } ᨀᨘᨁ {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        ᨀᨘ (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            ᨀᨘ (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    ᨀᨘ (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    ᨀᨘ (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    ᨀᨛ (info->dst_h--) {
        Uint8 *src = NULL;
        Uint8 *dst = info->dst;
        puur_naa_nka n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ᨀᨛ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            ᨀᨘ (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            ᨀᨘ (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            ᨀᨘ (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            ᨀᨘ ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } ᨀᨘᨁ {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            ᨀᨘ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ᨀᨘ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ᨀᨘ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                ᨀᨘ (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            switch (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            pak_sa 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                bha_nga;
            pak_sa SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                bha_nga;
            pak_sa SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                bha_nga;
            pak_sa SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                bha_nga;
            pak_sa SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                bha_nga;
            }

            ᨀᨘ (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                ᨀᨘ (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
            } ᨀᨘᨁ {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


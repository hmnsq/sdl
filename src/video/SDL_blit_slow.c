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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit_slow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

ਸਥਿਰ SlowBlitPixelAccess Get_Pixel_Access_ਵਿਧੀ(SDL_PixelFormat format)
{
    ਜੇ (SDL_BYTESPERPIXEL(format) > 4) {
        ਵਾਪਸ SlowBlitPixelAccess_Large;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_10_ਦੋਆਧਾਰੀ_ਅੰਕ(format)) {
        ਵਾਪਸ Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ;
    } ਨਹੀਂਤਾਂ ਜੇ (format == SDL_PIXELFORMAT_INDEX8) {
        ਵਾਪਸ SlowBlitPixelAccess_Index8;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_ALPHA(format)) {
        ਵਾਪਸ SlowBlitPixelAccess_RGBA;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
ਖਾਲੀ SDL_Blit_Slow(SDL_BlitInfo *info)
{
    ਅਚਲ ਪੂਰਨ flags = info->flags;
    ਅਚਲ Uint32 modulateR = info->r;
    ਅਚਲ Uint32 modulateG = info->g;
    ਅਚਲ Uint32 modulateB = info->b;
    ਅਚਲ Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ਅਚਲ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ਅਚਲ SDL_Palette *src_pal = info->src_pal;
    ਅਚਲ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ਅਚਲ SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_ਸਾਰਣੀ *palette_map = info->palette_map;
    ਪੂਰਨ srcbpp = src_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    ਪੂਰਨ dstbpp = dst_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 ਆਖਰੀ_pixel = 0;
    Uint8 ਆਖਰੀ_ਸੂਚਕਾਂਕ = 0;

    src_access = Get_Pixel_Access_ਵਿਧੀ(src_fmt->format);
    dst_access = Get_Pixel_Access_ਵਿਧੀ(dst_fmt->format);
    ਜੇ (dst_access == SlowBlitPixelAccess_Index8) {
        ਆਖਰੀ_ਸੂਚਕਾਂਕ = SDL_LookupRGBAColor(palette_map, ਆਖਰੀ_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    ਜਦੋਂ (info->dst_h--) {
        Uint8 *src = ਨਿਰਾ;
        Uint8 *dst = info->dst;
        ਪੂਰਨ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ਜਦੋਂ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ਚੋਣ (src_access) {
            ਹਾਲਤ SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                ਰੋਕੋ;
            ਹਾਲਤ SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                ਰੋਕੋ;
            ਹਾਲਤ SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                ਰੋਕੋ;
            ਹਾਲਤ Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ:
                srcpixel = *((Uint32 *)(src));
                ਚੋਣ (src_fmt->format) {
                ਹਾਲਤ SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ਰੋਕੋ;
                ਹਾਲਤ SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    ਰੋਕੋ;
                ਹਾਲਤ SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ਰੋਕੋ;
                ਹਾਲਤ SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    ਰੋਕੋ;
                ਮੂਲ:
                    ਰੋਕੋ;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ਰੋਕੋ;
            }

            ਜੇ (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                ਜੇ (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                ਜੇ ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    ਜਾਰੀ;
                }
            }
            ਜੇ (flags & SDL_COPY_BLEND_ਨਕਾਬ) {
                ਚੋਣ (dst_access) {
                ਹਾਲਤ SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    ਰੋਕੋ;
                ਹਾਲਤ SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    ਰੋਕੋ;
                ਹਾਲਤ SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    ਰੋਕੋ;
                ਹਾਲਤ Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ:
                    dstpixel = *((Uint32 *)(dst));
                    ਚੋਣ (dst_fmt->format) {
                    ਹਾਲਤ SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ਰੋਕੋ;
                    ਹਾਲਤ SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        ਰੋਕੋ;
                    ਹਾਲਤ SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ਰੋਕੋ;
                    ਹਾਲਤ SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        ਰੋਕੋ;
                    ਮੂਲ:
                        ਰੋਕੋ;
                    }
                    ਰੋਕੋ;
                ਹਾਲਤ SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    ਰੋਕੋ;
                }
            } ਨਹੀਂਤਾਂ {
                // don't care
            }

            ਜੇ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ਜੇ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ਜੇ (flags & (SDL_COPY_BLEND | SDL_COPY_ਜੋੜੋ)) {
                ਜੇ (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            ਚੋਣ (flags & SDL_COPY_BLEND_ਨਕਾਬ) {
            ਹਾਲਤ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                ਜੇ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                ਜੇ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                ਜੇ (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                ਜੇ (dstA > 255) {
                    dstA = 255;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_ਜੋੜੋ:
            ਹਾਲਤ SDL_COPY_ਜੋੜੋ_PREMULTIPLIED:
                dstR = srcR + dstR;
                ਜੇ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                ਜੇ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                ਜੇ (dstB > 255) {
                    dstB = 255;
                }
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                ਜੇ (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                ਜੇ (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                ਜੇ (dstB > 255) {
                    dstB = 255;
                }
                ਰੋਕੋ;
            }

            ਚੋਣ (dst_access) {
            ਹਾਲਤ SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                ਜੇ (dstpixel != ਆਖਰੀ_pixel) {
                    ਆਖਰੀ_pixel = dstpixel;
                    ਆਖਰੀ_ਸੂਚਕਾਂਕ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = ਆਖਰੀ_ਸੂਚਕਾਂਕ;
                ਰੋਕੋ;
            ਹਾਲਤ SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                ਰੋਕੋ;
            ਹਾਲਤ SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                ਰੋਕੋ;
            ਹਾਲਤ Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ:
            {
                Uint32 pixelvalue;
                ਚੋਣ (dst_fmt->format) {
                ਹਾਲਤ SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ਹਾਲਤ SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ਰੋਕੋ;
                ਹਾਲਤ SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                ਹਾਲਤ SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    ਰੋਕੋ;
                ਮੂਲ:
                    pixelvalue = 0;
                    ਰੋਕੋ;
                }
                *(Uint32 *)dst = pixelvalue;
                ਰੋਕੋ;
            }
            ਹਾਲਤ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                ਰੋਕੋ;
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
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸੰਘ
{
    Uint32 u;
    ਦਸ਼ਮਲਵ f;
    ਬਣਤਰ
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਧੱਕੋ)
#ਹਦਾਇਤ warning(disable:4214)
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸੰਘ
{
    Uint16 u;
    ਬਣਤਰ
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਕੱਢੋ)
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਦਸ਼ਮਲਵ half_ਮੰਜ਼ਿਲ_float(Uint16 un_ਮੁੱਲ)
{
    ਸਥਿਰ ਅਚਲ FP32 magic = { (254 - 15) << 23 };
    ਸਥਿਰ ਅਚਲ FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_ਮੁੱਲ;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    ਜੇ (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    ਵਾਪਸ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
ਸਥਿਰ Uint16 float_ਮੰਜ਼ਿਲ_half(ਦਸ਼ਮਲਵ a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, ਆਕਾਰ(ia));

    ir = (ia >> 16) & 0x8000;
    ਜੇ ((ia & 0x7f800000) == 0x7f800000) {
        ਜੇ ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } ਨਹੀਂਤਾਂ {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } ਨਹੀਂਤਾਂ ਜੇ ((ia & 0x7f800000) >= 0x33000000) {
        ਪੂਰਨ ਖਿਸਕਾਓ = (ਪੂਰਨ)((ia >> 23) & 0xff) - 127;
        ਜੇ (ਖਿਸਕਾਓ > 15) {
            ir |= 0x7c00; // infinity
        } ਨਹੀਂਤਾਂ {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            ਜੇ (ਖਿਸਕਾਓ < -14) { // denormal
                ir |= ia >> (-1 - ਖਿਸਕਾਓ);
                ia = ia << (32 - (-1 - ਖਿਸਕਾਓ));
            } ਨਹੀਂਤਾਂ { //ਸਾਧਾਰਨ
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + ਖਿਸਕਾਓ) << 10);
            }
            // IEEE-754 round to nearest of even
            ਜੇ ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    ਵਾਪਸ ir;
}

ਸਥਿਰ ਖਾਲੀ ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ਅਚਲ SDL_PixelFormatDetails *fmt, ਅਚਲ SDL_Palette *pal, SDL_Colorspace colorspace, ਦਸ਼ਮਲਵ SDR_white_ਬਿੰਦੂ,
                           ਦਸ਼ਮਲਵ *ਬਾਹਰਲਾ_R, ਦਸ਼ਮਲਵ *ਬਾਹਰਲਾ_G, ਦਸ਼ਮਲਵ *ਬਾਹਰਲਾ_B, ਦਸ਼ਮਲਵ *ਬਾਹਰਲਾ_A)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    ਦਸ਼ਮਲਵ fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    ਦਸ਼ਮਲਵ v[4];

    ਚੋਣ (access) {
    ਹਾਲਤ SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (ਦਸ਼ਮਲਵ)pal->colors[pixelvalue].r / 255.0f;
        fG = (ਦਸ਼ਮਲਵ)pal->colors[pixelvalue].g / 255.0f;
        fB = (ਦਸ਼ਮਲਵ)pal->colors[pixelvalue].b / 255.0f;
        fA = (ਦਸ਼ਮਲਵ)pal->colors[pixelvalue].a / 255.0f;
        ਰੋਕੋ;
    ਹਾਲਤ SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel, fmt, pixelvalue, R, G, B);
        fR = (ਦਸ਼ਮਲਵ)R / 255.0f;
        fG = (ਦਸ਼ਮਲਵ)G / 255.0f;
        fB = (ਦਸ਼ਮਲਵ)B / 255.0f;
        fA = 1.0f;
        ਰੋਕੋ;
    ਹਾਲਤ SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (ਦਸ਼ਮਲਵ)R / 255.0f;
        fG = (ਦਸ਼ਮਲਵ)G / 255.0f;
        fB = (ਦਸ਼ਮਲਵ)B / 255.0f;
        fA = (ਦਸ਼ਮਲਵ)A / 255.0f;
        ਰੋਕੋ;
    ਹਾਲਤ Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ:
        pixelvalue = *((Uint32 *)pixels);
        ਚੋਣ (fmt->format) {
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            ਰੋਕੋ;
        ਮੂਲ:
            fR = fG = fB = fA = 0.0f;
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    ਹਾਲਤ SlowBlitPixelAccess_Large:
        ਚੋਣ (SDL_PIXELTYPE(fmt->format)) {
        ਹਾਲਤ SDL_PIXELTYPE_ARRAYU16:
            v[0] = (ਦਸ਼ਮਲਵ)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (ਦਸ਼ਮਲਵ)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (ਦਸ਼ਮਲਵ)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            ਜੇ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 8) {
                v[3] = (ਦਸ਼ਮਲਵ)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } ਨਹੀਂਤਾਂ {
                v[3] = 1.0f;
            }
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_ਮੰਜ਼ਿਲ_float(((Uint16 *)pixels)[0]);
            v[1] = half_ਮੰਜ਼ਿਲ_float(((Uint16 *)pixels)[1]);
            v[2] = half_ਮੰਜ਼ਿਲ_float(((Uint16 *)pixels)[2]);
            ਜੇ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 8) {
                v[3] = half_ਮੰਜ਼ਿਲ_float(((Uint16 *)pixels)[3]);
            } ਨਹੀਂਤਾਂ {
                v[3] = 1.0f;
            }
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((ਦਸ਼ਮਲਵ *)pixels)[0];
            v[1] = ((ਦਸ਼ਮਲਵ *)pixels)[1];
            v[2] = ((ਦਸ਼ਮਲਵ *)pixels)[2];
            ਜੇ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 16) {
                v[3] = ((ਦਸ਼ਮਲਵ *)pixels)[3];
            } ਨਹੀਂਤਾਂ {
                v[3] = 1.0f;
            }
            ਰੋਕੋ;
        ਮੂਲ:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ਰੋਕੋ;
        }
        ਚੋਣ (SDL_PIXELORDER(fmt->format)) {
        ਹਾਲਤ SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            ਰੋਕੋ;
        ਮੂਲ:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    ਚੋਣ (SDL_COLORSPACETRANSFER(colorspace)) {
    ਹਾਲਤ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBto_ਰੇਖਿਕ(fR);
        fG = SDL_s_RGBto_ਰੇਖਿਕ(fG);
        fB = SDL_s_RGBto_ਰੇਖਿਕ(fB);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_ਬਿੰਦੂ;
        fG = SDL_PQtoNits(fG) / SDR_white_ਬਿੰਦੂ;
        fB = SDL_PQtoNits(fB) / SDR_white_ਬਿੰਦੂ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TRANSFER_CHARACTERISTICS_ਰੇਖਿਕ:
        fR /= SDR_white_ਬਿੰਦੂ;
        fG /= SDR_white_ਬਿੰਦੂ;
        fB /= SDR_white_ਬਿੰਦੂ;
        ਰੋਕੋ;
    ਮੂਲ:
        // Unknown, leave it alone
        ਰੋਕੋ;
    }

    *ਬਾਹਰਲਾ_R = fR;
    *ਬਾਹਰਲਾ_G = fG;
    *ਬਾਹਰਲਾ_B = fB;
    *ਬਾਹਰਲਾ_A = fA;
}

ਸਥਿਰ ਖਾਲੀ WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, ਅਚਲ SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, ਦਸ਼ਮਲਵ SDR_white_ਬਿੰਦੂ,
                            ਦਸ਼ਮਲਵ fR, ਦਸ਼ਮਲਵ fG, ਦਸ਼ਮਲਵ fB, ਦਸ਼ਮਲਵ fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    ਦਸ਼ਮਲਵ v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    ਚੋਣ (SDL_COLORSPACETRANSFER(colorspace)) {
    ਹਾਲਤ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_s_RGBfrom_ਰੇਖਿਕ(fR);
        fG = SDL_s_RGBfrom_ਰੇਖਿਕ(fG);
        fB = SDL_s_RGBfrom_ਰੇਖਿਕ(fB);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_ਬਿੰਦੂ);
        fG = SDL_PQfromNits(fG * SDR_white_ਬਿੰਦੂ);
        fB = SDL_PQfromNits(fB * SDR_white_ਬਿੰਦੂ);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TRANSFER_CHARACTERISTICS_ਰੇਖਿਕ:
        fR *= SDR_white_ਬਿੰਦੂ;
        fG *= SDR_white_ਬਿੰਦੂ;
        fB *= SDR_white_ਬਿੰਦੂ;
        ਰੋਕੋ;
    ਮੂਲ:
        // Unknown, leave it alone
        ਰੋਕੋ;
    }

    ਚੋਣ (access) {
    ਹਾਲਤ SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        ਰੋਕੋ;
    ਹਾਲਤ SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel, fmt, R, G, B);
        ਰੋਕੋ;
    ਹਾਲਤ SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel, fmt, R, G, B, A);
        ਰੋਕੋ;
    ਹਾਲਤ Slow_Blit_Pixel_Access_10_ਦੋਆਧਾਰੀ_ਅੰਕ:
    {
        ਚੋਣ (fmt->format) {
        ਹਾਲਤ SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ਹਾਲਤ SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        ਹਾਲਤ SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            ਰੋਕੋ;
        ਮੂਲ:
            pixelvalue = 0;
            ਰੋਕੋ;
        }
        *(Uint32 *)pixels = pixelvalue;
        ਰੋਕੋ;
    }
    ਹਾਲਤ SlowBlitPixelAccess_Large:
        ਚੋਣ (SDL_PIXELORDER(fmt->format)) {
        ਹਾਲਤ SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            ਰੋਕੋ;
        ਮੂਲ:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            ਰੋਕੋ;
        }
        ਚੋਣ (SDL_PIXELTYPE(fmt->format)) {
        ਹਾਲਤ SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ਜੇ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_ਮੰਜ਼ਿਲ_half(v[0]);
            ((Uint16 *)pixels)[1] = float_ਮੰਜ਼ਿਲ_half(v[1]);
            ((Uint16 *)pixels)[2] = float_ਮੰਜ਼ਿਲ_half(v[2]);
            ਜੇ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_ਮੰਜ਼ਿਲ_half(v[3]);
            }
            ਰੋਕੋ;
        ਹਾਲਤ SDL_PIXELTYPE_ARRAYF32:
            ((ਦਸ਼ਮਲਵ *)pixels)[0] = v[0];
            ((ਦਸ਼ਮਲਵ *)pixels)[1] = v[1];
            ((ਦਸ਼ਮਲਵ *)pixels)[2] = v[2];
            ਜੇ (fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel == 16) {
                ((ਦਸ਼ਮਲਵ *)pixels)[3] = v[3];
            }
            ਰੋਕੋ;
        ਮੂਲ:
            // Unknown array type
            ਰੋਕੋ;
        }
        ਰੋਕੋ;
    }
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_ਰੇਖਿਕ,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_TonemapOperator op;

    ਸੰਘ {
        ਬਣਤਰ {
            ਦਸ਼ਮਲਵ scale;
        } ਰੇਖਿਕ;

        ਬਣਤਰ {
            ਦਸ਼ਮਲਵ a;
            ਦਸ਼ਮਲਵ b;
            ਅਚਲ ਦਸ਼ਮਲਵ *color_primaries_ਮੈਟ੍ਰਿਕਸ;
        } chrome;

    } ਅੰਕੜੇ;

} SDL_TonemapContext;

ਸਥਿਰ ਖਾਲੀ Tonemap_ਰੇਖਿਕ(ਦਸ਼ਮਲਵ *r, ਦਸ਼ਮਲਵ *g, ਦਸ਼ਮਲਵ *b, ਦਸ਼ਮਲਵ scale)
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
ਸਥਿਰ ਖਾਲੀ TonemapChrome(ਦਸ਼ਮਲਵ *r, ਦਸ਼ਮਲਵ *g, ਦਸ਼ਮਲਵ *b, ਦਸ਼ਮਲਵ tonemap_a, ਦਸ਼ਮਲਵ tonemap_b)
{
    ਦਸ਼ਮਲਵ v1 = *r;
    ਦਸ਼ਮਲਵ v2 = *g;
    ਦਸ਼ਮਲਵ v3 = *b;
    ਦਸ਼ਮਲਵ vmax = SDL_max(v1, SDL_max(v2, v3));

    ਜੇ (vmax > 0.0f) {
        ਦਸ਼ਮਲਵ scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        Tonemap_ਰੇਖਿਕ(r, g, b, scale);
    }
}

ਸਥਿਰ ਖਾਲੀ ApplyTonemap(SDL_TonemapContext *ctx, ਦਸ਼ਮਲਵ *r, ਦਸ਼ਮਲਵ *g, ਦਸ਼ਮਲਵ *b)
{
    ਚੋਣ (ctx->op) {
    ਹਾਲਤ SDL_TONEMAP_ਰੇਖਿਕ:
        Tonemap_ਰੇਖਿਕ(r, g, b, ctx->ਅੰਕੜੇ.ਰੇਖਿਕ.scale);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TONEMAP_CHROME:
        ਜੇ (ctx->ਅੰਕੜੇ.chrome.color_primaries_ਮੈਟ੍ਰਿਕਸ) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->ਅੰਕੜੇ.chrome.color_primaries_ਮੈਟ੍ਰਿਕਸ);
        }
        TonemapChrome(r, g, b, ctx->ਅੰਕੜੇ.chrome.a, ctx->ਅੰਕੜੇ.chrome.b);
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
ਖਾਲੀ SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    ਅਚਲ ਪੂਰਨ flags = info->flags;
    ਅਚਲ Uint32 modulateR = info->r;
    ਅਚਲ Uint32 modulateG = info->g;
    ਅਚਲ Uint32 modulateB = info->b;
    ਅਚਲ Uint32 modulateA = info->a;
    ਦਸ਼ਮਲਵ srcR, srcG, srcB, srcA;
    ਦਸ਼ਮਲਵ dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    ਅਚਲ SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    ਅਚਲ SDL_Palette *src_pal = info->src_pal;
    ਅਚਲ SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    ਅਚਲ SDL_Palette *dst_pal = info->dst_pal;
    SDL_Hash_ਸਾਰਣੀ *palette_map = info->palette_map;
    ਪੂਰਨ srcbpp = src_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    ਪੂਰਨ dstbpp = dst_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    ਅਚਲ ਦਸ਼ਮਲਵ *color_primaries_ਮੈਟ੍ਰਿਕਸ = ਨਿਰਾ;
    ਦਸ਼ਮਲਵ src_white_ਬਿੰਦੂ;
    ਦਸ਼ਮਲਵ dst_white_ਬਿੰਦੂ;
    ਦਸ਼ਮਲਵ dst_headroom;
    ਦਸ਼ਮਲਵ src_headroom;
    SDL_TonemapContext tonemap;
    Uint32 ਆਖਰੀ_pixel = 0;
    Uint8 ਆਖਰੀ_ਸੂਚਕਾਂਕ = 0;

    src_colorspace = info->src_surface->colorspace;
    dst_colorspace = info->dst_surface->colorspace;
    src_primaries = SDL_COLORSPACEPRIMARIES(src_colorspace);
    dst_primaries = SDL_COLORSPACEPRIMARIES(dst_colorspace);

    src_white_ਬਿੰਦੂ = SDL_Get_Surface_SDRWhite_ਬਿੰਦੂ(info->src_surface, src_colorspace);
    dst_white_ਬਿੰਦੂ = SDL_Get_Surface_SDRWhite_ਬਿੰਦੂ(info->dst_surface, dst_colorspace);
    src_headroom = SDL_GetSurfaceHDRHeadroom(info->src_surface, src_colorspace);
    dst_headroom = SDL_GetSurfaceHDRHeadroom(info->dst_surface, dst_colorspace);
    ਜੇ (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_ਸੈੱਟ_Float_Property(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    ਜੇ (src_headroom > dst_headroom) {
        ਅਚਲ ਅੱਖਰ *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ਨਿਰਾ);
        ਜੇ (tonemap_operator) {
            ਜੇ (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_ਰੇਖਿਕ;
                tonemap.ਅੰਕੜੇ.ਰੇਖਿਕ.scale = (ਦਸ਼ਮਲਵ)SDL_atof(tonemap_operator + 2);
            } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } ਨਹੀਂਤਾਂ {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        ਜੇ (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.ਅੰਕੜੇ.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.ਅੰਕੜੇ.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.ਅੰਕੜੇ.chrome.color_primaries_ਮੈਟ੍ਰਿਕਸ = SDL_Get_Color_Primaries_Conversion_ਮੈਟ੍ਰਿਕਸ(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            ਜੇ (tonemap.ਅੰਕੜੇ.chrome.color_primaries_ਮੈਟ੍ਰਿਕਸ) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    ਜੇ (src_primaries != dst_primaries) {
        color_primaries_ਮੈਟ੍ਰਿਕਸ = SDL_Get_Color_Primaries_Conversion_ਮੈਟ੍ਰਿਕਸ(src_primaries, dst_primaries);
    }

    src_access = Get_Pixel_Access_ਵਿਧੀ(src_fmt->format);
    dst_access = Get_Pixel_Access_ਵਿਧੀ(dst_fmt->format);
    ਜੇ (dst_access == SlowBlitPixelAccess_Index8) {
        ਆਖਰੀ_ਸੂਚਕਾਂਕ = SDL_LookupRGBAColor(palette_map, ਆਖਰੀ_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    ਜਦੋਂ (info->dst_h--) {
        Uint8 *src = ਨਿਰਾ;
        Uint8 *dst = info->dst;
        ਪੂਰਨ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ਜਦੋਂ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_ਬਿੰਦੂ, &srcR, &srcG, &srcB, &srcA);

            ਜੇ (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            ਜੇ (color_primaries_ਮੈਟ੍ਰਿਕਸ) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_ਮੈਟ੍ਰਿਕਸ);
            }

            ਜੇ (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            ਜੇ ((flags & (SDL_COPY_BLEND | SDL_COPY_ਜੋੜੋ | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_ਬਿੰਦੂ, &dstR, &dstG, &dstB, &dstA);
            } ਨਹੀਂਤਾਂ {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            ਜੇ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            ਜੇ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            ਜੇ (flags & (SDL_COPY_BLEND | SDL_COPY_ਜੋੜੋ)) {
                ਜੇ (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            ਚੋਣ (flags & (SDL_COPY_BLEND | SDL_COPY_ਜੋੜੋ | SDL_COPY_MOD | SDL_COPY_MUL)) {
            ਹਾਲਤ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_ਜੋੜੋ:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                ਰੋਕੋ;
            ਹਾਲਤ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                ਰੋਕੋ;
            }

            ਜੇ (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_ਰੇਖਿਕ(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_ਰੇਖਿਕ(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_s_RGBfrom_ਰੇਖਿਕ(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                ਜੇ (dstpixel != ਆਖਰੀ_pixel) {
                    ਆਖਰੀ_pixel = dstpixel;
                    ਆਖਰੀ_ਸੂਚਕਾਂਕ = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = ਆਖਰੀ_ਸੂਚਕਾਂਕ;
            } ਨਹੀਂਤਾਂ {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_ਬਿੰਦੂ, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


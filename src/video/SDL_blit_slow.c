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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_surface_c.h"
#അന്തര്ഭാവ "SDL_blit_slow.h"
#അന്തര്ഭാവ "SDL_pixels_c.h"

തരനിർവചനം എണ്ണൽ
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

സ്ഥിതം SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    എങ്കിൽ (SDL_BYTESPERPIXEL(format) > 4) {
        തിരികെ SlowBlitPixelAccess_Large;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_10BIT(format)) {
        തിരികെ SlowBlitPixelAccess_10Bit;
    } അല്ലെങ്കിൽ എങ്കിൽ (format == SDL_PIXELFORMAT_INDEX8) {
        തിരികെ SlowBlitPixelAccess_Index8;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_ISPIXELFORMAT_ALPHA(format)) {
        തിരികെ SlowBlitPixelAccess_RGBA;
    } അല്ലെങ്കിൽ {
        തിരികെ SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
ശൂന്യം SDL_Blit_Slow(SDL_BlitInfo *info)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ flags = info->flags;
    സ്ഥിരം Uint32 modulateR = info->r;
    സ്ഥിരം Uint32 modulateG = info->g;
    സ്ഥിരം Uint32 modulateB = info->b;
    സ്ഥിരം Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    സ്ഥിരം SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    സ്ഥിരം SDL_Palette *src_pal = info->src_pal;
    സ്ഥിരം SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    സ്ഥിരം SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    പൂർണ്ണസംഖ്യ srcbpp = src_fmt->bytes_per_pixel;
    പൂർണ്ണസംഖ്യ dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    എങ്കിൽ (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    ആകുമ്പോൾ (info->dst_h--) {
        Uint8 *src = ശൂന്യ;
        Uint8 *dst = info->dst;
        പൂർണ്ണസംഖ്യ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ആകുമ്പോൾ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            തിരഞ്ഞെടുപ്പ് (src_access) {
            അവസ്ഥ SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                തിരഞ്ഞെടുപ്പ് (src_fmt->format) {
                അവസ്ഥ SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    നിർത്തുക;
                അവസ്ഥ SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    നിർത്തുക;
                അവസ്ഥ SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    നിർത്തുക;
                അവസ്ഥ SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    നിർത്തുക;
                സ്ഥിരസ്ഥിതി:
                    നിർത്തുക;
                }
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                നിർത്തുക;
            }

            എങ്കിൽ (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                എങ്കിൽ (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                എങ്കിൽ ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    തുടരുക;
                }
            }
            എങ്കിൽ (flags & SDL_COPY_BLEND_MASK) {
                തിരഞ്ഞെടുപ്പ് (dst_access) {
                അവസ്ഥ SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    നിർത്തുക;
                അവസ്ഥ SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    നിർത്തുക;
                അവസ്ഥ SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    നിർത്തുക;
                അവസ്ഥ SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    തിരഞ്ഞെടുപ്പ് (dst_fmt->format) {
                    അവസ്ഥ SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        നിർത്തുക;
                    അവസ്ഥ SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        നിർത്തുക;
                    അവസ്ഥ SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        നിർത്തുക;
                    അവസ്ഥ SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        നിർത്തുക;
                    സ്ഥിരസ്ഥിതി:
                        നിർത്തുക;
                    }
                    നിർത്തുക;
                അവസ്ഥ SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    നിർത്തുക;
                }
            } അല്ലെങ്കിൽ {
                // don't care
            }

            എങ്കിൽ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            എങ്കിൽ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            എങ്കിൽ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                എങ്കിൽ (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            തിരഞ്ഞെടുപ്പ് (flags & SDL_COPY_BLEND_MASK) {
            അവസ്ഥ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                എങ്കിൽ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                എങ്കിൽ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                എങ്കിൽ (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                എങ്കിൽ (dstA > 255) {
                    dstA = 255;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_ADD:
            അവസ്ഥ SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                എങ്കിൽ (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                എങ്കിൽ (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                എങ്കിൽ (dstB > 255) {
                    dstB = 255;
                }
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                എങ്കിൽ (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                എങ്കിൽ (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                എങ്കിൽ (dstB > 255) {
                    dstB = 255;
                }
                നിർത്തുക;
            }

            തിരഞ്ഞെടുപ്പ് (dst_access) {
            അവസ്ഥ SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                എങ്കിൽ (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                നിർത്തുക;
            അവസ്ഥ SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                തിരഞ്ഞെടുപ്പ് (dst_fmt->format) {
                അവസ്ഥ SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                അവസ്ഥ SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    നിർത്തുക;
                അവസ്ഥ SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                അവസ്ഥ SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    നിർത്തുക;
                സ്ഥിരസ്ഥിതി:
                    pixelvalue = 0;
                    നിർത്തുക;
                }
                *(Uint32 *)dst = pixelvalue;
                നിർത്തുക;
            }
            അവസ്ഥ SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                നിർത്തുക;
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
തരനിർവചനം സംഘം
{
    Uint32 u;
    ദശാംശം f;
    ഘടന
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(തള്ളുക)
#pragma warning(disable:4214)
#endif

തരനിർവചനം സംഘം
{
    Uint16 u;
    ഘടന
    {
        Uint16 Mantissa : 10;
        Uint16 Exponent : 5;
        Uint16 Sign : 1;
    } x;
} FP16;

#ifdef _MSC_VER
#pragma warning(എടുക്കുക)
#endif

സ്ഥിതം ദശാംശം half_to_float(Uint16 un_മൂല്യം)
{
    സ്ഥിതം സ്ഥിരം FP32 magic = { (254 - 15) << 23 };
    സ്ഥിതം സ്ഥിരം FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_മൂല്യം;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    എങ്കിൽ (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    തിരികെ o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
സ്ഥിതം Uint16 float_to_half(ദശാംശം a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, വലുപ്പം(ia));

    ir = (ia >> 16) & 0x8000;
    എങ്കിൽ ((ia & 0x7f800000) == 0x7f800000) {
        എങ്കിൽ ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } അല്ലെങ്കിൽ {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } അല്ലെങ്കിൽ എങ്കിൽ ((ia & 0x7f800000) >= 0x33000000) {
        പൂർണ്ണസംഖ്യ shift = (പൂർണ്ണസംഖ്യ)((ia >> 23) & 0xff) - 127;
        എങ്കിൽ (shift > 15) {
            ir |= 0x7c00; // infinity
        } അല്ലെങ്കിൽ {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            എങ്കിൽ (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } അല്ലെങ്കിൽ { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            എങ്കിൽ ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    തിരികെ ir;
}

സ്ഥിതം ശൂന്യം ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, സ്ഥിരം SDL_PixelFormatDetails *fmt, സ്ഥിരം SDL_Palette *pal, SDL_Colorspace colorspace, ദശാംശം SDR_white_point,
                           ദശാംശം *outR, ദശാംശം *outG, ദശാംശം *outB, ദശാംശം *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    ദശാംശം fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    ദശാംശം v[4];

    തിരഞ്ഞെടുപ്പ് (access) {
    അവസ്ഥ SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (ദശാംശം)pal->colors[pixelvalue].r / 255.0f;
        fG = (ദശാംശം)pal->colors[pixelvalue].g / 255.0f;
        fB = (ദശാംശം)pal->colors[pixelvalue].b / 255.0f;
        fA = (ദശാംശം)pal->colors[pixelvalue].a / 255.0f;
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (ദശാംശം)R / 255.0f;
        fG = (ദശാംശം)G / 255.0f;
        fB = (ദശാംശം)B / 255.0f;
        fA = 1.0f;
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (ദശാംശം)R / 255.0f;
        fG = (ദശാംശം)G / 255.0f;
        fB = (ദശാംശം)B / 255.0f;
        fA = (ദശാംശം)A / 255.0f;
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        തിരഞ്ഞെടുപ്പ് (fmt->format) {
        അവസ്ഥ SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            fR = fG = fB = fA = 0.0f;
            നിർത്തുക;
        }
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_Large:
        തിരഞ്ഞെടുപ്പ് (SDL_PIXELTYPE(fmt->format)) {
        അവസ്ഥ SDL_PIXELTYPE_ARRAYU16:
            v[0] = (ദശാംശം)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (ദശാംശം)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (ദശാംശം)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            എങ്കിൽ (fmt->bytes_per_pixel == 8) {
                v[3] = (ദശാംശം)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } അല്ലെങ്കിൽ {
                v[3] = 1.0f;
            }
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            എങ്കിൽ (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } അല്ലെങ്കിൽ {
                v[3] = 1.0f;
            }
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((ദശാംശം *)pixels)[0];
            v[1] = ((ദശാംശം *)pixels)[1];
            v[2] = ((ദശാംശം *)pixels)[2];
            എങ്കിൽ (fmt->bytes_per_pixel == 16) {
                v[3] = ((ദശാംശം *)pixels)[3];
            } അല്ലെങ്കിൽ {
                v[3] = 1.0f;
            }
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            നിർത്തുക;
        }
        തിരഞ്ഞെടുപ്പ് (SDL_PIXELORDER(fmt->format)) {
        അവസ്ഥ SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            നിർത്തുക;
        }
        നിർത്തുക;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    തിരഞ്ഞെടുപ്പ് (SDL_COLORSPACETRANSFER(colorspace)) {
    അവസ്ഥ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        നിർത്തുക;
    അവസ്ഥ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        നിർത്തുക;
    അവസ്ഥ SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        // Unknown, leave it alone
        നിർത്തുക;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

സ്ഥിതം ശൂന്യം WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, സ്ഥിരം SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, ദശാംശം SDR_white_point,
                            ദശാംശം fR, ദശാംശം fG, ദശാംശം fB, ദശാംശം fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    ദശാംശം v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    തിരഞ്ഞെടുപ്പ് (SDL_COLORSPACETRANSFER(colorspace)) {
    അവസ്ഥ SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        നിർത്തുക;
    അവസ്ഥ SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        നിർത്തുക;
    അവസ്ഥ SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        // Unknown, leave it alone
        നിർത്തുക;
    }

    തിരഞ്ഞെടുപ്പ് (access) {
    അവസ്ഥ SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        നിർത്തുക;
    അവസ്ഥ SlowBlitPixelAccess_10Bit:
    {
        തിരഞ്ഞെടുപ്പ് (fmt->format) {
        അവസ്ഥ SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        അവസ്ഥ SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        അവസ്ഥ SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            pixelvalue = 0;
            നിർത്തുക;
        }
        *(Uint32 *)pixels = pixelvalue;
        നിർത്തുക;
    }
    അവസ്ഥ SlowBlitPixelAccess_Large:
        തിരഞ്ഞെടുപ്പ് (SDL_PIXELORDER(fmt->format)) {
        അവസ്ഥ SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            നിർത്തുക;
        അവസ്ഥ SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            നിർത്തുക;
        }
        തിരഞ്ഞെടുപ്പ് (SDL_PIXELTYPE(fmt->format)) {
        അവസ്ഥ SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            എങ്കിൽ (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            എങ്കിൽ (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            നിർത്തുക;
        അവസ്ഥ SDL_PIXELTYPE_ARRAYF32:
            ((ദശാംശം *)pixels)[0] = v[0];
            ((ദശാംശം *)pixels)[1] = v[1];
            ((ദശാംശം *)pixels)[2] = v[2];
            എങ്കിൽ (fmt->bytes_per_pixel == 16) {
                ((ദശാംശം *)pixels)[3] = v[3];
            }
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            // Unknown array type
            നിർത്തുക;
        }
        നിർത്തുക;
    }
}

തരനിർവചനം എണ്ണൽ
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

തരനിർവചനം ഘടന
{
    SDL_TonemapOperator op;

    സംഘം {
        ഘടന {
            ദശാംശം scale;
        } linear;

        ഘടന {
            ദശാംശം a;
            ദശാംശം b;
            സ്ഥിരം ദശാംശം *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

സ്ഥിതം ശൂന്യം TonemapLinear(ദശാംശം *r, ദശാംശം *g, ദശാംശം *b, ദശാംശം scale)
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
സ്ഥിതം ശൂന്യം TonemapChrome(ദശാംശം *r, ദശാംശം *g, ദശാംശം *b, ദശാംശം tonemap_a, ദശാംശം tonemap_b)
{
    ദശാംശം v1 = *r;
    ദശാംശം v2 = *g;
    ദശാംശം v3 = *b;
    ദശാംശം vmax = SDL_max(v1, SDL_max(v2, v3));

    എങ്കിൽ (vmax > 0.0f) {
        ദശാംശം scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

സ്ഥിതം ശൂന്യം ApplyTonemap(SDL_TonemapContext *ctx, ദശാംശം *r, ദശാംശം *g, ദശാംശം *b)
{
    തിരഞ്ഞെടുപ്പ് (ctx->op) {
    അവസ്ഥ SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        നിർത്തുക;
    അവസ്ഥ SDL_TONEMAP_CHROME:
        എങ്കിൽ (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
ശൂന്യം SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ flags = info->flags;
    സ്ഥിരം Uint32 modulateR = info->r;
    സ്ഥിരം Uint32 modulateG = info->g;
    സ്ഥിരം Uint32 modulateB = info->b;
    സ്ഥിരം Uint32 modulateA = info->a;
    ദശാംശം srcR, srcG, srcB, srcA;
    ദശാംശം dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    സ്ഥിരം SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    സ്ഥിരം SDL_Palette *src_pal = info->src_pal;
    സ്ഥിരം SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    സ്ഥിരം SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    പൂർണ്ണസംഖ്യ srcbpp = src_fmt->bytes_per_pixel;
    പൂർണ്ണസംഖ്യ dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    സ്ഥിരം ദശാംശം *color_primaries_matrix = ശൂന്യ;
    ദശാംശം src_white_point;
    ദശാംശം dst_white_point;
    ദശാംശം dst_headroom;
    ദശാംശം src_headroom;
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
    എങ്കിൽ (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    എങ്കിൽ (src_headroom > dst_headroom) {
        സ്ഥിരം അക്ഷരം *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, ശൂന്യ);
        എങ്കിൽ (tonemap_operator) {
            എങ്കിൽ (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (ദശാംശം)SDL_atof(tonemap_operator + 2);
            } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } അല്ലെങ്കിൽ {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        എങ്കിൽ (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            എങ്കിൽ (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    എങ്കിൽ (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    എങ്കിൽ (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    ആകുമ്പോൾ (info->dst_h--) {
        Uint8 *src = ശൂന്യ;
        Uint8 *dst = info->dst;
        പൂർണ്ണസംഖ്യ n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        ആകുമ്പോൾ (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            എങ്കിൽ (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            എങ്കിൽ (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            എങ്കിൽ (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            എങ്കിൽ ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } അല്ലെങ്കിൽ {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            എങ്കിൽ (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            എങ്കിൽ (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            എങ്കിൽ (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                എങ്കിൽ (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            തിരഞ്ഞെടുപ്പ് (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            അവസ്ഥ 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                നിർത്തുക;
            അവസ്ഥ SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                നിർത്തുക;
            }

            എങ്കിൽ (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                എങ്കിൽ (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
            } അല്ലെങ്കിൽ {
                WriteFloatPixel(dst, dst_access, dst_fmt, dst_colorspace, dst_white_point, dstR, dstG, dstB, dstA);
            }

            posx += incx;
            dst += dstbpp;
        }
        posy += incy;
        info->dst += info->dst_pitch;
    }
}


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

प्रकारव्याख्या गणना
{
    SlowBlitPixelAccess_Index8,
    SlowBlitPixelAccess_RGB,
    SlowBlitPixelAccess_RGBA,
    SlowBlitPixelAccess_10Bit,
    SlowBlitPixelAccess_Large,
} SlowBlitPixelAccess;

स्थिर SlowBlitPixelAccess GetPixelAccessMethod(SDL_PixelFormat format)
{
    जर (SDL_BYTESPERPIXEL(format) > 4) {
        परत SlowBlitPixelAccess_Large;
    } अन्यथा जर (SDL_ISPIXELFORMAT_10BIT(format)) {
        परत SlowBlitPixelAccess_10Bit;
    } अन्यथा जर (format == SDL_PIXELFORMAT_INDEX8) {
        परत SlowBlitPixelAccess_Index8;
    } अन्यथा जर (SDL_ISPIXELFORMAT_ALPHA(format)) {
        परत SlowBlitPixelAccess_RGBA;
    } अन्यथा {
        परत SlowBlitPixelAccess_RGB;
    }
}

/* The ONE TRUE BLITTER
 * This puppy has to handle all the unoptimized cases - yes, it's slow.
 */
शून्य SDL_Blit_Slow(SDL_BlitInfo *info)
{
    स्थिरांक पूर्णांक flags = info->flags;
    स्थिरांक Uint32 modulateR = info->r;
    स्थिरांक Uint32 modulateG = info->g;
    स्थिरांक Uint32 modulateB = info->b;
    स्थिरांक Uint32 modulateA = info->a;
    Uint32 srcpixel = 0;
    Uint32 srcR = 0, srcG = 0, srcB = 0, srcA = 0;
    Uint32 dstpixel = 0;
    Uint32 dstR = 0, dstG = 0, dstB = 0, dstA = 0;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    स्थिरांक SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    स्थिरांक SDL_Palette *src_pal = info->src_pal;
    स्थिरांक SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    स्थिरांक SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    पूर्णांक srcbpp = src_fmt->bytes_per_pixel;
    पूर्णांक dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    Uint32 rgbmask = ~src_fmt->Amask;
    Uint32 ckey = info->colorkey & rgbmask;
    Uint32 last_pixel = 0;
    Uint8 last_index = 0;

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    जर (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = info->dst_h ? ((Uint64)info->src_h << 16) / info->dst_h : 0;
    incx = info->dst_w ? ((Uint64)info->src_w << 16) / info->dst_w : 0;
    posy = incy / 2; // start at the middle of pixel

    पर्यंत (info->dst_h--) {
        Uint8 *src = रिक्त;
        Uint8 *dst = info->dst;
        पूर्णांक n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        पर्यंत (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            निवड (src_access) {
            स्थिती SlowBlitPixelAccess_Index8:
                srcpixel = *src;
                srcR = src_pal->colors[srcpixel].r;
                srcG = src_pal->colors[srcpixel].g;
                srcB = src_pal->colors[srcpixel].b;
                srcA = src_pal->colors[srcpixel].a;
                थांबा;
            स्थिती SlowBlitPixelAccess_RGB:
                DISEMBLE_RGB(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB);
                srcA = 0xFF;
                थांबा;
            स्थिती SlowBlitPixelAccess_RGBA:
                DISEMBLE_RGBA(src, srcbpp, src_fmt, srcpixel, srcR, srcG, srcB, srcA);
                थांबा;
            स्थिती SlowBlitPixelAccess_10Bit:
                srcpixel = *((Uint32 *)(src));
                निवड (src_fmt->format) {
                स्थिती SDL_PIXELFORMAT_XRGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    थांबा;
                स्थिती SDL_PIXELFORMAT_XBGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    srcA = 0xFF;
                    थांबा;
                स्थिती SDL_PIXELFORMAT_ARGB2101010:
                    RGBA_FROM_ARGB2101010(srcpixel, srcR, srcG, srcB, srcA);
                    थांबा;
                स्थिती SDL_PIXELFORMAT_ABGR2101010:
                    RGBA_FROM_ABGR2101010(srcpixel, srcR, srcG, srcB, srcA);
                    थांबा;
                पूर्वनिर्धारित:
                    थांबा;
                }
                थांबा;
            स्थिती SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                थांबा;
            }

            जर (flags & SDL_COPY_COLORKEY) {
                // srcpixel isn't set for 24 bpp
                जर (srcbpp == 3) {
                    srcpixel = (srcR << src_fmt->Rshift) |
                               (srcG << src_fmt->Gshift) | (srcB << src_fmt->Bshift);
                }
                जर ((srcpixel & rgbmask) == ckey) {
                    posx += incx;
                    dst += dstbpp;
                    सुरूठेवा;
                }
            }
            जर (flags & SDL_COPY_BLEND_MASK) {
                निवड (dst_access) {
                स्थिती SlowBlitPixelAccess_Index8:
                    dstpixel = *dst;
                    dstR = dst_pal->colors[dstpixel].r;
                    dstG = dst_pal->colors[dstpixel].g;
                    dstB = dst_pal->colors[dstpixel].b;
                    dstA = dst_pal->colors[dstpixel].a;
                    थांबा;
                स्थिती SlowBlitPixelAccess_RGB:
                    DISEMBLE_RGB(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB);
                    dstA = 0xFF;
                    थांबा;
                स्थिती SlowBlitPixelAccess_RGBA:
                    DISEMBLE_RGBA(dst, dstbpp, dst_fmt, dstpixel, dstR, dstG, dstB, dstA);
                    थांबा;
                स्थिती SlowBlitPixelAccess_10Bit:
                    dstpixel = *((Uint32 *)(dst));
                    निवड (dst_fmt->format) {
                    स्थिती SDL_PIXELFORMAT_XRGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        थांबा;
                    स्थिती SDL_PIXELFORMAT_XBGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        dstA = 0xFF;
                        थांबा;
                    स्थिती SDL_PIXELFORMAT_ARGB2101010:
                        RGBA_FROM_ARGB2101010(dstpixel, dstR, dstG, dstB, dstA);
                        थांबा;
                    स्थिती SDL_PIXELFORMAT_ABGR2101010:
                        RGBA_FROM_ABGR2101010(dstpixel, dstR, dstG, dstB, dstA);
                        थांबा;
                    पूर्वनिर्धारित:
                        थांबा;
                    }
                    थांबा;
                स्थिती SlowBlitPixelAccess_Large:
                    // Handled in SDL_Blit_Slow_Float()
                    थांबा;
                }
            } अन्यथा {
                // don't care
            }

            जर (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            जर (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            जर (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                जर (srcA < 255) {
                    srcR = (srcR * srcA) / 255;
                    srcG = (srcG * srcA) / 255;
                    srcB = (srcB * srcA) / 255;
                }
            }
            निवड (flags & SDL_COPY_BLEND_MASK) {
            स्थिती 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                थांबा;
            स्थिती SDL_COPY_BLEND:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                थांबा;
            स्थिती SDL_COPY_BLEND_PREMULTIPLIED:
                dstR = srcR + ((255 - srcA) * dstR) / 255;
                जर (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + ((255 - srcA) * dstG) / 255;
                जर (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + ((255 - srcA) * dstB) / 255;
                जर (dstB > 255) {
                    dstB = 255;
                }
                dstA = srcA + ((255 - srcA) * dstA) / 255;
                जर (dstA > 255) {
                    dstA = 255;
                }
                थांबा;
            स्थिती SDL_COPY_ADD:
            स्थिती SDL_COPY_ADD_PREMULTIPLIED:
                dstR = srcR + dstR;
                जर (dstR > 255) {
                    dstR = 255;
                }
                dstG = srcG + dstG;
                जर (dstG > 255) {
                    dstG = 255;
                }
                dstB = srcB + dstB;
                जर (dstB > 255) {
                    dstB = 255;
                }
                थांबा;
            स्थिती SDL_COPY_MOD:
                dstR = (srcR * dstR) / 255;
                dstG = (srcG * dstG) / 255;
                dstB = (srcB * dstB) / 255;
                थांबा;
            स्थिती SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (255 - srcA))) / 255;
                जर (dstR > 255) {
                    dstR = 255;
                }
                dstG = ((srcG * dstG) + (dstG * (255 - srcA))) / 255;
                जर (dstG > 255) {
                    dstG = 255;
                }
                dstB = ((srcB * dstB) + (dstB * (255 - srcA))) / 255;
                जर (dstB > 255) {
                    dstB = 255;
                }
                थांबा;
            }

            निवड (dst_access) {
            स्थिती SlowBlitPixelAccess_Index8:
                dstpixel = ((dstR << 24) | (dstG << 16) | (dstB << 8) | dstA);
                जर (dstpixel != last_pixel) {
                    last_pixel = dstpixel;
                    last_index = SDL_LookupRGBAColor(palette_map, dstpixel, dst_pal);
                }
                *dst = last_index;
                थांबा;
            स्थिती SlowBlitPixelAccess_RGB:
                ASSEMBLE_RGB(dst, dstbpp, dst_fmt, dstR, dstG, dstB);
                थांबा;
            स्थिती SlowBlitPixelAccess_RGBA:
                ASSEMBLE_RGBA(dst, dstbpp, dst_fmt, dstR, dstG, dstB, dstA);
                थांबा;
            स्थिती SlowBlitPixelAccess_10Bit:
            {
                Uint32 pixelvalue;
                निवड (dst_fmt->format) {
                स्थिती SDL_PIXELFORMAT_XRGB2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                स्थिती SDL_PIXELFORMAT_ARGB2101010:
                    ARGB2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    थांबा;
                स्थिती SDL_PIXELFORMAT_XBGR2101010:
                    dstA = 0xFF;
                    SDL_FALLTHROUGH;
                स्थिती SDL_PIXELFORMAT_ABGR2101010:
                    ABGR2101010_FROM_RGBA(pixelvalue, dstR, dstG, dstB, dstA);
                    थांबा;
                पूर्वनिर्धारित:
                    pixelvalue = 0;
                    थांबा;
                }
                *(Uint32 *)dst = pixelvalue;
                थांबा;
            }
            स्थिती SlowBlitPixelAccess_Large:
                // Handled in SDL_Blit_Slow_Float()
                थांबा;
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
प्रकारव्याख्या संघ
{
    Uint32 u;
    दशांश f;
    संरचना
    {
        Uint32 Mantissa : 23;
        Uint32 Exponent : 8;
        Uint32 Sign : 1;
    } x;
} FP32;

#ifdef _MSC_VER
#pragma warning(ढकला)
#pragma warning(disable:4214)
#endif

प्रकारव्याख्या संघ
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
#pragma warning(काढा)
#endif

स्थिर दशांश half_to_float(Uint16 un_मूल्य)
{
    स्थिर स्थिरांक FP32 magic = { (254 - 15) << 23 };
    स्थिर स्थिरांक FP32 was_infnan = { (127 + 16) << 23 };
    FP16 h;
    FP32 o;

    h.u = un_मूल्य;
    o.u = (h.u & 0x7fff) << 13;     // exponent/mantissa bits
    o.f *= magic.f;                 // exponent adjust
    जर (o.f >= was_infnan.f)        // make sure Inf/NaN survive
        o.u |= 255 << 23;
    o.u |= (h.u & 0x8000) << 16;    // sign bit
    परत o.f;
}

/* Convert from float to F16
 * Public domain implementation from https://stackoverflow.com/questions/76799117/how-to-convert-a-float-to-a-half-type-and-the-other-way-around-in-c
 */
स्थिर Uint16 float_to_half(दशांश a)
{
    Uint32 ia;
    Uint16 ir;

    SDL_memcpy(&ia, &a, आकार(ia));

    ir = (ia >> 16) & 0x8000;
    जर ((ia & 0x7f800000) == 0x7f800000) {
        जर ((ia & 0x7fffffff) == 0x7f800000) {
            ir |= 0x7c00; // infinity
        } अन्यथा {
            ir |= 0x7e00 | ((ia >> (24 - 11)) & 0x1ff); // NaN, quietened
        }
    } अन्यथा जर ((ia & 0x7f800000) >= 0x33000000) {
        पूर्णांक shift = (पूर्णांक)((ia >> 23) & 0xff) - 127;
        जर (shift > 15) {
            ir |= 0x7c00; // infinity
        } अन्यथा {
            ia = (ia & 0x007fffff) | 0x00800000; // extract mantissa
            जर (shift < -14) { // denormal
                ir |= ia >> (-1 - shift);
                ia = ia << (32 - (-1 - shift));
            } अन्यथा { // normal
                ir |= ia >> (24 - 11);
                ia = ia << (32 - (24 - 11));
                ir = ir + ((14 + shift) << 10);
            }
            // IEEE-754 round to nearest of even
            जर ((ia > 0x80000000) || ((ia == 0x80000000) && (ir & 1))) {
                ir++;
            }
        }
    }
    परत ir;
}

स्थिर शून्य ReadFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, स्थिरांक SDL_PixelFormatDetails *fmt, स्थिरांक SDL_Palette *pal, SDL_Colorspace colorspace, दशांश SDR_white_point,
                           दशांश *outR, दशांश *outG, दशांश *outB, दशांश *outA)
{
    Uint32 pixelvalue;
    Uint32 R, G, B, A;
    दशांश fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;
    दशांश v[4];

    निवड (access) {
    स्थिती SlowBlitPixelAccess_Index8:
        pixelvalue = *pixels;
        fR = (दशांश)pal->colors[pixelvalue].r / 255.0f;
        fG = (दशांश)pal->colors[pixelvalue].g / 255.0f;
        fB = (दशांश)pal->colors[pixelvalue].b / 255.0f;
        fA = (दशांश)pal->colors[pixelvalue].a / 255.0f;
        थांबा;
    स्थिती SlowBlitPixelAccess_RGB:
        DISEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B);
        fR = (दशांश)R / 255.0f;
        fG = (दशांश)G / 255.0f;
        fB = (दशांश)B / 255.0f;
        fA = 1.0f;
        थांबा;
    स्थिती SlowBlitPixelAccess_RGBA:
        DISEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, pixelvalue, R, G, B, A);
        fR = (दशांश)R / 255.0f;
        fG = (दशांश)G / 255.0f;
        fB = (दशांश)B / 255.0f;
        fA = (दशांश)A / 255.0f;
        थांबा;
    स्थिती SlowBlitPixelAccess_10Bit:
        pixelvalue = *((Uint32 *)pixels);
        निवड (fmt->format) {
        स्थिती SDL_PIXELFORMAT_XRGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            थांबा;
        स्थिती SDL_PIXELFORMAT_XBGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            fA = 1.0f;
            थांबा;
        स्थिती SDL_PIXELFORMAT_ARGB2101010:
            RGBAFLOAT_FROM_ARGB2101010(pixelvalue, fR, fG, fB, fA);
            थांबा;
        स्थिती SDL_PIXELFORMAT_ABGR2101010:
            RGBAFLOAT_FROM_ABGR2101010(pixelvalue, fR, fG, fB, fA);
            थांबा;
        पूर्वनिर्धारित:
            fR = fG = fB = fA = 0.0f;
            थांबा;
        }
        थांबा;
    स्थिती SlowBlitPixelAccess_Large:
        निवड (SDL_PIXELTYPE(fmt->format)) {
        स्थिती SDL_PIXELTYPE_ARRAYU16:
            v[0] = (दशांश)(((Uint16 *)pixels)[0]) / SDL_MAX_UINT16;
            v[1] = (दशांश)(((Uint16 *)pixels)[1]) / SDL_MAX_UINT16;
            v[2] = (दशांश)(((Uint16 *)pixels)[2]) / SDL_MAX_UINT16;
            जर (fmt->bytes_per_pixel == 8) {
                v[3] = (दशांश)(((Uint16 *)pixels)[3]) / SDL_MAX_UINT16;
            } अन्यथा {
                v[3] = 1.0f;
            }
            थांबा;
        स्थिती SDL_PIXELTYPE_ARRAYF16:
            v[0] = half_to_float(((Uint16 *)pixels)[0]);
            v[1] = half_to_float(((Uint16 *)pixels)[1]);
            v[2] = half_to_float(((Uint16 *)pixels)[2]);
            जर (fmt->bytes_per_pixel == 8) {
                v[3] = half_to_float(((Uint16 *)pixels)[3]);
            } अन्यथा {
                v[3] = 1.0f;
            }
            थांबा;
        स्थिती SDL_PIXELTYPE_ARRAYF32:
            v[0] = ((दशांश *)pixels)[0];
            v[1] = ((दशांश *)pixels)[1];
            v[2] = ((दशांश *)pixels)[2];
            जर (fmt->bytes_per_pixel == 16) {
                v[3] = ((दशांश *)pixels)[3];
            } अन्यथा {
                v[3] = 1.0f;
            }
            थांबा;
        पूर्वनिर्धारित:
            // Unknown array type
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            थांबा;
        }
        निवड (SDL_PIXELORDER(fmt->format)) {
        स्थिती SDL_ARRAYORDER_RGB:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = 1.0f;
            थांबा;
        स्थिती SDL_ARRAYORDER_RGBA:
            fR = v[0];
            fG = v[1];
            fB = v[2];
            fA = v[3];
            थांबा;
        स्थिती SDL_ARRAYORDER_ARGB:
            fA = v[0];
            fR = v[1];
            fG = v[2];
            fB = v[3];
            थांबा;
        स्थिती SDL_ARRAYORDER_BGR:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = 1.0f;
            थांबा;
        स्थिती SDL_ARRAYORDER_BGRA:
            fB = v[0];
            fG = v[1];
            fR = v[2];
            fA = v[3];
            थांबा;
        स्थिती SDL_ARRAYORDER_ABGR:
            fA = v[0];
            fB = v[1];
            fG = v[2];
            fR = v[3];
            थांबा;
        पूर्वनिर्धारित:
            // Unknown array order
            fA = fR = fG = fB = 0.0f;
            थांबा;
        }
        थांबा;
    }

    // Convert to nits so src and dst are guaranteed to be linear and in the same units
    निवड (SDL_COLORSPACETRANSFER(colorspace)) {
    स्थिती SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBtoLinear(fR);
        fG = SDL_sRGBtoLinear(fG);
        fB = SDL_sRGBtoLinear(fB);
        थांबा;
    स्थिती SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQtoNits(fR) / SDR_white_point;
        fG = SDL_PQtoNits(fG) / SDR_white_point;
        fB = SDL_PQtoNits(fB) / SDR_white_point;
        थांबा;
    स्थिती SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR /= SDR_white_point;
        fG /= SDR_white_point;
        fB /= SDR_white_point;
        थांबा;
    पूर्वनिर्धारित:
        // Unknown, leave it alone
        थांबा;
    }

    *outR = fR;
    *outG = fG;
    *outB = fB;
    *outA = fA;
}

स्थिर शून्य WriteFloatPixel(Uint8 *pixels, SlowBlitPixelAccess access, स्थिरांक SDL_PixelFormatDetails *fmt, SDL_Colorspace colorspace, दशांश SDR_white_point,
                            दशांश fR, दशांश fG, दशांश fB, दशांश fA)
{
    Uint32 R, G, B, A;
    Uint32 pixelvalue;
    दशांश v[4];

    // We converted to nits so src and dst are guaranteed to be linear and in the same units
    निवड (SDL_COLORSPACETRANSFER(colorspace)) {
    स्थिती SDL_TRANSFER_CHARACTERISTICS_SRGB:
        fR = SDL_sRGBfromLinear(fR);
        fG = SDL_sRGBfromLinear(fG);
        fB = SDL_sRGBfromLinear(fB);
        थांबा;
    स्थिती SDL_TRANSFER_CHARACTERISTICS_PQ:
        fR = SDL_PQfromNits(fR * SDR_white_point);
        fG = SDL_PQfromNits(fG * SDR_white_point);
        fB = SDL_PQfromNits(fB * SDR_white_point);
        थांबा;
    स्थिती SDL_TRANSFER_CHARACTERISTICS_LINEAR:
        fR *= SDR_white_point;
        fG *= SDR_white_point;
        fB *= SDR_white_point;
        थांबा;
    पूर्वनिर्धारित:
        // Unknown, leave it alone
        थांबा;
    }

    निवड (access) {
    स्थिती SlowBlitPixelAccess_Index8:
        // This should never happen, checked before this call
        SDL_assert(0);
        थांबा;
    स्थिती SlowBlitPixelAccess_RGB:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGB(pixels, fmt->bytes_per_pixel, fmt, R, G, B);
        थांबा;
    स्थिती SlowBlitPixelAccess_RGBA:
        R = (Uint8)SDL_roundf(SDL_clamp(fR, 0.0f, 1.0f) * 255.0f);
        G = (Uint8)SDL_roundf(SDL_clamp(fG, 0.0f, 1.0f) * 255.0f);
        B = (Uint8)SDL_roundf(SDL_clamp(fB, 0.0f, 1.0f) * 255.0f);
        A = (Uint8)SDL_roundf(SDL_clamp(fA, 0.0f, 1.0f) * 255.0f);
        ASSEMBLE_RGBA(pixels, fmt->bytes_per_pixel, fmt, R, G, B, A);
        थांबा;
    स्थिती SlowBlitPixelAccess_10Bit:
    {
        निवड (fmt->format) {
        स्थिती SDL_PIXELFORMAT_XRGB2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        स्थिती SDL_PIXELFORMAT_ARGB2101010:
            ARGB2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            थांबा;
        स्थिती SDL_PIXELFORMAT_XBGR2101010:
            fA = 1.0f;
            SDL_FALLTHROUGH;
        स्थिती SDL_PIXELFORMAT_ABGR2101010:
            ABGR2101010_FROM_RGBAFLOAT(pixelvalue, fR, fG, fB, fA);
            थांबा;
        पूर्वनिर्धारित:
            pixelvalue = 0;
            थांबा;
        }
        *(Uint32 *)pixels = pixelvalue;
        थांबा;
    }
    स्थिती SlowBlitPixelAccess_Large:
        निवड (SDL_PIXELORDER(fmt->format)) {
        स्थिती SDL_ARRAYORDER_RGB:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = 1.0f;
            थांबा;
        स्थिती SDL_ARRAYORDER_RGBA:
            v[0] = fR;
            v[1] = fG;
            v[2] = fB;
            v[3] = fA;
            थांबा;
        स्थिती SDL_ARRAYORDER_ARGB:
            v[0] = fA;
            v[1] = fR;
            v[2] = fG;
            v[3] = fB;
            थांबा;
        स्थिती SDL_ARRAYORDER_BGR:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = 1.0f;
            थांबा;
        स्थिती SDL_ARRAYORDER_BGRA:
            v[0] = fB;
            v[1] = fG;
            v[2] = fR;
            v[3] = fA;
            थांबा;
        स्थिती SDL_ARRAYORDER_ABGR:
            v[0] = fA;
            v[1] = fB;
            v[2] = fG;
            v[3] = fR;
            थांबा;
        पूर्वनिर्धारित:
            // Unknown array order
            v[0] = v[1] = v[2] = v[3] = 0.0f;
            थांबा;
        }
        निवड (SDL_PIXELTYPE(fmt->format)) {
        स्थिती SDL_PIXELTYPE_ARRAYU16:
            ((Uint16 *)pixels)[0] = (Uint16)SDL_roundf(SDL_clamp(v[0], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[1] = (Uint16)SDL_roundf(SDL_clamp(v[1], 0.0f, 1.0f) * SDL_MAX_UINT16);
            ((Uint16 *)pixels)[2] = (Uint16)SDL_roundf(SDL_clamp(v[2], 0.0f, 1.0f) * SDL_MAX_UINT16);
            जर (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = (Uint16)SDL_roundf(SDL_clamp(v[3], 0.0f, 1.0f) * SDL_MAX_UINT16);
            }
            थांबा;
        स्थिती SDL_PIXELTYPE_ARRAYF16:
            ((Uint16 *)pixels)[0] = float_to_half(v[0]);
            ((Uint16 *)pixels)[1] = float_to_half(v[1]);
            ((Uint16 *)pixels)[2] = float_to_half(v[2]);
            जर (fmt->bytes_per_pixel == 8) {
                ((Uint16 *)pixels)[3] = float_to_half(v[3]);
            }
            थांबा;
        स्थिती SDL_PIXELTYPE_ARRAYF32:
            ((दशांश *)pixels)[0] = v[0];
            ((दशांश *)pixels)[1] = v[1];
            ((दशांश *)pixels)[2] = v[2];
            जर (fmt->bytes_per_pixel == 16) {
                ((दशांश *)pixels)[3] = v[3];
            }
            थांबा;
        पूर्वनिर्धारित:
            // Unknown array type
            थांबा;
        }
        थांबा;
    }
}

प्रकारव्याख्या गणना
{
    SDL_TONEMAP_NONE,
    SDL_TONEMAP_LINEAR,
    SDL_TONEMAP_CHROME
} SDL_TonemapOperator;

प्रकारव्याख्या संरचना
{
    SDL_TonemapOperator op;

    संघ {
        संरचना {
            दशांश scale;
        } linear;

        संरचना {
            दशांश a;
            दशांश b;
            स्थिरांक दशांश *color_primaries_matrix;
        } chrome;

    } data;

} SDL_TonemapContext;

स्थिर शून्य TonemapLinear(दशांश *r, दशांश *g, दशांश *b, दशांश scale)
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
स्थिर शून्य TonemapChrome(दशांश *r, दशांश *g, दशांश *b, दशांश tonemap_a, दशांश tonemap_b)
{
    दशांश v1 = *r;
    दशांश v2 = *g;
    दशांश v3 = *b;
    दशांश vmax = SDL_max(v1, SDL_max(v2, v3));

    जर (vmax > 0.0f) {
        दशांश scale = (1.0f + tonemap_a * vmax) / (1.0f + tonemap_b * vmax);
        TonemapLinear(r, g, b, scale);
    }
}

स्थिर शून्य ApplyTonemap(SDL_TonemapContext *ctx, दशांश *r, दशांश *g, दशांश *b)
{
    निवड (ctx->op) {
    स्थिती SDL_TONEMAP_LINEAR:
        TonemapLinear(r, g, b, ctx->data.linear.scale);
        थांबा;
    स्थिती SDL_TONEMAP_CHROME:
        जर (ctx->data.chrome.color_primaries_matrix) {
            SDL_ConvertColorPrimaries(r, g, b, ctx->data.chrome.color_primaries_matrix);
        }
        TonemapChrome(r, g, b, ctx->data.chrome.a, ctx->data.chrome.b);
        थांबा;
    पूर्वनिर्धारित:
        थांबा;
    }
}

/* The SECOND TRUE BLITTER
 * This one is even slower than the first, but also handles large pixel formats and colorspace conversion
 */
शून्य SDL_Blit_Slow_Float(SDL_BlitInfo *info)
{
    स्थिरांक पूर्णांक flags = info->flags;
    स्थिरांक Uint32 modulateR = info->r;
    स्थिरांक Uint32 modulateG = info->g;
    स्थिरांक Uint32 modulateB = info->b;
    स्थिरांक Uint32 modulateA = info->a;
    दशांश srcR, srcG, srcB, srcA;
    दशांश dstR, dstG, dstB, dstA;
    Uint64 srcy, srcx;
    Uint64 posy, posx;
    Uint64 incy, incx;
    स्थिरांक SDL_PixelFormatDetails *src_fmt = info->src_fmt;
    स्थिरांक SDL_Palette *src_pal = info->src_pal;
    स्थिरांक SDL_PixelFormatDetails *dst_fmt = info->dst_fmt;
    स्थिरांक SDL_Palette *dst_pal = info->dst_pal;
    SDL_HashTable *palette_map = info->palette_map;
    पूर्णांक srcbpp = src_fmt->bytes_per_pixel;
    पूर्णांक dstbpp = dst_fmt->bytes_per_pixel;
    SlowBlitPixelAccess src_access;
    SlowBlitPixelAccess dst_access;
    SDL_Colorspace src_colorspace;
    SDL_Colorspace dst_colorspace;
    SDL_ColorPrimaries src_primaries;
    SDL_ColorPrimaries dst_primaries;
    स्थिरांक दशांश *color_primaries_matrix = रिक्त;
    दशांश src_white_point;
    दशांश dst_white_point;
    दशांश dst_headroom;
    दशांश src_headroom;
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
    जर (dst_headroom == 0.0f) {
        // The destination will have the same headroom as the source
        dst_headroom = src_headroom;
        SDL_SetFloatProperty(SDL_GetSurfaceProperties(info->dst_surface), SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT, dst_headroom);
    }

    SDL_zero(tonemap);

    जर (src_headroom > dst_headroom) {
        स्थिरांक अक्षर *tonemap_operator = SDL_GetStringProperty(SDL_GetSurfaceProperties(info->src_surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, रिक्त);
        जर (tonemap_operator) {
            जर (SDL_strncmp(tonemap_operator, "*=", 2) == 0) {
                tonemap.op = SDL_TONEMAP_LINEAR;
                tonemap.data.linear.scale = (दशांश)SDL_atof(tonemap_operator + 2);
            } अन्यथा जर (SDL_strcasecmp(tonemap_operator, "chrome") == 0) {
                tonemap.op = SDL_TONEMAP_CHROME;
            } अन्यथा जर (SDL_strcasecmp(tonemap_operator, "none") == 0) {
                tonemap.op = SDL_TONEMAP_NONE;
            }
        } अन्यथा {
            tonemap.op = SDL_TONEMAP_CHROME;
        }
        जर (tonemap.op == SDL_TONEMAP_CHROME) {
            tonemap.data.chrome.a = (dst_headroom / (src_headroom * src_headroom));
            tonemap.data.chrome.b = (1.0f / dst_headroom);

            // We'll convert to BT.2020 primaries for the tonemap operation
            tonemap.data.chrome.color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, SDL_COLOR_PRIMARIES_BT2020);
            जर (tonemap.data.chrome.color_primaries_matrix) {
                src_primaries = SDL_COLOR_PRIMARIES_BT2020;
            }
        }
    }

    जर (src_primaries != dst_primaries) {
        color_primaries_matrix = SDL_GetColorPrimariesConversionMatrix(src_primaries, dst_primaries);
    }

    src_access = GetPixelAccessMethod(src_fmt->format);
    dst_access = GetPixelAccessMethod(dst_fmt->format);
    जर (dst_access == SlowBlitPixelAccess_Index8) {
        last_index = SDL_LookupRGBAColor(palette_map, last_pixel, dst_pal);
    }

    incy = ((Uint64)info->src_h << 16) / info->dst_h;
    incx = ((Uint64)info->src_w << 16) / info->dst_w;
    posy = incy / 2; // start at the middle of pixel

    पर्यंत (info->dst_h--) {
        Uint8 *src = रिक्त;
        Uint8 *dst = info->dst;
        पूर्णांक n = info->dst_w;
        posx = incx / 2; // start at the middle of pixel
        srcy = posy >> 16;
        पर्यंत (n--) {
            srcx = posx >> 16;
            src = (info->src + (srcy * info->src_pitch) + (srcx * srcbpp));

            ReadFloatPixel(src, src_access, src_fmt, src_pal, src_colorspace, src_white_point, &srcR, &srcG, &srcB, &srcA);

            जर (tonemap.op) {
                ApplyTonemap(&tonemap, &srcR, &srcG, &srcB);
            }

            जर (color_primaries_matrix) {
                SDL_ConvertColorPrimaries(&srcR, &srcG, &srcB, color_primaries_matrix);
            }

            जर (flags & SDL_COPY_COLORKEY) {
                // colorkey isn't supported
            }
            जर ((flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL))) {
                ReadFloatPixel(dst, dst_access, dst_fmt, dst_pal, dst_colorspace, dst_white_point, &dstR, &dstG, &dstB, &dstA);
            } अन्यथा {
                // don't care
                dstR = dstG = dstB = dstA = 0.0f;
            }

            जर (flags & SDL_COPY_MODULATE_COLOR) {
                srcR = (srcR * modulateR) / 255;
                srcG = (srcG * modulateG) / 255;
                srcB = (srcB * modulateB) / 255;
            }
            जर (flags & SDL_COPY_MODULATE_ALPHA) {
                srcA = (srcA * modulateA) / 255;
            }
            जर (flags & (SDL_COPY_BLEND | SDL_COPY_ADD)) {
                जर (srcA < 1.0f) {
                    srcR = (srcR * srcA);
                    srcG = (srcG * srcA);
                    srcB = (srcB * srcA);
                }
            }
            निवड (flags & (SDL_COPY_BLEND | SDL_COPY_ADD | SDL_COPY_MOD | SDL_COPY_MUL)) {
            स्थिती 0:
                dstR = srcR;
                dstG = srcG;
                dstB = srcB;
                dstA = srcA;
                थांबा;
            स्थिती SDL_COPY_BLEND:
                dstR = srcR + ((1.0f - srcA) * dstR);
                dstG = srcG + ((1.0f - srcA) * dstG);
                dstB = srcB + ((1.0f - srcA) * dstB);
                dstA = srcA + ((1.0f - srcA) * dstA);
                थांबा;
            स्थिती SDL_COPY_ADD:
                dstR = srcR + dstR;
                dstG = srcG + dstG;
                dstB = srcB + dstB;
                थांबा;
            स्थिती SDL_COPY_MOD:
                dstR = (srcR * dstR);
                dstG = (srcG * dstG);
                dstB = (srcB * dstB);
                थांबा;
            स्थिती SDL_COPY_MUL:
                dstR = ((srcR * dstR) + (dstR * (1.0f - srcA)));
                dstG = ((srcG * dstG) + (dstG * (1.0f - srcA)));
                dstB = ((srcB * dstB) + (dstB * (1.0f - srcA)));
                थांबा;
            }

            जर (dst_access == SlowBlitPixelAccess_Index8) {
                Uint32 R = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstR), 0.0f, 1.0f) * 255.0f);
                Uint32 G = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstG), 0.0f, 1.0f) * 255.0f);
                Uint32 B = (Uint8)SDL_roundf(SDL_clamp(SDL_sRGBfromLinear(dstB), 0.0f, 1.0f) * 255.0f);
                Uint32 A = (Uint8)SDL_roundf(SDL_clamp(dstA, 0.0f, 1.0f) * 255.0f);
                Uint32 dstpixel = ((R << 24) | (G << 16) | (B << 8) | A);
                जर (dstpixel != last_pixel) {
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


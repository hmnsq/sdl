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

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#ضمن "SDL_pixels_c.h"
#ضمن "SDL_surface_c.h"

#تعریف_کرو SAVE_32_ثنائی_ہندسہ_BMP

// Compression encodings for BMP files
#جے_بنا_تعریف BI_RGB
#تعریف_کرو BI_RGB       0
#تعریف_کرو BI_RLE8      1
#تعریف_کرو BI_RLE4      2
#تعریف_کرو BI_BITFIELDS 3
#جے_انت

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#جے_بنا_تعریف LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#تعریف_کرو LCS_WINDOWS_COLOR_SPACE 0x57696E20
#جے_انت

#جے_بنا_تعریف LCS_sRGB
// 0x73524742 == "sRGB"
#تعریف_کرو LCS_sRGB 0x73524742
#جے_انت

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#جے_بنا_تعریف LCS_GM_GRAPHICS
#تعریف_کرو LCS_GM_GRAPHICS 0x00000002
#جے_انت

ساكن bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, صحيح isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    صحيح pitch = surface->pitch;
    صحيح اچائی = surface->h;
    Uint8 *شروع = (Uint8 *)surface->pixels;
    Uint8 *سرا = شروع + (اچائی * pitch);
    Uint8 *بٹ = سرا - pitch, *spot;
    صحيح ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ثابت صحيح pixels_فی_byte = (isRle8 ? 1 : 2);

#تعریف_کرو COPY_PIXEL(x)                \
    spot = &بٹ[ofs++];             \
    إذا (spot >= شروع && spot < سرا) \
        *spot = (x)

    لكل (;;) {
        إذا (!SDL_ReadU8(src, &ch)) {
            أرجع false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        إذا (ch) {
            Uint8 pixelvalue;
            إذا (!SDL_ReadU8(src, &pixelvalue)) {
                أرجع false;
            }
            صحيح ich = (صحيح) ch;
            افعل {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_فی_byte;
            } طالما (ich > 0);
        } وإلا {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            إذا (!SDL_ReadU8(src, &ch)) {
                أرجع false;
            }
            بدل (ch) {
            حالة 0: // end of line
                ofs = 0;
                بٹ -= pitch; // go to previous
                اكسر;
            حالة 1:               // end of bitmap
                أرجع true; // success!
            حالة 2:               // delta
                إذا (!SDL_ReadU8(src, &ch)) {
                    أرجع false;
                }
                ofs += ch / pixels_فی_byte;
                إذا (ch & pixels_فی_byte) {
                    ofs++;
                }
                إذا (!SDL_ReadU8(src, &ch)) {
                    أرجع false;
                }
                بٹ -= (ch * pitch);
                اكسر;
            افتراضي: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                إذا (pixels_فی_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } وإلا {
                    needsPad = (((ch + (pixels_فی_byte-1)) / pixels_فی_byte) & (pixels_فی_byte-1)) != 0;
                }

                صحيح ich = (صحيح) ch;
                افعل {
                    Uint8 pixelvalue;
                    إذا (!SDL_ReadU8(src, &pixelvalue)) {
                        أرجع false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_فی_byte;
                } طالما (ich > 0);

                // pad at even boundary
                إذا (needsPad && !SDL_ReadU8(src, &ch)) {
                    أرجع false;
                }
                اكسر;
            }
        }
    }
}

ساكن فراغ CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
    صحيح alpha_Channel_وتھ = 0;
#وإلا
    صحيح alpha_Channel_وتھ = 3;
#جے_انت
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_وتھ;
    Uint8 *سرا = alpha + surface->h * surface->pitch;

    طالما (alpha < سرا) {
        إذا (*alpha != 0) {
            hasAlpha = true;
            اكسر;
        }
        alpha += 4;
    }

    إذا (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_وتھ;
        طالما (alpha < سرا) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 شروع;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    شروع = SDL_TellIO(src);
    إذا (شروع >= 0) {
        إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            إذا (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, شروع, SDL_IO_SEEK_سیٹ);
    }

    أرجع is_BMP;
}

SDL_Surface *SDL_لدو_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_وتھ = 0;
    صحيح i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *بٹ;
    Uint8 *چوٹی, *سرا;
    bool چوٹی_تھلے;
    bool haveRGBMasks = false;
    bool have_Alpha_نقاب = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bf_Off_بٹ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_ناپ;
    Sint32 bi_چوڑائی = 0;
    Sint32 bi_اچائی = 0;
    // Uint16 biPlanes;
    Uint16 bi_ثنائی_ہندسہ_گنتی = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_ورتیا = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = عدم;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب پورا;
    }

    // Read in the BMP file header
    fp_وتھ = SDL_TellIO(src);
    إذا (fp_وتھ < 0) {
        اذهب پورا;
    }
    SDL_ClearError();
    إذا (!SDL_IsBMP(src)) {
        SDL_سیٹ_Error("File is not a Windows BMP file");
        اذهب پورا;
    }
    إذا (!SDL_ReadU16LE(src, عدم /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, عدم /* bfSize */) ||
        !SDL_ReadU16LE(src, عدم /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, عدم /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_بٹ)) {
        اذهب پورا;
    }

    // Read the Win32 BITMAPINFOHEADER
    إذا (!SDL_ReadU32LE(src, &bi_ناپ)) {
        اذهب پورا;
    }
    إذا (bi_ناپ == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        إذا (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, عدم /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ثنائی_ہندسہ_گنتی)) {
            اذهب پورا;
        }
        bi_چوڑائی = biWidth16;
        bi_اچائی = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_ورتیا = 0;
        // biClrImportant = 0;
    } وإلا إذا (bi_ناپ >= 40) { // some version of BITMAPINFOHEADER
        Uint32 سرخی_ناپ;
        إذا (!SDL_ReadS32LE(src, &bi_چوڑائی) ||
            !SDL_ReadS32LE(src, &bi_اچائی) ||
            !SDL_ReadU16LE(src, عدم /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ثنائی_ہندسہ_گنتی) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, عدم /* biSizeImage */) ||
            !SDL_ReadU32LE(src, عدم /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, عدم /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_ورتیا) ||
            !SDL_ReadU32LE(src, عدم /* biClrImportant */)) {
            اذهب پورا;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        إذا (bi_ناپ != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            إذا (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                إذا (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    اذهب پورا;
                }

                // ...v3 adds an alpha mask.
                إذا (bi_ناپ >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_نقاب = true;
                    إذا (!SDL_ReadU32LE(src, &Amask)) {
                        اذهب پورا;
                    }
                }
            } وإلا {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                إذا (bi_ناپ >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    إذا (!SDL_ReadU32LE(src, عدم /* Rmask */) ||
                        !SDL_ReadU32LE(src, عدم /* Gmask */) ||
                        !SDL_ReadU32LE(src, عدم /* Bmask */)) {
                        اذهب پورا;
                    }
                }
                إذا (bi_ناپ >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    إذا (!SDL_ReadU32LE(src, عدم /* Amask */)) {
                        اذهب پورا;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        سرخی_ناپ = (Uint32)(SDL_TellIO(src) - (fp_وتھ + 14));
        إذا (bi_ناپ > سرخی_ناپ) {
            إذا (SDL_SeekIO(src, (bi_ناپ - سرخی_ناپ), SDL_IO_SEEK_CUR) < 0) {
                اذهب پورا;
            }
        }
    }
    إذا (bi_چوڑائی <= 0 || bi_اچائی == 0) {
        SDL_سیٹ_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_چوڑائی, bi_اچائی);
        اذهب پورا;
    }
    إذا (bi_اچائی < 0) {
        چوٹی_تھلے = true;
        bi_اچائی = -bi_اچائی;
    } وإلا {
        چوٹی_تھلے = false;
    }

    // Check for read error
    إذا (SDL_strcmp(SDL_GetError(), "") != 0) {
        اذهب پورا;
    }

    // Reject invalid bit depths
    بدل (bi_ثنائی_ہندسہ_گنتی) {
    حالة 0:
    حالة 3:
    حالة 5:
    حالة 6:
    حالة 7:
        SDL_سیٹ_Error("%u bpp BMP images are not supported", bi_ثنائی_ہندسہ_گنتی);
        اذهب پورا;
    افتراضي:
        اكسر;
    }

    // RLE4 and RLE8 BMP compression is supported
    بدل (biCompression) {
    حالة BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!have_Alpha_نقاب);
        // Default values for the BMP format
        بدل (bi_ثنائی_ہندسہ_گنتی) {
        حالة 15:
        حالة 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            اكسر;
        حالة 24:
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#وإلا
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#جے_انت
            اكسر;
        حالة 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            اكسر;
        افتراضي:
            اكسر;
        }
        اكسر;

    حالة BI_BITFIELDS:
        اكسر; // we handled this in the info header.

    افتراضي:
        اكسر;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_ثنائی_ہندسہ_گنتی, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_چوڑائی, bi_اچائی, format);

        إذا (!surface) {
            اذهب پورا;
        }
    }

    // Load the palette, if any
    إذا (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        إذا (!palette) {
            اذهب پورا;
        }

        إذا (SDL_SeekIO(src, fp_وتھ + 14 + bi_ناپ, SDL_IO_SEEK_سیٹ) < 0) {
            SDL_سیٹ_Error("Error seeking in datastream");
            اذهب پورا;
        }

        إذا (bi_ثنائی_ہندسہ_گنتی >= 32) { // we shift biClrUsed by this value later.
            SDL_سیٹ_Error("Unsupported or incorrect biBitCount field");
            اذهب پورا;
        }

        إذا (bi_Clr_ورتیا == 0) {
            bi_Clr_ورتیا = 1 << bi_ثنائی_ہندسہ_گنتی;
        }

        إذا (bi_Clr_ورتیا > (Uint32)palette->ncolors) {
            bi_Clr_ورتیا = 1 << bi_ثنائی_ہندسہ_گنتی; // try forcing it?
            إذا (bi_Clr_ورتیا > (Uint32)palette->ncolors) {
                SDL_سیٹ_Error("Unsupported or incorrect biClrUsed field");
                اذهب پورا;
            }
        }
        palette->ncolors = bi_Clr_ورتیا;

        إذا (bi_ناپ == 12) {
            لكل (i = 0; i < palette->ncolors; ++i) {
                إذا (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    اذهب پورا;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } وإلا {
            لكل (i = 0; i < palette->ncolors; ++i) {
                إذا (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    اذهب پورا;
                }

                /* According to Microsoft documentation, the fourth element
                   is reserved and must be zero, so we shouldn't treat it as
                   alpha.
                */
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        }
    }

    // Read the surface pixels.  Note that the bmp image is upside down
    إذا (SDL_SeekIO(src, fp_وتھ + bf_Off_بٹ, SDL_IO_SEEK_سیٹ) < 0) {
        SDL_سیٹ_Error("Error seeking in datastream");
        اذهب پورا;
    }
    إذا ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        إذا (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_سیٹ_Error("Error reading from datastream");
            اذهب پورا;
        }

        // Success!
        was_error = false;
        اذهب پورا;
    }
    چوٹی = (Uint8 *)surface->pixels;
    سرا = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    إذا (چوٹی_تھلے) {
        بٹ = چوٹی;
    } وإلا {
        بٹ = سرا - surface->pitch;
    }
    طالما (بٹ >= چوٹی && بٹ < سرا) {
        إذا (SDL_ReadIO(src, بٹ, surface->pitch) != (size_t)surface->pitch) {
            اذهب پورا;
        }
        إذا (bi_ثنائی_ہندسہ_گنتی == 8 && surface->palette && bi_Clr_ورتیا < (1u << bi_ثنائی_ہندسہ_گنتی)) {
            لكل (i = 0; i < surface->w; ++i) {
                إذا (بٹ[i] >= bi_Clr_ورتیا) {
                    SDL_سیٹ_Error("A BMP image contains a pixel with a color out of the palette");
                    اذهب پورا;
                }
            }
        }
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        بدل (bi_ثنائی_ہندسہ_گنتی) {
        حالة 15:
        حالة 16:
        {
            Uint16 *pix = (Uint16 *)بٹ;
            لكل (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            اكسر;
        }

        حالة 32:
        {
            Uint32 *pix = (Uint32 *)بٹ;
            لكل (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            اكسر;
        }
        }
#جے_انت

        // Skip padding bytes, ugh
        إذا (pad) {
            Uint8 padbyte;
            لكل (i = 0; i < pad; ++i) {
                إذا (!SDL_ReadU8(src, &padbyte)) {
                    اذهب پورا;
                }
            }
        }
        إذا (چوٹی_تھلے) {
            بٹ += surface->pitch;
        } وإلا {
            بٹ -= surface->pitch;
        }
    }
    إذا (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

پورا:
    إذا (was_error) {
        إذا (src) {
            SDL_SeekIO(src, fp_وتھ, SDL_IO_SEEK_سیٹ);
        }
        SDL_DestroySurface(surface);
        surface = عدم;
    }
    إذا (closeio && src) {
        SDL_CloseIO(src);
    }
    أرجع surface;
}

تعريفنوع بنية {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ساكن فراغ FreeBMPSaveState(BMPSaveState *state)
{
    إذا (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ساكن bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = عدم;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        أرجع SDL_InvalidParamError("surface");
    }

#جے_تعریف_شدہ SAVE_32_ثنائی_ہندسہ_BMP
    // We can save alpha information in a 32-bit BMP
    إذا (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#جے_انت // SAVE_32BIT_BMP

    إذا (surface->palette && !state->save32bit) {
        إذا (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } وإلا {
            SDL_سیٹ_Error("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            اذهب error;
        }
    } وإلا إذا ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } وإلا {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        إذا (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } وإلا {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        إذا (!state->intermediate_surface) {
            SDL_سیٹ_Error("Couldn't convert image to %d bpp",
                         (صحيح)SDL_BITSPERPIXEL(pixel_format));
            اذهب error;
        }
    }

    إذا (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    أرجع true;
error:
    FreeBMPSaveState(state);
    أرجع false;
}

SDL_Surface *SDL_لدو_BMP(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    إذا (!دھارا) {
        أرجع عدم;
    }
    أرجع SDL_لدو_BMP_IO(دھارا, true);
}
ساكن bool SDL_Save_BMP_IO_اندرونی(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_وتھ, new_وتھ;
    صحيح i, pad;
    Uint8 *بٹ;

    // The Win32 BMP file header (14 bytes)
    حرف magic[2] = { 'B', 'M' };
    Uint32 bf_ناپ;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_بٹ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_ناپ;
    Sint32 bi_چوڑائی;
    Sint32 bi_اچائی;
    Uint16 biPlanes;
    Uint16 bi_ثنائی_ہندسہ_گنتی;
    Uint32 biCompression;
    Uint32 bi_ناپ_Image;
    Sint32 bi_XPels_فی_Meter;
    Sint32 bi_YPels_فی_Meter;
    Uint32 bi_Clr_ورتیا;
    Uint32 biClrImportant;

    // The additional header members from the Win32 BITMAPV4HEADER struct (108 bytes in total)
    Uint32 b_V4_Red_نقاب = 0;
    Uint32 b_V4_Green_نقاب = 0;
    Uint32 b_V4_Blue_نقاب = 0;
    Uint32 b_V4_Alpha_نقاب = 0;
    Uint32 bV4CSType = 0;
    Sint32 bV4Endpoints[3 * 3] = { 0 };
    Uint32 bV4GammaRed = 0;
    Uint32 bV4GammaGreen = 0;
    Uint32 bV4GammaBlue = 0;

    // The additional header members from the Win32 BITMAPV5HEADER struct (124 bytes in total)
    Uint32 bV5Intent = 0;
    Uint32 b_V5_Profile_انکڑے = 0;
    Uint32 b_V5_Profile_ناپ = 0;
    Uint32 bV5Reserved = 0;

    إذا (SDL_جندرا_Surface(state->intermediate_surface)) {
        ثابت size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->بائٹاں_فی_pixel;

        // Set the BMP file header values
        bf_ناپ = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_بٹ = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_وتھ = SDL_TellIO(dst);
        إذا (fp_وتھ < 0) {
            اذهب پورا;
        }
        إذا (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_ناپ) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_بٹ)) {
            اذهب پورا;
        }

        // Set the BMP info values
        bi_ناپ = 40;
        bi_چوڑائی = state->intermediate_surface->w;
        bi_اچائی = state->intermediate_surface->h;
        biPlanes = 1;
        bi_ثنائی_ہندسہ_گنتی = state->intermediate_surface->fmt->بٹ_فی_pixel;
        biCompression = BI_RGB;
        bi_ناپ_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_فی_Meter = 0;
        bi_YPels_فی_Meter = 0;
        إذا (state->intermediate_surface->palette) {
            bi_Clr_ورتیا = state->intermediate_surface->palette->ncolors;
        } وإلا {
            bi_Clr_ورتیا = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        إذا (state->save32bit && !state->saveLegacyBMP) {
            bi_ناپ = 124;
            // Version 4 values
            biCompression = BI_BITFIELDS;
            // The BMP format is always little endian, these masks stay the same
            b_V4_Red_نقاب = 0x00ff0000;
            b_V4_Green_نقاب = 0x0000ff00;
            b_V4_Blue_نقاب = 0x000000ff;
            b_V4_Alpha_نقاب = 0xff000000;
            bV4CSType = LCS_sRGB;
            bV4GammaRed = 0;
            bV4GammaGreen = 0;
            bV4GammaBlue = 0;
            // Version 5 values
            bV5Intent = LCS_GM_GRAPHICS;
            b_V5_Profile_انکڑے = 0;
            b_V5_Profile_ناپ = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        إذا (!SDL_WriteU32LE(dst, bi_ناپ) ||
            !SDL_WriteS32LE(dst, bi_چوڑائی) ||
            !SDL_WriteS32LE(dst, bi_اچائی) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_ثنائی_ہندسہ_گنتی) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_ناپ_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_فی_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_فی_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_ورتیا) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            اذهب پورا;
        }

        // Write the BMP info values
        إذا (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            إذا (!SDL_WriteU32LE(dst, b_V4_Red_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Green_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_نقاب) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                اذهب پورا;
            }
            لكل (i = 0; i < 3 * 3; i++) {
                إذا (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    اذهب پورا;
                }
            }
            إذا (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                اذهب پورا;
            }
            // Version 5 values
            إذا (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_انکڑے) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_ناپ) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                اذهب پورا;
            }
        }

        // Write the palette (in BGR color order)
        إذا (state->intermediate_surface->palette) {
            SDL_Color *colors;
            صحيح ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            لكل (i = 0; i < ncolors; ++i) {
                إذا (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    اذهب پورا;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_بٹ = (Uint32)(SDL_TellIO(dst) - fp_وتھ);
        إذا (SDL_SeekIO(dst, fp_وتھ + 10, SDL_IO_SEEK_سیٹ) < 0) {
            اذهب پورا;
        }
        إذا (!SDL_WriteU32LE(dst, bf_Off_بٹ)) {
            اذهب پورا;
        }
        إذا (SDL_SeekIO(dst, fp_وتھ + bf_Off_بٹ, SDL_IO_SEEK_سیٹ) < 0) {
            اذهب پورا;
        }

        // Write the bitmap image upside down
        بٹ = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        طالما (بٹ > (Uint8 *)state->intermediate_surface->pixels) {
            بٹ -= state->intermediate_surface->pitch;
            إذا (SDL_WriteIO(dst, بٹ, bw) != bw) {
                اذهب پورا;
            }
            إذا (pad) {
                ثابت Uint8 padbyte = 0;
                لكل (i = 0; i < pad; ++i) {
                    إذا (!SDL_WriteU8(dst, padbyte)) {
                        اذهب پورا;
                    }
                }
            }
        }

        // Write the BMP file size
        new_وتھ = SDL_TellIO(dst);
        إذا (new_وتھ < 0) {
            اذهب پورا;
        }
        bf_ناپ = (Uint32)(new_وتھ - fp_وتھ);
        إذا (SDL_SeekIO(dst, fp_وتھ + 2, SDL_IO_SEEK_سیٹ) < 0) {
            اذهب پورا;
        }
        إذا (!SDL_WriteU32LE(dst, bf_ناپ)) {
            اذهب پورا;
        }
        إذا (SDL_SeekIO(dst, fp_وتھ + bf_ناپ, SDL_IO_SEEK_سیٹ) < 0) {
            اذهب پورا;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

پورا:
    إذا (closeio && dst) {
        إذا (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    إذا (was_error) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool نتیجہ = true;
    BMPSaveState state;
    إذا (!InitBMPSaveState(&state, surface)) {
        أرجع false;
    }
    CHECK_PARAM(!dst) {
        نتیجہ = SDL_InvalidParamError("dst");
        اذهب پورا;
    }
    نتیجہ = SDL_Save_BMP_IO_اندرونی(&state, dst, closeio);
پورا:
    FreeBMPSaveState(&state);
    أرجع نتیجہ;
}

bool SDL_SaveBMP(SDL_Surface *surface, ثابت حرف *file)
{
    BMPSaveState state;
    إذا (!InitBMPSaveState(&state, surface)) {
        أرجع false;
    }

    SDL_IOStream *دھارا = SDL_IOFromFile(file, "wb");
    إذا (!دھارا) {
        أرجع false;
    }

    bool نتیجہ = SDL_Save_BMP_IO_اندرونی(&state, دھارا, true);
    FreeBMPSaveState(&state);
    أرجع نتیجہ;
}

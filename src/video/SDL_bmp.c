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

#وصف_ڪريو SAVE_32_ٻٽو_انگ_BMP

// Compression encodings for BMP files
#جيڪڏهن_وصف_نه_ٿيل BI_RGB
#وصف_ڪريو BI_RGB       0
#وصف_ڪريو BI_RLE8      1
#وصف_ڪريو BI_RLE4      2
#وصف_ڪريو BI_BITFIELDS 3
#جيڪڏهن_پورو

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#جيڪڏهن_وصف_نه_ٿيل LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#وصف_ڪريو LCS_WINDOWS_COLOR_SPACE 0x57696E20
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل LCS_sRGB
// 0x73524742 == "sRGB"
#وصف_ڪريو LCS_sRGB 0x73524742
#جيڪڏهن_پورو

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#جيڪڏهن_وصف_نه_ٿيل LCS_GM_GRAPHICS
#وصف_ڪريو LCS_GM_GRAPHICS 0x00000002
#جيڪڏهن_پورو

ساكن bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, صحيح isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    صحيح pitch = surface->pitch;
    صحيح اوچائي = surface->h;
    Uint8 *شروعات = (Uint8 *)surface->pixels;
    Uint8 *پڇاڙي = شروعات + (اوچائي * pitch);
    Uint8 *بٽ = پڇاڙي - pitch, *spot;
    صحيح ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ثابت صحيح pixels_في_byte = (isRle8 ? 1 : 2);

#وصف_ڪريو COPY_PIXEL(x)                \
    spot = &بٽ[ofs++];             \
    إذا (spot >= شروعات && spot < پڇاڙي) \
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
                ich -= pixels_في_byte;
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
                بٽ -= pitch; // go to previous
                اكسر;
            حالة 1:               // end of bitmap
                أرجع true; // success!
            حالة 2:               // delta
                إذا (!SDL_ReadU8(src, &ch)) {
                    أرجع false;
                }
                ofs += ch / pixels_في_byte;
                إذا (ch & pixels_في_byte) {
                    ofs++;
                }
                إذا (!SDL_ReadU8(src, &ch)) {
                    أرجع false;
                }
                بٽ -= (ch * pitch);
                اكسر;
            افتراضي: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                إذا (pixels_في_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } وإلا {
                    needsPad = (((ch + (pixels_في_byte-1)) / pixels_في_byte) & (pixels_في_byte-1)) != 0;
                }

                صحيح ich = (صحيح) ch;
                افعل {
                    Uint8 pixelvalue;
                    إذا (!SDL_ReadU8(src, &pixelvalue)) {
                        أرجع false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_في_byte;
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
    صحيح alpha_Channel_وٿي = 0;
#وإلا
    صحيح alpha_Channel_وٿي = 3;
#جيڪڏهن_پورو
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_وٿي;
    Uint8 *پڇاڙي = alpha + surface->h * surface->pitch;

    طالما (alpha < پڇاڙي) {
        إذا (*alpha != 0) {
            hasAlpha = true;
            اكسر;
        }
        alpha += 4;
    }

    إذا (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_وٿي;
        طالما (alpha < پڇاڙي) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 شروعات;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    شروعات = SDL_TellIO(src);
    إذا (شروعات >= 0) {
        إذا (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            إذا (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, شروعات, SDL_IO_SEEK_سيٽ);
    }

    أرجع is_BMP;
}

SDL_Surface *SDL_ڀريو_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_وٿي = 0;
    صحيح i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *بٽ;
    Uint8 *چوٽي, *پڇاڙي;
    bool چوٽي_هيٺ_ڏانهن;
    bool haveRGBMasks = false;
    bool have_Alpha_نقاب = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bf_Off_بٽ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_سائيز;
    Sint32 bi_ويڪر = 0;
    Sint32 bi_اوچائي = 0;
    // Uint16 biPlanes;
    Uint16 bi_ٻٽو_انگ_ڳڻپ = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_استعمال_ٿيل = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = عدم;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب پورو;
    }

    // Read in the BMP file header
    fp_وٿي = SDL_TellIO(src);
    إذا (fp_وٿي < 0) {
        اذهب پورو;
    }
    SDL_ClearError();
    إذا (!SDL_IsBMP(src)) {
        SDL_سيٽ_Error("File is not a Windows BMP file");
        اذهب پورو;
    }
    إذا (!SDL_ReadU16LE(src, عدم /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, عدم /* bfSize */) ||
        !SDL_ReadU16LE(src, عدم /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, عدم /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_بٽ)) {
        اذهب پورو;
    }

    // Read the Win32 BITMAPINFOHEADER
    إذا (!SDL_ReadU32LE(src, &bi_سائيز)) {
        اذهب پورو;
    }
    إذا (bi_سائيز == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        إذا (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, عدم /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ٻٽو_انگ_ڳڻپ)) {
            اذهب پورو;
        }
        bi_ويڪر = biWidth16;
        bi_اوچائي = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_استعمال_ٿيل = 0;
        // biClrImportant = 0;
    } وإلا إذا (bi_سائيز >= 40) { // some version of BITMAPINFOHEADER
        Uint32 سرو_سائيز;
        إذا (!SDL_ReadS32LE(src, &bi_ويڪر) ||
            !SDL_ReadS32LE(src, &bi_اوچائي) ||
            !SDL_ReadU16LE(src, عدم /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ٻٽو_انگ_ڳڻپ) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, عدم /* biSizeImage */) ||
            !SDL_ReadU32LE(src, عدم /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, عدم /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_استعمال_ٿيل) ||
            !SDL_ReadU32LE(src, عدم /* biClrImportant */)) {
            اذهب پورو;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        إذا (bi_سائيز != 64) {
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
                    اذهب پورو;
                }

                // ...v3 adds an alpha mask.
                إذا (bi_سائيز >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_نقاب = true;
                    إذا (!SDL_ReadU32LE(src, &Amask)) {
                        اذهب پورو;
                    }
                }
            } وإلا {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                إذا (bi_سائيز >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    إذا (!SDL_ReadU32LE(src, عدم /* Rmask */) ||
                        !SDL_ReadU32LE(src, عدم /* Gmask */) ||
                        !SDL_ReadU32LE(src, عدم /* Bmask */)) {
                        اذهب پورو;
                    }
                }
                إذا (bi_سائيز >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    إذا (!SDL_ReadU32LE(src, عدم /* Amask */)) {
                        اذهب پورو;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        سرو_سائيز = (Uint32)(SDL_TellIO(src) - (fp_وٿي + 14));
        إذا (bi_سائيز > سرو_سائيز) {
            إذا (SDL_SeekIO(src, (bi_سائيز - سرو_سائيز), SDL_IO_SEEK_CUR) < 0) {
                اذهب پورو;
            }
        }
    }
    إذا (bi_ويڪر <= 0 || bi_اوچائي == 0) {
        SDL_سيٽ_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_ويڪر, bi_اوچائي);
        اذهب پورو;
    }
    إذا (bi_اوچائي < 0) {
        چوٽي_هيٺ_ڏانهن = true;
        bi_اوچائي = -bi_اوچائي;
    } وإلا {
        چوٽي_هيٺ_ڏانهن = false;
    }

    // Check for read error
    إذا (SDL_strcmp(SDL_GetError(), "") != 0) {
        اذهب پورو;
    }

    // Reject invalid bit depths
    بدل (bi_ٻٽو_انگ_ڳڻپ) {
    حالة 0:
    حالة 3:
    حالة 5:
    حالة 6:
    حالة 7:
        SDL_سيٽ_Error("%u bpp BMP images are not supported", bi_ٻٽو_انگ_ڳڻپ);
        اذهب پورو;
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
        بدل (bi_ٻٽو_انگ_ڳڻپ) {
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
#جيڪڏهن_پورو
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
        format = SDL_GetPixelFormatForMasks(bi_ٻٽو_انگ_ڳڻپ, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_ويڪر, bi_اوچائي, format);

        إذا (!surface) {
            اذهب پورو;
        }
    }

    // Load the palette, if any
    إذا (SDL_ISPIXELFORMAT_اشاريي_وارو(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        إذا (!palette) {
            اذهب پورو;
        }

        إذا (SDL_SeekIO(src, fp_وٿي + 14 + bi_سائيز, SDL_IO_SEEK_سيٽ) < 0) {
            SDL_سيٽ_Error("Error seeking in datastream");
            اذهب پورو;
        }

        إذا (bi_ٻٽو_انگ_ڳڻپ >= 32) { // we shift biClrUsed by this value later.
            SDL_سيٽ_Error("Unsupported or incorrect biBitCount field");
            اذهب پورو;
        }

        إذا (bi_Clr_استعمال_ٿيل == 0) {
            bi_Clr_استعمال_ٿيل = 1 << bi_ٻٽو_انگ_ڳڻپ;
        }

        إذا (bi_Clr_استعمال_ٿيل > (Uint32)palette->ncolors) {
            bi_Clr_استعمال_ٿيل = 1 << bi_ٻٽو_انگ_ڳڻپ; // try forcing it?
            إذا (bi_Clr_استعمال_ٿيل > (Uint32)palette->ncolors) {
                SDL_سيٽ_Error("Unsupported or incorrect biClrUsed field");
                اذهب پورو;
            }
        }
        palette->ncolors = bi_Clr_استعمال_ٿيل;

        إذا (bi_سائيز == 12) {
            لكل (i = 0; i < palette->ncolors; ++i) {
                إذا (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    اذهب پورو;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } وإلا {
            لكل (i = 0; i < palette->ncolors; ++i) {
                إذا (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    اذهب پورو;
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
    إذا (SDL_SeekIO(src, fp_وٿي + bf_Off_بٽ, SDL_IO_SEEK_سيٽ) < 0) {
        SDL_سيٽ_Error("Error seeking in datastream");
        اذهب پورو;
    }
    إذا ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        إذا (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_سيٽ_Error("Error reading from datastream");
            اذهب پورو;
        }

        // Success!
        was_error = false;
        اذهب پورو;
    }
    چوٽي = (Uint8 *)surface->pixels;
    پڇاڙي = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    إذا (چوٽي_هيٺ_ڏانهن) {
        بٽ = چوٽي;
    } وإلا {
        بٽ = پڇاڙي - surface->pitch;
    }
    طالما (بٽ >= چوٽي && بٽ < پڇاڙي) {
        إذا (SDL_ReadIO(src, بٽ, surface->pitch) != (size_t)surface->pitch) {
            اذهب پورو;
        }
        إذا (bi_ٻٽو_انگ_ڳڻپ == 8 && surface->palette && bi_Clr_استعمال_ٿيل < (1u << bi_ٻٽو_انگ_ڳڻپ)) {
            لكل (i = 0; i < surface->w; ++i) {
                إذا (بٽ[i] >= bi_Clr_استعمال_ٿيل) {
                    SDL_سيٽ_Error("A BMP image contains a pixel with a color out of the palette");
                    اذهب پورو;
                }
            }
        }
#إذا SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        بدل (bi_ٻٽو_انگ_ڳڻپ) {
        حالة 15:
        حالة 16:
        {
            Uint16 *pix = (Uint16 *)بٽ;
            لكل (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            اكسر;
        }

        حالة 32:
        {
            Uint32 *pix = (Uint32 *)بٽ;
            لكل (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            اكسر;
        }
        }
#جيڪڏهن_پورو

        // Skip padding bytes, ugh
        إذا (pad) {
            Uint8 padbyte;
            لكل (i = 0; i < pad; ++i) {
                إذا (!SDL_ReadU8(src, &padbyte)) {
                    اذهب پورو;
                }
            }
        }
        إذا (چوٽي_هيٺ_ڏانهن) {
            بٽ += surface->pitch;
        } وإلا {
            بٽ -= surface->pitch;
        }
    }
    إذا (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

پورو:
    إذا (was_error) {
        إذا (src) {
            SDL_SeekIO(src, fp_وٿي, SDL_IO_SEEK_سيٽ);
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

#جيڪڏهن_وصف_ٿيل SAVE_32_ٻٽو_انگ_BMP
    // We can save alpha information in a 32-bit BMP
    إذا (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#جيڪڏهن_پورو // SAVE_32BIT_BMP

    إذا (surface->palette && !state->save32bit) {
        إذا (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } وإلا {
            SDL_سيٽ_Error("%u bpp BMP files not supported",
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
            SDL_سيٽ_Error("Couldn't convert image to %d bpp",
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

SDL_Surface *SDL_ڀريو_BMP(ثابت حرف *file)
{
    SDL_IOStream *وهڪرو = SDL_IOFromFile(file, "rb");
    إذا (!وهڪرو) {
        أرجع عدم;
    }
    أرجع SDL_ڀريو_BMP_IO(وهڪرو, true);
}
ساكن bool SDL_Save_BMP_IO_اندروني(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_وٿي, new_وٿي;
    صحيح i, pad;
    Uint8 *بٽ;

    // The Win32 BMP file header (14 bytes)
    حرف magic[2] = { 'B', 'M' };
    Uint32 bf_سائيز;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_بٽ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_سائيز;
    Sint32 bi_ويڪر;
    Sint32 bi_اوچائي;
    Uint16 biPlanes;
    Uint16 bi_ٻٽو_انگ_ڳڻپ;
    Uint32 biCompression;
    Uint32 bi_سائيز_Image;
    Sint32 bi_XPels_في_Meter;
    Sint32 bi_YPels_في_Meter;
    Uint32 bi_Clr_استعمال_ٿيل;
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
    Uint32 b_V5_Profile_معلومات = 0;
    Uint32 b_V5_Profile_سائيز = 0;
    Uint32 bV5Reserved = 0;

    إذا (SDL_تالو_Surface(state->intermediate_surface)) {
        ثابت size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->بائيٽون_في_pixel;

        // Set the BMP file header values
        bf_سائيز = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_بٽ = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_وٿي = SDL_TellIO(dst);
        إذا (fp_وٿي < 0) {
            اذهب پورو;
        }
        إذا (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_سائيز) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_بٽ)) {
            اذهب پورو;
        }

        // Set the BMP info values
        bi_سائيز = 40;
        bi_ويڪر = state->intermediate_surface->w;
        bi_اوچائي = state->intermediate_surface->h;
        biPlanes = 1;
        bi_ٻٽو_انگ_ڳڻپ = state->intermediate_surface->fmt->بٽ_في_pixel;
        biCompression = BI_RGB;
        bi_سائيز_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_في_Meter = 0;
        bi_YPels_في_Meter = 0;
        إذا (state->intermediate_surface->palette) {
            bi_Clr_استعمال_ٿيل = state->intermediate_surface->palette->ncolors;
        } وإلا {
            bi_Clr_استعمال_ٿيل = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        إذا (state->save32bit && !state->saveLegacyBMP) {
            bi_سائيز = 124;
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
            b_V5_Profile_معلومات = 0;
            b_V5_Profile_سائيز = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        إذا (!SDL_WriteU32LE(dst, bi_سائيز) ||
            !SDL_WriteS32LE(dst, bi_ويڪر) ||
            !SDL_WriteS32LE(dst, bi_اوچائي) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_ٻٽو_انگ_ڳڻپ) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_سائيز_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_في_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_في_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_استعمال_ٿيل) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            اذهب پورو;
        }

        // Write the BMP info values
        إذا (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            إذا (!SDL_WriteU32LE(dst, b_V4_Red_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Green_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_نقاب) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                اذهب پورو;
            }
            لكل (i = 0; i < 3 * 3; i++) {
                إذا (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    اذهب پورو;
                }
            }
            إذا (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                اذهب پورو;
            }
            // Version 5 values
            إذا (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_معلومات) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_سائيز) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                اذهب پورو;
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
                    اذهب پورو;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_بٽ = (Uint32)(SDL_TellIO(dst) - fp_وٿي);
        إذا (SDL_SeekIO(dst, fp_وٿي + 10, SDL_IO_SEEK_سيٽ) < 0) {
            اذهب پورو;
        }
        إذا (!SDL_WriteU32LE(dst, bf_Off_بٽ)) {
            اذهب پورو;
        }
        إذا (SDL_SeekIO(dst, fp_وٿي + bf_Off_بٽ, SDL_IO_SEEK_سيٽ) < 0) {
            اذهب پورو;
        }

        // Write the bitmap image upside down
        بٽ = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        طالما (بٽ > (Uint8 *)state->intermediate_surface->pixels) {
            بٽ -= state->intermediate_surface->pitch;
            إذا (SDL_WriteIO(dst, بٽ, bw) != bw) {
                اذهب پورو;
            }
            إذا (pad) {
                ثابت Uint8 padbyte = 0;
                لكل (i = 0; i < pad; ++i) {
                    إذا (!SDL_WriteU8(dst, padbyte)) {
                        اذهب پورو;
                    }
                }
            }
        }

        // Write the BMP file size
        new_وٿي = SDL_TellIO(dst);
        إذا (new_وٿي < 0) {
            اذهب پورو;
        }
        bf_سائيز = (Uint32)(new_وٿي - fp_وٿي);
        إذا (SDL_SeekIO(dst, fp_وٿي + 2, SDL_IO_SEEK_سيٽ) < 0) {
            اذهب پورو;
        }
        إذا (!SDL_WriteU32LE(dst, bf_سائيز)) {
            اذهب پورو;
        }
        إذا (SDL_SeekIO(dst, fp_وٿي + bf_سائيز, SDL_IO_SEEK_سيٽ) < 0) {
            اذهب پورو;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

پورو:
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
    bool نتيجو = true;
    BMPSaveState state;
    إذا (!InitBMPSaveState(&state, surface)) {
        أرجع false;
    }
    CHECK_PARAM(!dst) {
        نتيجو = SDL_InvalidParamError("dst");
        اذهب پورو;
    }
    نتيجو = SDL_Save_BMP_IO_اندروني(&state, dst, closeio);
پورو:
    FreeBMPSaveState(&state);
    أرجع نتيجو;
}

bool SDL_SaveBMP(SDL_Surface *surface, ثابت حرف *file)
{
    BMPSaveState state;
    إذا (!InitBMPSaveState(&state, surface)) {
        أرجع false;
    }

    SDL_IOStream *وهڪرو = SDL_IOFromFile(file, "wb");
    إذا (!وهڪرو) {
        أرجع false;
    }

    bool نتيجو = SDL_Save_BMP_IO_اندروني(&state, وهڪرو, true);
    FreeBMPSaveState(&state);
    أرجع نتيجو;
}

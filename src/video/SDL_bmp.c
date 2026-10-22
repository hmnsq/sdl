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

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#شامل "SDL_pixels_c.h"
#شامل "SDL_surface_c.h"

#تعریف_کرو SAVE_32_ثنائی_ہندسہ_BMP

// Compression encodings for BMP files
#اگر_غیر_تعریف_شدہ BI_RGB
#تعریف_کرو BI_RGB       0
#تعریف_کرو BI_RLE8      1
#تعریف_کرو BI_RLE4      2
#تعریف_کرو BI_BITFIELDS 3
#اگر_ختم

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#اگر_غیر_تعریف_شدہ LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#تعریف_کرو LCS_WINDOWS_COLOR_SPACE 0x57696E20
#اگر_ختم

#اگر_غیر_تعریف_شدہ LCS_sRGB
// 0x73524742 == "sRGB"
#تعریف_کرو LCS_sRGB 0x73524742
#اگر_ختم

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#اگر_غیر_تعریف_شدہ LCS_GM_GRAPHICS
#تعریف_کرو LCS_GM_GRAPHICS 0x00000002
#اگر_ختم

ساکن bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, صحیح isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    صحیح pitch = surface->pitch;
    صحیح اونچائی = surface->h;
    Uint8 *آغاز = (Uint8 *)surface->pixels;
    Uint8 *انتہا = آغاز + (اونچائی * pitch);
    Uint8 *بٹ = انتہا - pitch, *spot;
    صحیح ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ثابت صحیح pixels_فی_byte = (isRle8 ? 1 : 2);

#تعریف_کرو COPY_PIXEL(x)                \
    spot = &بٹ[ofs++];             \
    اگر (spot >= آغاز && spot < انتہا) \
        *spot = (x)

    برائے (;;) {
        اگر (!SDL_ReadU8(src, &ch)) {
            واپس false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        اگر (ch) {
            Uint8 pixelvalue;
            اگر (!SDL_ReadU8(src, &pixelvalue)) {
                واپس false;
            }
            صحیح ich = (صحیح) ch;
            کرو {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_فی_byte;
            } جب (ich > 0);
        } ورنہ {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            اگر (!SDL_ReadU8(src, &ch)) {
                واپس false;
            }
            انتخاب (ch) {
            حالت 0: // end of line
                ofs = 0;
                بٹ -= pitch; // go to previous
                توڑو;
            حالت 1:               // end of bitmap
                واپس true; // success!
            حالت 2:               // delta
                اگر (!SDL_ReadU8(src, &ch)) {
                    واپس false;
                }
                ofs += ch / pixels_فی_byte;
                اگر (ch & pixels_فی_byte) {
                    ofs++;
                }
                اگر (!SDL_ReadU8(src, &ch)) {
                    واپس false;
                }
                بٹ -= (ch * pitch);
                توڑو;
            طےشدہ: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                اگر (pixels_فی_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } ورنہ {
                    needsPad = (((ch + (pixels_فی_byte-1)) / pixels_فی_byte) & (pixels_فی_byte-1)) != 0;
                }

                صحیح ich = (صحیح) ch;
                کرو {
                    Uint8 pixelvalue;
                    اگر (!SDL_ReadU8(src, &pixelvalue)) {
                        واپس false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_فی_byte;
                } جب (ich > 0);

                // pad at even boundary
                اگر (needsPad && !SDL_ReadU8(src, &ch)) {
                    واپس false;
                }
                توڑو;
            }
        }
    }
}

ساکن خالی CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
    صحیح alpha_Channel_انحراف = 0;
#ورنہ
    صحیح alpha_Channel_انحراف = 3;
#اگر_ختم
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_انحراف;
    Uint8 *انتہا = alpha + surface->h * surface->pitch;

    جب (alpha < انتہا) {
        اگر (*alpha != 0) {
            hasAlpha = true;
            توڑو;
        }
        alpha += 4;
    }

    اگر (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_انحراف;
        جب (alpha < انتہا) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 آغاز;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    آغاز = SDL_TellIO(src);
    اگر (آغاز >= 0) {
        اگر (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            اگر (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, آغاز, SDL_IO_SEEK_سیٹ);
    }

    واپس is_BMP;
}

SDL_Surface *SDL_بھرو_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_انحراف = 0;
    صحیح i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *بٹ;
    Uint8 *چوٹی, *انتہا;
    bool چوٹی_نیچے_کو;
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
    Uint32 bi_سائز;
    Sint32 bi_چوڑائی = 0;
    Sint32 bi_اونچائی = 0;
    // Uint16 biPlanes;
    Uint16 bi_ثنائی_ہندسہ_گنتی = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_مستعمل = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = تہی;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        جاؤ مکمل;
    }

    // Read in the BMP file header
    fp_انحراف = SDL_TellIO(src);
    اگر (fp_انحراف < 0) {
        جاؤ مکمل;
    }
    SDL_ClearError();
    اگر (!SDL_IsBMP(src)) {
        SDL_سیٹ_Error("File is not a Windows BMP file");
        جاؤ مکمل;
    }
    اگر (!SDL_ReadU16LE(src, تہی /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, تہی /* bfSize */) ||
        !SDL_ReadU16LE(src, تہی /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, تہی /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_بٹ)) {
        جاؤ مکمل;
    }

    // Read the Win32 BITMAPINFOHEADER
    اگر (!SDL_ReadU32LE(src, &bi_سائز)) {
        جاؤ مکمل;
    }
    اگر (bi_سائز == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        اگر (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, تہی /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ثنائی_ہندسہ_گنتی)) {
            جاؤ مکمل;
        }
        bi_چوڑائی = biWidth16;
        bi_اونچائی = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_مستعمل = 0;
        // biClrImportant = 0;
    } ورنہ اگر (bi_سائز >= 40) { // some version of BITMAPINFOHEADER
        Uint32 سرخی_سائز;
        اگر (!SDL_ReadS32LE(src, &bi_چوڑائی) ||
            !SDL_ReadS32LE(src, &bi_اونچائی) ||
            !SDL_ReadU16LE(src, تہی /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ثنائی_ہندسہ_گنتی) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, تہی /* biSizeImage */) ||
            !SDL_ReadU32LE(src, تہی /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, تہی /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_مستعمل) ||
            !SDL_ReadU32LE(src, تہی /* biClrImportant */)) {
            جاؤ مکمل;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        اگر (bi_سائز != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            اگر (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                اگر (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    جاؤ مکمل;
                }

                // ...v3 adds an alpha mask.
                اگر (bi_سائز >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_نقاب = true;
                    اگر (!SDL_ReadU32LE(src, &Amask)) {
                        جاؤ مکمل;
                    }
                }
            } ورنہ {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                اگر (bi_سائز >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    اگر (!SDL_ReadU32LE(src, تہی /* Rmask */) ||
                        !SDL_ReadU32LE(src, تہی /* Gmask */) ||
                        !SDL_ReadU32LE(src, تہی /* Bmask */)) {
                        جاؤ مکمل;
                    }
                }
                اگر (bi_سائز >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    اگر (!SDL_ReadU32LE(src, تہی /* Amask */)) {
                        جاؤ مکمل;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        سرخی_سائز = (Uint32)(SDL_TellIO(src) - (fp_انحراف + 14));
        اگر (bi_سائز > سرخی_سائز) {
            اگر (SDL_SeekIO(src, (bi_سائز - سرخی_سائز), SDL_IO_SEEK_CUR) < 0) {
                جاؤ مکمل;
            }
        }
    }
    اگر (bi_چوڑائی <= 0 || bi_اونچائی == 0) {
        SDL_سیٹ_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_چوڑائی, bi_اونچائی);
        جاؤ مکمل;
    }
    اگر (bi_اونچائی < 0) {
        چوٹی_نیچے_کو = true;
        bi_اونچائی = -bi_اونچائی;
    } ورنہ {
        چوٹی_نیچے_کو = false;
    }

    // Check for read error
    اگر (SDL_strcmp(SDL_GetError(), "") != 0) {
        جاؤ مکمل;
    }

    // Reject invalid bit depths
    انتخاب (bi_ثنائی_ہندسہ_گنتی) {
    حالت 0:
    حالت 3:
    حالت 5:
    حالت 6:
    حالت 7:
        SDL_سیٹ_Error("%u bpp BMP images are not supported", bi_ثنائی_ہندسہ_گنتی);
        جاؤ مکمل;
    طےشدہ:
        توڑو;
    }

    // RLE4 and RLE8 BMP compression is supported
    انتخاب (biCompression) {
    حالت BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!have_Alpha_نقاب);
        // Default values for the BMP format
        انتخاب (bi_ثنائی_ہندسہ_گنتی) {
        حالت 15:
        حالت 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            توڑو;
        حالت 24:
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#ورنہ
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#اگر_ختم
            توڑو;
        حالت 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            توڑو;
        طےشدہ:
            توڑو;
        }
        توڑو;

    حالت BI_BITFIELDS:
        توڑو; // we handled this in the info header.

    طےشدہ:
        توڑو;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_ثنائی_ہندسہ_گنتی, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_چوڑائی, bi_اونچائی, format);

        اگر (!surface) {
            جاؤ مکمل;
        }
    }

    // Load the palette, if any
    اگر (SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        اگر (!palette) {
            جاؤ مکمل;
        }

        اگر (SDL_SeekIO(src, fp_انحراف + 14 + bi_سائز, SDL_IO_SEEK_سیٹ) < 0) {
            SDL_سیٹ_Error("Error seeking in datastream");
            جاؤ مکمل;
        }

        اگر (bi_ثنائی_ہندسہ_گنتی >= 32) { // we shift biClrUsed by this value later.
            SDL_سیٹ_Error("Unsupported or incorrect biBitCount field");
            جاؤ مکمل;
        }

        اگر (bi_Clr_مستعمل == 0) {
            bi_Clr_مستعمل = 1 << bi_ثنائی_ہندسہ_گنتی;
        }

        اگر (bi_Clr_مستعمل > (Uint32)palette->ncolors) {
            bi_Clr_مستعمل = 1 << bi_ثنائی_ہندسہ_گنتی; // try forcing it?
            اگر (bi_Clr_مستعمل > (Uint32)palette->ncolors) {
                SDL_سیٹ_Error("Unsupported or incorrect biClrUsed field");
                جاؤ مکمل;
            }
        }
        palette->ncolors = bi_Clr_مستعمل;

        اگر (bi_سائز == 12) {
            برائے (i = 0; i < palette->ncolors; ++i) {
                اگر (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    جاؤ مکمل;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } ورنہ {
            برائے (i = 0; i < palette->ncolors; ++i) {
                اگر (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    جاؤ مکمل;
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
    اگر (SDL_SeekIO(src, fp_انحراف + bf_Off_بٹ, SDL_IO_SEEK_سیٹ) < 0) {
        SDL_سیٹ_Error("Error seeking in datastream");
        جاؤ مکمل;
    }
    اگر ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        اگر (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_سیٹ_Error("Error reading from datastream");
            جاؤ مکمل;
        }

        // Success!
        was_error = false;
        جاؤ مکمل;
    }
    چوٹی = (Uint8 *)surface->pixels;
    انتہا = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    اگر (چوٹی_نیچے_کو) {
        بٹ = چوٹی;
    } ورنہ {
        بٹ = انتہا - surface->pitch;
    }
    جب (بٹ >= چوٹی && بٹ < انتہا) {
        اگر (SDL_ReadIO(src, بٹ, surface->pitch) != (size_t)surface->pitch) {
            جاؤ مکمل;
        }
        اگر (bi_ثنائی_ہندسہ_گنتی == 8 && surface->palette && bi_Clr_مستعمل < (1u << bi_ثنائی_ہندسہ_گنتی)) {
            برائے (i = 0; i < surface->w; ++i) {
                اگر (بٹ[i] >= bi_Clr_مستعمل) {
                    SDL_سیٹ_Error("A BMP image contains a pixel with a color out of the palette");
                    جاؤ مکمل;
                }
            }
        }
#اگر SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        انتخاب (bi_ثنائی_ہندسہ_گنتی) {
        حالت 15:
        حالت 16:
        {
            Uint16 *pix = (Uint16 *)بٹ;
            برائے (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            توڑو;
        }

        حالت 32:
        {
            Uint32 *pix = (Uint32 *)بٹ;
            برائے (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            توڑو;
        }
        }
#اگر_ختم

        // Skip padding bytes, ugh
        اگر (pad) {
            Uint8 padbyte;
            برائے (i = 0; i < pad; ++i) {
                اگر (!SDL_ReadU8(src, &padbyte)) {
                    جاؤ مکمل;
                }
            }
        }
        اگر (چوٹی_نیچے_کو) {
            بٹ += surface->pitch;
        } ورنہ {
            بٹ -= surface->pitch;
        }
    }
    اگر (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

مکمل:
    اگر (was_error) {
        اگر (src) {
            SDL_SeekIO(src, fp_انحراف, SDL_IO_SEEK_سیٹ);
        }
        SDL_DestroySurface(surface);
        surface = تہی;
    }
    اگر (closeio && src) {
        SDL_CloseIO(src);
    }
    واپس surface;
}

قسمتعریف ساخت {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ساکن خالی FreeBMPSaveState(BMPSaveState *state)
{
    اگر (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ساکن bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = تہی;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        واپس SDL_InvalidParamError("surface");
    }

#اگر_تعریف_شدہ SAVE_32_ثنائی_ہندسہ_BMP
    // We can save alpha information in a 32-bit BMP
    اگر (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#اگر_ختم // SAVE_32BIT_BMP

    اگر (surface->palette && !state->save32bit) {
        اگر (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } ورنہ {
            SDL_سیٹ_Error("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            جاؤ error;
        }
    } ورنہ اگر ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } ورنہ {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        اگر (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } ورنہ {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        اگر (!state->intermediate_surface) {
            SDL_سیٹ_Error("Couldn't convert image to %d bpp",
                         (صحیح)SDL_BITSPERPIXEL(pixel_format));
            جاؤ error;
        }
    }

    اگر (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    واپس true;
error:
    FreeBMPSaveState(state);
    واپس false;
}

SDL_Surface *SDL_بھرو_BMP(ثابت حرف *file)
{
    SDL_IOStream *دھارا = SDL_IOFromFile(file, "rb");
    اگر (!دھارا) {
        واپس تہی;
    }
    واپس SDL_بھرو_BMP_IO(دھارا, true);
}
ساکن bool SDL_Save_BMP_IO_اندرونی(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_انحراف, new_انحراف;
    صحیح i, pad;
    Uint8 *بٹ;

    // The Win32 BMP file header (14 bytes)
    حرف magic[2] = { 'B', 'M' };
    Uint32 bf_سائز;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_بٹ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_سائز;
    Sint32 bi_چوڑائی;
    Sint32 bi_اونچائی;
    Uint16 biPlanes;
    Uint16 bi_ثنائی_ہندسہ_گنتی;
    Uint32 biCompression;
    Uint32 bi_سائز_Image;
    Sint32 bi_XPels_فی_Meter;
    Sint32 bi_YPels_فی_Meter;
    Uint32 bi_Clr_مستعمل;
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
    Uint32 b_V5_Profile_ڈیٹا = 0;
    Uint32 b_V5_Profile_سائز = 0;
    Uint32 bV5Reserved = 0;

    اگر (SDL_تالا_Surface(state->intermediate_surface)) {
        ثابت size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->بائٹیں_فی_pixel;

        // Set the BMP file header values
        bf_سائز = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_بٹ = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_انحراف = SDL_TellIO(dst);
        اگر (fp_انحراف < 0) {
            جاؤ مکمل;
        }
        اگر (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_سائز) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_بٹ)) {
            جاؤ مکمل;
        }

        // Set the BMP info values
        bi_سائز = 40;
        bi_چوڑائی = state->intermediate_surface->w;
        bi_اونچائی = state->intermediate_surface->h;
        biPlanes = 1;
        bi_ثنائی_ہندسہ_گنتی = state->intermediate_surface->fmt->بٹ_فی_pixel;
        biCompression = BI_RGB;
        bi_سائز_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_فی_Meter = 0;
        bi_YPels_فی_Meter = 0;
        اگر (state->intermediate_surface->palette) {
            bi_Clr_مستعمل = state->intermediate_surface->palette->ncolors;
        } ورنہ {
            bi_Clr_مستعمل = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        اگر (state->save32bit && !state->saveLegacyBMP) {
            bi_سائز = 124;
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
            b_V5_Profile_ڈیٹا = 0;
            b_V5_Profile_سائز = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        اگر (!SDL_WriteU32LE(dst, bi_سائز) ||
            !SDL_WriteS32LE(dst, bi_چوڑائی) ||
            !SDL_WriteS32LE(dst, bi_اونچائی) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_ثنائی_ہندسہ_گنتی) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_سائز_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_فی_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_فی_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_مستعمل) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            جاؤ مکمل;
        }

        // Write the BMP info values
        اگر (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            اگر (!SDL_WriteU32LE(dst, b_V4_Red_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Green_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_نقاب) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_نقاب) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                جاؤ مکمل;
            }
            برائے (i = 0; i < 3 * 3; i++) {
                اگر (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    جاؤ مکمل;
                }
            }
            اگر (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                جاؤ مکمل;
            }
            // Version 5 values
            اگر (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_ڈیٹا) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_سائز) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                جاؤ مکمل;
            }
        }

        // Write the palette (in BGR color order)
        اگر (state->intermediate_surface->palette) {
            SDL_Color *colors;
            صحیح ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            برائے (i = 0; i < ncolors; ++i) {
                اگر (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    جاؤ مکمل;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_بٹ = (Uint32)(SDL_TellIO(dst) - fp_انحراف);
        اگر (SDL_SeekIO(dst, fp_انحراف + 10, SDL_IO_SEEK_سیٹ) < 0) {
            جاؤ مکمل;
        }
        اگر (!SDL_WriteU32LE(dst, bf_Off_بٹ)) {
            جاؤ مکمل;
        }
        اگر (SDL_SeekIO(dst, fp_انحراف + bf_Off_بٹ, SDL_IO_SEEK_سیٹ) < 0) {
            جاؤ مکمل;
        }

        // Write the bitmap image upside down
        بٹ = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        جب (بٹ > (Uint8 *)state->intermediate_surface->pixels) {
            بٹ -= state->intermediate_surface->pitch;
            اگر (SDL_WriteIO(dst, بٹ, bw) != bw) {
                جاؤ مکمل;
            }
            اگر (pad) {
                ثابت Uint8 padbyte = 0;
                برائے (i = 0; i < pad; ++i) {
                    اگر (!SDL_WriteU8(dst, padbyte)) {
                        جاؤ مکمل;
                    }
                }
            }
        }

        // Write the BMP file size
        new_انحراف = SDL_TellIO(dst);
        اگر (new_انحراف < 0) {
            جاؤ مکمل;
        }
        bf_سائز = (Uint32)(new_انحراف - fp_انحراف);
        اگر (SDL_SeekIO(dst, fp_انحراف + 2, SDL_IO_SEEK_سیٹ) < 0) {
            جاؤ مکمل;
        }
        اگر (!SDL_WriteU32LE(dst, bf_سائز)) {
            جاؤ مکمل;
        }
        اگر (SDL_SeekIO(dst, fp_انحراف + bf_سائز, SDL_IO_SEEK_سیٹ) < 0) {
            جاؤ مکمل;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

مکمل:
    اگر (closeio && dst) {
        اگر (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    اگر (was_error) {
        واپس false;
    }
    واپس true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool نتیجہ = true;
    BMPSaveState state;
    اگر (!InitBMPSaveState(&state, surface)) {
        واپس false;
    }
    CHECK_PARAM(!dst) {
        نتیجہ = SDL_InvalidParamError("dst");
        جاؤ مکمل;
    }
    نتیجہ = SDL_Save_BMP_IO_اندرونی(&state, dst, closeio);
مکمل:
    FreeBMPSaveState(&state);
    واپس نتیجہ;
}

bool SDL_SaveBMP(SDL_Surface *surface, ثابت حرف *file)
{
    BMPSaveState state;
    اگر (!InitBMPSaveState(&state, surface)) {
        واپس false;
    }

    SDL_IOStream *دھارا = SDL_IOFromFile(file, "wb");
    اگر (!دھارا) {
        واپس false;
    }

    bool نتیجہ = SDL_Save_BMP_IO_اندرونی(&state, دھارا, true);
    FreeBMPSaveState(&state);
    واپس نتیجہ;
}

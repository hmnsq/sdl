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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"

#define SAVE_32BIT_BMP

// Compression encodings for BMP files
#ifndef BI_RGB
#define BI_RGB       0
#define BI_RLE8      1
#define BI_RLE4      2
#define BI_BITFIELDS 3
#endif

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#ifndef LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#define LCS_WINDOWS_COLOR_SPACE 0x57696E20
#endif

#ifndef LCS_sRGB
// 0x73524742 == "sRGB"
#define LCS_sRGB 0x73524742
#endif

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#ifndef LCS_GM_GRAPHICS
#define LCS_GM_GRAPHICS 0x00000002
#endif

ಸ್ಥಿರ bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, ಪೂರ್ಣಾಙ್ಕ isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    ಪೂರ್ಣಾಙ್ಕ pitch = surface->pitch;
    ಪೂರ್ಣಾಙ್ಕ height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    ಪೂರ್ಣಾಙ್ಕ ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    ಯದಿ (spot >= start && spot < end) \
        *spot = (x)

    ಪ್ರತಿ (;;) {
        ಯದಿ (!SDL_ReadU8(src, &ch)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        ಯದಿ (ch) {
            Uint8 pixelvalue;
            ಯದಿ (!SDL_ReadU8(src, &pixelvalue)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            ಪೂರ್ಣಾಙ್ಕ ich = (ಪೂರ್ಣಾಙ್ಕ) ch;
            ಕುರು {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } ಯಾವತ್ (ich > 0);
        } ಅನ್ಯಥಾ {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            ಯದಿ (!SDL_ReadU8(src, &ch)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
            ವಿಕಲ್ಪ (ch) {
            ಪಕ್ಷ 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                ಭಙ್ಗ;
            ಪಕ್ಷ 1:               // end of bitmap
                ಪ್ರತ್ಯಾಗಮ true; // success!
            ಪಕ್ಷ 2:               // delta
                ಯದಿ (!SDL_ReadU8(src, &ch)) {
                    ಪ್ರತ್ಯಾಗಮ false;
                }
                ofs += ch / pixels_per_byte;
                ಯದಿ (ch & pixels_per_byte) {
                    ofs++;
                }
                ಯದಿ (!SDL_ReadU8(src, &ch)) {
                    ಪ್ರತ್ಯಾಗಮ false;
                }
                bits -= (ch * pitch);
                ಭಙ್ಗ;
            ಸ್ವಭಾವ: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                ಯದಿ (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } ಅನ್ಯಥಾ {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                ಪೂರ್ಣಾಙ್ಕ ich = (ಪೂರ್ಣಾಙ್ಕ) ch;
                ಕುರು {
                    Uint8 pixelvalue;
                    ಯದಿ (!SDL_ReadU8(src, &pixelvalue)) {
                        ಪ್ರತ್ಯಾಗಮ false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } ಯಾವತ್ (ich > 0);

                // pad at even boundary
                ಯದಿ (needsPad && !SDL_ReadU8(src, &ch)) {
                    ಪ್ರತ್ಯಾಗಮ false;
                }
                ಭಙ್ಗ;
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#ಯದಿ SDL_BYTEORDER == SDL_BIG_ENDIAN
    ಪೂರ್ಣಾಙ್ಕ alphaChannelOffset = 0;
#ಅನ್ಯಥಾ
    ಪೂರ್ಣಾಙ್ಕ alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    ಯಾವತ್ (alpha < end) {
        ಯದಿ (*alpha != 0) {
            hasAlpha = true;
            ಭಙ್ಗ;
        }
        alpha += 4;
    }

    ಯದಿ (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        ಯಾವತ್ (alpha < end) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 start;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    start = SDL_TellIO(src);
    ಯದಿ (start >= 0) {
        ಯದಿ (SDL_ReadIO(src, magic, ಪರಿಮಾಣ(magic)) == ಪರಿಮಾಣ(magic)) {
            ಯದಿ (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    ಪ್ರತ್ಯಾಗಮ is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    ಪೂರ್ಣಾಙ್ಕ i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *ತುದಿ, *end;
    bool ತುದಿ_Down;
    bool haveRGBMasks = false;
    bool haveAlphaMask = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth = 0;
    Sint32 biHeight = 0;
    // Uint16 biPlanes;
    Uint16 bi_Bit_ಎಣಿಕೆ = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = ರಿಕ್ತ;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ಗಚ್ಛ done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    ಯದಿ (fp_offset < 0) {
        ಗಚ್ಛ done;
    }
    SDL_ClearError();
    ಯದಿ (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        ಗಚ್ಛ done;
    }
    ಯದಿ (!SDL_ReadU16LE(src, ರಿಕ್ತ /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, ರಿಕ್ತ /* bfSize */) ||
        !SDL_ReadU16LE(src, ರಿಕ್ತ /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, ರಿಕ್ತ /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        ಗಚ್ಛ done;
    }

    // Read the Win32 BITMAPINFOHEADER
    ಯದಿ (!SDL_ReadU32LE(src, &biSize)) {
        ಗಚ್ಛ done;
    }
    ಯದಿ (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        ಯದಿ (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, ರಿಕ್ತ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_ಎಣಿಕೆ)) {
            ಗಚ್ಛ done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } ಅನ್ಯಥಾ ಯದಿ (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        ಯದಿ (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, ರಿಕ್ತ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_ಎಣಿಕೆ) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, ರಿಕ್ತ /* biSizeImage */) ||
            !SDL_ReadU32LE(src, ರಿಕ್ತ /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, ರಿಕ್ತ /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, ರಿಕ್ತ /* biClrImportant */)) {
            ಗಚ್ಛ done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        ಯದಿ (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            ಯದಿ (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                ಯದಿ (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    ಗಚ್ಛ done;
                }

                // ...v3 adds an alpha mask.
                ಯದಿ (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    ಯದಿ (!SDL_ReadU32LE(src, &Amask)) {
                        ಗಚ್ಛ done;
                    }
                }
            } ಅನ್ಯಥಾ {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                ಯದಿ (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    ಯದಿ (!SDL_ReadU32LE(src, ರಿಕ್ತ /* Rmask */) ||
                        !SDL_ReadU32LE(src, ರಿಕ್ತ /* Gmask */) ||
                        !SDL_ReadU32LE(src, ರಿಕ್ತ /* Bmask */)) {
                        ಗಚ್ಛ done;
                    }
                }
                ಯದಿ (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    ಯದಿ (!SDL_ReadU32LE(src, ರಿಕ್ತ /* Amask */)) {
                        ಗಚ್ಛ done;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        headerSize = (Uint32)(SDL_TellIO(src) - (fp_offset + 14));
        ಯದಿ (biSize > headerSize) {
            ಯದಿ (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                ಗಚ್ಛ done;
            }
        }
    }
    ಯದಿ (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        ಗಚ್ಛ done;
    }
    ಯದಿ (biHeight < 0) {
        ತುದಿ_Down = true;
        biHeight = -biHeight;
    } ಅನ್ಯಥಾ {
        ತುದಿ_Down = false;
    }

    // Check for read error
    ಯದಿ (SDL_strcmp(SDL_GetError(), "") != 0) {
        ಗಚ್ಛ done;
    }

    // Reject invalid bit depths
    ವಿಕಲ್ಪ (bi_Bit_ಎಣಿಕೆ) {
    ಪಕ್ಷ 0:
    ಪಕ್ಷ 3:
    ಪಕ್ಷ 5:
    ಪಕ್ಷ 6:
    ಪಕ್ಷ 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_ಎಣಿಕೆ);
        ಗಚ್ಛ done;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }

    // RLE4 and RLE8 BMP compression is supported
    ವಿಕಲ್ಪ (biCompression) {
    ಪಕ್ಷ BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        ವಿಕಲ್ಪ (bi_Bit_ಎಣಿಕೆ) {
        ಪಕ್ಷ 15:
        ಪಕ್ಷ 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            ಭಙ್ಗ;
        ಪಕ್ಷ 24:
#ಯದಿ SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#ಅನ್ಯಥಾ
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            ಭಙ್ಗ;
        ಪಕ್ಷ 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ BI_BITFIELDS:
        ಭಙ್ಗ; // we handled this in the info header.

    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_ಎಣಿಕೆ, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        ಯದಿ (!surface) {
            ಗಚ್ಛ done;
        }
    }

    // Load the palette, if any
    ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ಯದಿ (!palette) {
            ಗಚ್ಛ done;
        }

        ಯದಿ (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            ಗಚ್ಛ done;
        }

        ಯದಿ (bi_Bit_ಎಣಿಕೆ >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            ಗಚ್ಛ done;
        }

        ಯದಿ (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_ಎಣಿಕೆ;
        }

        ಯದಿ (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_ಎಣಿಕೆ; // try forcing it?
            ಯದಿ (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                ಗಚ್ಛ done;
            }
        }
        palette->ncolors = biClrUsed;

        ಯದಿ (biSize == 12) {
            ಪ್ರತಿ (i = 0; i < palette->ncolors; ++i) {
                ಯದಿ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    ಗಚ್ಛ done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } ಅನ್ಯಥಾ {
            ಪ್ರತಿ (i = 0; i < palette->ncolors; ++i) {
                ಯದಿ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    ಗಚ್ಛ done;
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
    ಯದಿ (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        ಗಚ್ಛ done;
    }
    ಯದಿ ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        ಯದಿ (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            ಗಚ್ಛ done;
        }

        // Success!
        was_error = false;
        ಗಚ್ಛ done;
    }
    ತುದಿ = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    ಯದಿ (ತುದಿ_Down) {
        bits = ತುದಿ;
    } ಅನ್ಯಥಾ {
        bits = end - surface->pitch;
    }
    ಯಾವತ್ (bits >= ತುದಿ && bits < end) {
        ಯದಿ (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (bi_Bit_ಎಣಿಕೆ == 8 && surface->palette && biClrUsed < (1u << bi_Bit_ಎಣಿಕೆ)) {
            ಪ್ರತಿ (i = 0; i < surface->w; ++i) {
                ಯದಿ (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    ಗಚ್ಛ done;
                }
            }
        }
#ಯದಿ SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        ವಿಕಲ್ಪ (bi_Bit_ಎಣಿಕೆ) {
        ಪಕ್ಷ 15:
        ಪಕ್ಷ 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            ಪ್ರತಿ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            ಭಙ್ಗ;
        }

        ಪಕ್ಷ 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            ಪ್ರತಿ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            ಭಙ್ಗ;
        }
        }
#endif

        // Skip padding bytes, ugh
        ಯದಿ (pad) {
            Uint8 padbyte;
            ಪ್ರತಿ (i = 0; i < pad; ++i) {
                ಯದಿ (!SDL_ReadU8(src, &padbyte)) {
                    ಗಚ್ಛ done;
                }
            }
        }
        ಯದಿ (ತುದಿ_Down) {
            bits += surface->pitch;
        } ಅನ್ಯಥಾ {
            bits -= surface->pitch;
        }
    }
    ಯದಿ (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    ಯದಿ (was_error) {
        ಯದಿ (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = ರಿಕ್ತ;
    }
    ಯದಿ (closeio && src) {
        SDL_CloseIO(src);
    }
    ಪ್ರತ್ಯಾಗಮ surface;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ಸ್ಥಿರ ಶೂನ್ಯ FreeBMPSaveState(BMPSaveState *state)
{
    ಯದಿ (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ಸ್ಥಿರ bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = ರಿಕ್ತ;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    ಯದಿ (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    ಯದಿ (surface->palette && !state->save32bit) {
        ಯದಿ (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } ಅನ್ಯಥಾ {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            ಗಚ್ಛ error;
        }
    } ಅನ್ಯಥಾ ಯದಿ ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } ಅನ್ಯಥಾ {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        ಯದಿ (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } ಅನ್ಯಥಾ {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        ಯದಿ (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (ಪೂರ್ಣಾಙ್ಕ)SDL_BITSPERPIXEL(pixel_format));
            ಗಚ್ಛ error;
        }
    }

    ಯದಿ (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    ಪ್ರತ್ಯಾಗಮ true;
error:
    FreeBMPSaveState(state);
    ಪ್ರತ್ಯಾಗಮ false;
}

SDL_Surface *SDL_LoadBMP(ಧ್ರುವ ವರ್ಣ *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    ಯದಿ (!stream) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_LoadBMP_IO(stream, true);
}
ಸ್ಥಿರ bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    ಪೂರ್ಣಾಙ್ಕ i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    ವರ್ಣ magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_ಎಣಿಕೆ;
    Uint32 biCompression;
    Uint32 biSizeImage;
    Sint32 biXPelsPerMeter;
    Sint32 biYPelsPerMeter;
    Uint32 biClrUsed;
    Uint32 biClrImportant;

    // The additional header members from the Win32 BITMAPV4HEADER struct (108 bytes in total)
    Uint32 bV4RedMask = 0;
    Uint32 bV4GreenMask = 0;
    Uint32 bV4BlueMask = 0;
    Uint32 bV4AlphaMask = 0;
    Uint32 bV4CSType = 0;
    Sint32 bV4Endpoints[3 * 3] = { 0 };
    Uint32 bV4GammaRed = 0;
    Uint32 bV4GammaGreen = 0;
    Uint32 bV4GammaBlue = 0;

    // The additional header members from the Win32 BITMAPV5HEADER struct (124 bytes in total)
    Uint32 bV5Intent = 0;
    Uint32 bV5ProfileData = 0;
    Uint32 bV5ProfileSize = 0;
    Uint32 bV5Reserved = 0;

    ಯದಿ (SDL_LockSurface(state->intermediate_surface)) {
        ಧ್ರುವ size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        ಯದಿ (fp_offset < 0) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            ಗಚ್ಛ done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_ಎಣಿಕೆ = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        ಯದಿ (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } ಅನ್ಯಥಾ {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        ಯದಿ (state->save32bit && !state->saveLegacyBMP) {
            biSize = 124;
            // Version 4 values
            biCompression = BI_BITFIELDS;
            // The BMP format is always little endian, these masks stay the same
            bV4RedMask = 0x00ff0000;
            bV4GreenMask = 0x0000ff00;
            bV4BlueMask = 0x000000ff;
            bV4AlphaMask = 0xff000000;
            bV4CSType = LCS_sRGB;
            bV4GammaRed = 0;
            bV4GammaGreen = 0;
            bV4GammaBlue = 0;
            // Version 5 values
            bV5Intent = LCS_GM_GRAPHICS;
            bV5ProfileData = 0;
            bV5ProfileSize = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        ಯದಿ (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_ಎಣಿಕೆ) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            ಗಚ್ಛ done;
        }

        // Write the BMP info values
        ಯದಿ (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            ಯದಿ (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                ಗಚ್ಛ done;
            }
            ಪ್ರತಿ (i = 0; i < 3 * 3; i++) {
                ಯದಿ (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    ಗಚ್ಛ done;
                }
            }
            ಯದಿ (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                ಗಚ್ಛ done;
            }
            // Version 5 values
            ಯದಿ (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                ಗಚ್ಛ done;
            }
        }

        // Write the palette (in BGR color order)
        ಯದಿ (state->intermediate_surface->palette) {
            SDL_Color *colors;
            ಪೂರ್ಣಾಙ್ಕ ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            ಪ್ರತಿ (i = 0; i < ncolors; ++i) {
                ಯದಿ (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    ಗಚ್ಛ done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        ಯದಿ (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (!SDL_WriteU32LE(dst, bfOffBits)) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            ಗಚ್ಛ done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        ಯಾವತ್ (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            ಯದಿ (SDL_WriteIO(dst, bits, bw) != bw) {
                ಗಚ್ಛ done;
            }
            ಯದಿ (pad) {
                ಧ್ರುವ Uint8 padbyte = 0;
                ಪ್ರತಿ (i = 0; i < pad; ++i) {
                    ಯದಿ (!SDL_WriteU8(dst, padbyte)) {
                        ಗಚ್ಛ done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        ಯದಿ (new_offset < 0) {
            ಗಚ್ಛ done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        ಯದಿ (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (!SDL_WriteU32LE(dst, bfSize)) {
            ಗಚ್ಛ done;
        }
        ಯದಿ (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            ಗಚ್ಛ done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    ಯದಿ (closeio && dst) {
        ಯದಿ (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    ಯದಿ (was_error) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    ಯದಿ (!InitBMPSaveState(&state, surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        ಗಚ್ಛ done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_SaveBMP(SDL_Surface *surface, ಧ್ರುವ ವರ್ಣ *file)
{
    BMPSaveState state;
    ಯದಿ (!InitBMPSaveState(&state, surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    ಯದಿ (!stream) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    ಪ್ರತ್ಯಾಗಮ result;
}

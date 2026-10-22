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

#ವ್ಯಾಖ್ಯಾನಿಸು SAVE_32_ಬಿಟ್_BMP

// Compression encodings for BMP files
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ BI_RGB
#ವ್ಯಾಖ್ಯಾನಿಸು BI_RGB       0
#ವ್ಯಾಖ್ಯಾನಿಸು BI_RLE8      1
#ವ್ಯಾಖ್ಯಾನಿಸು BI_RLE4      2
#ವ್ಯಾಖ್ಯಾನಿಸು BI_BITFIELDS 3
#ಆದರೆ_ಅಂತ್ಯ

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#ವ್ಯಾಖ್ಯಾನಿಸು LCS_WINDOWS_COLOR_SPACE 0x57696E20
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ LCS_sRGB
// 0x73524742 == "sRGB"
#ವ್ಯಾಖ್ಯಾನಿಸು LCS_sRGB 0x73524742
#ಆದರೆ_ಅಂತ್ಯ

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ LCS_GM_GRAPHICS
#ವ್ಯಾಖ್ಯಾನಿಸು LCS_GM_GRAPHICS 0x00000002
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, ಪೂರ್ಣಾಂಕ isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    ಪೂರ್ಣಾಂಕ pitch = surface->pitch;
    ಪೂರ್ಣಾಂಕ ಎತ್ತರ = surface->h;
    Uint8 *ಆರಂಭ = (Uint8 *)surface->pixels;
    Uint8 *ಕೊನೆ = ಆರಂಭ + (ಎತ್ತರ * pitch);
    Uint8 *ಬಿಟ್ಟುಗಳು = ಕೊನೆ - pitch, *spot;
    ಪೂರ್ಣಾಂಕ ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ pixels_ಪ್ರತಿ_byte = (isRle8 ? 1 : 2);

#ವ್ಯಾಖ್ಯಾನಿಸು COPY_PIXEL(x)                \
    spot = &ಬಿಟ್ಟುಗಳು[ofs++];             \
    ಆದರೆ (spot >= ಆರಂಭ && spot < ಕೊನೆ) \
        *spot = (x)

    ಗಾಗಿ (;;) {
        ಆದರೆ (!SDL_ReadU8(src, &ch)) {
            ಹಿಂತಿರುಗಿ false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        ಆದರೆ (ch) {
            Uint8 pixelvalue;
            ಆದರೆ (!SDL_ReadU8(src, &pixelvalue)) {
                ಹಿಂತಿರುಗಿ false;
            }
            ಪೂರ್ಣಾಂಕ ich = (ಪೂರ್ಣಾಂಕ) ch;
            ಮಾಡು {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_ಪ್ರತಿ_byte;
            } ಆಗ (ich > 0);
        } ಇಲ್ಲದಿದ್ದರೆ {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            ಆದರೆ (!SDL_ReadU8(src, &ch)) {
                ಹಿಂತಿರುಗಿ false;
            }
            ಆಯ್ಕೆ (ch) {
            ಸ್ಥಿತಿ 0: // end of line
                ofs = 0;
                ಬಿಟ್ಟುಗಳು -= pitch; // go to previous
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 1:               // end of bitmap
                ಹಿಂತಿರುಗಿ true; // success!
            ಸ್ಥಿತಿ 2:               // delta
                ಆದರೆ (!SDL_ReadU8(src, &ch)) {
                    ಹಿಂತಿರುಗಿ false;
                }
                ofs += ch / pixels_ಪ್ರತಿ_byte;
                ಆದರೆ (ch & pixels_ಪ್ರತಿ_byte) {
                    ofs++;
                }
                ಆದರೆ (!SDL_ReadU8(src, &ch)) {
                    ಹಿಂತಿರುಗಿ false;
                }
                ಬಿಟ್ಟುಗಳು -= (ch * pitch);
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                ಆದರೆ (pixels_ಪ್ರತಿ_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    needsPad = (((ch + (pixels_ಪ್ರತಿ_byte-1)) / pixels_ಪ್ರತಿ_byte) & (pixels_ಪ್ರತಿ_byte-1)) != 0;
                }

                ಪೂರ್ಣಾಂಕ ich = (ಪೂರ್ಣಾಂಕ) ch;
                ಮಾಡು {
                    Uint8 pixelvalue;
                    ಆದರೆ (!SDL_ReadU8(src, &pixelvalue)) {
                        ಹಿಂತಿರುಗಿ false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_ಪ್ರತಿ_byte;
                } ಆಗ (ich > 0);

                // pad at even boundary
                ಆದರೆ (needsPad && !SDL_ReadU8(src, &ch)) {
                    ಹಿಂತಿರುಗಿ false;
                }
                ನಿಲ್ಲಿಸು;
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
    ಪೂರ್ಣಾಂಕ alpha_Channel_ಸ್ಥಾನಾಂತರ = 0;
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ alpha_Channel_ಸ್ಥಾನಾಂತರ = 3;
#ಆದರೆ_ಅಂತ್ಯ
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_ಸ್ಥಾನಾಂತರ;
    Uint8 *ಕೊನೆ = alpha + surface->h * surface->pitch;

    ಆಗ (alpha < ಕೊನೆ) {
        ಆದರೆ (*alpha != 0) {
            hasAlpha = true;
            ನಿಲ್ಲಿಸು;
        }
        alpha += 4;
    }

    ಆದರೆ (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_ಸ್ಥಾನಾಂತರ;
        ಆಗ (alpha < ಕೊನೆ) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 ಆರಂಭ;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    ಆರಂಭ = SDL_TellIO(src);
    ಆದರೆ (ಆರಂಭ >= 0) {
        ಆದರೆ (SDL_ReadIO(src, magic, ಗಾತ್ರ(magic)) == ಗಾತ್ರ(magic)) {
            ಆದರೆ (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, ಆರಂಭ, SDL_IO_SEEK_ಗಣ);
    }

    ಹಿಂತಿರುಗಿ is_BMP;
}

SDL_Surface *SDL_ತುಂಬು_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_ಸ್ಥಾನಾಂತರ = 0;
    ಪೂರ್ಣಾಂಕ i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *ಬಿಟ್ಟುಗಳು;
    Uint8 *ತುದಿ, *ಕೊನೆ;
    bool ತುದಿ_ಕೆಳಕ್ಕೆ;
    bool haveRGBMasks = false;
    bool have_Alpha_ಮುಖವಾಡ = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bf_Off_ಬಿಟ್ಟುಗಳು;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_ಗಾತ್ರ;
    Sint32 bi_ಅಗಲ = 0;
    Sint32 bi_ಎತ್ತರ = 0;
    // Uint16 biPlanes;
    Uint16 bi_ಬಿಟ್_ಎಣಿಕೆ = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_ಬಳಸಿದ = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = ಖಾಲಿ;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ಹೋಗು ಮುಗಿದ;
    }

    // Read in the BMP file header
    fp_ಸ್ಥಾನಾಂತರ = SDL_TellIO(src);
    ಆದರೆ (fp_ಸ್ಥಾನಾಂತರ < 0) {
        ಹೋಗು ಮುಗಿದ;
    }
    SDL_ClearError();
    ಆದರೆ (!SDL_IsBMP(src)) {
        SDL_ಗಣ_Error("File is not a Windows BMP file");
        ಹೋಗು ಮುಗಿದ;
    }
    ಆದರೆ (!SDL_ReadU16LE(src, ಖಾಲಿ /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, ಖಾಲಿ /* bfSize */) ||
        !SDL_ReadU16LE(src, ಖಾಲಿ /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, ಖಾಲಿ /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_ಬಿಟ್ಟುಗಳು)) {
        ಹೋಗು ಮುಗಿದ;
    }

    // Read the Win32 BITMAPINFOHEADER
    ಆದರೆ (!SDL_ReadU32LE(src, &bi_ಗಾತ್ರ)) {
        ಹೋಗು ಮುಗಿದ;
    }
    ಆದರೆ (bi_ಗಾತ್ರ == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        ಆದರೆ (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, ಖಾಲಿ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ಬಿಟ್_ಎಣಿಕೆ)) {
            ಹೋಗು ಮುಗಿದ;
        }
        bi_ಅಗಲ = biWidth16;
        bi_ಎತ್ತರ = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_ಬಳಸಿದ = 0;
        // biClrImportant = 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (bi_ಗಾತ್ರ >= 40) { // some version of BITMAPINFOHEADER
        Uint32 ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;
        ಆದರೆ (!SDL_ReadS32LE(src, &bi_ಅಗಲ) ||
            !SDL_ReadS32LE(src, &bi_ಎತ್ತರ) ||
            !SDL_ReadU16LE(src, ಖಾಲಿ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ಬಿಟ್_ಎಣಿಕೆ) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, ಖಾಲಿ /* biSizeImage */) ||
            !SDL_ReadU32LE(src, ಖಾಲಿ /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, ಖಾಲಿ /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_ಬಳಸಿದ) ||
            !SDL_ReadU32LE(src, ಖಾಲಿ /* biClrImportant */)) {
            ಹೋಗು ಮುಗಿದ;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        ಆದರೆ (bi_ಗಾತ್ರ != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            ಆದರೆ (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                ಆದರೆ (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    ಹೋಗು ಮುಗಿದ;
                }

                // ...v3 adds an alpha mask.
                ಆದರೆ (bi_ಗಾತ್ರ >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_ಮುಖವಾಡ = true;
                    ಆದರೆ (!SDL_ReadU32LE(src, &Amask)) {
                        ಹೋಗು ಮುಗಿದ;
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                ಆದರೆ (bi_ಗಾತ್ರ >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    ಆದರೆ (!SDL_ReadU32LE(src, ಖಾಲಿ /* Rmask */) ||
                        !SDL_ReadU32LE(src, ಖಾಲಿ /* Gmask */) ||
                        !SDL_ReadU32LE(src, ಖಾಲಿ /* Bmask */)) {
                        ಹೋಗು ಮುಗಿದ;
                    }
                }
                ಆದರೆ (bi_ಗಾತ್ರ >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    ಆದರೆ (!SDL_ReadU32LE(src, ಖಾಲಿ /* Amask */)) {
                        ಹೋಗು ಮುಗಿದ;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ = (Uint32)(SDL_TellIO(src) - (fp_ಸ್ಥಾನಾಂತರ + 14));
        ಆದರೆ (bi_ಗಾತ್ರ > ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) {
            ಆದರೆ (SDL_SeekIO(src, (bi_ಗಾತ್ರ - ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ), SDL_IO_SEEK_CUR) < 0) {
                ಹೋಗು ಮುಗಿದ;
            }
        }
    }
    ಆದರೆ (bi_ಅಗಲ <= 0 || bi_ಎತ್ತರ == 0) {
        SDL_ಗಣ_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_ಅಗಲ, bi_ಎತ್ತರ);
        ಹೋಗು ಮುಗಿದ;
    }
    ಆದರೆ (bi_ಎತ್ತರ < 0) {
        ತುದಿ_ಕೆಳಕ್ಕೆ = true;
        bi_ಎತ್ತರ = -bi_ಎತ್ತರ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ತುದಿ_ಕೆಳಕ್ಕೆ = false;
    }

    // Check for read error
    ಆದರೆ (SDL_strcmp(SDL_GetError(), "") != 0) {
        ಹೋಗು ಮುಗಿದ;
    }

    // Reject invalid bit depths
    ಆಯ್ಕೆ (bi_ಬಿಟ್_ಎಣಿಕೆ) {
    ಸ್ಥಿತಿ 0:
    ಸ್ಥಿತಿ 3:
    ಸ್ಥಿತಿ 5:
    ಸ್ಥಿತಿ 6:
    ಸ್ಥಿತಿ 7:
        SDL_ಗಣ_Error("%u bpp BMP images are not supported", bi_ಬಿಟ್_ಎಣಿಕೆ);
        ಹೋಗು ಮುಗಿದ;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

    // RLE4 and RLE8 BMP compression is supported
    ಆಯ್ಕೆ (biCompression) {
    ಸ್ಥಿತಿ BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!have_Alpha_ಮುಖವಾಡ);
        // Default values for the BMP format
        ಆಯ್ಕೆ (bi_ಬಿಟ್_ಎಣಿಕೆ) {
        ಸ್ಥಿತಿ 15:
        ಸ್ಥಿತಿ 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 24:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#ಇಲ್ಲದಿದ್ದರೆ
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#ಆದರೆ_ಅಂತ್ಯ
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ BI_BITFIELDS:
        ನಿಲ್ಲಿಸು; // we handled this in the info header.

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_ಬಿಟ್_ಎಣಿಕೆ, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_ಅಗಲ, bi_ಎತ್ತರ, format);

        ಆದರೆ (!surface) {
            ಹೋಗು ಮುಗಿದ;
        }
    }

    // Load the palette, if any
    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ಆದರೆ (!palette) {
            ಹೋಗು ಮುಗಿದ;
        }

        ಆದರೆ (SDL_SeekIO(src, fp_ಸ್ಥಾನಾಂತರ + 14 + bi_ಗಾತ್ರ, SDL_IO_SEEK_ಗಣ) < 0) {
            SDL_ಗಣ_Error("Error seeking in datastream");
            ಹೋಗು ಮುಗಿದ;
        }

        ಆದರೆ (bi_ಬಿಟ್_ಎಣಿಕೆ >= 32) { // we shift biClrUsed by this value later.
            SDL_ಗಣ_Error("Unsupported or incorrect biBitCount field");
            ಹೋಗು ಮುಗಿದ;
        }

        ಆದರೆ (bi_Clr_ಬಳಸಿದ == 0) {
            bi_Clr_ಬಳಸಿದ = 1 << bi_ಬಿಟ್_ಎಣಿಕೆ;
        }

        ಆದರೆ (bi_Clr_ಬಳಸಿದ > (Uint32)palette->ncolors) {
            bi_Clr_ಬಳಸಿದ = 1 << bi_ಬಿಟ್_ಎಣಿಕೆ; // try forcing it?
            ಆದರೆ (bi_Clr_ಬಳಸಿದ > (Uint32)palette->ncolors) {
                SDL_ಗಣ_Error("Unsupported or incorrect biClrUsed field");
                ಹೋಗು ಮುಗಿದ;
            }
        }
        palette->ncolors = bi_Clr_ಬಳಸಿದ;

        ಆದರೆ (bi_ಗಾತ್ರ == 12) {
            ಗಾಗಿ (i = 0; i < palette->ncolors; ++i) {
                ಆದರೆ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    ಹೋಗು ಮುಗಿದ;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಾಗಿ (i = 0; i < palette->ncolors; ++i) {
                ಆದರೆ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    ಹೋಗು ಮುಗಿದ;
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
    ಆದರೆ (SDL_SeekIO(src, fp_ಸ್ಥಾನಾಂತರ + bf_Off_ಬಿಟ್ಟುಗಳು, SDL_IO_SEEK_ಗಣ) < 0) {
        SDL_ಗಣ_Error("Error seeking in datastream");
        ಹೋಗು ಮುಗಿದ;
    }
    ಆದರೆ ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        ಆದರೆ (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_ಗಣ_Error("Error reading from datastream");
            ಹೋಗು ಮುಗಿದ;
        }

        // Success!
        was_error = false;
        ಹೋಗು ಮುಗಿದ;
    }
    ತುದಿ = (Uint8 *)surface->pixels;
    ಕೊನೆ = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    ಆದರೆ (ತುದಿ_ಕೆಳಕ್ಕೆ) {
        ಬಿಟ್ಟುಗಳು = ತುದಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬಿಟ್ಟುಗಳು = ಕೊನೆ - surface->pitch;
    }
    ಆಗ (ಬಿಟ್ಟುಗಳು >= ತುದಿ && ಬಿಟ್ಟುಗಳು < ಕೊನೆ) {
        ಆದರೆ (SDL_ReadIO(src, ಬಿಟ್ಟುಗಳು, surface->pitch) != (size_t)surface->pitch) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (bi_ಬಿಟ್_ಎಣಿಕೆ == 8 && surface->palette && bi_Clr_ಬಳಸಿದ < (1u << bi_ಬಿಟ್_ಎಣಿಕೆ)) {
            ಗಾಗಿ (i = 0; i < surface->w; ++i) {
                ಆದರೆ (ಬಿಟ್ಟುಗಳು[i] >= bi_Clr_ಬಳಸಿದ) {
                    SDL_ಗಣ_Error("A BMP image contains a pixel with a color out of the palette");
                    ಹೋಗು ಮುಗಿದ;
                }
            }
        }
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        ಆಯ್ಕೆ (bi_ಬಿಟ್_ಎಣಿಕೆ) {
        ಸ್ಥಿತಿ 15:
        ಸ್ಥಿತಿ 16:
        {
            Uint16 *pix = (Uint16 *)ಬಿಟ್ಟುಗಳು;
            ಗಾಗಿ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            ನಿಲ್ಲಿಸು;
        }

        ಸ್ಥಿತಿ 32:
        {
            Uint32 *pix = (Uint32 *)ಬಿಟ್ಟುಗಳು;
            ಗಾಗಿ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            ನಿಲ್ಲಿಸು;
        }
        }
#ಆದರೆ_ಅಂತ್ಯ

        // Skip padding bytes, ugh
        ಆದರೆ (pad) {
            Uint8 padbyte;
            ಗಾಗಿ (i = 0; i < pad; ++i) {
                ಆದರೆ (!SDL_ReadU8(src, &padbyte)) {
                    ಹೋಗು ಮುಗಿದ;
                }
            }
        }
        ಆದರೆ (ತುದಿ_ಕೆಳಕ್ಕೆ) {
            ಬಿಟ್ಟುಗಳು += surface->pitch;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬಿಟ್ಟುಗಳು -= surface->pitch;
        }
    }
    ಆದರೆ (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

ಮುಗಿದ:
    ಆದರೆ (was_error) {
        ಆದರೆ (src) {
            SDL_SeekIO(src, fp_ಸ್ಥಾನಾಂತರ, SDL_IO_SEEK_ಗಣ);
        }
        SDL_DestroySurface(surface);
        surface = ಖಾಲಿ;
    }
    ಆದರೆ (closeio && src) {
        SDL_CloseIO(src);
    }
    ಹಿಂತಿರುಗಿ surface;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ಸ್ಥಿರ ಶೂನ್ಯ FreeBMPSaveState(BMPSaveState *state)
{
    ಆದರೆ (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ಸ್ಥಿರ bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = ಖಾಲಿ;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SAVE_32_ಬಿಟ್_BMP
    // We can save alpha information in a 32-bit BMP
    ಆದರೆ (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#ಆದರೆ_ಅಂತ್ಯ // SAVE_32BIT_BMP

    ಆದರೆ (surface->palette && !state->save32bit) {
        ಆದರೆ (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_ಗಣ_Error("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            ಹೋಗು error;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        ಆದರೆ (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } ಇಲ್ಲದಿದ್ದರೆ {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        ಆದರೆ (!state->intermediate_surface) {
            SDL_ಗಣ_Error("Couldn't convert image to %d bpp",
                         (ಪೂರ್ಣಾಂಕ)SDL_BITSPERPIXEL(pixel_format));
            ಹೋಗು error;
        }
    }

    ಆದರೆ (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    ಹಿಂತಿರುಗಿ true;
error:
    FreeBMPSaveState(state);
    ಹಿಂತಿರುಗಿ false;
}

SDL_Surface *SDL_ತುಂಬು_BMP(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file)
{
    SDL_IOStream *ಹರಿವು = SDL_IOFromFile(file, "rb");
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ SDL_ತುಂಬು_BMP_IO(ಹರಿವು, true);
}
ಸ್ಥಿರ bool SDL_Save_BMP_IO_ಆಂತರಿಕ(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_ಸ್ಥಾನಾಂತರ, new_ಸ್ಥಾನಾಂತರ;
    ಪೂರ್ಣಾಂಕ i, pad;
    Uint8 *ಬಿಟ್ಟುಗಳು;

    // The Win32 BMP file header (14 bytes)
    ಅಕ್ಷರ magic[2] = { 'B', 'M' };
    Uint32 bf_ಗಾತ್ರ;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_ಬಿಟ್ಟುಗಳು;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_ಗಾತ್ರ;
    Sint32 bi_ಅಗಲ;
    Sint32 bi_ಎತ್ತರ;
    Uint16 biPlanes;
    Uint16 bi_ಬಿಟ್_ಎಣಿಕೆ;
    Uint32 biCompression;
    Uint32 bi_ಗಾತ್ರ_Image;
    Sint32 bi_XPels_ಪ್ರತಿ_Meter;
    Sint32 bi_YPels_ಪ್ರತಿ_Meter;
    Uint32 bi_Clr_ಬಳಸಿದ;
    Uint32 biClrImportant;

    // The additional header members from the Win32 BITMAPV4HEADER struct (108 bytes in total)
    Uint32 b_V4_Red_ಮುಖವಾಡ = 0;
    Uint32 b_V4_Green_ಮುಖವಾಡ = 0;
    Uint32 b_V4_Blue_ಮುಖವಾಡ = 0;
    Uint32 b_V4_Alpha_ಮುಖವಾಡ = 0;
    Uint32 bV4CSType = 0;
    Sint32 bV4Endpoints[3 * 3] = { 0 };
    Uint32 bV4GammaRed = 0;
    Uint32 bV4GammaGreen = 0;
    Uint32 bV4GammaBlue = 0;

    // The additional header members from the Win32 BITMAPV5HEADER struct (124 bytes in total)
    Uint32 bV5Intent = 0;
    Uint32 b_V5_Profile_ದತ್ತಾಂಶ = 0;
    Uint32 b_V5_Profile_ಗಾತ್ರ = 0;
    Uint32 bV5Reserved = 0;

    ಆದರೆ (SDL_ಬೀಗ_Surface(state->intermediate_surface)) {
        ಸ್ಥಿರಾಂಕ size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

        // Set the BMP file header values
        bf_ಗಾತ್ರ = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_ಬಿಟ್ಟುಗಳು = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_ಸ್ಥಾನಾಂತರ = SDL_TellIO(dst);
        ಆದರೆ (fp_ಸ್ಥಾನಾಂತರ < 0) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_ಗಾತ್ರ) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_ಬಿಟ್ಟುಗಳು)) {
            ಹೋಗು ಮುಗಿದ;
        }

        // Set the BMP info values
        bi_ಗಾತ್ರ = 40;
        bi_ಅಗಲ = state->intermediate_surface->w;
        bi_ಎತ್ತರ = state->intermediate_surface->h;
        biPlanes = 1;
        bi_ಬಿಟ್_ಎಣಿಕೆ = state->intermediate_surface->fmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel;
        biCompression = BI_RGB;
        bi_ಗಾತ್ರ_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_ಪ್ರತಿ_Meter = 0;
        bi_YPels_ಪ್ರತಿ_Meter = 0;
        ಆದರೆ (state->intermediate_surface->palette) {
            bi_Clr_ಬಳಸಿದ = state->intermediate_surface->palette->ncolors;
        } ಇಲ್ಲದಿದ್ದರೆ {
            bi_Clr_ಬಳಸಿದ = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        ಆದರೆ (state->save32bit && !state->saveLegacyBMP) {
            bi_ಗಾತ್ರ = 124;
            // Version 4 values
            biCompression = BI_BITFIELDS;
            // The BMP format is always little endian, these masks stay the same
            b_V4_Red_ಮುಖವಾಡ = 0x00ff0000;
            b_V4_Green_ಮುಖವಾಡ = 0x0000ff00;
            b_V4_Blue_ಮುಖವಾಡ = 0x000000ff;
            b_V4_Alpha_ಮುಖವಾಡ = 0xff000000;
            bV4CSType = LCS_sRGB;
            bV4GammaRed = 0;
            bV4GammaGreen = 0;
            bV4GammaBlue = 0;
            // Version 5 values
            bV5Intent = LCS_GM_GRAPHICS;
            b_V5_Profile_ದತ್ತಾಂಶ = 0;
            b_V5_Profile_ಗಾತ್ರ = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        ಆದರೆ (!SDL_WriteU32LE(dst, bi_ಗಾತ್ರ) ||
            !SDL_WriteS32LE(dst, bi_ಅಗಲ) ||
            !SDL_WriteS32LE(dst, bi_ಎತ್ತರ) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_ಬಿಟ್_ಎಣಿಕೆ) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_ಗಾತ್ರ_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_ಪ್ರತಿ_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_ಪ್ರತಿ_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_ಬಳಸಿದ) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            ಹೋಗು ಮುಗಿದ;
        }

        // Write the BMP info values
        ಆದರೆ (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            ಆದರೆ (!SDL_WriteU32LE(dst, b_V4_Red_ಮುಖವಾಡ) ||
                !SDL_WriteU32LE(dst, b_V4_Green_ಮುಖವಾಡ) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_ಮುಖವಾಡ) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_ಮುಖವಾಡ) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                ಹೋಗು ಮುಗಿದ;
            }
            ಗಾಗಿ (i = 0; i < 3 * 3; i++) {
                ಆದರೆ (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    ಹೋಗು ಮುಗಿದ;
                }
            }
            ಆದರೆ (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                ಹೋಗು ಮುಗಿದ;
            }
            // Version 5 values
            ಆದರೆ (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_ದತ್ತಾಂಶ) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_ಗಾತ್ರ) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                ಹೋಗು ಮುಗಿದ;
            }
        }

        // Write the palette (in BGR color order)
        ಆದರೆ (state->intermediate_surface->palette) {
            SDL_Color *colors;
            ಪೂರ್ಣಾಂಕ ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            ಗಾಗಿ (i = 0; i < ncolors; ++i) {
                ಆದರೆ (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    ಹೋಗು ಮುಗಿದ;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_ಬಿಟ್ಟುಗಳು = (Uint32)(SDL_TellIO(dst) - fp_ಸ್ಥಾನಾಂತರ);
        ಆದರೆ (SDL_SeekIO(dst, fp_ಸ್ಥಾನಾಂತರ + 10, SDL_IO_SEEK_ಗಣ) < 0) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (!SDL_WriteU32LE(dst, bf_Off_ಬಿಟ್ಟುಗಳು)) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (SDL_SeekIO(dst, fp_ಸ್ಥಾನಾಂತರ + bf_Off_ಬಿಟ್ಟುಗಳು, SDL_IO_SEEK_ಗಣ) < 0) {
            ಹೋಗು ಮುಗಿದ;
        }

        // Write the bitmap image upside down
        ಬಿಟ್ಟುಗಳು = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        ಆಗ (ಬಿಟ್ಟುಗಳು > (Uint8 *)state->intermediate_surface->pixels) {
            ಬಿಟ್ಟುಗಳು -= state->intermediate_surface->pitch;
            ಆದರೆ (SDL_WriteIO(dst, ಬಿಟ್ಟುಗಳು, bw) != bw) {
                ಹೋಗು ಮುಗಿದ;
            }
            ಆದರೆ (pad) {
                ಸ್ಥಿರಾಂಕ Uint8 padbyte = 0;
                ಗಾಗಿ (i = 0; i < pad; ++i) {
                    ಆದರೆ (!SDL_WriteU8(dst, padbyte)) {
                        ಹೋಗು ಮುಗಿದ;
                    }
                }
            }
        }

        // Write the BMP file size
        new_ಸ್ಥಾನಾಂತರ = SDL_TellIO(dst);
        ಆದರೆ (new_ಸ್ಥಾನಾಂತರ < 0) {
            ಹೋಗು ಮುಗಿದ;
        }
        bf_ಗಾತ್ರ = (Uint32)(new_ಸ್ಥಾನಾಂತರ - fp_ಸ್ಥಾನಾಂತರ);
        ಆದರೆ (SDL_SeekIO(dst, fp_ಸ್ಥಾನಾಂತರ + 2, SDL_IO_SEEK_ಗಣ) < 0) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (!SDL_WriteU32LE(dst, bf_ಗಾತ್ರ)) {
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (SDL_SeekIO(dst, fp_ಸ್ಥಾನಾಂತರ + bf_ಗಾತ್ರ, SDL_IO_SEEK_ಗಣ) < 0) {
            ಹೋಗು ಮುಗಿದ;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

ಮುಗಿದ:
    ಆದರೆ (closeio && dst) {
        ಆದರೆ (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    ಆದರೆ (was_error) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool ಫಲಿತಾಂಶ = true;
    BMPSaveState state;
    ಆದರೆ (!InitBMPSaveState(&state, surface)) {
        ಹಿಂತಿರುಗಿ false;
    }
    CHECK_PARAM(!dst) {
        ಫಲಿತಾಂಶ = SDL_InvalidParamError("dst");
        ಹೋಗು ಮುಗಿದ;
    }
    ಫಲಿತಾಂಶ = SDL_Save_BMP_IO_ಆಂತರಿಕ(&state, dst, closeio);
ಮುಗಿದ:
    FreeBMPSaveState(&state);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_SaveBMP(SDL_Surface *surface, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file)
{
    BMPSaveState state;
    ಆದರೆ (!InitBMPSaveState(&state, surface)) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_IOStream *ಹರಿವು = SDL_IOFromFile(file, "wb");
    ಆದರೆ (!ಹರಿವು) {
        ಹಿಂತಿರುಗಿ false;
    }

    bool ಫಲಿತಾಂಶ = SDL_Save_BMP_IO_ಆಂತರಿಕ(&state, ಹರಿವು, true);
    FreeBMPSaveState(&state);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

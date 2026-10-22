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

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAVE_32_ਦੋਆਧਾਰੀ_ਅੰਕ_BMP

// Compression encodings for BMP files
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ BI_RGB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BI_RGB       0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BI_RLE8      1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BI_RLE4      2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BI_BITFIELDS 3
#ਜੇ_ਅੰਤ

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LCS_WINDOWS_COLOR_SPACE 0x57696E20
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ LCS_sRGB
// 0x73524742 == "sRGB"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LCS_sRGB 0x73524742
#ਜੇ_ਅੰਤ

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ LCS_GM_GRAPHICS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LCS_GM_GRAPHICS 0x00000002
#ਜੇ_ਅੰਤ

ਸਥਿਰ bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, ਪੂਰਨ isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    ਪੂਰਨ pitch = surface->pitch;
    ਪੂਰਨ ਉਚਾਈ = surface->h;
    Uint8 *ਸ਼ੁਰੂ = (Uint8 *)surface->pixels;
    Uint8 *ਸਿਰਾ = ਸ਼ੁਰੂ + (ਉਚਾਈ * pitch);
    Uint8 *ਬਿੱਟ = ਸਿਰਾ - pitch, *spot;
    ਪੂਰਨ ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ਅਚਲ ਪੂਰਨ pixels_ਪ੍ਰਤੀ_byte = (isRle8 ? 1 : 2);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COPY_PIXEL(x)                \
    spot = &ਬਿੱਟ[ofs++];             \
    ਜੇ (spot >= ਸ਼ੁਰੂ && spot < ਸਿਰਾ) \
        *spot = (x)

    ਲਈ (;;) {
        ਜੇ (!SDL_ReadU8(src, &ch)) {
            ਵਾਪਸ false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        ਜੇ (ch) {
            Uint8 pixelvalue;
            ਜੇ (!SDL_ReadU8(src, &pixelvalue)) {
                ਵਾਪਸ false;
            }
            ਪੂਰਨ ich = (ਪੂਰਨ) ch;
            ਕਰੋ {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_ਪ੍ਰਤੀ_byte;
            } ਜਦੋਂ (ich > 0);
        } ਨਹੀਂਤਾਂ {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            ਜੇ (!SDL_ReadU8(src, &ch)) {
                ਵਾਪਸ false;
            }
            ਚੋਣ (ch) {
            ਹਾਲਤ 0: // end of line
                ofs = 0;
                ਬਿੱਟ -= pitch; // go to previous
                ਰੋਕੋ;
            ਹਾਲਤ 1:               // end of bitmap
                ਵਾਪਸ true; // success!
            ਹਾਲਤ 2:               // delta
                ਜੇ (!SDL_ReadU8(src, &ch)) {
                    ਵਾਪਸ false;
                }
                ofs += ch / pixels_ਪ੍ਰਤੀ_byte;
                ਜੇ (ch & pixels_ਪ੍ਰਤੀ_byte) {
                    ofs++;
                }
                ਜੇ (!SDL_ReadU8(src, &ch)) {
                    ਵਾਪਸ false;
                }
                ਬਿੱਟ -= (ch * pitch);
                ਰੋਕੋ;
            ਮੂਲ: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                ਜੇ (pixels_ਪ੍ਰਤੀ_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } ਨਹੀਂਤਾਂ {
                    needsPad = (((ch + (pixels_ਪ੍ਰਤੀ_byte-1)) / pixels_ਪ੍ਰਤੀ_byte) & (pixels_ਪ੍ਰਤੀ_byte-1)) != 0;
                }

                ਪੂਰਨ ich = (ਪੂਰਨ) ch;
                ਕਰੋ {
                    Uint8 pixelvalue;
                    ਜੇ (!SDL_ReadU8(src, &pixelvalue)) {
                        ਵਾਪਸ false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_ਪ੍ਰਤੀ_byte;
                } ਜਦੋਂ (ich > 0);

                // pad at even boundary
                ਜੇ (needsPad && !SDL_ReadU8(src, &ch)) {
                    ਵਾਪਸ false;
                }
                ਰੋਕੋ;
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#ਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
    ਪੂਰਨ alpha_Channel_ਵਿੱਥ = 0;
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ alpha_Channel_ਵਿੱਥ = 3;
#ਜੇ_ਅੰਤ
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_ਵਿੱਥ;
    Uint8 *ਸਿਰਾ = alpha + surface->h * surface->pitch;

    ਜਦੋਂ (alpha < ਸਿਰਾ) {
        ਜੇ (*alpha != 0) {
            hasAlpha = true;
            ਰੋਕੋ;
        }
        alpha += 4;
    }

    ਜੇ (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_ਵਿੱਥ;
        ਜਦੋਂ (alpha < ਸਿਰਾ) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 ਸ਼ੁਰੂ;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    ਸ਼ੁਰੂ = SDL_TellIO(src);
    ਜੇ (ਸ਼ੁਰੂ >= 0) {
        ਜੇ (SDL_ReadIO(src, magic, ਆਕਾਰ(magic)) == ਆਕਾਰ(magic)) {
            ਜੇ (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, ਸ਼ੁਰੂ, SDL_IO_SEEK_ਸੈੱਟ);
    }

    ਵਾਪਸ is_BMP;
}

SDL_Surface *SDL_ਲੱਦੋ_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_ਵਿੱਥ = 0;
    ਪੂਰਨ i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *ਬਿੱਟ;
    Uint8 *ਸਿਖਰ, *ਸਿਰਾ;
    bool ਸਿਖਰ_ਥੱਲੇ;
    bool haveRGBMasks = false;
    bool have_Alpha_ਨਕਾਬ = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bf_Off_ਬਿੱਟ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_ਮਾਪ;
    Sint32 bi_ਚੌੜਾਈ = 0;
    Sint32 bi_ਉਚਾਈ = 0;
    // Uint16 biPlanes;
    Uint16 bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_ਵਰਤਿਆ = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = ਨਿਰਾ;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ਜਾਓ ਪੂਰਾ;
    }

    // Read in the BMP file header
    fp_ਵਿੱਥ = SDL_TellIO(src);
    ਜੇ (fp_ਵਿੱਥ < 0) {
        ਜਾਓ ਪੂਰਾ;
    }
    SDL_ClearError();
    ਜੇ (!SDL_IsBMP(src)) {
        SDL_ਸੈੱਟ_Error("File is not a Windows BMP file");
        ਜਾਓ ਪੂਰਾ;
    }
    ਜੇ (!SDL_ReadU16LE(src, ਨਿਰਾ /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, ਨਿਰਾ /* bfSize */) ||
        !SDL_ReadU16LE(src, ਨਿਰਾ /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, ਨਿਰਾ /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_ਬਿੱਟ)) {
        ਜਾਓ ਪੂਰਾ;
    }

    // Read the Win32 BITMAPINFOHEADER
    ਜੇ (!SDL_ReadU32LE(src, &bi_ਮਾਪ)) {
        ਜਾਓ ਪੂਰਾ;
    }
    ਜੇ (bi_ਮਾਪ == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        ਜੇ (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, ਨਿਰਾ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ)) {
            ਜਾਓ ਪੂਰਾ;
        }
        bi_ਚੌੜਾਈ = biWidth16;
        bi_ਉਚਾਈ = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_ਵਰਤਿਆ = 0;
        // biClrImportant = 0;
    } ਨਹੀਂਤਾਂ ਜੇ (bi_ਮਾਪ >= 40) { // some version of BITMAPINFOHEADER
        Uint32 ਸਿਰਲੇਖ_ਮਾਪ;
        ਜੇ (!SDL_ReadS32LE(src, &bi_ਚੌੜਾਈ) ||
            !SDL_ReadS32LE(src, &bi_ਉਚਾਈ) ||
            !SDL_ReadU16LE(src, ਨਿਰਾ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, ਨਿਰਾ /* biSizeImage */) ||
            !SDL_ReadU32LE(src, ਨਿਰਾ /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, ਨਿਰਾ /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_ਵਰਤਿਆ) ||
            !SDL_ReadU32LE(src, ਨਿਰਾ /* biClrImportant */)) {
            ਜਾਓ ਪੂਰਾ;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        ਜੇ (bi_ਮਾਪ != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            ਜੇ (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                ਜੇ (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    ਜਾਓ ਪੂਰਾ;
                }

                // ...v3 adds an alpha mask.
                ਜੇ (bi_ਮਾਪ >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_ਨਕਾਬ = true;
                    ਜੇ (!SDL_ReadU32LE(src, &Amask)) {
                        ਜਾਓ ਪੂਰਾ;
                    }
                }
            } ਨਹੀਂਤਾਂ {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                ਜੇ (bi_ਮਾਪ >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    ਜੇ (!SDL_ReadU32LE(src, ਨਿਰਾ /* Rmask */) ||
                        !SDL_ReadU32LE(src, ਨਿਰਾ /* Gmask */) ||
                        !SDL_ReadU32LE(src, ਨਿਰਾ /* Bmask */)) {
                        ਜਾਓ ਪੂਰਾ;
                    }
                }
                ਜੇ (bi_ਮਾਪ >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    ਜੇ (!SDL_ReadU32LE(src, ਨਿਰਾ /* Amask */)) {
                        ਜਾਓ ਪੂਰਾ;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        ਸਿਰਲੇਖ_ਮਾਪ = (Uint32)(SDL_TellIO(src) - (fp_ਵਿੱਥ + 14));
        ਜੇ (bi_ਮਾਪ > ਸਿਰਲੇਖ_ਮਾਪ) {
            ਜੇ (SDL_SeekIO(src, (bi_ਮਾਪ - ਸਿਰਲੇਖ_ਮਾਪ), SDL_IO_SEEK_CUR) < 0) {
                ਜਾਓ ਪੂਰਾ;
            }
        }
    }
    ਜੇ (bi_ਚੌੜਾਈ <= 0 || bi_ਉਚਾਈ == 0) {
        SDL_ਸੈੱਟ_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_ਚੌੜਾਈ, bi_ਉਚਾਈ);
        ਜਾਓ ਪੂਰਾ;
    }
    ਜੇ (bi_ਉਚਾਈ < 0) {
        ਸਿਖਰ_ਥੱਲੇ = true;
        bi_ਉਚਾਈ = -bi_ਉਚਾਈ;
    } ਨਹੀਂਤਾਂ {
        ਸਿਖਰ_ਥੱਲੇ = false;
    }

    // Check for read error
    ਜੇ (SDL_strcmp(SDL_GetError(), "") != 0) {
        ਜਾਓ ਪੂਰਾ;
    }

    // Reject invalid bit depths
    ਚੋਣ (bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ) {
    ਹਾਲਤ 0:
    ਹਾਲਤ 3:
    ਹਾਲਤ 5:
    ਹਾਲਤ 6:
    ਹਾਲਤ 7:
        SDL_ਸੈੱਟ_Error("%u bpp BMP images are not supported", bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ);
        ਜਾਓ ਪੂਰਾ;
    ਮੂਲ:
        ਰੋਕੋ;
    }

    // RLE4 and RLE8 BMP compression is supported
    ਚੋਣ (biCompression) {
    ਹਾਲਤ BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!have_Alpha_ਨਕਾਬ);
        // Default values for the BMP format
        ਚੋਣ (bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ) {
        ਹਾਲਤ 15:
        ਹਾਲਤ 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            ਰੋਕੋ;
        ਹਾਲਤ 24:
#ਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#ਨਹੀਂਤਾਂ
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#ਜੇ_ਅੰਤ
            ਰੋਕੋ;
        ਹਾਲਤ 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
        ਰੋਕੋ;

    ਹਾਲਤ BI_BITFIELDS:
        ਰੋਕੋ; // we handled this in the info header.

    ਮੂਲ:
        ਰੋਕੋ;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_ਚੌੜਾਈ, bi_ਉਚਾਈ, format);

        ਜੇ (!surface) {
            ਜਾਓ ਪੂਰਾ;
        }
    }

    // Load the palette, if any
    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ਜੇ (!palette) {
            ਜਾਓ ਪੂਰਾ;
        }

        ਜੇ (SDL_SeekIO(src, fp_ਵਿੱਥ + 14 + bi_ਮਾਪ, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
            SDL_ਸੈੱਟ_Error("Error seeking in datastream");
            ਜਾਓ ਪੂਰਾ;
        }

        ਜੇ (bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ >= 32) { // we shift biClrUsed by this value later.
            SDL_ਸੈੱਟ_Error("Unsupported or incorrect biBitCount field");
            ਜਾਓ ਪੂਰਾ;
        }

        ਜੇ (bi_Clr_ਵਰਤਿਆ == 0) {
            bi_Clr_ਵਰਤਿਆ = 1 << bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ;
        }

        ਜੇ (bi_Clr_ਵਰਤਿਆ > (Uint32)palette->ncolors) {
            bi_Clr_ਵਰਤਿਆ = 1 << bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ; // try forcing it?
            ਜੇ (bi_Clr_ਵਰਤਿਆ > (Uint32)palette->ncolors) {
                SDL_ਸੈੱਟ_Error("Unsupported or incorrect biClrUsed field");
                ਜਾਓ ਪੂਰਾ;
            }
        }
        palette->ncolors = bi_Clr_ਵਰਤਿਆ;

        ਜੇ (bi_ਮਾਪ == 12) {
            ਲਈ (i = 0; i < palette->ncolors; ++i) {
                ਜੇ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    ਜਾਓ ਪੂਰਾ;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } ਨਹੀਂਤਾਂ {
            ਲਈ (i = 0; i < palette->ncolors; ++i) {
                ਜੇ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    ਜਾਓ ਪੂਰਾ;
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
    ਜੇ (SDL_SeekIO(src, fp_ਵਿੱਥ + bf_Off_ਬਿੱਟ, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
        SDL_ਸੈੱਟ_Error("Error seeking in datastream");
        ਜਾਓ ਪੂਰਾ;
    }
    ਜੇ ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        ਜੇ (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_ਸੈੱਟ_Error("Error reading from datastream");
            ਜਾਓ ਪੂਰਾ;
        }

        // Success!
        was_error = false;
        ਜਾਓ ਪੂਰਾ;
    }
    ਸਿਖਰ = (Uint8 *)surface->pixels;
    ਸਿਰਾ = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    ਜੇ (ਸਿਖਰ_ਥੱਲੇ) {
        ਬਿੱਟ = ਸਿਖਰ;
    } ਨਹੀਂਤਾਂ {
        ਬਿੱਟ = ਸਿਰਾ - surface->pitch;
    }
    ਜਦੋਂ (ਬਿੱਟ >= ਸਿਖਰ && ਬਿੱਟ < ਸਿਰਾ) {
        ਜੇ (SDL_ReadIO(src, ਬਿੱਟ, surface->pitch) != (size_t)surface->pitch) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ == 8 && surface->palette && bi_Clr_ਵਰਤਿਆ < (1u << bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ)) {
            ਲਈ (i = 0; i < surface->w; ++i) {
                ਜੇ (ਬਿੱਟ[i] >= bi_Clr_ਵਰਤਿਆ) {
                    SDL_ਸੈੱਟ_Error("A BMP image contains a pixel with a color out of the palette");
                    ਜਾਓ ਪੂਰਾ;
                }
            }
        }
#ਜੇ SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        ਚੋਣ (bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ) {
        ਹਾਲਤ 15:
        ਹਾਲਤ 16:
        {
            Uint16 *pix = (Uint16 *)ਬਿੱਟ;
            ਲਈ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            ਰੋਕੋ;
        }

        ਹਾਲਤ 32:
        {
            Uint32 *pix = (Uint32 *)ਬਿੱਟ;
            ਲਈ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            ਰੋਕੋ;
        }
        }
#ਜੇ_ਅੰਤ

        // Skip padding bytes, ugh
        ਜੇ (pad) {
            Uint8 padbyte;
            ਲਈ (i = 0; i < pad; ++i) {
                ਜੇ (!SDL_ReadU8(src, &padbyte)) {
                    ਜਾਓ ਪੂਰਾ;
                }
            }
        }
        ਜੇ (ਸਿਖਰ_ਥੱਲੇ) {
            ਬਿੱਟ += surface->pitch;
        } ਨਹੀਂਤਾਂ {
            ਬਿੱਟ -= surface->pitch;
        }
    }
    ਜੇ (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

ਪੂਰਾ:
    ਜੇ (was_error) {
        ਜੇ (src) {
            SDL_SeekIO(src, fp_ਵਿੱਥ, SDL_IO_SEEK_ਸੈੱਟ);
        }
        SDL_DestroySurface(surface);
        surface = ਨਿਰਾ;
    }
    ਜੇ (closeio && src) {
        SDL_CloseIO(src);
    }
    ਵਾਪਸ surface;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ਸਥਿਰ ਖਾਲੀ FreeBMPSaveState(BMPSaveState *state)
{
    ਜੇ (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ਸਥਿਰ bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = ਨਿਰਾ;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SAVE_32_ਦੋਆਧਾਰੀ_ਅੰਕ_BMP
    // We can save alpha information in a 32-bit BMP
    ਜੇ (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#ਜੇ_ਅੰਤ // SAVE_32BIT_BMP

    ਜੇ (surface->palette && !state->save32bit) {
        ਜੇ (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } ਨਹੀਂਤਾਂ {
            SDL_ਸੈੱਟ_Error("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            ਜਾਓ error;
        }
    } ਨਹੀਂਤਾਂ ਜੇ ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } ਨਹੀਂਤਾਂ {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        ਜੇ (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } ਨਹੀਂਤਾਂ {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        ਜੇ (!state->intermediate_surface) {
            SDL_ਸੈੱਟ_Error("Couldn't convert image to %d bpp",
                         (ਪੂਰਨ)SDL_BITSPERPIXEL(pixel_format));
            ਜਾਓ error;
        }
    }

    ਜੇ (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    ਵਾਪਸ true;
error:
    FreeBMPSaveState(state);
    ਵਾਪਸ false;
}

SDL_Surface *SDL_ਲੱਦੋ_BMP(ਅਚਲ ਅੱਖਰ *file)
{
    SDL_IOStream *ਧਾਰਾ = SDL_IOFromFile(file, "rb");
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ SDL_ਲੱਦੋ_BMP_IO(ਧਾਰਾ, true);
}
ਸਥਿਰ bool SDL_Save_BMP_IO_ਅੰਦਰੂਨੀ(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_ਵਿੱਥ, new_ਵਿੱਥ;
    ਪੂਰਨ i, pad;
    Uint8 *ਬਿੱਟ;

    // The Win32 BMP file header (14 bytes)
    ਅੱਖਰ magic[2] = { 'B', 'M' };
    Uint32 bf_ਮਾਪ;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_ਬਿੱਟ;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_ਮਾਪ;
    Sint32 bi_ਚੌੜਾਈ;
    Sint32 bi_ਉਚਾਈ;
    Uint16 biPlanes;
    Uint16 bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ;
    Uint32 biCompression;
    Uint32 bi_ਮਾਪ_Image;
    Sint32 bi_XPels_ਪ੍ਰਤੀ_Meter;
    Sint32 bi_YPels_ਪ੍ਰਤੀ_Meter;
    Uint32 bi_Clr_ਵਰਤਿਆ;
    Uint32 biClrImportant;

    // The additional header members from the Win32 BITMAPV4HEADER struct (108 bytes in total)
    Uint32 b_V4_Red_ਨਕਾਬ = 0;
    Uint32 b_V4_Green_ਨਕਾਬ = 0;
    Uint32 b_V4_Blue_ਨਕਾਬ = 0;
    Uint32 b_V4_Alpha_ਨਕਾਬ = 0;
    Uint32 bV4CSType = 0;
    Sint32 bV4Endpoints[3 * 3] = { 0 };
    Uint32 bV4GammaRed = 0;
    Uint32 bV4GammaGreen = 0;
    Uint32 bV4GammaBlue = 0;

    // The additional header members from the Win32 BITMAPV5HEADER struct (124 bytes in total)
    Uint32 bV5Intent = 0;
    Uint32 b_V5_Profile_ਅੰਕੜੇ = 0;
    Uint32 b_V5_Profile_ਮਾਪ = 0;
    Uint32 bV5Reserved = 0;

    ਜੇ (SDL_ਤਾਲਾ_Surface(state->intermediate_surface)) {
        ਅਚਲ size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

        // Set the BMP file header values
        bf_ਮਾਪ = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_ਬਿੱਟ = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_ਵਿੱਥ = SDL_TellIO(dst);
        ਜੇ (fp_ਵਿੱਥ < 0) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_ਮਾਪ) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_ਬਿੱਟ)) {
            ਜਾਓ ਪੂਰਾ;
        }

        // Set the BMP info values
        bi_ਮਾਪ = 40;
        bi_ਚੌੜਾਈ = state->intermediate_surface->w;
        bi_ਉਚਾਈ = state->intermediate_surface->h;
        biPlanes = 1;
        bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ = state->intermediate_surface->fmt->ਬਿੱਟ_ਪ੍ਰਤੀ_pixel;
        biCompression = BI_RGB;
        bi_ਮਾਪ_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_ਪ੍ਰਤੀ_Meter = 0;
        bi_YPels_ਪ੍ਰਤੀ_Meter = 0;
        ਜੇ (state->intermediate_surface->palette) {
            bi_Clr_ਵਰਤਿਆ = state->intermediate_surface->palette->ncolors;
        } ਨਹੀਂਤਾਂ {
            bi_Clr_ਵਰਤਿਆ = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        ਜੇ (state->save32bit && !state->saveLegacyBMP) {
            bi_ਮਾਪ = 124;
            // Version 4 values
            biCompression = BI_BITFIELDS;
            // The BMP format is always little endian, these masks stay the same
            b_V4_Red_ਨਕਾਬ = 0x00ff0000;
            b_V4_Green_ਨਕਾਬ = 0x0000ff00;
            b_V4_Blue_ਨਕਾਬ = 0x000000ff;
            b_V4_Alpha_ਨਕਾਬ = 0xff000000;
            bV4CSType = LCS_sRGB;
            bV4GammaRed = 0;
            bV4GammaGreen = 0;
            bV4GammaBlue = 0;
            // Version 5 values
            bV5Intent = LCS_GM_GRAPHICS;
            b_V5_Profile_ਅੰਕੜੇ = 0;
            b_V5_Profile_ਮਾਪ = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        ਜੇ (!SDL_WriteU32LE(dst, bi_ਮਾਪ) ||
            !SDL_WriteS32LE(dst, bi_ਚੌੜਾਈ) ||
            !SDL_WriteS32LE(dst, bi_ਉਚਾਈ) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_ਮਾਪ_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_ਪ੍ਰਤੀ_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_ਪ੍ਰਤੀ_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_ਵਰਤਿਆ) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            ਜਾਓ ਪੂਰਾ;
        }

        // Write the BMP info values
        ਜੇ (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            ਜੇ (!SDL_WriteU32LE(dst, b_V4_Red_ਨਕਾਬ) ||
                !SDL_WriteU32LE(dst, b_V4_Green_ਨਕਾਬ) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_ਨਕਾਬ) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_ਨਕਾਬ) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                ਜਾਓ ਪੂਰਾ;
            }
            ਲਈ (i = 0; i < 3 * 3; i++) {
                ਜੇ (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    ਜਾਓ ਪੂਰਾ;
                }
            }
            ਜੇ (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                ਜਾਓ ਪੂਰਾ;
            }
            // Version 5 values
            ਜੇ (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_ਅੰਕੜੇ) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_ਮਾਪ) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                ਜਾਓ ਪੂਰਾ;
            }
        }

        // Write the palette (in BGR color order)
        ਜੇ (state->intermediate_surface->palette) {
            SDL_Color *colors;
            ਪੂਰਨ ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            ਲਈ (i = 0; i < ncolors; ++i) {
                ਜੇ (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    ਜਾਓ ਪੂਰਾ;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_ਬਿੱਟ = (Uint32)(SDL_TellIO(dst) - fp_ਵਿੱਥ);
        ਜੇ (SDL_SeekIO(dst, fp_ਵਿੱਥ + 10, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (!SDL_WriteU32LE(dst, bf_Off_ਬਿੱਟ)) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (SDL_SeekIO(dst, fp_ਵਿੱਥ + bf_Off_ਬਿੱਟ, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
            ਜਾਓ ਪੂਰਾ;
        }

        // Write the bitmap image upside down
        ਬਿੱਟ = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        ਜਦੋਂ (ਬਿੱਟ > (Uint8 *)state->intermediate_surface->pixels) {
            ਬਿੱਟ -= state->intermediate_surface->pitch;
            ਜੇ (SDL_WriteIO(dst, ਬਿੱਟ, bw) != bw) {
                ਜਾਓ ਪੂਰਾ;
            }
            ਜੇ (pad) {
                ਅਚਲ Uint8 padbyte = 0;
                ਲਈ (i = 0; i < pad; ++i) {
                    ਜੇ (!SDL_WriteU8(dst, padbyte)) {
                        ਜਾਓ ਪੂਰਾ;
                    }
                }
            }
        }

        // Write the BMP file size
        new_ਵਿੱਥ = SDL_TellIO(dst);
        ਜੇ (new_ਵਿੱਥ < 0) {
            ਜਾਓ ਪੂਰਾ;
        }
        bf_ਮਾਪ = (Uint32)(new_ਵਿੱਥ - fp_ਵਿੱਥ);
        ਜੇ (SDL_SeekIO(dst, fp_ਵਿੱਥ + 2, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (!SDL_WriteU32LE(dst, bf_ਮਾਪ)) {
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (SDL_SeekIO(dst, fp_ਵਿੱਥ + bf_ਮਾਪ, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
            ਜਾਓ ਪੂਰਾ;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

ਪੂਰਾ:
    ਜੇ (closeio && dst) {
        ਜੇ (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    ਜੇ (was_error) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool ਨਤੀਜਾ = true;
    BMPSaveState state;
    ਜੇ (!InitBMPSaveState(&state, surface)) {
        ਵਾਪਸ false;
    }
    CHECK_PARAM(!dst) {
        ਨਤੀਜਾ = SDL_InvalidParamError("dst");
        ਜਾਓ ਪੂਰਾ;
    }
    ਨਤੀਜਾ = SDL_Save_BMP_IO_ਅੰਦਰੂਨੀ(&state, dst, closeio);
ਪੂਰਾ:
    FreeBMPSaveState(&state);
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_SaveBMP(SDL_Surface *surface, ਅਚਲ ਅੱਖਰ *file)
{
    BMPSaveState state;
    ਜੇ (!InitBMPSaveState(&state, surface)) {
        ਵਾਪਸ false;
    }

    SDL_IOStream *ਧਾਰਾ = SDL_IOFromFile(file, "wb");
    ਜੇ (!ਧਾਰਾ) {
        ਵਾਪਸ false;
    }

    bool ਨਤੀਜਾ = SDL_Save_BMP_IO_ਅੰਦਰੂਨੀ(&state, ਧਾਰਾ, true);
    FreeBMPSaveState(&state);
    ਵਾਪਸ ਨਤੀਜਾ;
}

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

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#include "SDL_pixels_c.h"
#include "SDL_surface_c.h"

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

static bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, puur_naa_nka isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    puur_naa_nka pitch = surface->pitch;
    puur_naa_nka height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    puur_naa_nka ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    const puur_naa_nka pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    ꦪꦼꦤ꧀ (spot >= start && spot < end) \
        *spot = (x)

    ꦏꦁꦒꦺꦴ (;;) {
        ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &ch)) {
            ꦮꦭꦶ false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        ꦪꦼꦤ꧀ (ch) {
            Uint8 pixelvalue;
            ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &pixelvalue)) {
                ꦮꦭꦶ false;
            }
            puur_naa_nka ich = (puur_naa_nka) ch;
            do {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } ꦱꦼꦢꦼꦭ (ich > 0);
        } ꦭꦶꦪ {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &ch)) {
                ꦮꦭꦶ false;
            }
            switch (ch) {
            pak_sa 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                bha_nga;
            pak_sa 1:               // end of bitmap
                ꦮꦭꦶ true; // success!
            pak_sa 2:               // delta
                ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &ch)) {
                    ꦮꦭꦶ false;
                }
                ofs += ch / pixels_per_byte;
                ꦪꦼꦤ꧀ (ch & pixels_per_byte) {
                    ofs++;
                }
                ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &ch)) {
                    ꦮꦭꦶ false;
                }
                bits -= (ch * pitch);
                bha_nga;
            default: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                ꦪꦼꦤ꧀ (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } ꦭꦶꦪ {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                puur_naa_nka ich = (puur_naa_nka) ch;
                do {
                    Uint8 pixelvalue;
                    ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &pixelvalue)) {
                        ꦮꦭꦶ false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } ꦱꦼꦢꦼꦭ (ich > 0);

                // pad at even boundary
                ꦪꦼꦤ꧀ (needsPad && !SDL_ReadU8(src, &ch)) {
                    ꦮꦭꦶ false;
                }
                bha_nga;
            }
        }
    }
}

static void CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#ꦪꦼꦤ꧀ SDL_BYTEORDER == SDL_BIG_ENDIAN
    puur_naa_nka alphaChannelOffset = 0;
#ꦭꦶꦪ
    puur_naa_nka alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    ꦱꦼꦢꦼꦭ (alpha < end) {
        ꦪꦼꦤ꧀ (*alpha != 0) {
            hasAlpha = true;
            bha_nga;
        }
        alpha += 4;
    }

    ꦪꦼꦤ꧀ (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        ꦱꦼꦢꦼꦭ (alpha < end) {
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
    ꦪꦼꦤ꧀ (start >= 0) {
        ꦪꦼꦤ꧀ (SDL_ReadIO(src, magic, parimaa_na(magic)) == parimaa_na(magic)) {
            ꦪꦼꦤ꧀ (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    ꦮꦭꦶ is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    puur_naa_nka i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *top, *end;
    bool topDown;
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
    Uint16 biBitCount = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = NULL;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        goto done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    ꦪꦼꦤ꧀ (fp_offset < 0) {
        goto done;
    }
    SDL_ClearError();
    ꦪꦼꦤ꧀ (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        goto done;
    }
    ꦪꦼꦤ꧀ (!SDL_ReadU16LE(src, NULL /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, NULL /* bfSize */) ||
        !SDL_ReadU16LE(src, NULL /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, NULL /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        goto done;
    }

    // Read the Win32 BITMAPINFOHEADER
    ꦪꦼꦤ꧀ (!SDL_ReadU32LE(src, &biSize)) {
        goto done;
    }
    ꦪꦼꦤ꧀ (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        ꦪꦼꦤ꧀ (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, NULL /* biPlanes */) ||
            !SDL_ReadU16LE(src, &biBitCount)) {
            goto done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } ꦭꦶꦪ ꦪꦼꦤ꧀ (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        ꦪꦼꦤ꧀ (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, NULL /* biPlanes */) ||
            !SDL_ReadU16LE(src, &biBitCount) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, NULL /* biSizeImage */) ||
            !SDL_ReadU32LE(src, NULL /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, NULL /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, NULL /* biClrImportant */)) {
            goto done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        ꦪꦼꦤ꧀ (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            ꦪꦼꦤ꧀ (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                ꦪꦼꦤ꧀ (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    goto done;
                }

                // ...v3 adds an alpha mask.
                ꦪꦼꦤ꧀ (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    ꦪꦼꦤ꧀ (!SDL_ReadU32LE(src, &Amask)) {
                        goto done;
                    }
                }
            } ꦭꦶꦪ {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                ꦪꦼꦤ꧀ (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    ꦪꦼꦤ꧀ (!SDL_ReadU32LE(src, NULL /* Rmask */) ||
                        !SDL_ReadU32LE(src, NULL /* Gmask */) ||
                        !SDL_ReadU32LE(src, NULL /* Bmask */)) {
                        goto done;
                    }
                }
                ꦪꦼꦤ꧀ (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    ꦪꦼꦤ꧀ (!SDL_ReadU32LE(src, NULL /* Amask */)) {
                        goto done;
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
        ꦪꦼꦤ꧀ (biSize > headerSize) {
            ꦪꦼꦤ꧀ (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                goto done;
            }
        }
    }
    ꦪꦼꦤ꧀ (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        goto done;
    }
    ꦪꦼꦤ꧀ (biHeight < 0) {
        topDown = true;
        biHeight = -biHeight;
    } ꦭꦶꦪ {
        topDown = false;
    }

    // Check for read error
    ꦪꦼꦤ꧀ (SDL_strcmp(SDL_GetError(), "") != 0) {
        goto done;
    }

    // Reject invalid bit depths
    switch (biBitCount) {
    pak_sa 0:
    pak_sa 3:
    pak_sa 5:
    pak_sa 6:
    pak_sa 7:
        SDL_SetError("%u bpp BMP images are not supported", biBitCount);
        goto done;
    default:
        bha_nga;
    }

    // RLE4 and RLE8 BMP compression is supported
    switch (biCompression) {
    pak_sa BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        switch (biBitCount) {
        pak_sa 15:
        pak_sa 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            bha_nga;
        pak_sa 24:
#ꦪꦼꦤ꧀ SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#ꦭꦶꦪ
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            bha_nga;
        pak_sa 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            bha_nga;
        default:
            bha_nga;
        }
        bha_nga;

    pak_sa BI_BITFIELDS:
        bha_nga; // we handled this in the info header.

    default:
        bha_nga;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(biBitCount, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        ꦪꦼꦤ꧀ (!surface) {
            goto done;
        }
    }

    // Load the palette, if any
    ꦪꦼꦤ꧀ (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ꦪꦼꦤ꧀ (!palette) {
            goto done;
        }

        ꦪꦼꦤ꧀ (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            goto done;
        }

        ꦪꦼꦤ꧀ (biBitCount >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            goto done;
        }

        ꦪꦼꦤ꧀ (biClrUsed == 0) {
            biClrUsed = 1 << biBitCount;
        }

        ꦪꦼꦤ꧀ (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << biBitCount; // try forcing it?
            ꦪꦼꦤ꧀ (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                goto done;
            }
        }
        palette->ncolors = biClrUsed;

        ꦪꦼꦤ꧀ (biSize == 12) {
            ꦏꦁꦒꦺꦴ (i = 0; i < palette->ncolors; ++i) {
                ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    goto done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } ꦭꦶꦪ {
            ꦏꦁꦒꦺꦴ (i = 0; i < palette->ncolors; ++i) {
                ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    goto done;
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
    ꦪꦼꦤ꧀ (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        goto done;
    }
    ꦪꦼꦤ꧀ ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        ꦪꦼꦤ꧀ (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            goto done;
        }

        // Success!
        was_error = false;
        goto done;
    }
    top = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    ꦪꦼꦤ꧀ (topDown) {
        bits = top;
    } ꦭꦶꦪ {
        bits = end - surface->pitch;
    }
    ꦱꦼꦢꦼꦭ (bits >= top && bits < end) {
        ꦪꦼꦤ꧀ (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            goto done;
        }
        ꦪꦼꦤ꧀ (biBitCount == 8 && surface->palette && biClrUsed < (1u << biBitCount)) {
            ꦏꦁꦒꦺꦴ (i = 0; i < surface->w; ++i) {
                ꦪꦼꦤ꧀ (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    goto done;
                }
            }
        }
#ꦪꦼꦤ꧀ SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        switch (biBitCount) {
        pak_sa 15:
        pak_sa 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            ꦏꦁꦒꦺꦴ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            bha_nga;
        }

        pak_sa 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            ꦏꦁꦒꦺꦴ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            bha_nga;
        }
        }
#endif

        // Skip padding bytes, ugh
        ꦪꦼꦤ꧀ (pad) {
            Uint8 padbyte;
            ꦏꦁꦒꦺꦴ (i = 0; i < pad; ++i) {
                ꦪꦼꦤ꧀ (!SDL_ReadU8(src, &padbyte)) {
                    goto done;
                }
            }
        }
        ꦪꦼꦤ꧀ (topDown) {
            bits += surface->pitch;
        } ꦭꦶꦪ {
            bits -= surface->pitch;
        }
    }
    ꦪꦼꦤ꧀ (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    ꦪꦼꦤ꧀ (was_error) {
        ꦪꦼꦤ꧀ (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = NULL;
    }
    ꦪꦼꦤ꧀ (closeio && src) {
        SDL_CloseIO(src);
    }
    ꦮꦭꦶ surface;
}

typedef sa_nracanaa {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

static void FreeBMPSaveState(BMPSaveState *state)
{
    ꦪꦼꦤ꧀ (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

static bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = NULL;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ꦮꦭꦶ SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    ꦪꦼꦤ꧀ (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    ꦪꦼꦤ꧀ (surface->palette && !state->save32bit) {
        ꦪꦼꦤ꧀ (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } ꦭꦶꦪ {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            goto error;
        }
    } ꦭꦶꦪ ꦪꦼꦤ꧀ ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } ꦭꦶꦪ {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        ꦪꦼꦤ꧀ (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } ꦭꦶꦪ {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        ꦪꦼꦤ꧀ (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (puur_naa_nka)SDL_BITSPERPIXEL(pixel_format));
            goto error;
        }
    }

    ꦪꦼꦤ꧀ (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    ꦮꦭꦶ true;
error:
    FreeBMPSaveState(state);
    ꦮꦭꦶ false;
}

SDL_Surface *SDL_LoadBMP(const var_na *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    ꦪꦼꦤ꧀ (!stream) {
        ꦮꦭꦶ NULL;
    }
    ꦮꦭꦶ SDL_LoadBMP_IO(stream, true);
}
static bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    puur_naa_nka i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    var_na magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 biBitCount;
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

    ꦪꦼꦤ꧀ (SDL_LockSurface(state->intermediate_surface)) {
        const size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        ꦪꦼꦤ꧀ (fp_offset < 0) {
            goto done;
        }
        ꦪꦼꦤ꧀ (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            goto done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        biBitCount = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        ꦪꦼꦤ꧀ (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } ꦭꦶꦪ {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        ꦪꦼꦤ꧀ (state->save32bit && !state->saveLegacyBMP) {
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
        ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, biBitCount) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            goto done;
        }

        // Write the BMP info values
        ꦪꦼꦤ꧀ (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                goto done;
            }
            ꦏꦁꦒꦺꦴ (i = 0; i < 3 * 3; i++) {
                ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    goto done;
                }
            }
            ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                goto done;
            }
            // Version 5 values
            ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                goto done;
            }
        }

        // Write the palette (in BGR color order)
        ꦪꦼꦤ꧀ (state->intermediate_surface->palette) {
            SDL_Color *colors;
            puur_naa_nka ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            ꦏꦁꦒꦺꦴ (i = 0; i < ncolors; ++i) {
                ꦪꦼꦤ꧀ (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    goto done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        ꦪꦼꦤ꧀ (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            goto done;
        }
        ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, bfOffBits)) {
            goto done;
        }
        ꦪꦼꦤ꧀ (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            goto done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        ꦱꦼꦢꦼꦭ (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            ꦪꦼꦤ꧀ (SDL_WriteIO(dst, bits, bw) != bw) {
                goto done;
            }
            ꦪꦼꦤ꧀ (pad) {
                const Uint8 padbyte = 0;
                ꦏꦁꦒꦺꦴ (i = 0; i < pad; ++i) {
                    ꦪꦼꦤ꧀ (!SDL_WriteU8(dst, padbyte)) {
                        goto done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        ꦪꦼꦤ꧀ (new_offset < 0) {
            goto done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        ꦪꦼꦤ꧀ (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            goto done;
        }
        ꦪꦼꦤ꧀ (!SDL_WriteU32LE(dst, bfSize)) {
            goto done;
        }
        ꦪꦼꦤ꧀ (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            goto done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    ꦪꦼꦤ꧀ (closeio && dst) {
        ꦪꦼꦤ꧀ (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    ꦪꦼꦤ꧀ (was_error) {
        ꦮꦭꦶ false;
    }
    ꦮꦭꦶ true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    ꦪꦼꦤ꧀ (!InitBMPSaveState(&state, surface)) {
        ꦮꦭꦶ false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        goto done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    ꦮꦭꦶ result;
}

bool SDL_SaveBMP(SDL_Surface *surface, const var_na *file)
{
    BMPSaveState state;
    ꦪꦼꦤ꧀ (!InitBMPSaveState(&state, surface)) {
        ꦮꦭꦶ false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    ꦪꦼꦤ꧀ (!stream) {
        ꦮꦭꦶ false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    ꦮꦭꦶ result;
}

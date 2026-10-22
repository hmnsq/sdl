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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#ଅନ୍ତର୍ଭାଵ "SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"

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

ସ୍ଥିର bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch = surface->pitch;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    ଯଦି (spot >= start && spot < end) \
        *spot = (x)

    ପାଇଁ (;;) {
        ଯଦି (!SDL_ReadU8(src, &ch)) {
            ଫେରନ୍ତୁ false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        ଯଦି (ch) {
            Uint8 pixelvalue;
            ଯଦି (!SDL_ReadU8(src, &pixelvalue)) {
                ଫେରନ୍ତୁ false;
            }
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ich = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ch;
            କର {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } ଯେତେବେଳେ (ich > 0);
        } ଅନ୍ୟଥା {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            ଯଦି (!SDL_ReadU8(src, &ch)) {
                ଫେରନ୍ତୁ false;
            }
            ବାଛ (ch) {
            ସ୍ଥିତି 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 1:               // end of bitmap
                ଫେରନ୍ତୁ true; // success!
            ସ୍ଥିତି 2:               // delta
                ଯଦି (!SDL_ReadU8(src, &ch)) {
                    ଫେରନ୍ତୁ false;
                }
                ofs += ch / pixels_per_byte;
                ଯଦି (ch & pixels_per_byte) {
                    ofs++;
                }
                ଯଦି (!SDL_ReadU8(src, &ch)) {
                    ଫେରନ୍ତୁ false;
                }
                bits -= (ch * pitch);
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                ଯଦି (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } ଅନ୍ୟଥା {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                ପୂର୍ଣ୍ଣସଂଖ୍ୟା ich = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ch;
                କର {
                    Uint8 pixelvalue;
                    ଯଦି (!SDL_ReadU8(src, &pixelvalue)) {
                        ଫେରନ୍ତୁ false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } ଯେତେବେଳେ (ich > 0);

                // pad at even boundary
                ଯଦି (needsPad && !SDL_ReadU8(src, &ch)) {
                    ଫେରନ୍ତୁ false;
                }
                ଭାଙ୍ଗ;
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#ଯଦି SDL_BYTEORDER == SDL_BIG_ENDIAN
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା alphaChannelOffset = 0;
#ଅନ୍ୟଥା
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    ଯେତେବେଳେ (alpha < end) {
        ଯଦି (*alpha != 0) {
            hasAlpha = true;
            ଭାଙ୍ଗ;
        }
        alpha += 4;
    }

    ଯଦି (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        ଯେତେବେଳେ (alpha < end) {
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
    ଯଦି (start >= 0) {
        ଯଦି (SDL_ReadIO(src, magic, ଆକାର(magic)) == ଆକାର(magic)) {
            ଯଦି (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    ଫେରନ୍ତୁ is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *ଶୀର୍ଷ, *end;
    bool ଶୀର୍ଷ_Down;
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
    Uint16 bi_Bit_ଗଣନା = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = ଖାଲି;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        ଯାଅ done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    ଯଦି (fp_offset < 0) {
        ଯାଅ done;
    }
    SDL_ClearError();
    ଯଦି (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        ଯାଅ done;
    }
    ଯଦି (!SDL_ReadU16LE(src, ଖାଲି /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, ଖାଲି /* bfSize */) ||
        !SDL_ReadU16LE(src, ଖାଲି /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, ଖାଲି /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        ଯାଅ done;
    }

    // Read the Win32 BITMAPINFOHEADER
    ଯଦି (!SDL_ReadU32LE(src, &biSize)) {
        ଯାଅ done;
    }
    ଯଦି (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        ଯଦି (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, ଖାଲି /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_ଗଣନା)) {
            ଯାଅ done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } ଅନ୍ୟଥା ଯଦି (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        ଯଦି (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, ଖାଲି /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_ଗଣନା) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, ଖାଲି /* biSizeImage */) ||
            !SDL_ReadU32LE(src, ଖାଲି /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, ଖାଲି /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, ଖାଲି /* biClrImportant */)) {
            ଯାଅ done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        ଯଦି (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            ଯଦି (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                ଯଦି (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    ଯାଅ done;
                }

                // ...v3 adds an alpha mask.
                ଯଦି (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    ଯଦି (!SDL_ReadU32LE(src, &Amask)) {
                        ଯାଅ done;
                    }
                }
            } ଅନ୍ୟଥା {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                ଯଦି (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    ଯଦି (!SDL_ReadU32LE(src, ଖାଲି /* Rmask */) ||
                        !SDL_ReadU32LE(src, ଖାଲି /* Gmask */) ||
                        !SDL_ReadU32LE(src, ଖାଲି /* Bmask */)) {
                        ଯାଅ done;
                    }
                }
                ଯଦି (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    ଯଦି (!SDL_ReadU32LE(src, ଖାଲି /* Amask */)) {
                        ଯାଅ done;
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
        ଯଦି (biSize > headerSize) {
            ଯଦି (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                ଯାଅ done;
            }
        }
    }
    ଯଦି (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        ଯାଅ done;
    }
    ଯଦି (biHeight < 0) {
        ଶୀର୍ଷ_Down = true;
        biHeight = -biHeight;
    } ଅନ୍ୟଥା {
        ଶୀର୍ଷ_Down = false;
    }

    // Check for read error
    ଯଦି (SDL_strcmp(SDL_GetError(), "") != 0) {
        ଯାଅ done;
    }

    // Reject invalid bit depths
    ବାଛ (bi_Bit_ଗଣନା) {
    ସ୍ଥିତି 0:
    ସ୍ଥିତି 3:
    ସ୍ଥିତି 5:
    ସ୍ଥିତି 6:
    ସ୍ଥିତି 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_ଗଣନା);
        ଯାଅ done;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }

    // RLE4 and RLE8 BMP compression is supported
    ବାଛ (biCompression) {
    ସ୍ଥିତି BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        ବାଛ (bi_Bit_ଗଣନା) {
        ସ୍ଥିତି 15:
        ସ୍ଥିତି 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 24:
#ଯଦି SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#ଅନ୍ୟଥା
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            ଭାଙ୍ଗ;
        ସ୍ଥିତି 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି BI_BITFIELDS:
        ଭାଙ୍ଗ; // we handled this in the info header.

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_ଗଣନା, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        ଯଦି (!surface) {
            ଯାଅ done;
        }
    }

    // Load the palette, if any
    ଯଦି (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ଯଦି (!palette) {
            ଯାଅ done;
        }

        ଯଦି (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            ଯାଅ done;
        }

        ଯଦି (bi_Bit_ଗଣନା >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            ଯାଅ done;
        }

        ଯଦି (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_ଗଣନା;
        }

        ଯଦି (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_ଗଣନା; // try forcing it?
            ଯଦି (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                ଯାଅ done;
            }
        }
        palette->ncolors = biClrUsed;

        ଯଦି (biSize == 12) {
            ପାଇଁ (i = 0; i < palette->ncolors; ++i) {
                ଯଦି (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    ଯାଅ done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } ଅନ୍ୟଥା {
            ପାଇଁ (i = 0; i < palette->ncolors; ++i) {
                ଯଦି (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    ଯାଅ done;
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
    ଯଦି (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        ଯାଅ done;
    }
    ଯଦି ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        ଯଦି (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            ଯାଅ done;
        }

        // Success!
        was_error = false;
        ଯାଅ done;
    }
    ଶୀର୍ଷ = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    ଯଦି (ଶୀର୍ଷ_Down) {
        bits = ଶୀର୍ଷ;
    } ଅନ୍ୟଥା {
        bits = end - surface->pitch;
    }
    ଯେତେବେଳେ (bits >= ଶୀର୍ଷ && bits < end) {
        ଯଦି (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            ଯାଅ done;
        }
        ଯଦି (bi_Bit_ଗଣନା == 8 && surface->palette && biClrUsed < (1u << bi_Bit_ଗଣନା)) {
            ପାଇଁ (i = 0; i < surface->w; ++i) {
                ଯଦି (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    ଯାଅ done;
                }
            }
        }
#ଯଦି SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        ବାଛ (bi_Bit_ଗଣନା) {
        ସ୍ଥିତି 15:
        ସ୍ଥିତି 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            ପାଇଁ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            ଭାଙ୍ଗ;
        }

        ସ୍ଥିତି 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            ପାଇଁ (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            ଭାଙ୍ଗ;
        }
        }
#endif

        // Skip padding bytes, ugh
        ଯଦି (pad) {
            Uint8 padbyte;
            ପାଇଁ (i = 0; i < pad; ++i) {
                ଯଦି (!SDL_ReadU8(src, &padbyte)) {
                    ଯାଅ done;
                }
            }
        }
        ଯଦି (ଶୀର୍ଷ_Down) {
            bits += surface->pitch;
        } ଅନ୍ୟଥା {
            bits -= surface->pitch;
        }
    }
    ଯଦି (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    ଯଦି (was_error) {
        ଯଦି (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = ଖାଲି;
    }
    ଯଦି (closeio && src) {
        SDL_CloseIO(src);
    }
    ଫେରନ୍ତୁ surface;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ସ୍ଥିର ଶୂନ୍ୟ FreeBMPSaveState(BMPSaveState *state)
{
    ଯଦି (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ସ୍ଥିର bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = ଖାଲି;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    ଯଦି (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    ଯଦି (surface->palette && !state->save32bit) {
        ଯଦି (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } ଅନ୍ୟଥା {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            ଯାଅ error;
        }
    } ଅନ୍ୟଥା ଯଦି ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } ଅନ୍ୟଥା {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        ଯଦି (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } ଅନ୍ୟଥା {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        ଯଦି (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_BITSPERPIXEL(pixel_format));
            ଯାଅ error;
        }
    }

    ଯଦି (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    ଫେରନ୍ତୁ true;
error:
    FreeBMPSaveState(state);
    ଫେରନ୍ତୁ false;
}

SDL_Surface *SDL_LoadBMP(ଅଚଳ ଅକ୍ଷର *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    ଯଦି (!stream) {
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ SDL_LoadBMP_IO(stream, true);
}
ସ୍ଥିର bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    ଅକ୍ଷର magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_ଗଣନା;
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

    ଯଦି (SDL_LockSurface(state->intermediate_surface)) {
        ଅଚଳ size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        ଯଦି (fp_offset < 0) {
            ଯାଅ done;
        }
        ଯଦି (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            ଯାଅ done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_ଗଣନା = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        ଯଦି (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } ଅନ୍ୟଥା {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        ଯଦି (state->save32bit && !state->saveLegacyBMP) {
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
        ଯଦି (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_ଗଣନା) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            ଯାଅ done;
        }

        // Write the BMP info values
        ଯଦି (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            ଯଦି (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                ଯାଅ done;
            }
            ପାଇଁ (i = 0; i < 3 * 3; i++) {
                ଯଦି (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    ଯାଅ done;
                }
            }
            ଯଦି (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                ଯାଅ done;
            }
            // Version 5 values
            ଯଦି (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                ଯାଅ done;
            }
        }

        // Write the palette (in BGR color order)
        ଯଦି (state->intermediate_surface->palette) {
            SDL_Color *colors;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            ପାଇଁ (i = 0; i < ncolors; ++i) {
                ଯଦି (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    ଯାଅ done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        ଯଦି (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            ଯାଅ done;
        }
        ଯଦି (!SDL_WriteU32LE(dst, bfOffBits)) {
            ଯାଅ done;
        }
        ଯଦି (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            ଯାଅ done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        ଯେତେବେଳେ (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            ଯଦି (SDL_WriteIO(dst, bits, bw) != bw) {
                ଯାଅ done;
            }
            ଯଦି (pad) {
                ଅଚଳ Uint8 padbyte = 0;
                ପାଇଁ (i = 0; i < pad; ++i) {
                    ଯଦି (!SDL_WriteU8(dst, padbyte)) {
                        ଯାଅ done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        ଯଦି (new_offset < 0) {
            ଯାଅ done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        ଯଦି (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            ଯାଅ done;
        }
        ଯଦି (!SDL_WriteU32LE(dst, bfSize)) {
            ଯାଅ done;
        }
        ଯଦି (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            ଯାଅ done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    ଯଦି (closeio && dst) {
        ଯଦି (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    ଯଦି (was_error) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    ଯଦି (!InitBMPSaveState(&state, surface)) {
        ଫେରନ୍ତୁ false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        ଯାଅ done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    ଫେରନ୍ତୁ result;
}

bool SDL_SaveBMP(SDL_Surface *surface, ଅଚଳ ଅକ୍ଷର *file)
{
    BMPSaveState state;
    ଯଦି (!InitBMPSaveState(&state, surface)) {
        ଫେରନ୍ତୁ false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    ଯଦି (!stream) {
        ଫେରନ୍ତୁ false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    ଫେରନ୍ତୁ result;
}

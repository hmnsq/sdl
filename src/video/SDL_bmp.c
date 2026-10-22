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
#অন্তর্ভাব "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#অন্তর্ভাব "SDL_pixels_c.h"
#অন্তর্ভাব "SDL_surface_c.h"

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

স্থির bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, পূর্ণাঙ্ক isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    পূর্ণাঙ্ক pitch = surface->pitch;
    পূর্ণাঙ্ক height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    পূর্ণাঙ্ক ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ধ্রুব পূর্ণাঙ্ক pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    যদি (spot >= start && spot < end) \
        *spot = (x)

    প্রতি (;;) {
        যদি (!SDL_ReadU8(src, &ch)) {
            প্রত্যাগম false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        যদি (ch) {
            Uint8 pixelvalue;
            যদি (!SDL_ReadU8(src, &pixelvalue)) {
                প্রত্যাগম false;
            }
            পূর্ণাঙ্ক ich = (পূর্ণাঙ্ক) ch;
            কুরু {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } যাবত্ (ich > 0);
        } অন্যথা {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            যদি (!SDL_ReadU8(src, &ch)) {
                প্রত্যাগম false;
            }
            বিকল্প (ch) {
            পক্ষ 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                ভঙ্গ;
            পক্ষ 1:               // end of bitmap
                প্রত্যাগম true; // success!
            পক্ষ 2:               // delta
                যদি (!SDL_ReadU8(src, &ch)) {
                    প্রত্যাগম false;
                }
                ofs += ch / pixels_per_byte;
                যদি (ch & pixels_per_byte) {
                    ofs++;
                }
                যদি (!SDL_ReadU8(src, &ch)) {
                    প্রত্যাগম false;
                }
                bits -= (ch * pitch);
                ভঙ্গ;
            স্বভাব: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                যদি (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } অন্যথা {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                পূর্ণাঙ্ক ich = (পূর্ণাঙ্ক) ch;
                কুরু {
                    Uint8 pixelvalue;
                    যদি (!SDL_ReadU8(src, &pixelvalue)) {
                        প্রত্যাগম false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } যাবত্ (ich > 0);

                // pad at even boundary
                যদি (needsPad && !SDL_ReadU8(src, &ch)) {
                    প্রত্যাগম false;
                }
                ভঙ্গ;
            }
        }
    }
}

স্থির শূন্য CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#যদি SDL_BYTEORDER == SDL_BIG_ENDIAN
    পূর্ণাঙ্ক alphaChannelOffset = 0;
#অন্যথা
    পূর্ণাঙ্ক alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    যাবত্ (alpha < end) {
        যদি (*alpha != 0) {
            hasAlpha = true;
            ভঙ্গ;
        }
        alpha += 4;
    }

    যদি (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        যাবত্ (alpha < end) {
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
    যদি (start >= 0) {
        যদি (SDL_ReadIO(src, magic, পরিমাণ(magic)) == পরিমাণ(magic)) {
            যদি (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    প্রত্যাগম is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    পূর্ণাঙ্ক i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *শীর্ষ, *end;
    bool শীর্ষ_Down;
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
    Uint16 bi_Bit_গুনতি = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = রিক্ত;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        গচ্ছ done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    যদি (fp_offset < 0) {
        গচ্ছ done;
    }
    SDL_ClearError();
    যদি (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        গচ্ছ done;
    }
    যদি (!SDL_ReadU16LE(src, রিক্ত /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, রিক্ত /* bfSize */) ||
        !SDL_ReadU16LE(src, রিক্ত /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, রিক্ত /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        গচ্ছ done;
    }

    // Read the Win32 BITMAPINFOHEADER
    যদি (!SDL_ReadU32LE(src, &biSize)) {
        গচ্ছ done;
    }
    যদি (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        যদি (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, রিক্ত /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_গুনতি)) {
            গচ্ছ done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } অন্যথা যদি (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        যদি (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, রিক্ত /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_গুনতি) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, রিক্ত /* biSizeImage */) ||
            !SDL_ReadU32LE(src, রিক্ত /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, রিক্ত /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, রিক্ত /* biClrImportant */)) {
            গচ্ছ done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        যদি (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            যদি (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                যদি (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    গচ্ছ done;
                }

                // ...v3 adds an alpha mask.
                যদি (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    যদি (!SDL_ReadU32LE(src, &Amask)) {
                        গচ্ছ done;
                    }
                }
            } অন্যথা {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                যদি (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    যদি (!SDL_ReadU32LE(src, রিক্ত /* Rmask */) ||
                        !SDL_ReadU32LE(src, রিক্ত /* Gmask */) ||
                        !SDL_ReadU32LE(src, রিক্ত /* Bmask */)) {
                        গচ্ছ done;
                    }
                }
                যদি (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    যদি (!SDL_ReadU32LE(src, রিক্ত /* Amask */)) {
                        গচ্ছ done;
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
        যদি (biSize > headerSize) {
            যদি (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                গচ্ছ done;
            }
        }
    }
    যদি (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        গচ্ছ done;
    }
    যদি (biHeight < 0) {
        শীর্ষ_Down = true;
        biHeight = -biHeight;
    } অন্যথা {
        শীর্ষ_Down = false;
    }

    // Check for read error
    যদি (SDL_strcmp(SDL_GetError(), "") != 0) {
        গচ্ছ done;
    }

    // Reject invalid bit depths
    বিকল্প (bi_Bit_গুনতি) {
    পক্ষ 0:
    পক্ষ 3:
    পক্ষ 5:
    পক্ষ 6:
    পক্ষ 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_গুনতি);
        গচ্ছ done;
    স্বভাব:
        ভঙ্গ;
    }

    // RLE4 and RLE8 BMP compression is supported
    বিকল্প (biCompression) {
    পক্ষ BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        বিকল্প (bi_Bit_গুনতি) {
        পক্ষ 15:
        পক্ষ 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            ভঙ্গ;
        পক্ষ 24:
#যদি SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#অন্যথা
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            ভঙ্গ;
        পক্ষ 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            ভঙ্গ;
        স্বভাব:
            ভঙ্গ;
        }
        ভঙ্গ;

    পক্ষ BI_BITFIELDS:
        ভঙ্গ; // we handled this in the info header.

    স্বভাব:
        ভঙ্গ;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_গুনতি, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        যদি (!surface) {
            গচ্ছ done;
        }
    }

    // Load the palette, if any
    যদি (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        যদি (!palette) {
            গচ্ছ done;
        }

        যদি (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            গচ্ছ done;
        }

        যদি (bi_Bit_গুনতি >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            গচ্ছ done;
        }

        যদি (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_গুনতি;
        }

        যদি (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_গুনতি; // try forcing it?
            যদি (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                গচ্ছ done;
            }
        }
        palette->ncolors = biClrUsed;

        যদি (biSize == 12) {
            প্রতি (i = 0; i < palette->ncolors; ++i) {
                যদি (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    গচ্ছ done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } অন্যথা {
            প্রতি (i = 0; i < palette->ncolors; ++i) {
                যদি (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    গচ্ছ done;
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
    যদি (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        গচ্ছ done;
    }
    যদি ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        যদি (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            গচ্ছ done;
        }

        // Success!
        was_error = false;
        গচ্ছ done;
    }
    শীর্ষ = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    যদি (শীর্ষ_Down) {
        bits = শীর্ষ;
    } অন্যথা {
        bits = end - surface->pitch;
    }
    যাবত্ (bits >= শীর্ষ && bits < end) {
        যদি (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            গচ্ছ done;
        }
        যদি (bi_Bit_গুনতি == 8 && surface->palette && biClrUsed < (1u << bi_Bit_গুনতি)) {
            প্রতি (i = 0; i < surface->w; ++i) {
                যদি (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    গচ্ছ done;
                }
            }
        }
#যদি SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        বিকল্প (bi_Bit_গুনতি) {
        পক্ষ 15:
        পক্ষ 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            প্রতি (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            ভঙ্গ;
        }

        পক্ষ 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            প্রতি (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            ভঙ্গ;
        }
        }
#endif

        // Skip padding bytes, ugh
        যদি (pad) {
            Uint8 padbyte;
            প্রতি (i = 0; i < pad; ++i) {
                যদি (!SDL_ReadU8(src, &padbyte)) {
                    গচ্ছ done;
                }
            }
        }
        যদি (শীর্ষ_Down) {
            bits += surface->pitch;
        } অন্যথা {
            bits -= surface->pitch;
        }
    }
    যদি (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    যদি (was_error) {
        যদি (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = রিক্ত;
    }
    যদি (closeio && src) {
        SDL_CloseIO(src);
    }
    প্রত্যাগম surface;
}

প্রকারনির্দেশ সংরচনা {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

স্থির শূন্য FreeBMPSaveState(BMPSaveState *state)
{
    যদি (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

স্থির bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = রিক্ত;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        প্রত্যাগম SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    যদি (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    যদি (surface->palette && !state->save32bit) {
        যদি (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } অন্যথা {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            গচ্ছ error;
        }
    } অন্যথা যদি ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } অন্যথা {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        যদি (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } অন্যথা {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        যদি (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (পূর্ণাঙ্ক)SDL_BITSPERPIXEL(pixel_format));
            গচ্ছ error;
        }
    }

    যদি (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    প্রত্যাগম true;
error:
    FreeBMPSaveState(state);
    প্রত্যাগম false;
}

SDL_Surface *SDL_LoadBMP(ধ্রুব বর্ণ *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    যদি (!stream) {
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম SDL_LoadBMP_IO(stream, true);
}
স্থির bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    পূর্ণাঙ্ক i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    বর্ণ magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_গুনতি;
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

    যদি (SDL_LockSurface(state->intermediate_surface)) {
        ধ্রুব size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        যদি (fp_offset < 0) {
            গচ্ছ done;
        }
        যদি (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            গচ্ছ done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_গুনতি = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        যদি (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } অন্যথা {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        যদি (state->save32bit && !state->saveLegacyBMP) {
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
        যদি (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_গুনতি) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            গচ্ছ done;
        }

        // Write the BMP info values
        যদি (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            যদি (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                গচ্ছ done;
            }
            প্রতি (i = 0; i < 3 * 3; i++) {
                যদি (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    গচ্ছ done;
                }
            }
            যদি (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                গচ্ছ done;
            }
            // Version 5 values
            যদি (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                গচ্ছ done;
            }
        }

        // Write the palette (in BGR color order)
        যদি (state->intermediate_surface->palette) {
            SDL_Color *colors;
            পূর্ণাঙ্ক ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            প্রতি (i = 0; i < ncolors; ++i) {
                যদি (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    গচ্ছ done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        যদি (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            গচ্ছ done;
        }
        যদি (!SDL_WriteU32LE(dst, bfOffBits)) {
            গচ্ছ done;
        }
        যদি (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            গচ্ছ done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        যাবত্ (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            যদি (SDL_WriteIO(dst, bits, bw) != bw) {
                গচ্ছ done;
            }
            যদি (pad) {
                ধ্রুব Uint8 padbyte = 0;
                প্রতি (i = 0; i < pad; ++i) {
                    যদি (!SDL_WriteU8(dst, padbyte)) {
                        গচ্ছ done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        যদি (new_offset < 0) {
            গচ্ছ done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        যদি (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            গচ্ছ done;
        }
        যদি (!SDL_WriteU32LE(dst, bfSize)) {
            গচ্ছ done;
        }
        যদি (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            গচ্ছ done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    যদি (closeio && dst) {
        যদি (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    যদি (was_error) {
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    যদি (!InitBMPSaveState(&state, surface)) {
        প্রত্যাগম false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        গচ্ছ done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    প্রত্যাগম result;
}

bool SDL_SaveBMP(SDL_Surface *surface, ধ্রুব বর্ণ *file)
{
    BMPSaveState state;
    যদি (!InitBMPSaveState(&state, surface)) {
        প্রত্যাগম false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    যদি (!stream) {
        প্রত্যাগম false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    প্রত্যাগম result;
}

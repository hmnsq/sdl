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

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_surface_c.h"

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

स्थिर bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, पूर्णाङ्क isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    पूर्णाङ्क pitch = surface->pitch;
    पूर्णाङ्क height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    पूर्णाङ्क ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ध्रुव पूर्णाङ्क pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    यदि (spot >= start && spot < end) \
        *spot = (x)

    प्रति (;;) {
        यदि (!SDL_ReadU8(src, &ch)) {
            प्रत्यागम false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        यदि (ch) {
            Uint8 pixelvalue;
            यदि (!SDL_ReadU8(src, &pixelvalue)) {
                प्रत्यागम false;
            }
            पूर्णाङ्क ich = (पूर्णाङ्क) ch;
            कुरु {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } यावत् (ich > 0);
        } अन्यथा {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            यदि (!SDL_ReadU8(src, &ch)) {
                प्रत्यागम false;
            }
            विकल्प (ch) {
            पक्ष 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                भङ्ग;
            पक्ष 1:               // end of bitmap
                प्रत्यागम true; // success!
            पक्ष 2:               // delta
                यदि (!SDL_ReadU8(src, &ch)) {
                    प्रत्यागम false;
                }
                ofs += ch / pixels_per_byte;
                यदि (ch & pixels_per_byte) {
                    ofs++;
                }
                यदि (!SDL_ReadU8(src, &ch)) {
                    प्रत्यागम false;
                }
                bits -= (ch * pitch);
                भङ्ग;
            स्वभाव: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                यदि (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } अन्यथा {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                पूर्णाङ्क ich = (पूर्णाङ्क) ch;
                कुरु {
                    Uint8 pixelvalue;
                    यदि (!SDL_ReadU8(src, &pixelvalue)) {
                        प्रत्यागम false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } यावत् (ich > 0);

                // pad at even boundary
                यदि (needsPad && !SDL_ReadU8(src, &ch)) {
                    प्रत्यागम false;
                }
                भङ्ग;
            }
        }
    }
}

स्थिर शून्य CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
    पूर्णाङ्क alphaChannelOffset = 0;
#अन्यथा
    पूर्णाङ्क alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    यावत् (alpha < end) {
        यदि (*alpha != 0) {
            hasAlpha = true;
            भङ्ग;
        }
        alpha += 4;
    }

    यदि (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        यावत् (alpha < end) {
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
    यदि (start >= 0) {
        यदि (SDL_ReadIO(src, magic, परिमाण(magic)) == परिमाण(magic)) {
            यदि (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    प्रत्यागम is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    पूर्णाङ्क i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *शीर्ष, *end;
    bool शीर्ष_Down;
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
    Uint16 bi_Bit_गिनती = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = रिक्त;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        गच्छ done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    यदि (fp_offset < 0) {
        गच्छ done;
    }
    SDL_ClearError();
    यदि (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        गच्छ done;
    }
    यदि (!SDL_ReadU16LE(src, रिक्त /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, रिक्त /* bfSize */) ||
        !SDL_ReadU16LE(src, रिक्त /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, रिक्त /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        गच्छ done;
    }

    // Read the Win32 BITMAPINFOHEADER
    यदि (!SDL_ReadU32LE(src, &biSize)) {
        गच्छ done;
    }
    यदि (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        यदि (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, रिक्त /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_गिनती)) {
            गच्छ done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } अन्यथा यदि (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        यदि (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, रिक्त /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_गिनती) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, रिक्त /* biSizeImage */) ||
            !SDL_ReadU32LE(src, रिक्त /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, रिक्त /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, रिक्त /* biClrImportant */)) {
            गच्छ done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        यदि (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            यदि (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                यदि (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    गच्छ done;
                }

                // ...v3 adds an alpha mask.
                यदि (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    यदि (!SDL_ReadU32LE(src, &Amask)) {
                        गच्छ done;
                    }
                }
            } अन्यथा {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                यदि (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    यदि (!SDL_ReadU32LE(src, रिक्त /* Rmask */) ||
                        !SDL_ReadU32LE(src, रिक्त /* Gmask */) ||
                        !SDL_ReadU32LE(src, रिक्त /* Bmask */)) {
                        गच्छ done;
                    }
                }
                यदि (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    यदि (!SDL_ReadU32LE(src, रिक्त /* Amask */)) {
                        गच्छ done;
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
        यदि (biSize > headerSize) {
            यदि (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                गच्छ done;
            }
        }
    }
    यदि (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        गच्छ done;
    }
    यदि (biHeight < 0) {
        शीर्ष_Down = true;
        biHeight = -biHeight;
    } अन्यथा {
        शीर्ष_Down = false;
    }

    // Check for read error
    यदि (SDL_strcmp(SDL_GetError(), "") != 0) {
        गच्छ done;
    }

    // Reject invalid bit depths
    विकल्प (bi_Bit_गिनती) {
    पक्ष 0:
    पक्ष 3:
    पक्ष 5:
    पक्ष 6:
    पक्ष 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_गिनती);
        गच्छ done;
    स्वभाव:
        भङ्ग;
    }

    // RLE4 and RLE8 BMP compression is supported
    विकल्प (biCompression) {
    पक्ष BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        विकल्प (bi_Bit_गिनती) {
        पक्ष 15:
        पक्ष 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            भङ्ग;
        पक्ष 24:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#अन्यथा
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            भङ्ग;
        पक्ष 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
        भङ्ग;

    पक्ष BI_BITFIELDS:
        भङ्ग; // we handled this in the info header.

    स्वभाव:
        भङ्ग;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_गिनती, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        यदि (!surface) {
            गच्छ done;
        }
    }

    // Load the palette, if any
    यदि (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        यदि (!palette) {
            गच्छ done;
        }

        यदि (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            गच्छ done;
        }

        यदि (bi_Bit_गिनती >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            गच्छ done;
        }

        यदि (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_गिनती;
        }

        यदि (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_गिनती; // try forcing it?
            यदि (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                गच्छ done;
            }
        }
        palette->ncolors = biClrUsed;

        यदि (biSize == 12) {
            प्रति (i = 0; i < palette->ncolors; ++i) {
                यदि (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    गच्छ done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } अन्यथा {
            प्रति (i = 0; i < palette->ncolors; ++i) {
                यदि (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    गच्छ done;
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
    यदि (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        गच्छ done;
    }
    यदि ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        यदि (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            गच्छ done;
        }

        // Success!
        was_error = false;
        गच्छ done;
    }
    शीर्ष = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    यदि (शीर्ष_Down) {
        bits = शीर्ष;
    } अन्यथा {
        bits = end - surface->pitch;
    }
    यावत् (bits >= शीर्ष && bits < end) {
        यदि (SDL_ReadIO(src, bits, surface->pitch) != (माप_प्रकार)surface->pitch) {
            गच्छ done;
        }
        यदि (bi_Bit_गिनती == 8 && surface->palette && biClrUsed < (1u << bi_Bit_गिनती)) {
            प्रति (i = 0; i < surface->w; ++i) {
                यदि (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    गच्छ done;
                }
            }
        }
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        विकल्प (bi_Bit_गिनती) {
        पक्ष 15:
        पक्ष 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            प्रति (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            भङ्ग;
        }

        पक्ष 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            प्रति (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            भङ्ग;
        }
        }
#endif

        // Skip padding bytes, ugh
        यदि (pad) {
            Uint8 padbyte;
            प्रति (i = 0; i < pad; ++i) {
                यदि (!SDL_ReadU8(src, &padbyte)) {
                    गच्छ done;
                }
            }
        }
        यदि (शीर्ष_Down) {
            bits += surface->pitch;
        } अन्यथा {
            bits -= surface->pitch;
        }
    }
    यदि (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    यदि (was_error) {
        यदि (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = रिक्त;
    }
    यदि (closeio && src) {
        SDL_CloseIO(src);
    }
    प्रत्यागम surface;
}

प्रकारनिर्देश संरचना {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

स्थिर शून्य FreeBMPSaveState(BMPSaveState *state)
{
    यदि (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

स्थिर bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = रिक्त;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    यदि (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    यदि (surface->palette && !state->save32bit) {
        यदि (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } अन्यथा {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            गच्छ error;
        }
    } अन्यथा यदि ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } अन्यथा {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        यदि (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } अन्यथा {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        यदि (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (पूर्णाङ्क)SDL_BITSPERPIXEL(pixel_format));
            गच्छ error;
        }
    }

    यदि (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    प्रत्यागम true;
error:
    FreeBMPSaveState(state);
    प्रत्यागम false;
}

SDL_Surface *SDL_LoadBMP(ध्रुव वर्ण *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    यदि (!stream) {
        प्रत्यागम रिक्त;
    }
    प्रत्यागम SDL_LoadBMP_IO(stream, true);
}
स्थिर bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    पूर्णाङ्क i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    वर्ण magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_गिनती;
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

    यदि (SDL_LockSurface(state->intermediate_surface)) {
        ध्रुव माप_प्रकार bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        यदि (fp_offset < 0) {
            गच्छ done;
        }
        यदि (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            गच्छ done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_गिनती = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        यदि (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } अन्यथा {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        यदि (state->save32bit && !state->saveLegacyBMP) {
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
        यदि (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_गिनती) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            गच्छ done;
        }

        // Write the BMP info values
        यदि (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            यदि (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                गच्छ done;
            }
            प्रति (i = 0; i < 3 * 3; i++) {
                यदि (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    गच्छ done;
                }
            }
            यदि (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                गच्छ done;
            }
            // Version 5 values
            यदि (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                गच्छ done;
            }
        }

        // Write the palette (in BGR color order)
        यदि (state->intermediate_surface->palette) {
            SDL_Color *colors;
            पूर्णाङ्क ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            प्रति (i = 0; i < ncolors; ++i) {
                यदि (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    गच्छ done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        यदि (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            गच्छ done;
        }
        यदि (!SDL_WriteU32LE(dst, bfOffBits)) {
            गच्छ done;
        }
        यदि (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            गच्छ done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        यावत् (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            यदि (SDL_WriteIO(dst, bits, bw) != bw) {
                गच्छ done;
            }
            यदि (pad) {
                ध्रुव Uint8 padbyte = 0;
                प्रति (i = 0; i < pad; ++i) {
                    यदि (!SDL_WriteU8(dst, padbyte)) {
                        गच्छ done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        यदि (new_offset < 0) {
            गच्छ done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        यदि (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            गच्छ done;
        }
        यदि (!SDL_WriteU32LE(dst, bfSize)) {
            गच्छ done;
        }
        यदि (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            गच्छ done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    यदि (closeio && dst) {
        यदि (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    यदि (was_error) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    यदि (!InitBMPSaveState(&state, surface)) {
        प्रत्यागम false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        गच्छ done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    प्रत्यागम result;
}

bool SDL_SaveBMP(SDL_Surface *surface, ध्रुव वर्ण *file)
{
    BMPSaveState state;
    यदि (!InitBMPSaveState(&state, surface)) {
        प्रत्यागम false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    यदि (!stream) {
        प्रत्यागम false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    प्रत्यागम result;
}

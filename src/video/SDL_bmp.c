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
#அந்தர்பாவ "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#அந்தர்பாவ "SDL_pixels_c.h"
#அந்தர்பாவ "SDL_surface_c.h"

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

நிலையான bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, முழு isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    முழு pitch = surface->pitch;
    முழு height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    முழு ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    மாறிலி முழு pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    எனில் (spot >= start && spot < end) \
        *spot = (x)

    க்கு (;;) {
        எனில் (!SDL_ReadU8(src, &ch)) {
            திரும்பு false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        எனில் (ch) {
            Uint8 pixelvalue;
            எனில் (!SDL_ReadU8(src, &pixelvalue)) {
                திரும்பு false;
            }
            முழு ich = (முழு) ch;
            செய் {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } போது (ich > 0);
        } இல்லையெனில் {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            எனில் (!SDL_ReadU8(src, &ch)) {
                திரும்பு false;
            }
            தேர்வு (ch) {
            நிலை 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                நிறுத்து;
            நிலை 1:               // end of bitmap
                திரும்பு true; // success!
            நிலை 2:               // delta
                எனில் (!SDL_ReadU8(src, &ch)) {
                    திரும்பு false;
                }
                ofs += ch / pixels_per_byte;
                எனில் (ch & pixels_per_byte) {
                    ofs++;
                }
                எனில் (!SDL_ReadU8(src, &ch)) {
                    திரும்பு false;
                }
                bits -= (ch * pitch);
                நிறுத்து;
            இயல்பு: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                எனில் (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } இல்லையெனில் {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                முழு ich = (முழு) ch;
                செய் {
                    Uint8 pixelvalue;
                    எனில் (!SDL_ReadU8(src, &pixelvalue)) {
                        திரும்பு false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } போது (ich > 0);

                // pad at even boundary
                எனில் (needsPad && !SDL_ReadU8(src, &ch)) {
                    திரும்பு false;
                }
                நிறுத்து;
            }
        }
    }
}

நிலையான வெறுமை CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
    முழு alphaChannelOffset = 0;
#இல்லையெனில்
    முழு alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    போது (alpha < end) {
        எனில் (*alpha != 0) {
            hasAlpha = true;
            நிறுத்து;
        }
        alpha += 4;
    }

    எனில் (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        போது (alpha < end) {
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
    எனில் (start >= 0) {
        எனில் (SDL_ReadIO(src, magic, அளவு(magic)) == அளவு(magic)) {
            எனில் (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    திரும்பு is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    முழு i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *உச்சி, *end;
    bool உச்சி_Down;
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
    Uint16 bi_Bit_மொத்தம் = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = வெற்று;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        செல் done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    எனில் (fp_offset < 0) {
        செல் done;
    }
    SDL_ClearError();
    எனில் (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        செல் done;
    }
    எனில் (!SDL_ReadU16LE(src, வெற்று /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, வெற்று /* bfSize */) ||
        !SDL_ReadU16LE(src, வெற்று /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, வெற்று /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        செல் done;
    }

    // Read the Win32 BITMAPINFOHEADER
    எனில் (!SDL_ReadU32LE(src, &biSize)) {
        செல் done;
    }
    எனில் (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        எனில் (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, வெற்று /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_மொத்தம்)) {
            செல் done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } இல்லையெனில் எனில் (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        எனில் (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, வெற்று /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_மொத்தம்) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, வெற்று /* biSizeImage */) ||
            !SDL_ReadU32LE(src, வெற்று /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, வெற்று /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, வெற்று /* biClrImportant */)) {
            செல் done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        எனில் (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            எனில் (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                எனில் (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    செல் done;
                }

                // ...v3 adds an alpha mask.
                எனில் (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    எனில் (!SDL_ReadU32LE(src, &Amask)) {
                        செல் done;
                    }
                }
            } இல்லையெனில் {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                எனில் (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    எனில் (!SDL_ReadU32LE(src, வெற்று /* Rmask */) ||
                        !SDL_ReadU32LE(src, வெற்று /* Gmask */) ||
                        !SDL_ReadU32LE(src, வெற்று /* Bmask */)) {
                        செல் done;
                    }
                }
                எனில் (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    எனில் (!SDL_ReadU32LE(src, வெற்று /* Amask */)) {
                        செல் done;
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
        எனில் (biSize > headerSize) {
            எனில் (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                செல் done;
            }
        }
    }
    எனில் (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        செல் done;
    }
    எனில் (biHeight < 0) {
        உச்சி_Down = true;
        biHeight = -biHeight;
    } இல்லையெனில் {
        உச்சி_Down = false;
    }

    // Check for read error
    எனில் (SDL_strcmp(SDL_GetError(), "") != 0) {
        செல் done;
    }

    // Reject invalid bit depths
    தேர்வு (bi_Bit_மொத்தம்) {
    நிலை 0:
    நிலை 3:
    நிலை 5:
    நிலை 6:
    நிலை 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_மொத்தம்);
        செல் done;
    இயல்பு:
        நிறுத்து;
    }

    // RLE4 and RLE8 BMP compression is supported
    தேர்வு (biCompression) {
    நிலை BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        தேர்வு (bi_Bit_மொத்தம்) {
        நிலை 15:
        நிலை 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            நிறுத்து;
        நிலை 24:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#இல்லையெனில்
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            நிறுத்து;
        நிலை 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            நிறுத்து;
        இயல்பு:
            நிறுத்து;
        }
        நிறுத்து;

    நிலை BI_BITFIELDS:
        நிறுத்து; // we handled this in the info header.

    இயல்பு:
        நிறுத்து;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_மொத்தம், Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        எனில் (!surface) {
            செல் done;
        }
    }

    // Load the palette, if any
    எனில் (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        எனில் (!palette) {
            செல் done;
        }

        எனில் (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            செல் done;
        }

        எனில் (bi_Bit_மொத்தம் >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            செல் done;
        }

        எனில் (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_மொத்தம்;
        }

        எனில் (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_மொத்தம்; // try forcing it?
            எனில் (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                செல் done;
            }
        }
        palette->ncolors = biClrUsed;

        எனில் (biSize == 12) {
            க்கு (i = 0; i < palette->ncolors; ++i) {
                எனில் (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    செல் done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } இல்லையெனில் {
            க்கு (i = 0; i < palette->ncolors; ++i) {
                எனில் (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    செல் done;
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
    எனில் (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        செல் done;
    }
    எனில் ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        எனில் (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            செல் done;
        }

        // Success!
        was_error = false;
        செல் done;
    }
    உச்சி = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    எனில் (உச்சி_Down) {
        bits = உச்சி;
    } இல்லையெனில் {
        bits = end - surface->pitch;
    }
    போது (bits >= உச்சி && bits < end) {
        எனில் (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            செல் done;
        }
        எனில் (bi_Bit_மொத்தம் == 8 && surface->palette && biClrUsed < (1u << bi_Bit_மொத்தம்)) {
            க்கு (i = 0; i < surface->w; ++i) {
                எனில் (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    செல் done;
                }
            }
        }
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        தேர்வு (bi_Bit_மொத்தம்) {
        நிலை 15:
        நிலை 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            க்கு (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            நிறுத்து;
        }

        நிலை 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            க்கு (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            நிறுத்து;
        }
        }
#endif

        // Skip padding bytes, ugh
        எனில் (pad) {
            Uint8 padbyte;
            க்கு (i = 0; i < pad; ++i) {
                எனில் (!SDL_ReadU8(src, &padbyte)) {
                    செல் done;
                }
            }
        }
        எனில் (உச்சி_Down) {
            bits += surface->pitch;
        } இல்லையெனில் {
            bits -= surface->pitch;
        }
    }
    எனில் (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    எனில் (was_error) {
        எனில் (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = வெற்று;
    }
    எனில் (closeio && src) {
        SDL_CloseIO(src);
    }
    திரும்பு surface;
}

வகைவரை கட்டமைப்பு {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

நிலையான வெறுமை FreeBMPSaveState(BMPSaveState *state)
{
    எனில் (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

நிலையான bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = வெற்று;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        திரும்பு SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    எனில் (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    எனில் (surface->palette && !state->save32bit) {
        எனில் (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } இல்லையெனில் {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            செல் error;
        }
    } இல்லையெனில் எனில் ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } இல்லையெனில் {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        எனில் (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } இல்லையெனில் {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        எனில் (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (முழு)SDL_BITSPERPIXEL(pixel_format));
            செல் error;
        }
    }

    எனில் (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    திரும்பு true;
error:
    FreeBMPSaveState(state);
    திரும்பு false;
}

SDL_Surface *SDL_LoadBMP(மாறிலி எழுத்து *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    எனில் (!stream) {
        திரும்பு வெற்று;
    }
    திரும்பு SDL_LoadBMP_IO(stream, true);
}
நிலையான bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    முழு i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    எழுத்து magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_மொத்தம்;
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

    எனில் (SDL_LockSurface(state->intermediate_surface)) {
        மாறிலி size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        எனில் (fp_offset < 0) {
            செல் done;
        }
        எனில் (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            செல் done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_மொத்தம் = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        எனில் (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } இல்லையெனில் {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        எனில் (state->save32bit && !state->saveLegacyBMP) {
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
        எனில் (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_மொத்தம்) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            செல் done;
        }

        // Write the BMP info values
        எனில் (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            எனில் (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                செல் done;
            }
            க்கு (i = 0; i < 3 * 3; i++) {
                எனில் (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    செல் done;
                }
            }
            எனில் (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                செல் done;
            }
            // Version 5 values
            எனில் (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                செல் done;
            }
        }

        // Write the palette (in BGR color order)
        எனில் (state->intermediate_surface->palette) {
            SDL_Color *colors;
            முழு ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            க்கு (i = 0; i < ncolors; ++i) {
                எனில் (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    செல் done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        எனில் (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            செல் done;
        }
        எனில் (!SDL_WriteU32LE(dst, bfOffBits)) {
            செல் done;
        }
        எனில் (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            செல் done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        போது (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            எனில் (SDL_WriteIO(dst, bits, bw) != bw) {
                செல் done;
            }
            எனில் (pad) {
                மாறிலி Uint8 padbyte = 0;
                க்கு (i = 0; i < pad; ++i) {
                    எனில் (!SDL_WriteU8(dst, padbyte)) {
                        செல் done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        எனில் (new_offset < 0) {
            செல் done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        எனில் (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            செல் done;
        }
        எனில் (!SDL_WriteU32LE(dst, bfSize)) {
            செல் done;
        }
        எனில் (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            செல் done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    எனில் (closeio && dst) {
        எனில் (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    எனில் (was_error) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    எனில் (!InitBMPSaveState(&state, surface)) {
        திரும்பு false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        செல் done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    திரும்பு result;
}

bool SDL_SaveBMP(SDL_Surface *surface, மாறிலி எழுத்து *file)
{
    BMPSaveState state;
    எனில் (!InitBMPSaveState(&state, surface)) {
        திரும்பு false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    எனில் (!stream) {
        திரும்பு false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    திரும்பு result;
}

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
#അന്തര്ഭാവ "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#അന്തര്ഭാവ "SDL_pixels_c.h"
#അന്തര്ഭാവ "SDL_surface_c.h"

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

സ്ഥിതം bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, പൂർണ്ണസംഖ്യ isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    പൂർണ്ണസംഖ്യ pitch = surface->pitch;
    പൂർണ്ണസംഖ്യ height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    പൂർണ്ണസംഖ്യ ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    സ്ഥിരം പൂർണ്ണസംഖ്യ pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    എങ്കിൽ (spot >= start && spot < end) \
        *spot = (x)

    വേണ്ടി (;;) {
        എങ്കിൽ (!SDL_ReadU8(src, &ch)) {
            തിരികെ false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        എങ്കിൽ (ch) {
            Uint8 pixelvalue;
            എങ്കിൽ (!SDL_ReadU8(src, &pixelvalue)) {
                തിരികെ false;
            }
            പൂർണ്ണസംഖ്യ ich = (പൂർണ്ണസംഖ്യ) ch;
            ചെയ്യുക {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } ആകുമ്പോൾ (ich > 0);
        } അല്ലെങ്കിൽ {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            എങ്കിൽ (!SDL_ReadU8(src, &ch)) {
                തിരികെ false;
            }
            തിരഞ്ഞെടുപ്പ് (ch) {
            അവസ്ഥ 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                നിർത്തുക;
            അവസ്ഥ 1:               // end of bitmap
                തിരികെ true; // success!
            അവസ്ഥ 2:               // delta
                എങ്കിൽ (!SDL_ReadU8(src, &ch)) {
                    തിരികെ false;
                }
                ofs += ch / pixels_per_byte;
                എങ്കിൽ (ch & pixels_per_byte) {
                    ofs++;
                }
                എങ്കിൽ (!SDL_ReadU8(src, &ch)) {
                    തിരികെ false;
                }
                bits -= (ch * pitch);
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                എങ്കിൽ (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } അല്ലെങ്കിൽ {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                പൂർണ്ണസംഖ്യ ich = (പൂർണ്ണസംഖ്യ) ch;
                ചെയ്യുക {
                    Uint8 pixelvalue;
                    എങ്കിൽ (!SDL_ReadU8(src, &pixelvalue)) {
                        തിരികെ false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } ആകുമ്പോൾ (ich > 0);

                // pad at even boundary
                എങ്കിൽ (needsPad && !SDL_ReadU8(src, &ch)) {
                    തിരികെ false;
                }
                നിർത്തുക;
            }
        }
    }
}

സ്ഥിതം ശൂന്യം CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#എങ്കിൽ SDL_BYTEORDER == SDL_BIG_ENDIAN
    പൂർണ്ണസംഖ്യ alphaChannelOffset = 0;
#അല്ലെങ്കിൽ
    പൂർണ്ണസംഖ്യ alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    ആകുമ്പോൾ (alpha < end) {
        എങ്കിൽ (*alpha != 0) {
            hasAlpha = true;
            നിർത്തുക;
        }
        alpha += 4;
    }

    എങ്കിൽ (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        ആകുമ്പോൾ (alpha < end) {
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
    എങ്കിൽ (start >= 0) {
        എങ്കിൽ (SDL_ReadIO(src, magic, വലുപ്പം(magic)) == വലുപ്പം(magic)) {
            എങ്കിൽ (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    തിരികെ is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    പൂർണ്ണസംഖ്യ i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *bits;
    Uint8 *മുകൾ, *end;
    bool മുകൾ_Down;
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
    Uint16 bi_Bit_എണ്ണം = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 biClrUsed = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = ശൂന്യ;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        പോകുക done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    എങ്കിൽ (fp_offset < 0) {
        പോകുക done;
    }
    SDL_ClearError();
    എങ്കിൽ (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        പോകുക done;
    }
    എങ്കിൽ (!SDL_ReadU16LE(src, ശൂന്യ /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, ശൂന്യ /* bfSize */) ||
        !SDL_ReadU16LE(src, ശൂന്യ /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, ശൂന്യ /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        പോകുക done;
    }

    // Read the Win32 BITMAPINFOHEADER
    എങ്കിൽ (!SDL_ReadU32LE(src, &biSize)) {
        പോകുക done;
    }
    എങ്കിൽ (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        എങ്കിൽ (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, ശൂന്യ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_എണ്ണം)) {
            പോകുക done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        എങ്കിൽ (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, ശൂന്യ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_എണ്ണം) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, ശൂന്യ /* biSizeImage */) ||
            !SDL_ReadU32LE(src, ശൂന്യ /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, ശൂന്യ /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, ശൂന്യ /* biClrImportant */)) {
            പോകുക done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        എങ്കിൽ (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            എങ്കിൽ (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                എങ്കിൽ (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    പോകുക done;
                }

                // ...v3 adds an alpha mask.
                എങ്കിൽ (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    എങ്കിൽ (!SDL_ReadU32LE(src, &Amask)) {
                        പോകുക done;
                    }
                }
            } അല്ലെങ്കിൽ {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                എങ്കിൽ (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    എങ്കിൽ (!SDL_ReadU32LE(src, ശൂന്യ /* Rmask */) ||
                        !SDL_ReadU32LE(src, ശൂന്യ /* Gmask */) ||
                        !SDL_ReadU32LE(src, ശൂന്യ /* Bmask */)) {
                        പോകുക done;
                    }
                }
                എങ്കിൽ (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    എങ്കിൽ (!SDL_ReadU32LE(src, ശൂന്യ /* Amask */)) {
                        പോകുക done;
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
        എങ്കിൽ (biSize > headerSize) {
            എങ്കിൽ (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                പോകുക done;
            }
        }
    }
    എങ്കിൽ (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        പോകുക done;
    }
    എങ്കിൽ (biHeight < 0) {
        മുകൾ_Down = true;
        biHeight = -biHeight;
    } അല്ലെങ്കിൽ {
        മുകൾ_Down = false;
    }

    // Check for read error
    എങ്കിൽ (SDL_strcmp(SDL_GetError(), "") != 0) {
        പോകുക done;
    }

    // Reject invalid bit depths
    തിരഞ്ഞെടുപ്പ് (bi_Bit_എണ്ണം) {
    അവസ്ഥ 0:
    അവസ്ഥ 3:
    അവസ്ഥ 5:
    അവസ്ഥ 6:
    അവസ്ഥ 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_എണ്ണം);
        പോകുക done;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }

    // RLE4 and RLE8 BMP compression is supported
    തിരഞ്ഞെടുപ്പ് (biCompression) {
    അവസ്ഥ BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        തിരഞ്ഞെടുപ്പ് (bi_Bit_എണ്ണം) {
        അവസ്ഥ 15:
        അവസ്ഥ 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            നിർത്തുക;
        അവസ്ഥ 24:
#എങ്കിൽ SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#അല്ലെങ്കിൽ
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            നിർത്തുക;
        അവസ്ഥ 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            നിർത്തുക;
        }
        നിർത്തുക;

    അവസ്ഥ BI_BITFIELDS:
        നിർത്തുക; // we handled this in the info header.

    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_എണ്ണം, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        എങ്കിൽ (!surface) {
            പോകുക done;
        }
    }

    // Load the palette, if any
    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        എങ്കിൽ (!palette) {
            പോകുക done;
        }

        എങ്കിൽ (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            പോകുക done;
        }

        എങ്കിൽ (bi_Bit_എണ്ണം >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            പോകുക done;
        }

        എങ്കിൽ (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_എണ്ണം;
        }

        എങ്കിൽ (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_എണ്ണം; // try forcing it?
            എങ്കിൽ (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                പോകുക done;
            }
        }
        palette->ncolors = biClrUsed;

        എങ്കിൽ (biSize == 12) {
            വേണ്ടി (i = 0; i < palette->ncolors; ++i) {
                എങ്കിൽ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    പോകുക done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } അല്ലെങ്കിൽ {
            വേണ്ടി (i = 0; i < palette->ncolors; ++i) {
                എങ്കിൽ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    പോകുക done;
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
    എങ്കിൽ (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        പോകുക done;
    }
    എങ്കിൽ ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        എങ്കിൽ (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            പോകുക done;
        }

        // Success!
        was_error = false;
        പോകുക done;
    }
    മുകൾ = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    എങ്കിൽ (മുകൾ_Down) {
        bits = മുകൾ;
    } അല്ലെങ്കിൽ {
        bits = end - surface->pitch;
    }
    ആകുമ്പോൾ (bits >= മുകൾ && bits < end) {
        എങ്കിൽ (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            പോകുക done;
        }
        എങ്കിൽ (bi_Bit_എണ്ണം == 8 && surface->palette && biClrUsed < (1u << bi_Bit_എണ്ണം)) {
            വേണ്ടി (i = 0; i < surface->w; ++i) {
                എങ്കിൽ (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    പോകുക done;
                }
            }
        }
#എങ്കിൽ SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        തിരഞ്ഞെടുപ്പ് (bi_Bit_എണ്ണം) {
        അവസ്ഥ 15:
        അവസ്ഥ 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            വേണ്ടി (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            നിർത്തുക;
        }

        അവസ്ഥ 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            വേണ്ടി (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            നിർത്തുക;
        }
        }
#endif

        // Skip padding bytes, ugh
        എങ്കിൽ (pad) {
            Uint8 padbyte;
            വേണ്ടി (i = 0; i < pad; ++i) {
                എങ്കിൽ (!SDL_ReadU8(src, &padbyte)) {
                    പോകുക done;
                }
            }
        }
        എങ്കിൽ (മുകൾ_Down) {
            bits += surface->pitch;
        } അല്ലെങ്കിൽ {
            bits -= surface->pitch;
        }
    }
    എങ്കിൽ (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    എങ്കിൽ (was_error) {
        എങ്കിൽ (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = ശൂന്യ;
    }
    എങ്കിൽ (closeio && src) {
        SDL_CloseIO(src);
    }
    തിരികെ surface;
}

തരനിർവചനം ഘടന {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

സ്ഥിതം ശൂന്യം FreeBMPSaveState(BMPSaveState *state)
{
    എങ്കിൽ (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

സ്ഥിതം bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = ശൂന്യ;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        തിരികെ SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    എങ്കിൽ (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    എങ്കിൽ (surface->palette && !state->save32bit) {
        എങ്കിൽ (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } അല്ലെങ്കിൽ {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            പോകുക error;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } അല്ലെങ്കിൽ {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        എങ്കിൽ (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } അല്ലെങ്കിൽ {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        എങ്കിൽ (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (പൂർണ്ണസംഖ്യ)SDL_BITSPERPIXEL(pixel_format));
            പോകുക error;
        }
    }

    എങ്കിൽ (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    തിരികെ true;
error:
    FreeBMPSaveState(state);
    തിരികെ false;
}

SDL_Surface *SDL_LoadBMP(സ്ഥിരം അക്ഷരം *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    എങ്കിൽ (!stream) {
        തിരികെ ശൂന്യ;
    }
    തിരികെ SDL_LoadBMP_IO(stream, true);
}
സ്ഥിതം bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    പൂർണ്ണസംഖ്യ i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    അക്ഷരം magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_എണ്ണം;
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

    എങ്കിൽ (SDL_LockSurface(state->intermediate_surface)) {
        സ്ഥിരം size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        എങ്കിൽ (fp_offset < 0) {
            പോകുക done;
        }
        എങ്കിൽ (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            പോകുക done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_എണ്ണം = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        എങ്കിൽ (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } അല്ലെങ്കിൽ {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        എങ്കിൽ (state->save32bit && !state->saveLegacyBMP) {
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
        എങ്കിൽ (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_എണ്ണം) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            പോകുക done;
        }

        // Write the BMP info values
        എങ്കിൽ (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            എങ്കിൽ (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                പോകുക done;
            }
            വേണ്ടി (i = 0; i < 3 * 3; i++) {
                എങ്കിൽ (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    പോകുക done;
                }
            }
            എങ്കിൽ (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                പോകുക done;
            }
            // Version 5 values
            എങ്കിൽ (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                പോകുക done;
            }
        }

        // Write the palette (in BGR color order)
        എങ്കിൽ (state->intermediate_surface->palette) {
            SDL_Color *colors;
            പൂർണ്ണസംഖ്യ ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            വേണ്ടി (i = 0; i < ncolors; ++i) {
                എങ്കിൽ (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    പോകുക done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        എങ്കിൽ (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            പോകുക done;
        }
        എങ്കിൽ (!SDL_WriteU32LE(dst, bfOffBits)) {
            പോകുക done;
        }
        എങ്കിൽ (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            പോകുക done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        ആകുമ്പോൾ (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            എങ്കിൽ (SDL_WriteIO(dst, bits, bw) != bw) {
                പോകുക done;
            }
            എങ്കിൽ (pad) {
                സ്ഥിരം Uint8 padbyte = 0;
                വേണ്ടി (i = 0; i < pad; ++i) {
                    എങ്കിൽ (!SDL_WriteU8(dst, padbyte)) {
                        പോകുക done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        എങ്കിൽ (new_offset < 0) {
            പോകുക done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        എങ്കിൽ (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            പോകുക done;
        }
        എങ്കിൽ (!SDL_WriteU32LE(dst, bfSize)) {
            പോകുക done;
        }
        എങ്കിൽ (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            പോകുക done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    എങ്കിൽ (closeio && dst) {
        എങ്കിൽ (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    എങ്കിൽ (was_error) {
        തിരികെ false;
    }
    തിരികെ true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    എങ്കിൽ (!InitBMPSaveState(&state, surface)) {
        തിരികെ false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        പോകുക done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    തിരികെ result;
}

bool SDL_SaveBMP(SDL_Surface *surface, സ്ഥിരം അക്ഷരം *file)
{
    BMPSaveState state;
    എങ്കിൽ (!InitBMPSaveState(&state, surface)) {
        തിരികെ false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    എങ്കിൽ (!stream) {
        തിരികെ false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    തിരികെ result;
}

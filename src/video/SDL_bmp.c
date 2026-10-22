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

स्थिर bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, पूर्णांक isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    पूर्णांक pitch = surface->pitch;
    पूर्णांक height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    पूर्णांक ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    स्थिरांक पूर्णांक pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    जर (spot >= start && spot < end) \
        *spot = (x)

    साठी (;;) {
        जर (!SDL_ReadU8(src, &ch)) {
            परत false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        जर (ch) {
            Uint8 pixelvalue;
            जर (!SDL_ReadU8(src, &pixelvalue)) {
                परत false;
            }
            पूर्णांक ich = (पूर्णांक) ch;
            करा {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } पर्यंत (ich > 0);
        } अन्यथा {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            जर (!SDL_ReadU8(src, &ch)) {
                परत false;
            }
            निवड (ch) {
            स्थिती 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                थांबा;
            स्थिती 1:               // end of bitmap
                परत true; // success!
            स्थिती 2:               // delta
                जर (!SDL_ReadU8(src, &ch)) {
                    परत false;
                }
                ofs += ch / pixels_per_byte;
                जर (ch & pixels_per_byte) {
                    ofs++;
                }
                जर (!SDL_ReadU8(src, &ch)) {
                    परत false;
                }
                bits -= (ch * pitch);
                थांबा;
            पूर्वनिर्धारित: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                जर (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } अन्यथा {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                पूर्णांक ich = (पूर्णांक) ch;
                करा {
                    Uint8 pixelvalue;
                    जर (!SDL_ReadU8(src, &pixelvalue)) {
                        परत false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } पर्यंत (ich > 0);

                // pad at even boundary
                जर (needsPad && !SDL_ReadU8(src, &ch)) {
                    परत false;
                }
                थांबा;
            }
        }
    }
}

स्थिर शून्य CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#जर SDL_BYTEORDER == SDL_BIG_ENDIAN
    पूर्णांक alphaChannelOffset = 0;
#अन्यथा
    पूर्णांक alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    पर्यंत (alpha < end) {
        जर (*alpha != 0) {
            hasAlpha = true;
            थांबा;
        }
        alpha += 4;
    }

    जर (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        पर्यंत (alpha < end) {
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
    जर (start >= 0) {
        जर (SDL_ReadIO(src, magic, आकार(magic)) == आकार(magic)) {
            जर (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    परत is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    पूर्णांक i, pad;
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
    Uint16 bi_Bit_मोजणी = 0;
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
        जा done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    जर (fp_offset < 0) {
        जा done;
    }
    SDL_ClearError();
    जर (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        जा done;
    }
    जर (!SDL_ReadU16LE(src, रिक्त /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, रिक्त /* bfSize */) ||
        !SDL_ReadU16LE(src, रिक्त /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, रिक्त /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        जा done;
    }

    // Read the Win32 BITMAPINFOHEADER
    जर (!SDL_ReadU32LE(src, &biSize)) {
        जा done;
    }
    जर (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        जर (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, रिक्त /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_मोजणी)) {
            जा done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } अन्यथा जर (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        जर (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, रिक्त /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_मोजणी) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, रिक्त /* biSizeImage */) ||
            !SDL_ReadU32LE(src, रिक्त /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, रिक्त /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, रिक्त /* biClrImportant */)) {
            जा done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        जर (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            जर (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                जर (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    जा done;
                }

                // ...v3 adds an alpha mask.
                जर (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    जर (!SDL_ReadU32LE(src, &Amask)) {
                        जा done;
                    }
                }
            } अन्यथा {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                जर (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    जर (!SDL_ReadU32LE(src, रिक्त /* Rmask */) ||
                        !SDL_ReadU32LE(src, रिक्त /* Gmask */) ||
                        !SDL_ReadU32LE(src, रिक्त /* Bmask */)) {
                        जा done;
                    }
                }
                जर (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    जर (!SDL_ReadU32LE(src, रिक्त /* Amask */)) {
                        जा done;
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
        जर (biSize > headerSize) {
            जर (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                जा done;
            }
        }
    }
    जर (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        जा done;
    }
    जर (biHeight < 0) {
        शीर्ष_Down = true;
        biHeight = -biHeight;
    } अन्यथा {
        शीर्ष_Down = false;
    }

    // Check for read error
    जर (SDL_strcmp(SDL_GetError(), "") != 0) {
        जा done;
    }

    // Reject invalid bit depths
    निवड (bi_Bit_मोजणी) {
    स्थिती 0:
    स्थिती 3:
    स्थिती 5:
    स्थिती 6:
    स्थिती 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_मोजणी);
        जा done;
    पूर्वनिर्धारित:
        थांबा;
    }

    // RLE4 and RLE8 BMP compression is supported
    निवड (biCompression) {
    स्थिती BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        निवड (bi_Bit_मोजणी) {
        स्थिती 15:
        स्थिती 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            थांबा;
        स्थिती 24:
#जर SDL_BYTEORDER == SDL_BIG_ENDIAN
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
            थांबा;
        स्थिती 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            थांबा;
        पूर्वनिर्धारित:
            थांबा;
        }
        थांबा;

    स्थिती BI_BITFIELDS:
        थांबा; // we handled this in the info header.

    पूर्वनिर्धारित:
        थांबा;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_मोजणी, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        जर (!surface) {
            जा done;
        }
    }

    // Load the palette, if any
    जर (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        जर (!palette) {
            जा done;
        }

        जर (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            जा done;
        }

        जर (bi_Bit_मोजणी >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            जा done;
        }

        जर (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_मोजणी;
        }

        जर (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_मोजणी; // try forcing it?
            जर (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                जा done;
            }
        }
        palette->ncolors = biClrUsed;

        जर (biSize == 12) {
            साठी (i = 0; i < palette->ncolors; ++i) {
                जर (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    जा done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } अन्यथा {
            साठी (i = 0; i < palette->ncolors; ++i) {
                जर (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    जा done;
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
    जर (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        जा done;
    }
    जर ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        जर (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            जा done;
        }

        // Success!
        was_error = false;
        जा done;
    }
    शीर्ष = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    जर (शीर्ष_Down) {
        bits = शीर्ष;
    } अन्यथा {
        bits = end - surface->pitch;
    }
    पर्यंत (bits >= शीर्ष && bits < end) {
        जर (SDL_ReadIO(src, bits, surface->pitch) != (माप_प्रकार)surface->pitch) {
            जा done;
        }
        जर (bi_Bit_मोजणी == 8 && surface->palette && biClrUsed < (1u << bi_Bit_मोजणी)) {
            साठी (i = 0; i < surface->w; ++i) {
                जर (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    जा done;
                }
            }
        }
#जर SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        निवड (bi_Bit_मोजणी) {
        स्थिती 15:
        स्थिती 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            साठी (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            थांबा;
        }

        स्थिती 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            साठी (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            थांबा;
        }
        }
#endif

        // Skip padding bytes, ugh
        जर (pad) {
            Uint8 padbyte;
            साठी (i = 0; i < pad; ++i) {
                जर (!SDL_ReadU8(src, &padbyte)) {
                    जा done;
                }
            }
        }
        जर (शीर्ष_Down) {
            bits += surface->pitch;
        } अन्यथा {
            bits -= surface->pitch;
        }
    }
    जर (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    जर (was_error) {
        जर (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = रिक्त;
    }
    जर (closeio && src) {
        SDL_CloseIO(src);
    }
    परत surface;
}

प्रकारव्याख्या संरचना {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

स्थिर शून्य FreeBMPSaveState(BMPSaveState *state)
{
    जर (state->intermediate_surface && state->intermediate_surface != state->surface) {
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
        परत SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    जर (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    जर (surface->palette && !state->save32bit) {
        जर (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } अन्यथा {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            जा error;
        }
    } अन्यथा जर ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } अन्यथा {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        जर (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } अन्यथा {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        जर (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (पूर्णांक)SDL_BITSPERPIXEL(pixel_format));
            जा error;
        }
    }

    जर (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    परत true;
error:
    FreeBMPSaveState(state);
    परत false;
}

SDL_Surface *SDL_LoadBMP(स्थिरांक अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    जर (!stream) {
        परत रिक्त;
    }
    परत SDL_LoadBMP_IO(stream, true);
}
स्थिर bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    पूर्णांक i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    अक्षर magic[2] = { 'B', 'M' };
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_मोजणी;
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

    जर (SDL_LockSurface(state->intermediate_surface)) {
        स्थिरांक माप_प्रकार bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        जर (fp_offset < 0) {
            जा done;
        }
        जर (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            जा done;
        }

        // Set the BMP info values
        biSize = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_मोजणी = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        biSizeImage = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        जर (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } अन्यथा {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        जर (state->save32bit && !state->saveLegacyBMP) {
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
        जर (!SDL_WriteU32LE(dst, biSize) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_मोजणी) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, biSizeImage) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            जा done;
        }

        // Write the BMP info values
        जर (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            जर (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                जा done;
            }
            साठी (i = 0; i < 3 * 3; i++) {
                जर (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    जा done;
                }
            }
            जर (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                जा done;
            }
            // Version 5 values
            जर (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                जा done;
            }
        }

        // Write the palette (in BGR color order)
        जर (state->intermediate_surface->palette) {
            SDL_Color *colors;
            पूर्णांक ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            साठी (i = 0; i < ncolors; ++i) {
                जर (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    जा done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        जर (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            जा done;
        }
        जर (!SDL_WriteU32LE(dst, bfOffBits)) {
            जा done;
        }
        जर (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            जा done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        पर्यंत (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            जर (SDL_WriteIO(dst, bits, bw) != bw) {
                जा done;
            }
            जर (pad) {
                स्थिरांक Uint8 padbyte = 0;
                साठी (i = 0; i < pad; ++i) {
                    जर (!SDL_WriteU8(dst, padbyte)) {
                        जा done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        जर (new_offset < 0) {
            जा done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        जर (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            जा done;
        }
        जर (!SDL_WriteU32LE(dst, bfSize)) {
            जा done;
        }
        जर (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            जा done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    जर (closeio && dst) {
        जर (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    जर (was_error) {
        परत false;
    }
    परत true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    जर (!InitBMPSaveState(&state, surface)) {
        परत false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        जा done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    परत result;
}

bool SDL_SaveBMP(SDL_Surface *surface, स्थिरांक अक्षर *file)
{
    BMPSaveState state;
    जर (!InitBMPSaveState(&state, surface)) {
        परत false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    जर (!stream) {
        परत false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    परत result;
}

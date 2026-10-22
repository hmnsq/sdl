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
#ضمن "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#ضمن "SDL_pixels_c.h"
#ضمن "SDL_surface_c.h"

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

ساكن bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, صحيح isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    صحيح pitch = surface->pitch;
    صحيح height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *end = start + (height * pitch);
    Uint8 *bits = end - pitch, *spot;
    صحيح ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ثابت صحيح pixels_per_byte = (isRle8 ? 1 : 2);

#define COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    אם (spot >= start && spot < end) \
        *spot = (x)

    עבור (;;) {
        אם (!SDL_ReadU8(src, &ch)) {
            החזר false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        אם (ch) {
            Uint8 pixelvalue;
            אם (!SDL_ReadU8(src, &pixelvalue)) {
                החזר false;
            }
            صحيح ich = (صحيح) ch;
            עשה {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } כלעוד (ich > 0);
        } אחרת {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            אם (!SDL_ReadU8(src, &ch)) {
                החזר false;
            }
            بدل (ch) {
            حالة 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                اكسر;
            حالة 1:               // end of bitmap
                החזר true; // success!
            حالة 2:               // delta
                אם (!SDL_ReadU8(src, &ch)) {
                    החזר false;
                }
                ofs += ch / pixels_per_byte;
                אם (ch & pixels_per_byte) {
                    ofs++;
                }
                אם (!SDL_ReadU8(src, &ch)) {
                    החזר false;
                }
                bits -= (ch * pitch);
                اكسر;
            افتراضي: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                אם (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } אחרת {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                صحيح ich = (صحيح) ch;
                עשה {
                    Uint8 pixelvalue;
                    אם (!SDL_ReadU8(src, &pixelvalue)) {
                        החזר false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } כלעוד (ich > 0);

                // pad at even boundary
                אם (needsPad && !SDL_ReadU8(src, &ch)) {
                    החזר false;
                }
                اكسر;
            }
        }
    }
}

ساكن فراغ CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#אם SDL_BYTEORDER == SDL_BIG_ENDIAN
    صحيح alphaChannelOffset = 0;
#אחרת
    صحيح alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    כלעוד (alpha < end) {
        אם (*alpha != 0) {
            hasAlpha = true;
            اكسر;
        }
        alpha += 4;
    }

    אם (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        כלעוד (alpha < end) {
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
    אם (start >= 0) {
        אם (SDL_ReadIO(src, magic, حجم(magic)) == حجم(magic)) {
            אם (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    החזר is_BMP;
}

SDL_Surface *SDL_LoadBMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset = 0;
    صحيح i, pad;
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
    surface = عدم;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        اذهب done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    אם (fp_offset < 0) {
        اذهب done;
    }
    SDL_ClearError();
    אם (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        اذهب done;
    }
    אם (!SDL_ReadU16LE(src, عدم /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, عدم /* bfSize */) ||
        !SDL_ReadU16LE(src, عدم /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, عدم /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        اذهب done;
    }

    // Read the Win32 BITMAPINFOHEADER
    אם (!SDL_ReadU32LE(src, &biSize)) {
        اذهب done;
    }
    אם (biSize == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        אם (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, عدم /* biPlanes */) ||
            !SDL_ReadU16LE(src, &biBitCount)) {
            اذهب done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } אחרת אם (biSize >= 40) { // some version of BITMAPINFOHEADER
        Uint32 headerSize;
        אם (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, عدم /* biPlanes */) ||
            !SDL_ReadU16LE(src, &biBitCount) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, عدم /* biSizeImage */) ||
            !SDL_ReadU32LE(src, عدم /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, عدم /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, عدم /* biClrImportant */)) {
            اذهب done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        אם (biSize != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            אם (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                אם (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    اذهب done;
                }

                // ...v3 adds an alpha mask.
                אם (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    אם (!SDL_ReadU32LE(src, &Amask)) {
                        اذهب done;
                    }
                }
            } אחרת {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                אם (biSize >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    אם (!SDL_ReadU32LE(src, عدم /* Rmask */) ||
                        !SDL_ReadU32LE(src, عدم /* Gmask */) ||
                        !SDL_ReadU32LE(src, عدم /* Bmask */)) {
                        اذهب done;
                    }
                }
                אם (biSize >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    אם (!SDL_ReadU32LE(src, عدم /* Amask */)) {
                        اذهب done;
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
        אם (biSize > headerSize) {
            אם (SDL_SeekIO(src, (biSize - headerSize), SDL_IO_SEEK_CUR) < 0) {
                اذهب done;
            }
        }
    }
    אם (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        اذهب done;
    }
    אם (biHeight < 0) {
        topDown = true;
        biHeight = -biHeight;
    } אחרת {
        topDown = false;
    }

    // Check for read error
    אם (SDL_strcmp(SDL_GetError(), "") != 0) {
        اذهب done;
    }

    // Reject invalid bit depths
    بدل (biBitCount) {
    حالة 0:
    حالة 3:
    حالة 5:
    حالة 6:
    حالة 7:
        SDL_SetError("%u bpp BMP images are not supported", biBitCount);
        اذهب done;
    افتراضي:
        اكسر;
    }

    // RLE4 and RLE8 BMP compression is supported
    بدل (biCompression) {
    حالة BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        بدل (biBitCount) {
        حالة 15:
        حالة 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            اكسر;
        حالة 24:
#אם SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#אחרת
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#endif
            اكسر;
        حالة 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            اكسر;
        افتراضي:
            اكسر;
        }
        اكسر;

    حالة BI_BITFIELDS:
        اكسر; // we handled this in the info header.

    افتراضي:
        اكسر;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(biBitCount, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        אם (!surface) {
            اذهب done;
        }
    }

    // Load the palette, if any
    אם (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        אם (!palette) {
            اذهب done;
        }

        אם (SDL_SeekIO(src, fp_offset + 14 + biSize, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            اذهب done;
        }

        אם (biBitCount >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            اذهب done;
        }

        אם (biClrUsed == 0) {
            biClrUsed = 1 << biBitCount;
        }

        אם (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << biBitCount; // try forcing it?
            אם (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                اذهب done;
            }
        }
        palette->ncolors = biClrUsed;

        אם (biSize == 12) {
            עבור (i = 0; i < palette->ncolors; ++i) {
                אם (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    اذهب done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } אחרת {
            עבור (i = 0; i < palette->ncolors; ++i) {
                אם (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    اذهب done;
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
    אם (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        اذهب done;
    }
    אם ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        אם (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            اذهب done;
        }

        // Success!
        was_error = false;
        اذهب done;
    }
    top = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    אם (topDown) {
        bits = top;
    } אחרת {
        bits = end - surface->pitch;
    }
    כלעוד (bits >= top && bits < end) {
        אם (SDL_ReadIO(src, bits, surface->pitch) != (size_t)surface->pitch) {
            اذهب done;
        }
        אם (biBitCount == 8 && surface->palette && biClrUsed < (1u << biBitCount)) {
            עבור (i = 0; i < surface->w; ++i) {
                אם (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    اذهب done;
                }
            }
        }
#אם SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        بدل (biBitCount) {
        حالة 15:
        حالة 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            עבור (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            اكسر;
        }

        حالة 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            עבור (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            اكسر;
        }
        }
#endif

        // Skip padding bytes, ugh
        אם (pad) {
            Uint8 padbyte;
            עבור (i = 0; i < pad; ++i) {
                אם (!SDL_ReadU8(src, &padbyte)) {
                    اذهب done;
                }
            }
        }
        אם (topDown) {
            bits += surface->pitch;
        } אחרת {
            bits -= surface->pitch;
        }
    }
    אם (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    אם (was_error) {
        אם (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = عدم;
    }
    אם (closeio && src) {
        SDL_CloseIO(src);
    }
    החזר surface;
}

تعريفنوع بنية {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

ساكن فراغ FreeBMPSaveState(BMPSaveState *state)
{
    אם (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

ساكن bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = عدم;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        החזר SDL_InvalidParamError("surface");
    }

#ifdef SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    אם (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#endif // SAVE_32BIT_BMP

    אם (surface->palette && !state->save32bit) {
        אם (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } אחרת {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            اذهب error;
        }
    } אחרת אם ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } אחרת {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        אם (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } אחרת {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        אם (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (صحيح)SDL_BITSPERPIXEL(pixel_format));
            اذهب error;
        }
    }

    אם (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    החזר true;
error:
    FreeBMPSaveState(state);
    החזר false;
}

SDL_Surface *SDL_LoadBMP(ثابت حرف *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    אם (!stream) {
        החזר عدم;
    }
    החזר SDL_LoadBMP_IO(stream, true);
}
ساكن bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    صحيح i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    حرف magic[2] = { 'B', 'M' };
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

    אם (SDL_LockSurface(state->intermediate_surface)) {
        ثابت size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bfSize = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        אם (fp_offset < 0) {
            اذهب done;
        }
        אם (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bfSize) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            اذهب done;
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
        אם (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } אחרת {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        אם (state->save32bit && !state->saveLegacyBMP) {
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
        אם (!SDL_WriteU32LE(dst, biSize) ||
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
            اذهب done;
        }

        // Write the BMP info values
        אם (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            אם (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                اذهب done;
            }
            עבור (i = 0; i < 3 * 3; i++) {
                אם (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    اذهب done;
                }
            }
            אם (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                اذهب done;
            }
            // Version 5 values
            אם (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, bV5ProfileData) ||
                !SDL_WriteU32LE(dst, bV5ProfileSize) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                اذهب done;
            }
        }

        // Write the palette (in BGR color order)
        אם (state->intermediate_surface->palette) {
            SDL_Color *colors;
            صحيح ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            עבור (i = 0; i < ncolors; ++i) {
                אם (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    اذهب done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        אם (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            اذهب done;
        }
        אם (!SDL_WriteU32LE(dst, bfOffBits)) {
            اذهب done;
        }
        אם (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            اذهب done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        כלעוד (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            אם (SDL_WriteIO(dst, bits, bw) != bw) {
                اذهب done;
            }
            אם (pad) {
                ثابت Uint8 padbyte = 0;
                עבור (i = 0; i < pad; ++i) {
                    אם (!SDL_WriteU8(dst, padbyte)) {
                        اذهب done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        אם (new_offset < 0) {
            اذهب done;
        }
        bfSize = (Uint32)(new_offset - fp_offset);
        אם (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            اذهب done;
        }
        אם (!SDL_WriteU32LE(dst, bfSize)) {
            اذهب done;
        }
        אם (SDL_SeekIO(dst, fp_offset + bfSize, SDL_IO_SEEK_SET) < 0) {
            اذهب done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    אם (closeio && dst) {
        אם (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    אם (was_error) {
        החזר false;
    }
    החזר true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool result = true;
    BMPSaveState state;
    אם (!InitBMPSaveState(&state, surface)) {
        החזר false;
    }
    CHECK_PARAM(!dst) {
        result = SDL_InvalidParamError("dst");
        اذهب done;
    }
    result = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    החזר result;
}

bool SDL_SaveBMP(SDL_Surface *surface, ثابت حرف *file)
{
    BMPSaveState state;
    אם (!InitBMPSaveState(&state, surface)) {
        החזר false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    אם (!stream) {
        החזר false;
    }

    bool result = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    החזר result;
}

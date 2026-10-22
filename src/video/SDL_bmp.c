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
#समावेश "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#समावेश "SDL_pixels_c.h"
#समावेश "SDL_surface_c.h"

#घोषणा SAVE_32BIT_BMP

// Compression encodings for BMP files
#अगर_अघोषित BI_RGB
#घोषणा BI_RGB       0
#घोषणा BI_RLE8      1
#घोषणा BI_RLE4      2
#घोषणा BI_BITFIELDS 3
#पूर्ण_अगर

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#अगर_अघोषित LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#घोषणा LCS_WINDOWS_COLOR_SPACE 0x57696E20
#पूर्ण_अगर

#अगर_अघोषित LCS_sRGB
// 0x73524742 == "sRGB"
#घोषणा LCS_sRGB 0x73524742
#पूर्ण_अगर

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#अगर_अघोषित LCS_GM_GRAPHICS
#घोषणा LCS_GM_GRAPHICS 0x00000002
#पूर्ण_अगर

अटल bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, पूर्णांक isRle8)
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
    स्थिर पूर्णांक pixels_per_byte = (isRle8 ? 1 : 2);

#घोषणा COPY_PIXEL(x)                \
    spot = &bits[ofs++];             \
    अगर (spot >= start && spot < end) \
        *spot = (x)

    क्रम (;;) {
        अगर (!SDL_ReadU8(src, &ch)) {
            वापस false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        अगर (ch) {
            Uint8 pixelvalue;
            अगर (!SDL_ReadU8(src, &pixelvalue)) {
                वापस false;
            }
            पूर्णांक ich = (पूर्णांक) ch;
            करो {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_per_byte;
            } जबतक (ich > 0);
        } अन्यथा {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            अगर (!SDL_ReadU8(src, &ch)) {
                वापस false;
            }
            चयन (ch) {
            हाल 0: // end of line
                ofs = 0;
                bits -= pitch; // go to previous
                अवरोध;
            हाल 1:               // end of bitmap
                वापस true; // success!
            हाल 2:               // delta
                अगर (!SDL_ReadU8(src, &ch)) {
                    वापस false;
                }
                ofs += ch / pixels_per_byte;
                अगर (ch & pixels_per_byte) {
                    ofs++;
                }
                अगर (!SDL_ReadU8(src, &ch)) {
                    वापस false;
                }
                bits -= (ch * pitch);
                अवरोध;
            शेष: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                अगर (pixels_per_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } अन्यथा {
                    needsPad = (((ch + (pixels_per_byte-1)) / pixels_per_byte) & (pixels_per_byte-1)) != 0;
                }

                पूर्णांक ich = (पूर्णांक) ch;
                करो {
                    Uint8 pixelvalue;
                    अगर (!SDL_ReadU8(src, &pixelvalue)) {
                        वापस false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_per_byte;
                } जबतक (ich > 0);

                // pad at even boundary
                अगर (needsPad && !SDL_ReadU8(src, &ch)) {
                    वापस false;
                }
                अवरोध;
            }
        }
    }
}

अटल व्योम CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#अगर SDL_BYTEORDER == SDL_BIG_ENDIAN
    पूर्णांक alphaChannelOffset = 0;
#अन्यथा
    पूर्णांक alphaChannelOffset = 3;
#पूर्ण_अगर
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
    Uint8 *end = alpha + surface->h * surface->pitch;

    जबतक (alpha < end) {
        अगर (*alpha != 0) {
            hasAlpha = true;
            अवरोध;
        }
        alpha += 4;
    }

    अगर (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alphaChannelOffset;
        जबतक (alpha < end) {
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
    अगर (start >= 0) {
        अगर (SDL_ReadIO(src, magic, माप(magic)) == माप(magic)) {
            अगर (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, start, SDL_IO_SEEK_SET);
    }

    वापस is_BMP;
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
    Uint32 bi_आकार;
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
    surface = शून्य;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        जाओ done;
    }

    // Read in the BMP file header
    fp_offset = SDL_TellIO(src);
    अगर (fp_offset < 0) {
        जाओ done;
    }
    SDL_ClearError();
    अगर (!SDL_IsBMP(src)) {
        SDL_SetError("File is not a Windows BMP file");
        जाओ done;
    }
    अगर (!SDL_ReadU16LE(src, शून्य /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, शून्य /* bfSize */) ||
        !SDL_ReadU16LE(src, शून्य /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, शून्य /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bfOffBits)) {
        जाओ done;
    }

    // Read the Win32 BITMAPINFOHEADER
    अगर (!SDL_ReadU32LE(src, &bi_आकार)) {
        जाओ done;
    }
    अगर (bi_आकार == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        अगर (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, शून्य /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_गिनती)) {
            जाओ done;
        }
        biWidth = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        biClrUsed = 0;
        // biClrImportant = 0;
    } अन्यथा अगर (bi_आकार >= 40) { // some version of BITMAPINFOHEADER
        Uint32 header_आकार;
        अगर (!SDL_ReadS32LE(src, &biWidth) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, शून्य /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_गिनती) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, शून्य /* biSizeImage */) ||
            !SDL_ReadU32LE(src, शून्य /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, शून्य /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &biClrUsed) ||
            !SDL_ReadU32LE(src, शून्य /* biClrImportant */)) {
            जाओ done;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        अगर (bi_आकार != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            अगर (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                अगर (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    जाओ done;
                }

                // ...v3 adds an alpha mask.
                अगर (bi_आकार >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    haveAlphaMask = true;
                    अगर (!SDL_ReadU32LE(src, &Amask)) {
                        जाओ done;
                    }
                }
            } अन्यथा {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                अगर (bi_आकार >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    अगर (!SDL_ReadU32LE(src, शून्य /* Rmask */) ||
                        !SDL_ReadU32LE(src, शून्य /* Gmask */) ||
                        !SDL_ReadU32LE(src, शून्य /* Bmask */)) {
                        जाओ done;
                    }
                }
                अगर (bi_आकार >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    अगर (!SDL_ReadU32LE(src, शून्य /* Amask */)) {
                        जाओ done;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        header_आकार = (Uint32)(SDL_TellIO(src) - (fp_offset + 14));
        अगर (bi_आकार > header_आकार) {
            अगर (SDL_SeekIO(src, (bi_आकार - header_आकार), SDL_IO_SEEK_CUR) < 0) {
                जाओ done;
            }
        }
    }
    अगर (biWidth <= 0 || biHeight == 0) {
        SDL_SetError("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", biWidth, biHeight);
        जाओ done;
    }
    अगर (biHeight < 0) {
        शीर्ष_Down = true;
        biHeight = -biHeight;
    } अन्यथा {
        शीर्ष_Down = false;
    }

    // Check for read error
    अगर (SDL_strcmp(SDL_GetError(), "") != 0) {
        जाओ done;
    }

    // Reject invalid bit depths
    चयन (bi_Bit_गिनती) {
    हाल 0:
    हाल 3:
    हाल 5:
    हाल 6:
    हाल 7:
        SDL_SetError("%u bpp BMP images are not supported", bi_Bit_गिनती);
        जाओ done;
    शेष:
        अवरोध;
    }

    // RLE4 and RLE8 BMP compression is supported
    चयन (biCompression) {
    हाल BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!haveAlphaMask);
        // Default values for the BMP format
        चयन (bi_Bit_गिनती) {
        हाल 15:
        हाल 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            अवरोध;
        हाल 24:
#अगर SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#अन्यथा
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#पूर्ण_अगर
            अवरोध;
        हाल 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            अवरोध;
        शेष:
            अवरोध;
        }
        अवरोध;

    हाल BI_BITFIELDS:
        अवरोध; // we handled this in the info header.

    शेष:
        अवरोध;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_Bit_गिनती, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(biWidth, biHeight, format);

        अगर (!surface) {
            जाओ done;
        }
    }

    // Load the palette, if any
    अगर (SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        अगर (!palette) {
            जाओ done;
        }

        अगर (SDL_SeekIO(src, fp_offset + 14 + bi_आकार, SDL_IO_SEEK_SET) < 0) {
            SDL_SetError("Error seeking in datastream");
            जाओ done;
        }

        अगर (bi_Bit_गिनती >= 32) { // we shift biClrUsed by this value later.
            SDL_SetError("Unsupported or incorrect biBitCount field");
            जाओ done;
        }

        अगर (biClrUsed == 0) {
            biClrUsed = 1 << bi_Bit_गिनती;
        }

        अगर (biClrUsed > (Uint32)palette->ncolors) {
            biClrUsed = 1 << bi_Bit_गिनती; // try forcing it?
            अगर (biClrUsed > (Uint32)palette->ncolors) {
                SDL_SetError("Unsupported or incorrect biClrUsed field");
                जाओ done;
            }
        }
        palette->ncolors = biClrUsed;

        अगर (bi_आकार == 12) {
            क्रम (i = 0; i < palette->ncolors; ++i) {
                अगर (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    जाओ done;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } अन्यथा {
            क्रम (i = 0; i < palette->ncolors; ++i) {
                अगर (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    जाओ done;
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
    अगर (SDL_SeekIO(src, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
        SDL_SetError("Error seeking in datastream");
        जाओ done;
    }
    अगर ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        अगर (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_SetError("Error reading from datastream");
            जाओ done;
        }

        // Success!
        was_error = false;
        जाओ done;
    }
    शीर्ष = (Uint8 *)surface->pixels;
    end = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    अगर (शीर्ष_Down) {
        bits = शीर्ष;
    } अन्यथा {
        bits = end - surface->pitch;
    }
    जबतक (bits >= शीर्ष && bits < end) {
        अगर (SDL_ReadIO(src, bits, surface->pitch) != (माप_प्रकार)surface->pitch) {
            जाओ done;
        }
        अगर (bi_Bit_गिनती == 8 && surface->palette && biClrUsed < (1u << bi_Bit_गिनती)) {
            क्रम (i = 0; i < surface->w; ++i) {
                अगर (bits[i] >= biClrUsed) {
                    SDL_SetError("A BMP image contains a pixel with a color out of the palette");
                    जाओ done;
                }
            }
        }
#अगर SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        चयन (bi_Bit_गिनती) {
        हाल 15:
        हाल 16:
        {
            Uint16 *pix = (Uint16 *)bits;
            क्रम (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            अवरोध;
        }

        हाल 32:
        {
            Uint32 *pix = (Uint32 *)bits;
            क्रम (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            अवरोध;
        }
        }
#पूर्ण_अगर

        // Skip padding bytes, ugh
        अगर (pad) {
            Uint8 padbyte;
            क्रम (i = 0; i < pad; ++i) {
                अगर (!SDL_ReadU8(src, &padbyte)) {
                    जाओ done;
                }
            }
        }
        अगर (शीर्ष_Down) {
            bits += surface->pitch;
        } अन्यथा {
            bits -= surface->pitch;
        }
    }
    अगर (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

done:
    अगर (was_error) {
        अगर (src) {
            SDL_SeekIO(src, fp_offset, SDL_IO_SEEK_SET);
        }
        SDL_DestroySurface(surface);
        surface = शून्य;
    }
    अगर (closeio && src) {
        SDL_CloseIO(src);
    }
    वापस surface;
}

प्रकार काष्ठा {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

अटल व्योम FreeBMPSaveState(BMPSaveState *state)
{
    अगर (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

अटल bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = शून्य;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        वापस SDL_InvalidParamError("surface");
    }

#अगर_घोषित SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    अगर (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#पूर्ण_अगर // SAVE_32BIT_BMP

    अगर (surface->palette && !state->save32bit) {
        अगर (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } अन्यथा {
            SDL_SetError("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            जाओ error;
        }
    } अन्यथा अगर ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } अन्यथा {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        अगर (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } अन्यथा {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        अगर (!state->intermediate_surface) {
            SDL_SetError("Couldn't convert image to %d bpp",
                         (पूर्णांक)SDL_BITSPERPIXEL(pixel_format));
            जाओ error;
        }
    }

    अगर (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    वापस true;
error:
    FreeBMPSaveState(state);
    वापस false;
}

SDL_Surface *SDL_LoadBMP(स्थिर अक्षर *file)
{
    SDL_IOStream *stream = SDL_IOFromFile(file, "rb");
    अगर (!stream) {
        वापस शून्य;
    }
    वापस SDL_LoadBMP_IO(stream, true);
}
अटल bool SDL_SaveBMP_IO_Internal(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_offset, new_offset;
    पूर्णांक i, pad;
    Uint8 *bits;

    // The Win32 BMP file header (14 bytes)
    अक्षर magic[2] = { 'B', 'M' };
    Uint32 bf_आकार;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_आकार;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_गिनती;
    Uint32 biCompression;
    Uint32 bi_आकार_Image;
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
    Uint32 b_V5_Profile_तथ्य = 0;
    Uint32 b_V5_Profile_आकार = 0;
    Uint32 bV5Reserved = 0;

    अगर (SDL_LockSurface(state->intermediate_surface)) {
        स्थिर माप_प्रकार bw = state->intermediate_surface->w * state->intermediate_surface->fmt->bytes_per_pixel;

        // Set the BMP file header values
        bf_आकार = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bfOffBits = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_offset = SDL_TellIO(dst);
        अगर (fp_offset < 0) {
            जाओ done;
        }
        अगर (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_आकार) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bfOffBits)) {
            जाओ done;
        }

        // Set the BMP info values
        bi_आकार = 40;
        biWidth = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_गिनती = state->intermediate_surface->fmt->bits_per_pixel;
        biCompression = BI_RGB;
        bi_आकार_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        अगर (state->intermediate_surface->palette) {
            biClrUsed = state->intermediate_surface->palette->ncolors;
        } अन्यथा {
            biClrUsed = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        अगर (state->save32bit && !state->saveLegacyBMP) {
            bi_आकार = 124;
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
            b_V5_Profile_तथ्य = 0;
            b_V5_Profile_आकार = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        अगर (!SDL_WriteU32LE(dst, bi_आकार) ||
            !SDL_WriteS32LE(dst, biWidth) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_गिनती) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_आकार_Image) ||
            !SDL_WriteU32LE(dst, biXPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biYPelsPerMeter) ||
            !SDL_WriteU32LE(dst, biClrUsed) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            जाओ done;
        }

        // Write the BMP info values
        अगर (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            अगर (!SDL_WriteU32LE(dst, bV4RedMask) ||
                !SDL_WriteU32LE(dst, bV4GreenMask) ||
                !SDL_WriteU32LE(dst, bV4BlueMask) ||
                !SDL_WriteU32LE(dst, bV4AlphaMask) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                जाओ done;
            }
            क्रम (i = 0; i < 3 * 3; i++) {
                अगर (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    जाओ done;
                }
            }
            अगर (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                जाओ done;
            }
            // Version 5 values
            अगर (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_तथ्य) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_आकार) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                जाओ done;
            }
        }

        // Write the palette (in BGR color order)
        अगर (state->intermediate_surface->palette) {
            SDL_Color *colors;
            पूर्णांक ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            क्रम (i = 0; i < ncolors; ++i) {
                अगर (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    जाओ done;
                }
            }
        }

        // Write the bitmap offset
        bfOffBits = (Uint32)(SDL_TellIO(dst) - fp_offset);
        अगर (SDL_SeekIO(dst, fp_offset + 10, SDL_IO_SEEK_SET) < 0) {
            जाओ done;
        }
        अगर (!SDL_WriteU32LE(dst, bfOffBits)) {
            जाओ done;
        }
        अगर (SDL_SeekIO(dst, fp_offset + bfOffBits, SDL_IO_SEEK_SET) < 0) {
            जाओ done;
        }

        // Write the bitmap image upside down
        bits = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        जबतक (bits > (Uint8 *)state->intermediate_surface->pixels) {
            bits -= state->intermediate_surface->pitch;
            अगर (SDL_WriteIO(dst, bits, bw) != bw) {
                जाओ done;
            }
            अगर (pad) {
                स्थिर Uint8 padbyte = 0;
                क्रम (i = 0; i < pad; ++i) {
                    अगर (!SDL_WriteU8(dst, padbyte)) {
                        जाओ done;
                    }
                }
            }
        }

        // Write the BMP file size
        new_offset = SDL_TellIO(dst);
        अगर (new_offset < 0) {
            जाओ done;
        }
        bf_आकार = (Uint32)(new_offset - fp_offset);
        अगर (SDL_SeekIO(dst, fp_offset + 2, SDL_IO_SEEK_SET) < 0) {
            जाओ done;
        }
        अगर (!SDL_WriteU32LE(dst, bf_आकार)) {
            जाओ done;
        }
        अगर (SDL_SeekIO(dst, fp_offset + bf_आकार, SDL_IO_SEEK_SET) < 0) {
            जाओ done;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

done:
    अगर (closeio && dst) {
        अगर (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    अगर (was_error) {
        वापस false;
    }
    वापस true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool परिणाम = true;
    BMPSaveState state;
    अगर (!InitBMPSaveState(&state, surface)) {
        वापस false;
    }
    CHECK_PARAM(!dst) {
        परिणाम = SDL_InvalidParamError("dst");
        जाओ done;
    }
    परिणाम = SDL_SaveBMP_IO_Internal(&state, dst, closeio);
done:
    FreeBMPSaveState(&state);
    वापस परिणाम;
}

bool SDL_SaveBMP(SDL_Surface *surface, स्थिर अक्षर *file)
{
    BMPSaveState state;
    अगर (!InitBMPSaveState(&state, surface)) {
        वापस false;
    }

    SDL_IOStream *stream = SDL_IOFromFile(file, "wb");
    अगर (!stream) {
        वापस false;
    }

    bool परिणाम = SDL_SaveBMP_IO_Internal(&state, stream, true);
    FreeBMPSaveState(&state);
    वापस परिणाम;
}

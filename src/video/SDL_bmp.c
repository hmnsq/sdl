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

#परिभाषय SAVE_32BIT_BMP

// Compression encodings for BMP files
#यदि_अपरिभाषितम् BI_RGB
#परिभाषय BI_RGB       0
#परिभाषय BI_RLE8      1
#परिभाषय BI_RLE4      2
#परिभाषय BI_BITFIELDS 3
#यदि_अन्तः

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#यदि_अपरिभाषितम् LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#परिभाषय LCS_WINDOWS_COLOR_SPACE 0x57696E20
#यदि_अन्तः

#यदि_अपरिभाषितम् LCS_sRGB
// 0x73524742 == "sRGB"
#परिभाषय LCS_sRGB 0x73524742
#यदि_अन्तः

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#यदि_अपरिभाषितम् LCS_GM_GRAPHICS
#परिभाषय LCS_GM_GRAPHICS 0x00000002
#यदि_अन्तः

स्थिर bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, पूर्णाङ्क isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    पूर्णाङ्क pitch = surface->pitch;
    पूर्णाङ्क height = surface->h;
    Uint8 *start = (Uint8 *)surface->pixels;
    Uint8 *अन्तः = start + (height * pitch);
    Uint8 *द्वयङ्काः = अन्तः - pitch, *spot;
    पूर्णाङ्क ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    ध्रुव पूर्णाङ्क pixels_प्रत्येकम्_byte = (isRle8 ? 1 : 2);

#परिभाषय COPY_PIXEL(x)                \
    spot = &द्वयङ्काः[ofs++];             \
    यदि (spot >= start && spot < अन्तः) \
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
                ich -= pixels_प्रत्येकम्_byte;
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
                द्वयङ्काः -= pitch; // go to previous
                भङ्ग;
            पक्ष 1:               // end of bitmap
                प्रत्यागम true; // success!
            पक्ष 2:               // delta
                यदि (!SDL_ReadU8(src, &ch)) {
                    प्रत्यागम false;
                }
                ofs += ch / pixels_प्रत्येकम्_byte;
                यदि (ch & pixels_प्रत्येकम्_byte) {
                    ofs++;
                }
                यदि (!SDL_ReadU8(src, &ch)) {
                    प्रत्यागम false;
                }
                द्वयङ्काः -= (ch * pitch);
                भङ्ग;
            स्वभाव: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                यदि (pixels_प्रत्येकम्_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } अन्यथा {
                    needsPad = (((ch + (pixels_प्रत्येकम्_byte-1)) / pixels_प्रत्येकम्_byte) & (pixels_प्रत्येकम्_byte-1)) != 0;
                }

                पूर्णाङ्क ich = (पूर्णाङ्क) ch;
                कुरु {
                    Uint8 pixelvalue;
                    यदि (!SDL_ReadU8(src, &pixelvalue)) {
                        प्रत्यागम false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_प्रत्येकम्_byte;
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
    पूर्णाङ्क alpha_Channel_विस्थापनम् = 0;
#अन्यथा
    पूर्णाङ्क alpha_Channel_विस्थापनम् = 3;
#यदि_अन्तः
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_विस्थापनम्;
    Uint8 *अन्तः = alpha + surface->h * surface->pitch;

    यावत् (alpha < अन्तः) {
        यदि (*alpha != 0) {
            hasAlpha = true;
            भङ्ग;
        }
        alpha += 4;
    }

    यदि (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_विस्थापनम्;
        यावत् (alpha < अन्तः) {
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
        SDL_SeekIO(src, start, SDL_IO_SEEK_समुच्चयः);
    }

    प्रत्यागम is_BMP;
}

SDL_Surface *SDL_आरोपय_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_विस्थापनम् = 0;
    पूर्णाङ्क i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *द्वयङ्काः;
    Uint8 *शिखरम्, *अन्तः;
    bool शिखरम्_अधस्तात्;
    bool haveRGBMasks = false;
    bool have_Alpha_आवरणम् = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bf_Off_द्वयङ्काः;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_आकार;
    Sint32 bi_विस्तारः = 0;
    Sint32 biHeight = 0;
    // Uint16 biPlanes;
    Uint16 bi_Bit_गणनम् = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_प्रयुक्तम् = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = रिक्त;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        गच्छ समाप्तम्;
    }

    // Read in the BMP file header
    fp_विस्थापनम् = SDL_TellIO(src);
    यदि (fp_विस्थापनम् < 0) {
        गच्छ समाप्तम्;
    }
    SDL_ClearError();
    यदि (!SDL_IsBMP(src)) {
        SDL_समुच्चयः_Error("File is not a Windows BMP file");
        गच्छ समाप्तम्;
    }
    यदि (!SDL_ReadU16LE(src, रिक्त /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, रिक्त /* bfSize */) ||
        !SDL_ReadU16LE(src, रिक्त /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, रिक्त /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_द्वयङ्काः)) {
        गच्छ समाप्तम्;
    }

    // Read the Win32 BITMAPINFOHEADER
    यदि (!SDL_ReadU32LE(src, &bi_आकार)) {
        गच्छ समाप्तम्;
    }
    यदि (bi_आकार == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        यदि (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, रिक्त /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_गणनम्)) {
            गच्छ समाप्तम्;
        }
        bi_विस्तारः = biWidth16;
        biHeight = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_प्रयुक्तम् = 0;
        // biClrImportant = 0;
    } अन्यथा यदि (bi_आकार >= 40) { // some version of BITMAPINFOHEADER
        Uint32 शीर्षकम्_आकार;
        यदि (!SDL_ReadS32LE(src, &bi_विस्तारः) ||
            !SDL_ReadS32LE(src, &biHeight) ||
            !SDL_ReadU16LE(src, रिक्त /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_Bit_गणनम्) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, रिक्त /* biSizeImage */) ||
            !SDL_ReadU32LE(src, रिक्त /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, रिक्त /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_प्रयुक्तम्) ||
            !SDL_ReadU32LE(src, रिक्त /* biClrImportant */)) {
            गच्छ समाप्तम्;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        यदि (bi_आकार != 64) {
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
                    गच्छ समाप्तम्;
                }

                // ...v3 adds an alpha mask.
                यदि (bi_आकार >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_आवरणम् = true;
                    यदि (!SDL_ReadU32LE(src, &Amask)) {
                        गच्छ समाप्तम्;
                    }
                }
            } अन्यथा {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                यदि (bi_आकार >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    यदि (!SDL_ReadU32LE(src, रिक्त /* Rmask */) ||
                        !SDL_ReadU32LE(src, रिक्त /* Gmask */) ||
                        !SDL_ReadU32LE(src, रिक्त /* Bmask */)) {
                        गच्छ समाप्तम्;
                    }
                }
                यदि (bi_आकार >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    यदि (!SDL_ReadU32LE(src, रिक्त /* Amask */)) {
                        गच्छ समाप्तम्;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        शीर्षकम्_आकार = (Uint32)(SDL_TellIO(src) - (fp_विस्थापनम् + 14));
        यदि (bi_आकार > शीर्षकम्_आकार) {
            यदि (SDL_SeekIO(src, (bi_आकार - शीर्षकम्_आकार), SDL_IO_SEEK_CUR) < 0) {
                गच्छ समाप्तम्;
            }
        }
    }
    यदि (bi_विस्तारः <= 0 || biHeight == 0) {
        SDL_समुच्चयः_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_विस्तारः, biHeight);
        गच्छ समाप्तम्;
    }
    यदि (biHeight < 0) {
        शिखरम्_अधस्तात् = true;
        biHeight = -biHeight;
    } अन्यथा {
        शिखरम्_अधस्तात् = false;
    }

    // Check for read error
    यदि (SDL_strcmp(SDL_GetError(), "") != 0) {
        गच्छ समाप्तम्;
    }

    // Reject invalid bit depths
    विकल्प (bi_Bit_गणनम्) {
    पक्ष 0:
    पक्ष 3:
    पक्ष 5:
    पक्ष 6:
    पक्ष 7:
        SDL_समुच्चयः_Error("%u bpp BMP images are not supported", bi_Bit_गणनम्);
        गच्छ समाप्तम्;
    स्वभाव:
        भङ्ग;
    }

    // RLE4 and RLE8 BMP compression is supported
    विकल्प (biCompression) {
    पक्ष BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!have_Alpha_आवरणम्);
        // Default values for the BMP format
        विकल्प (bi_Bit_गणनम्) {
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
#यदि_अन्तः
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
        format = SDL_GetPixelFormatForMasks(bi_Bit_गणनम्, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_विस्तारः, biHeight, format);

        यदि (!surface) {
            गच्छ समाप्तम्;
        }
    }

    // Load the palette, if any
    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        यदि (!palette) {
            गच्छ समाप्तम्;
        }

        यदि (SDL_SeekIO(src, fp_विस्थापनम् + 14 + bi_आकार, SDL_IO_SEEK_समुच्चयः) < 0) {
            SDL_समुच्चयः_Error("Error seeking in datastream");
            गच्छ समाप्तम्;
        }

        यदि (bi_Bit_गणनम् >= 32) { // we shift biClrUsed by this value later.
            SDL_समुच्चयः_Error("Unsupported or incorrect biBitCount field");
            गच्छ समाप्तम्;
        }

        यदि (bi_Clr_प्रयुक्तम् == 0) {
            bi_Clr_प्रयुक्तम् = 1 << bi_Bit_गणनम्;
        }

        यदि (bi_Clr_प्रयुक्तम् > (Uint32)palette->ncolors) {
            bi_Clr_प्रयुक्तम् = 1 << bi_Bit_गणनम्; // try forcing it?
            यदि (bi_Clr_प्रयुक्तम् > (Uint32)palette->ncolors) {
                SDL_समुच्चयः_Error("Unsupported or incorrect biClrUsed field");
                गच्छ समाप्तम्;
            }
        }
        palette->ncolors = bi_Clr_प्रयुक्तम्;

        यदि (bi_आकार == 12) {
            प्रति (i = 0; i < palette->ncolors; ++i) {
                यदि (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    गच्छ समाप्तम्;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } अन्यथा {
            प्रति (i = 0; i < palette->ncolors; ++i) {
                यदि (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    गच्छ समाप्तम्;
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
    यदि (SDL_SeekIO(src, fp_विस्थापनम् + bf_Off_द्वयङ्काः, SDL_IO_SEEK_समुच्चयः) < 0) {
        SDL_समुच्चयः_Error("Error seeking in datastream");
        गच्छ समाप्तम्;
    }
    यदि ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        यदि (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_समुच्चयः_Error("Error reading from datastream");
            गच्छ समाप्तम्;
        }

        // Success!
        was_error = false;
        गच्छ समाप्तम्;
    }
    शिखरम् = (Uint8 *)surface->pixels;
    अन्तः = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    यदि (शिखरम्_अधस्तात्) {
        द्वयङ्काः = शिखरम्;
    } अन्यथा {
        द्वयङ्काः = अन्तः - surface->pitch;
    }
    यावत् (द्वयङ्काः >= शिखरम् && द्वयङ्काः < अन्तः) {
        यदि (SDL_ReadIO(src, द्वयङ्काः, surface->pitch) != (size_t)surface->pitch) {
            गच्छ समाप्तम्;
        }
        यदि (bi_Bit_गणनम् == 8 && surface->palette && bi_Clr_प्रयुक्तम् < (1u << bi_Bit_गणनम्)) {
            प्रति (i = 0; i < surface->w; ++i) {
                यदि (द्वयङ्काः[i] >= bi_Clr_प्रयुक्तम्) {
                    SDL_समुच्चयः_Error("A BMP image contains a pixel with a color out of the palette");
                    गच्छ समाप्तम्;
                }
            }
        }
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        विकल्प (bi_Bit_गणनम्) {
        पक्ष 15:
        पक्ष 16:
        {
            Uint16 *pix = (Uint16 *)द्वयङ्काः;
            प्रति (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            भङ्ग;
        }

        पक्ष 32:
        {
            Uint32 *pix = (Uint32 *)द्वयङ्काः;
            प्रति (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            भङ्ग;
        }
        }
#यदि_अन्तः

        // Skip padding bytes, ugh
        यदि (pad) {
            Uint8 padbyte;
            प्रति (i = 0; i < pad; ++i) {
                यदि (!SDL_ReadU8(src, &padbyte)) {
                    गच्छ समाप्तम्;
                }
            }
        }
        यदि (शिखरम्_अधस्तात्) {
            द्वयङ्काः += surface->pitch;
        } अन्यथा {
            द्वयङ्काः -= surface->pitch;
        }
    }
    यदि (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

समाप्तम्:
    यदि (was_error) {
        यदि (src) {
            SDL_SeekIO(src, fp_विस्थापनम्, SDL_IO_SEEK_समुच्चयः);
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

#यदि_परिभाषितम् SAVE_32BIT_BMP
    // We can save alpha information in a 32-bit BMP
    यदि (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#यदि_अन्तः // SAVE_32BIT_BMP

    यदि (surface->palette && !state->save32bit) {
        यदि (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } अन्यथा {
            SDL_समुच्चयः_Error("%u bpp BMP files not supported",
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
            SDL_समुच्चयः_Error("Couldn't convert image to %d bpp",
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

SDL_Surface *SDL_आरोपय_BMP(ध्रुव वर्ण *file)
{
    SDL_IOStream *प्रवाहः = SDL_IOFromFile(file, "rb");
    यदि (!प्रवाहः) {
        प्रत्यागम रिक्त;
    }
    प्रत्यागम SDL_आरोपय_BMP_IO(प्रवाहः, true);
}
स्थिर bool SDL_Save_BMP_IO_आन्तरिकम्(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_विस्थापनम्, new_विस्थापनम्;
    पूर्णाङ्क i, pad;
    Uint8 *द्वयङ्काः;

    // The Win32 BMP file header (14 bytes)
    वर्ण magic[2] = { 'B', 'M' };
    Uint32 bf_आकार;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_द्वयङ्काः;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_आकार;
    Sint32 bi_विस्तारः;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 bi_Bit_गणनम्;
    Uint32 biCompression;
    Uint32 bi_आकार_Image;
    Sint32 bi_XPels_प्रत्येकम्_Meter;
    Sint32 bi_YPels_प्रत्येकम्_Meter;
    Uint32 bi_Clr_प्रयुक्तम्;
    Uint32 biClrImportant;

    // The additional header members from the Win32 BITMAPV4HEADER struct (108 bytes in total)
    Uint32 b_V4_Red_आवरणम् = 0;
    Uint32 b_V4_Green_आवरणम् = 0;
    Uint32 b_V4_Blue_आवरणम् = 0;
    Uint32 b_V4_Alpha_आवरणम् = 0;
    Uint32 bV4CSType = 0;
    Sint32 bV4Endpoints[3 * 3] = { 0 };
    Uint32 bV4GammaRed = 0;
    Uint32 bV4GammaGreen = 0;
    Uint32 bV4GammaBlue = 0;

    // The additional header members from the Win32 BITMAPV5HEADER struct (124 bytes in total)
    Uint32 bV5Intent = 0;
    Uint32 b_V5_Profile_दत्त = 0;
    Uint32 b_V5_Profile_आकार = 0;
    Uint32 bV5Reserved = 0;

    यदि (SDL_तालकम्_Surface(state->intermediate_surface)) {
        ध्रुव size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->अष्टकानि_प्रत्येकम्_pixel;

        // Set the BMP file header values
        bf_आकार = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_द्वयङ्काः = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_विस्थापनम् = SDL_TellIO(dst);
        यदि (fp_विस्थापनम् < 0) {
            गच्छ समाप्तम्;
        }
        यदि (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_आकार) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_द्वयङ्काः)) {
            गच्छ समाप्तम्;
        }

        // Set the BMP info values
        bi_आकार = 40;
        bi_विस्तारः = state->intermediate_surface->w;
        biHeight = state->intermediate_surface->h;
        biPlanes = 1;
        bi_Bit_गणनम् = state->intermediate_surface->fmt->द्वयङ्काः_प्रत्येकम्_pixel;
        biCompression = BI_RGB;
        bi_आकार_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_प्रत्येकम्_Meter = 0;
        bi_YPels_प्रत्येकम्_Meter = 0;
        यदि (state->intermediate_surface->palette) {
            bi_Clr_प्रयुक्तम् = state->intermediate_surface->palette->ncolors;
        } अन्यथा {
            bi_Clr_प्रयुक्तम् = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        यदि (state->save32bit && !state->saveLegacyBMP) {
            bi_आकार = 124;
            // Version 4 values
            biCompression = BI_BITFIELDS;
            // The BMP format is always little endian, these masks stay the same
            b_V4_Red_आवरणम् = 0x00ff0000;
            b_V4_Green_आवरणम् = 0x0000ff00;
            b_V4_Blue_आवरणम् = 0x000000ff;
            b_V4_Alpha_आवरणम् = 0xff000000;
            bV4CSType = LCS_sRGB;
            bV4GammaRed = 0;
            bV4GammaGreen = 0;
            bV4GammaBlue = 0;
            // Version 5 values
            bV5Intent = LCS_GM_GRAPHICS;
            b_V5_Profile_दत्त = 0;
            b_V5_Profile_आकार = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        यदि (!SDL_WriteU32LE(dst, bi_आकार) ||
            !SDL_WriteS32LE(dst, bi_विस्तारः) ||
            !SDL_WriteS32LE(dst, biHeight) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_Bit_गणनम्) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_आकार_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_प्रत्येकम्_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_प्रत्येकम्_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_प्रयुक्तम्) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            गच्छ समाप्तम्;
        }

        // Write the BMP info values
        यदि (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            यदि (!SDL_WriteU32LE(dst, b_V4_Red_आवरणम्) ||
                !SDL_WriteU32LE(dst, b_V4_Green_आवरणम्) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_आवरणम्) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_आवरणम्) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                गच्छ समाप्तम्;
            }
            प्रति (i = 0; i < 3 * 3; i++) {
                यदि (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    गच्छ समाप्तम्;
                }
            }
            यदि (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                गच्छ समाप्तम्;
            }
            // Version 5 values
            यदि (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_दत्त) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_आकार) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                गच्छ समाप्तम्;
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
                    गच्छ समाप्तम्;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_द्वयङ्काः = (Uint32)(SDL_TellIO(dst) - fp_विस्थापनम्);
        यदि (SDL_SeekIO(dst, fp_विस्थापनम् + 10, SDL_IO_SEEK_समुच्चयः) < 0) {
            गच्छ समाप्तम्;
        }
        यदि (!SDL_WriteU32LE(dst, bf_Off_द्वयङ्काः)) {
            गच्छ समाप्तम्;
        }
        यदि (SDL_SeekIO(dst, fp_विस्थापनम् + bf_Off_द्वयङ्काः, SDL_IO_SEEK_समुच्चयः) < 0) {
            गच्छ समाप्तम्;
        }

        // Write the bitmap image upside down
        द्वयङ्काः = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        यावत् (द्वयङ्काः > (Uint8 *)state->intermediate_surface->pixels) {
            द्वयङ्काः -= state->intermediate_surface->pitch;
            यदि (SDL_WriteIO(dst, द्वयङ्काः, bw) != bw) {
                गच्छ समाप्तम्;
            }
            यदि (pad) {
                ध्रुव Uint8 padbyte = 0;
                प्रति (i = 0; i < pad; ++i) {
                    यदि (!SDL_WriteU8(dst, padbyte)) {
                        गच्छ समाप्तम्;
                    }
                }
            }
        }

        // Write the BMP file size
        new_विस्थापनम् = SDL_TellIO(dst);
        यदि (new_विस्थापनम् < 0) {
            गच्छ समाप्तम्;
        }
        bf_आकार = (Uint32)(new_विस्थापनम् - fp_विस्थापनम्);
        यदि (SDL_SeekIO(dst, fp_विस्थापनम् + 2, SDL_IO_SEEK_समुच्चयः) < 0) {
            गच्छ समाप्तम्;
        }
        यदि (!SDL_WriteU32LE(dst, bf_आकार)) {
            गच्छ समाप्तम्;
        }
        यदि (SDL_SeekIO(dst, fp_विस्थापनम् + bf_आकार, SDL_IO_SEEK_समुच्चयः) < 0) {
            गच्छ समाप्तम्;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

समाप्तम्:
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
    bool परिणाम = true;
    BMPSaveState state;
    यदि (!InitBMPSaveState(&state, surface)) {
        प्रत्यागम false;
    }
    CHECK_PARAM(!dst) {
        परिणाम = SDL_InvalidParamError("dst");
        गच्छ समाप्तम्;
    }
    परिणाम = SDL_Save_BMP_IO_आन्तरिकम्(&state, dst, closeio);
समाप्तम्:
    FreeBMPSaveState(&state);
    प्रत्यागम परिणाम;
}

bool SDL_SaveBMP(SDL_Surface *surface, ध्रुव वर्ण *file)
{
    BMPSaveState state;
    यदि (!InitBMPSaveState(&state, surface)) {
        प्रत्यागम false;
    }

    SDL_IOStream *प्रवाहः = SDL_IOFromFile(file, "wb");
    यदि (!प्रवाहः) {
        प्रत्यागम false;
    }

    bool परिणाम = SDL_Save_BMP_IO_आन्तरिकम्(&state, प्रवाहः, true);
    FreeBMPSaveState(&state);
    प्रत्यागम परिणाम;
}

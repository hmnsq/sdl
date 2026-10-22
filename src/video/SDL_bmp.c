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
#అన్తర్భావ "SDL_internal.h"

/*
   Code to load and save surfaces in Windows BMP format.

   Why support BMP format?  Well, it's a native format for Windows, and
   most image processing programs can read and write it.  It would be nice
   to be able to have at least one image format that we can natively load
   and save, and since PNG is so complex that it would bloat the library,
   BMP is a good alternative.

   This code currently supports Win32 DIBs in uncompressed 8 and 24 bpp.
*/

#అన్తర్భావ "SDL_pixels_c.h"
#అన్తర్భావ "SDL_surface_c.h"

#నిర్వచించు SAVE_32_బిట్టు_BMP

// Compression encodings for BMP files
#నిర్వచితం_కాకపోతే BI_RGB
#నిర్వచించు BI_RGB       0
#నిర్వచించు BI_RLE8      1
#నిర్వచించు BI_RLE4      2
#నిర్వచించు BI_BITFIELDS 3
#అయితే_ముగింపు

// Logical color space values for BMP files
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/eb4bbd50-b3ce-4917-895c-be31f214797f
#నిర్వచితం_కాకపోతే LCS_WINDOWS_COLOR_SPACE
// 0x57696E20 == "Win "
#నిర్వచించు LCS_WINDOWS_COLOR_SPACE 0x57696E20
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే LCS_sRGB
// 0x73524742 == "sRGB"
#నిర్వచించు LCS_sRGB 0x73524742
#అయితే_ముగింపు

// Logical/physical color relationship
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/9fec0834-607d-427d-abd5-ab240fb0db38
#నిర్వచితం_కాకపోతే LCS_GM_GRAPHICS
#నిర్వచించు LCS_GM_GRAPHICS 0x00000002
#అయితే_ముగింపు

స్థిర bool readRlePixels(SDL_Surface *surface, SDL_IOStream *src, పూర్ణాంకం isRle8)
{
    /*
    | Sets the surface pixels from src.  A bmp image is upside down.
    */
    పూర్ణాంకం pitch = surface->pitch;
    పూర్ణాంకం ఎత్తు = surface->h;
    Uint8 *ప్రారంభం = (Uint8 *)surface->pixels;
    Uint8 *చివర = ప్రారంభం + (ఎత్తు * pitch);
    Uint8 *బిట్లు = చివర - pitch, *spot;
    పూర్ణాంకం ofs = 0;
    Uint8 ch;
    Uint8 needsPad;
    స్థిరరాశి పూర్ణాంకం pixels_చొప్పున_byte = (isRle8 ? 1 : 2);

#నిర్వచించు COPY_PIXEL(x)                \
    spot = &బిట్లు[ofs++];             \
    ఒకవేళ (spot >= ప్రారంభం && spot < చివర) \
        *spot = (x)

    కొరకు (;;) {
        ఒకవేళ (!SDL_ReadU8(src, &ch)) {
            తిరిగి false;
        }
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        ఒకవేళ (ch) {
            Uint8 pixelvalue;
            ఒకవేళ (!SDL_ReadU8(src, &pixelvalue)) {
                తిరిగి false;
            }
            పూర్ణాంకం ich = (పూర్ణాంకం) ch;
            చేయి {
                COPY_PIXEL(pixelvalue);
                ich -= pixels_చొప్పున_byte;
            } అయితే (ich > 0);
        } లేకపోతే {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            ఒకవేళ (!SDL_ReadU8(src, &ch)) {
                తిరిగి false;
            }
            ఎంపిక (ch) {
            స్థితి 0: // end of line
                ofs = 0;
                బిట్లు -= pitch; // go to previous
                ఆపు;
            స్థితి 1:               // end of bitmap
                తిరిగి true; // success!
            స్థితి 2:               // delta
                ఒకవేళ (!SDL_ReadU8(src, &ch)) {
                    తిరిగి false;
                }
                ofs += ch / pixels_చొప్పున_byte;
                ఒకవేళ (ch & pixels_చొప్పున_byte) {
                    ofs++;
                }
                ఒకవేళ (!SDL_ReadU8(src, &ch)) {
                    తిరిగి false;
                }
                బిట్లు -= (ch * pitch);
                ఆపు;
            అప్రమేయ: // no compression
                // !!! FIXME: this needsPad calculation can probably be simpler than this.
                ఒకవేళ (pixels_చొప్పున_byte == 1) {
                    needsPad = (ch & 1) != 0;
                } లేకపోతే {
                    needsPad = (((ch + (pixels_చొప్పున_byte-1)) / pixels_చొప్పున_byte) & (pixels_చొప్పున_byte-1)) != 0;
                }

                పూర్ణాంకం ich = (పూర్ణాంకం) ch;
                చేయి {
                    Uint8 pixelvalue;
                    ఒకవేళ (!SDL_ReadU8(src, &pixelvalue)) {
                        తిరిగి false;
                    }
                    COPY_PIXEL(pixelvalue);
                    ich -= pixels_చొప్పున_byte;
                } అయితే (ich > 0);

                // pad at even boundary
                ఒకవేళ (needsPad && !SDL_ReadU8(src, &ch)) {
                    తిరిగి false;
                }
                ఆపు;
            }
        }
    }
}

స్థిర శూన్య CorrectAlphaChannel(SDL_Surface *surface)
{
    // Check to see if there is any alpha channel data
    bool hasAlpha = false;
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
    పూర్ణాంకం alpha_Channel_స్థానభ్రంశం = 0;
#లేకపోతే
    పూర్ణాంకం alpha_Channel_స్థానభ్రంశం = 3;
#అయితే_ముగింపు
    Uint8 *alpha = ((Uint8 *)surface->pixels) + alpha_Channel_స్థానభ్రంశం;
    Uint8 *చివర = alpha + surface->h * surface->pitch;

    అయితే (alpha < చివర) {
        ఒకవేళ (*alpha != 0) {
            hasAlpha = true;
            ఆపు;
        }
        alpha += 4;
    }

    ఒకవేళ (!hasAlpha) {
        alpha = ((Uint8 *)surface->pixels) + alpha_Channel_స్థానభ్రంశం;
        అయితే (alpha < చివర) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}

bool SDL_IsBMP(SDL_IOStream *src)
{
    Sint64 ప్రారంభం;
    Uint8 magic[2];
    bool is_BMP;

    is_BMP = false;
    ప్రారంభం = SDL_TellIO(src);
    ఒకవేళ (ప్రారంభం >= 0) {
        ఒకవేళ (SDL_ReadIO(src, magic, పరిమాణం(magic)) == పరిమాణం(magic)) {
            ఒకవేళ (magic[0] == 'B' && magic[1] == 'M') {
                is_BMP = true;
            }
        }
        SDL_SeekIO(src, ప్రారంభం, SDL_IO_SEEK_సమితి);
    }

    తిరిగి is_BMP;
}

SDL_Surface *SDL_ఎక్కించు_BMP_IO(SDL_IOStream *src, bool closeio)
{
    bool was_error = true;
    Sint64 fp_స్థానభ్రంశం = 0;
    పూర్ణాంకం i, pad;
    SDL_Surface *surface;
    Uint32 Rmask = 0;
    Uint32 Gmask = 0;
    Uint32 Bmask = 0;
    Uint32 Amask = 0;
    Uint8 *బిట్లు;
    Uint8 *శిఖరం, *చివర;
    bool శిఖరం_కిందికి;
    bool haveRGBMasks = false;
    bool have_Alpha_ముసుగు = false;
    bool correctAlpha = false;

    // The Win32 BMP file header (14 bytes)
    // char magic[2];
    // Uint32 bfSize;
    // Uint16 bfReserved1;
    // Uint16 bfReserved2;
    Uint32 bf_Off_బిట్లు;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_కొలత;
    Sint32 bi_వెడల్పు = 0;
    Sint32 bi_ఎత్తు = 0;
    // Uint16 biPlanes;
    Uint16 bi_బిట్టు_లెక్క = 0;
    Uint32 biCompression = 0;
    // Uint32 biSizeImage;
    // Sint32 biXPelsPerMeter;
    // Sint32 biYPelsPerMeter;
    Uint32 bi_Clr_వాడిన = 0;
    // Uint32 biClrImportant;

    // Make sure we are passed a valid data source
    surface = ఖాళీ;
    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        వెళ్ళు పూర్తి;
    }

    // Read in the BMP file header
    fp_స్థానభ్రంశం = SDL_TellIO(src);
    ఒకవేళ (fp_స్థానభ్రంశం < 0) {
        వెళ్ళు పూర్తి;
    }
    SDL_ClearError();
    ఒకవేళ (!SDL_IsBMP(src)) {
        SDL_సమితి_Error("File is not a Windows BMP file");
        వెళ్ళు పూర్తి;
    }
    ఒకవేళ (!SDL_ReadU16LE(src, ఖాళీ /* magic (already checked) */) ||
        !SDL_ReadU32LE(src, ఖాళీ /* bfSize */) ||
        !SDL_ReadU16LE(src, ఖాళీ /* bfReserved1 */) ||
        !SDL_ReadU16LE(src, ఖాళీ /* bfReserved2 */) ||
        !SDL_ReadU32LE(src, &bf_Off_బిట్లు)) {
        వెళ్ళు పూర్తి;
    }

    // Read the Win32 BITMAPINFOHEADER
    ఒకవేళ (!SDL_ReadU32LE(src, &bi_కొలత)) {
        వెళ్ళు పూర్తి;
    }
    ఒకవేళ (bi_కొలత == 12) { // really old BITMAPCOREHEADER
        Uint16 biWidth16, biHeight16;
        ఒకవేళ (!SDL_ReadU16LE(src, &biWidth16) ||
            !SDL_ReadU16LE(src, &biHeight16) ||
            !SDL_ReadU16LE(src, ఖాళీ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_బిట్టు_లెక్క)) {
            వెళ్ళు పూర్తి;
        }
        bi_వెడల్పు = biWidth16;
        bi_ఎత్తు = biHeight16;
        biCompression = BI_RGB;
        // biSizeImage = 0;
        // biXPelsPerMeter = 0;
        // biYPelsPerMeter = 0;
        bi_Clr_వాడిన = 0;
        // biClrImportant = 0;
    } లేకపోతే ఒకవేళ (bi_కొలత >= 40) { // some version of BITMAPINFOHEADER
        Uint32 శీర్షిక_కొలత;
        ఒకవేళ (!SDL_ReadS32LE(src, &bi_వెడల్పు) ||
            !SDL_ReadS32LE(src, &bi_ఎత్తు) ||
            !SDL_ReadU16LE(src, ఖాళీ /* biPlanes */) ||
            !SDL_ReadU16LE(src, &bi_బిట్టు_లెక్క) ||
            !SDL_ReadU32LE(src, &biCompression) ||
            !SDL_ReadU32LE(src, ఖాళీ /* biSizeImage */) ||
            !SDL_ReadU32LE(src, ఖాళీ /* biXPelsPerMeter */) ||
            !SDL_ReadU32LE(src, ఖాళీ /* biYPelsPerMeter */) ||
            !SDL_ReadU32LE(src, &bi_Clr_వాడిన) ||
            !SDL_ReadU32LE(src, ఖాళీ /* biClrImportant */)) {
            వెళ్ళు పూర్తి;
        }

        // 64 == BITMAPCOREHEADER2, an incompatible OS/2 2.x extension. Skip this stuff for now.
        ఒకవేళ (bi_కొలత != 64) {
            /* This is complicated. If compression is BI_BITFIELDS, then
               we have 3 DWORDS that specify the RGB masks. This is either
               stored here in an BITMAPV2INFOHEADER (which only differs in
               that it adds these RGB masks) and biSize >= 52, or we've got
               these masks stored in the exact same place, but strictly
               speaking, this is the bmiColors field in BITMAPINFO immediately
               following the legacy v1 info header, just past biSize. */
            ఒకవేళ (biCompression == BI_BITFIELDS) {
                haveRGBMasks = true;
                ఒకవేళ (!SDL_ReadU32LE(src, &Rmask) ||
                    !SDL_ReadU32LE(src, &Gmask) ||
                    !SDL_ReadU32LE(src, &Bmask)) {
                    వెళ్ళు పూర్తి;
                }

                // ...v3 adds an alpha mask.
                ఒకవేళ (bi_కొలత >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    have_Alpha_ముసుగు = true;
                    ఒకవేళ (!SDL_ReadU32LE(src, &Amask)) {
                        వెళ్ళు పూర్తి;
                    }
                }
            } లేకపోతే {
                // the mask fields are ignored for v2+ headers if not BI_BITFIELD.
                ఒకవేళ (bi_కొలత >= 52) { // BITMAPV2INFOHEADER; adds RGB masks
                    ఒకవేళ (!SDL_ReadU32LE(src, ఖాళీ /* Rmask */) ||
                        !SDL_ReadU32LE(src, ఖాళీ /* Gmask */) ||
                        !SDL_ReadU32LE(src, ఖాళీ /* Bmask */)) {
                        వెళ్ళు పూర్తి;
                    }
                }
                ఒకవేళ (bi_కొలత >= 56) { // BITMAPV3INFOHEADER; adds alpha mask
                    ఒకవేళ (!SDL_ReadU32LE(src, ఖాళీ /* Amask */)) {
                        వెళ్ళు పూర్తి;
                    }
                }
            }

            /* Insert other fields here; Wikipedia and MSDN say we're up to
               v5 of this header, but we ignore those for now (they add gamma,
               color spaces, etc). Ignoring the weird OS/2 2.x format, we
               currently parse up to v3 correctly (hopefully!). */
        }

        // skip any header bytes we didn't handle...
        శీర్షిక_కొలత = (Uint32)(SDL_TellIO(src) - (fp_స్థానభ్రంశం + 14));
        ఒకవేళ (bi_కొలత > శీర్షిక_కొలత) {
            ఒకవేళ (SDL_SeekIO(src, (bi_కొలత - శీర్షిక_కొలత), SDL_IO_SEEK_CUR) < 0) {
                వెళ్ళు పూర్తి;
            }
        }
    }
    ఒకవేళ (bi_వెడల్పు <= 0 || bi_ఎత్తు == 0) {
        SDL_సమితి_Error("BMP file with bad dimensions (%" SDL_PRIs32 "x%" SDL_PRIs32 ")", bi_వెడల్పు, bi_ఎత్తు);
        వెళ్ళు పూర్తి;
    }
    ఒకవేళ (bi_ఎత్తు < 0) {
        శిఖరం_కిందికి = true;
        bi_ఎత్తు = -bi_ఎత్తు;
    } లేకపోతే {
        శిఖరం_కిందికి = false;
    }

    // Check for read error
    ఒకవేళ (SDL_strcmp(SDL_GetError(), "") != 0) {
        వెళ్ళు పూర్తి;
    }

    // Reject invalid bit depths
    ఎంపిక (bi_బిట్టు_లెక్క) {
    స్థితి 0:
    స్థితి 3:
    స్థితి 5:
    స్థితి 6:
    స్థితి 7:
        SDL_సమితి_Error("%u bpp BMP images are not supported", bi_బిట్టు_లెక్క);
        వెళ్ళు పూర్తి;
    అప్రమేయ:
        ఆపు;
    }

    // RLE4 and RLE8 BMP compression is supported
    ఎంపిక (biCompression) {
    స్థితి BI_RGB:
        // If there are no masks, use the defaults
        SDL_assert(!haveRGBMasks);
        SDL_assert(!have_Alpha_ముసుగు);
        // Default values for the BMP format
        ఎంపిక (bi_బిట్టు_లెక్క) {
        స్థితి 15:
        స్థితి 16:
            // SDL_PIXELFORMAT_XRGB1555 or SDL_PIXELFORMAT_ARGB1555 if Amask
            Rmask = 0x7C00;
            Gmask = 0x03E0;
            Bmask = 0x001F;
            ఆపు;
        స్థితి 24:
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
            // SDL_PIXELFORMAT_RGB24
            Rmask = 0x000000FF;
            Gmask = 0x0000FF00;
            Bmask = 0x00FF0000;
#లేకపోతే
            // SDL_PIXELFORMAT_BGR24
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
#అయితే_ముగింపు
            ఆపు;
        స్థితి 32:
            // We don't know if this has alpha channel or not
            correctAlpha = true;
            // SDL_PIXELFORMAT_RGBA8888
            Amask = 0xFF000000;
            Rmask = 0x00FF0000;
            Gmask = 0x0000FF00;
            Bmask = 0x000000FF;
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
        ఆపు;

    స్థితి BI_BITFIELDS:
        ఆపు; // we handled this in the info header.

    అప్రమేయ:
        ఆపు;
    }

    // Create a compatible surface, note that the colors are RGB ordered
    {
        SDL_PixelFormat format;

        // Get the pixel format
        format = SDL_GetPixelFormatForMasks(bi_బిట్టు_లెక్క, Rmask, Gmask, Bmask, Amask);
        surface = SDL_CreateSurfaceUninitialized(bi_వెడల్పు, bi_ఎత్తు, format);

        ఒకవేళ (!surface) {
            వెళ్ళు పూర్తి;
        }
    }

    // Load the palette, if any
    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ఒకవేళ (!palette) {
            వెళ్ళు పూర్తి;
        }

        ఒకవేళ (SDL_SeekIO(src, fp_స్థానభ్రంశం + 14 + bi_కొలత, SDL_IO_SEEK_సమితి) < 0) {
            SDL_సమితి_Error("Error seeking in datastream");
            వెళ్ళు పూర్తి;
        }

        ఒకవేళ (bi_బిట్టు_లెక్క >= 32) { // we shift biClrUsed by this value later.
            SDL_సమితి_Error("Unsupported or incorrect biBitCount field");
            వెళ్ళు పూర్తి;
        }

        ఒకవేళ (bi_Clr_వాడిన == 0) {
            bi_Clr_వాడిన = 1 << bi_బిట్టు_లెక్క;
        }

        ఒకవేళ (bi_Clr_వాడిన > (Uint32)palette->ncolors) {
            bi_Clr_వాడిన = 1 << bi_బిట్టు_లెక్క; // try forcing it?
            ఒకవేళ (bi_Clr_వాడిన > (Uint32)palette->ncolors) {
                SDL_సమితి_Error("Unsupported or incorrect biClrUsed field");
                వెళ్ళు పూర్తి;
            }
        }
        palette->ncolors = bi_Clr_వాడిన;

        ఒకవేళ (bi_కొలత == 12) {
            కొరకు (i = 0; i < palette->ncolors; ++i) {
                ఒకవేళ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r)) {
                    వెళ్ళు పూర్తి;
                }
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } లేకపోతే {
            కొరకు (i = 0; i < palette->ncolors; ++i) {
                ఒకవేళ (!SDL_ReadU8(src, &palette->colors[i].b) ||
                    !SDL_ReadU8(src, &palette->colors[i].g) ||
                    !SDL_ReadU8(src, &palette->colors[i].r) ||
                    !SDL_ReadU8(src, &palette->colors[i].a)) {
                    వెళ్ళు పూర్తి;
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
    ఒకవేళ (SDL_SeekIO(src, fp_స్థానభ్రంశం + bf_Off_బిట్లు, SDL_IO_SEEK_సమితి) < 0) {
        SDL_సమితి_Error("Error seeking in datastream");
        వెళ్ళు పూర్తి;
    }
    ఒకవేళ ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        ఒకవేళ (!readRlePixels(surface, src, biCompression == BI_RLE8)) {
            SDL_సమితి_Error("Error reading from datastream");
            వెళ్ళు పూర్తి;
        }

        // Success!
        was_error = false;
        వెళ్ళు పూర్తి;
    }
    శిఖరం = (Uint8 *)surface->pixels;
    చివర = (Uint8 *)surface->pixels + (surface->h * surface->pitch);
    pad = ((surface->pitch % 4) ? (4 - (surface->pitch % 4)) : 0);
    ఒకవేళ (శిఖరం_కిందికి) {
        బిట్లు = శిఖరం;
    } లేకపోతే {
        బిట్లు = చివర - surface->pitch;
    }
    అయితే (బిట్లు >= శిఖరం && బిట్లు < చివర) {
        ఒకవేళ (SDL_ReadIO(src, బిట్లు, surface->pitch) != (size_t)surface->pitch) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (bi_బిట్టు_లెక్క == 8 && surface->palette && bi_Clr_వాడిన < (1u << bi_బిట్టు_లెక్క)) {
            కొరకు (i = 0; i < surface->w; ++i) {
                ఒకవేళ (బిట్లు[i] >= bi_Clr_వాడిన) {
                    SDL_సమితి_Error("A BMP image contains a pixel with a color out of the palette");
                    వెళ్ళు పూర్తి;
                }
            }
        }
#ఒకవేళ SDL_BYTEORDER == SDL_BIG_ENDIAN
        /* Byte-swap the pixels if needed. Note that the 24bpp
           case has already been taken care of above. */
        ఎంపిక (bi_బిట్టు_లెక్క) {
        స్థితి 15:
        స్థితి 16:
        {
            Uint16 *pix = (Uint16 *)బిట్లు;
            కొరకు (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap16(pix[i]);
            }
            ఆపు;
        }

        స్థితి 32:
        {
            Uint32 *pix = (Uint32 *)బిట్లు;
            కొరకు (i = 0; i < surface->w; i++) {
                pix[i] = SDL_Swap32(pix[i]);
            }
            ఆపు;
        }
        }
#అయితే_ముగింపు

        // Skip padding bytes, ugh
        ఒకవేళ (pad) {
            Uint8 padbyte;
            కొరకు (i = 0; i < pad; ++i) {
                ఒకవేళ (!SDL_ReadU8(src, &padbyte)) {
                    వెళ్ళు పూర్తి;
                }
            }
        }
        ఒకవేళ (శిఖరం_కిందికి) {
            బిట్లు += surface->pitch;
        } లేకపోతే {
            బిట్లు -= surface->pitch;
        }
    }
    ఒకవేళ (correctAlpha) {
        CorrectAlphaChannel(surface);
    }

    was_error = false;

పూర్తి:
    ఒకవేళ (was_error) {
        ఒకవేళ (src) {
            SDL_SeekIO(src, fp_స్థానభ్రంశం, SDL_IO_SEEK_సమితి);
        }
        SDL_DestroySurface(surface);
        surface = ఖాళీ;
    }
    ఒకవేళ (closeio && src) {
        SDL_CloseIO(src);
    }
    తిరిగి surface;
}

రకనిర్వచనం నిర్మాణం {
    SDL_Surface *surface;
    SDL_Surface *intermediate_surface;
    bool save32bit;
    bool saveLegacyBMP;
} BMPSaveState;

స్థిర శూన్య FreeBMPSaveState(BMPSaveState *state)
{
    ఒకవేళ (state->intermediate_surface && state->intermediate_surface != state->surface) {
        SDL_DestroySurface(state->intermediate_surface);
    }
}

స్థిర bool InitBMPSaveState(BMPSaveState *state, SDL_Surface *surface)
{
    state->surface = surface;
    state->intermediate_surface = ఖాళీ;
    state->save32bit = false;
    state->saveLegacyBMP = false;

    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

#నిర్వచితమైతే SAVE_32_బిట్టు_BMP
    // We can save alpha information in a 32-bit BMP
    ఒకవేళ (SDL_BITSPERPIXEL(surface->format) >= 8 &&
        (SDL_ISPIXELFORMAT_ALPHA(surface->format) ||
         (surface->map.info.flags & SDL_COPY_COLORKEY))) {
        state->save32bit = true;
    }
#అయితే_ముగింపు // SAVE_32BIT_BMP

    ఒకవేళ (surface->palette && !state->save32bit) {
        ఒకవేళ (SDL_BITSPERPIXEL(surface->format) == 8) {
            state->intermediate_surface = surface;
        } లేకపోతే {
            SDL_సమితి_Error("%u bpp BMP files not supported",
                         SDL_BITSPERPIXEL(surface->format));
            వెళ్ళు error;
        }
    } లేకపోతే ఒకవేళ ((surface->format == SDL_PIXELFORMAT_BGR24 && !state->save32bit) ||
               (surface->format == SDL_PIXELFORMAT_BGRA32 && state->save32bit)) {
        state->intermediate_surface = surface;
    } లేకపోతే {
        SDL_PixelFormat pixel_format;

        /* If the surface has a colorkey or alpha channel we'll save a
           32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
        ఒకవేళ (state->save32bit) {
            pixel_format = SDL_PIXELFORMAT_BGRA32;
        } లేకపోతే {
            pixel_format = SDL_PIXELFORMAT_BGR24;
        }
        state->intermediate_surface = SDL_ConvertSurface(surface, pixel_format);
        ఒకవేళ (!state->intermediate_surface) {
            SDL_సమితి_Error("Couldn't convert image to %d bpp",
                         (పూర్ణాంకం)SDL_BITSPERPIXEL(pixel_format));
            వెళ్ళు error;
        }
    }

    ఒకవేళ (state->save32bit) {
        state->saveLegacyBMP = SDL_GetHintBoolean(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, false);
    }
    తిరిగి true;
error:
    FreeBMPSaveState(state);
    తిరిగి false;
}

SDL_Surface *SDL_ఎక్కించు_BMP(స్థిరరాశి అక్షరం *file)
{
    SDL_IOStream *ప్రవాహం = SDL_IOFromFile(file, "rb");
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి ఖాళీ;
    }
    తిరిగి SDL_ఎక్కించు_BMP_IO(ప్రవాహం, true);
}
స్థిర bool SDL_Save_BMP_IO_అంతర్గత(BMPSaveState *state, SDL_IOStream *dst, bool closeio)
{
    bool was_error = true;
    Sint64 fp_స్థానభ్రంశం, new_స్థానభ్రంశం;
    పూర్ణాంకం i, pad;
    Uint8 *బిట్లు;

    // The Win32 BMP file header (14 bytes)
    అక్షరం magic[2] = { 'B', 'M' };
    Uint32 bf_కొలత;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bf_Off_బిట్లు;

    // The Win32 BITMAPINFOHEADER struct (40 bytes)
    Uint32 bi_కొలత;
    Sint32 bi_వెడల్పు;
    Sint32 bi_ఎత్తు;
    Uint16 biPlanes;
    Uint16 bi_బిట్టు_లెక్క;
    Uint32 biCompression;
    Uint32 bi_కొలత_Image;
    Sint32 bi_XPels_చొప్పున_Meter;
    Sint32 bi_YPels_చొప్పున_Meter;
    Uint32 bi_Clr_వాడిన;
    Uint32 biClrImportant;

    // The additional header members from the Win32 BITMAPV4HEADER struct (108 bytes in total)
    Uint32 b_V4_Red_ముసుగు = 0;
    Uint32 b_V4_Green_ముసుగు = 0;
    Uint32 b_V4_Blue_ముసుగు = 0;
    Uint32 b_V4_Alpha_ముసుగు = 0;
    Uint32 bV4CSType = 0;
    Sint32 bV4Endpoints[3 * 3] = { 0 };
    Uint32 bV4GammaRed = 0;
    Uint32 bV4GammaGreen = 0;
    Uint32 bV4GammaBlue = 0;

    // The additional header members from the Win32 BITMAPV5HEADER struct (124 bytes in total)
    Uint32 bV5Intent = 0;
    Uint32 b_V5_Profile_దత్తాంశం = 0;
    Uint32 b_V5_Profile_కొలత = 0;
    Uint32 bV5Reserved = 0;

    ఒకవేళ (SDL_తాళం_Surface(state->intermediate_surface)) {
        స్థిరరాశి size_t bw = state->intermediate_surface->w * state->intermediate_surface->fmt->బైట్లు_చొప్పున_pixel;

        // Set the BMP file header values
        bf_కొలత = 0; // We'll write this when we're done
        bfReserved1 = 0;
        bfReserved2 = 0;
        bf_Off_బిట్లు = 0; // We'll write this when we're done

        // Write the BMP file header values
        fp_స్థానభ్రంశం = SDL_TellIO(dst);
        ఒకవేళ (fp_స్థానభ్రంశం < 0) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (SDL_WriteIO(dst, magic, 2) != 2 ||
            !SDL_WriteU32LE(dst, bf_కొలత) ||
            !SDL_WriteU16LE(dst, bfReserved1) ||
            !SDL_WriteU16LE(dst, bfReserved2) ||
            !SDL_WriteU32LE(dst, bf_Off_బిట్లు)) {
            వెళ్ళు పూర్తి;
        }

        // Set the BMP info values
        bi_కొలత = 40;
        bi_వెడల్పు = state->intermediate_surface->w;
        bi_ఎత్తు = state->intermediate_surface->h;
        biPlanes = 1;
        bi_బిట్టు_లెక్క = state->intermediate_surface->fmt->బిట్లు_చొప్పున_pixel;
        biCompression = BI_RGB;
        bi_కొలత_Image = state->intermediate_surface->h * state->intermediate_surface->pitch;
        bi_XPels_చొప్పున_Meter = 0;
        bi_YPels_చొప్పున_Meter = 0;
        ఒకవేళ (state->intermediate_surface->palette) {
            bi_Clr_వాడిన = state->intermediate_surface->palette->ncolors;
        } లేకపోతే {
            bi_Clr_వాడిన = 0;
        }
        biClrImportant = 0;

        // Set the BMP info values
        ఒకవేళ (state->save32bit && !state->saveLegacyBMP) {
            bi_కొలత = 124;
            // Version 4 values
            biCompression = BI_BITFIELDS;
            // The BMP format is always little endian, these masks stay the same
            b_V4_Red_ముసుగు = 0x00ff0000;
            b_V4_Green_ముసుగు = 0x0000ff00;
            b_V4_Blue_ముసుగు = 0x000000ff;
            b_V4_Alpha_ముసుగు = 0xff000000;
            bV4CSType = LCS_sRGB;
            bV4GammaRed = 0;
            bV4GammaGreen = 0;
            bV4GammaBlue = 0;
            // Version 5 values
            bV5Intent = LCS_GM_GRAPHICS;
            b_V5_Profile_దత్తాంశం = 0;
            b_V5_Profile_కొలత = 0;
            bV5Reserved = 0;
        }

        // Write the BMP info values
        ఒకవేళ (!SDL_WriteU32LE(dst, bi_కొలత) ||
            !SDL_WriteS32LE(dst, bi_వెడల్పు) ||
            !SDL_WriteS32LE(dst, bi_ఎత్తు) ||
            !SDL_WriteU16LE(dst, biPlanes) ||
            !SDL_WriteU16LE(dst, bi_బిట్టు_లెక్క) ||
            !SDL_WriteU32LE(dst, biCompression) ||
            !SDL_WriteU32LE(dst, bi_కొలత_Image) ||
            !SDL_WriteU32LE(dst, bi_XPels_చొప్పున_Meter) ||
            !SDL_WriteU32LE(dst, bi_YPels_చొప్పున_Meter) ||
            !SDL_WriteU32LE(dst, bi_Clr_వాడిన) ||
            !SDL_WriteU32LE(dst, biClrImportant)) {
            వెళ్ళు పూర్తి;
        }

        // Write the BMP info values
        ఒకవేళ (state->save32bit && !state->saveLegacyBMP) {
            // Version 4 values
            ఒకవేళ (!SDL_WriteU32LE(dst, b_V4_Red_ముసుగు) ||
                !SDL_WriteU32LE(dst, b_V4_Green_ముసుగు) ||
                !SDL_WriteU32LE(dst, b_V4_Blue_ముసుగు) ||
                !SDL_WriteU32LE(dst, b_V4_Alpha_ముసుగు) ||
                !SDL_WriteU32LE(dst, bV4CSType)) {
                వెళ్ళు పూర్తి;
            }
            కొరకు (i = 0; i < 3 * 3; i++) {
                ఒకవేళ (!SDL_WriteU32LE(dst, bV4Endpoints[i])) {
                    వెళ్ళు పూర్తి;
                }
            }
            ఒకవేళ (!SDL_WriteU32LE(dst, bV4GammaRed) ||
                !SDL_WriteU32LE(dst, bV4GammaGreen) ||
                !SDL_WriteU32LE(dst, bV4GammaBlue)) {
                వెళ్ళు పూర్తి;
            }
            // Version 5 values
            ఒకవేళ (!SDL_WriteU32LE(dst, bV5Intent) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_దత్తాంశం) ||
                !SDL_WriteU32LE(dst, b_V5_Profile_కొలత) ||
                !SDL_WriteU32LE(dst, bV5Reserved)) {
                వెళ్ళు పూర్తి;
            }
        }

        // Write the palette (in BGR color order)
        ఒకవేళ (state->intermediate_surface->palette) {
            SDL_Color *colors;
            పూర్ణాంకం ncolors;

            colors = state->intermediate_surface->palette->colors;
            ncolors = state->intermediate_surface->palette->ncolors;
            కొరకు (i = 0; i < ncolors; ++i) {
                ఒకవేళ (!SDL_WriteU8(dst, colors[i].b) ||
                    !SDL_WriteU8(dst, colors[i].g) ||
                    !SDL_WriteU8(dst, colors[i].r) ||
                    !SDL_WriteU8(dst, colors[i].a)) {
                    వెళ్ళు పూర్తి;
                }
            }
        }

        // Write the bitmap offset
        bf_Off_బిట్లు = (Uint32)(SDL_TellIO(dst) - fp_స్థానభ్రంశం);
        ఒకవేళ (SDL_SeekIO(dst, fp_స్థానభ్రంశం + 10, SDL_IO_SEEK_సమితి) < 0) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (!SDL_WriteU32LE(dst, bf_Off_బిట్లు)) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (SDL_SeekIO(dst, fp_స్థానభ్రంశం + bf_Off_బిట్లు, SDL_IO_SEEK_సమితి) < 0) {
            వెళ్ళు పూర్తి;
        }

        // Write the bitmap image upside down
        బిట్లు = (Uint8 *)state->intermediate_surface->pixels + (state->intermediate_surface->h * state->intermediate_surface->pitch);
        pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
        అయితే (బిట్లు > (Uint8 *)state->intermediate_surface->pixels) {
            బిట్లు -= state->intermediate_surface->pitch;
            ఒకవేళ (SDL_WriteIO(dst, బిట్లు, bw) != bw) {
                వెళ్ళు పూర్తి;
            }
            ఒకవేళ (pad) {
                స్థిరరాశి Uint8 padbyte = 0;
                కొరకు (i = 0; i < pad; ++i) {
                    ఒకవేళ (!SDL_WriteU8(dst, padbyte)) {
                        వెళ్ళు పూర్తి;
                    }
                }
            }
        }

        // Write the BMP file size
        new_స్థానభ్రంశం = SDL_TellIO(dst);
        ఒకవేళ (new_స్థానభ్రంశం < 0) {
            వెళ్ళు పూర్తి;
        }
        bf_కొలత = (Uint32)(new_స్థానభ్రంశం - fp_స్థానభ్రంశం);
        ఒకవేళ (SDL_SeekIO(dst, fp_స్థానభ్రంశం + 2, SDL_IO_SEEK_సమితి) < 0) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (!SDL_WriteU32LE(dst, bf_కొలత)) {
            వెళ్ళు పూర్తి;
        }
        ఒకవేళ (SDL_SeekIO(dst, fp_స్థానభ్రంశం + bf_కొలత, SDL_IO_SEEK_సమితి) < 0) {
            వెళ్ళు పూర్తి;
        }

        // Close it up..
        SDL_UnlockSurface(state->intermediate_surface);

        was_error = false;
    }

పూర్తి:
    ఒకవేళ (closeio && dst) {
        ఒకవేళ (!SDL_CloseIO(dst)) {
            was_error = true;
        }
    }
    ఒకవేళ (was_error) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool SDL_SaveBMP_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool ఫలితం = true;
    BMPSaveState state;
    ఒకవేళ (!InitBMPSaveState(&state, surface)) {
        తిరిగి false;
    }
    CHECK_PARAM(!dst) {
        ఫలితం = SDL_InvalidParamError("dst");
        వెళ్ళు పూర్తి;
    }
    ఫలితం = SDL_Save_BMP_IO_అంతర్గత(&state, dst, closeio);
పూర్తి:
    FreeBMPSaveState(&state);
    తిరిగి ఫలితం;
}

bool SDL_SaveBMP(SDL_Surface *surface, స్థిరరాశి అక్షరం *file)
{
    BMPSaveState state;
    ఒకవేళ (!InitBMPSaveState(&state, surface)) {
        తిరిగి false;
    }

    SDL_IOStream *ప్రవాహం = SDL_IOFromFile(file, "wb");
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి false;
    }

    bool ఫలితం = SDL_Save_BMP_IO_అంతర్గత(&state, ప్రవాహం, true);
    FreeBMPSaveState(&state);
    తిరిగి ఫలితం;
}

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

#అన్తర్భావ "SDL_stb_c.h"
#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_yuv_c.h"

/* STB image conversion */
#నిర్వచితం_కాకపోతే SDL_DISABLE_STB
#నిర్వచించు SDL_HAVE_STB
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_HAVE_STB
////////////////////////////////////////////////////////////////////////////
#నిర్వచించు జ్ఞాపకం_ఇవ్వు SDL_malloc
#నిర్వచించు realloc SDL_realloc
#నిర్వచించు విడుదల SDL_free
#నిర్వచనం_రద్దు జ్ఞాపకం_నకలు
#నిర్వచించు జ్ఞాపకం_నకలు SDL_memcpy
#నిర్వచనం_రద్దు memset
#నిర్వచించు memset SDL_memset
#నిర్వచనం_రద్దు strcmp
#నిర్వచించు strcmp SDL_strcmp
#నిర్వచనం_రద్దు అక్షరశ్రేణి_పోలిక
#నిర్వచించు అక్షరశ్రేణి_పోలిక SDL_strncmp
#నిర్వచించు strtol SDL_strtol

#నిర్వచించు నిరపేక్ష SDL_abs
#నిర్వచించు ఘాతం SDL_pow
#నిర్వచించు ldexp SDL_scalbn

#నిర్వచించు STB_IMAGE_STATIC
#నిర్వచించు STBI_NO_THREAD_LOCALS
#నిర్వచించు STBI_FAILURE_USERMSG
#ఒకవేళ defined(SDL_NEON_INTRINSICS)
#నిర్వచించు STBI_NEON
#అయితే_ముగింపు
#నిర్వచించు STBI_ONLY_PNG
#నిర్వచించు STBI_ONLY_JPEG
#నిర్వచించు STBI_NO_GIF
#నిర్వచించు STBI_NO_HDR
#నిర్వచించు STBI_NO_రేఖీయ
#నిర్వచించు STBI_NO_STDIO
#నిర్వచించు STBI_ASSERT SDL_assert
#నిర్వచించు STB_IMAGE_IMPLEMENTATION
#అన్తర్భావ "stb_image.h"

////////////////////////////////////////////////////////////////////////////
#నిర్వచించు MZ_ASSERT(x) SDL_assert(x)
//#undef memcpy
//#define memcpy SDL_memcpy
//#undef memset
//#define memset SDL_memset
#ఒకవేళ SDL_BYTEORDER == SDL_LIL_ENDIAN
#నిర్వచించు MINIZ_LITTLE_ENDIAN 1
#లేకపోతే
#నిర్వచించు MINIZ_LITTLE_ENDIAN 0
#అయితే_ముగింపు
#నిర్వచించు MINIZ_USE_UNALIGNED_LOADS_AND_STORES 0
#నిర్వచించు MINIZ_SDL_NOUNUSED
#అన్తర్భావ "miniz.h"

#నిర్వచనం_రద్దు memset
#అయితే_ముగింపు // SDL_HAVE_STB

#నిర్వచితమైతే SDL_HAVE_STB
స్థిర bool SDL_Convert_Pixels_MJPG_గమ్యం_NV12(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
    పూర్ణాంకం w = 0, h = 0, format = 0;
    stbi__context s;
    stbi_ప్రారంభం_mem(&s, src, src_pitch);

    stbi_ఫలితం_info ri;
    SDL_zero(ri);
    ri.బిట్లు_చొప్పున_channel = 8;
    ri.channel_క్రమం = STBI_క్రమం_RGB;
    ri.అంకె_channels = 0;

    stbi__nv12 nv12;
    nv12.w = వెడల్పు;
    nv12.h = ఎత్తు;
    nv12.pitch = dst_pitch;
    nv12.y = (stbi_uc *)dst;
    nv12.uv = nv12.y + (nv12.h * nv12.pitch);

    శూన్య *pixels = stbi_jpeg_ఎక్కించు(&s, &w, &h, &format, 4, &nv12, &ri);
    ఒకవేళ (!pixels) {
        తిరిగి false;
    }
    తిరిగి true;
}
#అయితే_ముగింపు // SDL_HAVE_STB

bool SDL_ConvertPixels_STB(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                           SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, స్థిరరాశి శూన్య *src, పూర్ణాంకం src_pitch,
                           SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, శూన్య *dst, పూర్ణాంకం dst_pitch)
{
#నిర్వచితమైతే SDL_HAVE_STB
    ఒకవేళ (src_format == SDL_PIXELFORMAT_MJPG) {
        ఒకవేళ (dst_format == SDL_PIXELFORMAT_NV12) {
            తిరిగి SDL_Convert_Pixels_MJPG_గమ్యం_NV12(వెడల్పు, ఎత్తు, src, src_pitch, dst, dst_pitch);
        } లేకపోతే ఒకవేళ (
            dst_format == SDL_PIXELFORMAT_YV12 ||
            dst_format == SDL_PIXELFORMAT_IYUV ||
            dst_format == SDL_PIXELFORMAT_YUY2 ||
            dst_format == SDL_PIXELFORMAT_UYVY ||
            dst_format == SDL_PIXELFORMAT_YVYU ||
            dst_format == SDL_PIXELFORMAT_NV21 ||
            dst_format == SDL_PIXELFORMAT_P010
        ) {
            size_t తాత్కాలిక_కొలత = 0;
            size_t తాత్కాలిక_pitch = 0;
            ఒకవేళ (!SDL_CalculateYUVSize(dst_format, వెడల్పు, ఎత్తు, &తాత్కాలిక_కొలత, &తాత్కాలిక_pitch)) {
                తిరిగి false;
            }
            శూన్య *తాత్కాలిక_pixels = SDL_malloc(తాత్కాలిక_కొలత);
            ఒకవేళ (!తాత్కాలిక_pixels) {
                తిరిగి false;
            }

            ఒకవేళ (!SDL_Convert_Pixels_MJPG_గమ్యం_NV12(వెడల్పు, ఎత్తు, src, src_pitch, తాత్కాలిక_pixels, (పూర్ణాంకం)తాత్కాలిక_pitch)) {
                SDL_free(తాత్కాలిక_pixels);
                తిరిగి false;
            }

            bool ఫలితం = SDL_ConvertPixelsAndColorspace(వెడల్పు, ఎత్తు, SDL_PIXELFORMAT_NV12, src_colorspace, 0 /*props*/, తాత్కాలిక_pixels, (పూర్ణాంకం)తాత్కాలిక_pitch, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
            SDL_free(తాత్కాలిక_pixels);
            తిరిగి ఫలితం;
        }
    }

    bool ఫలితం;
    పూర్ణాంకం w = 0, h = 0, format = 0;
    పూర్ణాంకం len = (src_format == SDL_PIXELFORMAT_MJPG) ? src_pitch : (ఎత్తు * src_pitch);
    శూన్య *pixels = stbi_ఎక్కించు_from_జ్ఞాపకం(src, len, &w, &h, &format, 4);
    ఒకవేళ (!pixels) {
        తిరిగి false;
    }

    ఒకవేళ (w == వెడల్పు && h == ఎత్తు) {
        ఫలితం = SDL_ConvertPixelsAndColorspace(w, h, SDL_PIXELFORMAT_RGBA32, SDL_COLORSPACE_SRGB, 0, pixels, వెడల్పు * 4, dst_format, dst_colorspace, dst_properties, dst, dst_pitch);
    } లేకపోతే {
        ఫలితం = SDL_సమితి_Error("Expected image size %dx%d, actual size %dx%d", వెడల్పు, ఎత్తు, w, h);
    }
    stbi_image_free(pixels);

    తిరిగి ఫలితం;
#లేకపోతే
    తిరిగి SDL_సమితి_Error("SDL not built with STB image support");
#అయితే_ముగింపు
}

#నిర్వచితమైతే SDL_HAVE_STB
స్థిర పూర్ణాంకం IMG_ఎక్కించు_STB_IO_read(శూన్య *user, అక్షరం *దత్తాంశం, పూర్ణాంకం కొలత)
{
    size_t amount = SDL_ReadIO((SDL_IOStream*)user, దత్తాంశం, కొలత);
    తిరిగి (పూర్ణాంకం)amount;
}

స్థిర శూన్య IMG_ఎక్కించు_STB_IO_skip(శూన్య *user, పూర్ణాంకం n)
{
    SDL_SeekIO((SDL_IOStream*)user, n, SDL_IO_SEEK_CUR);
}

స్థిర పూర్ణాంకం IMG_ఎక్కించు_STB_IO_eof(శూన్య *user)
{
    SDL_IOStream *src = (SDL_IOStream*)user;
    తిరిగి SDL_GetIOStatus(src) == SDL_IO_స్థితి_EOF;
}

స్థిర SDL_Surface *SDL_ఎక్కించు_STB_IO(SDL_IOStream *src)
{
    Sint64 ప్రారంభం;
    Uint8 magic[26];
    పూర్ణాంకం w, h, format;
    stbi_uc *pixels;
    stbi_io_callbacks rw_callbacks;
    SDL_Surface *surface = ఖాళీ;
    bool use_palette = false;
    గుర్తులేని పూర్ణాంకం palette_colors[256];

    // src has already been validated
    ప్రారంభం = SDL_TellIO(src);

    ఒకవేళ (SDL_ReadIO(src, magic, పరిమాణం(magic)) == పరిమాణం(magic)) {
        స్థిరరాశి Uint8 PNG_COLOR_సూచీకృత = 3;
        ఒకవేళ (magic[0] == 0x89 &&
            magic[1] == 'P' &&
            magic[2] == 'N' &&
            magic[3] == 'G' &&
            magic[12] == 'I' &&
            magic[13] == 'H' &&
            magic[14] == 'D' &&
            magic[15] == 'R' &&
            magic[25] == PNG_COLOR_సూచీకృత) {
            use_palette = true;
        }
    }
    SDL_SeekIO(src, ప్రారంభం, SDL_IO_SEEK_సమితి);

    /* Load the image data */
    rw_callbacks.పఠ = IMG_ఎక్కించు_STB_IO_read;
    rw_callbacks.skip = IMG_ఎక్కించు_STB_IO_skip;
    rw_callbacks.eof = IMG_ఎక్కించు_STB_IO_eof;
    w = h = format = 0; /* silence warning */
    ఒకవేళ (use_palette) {
        /* Unused palette entries will be opaque white */
        SDL_memset(palette_colors, 0xff, పరిమాణం(palette_colors));

        pixels = stbi_ఎక్కించు_from_callbacks_with_palette(
            &rw_callbacks,
            src,
            &w,
            &h,
            palette_colors,
            SDL_arraysize(palette_colors)
        );
    } లేకపోతే {
        pixels = stbi_ఎక్కించు_from_callbacks(
            &rw_callbacks,
            src,
            &w,
            &h,
            &format,
            STBI_default
        );
    }
    ఒకవేళ (!pixels) {
        SDL_SeekIO(src, ప్రారంభం, SDL_IO_SEEK_సమితి);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (use_palette) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w
        );
        ఒకవేళ (surface) {
            bool has_colorkey = false;
            పూర్ణాంకం colorkey_సూచీ = -1;
            bool has_alpha = false;
            SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
            ఒకవేళ (palette) {
                పూర్ణాంకం i;
                Uint8 *palette_బైట్లు = (Uint8 *)palette_colors;

                కొరకు (i = 0; i < palette->ncolors; i++) {
                    palette->colors[i].r = *palette_బైట్లు++;
                    palette->colors[i].g = *palette_బైట్లు++;
                    palette->colors[i].b = *palette_బైట్లు++;
                    palette->colors[i].a = *palette_బైట్లు++;
                    ఒకవేళ (palette->colors[i].a != SDL_ALPHA_OPAQUE) {
                        ఒకవేళ (palette->colors[i].a == SDL_ALPHA_TRANSPARENT && !has_colorkey) {
                            has_colorkey = true;
                            colorkey_సూచీ = i;
                        } లేకపోతే {
                            /* Partial opacity or multiple colorkeys */
                            has_alpha = true;
                        }
                    }
                }
            }
            ఒకవేళ (has_alpha) {
                SDL_సమితి_Surface_Blend_బహుళకం(surface, SDL_BLENDMODE_BLEND);
            } లేకపోతే ఒకవేళ (has_colorkey) {
                SDL_సమితి_Surface_Color_కీలకం(surface, true, colorkey_సూచీ);
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } లేకపోతే ఒకవేళ (format == STBI_grey || format == STBI_rgb || format == STBI_rgb_alpha) {
        surface = SDL_CreateSurfaceFrom(
            w,
            h,
            (format == STBI_rgb_alpha) ? SDL_PIXELFORMAT_RGBA32 :
            (format == STBI_rgb) ? SDL_PIXELFORMAT_RGB24 :
            SDL_PIXELFORMAT_INDEX8,
            pixels,
            w * format
        );
        ఒకవేళ (surface) {
            /* Set a grayscale palette for gray images */
            ఒకవేళ (surface->format == SDL_PIXELFORMAT_INDEX8) {
                SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
                ఒకవేళ (palette) {
                    పూర్ణాంకం i;

                    కొరకు (i = 0; i < palette->ncolors; i++) {
                        palette->colors[i].r = (Uint8)i;
                        palette->colors[i].g = (Uint8)i;
                        palette->colors[i].b = (Uint8)i;
                    }
                }
            }

            /* FIXME: This sucks. It'd be better to allocate the surface first, then
             * write directly to the pixel buffer:
             * https://github.com/nothings/stb/issues/58
             * -flibit
             */
            surface->flags &= ~SDL_SURFACE_PREALLOCATED;
        }

    } లేకపోతే ఒకవేళ (format == STBI_grey_alpha) {
        surface = SDL_CreateSurfaceUninitialized(w, h, SDL_PIXELFORMAT_RGBA32);
        ఒకవేళ (surface) {
            Uint8 *src_ptr = pixels;
            Uint8 *dst = (Uint8 *)surface->pixels;
            పూర్ణాంకం skip = surface->pitch - (surface->w * 4);
            పూర్ణాంకం అడ్డువరుస, నిలువు;

            కొరకు (అడ్డువరుస = 0; అడ్డువరుస < h; ++అడ్డువరుస) {
                కొరకు (నిలువు = 0; నిలువు < w; ++నిలువు) {
                    Uint8 c = *src_ptr++;
                    Uint8 a = *src_ptr++;
                    *dst++ = c;
                    *dst++ = c;
                    *dst++ = c;
                    *dst++ = a;
                }
                dst += skip;
            }
            stbi_image_free(pixels);
        }
    } లేకపోతే {
        SDL_సమితి_Error("Unknown image format: %d", format);
    }

    ఒకవేళ (!surface) {
        /* The error message should already be set */
        stbi_image_free(pixels); /* calls SDL_free() */
        SDL_SeekIO(src, ప్రారంభం, SDL_IO_SEEK_సమితి);
    }
    తిరిగి surface;
}
#అయితే_ముగింపు // SDL_HAVE_STB

/* FIXME: This is a copypaste from JPEGLIB! Pull that out of the ifdefs */
/* Define this for quicker (but less perfect) JPEG identification */
#నిర్వచించు FAST_IS_JPEG

/* See if an image is contained in a data source */
bool SDL_IsJPG(SDL_IOStream *src)
{
    Sint64 ప్రారంభం;
    bool is_JPG;
    bool లోపల_పరిశీలన;
    Uint8 magic[4];

    /* This detection code is by Steaphan Greene <stea@cs.binghamton.edu> */
    /* Blame me, not Sam, if this doesn't work right. */
    /* And don't forget to report the problem to the the sdl list too! */

    ఒకవేళ (!src) {
        తిరిగి false;
    }

    ప్రారంభం = SDL_TellIO(src);
    is_JPG = false;
    లోపల_పరిశీలన = false;
    ఒకవేళ (SDL_ReadIO(src, magic, 2) == 2) {
        ఒకవేళ ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
            is_JPG = true;
            అయితే (is_JPG) {
                ఒకవేళ (SDL_ReadIO(src, magic, 2) != 2) {
                    is_JPG = false;
                } లేకపోతే ఒకవేళ ( (magic[0] != 0xFF) && !లోపల_పరిశీలన ) {
                    is_JPG = false;
                } లేకపోతే ఒకవేళ ( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    SDL_SeekIO(src, -1, SDL_IO_SEEK_CUR);
                } లేకపోతే ఒకవేళ (magic[1] == 0xD9) {
                    /* Got to end of good JPEG */
                    ఆపు;
                } లేకపోతే ఒకవేళ ( లోపల_పరిశీలన && (magic[1] == 0x00) ) {
                    /* This is an encoded 0xFF within the data */
                } లేకపోతే ఒకవేళ ( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
                    /* These have nothing else */
                } లేకపోతే ఒకవేళ (SDL_ReadIO(src, magic+2, 2) != 2) {
                    is_JPG = false;
                } లేకపోతే {
                    /* Yes, it's big-endian */
                    Sint64 inner_ప్రారంభం;
                    Uint32 కొలత;
                    Sint64 చివర;
                    inner_ప్రారంభం = SDL_TellIO(src);
                    కొలత = (magic[2] << 8) + magic[3];
                    చివర = SDL_SeekIO(src, కొలత-2, SDL_IO_SEEK_CUR);
                    ఒకవేళ ( చివర != inner_ప్రారంభం + కొలత - 2 ) {
                        is_JPG = false;
                    }
                    ఒకవేళ ( magic[1] == 0xDA ) {
                        /* Now comes the actual JPEG meat */
#నిర్వచితమైతే  FAST_IS_JPEG
                        /* Ok, I'm convinced.  It is a JPEG. */
                        ఆపు;
#లేకపోతే
                        /* I'm not convinced.  Prove it! */
                        లోపల_పరిశీలన = true;
#అయితే_ముగింపు
                    }
                }
            }
        }
    }
    SDL_SeekIO(src, ప్రారంభం, SDL_IO_SEEK_సమితి);
    తిరిగి is_JPG;
}

SDL_Surface *SDL_ఎక్కించు_JPG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ఖాళీ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        వెళ్ళు పూర్తి;
    }

    ఒకవేళ (!SDL_IsJPG(src)) {
        SDL_సమితి_Error("File is not a JPEG file");
        వెళ్ళు పూర్తి;
    }

#నిర్వచితమైతే SDL_HAVE_STB
    surface = SDL_ఎక్కించు_STB_IO(src);
#లేకపోతే
    SDL_సమితి_Error("SDL not built with STB image support");
#అయితే_ముగింపు // SDL_HAVE_STB

పూర్తి:
    ఒకవేళ (src && closeio) {
        SDL_CloseIO(src);
    }
    తిరిగి surface;
}

SDL_Surface *SDL_ఎక్కించు_JPG(స్థిరరాశి అక్షరం *file)
{
    SDL_IOStream *ప్రవాహం = SDL_IOFromFile(file, "rb");
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి ఖాళీ;
    }

    తిరిగి SDL_ఎక్కించు_JPG_IO(ప్రవాహం, true);
}

bool SDL_IsPNG(SDL_IOStream *src)
{
    Sint64 ప్రారంభం;
    Uint8 magic[4];
    bool is_PNG;

    is_PNG = false;
    ప్రారంభం = SDL_TellIO(src);
    ఒకవేళ (ప్రారంభం >= 0) {
        ఒకవేళ (SDL_ReadIO(src, magic, పరిమాణం(magic)) == పరిమాణం(magic)) {
            ఒకవేళ (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G') {
                is_PNG = true;
            }
        }
        SDL_SeekIO(src, ప్రారంభం, SDL_IO_SEEK_సమితి);
    }

    తిరిగి is_PNG;
}

SDL_Surface *SDL_ఎక్కించు_PNG_IO(SDL_IOStream *src, bool closeio)
{
    SDL_Surface *surface = ఖాళీ;

    CHECK_PARAM(!src) {
        SDL_InvalidParamError("src");
        వెళ్ళు పూర్తి;
    }

    ఒకవేళ (!SDL_IsPNG(src)) {
        SDL_సమితి_Error("File is not a PNG file");
        వెళ్ళు పూర్తి;
    }

#నిర్వచితమైతే SDL_HAVE_STB
    surface = SDL_ఎక్కించు_STB_IO(src);
#లేకపోతే
    SDL_సమితి_Error("SDL not built with STB image support");
#అయితే_ముగింపు // SDL_HAVE_STB

పూర్తి:
    ఒకవేళ (src && closeio) {
        SDL_CloseIO(src);
    }
    తిరిగి surface;
}

SDL_Surface *SDL_ఎక్కించు_PNG(స్థిరరాశి అక్షరం *file)
{
    SDL_IOStream *ప్రవాహం = SDL_IOFromFile(file, "rb");
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి ఖాళీ;
    }

    తిరిగి SDL_ఎక్కించు_PNG_IO(ప్రవాహం, true);
}

bool SDL_SavePNG_IO(SDL_Surface *surface, SDL_IOStream *dst, bool closeio)
{
    bool retval = false;
    Uint8 *plte = ఖాళీ;
    Uint8 *trns = ఖాళీ;
    bool free_surface = false;

    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        SDL_InvalidParamError("surface");
        వెళ్ళు పూర్తి;
    }
    CHECK_PARAM(!dst) {
        SDL_InvalidParamError("dst");
        వెళ్ళు పూర్తి;
    }

#నిర్వచితమైతే SDL_HAVE_STB
    పూర్ణాంకం plte_కొలత = 0;
    పూర్ణాంకం trns_కొలత = 0;

    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
        ఒకవేళ (!surface->palette) {
            SDL_సమితి_Error("Indexed surfaces must have a palette");
            వెళ్ళు పూర్తి;
        }

        ఒకవేళ (surface->format != SDL_PIXELFORMAT_INDEX8) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_INDEX8);
            ఒకవేళ (!surface) {
                వెళ్ళు పూర్తి;
            }
            free_surface = true;
        }

        plte_కొలత = surface->palette->ncolors * 3;
        trns_కొలత = surface->palette->ncolors;
        plte = (Uint8 *)SDL_malloc(plte_కొలత);
        trns = (Uint8 *)SDL_malloc(trns_కొలత);
        ఒకవేళ (!plte || !trns) {
            వెళ్ళు పూర్తి;
        }
        SDL_Color *colors = surface->palette->colors;
        కొరకు (పూర్ణాంకం i = 0; i < surface->palette->ncolors; ++i) {
            plte[i * 3 + 0] = colors[i].r;
            plte[i * 3 + 1] = colors[i].g;
            plte[i * 3 + 2] = colors[i].b;
            trns[i] = colors[i].a;
        }
    } లేకపోతే {
        ఒకవేళ (surface->format != SDL_PIXELFORMAT_RGBA32) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            ఒకవేళ (!surface) {
                వెళ్ళు పూర్తి;
            }
            free_surface = true;
        }
    }

    size_t కొలత = 0;
    శూన్య *png = tdefl_write_image_గమ్యం_png_file_లోపల_జ్ఞాపకం_ex(surface->pixels, surface->w, surface->h, SDL_BYTESPERPIXEL(surface->format), surface->pitch, &కొలత, 6, MZ_FALSE, plte, plte_కొలత, trns, trns_కొలత);
    ఒకవేళ (png) {
        ఒకవేళ (SDL_WriteIO(dst, png, కొలత)) {
            retval = true;
        }
        mz_free(png); /* calls SDL_free() */
    } లేకపోతే {
        SDL_సమితి_Error("Failed to convert and save image");
    }

#లేకపోతే
    SDL_సమితి_Error("SDL not built with STB image support");
#అయితే_ముగింపు

పూర్తి:
    ఒకవేళ (free_surface) {
        SDL_DestroySurface(surface);
    }
    SDL_free(plte);
    SDL_free(trns);

    ఒకవేళ (dst && closeio) {
        retval &= SDL_CloseIO(dst);
    }
    తిరిగి retval;
}

bool SDL_SavePNG(SDL_Surface *surface, స్థిరరాశి అక్షరం *file)
{
#నిర్వచితమైతే SDL_HAVE_STB
    // Make sure we have something to save
    CHECK_PARAM(!SDL_SurfaceValid(surface)) {
        తిరిగి SDL_InvalidParamError("surface");
    }

    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(surface->format) && !surface->palette) {
        తిరిగి SDL_సమితి_Error("Indexed surfaces must have a palette");
    }
    SDL_IOStream *ప్రవాహం = SDL_IOFromFile(file, "wb");
    ఒకవేళ (!ప్రవాహం) {
        తిరిగి false;
    }

    తిరిగి SDL_SavePNG_IO(surface, ప్రవాహం, true);
#లేకపోతే
    తిరిగి SDL_సమితి_Error("SDL not built with STB image support");
#అయితే_ముగింపు
}

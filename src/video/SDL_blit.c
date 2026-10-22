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

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_blit_auto.h"
#अन्तर्भाव "SDL_blit_copy.h"
#अन्तर्भाव "SDL_blit_slow.h"
#अन्तर्भाव "SDL_RLEaccel_c.h"
#अन्तर्भाव "SDL_pixels_c.h"

// The general purpose software blit routine
स्थिर bool SDLCALL SDL_SoftBlit(SDL_Surface *src, ध्रुव SDL_Rect *srcrect,
                                SDL_Surface *dst, ध्रुव SDL_Rect *dstrect)
{
    bool okay;
    पूर्णाङ्क src_locked;
    पूर्णाङ्क dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    यदि (SDL_MUSTLOCK(dst)) {
        यदि (!SDL_तालकम्_Surface(dst)) {
            okay = false;
        } अन्यथा {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    यदि (SDL_MUSTLOCK(src)) {
        यदि (!SDL_तालकम्_Surface(src)) {
            okay = false;
        } अन्यथा {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    यदि (okay) {
        SDL_BlitFunc सततम्_Blit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        यदि (info->src_fmt->द्वयङ्काः_प्रत्येकम्_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->अष्टकानि_प्रत्येकम्_pixel;
        } अन्यथा {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        (srcrect->x * info->src_fmt->द्वयङ्काः_प्रत्येकम्_pixel) / 8;
            info->leading_skip =
                        ((srcrect->x * info->src_fmt->द्वयङ्काः_प्रत्येकम्_pixel) % 8) /
                        info->src_fmt->द्वयङ्काः_प्रत्येकम्_pixel;
        }
        info->src_w = srcrect->w;
        info->src_h = srcrect->h;
        info->src_pitch = src->pitch;
        info->src_skip =
            info->src_pitch - info->src_w * info->src_fmt->अष्टकानि_प्रत्येकम्_pixel;
        info->dst = (Uint8 *)dst->pixels +
                    dstrect->y * dst->pitch +
                    dstrect->x * info->dst_fmt->अष्टकानि_प्रत्येकम्_pixel;
        info->dst_w = dstrect->w;
        info->dst_h = dstrect->h;
        info->dst_pitch = dst->pitch;
        info->dst_skip =
            info->dst_pitch - info->dst_w * info->dst_fmt->अष्टकानि_प्रत्येकम्_pixel;
        सततम्_Blit = (SDL_BlitFunc)src->map.दत्त;

        // Run the actual software blit
        सततम्_Blit(info);
    }

    // We need to unlock the surfaces if they're locked
    यदि (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    यदि (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    प्रत्यागम okay;
}

#यदि_परिभाषितम् SDL_HAVE_BLIT_AUTO

स्थिर SDL_BlitFunc SDL_वृणु_Blit_Func(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, पूर्णाङ्क flags,
                                       SDL_Blit_Func_प्रविष्टिः *entries)
{
    पूर्णाङ्क i, flagcheck = (flags & (SDL_COPY_MODULATE_आवरणम् | SDL_COPY_BLEND_आवरणम् | SDL_COPY_COLORKEY | SDL_COPY_निकटतमः));

    प्रति (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        यदि (src_format != entries[i].src_format) {
            अनुवर्त;
        }
        यदि (dst_format != entries[i].dst_format) {
            अनुवर्त;
        }

        // Check flags
        यदि ((flagcheck & entries[i].flags) != flagcheck) {
            अनुवर्त;
        }

        // We found the best one!
        प्रत्यागम entries[i].func;
    }
    प्रत्यागम रिक्त;
}
#यदि_अन्तः // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = रिक्त;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    यदि (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        प्रत्यागम SDL_समुच्चयः_Error("Blit combination not supported");
    }

    // We should have cleared out RLE at this point
    SDL_assert(!(surface->आन्तरिकम्_flags & SDL_आन्तरिकम्_SURFACE_RLEACCEL));

    map->blit = SDL_SoftBlit;
    map->info.src_surface = surface;
    map->info.src_fmt = surface->fmt;
    map->info.src_pal = surface->palette;
    map->info.dst_surface = dst;
    map->info.dst_fmt = dst->fmt;
    map->info.dst_pal = dst->palette;

#यदि_परिभाषितम् SDL_HAVE_RLE
    // See if we can do RLE acceleration
    यदि (map->info.flags & SDL_COPY_RLE_DESIRED) {
        यदि (SDL_RLESurface(surface)) {
            प्रत्यागम true;
        }
    }
#यदि_अन्तः

    // Choose a standard blit function
    यदि (!blit) {
        यदि (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    यदि (!blit) {
        यदि (map->तटस्थः && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } अन्यथा यदि (SDL_ISPIXELFORMAT_10BIT(surface->format) ||
                   SDL_ISPIXELFORMAT_10BIT(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#यदि_परिभाषितम् SDL_HAVE_BLIT_0
        अन्यथा यदि (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#यदि_अन्तः
#यदि_परिभाषितम् SDL_HAVE_BLIT_1
        अन्यथा यदि (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_अनुक्रमितम्(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#यदि_अन्तः
#यदि_परिभाषितम् SDL_HAVE_BLIT_A
        अन्यथा यदि (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#यदि_अन्तः
#यदि_परिभाषितम् SDL_HAVE_BLIT_N
        अन्यथा {
            blit = SDL_CalculateBlitN(surface);
        }
#यदि_अन्तः
    }
#यदि_परिभाषितम् SDL_HAVE_BLIT_AUTO
    यदि (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_वृणु_Blit_Func(src_format, dst_format, map->info.flags,
                               SDL_Generated_Blit_Func_सारणी);
    }
#यदि_अन्तः

#यदि_अपरिभाषितम् TEST_SLOW_BLIT
    यदि (!blit)
#यदि_अन्तः
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        यदि ((!SDL_ISPIXELFORMAT_अनुक्रमितम्(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_अनुक्रमितम्(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->दत्त = (शून्य *)blit;

    // Make sure we have a blit function
    यदि (!blit) {
        SDL_InvalidateMap(map);
        प्रत्यागम SDL_समुच्चयः_Error("Blit combination not supported");
    }

    प्रत्यागम true;
}

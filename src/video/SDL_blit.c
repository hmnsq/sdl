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

#అన్తర్భావ "SDL_sysvideo.h"
#అన్తర్భావ "SDL_surface_c.h"
#అన్తర్భావ "SDL_blit_auto.h"
#అన్తర్భావ "SDL_blit_copy.h"
#అన్తర్భావ "SDL_blit_slow.h"
#అన్తర్భావ "SDL_RLEaccel_c.h"
#అన్తర్భావ "SDL_pixels_c.h"

// The general purpose software blit routine
స్థిర bool SDLCALL SDL_SoftBlit(SDL_Surface *src, స్థిరరాశి SDL_Rect *srcrect,
                                SDL_Surface *dst, స్థిరరాశి SDL_Rect *dstrect)
{
    bool okay;
    పూర్ణాంకం src_locked;
    పూర్ణాంకం dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    ఒకవేళ (SDL_MUSTLOCK(dst)) {
        ఒకవేళ (!SDL_తాళం_Surface(dst)) {
            okay = false;
        } లేకపోతే {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    ఒకవేళ (SDL_MUSTLOCK(src)) {
        ఒకవేళ (!SDL_తాళం_Surface(src)) {
            okay = false;
        } లేకపోతే {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    ఒకవేళ (okay) {
        SDL_BlitFunc నిరంతరం_Blit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        ఒకవేళ (info->src_fmt->బిట్లు_చొప్పున_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->బైట్లు_చొప్పున_pixel;
        } లేకపోతే {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        (srcrect->x * info->src_fmt->బిట్లు_చొప్పున_pixel) / 8;
            info->leading_skip =
                        ((srcrect->x * info->src_fmt->బిట్లు_చొప్పున_pixel) % 8) /
                        info->src_fmt->బిట్లు_చొప్పున_pixel;
        }
        info->src_w = srcrect->w;
        info->src_h = srcrect->h;
        info->src_pitch = src->pitch;
        info->src_skip =
            info->src_pitch - info->src_w * info->src_fmt->బైట్లు_చొప్పున_pixel;
        info->dst = (Uint8 *)dst->pixels +
                    dstrect->y * dst->pitch +
                    dstrect->x * info->dst_fmt->బైట్లు_చొప్పున_pixel;
        info->dst_w = dstrect->w;
        info->dst_h = dstrect->h;
        info->dst_pitch = dst->pitch;
        info->dst_skip =
            info->dst_pitch - info->dst_w * info->dst_fmt->బైట్లు_చొప్పున_pixel;
        నిరంతరం_Blit = (SDL_BlitFunc)src->map.దత్తాంశం;

        // Run the actual software blit
        నిరంతరం_Blit(info);
    }

    // We need to unlock the surfaces if they're locked
    ఒకవేళ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    ఒకవేళ (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    తిరిగి okay;
}

#నిర్వచితమైతే SDL_HAVE_BLIT_AUTO

స్థిర SDL_BlitFunc SDL_ఎంచుకో_Blit_Func(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, పూర్ణాంకం flags,
                                       SDL_Blit_Func_నమోదు *entries)
{
    పూర్ణాంకం i, flagcheck = (flags & (SDL_COPY_MODULATE_ముసుగు | SDL_COPY_BLEND_ముసుగు | SDL_COPY_COLORKEY | SDL_COPY_సమీప));

    కొరకు (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        ఒకవేళ (src_format != entries[i].src_format) {
            కొనసాగు;
        }
        ఒకవేళ (dst_format != entries[i].dst_format) {
            కొనసాగు;
        }

        // Check flags
        ఒకవేళ ((flagcheck & entries[i].flags) != flagcheck) {
            కొనసాగు;
        }

        // We found the best one!
        తిరిగి entries[i].func;
    }
    తిరిగి ఖాళీ;
}
#అయితే_ముగింపు // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = ఖాళీ;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    ఒకవేళ (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        తిరిగి SDL_సమితి_Error("Blit combination not supported");
    }

    // We should have cleared out RLE at this point
    SDL_assert(!(surface->అంతర్గత_flags & SDL_అంతర్గత_SURFACE_RLEACCEL));

    map->blit = SDL_SoftBlit;
    map->info.src_surface = surface;
    map->info.src_fmt = surface->fmt;
    map->info.src_pal = surface->palette;
    map->info.dst_surface = dst;
    map->info.dst_fmt = dst->fmt;
    map->info.dst_pal = dst->palette;

#నిర్వచితమైతే SDL_HAVE_RLE
    // See if we can do RLE acceleration
    ఒకవేళ (map->info.flags & SDL_COPY_RLE_DESIRED) {
        ఒకవేళ (SDL_RLESurface(surface)) {
            తిరిగి true;
        }
    }
#అయితే_ముగింపు

    // Choose a standard blit function
    ఒకవేళ (!blit) {
        ఒకవేళ (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    ఒకవేళ (!blit) {
        ఒకవేళ (map->తటస్థం && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } లేకపోతే ఒకవేళ (SDL_ISPIXELFORMAT_10_బిట్టు(surface->format) ||
                   SDL_ISPIXELFORMAT_10_బిట్టు(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#నిర్వచితమైతే SDL_HAVE_BLIT_0
        లేకపోతే ఒకవేళ (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_HAVE_BLIT_1
        లేకపోతే ఒకవేళ (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_సూచీకృత(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_HAVE_BLIT_A
        లేకపోతే ఒకవేళ (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_HAVE_BLIT_N
        లేకపోతే {
            blit = SDL_CalculateBlitN(surface);
        }
#అయితే_ముగింపు
    }
#నిర్వచితమైతే SDL_HAVE_BLIT_AUTO
    ఒకవేళ (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_ఎంచుకో_Blit_Func(src_format, dst_format, map->info.flags,
                               SDL_Generated_Blit_Func_పట్టిక);
    }
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే TEST_SLOW_BLIT
    ఒకవేళ (!blit)
#అయితే_ముగింపు
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        ఒకవేళ ((!SDL_ISPIXELFORMAT_సూచీకృత(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_సూచీకృత(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->దత్తాంశం = (శూన్య *)blit;

    // Make sure we have a blit function
    ఒకవేళ (!blit) {
        SDL_InvalidateMap(map);
        తిరిగి SDL_సమితి_Error("Blit combination not supported");
    }

    తిరిగి true;
}

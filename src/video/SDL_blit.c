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

#அந்தர்பாவ "SDL_sysvideo.h"
#அந்தர்பாவ "SDL_surface_c.h"
#அந்தர்பாவ "SDL_blit_auto.h"
#அந்தர்பாவ "SDL_blit_copy.h"
#அந்தர்பாவ "SDL_blit_slow.h"
#அந்தர்பாவ "SDL_RLEaccel_c.h"
#அந்தர்பாவ "SDL_pixels_c.h"

// The general purpose software blit routine
நிலையான bool SDLCALL SDL_SoftBlit(SDL_Surface *src, மாறிலி SDL_Rect *srcrect,
                                SDL_Surface *dst, மாறிலி SDL_Rect *dstrect)
{
    bool okay;
    முழு src_locked;
    முழு dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    எனில் (SDL_MUSTLOCK(dst)) {
        எனில் (!SDL_LockSurface(dst)) {
            okay = false;
        } இல்லையெனில் {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    எனில் (SDL_MUSTLOCK(src)) {
        எனில் (!SDL_LockSurface(src)) {
            okay = false;
        } இல்லையெனில் {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    எனில் (okay) {
        SDL_BlitFunc RunBlit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        எனில் (info->src_fmt->bits_per_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->bytes_per_pixel;
        } இல்லையெனில் {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        (srcrect->x * info->src_fmt->bits_per_pixel) / 8;
            info->leading_skip =
                        ((srcrect->x * info->src_fmt->bits_per_pixel) % 8) /
                        info->src_fmt->bits_per_pixel;
        }
        info->src_w = srcrect->w;
        info->src_h = srcrect->h;
        info->src_pitch = src->pitch;
        info->src_skip =
            info->src_pitch - info->src_w * info->src_fmt->bytes_per_pixel;
        info->dst = (Uint8 *)dst->pixels +
                    dstrect->y * dst->pitch +
                    dstrect->x * info->dst_fmt->bytes_per_pixel;
        info->dst_w = dstrect->w;
        info->dst_h = dstrect->h;
        info->dst_pitch = dst->pitch;
        info->dst_skip =
            info->dst_pitch - info->dst_w * info->dst_fmt->bytes_per_pixel;
        RunBlit = (SDL_BlitFunc)src->map.data;

        // Run the actual software blit
        RunBlit(info);
    }

    // We need to unlock the surfaces if they're locked
    எனில் (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    எனில் (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    திரும்பு okay;
}

#ifdef SDL_HAVE_BLIT_AUTO

நிலையான SDL_BlitFunc SDL_ChooseBlitFunc(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, முழு flags,
                                       SDL_BlitFuncEntry *entries)
{
    முழு i, flagcheck = (flags & (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY | SDL_COPY_NEAREST));

    க்கு (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        எனில் (src_format != entries[i].src_format) {
            தொடர்;
        }
        எனில் (dst_format != entries[i].dst_format) {
            தொடர்;
        }

        // Check flags
        எனில் ((flagcheck & entries[i].flags) != flagcheck) {
            தொடர்;
        }

        // We found the best one!
        திரும்பு entries[i].func;
    }
    திரும்பு வெற்று;
}
#endif // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = வெற்று;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    எனில் (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        திரும்பு SDL_SetError("Blit combination not supported");
    }

    // We should have cleared out RLE at this point
    SDL_assert(!(surface->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL));

    map->blit = SDL_SoftBlit;
    map->info.src_surface = surface;
    map->info.src_fmt = surface->fmt;
    map->info.src_pal = surface->palette;
    map->info.dst_surface = dst;
    map->info.dst_fmt = dst->fmt;
    map->info.dst_pal = dst->palette;

#ifdef SDL_HAVE_RLE
    // See if we can do RLE acceleration
    எனில் (map->info.flags & SDL_COPY_RLE_DESIRED) {
        எனில் (SDL_RLESurface(surface)) {
            திரும்பு true;
        }
    }
#endif

    // Choose a standard blit function
    எனில் (!blit) {
        எனில் (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    எனில் (!blit) {
        எனில் (map->identity && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_10BIT(surface->format) ||
                   SDL_ISPIXELFORMAT_10BIT(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#ifdef SDL_HAVE_BLIT_0
        இல்லையெனில் எனில் (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_1
        இல்லையெனில் எனில் (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_A
        இல்லையெனில் எனில் (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_N
        இல்லையெனில் {
            blit = SDL_CalculateBlitN(surface);
        }
#endif
    }
#ifdef SDL_HAVE_BLIT_AUTO
    எனில் (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_ChooseBlitFunc(src_format, dst_format, map->info.flags,
                               SDL_GeneratedBlitFuncTable);
    }
#endif

#ifndef TEST_SLOW_BLIT
    எனில் (!blit)
#endif
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        எனில் ((!SDL_ISPIXELFORMAT_INDEXED(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_INDEXED(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->data = (வெறுமை *)blit;

    // Make sure we have a blit function
    எனில் (!blit) {
        SDL_InvalidateMap(map);
        திரும்பு SDL_SetError("Blit combination not supported");
    }

    திரும்பு true;
}

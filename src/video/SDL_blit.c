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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_surface_c.h"
#અન્તર્ભાવ "SDL_blit_auto.h"
#અન્તર્ભાવ "SDL_blit_copy.h"
#અન્તર્ભાવ "SDL_blit_slow.h"
#અન્તર્ભાવ "SDL_RLEaccel_c.h"
#અન્તર્ભાવ "SDL_pixels_c.h"

// The general purpose software blit routine
સ્થિર bool SDLCALL SDL_SoftBlit(SDL_Surface *src, અચલ SDL_Rect *srcrect,
                                SDL_Surface *dst, અચલ SDL_Rect *dstrect)
{
    bool okay;
    પૂર્ણાંક src_locked;
    પૂર્ણાંક dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    જો (SDL_MUSTLOCK(dst)) {
        જો (!SDL_LockSurface(dst)) {
            okay = false;
        } નહીંતર {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    જો (SDL_MUSTLOCK(src)) {
        જો (!SDL_LockSurface(src)) {
            okay = false;
        } નહીંતર {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    જો (okay) {
        SDL_BlitFunc RunBlit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        જો (info->src_fmt->bits_per_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->bytes_per_pixel;
        } નહીંતર {
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
    જો (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    જો (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    પાછા okay;
}

#ifdef SDL_HAVE_BLIT_AUTO

સ્થિર SDL_BlitFunc SDL_ChooseBlitFunc(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, પૂર્ણાંક flags,
                                       SDL_BlitFuncEntry *entries)
{
    પૂર્ણાંક i, flagcheck = (flags & (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY | SDL_COPY_NEAREST));

    માટે (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        જો (src_format != entries[i].src_format) {
            ચાલુ;
        }
        જો (dst_format != entries[i].dst_format) {
            ચાલુ;
        }

        // Check flags
        જો ((flagcheck & entries[i].flags) != flagcheck) {
            ચાલુ;
        }

        // We found the best one!
        પાછા entries[i].func;
    }
    પાછા ખાલી;
}
#endif // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = ખાલી;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    જો (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        પાછા SDL_SetError("Blit combination not supported");
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
    જો (map->info.flags & SDL_COPY_RLE_DESIRED) {
        જો (SDL_RLESurface(surface)) {
            પાછા true;
        }
    }
#endif

    // Choose a standard blit function
    જો (!blit) {
        જો (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    જો (!blit) {
        જો (map->identity && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } નહીંતર જો (SDL_ISPIXELFORMAT_10BIT(surface->format) ||
                   SDL_ISPIXELFORMAT_10BIT(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#ifdef SDL_HAVE_BLIT_0
        નહીંતર જો (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_1
        નહીંતર જો (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_A
        નહીંતર જો (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_N
        નહીંતર {
            blit = SDL_CalculateBlitN(surface);
        }
#endif
    }
#ifdef SDL_HAVE_BLIT_AUTO
    જો (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_ChooseBlitFunc(src_format, dst_format, map->info.flags,
                               SDL_GeneratedBlitFuncTable);
    }
#endif

#ifndef TEST_SLOW_BLIT
    જો (!blit)
#endif
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        જો ((!SDL_ISPIXELFORMAT_INDEXED(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_INDEXED(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->data = (શૂન્ય *)blit;

    // Make sure we have a blit function
    જો (!blit) {
        SDL_InvalidateMap(map);
        પાછા SDL_SetError("Blit combination not supported");
    }

    પાછા true;
}

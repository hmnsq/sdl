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
#include "SDL_internal.h"

#include "SDL_sysvideo.h"
#include "SDL_surface_c.h"
#include "SDL_blit_auto.h"
#include "SDL_blit_copy.h"
#include "SDL_blit_slow.h"
#include "SDL_RLEaccel_c.h"
#include "SDL_pixels_c.h"

// The general purpose software blit routine
static bool SDLCALL SDL_SoftBlit(SDL_Surface *src, const SDL_Rect *srcrect,
                                SDL_Surface *dst, const SDL_Rect *dstrect)
{
    bool okay;
    ကိန်းပြည့် src_locked;
    ကိန်းပြည့် dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    အကယ်၍ (SDL_MUSTLOCK(dst)) {
        အကယ်၍ (!SDL_LockSurface(dst)) {
            okay = false;
        } မဟုတ်ပါက {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    အကယ်၍ (SDL_MUSTLOCK(src)) {
        အကယ်၍ (!SDL_LockSurface(src)) {
            okay = false;
        } မဟုတ်ပါက {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    အကယ်၍ (okay) {
        SDL_BlitFunc RunBlit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        အကယ်၍ (info->src_fmt->bits_per_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->bytes_per_pixel;
        } မဟုတ်ပါက {
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
    အကယ်၍ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    အကယ်၍ (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    ပြန်ပေး okay;
}

#ifdef SDL_HAVE_BLIT_AUTO

static SDL_BlitFunc SDL_ChooseBlitFunc(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, ကိန်းပြည့် flags,
                                       SDL_BlitFuncEntry *entries)
{
    ကိန်းပြည့် i, flagcheck = (flags & (SDL_COPY_MODULATE_MASK | SDL_COPY_BLEND_MASK | SDL_COPY_COLORKEY | SDL_COPY_NEAREST));

    အတွက် (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        အကယ်၍ (src_format != entries[i].src_format) {
            continue;
        }
        အကယ်၍ (dst_format != entries[i].dst_format) {
            continue;
        }

        // Check flags
        အကယ်၍ ((flagcheck & entries[i].flags) != flagcheck) {
            continue;
        }

        // We found the best one!
        ပြန်ပေး entries[i].func;
    }
    ပြန်ပေး NULL;
}
#endif // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = NULL;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    အကယ်၍ (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        ပြန်ပေး SDL_SetError("Blit combination not supported");
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
    အကယ်၍ (map->info.flags & SDL_COPY_RLE_DESIRED) {
        အကယ်၍ (SDL_RLESurface(surface)) {
            ပြန်ပေး true;
        }
    }
#endif

    // Choose a standard blit function
    အကယ်၍ (!blit) {
        အကယ်၍ (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    အကယ်၍ (!blit) {
        အကယ်၍ (map->identity && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } မဟုတ်ပါက အကယ်၍ (SDL_ISPIXELFORMAT_10BIT(surface->format) ||
                   SDL_ISPIXELFORMAT_10BIT(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#ifdef SDL_HAVE_BLIT_0
        မဟုတ်ပါက အကယ်၍ (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_1
        မဟုတ်ပါက အကယ်၍ (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_INDEXED(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_A
        မဟုတ်ပါက အကယ်၍ (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#endif
#ifdef SDL_HAVE_BLIT_N
        မဟုတ်ပါက {
            blit = SDL_CalculateBlitN(surface);
        }
#endif
    }
#ifdef SDL_HAVE_BLIT_AUTO
    အကယ်၍ (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_ChooseBlitFunc(src_format, dst_format, map->info.flags,
                               SDL_GeneratedBlitFuncTable);
    }
#endif

#ifndef TEST_SLOW_BLIT
    အကယ်၍ (!blit)
#endif
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        အကယ်၍ ((!SDL_ISPIXELFORMAT_INDEXED(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_INDEXED(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->data = (void *)blit;

    // Make sure we have a blit function
    အကယ်၍ (!blit) {
        SDL_InvalidateMap(map);
        ပြန်ပေး SDL_SetError("Blit combination not supported");
    }

    ပြန်ပေး true;
}

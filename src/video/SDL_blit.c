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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit_auto.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit_copy.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit_slow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_RLEaccel_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"

// The general purpose software blit routine
ਸਥਿਰ bool SDLCALL SDL_SoftBlit(SDL_Surface *src, ਅਚਲ SDL_Rect *srcrect,
                                SDL_Surface *dst, ਅਚਲ SDL_Rect *dstrect)
{
    bool okay;
    ਪੂਰਨ src_locked;
    ਪੂਰਨ dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    ਜੇ (SDL_MUSTLOCK(dst)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(dst)) {
            okay = false;
        } ਨਹੀਂਤਾਂ {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    ਜੇ (SDL_MUSTLOCK(src)) {
        ਜੇ (!SDL_ਤਾਲਾ_Surface(src)) {
            okay = false;
        } ਨਹੀਂਤਾਂ {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    ਜੇ (okay) {
        SDL_BlitFunc ਲੜੀਵਾਰ_Blit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        ਜੇ (info->src_fmt->ਬਿੱਟ_ਪ੍ਰਤੀ_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        } ਨਹੀਂਤਾਂ {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        (srcrect->x * info->src_fmt->ਬਿੱਟ_ਪ੍ਰਤੀ_pixel) / 8;
            info->leading_skip =
                        ((srcrect->x * info->src_fmt->ਬਿੱਟ_ਪ੍ਰਤੀ_pixel) % 8) /
                        info->src_fmt->ਬਿੱਟ_ਪ੍ਰਤੀ_pixel;
        }
        info->src_w = srcrect->w;
        info->src_h = srcrect->h;
        info->src_pitch = src->pitch;
        info->src_skip =
            info->src_pitch - info->src_w * info->src_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        info->dst = (Uint8 *)dst->pixels +
                    dstrect->y * dst->pitch +
                    dstrect->x * info->dst_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        info->dst_w = dstrect->w;
        info->dst_h = dstrect->h;
        info->dst_pitch = dst->pitch;
        info->dst_skip =
            info->dst_pitch - info->dst_w * info->dst_fmt->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        ਲੜੀਵਾਰ_Blit = (SDL_BlitFunc)src->map.ਅੰਕੜੇ;

        // Run the actual software blit
        ਲੜੀਵਾਰ_Blit(info);
    }

    // We need to unlock the surfaces if they're locked
    ਜੇ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    ਜੇ (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    ਵਾਪਸ okay;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_AUTO

ਸਥਿਰ SDL_BlitFunc SDL_ਚੁਣੋ_Blit_Func(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, ਪੂਰਨ flags,
                                       SDL_Blit_Func_ਇੰਦਰਾਜ *entries)
{
    ਪੂਰਨ i, flagcheck = (flags & (SDL_COPY_MODULATE_ਨਕਾਬ | SDL_COPY_BLEND_ਨਕਾਬ | SDL_COPY_COLORKEY | SDL_COPY_ਸਭ_ਤੋਂ_ਨੇੜੇ));

    ਲਈ (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        ਜੇ (src_format != entries[i].src_format) {
            ਜਾਰੀ;
        }
        ਜੇ (dst_format != entries[i].dst_format) {
            ਜਾਰੀ;
        }

        // Check flags
        ਜੇ ((flagcheck & entries[i].flags) != flagcheck) {
            ਜਾਰੀ;
        }

        // We found the best one!
        ਵਾਪਸ entries[i].func;
    }
    ਵਾਪਸ ਨਿਰਾ;
}
#ਜੇ_ਅੰਤ // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = ਨਿਰਾ;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    ਜੇ (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Blit combination not supported");
    }

    // We should have cleared out RLE at this point
    SDL_assert(!(surface->ਅੰਦਰੂਨੀ_flags & SDL_ਅੰਦਰੂਨੀ_SURFACE_RLEACCEL));

    map->blit = SDL_SoftBlit;
    map->info.src_surface = surface;
    map->info.src_fmt = surface->fmt;
    map->info.src_pal = surface->palette;
    map->info.dst_surface = dst;
    map->info.dst_fmt = dst->fmt;
    map->info.dst_pal = dst->palette;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_RLE
    // See if we can do RLE acceleration
    ਜੇ (map->info.flags & SDL_COPY_RLE_DESIRED) {
        ਜੇ (SDL_RLESurface(surface)) {
            ਵਾਪਸ true;
        }
    }
#ਜੇ_ਅੰਤ

    // Choose a standard blit function
    ਜੇ (!blit) {
        ਜੇ (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    ਜੇ (!blit) {
        ਜੇ (map->ਪਛਾਣ_ਤੱਤ && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_ISPIXELFORMAT_10_ਦੋਆਧਾਰੀ_ਅੰਕ(surface->format) ||
                   SDL_ISPIXELFORMAT_10_ਦੋਆਧਾਰੀ_ਅੰਕ(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_0
        ਨਹੀਂਤਾਂ ਜੇ (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_1
        ਨਹੀਂਤਾਂ ਜੇ (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_A
        ਨਹੀਂਤਾਂ ਜੇ (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_N
        ਨਹੀਂਤਾਂ {
            blit = SDL_CalculateBlitN(surface);
        }
#ਜੇ_ਅੰਤ
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_HAVE_BLIT_AUTO
    ਜੇ (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_ਚੁਣੋ_Blit_Func(src_format, dst_format, map->info.flags,
                               SDL_Generated_Blit_Func_ਸਾਰਣੀ);
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TEST_SLOW_BLIT
    ਜੇ (!blit)
#ਜੇ_ਅੰਤ
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        ਜੇ ((!SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->ਅੰਕੜੇ = (ਖਾਲੀ *)blit;

    // Make sure we have a blit function
    ਜੇ (!blit) {
        SDL_InvalidateMap(map);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Blit combination not supported");
    }

    ਵਾਪਸ true;
}

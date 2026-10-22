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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_blit_auto.h"
#ಅನ್ತರ್ಭಾವ "SDL_blit_copy.h"
#ಅನ್ತರ್ಭಾವ "SDL_blit_slow.h"
#ಅನ್ತರ್ಭಾವ "SDL_RLEaccel_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"

// The general purpose software blit routine
ಸ್ಥಿರ bool SDLCALL SDL_SoftBlit(SDL_Surface *src, ಸ್ಥಿರಾಂಕ SDL_Rect *srcrect,
                                SDL_Surface *dst, ಸ್ಥಿರಾಂಕ SDL_Rect *dstrect)
{
    bool okay;
    ಪೂರ್ಣಾಂಕ src_locked;
    ಪೂರ್ಣಾಂಕ dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    ಆದರೆ (SDL_MUSTLOCK(dst)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(dst)) {
            okay = false;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    ಆದರೆ (SDL_MUSTLOCK(src)) {
        ಆದರೆ (!SDL_ಬೀಗ_Surface(src)) {
            okay = false;
        } ಇಲ್ಲದಿದ್ದರೆ {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    ಆದರೆ (okay) {
        SDL_BlitFunc ಸತತ_Blit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        ಆದರೆ (info->src_fmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        } ಇಲ್ಲದಿದ್ದರೆ {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        (srcrect->x * info->src_fmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel) / 8;
            info->leading_skip =
                        ((srcrect->x * info->src_fmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel) % 8) /
                        info->src_fmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel;
        }
        info->src_w = srcrect->w;
        info->src_h = srcrect->h;
        info->src_pitch = src->pitch;
        info->src_skip =
            info->src_pitch - info->src_w * info->src_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        info->dst = (Uint8 *)dst->pixels +
                    dstrect->y * dst->pitch +
                    dstrect->x * info->dst_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        info->dst_w = dstrect->w;
        info->dst_h = dstrect->h;
        info->dst_pitch = dst->pitch;
        info->dst_skip =
            info->dst_pitch - info->dst_w * info->dst_fmt->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        ಸತತ_Blit = (SDL_BlitFunc)src->map.ದತ್ತಾಂಶ;

        // Run the actual software blit
        ಸತತ_Blit(info);
    }

    // We need to unlock the surfaces if they're locked
    ಆದರೆ (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    ಆದರೆ (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    ಹಿಂತಿರುಗಿ okay;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_AUTO

ಸ್ಥಿರ SDL_BlitFunc SDL_ಆರಿಸು_Blit_Func(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, ಪೂರ್ಣಾಂಕ flags,
                                       SDL_Blit_Func_ನಮೂದು *entries)
{
    ಪೂರ್ಣಾಂಕ i, flagcheck = (flags & (SDL_COPY_MODULATE_ಮುಖವಾಡ | SDL_COPY_BLEND_ಮುಖವಾಡ | SDL_COPY_COLORKEY | SDL_COPY_ಹತ್ತಿರದ));

    ಗಾಗಿ (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        ಆದರೆ (src_format != entries[i].src_format) {
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (dst_format != entries[i].dst_format) {
            ಮುಂದುವರಿ;
        }

        // Check flags
        ಆದರೆ ((flagcheck & entries[i].flags) != flagcheck) {
            ಮುಂದುವರಿ;
        }

        // We found the best one!
        ಹಿಂತಿರುಗಿ entries[i].func;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = ಖಾಲಿ;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    ಆದರೆ (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Blit combination not supported");
    }

    // We should have cleared out RLE at this point
    SDL_assert(!(surface->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL));

    map->blit = SDL_SoftBlit;
    map->info.src_surface = surface;
    map->info.src_fmt = surface->fmt;
    map->info.src_pal = surface->palette;
    map->info.dst_surface = dst;
    map->info.dst_fmt = dst->fmt;
    map->info.dst_pal = dst->palette;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_RLE
    // See if we can do RLE acceleration
    ಆದರೆ (map->info.flags & SDL_COPY_RLE_DESIRED) {
        ಆದರೆ (SDL_RLESurface(surface)) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Choose a standard blit function
    ಆದರೆ (!blit) {
        ಆದರೆ (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    ಆದರೆ (!blit) {
        ಆದರೆ (map->ತಟಸ್ಥ && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(surface->format) ||
                   SDL_ISPIXELFORMAT_10_ಬಿಟ್(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_0
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_1
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_A
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_N
        ಇಲ್ಲದಿದ್ದರೆ {
            blit = SDL_CalculateBlitN(surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_BLIT_AUTO
    ಆದರೆ (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_ಆರಿಸು_Blit_Func(src_format, dst_format, map->info.flags,
                               SDL_Generated_Blit_Func_ಕೋಷ್ಟಕ);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TEST_SLOW_BLIT
    ಆದರೆ (!blit)
#ಆದರೆ_ಅಂತ್ಯ
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        ಆದರೆ ((!SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->ದತ್ತಾಂಶ = (ಶೂನ್ಯ *)blit;

    // Make sure we have a blit function
    ಆದರೆ (!blit) {
        SDL_InvalidateMap(map);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Blit combination not supported");
    }

    ಹಿಂತಿರುಗಿ true;
}

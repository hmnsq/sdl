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
#ضمن "SDL_internal.h"

#ضمن "SDL_sysvideo.h"
#ضمن "SDL_surface_c.h"
#ضمن "SDL_blit_auto.h"
#ضمن "SDL_blit_copy.h"
#ضمن "SDL_blit_slow.h"
#ضمن "SDL_RLEaccel_c.h"
#ضمن "SDL_pixels_c.h"

// The general purpose software blit routine
ساكن bool SDLCALL SDL_SoftBlit(SDL_Surface *src, ثابت SDL_Rect *srcrect,
                                SDL_Surface *dst, ثابت SDL_Rect *dstrect)
{
    bool okay;
    صحيح src_locked;
    صحيح dst_locked;

    // Everything is okay at the beginning...
    okay = true;

    // Lock the destination if it's in hardware
    dst_locked = 0;
    إذا (SDL_MUSTLOCK(dst)) {
        إذا (!SDL_جندرا_Surface(dst)) {
            okay = false;
        } وإلا {
            dst_locked = 1;
        }
    }
    // Lock the source if it's in hardware
    src_locked = 0;
    إذا (SDL_MUSTLOCK(src)) {
        إذا (!SDL_جندرا_Surface(src)) {
            okay = false;
        } وإلا {
            src_locked = 1;
        }
    }

    // Set up source and destination buffer pointers, and BLIT!
    إذا (okay) {
        SDL_BlitFunc لگاتار_Blit;
        SDL_BlitInfo *info = &src->map.info;

        // Set up the blit information
        إذا (info->src_fmt->بٹ_فی_pixel >= 8) {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        srcrect->x * info->src_fmt->بائٹاں_فی_pixel;
        } وإلا {
            info->src = (Uint8 *)src->pixels +
                        srcrect->y * src->pitch +
                        (srcrect->x * info->src_fmt->بٹ_فی_pixel) / 8;
            info->leading_skip =
                        ((srcrect->x * info->src_fmt->بٹ_فی_pixel) % 8) /
                        info->src_fmt->بٹ_فی_pixel;
        }
        info->src_w = srcrect->w;
        info->src_h = srcrect->h;
        info->src_pitch = src->pitch;
        info->src_skip =
            info->src_pitch - info->src_w * info->src_fmt->بائٹاں_فی_pixel;
        info->dst = (Uint8 *)dst->pixels +
                    dstrect->y * dst->pitch +
                    dstrect->x * info->dst_fmt->بائٹاں_فی_pixel;
        info->dst_w = dstrect->w;
        info->dst_h = dstrect->h;
        info->dst_pitch = dst->pitch;
        info->dst_skip =
            info->dst_pitch - info->dst_w * info->dst_fmt->بائٹاں_فی_pixel;
        لگاتار_Blit = (SDL_BlitFunc)src->map.انکڑے;

        // Run the actual software blit
        لگاتار_Blit(info);
    }

    // We need to unlock the surfaces if they're locked
    إذا (dst_locked) {
        SDL_UnlockSurface(dst);
    }
    إذا (src_locked) {
        SDL_UnlockSurface(src);
    }
    // Blit is done!
    أرجع okay;
}

#جے_تعریف_شدہ SDL_HAVE_BLIT_AUTO

ساكن SDL_BlitFunc SDL_چنو_Blit_Func(SDL_PixelFormat src_format, SDL_PixelFormat dst_format, صحيح flags,
                                       SDL_Blit_Func_اندراج *entries)
{
    صحيح i, flagcheck = (flags & (SDL_COPY_MODULATE_نقاب | SDL_COPY_BLEND_نقاب | SDL_COPY_COLORKEY | SDL_COPY_سبھ_توں_نیڑے));

    لكل (i = 0; entries[i].func; ++i) {
        // Check for matching pixel formats
        إذا (src_format != entries[i].src_format) {
            استمر;
        }
        إذا (dst_format != entries[i].dst_format) {
            استمر;
        }

        // Check flags
        إذا ((flagcheck & entries[i].flags) != flagcheck) {
            استمر;
        }

        // We found the best one!
        أرجع entries[i].func;
    }
    أرجع عدم;
}
#جے_انت // SDL_HAVE_BLIT_AUTO

// Figure out which of many blit routines to set up on a surface
bool SDL_CalculateBlit(SDL_Surface *surface, SDL_Surface *dst)
{
    SDL_BlitFunc blit = عدم;
    SDL_BlitMap *map = &surface->map;
    SDL_Colorspace src_colorspace = surface->colorspace;
    SDL_Colorspace dst_colorspace = dst->colorspace;

    // We don't currently support blitting to < 8 bpp surfaces
    إذا (SDL_BITSPERPIXEL(dst->format) < 8) {
        SDL_InvalidateMap(map);
        أرجع SDL_سیٹ_Error("Blit combination not supported");
    }

    // We should have cleared out RLE at this point
    SDL_assert(!(surface->اندرونی_flags & SDL_اندرونی_SURFACE_RLEACCEL));

    map->blit = SDL_SoftBlit;
    map->info.src_surface = surface;
    map->info.src_fmt = surface->fmt;
    map->info.src_pal = surface->palette;
    map->info.dst_surface = dst;
    map->info.dst_fmt = dst->fmt;
    map->info.dst_pal = dst->palette;

#جے_تعریف_شدہ SDL_HAVE_RLE
    // See if we can do RLE acceleration
    إذا (map->info.flags & SDL_COPY_RLE_DESIRED) {
        إذا (SDL_RLESurface(surface)) {
            أرجع true;
        }
    }
#جے_انت

    // Choose a standard blit function
    إذا (!blit) {
        إذا (src_colorspace != dst_colorspace ||
            SDL_BYTESPERPIXEL(surface->format) > 4 ||
            SDL_BYTESPERPIXEL(dst->format) > 4) {
            blit = SDL_Blit_Slow_Float;
        }
    }
    إذا (!blit) {
        إذا (map->پچھان_تت && !(map->info.flags & ~SDL_COPY_RLE_DESIRED)) {
            blit = SDL_BlitCopy;
        } وإلا إذا (SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(surface->format) ||
                   SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(dst->format)) {
            blit = SDL_Blit_Slow;
        }
#جے_تعریف_شدہ SDL_HAVE_BLIT_0
        وإلا إذا (SDL_BITSPERPIXEL(surface->format) < 8 &&
                 SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
            blit = SDL_CalculateBlit0(surface);
        }
#جے_انت
#جے_تعریف_شدہ SDL_HAVE_BLIT_1
        وإلا إذا (SDL_BYTESPERPIXEL(surface->format) == 1 &&
                 SDL_ISPIXELFORMAT_اشاریہ_دار(surface->format)) {
            blit = SDL_CalculateBlit1(surface);
        }
#جے_انت
#جے_تعریف_شدہ SDL_HAVE_BLIT_A
        وإلا إذا (map->info.flags & SDL_COPY_BLEND) {
            blit = SDL_CalculateBlitA(surface);
        }
#جے_انت
#جے_تعریف_شدہ SDL_HAVE_BLIT_N
        وإلا {
            blit = SDL_CalculateBlitN(surface);
        }
#جے_انت
    }
#جے_تعریف_شدہ SDL_HAVE_BLIT_AUTO
    إذا (!blit) {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        blit =
            SDL_چنو_Blit_Func(src_format, dst_format, map->info.flags,
                               SDL_Generated_Blit_Func_جدول);
    }
#جے_انت

#جے_بنا_تعریف TEST_SLOW_BLIT
    إذا (!blit)
#جے_انت
    {
        SDL_PixelFormat src_format = surface->format;
        SDL_PixelFormat dst_format = dst->format;

        إذا ((!SDL_ISPIXELFORMAT_اشاریہ_دار(src_format) ||
             (src_format == SDL_PIXELFORMAT_INDEX8 && surface->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(src_format) &&
            (!SDL_ISPIXELFORMAT_اشاریہ_دار(dst_format) ||
             (dst_format == SDL_PIXELFORMAT_INDEX8 && dst->palette)) &&
            !SDL_ISPIXELFORMAT_FOURCC(dst_format)) {
            blit = SDL_Blit_Slow;
        }
    }
    map->انکڑے = (فراغ *)blit;

    // Make sure we have a blit function
    إذا (!blit) {
        SDL_InvalidateMap(map);
        أرجع SDL_سیٹ_Error("Blit combination not supported");
    }

    أرجع true;
}

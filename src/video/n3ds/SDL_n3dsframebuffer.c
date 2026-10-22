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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../SDL_properties_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsvideo.h"

#وصف_ڪريو N3DS_SURFACE "SDL.internal.window.surface"

تعريفنوع بنية
{
    صحيح ويڪر, اوچائي;
} Dimensions;

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *ذريعو, ثابت Dimensions ذريعو_dim);
ساكن فراغ CopyFramebuffertoN3DS_24(u8  *dest, ثابت Dimensions dest_dim, ثابت u8  *ذريعو, ثابت Dimensions ذريعو_dim);
ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *ذريعو, ثابت Dimensions ذريعو_dim);
ساكن صحيح Get_Dest_وٿي(صحيح x, صحيح y, صحيح dest_ويڪر);
ساكن صحيح Get_ذريعو_وٿي(صحيح x, صحيح y, صحيح ذريعو_ويڪر);
ساكن فراغ FlushN3DSBuffer(ثابت فراغ *بفر_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *framebuffer;
    ثابت SDL_Display_گهڻائي *گهڻائي;
    صحيح w, h;

    SDL_N3_DS_Destroy_دري_Framebuffer(_this, دري);

    گهڻائي = SDL_Get_Current_Display_گهڻائي(SDL_Get_Display_For_دري(دري));
    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, گهڻائي->format);

    إذا (!framebuffer) {
        أرجع false;
    }

    SDL_سيٽ_Surface_Property(SDL_Get_دري_Properties(دري), N3DS_SURFACE, framebuffer);
    *format = گهڻائي->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    أرجع true;
}

bool SDL_N3_DS_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_دري_معلومات *drv_معلومات = دري->اندروني;
    SDL_Surface *surface;
    u16 ويڪر, اوچائي;
    فراغ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_اشارو_Property(SDL_Get_دري_Properties(دري), N3DS_SURFACE, عدم);
    إذا (!surface) {
        أرجع SDL_سيٽ_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_معلومات->screen, GFX_کاٻو, &ويڪر, &اوچائي);
    bufsize = ويڪر * اوچائي * 4;

    إذا (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ ويڪر, اوچائي },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا إذا (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ ويڪر, اوچائي },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ ويڪر, اوچائي },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_معلومات->screen);

    أرجع true;
}

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *ذريعو, ثابت Dimensions ذريعو_dim)
{
    صحيح صفون = SDL_min(dest_dim.ويڪر, ذريعو_dim.اوچائي);
    صحيح کانن_ڳڻپ = SDL_min(dest_dim.اوچائي, ذريعو_dim.ويڪر);
    لكل (صحيح y = 0; y < صفون; ++y) {
        لكل (صحيح x = 0; x < کانن_ڳڻپ; ++x) {
            ثابت u16 *s = ذريعو + Get_ذريعو_وٿي(x, y, ذريعو_dim.ويڪر);
            u16 *d = dest + Get_Dest_وٿي(x, y, dest_dim.ويڪر);
            *d = *s;
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_24(u8 *dest, ثابت Dimensions dest_dim, ثابت u8 *ذريعو, ثابت Dimensions ذريعو_dim)
{
    صحيح صفون = SDL_min(dest_dim.ويڪر, ذريعو_dim.اوچائي);
    صحيح کانن_ڳڻپ = SDL_min(dest_dim.اوچائي, ذريعو_dim.ويڪر);
    لكل (صحيح y = 0; y < صفون; ++y) {
        لكل (صحيح x = 0; x < کانن_ڳڻپ; ++x) {
            ثابت u8 *s = ذريعو + Get_ذريعو_وٿي(x, y, ذريعو_dim.ويڪر) * 3;
            u8 *d = dest + Get_Dest_وٿي(x, y, dest_dim.ويڪر) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *ذريعو, ثابت Dimensions ذريعو_dim)
{
    صحيح صفون = SDL_min(dest_dim.ويڪر, ذريعو_dim.اوچائي);
    صحيح کانن_ڳڻپ = SDL_min(dest_dim.اوچائي, ذريعو_dim.ويڪر);
    لكل (صحيح y = 0; y < صفون; ++y) {
        لكل (صحيح x = 0; x < کانن_ڳڻپ; ++x) {
            ثابت u32 *s = ذريعو + Get_ذريعو_وٿي(x, y, ذريعو_dim.ويڪر);
            u32 *d = dest + Get_Dest_وٿي(x, y, dest_dim.ويڪر);
            *d = *s;
        }
    }
}

ساكن صحيح Get_Dest_وٿي(صحيح x, صحيح y, صحيح dest_ويڪر)
{
    أرجع dest_ويڪر - y - 1 + dest_ويڪر * x;
}

ساكن صحيح Get_ذريعو_وٿي(صحيح x, صحيح y, صحيح ذريعو_ويڪر)
{
    أرجع x + y * ذريعو_ويڪر;
}

ساكن فراغ FlushN3DSBuffer(ثابت فراغ *بفر_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_معلومات_Cache(بفر_2, bufsize);
    gfx_Screen_مٽا_سٽا_Buffers(screen, false);
}

فراغ SDL_N3_DS_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_ClearProperty(SDL_Get_دري_Properties(دري), N3DS_SURFACE);
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_N3DS

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

#که_تعریف_شوی SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../SDL_properties_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsvideo.h"

#تعریف_کړه N3DS_SURFACE "SDL.internal.window.surface"

تعريفنوع بنية
{
    صحيح پلنوالی, لوړوالی;
} Dimensions;

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *سرچینه, ثابت Dimensions سرچینه_dim);
ساكن فراغ CopyFramebuffertoN3DS_24(u8  *dest, ثابت Dimensions dest_dim, ثابت u8  *سرچینه, ثابت Dimensions سرچینه_dim);
ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *سرچینه, ثابت Dimensions سرچینه_dim);
ساكن صحيح Get_Dest_دننه_واټن(صحيح x, صحيح y, صحيح dest_پلنوالی);
ساكن صحيح Get_سرچینه_دننه_واټن(صحيح x, صحيح y, صحيح سرچینه_پلنوالی);
ساكن فراغ FlushN3DSBuffer(ثابت فراغ *بفر_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *framebuffer;
    ثابت SDL_Display_ډېرپېښ *ډېرپېښ;
    صحيح w, h;

    SDL_N3_DS_Destroy_کړکۍ_Framebuffer(_this, کړکۍ);

    ډېرپېښ = SDL_Get_Current_Display_ډېرپېښ(SDL_Get_Display_For_کړکۍ(کړکۍ));
    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, ډېرپېښ->format);

    إذا (!framebuffer) {
        أرجع false;
    }

    SDL_سېټ_Surface_Property(SDL_Get_کړکۍ_Properties(کړکۍ), N3DS_SURFACE, framebuffer);
    *format = ډېرپېښ->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    أرجع true;
}

bool SDL_N3_DS_Update_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کړکۍ_معلومات *drv_معلومات = کړکۍ->دننی;
    SDL_Surface *surface;
    u16 پلنوالی, لوړوالی;
    فراغ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), N3DS_SURFACE, عدم);
    إذا (!surface) {
        أرجع SDL_سېټ_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_معلومات->screen, GFX_کیڼ, &پلنوالی, &لوړوالی);
    bufsize = پلنوالی * لوړوالی * 4;

    إذا (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ پلنوالی, لوړوالی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا إذا (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ پلنوالی, لوړوالی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ پلنوالی, لوړوالی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_معلومات->screen);

    أرجع true;
}

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *سرچینه, ثابت Dimensions سرچینه_dim)
{
    صحيح لیکې = SDL_min(dest_dim.پلنوالی, سرچینه_dim.لوړوالی);
    صحيح ستون_شمېر = SDL_min(dest_dim.لوړوالی, سرچینه_dim.پلنوالی);
    لكل (صحيح y = 0; y < لیکې; ++y) {
        لكل (صحيح x = 0; x < ستون_شمېر; ++x) {
            ثابت u16 *s = سرچینه + Get_سرچینه_دننه_واټن(x, y, سرچینه_dim.پلنوالی);
            u16 *d = dest + Get_Dest_دننه_واټن(x, y, dest_dim.پلنوالی);
            *d = *s;
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_24(u8 *dest, ثابت Dimensions dest_dim, ثابت u8 *سرچینه, ثابت Dimensions سرچینه_dim)
{
    صحيح لیکې = SDL_min(dest_dim.پلنوالی, سرچینه_dim.لوړوالی);
    صحيح ستون_شمېر = SDL_min(dest_dim.لوړوالی, سرچینه_dim.پلنوالی);
    لكل (صحيح y = 0; y < لیکې; ++y) {
        لكل (صحيح x = 0; x < ستون_شمېر; ++x) {
            ثابت u8 *s = سرچینه + Get_سرچینه_دننه_واټن(x, y, سرچینه_dim.پلنوالی) * 3;
            u8 *d = dest + Get_Dest_دننه_واټن(x, y, dest_dim.پلنوالی) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *سرچینه, ثابت Dimensions سرچینه_dim)
{
    صحيح لیکې = SDL_min(dest_dim.پلنوالی, سرچینه_dim.لوړوالی);
    صحيح ستون_شمېر = SDL_min(dest_dim.لوړوالی, سرچینه_dim.پلنوالی);
    لكل (صحيح y = 0; y < لیکې; ++y) {
        لكل (صحيح x = 0; x < ستون_شمېر; ++x) {
            ثابت u32 *s = سرچینه + Get_سرچینه_دننه_واټن(x, y, سرچینه_dim.پلنوالی);
            u32 *d = dest + Get_Dest_دننه_واټن(x, y, dest_dim.پلنوالی);
            *d = *s;
        }
    }
}

ساكن صحيح Get_Dest_دننه_واټن(صحيح x, صحيح y, صحيح dest_پلنوالی)
{
    أرجع dest_پلنوالی - y - 1 + dest_پلنوالی * x;
}

ساكن صحيح Get_سرچینه_دننه_واټن(صحيح x, صحيح y, صحيح سرچینه_پلنوالی)
{
    أرجع x + y * سرچینه_پلنوالی;
}

ساكن فراغ FlushN3DSBuffer(ثابت فراغ *بفر_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_معلومات_Cache(بفر_2, bufsize);
    gfx_Screen_بدلون_Buffers(screen, false);
}

فراغ SDL_N3_DS_Destroy_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_ClearProperty(SDL_Get_کړکۍ_Properties(کړکۍ), N3DS_SURFACE);
}

#د_که_پای // SDL_VIDEO_DRIVER_N3DS

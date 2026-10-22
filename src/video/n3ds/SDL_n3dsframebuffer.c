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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../SDL_properties_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsvideo.h"

#تعریف_کن N3DS_SURFACE "SDL.internal.window.surface"

تعريفنوع بنية
{
    صحيح عرض, ارتفاع;
} Dimensions;

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *منبع, ثابت Dimensions منبع_dim);
ساكن فراغ CopyFramebuffertoN3DS_24(u8  *dest, ثابت Dimensions dest_dim, ثابت u8  *منبع, ثابت Dimensions منبع_dim);
ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *منبع, ثابت Dimensions منبع_dim);
ساكن صحيح Get_Dest_جابه_جایی(صحيح x, صحيح y, صحيح dest_عرض);
ساكن صحيح Get_منبع_جابه_جایی(صحيح x, صحيح y, صحيح منبع_عرض);
ساكن فراغ FlushN3DSBuffer(ثابت فراغ *میانگیر_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *framebuffer;
    ثابت SDL_Display_نما *نما;
    صحيح w, h;

    SDL_N3_DS_Destroy_پنجره_Framebuffer(_this, پنجره);

    نما = SDL_Get_Current_Display_نما(SDL_Get_Display_For_پنجره(پنجره));
    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, نما->format);

    إذا (!framebuffer) {
        أرجع false;
    }

    SDL_مجموعه_Surface_Property(SDL_Get_پنجره_Properties(پنجره), N3DS_SURFACE, framebuffer);
    *format = نما->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    أرجع true;
}

bool SDL_N3_DS_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_پنجره_داده *drv_داده = پنجره->داخلی;
    SDL_Surface *surface;
    u16 عرض, ارتفاع;
    فراغ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), N3DS_SURFACE, عدم);
    إذا (!surface) {
        أرجع SDL_مجموعه_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_داده->screen, GFX_چپ, &عرض, &ارتفاع);
    bufsize = عرض * ارتفاع * 4;

    إذا (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ عرض, ارتفاع },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا إذا (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ عرض, ارتفاع },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ عرض, ارتفاع },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_داده->screen);

    أرجع true;
}

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *منبع, ثابت Dimensions منبع_dim)
{
    صحيح ردیفها = SDL_min(dest_dim.عرض, منبع_dim.ارتفاع);
    صحيح تعداد_ستون = SDL_min(dest_dim.ارتفاع, منبع_dim.عرض);
    لكل (صحيح y = 0; y < ردیفها; ++y) {
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            ثابت u16 *s = منبع + Get_منبع_جابه_جایی(x, y, منبع_dim.عرض);
            u16 *d = dest + Get_Dest_جابه_جایی(x, y, dest_dim.عرض);
            *d = *s;
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_24(u8 *dest, ثابت Dimensions dest_dim, ثابت u8 *منبع, ثابت Dimensions منبع_dim)
{
    صحيح ردیفها = SDL_min(dest_dim.عرض, منبع_dim.ارتفاع);
    صحيح تعداد_ستون = SDL_min(dest_dim.ارتفاع, منبع_dim.عرض);
    لكل (صحيح y = 0; y < ردیفها; ++y) {
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            ثابت u8 *s = منبع + Get_منبع_جابه_جایی(x, y, منبع_dim.عرض) * 3;
            u8 *d = dest + Get_Dest_جابه_جایی(x, y, dest_dim.عرض) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *منبع, ثابت Dimensions منبع_dim)
{
    صحيح ردیفها = SDL_min(dest_dim.عرض, منبع_dim.ارتفاع);
    صحيح تعداد_ستون = SDL_min(dest_dim.ارتفاع, منبع_dim.عرض);
    لكل (صحيح y = 0; y < ردیفها; ++y) {
        لكل (صحيح x = 0; x < تعداد_ستون; ++x) {
            ثابت u32 *s = منبع + Get_منبع_جابه_جایی(x, y, منبع_dim.عرض);
            u32 *d = dest + Get_Dest_جابه_جایی(x, y, dest_dim.عرض);
            *d = *s;
        }
    }
}

ساكن صحيح Get_Dest_جابه_جایی(صحيح x, صحيح y, صحيح dest_عرض)
{
    أرجع dest_عرض - y - 1 + dest_عرض * x;
}

ساكن صحيح Get_منبع_جابه_جایی(صحيح x, صحيح y, صحيح منبع_عرض)
{
    أرجع x + y * منبع_عرض;
}

ساكن فراغ FlushN3DSBuffer(ثابت فراغ *میانگیر_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_داده_Cache(میانگیر_2, bufsize);
    gfx_Screen_جابجا_Buffers(screen, false);
}

فراغ SDL_N3_DS_Destroy_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_ClearProperty(SDL_Get_پنجره_Properties(پنجره), N3DS_SURFACE);
}

#پایان_اگر // SDL_VIDEO_DRIVER_N3DS

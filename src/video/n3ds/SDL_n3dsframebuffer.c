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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../SDL_properties_c.h"
#ضمن "SDL_n3dsframebuffer_c.h"
#ضمن "SDL_n3dsvideo.h"

#تعریف_کرو N3DS_SURFACE "SDL.internal.window.surface"

تعريفنوع بنية
{
    صحيح چوڑائی, اچائی;
} Dimensions;

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *سروت, ثابت Dimensions سروت_dim);
ساكن فراغ CopyFramebuffertoN3DS_24(u8  *dest, ثابت Dimensions dest_dim, ثابت u8  *سروت, ثابت Dimensions سروت_dim);
ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *سروت, ثابت Dimensions سروت_dim);
ساكن صحيح Get_Dest_وتھ(صحيح x, صحيح y, صحيح dest_چوڑائی);
ساكن صحيح Get_سروت_وتھ(صحيح x, صحيح y, صحيح سروت_چوڑائی);
ساكن فراغ FlushN3DSBuffer(ثابت فراغ *بفر_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Surface *framebuffer;
    ثابت SDL_Display_منوال *منوال;
    صحيح w, h;

    SDL_N3_DS_Destroy_کھڑکی_Framebuffer(_this, کھڑکی);

    منوال = SDL_Get_Current_Display_منوال(SDL_Get_Display_For_کھڑکی(کھڑکی));
    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, منوال->format);

    إذا (!framebuffer) {
        أرجع false;
    }

    SDL_سیٹ_Surface_Property(SDL_Get_کھڑکی_Properties(کھڑکی), N3DS_SURFACE, framebuffer);
    *format = منوال->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    أرجع true;
}

bool SDL_N3_DS_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کھڑکی_انکڑے *drv_انکڑے = کھڑکی->اندرونی;
    SDL_Surface *surface;
    u16 چوڑائی, اچائی;
    فراغ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), N3DS_SURFACE, عدم);
    إذا (!surface) {
        أرجع SDL_سیٹ_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_انکڑے->screen, GFX_بایاں, &چوڑائی, &اچائی);
    bufsize = چوڑائی * اچائی * 4;

    إذا (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ چوڑائی, اچائی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا إذا (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ چوڑائی, اچائی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    وإلا
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ چوڑائی, اچائی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_انکڑے->screen);

    أرجع true;
}

ساكن فراغ CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *سروت, ثابت Dimensions سروت_dim)
{
    صحيح صفاں = SDL_min(dest_dim.چوڑائی, سروت_dim.اچائی);
    صحيح خانے_گنتی = SDL_min(dest_dim.اچائی, سروت_dim.چوڑائی);
    لكل (صحيح y = 0; y < صفاں; ++y) {
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            ثابت u16 *s = سروت + Get_سروت_وتھ(x, y, سروت_dim.چوڑائی);
            u16 *d = dest + Get_Dest_وتھ(x, y, dest_dim.چوڑائی);
            *d = *s;
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_24(u8 *dest, ثابت Dimensions dest_dim, ثابت u8 *سروت, ثابت Dimensions سروت_dim)
{
    صحيح صفاں = SDL_min(dest_dim.چوڑائی, سروت_dim.اچائی);
    صحيح خانے_گنتی = SDL_min(dest_dim.اچائی, سروت_dim.چوڑائی);
    لكل (صحيح y = 0; y < صفاں; ++y) {
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            ثابت u8 *s = سروت + Get_سروت_وتھ(x, y, سروت_dim.چوڑائی) * 3;
            u8 *d = dest + Get_Dest_وتھ(x, y, dest_dim.چوڑائی) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ساكن فراغ CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *سروت, ثابت Dimensions سروت_dim)
{
    صحيح صفاں = SDL_min(dest_dim.چوڑائی, سروت_dim.اچائی);
    صحيح خانے_گنتی = SDL_min(dest_dim.اچائی, سروت_dim.چوڑائی);
    لكل (صحيح y = 0; y < صفاں; ++y) {
        لكل (صحيح x = 0; x < خانے_گنتی; ++x) {
            ثابت u32 *s = سروت + Get_سروت_وتھ(x, y, سروت_dim.چوڑائی);
            u32 *d = dest + Get_Dest_وتھ(x, y, dest_dim.چوڑائی);
            *d = *s;
        }
    }
}

ساكن صحيح Get_Dest_وتھ(صحيح x, صحيح y, صحيح dest_چوڑائی)
{
    أرجع dest_چوڑائی - y - 1 + dest_چوڑائی * x;
}

ساكن صحيح Get_سروت_وتھ(صحيح x, صحيح y, صحيح سروت_چوڑائی)
{
    أرجع x + y * سروت_چوڑائی;
}

ساكن فراغ FlushN3DSBuffer(ثابت فراغ *بفر_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_انکڑے_Cache(بفر_2, bufsize);
    gfx_Screen_وٹاندرا_Buffers(screen, false);
}

فراغ SDL_N3_DS_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_ClearProperty(SDL_Get_کھڑکی_Properties(کھڑکی), N3DS_SURFACE);
}

#جے_انت // SDL_VIDEO_DRIVER_N3DS

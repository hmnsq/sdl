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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS

#شامل "../SDL_sysvideo.h"
#شامل "../../SDL_properties_c.h"
#شامل "SDL_n3dsframebuffer_c.h"
#شامل "SDL_n3dsvideo.h"

#تعریف_کرو N3DS_SURFACE "SDL.internal.window.surface"

قسمتعریف ساخت
{
    صحیح چوڑائی, اونچائی;
} Dimensions;

ساکن خالی CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *ماخذ, ثابت Dimensions ماخذ_dim);
ساکن خالی CopyFramebuffertoN3DS_24(u8  *dest, ثابت Dimensions dest_dim, ثابت u8  *ماخذ, ثابت Dimensions ماخذ_dim);
ساکن خالی CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *ماخذ, ثابت Dimensions ماخذ_dim);
ساکن صحیح Get_Dest_انحراف(صحیح x, صحیح y, صحیح dest_چوڑائی);
ساکن صحیح Get_ماخذ_انحراف(صحیح x, صحیح y, صحیح ماخذ_چوڑائی);
ساکن خالی FlushN3DSBuffer(ثابت خالی *بفر_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, خالی **pixels, صحیح *pitch)
{
    SDL_Surface *framebuffer;
    ثابت SDL_Display_منوال *منوال;
    صحیح w, h;

    SDL_N3_DS_Destroy_کھڑکی_Framebuffer(_this, کھڑکی);

    منوال = SDL_Get_Current_Display_منوال(SDL_Get_Display_For_کھڑکی(کھڑکی));
    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, منوال->format);

    اگر (!framebuffer) {
        واپس false;
    }

    SDL_سیٹ_Surface_Property(SDL_Get_کھڑکی_Properties(کھڑکی), N3DS_SURFACE, framebuffer);
    *format = منوال->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    واپس true;
}

bool SDL_N3_DS_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحیح numrects)
{
    SDL_کھڑکی_ڈیٹا *drv_ڈیٹا = کھڑکی->اندرونی_2;
    SDL_Surface *surface;
    u16 چوڑائی, اونچائی;
    خالی *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), N3DS_SURFACE, تہی);
    اگر (!surface) {
        واپس SDL_سیٹ_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_ڈیٹا->screen, GFX_بایاں, &چوڑائی, &اونچائی);
    bufsize = چوڑائی * اونچائی * 4;

    اگر (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ چوڑائی, اونچائی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ورنہ اگر (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ چوڑائی, اونچائی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ورنہ
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ چوڑائی, اونچائی },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_ڈیٹا->screen);

    واپس true;
}

ساکن خالی CopyFramebuffertoN3DS_16(u16 *dest, ثابت Dimensions dest_dim, ثابت u16 *ماخذ, ثابت Dimensions ماخذ_dim)
{
    صحیح صفیں = SDL_min(dest_dim.چوڑائی, ماخذ_dim.اونچائی);
    صحیح ستون_تعداد = SDL_min(dest_dim.اونچائی, ماخذ_dim.چوڑائی);
    برائے (صحیح y = 0; y < صفیں; ++y) {
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            ثابت u16 *s = ماخذ + Get_ماخذ_انحراف(x, y, ماخذ_dim.چوڑائی);
            u16 *d = dest + Get_Dest_انحراف(x, y, dest_dim.چوڑائی);
            *d = *s;
        }
    }
}

ساکن خالی CopyFramebuffertoN3DS_24(u8 *dest, ثابت Dimensions dest_dim, ثابت u8 *ماخذ, ثابت Dimensions ماخذ_dim)
{
    صحیح صفیں = SDL_min(dest_dim.چوڑائی, ماخذ_dim.اونچائی);
    صحیح ستون_تعداد = SDL_min(dest_dim.اونچائی, ماخذ_dim.چوڑائی);
    برائے (صحیح y = 0; y < صفیں; ++y) {
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            ثابت u8 *s = ماخذ + Get_ماخذ_انحراف(x, y, ماخذ_dim.چوڑائی) * 3;
            u8 *d = dest + Get_Dest_انحراف(x, y, dest_dim.چوڑائی) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ساکن خالی CopyFramebuffertoN3DS_32(u32 *dest, ثابت Dimensions dest_dim, ثابت u32 *ماخذ, ثابت Dimensions ماخذ_dim)
{
    صحیح صفیں = SDL_min(dest_dim.چوڑائی, ماخذ_dim.اونچائی);
    صحیح ستون_تعداد = SDL_min(dest_dim.اونچائی, ماخذ_dim.چوڑائی);
    برائے (صحیح y = 0; y < صفیں; ++y) {
        برائے (صحیح x = 0; x < ستون_تعداد; ++x) {
            ثابت u32 *s = ماخذ + Get_ماخذ_انحراف(x, y, ماخذ_dim.چوڑائی);
            u32 *d = dest + Get_Dest_انحراف(x, y, dest_dim.چوڑائی);
            *d = *s;
        }
    }
}

ساکن صحیح Get_Dest_انحراف(صحیح x, صحیح y, صحیح dest_چوڑائی)
{
    واپس dest_چوڑائی - y - 1 + dest_چوڑائی * x;
}

ساکن صحیح Get_ماخذ_انحراف(صحیح x, صحیح y, صحیح ماخذ_چوڑائی)
{
    واپس x + y * ماخذ_چوڑائی;
}

ساکن خالی FlushN3DSBuffer(ثابت خالی *بفر_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_ڈیٹا_Cache(بفر_2, bufsize);
    gfx_Screen_تبادلہ_Buffers(screen, false);
}

خالی SDL_N3_DS_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_ClearProperty(SDL_Get_کھڑکی_Properties(کھڑکی), N3DS_SURFACE);
}

#اگر_ختم // SDL_VIDEO_DRIVER_N3DS

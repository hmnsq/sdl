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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_N3DS

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_properties_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_n3dsvideo.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N3DS_SURFACE "SDL.internal.window.surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;
} Dimensions;

ਸਥਿਰ ਖਾਲੀ CopyFramebuffertoN3DS_16(u16 *dest, ਅਚਲ Dimensions dest_dim, ਅਚਲ u16 *ਸਰੋਤ, ਅਚਲ Dimensions ਸਰੋਤ_dim);
ਸਥਿਰ ਖਾਲੀ CopyFramebuffertoN3DS_24(u8  *dest, ਅਚਲ Dimensions dest_dim, ਅਚਲ u8  *ਸਰੋਤ, ਅਚਲ Dimensions ਸਰੋਤ_dim);
ਸਥਿਰ ਖਾਲੀ CopyFramebuffertoN3DS_32(u32 *dest, ਅਚਲ Dimensions dest_dim, ਅਚਲ u32 *ਸਰੋਤ, ਅਚਲ Dimensions ਸਰੋਤ_dim);
ਸਥਿਰ ਪੂਰਨ Get_Dest_ਵਿੱਥ(ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ dest_ਚੌੜਾਈ);
ਸਥਿਰ ਪੂਰਨ Get_ਸਰੋਤ_ਵਿੱਥ(ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ ਸਰੋਤ_ਚੌੜਾਈ);
ਸਥਿਰ ਖਾਲੀ FlushN3DSBuffer(ਅਚਲ ਖਾਲੀ *ਬਫਰ_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_Surface *framebuffer;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ;
    ਪੂਰਨ w, h;

    SDL_N3_DS_Destroy_ਖਿੜਕੀ_Framebuffer(_this, ਖਿੜਕੀ);

    ਬਹੁਲਕ = SDL_Get_Current_Display_ਬਹੁਲਕ(SDL_Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ));
    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, ਬਹੁਲਕ->format);

    ਜੇ (!framebuffer) {
        ਵਾਪਸ false;
    }

    SDL_ਸੈੱਟ_Surface_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), N3DS_SURFACE, framebuffer);
    *format = ਬਹੁਲਕ->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    ਵਾਪਸ true;
}

bool SDL_N3_DS_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *drv_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Surface *surface;
    u16 ਚੌੜਾਈ, ਉਚਾਈ;
    ਖਾਲੀ *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), N3DS_SURFACE, ਨਿਰਾ);
    ਜੇ (!surface) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_ਅੰਕੜੇ->screen, GFX_ਖੱਬਾ, &ਚੌੜਾਈ, &ਉਚਾਈ);
    bufsize = ਚੌੜਾਈ * ਉਚਾਈ * 4;

    ਜੇ (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ ਚੌੜਾਈ, ਉਚਾਈ },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ਨਹੀਂਤਾਂ ਜੇ (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ ਚੌੜਾਈ, ਉਚਾਈ },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    ਨਹੀਂਤਾਂ
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ ਚੌੜਾਈ, ਉਚਾਈ },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_ਅੰਕੜੇ->screen);

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ CopyFramebuffertoN3DS_16(u16 *dest, ਅਚਲ Dimensions dest_dim, ਅਚਲ u16 *ਸਰੋਤ, ਅਚਲ Dimensions ਸਰੋਤ_dim)
{
    ਪੂਰਨ ਪੰਕਤੀਆਂ = SDL_min(dest_dim.ਚੌੜਾਈ, ਸਰੋਤ_dim.ਉਚਾਈ);
    ਪੂਰਨ ਖਾਨੇ_ਗਿਣਤੀ = SDL_min(dest_dim.ਉਚਾਈ, ਸਰੋਤ_dim.ਚੌੜਾਈ);
    ਲਈ (ਪੂਰਨ y = 0; y < ਪੰਕਤੀਆਂ; ++y) {
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਅਚਲ u16 *s = ਸਰੋਤ + Get_ਸਰੋਤ_ਵਿੱਥ(x, y, ਸਰੋਤ_dim.ਚੌੜਾਈ);
            u16 *d = dest + Get_Dest_ਵਿੱਥ(x, y, dest_dim.ਚੌੜਾਈ);
            *d = *s;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ CopyFramebuffertoN3DS_24(u8 *dest, ਅਚਲ Dimensions dest_dim, ਅਚਲ u8 *ਸਰੋਤ, ਅਚਲ Dimensions ਸਰੋਤ_dim)
{
    ਪੂਰਨ ਪੰਕਤੀਆਂ = SDL_min(dest_dim.ਚੌੜਾਈ, ਸਰੋਤ_dim.ਉਚਾਈ);
    ਪੂਰਨ ਖਾਨੇ_ਗਿਣਤੀ = SDL_min(dest_dim.ਉਚਾਈ, ਸਰੋਤ_dim.ਚੌੜਾਈ);
    ਲਈ (ਪੂਰਨ y = 0; y < ਪੰਕਤੀਆਂ; ++y) {
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਅਚਲ u8 *s = ਸਰੋਤ + Get_ਸਰੋਤ_ਵਿੱਥ(x, y, ਸਰੋਤ_dim.ਚੌੜਾਈ) * 3;
            u8 *d = dest + Get_Dest_ਵਿੱਥ(x, y, dest_dim.ਚੌੜਾਈ) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

ਸਥਿਰ ਖਾਲੀ CopyFramebuffertoN3DS_32(u32 *dest, ਅਚਲ Dimensions dest_dim, ਅਚਲ u32 *ਸਰੋਤ, ਅਚਲ Dimensions ਸਰੋਤ_dim)
{
    ਪੂਰਨ ਪੰਕਤੀਆਂ = SDL_min(dest_dim.ਚੌੜਾਈ, ਸਰੋਤ_dim.ਉਚਾਈ);
    ਪੂਰਨ ਖਾਨੇ_ਗਿਣਤੀ = SDL_min(dest_dim.ਉਚਾਈ, ਸਰੋਤ_dim.ਚੌੜਾਈ);
    ਲਈ (ਪੂਰਨ y = 0; y < ਪੰਕਤੀਆਂ; ++y) {
        ਲਈ (ਪੂਰਨ x = 0; x < ਖਾਨੇ_ਗਿਣਤੀ; ++x) {
            ਅਚਲ u32 *s = ਸਰੋਤ + Get_ਸਰੋਤ_ਵਿੱਥ(x, y, ਸਰੋਤ_dim.ਚੌੜਾਈ);
            u32 *d = dest + Get_Dest_ਵਿੱਥ(x, y, dest_dim.ਚੌੜਾਈ);
            *d = *s;
        }
    }
}

ਸਥਿਰ ਪੂਰਨ Get_Dest_ਵਿੱਥ(ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ dest_ਚੌੜਾਈ)
{
    ਵਾਪਸ dest_ਚੌੜਾਈ - y - 1 + dest_ਚੌੜਾਈ * x;
}

ਸਥਿਰ ਪੂਰਨ Get_ਸਰੋਤ_ਵਿੱਥ(ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ ਸਰੋਤ_ਚੌੜਾਈ)
{
    ਵਾਪਸ x + y * ਸਰੋਤ_ਚੌੜਾਈ;
}

ਸਥਿਰ ਖਾਲੀ FlushN3DSBuffer(ਅਚਲ ਖਾਲੀ *ਬਫਰ_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_ਅੰਕੜੇ_Cache(ਬਫਰ_2, bufsize);
    gfx_Screen_ਅਦਲਾ_ਬਦਲੀ_Buffers(screen, false);
}

ਖਾਲੀ SDL_N3_DS_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ClearProperty(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), N3DS_SURFACE);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_N3DS

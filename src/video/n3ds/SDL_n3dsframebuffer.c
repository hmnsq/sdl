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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_N3DS

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../SDL_properties_c.h"
#అన్తర్భావ "SDL_n3dsframebuffer_c.h"
#అన్తర్భావ "SDL_n3dsvideo.h"

#నిర్వచించు N3DS_SURFACE "SDL.internal.window.surface"

రకనిర్వచనం నిర్మాణం
{
    పూర్ణాంకం వెడల్పు, ఎత్తు;
} Dimensions;

స్థిర శూన్య CopyFramebuffertoN3DS_16(u16 *dest, స్థిరరాశి Dimensions dest_dim, స్థిరరాశి u16 *ఆధారం, స్థిరరాశి Dimensions ఆధారం_dim);
స్థిర శూన్య CopyFramebuffertoN3DS_24(u8  *dest, స్థిరరాశి Dimensions dest_dim, స్థిరరాశి u8  *ఆధారం, స్థిరరాశి Dimensions ఆధారం_dim);
స్థిర శూన్య CopyFramebuffertoN3DS_32(u32 *dest, స్థిరరాశి Dimensions dest_dim, స్థిరరాశి u32 *ఆధారం, స్థిరరాశి Dimensions ఆధారం_dim);
స్థిర పూర్ణాంకం Get_Dest_స్థానభ్రంశం(పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం dest_వెడల్పు);
స్థిర పూర్ణాంకం Get_ఆధారం_స్థానభ్రంశం(పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం ఆధారం_వెడల్పు);
స్థిర శూన్య FlushN3DSBuffer(స్థిరరాశి శూన్య *బఫరు_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_Surface *framebuffer;
    స్థిరరాశి SDL_Display_బహుళకం *బహుళకం;
    పూర్ణాంకం w, h;

    SDL_N3_DS_Destroy_కిటికీ_Framebuffer(_this, కిటికీ);

    బహుళకం = SDL_Get_Current_Display_బహుళకం(SDL_Get_Display_For_కిటికీ(కిటికీ));
    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, బహుళకం->format);

    ఒకవేళ (!framebuffer) {
        తిరిగి false;
    }

    SDL_సమితి_Surface_Property(SDL_Get_కిటికీ_Properties(కిటికీ), N3DS_SURFACE, framebuffer);
    *format = బహుళకం->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    తిరిగి true;
}

bool SDL_N3_DS_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    SDL_కిటికీ_దత్తాంశం *drv_దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_Surface *surface;
    u16 వెడల్పు, ఎత్తు;
    శూన్య *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_Get_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), N3DS_SURFACE, ఖాళీ);
    ఒకవేళ (!surface) {
        తిరిగి SDL_సమితి_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_దత్తాంశం->screen, GFX_ఎడమ, &వెడల్పు, &ఎత్తు);
    bufsize = వెడల్పు * ఎత్తు * 4;

    ఒకవేళ (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ వెడల్పు, ఎత్తు },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    లేకపోతే ఒకవేళ (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ వెడల్పు, ఎత్తు },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    లేకపోతే
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ వెడల్పు, ఎత్తు },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_దత్తాంశం->screen);

    తిరిగి true;
}

స్థిర శూన్య CopyFramebuffertoN3DS_16(u16 *dest, స్థిరరాశి Dimensions dest_dim, స్థిరరాశి u16 *ఆధారం, స్థిరరాశి Dimensions ఆధారం_dim)
{
    పూర్ణాంకం అడ్డువరుసలు = SDL_min(dest_dim.వెడల్పు, ఆధారం_dim.ఎత్తు);
    పూర్ణాంకం నిలువుల_సంఖ్య = SDL_min(dest_dim.ఎత్తు, ఆధారం_dim.వెడల్పు);
    కొరకు (పూర్ణాంకం y = 0; y < అడ్డువరుసలు; ++y) {
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            స్థిరరాశి u16 *s = ఆధారం + Get_ఆధారం_స్థానభ్రంశం(x, y, ఆధారం_dim.వెడల్పు);
            u16 *d = dest + Get_Dest_స్థానభ్రంశం(x, y, dest_dim.వెడల్పు);
            *d = *s;
        }
    }
}

స్థిర శూన్య CopyFramebuffertoN3DS_24(u8 *dest, స్థిరరాశి Dimensions dest_dim, స్థిరరాశి u8 *ఆధారం, స్థిరరాశి Dimensions ఆధారం_dim)
{
    పూర్ణాంకం అడ్డువరుసలు = SDL_min(dest_dim.వెడల్పు, ఆధారం_dim.ఎత్తు);
    పూర్ణాంకం నిలువుల_సంఖ్య = SDL_min(dest_dim.ఎత్తు, ఆధారం_dim.వెడల్పు);
    కొరకు (పూర్ణాంకం y = 0; y < అడ్డువరుసలు; ++y) {
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            స్థిరరాశి u8 *s = ఆధారం + Get_ఆధారం_స్థానభ్రంశం(x, y, ఆధారం_dim.వెడల్పు) * 3;
            u8 *d = dest + Get_Dest_స్థానభ్రంశం(x, y, dest_dim.వెడల్పు) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

స్థిర శూన్య CopyFramebuffertoN3DS_32(u32 *dest, స్థిరరాశి Dimensions dest_dim, స్థిరరాశి u32 *ఆధారం, స్థిరరాశి Dimensions ఆధారం_dim)
{
    పూర్ణాంకం అడ్డువరుసలు = SDL_min(dest_dim.వెడల్పు, ఆధారం_dim.ఎత్తు);
    పూర్ణాంకం నిలువుల_సంఖ్య = SDL_min(dest_dim.ఎత్తు, ఆధారం_dim.వెడల్పు);
    కొరకు (పూర్ణాంకం y = 0; y < అడ్డువరుసలు; ++y) {
        కొరకు (పూర్ణాంకం x = 0; x < నిలువుల_సంఖ్య; ++x) {
            స్థిరరాశి u32 *s = ఆధారం + Get_ఆధారం_స్థానభ్రంశం(x, y, ఆధారం_dim.వెడల్పు);
            u32 *d = dest + Get_Dest_స్థానభ్రంశం(x, y, dest_dim.వెడల్పు);
            *d = *s;
        }
    }
}

స్థిర పూర్ణాంకం Get_Dest_స్థానభ్రంశం(పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం dest_వెడల్పు)
{
    తిరిగి dest_వెడల్పు - y - 1 + dest_వెడల్పు * x;
}

స్థిర పూర్ణాంకం Get_ఆధారం_స్థానభ్రంశం(పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం ఆధారం_వెడల్పు)
{
    తిరిగి x + y * ఆధారం_వెడల్పు;
}

స్థిర శూన్య FlushN3DSBuffer(స్థిరరాశి శూన్య *బఫరు_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_దత్తాంశం_Cache(బఫరు_2, bufsize);
    gfx_Screen_మార్పిడి_Buffers(screen, false);
}

శూన్య SDL_N3_DS_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_ClearProperty(SDL_Get_కిటికీ_Properties(కిటికీ), N3DS_SURFACE);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_N3DS

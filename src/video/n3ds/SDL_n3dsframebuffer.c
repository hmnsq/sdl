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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_N3DS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../SDL_properties_c.h"
#अन्तर्भाव "SDL_n3dsframebuffer_c.h"
#अन्तर्भाव "SDL_n3dsvideo.h"

#परिभाषय N3DS_SURFACE "SDL.internal.window.surface"

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क विस्तारः, height;
} Dimensions;

स्थिर शून्य CopyFramebuffertoN3DS_16(u16 *dest, ध्रुव Dimensions dest_dim, ध्रुव u16 *source, ध्रुव Dimensions source_dim);
स्थिर शून्य CopyFramebuffertoN3DS_24(u8  *dest, ध्रुव Dimensions dest_dim, ध्रुव u8  *source, ध्रुव Dimensions source_dim);
स्थिर शून्य CopyFramebuffertoN3DS_32(u32 *dest, ध्रुव Dimensions dest_dim, ध्रुव u32 *source, ध्रुव Dimensions source_dim);
स्थिर पूर्णाङ्क Get_Dest_विस्थापनम्(पूर्णाङ्क x, पूर्णाङ्क y, पूर्णाङ्क dest_विस्तारः);
स्थिर पूर्णाङ्क Get_Source_विस्थापनम्(पूर्णाङ्क x, पूर्णाङ्क y, पूर्णाङ्क source_विस्तारः);
स्थिर शून्य FlushN3DSBuffer(ध्रुव शून्य *बफर_2, u32 bufsize, gfxScreen_t screen);


bool SDL_N3_DS_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_Surface *framebuffer;
    ध्रुव SDL_Display_बहुलकम् *बहुलकम्;
    पूर्णाङ्क w, h;

    SDL_N3_DS_Destroy_गवाक्षः_Framebuffer(_this, गवाक्षः);

    बहुलकम् = SDL_Get_Current_Display_बहुलकम्(SDL_Get_Display_For_गवाक्षः(गवाक्षः));
    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);
    framebuffer = SDL_CreateSurfaceZeroed(w, h, बहुलकम्->format);

    यदि (!framebuffer) {
        प्रत्यागम false;
    }

    SDL_समुच्चयः_Surface_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), N3DS_SURFACE, framebuffer);
    *format = बहुलकम्->format;
    *pixels = framebuffer->pixels;
    *pitch = framebuffer->pitch;
    प्रत्यागम true;
}

bool SDL_N3_DS_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_गवाक्षः_दत्त *drv_दत्त = गवाक्षः->आन्तरिकम्;
    SDL_Surface *surface;
    u16 विस्तारः, height;
    शून्य *framebuffer;
    u32 bufsize;

    surface = (SDL_Surface *)SDL_GetPointerProperty(SDL_Get_गवाक्षः_Properties(गवाक्षः), N3DS_SURFACE, रिक्त);
    यदि (!surface) {
        प्रत्यागम SDL_समुच्चयः_Error("%s: Unable to get the window surface.", SDL_FUNCTION);
    }

    // Get the N3DS internal framebuffer and its size
    framebuffer = gfxGetFramebuffer(drv_दत्त->screen, GFX_वामः, &विस्तारः, &height);
    bufsize = विस्तारः * height * 4;

    यदि (SDL_BYTESPERPIXEL(surface->format) == 2)
        CopyFramebuffertoN3DS_16(framebuffer, (Dimensions){ विस्तारः, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    अन्यथा यदि (SDL_BYTESPERPIXEL(surface->format) == 3)
        CopyFramebuffertoN3DS_24(framebuffer, (Dimensions){ विस्तारः, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    अन्यथा
        CopyFramebuffertoN3DS_32(framebuffer, (Dimensions){ विस्तारः, height },
                                 surface->pixels, (Dimensions){ surface->w, surface->h });
    FlushN3DSBuffer(framebuffer, bufsize, drv_दत्त->screen);

    प्रत्यागम true;
}

स्थिर शून्य CopyFramebuffertoN3DS_16(u16 *dest, ध्रुव Dimensions dest_dim, ध्रुव u16 *source, ध्रुव Dimensions source_dim)
{
    पूर्णाङ्क पङ्क्तिकाः = SDL_min(dest_dim.विस्तारः, source_dim.height);
    पूर्णाङ्क स्तम्भसङ्ख्या = SDL_min(dest_dim.height, source_dim.विस्तारः);
    प्रति (पूर्णाङ्क y = 0; y < पङ्क्तिकाः; ++y) {
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            ध्रुव u16 *s = source + Get_Source_विस्थापनम्(x, y, source_dim.विस्तारः);
            u16 *d = dest + Get_Dest_विस्थापनम्(x, y, dest_dim.विस्तारः);
            *d = *s;
        }
    }
}

स्थिर शून्य CopyFramebuffertoN3DS_24(u8 *dest, ध्रुव Dimensions dest_dim, ध्रुव u8 *source, ध्रुव Dimensions source_dim)
{
    पूर्णाङ्क पङ्क्तिकाः = SDL_min(dest_dim.विस्तारः, source_dim.height);
    पूर्णाङ्क स्तम्भसङ्ख्या = SDL_min(dest_dim.height, source_dim.विस्तारः);
    प्रति (पूर्णाङ्क y = 0; y < पङ्क्तिकाः; ++y) {
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            ध्रुव u8 *s = source + Get_Source_विस्थापनम्(x, y, source_dim.विस्तारः) * 3;
            u8 *d = dest + Get_Dest_विस्थापनम्(x, y, dest_dim.विस्तारः) * 3;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
        }
    }
}

स्थिर शून्य CopyFramebuffertoN3DS_32(u32 *dest, ध्रुव Dimensions dest_dim, ध्रुव u32 *source, ध्रुव Dimensions source_dim)
{
    पूर्णाङ्क पङ्क्तिकाः = SDL_min(dest_dim.विस्तारः, source_dim.height);
    पूर्णाङ्क स्तम्भसङ्ख्या = SDL_min(dest_dim.height, source_dim.विस्तारः);
    प्रति (पूर्णाङ्क y = 0; y < पङ्क्तिकाः; ++y) {
        प्रति (पूर्णाङ्क x = 0; x < स्तम्भसङ्ख्या; ++x) {
            ध्रुव u32 *s = source + Get_Source_विस्थापनम्(x, y, source_dim.विस्तारः);
            u32 *d = dest + Get_Dest_विस्थापनम्(x, y, dest_dim.विस्तारः);
            *d = *s;
        }
    }
}

स्थिर पूर्णाङ्क Get_Dest_विस्थापनम्(पूर्णाङ्क x, पूर्णाङ्क y, पूर्णाङ्क dest_विस्तारः)
{
    प्रत्यागम dest_विस्तारः - y - 1 + dest_विस्तारः * x;
}

स्थिर पूर्णाङ्क Get_Source_विस्थापनम्(पूर्णाङ्क x, पूर्णाङ्क y, पूर्णाङ्क source_विस्तारः)
{
    प्रत्यागम x + y * source_विस्तारः;
}

स्थिर शून्य FlushN3DSBuffer(ध्रुव शून्य *बफर_2, u32 bufsize, gfxScreen_t screen)
{
    GSPGPU_Flush_दत्त_Cache(बफर_2, bufsize);
    gfxScreenSwapBuffers(screen, false);
}

शून्य SDL_N3_DS_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_ClearProperty(SDL_Get_गवाक्षः_Properties(गवाक्षः), N3DS_SURFACE);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_N3DS

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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_riscosframebuffer_c.h"
#અન્તર્ભાવ "SDL_riscosvideo.h"
#અન્તર્ભાવ "SDL_riscoswindow.h"

#અન્તર્ભાવ <kernel.h>
#અન્તર્ભાવ <swis.h>

bool RISCOS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_WindowData *internal = window->internal;
    અચલ અક્ષર *sprite_name = "display";
    unsigned પૂર્ણાંક sprite_mode;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    અચલ SDL_DisplayMode *mode;
    પૂર્ણાંક size;
    પૂર્ણાંક w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    RISCOS_DestroyWindowFramebuffer(_this, window);

    // Create a new one
    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    જો ((SDL_ISPIXELFORMAT_PACKED(mode->format) || SDL_ISPIXELFORMAT_ARRAY(mode->format))) {
        *format = mode->format;
        sprite_mode = (unsigned પૂર્ણાંક)mode->internal;
    } નહીંતર {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_mode = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    size = કદ(sprite_area) + કદ(sprite_header) + ((*pitch) * h);
    internal->fb_area = SDL_malloc(size);
    જો (!internal->fb_area) {
        પાછા false;
    }

    internal->fb_area->size = size;
    internal->fb_area->ગણતરી = 0;
    internal->fb_area->start = 16;
    internal->fb_area->end = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (પૂર્ણાંક)internal->fb_area;
    regs.r[2] = (પૂર્ણાંક)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_mode;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    જો (error) {
        SDL_free(internal->fb_area);
        પાછા SDL_SetError("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    internal->fb_sprite = (sprite_header *)(((Uint8 *)internal->fb_area) + internal->fb_area->start);
    *pixels = ((Uint8 *)internal->fb_sprite) + internal->fb_sprite->image_offset;

    પાછા true;
}

bool RISCOS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects)
{
    SDL_WindowData *internal = window->internal;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (પૂર્ણાંક)internal->fb_area;
    regs.r[2] = (પૂર્ણાંક)internal->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    જો (error) {
        પાછા SDL_SetError("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    પાછા true;
}

શૂન્ય RISCOS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *internal = window->internal;

    જો (internal->fb_area) {
        SDL_free(internal->fb_area);
        internal->fb_area = ખાલી;
    }
    internal->fb_sprite = ખાલી;
}

#endif // SDL_VIDEO_DRIVER_RISCOS

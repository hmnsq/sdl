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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_RISCOS

#समावेश "../SDL_sysvideo.h"
#समावेश "SDL_riscosframebuffer_c.h"
#समावेश "SDL_riscosvideo.h"
#समावेश "SDL_riscoswindow.h"

#समावेश <kernel.h>
#समावेश <swis.h>

bool RISCOS_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Window_तथ्य *internal = window->internal;
    स्थिर अक्षर *sprite_name = "display";
    अचिन्हित पूर्णांक sprite_mode;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    स्थिर SDL_DisplayMode *mode;
    पूर्णांक आकार;
    पूर्णांक w, h;

    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    // Free the old framebuffer surface
    RISCOS_DestroyWindowFramebuffer(_this, window);

    // Create a new one
    mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
    अगर ((SDL_ISPIXELFORMAT_PACKED(mode->format) || SDL_ISPIXELFORMAT_ARRAY(mode->format))) {
        *format = mode->format;
        sprite_mode = (अचिन्हित पूर्णांक)mode->internal;
    } अन्यथा {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_mode = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    आकार = माप(sprite_area) + माप(sprite_header) + ((*pitch) * h);
    internal->fb_area = SDL_malloc(आकार);
    अगर (!internal->fb_area) {
        वापस false;
    }

    internal->fb_area->आकार = आकार;
    internal->fb_area->गिनती = 0;
    internal->fb_area->start = 16;
    internal->fb_area->end = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (पूर्णांक)internal->fb_area;
    regs.r[2] = (पूर्णांक)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_mode;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    अगर (error) {
        SDL_free(internal->fb_area);
        वापस SDL_SetError("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    internal->fb_sprite = (sprite_header *)(((Uint8 *)internal->fb_area) + internal->fb_area->start);
    *pixels = ((Uint8 *)internal->fb_sprite) + internal->fb_sprite->image_offset;

    वापस true;
}

bool RISCOS_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_Window_तथ्य *internal = window->internal;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (पूर्णांक)internal->fb_area;
    regs.r[2] = (पूर्णांक)internal->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    अगर (error) {
        वापस SDL_SetError("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    वापस true;
}

व्योम RISCOS_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *internal = window->internal;

    अगर (internal->fb_area) {
        SDL_free(internal->fb_area);
        internal->fb_area = शून्य;
    }
    internal->fb_sprite = शून्य;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RISCOS

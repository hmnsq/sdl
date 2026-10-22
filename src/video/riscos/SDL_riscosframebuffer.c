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

#که_تعریف_شوی SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_riscosframebuffer_c.h"
#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscoswindow.h"

#ضمن <kernel.h>
#ضمن <swis.h>

bool RISCOS_Create_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_کړکۍ_معلومات *دننی = کړکۍ->دننی;
    ثابت حرف *sprite_name = "display";
    بینښه صحيح sprite_ډېرپېښ;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ثابت SDL_Display_ډېرپېښ *ډېرپېښ;
    صحيح اندازه;
    صحيح w, h;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_کړکۍ_Framebuffer(_this, کړکۍ);

    // Create a new one
    ډېرپېښ = SDL_Get_Current_Display_ډېرپېښ(SDL_Get_Display_For_کړکۍ(کړکۍ));
    إذا ((SDL_ISPIXELFORMAT_PACKED(ډېرپېښ->format) || SDL_ISPIXELFORMAT_ARRAY(ډېرپېښ->format))) {
        *format = ډېرپېښ->format;
        sprite_ډېرپېښ = (بینښه صحيح)ډېرپېښ->دننی;
    } وإلا {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_ډېرپېښ = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    اندازه = حجم(sprite_area) + حجم(sprite_سرلیک) + ((*pitch) * h);
    دننی->fb_area = SDL_malloc(اندازه);
    إذا (!دننی->fb_area) {
        أرجع false;
    }

    دننی->fb_area->اندازه = اندازه;
    دننی->fb_area->شمېر = 0;
    دننی->fb_area->پیل = 16;
    دننی->fb_area->پای_ټکی = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (صحيح)دننی->fb_area;
    regs.r[2] = (صحيح)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_ډېرپېښ;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        SDL_free(دننی->fb_area);
        أرجع SDL_سېټ_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    دننی->fb_sprite = (sprite_سرلیک *)(((Uint8 *)دننی->fb_area) + دننی->fb_area->پیل);
    *pixels = ((Uint8 *)دننی->fb_sprite) + دننی->fb_sprite->image_دننه_واټن_2;

    أرجع true;
}

bool RISCOS_Update_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کړکۍ_معلومات *دننی = کړکۍ->دننی;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (صحيح)دننی->fb_area;
    regs.r[2] = (صحيح)دننی->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        أرجع SDL_سېټ_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    أرجع true;
}

فراغ RISCOS_Destroy_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *دننی = کړکۍ->دننی;

    إذا (دننی->fb_area) {
        SDL_free(دننی->fb_area);
        دننی->fb_area = عدم;
    }
    دننی->fb_sprite = عدم;
}

#د_که_پای // SDL_VIDEO_DRIVER_RISCOS

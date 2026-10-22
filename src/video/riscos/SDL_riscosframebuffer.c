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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_riscosframebuffer_c.h"
#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscoswindow.h"

#ضمن <kernel.h>
#ضمن <swis.h>

bool RISCOS_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_کھڑکی_انکڑے *اندرونی = کھڑکی->اندرونی;
    ثابت حرف *sprite_name = "display";
    بنانشانی صحيح sprite_منوال;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ثابت SDL_Display_منوال *منوال;
    صحيح ناپ;
    صحيح w, h;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_کھڑکی_Framebuffer(_this, کھڑکی);

    // Create a new one
    منوال = SDL_Get_Current_Display_منوال(SDL_Get_Display_For_کھڑکی(کھڑکی));
    إذا ((SDL_ISPIXELFORMAT_PACKED(منوال->format) || SDL_ISPIXELFORMAT_ARRAY(منوال->format))) {
        *format = منوال->format;
        sprite_منوال = (بنانشانی صحيح)منوال->اندرونی;
    } وإلا {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_منوال = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    ناپ = حجم(sprite_area) + حجم(sprite_سرخی) + ((*pitch) * h);
    اندرونی->fb_area = SDL_malloc(ناپ);
    إذا (!اندرونی->fb_area) {
        أرجع false;
    }

    اندرونی->fb_area->ناپ = ناپ;
    اندرونی->fb_area->گنتی = 0;
    اندرونی->fb_area->شروع = 16;
    اندرونی->fb_area->سرا = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (صحيح)اندرونی->fb_area;
    regs.r[2] = (صحيح)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_منوال;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        SDL_free(اندرونی->fb_area);
        أرجع SDL_سیٹ_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    اندرونی->fb_sprite = (sprite_سرخی *)(((Uint8 *)اندرونی->fb_area) + اندرونی->fb_area->شروع);
    *pixels = ((Uint8 *)اندرونی->fb_sprite) + اندرونی->fb_sprite->image_وتھ_2;

    أرجع true;
}

bool RISCOS_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کھڑکی_انکڑے *اندرونی = کھڑکی->اندرونی;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (صحيح)اندرونی->fb_area;
    regs.r[2] = (صحيح)اندرونی->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        أرجع SDL_سیٹ_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    أرجع true;
}

فراغ RISCOS_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *اندرونی = کھڑکی->اندرونی;

    إذا (اندرونی->fb_area) {
        SDL_free(اندرونی->fb_area);
        اندرونی->fb_area = عدم;
    }
    اندرونی->fb_sprite = عدم;
}

#جے_انت // SDL_VIDEO_DRIVER_RISCOS

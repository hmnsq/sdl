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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_riscosframebuffer_c.h"
#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscoswindow.h"

#ضمن <kernel.h>
#ضمن <swis.h>

bool RISCOS_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_دري_معلومات *اندروني = دري->اندروني;
    ثابت حرف *sprite_name = "display";
    بنانشان صحيح sprite_گهڻائي;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ثابت SDL_Display_گهڻائي *گهڻائي;
    صحيح سائيز;
    صحيح w, h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_دري_Framebuffer(_this, دري);

    // Create a new one
    گهڻائي = SDL_Get_Current_Display_گهڻائي(SDL_Get_Display_For_دري(دري));
    إذا ((SDL_ISPIXELFORMAT_PACKED(گهڻائي->format) || SDL_ISPIXELFORMAT_ARRAY(گهڻائي->format))) {
        *format = گهڻائي->format;
        sprite_گهڻائي = (بنانشان صحيح)گهڻائي->اندروني;
    } وإلا {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_گهڻائي = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    سائيز = حجم(sprite_area) + حجم(sprite_سرو) + ((*pitch) * h);
    اندروني->fb_area = SDL_malloc(سائيز);
    إذا (!اندروني->fb_area) {
        أرجع false;
    }

    اندروني->fb_area->سائيز = سائيز;
    اندروني->fb_area->ڳڻپ = 0;
    اندروني->fb_area->شروعات = 16;
    اندروني->fb_area->پڇاڙي = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (صحيح)اندروني->fb_area;
    regs.r[2] = (صحيح)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_گهڻائي;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        SDL_free(اندروني->fb_area);
        أرجع SDL_سيٽ_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    اندروني->fb_sprite = (sprite_سرو *)(((Uint8 *)اندروني->fb_area) + اندروني->fb_area->شروعات);
    *pixels = ((Uint8 *)اندروني->fb_sprite) + اندروني->fb_sprite->image_وٿي_2;

    أرجع true;
}

bool RISCOS_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_دري_معلومات *اندروني = دري->اندروني;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (صحيح)اندروني->fb_area;
    regs.r[2] = (صحيح)اندروني->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        أرجع SDL_سيٽ_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    أرجع true;
}

فراغ RISCOS_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *اندروني = دري->اندروني;

    إذا (اندروني->fb_area) {
        SDL_free(اندروني->fb_area);
        اندروني->fb_area = عدم;
    }
    اندروني->fb_sprite = عدم;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_RISCOS

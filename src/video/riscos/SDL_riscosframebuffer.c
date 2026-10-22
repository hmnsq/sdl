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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_riscosframebuffer_c.h"
#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscoswindow.h"

#ضمن <kernel.h>
#ضمن <swis.h>

bool RISCOS_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_پنجره_داده *داخلی = پنجره->داخلی;
    ثابت حرف *sprite_name = "display";
    بیعلامت صحيح sprite_نما;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ثابت SDL_Display_نما *نما;
    صحيح اندازه;
    صحيح w, h;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_پنجره_Framebuffer(_this, پنجره);

    // Create a new one
    نما = SDL_Get_Current_Display_نما(SDL_Get_Display_For_پنجره(پنجره));
    إذا ((SDL_ISPIXELFORMAT_PACKED(نما->format) || SDL_ISPIXELFORMAT_ARRAY(نما->format))) {
        *format = نما->format;
        sprite_نما = (بیعلامت صحيح)نما->داخلی;
    } وإلا {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_نما = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    اندازه = حجم(sprite_area) + حجم(sprite_سرآیند) + ((*pitch) * h);
    داخلی->fb_area = SDL_malloc(اندازه);
    إذا (!داخلی->fb_area) {
        أرجع false;
    }

    داخلی->fb_area->اندازه = اندازه;
    داخلی->fb_area->شمار = 0;
    داخلی->fb_area->شروع = 16;
    داخلی->fb_area->انتها = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (صحيح)داخلی->fb_area;
    regs.r[2] = (صحيح)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_نما;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        SDL_free(داخلی->fb_area);
        أرجع SDL_مجموعه_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    داخلی->fb_sprite = (sprite_سرآیند *)(((Uint8 *)داخلی->fb_area) + داخلی->fb_area->شروع);
    *pixels = ((Uint8 *)داخلی->fb_sprite) + داخلی->fb_sprite->image_جابه_جایی_2;

    أرجع true;
}

bool RISCOS_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_پنجره_داده *داخلی = پنجره->داخلی;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (صحيح)داخلی->fb_area;
    regs.r[2] = (صحيح)داخلی->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    إذا (error) {
        أرجع SDL_مجموعه_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    أرجع true;
}

فراغ RISCOS_Destroy_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داخلی = پنجره->داخلی;

    إذا (داخلی->fb_area) {
        SDL_free(داخلی->fb_area);
        داخلی->fb_area = عدم;
    }
    داخلی->fb_sprite = عدم;
}

#پایان_اگر // SDL_VIDEO_DRIVER_RISCOS

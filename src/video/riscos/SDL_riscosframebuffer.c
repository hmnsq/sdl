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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_riscosframebuffer_c.h"
#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscoswindow.h"

#अन्तर्भाव <kernel.h>
#अन्तर्भाव <swis.h>

bool RISCOS_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_गवाक्षः_दत्त *आन्तरिकम् = गवाक्षः->आन्तरिकम्;
    ध्रुव वर्ण *sprite_name = "display";
    अचिह्नित पूर्णाङ्क sprite_बहुलकम्;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ध्रुव SDL_Display_बहुलकम् *बहुलकम्;
    पूर्णाङ्क आकार;
    पूर्णाङ्क w, h;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_गवाक्षः_Framebuffer(_this, गवाक्षः);

    // Create a new one
    बहुलकम् = SDL_Get_Current_Display_बहुलकम्(SDL_Get_Display_For_गवाक्षः(गवाक्षः));
    यदि ((SDL_ISPIXELFORMAT_PACKED(बहुलकम्->format) || SDL_ISPIXELFORMAT_ARRAY(बहुलकम्->format))) {
        *format = बहुलकम्->format;
        sprite_बहुलकम् = (अचिह्नित पूर्णाङ्क)बहुलकम्->आन्तरिकम्;
    } अन्यथा {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_बहुलकम् = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    आकार = परिमाण(sprite_area) + परिमाण(sprite_शीर्षकम्) + ((*pitch) * h);
    आन्तरिकम्->fb_area = SDL_malloc(आकार);
    यदि (!आन्तरिकम्->fb_area) {
        प्रत्यागम false;
    }

    आन्तरिकम्->fb_area->आकार = आकार;
    आन्तरिकम्->fb_area->गणनम् = 0;
    आन्तरिकम्->fb_area->start = 16;
    आन्तरिकम्->fb_area->अन्तः = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (पूर्णाङ्क)आन्तरिकम्->fb_area;
    regs.r[2] = (पूर्णाङ्क)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_बहुलकम्;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    यदि (error) {
        SDL_free(आन्तरिकम्->fb_area);
        प्रत्यागम SDL_समुच्चयः_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    आन्तरिकम्->fb_sprite = (sprite_शीर्षकम् *)(((Uint8 *)आन्तरिकम्->fb_area) + आन्तरिकम्->fb_area->start);
    *pixels = ((Uint8 *)आन्तरिकम्->fb_sprite) + आन्तरिकम्->fb_sprite->image_विस्थापनम्_2;

    प्रत्यागम true;
}

bool RISCOS_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_गवाक्षः_दत्त *आन्तरिकम् = गवाक्षः->आन्तरिकम्;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (पूर्णाङ्क)आन्तरिकम्->fb_area;
    regs.r[2] = (पूर्णाङ्क)आन्तरिकम्->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    यदि (error) {
        प्रत्यागम SDL_समुच्चयः_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    प्रत्यागम true;
}

शून्य RISCOS_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *आन्तरिकम् = गवाक्षः->आन्तरिकम्;

    यदि (आन्तरिकम्->fb_area) {
        SDL_free(आन्तरिकम्->fb_area);
        आन्तरिकम्->fb_area = रिक्त;
    }
    आन्तरिकम्->fb_sprite = रिक्त;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_RISCOS

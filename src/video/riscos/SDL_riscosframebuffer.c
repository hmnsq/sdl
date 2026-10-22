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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscoswindow.h"

#ಅನ್ತರ್ಭಾವ <kernel.h>
#ಅನ್ತರ್ಭಾವ <swis.h>

bool RISCOS_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಆಂತರಿಕ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sprite_name = "display";
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ sprite_ಬಹುಲಕ;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ;
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_ಕಿಟಕಿ_Framebuffer(_this, ಕಿಟಕಿ);

    // Create a new one
    ಬಹುಲಕ = SDL_Get_Current_Display_ಬಹುಲಕ(SDL_Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ));
    ಆದರೆ ((SDL_ISPIXELFORMAT_PACKED(ಬಹುಲಕ->format) || SDL_ISPIXELFORMAT_ARRAY(ಬಹುಲಕ->format))) {
        *format = ಬಹುಲಕ->format;
        sprite_ಬಹುಲಕ = (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)ಬಹುಲಕ->ಆಂತರಿಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_ಬಹುಲಕ = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    ಗಾತ್ರ_2 = ಗಾತ್ರ(sprite_area) + ಗಾತ್ರ(sprite_ಶೀರ್ಷಿಕೆ) + ((*pitch) * h);
    ಆಂತರಿಕ->fb_area = SDL_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!ಆಂತರಿಕ->fb_area) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆಂತರಿಕ->fb_area->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
    ಆಂತರಿಕ->fb_area->ಎಣಿಕೆ_2 = 0;
    ಆಂತರಿಕ->fb_area->ಆರಂಭ = 16;
    ಆಂತರಿಕ->fb_area->ಕೊನೆ = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (ಪೂರ್ಣಾಂಕ)ಆಂತರಿಕ->fb_area;
    regs.r[2] = (ಪೂರ್ಣಾಂಕ)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_ಬಹುಲಕ;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    ಆದರೆ (error) {
        SDL_free(ಆಂತರಿಕ->fb_area);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    ಆಂತರಿಕ->fb_sprite = (sprite_ಶೀರ್ಷಿಕೆ *)(((Uint8 *)ಆಂತರಿಕ->fb_area) + ಆಂತರಿಕ->fb_area->ಆರಂಭ);
    *pixels = ((Uint8 *)ಆಂತರಿಕ->fb_sprite) + ಆಂತರಿಕ->fb_sprite->image_ಸ್ಥಾನಾಂತರ_2;

    ಹಿಂತಿರುಗಿ true;
}

bool RISCOS_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಆಂತರಿಕ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (ಪೂರ್ಣಾಂಕ)ಆಂತರಿಕ->fb_area;
    regs.r[2] = (ಪೂರ್ಣಾಂಕ)ಆಂತರಿಕ->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    ಆದರೆ (error) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ RISCOS_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಆಂತರಿಕ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ಆಂತರಿಕ->fb_area) {
        SDL_free(ಆಂತರಿಕ->fb_area);
        ಆಂತರಿಕ->fb_area = ಖಾಲಿ;
    }
    ಆಂತರಿಕ->fb_sprite = ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RISCOS

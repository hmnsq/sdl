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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_riscosframebuffer_c.h"
#అన్తర్భావ "SDL_riscosvideo.h"
#అన్తర్భావ "SDL_riscoswindow.h"

#అన్తర్భావ <kernel.h>
#అన్తర్భావ <swis.h>

bool RISCOS_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_కిటికీ_దత్తాంశం *అంతర్గత = కిటికీ->అంతర్గత;
    స్థిరరాశి అక్షరం *sprite_name = "display";
    గుర్తులేని పూర్ణాంకం sprite_బహుళకం;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    స్థిరరాశి SDL_Display_బహుళకం *బహుళకం;
    పూర్ణాంకం కొలత;
    పూర్ణాంకం w, h;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_కిటికీ_Framebuffer(_this, కిటికీ);

    // Create a new one
    బహుళకం = SDL_Get_Current_Display_బహుళకం(SDL_Get_Display_For_కిటికీ(కిటికీ));
    ఒకవేళ ((SDL_ISPIXELFORMAT_PACKED(బహుళకం->format) || SDL_ISPIXELFORMAT_ARRAY(బహుళకం->format))) {
        *format = బహుళకం->format;
        sprite_బహుళకం = (గుర్తులేని పూర్ణాంకం)బహుళకం->అంతర్గత;
    } లేకపోతే {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_బహుళకం = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    కొలత = పరిమాణం(sprite_area) + పరిమాణం(sprite_శీర్షిక) + ((*pitch) * h);
    అంతర్గత->fb_area = SDL_malloc(కొలత);
    ఒకవేళ (!అంతర్గత->fb_area) {
        తిరిగి false;
    }

    అంతర్గత->fb_area->కొలత = కొలత;
    అంతర్గత->fb_area->లెక్క = 0;
    అంతర్గత->fb_area->ప్రారంభం = 16;
    అంతర్గత->fb_area->చివర = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (పూర్ణాంకం)అంతర్గత->fb_area;
    regs.r[2] = (పూర్ణాంకం)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_బహుళకం;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    ఒకవేళ (error) {
        SDL_free(అంతర్గత->fb_area);
        తిరిగి SDL_సమితి_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    అంతర్గత->fb_sprite = (sprite_శీర్షిక *)(((Uint8 *)అంతర్గత->fb_area) + అంతర్గత->fb_area->ప్రారంభం);
    *pixels = ((Uint8 *)అంతర్గత->fb_sprite) + అంతర్గత->fb_sprite->image_స్థానభ్రంశం_2;

    తిరిగి true;
}

bool RISCOS_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    SDL_కిటికీ_దత్తాంశం *అంతర్గత = కిటికీ->అంతర్గత;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (పూర్ణాంకం)అంతర్గత->fb_area;
    regs.r[2] = (పూర్ణాంకం)అంతర్గత->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    ఒకవేళ (error) {
        తిరిగి SDL_సమితి_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    తిరిగి true;
}

శూన్య RISCOS_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *అంతర్గత = కిటికీ->అంతర్గత;

    ఒకవేళ (అంతర్గత->fb_area) {
        SDL_free(అంతర్గత->fb_area);
        అంతర్గత->fb_area = ఖాళీ;
    }
    అంతర్గత->fb_sprite = ఖాళీ;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS

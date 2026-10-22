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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RISCOS

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscoswindow.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <kernel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <swis.h>

bool RISCOS_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ ਅੱਖਰ *sprite_name = "display";
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ sprite_ਬਹੁਲਕ;
    _kernel_oserror *error;
    _kernel_swi_regs regs;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ;
    ਪੂਰਨ ਮਾਪ;
    ਪੂਰਨ w, h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    // Free the old framebuffer surface
    RISCOS_Destroy_ਖਿੜਕੀ_Framebuffer(_this, ਖਿੜਕੀ);

    // Create a new one
    ਬਹੁਲਕ = SDL_Get_Current_Display_ਬਹੁਲਕ(SDL_Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ));
    ਜੇ ((SDL_ISPIXELFORMAT_PACKED(ਬਹੁਲਕ->format) || SDL_ISPIXELFORMAT_ARRAY(ਬਹੁਲਕ->format))) {
        *format = ਬਹੁਲਕ->format;
        sprite_ਬਹੁਲਕ = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    } ਨਹੀਂਤਾਂ {
        *format = SDL_PIXELFORMAT_XBGR8888;
        sprite_ਬਹੁਲਕ = (1 | (90 << 1) | (90 << 14) | (6 << 27));
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Allocate the sprite area
    ਮਾਪ = ਆਕਾਰ(sprite_area) + ਆਕਾਰ(sprite_ਸਿਰਲੇਖ) + ((*pitch) * h);
    ਅੰਦਰੂਨੀ->fb_area = SDL_malloc(ਮਾਪ);
    ਜੇ (!ਅੰਦਰੂਨੀ->fb_area) {
        ਵਾਪਸ false;
    }

    ਅੰਦਰੂਨੀ->fb_area->ਮਾਪ = ਮਾਪ;
    ਅੰਦਰੂਨੀ->fb_area->ਗਿਣਤੀ_2 = 0;
    ਅੰਦਰੂਨੀ->fb_area->ਸ਼ੁਰੂ = 16;
    ਅੰਦਰੂਨੀ->fb_area->ਸਿਰਾ = 16;

    // Create the actual image
    regs.r[0] = 256 + 15;
    regs.r[1] = (ਪੂਰਨ)ਅੰਦਰੂਨੀ->fb_area;
    regs.r[2] = (ਪੂਰਨ)sprite_name;
    regs.r[3] = 0;
    regs.r[4] = w;
    regs.r[5] = h;
    regs.r[6] = sprite_ਬਹੁਲਕ;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    ਜੇ (error) {
        SDL_free(ਅੰਦਰੂਨੀ->fb_area);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to create sprite: %s (%i)", error->errmess, error->errnum);
    }

    ਅੰਦਰੂਨੀ->fb_sprite = (sprite_ਸਿਰਲੇਖ *)(((Uint8 *)ਅੰਦਰੂਨੀ->fb_area) + ਅੰਦਰੂਨੀ->fb_area->ਸ਼ੁਰੂ);
    *pixels = ((Uint8 *)ਅੰਦਰੂਨੀ->fb_sprite) + ਅੰਦਰੂਨੀ->fb_sprite->image_ਵਿੱਥ_2;

    ਵਾਪਸ true;
}

bool RISCOS_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    _kernel_swi_regs regs;
    _kernel_oserror *error;

    regs.r[0] = 512 + 52;
    regs.r[1] = (ਪੂਰਨ)ਅੰਦਰੂਨੀ->fb_area;
    regs.r[2] = (ਪੂਰਨ)ਅੰਦਰੂਨੀ->fb_sprite;
    regs.r[3] = 0; // window->x << 1;
    regs.r[4] = 0; // window->y << 1;
    regs.r[5] = 0x50;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_SpriteOp, &regs, &regs);
    ਜੇ (error) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OS_SpriteOp 52 failed: %s (%i)", error->errmess, error->errnum);
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ RISCOS_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਦਰੂਨੀ->fb_area) {
        SDL_free(ਅੰਦਰੂਨੀ->fb_area);
        ਅੰਦਰੂਨੀ->fb_area = ਨਿਰਾ;
    }
    ਅੰਦਰੂਨੀ->fb_sprite = ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RISCOS

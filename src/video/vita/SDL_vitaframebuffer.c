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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"

#ಅನ್ತರ್ಭಾವ <psp2/kernel/sysmem.h>

#ವ್ಯಾಖ್ಯಾನಿಸು SCREEN_W             960
#ವ್ಯಾಖ್ಯಾನಿಸು SCREEN_H             544
#ವ್ಯಾಖ್ಯಾನಿಸು ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#ವ್ಯಾಖ್ಯಾನಿಸು DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

ಶೂನ್ಯ *vita_gpu_alloc(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ type, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, SceUID *uid)
{
    ಶೂನ್ಯ *mem;

    ಆದರೆ (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        ಗಾತ್ರ_2 = ALIGN(ಗಾತ್ರ_2, 256 * 1024);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾತ್ರ_2 = ALIGN(ಗಾತ್ರ_2, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_ಖಂಡ("gpu_mem", type, ಗಾತ್ರ_2, ಖಾಲಿ);

    ಆದರೆ (*uid < 0) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (sce_Kernel_Get_Mem_ಖಂಡ_ತಳ(*uid, &mem) < 0) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ mem;
}

ಶೂನ್ಯ vita_gpu_free(SceUID uid)
{
    ಶೂನ್ಯ *mem = ಖಾಲಿ;
    ಆದರೆ (sce_Kernel_Get_Mem_ಖಂಡ_ತಳ(uid, &mem) < 0) {
        ಹಿಂತಿರುಗಿ;
    }
    sce_Kernel_Free_Mem_ಖಂಡ(uid);
}

bool VITA_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Sce_Display_ಚೌಕಟ್ಟು_Buf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    ದತ್ತಾಂಶ->ಬಫರ್_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &ದತ್ತಾಂಶ->ಬಫರ್_uid);

    // SDL_memset the buffer to black
    SDL_memset(ದತ್ತಾಂಶ->ಬಫರ್_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.ಗಾತ್ರ_2 = ಗಾತ್ರ(Sce_Display_ಚೌಕಟ್ಟು_Buf);
    framebuf.ತಳ = ದತ್ತಾಂಶ->ಬಫರ್_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.ಅಗಲ = SCREEN_W;
    framebuf.ಎತ್ತರ = SCREEN_H;
    sce_Display_ಗಣ_ಚೌಕಟ್ಟು_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = ದತ್ತಾಂಶ->ಬಫರ್_2;

    ಹಿಂತಿರುಗಿ true;
}

bool VITA_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    // do nothing
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ VITA_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        // The window wasn't fully initialized
        ಹಿಂತಿರುಗಿ;
    }

    vita_gpu_free(ದತ್ತಾಂಶ->ಬಫರ್_uid);
    ದತ್ತಾಂಶ->ಬಫರ್_2 = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA

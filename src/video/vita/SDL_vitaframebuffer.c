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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VITA

#ضمن "SDL_vitavideo.h"

#ضمن <psp2/kernel/sysmem.h>

#وصف_ڪريو SCREEN_W             960
#وصف_ڪريو SCREEN_H             544
#وصف_ڪريو ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#وصف_ڪريو DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

فراغ *vita_gpu_alloc(بنانشان صحيح type, بنانشان صحيح سائيز, SceUID *uid)
{
    فراغ *mem;

    إذا (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        سائيز = ALIGN(سائيز, 256 * 1024);
    } وإلا {
        سائيز = ALIGN(سائيز, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_بلاڪ("gpu_mem", type, سائيز, عدم);

    إذا (*uid < 0) {
        أرجع عدم;
    }

    إذا (sce_Kernel_Get_Mem_بلاڪ_بنياد(*uid, &mem) < 0) {
        أرجع عدم;
    }

    أرجع mem;
}

فراغ vita_gpu_free(SceUID uid)
{
    فراغ *mem = عدم;
    إذا (sce_Kernel_Get_Mem_بلاڪ_بنياد(uid, &mem) < 0) {
        أرجع;
    }
    sce_Kernel_Free_Mem_بلاڪ(uid);
}

bool VITA_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Sce_Display_چوکٺو_Buf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    معلومات->بفر_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &معلومات->بفر_uid);

    // SDL_memset the buffer to black
    SDL_memset(معلومات->بفر_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.سائيز = حجم(Sce_Display_چوکٺو_Buf);
    framebuf.بنياد = معلومات->بفر_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.ويڪر = SCREEN_W;
    framebuf.اوچائي = SCREEN_H;
    sce_Display_سيٽ_چوکٺو_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = معلومات->بفر_2;

    أرجع true;
}

bool VITA_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    // do nothing
    أرجع true;
}

فراغ VITA_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (!معلومات) {
        // The window wasn't fully initialized
        أرجع;
    }

    vita_gpu_free(معلومات->بفر_uid);
    معلومات->بفر_2 = عدم;
    أرجع;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VITA

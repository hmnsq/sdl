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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#ضمن "SDL_vitavideo.h"

#ضمن <psp2/kernel/sysmem.h>

#تعریف_کرو SCREEN_W             960
#تعریف_کرو SCREEN_H             544
#تعریف_کرو ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#تعریف_کرو DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

فراغ *vita_gpu_alloc(بنانشانی صحيح type, بنانشانی صحيح ناپ, SceUID *uid)
{
    فراغ *mem;

    إذا (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        ناپ = ALIGN(ناپ, 256 * 1024);
    } وإلا {
        ناپ = ALIGN(ناپ, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_بلاک("gpu_mem", type, ناپ, عدم);

    إذا (*uid < 0) {
        أرجع عدم;
    }

    إذا (sce_Kernel_Get_Mem_بلاک_ادھار(*uid, &mem) < 0) {
        أرجع عدم;
    }

    أرجع mem;
}

فراغ vita_gpu_free(SceUID uid)
{
    فراغ *mem = عدم;
    إذا (sce_Kernel_Get_Mem_بلاک_ادھار(uid, &mem) < 0) {
        أرجع;
    }
    sce_Kernel_Free_Mem_بلاک(uid);
}

bool VITA_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Sce_Display_چوکھٹا_Buf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    انکڑے->بفر_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &انکڑے->بفر_uid);

    // SDL_memset the buffer to black
    SDL_memset(انکڑے->بفر_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.ناپ = حجم(Sce_Display_چوکھٹا_Buf);
    framebuf.ادھار = انکڑے->بفر_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.چوڑائی = SCREEN_W;
    framebuf.اچائی = SCREEN_H;
    sce_Display_سیٹ_چوکھٹا_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = انکڑے->بفر_2;

    أرجع true;
}

bool VITA_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects)
{
    // do nothing
    أرجع true;
}

فراغ VITA_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (!انکڑے) {
        // The window wasn't fully initialized
        أرجع;
    }

    vita_gpu_free(انکڑے->بفر_uid);
    انکڑے->بفر_2 = عدم;
    أرجع;
}

#جے_انت // SDL_VIDEO_DRIVER_VITA

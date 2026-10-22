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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#شامل "SDL_vitavideo.h"

#شامل <psp2/kernel/sysmem.h>

#تعریف_کرو SCREEN_W             960
#تعریف_کرو SCREEN_H             544
#تعریف_کرو ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#تعریف_کرو DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

خالی *vita_gpu_alloc(غیرعلامتی صحیح type, غیرعلامتی صحیح سائز, SceUID *uid)
{
    خالی *mem;

    اگر (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        سائز = ALIGN(سائز, 256 * 1024);
    } ورنہ {
        سائز = ALIGN(سائز, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_بلاک("gpu_mem", type, سائز, تہی);

    اگر (*uid < 0) {
        واپس تہی;
    }

    اگر (sce_Kernel_Get_Mem_بلاک_بنیاد(*uid, &mem) < 0) {
        واپس تہی;
    }

    واپس mem;
}

خالی vita_gpu_free(SceUID uid)
{
    خالی *mem = تہی;
    اگر (sce_Kernel_Get_Mem_بلاک_بنیاد(uid, &mem) < 0) {
        واپس;
    }
    sce_Kernel_Free_Mem_بلاک(uid);
}

bool VITA_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, خالی **pixels, صحیح *pitch)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Sce_Display_چوکھٹا_Buf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    ڈیٹا->بفر_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &ڈیٹا->بفر_uid);

    // SDL_memset the buffer to black
    SDL_memset(ڈیٹا->بفر_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.سائز = حجم(Sce_Display_چوکھٹا_Buf);
    framebuf.بنیاد = ڈیٹا->بفر_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.چوڑائی = SCREEN_W;
    framebuf.اونچائی = SCREEN_H;
    sce_Display_سیٹ_چوکھٹا_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = ڈیٹا->بفر_2;

    واپس true;
}

bool VITA_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحیح numrects)
{
    // do nothing
    واپس true;
}

خالی VITA_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (!ڈیٹا) {
        // The window wasn't fully initialized
        واپس;
    }

    vita_gpu_free(ڈیٹا->بفر_uid);
    ڈیٹا->بفر_2 = تہی;
    واپس;
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA

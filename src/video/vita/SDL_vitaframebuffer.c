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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/sysmem.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCREEN_W             960
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCREEN_H             544
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

ਖਾਲੀ *vita_gpu_alloc(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ type, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਮਾਪ, SceUID *uid)
{
    ਖਾਲੀ *mem;

    ਜੇ (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        ਮਾਪ = ALIGN(ਮਾਪ, 256 * 1024);
    } ਨਹੀਂਤਾਂ {
        ਮਾਪ = ALIGN(ਮਾਪ, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_ਖੰਡ("gpu_mem", type, ਮਾਪ, ਨਿਰਾ);

    ਜੇ (*uid < 0) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (sce_Kernel_Get_Mem_ਖੰਡ_ਅਧਾਰ(*uid, &mem) < 0) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ mem;
}

ਖਾਲੀ vita_gpu_free(SceUID uid)
{
    ਖਾਲੀ *mem = ਨਿਰਾ;
    ਜੇ (sce_Kernel_Get_Mem_ਖੰਡ_ਅਧਾਰ(uid, &mem) < 0) {
        ਵਾਪਸ;
    }
    sce_Kernel_Free_Mem_ਖੰਡ(uid);
}

bool VITA_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Sce_Display_ਚੌਖਟਾ_Buf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    ਅੰਕੜੇ->ਬਫਰ_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &ਅੰਕੜੇ->ਬਫਰ_uid);

    // SDL_memset the buffer to black
    SDL_memset(ਅੰਕੜੇ->ਬਫਰ_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.ਮਾਪ = ਆਕਾਰ(Sce_Display_ਚੌਖਟਾ_Buf);
    framebuf.ਅਧਾਰ = ਅੰਕੜੇ->ਬਫਰ_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.ਚੌੜਾਈ = SCREEN_W;
    framebuf.ਉਚਾਈ = SCREEN_H;
    sce_Display_ਸੈੱਟ_ਚੌਖਟਾ_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = ਅੰਕੜੇ->ਬਫਰ_2;

    ਵਾਪਸ true;
}

bool VITA_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    // do nothing
    ਵਾਪਸ true;
}

ਖਾਲੀ VITA_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (!ਅੰਕੜੇ) {
        // The window wasn't fully initialized
        ਵਾਪਸ;
    }

    vita_gpu_free(ਅੰਕੜੇ->ਬਫਰ_uid);
    ਅੰਕੜੇ->ਬਫਰ_2 = ਨਿਰਾ;
    ਵਾਪਸ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA

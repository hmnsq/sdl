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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA

#అన్తర్భావ "SDL_vitavideo.h"

#అన్తర్భావ <psp2/kernel/sysmem.h>

#నిర్వచించు SCREEN_W             960
#నిర్వచించు SCREEN_H             544
#నిర్వచించు ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#నిర్వచించు DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

శూన్య *vita_gpu_alloc(గుర్తులేని పూర్ణాంకం type, గుర్తులేని పూర్ణాంకం కొలత, SceUID *uid)
{
    శూన్య *mem;

    ఒకవేళ (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        కొలత = ALIGN(కొలత, 256 * 1024);
    } లేకపోతే {
        కొలత = ALIGN(కొలత, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_ఖండం("gpu_mem", type, కొలత, ఖాళీ);

    ఒకవేళ (*uid < 0) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (sce_Kernel_Get_Mem_ఖండం_పునాది(*uid, &mem) < 0) {
        తిరిగి ఖాళీ;
    }

    తిరిగి mem;
}

శూన్య vita_gpu_free(SceUID uid)
{
    శూన్య *mem = ఖాళీ;
    ఒకవేళ (sce_Kernel_Get_Mem_ఖండం_పునాది(uid, &mem) < 0) {
        తిరిగి;
    }
    sce_Kernel_Free_Mem_ఖండం(uid);
}

bool VITA_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Sce_Display_చట్రం_Buf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    దత్తాంశం->బఫరు_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &దత్తాంశం->బఫరు_uid);

    // SDL_memset the buffer to black
    SDL_memset(దత్తాంశం->బఫరు_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.కొలత = పరిమాణం(Sce_Display_చట్రం_Buf);
    framebuf.పునాది = దత్తాంశం->బఫరు_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.వెడల్పు = SCREEN_W;
    framebuf.ఎత్తు = SCREEN_H;
    sce_Display_సమితి_చట్రం_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = దత్తాంశం->బఫరు_2;

    తిరిగి true;
}

bool VITA_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    // do nothing
    తిరిగి true;
}

శూన్య VITA_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (!దత్తాంశం) {
        // The window wasn't fully initialized
        తిరిగి;
    }

    vita_gpu_free(దత్తాంశం->బఫరు_uid);
    దత్తాంశం->బఫరు_2 = ఖాళీ;
    తిరిగి;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA

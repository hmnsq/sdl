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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#অন্তর্ভাব "SDL_vitavideo.h"

#অন্তর্ভাব <psp2/kernel/sysmem.h>

#define SCREEN_W             960
#define SCREEN_H             544
#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#define DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

শূন্য *vita_gpu_alloc(unsigned পূর্ণসংখ্যা type, unsigned পূর্ণসংখ্যা আকার_2, SceUID *uid)
{
    শূন্য *mem;

    যদি (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        আকার_2 = ALIGN(আকার_2, 256 * 1024);
    } অন্যথা {
        আকার_2 = ALIGN(আকার_2, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("gpu_mem", type, আকার_2, ফাঁকা);

    যদি (*uid < 0) {
        ফেরত ফাঁকা;
    }

    যদি (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        ফেরত ফাঁকা;
    }

    ফেরত mem;
}

শূন্য vita_gpu_free(SceUID uid)
{
    শূন্য *mem = ফাঁকা;
    যদি (sceKernelGetMemBlockBase(uid, &mem) < 0) {
        ফেরত;
    }
    sceKernelFreeMemBlock(uid);
}

bool VITA_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণসংখ্যা *pitch)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    SceDisplayFrameBuf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    তথ্য->বাফার_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &তথ্য->বাফার_uid);

    // SDL_memset the buffer to black
    SDL_memset(তথ্য->বাফার_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.আকার_2 = আকার(SceDisplayFrameBuf);
    framebuf.base = তথ্য->বাফার_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.width = SCREEN_W;
    framebuf.height = SCREEN_H;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = তথ্য->বাফার_2;

    ফেরত true;
}

bool VITA_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects, পূর্ণসংখ্যা numrects)
{
    // do nothing
    ফেরত true;
}

শূন্য VITA_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (!তথ্য) {
        // The window wasn't fully initialized
        ফেরত;
    }

    vita_gpu_free(তথ্য->বাফার_uid);
    তথ্য->বাফার_2 = ফাঁকা;
    ফেরত;
}

#endif // SDL_VIDEO_DRIVER_VITA

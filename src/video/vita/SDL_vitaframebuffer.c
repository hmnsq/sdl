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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#include "SDL_vitavideo.h"

#include <psp2/kernel/sysmem.h>

#define SCREEN_W             960
#define SCREEN_H             544
#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#define DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

void *vita_gpu_alloc(unsigned පූර්ණ_සංඛ්‍යා type, unsigned පූර්ණ_සංඛ්‍යා size, SceUID *uid)
{
    void *mem;

    නම් (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        size = ALIGN(size, 256 * 1024);
    } නැතහොත් {
        size = ALIGN(size, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("gpu_mem", type, size, NULL);

    නම් (*uid < 0) {
        ආපසු NULL;
    }

    නම් (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        ආපසු NULL;
    }

    ආපසු mem;
}

void vita_gpu_free(SceUID uid)
{
    void *mem = NULL;
    නම් (sceKernelGetMemBlockBase(uid, &mem) < 0) {
        ආපසු;
    }
    sceKernelFreeMemBlock(uid);
}

bool VITA_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, void **pixels, පූර්ණ_සංඛ්‍යා *pitch)
{
    SDL_WindowData *data = window->internal;
    SceDisplayFrameBuf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    data->buffer = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &data->buffer_uid);

    // SDL_memset the buffer to black
    SDL_memset(data->buffer, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.size = parimaa_na(SceDisplayFrameBuf);
    framebuf.base = data->buffer;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.width = SCREEN_W;
    framebuf.height = SCREEN_H;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = data->buffer;

    ආපසු true;
}

bool VITA_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects, පූර්ණ_සංඛ්‍යා numrects)
{
    // do nothing
    ආපසු true;
}

void VITA_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    නම් (!data) {
        // The window wasn't fully initialized
        ආපසු;
    }

    vita_gpu_free(data->buffer_uid);
    data->buffer = NULL;
    ආපසු;
}

#endif // SDL_VIDEO_DRIVER_VITA

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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#அந்தர்பாவ "SDL_vitavideo.h"

#அந்தர்பாவ <psp2/kernel/sysmem.h>

#define SCREEN_W             960
#define SCREEN_H             544
#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#define DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

வெறுமை *vita_gpu_alloc(unsigned முழு type, unsigned முழு size, SceUID *uid)
{
    வெறுமை *mem;

    எனில் (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        size = ALIGN(size, 256 * 1024);
    } இல்லையெனில் {
        size = ALIGN(size, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("gpu_mem", type, size, வெற்று);

    எனில் (*uid < 0) {
        திரும்பு வெற்று;
    }

    எனில் (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        திரும்பு வெற்று;
    }

    திரும்பு mem;
}

வெறுமை vita_gpu_free(SceUID uid)
{
    வெறுமை *mem = வெற்று;
    எனில் (sceKernelGetMemBlockBase(uid, &mem) < 0) {
        திரும்பு;
    }
    sceKernelFreeMemBlock(uid);
}

bool VITA_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, வெறுமை **pixels, முழு *pitch)
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
    framebuf.size = அளவு(SceDisplayFrameBuf);
    framebuf.base = data->buffer;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.width = SCREEN_W;
    framebuf.height = SCREEN_H;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = data->buffer;

    திரும்பு true;
}

bool VITA_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects, முழு numrects)
{
    // do nothing
    திரும்பு true;
}

வெறுமை VITA_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    எனில் (!data) {
        // The window wasn't fully initialized
        திரும்பு;
    }

    vita_gpu_free(data->buffer_uid);
    data->buffer = வெற்று;
    திரும்பு;
}

#endif // SDL_VIDEO_DRIVER_VITA

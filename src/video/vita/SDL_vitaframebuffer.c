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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ଅନ୍ତର୍ଭାଵ "SDL_vitavideo.h"

#ଅନ୍ତର୍ଭାଵ <psp2/kernel/sysmem.h>

#define SCREEN_W             960
#define SCREEN_H             544
#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#define DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

ଶୂନ୍ୟ *vita_gpu_alloc(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା type, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା size, SceUID *uid)
{
    ଶୂନ୍ୟ *mem;

    ଯଦି (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        size = ALIGN(size, 256 * 1024);
    } ଅନ୍ୟଥା {
        size = ALIGN(size, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("gpu_mem", type, size, ଖାଲି);

    ଯଦି (*uid < 0) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ mem;
}

ଶୂନ୍ୟ vita_gpu_free(SceUID uid)
{
    ଶୂନ୍ୟ *mem = ଖାଲି;
    ଯଦି (sceKernelGetMemBlockBase(uid, &mem) < 0) {
        ଫେରନ୍ତୁ;
    }
    sceKernelFreeMemBlock(uid);
}

bool VITA_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
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
    framebuf.size = ଆକାର(SceDisplayFrameBuf);
    framebuf.base = data->buffer;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.width = SCREEN_W;
    framebuf.height = SCREEN_H;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = data->buffer;

    ଫେରନ୍ତୁ true;
}

bool VITA_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    // do nothing
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ VITA_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ଯଦି (!data) {
        // The window wasn't fully initialized
        ଫେରନ୍ତୁ;
    }

    vita_gpu_free(data->buffer_uid);
    data->buffer = ଖାଲି;
    ଫେରନ୍ତୁ;
}

#endif // SDL_VIDEO_DRIVER_VITA

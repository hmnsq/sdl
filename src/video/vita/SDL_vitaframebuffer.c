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

#ifdef SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"

#ಅನ್ತರ್ಭಾವ <psp2/kernel/sysmem.h>

#define SCREEN_W             960
#define SCREEN_H             544
#define ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#define DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

ಶೂನ್ಯ *vita_gpu_alloc(unsigned ಪೂರ್ಣಾಙ್ಕ type, unsigned ಪೂರ್ಣಾಙ್ಕ size, SceUID *uid)
{
    ಶೂನ್ಯ *mem;

    ಯದಿ (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        size = ALIGN(size, 256 * 1024);
    } ಅನ್ಯಥಾ {
        size = ALIGN(size, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("gpu_mem", type, size, ರಿಕ್ತ);

    ಯದಿ (*uid < 0) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ mem;
}

ಶೂನ್ಯ vita_gpu_free(SceUID uid)
{
    ಶೂನ್ಯ *mem = ರಿಕ್ತ;
    ಯದಿ (sceKernelGetMemBlockBase(uid, &mem) < 0) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    sceKernelFreeMemBlock(uid);
}

bool VITA_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
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
    framebuf.size = ಪರಿಮಾಣ(SceDisplayFrameBuf);
    framebuf.base = data->buffer;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.width = SCREEN_W;
    framebuf.height = SCREEN_H;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = data->buffer;

    ಪ್ರತ್ಯಾಗಮ true;
}

bool VITA_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects, ಪೂರ್ಣಾಙ್ಕ numrects)
{
    // do nothing
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ VITA_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (!data) {
        // The window wasn't fully initialized
        ಪ್ರತ್ಯಾಗಮ;
    }

    vita_gpu_free(data->buffer_uid);
    data->buffer = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ;
}

#endif // SDL_VIDEO_DRIVER_VITA

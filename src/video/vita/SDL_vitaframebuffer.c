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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_VITA

#समावेश "SDL_vitavideo.h"

#समावेश <psp2/kernel/sysmem.h>

#घोषणा SCREEN_W             960
#घोषणा SCREEN_H             544
#घोषणा ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#घोषणा DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

व्योम *vita_gpu_alloc(अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक आकार, SceUID *uid)
{
    व्योम *mem;

    अगर (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        आकार = ALIGN(आकार, 256 * 1024);
    } अन्यथा {
        आकार = ALIGN(आकार, 4 * 1024);
    }

    *uid = sceKernelAllocMemBlock("gpu_mem", type, आकार, शून्य);

    अगर (*uid < 0) {
        वापस शून्य;
    }

    अगर (sceKernelGetMemBlockBase(*uid, &mem) < 0) {
        वापस शून्य;
    }

    वापस mem;
}

व्योम vita_gpu_free(SceUID uid)
{
    व्योम *mem = शून्य;
    अगर (sceKernelGetMemBlockBase(uid, &mem) < 0) {
        वापस;
    }
    sceKernelFreeMemBlock(uid);
}

bool VITA_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    SceDisplayFrameBuf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    तथ्य->बफर_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &तथ्य->बफर_uid);

    // SDL_memset the buffer to black
    SDL_memset(तथ्य->बफर_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.आकार = माप(SceDisplayFrameBuf);
    framebuf.base = तथ्य->बफर_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.width = SCREEN_W;
    framebuf.height = SCREEN_H;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = तथ्य->बफर_2;

    वापस true;
}

bool VITA_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    // do nothing
    वापस true;
}

व्योम VITA_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (!तथ्य) {
        // The window wasn't fully initialized
        वापस;
    }

    vita_gpu_free(तथ्य->बफर_uid);
    तथ्य->बफर_2 = शून्य;
    वापस;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA

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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव "SDL_vitavideo.h"

#अन्तर्भाव <psp2/kernel/sysmem.h>

#परिभाषय SCREEN_W             960
#परिभाषय SCREEN_H             544
#परिभाषय ALIGN(x, a)          (((x) + ((a)-1)) & ~((a)-1))
#परिभाषय DISPLAY_PIXEL_FORMAT SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

शून्य *vita_gpu_alloc(अचिह्नित पूर्णाङ्क type, अचिह्नित पूर्णाङ्क आकार, SceUID *uid)
{
    शून्य *mem;

    यदि (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW) {
        आकार = ALIGN(आकार, 256 * 1024);
    } अन्यथा {
        आकार = ALIGN(आकार, 4 * 1024);
    }

    *uid = sce_Kernel_Alloc_Mem_खण्डम्("gpu_mem", type, आकार, रिक्त);

    यदि (*uid < 0) {
        प्रत्यागम रिक्त;
    }

    यदि (sce_Kernel_Get_Mem_खण्डम्_आधारः(*uid, &mem) < 0) {
        प्रत्यागम रिक्त;
    }

    प्रत्यागम mem;
}

शून्य vita_gpu_free(SceUID uid)
{
    शून्य *mem = रिक्त;
    यदि (sce_Kernel_Get_Mem_खण्डम्_आधारः(uid, &mem) < 0) {
        प्रत्यागम;
    }
    sce_Kernel_Free_Mem_खण्डम्(uid);
}

bool VITA_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SceDisplayFrameBuf framebuf;

    *format = SDL_PIXELFORMAT_ABGR8888;
    *pitch = SCREEN_W * 4;

    दत्त->बफर_2 = vita_gpu_alloc(
        SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
        4 * SCREEN_W * SCREEN_H,
        &दत्त->बफर_uid);

    // SDL_memset the buffer to black
    SDL_memset(दत्त->बफर_2, 0x0, SCREEN_W * SCREEN_H * 4);

    SDL_zero(framebuf);
    framebuf.आकार = परिमाण(SceDisplayFrameBuf);
    framebuf.आधारः = दत्त->बफर_2;
    framebuf.pitch = SCREEN_W;
    framebuf.pixelformat = DISPLAY_PIXEL_FORMAT;
    framebuf.विस्तारः = SCREEN_W;
    framebuf.height = SCREEN_H;
    sce_Display_समुच्चयः_Frame_Buf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

    *pixels = दत्त->बफर_2;

    प्रत्यागम true;
}

bool VITA_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    // do nothing
    प्रत्यागम true;
}

शून्य VITA_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (!दत्त) {
        // The window wasn't fully initialized
        प्रत्यागम;
    }

    vita_gpu_free(दत्त->बफर_uid);
    दत्त->बफर_2 = रिक्त;
    प्रत्यागम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA

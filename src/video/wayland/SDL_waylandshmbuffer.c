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

#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

#ضمن <errno.h>
#ضمن <fcntl.h>
#ضمن <limits.h>
#ضمن <signal.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>

#ضمن "SDL_waylandshmbuffer.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "single-pixel-buffer-v1-client-protocol.h"

ساكن bool مجموعه_موقت_File_اندازه(صحيح fd, off_t اندازه)
{
#اگر_تعریف_شده HAVE_POSIX_FALLOCATE
    sigset_t مجموعه, old_مجموعه;
    صحيح ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&مجموعه);
    sigaddset(&مجموعه, SIGALRM);
    sigprocmask(SIG_BLOCK, &مجموعه, &old_مجموعه);

    افعل {
        ret = posix_fallocate(fd, 0, اندازه);
    } طالما (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_مجموعه, عدم);

    إذا (ret == 0) {
        أرجع true;
    } وإلا إذا (ret != EINVAL && errno != EOPNOTSUPP) {
        أرجع false;
    }
#پایان_اگر

    إذا (ftruncate(fd, اندازه) < 0) {
        أرجع false;
    }
    أرجع true;
}

ساكن صحيح Create_موقت_FD(off_t اندازه)
{
    صحيح fd;

#اگر_تعریف_شده HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    إذا (fd >= 0) {
        fcntl(fd, F_جمع_کن_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } وإلا
#پایان_اگر
    {
        ساكن ثابت حرف قالب[] = "/sdl-shared-XXXXXX";
        ثابت حرف *xdg_مسیر;
        حرف tmp_مسیر[PATH_MAX];

        xdg_مسیر = SDL_getenv("XDG_RUNTIME_DIR");
        إذا (!xdg_مسیر) {
            أرجع -1;
        }

        SDL_strlcpy(tmp_مسیر, xdg_مسیر, PATH_MAX);
        SDL_strlcat(tmp_مسیر, قالب, PATH_MAX);

        fd = mkostemp(tmp_مسیر, O_CLOEXEC);
        إذا (fd < 0) {
            أرجع -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_مسیر);
    }

    إذا (!مجموعه_موقت_File_اندازه(fd, اندازه)) {
        close(fd);
        أرجع -1;
    }

    أرجع fd;
}

ساكن فراغ میانگیر_handle_release(فراغ *داده, بنية wl_میانگیر *wl_میانگیر)
{
    // NOP
}

ساكن بنية wl_میانگیر_listener میانگیر_listener = {
    میانگیر_handle_release
};

بنية Wayland_SHMPool
{
    بنية wl_shm_pool *shm_pool;
    فراغ *shm_pool_حافظه;
    صحيح shm_pool_اندازه;
    صحيح جابه_جایی_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(صحيح اندازه)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_داده *داده = vd->داخلی;

    إذا (اندازه <= 0) {
        أرجع عدم;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, حجم(Wayland_SHMPool));
    إذا (!shmPool) {
        أرجع عدم;
    }

    shmPool->shm_pool_اندازه = (اندازه + 15) & (~15);

    ثابت صحيح shm_fd = Create_موقت_FD(shmPool->shm_pool_اندازه);
    إذا (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_مجموعه_Error("Creating SHM buffer failed.");
        أرجع عدم;
    }

    shmPool->shm_pool_حافظه = mmap(عدم, shmPool->shm_pool_اندازه, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    إذا (shmPool->shm_pool_حافظه == MAP_FAILED) {
        shmPool->shm_pool_حافظه = عدم;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_مجموعه_Error("mmap() failed.");
        أرجع عدم;
    }

    shmPool->shm_pool = wl_shm_create_pool(داده->shm, shm_fd, shmPool->shm_pool_اندازه);
    close(shm_fd);

    أرجع shmPool;
}

بنية wl_میانگیر *Wayland_Alloc_میانگیر_From_Pool(Wayland_SHMPool *shmPool, صحيح عرض, صحيح ارتفاع, فراغ **داده)
{
    ثابت Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    إذا (!shmPool || !عرض || !ارتفاع || !داده) {
        أرجع عدم;
    }

    *داده = (Uint8 *)shmPool->shm_pool_حافظه + shmPool->جابه_جایی_2;
    بنية wl_میانگیر *میانگیر_2 = wl_shm_pool_create_میانگیر(shmPool->shm_pool, shmPool->جابه_جایی_2, عرض, ارتفاع, عرض * 4, SHM_FMT);
    wl_میانگیر_جمع_کن_listener(میانگیر_2, &میانگیر_listener, shmPool);

    shmPool->جابه_جایی_2 += عرض * ارتفاع * 4;

    أرجع میانگیر_2;
}

فراغ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    إذا (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_حافظه, shmPool->shm_pool_اندازه);
        SDL_free(shmPool);
    }
}

بنية wl_میانگیر *Wayland_Create_Single_Pixel_میانگیر(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_داده *viddata = SDL_GetVideoDevice()->داخلی;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    إذا (viddata->single_pixel_میانگیر_manager) {
        أرجع wp_single_pixel_میانگیر_manager_v1_create_u32_rgba_میانگیر(viddata->single_pixel_میانگیر_manager, r, g, b, a);
    } وإلا {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        إذا (!pool) {
            أرجع عدم;
        }

        فراغ *mem;
        بنية wl_میانگیر *wl_میانگیر = Wayland_Alloc_میانگیر_From_Pool(pool, 1, 1, &mem);

        ثابت Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, حجم(pixel));

        Wayland_ReleaseSHMPool(pool);
        أرجع wl_میانگیر;
    }
}

#پایان_اگر

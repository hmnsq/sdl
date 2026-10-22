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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

#ضمن <errno.h>
#ضمن <fcntl.h>
#ضمن <limits.h>
#ضمن <signal.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>

#ضمن "SDL_waylandshmbuffer.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "single-pixel-buffer-v1-client-protocol.h"

ساكن bool سېټ_لنډمهاله_File_اندازه(صحيح fd, off_t اندازه)
{
#که_تعریف_شوی HAVE_POSIX_FALLOCATE
    sigset_t سېټ, old_سېټ;
    صحيح ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&سېټ);
    sigaddset(&سېټ, SIGALRM);
    sigprocmask(SIG_BLOCK, &سېټ, &old_سېټ);

    افعل {
        ret = posix_fallocate(fd, 0, اندازه);
    } طالما (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_سېټ, عدم);

    إذا (ret == 0) {
        أرجع true;
    } وإلا إذا (ret != EINVAL && errno != EOPNOTSUPP) {
        أرجع false;
    }
#د_که_پای

    إذا (ftruncate(fd, اندازه) < 0) {
        أرجع false;
    }
    أرجع true;
}

ساكن صحيح Create_لنډمهاله_FD(off_t اندازه)
{
    صحيح fd;

#که_تعریف_شوی HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    إذا (fd >= 0) {
        fcntl(fd, F_جمع_کړه_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } وإلا
#د_که_پای
    {
        ساكن ثابت حرف کينډۍ[] = "/sdl-shared-XXXXXX";
        ثابت حرف *xdg_لار;
        حرف tmp_لار[PATH_MAX];

        xdg_لار = SDL_getenv("XDG_RUNTIME_DIR");
        إذا (!xdg_لار) {
            أرجع -1;
        }

        SDL_strlcpy(tmp_لار, xdg_لار, PATH_MAX);
        SDL_strlcat(tmp_لار, کينډۍ, PATH_MAX);

        fd = mkostemp(tmp_لار, O_CLOEXEC);
        إذا (fd < 0) {
            أرجع -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_لار);
    }

    إذا (!سېټ_لنډمهاله_File_اندازه(fd, اندازه)) {
        close(fd);
        أرجع -1;
    }

    أرجع fd;
}

ساكن فراغ بفر_handle_release(فراغ *معلومات, بنية wl_بفر *wl_بفر)
{
    // NOP
}

ساكن بنية wl_بفر_listener بفر_listener = {
    بفر_handle_release
};

بنية Wayland_SHMPool
{
    بنية wl_shm_pool *shm_pool;
    فراغ *shm_pool_حافظه;
    صحيح shm_pool_اندازه;
    صحيح دننه_واټن_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(صحيح اندازه)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *معلومات = vd->دننی;

    إذا (اندازه <= 0) {
        أرجع عدم;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, حجم(Wayland_SHMPool));
    إذا (!shmPool) {
        أرجع عدم;
    }

    shmPool->shm_pool_اندازه = (اندازه + 15) & (~15);

    ثابت صحيح shm_fd = Create_لنډمهاله_FD(shmPool->shm_pool_اندازه);
    إذا (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_سېټ_Error("Creating SHM buffer failed.");
        أرجع عدم;
    }

    shmPool->shm_pool_حافظه = mmap(عدم, shmPool->shm_pool_اندازه, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    إذا (shmPool->shm_pool_حافظه == MAP_FAILED) {
        shmPool->shm_pool_حافظه = عدم;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_سېټ_Error("mmap() failed.");
        أرجع عدم;
    }

    shmPool->shm_pool = wl_shm_create_pool(معلومات->shm, shm_fd, shmPool->shm_pool_اندازه);
    close(shm_fd);

    أرجع shmPool;
}

بنية wl_بفر *Wayland_Alloc_بفر_From_Pool(Wayland_SHMPool *shmPool, صحيح پلنوالی, صحيح لوړوالی, فراغ **معلومات)
{
    ثابت Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    إذا (!shmPool || !پلنوالی || !لوړوالی || !معلومات) {
        أرجع عدم;
    }

    *معلومات = (Uint8 *)shmPool->shm_pool_حافظه + shmPool->دننه_واټن_2;
    بنية wl_بفر *بفر_2 = wl_shm_pool_create_بفر(shmPool->shm_pool, shmPool->دننه_واټن_2, پلنوالی, لوړوالی, پلنوالی * 4, SHM_FMT);
    wl_بفر_جمع_کړه_listener(بفر_2, &بفر_listener, shmPool);

    shmPool->دننه_واټن_2 += پلنوالی * لوړوالی * 4;

    أرجع بفر_2;
}

فراغ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    إذا (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_حافظه, shmPool->shm_pool_اندازه);
        SDL_free(shmPool);
    }
}

بنية wl_بفر *Wayland_Create_Single_Pixel_بفر(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->دننی;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    إذا (viddata->single_pixel_بفر_manager) {
        أرجع wp_single_pixel_بفر_manager_v1_create_u32_rgba_بفر(viddata->single_pixel_بفر_manager, r, g, b, a);
    } وإلا {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        إذا (!pool) {
            أرجع عدم;
        }

        فراغ *mem;
        بنية wl_بفر *wl_بفر = Wayland_Alloc_بفر_From_Pool(pool, 1, 1, &mem);

        ثابت Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, حجم(pixel));

        Wayland_ReleaseSHMPool(pool);
        أرجع wl_بفر;
    }
}

#د_که_پای

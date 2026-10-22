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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <sys/mman.h>
#অন্তর্ভাব <unistd.h>

#অন্তর্ভাব "SDL_waylandshmbuffer.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "single-pixel-buffer-v1-client-protocol.h"

স্থির bool Set_অস্থায়ী_File_আকার(পূর্ণসংখ্যা fd, off_t আকার_2)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    পূর্ণসংখ্যা ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    করো {
        ret = posix_fallocate(fd, 0, আকার_2);
    } যখন (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, ফাঁকা);

    যদি (ret == 0) {
        ফেরত true;
    } অন্যথা যদি (ret != EINVAL && errno != EOPNOTSUPP) {
        ফেরত false;
    }
#endif

    যদি (ftruncate(fd, আকার_2) < 0) {
        ফেরত false;
    }
    ফেরত true;
}

স্থির পূর্ণসংখ্যা Create_অস্থায়ী_FD(off_t আকার_2)
{
    পূর্ণসংখ্যা fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    যদি (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } অন্যথা
#endif
    {
        স্থির ধ্রুবক অক্ষর template[] = "/sdl-shared-XXXXXX";
        ধ্রুবক অক্ষর *xdg_path;
        অক্ষর tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        যদি (!xdg_path) {
            ফেরত -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        যদি (fd < 0) {
            ফেরত -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    যদি (!Set_অস্থায়ী_File_আকার(fd, আকার_2)) {
        close(fd);
        ফেরত -1;
    }

    ফেরত fd;
}

স্থির শূন্য বাফার_handle_release(শূন্য *তথ্য, কাঠামো wl_বাফার *wl_বাফার)
{
    // NOP
}

স্থির কাঠামো wl_বাফার_listener বাফার_listener = {
    বাফার_handle_release
};

কাঠামো Wayland_SHMPool
{
    কাঠামো wl_shm_pool *shm_pool;
    শূন্য *shm_pool_memory;
    পূর্ণসংখ্যা shm_pool_আকার;
    পূর্ণসংখ্যা offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(পূর্ণসংখ্যা আকার_2)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_তথ্য *তথ্য = vd->internal;

    যদি (আকার_2 <= 0) {
        ফেরত ফাঁকা;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, আকার(Wayland_SHMPool));
    যদি (!shmPool) {
        ফেরত ফাঁকা;
    }

    shmPool->shm_pool_আকার = (আকার_2 + 15) & (~15);

    ধ্রুবক পূর্ণসংখ্যা shm_fd = Create_অস্থায়ী_FD(shmPool->shm_pool_আকার);
    যদি (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        ফেরত ফাঁকা;
    }

    shmPool->shm_pool_memory = mmap(ফাঁকা, shmPool->shm_pool_আকার, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    যদি (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = ফাঁকা;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        ফেরত ফাঁকা;
    }

    shmPool->shm_pool = wl_shm_create_pool(তথ্য->shm, shm_fd, shmPool->shm_pool_আকার);
    close(shm_fd);

    ফেরত shmPool;
}

কাঠামো wl_বাফার *Wayland_Alloc_বাফার_From_Pool(Wayland_SHMPool *shmPool, পূর্ণসংখ্যা width, পূর্ণসংখ্যা height, শূন্য **তথ্য)
{
    ধ্রুবক Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    যদি (!shmPool || !width || !height || !তথ্য) {
        ফেরত ফাঁকা;
    }

    *তথ্য = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    কাঠামো wl_বাফার *বাফার_2 = wl_shm_pool_create_বাফার(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_বাফার_add_listener(বাফার_2, &বাফার_listener, shmPool);

    shmPool->offset += width * height * 4;

    ফেরত বাফার_2;
}

শূন্য Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    যদি (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_আকার);
        SDL_free(shmPool);
    }
}

কাঠামো wl_বাফার *Wayland_Create_Single_Pixel_বাফার(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_তথ্য *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    যদি (viddata->single_pixel_বাফার_manager) {
        ফেরত wp_single_pixel_বাফার_manager_v1_create_u32_rgba_বাফার(viddata->single_pixel_বাফার_manager, r, g, b, a);
    } অন্যথা {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        যদি (!pool) {
            ফেরত ফাঁকা;
        }

        শূন্য *mem;
        কাঠামো wl_বাফার *wl_বাফার = Wayland_Alloc_বাফার_From_Pool(pool, 1, 1, &mem);

        ধ্রুবক Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, আকার(pixel));

        Wayland_ReleaseSHMPool(pool);
        ফেরত wl_বাফার;
    }
}

#endif

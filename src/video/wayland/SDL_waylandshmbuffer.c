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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ضمن <errno.h>
#ضمن <fcntl.h>
#ضمن <limits.h>
#ضمن <signal.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>

#ضمن "SDL_waylandshmbuffer.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "single-pixel-buffer-v1-client-protocol.h"

ساكن bool SetTempFileSize(صحيح fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    صحيح ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    افعل {
        ret = posix_fallocate(fd, 0, size);
    } بينما (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, عدم);

    إذا (ret == 0) {
        إرجاع true;
    } وإلا إذا (ret != EINVAL && errno != EOPNOTSUPP) {
        إرجاع false;
    }
#endif

    إذا (ftruncate(fd, size) < 0) {
        إرجاع false;
    }
    إرجاع true;
}

ساكن صحيح CreateTempFD(off_t size)
{
    صحيح fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    إذا (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } وإلا
#endif
    {
        ساكن ثابت حرف template[] = "/sdl-shared-XXXXXX";
        ثابت حرف *xdg_path;
        حرف tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        إذا (!xdg_path) {
            إرجاع -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        إذا (fd < 0) {
            إرجاع -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    إذا (!SetTempFileSize(fd, size)) {
        close(fd);
        إرجاع -1;
    }

    إرجاع fd;
}

ساكن فراغ buffer_handle_release(فراغ *data, بنية wl_buffer *wl_buffer)
{
    // NOP
}

ساكن بنية wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

بنية Wayland_SHMPool
{
    بنية wl_shm_pool *shm_pool;
    فراغ *shm_pool_memory;
    صحيح shm_pool_size;
    صحيح offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(صحيح size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    إذا (size <= 0) {
        إرجاع عدم;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, حجم(Wayland_SHMPool));
    إذا (!shmPool) {
        إرجاع عدم;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    ثابت صحيح shm_fd = CreateTempFD(shmPool->shm_pool_size);
    إذا (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        إرجاع عدم;
    }

    shmPool->shm_pool_memory = mmap(عدم, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    إذا (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = عدم;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        إرجاع عدم;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    إرجاع shmPool;
}

بنية wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, صحيح width, صحيح height, فراغ **data)
{
    ثابت Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    إذا (!shmPool || !width || !height || !data) {
        إرجاع عدم;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    بنية wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    إرجاع buffer;
}

فراغ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    إذا (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

بنية wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    إذا (viddata->single_pixel_buffer_manager) {
        إرجاع wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } وإلا {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        إذا (!pool) {
            إرجاع عدم;
        }

        فراغ *mem;
        بنية wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        ثابت Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, حجم(pixel));

        Wayland_ReleaseSHMPool(pool);
        إرجاع wl_buffer;
    }
}

#endif

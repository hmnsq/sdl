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

#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#شامل <errno.h>
#شامل <fcntl.h>
#شامل <limits.h>
#شامل <signal.h>
#شامل <sys/mman.h>
#شامل <unistd.h>

#شامل "SDL_waylandshmbuffer.h"
#شامل "SDL_waylandvideo.h"
#شامل "single-pixel-buffer-v1-client-protocol.h"

ایستا bool SetTempFileSize(صحیح fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    صحیح ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    انجامبده {
        ret = posix_fallocate(fd, 0, size);
    } وقتی (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, پوچ);

    اگر (ret == 0) {
        بازگشت true;
    } وگرنه اگر (ret != EINVAL && errno != EOPNOTSUPP) {
        بازگشت false;
    }
#endif

    اگر (ftruncate(fd, size) < 0) {
        بازگشت false;
    }
    بازگشت true;
}

ایستا صحیح CreateTempFD(off_t size)
{
    صحیح fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    اگر (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } وگرنه
#endif
    {
        ایستا ثابت نویسه template[] = "/sdl-shared-XXXXXX";
        ثابت نویسه *xdg_path;
        نویسه tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        اگر (!xdg_path) {
            بازگشت -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        اگر (fd < 0) {
            بازگشت -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    اگر (!SetTempFileSize(fd, size)) {
        close(fd);
        بازگشت -1;
    }

    بازگشت fd;
}

ایستا تهی buffer_handle_release(تهی *data, ساختار wl_buffer *wl_buffer)
{
    // NOP
}

ایستا ساختار wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

ساختار Wayland_SHMPool
{
    ساختار wl_shm_pool *shm_pool;
    تهی *shm_pool_memory;
    صحیح shm_pool_size;
    صحیح offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(صحیح size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    اگر (size <= 0) {
        بازگشت پوچ;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, اندازه(Wayland_SHMPool));
    اگر (!shmPool) {
        بازگشت پوچ;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    ثابت صحیح shm_fd = CreateTempFD(shmPool->shm_pool_size);
    اگر (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        بازگشت پوچ;
    }

    shmPool->shm_pool_memory = mmap(پوچ, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    اگر (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = پوچ;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        بازگشت پوچ;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    بازگشت shmPool;
}

ساختار wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, صحیح width, صحیح height, تهی **data)
{
    ثابت Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    اگر (!shmPool || !width || !height || !data) {
        بازگشت پوچ;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    ساختار wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    بازگشت buffer;
}

تهی Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    اگر (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

ساختار wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    اگر (viddata->single_pixel_buffer_manager) {
        بازگشت wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } وگرنه {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        اگر (!pool) {
            بازگشت پوچ;
        }

        تهی *mem;
        ساختار wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        ثابت Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, اندازه(pixel));

        Wayland_ReleaseSHMPool(pool);
        بازگشت wl_buffer;
    }
}

#endif

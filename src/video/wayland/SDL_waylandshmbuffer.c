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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

#ಅನ್ತರ್ಭಾವ "SDL_waylandshmbuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "single-pixel-buffer-v1-client-protocol.h"

ಸ್ಥಿರ bool SetTempFileSize(ಪೂರ್ಣಾಙ್ಕ fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    ಪೂರ್ಣಾಙ್ಕ ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    ಕುರು {
        ret = posix_fallocate(fd, 0, size);
    } ಯಾವತ್ (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, ರಿಕ್ತ);

    ಯದಿ (ret == 0) {
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ ಯದಿ (ret != EINVAL && errno != EOPNOTSUPP) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
#endif

    ಯದಿ (ftruncate(fd, size) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ CreateTempFD(off_t size)
{
    ಪೂರ್ಣಾಙ್ಕ fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    ಯದಿ (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } ಅನ್ಯಥಾ
#endif
    {
        ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ template[] = "/sdl-shared-XXXXXX";
        ಧ್ರುವ ವರ್ಣ *xdg_path;
        ವರ್ಣ tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        ಯದಿ (!xdg_path) {
            ಪ್ರತ್ಯಾಗಮ -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        ಯದಿ (fd < 0) {
            ಪ್ರತ್ಯಾಗಮ -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    ಯದಿ (!SetTempFileSize(fd, size)) {
        close(fd);
        ಪ್ರತ್ಯಾಗಮ -1;
    }

    ಪ್ರತ್ಯಾಗಮ fd;
}

ಸ್ಥಿರ ಶೂನ್ಯ buffer_handle_release(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_buffer *wl_buffer)
{
    // NOP
}

ಸ್ಥಿರ ಸಂರಚನಾ wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

ಸಂರಚನಾ Wayland_SHMPool
{
    ಸಂರಚನಾ wl_shm_pool *shm_pool;
    ಶೂನ್ಯ *shm_pool_memory;
    ಪೂರ್ಣಾಙ್ಕ shm_pool_size;
    ಪೂರ್ಣಾಙ್ಕ offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(ಪೂರ್ಣಾಙ್ಕ size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    ಯದಿ (size <= 0) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, ಪರಿಮಾಣ(Wayland_SHMPool));
    ಯದಿ (!shmPool) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ shm_fd = CreateTempFD(shmPool->shm_pool_size);
    ಯದಿ (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    shmPool->shm_pool_memory = mmap(ರಿಕ್ತ, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ಯದಿ (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = ರಿಕ್ತ;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    ಪ್ರತ್ಯಾಗಮ shmPool;
}

ಸಂರಚನಾ wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, ಶೂನ್ಯ **data)
{
    ಧ್ರುವ Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    ಯದಿ (!shmPool || !width || !height || !data) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    ಸಂರಚನಾ wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    ಪ್ರತ್ಯಾಗಮ buffer;
}

ಶೂನ್ಯ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    ಯದಿ (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

ಸಂರಚನಾ wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    ಯದಿ (viddata->single_pixel_buffer_manager) {
        ಪ್ರತ್ಯಾಗಮ wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } ಅನ್ಯಥಾ {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        ಯದಿ (!pool) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        ಶೂನ್ಯ *mem;
        ಸಂರಚನಾ wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        ಧ್ರುವ Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, ಪರಿಮಾಣ(pixel));

        Wayland_ReleaseSHMPool(pool);
        ಪ್ರತ್ಯಾಗಮ wl_buffer;
    }
}

#endif

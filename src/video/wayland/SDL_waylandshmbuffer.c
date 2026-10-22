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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

#include "SDL_waylandshmbuffer.h"
#include "SDL_waylandvideo.h"
#include "single-pixel-buffer-v1-client-protocol.h"

static bool SetTempFileSize(số_nguyên fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    số_nguyên ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    do {
        ret = posix_fallocate(fd, 0, size);
    } trong_khi (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, NULL);

    nếu (ret == 0) {
        trả_về true;
    } không_thì nếu (ret != EINVAL && errno != EOPNOTSUPP) {
        trả_về false;
    }
#endif

    nếu (ftruncate(fd, size) < 0) {
        trả_về false;
    }
    trả_về true;
}

static số_nguyên CreateTempFD(off_t size)
{
    số_nguyên fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    nếu (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } không_thì
#endif
    {
        static const char template[] = "/sdl-shared-XXXXXX";
        const char *xdg_path;
        char tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        nếu (!xdg_path) {
            trả_về -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        nếu (fd < 0) {
            trả_về -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    nếu (!SetTempFileSize(fd, size)) {
        close(fd);
        trả_về -1;
    }

    trả_về fd;
}

static void buffer_handle_release(void *data, struct wl_buffer *wl_buffer)
{
    // NOP
}

static struct wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

struct Wayland_SHMPool
{
    struct wl_shm_pool *shm_pool;
    void *shm_pool_memory;
    số_nguyên shm_pool_size;
    số_nguyên offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(số_nguyên size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    nếu (size <= 0) {
        trả_về NULL;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, sizeof(Wayland_SHMPool));
    nếu (!shmPool) {
        trả_về NULL;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    const số_nguyên shm_fd = CreateTempFD(shmPool->shm_pool_size);
    nếu (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        trả_về NULL;
    }

    shmPool->shm_pool_memory = mmap(NULL, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    nếu (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = NULL;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        trả_về NULL;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    trả_về shmPool;
}

struct wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, số_nguyên width, số_nguyên height, void **data)
{
    const Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    nếu (!shmPool || !width || !height || !data) {
        trả_về NULL;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    trả_về buffer;
}

void Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    nếu (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

struct wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    nếu (viddata->single_pixel_buffer_manager) {
        trả_về wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } không_thì {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        nếu (!pool) {
            trả_về NULL;
        }

        void *mem;
        struct wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        const Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, sizeof(pixel));

        Wayland_ReleaseSHMPool(pool);
        trả_về wl_buffer;
    }
}

#endif

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

static bool SetTempFileSize(puur_naa_nka fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    puur_naa_nka ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    do {
        ret = posix_fallocate(fd, 0, size);
    } ၶၢဝ်း (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, NULL);

    ပေႃး (ret == 0) {
        ပွၵ်ႈ true;
    } ပေႃးဢမ်ႇ ပေႃး (ret != EINVAL && errno != EOPNOTSUPP) {
        ပွၵ်ႈ false;
    }
#endif

    ပေႃး (ftruncate(fd, size) < 0) {
        ပွၵ်ႈ false;
    }
    ပွၵ်ႈ true;
}

static puur_naa_nka CreateTempFD(off_t size)
{
    puur_naa_nka fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    ပေႃး (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } ပေႃးဢမ်ႇ
#endif
    {
        static const var_na template[] = "/sdl-shared-XXXXXX";
        const var_na *xdg_path;
        var_na tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        ပေႃး (!xdg_path) {
            ပွၵ်ႈ -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        ပေႃး (fd < 0) {
            ပွၵ်ႈ -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    ပေႃး (!SetTempFileSize(fd, size)) {
        close(fd);
        ပွၵ်ႈ -1;
    }

    ပွၵ်ႈ fd;
}

static void buffer_handle_release(void *data, sa_nracanaa wl_buffer *wl_buffer)
{
    // NOP
}

static sa_nracanaa wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

sa_nracanaa Wayland_SHMPool
{
    sa_nracanaa wl_shm_pool *shm_pool;
    void *shm_pool_memory;
    puur_naa_nka shm_pool_size;
    puur_naa_nka offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(puur_naa_nka size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    ပေႃး (size <= 0) {
        ပွၵ်ႈ NULL;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, parimaa_na(Wayland_SHMPool));
    ပေႃး (!shmPool) {
        ပွၵ်ႈ NULL;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    const puur_naa_nka shm_fd = CreateTempFD(shmPool->shm_pool_size);
    ပေႃး (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        ပွၵ်ႈ NULL;
    }

    shmPool->shm_pool_memory = mmap(NULL, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ပေႃး (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = NULL;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        ပွၵ်ႈ NULL;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    ပွၵ်ႈ shmPool;
}

sa_nracanaa wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, puur_naa_nka width, puur_naa_nka height, void **data)
{
    const Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    ပေႃး (!shmPool || !width || !height || !data) {
        ပွၵ်ႈ NULL;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    sa_nracanaa wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    ပွၵ်ႈ buffer;
}

void Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    ပေႃး (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

sa_nracanaa wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    ပေႃး (viddata->single_pixel_buffer_manager) {
        ပွၵ်ႈ wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } ပေႃးဢမ်ႇ {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        ပေႃး (!pool) {
            ပွၵ်ႈ NULL;
        }

        void *mem;
        sa_nracanaa wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        const Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, parimaa_na(pixel));

        Wayland_ReleaseSHMPool(pool);
        ပွၵ်ႈ wl_buffer;
    }
}

#endif

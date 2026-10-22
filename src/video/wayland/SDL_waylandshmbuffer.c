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

static bool SetTempFileSize(ཧྲིལ fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    ཧྲིལ ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    do {
        ret = posix_fallocate(fd, 0, size);
    } སྐབས (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, NULL);

    གལ་ཏེ (ret == 0) {
        ཕྱིར true;
    } དེ་མིན གལ་ཏེ (ret != EINVAL && errno != EOPNOTSUPP) {
        ཕྱིར false;
    }
#endif

    གལ་ཏེ (ftruncate(fd, size) < 0) {
        ཕྱིར false;
    }
    ཕྱིར true;
}

static ཧྲིལ CreateTempFD(off_t size)
{
    ཧྲིལ fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    གལ་ཏེ (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } དེ་མིན
#endif
    {
        static const var_na template[] = "/sdl-shared-XXXXXX";
        const var_na *xdg_path;
        var_na tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        གལ་ཏེ (!xdg_path) {
            ཕྱིར -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        གལ་ཏེ (fd < 0) {
            ཕྱིར -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    གལ་ཏེ (!SetTempFileSize(fd, size)) {
        close(fd);
        ཕྱིར -1;
    }

    ཕྱིར fd;
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
    ཧྲིལ shm_pool_size;
    ཧྲིལ offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(ཧྲིལ size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    གལ་ཏེ (size <= 0) {
        ཕྱིར NULL;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, parimaa_na(Wayland_SHMPool));
    གལ་ཏེ (!shmPool) {
        ཕྱིར NULL;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    const ཧྲིལ shm_fd = CreateTempFD(shmPool->shm_pool_size);
    གལ་ཏེ (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        ཕྱིར NULL;
    }

    shmPool->shm_pool_memory = mmap(NULL, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    གལ་ཏེ (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = NULL;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        ཕྱིར NULL;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    ཕྱིར shmPool;
}

sa_nracanaa wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, ཧྲིལ width, ཧྲིལ height, void **data)
{
    const Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    གལ་ཏེ (!shmPool || !width || !height || !data) {
        ཕྱིར NULL;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    sa_nracanaa wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    ཕྱིར buffer;
}

void Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    གལ་ཏེ (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

sa_nracanaa wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    གལ་ཏེ (viddata->single_pixel_buffer_manager) {
        ཕྱིར wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } དེ་མིན {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        གལ་ཏེ (!pool) {
            ཕྱིར NULL;
        }

        void *mem;
        sa_nracanaa wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        const Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, parimaa_na(pixel));

        Wayland_ReleaseSHMPool(pool);
        ཕྱིར wl_buffer;
    }
}

#endif

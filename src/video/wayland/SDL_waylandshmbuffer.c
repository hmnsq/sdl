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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <signal.h>
#அந்தர்பாவ <sys/mman.h>
#அந்தர்பாவ <unistd.h>

#அந்தர்பாவ "SDL_waylandshmbuffer.h"
#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "single-pixel-buffer-v1-client-protocol.h"

நிலையான bool SetTempFileSize(முழு fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    முழு ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    செய் {
        ret = posix_fallocate(fd, 0, size);
    } போது (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, வெற்று);

    எனில் (ret == 0) {
        திரும்பு true;
    } இல்லையெனில் எனில் (ret != EINVAL && errno != EOPNOTSUPP) {
        திரும்பு false;
    }
#endif

    எனில் (ftruncate(fd, size) < 0) {
        திரும்பு false;
    }
    திரும்பு true;
}

நிலையான முழு CreateTempFD(off_t size)
{
    முழு fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    எனில் (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } இல்லையெனில்
#endif
    {
        நிலையான மாறிலி எழுத்து template[] = "/sdl-shared-XXXXXX";
        மாறிலி எழுத்து *xdg_path;
        எழுத்து tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        எனில் (!xdg_path) {
            திரும்பு -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        எனில் (fd < 0) {
            திரும்பு -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    எனில் (!SetTempFileSize(fd, size)) {
        close(fd);
        திரும்பு -1;
    }

    திரும்பு fd;
}

நிலையான வெறுமை buffer_handle_release(வெறுமை *data, கட்டமைப்பு wl_buffer *wl_buffer)
{
    // NOP
}

நிலையான கட்டமைப்பு wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

கட்டமைப்பு Wayland_SHMPool
{
    கட்டமைப்பு wl_shm_pool *shm_pool;
    வெறுமை *shm_pool_memory;
    முழு shm_pool_size;
    முழு offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(முழு size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    எனில் (size <= 0) {
        திரும்பு வெற்று;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, அளவு(Wayland_SHMPool));
    எனில் (!shmPool) {
        திரும்பு வெற்று;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    மாறிலி முழு shm_fd = CreateTempFD(shmPool->shm_pool_size);
    எனில் (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        திரும்பு வெற்று;
    }

    shmPool->shm_pool_memory = mmap(வெற்று, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    எனில் (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = வெற்று;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        திரும்பு வெற்று;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    திரும்பு shmPool;
}

கட்டமைப்பு wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, முழு width, முழு height, வெறுமை **data)
{
    மாறிலி Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    எனில் (!shmPool || !width || !height || !data) {
        திரும்பு வெற்று;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    கட்டமைப்பு wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    திரும்பு buffer;
}

வெறுமை Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    எனில் (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

கட்டமைப்பு wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    எனில் (viddata->single_pixel_buffer_manager) {
        திரும்பு wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } இல்லையெனில் {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        எனில் (!pool) {
            திரும்பு வெற்று;
        }

        வெறுமை *mem;
        கட்டமைப்பு wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        மாறிலி Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, அளவு(pixel));

        Wayland_ReleaseSHMPool(pool);
        திரும்பு wl_buffer;
    }
}

#endif

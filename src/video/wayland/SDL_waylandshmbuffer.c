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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <signal.h>
#અન્તર્ભાવ <sys/mman.h>
#અન્તર્ભાવ <unistd.h>

#અન્તર્ભાવ "SDL_waylandshmbuffer.h"
#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "single-pixel-buffer-v1-client-protocol.h"

સ્થિર bool SetTempFileSize(પૂર્ણાંક fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    પૂર્ણાંક ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    કરો {
        ret = posix_fallocate(fd, 0, size);
    } જ્યારે (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, ખાલી);

    જો (ret == 0) {
        પાછા true;
    } નહીંતર જો (ret != EINVAL && errno != EOPNOTSUPP) {
        પાછા false;
    }
#endif

    જો (ftruncate(fd, size) < 0) {
        પાછા false;
    }
    પાછા true;
}

સ્થિર પૂર્ણાંક CreateTempFD(off_t size)
{
    પૂર્ણાંક fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    જો (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } નહીંતર
#endif
    {
        સ્થિર અચલ અક્ષર template[] = "/sdl-shared-XXXXXX";
        અચલ અક્ષર *xdg_path;
        અક્ષર tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        જો (!xdg_path) {
            પાછા -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        જો (fd < 0) {
            પાછા -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    જો (!SetTempFileSize(fd, size)) {
        close(fd);
        પાછા -1;
    }

    પાછા fd;
}

સ્થિર શૂન્ય buffer_handle_release(શૂન્ય *data, સંરચના wl_buffer *wl_buffer)
{
    // NOP
}

સ્થિર સંરચના wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

સંરચના Wayland_SHMPool
{
    સંરચના wl_shm_pool *shm_pool;
    શૂન્ય *shm_pool_memory;
    પૂર્ણાંક shm_pool_size;
    પૂર્ણાંક offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(પૂર્ણાંક size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    જો (size <= 0) {
        પાછા ખાલી;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, કદ(Wayland_SHMPool));
    જો (!shmPool) {
        પાછા ખાલી;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    અચલ પૂર્ણાંક shm_fd = CreateTempFD(shmPool->shm_pool_size);
    જો (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        પાછા ખાલી;
    }

    shmPool->shm_pool_memory = mmap(ખાલી, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    જો (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = ખાલી;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        પાછા ખાલી;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    પાછા shmPool;
}

સંરચના wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, પૂર્ણાંક width, પૂર્ણાંક height, શૂન્ય **data)
{
    અચલ Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    જો (!shmPool || !width || !height || !data) {
        પાછા ખાલી;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    સંરચના wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    પાછા buffer;
}

શૂન્ય Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    જો (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

સંરચના wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    જો (viddata->single_pixel_buffer_manager) {
        પાછા wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } નહીંતર {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        જો (!pool) {
            પાછા ખાલી;
        }

        શૂન્ય *mem;
        સંરચના wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        અચલ Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, કદ(pixel));

        Wayland_ReleaseSHMPool(pool);
        પાછા wl_buffer;
    }
}

#endif

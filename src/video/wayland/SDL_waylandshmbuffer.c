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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <signal.h>
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

#ଅନ୍ତର୍ଭାଵ "SDL_waylandshmbuffer.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"
#ଅନ୍ତର୍ଭାଵ "single-pixel-buffer-v1-client-protocol.h"

ସ୍ଥିର bool SetTempFileSize(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    କର {
        ret = posix_fallocate(fd, 0, size);
    } ଯେତେବେଳେ (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, ଖାଲି);

    ଯଦି (ret == 0) {
        ଫେରନ୍ତୁ true;
    } ଅନ୍ୟଥା ଯଦି (ret != EINVAL && errno != EOPNOTSUPP) {
        ଫେରନ୍ତୁ false;
    }
#endif

    ଯଦି (ftruncate(fd, size) < 0) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା CreateTempFD(off_t size)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    ଯଦି (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } ଅନ୍ୟଥା
#endif
    {
        ସ୍ଥିର ଅଚଳ ଅକ୍ଷର template[] = "/sdl-shared-XXXXXX";
        ଅଚଳ ଅକ୍ଷର *xdg_path;
        ଅକ୍ଷର tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        ଯଦି (!xdg_path) {
            ଫେରନ୍ତୁ -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        ଯଦି (fd < 0) {
            ଫେରନ୍ତୁ -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    ଯଦି (!SetTempFileSize(fd, size)) {
        close(fd);
        ଫେରନ୍ତୁ -1;
    }

    ଫେରନ୍ତୁ fd;
}

ସ୍ଥିର ଶୂନ୍ୟ buffer_handle_release(ଶୂନ୍ୟ *data, ସଂରଚନା wl_buffer *wl_buffer)
{
    // NOP
}

ସ୍ଥିର ସଂରଚନା wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

ସଂରଚନା Wayland_SHMPool
{
    ସଂରଚନା wl_shm_pool *shm_pool;
    ଶୂନ୍ୟ *shm_pool_memory;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shm_pool_size;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    ଯଦି (size <= 0) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, ଆକାର(Wayland_SHMPool));
    ଯଦି (!shmPool) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା shm_fd = CreateTempFD(shmPool->shm_pool_size);
    ଯଦି (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    shmPool->shm_pool_memory = mmap(ଖାଲି, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ଯଦି (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = ଖାଲି;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    ଫେରନ୍ତୁ shmPool;
}

ସଂରଚନା wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, ଶୂନ୍ୟ **data)
{
    ଅଚଳ Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    ଯଦି (!shmPool || !width || !height || !data) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    ସଂରଚନା wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    ଫେରନ୍ତୁ buffer;
}

ଶୂନ୍ୟ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    ଯଦି (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

ସଂରଚନା wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    ଯଦି (viddata->single_pixel_buffer_manager) {
        ଫେରନ୍ତୁ wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } ଅନ୍ୟଥା {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        ଯଦି (!pool) {
            ଫେରନ୍ତୁ ଖାଲି;
        }

        ଶୂନ୍ୟ *mem;
        ସଂରଚନା wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        ଅଚଳ Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, ଆକାର(pixel));

        Wayland_ReleaseSHMPool(pool);
        ଫେରନ୍ତୁ wl_buffer;
    }
}

#endif

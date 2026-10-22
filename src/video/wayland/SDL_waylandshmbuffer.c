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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव <errno.h>
#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <limits.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <unistd.h>

#अन्तर्भाव "SDL_waylandshmbuffer.h"
#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "single-pixel-buffer-v1-client-protocol.h"

स्थिर bool SetTempFileSize(पूर्णांक fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    पूर्णांक ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    करा {
        ret = posix_fallocate(fd, 0, size);
    } पर्यंत (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, रिक्त);

    जर (ret == 0) {
        परत true;
    } अन्यथा जर (ret != EINVAL && त्रुटि_सं != EOPNOTSUPP) {
        परत false;
    }
#endif

    जर (ftruncate(fd, size) < 0) {
        परत false;
    }
    परत true;
}

स्थिर पूर्णांक CreateTempFD(off_t size)
{
    पूर्णांक fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    जर (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } अन्यथा
#endif
    {
        स्थिर स्थिरांक अक्षर ढाँचा[] = "/sdl-shared-XXXXXX";
        स्थिरांक अक्षर *xdg_path;
        अक्षर tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        जर (!xdg_path) {
            परत -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, ढाँचा, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        जर (fd < 0) {
            परत -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    जर (!SetTempFileSize(fd, size)) {
        बंद(fd);
        परत -1;
    }

    परत fd;
}

स्थिर शून्य buffer_handle_release(शून्य *data, संरचना wl_buffer *wl_buffer)
{
    // NOP
}

स्थिर संरचना wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

संरचना Wayland_SHMPool
{
    संरचना wl_shm_pool *shm_pool;
    शून्य *shm_pool_memory;
    पूर्णांक shm_pool_size;
    पूर्णांक offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(पूर्णांक size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    जर (size <= 0) {
        परत रिक्त;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, आकार(Wayland_SHMPool));
    जर (!shmPool) {
        परत रिक्त;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    स्थिरांक पूर्णांक shm_fd = CreateTempFD(shmPool->shm_pool_size);
    जर (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        परत रिक्त;
    }

    shmPool->shm_pool_memory = mmap(रिक्त, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    जर (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = रिक्त;
        बंद(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        परत रिक्त;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    बंद(shm_fd);

    परत shmPool;
}

संरचना wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, पूर्णांक width, पूर्णांक height, शून्य **data)
{
    स्थिरांक Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    जर (!shmPool || !width || !height || !data) {
        परत रिक्त;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    संरचना wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    परत buffer;
}

शून्य Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    जर (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

संरचना wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    जर (viddata->single_pixel_buffer_manager) {
        परत wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } अन्यथा {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        जर (!pool) {
            परत रिक्त;
        }

        शून्य *mem;
        संरचना wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        स्थिरांक Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, आकार(pixel));

        Wayland_ReleaseSHMPool(pool);
        परत wl_buffer;
    }
}

#endif

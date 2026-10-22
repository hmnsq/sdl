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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <sys/mman.h>
#অন্তর্ভাব <unistd.h>

#অন্তর্ভাব "SDL_waylandshmbuffer.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "single-pixel-buffer-v1-client-protocol.h"

স্থির bool SetTempFileSize(পূর্ণাঙ্ক fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    পূর্ণাঙ্ক ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    কুরু {
        ret = posix_fallocate(fd, 0, size);
    } যাবত্ (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, রিক্ত);

    যদি (ret == 0) {
        প্রত্যাগম true;
    } অন্যথা যদি (ret != EINVAL && errno != EOPNOTSUPP) {
        প্রত্যাগম false;
    }
#endif

    যদি (ftruncate(fd, size) < 0) {
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

স্থির পূর্ণাঙ্ক CreateTempFD(off_t size)
{
    পূর্ণাঙ্ক fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    যদি (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } অন্যথা
#endif
    {
        স্থির ধ্রুব বর্ণ template[] = "/sdl-shared-XXXXXX";
        ধ্রুব বর্ণ *xdg_path;
        বর্ণ tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        যদি (!xdg_path) {
            প্রত্যাগম -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        যদি (fd < 0) {
            প্রত্যাগম -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    যদি (!SetTempFileSize(fd, size)) {
        close(fd);
        প্রত্যাগম -1;
    }

    প্রত্যাগম fd;
}

স্থির শূন্য buffer_handle_release(শূন্য *data, সংরচনা wl_buffer *wl_buffer)
{
    // NOP
}

স্থির সংরচনা wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

সংরচনা Wayland_SHMPool
{
    সংরচনা wl_shm_pool *shm_pool;
    শূন্য *shm_pool_memory;
    পূর্ণাঙ্ক shm_pool_size;
    পূর্ণাঙ্ক offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(পূর্ণাঙ্ক size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    যদি (size <= 0) {
        প্রত্যাগম রিক্ত;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, পরিমাণ(Wayland_SHMPool));
    যদি (!shmPool) {
        প্রত্যাগম রিক্ত;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    ধ্রুব পূর্ণাঙ্ক shm_fd = CreateTempFD(shmPool->shm_pool_size);
    যদি (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        প্রত্যাগম রিক্ত;
    }

    shmPool->shm_pool_memory = mmap(রিক্ত, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    যদি (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = রিক্ত;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        প্রত্যাগম রিক্ত;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    প্রত্যাগম shmPool;
}

সংরচনা wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, শূন্য **data)
{
    ধ্রুব Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    যদি (!shmPool || !width || !height || !data) {
        প্রত্যাগম রিক্ত;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    সংরচনা wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    প্রত্যাগম buffer;
}

শূন্য Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    যদি (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

সংরচনা wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    যদি (viddata->single_pixel_buffer_manager) {
        প্রত্যাগম wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } অন্যথা {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        যদি (!pool) {
            প্রত্যাগম রিক্ত;
        }

        শূন্য *mem;
        সংরচনা wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        ধ্রুব Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, পরিমাণ(pixel));

        Wayland_ReleaseSHMPool(pool);
        প্রত্যাগম wl_buffer;
    }
}

#endif

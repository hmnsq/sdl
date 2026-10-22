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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <fcntl.h>
#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <signal.h>
#അന്തര്ഭാവ <sys/mman.h>
#അന്തര്ഭാവ <unistd.h>

#അന്തര്ഭാവ "SDL_waylandshmbuffer.h"
#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "single-pixel-buffer-v1-client-protocol.h"

സ്ഥിതം bool SetTempFileSize(പൂർണ്ണസംഖ്യ fd, off_t size)
{
#ifdef HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    പൂർണ്ണസംഖ്യ ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    ചെയ്യുക {
        ret = posix_fallocate(fd, 0, size);
    } ആകുമ്പോൾ (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, ശൂന്യ);

    എങ്കിൽ (ret == 0) {
        തിരികെ true;
    } അല്ലെങ്കിൽ എങ്കിൽ (ret != EINVAL && errno != EOPNOTSUPP) {
        തിരികെ false;
    }
#endif

    എങ്കിൽ (ftruncate(fd, size) < 0) {
        തിരികെ false;
    }
    തിരികെ true;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ CreateTempFD(off_t size)
{
    പൂർണ്ണസംഖ്യ fd;

#ifdef HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    എങ്കിൽ (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } അല്ലെങ്കിൽ
#endif
    {
        സ്ഥിതം സ്ഥിരം അക്ഷരം template[] = "/sdl-shared-XXXXXX";
        സ്ഥിരം അക്ഷരം *xdg_path;
        അക്ഷരം tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        എങ്കിൽ (!xdg_path) {
            തിരികെ -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, template, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        എങ്കിൽ (fd < 0) {
            തിരികെ -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    എങ്കിൽ (!SetTempFileSize(fd, size)) {
        close(fd);
        തിരികെ -1;
    }

    തിരികെ fd;
}

സ്ഥിതം ശൂന്യം buffer_handle_release(ശൂന്യം *data, ഘടന wl_buffer *wl_buffer)
{
    // NOP
}

സ്ഥിതം ഘടന wl_buffer_listener buffer_listener = {
    buffer_handle_release
};

ഘടന Wayland_SHMPool
{
    ഘടന wl_shm_pool *shm_pool;
    ശൂന്യം *shm_pool_memory;
    പൂർണ്ണസംഖ്യ shm_pool_size;
    പൂർണ്ണസംഖ്യ offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(പൂർണ്ണസംഖ്യ size)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    എങ്കിൽ (size <= 0) {
        തിരികെ ശൂന്യ;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, വലുപ്പം(Wayland_SHMPool));
    എങ്കിൽ (!shmPool) {
        തിരികെ ശൂന്യ;
    }

    shmPool->shm_pool_size = (size + 15) & (~15);

    സ്ഥിരം പൂർണ്ണസംഖ്യ shm_fd = CreateTempFD(shmPool->shm_pool_size);
    എങ്കിൽ (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        തിരികെ ശൂന്യ;
    }

    shmPool->shm_pool_memory = mmap(ശൂന്യ, shmPool->shm_pool_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    എങ്കിൽ (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = ശൂന്യ;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        തിരികെ ശൂന്യ;
    }

    shmPool->shm_pool = wl_shm_create_pool(data->shm, shm_fd, shmPool->shm_pool_size);
    close(shm_fd);

    തിരികെ shmPool;
}

ഘടന wl_buffer *Wayland_AllocBufferFromPool(Wayland_SHMPool *shmPool, പൂർണ്ണസംഖ്യ width, പൂർണ്ണസംഖ്യ height, ശൂന്യം **data)
{
    സ്ഥിരം Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    എങ്കിൽ (!shmPool || !width || !height || !data) {
        തിരികെ ശൂന്യ;
    }

    *data = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    ഘടന wl_buffer *buffer = wl_shm_pool_create_buffer(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_buffer_add_listener(buffer, &buffer_listener, shmPool);

    shmPool->offset += width * height * 4;

    തിരികെ buffer;
}

ശൂന്യം Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    എങ്കിൽ (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_size);
        SDL_free(shmPool);
    }
}

ഘടന wl_buffer *Wayland_CreateSinglePixelBuffer(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    എങ്കിൽ (viddata->single_pixel_buffer_manager) {
        തിരികെ wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(viddata->single_pixel_buffer_manager, r, g, b, a);
    } അല്ലെങ്കിൽ {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        എങ്കിൽ (!pool) {
            തിരികെ ശൂന്യ;
        }

        ശൂന്യം *mem;
        ഘടന wl_buffer *wl_buffer = Wayland_AllocBufferFromPool(pool, 1, 1, &mem);

        സ്ഥിരം Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, വലുപ്പം(pixel));

        Wayland_ReleaseSHMPool(pool);
        തിരികെ wl_buffer;
    }
}

#endif

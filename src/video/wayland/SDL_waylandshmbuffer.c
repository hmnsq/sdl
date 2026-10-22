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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandshmbuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "single-pixel-buffer-v1-client-protocol.h"

ਸਥਿਰ bool ਸੈੱਟ_ਆਰਜ਼ੀ_File_ਮਾਪ(ਪੂਰਨ fd, off_t ਮਾਪ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_POSIX_FALLOCATE
    sigset_t ਸੈੱਟ, old_ਸੈੱਟ;
    ਪੂਰਨ ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&ਸੈੱਟ);
    sigaddset(&ਸੈੱਟ, SIGALRM);
    sigprocmask(SIG_BLOCK, &ਸੈੱਟ, &old_ਸੈੱਟ);

    ਕਰੋ {
        ret = posix_fallocate(fd, 0, ਮਾਪ);
    } ਜਦੋਂ (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_ਸੈੱਟ, ਨਿਰਾ);

    ਜੇ (ret == 0) {
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ ਜੇ (ret != EINVAL && errno != EOPNOTSUPP) {
        ਵਾਪਸ false;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ftruncate(fd, ਮਾਪ) < 0) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ ਪੂਰਨ Create_ਆਰਜ਼ੀ_FD(off_t ਮਾਪ)
{
    ਪੂਰਨ fd;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    ਜੇ (fd >= 0) {
        fcntl(fd, F_ਜੋੜੋ_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        ਸਥਿਰ ਅਚਲ ਅੱਖਰ ਸਾਂਚਾ[] = "/sdl-shared-XXXXXX";
        ਅਚਲ ਅੱਖਰ *xdg_ਰਸਤਾ;
        ਅੱਖਰ tmp_ਰਸਤਾ[PATH_MAX];

        xdg_ਰਸਤਾ = SDL_getenv("XDG_RUNTIME_DIR");
        ਜੇ (!xdg_ਰਸਤਾ) {
            ਵਾਪਸ -1;
        }

        SDL_strlcpy(tmp_ਰਸਤਾ, xdg_ਰਸਤਾ, PATH_MAX);
        SDL_strlcat(tmp_ਰਸਤਾ, ਸਾਂਚਾ, PATH_MAX);

        fd = mkostemp(tmp_ਰਸਤਾ, O_CLOEXEC);
        ਜੇ (fd < 0) {
            ਵਾਪਸ -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_ਰਸਤਾ);
    }

    ਜੇ (!ਸੈੱਟ_ਆਰਜ਼ੀ_File_ਮਾਪ(fd, ਮਾਪ)) {
        close(fd);
        ਵਾਪਸ -1;
    }

    ਵਾਪਸ fd;
}

ਸਥਿਰ ਖਾਲੀ ਬਫਰ_handle_release(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਬਫਰ *wl_ਬਫਰ)
{
    // NOP
}

ਸਥਿਰ ਬਣਤਰ wl_ਬਫਰ_listener ਬਫਰ_listener = {
    ਬਫਰ_handle_release
};

ਬਣਤਰ Wayland_SHMPool
{
    ਬਣਤਰ wl_shm_pool *shm_pool;
    ਖਾਲੀ *shm_pool_ਸਮ੍ਰਿਤੀ;
    ਪੂਰਨ shm_pool_ਮਾਪ;
    ਪੂਰਨ ਵਿੱਥ_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(ਪੂਰਨ ਮਾਪ)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = vd->ਅੰਦਰੂਨੀ;

    ਜੇ (ਮਾਪ <= 0) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, ਆਕਾਰ(Wayland_SHMPool));
    ਜੇ (!shmPool) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    shmPool->shm_pool_ਮਾਪ = (ਮਾਪ + 15) & (~15);

    ਅਚਲ ਪੂਰਨ shm_fd = Create_ਆਰਜ਼ੀ_FD(shmPool->shm_pool_ਮਾਪ);
    ਜੇ (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_ਸੈੱਟ_Error("Creating SHM buffer failed.");
        ਵਾਪਸ ਨਿਰਾ;
    }

    shmPool->shm_pool_ਸਮ੍ਰਿਤੀ = mmap(ਨਿਰਾ, shmPool->shm_pool_ਮਾਪ, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ਜੇ (shmPool->shm_pool_ਸਮ੍ਰਿਤੀ == MAP_FAILED) {
        shmPool->shm_pool_ਸਮ੍ਰਿਤੀ = ਨਿਰਾ;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_ਸੈੱਟ_Error("mmap() failed.");
        ਵਾਪਸ ਨਿਰਾ;
    }

    shmPool->shm_pool = wl_shm_create_pool(ਅੰਕੜੇ->shm, shm_fd, shmPool->shm_pool_ਮਾਪ);
    close(shm_fd);

    ਵਾਪਸ shmPool;
}

ਬਣਤਰ wl_ਬਫਰ *Wayland_Alloc_ਬਫਰ_From_Pool(Wayland_SHMPool *shmPool, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਖਾਲੀ **ਅੰਕੜੇ)
{
    ਅਚਲ Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    ਜੇ (!shmPool || !ਚੌੜਾਈ || !ਉਚਾਈ || !ਅੰਕੜੇ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    *ਅੰਕੜੇ = (Uint8 *)shmPool->shm_pool_ਸਮ੍ਰਿਤੀ + shmPool->ਵਿੱਥ_2;
    ਬਣਤਰ wl_ਬਫਰ *ਬਫਰ_2 = wl_shm_pool_create_ਬਫਰ(shmPool->shm_pool, shmPool->ਵਿੱਥ_2, ਚੌੜਾਈ, ਉਚਾਈ, ਚੌੜਾਈ * 4, SHM_FMT);
    wl_ਬਫਰ_ਜੋੜੋ_listener(ਬਫਰ_2, &ਬਫਰ_listener, shmPool);

    shmPool->ਵਿੱਥ_2 += ਚੌੜਾਈ * ਉਚਾਈ * 4;

    ਵਾਪਸ ਬਫਰ_2;
}

ਖਾਲੀ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    ਜੇ (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_ਸਮ੍ਰਿਤੀ, shmPool->shm_pool_ਮਾਪ);
        SDL_free(shmPool);
    }
}

ਬਣਤਰ wl_ਬਫਰ *Wayland_Create_Single_Pixel_ਬਫਰ(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_ਅੰਕੜੇ *viddata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    ਜੇ (viddata->single_pixel_ਬਫਰ_manager) {
        ਵਾਪਸ wp_single_pixel_ਬਫਰ_manager_v1_create_u32_rgba_ਬਫਰ(viddata->single_pixel_ਬਫਰ_manager, r, g, b, a);
    } ਨਹੀਂਤਾਂ {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        ਜੇ (!pool) {
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਖਾਲੀ *mem;
        ਬਣਤਰ wl_ਬਫਰ *wl_ਬਫਰ = Wayland_Alloc_ਬਫਰ_From_Pool(pool, 1, 1, &mem);

        ਅਚਲ Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, ਆਕਾਰ(pixel));

        Wayland_ReleaseSHMPool(pool);
        ਵਾਪਸ wl_ਬਫਰ;
    }
}

#ਜੇ_ਅੰਤ

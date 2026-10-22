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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

#ಅನ್ತರ್ಭಾವ "SDL_waylandshmbuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "single-pixel-buffer-v1-client-protocol.h"

ಸ್ಥಿರ bool ಗಣ_ತಾತ್ಕಾಲಿಕ_File_ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ fd, off_t ಗಾತ್ರ_2)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_POSIX_FALLOCATE
    sigset_t ಗಣ, old_ಗಣ;
    ಪೂರ್ಣಾಂಕ ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&ಗಣ);
    sigaddset(&ಗಣ, SIGALRM);
    sigprocmask(SIG_BLOCK, &ಗಣ, &old_ಗಣ);

    ಮಾಡು {
        ret = posix_fallocate(fd, 0, ಗಾತ್ರ_2);
    } ಆಗ (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_ಗಣ, ಖಾಲಿ);

    ಆದರೆ (ret == 0) {
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret != EINVAL && errno != EOPNOTSUPP) {
        ಹಿಂತಿರುಗಿ false;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ftruncate(fd, ಗಾತ್ರ_2) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Create_ತಾತ್ಕಾಲಿಕ_FD(off_t ಗಾತ್ರ_2)
{
    ಪೂರ್ಣಾಂಕ fd;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    ಆದರೆ (fd >= 0) {
        fcntl(fd, F_ಕೂಡಿಸು_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಮಾದರಿ[] = "/sdl-shared-XXXXXX";
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *xdg_ಮಾರ್ಗ;
        ಅಕ್ಷರ tmp_ಮಾರ್ಗ[PATH_MAX];

        xdg_ಮಾರ್ಗ = SDL_getenv("XDG_RUNTIME_DIR");
        ಆದರೆ (!xdg_ಮಾರ್ಗ) {
            ಹಿಂತಿರುಗಿ -1;
        }

        SDL_strlcpy(tmp_ಮಾರ್ಗ, xdg_ಮಾರ್ಗ, PATH_MAX);
        SDL_strlcat(tmp_ಮಾರ್ಗ, ಮಾದರಿ, PATH_MAX);

        fd = mkostemp(tmp_ಮಾರ್ಗ, O_CLOEXEC);
        ಆದರೆ (fd < 0) {
            ಹಿಂತಿರುಗಿ -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_ಮಾರ್ಗ);
    }

    ಆದರೆ (!ಗಣ_ತಾತ್ಕಾಲಿಕ_File_ಗಾತ್ರ(fd, ಗಾತ್ರ_2)) {
        close(fd);
        ಹಿಂತಿರುಗಿ -1;
    }

    ಹಿಂತಿರುಗಿ fd;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಬಫರ್_handle_release(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ಬಫರ್ *wl_ಬಫರ್)
{
    // NOP
}

ಸ್ಥಿರ ರಚನೆ wl_ಬಫರ್_listener ಬಫರ್_listener = {
    ಬಫರ್_handle_release
};

ರಚನೆ Wayland_SHMPool
{
    ರಚನೆ wl_shm_pool *shm_pool;
    ಶೂನ್ಯ *shm_pool_ಸ್ಮರಣೆ;
    ಪೂರ್ಣಾಂಕ shm_pool_ಗಾತ್ರ;
    ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = vd->ಆಂತರಿಕ;

    ಆದರೆ (ಗಾತ್ರ_2 <= 0) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, ಗಾತ್ರ(Wayland_SHMPool));
    ಆದರೆ (!shmPool) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    shmPool->shm_pool_ಗಾತ್ರ = (ಗಾತ್ರ_2 + 15) & (~15);

    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ shm_fd = Create_ತಾತ್ಕಾಲಿಕ_FD(shmPool->shm_pool_ಗಾತ್ರ);
    ಆದರೆ (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_ಗಣ_Error("Creating SHM buffer failed.");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    shmPool->shm_pool_ಸ್ಮರಣೆ = mmap(ಖಾಲಿ, shmPool->shm_pool_ಗಾತ್ರ, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ಆದರೆ (shmPool->shm_pool_ಸ್ಮರಣೆ == MAP_FAILED) {
        shmPool->shm_pool_ಸ್ಮರಣೆ = ಖಾಲಿ;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_ಗಣ_Error("mmap() failed.");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    shmPool->shm_pool = wl_shm_create_pool(ದತ್ತಾಂಶ->shm, shm_fd, shmPool->shm_pool_ಗಾತ್ರ);
    close(shm_fd);

    ಹಿಂತಿರುಗಿ shmPool;
}

ರಚನೆ wl_ಬಫರ್ *Wayland_Alloc_ಬಫರ್_From_Pool(Wayland_SHMPool *shmPool, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಶೂನ್ಯ **ದತ್ತಾಂಶ)
{
    ಸ್ಥಿರಾಂಕ Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    ಆದರೆ (!shmPool || !ಅಗಲ || !ಎತ್ತರ || !ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    *ದತ್ತಾಂಶ = (Uint8 *)shmPool->shm_pool_ಸ್ಮರಣೆ + shmPool->ಸ್ಥಾನಾಂತರ_2;
    ರಚನೆ wl_ಬಫರ್ *ಬಫರ್_2 = wl_shm_pool_create_ಬಫರ್(shmPool->shm_pool, shmPool->ಸ್ಥಾನಾಂತರ_2, ಅಗಲ, ಎತ್ತರ, ಅಗಲ * 4, SHM_FMT);
    wl_ಬಫರ್_ಕೂಡಿಸು_listener(ಬಫರ್_2, &ಬಫರ್_listener, shmPool);

    shmPool->ಸ್ಥಾನಾಂತರ_2 += ಅಗಲ * ಎತ್ತರ * 4;

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

ಶೂನ್ಯ Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    ಆದರೆ (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_ಸ್ಮರಣೆ, shmPool->shm_pool_ಗಾತ್ರ);
        SDL_free(shmPool);
    }
}

ರಚನೆ wl_ಬಫರ್ *Wayland_Create_Single_Pixel_ಬಫರ್(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = SDL_GetVideoDevice()->ಆಂತರಿಕ;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    ಆದರೆ (viddata->single_pixel_ಬಫರ್_manager) {
        ಹಿಂತಿರುಗಿ wp_single_pixel_ಬಫರ್_manager_v1_create_u32_rgba_ಬಫರ್(viddata->single_pixel_ಬಫರ್_manager, r, g, b, a);
    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        ಆದರೆ (!pool) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಶೂನ್ಯ *mem;
        ರಚನೆ wl_ಬಫರ್ *wl_ಬಫರ್ = Wayland_Alloc_ಬಫರ್_From_Pool(pool, 1, 1, &mem);

        ಸ್ಥಿರಾಂಕ Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, ಗಾತ್ರ(pixel));

        Wayland_ReleaseSHMPool(pool);
        ಹಿಂತಿರುಗಿ wl_ಬಫರ್;
    }
}

#ಆದರೆ_ಅಂತ್ಯ

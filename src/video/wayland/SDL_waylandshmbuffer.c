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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل <errno.h>
#شامل <fcntl.h>
#شامل <limits.h>
#شامل <signal.h>
#شامل <sys/mman.h>
#شامل <unistd.h>

#شامل "SDL_waylandshmbuffer.h"
#شامل "SDL_waylandvideo.h"
#شامل "single-pixel-buffer-v1-client-protocol.h"

ساکن bool سیٹ_عارضی_File_سائز(صحیح fd, off_t سائز)
{
#اگر_تعریف_شدہ HAVE_POSIX_FALLOCATE
    sigset_t سیٹ, old_سیٹ;
    صحیح ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&سیٹ);
    sigaddset(&سیٹ, SIGALRM);
    sigprocmask(SIG_BLOCK, &سیٹ, &old_سیٹ);

    کرو {
        ret = posix_fallocate(fd, 0, سائز);
    } جب (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_سیٹ, تہی);

    اگر (ret == 0) {
        واپس true;
    } ورنہ اگر (ret != EINVAL && errno != EOPNOTSUPP) {
        واپس false;
    }
#اگر_ختم

    اگر (ftruncate(fd, سائز) < 0) {
        واپس false;
    }
    واپس true;
}

ساکن صحیح Create_عارضی_FD(off_t سائز)
{
    صحیح fd;

#اگر_تعریف_شدہ HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    اگر (fd >= 0) {
        fcntl(fd, F_جوڑو_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } ورنہ
#اگر_ختم
    {
        ساکن ثابت حرف سانچہ[] = "/sdl-shared-XXXXXX";
        ثابت حرف *xdg_راستہ;
        حرف tmp_راستہ[PATH_MAX];

        xdg_راستہ = SDL_getenv("XDG_RUNTIME_DIR");
        اگر (!xdg_راستہ) {
            واپس -1;
        }

        SDL_strlcpy(tmp_راستہ, xdg_راستہ, PATH_MAX);
        SDL_strlcat(tmp_راستہ, سانچہ, PATH_MAX);

        fd = mkostemp(tmp_راستہ, O_CLOEXEC);
        اگر (fd < 0) {
            واپس -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_راستہ);
    }

    اگر (!سیٹ_عارضی_File_سائز(fd, سائز)) {
        close(fd);
        واپس -1;
    }

    واپس fd;
}

ساکن خالی بفر_handle_release(خالی *ڈیٹا, ساخت wl_بفر *wl_بفر)
{
    // NOP
}

ساکن ساخت wl_بفر_listener بفر_listener = {
    بفر_handle_release
};

ساخت Wayland_SHMPool
{
    ساخت wl_shm_pool *shm_pool;
    خالی *shm_pool_حافظہ;
    صحیح shm_pool_سائز;
    صحیح انحراف_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(صحیح سائز)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *ڈیٹا = vd->اندرونی_2;

    اگر (سائز <= 0) {
        واپس تہی;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, حجم(Wayland_SHMPool));
    اگر (!shmPool) {
        واپس تہی;
    }

    shmPool->shm_pool_سائز = (سائز + 15) & (~15);

    ثابت صحیح shm_fd = Create_عارضی_FD(shmPool->shm_pool_سائز);
    اگر (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_سیٹ_Error("Creating SHM buffer failed.");
        واپس تہی;
    }

    shmPool->shm_pool_حافظہ = mmap(تہی, shmPool->shm_pool_سائز, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    اگر (shmPool->shm_pool_حافظہ == MAP_FAILED) {
        shmPool->shm_pool_حافظہ = تہی;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_سیٹ_Error("mmap() failed.");
        واپس تہی;
    }

    shmPool->shm_pool = wl_shm_create_pool(ڈیٹا->shm, shm_fd, shmPool->shm_pool_سائز);
    close(shm_fd);

    واپس shmPool;
}

ساخت wl_بفر *Wayland_Alloc_بفر_From_Pool(Wayland_SHMPool *shmPool, صحیح چوڑائی, صحیح اونچائی, خالی **ڈیٹا)
{
    ثابت Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    اگر (!shmPool || !چوڑائی || !اونچائی || !ڈیٹا) {
        واپس تہی;
    }

    *ڈیٹا = (Uint8 *)shmPool->shm_pool_حافظہ + shmPool->انحراف_2;
    ساخت wl_بفر *بفر_2 = wl_shm_pool_create_بفر(shmPool->shm_pool, shmPool->انحراف_2, چوڑائی, اونچائی, چوڑائی * 4, SHM_FMT);
    wl_بفر_جوڑو_listener(بفر_2, &بفر_listener, shmPool);

    shmPool->انحراف_2 += چوڑائی * اونچائی * 4;

    واپس بفر_2;
}

خالی Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    اگر (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_حافظہ, shmPool->shm_pool_سائز);
        SDL_free(shmPool);
    }
}

ساخت wl_بفر *Wayland_Create_Single_Pixel_بفر(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_ڈیٹا *viddata = SDL_GetVideoDevice()->اندرونی_2;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    اگر (viddata->single_pixel_بفر_manager) {
        واپس wp_single_pixel_بفر_manager_v1_create_u32_rgba_بفر(viddata->single_pixel_بفر_manager, r, g, b, a);
    } ورنہ {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        اگر (!pool) {
            واپس تہی;
        }

        خالی *mem;
        ساخت wl_بفر *wl_بفر = Wayland_Alloc_بفر_From_Pool(pool, 1, 1, &mem);

        ثابت Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, حجم(pixel));

        Wayland_ReleaseSHMPool(pool);
        واپس wl_بفر;
    }
}

#اگر_ختم

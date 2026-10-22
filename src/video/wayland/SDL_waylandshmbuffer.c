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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ <errno.h>
#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <signal.h>
#అన్తర్భావ <sys/mman.h>
#అన్తర్భావ <unistd.h>

#అన్తర్భావ "SDL_waylandshmbuffer.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "single-pixel-buffer-v1-client-protocol.h"

స్థిర bool సమితి_తాత్కాలిక_File_కొలత(పూర్ణాంకం fd, off_t కొలత)
{
#నిర్వచితమైతే HAVE_POSIX_FALLOCATE
    sigset_t సమితి, old_సమితి;
    పూర్ణాంకం ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&సమితి);
    sigaddset(&సమితి, SIGALRM);
    sigprocmask(SIG_BLOCK, &సమితి, &old_సమితి);

    చేయి {
        ret = posix_fallocate(fd, 0, కొలత);
    } అయితే (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_సమితి, ఖాళీ);

    ఒకవేళ (ret == 0) {
        తిరిగి true;
    } లేకపోతే ఒకవేళ (ret != EINVAL && errno != EOPNOTSUPP) {
        తిరిగి false;
    }
#అయితే_ముగింపు

    ఒకవేళ (ftruncate(fd, కొలత) < 0) {
        తిరిగి false;
    }
    తిరిగి true;
}

స్థిర పూర్ణాంకం Create_తాత్కాలిక_FD(off_t కొలత)
{
    పూర్ణాంకం fd;

#నిర్వచితమైతే HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    ఒకవేళ (fd >= 0) {
        fcntl(fd, F_కూడు_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } లేకపోతే
#అయితే_ముగింపు
    {
        స్థిర స్థిరరాశి అక్షరం మూస[] = "/sdl-shared-XXXXXX";
        స్థిరరాశి అక్షరం *xdg_మార్గం;
        అక్షరం tmp_మార్గం[PATH_MAX];

        xdg_మార్గం = SDL_getenv("XDG_RUNTIME_DIR");
        ఒకవేళ (!xdg_మార్గం) {
            తిరిగి -1;
        }

        SDL_strlcpy(tmp_మార్గం, xdg_మార్గం, PATH_MAX);
        SDL_strlcat(tmp_మార్గం, మూస, PATH_MAX);

        fd = mkostemp(tmp_మార్గం, O_CLOEXEC);
        ఒకవేళ (fd < 0) {
            తిరిగి -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_మార్గం);
    }

    ఒకవేళ (!సమితి_తాత్కాలిక_File_కొలత(fd, కొలత)) {
        close(fd);
        తిరిగి -1;
    }

    తిరిగి fd;
}

స్థిర శూన్య బఫరు_handle_release(శూన్య *దత్తాంశం, నిర్మాణం wl_బఫరు *wl_బఫరు)
{
    // NOP
}

స్థిర నిర్మాణం wl_బఫరు_listener బఫరు_listener = {
    బఫరు_handle_release
};

నిర్మాణం Wayland_SHMPool
{
    నిర్మాణం wl_shm_pool *shm_pool;
    శూన్య *shm_pool_జ్ఞాపకం;
    పూర్ణాంకం shm_pool_కొలత;
    పూర్ణాంకం స్థానభ్రంశం_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(పూర్ణాంకం కొలత)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *దత్తాంశం = vd->అంతర్గత;

    ఒకవేళ (కొలత <= 0) {
        తిరిగి ఖాళీ;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, పరిమాణం(Wayland_SHMPool));
    ఒకవేళ (!shmPool) {
        తిరిగి ఖాళీ;
    }

    shmPool->shm_pool_కొలత = (కొలత + 15) & (~15);

    స్థిరరాశి పూర్ణాంకం shm_fd = Create_తాత్కాలిక_FD(shmPool->shm_pool_కొలత);
    ఒకవేళ (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_సమితి_Error("Creating SHM buffer failed.");
        తిరిగి ఖాళీ;
    }

    shmPool->shm_pool_జ్ఞాపకం = mmap(ఖాళీ, shmPool->shm_pool_కొలత, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    ఒకవేళ (shmPool->shm_pool_జ్ఞాపకం == MAP_FAILED) {
        shmPool->shm_pool_జ్ఞాపకం = ఖాళీ;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_సమితి_Error("mmap() failed.");
        తిరిగి ఖాళీ;
    }

    shmPool->shm_pool = wl_shm_create_pool(దత్తాంశం->shm, shm_fd, shmPool->shm_pool_కొలత);
    close(shm_fd);

    తిరిగి shmPool;
}

నిర్మాణం wl_బఫరు *Wayland_Alloc_బఫరు_From_Pool(Wayland_SHMPool *shmPool, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, శూన్య **దత్తాంశం)
{
    స్థిరరాశి Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    ఒకవేళ (!shmPool || !వెడల్పు || !ఎత్తు || !దత్తాంశం) {
        తిరిగి ఖాళీ;
    }

    *దత్తాంశం = (Uint8 *)shmPool->shm_pool_జ్ఞాపకం + shmPool->స్థానభ్రంశం_2;
    నిర్మాణం wl_బఫరు *బఫరు_2 = wl_shm_pool_create_బఫరు(shmPool->shm_pool, shmPool->స్థానభ్రంశం_2, వెడల్పు, ఎత్తు, వెడల్పు * 4, SHM_FMT);
    wl_బఫరు_కూడు_listener(బఫరు_2, &బఫరు_listener, shmPool);

    shmPool->స్థానభ్రంశం_2 += వెడల్పు * ఎత్తు * 4;

    తిరిగి బఫరు_2;
}

శూన్య Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    ఒకవేళ (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_జ్ఞాపకం, shmPool->shm_pool_కొలత);
        SDL_free(shmPool);
    }
}

నిర్మాణం wl_బఫరు *Wayland_Create_Single_Pixel_బఫరు(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_దత్తాంశం *viddata = SDL_GetVideoDevice()->అంతర్గత;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    ఒకవేళ (viddata->single_pixel_బఫరు_manager) {
        తిరిగి wp_single_pixel_బఫరు_manager_v1_create_u32_rgba_బఫరు(viddata->single_pixel_బఫరు_manager, r, g, b, a);
    } లేకపోతే {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        ఒకవేళ (!pool) {
            తిరిగి ఖాళీ;
        }

        శూన్య *mem;
        నిర్మాణం wl_బఫరు *wl_బఫరు = Wayland_Alloc_బఫరు_From_Pool(pool, 1, 1, &mem);

        స్థిరరాశి Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, పరిమాణం(pixel));

        Wayland_ReleaseSHMPool(pool);
        తిరిగి wl_బఫరు;
    }
}

#అయితే_ముగింపు

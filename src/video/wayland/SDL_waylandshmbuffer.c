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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव <errno.h>
#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <limits.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <unistd.h>

#अन्तर्भाव "SDL_waylandshmbuffer.h"
#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "single-pixel-buffer-v1-client-protocol.h"

स्थिर bool समुच्चयः_अस्थायी_File_आकार(पूर्णाङ्क fd, off_t आकार)
{
#यदि_परिभाषितम् HAVE_POSIX_FALLOCATE
    sigset_t समुच्चयः, old_समुच्चयः;
    पूर्णाङ्क ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&समुच्चयः);
    sigaddset(&समुच्चयः, SIGALRM);
    sigprocmask(SIG_BLOCK, &समुच्चयः, &old_समुच्चयः);

    कुरु {
        ret = posix_fallocate(fd, 0, आकार);
    } यावत् (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_समुच्चयः, रिक्त);

    यदि (ret == 0) {
        प्रत्यागम true;
    } अन्यथा यदि (ret != EINVAL && errno != EOPNOTSUPP) {
        प्रत्यागम false;
    }
#यदि_अन्तः

    यदि (ftruncate(fd, आकार) < 0) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

स्थिर पूर्णाङ्क Create_अस्थायी_FD(off_t आकार)
{
    पूर्णाङ्क fd;

#यदि_परिभाषितम् HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    यदि (fd >= 0) {
        fcntl(fd, F_सङ्कलय_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } अन्यथा
#यदि_अन्तः
    {
        स्थिर ध्रुव वर्ण प्रतिरूपम्[] = "/sdl-shared-XXXXXX";
        ध्रुव वर्ण *xdg_मार्गः;
        वर्ण tmp_मार्गः[PATH_MAX];

        xdg_मार्गः = SDL_getenv("XDG_RUNTIME_DIR");
        यदि (!xdg_मार्गः) {
            प्रत्यागम -1;
        }

        SDL_strlcpy(tmp_मार्गः, xdg_मार्गः, PATH_MAX);
        SDL_strlcat(tmp_मार्गः, प्रतिरूपम्, PATH_MAX);

        fd = mkostemp(tmp_मार्गः, O_CLOEXEC);
        यदि (fd < 0) {
            प्रत्यागम -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_मार्गः);
    }

    यदि (!समुच्चयः_अस्थायी_File_आकार(fd, आकार)) {
        close(fd);
        प्रत्यागम -1;
    }

    प्रत्यागम fd;
}

स्थिर शून्य बफर_handle_release(शून्य *दत्त, संरचना wl_बफर *wl_बफर)
{
    // NOP
}

स्थिर संरचना wl_बफर_listener बफर_listener = {
    बफर_handle_release
};

संरचना Wayland_SHMPool
{
    संरचना wl_shm_pool *shm_pool;
    शून्य *shm_pool_स्मृतिः;
    पूर्णाङ्क shm_pool_आकार;
    पूर्णाङ्क विस्थापनम्_2;
};

Wayland_SHMPool *Wayland_AllocSHMPool(पूर्णाङ्क आकार)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_दत्त *दत्त = vd->आन्तरिकम्;

    यदि (आकार <= 0) {
        प्रत्यागम रिक्त;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, परिमाण(Wayland_SHMPool));
    यदि (!shmPool) {
        प्रत्यागम रिक्त;
    }

    shmPool->shm_pool_आकार = (आकार + 15) & (~15);

    ध्रुव पूर्णाङ्क shm_fd = Create_अस्थायी_FD(shmPool->shm_pool_आकार);
    यदि (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_समुच्चयः_Error("Creating SHM buffer failed.");
        प्रत्यागम रिक्त;
    }

    shmPool->shm_pool_स्मृतिः = mmap(रिक्त, shmPool->shm_pool_आकार, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    यदि (shmPool->shm_pool_स्मृतिः == MAP_FAILED) {
        shmPool->shm_pool_स्मृतिः = रिक्त;
        close(shm_fd);
        SDL_free(shmPool);
        SDL_समुच्चयः_Error("mmap() failed.");
        प्रत्यागम रिक्त;
    }

    shmPool->shm_pool = wl_shm_create_pool(दत्त->shm, shm_fd, shmPool->shm_pool_आकार);
    close(shm_fd);

    प्रत्यागम shmPool;
}

संरचना wl_बफर *Wayland_Alloc_बफर_From_Pool(Wayland_SHMPool *shmPool, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, शून्य **दत्त)
{
    ध्रुव Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    यदि (!shmPool || !विस्तारः || !height || !दत्त) {
        प्रत्यागम रिक्त;
    }

    *दत्त = (Uint8 *)shmPool->shm_pool_स्मृतिः + shmPool->विस्थापनम्_2;
    संरचना wl_बफर *बफर_2 = wl_shm_pool_create_बफर(shmPool->shm_pool, shmPool->विस्थापनम्_2, विस्तारः, height, विस्तारः * 4, SHM_FMT);
    wl_बफर_सङ्कलय_listener(बफर_2, &बफर_listener, shmPool);

    shmPool->विस्थापनम्_2 += विस्तारः * height * 4;

    प्रत्यागम बफर_2;
}

शून्य Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    यदि (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_स्मृतिः, shmPool->shm_pool_आकार);
        SDL_free(shmPool);
    }
}

संरचना wl_बफर *Wayland_Create_Single_Pixel_बफर(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_दत्त *viddata = SDL_GetVideoDevice()->आन्तरिकम्;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    यदि (viddata->single_pixel_बफर_manager) {
        प्रत्यागम wp_single_pixel_बफर_manager_v1_create_u32_rgba_बफर(viddata->single_pixel_बफर_manager, r, g, b, a);
    } अन्यथा {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        यदि (!pool) {
            प्रत्यागम रिक्त;
        }

        शून्य *mem;
        संरचना wl_बफर *wl_बफर = Wayland_Alloc_बफर_From_Pool(pool, 1, 1, &mem);

        ध्रुव Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, परिमाण(pixel));

        Wayland_ReleaseSHMPool(pool);
        प्रत्यागम wl_बफर;
    }
}

#यदि_अन्तः

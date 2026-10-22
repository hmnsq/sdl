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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश <errno.h>
#समावेश <fcntl.h>
#समावेश <limits.h>
#समावेश <signal.h>
#समावेश <sys/mman.h>
#समावेश <unistd.h>

#समावेश "SDL_waylandshmbuffer.h"
#समावेश "SDL_waylandvideo.h"
#समावेश "single-pixel-buffer-v1-client-protocol.h"

अटल bool Set_अस्थायी_File_आकार(पूर्णांक fd, off_t आकार)
{
#अगर_घोषित HAVE_POSIX_FALLOCATE
    sigset_t set, old_set;
    पूर्णांक ret;

    /* SIGALRM can potentially block a large posix_fallocate() operation
     * from succeeding, so block it.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &old_set);

    करो {
        ret = posix_fallocate(fd, 0, आकार);
    } जबतक (ret == EINTR);

    sigprocmask(SIG_SETMASK, &old_set, शून्य);

    अगर (ret == 0) {
        वापस true;
    } अन्यथा अगर (ret != EINVAL && त्रुटि_सं != EOPNOTSUPP) {
        वापस false;
    }
#पूर्ण_अगर

    अगर (ftruncate(fd, आकार) < 0) {
        वापस false;
    }
    वापस true;
}

अटल पूर्णांक Create_अस्थायी_FD(off_t आकार)
{
    पूर्णांक fd;

#अगर_घोषित HAVE_MEMFD_CREATE
    fd = memfd_create("SDL", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    अगर (fd >= 0) {
        fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
    } अन्यथा
#पूर्ण_अगर
    {
        अटल स्थिर अक्षर ढाँचा[] = "/sdl-shared-XXXXXX";
        स्थिर अक्षर *xdg_path;
        अक्षर tmp_path[PATH_MAX];

        xdg_path = SDL_getenv("XDG_RUNTIME_DIR");
        अगर (!xdg_path) {
            वापस -1;
        }

        SDL_strlcpy(tmp_path, xdg_path, PATH_MAX);
        SDL_strlcat(tmp_path, ढाँचा, PATH_MAX);

        fd = mkostemp(tmp_path, O_CLOEXEC);
        अगर (fd < 0) {
            वापस -1;
        }

        // Need to manually unlink the temp files, or they can persist after close and fill up the temp storage.
        unlink(tmp_path);
    }

    अगर (!Set_अस्थायी_File_आकार(fd, आकार)) {
        बंद(fd);
        वापस -1;
    }

    वापस fd;
}

अटल व्योम बफर_handle_release(व्योम *तथ्य, काष्ठा wl_बफर *wl_बफर)
{
    // NOP
}

अटल काष्ठा wl_बफर_listener बफर_listener = {
    बफर_handle_release
};

काष्ठा Wayland_SHMPool
{
    काष्ठा wl_shm_pool *shm_pool;
    व्योम *shm_pool_memory;
    पूर्णांक shm_pool_आकार;
    पूर्णांक offset;
};

Wayland_SHMPool *Wayland_AllocSHMPool(पूर्णांक आकार)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *तथ्य = vd->internal;

    अगर (आकार <= 0) {
        वापस शून्य;
    }

    Wayland_SHMPool *shmPool = SDL_calloc(1, माप(Wayland_SHMPool));
    अगर (!shmPool) {
        वापस शून्य;
    }

    shmPool->shm_pool_आकार = (आकार + 15) & (~15);

    स्थिर पूर्णांक shm_fd = Create_अस्थायी_FD(shmPool->shm_pool_आकार);
    अगर (shm_fd < 0) {
        SDL_free(shmPool);
        SDL_SetError("Creating SHM buffer failed.");
        वापस शून्य;
    }

    shmPool->shm_pool_memory = mmap(शून्य, shmPool->shm_pool_आकार, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    अगर (shmPool->shm_pool_memory == MAP_FAILED) {
        shmPool->shm_pool_memory = शून्य;
        बंद(shm_fd);
        SDL_free(shmPool);
        SDL_SetError("mmap() failed.");
        वापस शून्य;
    }

    shmPool->shm_pool = wl_shm_create_pool(तथ्य->shm, shm_fd, shmPool->shm_pool_आकार);
    बंद(shm_fd);

    वापस shmPool;
}

काष्ठा wl_बफर *Wayland_Alloc_बफर_From_Pool(Wayland_SHMPool *shmPool, पूर्णांक width, पूर्णांक height, व्योम **तथ्य)
{
    स्थिर Uint32 SHM_FMT = WL_SHM_FORMAT_ARGB8888;

    अगर (!shmPool || !width || !height || !तथ्य) {
        वापस शून्य;
    }

    *तथ्य = (Uint8 *)shmPool->shm_pool_memory + shmPool->offset;
    काष्ठा wl_बफर *बफर_2 = wl_shm_pool_create_बफर(shmPool->shm_pool, shmPool->offset, width, height, width * 4, SHM_FMT);
    wl_बफर_add_listener(बफर_2, &बफर_listener, shmPool);

    shmPool->offset += width * height * 4;

    वापस बफर_2;
}

व्योम Wayland_ReleaseSHMPool(Wayland_SHMPool *shmPool)
{
    अगर (shmPool) {
        wl_shm_pool_destroy(shmPool->shm_pool);
        munmap(shmPool->shm_pool_memory, shmPool->shm_pool_आकार);
        SDL_free(shmPool);
    }
}

काष्ठा wl_बफर *Wayland_Create_Single_Pixel_बफर(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    SDL_Video_तथ्य *viddata = SDL_GetVideoDevice()->internal;

    // The single-pixel buffer protocol is preferred, as the compositor can choose an optimal format.
    अगर (viddata->single_pixel_बफर_manager) {
        वापस wp_single_pixel_बफर_manager_v1_create_u32_rgba_बफर(viddata->single_pixel_बफर_manager, r, g, b, a);
    } अन्यथा {
        Wayland_SHMPool *pool = Wayland_AllocSHMPool(4);
        अगर (!pool) {
            वापस शून्य;
        }

        व्योम *mem;
        काष्ठा wl_बफर *wl_बफर = Wayland_Alloc_बफर_From_Pool(pool, 1, 1, &mem);

        स्थिर Uint8 pixel[4] = { r >> 24, g >> 24, b >> 24, a >> 24 };
        SDL_memcpy(mem, pixel, माप(pixel));

        Wayland_ReleaseSHMPool(pool);
        वापस wl_बफर;
    }
}

#पूर्ण_अगर

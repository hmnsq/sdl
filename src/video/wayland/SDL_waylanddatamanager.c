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

#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <signal.h>

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_clipboard_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylanddatamanager.h"
#ಅನ್ತರ್ಭಾವ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_PIPE_TIMEOUT_NS SDL_MS_ಗಮ್ಯ_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HAVE_SIGTIMEDWAIT
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <time.h>
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ sigtimedwait(ಸ್ಥಿರಾಂಕ sigset_t *ಗಣ, siginfo_t *info, ಸ್ಥಿರಾಂಕ ರಚನೆ timespec *timeout)
{
    ರಚನೆ timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    ಮಾಡು {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ signo = 1; signo < NSIG; ++signo) {
            ಆದರೆ (sigismember(ಗಣ, signo) && sigismember(&pending, signo)) {
                ಆದರೆ (!sigwait(ಗಣ, &signo)) {
                    ಆದರೆ (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    ಹಿಂತಿರುಗಿ signo;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಹಿಂತಿರುಗಿ -1;
                }
            }
        }

        ಆದರೆ (timeout->tv_sec || timeout->tv_nsec) {
            ದೀರ್ಘ ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ರಚನೆ timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } ಆಗ (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    ಹಿಂತಿರುಗಿ -1;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ssize_t WritePipe(ಪೂರ್ಣಾಂಕ fd, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2, size_t ಒಟ್ಟು_ಉದ್ದಳತೆ, size_t *pos)
{
    ssize_t ಬೈಟುಗಳು_written = 0;
    ಸ್ಥಿರಾಂಕ ssize_t ಉದ್ದಳತೆ = ಒಟ್ಟು_ಉದ್ದಳತೆ - *pos;

    sigset_t sig_ಗಣ;
    sigset_t old_sig_ಗಣ;
    ರಚನೆ timespec zerotime = { 0 };

    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_ಗಣ);
    sigaddset(&sig_ಗಣ, SIGPIPE);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಎಳೆಗಳು_DISABLED
    sigprocmask(SIG_BLOCK, &sig_ಗಣ, &old_sig_ಗಣ);
#ಇಲ್ಲದಿದ್ದರೆ
    pthread_sigmask(SIG_BLOCK, &sig_ಗಣ, &old_sig_ಗಣ);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ready > 0) {
        ಆದರೆ (ಉದ್ದಳತೆ > 0) {
            ಬೈಟುಗಳು_written = ಲಿಖ(fd, (Uint8 *)ಬಫರ್_2 + *pos, SDL_min(ಉದ್ದಳತೆ, PIPE_BUF));
        }

        ಆದರೆ (ಬೈಟುಗಳು_written > 0) {
            *pos += ಬೈಟುಗಳು_written;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ready == 0) {
        SDL_ಗಣ_Error("Pipe timeout");
    } ಇಲ್ಲದಿದ್ದರೆ  {
        SDL_ಗಣ_Error("Pipe poll error");
    }

    sigtimedwait(&sig_ಗಣ, ಖಾಲಿ, &zerotime);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಎಳೆಗಳು_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_ಗಣ, ಖಾಲಿ);
#ಇಲ್ಲದಿದ್ದರೆ
    pthread_sigmask(SIG_SETMASK, &old_sig_ಗಣ, ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ಬೈಟುಗಳು_written;
}

ಸ್ಥಿರ ssize_t ReadPipe(ಪೂರ್ಣಾಂಕ fd, ಶೂನ್ಯ **ಬಫರ್_2, size_t *ಒಟ್ಟು_ಉದ್ದಳತೆ, Sint64 timeout_ns)
{
    ಶೂನ್ಯ *output_ಬಫರ್ = ಖಾಲಿ;
    ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ[PIPE_BUF];
    ssize_t ಬೈಟುಗಳು_read = 0;

    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    ಆದರೆ (ready > 0) {
        ಬೈಟುಗಳು_read = ಪಠ(fd, ತಾತ್ಕಾಲಿಕ, ಗಾತ್ರ(ತಾತ್ಕಾಲಿಕ));
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ready == 0) {
        SDL_ಗಣ_Error("Pipe timeout");
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Pipe poll error");
    }

    ಆದರೆ (ಬೈಟುಗಳು_read > 0) {
        ಸ್ಥಿರಾಂಕ size_t pos = *ಒಟ್ಟು_ಉದ್ದಳತೆ;
        *ಒಟ್ಟು_ಉದ್ದಳತೆ += ಬೈಟುಗಳು_read;

        ಸ್ಥಿರಾಂಕ size_t new_ಬಫರ್_ಉದ್ದಳತೆ = *ಒಟ್ಟು_ಉದ್ದಳತೆ + ಗಾತ್ರ(Uint32);

        ಆದರೆ (!*ಬಫರ್_2) {
            output_ಬಫರ್ = SDL_malloc(new_ಬಫರ್_ಉದ್ದಳತೆ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            output_ಬಫರ್ = SDL_realloc(*ಬಫರ್_2, new_ಬಫರ್_ಉದ್ದಳತೆ);
        }

        ಆದರೆ (!output_ಬಫರ್) {
            ಬೈಟುಗಳು_read = -1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_memcpy((Uint8 *)output_ಬಫರ್ + pos, ತಾತ್ಕಾಲಿಕ, ಬೈಟುಗಳು_read);
            SDL_memset((Uint8 *)output_ಬಫರ್ + (new_ಬಫರ್_ಉದ್ದಳತೆ - ಗಾತ್ರ(Uint32)), 0, ಗಾತ್ರ(Uint32));

            *ಬಫರ್_2 = output_ಬಫರ್;
        }
    }

    ಹಿಂತಿರುಗಿ ಬೈಟುಗಳು_read;
}

ಸ್ಥಿರ bool MIMEDataListHasType(ರಚನೆ wl_array *list, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **ಅಂಶ;
    wl_array_for_each(ಅಂಶ, list) {
        ಆದರೆ (SDL_strcmp(*ಅಂಶ, mime_type) == 0) {
            ಹಿಂತಿರುಗಿ true;
        }
    }

    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool MIMEData_List_ಕೂಡಿಸು(ರಚನೆ wl_array *list, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಆದರೆ (!MIMEDataListHasType(list, mime_type)) {
        ಅಕ್ಷರ **ಅಂಶ = WAYLAND_wl_array_ಕೂಡಿಸು(list, ಗಾತ್ರ(ಅಕ್ಷರ *));
        *ಅಂಶ = SDL_strdup(mime_type);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ MIMEDataListFree(ರಚನೆ wl_array *list)
{
    ಅಕ್ಷರ **ಅಂಶ;
    wl_array_for_each(ಅಂಶ, list) {
        SDL_free(*ಅಂಶ);
    }

    WAYLAND_wl_array_release(list);
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_ಮೂಲ_handle_ಗುರಿ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *wl_ದತ್ತಾಂಶ_ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_ಮೂಲ_handle_send(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *wl_ದತ್ತಾಂಶ_ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, int32_t fd)
{
    Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Send((SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *)ದತ್ತಾಂಶ, mime_type, fd);
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_ಮೂಲ_handle_cancelled(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *wl_ದತ್ತಾಂಶ_ಮೂಲ)
{
    SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ = ದತ್ತಾಂಶ;
    ಆದರೆ (ಮೂಲ) {
        Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(ಮೂಲ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_ಮೂಲ_handle_dnd_drop_performed(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *wl_ದತ್ತಾಂಶ_ಮೂಲ)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_ಮೂಲ_handle_dnd_ಪೂರ್ಣಗೊಂಡ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *wl_ದತ್ತಾಂಶ_ಮೂಲ)
{
    SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ = ದತ್ತಾಂಶ;
    ಆದರೆ (ಮೂಲ) {
        Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(ಮೂಲ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ದತ್ತಾಂಶ_ಮೂಲ_handle_action(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *wl_ದತ್ತಾಂಶ_ಮೂಲ, uint32_t dnd_action)
{
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ_listener ದತ್ತಾಂಶ_ಮೂಲ_listener = {
    ದತ್ತಾಂಶ_ಮೂಲ_handle_ಗುರಿ,
    ದತ್ತಾಂಶ_ಮೂಲ_handle_send,
    ದತ್ತಾಂಶ_ಮೂಲ_handle_cancelled,
    ದತ್ತಾಂಶ_ಮೂಲ_handle_dnd_drop_performed, // Version 3
    ದತ್ತಾಂಶ_ಮೂಲ_handle_dnd_ಪೂರ್ಣಗೊಂಡ,       // Version 3
    ದತ್ತಾಂಶ_ಮೂಲ_handle_action,             // Version 3
};

SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Create(SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ)
{
    SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ದತ್ತಾಂಶ_ಮೂಲ_2 = SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ_ಮೂಲ_2));
    ಆದರೆ (!ದತ್ತಾಂಶ_ಮೂಲ_2) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ರಚನೆ wl_ದತ್ತಾಂಶ_ಮೂಲ *id = wl_ದತ್ತಾಂಶ_device_manager_create_ದತ್ತಾಂಶ_ಮೂಲ(video_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ_device_manager);
    ದತ್ತಾಂಶ_ಮೂಲ_2->ಮೂಲ = id;
    wl_ದತ್ತಾಂಶ_ಮೂಲ_ಗಣ_user_ದತ್ತಾಂಶ(id, ದತ್ತಾಂಶ_ಮೂಲ_2);
    wl_ದತ್ತಾಂಶ_ಮೂಲ_ಕೂಡಿಸು_listener(id, &ದತ್ತಾಂಶ_ಮೂಲ_listener, ದತ್ತಾಂಶ_ಮೂಲ_2);

    ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ_ಮೂಲ_2;
}

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_ಮೂಲ_send(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_primary_selection_ಮೂಲ_v1 *zwp_primary_selection_ಮೂಲ_v1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_ಮೂಲ_Send((SDL_Wayland_Primary_Selection_ಮೂಲ *)ದತ್ತಾಂಶ, mime_type, fd);
}

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_ಮೂಲ_cancelled(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zwp_primary_selection_ಮೂಲ_v1 *zwp_primary_selection_ಮೂಲ_v1)
{
    Wayland_Primary_Selection_ಮೂಲ_Destroy(ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zwp_primary_selection_ಮೂಲ_v1_listener primary_selection_ಮೂಲ_listener = {
    primary_selection_ಮೂಲ_send,
    primary_selection_ಮೂಲ_cancelled,
};

SDL_Wayland_Primary_Selection_ಮೂಲ *Wayland_Primary_Selection_ಮೂಲ_Create(SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ)
{
    SDL_Wayland_Primary_Selection_ಮೂಲ *primary_selection_ಮೂಲ = SDL_calloc(1, ಗಾತ್ರ(*primary_selection_ಮೂಲ));
    ಆದರೆ (!primary_selection_ಮೂಲ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ರಚನೆ zwp_primary_selection_ಮೂಲ_v1 *id = zwp_primary_selection_device_manager_v1_create_ಮೂಲ(video_ದತ್ತಾಂಶ->primary_selection_device_manager);
    primary_selection_ಮೂಲ->ಮೂಲ = id;
    zwp_primary_selection_ಮೂಲ_v1_ಕೂಡಿಸು_listener(id, &primary_selection_ಮೂಲ_listener, primary_selection_ಮೂಲ);

    ಹಿಂತಿರುಗಿ primary_selection_ಮೂಲ;
}

ಸ್ಥಿರ size_t Send_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ, size_t ಉದ್ದಳತೆ, ಪೂರ್ಣಾಂಕ fd)
{
    size_t ಫಲಿತಾಂಶ = 0;

    ಆದರೆ (ಉದ್ದಳತೆ > 0 && ದತ್ತಾಂಶ) {
        ಆಗ (WritePipe(fd, ದತ್ತಾಂಶ, ಉದ್ದಳತೆ, &ಫಲಿತಾಂಶ) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ssize_t Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Send(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, ಪೂರ್ಣಾಂಕ fd)
{
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ = ಖಾಲಿ;
    size_t ಉದ್ದಳತೆ = 0;

    ಆದರೆ (SDL_strcmp(mime_type, SDL_ದತ್ತಾಂಶ_ORIGIN_MIME) == 0) {
        ದತ್ತಾಂಶ = ಮೂಲ->ದತ್ತಾಂಶ_device->id_str;
        ಉದ್ದಳತೆ = SDL_strlen(ಮೂಲ->ದತ್ತಾಂಶ_device->id_str);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೂಲ->ದತ್ತಾಂಶ_callback) {
        ದತ್ತಾಂಶ = ಮೂಲ->ದತ್ತಾಂಶ_callback(ಮೂಲ->userdata.ದತ್ತಾಂಶ, mime_type, &ಉದ್ದಳತೆ);
    }

    ಹಿಂತಿರುಗಿ Send_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ, ಉದ್ದಳತೆ, fd);
}

ssize_t Wayland_Primary_Selection_ಮೂಲ_Send(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, ಪೂರ್ಣಾಂಕ fd)
{
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ = ಖಾಲಿ;
    size_t ಉದ್ದಳತೆ = 0;

    ಆದರೆ (ಮೂಲ->ದತ್ತಾಂಶ_callback) {
        ದತ್ತಾಂಶ = ಮೂಲ->ದತ್ತಾಂಶ_callback(ಮೂಲ->userdata.ದತ್ತಾಂಶ, mime_type, &ಉದ್ದಳತೆ);
    }

    ಹಿಂತಿರುಗಿ Send_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ, ಉದ್ದಳತೆ, fd);
}

ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_ಮೂಲ_ಗಣ_Callback(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, SDL_Clipboard_ದತ್ತಾಂಶ_Callback ದತ್ತಾಂಶ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata, Uint32 sequence)
{
    ಆದರೆ (ಮೂಲ) {
        ಮೂಲ->ದತ್ತಾಂಶ_callback = ದತ್ತಾಂಶ_callback;
        ಮೂಲ->cleanup_callback = cleanup_callback;
        ಮೂಲ->userdata.sequence = sequence;
        ಮೂಲ->userdata.ದತ್ತಾಂಶ = userdata;
    }
}

ಶೂನ್ಯ Wayland_Primary_Selection_ಮೂಲ_ಗಣ_Callback(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, SDL_Clipboard_ದತ್ತಾಂಶ_Callback ದತ್ತಾಂಶ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata)
{
    ಆದರೆ (ಮೂಲ) {
        ಮೂಲ->ದತ್ತಾಂಶ_callback = ದತ್ತಾಂಶ_callback;
        ಮೂಲ->cleanup_callback = cleanup_callback;
        ಮೂಲ->userdata.sequence = 0;
        ಮೂಲ->userdata.ದತ್ತಾಂಶ = userdata;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ *Clone_ದತ್ತಾಂಶ_ಬಫರ್(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಬಫರ್_2, ಸ್ಥಿರಾಂಕ size_t *len)
{
    ಶೂನ್ಯ *clone = ಖಾಲಿ;
    ಆದರೆ (*len > 0 && ಬಫರ್_2) {
        clone = SDL_malloc((*len)+ಗಾತ್ರ(Uint32));
        ಆದರೆ (clone) {
            SDL_memcpy(clone, ಬಫರ್_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, ಗಾತ್ರ(Uint32));
        }
    }
    ಹಿಂತಿರುಗಿ clone;
}

ಶೂನ್ಯ *Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Get_ದತ್ತಾಂಶ(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ)
{
    ಶೂನ್ಯ *ಬಫರ್_2 = ಖಾಲಿ;
    *ಉದ್ದಳತೆ = 0;

    ಆದರೆ (!ಮೂಲ) {
        SDL_ಗಣ_Error("Invalid data source");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೂಲ->ದತ್ತಾಂಶ_callback) {
        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಆಂತರಿಕ_ಬಫರ್ = ಮೂಲ->ದತ್ತಾಂಶ_callback(ಮೂಲ->userdata.ದತ್ತಾಂಶ, mime_type, ಉದ್ದಳತೆ);
        ಬಫರ್_2 = Clone_ದತ್ತಾಂಶ_ಬಫರ್(ಆಂತರಿಕ_ಬಫರ್, ಉದ್ದಳತೆ);
    }

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

ಶೂನ್ಯ *Wayland_Primary_Selection_ಮೂಲ_Get_ದತ್ತಾಂಶ(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ)
{
    ಶೂನ್ಯ *ಬಫರ್_2 = ಖಾಲಿ;
    *ಉದ್ದಳತೆ = 0;

    ಆದರೆ (!ಮೂಲ) {
        SDL_ಗಣ_Error("Invalid primary selection source");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೂಲ->ದತ್ತಾಂಶ_callback) {
        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಆಂತರಿಕ_ಬಫರ್ = ಮೂಲ->ದತ್ತಾಂಶ_callback(ಮೂಲ->userdata.ದತ್ತಾಂಶ, mime_type, ಉದ್ದಳತೆ);
        ಬಫರ್_2 = Clone_ದತ್ತಾಂಶ_ಬಫರ್(ಆಂತರಿಕ_ಬಫರ್, ಉದ್ದಳತೆ);
    }

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ)
{
    ಆದರೆ (ಮೂಲ) {
        SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = ಮೂಲ->ದತ್ತಾಂಶ_device;
        ಆದರೆ (ದತ್ತಾಂಶ_device && (ದತ್ತಾಂಶ_device->selection_ಮೂಲ == ಮೂಲ)) {
            ದತ್ತಾಂಶ_device->selection_ಮೂಲ = ಖಾಲಿ;
        }
        wl_ದತ್ತಾಂಶ_ಮೂಲ_destroy(ಮೂಲ->ಮೂಲ);
        ಆದರೆ (ಮೂಲ->userdata.sequence) {
            SDL_Cancel_Clipboard_ದತ್ತಾಂಶ(ಮೂಲ->userdata.sequence);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೂಲ->cleanup_callback) {
            ಮೂಲ->cleanup_callback(ಮೂಲ->userdata.ದತ್ತಾಂಶ);
        }
        SDL_free(ಮೂಲ);
    }
}

ಶೂನ್ಯ Wayland_Primary_Selection_ಮೂಲ_Destroy(SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ)
{
    ಆದರೆ (ಮೂಲ) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = ಮೂಲ->primary_selection_device;
        ಆದರೆ (primary_selection_device && (primary_selection_device->selection_ಮೂಲ == ಮೂಲ)) {
            primary_selection_device->selection_ಮೂಲ = ಖಾಲಿ;
        }
        zwp_primary_selection_ಮೂಲ_v1_destroy(ಮೂಲ->ಮೂಲ);
        ಆದರೆ (ಮೂಲ->cleanup_callback) {
            ಮೂಲ->cleanup_callback(ಮೂಲ->userdata.ದತ್ತಾಂಶ);
        }
        SDL_free(ಮೂಲ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SelectionOfferNotifyFromMIMEs(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device, bool check_origin);

ಸ್ಥಿರ ಶೂನ್ಯ offer_ಮೂಲ_ಮುಗಿದ_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *callback, uint32_t callback_ದತ್ತಾಂಶ)
{
    ಆದರೆ (!callback) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer = (SDL_Wayland_ದತ್ತಾಂಶ_Offer *)ದತ್ತಾಂಶ;
    ಅಕ್ಷರ *id = ಖಾಲಿ;
    size_t ಉದ್ದಳತೆ = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ಖಾಲಿ;

    ಆಗ (ReadPipe(offer->read_fd, (ಶೂನ್ಯ **)&id, &ಉದ್ದಳತೆ, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    ಆದರೆ (id) {
        ಸ್ಥಿರಾಂಕ bool ಮೂಲ_is_external = SDL_strncmp(offer->ದತ್ತಾಂಶ_device->id_str, id, ಉದ್ದಳತೆ) != 0;
        SDL_free(id);
        ಆದರೆ (ಮೂಲ_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->ದತ್ತಾಂಶ_device, false);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Recursive data offer; just destroy it.
            SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = offer->ದತ್ತಾಂಶ_device;
            Wayland_ದತ್ತಾಂಶ_Offer_Destroy(offer);
            ದತ್ತಾಂಶ_device->selection_offer = ಖಾಲಿ;
        }
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener offer_ಮೂಲ_listener = {
    offer_ಮೂಲ_ಮುಗಿದ_handler
};

ಸ್ಥಿರ ಶೂನ್ಯ UpdateSeatOffers(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device)
{
    SDL_WaylandSeat *offer_seat = ದತ್ತಾಂಶ_device->seat;
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_ದತ್ತಾಂಶ->seat_list, link) {
        ಆದರೆ (s->ದತ್ತಾಂಶ_device) {
            Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(s->ದತ್ತಾಂಶ_device->selection_ಮೂಲ);
            s->ದತ್ತಾಂಶ_device->selection_ಮೂಲ = ಖಾಲಿ;

            // Don't clear the offer that is about to be set.
            ಆದರೆ (s != offer_seat) {
                Wayland_ದತ್ತಾಂಶ_Offer_Destroy(s->ದತ್ತಾಂಶ_device->selection_offer);
                s->ದತ್ತಾಂಶ_device->selection_offer = ಖಾಲಿ;
            }
        }
    }

    video_ದತ್ತಾಂಶ->current_ದತ್ತಾಂಶ_offer_seat = offer_seat;
}

ಸ್ಥಿರ ಶೂನ್ಯ SelectionOfferNotifyFromMIMEs(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device, bool check_origin)
{
    SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer = ದತ್ತಾಂಶ_device->selection_offer;
    ಅಕ್ಷರ **new_mime_types = ಖಾಲಿ;
    size_t ಅಂಕೆ_formats = 0;

    ಆದರೆ (offer) {
        size_t alloc_ಗಾತ್ರ_2 = 0;

        // Do a first pass to compute allocation size.
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **ಅಂಶ;
        wl_array_for_each(ಅಂಶ, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            ಆದರೆ (check_origin && SDL_strcmp(*ಅಂಶ, SDL_ದತ್ತಾಂಶ_ORIGIN_MIME) == 0) {
                Wayland_ದತ್ತಾಂಶ_Offer_Request_ದತ್ತಾಂಶ_From_Self(offer, *ಅಂಶ, &offer_ಮೂಲ_listener, offer);
                ಹಿಂತಿರುಗಿ;
            }

            ++ಅಂಕೆ_formats;
            alloc_ಗಾತ್ರ_2 += SDL_strlen(*ಅಂಶ) + 1;
        }

        alloc_ಗಾತ್ರ_2 += (ಅಂಕೆ_formats + 1) * ಗಾತ್ರ(ಅಕ್ಷರ *);

        new_mime_types = SDL_Allocate_Temporary_ಸ್ಮರಣೆ(alloc_ಗಾತ್ರ_2);
        ಆದರೆ (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_ಒಳಹರಿವು, "unable to allocate new_mime_types");
            ಹಿಂತಿರುಗಿ;
        }

        // Second pass to fill.
        ಅಕ್ಷರ *strPtr = (ಅಕ್ಷರ *)(new_mime_types + ಅಂಕೆ_formats + 1);
        alloc_ಗಾತ್ರ_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        ಅಂಶ = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ i = 0;
        wl_array_for_each(ಅಂಶ, &offer->mimes) {
            ಆದರೆ (!ಅಂಶ) {
                ಮುಂದುವರಿ;
            }

            new_mime_types[i++] = strPtr;
            ಸ್ಥಿರಾಂಕ size_t len = SDL_strlcpy(strPtr, *ಅಂಶ, alloc_ಗಾತ್ರ_2) + 1;
            strPtr += len;
            alloc_ಗಾತ್ರ_2 -= len;
        }
        new_mime_types[ಅಂಕೆ_formats] = ಖಾಲಿ;
    }

    UpdateSeatOffers(ದತ್ತಾಂಶ_device);
    SDL_SendClipboardUpdate(false, new_mime_types, ಅಂಕೆ_formats);
}

ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_Offer(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device, SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ಸ್ಥಿರಾಂಕ bool notify = offer || (!offer && ದತ್ತಾಂಶ_device->selection_offer && (!ದತ್ತಾಂಶ_device->selection_offer->callback || !ದತ್ತಾಂಶ_device->selection_ಮೂಲ));
    Wayland_ದತ್ತಾಂಶ_Offer_Destroy(ದತ್ತಾಂಶ_device->selection_offer);
    ದತ್ತಾಂಶ_device->selection_offer = offer;
    ಆದರೆ (notify) {
        SelectionOfferNotifyFromMIMEs(ದತ್ತಾಂಶ_device, true);
    }
}

ಶೂನ್ಯ *Wayland_ದತ್ತಾಂಶ_Offer_Get_ದತ್ತಾಂಶ_From_Self(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, size_t *ಉದ್ದಳತೆ)
{
    ಆದರೆ (!offer) {
        SDL_ಗಣ_Error("Invalid data offer");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (offer->read_fd < 0) {
        SDL_ಗಣ_Error("Pipe closed");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    ಶೂನ್ಯ *ಬಫರ್_2 = ಖಾಲಿ;
    ಆಗ (ReadPipe(offer->read_fd, &ಬಫರ್_2, ಉದ್ದಳತೆ, 0) > 0) {
    }

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

bool Wayland_ದತ್ತಾಂಶ_Offer_Request_ದತ್ತಾಂಶ_From_Self(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener *completion_listener, ಶೂನ್ಯ *userdata)
{
    ಪೂರ್ಣಾಂಕ pipefd[2];

    ಆದರೆ (!offer) {
        SDL_ಗಣ_Error("Invalid data offer");
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = offer->ದತ್ತಾಂಶ_device;
    ಆದರೆ (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    ಆದರೆ (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ಖಾಲಿ;
    }

    ಆದರೆ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_ದತ್ತಾಂಶ_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(ದತ್ತಾಂಶ_device->seat->display->display);
        wl_callback_ಕೂಡಿಸು_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(ದತ್ತಾಂಶ_device->seat->display->display);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create pipe");
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ *Wayland_ದತ್ತಾಂಶ_Offer_Receive(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ)
{
    ಪೂರ್ಣಾಂಕ pipefd[2];
    ಶೂನ್ಯ *ಬಫರ್_2 = ಖಾಲಿ;
    *ಉದ್ದಳತೆ = 0;

    ಆದರೆ (!offer) {
        SDL_ಗಣ_Error("Invalid data offer");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device = offer->ದತ್ತಾಂಶ_device;

    ಆದರೆ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_ದತ್ತಾಂಶ_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(ದತ್ತಾಂಶ_device->seat->display->display);

        ಆಗ (ReadPipe(pipefd[0], &ಬಫರ್_2, ಉದ್ದಳತೆ, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *ಉದ್ದಳತೆ, ಬಫರ್_2);

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

ಶೂನ್ಯ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type, size_t *ಉದ್ದಳತೆ)
{
    ಪೂರ್ಣಾಂಕ pipefd[2];
    ಶೂನ್ಯ *ಬಫರ್_2 = ಖಾಲಿ;
    *ಉದ್ದಳತೆ = 0;

    ಆದರೆ (!offer) {
        SDL_ಗಣ_Error("Invalid data offer");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    ಆದರೆ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        ಆಗ (ReadPipe(pipefd[0], &ಬಫರ್_2, ಉದ್ದಳತೆ, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *ಉದ್ದಳತೆ, ಬಫರ್_2);

    ಹಿಂತಿರುಗಿ ಬಫರ್_2;
}

bool Wayland_ದತ್ತಾಂಶ_Offer_ಕೂಡಿಸು_MIME(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಹಿಂತಿರುಗಿ MIMEData_List_ಕೂಡಿಸು(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_ಕೂಡಿಸು_MIME(SDL_WaylandPrimarySelectionOffer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಹಿಂತಿರುಗಿ MIMEData_List_ಕೂಡಿಸು(&offer->mimes, mime_type);
}

bool Wayland_ದತ್ತಾಂಶ_Offer_Has_MIME(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಆದರೆ (offer && mime_type) {
        ಹಿಂತಿರುಗಿ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ಹಿಂತಿರುಗಿ false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type)
{
    ಆದರೆ (offer && mime_type) {
        ಹಿಂತಿರುಗಿ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ Wayland_ದತ್ತಾಂಶ_Offer_Destroy(SDL_Wayland_ದತ್ತಾಂಶ_Offer *offer)
{
    ಆದರೆ (offer) {
        ಆದರೆ (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        ಆದರೆ (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_ದತ್ತಾಂಶ_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

ಶೂನ್ಯ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    ಆದರೆ (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_ದತ್ತಾಂಶ_Device_ಗಣ_Selection_ಮೂಲ(SDL_Wayland_ದತ್ತಾಂಶ_Device *ದತ್ತಾಂಶ_device, SDL_Wayland_ದತ್ತಾಂಶ_ಮೂಲ *ಮೂಲ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **mime_types, size_t mime_ಎಣಿಕೆ)
{
    ಆದರೆ (!ದತ್ತಾಂಶ_device) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid Data Device");
    }
    ಆದರೆ (!ಮೂಲ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid source");
    }

    ಆದರೆ (mime_ಎಣಿಕೆ) {
        ಗಾಗಿ (size_t ಸೂಚ್ಯಂಕ = 0; ಸೂಚ್ಯಂಕ < mime_ಎಣಿಕೆ; ++ಸೂಚ್ಯಂಕ) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = mime_types[ಸೂಚ್ಯಂಕ];
            wl_ದತ್ತಾಂಶ_ಮೂಲ_offer(ಮೂಲ->ಮೂಲ, mime_type);
        }

        // Advertise the data origin MIME
        wl_ದತ್ತಾಂಶ_ಮೂಲ_offer(ಮೂಲ->ಮೂಲ, SDL_ದತ್ತಾಂಶ_ORIGIN_MIME);

        wl_ದತ್ತಾಂಶ_device_ಗಣ_selection(ದತ್ತಾಂಶ_device->ದತ್ತಾಂಶ_device, ಮೂಲ->ಮೂಲ, ದತ್ತಾಂಶ_device->seat->ಕೊನೆಯ_implicit_grab_serial);
        ಆದರೆ (ದತ್ತಾಂಶ_device->selection_ಮೂಲ) {
            Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(ದತ್ತಾಂಶ_device->selection_ಮೂಲ);
        }
        ದತ್ತಾಂಶ_device->selection_ಮೂಲ = ಮೂಲ;
        ಮೂಲ->ದತ್ತಾಂಶ_device = ದತ್ತಾಂಶ_device;

    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_ದತ್ತಾಂಶ_ಮೂಲ_Destroy(ದತ್ತಾಂಶ_device->selection_ಮೂಲ);
        ದತ್ತಾಂಶ_device->selection_ಮೂಲ = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No mime data");
    }

    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_Primary_Selection_Device_ಗಣ_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_ಮೂಲ *ಮೂಲ,
                                                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *mime_types, size_t mime_ಎಣಿಕೆ)
{
    ಆದರೆ (!primary_selection_device) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid Primary Selection Device");
    }
    ಆದರೆ (!ಮೂಲ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid source");
    }

    ಆದರೆ (mime_ಎಣಿಕೆ) {
        ಗಾಗಿ (size_t ಸೂಚ್ಯಂಕ = 0; ಸೂಚ್ಯಂಕ < mime_ಎಣಿಕೆ; ++ಸೂಚ್ಯಂಕ) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mime_type = mime_types[ಸೂಚ್ಯಂಕ];
            zwp_primary_selection_ಮೂಲ_v1_offer(ಮೂಲ->ಮೂಲ, mime_type);
        }

        zwp_primary_selection_device_v1_ಗಣ_selection(primary_selection_device->primary_selection_device,
                                                      ಮೂಲ->ಮೂಲ,
                                                      primary_selection_device->seat->ಕೊನೆಯ_implicit_grab_serial);
        ಆದರೆ (primary_selection_device->selection_ಮೂಲ) {
            Wayland_Primary_Selection_ಮೂಲ_Destroy(primary_selection_device->selection_ಮೂಲ);
        }
        primary_selection_device->selection_ಮೂಲ = ಮೂಲ;
        ಮೂಲ->primary_selection_device = primary_selection_device;
    } ಇಲ್ಲದಿದ್ದರೆ {
        Wayland_Primary_Selection_ಮೂಲ_Destroy(primary_selection_device->selection_ಮೂಲ);
        primary_selection_device->selection_ಮೂಲ = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No mime data");
    }

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND

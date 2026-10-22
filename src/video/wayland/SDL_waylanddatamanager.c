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

#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_poll.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_clipboard_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylanddatamanager.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_PIPE_TIMEOUT_NS SDL_MS_ਮੰਜ਼ਿਲ_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HAVE_SIGTIMEDWAIT
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
ਸਥਿਰ ਪੂਰਨ sigtimedwait(ਅਚਲ sigset_t *ਸੈੱਟ, siginfo_t *info, ਅਚਲ ਬਣਤਰ timespec *timeout)
{
    ਬਣਤਰ timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    ਕਰੋ {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        ਲਈ (ਪੂਰਨ signo = 1; signo < NSIG; ++signo) {
            ਜੇ (sigismember(ਸੈੱਟ, signo) && sigismember(&pending, signo)) {
                ਜੇ (!sigwait(ਸੈੱਟ, &signo)) {
                    ਜੇ (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    ਵਾਪਸ signo;
                } ਨਹੀਂਤਾਂ {
                    ਵਾਪਸ -1;
                }
            }
        }

        ਜੇ (timeout->tv_sec || timeout->tv_nsec) {
            ਲੰਮਾ ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ਬਣਤਰ timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } ਜਦੋਂ (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    ਵਾਪਸ -1;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ssize_t WritePipe(ਪੂਰਨ fd, ਅਚਲ ਖਾਲੀ *ਬਫਰ_2, size_t ਕੁੱਲ_ਲੰਮਾਈ, size_t *pos)
{
    ssize_t ਬਾਈਟਾਂ_written = 0;
    ਅਚਲ ssize_t ਲੰਮਾਈ = ਕੁੱਲ_ਲੰਮਾਈ - *pos;

    sigset_t sig_ਸੈੱਟ;
    sigset_t old_sig_ਸੈੱਟ;
    ਬਣਤਰ timespec zerotime = { 0 };

    ਅਚਲ ਪੂਰਨ ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_ਸੈੱਟ);
    sigaddset(&sig_ਸੈੱਟ, SIGPIPE);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਧਾਗੇ_DISABLED
    sigprocmask(SIG_BLOCK, &sig_ਸੈੱਟ, &old_sig_ਸੈੱਟ);
#ਨਹੀਂਤਾਂ
    pthread_sigmask(SIG_BLOCK, &sig_ਸੈੱਟ, &old_sig_ਸੈੱਟ);
#ਜੇ_ਅੰਤ

    ਜੇ (ready > 0) {
        ਜੇ (ਲੰਮਾਈ > 0) {
            ਬਾਈਟਾਂ_written = ਲਿਖ(fd, (Uint8 *)ਬਫਰ_2 + *pos, SDL_min(ਲੰਮਾਈ, PIPE_BUF));
        }

        ਜੇ (ਬਾਈਟਾਂ_written > 0) {
            *pos += ਬਾਈਟਾਂ_written;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (ready == 0) {
        SDL_ਸੈੱਟ_Error("Pipe timeout");
    } ਨਹੀਂਤਾਂ  {
        SDL_ਸੈੱਟ_Error("Pipe poll error");
    }

    sigtimedwait(&sig_ਸੈੱਟ, ਨਿਰਾ, &zerotime);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਧਾਗੇ_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_ਸੈੱਟ, ਨਿਰਾ);
#ਨਹੀਂਤਾਂ
    pthread_sigmask(SIG_SETMASK, &old_sig_ਸੈੱਟ, ਨਿਰਾ);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ਬਾਈਟਾਂ_written;
}

ਸਥਿਰ ssize_t ReadPipe(ਪੂਰਨ fd, ਖਾਲੀ **ਬਫਰ_2, size_t *ਕੁੱਲ_ਲੰਮਾਈ, Sint64 timeout_ns)
{
    ਖਾਲੀ *output_ਬਫਰ = ਨਿਰਾ;
    ਅੱਖਰ ਆਰਜ਼ੀ[PIPE_BUF];
    ssize_t ਬਾਈਟਾਂ_read = 0;

    ਅਚਲ ਪੂਰਨ ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    ਜੇ (ready > 0) {
        ਬਾਈਟਾਂ_read = ਪਠ(fd, ਆਰਜ਼ੀ, ਆਕਾਰ(ਆਰਜ਼ੀ));
    } ਨਹੀਂਤਾਂ ਜੇ (ready == 0) {
        SDL_ਸੈੱਟ_Error("Pipe timeout");
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Pipe poll error");
    }

    ਜੇ (ਬਾਈਟਾਂ_read > 0) {
        ਅਚਲ size_t pos = *ਕੁੱਲ_ਲੰਮਾਈ;
        *ਕੁੱਲ_ਲੰਮਾਈ += ਬਾਈਟਾਂ_read;

        ਅਚਲ size_t new_ਬਫਰ_ਲੰਮਾਈ = *ਕੁੱਲ_ਲੰਮਾਈ + ਆਕਾਰ(Uint32);

        ਜੇ (!*ਬਫਰ_2) {
            output_ਬਫਰ = SDL_malloc(new_ਬਫਰ_ਲੰਮਾਈ);
        } ਨਹੀਂਤਾਂ {
            output_ਬਫਰ = SDL_realloc(*ਬਫਰ_2, new_ਬਫਰ_ਲੰਮਾਈ);
        }

        ਜੇ (!output_ਬਫਰ) {
            ਬਾਈਟਾਂ_read = -1;
        } ਨਹੀਂਤਾਂ {
            SDL_memcpy((Uint8 *)output_ਬਫਰ + pos, ਆਰਜ਼ੀ, ਬਾਈਟਾਂ_read);
            SDL_memset((Uint8 *)output_ਬਫਰ + (new_ਬਫਰ_ਲੰਮਾਈ - ਆਕਾਰ(Uint32)), 0, ਆਕਾਰ(Uint32));

            *ਬਫਰ_2 = output_ਬਫਰ;
        }
    }

    ਵਾਪਸ ਬਾਈਟਾਂ_read;
}

ਸਥਿਰ bool MIMEDataListHasType(ਬਣਤਰ wl_array *list, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਅਚਲ ਅੱਖਰ **ਵਸਤੂ;
    wl_array_for_each(ਵਸਤੂ, list) {
        ਜੇ (SDL_strcmp(*ਵਸਤੂ, mime_type) == 0) {
            ਵਾਪਸ true;
        }
    }

    ਵਾਪਸ false;
}

ਸਥਿਰ bool MIMEData_List_ਜੋੜੋ(ਬਣਤਰ wl_array *list, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਜੇ (!MIMEDataListHasType(list, mime_type)) {
        ਅੱਖਰ **ਵਸਤੂ = WAYLAND_wl_array_ਜੋੜੋ(list, ਆਕਾਰ(ਅੱਖਰ *));
        *ਵਸਤੂ = SDL_strdup(mime_type);
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ MIMEDataListFree(ਬਣਤਰ wl_array *list)
{
    ਅੱਖਰ **ਵਸਤੂ;
    wl_array_for_each(ਵਸਤੂ, list) {
        SDL_free(*ਵਸਤੂ);
    }

    WAYLAND_wl_array_release(list);
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_ਸਰੋਤ_handle_ਨਿਸ਼ਾਨਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *wl_ਅੰਕੜੇ_ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type)
{
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_ਸਰੋਤ_handle_send(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *wl_ਅੰਕੜੇ_ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, int32_t fd)
{
    Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Send((SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *)ਅੰਕੜੇ, mime_type, fd);
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_ਸਰੋਤ_handle_cancelled(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *wl_ਅੰਕੜੇ_ਸਰੋਤ)
{
    SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ = ਅੰਕੜੇ;
    ਜੇ (ਸਰੋਤ) {
        Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(ਸਰੋਤ);
    }
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_ਸਰੋਤ_handle_dnd_drop_performed(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *wl_ਅੰਕੜੇ_ਸਰੋਤ)
{
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_ਸਰੋਤ_handle_dnd_ਮੁਕੰਮਲ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *wl_ਅੰਕੜੇ_ਸਰੋਤ)
{
    SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ = ਅੰਕੜੇ;
    ਜੇ (ਸਰੋਤ) {
        Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(ਸਰੋਤ);
    }
}

ਸਥਿਰ ਖਾਲੀ ਅੰਕੜੇ_ਸਰੋਤ_handle_action(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *wl_ਅੰਕੜੇ_ਸਰੋਤ, uint32_t dnd_action)
{
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ_listener ਅੰਕੜੇ_ਸਰੋਤ_listener = {
    ਅੰਕੜੇ_ਸਰੋਤ_handle_ਨਿਸ਼ਾਨਾ,
    ਅੰਕੜੇ_ਸਰੋਤ_handle_send,
    ਅੰਕੜੇ_ਸਰੋਤ_handle_cancelled,
    ਅੰਕੜੇ_ਸਰੋਤ_handle_dnd_drop_performed, // Version 3
    ਅੰਕੜੇ_ਸਰੋਤ_handle_dnd_ਮੁਕੰਮਲ,       // Version 3
    ਅੰਕੜੇ_ਸਰੋਤ_handle_action,             // Version 3
};

SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Create(SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ)
{
    SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਅੰਕੜੇ_ਸਰੋਤ_2 = SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ_ਸਰੋਤ_2));
    ਜੇ (!ਅੰਕੜੇ_ਸਰੋਤ_2) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਬਣਤਰ wl_ਅੰਕੜੇ_ਸਰੋਤ *id = wl_ਅੰਕੜੇ_device_manager_create_ਅੰਕੜੇ_ਸਰੋਤ(video_ਅੰਕੜੇ->ਅੰਕੜੇ_device_manager);
    ਅੰਕੜੇ_ਸਰੋਤ_2->ਸਰੋਤ = id;
    wl_ਅੰਕੜੇ_ਸਰੋਤ_ਸੈੱਟ_user_ਅੰਕੜੇ(id, ਅੰਕੜੇ_ਸਰੋਤ_2);
    wl_ਅੰਕੜੇ_ਸਰੋਤ_ਜੋੜੋ_listener(id, &ਅੰਕੜੇ_ਸਰੋਤ_listener, ਅੰਕੜੇ_ਸਰੋਤ_2);

    ਵਾਪਸ ਅੰਕੜੇ_ਸਰੋਤ_2;
}

ਸਥਿਰ ਖਾਲੀ primary_selection_ਸਰੋਤ_send(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_primary_selection_ਸਰੋਤ_v1 *zwp_primary_selection_ਸਰੋਤ_v1, ਅਚਲ ਅੱਖਰ *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_ਸਰੋਤ_Send((SDL_Wayland_Primary_Selection_ਸਰੋਤ *)ਅੰਕੜੇ, mime_type, fd);
}

ਸਥਿਰ ਖਾਲੀ primary_selection_ਸਰੋਤ_cancelled(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zwp_primary_selection_ਸਰੋਤ_v1 *zwp_primary_selection_ਸਰੋਤ_v1)
{
    Wayland_Primary_Selection_ਸਰੋਤ_Destroy(ਅੰਕੜੇ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zwp_primary_selection_ਸਰੋਤ_v1_listener primary_selection_ਸਰੋਤ_listener = {
    primary_selection_ਸਰੋਤ_send,
    primary_selection_ਸਰੋਤ_cancelled,
};

SDL_Wayland_Primary_Selection_ਸਰੋਤ *Wayland_Primary_Selection_ਸਰੋਤ_Create(SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ)
{
    SDL_Wayland_Primary_Selection_ਸਰੋਤ *primary_selection_ਸਰੋਤ = SDL_calloc(1, ਆਕਾਰ(*primary_selection_ਸਰੋਤ));
    ਜੇ (!primary_selection_ਸਰੋਤ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਬਣਤਰ zwp_primary_selection_ਸਰੋਤ_v1 *id = zwp_primary_selection_device_manager_v1_create_ਸਰੋਤ(video_ਅੰਕੜੇ->primary_selection_device_manager);
    primary_selection_ਸਰੋਤ->ਸਰੋਤ = id;
    zwp_primary_selection_ਸਰੋਤ_v1_ਜੋੜੋ_listener(id, &primary_selection_ਸਰੋਤ_listener, primary_selection_ਸਰੋਤ);

    ਵਾਪਸ primary_selection_ਸਰੋਤ;
}

ਸਥਿਰ size_t Send_ਅੰਕੜੇ(ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ, size_t ਲੰਮਾਈ, ਪੂਰਨ fd)
{
    size_t ਨਤੀਜਾ = 0;

    ਜੇ (ਲੰਮਾਈ > 0 && ਅੰਕੜੇ) {
        ਜਦੋਂ (WritePipe(fd, ਅੰਕੜੇ, ਲੰਮਾਈ, &ਨਤੀਜਾ) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    ਵਾਪਸ ਨਤੀਜਾ;
}

ssize_t Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Send(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, ਪੂਰਨ fd)
{
    ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ = ਨਿਰਾ;
    size_t ਲੰਮਾਈ = 0;

    ਜੇ (SDL_strcmp(mime_type, SDL_ਅੰਕੜੇ_ORIGIN_MIME) == 0) {
        ਅੰਕੜੇ = ਸਰੋਤ->ਅੰਕੜੇ_device->id_str;
        ਲੰਮਾਈ = SDL_strlen(ਸਰੋਤ->ਅੰਕੜੇ_device->id_str);
    } ਨਹੀਂਤਾਂ ਜੇ (ਸਰੋਤ->ਅੰਕੜੇ_callback) {
        ਅੰਕੜੇ = ਸਰੋਤ->ਅੰਕੜੇ_callback(ਸਰੋਤ->userdata.ਅੰਕੜੇ, mime_type, &ਲੰਮਾਈ);
    }

    ਵਾਪਸ Send_ਅੰਕੜੇ(ਅੰਕੜੇ, ਲੰਮਾਈ, fd);
}

ssize_t Wayland_Primary_Selection_ਸਰੋਤ_Send(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, ਪੂਰਨ fd)
{
    ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ = ਨਿਰਾ;
    size_t ਲੰਮਾਈ = 0;

    ਜੇ (ਸਰੋਤ->ਅੰਕੜੇ_callback) {
        ਅੰਕੜੇ = ਸਰੋਤ->ਅੰਕੜੇ_callback(ਸਰੋਤ->userdata.ਅੰਕੜੇ, mime_type, &ਲੰਮਾਈ);
    }

    ਵਾਪਸ Send_ਅੰਕੜੇ(ਅੰਕੜੇ, ਲੰਮਾਈ, fd);
}

ਖਾਲੀ Wayland_ਅੰਕੜੇ_ਸਰੋਤ_ਸੈੱਟ_Callback(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, SDL_Clipboard_ਅੰਕੜੇ_Callback ਅੰਕੜੇ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ਖਾਲੀ *userdata, Uint32 sequence)
{
    ਜੇ (ਸਰੋਤ) {
        ਸਰੋਤ->ਅੰਕੜੇ_callback = ਅੰਕੜੇ_callback;
        ਸਰੋਤ->cleanup_callback = cleanup_callback;
        ਸਰੋਤ->userdata.sequence = sequence;
        ਸਰੋਤ->userdata.ਅੰਕੜੇ = userdata;
    }
}

ਖਾਲੀ Wayland_Primary_Selection_ਸਰੋਤ_ਸੈੱਟ_Callback(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, SDL_Clipboard_ਅੰਕੜੇ_Callback ਅੰਕੜੇ_callback, SDL_ClipboardCleanupCallback cleanup_callback, ਖਾਲੀ *userdata)
{
    ਜੇ (ਸਰੋਤ) {
        ਸਰੋਤ->ਅੰਕੜੇ_callback = ਅੰਕੜੇ_callback;
        ਸਰੋਤ->cleanup_callback = cleanup_callback;
        ਸਰੋਤ->userdata.sequence = 0;
        ਸਰੋਤ->userdata.ਅੰਕੜੇ = userdata;
    }
}

ਸਥਿਰ ਖਾਲੀ *Clone_ਅੰਕੜੇ_ਬਫਰ(ਅਚਲ ਖਾਲੀ *ਬਫਰ_2, ਅਚਲ size_t *len)
{
    ਖਾਲੀ *clone = ਨਿਰਾ;
    ਜੇ (*len > 0 && ਬਫਰ_2) {
        clone = SDL_malloc((*len)+ਆਕਾਰ(Uint32));
        ਜੇ (clone) {
            SDL_memcpy(clone, ਬਫਰ_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, ਆਕਾਰ(Uint32));
        }
    }
    ਵਾਪਸ clone;
}

ਖਾਲੀ *Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Get_ਅੰਕੜੇ(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    ਖਾਲੀ *ਬਫਰ_2 = ਨਿਰਾ;
    *ਲੰਮਾਈ = 0;

    ਜੇ (!ਸਰੋਤ) {
        SDL_ਸੈੱਟ_Error("Invalid data source");
    } ਨਹੀਂਤਾਂ ਜੇ (ਸਰੋਤ->ਅੰਕੜੇ_callback) {
        ਅਚਲ ਖਾਲੀ *ਅੰਦਰੂਨੀ_ਬਫਰ = ਸਰੋਤ->ਅੰਕੜੇ_callback(ਸਰੋਤ->userdata.ਅੰਕੜੇ, mime_type, ਲੰਮਾਈ);
        ਬਫਰ_2 = Clone_ਅੰਕੜੇ_ਬਫਰ(ਅੰਦਰੂਨੀ_ਬਫਰ, ਲੰਮਾਈ);
    }

    ਵਾਪਸ ਬਫਰ_2;
}

ਖਾਲੀ *Wayland_Primary_Selection_ਸਰੋਤ_Get_ਅੰਕੜੇ(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    ਖਾਲੀ *ਬਫਰ_2 = ਨਿਰਾ;
    *ਲੰਮਾਈ = 0;

    ਜੇ (!ਸਰੋਤ) {
        SDL_ਸੈੱਟ_Error("Invalid primary selection source");
    } ਨਹੀਂਤਾਂ ਜੇ (ਸਰੋਤ->ਅੰਕੜੇ_callback) {
        ਅਚਲ ਖਾਲੀ *ਅੰਦਰੂਨੀ_ਬਫਰ = ਸਰੋਤ->ਅੰਕੜੇ_callback(ਸਰੋਤ->userdata.ਅੰਕੜੇ, mime_type, ਲੰਮਾਈ);
        ਬਫਰ_2 = Clone_ਅੰਕੜੇ_ਬਫਰ(ਅੰਦਰੂਨੀ_ਬਫਰ, ਲੰਮਾਈ);
    }

    ਵਾਪਸ ਬਫਰ_2;
}

ਖਾਲੀ Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ)
{
    ਜੇ (ਸਰੋਤ) {
        SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = ਸਰੋਤ->ਅੰਕੜੇ_device;
        ਜੇ (ਅੰਕੜੇ_device && (ਅੰਕੜੇ_device->selection_ਸਰੋਤ == ਸਰੋਤ)) {
            ਅੰਕੜੇ_device->selection_ਸਰੋਤ = ਨਿਰਾ;
        }
        wl_ਅੰਕੜੇ_ਸਰੋਤ_destroy(ਸਰੋਤ->ਸਰੋਤ);
        ਜੇ (ਸਰੋਤ->userdata.sequence) {
            SDL_Cancel_Clipboard_ਅੰਕੜੇ(ਸਰੋਤ->userdata.sequence);
        } ਨਹੀਂਤਾਂ ਜੇ (ਸਰੋਤ->cleanup_callback) {
            ਸਰੋਤ->cleanup_callback(ਸਰੋਤ->userdata.ਅੰਕੜੇ);
        }
        SDL_free(ਸਰੋਤ);
    }
}

ਖਾਲੀ Wayland_Primary_Selection_ਸਰੋਤ_Destroy(SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ)
{
    ਜੇ (ਸਰੋਤ) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = ਸਰੋਤ->primary_selection_device;
        ਜੇ (primary_selection_device && (primary_selection_device->selection_ਸਰੋਤ == ਸਰੋਤ)) {
            primary_selection_device->selection_ਸਰੋਤ = ਨਿਰਾ;
        }
        zwp_primary_selection_ਸਰੋਤ_v1_destroy(ਸਰੋਤ->ਸਰੋਤ);
        ਜੇ (ਸਰੋਤ->cleanup_callback) {
            ਸਰੋਤ->cleanup_callback(ਸਰੋਤ->userdata.ਅੰਕੜੇ);
        }
        SDL_free(ਸਰੋਤ);
    }
}

ਸਥਿਰ ਖਾਲੀ SelectionOfferNotifyFromMIMEs(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device, bool check_origin);

ਸਥਿਰ ਖਾਲੀ offer_ਸਰੋਤ_ਪੂਰਾ_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *callback, uint32_t callback_ਅੰਕੜੇ)
{
    ਜੇ (!callback) {
        ਵਾਪਸ;
    }

    SDL_Wayland_ਅੰਕੜੇ_Offer *offer = (SDL_Wayland_ਅੰਕੜੇ_Offer *)ਅੰਕੜੇ;
    ਅੱਖਰ *id = ਨਿਰਾ;
    size_t ਲੰਮਾਈ = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ਨਿਰਾ;

    ਜਦੋਂ (ReadPipe(offer->read_fd, (ਖਾਲੀ **)&id, &ਲੰਮਾਈ, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    ਜੇ (id) {
        ਅਚਲ bool ਸਰੋਤ_is_external = SDL_strncmp(offer->ਅੰਕੜੇ_device->id_str, id, ਲੰਮਾਈ) != 0;
        SDL_free(id);
        ਜੇ (ਸਰੋਤ_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->ਅੰਕੜੇ_device, false);
        } ਨਹੀਂਤਾਂ {
            // Recursive data offer; just destroy it.
            SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = offer->ਅੰਕੜੇ_device;
            Wayland_ਅੰਕੜੇ_Offer_Destroy(offer);
            ਅੰਕੜੇ_device->selection_offer = ਨਿਰਾ;
        }
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener offer_ਸਰੋਤ_listener = {
    offer_ਸਰੋਤ_ਪੂਰਾ_handler
};

ਸਥਿਰ ਖਾਲੀ UpdateSeatOffers(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device)
{
    SDL_WaylandSeat *offer_seat = ਅੰਕੜੇ_device->seat;
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_ਅੰਕੜੇ->seat_list, link) {
        ਜੇ (s->ਅੰਕੜੇ_device) {
            Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(s->ਅੰਕੜੇ_device->selection_ਸਰੋਤ);
            s->ਅੰਕੜੇ_device->selection_ਸਰੋਤ = ਨਿਰਾ;

            // Don't clear the offer that is about to be set.
            ਜੇ (s != offer_seat) {
                Wayland_ਅੰਕੜੇ_Offer_Destroy(s->ਅੰਕੜੇ_device->selection_offer);
                s->ਅੰਕੜੇ_device->selection_offer = ਨਿਰਾ;
            }
        }
    }

    video_ਅੰਕੜੇ->current_ਅੰਕੜੇ_offer_seat = offer_seat;
}

ਸਥਿਰ ਖਾਲੀ SelectionOfferNotifyFromMIMEs(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device, bool check_origin)
{
    SDL_Wayland_ਅੰਕੜੇ_Offer *offer = ਅੰਕੜੇ_device->selection_offer;
    ਅੱਖਰ **new_mime_types = ਨਿਰਾ;
    size_t ਅੰਕ_formats = 0;

    ਜੇ (offer) {
        size_t alloc_ਮਾਪ_2 = 0;

        // Do a first pass to compute allocation size.
        ਅਚਲ ਅੱਖਰ **ਵਸਤੂ;
        wl_array_for_each(ਵਸਤੂ, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            ਜੇ (check_origin && SDL_strcmp(*ਵਸਤੂ, SDL_ਅੰਕੜੇ_ORIGIN_MIME) == 0) {
                Wayland_ਅੰਕੜੇ_Offer_Request_ਅੰਕੜੇ_From_Self(offer, *ਵਸਤੂ, &offer_ਸਰੋਤ_listener, offer);
                ਵਾਪਸ;
            }

            ++ਅੰਕ_formats;
            alloc_ਮਾਪ_2 += SDL_strlen(*ਵਸਤੂ) + 1;
        }

        alloc_ਮਾਪ_2 += (ਅੰਕ_formats + 1) * ਆਕਾਰ(ਅੱਖਰ *);

        new_mime_types = SDL_Allocate_Temporary_ਸਮ੍ਰਿਤੀ(alloc_ਮਾਪ_2);
        ਜੇ (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼, "unable to allocate new_mime_types");
            ਵਾਪਸ;
        }

        // Second pass to fill.
        ਅੱਖਰ *strPtr = (ਅੱਖਰ *)(new_mime_types + ਅੰਕ_formats + 1);
        alloc_ਮਾਪ_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        ਵਸਤੂ = ਨਿਰਾ;
        ਪੂਰਨ i = 0;
        wl_array_for_each(ਵਸਤੂ, &offer->mimes) {
            ਜੇ (!ਵਸਤੂ) {
                ਜਾਰੀ;
            }

            new_mime_types[i++] = strPtr;
            ਅਚਲ size_t len = SDL_strlcpy(strPtr, *ਵਸਤੂ, alloc_ਮਾਪ_2) + 1;
            strPtr += len;
            alloc_ਮਾਪ_2 -= len;
        }
        new_mime_types[ਅੰਕ_formats] = ਨਿਰਾ;
    }

    UpdateSeatOffers(ਅੰਕੜੇ_device);
    SDL_SendClipboardUpdate(false, new_mime_types, ਅੰਕ_formats);
}

ਖਾਲੀ Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_Offer(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device, SDL_Wayland_ਅੰਕੜੇ_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ਅਚਲ bool notify = offer || (!offer && ਅੰਕੜੇ_device->selection_offer && (!ਅੰਕੜੇ_device->selection_offer->callback || !ਅੰਕੜੇ_device->selection_ਸਰੋਤ));
    Wayland_ਅੰਕੜੇ_Offer_Destroy(ਅੰਕੜੇ_device->selection_offer);
    ਅੰਕੜੇ_device->selection_offer = offer;
    ਜੇ (notify) {
        SelectionOfferNotifyFromMIMEs(ਅੰਕੜੇ_device, true);
    }
}

ਖਾਲੀ *Wayland_ਅੰਕੜੇ_Offer_Get_ਅੰਕੜੇ_From_Self(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, size_t *ਲੰਮਾਈ)
{
    ਜੇ (!offer) {
        SDL_ਸੈੱਟ_Error("Invalid data offer");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (offer->read_fd < 0) {
        SDL_ਸੈੱਟ_Error("Pipe closed");
        ਵਾਪਸ ਨਿਰਾ;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    ਖਾਲੀ *ਬਫਰ_2 = ਨਿਰਾ;
    ਜਦੋਂ (ReadPipe(offer->read_fd, &ਬਫਰ_2, ਲੰਮਾਈ, 0) > 0) {
    }

    ਵਾਪਸ ਬਫਰ_2;
}

bool Wayland_ਅੰਕੜੇ_Offer_Request_ਅੰਕੜੇ_From_Self(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type, ਅਚਲ ਬਣਤਰ wl_callback_listener *completion_listener, ਖਾਲੀ *userdata)
{
    ਪੂਰਨ pipefd[2];

    ਜੇ (!offer) {
        SDL_ਸੈੱਟ_Error("Invalid data offer");
        ਵਾਪਸ false;
    }

    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = offer->ਅੰਕੜੇ_device;
    ਜੇ (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    ਜੇ (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ਨਿਰਾ;
    }

    ਜੇ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_ਅੰਕੜੇ_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(ਅੰਕੜੇ_device->seat->display->display);
        wl_callback_ਜੋੜੋ_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(ਅੰਕੜੇ_device->seat->display->display);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create pipe");
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ *Wayland_ਅੰਕੜੇ_Offer_Receive(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    ਪੂਰਨ pipefd[2];
    ਖਾਲੀ *ਬਫਰ_2 = ਨਿਰਾ;
    *ਲੰਮਾਈ = 0;

    ਜੇ (!offer) {
        SDL_ਸੈੱਟ_Error("Invalid data offer");
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device = offer->ਅੰਕੜੇ_device;

    ਜੇ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_ਅੰਕੜੇ_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(ਅੰਕੜੇ_device->seat->display->display);

        ਜਦੋਂ (ReadPipe(pipefd[0], &ਬਫਰ_2, ਲੰਮਾਈ, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *ਲੰਮਾਈ, ਬਫਰ_2);

    ਵਾਪਸ ਬਫਰ_2;
}

ਖਾਲੀ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ਅਚਲ ਅੱਖਰ *mime_type, size_t *ਲੰਮਾਈ)
{
    ਪੂਰਨ pipefd[2];
    ਖਾਲੀ *ਬਫਰ_2 = ਨਿਰਾ;
    *ਲੰਮਾਈ = 0;

    ਜੇ (!offer) {
        SDL_ਸੈੱਟ_Error("Invalid data offer");
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    ਜੇ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        ਜਦੋਂ (ReadPipe(pipefd[0], &ਬਫਰ_2, ਲੰਮਾਈ, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *ਲੰਮਾਈ, ਬਫਰ_2);

    ਵਾਪਸ ਬਫਰ_2;
}

bool Wayland_ਅੰਕੜੇ_Offer_ਜੋੜੋ_MIME(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਵਾਪਸ MIMEData_List_ਜੋੜੋ(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_ਜੋੜੋ_MIME(SDL_WaylandPrimarySelectionOffer *offer, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਵਾਪਸ MIMEData_List_ਜੋੜੋ(&offer->mimes, mime_type);
}

bool Wayland_ਅੰਕੜੇ_Offer_Has_MIME(SDL_Wayland_ਅੰਕੜੇ_Offer *offer, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਜੇ (offer && mime_type) {
        ਵਾਪਸ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ਵਾਪਸ false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ਅਚਲ ਅੱਖਰ *mime_type)
{
    ਜੇ (offer && mime_type) {
        ਵਾਪਸ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ਵਾਪਸ false;
}

ਖਾਲੀ Wayland_ਅੰਕੜੇ_Offer_Destroy(SDL_Wayland_ਅੰਕੜੇ_Offer *offer)
{
    ਜੇ (offer) {
        ਜੇ (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        ਜੇ (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_ਅੰਕੜੇ_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

ਖਾਲੀ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    ਜੇ (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_ਅੰਕੜੇ_Device_ਸੈੱਟ_Selection_ਸਰੋਤ(SDL_Wayland_ਅੰਕੜੇ_Device *ਅੰਕੜੇ_device, SDL_Wayland_ਅੰਕੜੇ_ਸਰੋਤ *ਸਰੋਤ, ਅਚਲ ਅੱਖਰ **mime_types, size_t mime_ਗਿਣਤੀ)
{
    ਜੇ (!ਅੰਕੜੇ_device) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid Data Device");
    }
    ਜੇ (!ਸਰੋਤ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid source");
    }

    ਜੇ (mime_ਗਿਣਤੀ) {
        ਲਈ (size_t ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < mime_ਗਿਣਤੀ; ++ਸੂਚਕਾਂਕ) {
            ਅਚਲ ਅੱਖਰ *mime_type = mime_types[ਸੂਚਕਾਂਕ];
            wl_ਅੰਕੜੇ_ਸਰੋਤ_offer(ਸਰੋਤ->ਸਰੋਤ, mime_type);
        }

        // Advertise the data origin MIME
        wl_ਅੰਕੜੇ_ਸਰੋਤ_offer(ਸਰੋਤ->ਸਰੋਤ, SDL_ਅੰਕੜੇ_ORIGIN_MIME);

        wl_ਅੰਕੜੇ_device_ਸੈੱਟ_selection(ਅੰਕੜੇ_device->ਅੰਕੜੇ_device, ਸਰੋਤ->ਸਰੋਤ, ਅੰਕੜੇ_device->seat->ਆਖਰੀ_implicit_grab_serial);
        ਜੇ (ਅੰਕੜੇ_device->selection_ਸਰੋਤ) {
            Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(ਅੰਕੜੇ_device->selection_ਸਰੋਤ);
        }
        ਅੰਕੜੇ_device->selection_ਸਰੋਤ = ਸਰੋਤ;
        ਸਰੋਤ->ਅੰਕੜੇ_device = ਅੰਕੜੇ_device;

    } ਨਹੀਂਤਾਂ {
        Wayland_ਅੰਕੜੇ_ਸਰੋਤ_Destroy(ਅੰਕੜੇ_device->selection_ਸਰੋਤ);
        ਅੰਕੜੇ_device->selection_ਸਰੋਤ = ਨਿਰਾ;
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No mime data");
    }

    ਵਾਪਸ true;
}

bool Wayland_Primary_Selection_Device_ਸੈੱਟ_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_ਸਰੋਤ *ਸਰੋਤ,
                                                ਅਚਲ ਅੱਖਰ *ਅਚਲ *mime_types, size_t mime_ਗਿਣਤੀ)
{
    ਜੇ (!primary_selection_device) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid Primary Selection Device");
    }
    ਜੇ (!ਸਰੋਤ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid source");
    }

    ਜੇ (mime_ਗਿਣਤੀ) {
        ਲਈ (size_t ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < mime_ਗਿਣਤੀ; ++ਸੂਚਕਾਂਕ) {
            ਅਚਲ ਅੱਖਰ *mime_type = mime_types[ਸੂਚਕਾਂਕ];
            zwp_primary_selection_ਸਰੋਤ_v1_offer(ਸਰੋਤ->ਸਰੋਤ, mime_type);
        }

        zwp_primary_selection_device_v1_ਸੈੱਟ_selection(primary_selection_device->primary_selection_device,
                                                      ਸਰੋਤ->ਸਰੋਤ,
                                                      primary_selection_device->seat->ਆਖਰੀ_implicit_grab_serial);
        ਜੇ (primary_selection_device->selection_ਸਰੋਤ) {
            Wayland_Primary_Selection_ਸਰੋਤ_Destroy(primary_selection_device->selection_ਸਰੋਤ);
        }
        primary_selection_device->selection_ਸਰੋਤ = ਸਰੋਤ;
        ਸਰੋਤ->primary_selection_device = primary_selection_device;
    } ਨਹੀਂਤਾਂ {
        Wayland_Primary_Selection_ਸਰੋਤ_Destroy(primary_selection_device->selection_ਸਰੋਤ);
        primary_selection_device->selection_ਸਰੋਤ = ਨਿਰਾ;
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No mime data");
    }

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND

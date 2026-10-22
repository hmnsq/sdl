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

#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <signal.h>

#అన్తర్భావ "../../core/unix/SDL_poll.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../SDL_clipboard_c.h"

#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "SDL_waylanddatamanager.h"
#అన్తర్భావ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#నిర్వచించు DEFAULT_PIPE_TIMEOUT_NS SDL_MS_గమ్యం_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#నిర్వచితం_కాకపోతే HAVE_SIGTIMEDWAIT
#అన్తర్భావ <errno.h>
#అన్తర్భావ <time.h>
స్థిర పూర్ణాంకం sigtimedwait(స్థిరరాశి sigset_t *సమితి, siginfo_t *info, స్థిరరాశి నిర్మాణం timespec *timeout)
{
    నిర్మాణం timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    చేయి {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        కొరకు (పూర్ణాంకం signo = 1; signo < NSIG; ++signo) {
            ఒకవేళ (sigismember(సమితి, signo) && sigismember(&pending, signo)) {
                ఒకవేళ (!sigwait(సమితి, &signo)) {
                    ఒకవేళ (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    తిరిగి signo;
                } లేకపోతే {
                    తిరిగి -1;
                }
            }
        }

        ఒకవేళ (timeout->tv_sec || timeout->tv_nsec) {
            దీర్ఘ ns = 20000000L; // 2/100ths of a second
            nanosleep(&(నిర్మాణం timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } అయితే (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    తిరిగి -1;
}
#అయితే_ముగింపు

స్థిర ssize_t WritePipe(పూర్ణాంకం fd, స్థిరరాశి శూన్య *బఫరు_2, size_t మొత్తం_నిడివి, size_t *pos)
{
    ssize_t బైట్లు_written = 0;
    స్థిరరాశి ssize_t నిడివి = మొత్తం_నిడివి - *pos;

    sigset_t sig_సమితి;
    sigset_t old_sig_సమితి;
    నిర్మాణం timespec zerotime = { 0 };

    స్థిరరాశి పూర్ణాంకం ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_సమితి);
    sigaddset(&sig_సమితి, SIGPIPE);

#నిర్వచితమైతే SDL_దారాలు_DISABLED
    sigprocmask(SIG_BLOCK, &sig_సమితి, &old_sig_సమితి);
#లేకపోతే
    pthread_sigmask(SIG_BLOCK, &sig_సమితి, &old_sig_సమితి);
#అయితే_ముగింపు

    ఒకవేళ (ready > 0) {
        ఒకవేళ (నిడివి > 0) {
            బైట్లు_written = లిఖ(fd, (Uint8 *)బఫరు_2 + *pos, SDL_min(నిడివి, PIPE_BUF));
        }

        ఒకవేళ (బైట్లు_written > 0) {
            *pos += బైట్లు_written;
        }
    } లేకపోతే ఒకవేళ (ready == 0) {
        SDL_సమితి_Error("Pipe timeout");
    } లేకపోతే  {
        SDL_సమితి_Error("Pipe poll error");
    }

    sigtimedwait(&sig_సమితి, ఖాళీ, &zerotime);

#నిర్వచితమైతే SDL_దారాలు_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_సమితి, ఖాళీ);
#లేకపోతే
    pthread_sigmask(SIG_SETMASK, &old_sig_సమితి, ఖాళీ);
#అయితే_ముగింపు

    తిరిగి బైట్లు_written;
}

స్థిర ssize_t ReadPipe(పూర్ణాంకం fd, శూన్య **బఫరు_2, size_t *మొత్తం_నిడివి, Sint64 timeout_ns)
{
    శూన్య *output_బఫరు = ఖాళీ;
    అక్షరం తాత్కాలిక[PIPE_BUF];
    ssize_t బైట్లు_read = 0;

    స్థిరరాశి పూర్ణాంకం ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    ఒకవేళ (ready > 0) {
        బైట్లు_read = పఠ(fd, తాత్కాలిక, పరిమాణం(తాత్కాలిక));
    } లేకపోతే ఒకవేళ (ready == 0) {
        SDL_సమితి_Error("Pipe timeout");
    } లేకపోతే {
        SDL_సమితి_Error("Pipe poll error");
    }

    ఒకవేళ (బైట్లు_read > 0) {
        స్థిరరాశి size_t pos = *మొత్తం_నిడివి;
        *మొత్తం_నిడివి += బైట్లు_read;

        స్థిరరాశి size_t new_బఫరు_నిడివి = *మొత్తం_నిడివి + పరిమాణం(Uint32);

        ఒకవేళ (!*బఫరు_2) {
            output_బఫరు = SDL_malloc(new_బఫరు_నిడివి);
        } లేకపోతే {
            output_బఫరు = SDL_realloc(*బఫరు_2, new_బఫరు_నిడివి);
        }

        ఒకవేళ (!output_బఫరు) {
            బైట్లు_read = -1;
        } లేకపోతే {
            SDL_memcpy((Uint8 *)output_బఫరు + pos, తాత్కాలిక, బైట్లు_read);
            SDL_memset((Uint8 *)output_బఫరు + (new_బఫరు_నిడివి - పరిమాణం(Uint32)), 0, పరిమాణం(Uint32));

            *బఫరు_2 = output_బఫరు;
        }
    }

    తిరిగి బైట్లు_read;
}

స్థిర bool MIMEDataListHasType(నిర్మాణం wl_array *list, స్థిరరాశి అక్షరం *mime_type)
{
    స్థిరరాశి అక్షరం **అంశం;
    wl_array_for_each(అంశం, list) {
        ఒకవేళ (SDL_strcmp(*అంశం, mime_type) == 0) {
            తిరిగి true;
        }
    }

    తిరిగి false;
}

స్థిర bool MIMEData_List_కూడు(నిర్మాణం wl_array *list, స్థిరరాశి అక్షరం *mime_type)
{
    ఒకవేళ (!MIMEDataListHasType(list, mime_type)) {
        అక్షరం **అంశం = WAYLAND_wl_array_కూడు(list, పరిమాణం(అక్షరం *));
        *అంశం = SDL_strdup(mime_type);
    }

    తిరిగి true;
}

స్థిర శూన్య MIMEDataListFree(నిర్మాణం wl_array *list)
{
    అక్షరం **అంశం;
    wl_array_for_each(అంశం, list) {
        SDL_free(*అంశం);
    }

    WAYLAND_wl_array_release(list);
}

స్థిర శూన్య దత్తాంశం_ఆధారం_handle_లక్ష్యం(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_ఆధారం *wl_దత్తాంశం_ఆధారం, స్థిరరాశి అక్షరం *mime_type)
{
}

స్థిర శూన్య దత్తాంశం_ఆధారం_handle_send(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_ఆధారం *wl_దత్తాంశం_ఆధారం, స్థిరరాశి అక్షరం *mime_type, int32_t fd)
{
    Wayland_దత్తాంశం_ఆధారం_Send((SDL_Wayland_దత్తాంశం_ఆధారం *)దత్తాంశం, mime_type, fd);
}

స్థిర శూన్య దత్తాంశం_ఆధారం_handle_cancelled(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_ఆధారం *wl_దత్తాంశం_ఆధారం)
{
    SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం = దత్తాంశం;
    ఒకవేళ (ఆధారం) {
        Wayland_దత్తాంశం_ఆధారం_Destroy(ఆధారం);
    }
}

స్థిర శూన్య దత్తాంశం_ఆధారం_handle_dnd_drop_performed(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_ఆధారం *wl_దత్తాంశం_ఆధారం)
{
}

స్థిర శూన్య దత్తాంశం_ఆధారం_handle_dnd_ముగిసిన(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_ఆధారం *wl_దత్తాంశం_ఆధారం)
{
    SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం = దత్తాంశం;
    ఒకవేళ (ఆధారం) {
        Wayland_దత్తాంశం_ఆధారం_Destroy(ఆధారం);
    }
}

స్థిర శూన్య దత్తాంశం_ఆధారం_handle_action(శూన్య *దత్తాంశం, నిర్మాణం wl_దత్తాంశం_ఆధారం *wl_దత్తాంశం_ఆధారం, uint32_t dnd_action)
{
}

స్థిర స్థిరరాశి నిర్మాణం wl_దత్తాంశం_ఆధారం_listener దత్తాంశం_ఆధారం_listener = {
    దత్తాంశం_ఆధారం_handle_లక్ష్యం,
    దత్తాంశం_ఆధారం_handle_send,
    దత్తాంశం_ఆధారం_handle_cancelled,
    దత్తాంశం_ఆధారం_handle_dnd_drop_performed, // Version 3
    దత్తాంశం_ఆధారం_handle_dnd_ముగిసిన,       // Version 3
    దత్తాంశం_ఆధారం_handle_action,             // Version 3
};

SDL_Wayland_దత్తాంశం_ఆధారం *Wayland_దత్తాంశం_ఆధారం_Create(SDL_Video_దత్తాంశం *video_దత్తాంశం)
{
    SDL_Wayland_దత్తాంశం_ఆధారం *దత్తాంశం_ఆధారం_2 = SDL_calloc(1, పరిమాణం(*దత్తాంశం_ఆధారం_2));
    ఒకవేళ (!దత్తాంశం_ఆధారం_2) {
        తిరిగి ఖాళీ;
    }

    నిర్మాణం wl_దత్తాంశం_ఆధారం *id = wl_దత్తాంశం_device_manager_create_దత్తాంశం_ఆధారం(video_దత్తాంశం->దత్తాంశం_device_manager);
    దత్తాంశం_ఆధారం_2->ఆధారం = id;
    wl_దత్తాంశం_ఆధారం_సమితి_user_దత్తాంశం(id, దత్తాంశం_ఆధారం_2);
    wl_దత్తాంశం_ఆధారం_కూడు_listener(id, &దత్తాంశం_ఆధారం_listener, దత్తాంశం_ఆధారం_2);

    తిరిగి దత్తాంశం_ఆధారం_2;
}

స్థిర శూన్య primary_selection_ఆధారం_send(శూన్య *దత్తాంశం, నిర్మాణం zwp_primary_selection_ఆధారం_v1 *zwp_primary_selection_ఆధారం_v1, స్థిరరాశి అక్షరం *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_ఆధారం_Send((SDL_Wayland_Primary_Selection_ఆధారం *)దత్తాంశం, mime_type, fd);
}

స్థిర శూన్య primary_selection_ఆధారం_cancelled(శూన్య *దత్తాంశం, నిర్మాణం zwp_primary_selection_ఆధారం_v1 *zwp_primary_selection_ఆధారం_v1)
{
    Wayland_Primary_Selection_ఆధారం_Destroy(దత్తాంశం);
}

స్థిర స్థిరరాశి నిర్మాణం zwp_primary_selection_ఆధారం_v1_listener primary_selection_ఆధారం_listener = {
    primary_selection_ఆధారం_send,
    primary_selection_ఆధారం_cancelled,
};

SDL_Wayland_Primary_Selection_ఆధారం *Wayland_Primary_Selection_ఆధారం_Create(SDL_Video_దత్తాంశం *video_దత్తాంశం)
{
    SDL_Wayland_Primary_Selection_ఆధారం *primary_selection_ఆధారం = SDL_calloc(1, పరిమాణం(*primary_selection_ఆధారం));
    ఒకవేళ (!primary_selection_ఆధారం) {
        తిరిగి ఖాళీ;
    }

    నిర్మాణం zwp_primary_selection_ఆధారం_v1 *id = zwp_primary_selection_device_manager_v1_create_ఆధారం(video_దత్తాంశం->primary_selection_device_manager);
    primary_selection_ఆధారం->ఆధారం = id;
    zwp_primary_selection_ఆధారం_v1_కూడు_listener(id, &primary_selection_ఆధారం_listener, primary_selection_ఆధారం);

    తిరిగి primary_selection_ఆధారం;
}

స్థిర size_t Send_దత్తాంశం(స్థిరరాశి శూన్య *దత్తాంశం, size_t నిడివి, పూర్ణాంకం fd)
{
    size_t ఫలితం = 0;

    ఒకవేళ (నిడివి > 0 && దత్తాంశం) {
        అయితే (WritePipe(fd, దత్తాంశం, నిడివి, &ఫలితం) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    తిరిగి ఫలితం;
}

ssize_t Wayland_దత్తాంశం_ఆధారం_Send(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, పూర్ణాంకం fd)
{
    స్థిరరాశి శూన్య *దత్తాంశం = ఖాళీ;
    size_t నిడివి = 0;

    ఒకవేళ (SDL_strcmp(mime_type, SDL_దత్తాంశం_ORIGIN_MIME) == 0) {
        దత్తాంశం = ఆధారం->దత్తాంశం_device->id_str;
        నిడివి = SDL_strlen(ఆధారం->దత్తాంశం_device->id_str);
    } లేకపోతే ఒకవేళ (ఆధారం->దత్తాంశం_callback) {
        దత్తాంశం = ఆధారం->దత్తాంశం_callback(ఆధారం->userdata.దత్తాంశం, mime_type, &నిడివి);
    }

    తిరిగి Send_దత్తాంశం(దత్తాంశం, నిడివి, fd);
}

ssize_t Wayland_Primary_Selection_ఆధారం_Send(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, పూర్ణాంకం fd)
{
    స్థిరరాశి శూన్య *దత్తాంశం = ఖాళీ;
    size_t నిడివి = 0;

    ఒకవేళ (ఆధారం->దత్తాంశం_callback) {
        దత్తాంశం = ఆధారం->దత్తాంశం_callback(ఆధారం->userdata.దత్తాంశం, mime_type, &నిడివి);
    }

    తిరిగి Send_దత్తాంశం(దత్తాంశం, నిడివి, fd);
}

శూన్య Wayland_దత్తాంశం_ఆధారం_సమితి_Callback(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, SDL_Clipboard_దత్తాంశం_Callback దత్తాంశం_callback, SDL_ClipboardCleanupCallback cleanup_callback, శూన్య *userdata, Uint32 sequence)
{
    ఒకవేళ (ఆధారం) {
        ఆధారం->దత్తాంశం_callback = దత్తాంశం_callback;
        ఆధారం->cleanup_callback = cleanup_callback;
        ఆధారం->userdata.sequence = sequence;
        ఆధారం->userdata.దత్తాంశం = userdata;
    }
}

శూన్య Wayland_Primary_Selection_ఆధారం_సమితి_Callback(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, SDL_Clipboard_దత్తాంశం_Callback దత్తాంశం_callback, SDL_ClipboardCleanupCallback cleanup_callback, శూన్య *userdata)
{
    ఒకవేళ (ఆధారం) {
        ఆధారం->దత్తాంశం_callback = దత్తాంశం_callback;
        ఆధారం->cleanup_callback = cleanup_callback;
        ఆధారం->userdata.sequence = 0;
        ఆధారం->userdata.దత్తాంశం = userdata;
    }
}

స్థిర శూన్య *Clone_దత్తాంశం_బఫరు(స్థిరరాశి శూన్య *బఫరు_2, స్థిరరాశి size_t *len)
{
    శూన్య *clone = ఖాళీ;
    ఒకవేళ (*len > 0 && బఫరు_2) {
        clone = SDL_malloc((*len)+పరిమాణం(Uint32));
        ఒకవేళ (clone) {
            SDL_memcpy(clone, బఫరు_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, పరిమాణం(Uint32));
        }
    }
    తిరిగి clone;
}

శూన్య *Wayland_దత్తాంశం_ఆధారం_Get_దత్తాంశం(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి)
{
    శూన్య *బఫరు_2 = ఖాళీ;
    *నిడివి = 0;

    ఒకవేళ (!ఆధారం) {
        SDL_సమితి_Error("Invalid data source");
    } లేకపోతే ఒకవేళ (ఆధారం->దత్తాంశం_callback) {
        స్థిరరాశి శూన్య *అంతర్గత_బఫరు = ఆధారం->దత్తాంశం_callback(ఆధారం->userdata.దత్తాంశం, mime_type, నిడివి);
        బఫరు_2 = Clone_దత్తాంశం_బఫరు(అంతర్గత_బఫరు, నిడివి);
    }

    తిరిగి బఫరు_2;
}

శూన్య *Wayland_Primary_Selection_ఆధారం_Get_దత్తాంశం(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి)
{
    శూన్య *బఫరు_2 = ఖాళీ;
    *నిడివి = 0;

    ఒకవేళ (!ఆధారం) {
        SDL_సమితి_Error("Invalid primary selection source");
    } లేకపోతే ఒకవేళ (ఆధారం->దత్తాంశం_callback) {
        స్థిరరాశి శూన్య *అంతర్గత_బఫరు = ఆధారం->దత్తాంశం_callback(ఆధారం->userdata.దత్తాంశం, mime_type, నిడివి);
        బఫరు_2 = Clone_దత్తాంశం_బఫరు(అంతర్గత_బఫరు, నిడివి);
    }

    తిరిగి బఫరు_2;
}

శూన్య Wayland_దత్తాంశం_ఆధారం_Destroy(SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం)
{
    ఒకవేళ (ఆధారం) {
        SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = ఆధారం->దత్తాంశం_device;
        ఒకవేళ (దత్తాంశం_device && (దత్తాంశం_device->selection_ఆధారం == ఆధారం)) {
            దత్తాంశం_device->selection_ఆధారం = ఖాళీ;
        }
        wl_దత్తాంశం_ఆధారం_destroy(ఆధారం->ఆధారం);
        ఒకవేళ (ఆధారం->userdata.sequence) {
            SDL_Cancel_Clipboard_దత్తాంశం(ఆధారం->userdata.sequence);
        } లేకపోతే ఒకవేళ (ఆధారం->cleanup_callback) {
            ఆధారం->cleanup_callback(ఆధారం->userdata.దత్తాంశం);
        }
        SDL_free(ఆధారం);
    }
}

శూన్య Wayland_Primary_Selection_ఆధారం_Destroy(SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం)
{
    ఒకవేళ (ఆధారం) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = ఆధారం->primary_selection_device;
        ఒకవేళ (primary_selection_device && (primary_selection_device->selection_ఆధారం == ఆధారం)) {
            primary_selection_device->selection_ఆధారం = ఖాళీ;
        }
        zwp_primary_selection_ఆధారం_v1_destroy(ఆధారం->ఆధారం);
        ఒకవేళ (ఆధారం->cleanup_callback) {
            ఆధారం->cleanup_callback(ఆధారం->userdata.దత్తాంశం);
        }
        SDL_free(ఆధారం);
    }
}

స్థిర శూన్య SelectionOfferNotifyFromMIMEs(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device, bool check_origin);

స్థిర శూన్య offer_ఆధారం_పూర్తి_handler(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *callback, uint32_t callback_దత్తాంశం)
{
    ఒకవేళ (!callback) {
        తిరిగి;
    }

    SDL_Wayland_దత్తాంశం_Offer *offer = (SDL_Wayland_దత్తాంశం_Offer *)దత్తాంశం;
    అక్షరం *id = ఖాళీ;
    size_t నిడివి = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ఖాళీ;

    అయితే (ReadPipe(offer->read_fd, (శూన్య **)&id, &నిడివి, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    ఒకవేళ (id) {
        స్థిరరాశి bool ఆధారం_is_external = SDL_strncmp(offer->దత్తాంశం_device->id_str, id, నిడివి) != 0;
        SDL_free(id);
        ఒకవేళ (ఆధారం_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->దత్తాంశం_device, false);
        } లేకపోతే {
            // Recursive data offer; just destroy it.
            SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = offer->దత్తాంశం_device;
            Wayland_దత్తాంశం_Offer_Destroy(offer);
            దత్తాంశం_device->selection_offer = ఖాళీ;
        }
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener offer_ఆధారం_listener = {
    offer_ఆధారం_పూర్తి_handler
};

స్థిర శూన్య UpdateSeatOffers(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device)
{
    SDL_WaylandSeat *offer_seat = దత్తాంశం_device->seat;
    SDL_Video_దత్తాంశం *video_దత్తాంశం = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_దత్తాంశం->seat_list, link) {
        ఒకవేళ (s->దత్తాంశం_device) {
            Wayland_దత్తాంశం_ఆధారం_Destroy(s->దత్తాంశం_device->selection_ఆధారం);
            s->దత్తాంశం_device->selection_ఆధారం = ఖాళీ;

            // Don't clear the offer that is about to be set.
            ఒకవేళ (s != offer_seat) {
                Wayland_దత్తాంశం_Offer_Destroy(s->దత్తాంశం_device->selection_offer);
                s->దత్తాంశం_device->selection_offer = ఖాళీ;
            }
        }
    }

    video_దత్తాంశం->current_దత్తాంశం_offer_seat = offer_seat;
}

స్థిర శూన్య SelectionOfferNotifyFromMIMEs(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device, bool check_origin)
{
    SDL_Wayland_దత్తాంశం_Offer *offer = దత్తాంశం_device->selection_offer;
    అక్షరం **new_mime_types = ఖాళీ;
    size_t అంకె_formats = 0;

    ఒకవేళ (offer) {
        size_t alloc_కొలత_2 = 0;

        // Do a first pass to compute allocation size.
        స్థిరరాశి అక్షరం **అంశం;
        wl_array_for_each(అంశం, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            ఒకవేళ (check_origin && SDL_strcmp(*అంశం, SDL_దత్తాంశం_ORIGIN_MIME) == 0) {
                Wayland_దత్తాంశం_Offer_Request_దత్తాంశం_From_Self(offer, *అంశం, &offer_ఆధారం_listener, offer);
                తిరిగి;
            }

            ++అంకె_formats;
            alloc_కొలత_2 += SDL_strlen(*అంశం) + 1;
        }

        alloc_కొలత_2 += (అంకె_formats + 1) * పరిమాణం(అక్షరం *);

        new_mime_types = SDL_Allocate_Temporary_జ్ఞాపకం(alloc_కొలత_2);
        ఒకవేళ (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_ఆదానం, "unable to allocate new_mime_types");
            తిరిగి;
        }

        // Second pass to fill.
        అక్షరం *strPtr = (అక్షరం *)(new_mime_types + అంకె_formats + 1);
        alloc_కొలత_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        అంశం = ఖాళీ;
        పూర్ణాంకం i = 0;
        wl_array_for_each(అంశం, &offer->mimes) {
            ఒకవేళ (!అంశం) {
                కొనసాగు;
            }

            new_mime_types[i++] = strPtr;
            స్థిరరాశి size_t len = SDL_strlcpy(strPtr, *అంశం, alloc_కొలత_2) + 1;
            strPtr += len;
            alloc_కొలత_2 -= len;
        }
        new_mime_types[అంకె_formats] = ఖాళీ;
    }

    UpdateSeatOffers(దత్తాంశం_device);
    SDL_SendClipboardUpdate(false, new_mime_types, అంకె_formats);
}

శూన్య Wayland_దత్తాంశం_Device_సమితి_Selection_Offer(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device, SDL_Wayland_దత్తాంశం_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    స్థిరరాశి bool notify = offer || (!offer && దత్తాంశం_device->selection_offer && (!దత్తాంశం_device->selection_offer->callback || !దత్తాంశం_device->selection_ఆధారం));
    Wayland_దత్తాంశం_Offer_Destroy(దత్తాంశం_device->selection_offer);
    దత్తాంశం_device->selection_offer = offer;
    ఒకవేళ (notify) {
        SelectionOfferNotifyFromMIMEs(దత్తాంశం_device, true);
    }
}

శూన్య *Wayland_దత్తాంశం_Offer_Get_దత్తాంశం_From_Self(SDL_Wayland_దత్తాంశం_Offer *offer, size_t *నిడివి)
{
    ఒకవేళ (!offer) {
        SDL_సమితి_Error("Invalid data offer");
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (offer->read_fd < 0) {
        SDL_సమితి_Error("Pipe closed");
        తిరిగి ఖాళీ;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    శూన్య *బఫరు_2 = ఖాళీ;
    అయితే (ReadPipe(offer->read_fd, &బఫరు_2, నిడివి, 0) > 0) {
    }

    తిరిగి బఫరు_2;
}

bool Wayland_దత్తాంశం_Offer_Request_దత్తాంశం_From_Self(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type, స్థిరరాశి నిర్మాణం wl_callback_listener *completion_listener, శూన్య *userdata)
{
    పూర్ణాంకం pipefd[2];

    ఒకవేళ (!offer) {
        SDL_సమితి_Error("Invalid data offer");
        తిరిగి false;
    }

    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = offer->దత్తాంశం_device;
    ఒకవేళ (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    ఒకవేళ (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ఖాళీ;
    }

    ఒకవేళ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_దత్తాంశం_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(దత్తాంశం_device->seat->display->display);
        wl_callback_కూడు_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(దత్తాంశం_device->seat->display->display);
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("Could not create pipe");
    }

    తిరిగి true;
}

శూన్య *Wayland_దత్తాంశం_Offer_Receive(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి)
{
    పూర్ణాంకం pipefd[2];
    శూన్య *బఫరు_2 = ఖాళీ;
    *నిడివి = 0;

    ఒకవేళ (!offer) {
        SDL_సమితి_Error("Invalid data offer");
        తిరిగి ఖాళీ;
    }

    SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device = offer->దత్తాంశం_device;

    ఒకవేళ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_దత్తాంశం_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(దత్తాంశం_device->seat->display->display);

        అయితే (ReadPipe(pipefd[0], &బఫరు_2, నిడివి, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } లేకపోతే {
        SDL_సమితి_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *నిడివి, బఫరు_2);

    తిరిగి బఫరు_2;
}

శూన్య *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, స్థిరరాశి అక్షరం *mime_type, size_t *నిడివి)
{
    పూర్ణాంకం pipefd[2];
    శూన్య *బఫరు_2 = ఖాళీ;
    *నిడివి = 0;

    ఒకవేళ (!offer) {
        SDL_సమితి_Error("Invalid data offer");
        తిరిగి ఖాళీ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    ఒకవేళ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        అయితే (ReadPipe(pipefd[0], &బఫరు_2, నిడివి, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } లేకపోతే {
        SDL_సమితి_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ఆదానం,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *నిడివి, బఫరు_2);

    తిరిగి బఫరు_2;
}

bool Wayland_దత్తాంశం_Offer_కూడు_MIME(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type)
{
    తిరిగి MIMEData_List_కూడు(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_కూడు_MIME(SDL_WaylandPrimarySelectionOffer *offer, స్థిరరాశి అక్షరం *mime_type)
{
    తిరిగి MIMEData_List_కూడు(&offer->mimes, mime_type);
}

bool Wayland_దత్తాంశం_Offer_Has_MIME(SDL_Wayland_దత్తాంశం_Offer *offer, స్థిరరాశి అక్షరం *mime_type)
{
    ఒకవేళ (offer && mime_type) {
        తిరిగి MIMEDataListHasType(&offer->mimes, mime_type);
    }
    తిరిగి false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, స్థిరరాశి అక్షరం *mime_type)
{
    ఒకవేళ (offer && mime_type) {
        తిరిగి MIMEDataListHasType(&offer->mimes, mime_type);
    }
    తిరిగి false;
}

శూన్య Wayland_దత్తాంశం_Offer_Destroy(SDL_Wayland_దత్తాంశం_Offer *offer)
{
    ఒకవేళ (offer) {
        ఒకవేళ (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        ఒకవేళ (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_దత్తాంశం_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

శూన్య Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    ఒకవేళ (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_దత్తాంశం_Device_సమితి_Selection_ఆధారం(SDL_Wayland_దత్తాంశం_Device *దత్తాంశం_device, SDL_Wayland_దత్తాంశం_ఆధారం *ఆధారం, స్థిరరాశి అక్షరం **mime_types, size_t mime_లెక్క)
{
    ఒకవేళ (!దత్తాంశం_device) {
        తిరిగి SDL_సమితి_Error("Invalid Data Device");
    }
    ఒకవేళ (!ఆధారం) {
        తిరిగి SDL_సమితి_Error("Invalid source");
    }

    ఒకవేళ (mime_లెక్క) {
        కొరకు (size_t సూచీ = 0; సూచీ < mime_లెక్క; ++సూచీ) {
            స్థిరరాశి అక్షరం *mime_type = mime_types[సూచీ];
            wl_దత్తాంశం_ఆధారం_offer(ఆధారం->ఆధారం, mime_type);
        }

        // Advertise the data origin MIME
        wl_దత్తాంశం_ఆధారం_offer(ఆధారం->ఆధారం, SDL_దత్తాంశం_ORIGIN_MIME);

        wl_దత్తాంశం_device_సమితి_selection(దత్తాంశం_device->దత్తాంశం_device, ఆధారం->ఆధారం, దత్తాంశం_device->seat->చివరి_implicit_grab_serial);
        ఒకవేళ (దత్తాంశం_device->selection_ఆధారం) {
            Wayland_దత్తాంశం_ఆధారం_Destroy(దత్తాంశం_device->selection_ఆధారం);
        }
        దత్తాంశం_device->selection_ఆధారం = ఆధారం;
        ఆధారం->దత్తాంశం_device = దత్తాంశం_device;

    } లేకపోతే {
        Wayland_దత్తాంశం_ఆధారం_Destroy(దత్తాంశం_device->selection_ఆధారం);
        దత్తాంశం_device->selection_ఆధారం = ఖాళీ;
        తిరిగి SDL_సమితి_Error("No mime data");
    }

    తిరిగి true;
}

bool Wayland_Primary_Selection_Device_సమితి_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_ఆధారం *ఆధారం,
                                                స్థిరరాశి అక్షరం *స్థిరరాశి *mime_types, size_t mime_లెక్క)
{
    ఒకవేళ (!primary_selection_device) {
        తిరిగి SDL_సమితి_Error("Invalid Primary Selection Device");
    }
    ఒకవేళ (!ఆధారం) {
        తిరిగి SDL_సమితి_Error("Invalid source");
    }

    ఒకవేళ (mime_లెక్క) {
        కొరకు (size_t సూచీ = 0; సూచీ < mime_లెక్క; ++సూచీ) {
            స్థిరరాశి అక్షరం *mime_type = mime_types[సూచీ];
            zwp_primary_selection_ఆధారం_v1_offer(ఆధారం->ఆధారం, mime_type);
        }

        zwp_primary_selection_device_v1_సమితి_selection(primary_selection_device->primary_selection_device,
                                                      ఆధారం->ఆధారం,
                                                      primary_selection_device->seat->చివరి_implicit_grab_serial);
        ఒకవేళ (primary_selection_device->selection_ఆధారం) {
            Wayland_Primary_Selection_ఆధారం_Destroy(primary_selection_device->selection_ఆధారం);
        }
        primary_selection_device->selection_ఆధారం = ఆధారం;
        ఆధారం->primary_selection_device = primary_selection_device;
    } లేకపోతే {
        Wayland_Primary_Selection_ఆధారం_Destroy(primary_selection_device->selection_ఆధారం);
        primary_selection_device->selection_ఆధారం = ఖాళీ;
        తిరిగి SDL_సమితి_Error("No mime data");
    }

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND

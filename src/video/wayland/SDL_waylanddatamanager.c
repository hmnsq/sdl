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

#شامل <fcntl.h>
#شامل <unistd.h>
#شامل <limits.h>
#شامل <signal.h>

#شامل "../../core/unix/SDL_poll.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../SDL_clipboard_c.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylanddatamanager.h"
#شامل "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#تعریف_کرو DEFAULT_PIPE_TIMEOUT_NS SDL_MS_مقصد_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#اگر_غیر_تعریف_شدہ HAVE_SIGTIMEDWAIT
#شامل <errno.h>
#شامل <time.h>
ساکن صحیح sigtimedwait(ثابت sigset_t *سیٹ, siginfo_t *info, ثابت ساخت timespec *timeout)
{
    ساخت timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    کرو {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        برائے (صحیح signo = 1; signo < NSIG; ++signo) {
            اگر (sigismember(سیٹ, signo) && sigismember(&pending, signo)) {
                اگر (!sigwait(سیٹ, &signo)) {
                    اگر (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    واپس signo;
                } ورنہ {
                    واپس -1;
                }
            }
        }

        اگر (timeout->tv_sec || timeout->tv_nsec) {
            طویل ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ساخت timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } جب (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    واپس -1;
}
#اگر_ختم

ساکن ssize_t WritePipe(صحیح fd, ثابت خالی *بفر_2, size_t کل_لمبائی, size_t *pos)
{
    ssize_t بائٹیں_written = 0;
    ثابت ssize_t لمبائی = کل_لمبائی - *pos;

    sigset_t sig_سیٹ;
    sigset_t old_sig_سیٹ;
    ساخت timespec zerotime = { 0 };

    ثابت صحیح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_سیٹ);
    sigaddset(&sig_سیٹ, SIGPIPE);

#اگر_تعریف_شدہ SDL_دھاگے_DISABLED
    sigprocmask(SIG_BLOCK, &sig_سیٹ, &old_sig_سیٹ);
#ورنہ
    pthread_sigmask(SIG_BLOCK, &sig_سیٹ, &old_sig_سیٹ);
#اگر_ختم

    اگر (ready > 0) {
        اگر (لمبائی > 0) {
            بائٹیں_written = اكتب(fd, (Uint8 *)بفر_2 + *pos, SDL_min(لمبائی, PIPE_BUF));
        }

        اگر (بائٹیں_written > 0) {
            *pos += بائٹیں_written;
        }
    } ورنہ اگر (ready == 0) {
        SDL_سیٹ_Error("Pipe timeout");
    } ورنہ  {
        SDL_سیٹ_Error("Pipe poll error");
    }

    sigtimedwait(&sig_سیٹ, تہی, &zerotime);

#اگر_تعریف_شدہ SDL_دھاگے_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_سیٹ, تہی);
#ورنہ
    pthread_sigmask(SIG_SETMASK, &old_sig_سیٹ, تہی);
#اگر_ختم

    واپس بائٹیں_written;
}

ساکن ssize_t ReadPipe(صحیح fd, خالی **بفر_2, size_t *کل_لمبائی, Sint64 timeout_ns)
{
    خالی *output_بفر = تہی;
    حرف عارضی[PIPE_BUF];
    ssize_t بائٹیں_read = 0;

    ثابت صحیح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    اگر (ready > 0) {
        بائٹیں_read = اقرأ(fd, عارضی, حجم(عارضی));
    } ورنہ اگر (ready == 0) {
        SDL_سیٹ_Error("Pipe timeout");
    } ورنہ {
        SDL_سیٹ_Error("Pipe poll error");
    }

    اگر (بائٹیں_read > 0) {
        ثابت size_t pos = *کل_لمبائی;
        *کل_لمبائی += بائٹیں_read;

        ثابت size_t new_بفر_لمبائی = *کل_لمبائی + حجم(Uint32);

        اگر (!*بفر_2) {
            output_بفر = SDL_malloc(new_بفر_لمبائی);
        } ورنہ {
            output_بفر = SDL_realloc(*بفر_2, new_بفر_لمبائی);
        }

        اگر (!output_بفر) {
            بائٹیں_read = -1;
        } ورنہ {
            SDL_memcpy((Uint8 *)output_بفر + pos, عارضی, بائٹیں_read);
            SDL_memset((Uint8 *)output_بفر + (new_بفر_لمبائی - حجم(Uint32)), 0, حجم(Uint32));

            *بفر_2 = output_بفر;
        }
    }

    واپس بائٹیں_read;
}

ساکن bool MIMEDataListHasType(ساخت wl_array *list, ثابت حرف *mime_type)
{
    ثابت حرف **شے;
    wl_array_for_each(شے, list) {
        اگر (SDL_strcmp(*شے, mime_type) == 0) {
            واپس true;
        }
    }

    واپس false;
}

ساکن bool MIMEData_List_جوڑو(ساخت wl_array *list, ثابت حرف *mime_type)
{
    اگر (!MIMEDataListHasType(list, mime_type)) {
        حرف **شے = WAYLAND_wl_array_جوڑو(list, حجم(حرف *));
        *شے = SDL_strdup(mime_type);
    }

    واپس true;
}

ساکن خالی MIMEDataListFree(ساخت wl_array *list)
{
    حرف **شے;
    wl_array_for_each(شے, list) {
        SDL_free(*شے);
    }

    WAYLAND_wl_array_release(list);
}

ساکن خالی ڈیٹا_ماخذ_handle_ہدف(خالی *ڈیٹا, ساخت wl_ڈیٹا_ماخذ *wl_ڈیٹا_ماخذ, ثابت حرف *mime_type)
{
}

ساکن خالی ڈیٹا_ماخذ_handle_send(خالی *ڈیٹا, ساخت wl_ڈیٹا_ماخذ *wl_ڈیٹا_ماخذ, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_ڈیٹا_ماخذ_Send((SDL_Wayland_ڈیٹا_ماخذ *)ڈیٹا, mime_type, fd);
}

ساکن خالی ڈیٹا_ماخذ_handle_cancelled(خالی *ڈیٹا, ساخت wl_ڈیٹا_ماخذ *wl_ڈیٹا_ماخذ)
{
    SDL_Wayland_ڈیٹا_ماخذ *ماخذ = ڈیٹا;
    اگر (ماخذ) {
        Wayland_ڈیٹا_ماخذ_Destroy(ماخذ);
    }
}

ساکن خالی ڈیٹا_ماخذ_handle_dnd_drop_performed(خالی *ڈیٹا, ساخت wl_ڈیٹا_ماخذ *wl_ڈیٹا_ماخذ)
{
}

ساکن خالی ڈیٹا_ماخذ_handle_dnd_ختم_شدہ(خالی *ڈیٹا, ساخت wl_ڈیٹا_ماخذ *wl_ڈیٹا_ماخذ)
{
    SDL_Wayland_ڈیٹا_ماخذ *ماخذ = ڈیٹا;
    اگر (ماخذ) {
        Wayland_ڈیٹا_ماخذ_Destroy(ماخذ);
    }
}

ساکن خالی ڈیٹا_ماخذ_handle_action(خالی *ڈیٹا, ساخت wl_ڈیٹا_ماخذ *wl_ڈیٹا_ماخذ, uint32_t dnd_action)
{
}

ساکن ثابت ساخت wl_ڈیٹا_ماخذ_listener ڈیٹا_ماخذ_listener = {
    ڈیٹا_ماخذ_handle_ہدف,
    ڈیٹا_ماخذ_handle_send,
    ڈیٹا_ماخذ_handle_cancelled,
    ڈیٹا_ماخذ_handle_dnd_drop_performed, // Version 3
    ڈیٹا_ماخذ_handle_dnd_ختم_شدہ,       // Version 3
    ڈیٹا_ماخذ_handle_action,             // Version 3
};

SDL_Wayland_ڈیٹا_ماخذ *Wayland_ڈیٹا_ماخذ_Create(SDL_Video_ڈیٹا *video_ڈیٹا)
{
    SDL_Wayland_ڈیٹا_ماخذ *ڈیٹا_ماخذ_2 = SDL_calloc(1, حجم(*ڈیٹا_ماخذ_2));
    اگر (!ڈیٹا_ماخذ_2) {
        واپس تہی;
    }

    ساخت wl_ڈیٹا_ماخذ *id = wl_ڈیٹا_device_manager_create_ڈیٹا_ماخذ(video_ڈیٹا->ڈیٹا_device_manager);
    ڈیٹا_ماخذ_2->ماخذ = id;
    wl_ڈیٹا_ماخذ_سیٹ_user_ڈیٹا(id, ڈیٹا_ماخذ_2);
    wl_ڈیٹا_ماخذ_جوڑو_listener(id, &ڈیٹا_ماخذ_listener, ڈیٹا_ماخذ_2);

    واپس ڈیٹا_ماخذ_2;
}

ساکن خالی primary_selection_ماخذ_send(خالی *ڈیٹا, ساخت zwp_primary_selection_ماخذ_v1 *zwp_primary_selection_ماخذ_v1, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_ماخذ_Send((SDL_Wayland_Primary_Selection_ماخذ *)ڈیٹا, mime_type, fd);
}

ساکن خالی primary_selection_ماخذ_cancelled(خالی *ڈیٹا, ساخت zwp_primary_selection_ماخذ_v1 *zwp_primary_selection_ماخذ_v1)
{
    Wayland_Primary_Selection_ماخذ_Destroy(ڈیٹا);
}

ساکن ثابت ساخت zwp_primary_selection_ماخذ_v1_listener primary_selection_ماخذ_listener = {
    primary_selection_ماخذ_send,
    primary_selection_ماخذ_cancelled,
};

SDL_Wayland_Primary_Selection_ماخذ *Wayland_Primary_Selection_ماخذ_Create(SDL_Video_ڈیٹا *video_ڈیٹا)
{
    SDL_Wayland_Primary_Selection_ماخذ *primary_selection_ماخذ = SDL_calloc(1, حجم(*primary_selection_ماخذ));
    اگر (!primary_selection_ماخذ) {
        واپس تہی;
    }

    ساخت zwp_primary_selection_ماخذ_v1 *id = zwp_primary_selection_device_manager_v1_create_ماخذ(video_ڈیٹا->primary_selection_device_manager);
    primary_selection_ماخذ->ماخذ = id;
    zwp_primary_selection_ماخذ_v1_جوڑو_listener(id, &primary_selection_ماخذ_listener, primary_selection_ماخذ);

    واپس primary_selection_ماخذ;
}

ساکن size_t Send_ڈیٹا(ثابت خالی *ڈیٹا, size_t لمبائی, صحیح fd)
{
    size_t نتیجہ = 0;

    اگر (لمبائی > 0 && ڈیٹا) {
        جب (WritePipe(fd, ڈیٹا, لمبائی, &نتیجہ) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    واپس نتیجہ;
}

ssize_t Wayland_ڈیٹا_ماخذ_Send(SDL_Wayland_ڈیٹا_ماخذ *ماخذ, ثابت حرف *mime_type, صحیح fd)
{
    ثابت خالی *ڈیٹا = تہی;
    size_t لمبائی = 0;

    اگر (SDL_strcmp(mime_type, SDL_ڈیٹا_ORIGIN_MIME) == 0) {
        ڈیٹا = ماخذ->ڈیٹا_device->id_str;
        لمبائی = SDL_strlen(ماخذ->ڈیٹا_device->id_str);
    } ورنہ اگر (ماخذ->ڈیٹا_callback) {
        ڈیٹا = ماخذ->ڈیٹا_callback(ماخذ->userdata.ڈیٹا, mime_type, &لمبائی);
    }

    واپس Send_ڈیٹا(ڈیٹا, لمبائی, fd);
}

ssize_t Wayland_Primary_Selection_ماخذ_Send(SDL_Wayland_Primary_Selection_ماخذ *ماخذ, ثابت حرف *mime_type, صحیح fd)
{
    ثابت خالی *ڈیٹا = تہی;
    size_t لمبائی = 0;

    اگر (ماخذ->ڈیٹا_callback) {
        ڈیٹا = ماخذ->ڈیٹا_callback(ماخذ->userdata.ڈیٹا, mime_type, &لمبائی);
    }

    واپس Send_ڈیٹا(ڈیٹا, لمبائی, fd);
}

خالی Wayland_ڈیٹا_ماخذ_سیٹ_Callback(SDL_Wayland_ڈیٹا_ماخذ *ماخذ, SDL_Clipboard_ڈیٹا_Callback ڈیٹا_callback, SDL_ClipboardCleanupCallback cleanup_callback, خالی *userdata, Uint32 sequence)
{
    اگر (ماخذ) {
        ماخذ->ڈیٹا_callback = ڈیٹا_callback;
        ماخذ->cleanup_callback = cleanup_callback;
        ماخذ->userdata.sequence = sequence;
        ماخذ->userdata.ڈیٹا = userdata;
    }
}

خالی Wayland_Primary_Selection_ماخذ_سیٹ_Callback(SDL_Wayland_Primary_Selection_ماخذ *ماخذ, SDL_Clipboard_ڈیٹا_Callback ڈیٹا_callback, SDL_ClipboardCleanupCallback cleanup_callback, خالی *userdata)
{
    اگر (ماخذ) {
        ماخذ->ڈیٹا_callback = ڈیٹا_callback;
        ماخذ->cleanup_callback = cleanup_callback;
        ماخذ->userdata.sequence = 0;
        ماخذ->userdata.ڈیٹا = userdata;
    }
}

ساکن خالی *Clone_ڈیٹا_بفر(ثابت خالی *بفر_2, ثابت size_t *len)
{
    خالی *clone = تہی;
    اگر (*len > 0 && بفر_2) {
        clone = SDL_malloc((*len)+حجم(Uint32));
        اگر (clone) {
            SDL_memcpy(clone, بفر_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, حجم(Uint32));
        }
    }
    واپس clone;
}

خالی *Wayland_ڈیٹا_ماخذ_Get_ڈیٹا(SDL_Wayland_ڈیٹا_ماخذ *ماخذ, ثابت حرف *mime_type, size_t *لمبائی)
{
    خالی *بفر_2 = تہی;
    *لمبائی = 0;

    اگر (!ماخذ) {
        SDL_سیٹ_Error("Invalid data source");
    } ورنہ اگر (ماخذ->ڈیٹا_callback) {
        ثابت خالی *اندرونی_بفر = ماخذ->ڈیٹا_callback(ماخذ->userdata.ڈیٹا, mime_type, لمبائی);
        بفر_2 = Clone_ڈیٹا_بفر(اندرونی_بفر, لمبائی);
    }

    واپس بفر_2;
}

خالی *Wayland_Primary_Selection_ماخذ_Get_ڈیٹا(SDL_Wayland_Primary_Selection_ماخذ *ماخذ, ثابت حرف *mime_type, size_t *لمبائی)
{
    خالی *بفر_2 = تہی;
    *لمبائی = 0;

    اگر (!ماخذ) {
        SDL_سیٹ_Error("Invalid primary selection source");
    } ورنہ اگر (ماخذ->ڈیٹا_callback) {
        ثابت خالی *اندرونی_بفر = ماخذ->ڈیٹا_callback(ماخذ->userdata.ڈیٹا, mime_type, لمبائی);
        بفر_2 = Clone_ڈیٹا_بفر(اندرونی_بفر, لمبائی);
    }

    واپس بفر_2;
}

خالی Wayland_ڈیٹا_ماخذ_Destroy(SDL_Wayland_ڈیٹا_ماخذ *ماخذ)
{
    اگر (ماخذ) {
        SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = ماخذ->ڈیٹا_device;
        اگر (ڈیٹا_device && (ڈیٹا_device->selection_ماخذ == ماخذ)) {
            ڈیٹا_device->selection_ماخذ = تہی;
        }
        wl_ڈیٹا_ماخذ_destroy(ماخذ->ماخذ);
        اگر (ماخذ->userdata.sequence) {
            SDL_Cancel_Clipboard_ڈیٹا(ماخذ->userdata.sequence);
        } ورنہ اگر (ماخذ->cleanup_callback) {
            ماخذ->cleanup_callback(ماخذ->userdata.ڈیٹا);
        }
        SDL_free(ماخذ);
    }
}

خالی Wayland_Primary_Selection_ماخذ_Destroy(SDL_Wayland_Primary_Selection_ماخذ *ماخذ)
{
    اگر (ماخذ) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = ماخذ->primary_selection_device;
        اگر (primary_selection_device && (primary_selection_device->selection_ماخذ == ماخذ)) {
            primary_selection_device->selection_ماخذ = تہی;
        }
        zwp_primary_selection_ماخذ_v1_destroy(ماخذ->ماخذ);
        اگر (ماخذ->cleanup_callback) {
            ماخذ->cleanup_callback(ماخذ->userdata.ڈیٹا);
        }
        SDL_free(ماخذ);
    }
}

ساکن خالی SelectionOfferNotifyFromMIMEs(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device, bool check_origin);

ساکن خالی offer_ماخذ_مکمل_handler(خالی *ڈیٹا, ساخت wl_callback *callback, uint32_t callback_ڈیٹا)
{
    اگر (!callback) {
        واپس;
    }

    SDL_Wayland_ڈیٹا_Offer *offer = (SDL_Wayland_ڈیٹا_Offer *)ڈیٹا;
    حرف *id = تہی;
    size_t لمبائی = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = تہی;

    جب (ReadPipe(offer->read_fd, (خالی **)&id, &لمبائی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    اگر (id) {
        ثابت bool ماخذ_is_external = SDL_strncmp(offer->ڈیٹا_device->id_str, id, لمبائی) != 0;
        SDL_free(id);
        اگر (ماخذ_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->ڈیٹا_device, false);
        } ورنہ {
            // Recursive data offer; just destroy it.
            SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = offer->ڈیٹا_device;
            Wayland_ڈیٹا_Offer_Destroy(offer);
            ڈیٹا_device->selection_offer = تہی;
        }
    }
}

ساکن ثابت ساخت wl_callback_listener offer_ماخذ_listener = {
    offer_ماخذ_مکمل_handler
};

ساکن خالی UpdateSeatOffers(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device)
{
    SDL_WaylandSeat *offer_seat = ڈیٹا_device->seat;
    SDL_Video_ڈیٹا *video_ڈیٹا = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_ڈیٹا->seat_list, link) {
        اگر (s->ڈیٹا_device) {
            Wayland_ڈیٹا_ماخذ_Destroy(s->ڈیٹا_device->selection_ماخذ);
            s->ڈیٹا_device->selection_ماخذ = تہی;

            // Don't clear the offer that is about to be set.
            اگر (s != offer_seat) {
                Wayland_ڈیٹا_Offer_Destroy(s->ڈیٹا_device->selection_offer);
                s->ڈیٹا_device->selection_offer = تہی;
            }
        }
    }

    video_ڈیٹا->current_ڈیٹا_offer_seat = offer_seat;
}

ساکن خالی SelectionOfferNotifyFromMIMEs(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device, bool check_origin)
{
    SDL_Wayland_ڈیٹا_Offer *offer = ڈیٹا_device->selection_offer;
    حرف **new_mime_types = تہی;
    size_t عدد_formats = 0;

    اگر (offer) {
        size_t alloc_سائز_2 = 0;

        // Do a first pass to compute allocation size.
        ثابت حرف **شے;
        wl_array_for_each(شے, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            اگر (check_origin && SDL_strcmp(*شے, SDL_ڈیٹا_ORIGIN_MIME) == 0) {
                Wayland_ڈیٹا_Offer_Request_ڈیٹا_From_Self(offer, *شے, &offer_ماخذ_listener, offer);
                واپس;
            }

            ++عدد_formats;
            alloc_سائز_2 += SDL_strlen(*شے) + 1;
        }

        alloc_سائز_2 += (عدد_formats + 1) * حجم(حرف *);

        new_mime_types = SDL_Allocate_Temporary_حافظہ(alloc_سائز_2);
        اگر (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_داخلہ, "unable to allocate new_mime_types");
            واپس;
        }

        // Second pass to fill.
        حرف *strPtr = (حرف *)(new_mime_types + عدد_formats + 1);
        alloc_سائز_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        شے = تہی;
        صحیح i = 0;
        wl_array_for_each(شے, &offer->mimes) {
            اگر (!شے) {
                جاری;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *شے, alloc_سائز_2) + 1;
            strPtr += len;
            alloc_سائز_2 -= len;
        }
        new_mime_types[عدد_formats] = تہی;
    }

    UpdateSeatOffers(ڈیٹا_device);
    SDL_SendClipboardUpdate(false, new_mime_types, عدد_formats);
}

خالی Wayland_ڈیٹا_Device_سیٹ_Selection_Offer(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device, SDL_Wayland_ڈیٹا_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && ڈیٹا_device->selection_offer && (!ڈیٹا_device->selection_offer->callback || !ڈیٹا_device->selection_ماخذ));
    Wayland_ڈیٹا_Offer_Destroy(ڈیٹا_device->selection_offer);
    ڈیٹا_device->selection_offer = offer;
    اگر (notify) {
        SelectionOfferNotifyFromMIMEs(ڈیٹا_device, true);
    }
}

خالی *Wayland_ڈیٹا_Offer_Get_ڈیٹا_From_Self(SDL_Wayland_ڈیٹا_Offer *offer, size_t *لمبائی)
{
    اگر (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        واپس تہی;
    }

    اگر (offer->read_fd < 0) {
        SDL_سیٹ_Error("Pipe closed");
        واپس تہی;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    خالی *بفر_2 = تہی;
    جب (ReadPipe(offer->read_fd, &بفر_2, لمبائی, 0) > 0) {
    }

    واپس بفر_2;
}

bool Wayland_ڈیٹا_Offer_Request_ڈیٹا_From_Self(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type, ثابت ساخت wl_callback_listener *completion_listener, خالی *userdata)
{
    صحیح pipefd[2];

    اگر (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        واپس false;
    }

    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = offer->ڈیٹا_device;
    اگر (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    اگر (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = تہی;
    }

    اگر (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_ڈیٹا_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(ڈیٹا_device->seat->display->display);
        wl_callback_جوڑو_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(ڈیٹا_device->seat->display->display);
    } ورنہ {
        واپس SDL_سیٹ_Error("Could not create pipe");
    }

    واپس true;
}

خالی *Wayland_ڈیٹا_Offer_Receive(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type, size_t *لمبائی)
{
    صحیح pipefd[2];
    خالی *بفر_2 = تہی;
    *لمبائی = 0;

    اگر (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        واپس تہی;
    }

    SDL_Wayland_ڈیٹا_Device *ڈیٹا_device = offer->ڈیٹا_device;

    اگر (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_ڈیٹا_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(ڈیٹا_device->seat->display->display);

        جب (ReadPipe(pipefd[0], &بفر_2, لمبائی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } ورنہ {
        SDL_سیٹ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *لمبائی, بفر_2);

    واپس بفر_2;
}

خالی *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *لمبائی)
{
    صحیح pipefd[2];
    خالی *بفر_2 = تہی;
    *لمبائی = 0;

    اگر (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        واپس تہی;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    اگر (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        جب (ReadPipe(pipefd[0], &بفر_2, لمبائی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } ورنہ {
        SDL_سیٹ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *لمبائی, بفر_2);

    واپس بفر_2;
}

bool Wayland_ڈیٹا_Offer_جوڑو_MIME(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type)
{
    واپس MIMEData_List_جوڑو(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_جوڑو_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    واپس MIMEData_List_جوڑو(&offer->mimes, mime_type);
}

bool Wayland_ڈیٹا_Offer_Has_MIME(SDL_Wayland_ڈیٹا_Offer *offer, ثابت حرف *mime_type)
{
    اگر (offer && mime_type) {
        واپس MIMEDataListHasType(&offer->mimes, mime_type);
    }
    واپس false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    اگر (offer && mime_type) {
        واپس MIMEDataListHasType(&offer->mimes, mime_type);
    }
    واپس false;
}

خالی Wayland_ڈیٹا_Offer_Destroy(SDL_Wayland_ڈیٹا_Offer *offer)
{
    اگر (offer) {
        اگر (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        اگر (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_ڈیٹا_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

خالی Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    اگر (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_ڈیٹا_Device_سیٹ_Selection_ماخذ(SDL_Wayland_ڈیٹا_Device *ڈیٹا_device, SDL_Wayland_ڈیٹا_ماخذ *ماخذ, ثابت حرف **mime_types, size_t mime_گنتی)
{
    اگر (!ڈیٹا_device) {
        واپس SDL_سیٹ_Error("Invalid Data Device");
    }
    اگر (!ماخذ) {
        واپس SDL_سیٹ_Error("Invalid source");
    }

    اگر (mime_گنتی) {
        برائے (size_t اشاریہ = 0; اشاریہ < mime_گنتی; ++اشاریہ) {
            ثابت حرف *mime_type = mime_types[اشاریہ];
            wl_ڈیٹا_ماخذ_offer(ماخذ->ماخذ, mime_type);
        }

        // Advertise the data origin MIME
        wl_ڈیٹا_ماخذ_offer(ماخذ->ماخذ, SDL_ڈیٹا_ORIGIN_MIME);

        wl_ڈیٹا_device_سیٹ_selection(ڈیٹا_device->ڈیٹا_device, ماخذ->ماخذ, ڈیٹا_device->seat->آخری_implicit_grab_serial);
        اگر (ڈیٹا_device->selection_ماخذ) {
            Wayland_ڈیٹا_ماخذ_Destroy(ڈیٹا_device->selection_ماخذ);
        }
        ڈیٹا_device->selection_ماخذ = ماخذ;
        ماخذ->ڈیٹا_device = ڈیٹا_device;

    } ورنہ {
        Wayland_ڈیٹا_ماخذ_Destroy(ڈیٹا_device->selection_ماخذ);
        ڈیٹا_device->selection_ماخذ = تہی;
        واپس SDL_سیٹ_Error("No mime data");
    }

    واپس true;
}

bool Wayland_Primary_Selection_Device_سیٹ_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_ماخذ *ماخذ,
                                                ثابت حرف *ثابت *mime_types, size_t mime_گنتی)
{
    اگر (!primary_selection_device) {
        واپس SDL_سیٹ_Error("Invalid Primary Selection Device");
    }
    اگر (!ماخذ) {
        واپس SDL_سیٹ_Error("Invalid source");
    }

    اگر (mime_گنتی) {
        برائے (size_t اشاریہ = 0; اشاریہ < mime_گنتی; ++اشاریہ) {
            ثابت حرف *mime_type = mime_types[اشاریہ];
            zwp_primary_selection_ماخذ_v1_offer(ماخذ->ماخذ, mime_type);
        }

        zwp_primary_selection_device_v1_سیٹ_selection(primary_selection_device->primary_selection_device,
                                                      ماخذ->ماخذ,
                                                      primary_selection_device->seat->آخری_implicit_grab_serial);
        اگر (primary_selection_device->selection_ماخذ) {
            Wayland_Primary_Selection_ماخذ_Destroy(primary_selection_device->selection_ماخذ);
        }
        primary_selection_device->selection_ماخذ = ماخذ;
        ماخذ->primary_selection_device = primary_selection_device;
    } ورنہ {
        Wayland_Primary_Selection_ماخذ_Destroy(primary_selection_device->selection_ماخذ);
        primary_selection_device->selection_ماخذ = تہی;
        واپس SDL_سیٹ_Error("No mime data");
    }

    واپس true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND

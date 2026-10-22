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

#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND

#ضمن <fcntl.h>
#ضمن <unistd.h>
#ضمن <limits.h>
#ضمن <signal.h>

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../SDL_clipboard_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandevents_c.h"
#ضمن "SDL_waylanddatamanager.h"
#ضمن "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#وصف_ڪريو DEFAULT_PIPE_TIMEOUT_NS SDL_MS_منزل_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#جيڪڏهن_وصف_نه_ٿيل HAVE_SIGTIMEDWAIT
#ضمن <errno.h>
#ضمن <time.h>
ساكن صحيح sigtimedwait(ثابت sigset_t *سيٽ, siginfo_t *info, ثابت بنية timespec *timeout)
{
    بنية timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    افعل {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        لكل (صحيح signo = 1; signo < NSIG; ++signo) {
            إذا (sigismember(سيٽ, signo) && sigismember(&pending, signo)) {
                إذا (!sigwait(سيٽ, &signo)) {
                    إذا (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    أرجع signo;
                } وإلا {
                    أرجع -1;
                }
            }
        }

        إذا (timeout->tv_sec || timeout->tv_nsec) {
            ڊگهو ns = 20000000L; // 2/100ths of a second
            nanosleep(&(بنية timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } طالما (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    أرجع -1;
}
#جيڪڏهن_پورو

ساكن ssize_t WritePipe(صحيح fd, ثابت فراغ *بفر_2, size_t ڪل_ڊيگهائي, size_t *pos)
{
    ssize_t بائيٽون_written = 0;
    ثابت ssize_t ڊيگهائي = ڪل_ڊيگهائي - *pos;

    sigset_t sig_سيٽ;
    sigset_t old_sig_سيٽ;
    بنية timespec zerotime = { 0 };

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_سيٽ);
    sigaddset(&sig_سيٽ, SIGPIPE);

#جيڪڏهن_وصف_ٿيل SDL_ڌاڳا_DISABLED
    sigprocmask(SIG_BLOCK, &sig_سيٽ, &old_sig_سيٽ);
#وإلا
    pthread_sigmask(SIG_BLOCK, &sig_سيٽ, &old_sig_سيٽ);
#جيڪڏهن_پورو

    إذا (ready > 0) {
        إذا (ڊيگهائي > 0) {
            بائيٽون_written = اكتب(fd, (Uint8 *)بفر_2 + *pos, SDL_min(ڊيگهائي, PIPE_BUF));
        }

        إذا (بائيٽون_written > 0) {
            *pos += بائيٽون_written;
        }
    } وإلا إذا (ready == 0) {
        SDL_سيٽ_Error("Pipe timeout");
    } وإلا  {
        SDL_سيٽ_Error("Pipe poll error");
    }

    sigtimedwait(&sig_سيٽ, عدم, &zerotime);

#جيڪڏهن_وصف_ٿيل SDL_ڌاڳا_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_سيٽ, عدم);
#وإلا
    pthread_sigmask(SIG_SETMASK, &old_sig_سيٽ, عدم);
#جيڪڏهن_پورو

    أرجع بائيٽون_written;
}

ساكن ssize_t ReadPipe(صحيح fd, فراغ **بفر_2, size_t *ڪل_ڊيگهائي, Sint64 timeout_ns)
{
    فراغ *output_بفر = عدم;
    حرف عارضي[PIPE_BUF];
    ssize_t بائيٽون_read = 0;

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    إذا (ready > 0) {
        بائيٽون_read = اقرأ(fd, عارضي, حجم(عارضي));
    } وإلا إذا (ready == 0) {
        SDL_سيٽ_Error("Pipe timeout");
    } وإلا {
        SDL_سيٽ_Error("Pipe poll error");
    }

    إذا (بائيٽون_read > 0) {
        ثابت size_t pos = *ڪل_ڊيگهائي;
        *ڪل_ڊيگهائي += بائيٽون_read;

        ثابت size_t new_بفر_ڊيگهائي = *ڪل_ڊيگهائي + حجم(Uint32);

        إذا (!*بفر_2) {
            output_بفر = SDL_malloc(new_بفر_ڊيگهائي);
        } وإلا {
            output_بفر = SDL_realloc(*بفر_2, new_بفر_ڊيگهائي);
        }

        إذا (!output_بفر) {
            بائيٽون_read = -1;
        } وإلا {
            SDL_memcpy((Uint8 *)output_بفر + pos, عارضي, بائيٽون_read);
            SDL_memset((Uint8 *)output_بفر + (new_بفر_ڊيگهائي - حجم(Uint32)), 0, حجم(Uint32));

            *بفر_2 = output_بفر;
        }
    }

    أرجع بائيٽون_read;
}

ساكن bool MIMEDataListHasType(بنية wl_array *list, ثابت حرف *mime_type)
{
    ثابت حرف **شي;
    wl_array_for_each(شي, list) {
        إذا (SDL_strcmp(*شي, mime_type) == 0) {
            أرجع true;
        }
    }

    أرجع false;
}

ساكن bool MIMEData_List_جوڙيو(بنية wl_array *list, ثابت حرف *mime_type)
{
    إذا (!MIMEDataListHasType(list, mime_type)) {
        حرف **شي = WAYLAND_wl_array_جوڙيو(list, حجم(حرف *));
        *شي = SDL_strdup(mime_type);
    }

    أرجع true;
}

ساكن فراغ MIMEDataListFree(بنية wl_array *list)
{
    حرف **شي;
    wl_array_for_each(شي, list) {
        SDL_free(*شي);
    }

    WAYLAND_wl_array_release(list);
}

ساكن فراغ معلومات_ذريعو_handle_هدف(فراغ *معلومات, بنية wl_معلومات_ذريعو *wl_معلومات_ذريعو, ثابت حرف *mime_type)
{
}

ساكن فراغ معلومات_ذريعو_handle_send(فراغ *معلومات, بنية wl_معلومات_ذريعو *wl_معلومات_ذريعو, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_معلومات_ذريعو_Send((SDL_Wayland_معلومات_ذريعو *)معلومات, mime_type, fd);
}

ساكن فراغ معلومات_ذريعو_handle_cancelled(فراغ *معلومات, بنية wl_معلومات_ذريعو *wl_معلومات_ذريعو)
{
    SDL_Wayland_معلومات_ذريعو *ذريعو = معلومات;
    إذا (ذريعو) {
        Wayland_معلومات_ذريعو_Destroy(ذريعو);
    }
}

ساكن فراغ معلومات_ذريعو_handle_dnd_drop_performed(فراغ *معلومات, بنية wl_معلومات_ذريعو *wl_معلومات_ذريعو)
{
}

ساكن فراغ معلومات_ذريعو_handle_dnd_ختم(فراغ *معلومات, بنية wl_معلومات_ذريعو *wl_معلومات_ذريعو)
{
    SDL_Wayland_معلومات_ذريعو *ذريعو = معلومات;
    إذا (ذريعو) {
        Wayland_معلومات_ذريعو_Destroy(ذريعو);
    }
}

ساكن فراغ معلومات_ذريعو_handle_action(فراغ *معلومات, بنية wl_معلومات_ذريعو *wl_معلومات_ذريعو, uint32_t dnd_action)
{
}

ساكن ثابت بنية wl_معلومات_ذريعو_listener معلومات_ذريعو_listener = {
    معلومات_ذريعو_handle_هدف,
    معلومات_ذريعو_handle_send,
    معلومات_ذريعو_handle_cancelled,
    معلومات_ذريعو_handle_dnd_drop_performed, // Version 3
    معلومات_ذريعو_handle_dnd_ختم,       // Version 3
    معلومات_ذريعو_handle_action,             // Version 3
};

SDL_Wayland_معلومات_ذريعو *Wayland_معلومات_ذريعو_Create(SDL_Video_معلومات *video_معلومات)
{
    SDL_Wayland_معلومات_ذريعو *معلومات_ذريعو_2 = SDL_calloc(1, حجم(*معلومات_ذريعو_2));
    إذا (!معلومات_ذريعو_2) {
        أرجع عدم;
    }

    بنية wl_معلومات_ذريعو *id = wl_معلومات_device_manager_create_معلومات_ذريعو(video_معلومات->معلومات_device_manager);
    معلومات_ذريعو_2->ذريعو = id;
    wl_معلومات_ذريعو_سيٽ_user_معلومات(id, معلومات_ذريعو_2);
    wl_معلومات_ذريعو_جوڙيو_listener(id, &معلومات_ذريعو_listener, معلومات_ذريعو_2);

    أرجع معلومات_ذريعو_2;
}

ساكن فراغ primary_selection_ذريعو_send(فراغ *معلومات, بنية zwp_primary_selection_ذريعو_v1 *zwp_primary_selection_ذريعو_v1, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_ذريعو_Send((SDL_Wayland_Primary_Selection_ذريعو *)معلومات, mime_type, fd);
}

ساكن فراغ primary_selection_ذريعو_cancelled(فراغ *معلومات, بنية zwp_primary_selection_ذريعو_v1 *zwp_primary_selection_ذريعو_v1)
{
    Wayland_Primary_Selection_ذريعو_Destroy(معلومات);
}

ساكن ثابت بنية zwp_primary_selection_ذريعو_v1_listener primary_selection_ذريعو_listener = {
    primary_selection_ذريعو_send,
    primary_selection_ذريعو_cancelled,
};

SDL_Wayland_Primary_Selection_ذريعو *Wayland_Primary_Selection_ذريعو_Create(SDL_Video_معلومات *video_معلومات)
{
    SDL_Wayland_Primary_Selection_ذريعو *primary_selection_ذريعو = SDL_calloc(1, حجم(*primary_selection_ذريعو));
    إذا (!primary_selection_ذريعو) {
        أرجع عدم;
    }

    بنية zwp_primary_selection_ذريعو_v1 *id = zwp_primary_selection_device_manager_v1_create_ذريعو(video_معلومات->primary_selection_device_manager);
    primary_selection_ذريعو->ذريعو = id;
    zwp_primary_selection_ذريعو_v1_جوڙيو_listener(id, &primary_selection_ذريعو_listener, primary_selection_ذريعو);

    أرجع primary_selection_ذريعو;
}

ساكن size_t Send_معلومات(ثابت فراغ *معلومات, size_t ڊيگهائي, صحيح fd)
{
    size_t نتيجو = 0;

    إذا (ڊيگهائي > 0 && معلومات) {
        طالما (WritePipe(fd, معلومات, ڊيگهائي, &نتيجو) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    أرجع نتيجو;
}

ssize_t Wayland_معلومات_ذريعو_Send(SDL_Wayland_معلومات_ذريعو *ذريعو, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *معلومات = عدم;
    size_t ڊيگهائي = 0;

    إذا (SDL_strcmp(mime_type, SDL_معلومات_ORIGIN_MIME) == 0) {
        معلومات = ذريعو->معلومات_device->id_str;
        ڊيگهائي = SDL_strlen(ذريعو->معلومات_device->id_str);
    } وإلا إذا (ذريعو->معلومات_callback) {
        معلومات = ذريعو->معلومات_callback(ذريعو->userdata.معلومات, mime_type, &ڊيگهائي);
    }

    أرجع Send_معلومات(معلومات, ڊيگهائي, fd);
}

ssize_t Wayland_Primary_Selection_ذريعو_Send(SDL_Wayland_Primary_Selection_ذريعو *ذريعو, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *معلومات = عدم;
    size_t ڊيگهائي = 0;

    إذا (ذريعو->معلومات_callback) {
        معلومات = ذريعو->معلومات_callback(ذريعو->userdata.معلومات, mime_type, &ڊيگهائي);
    }

    أرجع Send_معلومات(معلومات, ڊيگهائي, fd);
}

فراغ Wayland_معلومات_ذريعو_سيٽ_Callback(SDL_Wayland_معلومات_ذريعو *ذريعو, SDL_Clipboard_معلومات_Callback معلومات_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence)
{
    إذا (ذريعو) {
        ذريعو->معلومات_callback = معلومات_callback;
        ذريعو->cleanup_callback = cleanup_callback;
        ذريعو->userdata.sequence = sequence;
        ذريعو->userdata.معلومات = userdata;
    }
}

فراغ Wayland_Primary_Selection_ذريعو_سيٽ_Callback(SDL_Wayland_Primary_Selection_ذريعو *ذريعو, SDL_Clipboard_معلومات_Callback معلومات_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata)
{
    إذا (ذريعو) {
        ذريعو->معلومات_callback = معلومات_callback;
        ذريعو->cleanup_callback = cleanup_callback;
        ذريعو->userdata.sequence = 0;
        ذريعو->userdata.معلومات = userdata;
    }
}

ساكن فراغ *Clone_معلومات_بفر(ثابت فراغ *بفر_2, ثابت size_t *len)
{
    فراغ *clone = عدم;
    إذا (*len > 0 && بفر_2) {
        clone = SDL_malloc((*len)+حجم(Uint32));
        إذا (clone) {
            SDL_memcpy(clone, بفر_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, حجم(Uint32));
        }
    }
    أرجع clone;
}

فراغ *Wayland_معلومات_ذريعو_Get_معلومات(SDL_Wayland_معلومات_ذريعو *ذريعو, ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    فراغ *بفر_2 = عدم;
    *ڊيگهائي = 0;

    إذا (!ذريعو) {
        SDL_سيٽ_Error("Invalid data source");
    } وإلا إذا (ذريعو->معلومات_callback) {
        ثابت فراغ *اندروني_بفر = ذريعو->معلومات_callback(ذريعو->userdata.معلومات, mime_type, ڊيگهائي);
        بفر_2 = Clone_معلومات_بفر(اندروني_بفر, ڊيگهائي);
    }

    أرجع بفر_2;
}

فراغ *Wayland_Primary_Selection_ذريعو_Get_معلومات(SDL_Wayland_Primary_Selection_ذريعو *ذريعو, ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    فراغ *بفر_2 = عدم;
    *ڊيگهائي = 0;

    إذا (!ذريعو) {
        SDL_سيٽ_Error("Invalid primary selection source");
    } وإلا إذا (ذريعو->معلومات_callback) {
        ثابت فراغ *اندروني_بفر = ذريعو->معلومات_callback(ذريعو->userdata.معلومات, mime_type, ڊيگهائي);
        بفر_2 = Clone_معلومات_بفر(اندروني_بفر, ڊيگهائي);
    }

    أرجع بفر_2;
}

فراغ Wayland_معلومات_ذريعو_Destroy(SDL_Wayland_معلومات_ذريعو *ذريعو)
{
    إذا (ذريعو) {
        SDL_Wayland_معلومات_Device *معلومات_device = ذريعو->معلومات_device;
        إذا (معلومات_device && (معلومات_device->selection_ذريعو == ذريعو)) {
            معلومات_device->selection_ذريعو = عدم;
        }
        wl_معلومات_ذريعو_destroy(ذريعو->ذريعو);
        إذا (ذريعو->userdata.sequence) {
            SDL_Cancel_Clipboard_معلومات(ذريعو->userdata.sequence);
        } وإلا إذا (ذريعو->cleanup_callback) {
            ذريعو->cleanup_callback(ذريعو->userdata.معلومات);
        }
        SDL_free(ذريعو);
    }
}

فراغ Wayland_Primary_Selection_ذريعو_Destroy(SDL_Wayland_Primary_Selection_ذريعو *ذريعو)
{
    إذا (ذريعو) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = ذريعو->primary_selection_device;
        إذا (primary_selection_device && (primary_selection_device->selection_ذريعو == ذريعو)) {
            primary_selection_device->selection_ذريعو = عدم;
        }
        zwp_primary_selection_ذريعو_v1_destroy(ذريعو->ذريعو);
        إذا (ذريعو->cleanup_callback) {
            ذريعو->cleanup_callback(ذريعو->userdata.معلومات);
        }
        SDL_free(ذريعو);
    }
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_معلومات_Device *معلومات_device, bool check_origin);

ساكن فراغ offer_ذريعو_پورو_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    إذا (!callback) {
        أرجع;
    }

    SDL_Wayland_معلومات_Offer *offer = (SDL_Wayland_معلومات_Offer *)معلومات;
    حرف *id = عدم;
    size_t ڊيگهائي = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = عدم;

    طالما (ReadPipe(offer->read_fd, (فراغ **)&id, &ڊيگهائي, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    إذا (id) {
        ثابت bool ذريعو_is_external = SDL_strncmp(offer->معلومات_device->id_str, id, ڊيگهائي) != 0;
        SDL_free(id);
        إذا (ذريعو_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->معلومات_device, false);
        } وإلا {
            // Recursive data offer; just destroy it.
            SDL_Wayland_معلومات_Device *معلومات_device = offer->معلومات_device;
            Wayland_معلومات_Offer_Destroy(offer);
            معلومات_device->selection_offer = عدم;
        }
    }
}

ساكن ثابت بنية wl_callback_listener offer_ذريعو_listener = {
    offer_ذريعو_پورو_handler
};

ساكن فراغ UpdateSeatOffers(SDL_Wayland_معلومات_Device *معلومات_device)
{
    SDL_WaylandSeat *offer_seat = معلومات_device->seat;
    SDL_Video_معلومات *video_معلومات = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_معلومات->seat_list, link) {
        إذا (s->معلومات_device) {
            Wayland_معلومات_ذريعو_Destroy(s->معلومات_device->selection_ذريعو);
            s->معلومات_device->selection_ذريعو = عدم;

            // Don't clear the offer that is about to be set.
            إذا (s != offer_seat) {
                Wayland_معلومات_Offer_Destroy(s->معلومات_device->selection_offer);
                s->معلومات_device->selection_offer = عدم;
            }
        }
    }

    video_معلومات->current_معلومات_offer_seat = offer_seat;
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_معلومات_Device *معلومات_device, bool check_origin)
{
    SDL_Wayland_معلومات_Offer *offer = معلومات_device->selection_offer;
    حرف **new_mime_types = عدم;
    size_t انگ_formats = 0;

    إذا (offer) {
        size_t alloc_سائيز_2 = 0;

        // Do a first pass to compute allocation size.
        ثابت حرف **شي;
        wl_array_for_each(شي, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            إذا (check_origin && SDL_strcmp(*شي, SDL_معلومات_ORIGIN_MIME) == 0) {
                Wayland_معلومات_Offer_Request_معلومات_From_Self(offer, *شي, &offer_ذريعو_listener, offer);
                أرجع;
            }

            ++انگ_formats;
            alloc_سائيز_2 += SDL_strlen(*شي) + 1;
        }

        alloc_سائيز_2 += (انگ_formats + 1) * حجم(حرف *);

        new_mime_types = SDL_Allocate_Temporary_يادگيري(alloc_سائيز_2);
        إذا (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_داخلا, "unable to allocate new_mime_types");
            أرجع;
        }

        // Second pass to fill.
        حرف *strPtr = (حرف *)(new_mime_types + انگ_formats + 1);
        alloc_سائيز_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        شي = عدم;
        صحيح i = 0;
        wl_array_for_each(شي, &offer->mimes) {
            إذا (!شي) {
                استمر;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *شي, alloc_سائيز_2) + 1;
            strPtr += len;
            alloc_سائيز_2 -= len;
        }
        new_mime_types[انگ_formats] = عدم;
    }

    UpdateSeatOffers(معلومات_device);
    SDL_SendClipboardUpdate(false, new_mime_types, انگ_formats);
}

فراغ Wayland_معلومات_Device_سيٽ_Selection_Offer(SDL_Wayland_معلومات_Device *معلومات_device, SDL_Wayland_معلومات_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && معلومات_device->selection_offer && (!معلومات_device->selection_offer->callback || !معلومات_device->selection_ذريعو));
    Wayland_معلومات_Offer_Destroy(معلومات_device->selection_offer);
    معلومات_device->selection_offer = offer;
    إذا (notify) {
        SelectionOfferNotifyFromMIMEs(معلومات_device, true);
    }
}

فراغ *Wayland_معلومات_Offer_Get_معلومات_From_Self(SDL_Wayland_معلومات_Offer *offer, size_t *ڊيگهائي)
{
    إذا (!offer) {
        SDL_سيٽ_Error("Invalid data offer");
        أرجع عدم;
    }

    إذا (offer->read_fd < 0) {
        SDL_سيٽ_Error("Pipe closed");
        أرجع عدم;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    فراغ *بفر_2 = عدم;
    طالما (ReadPipe(offer->read_fd, &بفر_2, ڊيگهائي, 0) > 0) {
    }

    أرجع بفر_2;
}

bool Wayland_معلومات_Offer_Request_معلومات_From_Self(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata)
{
    صحيح pipefd[2];

    إذا (!offer) {
        SDL_سيٽ_Error("Invalid data offer");
        أرجع false;
    }

    SDL_Wayland_معلومات_Device *معلومات_device = offer->معلومات_device;
    إذا (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    إذا (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = عدم;
    }

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_معلومات_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(معلومات_device->seat->display->display);
        wl_callback_جوڙيو_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(معلومات_device->seat->display->display);
    } وإلا {
        أرجع SDL_سيٽ_Error("Could not create pipe");
    }

    أرجع true;
}

فراغ *Wayland_معلومات_Offer_Receive(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    صحيح pipefd[2];
    فراغ *بفر_2 = عدم;
    *ڊيگهائي = 0;

    إذا (!offer) {
        SDL_سيٽ_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_Wayland_معلومات_Device *معلومات_device = offer->معلومات_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_معلومات_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(معلومات_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &بفر_2, ڊيگهائي, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } وإلا {
        SDL_سيٽ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *ڊيگهائي, بفر_2);

    أرجع بفر_2;
}

فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *ڊيگهائي)
{
    صحيح pipefd[2];
    فراغ *بفر_2 = عدم;
    *ڊيگهائي = 0;

    إذا (!offer) {
        SDL_سيٽ_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &بفر_2, ڊيگهائي, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } وإلا {
        SDL_سيٽ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلا,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *ڊيگهائي, بفر_2);

    أرجع بفر_2;
}

bool Wayland_معلومات_Offer_جوڙيو_MIME(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جوڙيو(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_جوڙيو_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جوڙيو(&offer->mimes, mime_type);
}

bool Wayland_معلومات_Offer_Has_MIME(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type)
{
    إذا (offer && mime_type) {
        أرجع MIMEDataListHasType(&offer->mimes, mime_type);
    }
    أرجع false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    إذا (offer && mime_type) {
        أرجع MIMEDataListHasType(&offer->mimes, mime_type);
    }
    أرجع false;
}

فراغ Wayland_معلومات_Offer_Destroy(SDL_Wayland_معلومات_Offer *offer)
{
    إذا (offer) {
        إذا (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        إذا (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_معلومات_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

فراغ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    إذا (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_معلومات_Device_سيٽ_Selection_ذريعو(SDL_Wayland_معلومات_Device *معلومات_device, SDL_Wayland_معلومات_ذريعو *ذريعو, ثابت حرف **mime_types, size_t mime_ڳڻپ)
{
    إذا (!معلومات_device) {
        أرجع SDL_سيٽ_Error("Invalid Data Device");
    }
    إذا (!ذريعو) {
        أرجع SDL_سيٽ_Error("Invalid source");
    }

    إذا (mime_ڳڻپ) {
        لكل (size_t اشاريو = 0; اشاريو < mime_ڳڻپ; ++اشاريو) {
            ثابت حرف *mime_type = mime_types[اشاريو];
            wl_معلومات_ذريعو_offer(ذريعو->ذريعو, mime_type);
        }

        // Advertise the data origin MIME
        wl_معلومات_ذريعو_offer(ذريعو->ذريعو, SDL_معلومات_ORIGIN_MIME);

        wl_معلومات_device_سيٽ_selection(معلومات_device->معلومات_device, ذريعو->ذريعو, معلومات_device->seat->آخري_implicit_grab_serial);
        إذا (معلومات_device->selection_ذريعو) {
            Wayland_معلومات_ذريعو_Destroy(معلومات_device->selection_ذريعو);
        }
        معلومات_device->selection_ذريعو = ذريعو;
        ذريعو->معلومات_device = معلومات_device;

    } وإلا {
        Wayland_معلومات_ذريعو_Destroy(معلومات_device->selection_ذريعو);
        معلومات_device->selection_ذريعو = عدم;
        أرجع SDL_سيٽ_Error("No mime data");
    }

    أرجع true;
}

bool Wayland_Primary_Selection_Device_سيٽ_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_ذريعو *ذريعو,
                                                ثابت حرف *ثابت *mime_types, size_t mime_ڳڻپ)
{
    إذا (!primary_selection_device) {
        أرجع SDL_سيٽ_Error("Invalid Primary Selection Device");
    }
    إذا (!ذريعو) {
        أرجع SDL_سيٽ_Error("Invalid source");
    }

    إذا (mime_ڳڻپ) {
        لكل (size_t اشاريو = 0; اشاريو < mime_ڳڻپ; ++اشاريو) {
            ثابت حرف *mime_type = mime_types[اشاريو];
            zwp_primary_selection_ذريعو_v1_offer(ذريعو->ذريعو, mime_type);
        }

        zwp_primary_selection_device_v1_سيٽ_selection(primary_selection_device->primary_selection_device,
                                                      ذريعو->ذريعو,
                                                      primary_selection_device->seat->آخري_implicit_grab_serial);
        إذا (primary_selection_device->selection_ذريعو) {
            Wayland_Primary_Selection_ذريعو_Destroy(primary_selection_device->selection_ذريعو);
        }
        primary_selection_device->selection_ذريعو = ذريعو;
        ذريعو->primary_selection_device = primary_selection_device;
    } وإلا {
        Wayland_Primary_Selection_ذريعو_Destroy(primary_selection_device->selection_ذريعو);
        primary_selection_device->selection_ذريعو = عدم;
        أرجع SDL_سيٽ_Error("No mime data");
    }

    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND

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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

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
#تعریف_کرو DEFAULT_PIPE_TIMEOUT_NS SDL_MS_منزل_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#جے_بنا_تعریف HAVE_SIGTIMEDWAIT
#ضمن <errno.h>
#ضمن <time.h>
ساكن صحيح sigtimedwait(ثابت sigset_t *سیٹ, siginfo_t *info, ثابت بنية timespec *timeout)
{
    بنية timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    افعل {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        لكل (صحيح signo = 1; signo < NSIG; ++signo) {
            إذا (sigismember(سیٹ, signo) && sigismember(&pending, signo)) {
                إذا (!sigwait(سیٹ, &signo)) {
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
            لما ns = 20000000L; // 2/100ths of a second
            nanosleep(&(بنية timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } طالما (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    أرجع -1;
}
#جے_انت

ساكن ssize_t WritePipe(صحيح fd, ثابت فراغ *بفر_2, size_t کل_لمائی, size_t *pos)
{
    ssize_t بائٹاں_written = 0;
    ثابت ssize_t لمائی = کل_لمائی - *pos;

    sigset_t sig_سیٹ;
    sigset_t old_sig_سیٹ;
    بنية timespec zerotime = { 0 };

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_سیٹ);
    sigaddset(&sig_سیٹ, SIGPIPE);

#جے_تعریف_شدہ SDL_دھاگے_DISABLED
    sigprocmask(SIG_BLOCK, &sig_سیٹ, &old_sig_سیٹ);
#وإلا
    pthread_sigmask(SIG_BLOCK, &sig_سیٹ, &old_sig_سیٹ);
#جے_انت

    إذا (ready > 0) {
        إذا (لمائی > 0) {
            بائٹاں_written = اكتب(fd, (Uint8 *)بفر_2 + *pos, SDL_min(لمائی, PIPE_BUF));
        }

        إذا (بائٹاں_written > 0) {
            *pos += بائٹاں_written;
        }
    } وإلا إذا (ready == 0) {
        SDL_سیٹ_Error("Pipe timeout");
    } وإلا  {
        SDL_سیٹ_Error("Pipe poll error");
    }

    sigtimedwait(&sig_سیٹ, عدم, &zerotime);

#جے_تعریف_شدہ SDL_دھاگے_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_سیٹ, عدم);
#وإلا
    pthread_sigmask(SIG_SETMASK, &old_sig_سیٹ, عدم);
#جے_انت

    أرجع بائٹاں_written;
}

ساكن ssize_t ReadPipe(صحيح fd, فراغ **بفر_2, size_t *کل_لمائی, Sint64 timeout_ns)
{
    فراغ *output_بفر = عدم;
    حرف عارضی[PIPE_BUF];
    ssize_t بائٹاں_read = 0;

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    إذا (ready > 0) {
        بائٹاں_read = اقرأ(fd, عارضی, حجم(عارضی));
    } وإلا إذا (ready == 0) {
        SDL_سیٹ_Error("Pipe timeout");
    } وإلا {
        SDL_سیٹ_Error("Pipe poll error");
    }

    إذا (بائٹاں_read > 0) {
        ثابت size_t pos = *کل_لمائی;
        *کل_لمائی += بائٹاں_read;

        ثابت size_t new_بفر_لمائی = *کل_لمائی + حجم(Uint32);

        إذا (!*بفر_2) {
            output_بفر = SDL_malloc(new_بفر_لمائی);
        } وإلا {
            output_بفر = SDL_realloc(*بفر_2, new_بفر_لمائی);
        }

        إذا (!output_بفر) {
            بائٹاں_read = -1;
        } وإلا {
            SDL_memcpy((Uint8 *)output_بفر + pos, عارضی, بائٹاں_read);
            SDL_memset((Uint8 *)output_بفر + (new_بفر_لمائی - حجم(Uint32)), 0, حجم(Uint32));

            *بفر_2 = output_بفر;
        }
    }

    أرجع بائٹاں_read;
}

ساكن bool MIMEDataListHasType(بنية wl_array *list, ثابت حرف *mime_type)
{
    ثابت حرف **شے;
    wl_array_for_each(شے, list) {
        إذا (SDL_strcmp(*شے, mime_type) == 0) {
            أرجع true;
        }
    }

    أرجع false;
}

ساكن bool MIMEData_List_جوڑو(بنية wl_array *list, ثابت حرف *mime_type)
{
    إذا (!MIMEDataListHasType(list, mime_type)) {
        حرف **شے = WAYLAND_wl_array_جوڑو(list, حجم(حرف *));
        *شے = SDL_strdup(mime_type);
    }

    أرجع true;
}

ساكن فراغ MIMEDataListFree(بنية wl_array *list)
{
    حرف **شے;
    wl_array_for_each(شے, list) {
        SDL_free(*شے);
    }

    WAYLAND_wl_array_release(list);
}

ساكن فراغ انکڑے_سروت_handle_نشانہ(فراغ *انکڑے, بنية wl_انکڑے_سروت *wl_انکڑے_سروت, ثابت حرف *mime_type)
{
}

ساكن فراغ انکڑے_سروت_handle_send(فراغ *انکڑے, بنية wl_انکڑے_سروت *wl_انکڑے_سروت, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_انکڑے_سروت_Send((SDL_Wayland_انکڑے_سروت *)انکڑے, mime_type, fd);
}

ساكن فراغ انکڑے_سروت_handle_cancelled(فراغ *انکڑے, بنية wl_انکڑے_سروت *wl_انکڑے_سروت)
{
    SDL_Wayland_انکڑے_سروت *سروت = انکڑے;
    إذا (سروت) {
        Wayland_انکڑے_سروت_Destroy(سروت);
    }
}

ساكن فراغ انکڑے_سروت_handle_dnd_drop_performed(فراغ *انکڑے, بنية wl_انکڑے_سروت *wl_انکڑے_سروت)
{
}

ساكن فراغ انکڑے_سروت_handle_dnd_مکمل(فراغ *انکڑے, بنية wl_انکڑے_سروت *wl_انکڑے_سروت)
{
    SDL_Wayland_انکڑے_سروت *سروت = انکڑے;
    إذا (سروت) {
        Wayland_انکڑے_سروت_Destroy(سروت);
    }
}

ساكن فراغ انکڑے_سروت_handle_action(فراغ *انکڑے, بنية wl_انکڑے_سروت *wl_انکڑے_سروت, uint32_t dnd_action)
{
}

ساكن ثابت بنية wl_انکڑے_سروت_listener انکڑے_سروت_listener = {
    انکڑے_سروت_handle_نشانہ,
    انکڑے_سروت_handle_send,
    انکڑے_سروت_handle_cancelled,
    انکڑے_سروت_handle_dnd_drop_performed, // Version 3
    انکڑے_سروت_handle_dnd_مکمل,       // Version 3
    انکڑے_سروت_handle_action,             // Version 3
};

SDL_Wayland_انکڑے_سروت *Wayland_انکڑے_سروت_Create(SDL_Video_انکڑے *video_انکڑے)
{
    SDL_Wayland_انکڑے_سروت *انکڑے_سروت_2 = SDL_calloc(1, حجم(*انکڑے_سروت_2));
    إذا (!انکڑے_سروت_2) {
        أرجع عدم;
    }

    بنية wl_انکڑے_سروت *id = wl_انکڑے_device_manager_create_انکڑے_سروت(video_انکڑے->انکڑے_device_manager);
    انکڑے_سروت_2->سروت = id;
    wl_انکڑے_سروت_سیٹ_user_انکڑے(id, انکڑے_سروت_2);
    wl_انکڑے_سروت_جوڑو_listener(id, &انکڑے_سروت_listener, انکڑے_سروت_2);

    أرجع انکڑے_سروت_2;
}

ساكن فراغ primary_selection_سروت_send(فراغ *انکڑے, بنية zwp_primary_selection_سروت_v1 *zwp_primary_selection_سروت_v1, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_سروت_Send((SDL_Wayland_Primary_Selection_سروت *)انکڑے, mime_type, fd);
}

ساكن فراغ primary_selection_سروت_cancelled(فراغ *انکڑے, بنية zwp_primary_selection_سروت_v1 *zwp_primary_selection_سروت_v1)
{
    Wayland_Primary_Selection_سروت_Destroy(انکڑے);
}

ساكن ثابت بنية zwp_primary_selection_سروت_v1_listener primary_selection_سروت_listener = {
    primary_selection_سروت_send,
    primary_selection_سروت_cancelled,
};

SDL_Wayland_Primary_Selection_سروت *Wayland_Primary_Selection_سروت_Create(SDL_Video_انکڑے *video_انکڑے)
{
    SDL_Wayland_Primary_Selection_سروت *primary_selection_سروت = SDL_calloc(1, حجم(*primary_selection_سروت));
    إذا (!primary_selection_سروت) {
        أرجع عدم;
    }

    بنية zwp_primary_selection_سروت_v1 *id = zwp_primary_selection_device_manager_v1_create_سروت(video_انکڑے->primary_selection_device_manager);
    primary_selection_سروت->سروت = id;
    zwp_primary_selection_سروت_v1_جوڑو_listener(id, &primary_selection_سروت_listener, primary_selection_سروت);

    أرجع primary_selection_سروت;
}

ساكن size_t Send_انکڑے(ثابت فراغ *انکڑے, size_t لمائی, صحيح fd)
{
    size_t نتیجہ = 0;

    إذا (لمائی > 0 && انکڑے) {
        طالما (WritePipe(fd, انکڑے, لمائی, &نتیجہ) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    أرجع نتیجہ;
}

ssize_t Wayland_انکڑے_سروت_Send(SDL_Wayland_انکڑے_سروت *سروت, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *انکڑے = عدم;
    size_t لمائی = 0;

    إذا (SDL_strcmp(mime_type, SDL_انکڑے_ORIGIN_MIME) == 0) {
        انکڑے = سروت->انکڑے_device->id_str;
        لمائی = SDL_strlen(سروت->انکڑے_device->id_str);
    } وإلا إذا (سروت->انکڑے_callback) {
        انکڑے = سروت->انکڑے_callback(سروت->userdata.انکڑے, mime_type, &لمائی);
    }

    أرجع Send_انکڑے(انکڑے, لمائی, fd);
}

ssize_t Wayland_Primary_Selection_سروت_Send(SDL_Wayland_Primary_Selection_سروت *سروت, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *انکڑے = عدم;
    size_t لمائی = 0;

    إذا (سروت->انکڑے_callback) {
        انکڑے = سروت->انکڑے_callback(سروت->userdata.انکڑے, mime_type, &لمائی);
    }

    أرجع Send_انکڑے(انکڑے, لمائی, fd);
}

فراغ Wayland_انکڑے_سروت_سیٹ_Callback(SDL_Wayland_انکڑے_سروت *سروت, SDL_Clipboard_انکڑے_Callback انکڑے_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence)
{
    إذا (سروت) {
        سروت->انکڑے_callback = انکڑے_callback;
        سروت->cleanup_callback = cleanup_callback;
        سروت->userdata.sequence = sequence;
        سروت->userdata.انکڑے = userdata;
    }
}

فراغ Wayland_Primary_Selection_سروت_سیٹ_Callback(SDL_Wayland_Primary_Selection_سروت *سروت, SDL_Clipboard_انکڑے_Callback انکڑے_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata)
{
    إذا (سروت) {
        سروت->انکڑے_callback = انکڑے_callback;
        سروت->cleanup_callback = cleanup_callback;
        سروت->userdata.sequence = 0;
        سروت->userdata.انکڑے = userdata;
    }
}

ساكن فراغ *Clone_انکڑے_بفر(ثابت فراغ *بفر_2, ثابت size_t *len)
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

فراغ *Wayland_انکڑے_سروت_Get_انکڑے(SDL_Wayland_انکڑے_سروت *سروت, ثابت حرف *mime_type, size_t *لمائی)
{
    فراغ *بفر_2 = عدم;
    *لمائی = 0;

    إذا (!سروت) {
        SDL_سیٹ_Error("Invalid data source");
    } وإلا إذا (سروت->انکڑے_callback) {
        ثابت فراغ *اندرونی_بفر = سروت->انکڑے_callback(سروت->userdata.انکڑے, mime_type, لمائی);
        بفر_2 = Clone_انکڑے_بفر(اندرونی_بفر, لمائی);
    }

    أرجع بفر_2;
}

فراغ *Wayland_Primary_Selection_سروت_Get_انکڑے(SDL_Wayland_Primary_Selection_سروت *سروت, ثابت حرف *mime_type, size_t *لمائی)
{
    فراغ *بفر_2 = عدم;
    *لمائی = 0;

    إذا (!سروت) {
        SDL_سیٹ_Error("Invalid primary selection source");
    } وإلا إذا (سروت->انکڑے_callback) {
        ثابت فراغ *اندرونی_بفر = سروت->انکڑے_callback(سروت->userdata.انکڑے, mime_type, لمائی);
        بفر_2 = Clone_انکڑے_بفر(اندرونی_بفر, لمائی);
    }

    أرجع بفر_2;
}

فراغ Wayland_انکڑے_سروت_Destroy(SDL_Wayland_انکڑے_سروت *سروت)
{
    إذا (سروت) {
        SDL_Wayland_انکڑے_Device *انکڑے_device = سروت->انکڑے_device;
        إذا (انکڑے_device && (انکڑے_device->selection_سروت == سروت)) {
            انکڑے_device->selection_سروت = عدم;
        }
        wl_انکڑے_سروت_destroy(سروت->سروت);
        إذا (سروت->userdata.sequence) {
            SDL_Cancel_Clipboard_انکڑے(سروت->userdata.sequence);
        } وإلا إذا (سروت->cleanup_callback) {
            سروت->cleanup_callback(سروت->userdata.انکڑے);
        }
        SDL_free(سروت);
    }
}

فراغ Wayland_Primary_Selection_سروت_Destroy(SDL_Wayland_Primary_Selection_سروت *سروت)
{
    إذا (سروت) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = سروت->primary_selection_device;
        إذا (primary_selection_device && (primary_selection_device->selection_سروت == سروت)) {
            primary_selection_device->selection_سروت = عدم;
        }
        zwp_primary_selection_سروت_v1_destroy(سروت->سروت);
        إذا (سروت->cleanup_callback) {
            سروت->cleanup_callback(سروت->userdata.انکڑے);
        }
        SDL_free(سروت);
    }
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_انکڑے_Device *انکڑے_device, bool check_origin);

ساكن فراغ offer_سروت_پورا_handler(فراغ *انکڑے, بنية wl_callback *callback, uint32_t callback_انکڑے)
{
    إذا (!callback) {
        أرجع;
    }

    SDL_Wayland_انکڑے_Offer *offer = (SDL_Wayland_انکڑے_Offer *)انکڑے;
    حرف *id = عدم;
    size_t لمائی = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = عدم;

    طالما (ReadPipe(offer->read_fd, (فراغ **)&id, &لمائی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    إذا (id) {
        ثابت bool سروت_is_external = SDL_strncmp(offer->انکڑے_device->id_str, id, لمائی) != 0;
        SDL_free(id);
        إذا (سروت_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->انکڑے_device, false);
        } وإلا {
            // Recursive data offer; just destroy it.
            SDL_Wayland_انکڑے_Device *انکڑے_device = offer->انکڑے_device;
            Wayland_انکڑے_Offer_Destroy(offer);
            انکڑے_device->selection_offer = عدم;
        }
    }
}

ساكن ثابت بنية wl_callback_listener offer_سروت_listener = {
    offer_سروت_پورا_handler
};

ساكن فراغ UpdateSeatOffers(SDL_Wayland_انکڑے_Device *انکڑے_device)
{
    SDL_WaylandSeat *offer_seat = انکڑے_device->seat;
    SDL_Video_انکڑے *video_انکڑے = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_انکڑے->seat_list, link) {
        إذا (s->انکڑے_device) {
            Wayland_انکڑے_سروت_Destroy(s->انکڑے_device->selection_سروت);
            s->انکڑے_device->selection_سروت = عدم;

            // Don't clear the offer that is about to be set.
            إذا (s != offer_seat) {
                Wayland_انکڑے_Offer_Destroy(s->انکڑے_device->selection_offer);
                s->انکڑے_device->selection_offer = عدم;
            }
        }
    }

    video_انکڑے->current_انکڑے_offer_seat = offer_seat;
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_انکڑے_Device *انکڑے_device, bool check_origin)
{
    SDL_Wayland_انکڑے_Offer *offer = انکڑے_device->selection_offer;
    حرف **new_mime_types = عدم;
    size_t عدد_formats = 0;

    إذا (offer) {
        size_t alloc_ناپ_2 = 0;

        // Do a first pass to compute allocation size.
        ثابت حرف **شے;
        wl_array_for_each(شے, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            إذا (check_origin && SDL_strcmp(*شے, SDL_انکڑے_ORIGIN_MIME) == 0) {
                Wayland_انکڑے_Offer_Request_انکڑے_From_Self(offer, *شے, &offer_سروت_listener, offer);
                أرجع;
            }

            ++عدد_formats;
            alloc_ناپ_2 += SDL_strlen(*شے) + 1;
        }

        alloc_ناپ_2 += (عدد_formats + 1) * حجم(حرف *);

        new_mime_types = SDL_Allocate_Temporary_حافظہ(alloc_ناپ_2);
        إذا (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_داخلہ, "unable to allocate new_mime_types");
            أرجع;
        }

        // Second pass to fill.
        حرف *strPtr = (حرف *)(new_mime_types + عدد_formats + 1);
        alloc_ناپ_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        شے = عدم;
        صحيح i = 0;
        wl_array_for_each(شے, &offer->mimes) {
            إذا (!شے) {
                استمر;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *شے, alloc_ناپ_2) + 1;
            strPtr += len;
            alloc_ناپ_2 -= len;
        }
        new_mime_types[عدد_formats] = عدم;
    }

    UpdateSeatOffers(انکڑے_device);
    SDL_SendClipboardUpdate(false, new_mime_types, عدد_formats);
}

فراغ Wayland_انکڑے_Device_سیٹ_Selection_Offer(SDL_Wayland_انکڑے_Device *انکڑے_device, SDL_Wayland_انکڑے_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && انکڑے_device->selection_offer && (!انکڑے_device->selection_offer->callback || !انکڑے_device->selection_سروت));
    Wayland_انکڑے_Offer_Destroy(انکڑے_device->selection_offer);
    انکڑے_device->selection_offer = offer;
    إذا (notify) {
        SelectionOfferNotifyFromMIMEs(انکڑے_device, true);
    }
}

فراغ *Wayland_انکڑے_Offer_Get_انکڑے_From_Self(SDL_Wayland_انکڑے_Offer *offer, size_t *لمائی)
{
    إذا (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        أرجع عدم;
    }

    إذا (offer->read_fd < 0) {
        SDL_سیٹ_Error("Pipe closed");
        أرجع عدم;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    فراغ *بفر_2 = عدم;
    طالما (ReadPipe(offer->read_fd, &بفر_2, لمائی, 0) > 0) {
    }

    أرجع بفر_2;
}

bool Wayland_انکڑے_Offer_Request_انکڑے_From_Self(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata)
{
    صحيح pipefd[2];

    إذا (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        أرجع false;
    }

    SDL_Wayland_انکڑے_Device *انکڑے_device = offer->انکڑے_device;
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
        wl_انکڑے_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(انکڑے_device->seat->display->display);
        wl_callback_جوڑو_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(انکڑے_device->seat->display->display);
    } وإلا {
        أرجع SDL_سیٹ_Error("Could not create pipe");
    }

    أرجع true;
}

فراغ *Wayland_انکڑے_Offer_Receive(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type, size_t *لمائی)
{
    صحيح pipefd[2];
    فراغ *بفر_2 = عدم;
    *لمائی = 0;

    إذا (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_Wayland_انکڑے_Device *انکڑے_device = offer->انکڑے_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_انکڑے_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(انکڑے_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &بفر_2, لمائی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } وإلا {
        SDL_سیٹ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *لمائی, بفر_2);

    أرجع بفر_2;
}

فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *لمائی)
{
    صحيح pipefd[2];
    فراغ *بفر_2 = عدم;
    *لمائی = 0;

    إذا (!offer) {
        SDL_سیٹ_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &بفر_2, لمائی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } وإلا {
        SDL_سیٹ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_داخلہ,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *لمائی, بفر_2);

    أرجع بفر_2;
}

bool Wayland_انکڑے_Offer_جوڑو_MIME(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جوڑو(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_جوڑو_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جوڑو(&offer->mimes, mime_type);
}

bool Wayland_انکڑے_Offer_Has_MIME(SDL_Wayland_انکڑے_Offer *offer, ثابت حرف *mime_type)
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

فراغ Wayland_انکڑے_Offer_Destroy(SDL_Wayland_انکڑے_Offer *offer)
{
    إذا (offer) {
        إذا (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        إذا (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_انکڑے_offer_destroy(offer->offer);
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

bool Wayland_انکڑے_Device_سیٹ_Selection_سروت(SDL_Wayland_انکڑے_Device *انکڑے_device, SDL_Wayland_انکڑے_سروت *سروت, ثابت حرف **mime_types, size_t mime_گنتی)
{
    إذا (!انکڑے_device) {
        أرجع SDL_سیٹ_Error("Invalid Data Device");
    }
    إذا (!سروت) {
        أرجع SDL_سیٹ_Error("Invalid source");
    }

    إذا (mime_گنتی) {
        لكل (size_t اشاریہ = 0; اشاریہ < mime_گنتی; ++اشاریہ) {
            ثابت حرف *mime_type = mime_types[اشاریہ];
            wl_انکڑے_سروت_offer(سروت->سروت, mime_type);
        }

        // Advertise the data origin MIME
        wl_انکڑے_سروت_offer(سروت->سروت, SDL_انکڑے_ORIGIN_MIME);

        wl_انکڑے_device_سیٹ_selection(انکڑے_device->انکڑے_device, سروت->سروت, انکڑے_device->seat->آخری_implicit_grab_serial);
        إذا (انکڑے_device->selection_سروت) {
            Wayland_انکڑے_سروت_Destroy(انکڑے_device->selection_سروت);
        }
        انکڑے_device->selection_سروت = سروت;
        سروت->انکڑے_device = انکڑے_device;

    } وإلا {
        Wayland_انکڑے_سروت_Destroy(انکڑے_device->selection_سروت);
        انکڑے_device->selection_سروت = عدم;
        أرجع SDL_سیٹ_Error("No mime data");
    }

    أرجع true;
}

bool Wayland_Primary_Selection_Device_سیٹ_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_سروت *سروت,
                                                ثابت حرف *ثابت *mime_types, size_t mime_گنتی)
{
    إذا (!primary_selection_device) {
        أرجع SDL_سیٹ_Error("Invalid Primary Selection Device");
    }
    إذا (!سروت) {
        أرجع SDL_سیٹ_Error("Invalid source");
    }

    إذا (mime_گنتی) {
        لكل (size_t اشاریہ = 0; اشاریہ < mime_گنتی; ++اشاریہ) {
            ثابت حرف *mime_type = mime_types[اشاریہ];
            zwp_primary_selection_سروت_v1_offer(سروت->سروت, mime_type);
        }

        zwp_primary_selection_device_v1_سیٹ_selection(primary_selection_device->primary_selection_device,
                                                      سروت->سروت,
                                                      primary_selection_device->seat->آخری_implicit_grab_serial);
        إذا (primary_selection_device->selection_سروت) {
            Wayland_Primary_Selection_سروت_Destroy(primary_selection_device->selection_سروت);
        }
        primary_selection_device->selection_سروت = سروت;
        سروت->primary_selection_device = primary_selection_device;
    } وإلا {
        Wayland_Primary_Selection_سروت_Destroy(primary_selection_device->selection_سروت);
        primary_selection_device->selection_سروت = عدم;
        أرجع SDL_سیٹ_Error("No mime data");
    }

    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND

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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

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
#تعریف_کړه DEFAULT_PIPE_TIMEOUT_NS SDL_MS_منزل_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#که_نه_تعریف_شوی HAVE_SIGTIMEDWAIT
#ضمن <errno.h>
#ضمن <time.h>
ساكن صحيح sigtimedwait(ثابت sigset_t *سېټ, siginfo_t *info, ثابت بنية timespec *timeout)
{
    بنية timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    افعل {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        لكل (صحيح signo = 1; signo < NSIG; ++signo) {
            إذا (sigismember(سېټ, signo) && sigismember(&pending, signo)) {
                إذا (!sigwait(سېټ, &signo)) {
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
            اوږد ns = 20000000L; // 2/100ths of a second
            nanosleep(&(بنية timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } طالما (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    أرجع -1;
}
#د_که_پای

ساكن ssize_t WritePipe(صحيح fd, ثابت فراغ *بفر_2, size_t ټول_اوږدتیا, size_t *pos)
{
    ssize_t بایټونه_written = 0;
    ثابت ssize_t اوږدتیا = ټول_اوږدتیا - *pos;

    sigset_t sig_سېټ;
    sigset_t old_sig_سېټ;
    بنية timespec zerotime = { 0 };

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_سېټ);
    sigaddset(&sig_سېټ, SIGPIPE);

#که_تعریف_شوی SDL_تارونه_DISABLED
    sigprocmask(SIG_BLOCK, &sig_سېټ, &old_sig_سېټ);
#وإلا
    pthread_sigmask(SIG_BLOCK, &sig_سېټ, &old_sig_سېټ);
#د_که_پای

    إذا (ready > 0) {
        إذا (اوږدتیا > 0) {
            بایټونه_written = اكتب(fd, (Uint8 *)بفر_2 + *pos, SDL_min(اوږدتیا, PIPE_BUF));
        }

        إذا (بایټونه_written > 0) {
            *pos += بایټونه_written;
        }
    } وإلا إذا (ready == 0) {
        SDL_سېټ_Error("Pipe timeout");
    } وإلا  {
        SDL_سېټ_Error("Pipe poll error");
    }

    sigtimedwait(&sig_سېټ, عدم, &zerotime);

#که_تعریف_شوی SDL_تارونه_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_سېټ, عدم);
#وإلا
    pthread_sigmask(SIG_SETMASK, &old_sig_سېټ, عدم);
#د_که_پای

    أرجع بایټونه_written;
}

ساكن ssize_t ReadPipe(صحيح fd, فراغ **بفر_2, size_t *ټول_اوږدتیا, Sint64 timeout_ns)
{
    فراغ *output_بفر = عدم;
    حرف لنډمهاله[PIPE_BUF];
    ssize_t بایټونه_read = 0;

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    إذا (ready > 0) {
        بایټونه_read = اقرأ(fd, لنډمهاله, حجم(لنډمهاله));
    } وإلا إذا (ready == 0) {
        SDL_سېټ_Error("Pipe timeout");
    } وإلا {
        SDL_سېټ_Error("Pipe poll error");
    }

    إذا (بایټونه_read > 0) {
        ثابت size_t pos = *ټول_اوږدتیا;
        *ټول_اوږدتیا += بایټونه_read;

        ثابت size_t new_بفر_اوږدتیا = *ټول_اوږدتیا + حجم(Uint32);

        إذا (!*بفر_2) {
            output_بفر = SDL_malloc(new_بفر_اوږدتیا);
        } وإلا {
            output_بفر = SDL_realloc(*بفر_2, new_بفر_اوږدتیا);
        }

        إذا (!output_بفر) {
            بایټونه_read = -1;
        } وإلا {
            SDL_memcpy((Uint8 *)output_بفر + pos, لنډمهاله, بایټونه_read);
            SDL_memset((Uint8 *)output_بفر + (new_بفر_اوږدتیا - حجم(Uint32)), 0, حجم(Uint32));

            *بفر_2 = output_بفر;
        }
    }

    أرجع بایټونه_read;
}

ساكن bool MIMEDataListHasType(بنية wl_array *list, ثابت حرف *mime_type)
{
    ثابت حرف **توکی;
    wl_array_for_each(توکی, list) {
        إذا (SDL_strcmp(*توکی, mime_type) == 0) {
            أرجع true;
        }
    }

    أرجع false;
}

ساكن bool MIMEData_List_جمع_کړه(بنية wl_array *list, ثابت حرف *mime_type)
{
    إذا (!MIMEDataListHasType(list, mime_type)) {
        حرف **توکی = WAYLAND_wl_array_جمع_کړه(list, حجم(حرف *));
        *توکی = SDL_strdup(mime_type);
    }

    أرجع true;
}

ساكن فراغ MIMEDataListFree(بنية wl_array *list)
{
    حرف **توکی;
    wl_array_for_each(توکی, list) {
        SDL_free(*توکی);
    }

    WAYLAND_wl_array_release(list);
}

ساكن فراغ معلومات_سرچینه_handle_موخه(فراغ *معلومات, بنية wl_معلومات_سرچینه *wl_معلومات_سرچینه, ثابت حرف *mime_type)
{
}

ساكن فراغ معلومات_سرچینه_handle_send(فراغ *معلومات, بنية wl_معلومات_سرچینه *wl_معلومات_سرچینه, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_معلومات_سرچینه_Send((SDL_Wayland_معلومات_سرچینه *)معلومات, mime_type, fd);
}

ساكن فراغ معلومات_سرچینه_handle_cancelled(فراغ *معلومات, بنية wl_معلومات_سرچینه *wl_معلومات_سرچینه)
{
    SDL_Wayland_معلومات_سرچینه *سرچینه = معلومات;
    إذا (سرچینه) {
        Wayland_معلومات_سرچینه_Destroy(سرچینه);
    }
}

ساكن فراغ معلومات_سرچینه_handle_dnd_drop_performed(فراغ *معلومات, بنية wl_معلومات_سرچینه *wl_معلومات_سرچینه)
{
}

ساكن فراغ معلومات_سرچینه_handle_dnd_پای_ته_رسېدلی(فراغ *معلومات, بنية wl_معلومات_سرچینه *wl_معلومات_سرچینه)
{
    SDL_Wayland_معلومات_سرچینه *سرچینه = معلومات;
    إذا (سرچینه) {
        Wayland_معلومات_سرچینه_Destroy(سرچینه);
    }
}

ساكن فراغ معلومات_سرچینه_handle_action(فراغ *معلومات, بنية wl_معلومات_سرچینه *wl_معلومات_سرچینه, uint32_t dnd_action)
{
}

ساكن ثابت بنية wl_معلومات_سرچینه_listener معلومات_سرچینه_listener = {
    معلومات_سرچینه_handle_موخه,
    معلومات_سرچینه_handle_send,
    معلومات_سرچینه_handle_cancelled,
    معلومات_سرچینه_handle_dnd_drop_performed, // Version 3
    معلومات_سرچینه_handle_dnd_پای_ته_رسېدلی,       // Version 3
    معلومات_سرچینه_handle_action,             // Version 3
};

SDL_Wayland_معلومات_سرچینه *Wayland_معلومات_سرچینه_Create(SDL_Video_معلومات *video_معلومات)
{
    SDL_Wayland_معلومات_سرچینه *معلومات_سرچینه_2 = SDL_calloc(1, حجم(*معلومات_سرچینه_2));
    إذا (!معلومات_سرچینه_2) {
        أرجع عدم;
    }

    بنية wl_معلومات_سرچینه *id = wl_معلومات_device_manager_create_معلومات_سرچینه(video_معلومات->معلومات_device_manager);
    معلومات_سرچینه_2->سرچینه = id;
    wl_معلومات_سرچینه_سېټ_user_معلومات(id, معلومات_سرچینه_2);
    wl_معلومات_سرچینه_جمع_کړه_listener(id, &معلومات_سرچینه_listener, معلومات_سرچینه_2);

    أرجع معلومات_سرچینه_2;
}

ساكن فراغ primary_selection_سرچینه_send(فراغ *معلومات, بنية zwp_primary_selection_سرچینه_v1 *zwp_primary_selection_سرچینه_v1, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_سرچینه_Send((SDL_Wayland_Primary_Selection_سرچینه *)معلومات, mime_type, fd);
}

ساكن فراغ primary_selection_سرچینه_cancelled(فراغ *معلومات, بنية zwp_primary_selection_سرچینه_v1 *zwp_primary_selection_سرچینه_v1)
{
    Wayland_Primary_Selection_سرچینه_Destroy(معلومات);
}

ساكن ثابت بنية zwp_primary_selection_سرچینه_v1_listener primary_selection_سرچینه_listener = {
    primary_selection_سرچینه_send,
    primary_selection_سرچینه_cancelled,
};

SDL_Wayland_Primary_Selection_سرچینه *Wayland_Primary_Selection_سرچینه_Create(SDL_Video_معلومات *video_معلومات)
{
    SDL_Wayland_Primary_Selection_سرچینه *primary_selection_سرچینه = SDL_calloc(1, حجم(*primary_selection_سرچینه));
    إذا (!primary_selection_سرچینه) {
        أرجع عدم;
    }

    بنية zwp_primary_selection_سرچینه_v1 *id = zwp_primary_selection_device_manager_v1_create_سرچینه(video_معلومات->primary_selection_device_manager);
    primary_selection_سرچینه->سرچینه = id;
    zwp_primary_selection_سرچینه_v1_جمع_کړه_listener(id, &primary_selection_سرچینه_listener, primary_selection_سرچینه);

    أرجع primary_selection_سرچینه;
}

ساكن size_t Send_معلومات(ثابت فراغ *معلومات, size_t اوږدتیا, صحيح fd)
{
    size_t پایله = 0;

    إذا (اوږدتیا > 0 && معلومات) {
        طالما (WritePipe(fd, معلومات, اوږدتیا, &پایله) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    أرجع پایله;
}

ssize_t Wayland_معلومات_سرچینه_Send(SDL_Wayland_معلومات_سرچینه *سرچینه, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *معلومات = عدم;
    size_t اوږدتیا = 0;

    إذا (SDL_strcmp(mime_type, SDL_معلومات_ORIGIN_MIME) == 0) {
        معلومات = سرچینه->معلومات_device->id_str;
        اوږدتیا = SDL_strlen(سرچینه->معلومات_device->id_str);
    } وإلا إذا (سرچینه->معلومات_callback) {
        معلومات = سرچینه->معلومات_callback(سرچینه->userdata.معلومات, mime_type, &اوږدتیا);
    }

    أرجع Send_معلومات(معلومات, اوږدتیا, fd);
}

ssize_t Wayland_Primary_Selection_سرچینه_Send(SDL_Wayland_Primary_Selection_سرچینه *سرچینه, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *معلومات = عدم;
    size_t اوږدتیا = 0;

    إذا (سرچینه->معلومات_callback) {
        معلومات = سرچینه->معلومات_callback(سرچینه->userdata.معلومات, mime_type, &اوږدتیا);
    }

    أرجع Send_معلومات(معلومات, اوږدتیا, fd);
}

فراغ Wayland_معلومات_سرچینه_سېټ_Callback(SDL_Wayland_معلومات_سرچینه *سرچینه, SDL_Clipboard_معلومات_Callback معلومات_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence)
{
    إذا (سرچینه) {
        سرچینه->معلومات_callback = معلومات_callback;
        سرچینه->cleanup_callback = cleanup_callback;
        سرچینه->userdata.sequence = sequence;
        سرچینه->userdata.معلومات = userdata;
    }
}

فراغ Wayland_Primary_Selection_سرچینه_سېټ_Callback(SDL_Wayland_Primary_Selection_سرچینه *سرچینه, SDL_Clipboard_معلومات_Callback معلومات_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata)
{
    إذا (سرچینه) {
        سرچینه->معلومات_callback = معلومات_callback;
        سرچینه->cleanup_callback = cleanup_callback;
        سرچینه->userdata.sequence = 0;
        سرچینه->userdata.معلومات = userdata;
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

فراغ *Wayland_معلومات_سرچینه_Get_معلومات(SDL_Wayland_معلومات_سرچینه *سرچینه, ثابت حرف *mime_type, size_t *اوږدتیا)
{
    فراغ *بفر_2 = عدم;
    *اوږدتیا = 0;

    إذا (!سرچینه) {
        SDL_سېټ_Error("Invalid data source");
    } وإلا إذا (سرچینه->معلومات_callback) {
        ثابت فراغ *دننی_بفر = سرچینه->معلومات_callback(سرچینه->userdata.معلومات, mime_type, اوږدتیا);
        بفر_2 = Clone_معلومات_بفر(دننی_بفر, اوږدتیا);
    }

    أرجع بفر_2;
}

فراغ *Wayland_Primary_Selection_سرچینه_Get_معلومات(SDL_Wayland_Primary_Selection_سرچینه *سرچینه, ثابت حرف *mime_type, size_t *اوږدتیا)
{
    فراغ *بفر_2 = عدم;
    *اوږدتیا = 0;

    إذا (!سرچینه) {
        SDL_سېټ_Error("Invalid primary selection source");
    } وإلا إذا (سرچینه->معلومات_callback) {
        ثابت فراغ *دننی_بفر = سرچینه->معلومات_callback(سرچینه->userdata.معلومات, mime_type, اوږدتیا);
        بفر_2 = Clone_معلومات_بفر(دننی_بفر, اوږدتیا);
    }

    أرجع بفر_2;
}

فراغ Wayland_معلومات_سرچینه_Destroy(SDL_Wayland_معلومات_سرچینه *سرچینه)
{
    إذا (سرچینه) {
        SDL_Wayland_معلومات_Device *معلومات_device = سرچینه->معلومات_device;
        إذا (معلومات_device && (معلومات_device->selection_سرچینه == سرچینه)) {
            معلومات_device->selection_سرچینه = عدم;
        }
        wl_معلومات_سرچینه_destroy(سرچینه->سرچینه);
        إذا (سرچینه->userdata.sequence) {
            SDL_Cancel_Clipboard_معلومات(سرچینه->userdata.sequence);
        } وإلا إذا (سرچینه->cleanup_callback) {
            سرچینه->cleanup_callback(سرچینه->userdata.معلومات);
        }
        SDL_free(سرچینه);
    }
}

فراغ Wayland_Primary_Selection_سرچینه_Destroy(SDL_Wayland_Primary_Selection_سرچینه *سرچینه)
{
    إذا (سرچینه) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = سرچینه->primary_selection_device;
        إذا (primary_selection_device && (primary_selection_device->selection_سرچینه == سرچینه)) {
            primary_selection_device->selection_سرچینه = عدم;
        }
        zwp_primary_selection_سرچینه_v1_destroy(سرچینه->سرچینه);
        إذا (سرچینه->cleanup_callback) {
            سرچینه->cleanup_callback(سرچینه->userdata.معلومات);
        }
        SDL_free(سرچینه);
    }
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_معلومات_Device *معلومات_device, bool check_origin);

ساكن فراغ offer_سرچینه_بشپړ_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    إذا (!callback) {
        أرجع;
    }

    SDL_Wayland_معلومات_Offer *offer = (SDL_Wayland_معلومات_Offer *)معلومات;
    حرف *id = عدم;
    size_t اوږدتیا = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = عدم;

    طالما (ReadPipe(offer->read_fd, (فراغ **)&id, &اوږدتیا, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    إذا (id) {
        ثابت bool سرچینه_is_external = SDL_strncmp(offer->معلومات_device->id_str, id, اوږدتیا) != 0;
        SDL_free(id);
        إذا (سرچینه_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->معلومات_device, false);
        } وإلا {
            // Recursive data offer; just destroy it.
            SDL_Wayland_معلومات_Device *معلومات_device = offer->معلومات_device;
            Wayland_معلومات_Offer_Destroy(offer);
            معلومات_device->selection_offer = عدم;
        }
    }
}

ساكن ثابت بنية wl_callback_listener offer_سرچینه_listener = {
    offer_سرچینه_بشپړ_handler
};

ساكن فراغ UpdateSeatOffers(SDL_Wayland_معلومات_Device *معلومات_device)
{
    SDL_WaylandSeat *offer_seat = معلومات_device->seat;
    SDL_Video_معلومات *video_معلومات = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_معلومات->seat_list, link) {
        إذا (s->معلومات_device) {
            Wayland_معلومات_سرچینه_Destroy(s->معلومات_device->selection_سرچینه);
            s->معلومات_device->selection_سرچینه = عدم;

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
    size_t عدد_formats = 0;

    إذا (offer) {
        size_t alloc_اندازه_2 = 0;

        // Do a first pass to compute allocation size.
        ثابت حرف **توکی;
        wl_array_for_each(توکی, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            إذا (check_origin && SDL_strcmp(*توکی, SDL_معلومات_ORIGIN_MIME) == 0) {
                Wayland_معلومات_Offer_Request_معلومات_From_Self(offer, *توکی, &offer_سرچینه_listener, offer);
                أرجع;
            }

            ++عدد_formats;
            alloc_اندازه_2 += SDL_strlen(*توکی) + 1;
        }

        alloc_اندازه_2 += (عدد_formats + 1) * حجم(حرف *);

        new_mime_types = SDL_Allocate_Temporary_حافظه(alloc_اندازه_2);
        إذا (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_ننوت, "unable to allocate new_mime_types");
            أرجع;
        }

        // Second pass to fill.
        حرف *strPtr = (حرف *)(new_mime_types + عدد_formats + 1);
        alloc_اندازه_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        توکی = عدم;
        صحيح i = 0;
        wl_array_for_each(توکی, &offer->mimes) {
            إذا (!توکی) {
                استمر;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *توکی, alloc_اندازه_2) + 1;
            strPtr += len;
            alloc_اندازه_2 -= len;
        }
        new_mime_types[عدد_formats] = عدم;
    }

    UpdateSeatOffers(معلومات_device);
    SDL_SendClipboardUpdate(false, new_mime_types, عدد_formats);
}

فراغ Wayland_معلومات_Device_سېټ_Selection_Offer(SDL_Wayland_معلومات_Device *معلومات_device, SDL_Wayland_معلومات_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && معلومات_device->selection_offer && (!معلومات_device->selection_offer->callback || !معلومات_device->selection_سرچینه));
    Wayland_معلومات_Offer_Destroy(معلومات_device->selection_offer);
    معلومات_device->selection_offer = offer;
    إذا (notify) {
        SelectionOfferNotifyFromMIMEs(معلومات_device, true);
    }
}

فراغ *Wayland_معلومات_Offer_Get_معلومات_From_Self(SDL_Wayland_معلومات_Offer *offer, size_t *اوږدتیا)
{
    إذا (!offer) {
        SDL_سېټ_Error("Invalid data offer");
        أرجع عدم;
    }

    إذا (offer->read_fd < 0) {
        SDL_سېټ_Error("Pipe closed");
        أرجع عدم;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    فراغ *بفر_2 = عدم;
    طالما (ReadPipe(offer->read_fd, &بفر_2, اوږدتیا, 0) > 0) {
    }

    أرجع بفر_2;
}

bool Wayland_معلومات_Offer_Request_معلومات_From_Self(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata)
{
    صحيح pipefd[2];

    إذا (!offer) {
        SDL_سېټ_Error("Invalid data offer");
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
        wl_callback_جمع_کړه_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(معلومات_device->seat->display->display);
    } وإلا {
        أرجع SDL_سېټ_Error("Could not create pipe");
    }

    أرجع true;
}

فراغ *Wayland_معلومات_Offer_Receive(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type, size_t *اوږدتیا)
{
    صحيح pipefd[2];
    فراغ *بفر_2 = عدم;
    *اوږدتیا = 0;

    إذا (!offer) {
        SDL_سېټ_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_Wayland_معلومات_Device *معلومات_device = offer->معلومات_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_معلومات_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(معلومات_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &بفر_2, اوږدتیا, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } وإلا {
        SDL_سېټ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *اوږدتیا, بفر_2);

    أرجع بفر_2;
}

فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *اوږدتیا)
{
    صحيح pipefd[2];
    فراغ *بفر_2 = عدم;
    *اوږدتیا = 0;

    إذا (!offer) {
        SDL_سېټ_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &بفر_2, اوږدتیا, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } وإلا {
        SDL_سېټ_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ننوت,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *اوږدتیا, بفر_2);

    أرجع بفر_2;
}

bool Wayland_معلومات_Offer_جمع_کړه_MIME(SDL_Wayland_معلومات_Offer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جمع_کړه(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_جمع_کړه_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جمع_کړه(&offer->mimes, mime_type);
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

bool Wayland_معلومات_Device_سېټ_Selection_سرچینه(SDL_Wayland_معلومات_Device *معلومات_device, SDL_Wayland_معلومات_سرچینه *سرچینه, ثابت حرف **mime_types, size_t mime_شمېر)
{
    إذا (!معلومات_device) {
        أرجع SDL_سېټ_Error("Invalid Data Device");
    }
    إذا (!سرچینه) {
        أرجع SDL_سېټ_Error("Invalid source");
    }

    إذا (mime_شمېر) {
        لكل (size_t شاخص = 0; شاخص < mime_شمېر; ++شاخص) {
            ثابت حرف *mime_type = mime_types[شاخص];
            wl_معلومات_سرچینه_offer(سرچینه->سرچینه, mime_type);
        }

        // Advertise the data origin MIME
        wl_معلومات_سرچینه_offer(سرچینه->سرچینه, SDL_معلومات_ORIGIN_MIME);

        wl_معلومات_device_سېټ_selection(معلومات_device->معلومات_device, سرچینه->سرچینه, معلومات_device->seat->وروستی_implicit_grab_serial);
        إذا (معلومات_device->selection_سرچینه) {
            Wayland_معلومات_سرچینه_Destroy(معلومات_device->selection_سرچینه);
        }
        معلومات_device->selection_سرچینه = سرچینه;
        سرچینه->معلومات_device = معلومات_device;

    } وإلا {
        Wayland_معلومات_سرچینه_Destroy(معلومات_device->selection_سرچینه);
        معلومات_device->selection_سرچینه = عدم;
        أرجع SDL_سېټ_Error("No mime data");
    }

    أرجع true;
}

bool Wayland_Primary_Selection_Device_سېټ_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_سرچینه *سرچینه,
                                                ثابت حرف *ثابت *mime_types, size_t mime_شمېر)
{
    إذا (!primary_selection_device) {
        أرجع SDL_سېټ_Error("Invalid Primary Selection Device");
    }
    إذا (!سرچینه) {
        أرجع SDL_سېټ_Error("Invalid source");
    }

    إذا (mime_شمېر) {
        لكل (size_t شاخص = 0; شاخص < mime_شمېر; ++شاخص) {
            ثابت حرف *mime_type = mime_types[شاخص];
            zwp_primary_selection_سرچینه_v1_offer(سرچینه->سرچینه, mime_type);
        }

        zwp_primary_selection_device_v1_سېټ_selection(primary_selection_device->primary_selection_device,
                                                      سرچینه->سرچینه,
                                                      primary_selection_device->seat->وروستی_implicit_grab_serial);
        إذا (primary_selection_device->selection_سرچینه) {
            Wayland_Primary_Selection_سرچینه_Destroy(primary_selection_device->selection_سرچینه);
        }
        primary_selection_device->selection_سرچینه = سرچینه;
        سرچینه->primary_selection_device = primary_selection_device;
    } وإلا {
        Wayland_Primary_Selection_سرچینه_Destroy(primary_selection_device->selection_سرچینه);
        primary_selection_device->selection_سرچینه = عدم;
        أرجع SDL_سېټ_Error("No mime data");
    }

    أرجع true;
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND

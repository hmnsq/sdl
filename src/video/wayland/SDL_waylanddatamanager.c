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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

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
#تعریف_کن DEFAULT_PIPE_TIMEOUT_NS SDL_MS_مقصد_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#اگر_تعریف_نشده HAVE_SIGTIMEDWAIT
#ضمن <errno.h>
#ضمن <time.h>
ساكن صحيح sigtimedwait(ثابت sigset_t *مجموعه, siginfo_t *info, ثابت بنية timespec *timeout)
{
    بنية timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    افعل {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        لكل (صحيح signo = 1; signo < NSIG; ++signo) {
            إذا (sigismember(مجموعه, signo) && sigismember(&pending, signo)) {
                إذا (!sigwait(مجموعه, &signo)) {
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
            دراز ns = 20000000L; // 2/100ths of a second
            nanosleep(&(بنية timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } طالما (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    أرجع -1;
}
#پایان_اگر

ساكن ssize_t WritePipe(صحيح fd, ثابت فراغ *میانگیر_2, size_t مجموع_درازی, size_t *pos)
{
    ssize_t بایتها_written = 0;
    ثابت ssize_t درازی = مجموع_درازی - *pos;

    sigset_t sig_مجموعه;
    sigset_t old_sig_مجموعه;
    بنية timespec zerotime = { 0 };

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_مجموعه);
    sigaddset(&sig_مجموعه, SIGPIPE);

#اگر_تعریف_شده SDL_نخها_DISABLED
    sigprocmask(SIG_BLOCK, &sig_مجموعه, &old_sig_مجموعه);
#وإلا
    pthread_sigmask(SIG_BLOCK, &sig_مجموعه, &old_sig_مجموعه);
#پایان_اگر

    إذا (ready > 0) {
        إذا (درازی > 0) {
            بایتها_written = اكتب(fd, (Uint8 *)میانگیر_2 + *pos, SDL_min(درازی, PIPE_BUF));
        }

        إذا (بایتها_written > 0) {
            *pos += بایتها_written;
        }
    } وإلا إذا (ready == 0) {
        SDL_مجموعه_Error("Pipe timeout");
    } وإلا  {
        SDL_مجموعه_Error("Pipe poll error");
    }

    sigtimedwait(&sig_مجموعه, عدم, &zerotime);

#اگر_تعریف_شده SDL_نخها_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_مجموعه, عدم);
#وإلا
    pthread_sigmask(SIG_SETMASK, &old_sig_مجموعه, عدم);
#پایان_اگر

    أرجع بایتها_written;
}

ساكن ssize_t ReadPipe(صحيح fd, فراغ **میانگیر_2, size_t *مجموع_درازی, Sint64 timeout_ns)
{
    فراغ *output_میانگیر = عدم;
    حرف موقت[PIPE_BUF];
    ssize_t بایتها_read = 0;

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    إذا (ready > 0) {
        بایتها_read = اقرأ(fd, موقت, حجم(موقت));
    } وإلا إذا (ready == 0) {
        SDL_مجموعه_Error("Pipe timeout");
    } وإلا {
        SDL_مجموعه_Error("Pipe poll error");
    }

    إذا (بایتها_read > 0) {
        ثابت size_t pos = *مجموع_درازی;
        *مجموع_درازی += بایتها_read;

        ثابت size_t new_میانگیر_درازی = *مجموع_درازی + حجم(Uint32);

        إذا (!*میانگیر_2) {
            output_میانگیر = SDL_malloc(new_میانگیر_درازی);
        } وإلا {
            output_میانگیر = SDL_realloc(*میانگیر_2, new_میانگیر_درازی);
        }

        إذا (!output_میانگیر) {
            بایتها_read = -1;
        } وإلا {
            SDL_memcpy((Uint8 *)output_میانگیر + pos, موقت, بایتها_read);
            SDL_memset((Uint8 *)output_میانگیر + (new_میانگیر_درازی - حجم(Uint32)), 0, حجم(Uint32));

            *میانگیر_2 = output_میانگیر;
        }
    }

    أرجع بایتها_read;
}

ساكن bool MIMEDataListHasType(بنية wl_array *list, ثابت حرف *mime_type)
{
    ثابت حرف **قلم;
    wl_array_for_each(قلم, list) {
        إذا (SDL_strcmp(*قلم, mime_type) == 0) {
            أرجع true;
        }
    }

    أرجع false;
}

ساكن bool MIMEData_List_جمع_کن(بنية wl_array *list, ثابت حرف *mime_type)
{
    إذا (!MIMEDataListHasType(list, mime_type)) {
        حرف **قلم = WAYLAND_wl_array_جمع_کن(list, حجم(حرف *));
        *قلم = SDL_strdup(mime_type);
    }

    أرجع true;
}

ساكن فراغ MIMEDataListFree(بنية wl_array *list)
{
    حرف **قلم;
    wl_array_for_each(قلم, list) {
        SDL_free(*قلم);
    }

    WAYLAND_wl_array_release(list);
}

ساكن فراغ داده_منبع_handle_هدف(فراغ *داده, بنية wl_داده_منبع *wl_داده_منبع, ثابت حرف *mime_type)
{
}

ساكن فراغ داده_منبع_handle_send(فراغ *داده, بنية wl_داده_منبع *wl_داده_منبع, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_داده_منبع_Send((SDL_Wayland_داده_منبع *)داده, mime_type, fd);
}

ساكن فراغ داده_منبع_handle_cancelled(فراغ *داده, بنية wl_داده_منبع *wl_داده_منبع)
{
    SDL_Wayland_داده_منبع *منبع = داده;
    إذا (منبع) {
        Wayland_داده_منبع_Destroy(منبع);
    }
}

ساكن فراغ داده_منبع_handle_dnd_drop_performed(فراغ *داده, بنية wl_داده_منبع *wl_داده_منبع)
{
}

ساكن فراغ داده_منبع_handle_dnd_پایانیافته(فراغ *داده, بنية wl_داده_منبع *wl_داده_منبع)
{
    SDL_Wayland_داده_منبع *منبع = داده;
    إذا (منبع) {
        Wayland_داده_منبع_Destroy(منبع);
    }
}

ساكن فراغ داده_منبع_handle_action(فراغ *داده, بنية wl_داده_منبع *wl_داده_منبع, uint32_t dnd_action)
{
}

ساكن ثابت بنية wl_داده_منبع_listener داده_منبع_listener = {
    داده_منبع_handle_هدف,
    داده_منبع_handle_send,
    داده_منبع_handle_cancelled,
    داده_منبع_handle_dnd_drop_performed, // Version 3
    داده_منبع_handle_dnd_پایانیافته,       // Version 3
    داده_منبع_handle_action,             // Version 3
};

SDL_Wayland_داده_منبع *Wayland_داده_منبع_Create(SDL_Video_داده *video_داده)
{
    SDL_Wayland_داده_منبع *داده_منبع_2 = SDL_calloc(1, حجم(*داده_منبع_2));
    إذا (!داده_منبع_2) {
        أرجع عدم;
    }

    بنية wl_داده_منبع *id = wl_داده_device_manager_create_داده_منبع(video_داده->داده_device_manager);
    داده_منبع_2->منبع = id;
    wl_داده_منبع_مجموعه_user_داده(id, داده_منبع_2);
    wl_داده_منبع_جمع_کن_listener(id, &داده_منبع_listener, داده_منبع_2);

    أرجع داده_منبع_2;
}

ساكن فراغ primary_selection_منبع_send(فراغ *داده, بنية zwp_primary_selection_منبع_v1 *zwp_primary_selection_منبع_v1, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_Primary_Selection_منبع_Send((SDL_Wayland_Primary_Selection_منبع *)داده, mime_type, fd);
}

ساكن فراغ primary_selection_منبع_cancelled(فراغ *داده, بنية zwp_primary_selection_منبع_v1 *zwp_primary_selection_منبع_v1)
{
    Wayland_Primary_Selection_منبع_Destroy(داده);
}

ساكن ثابت بنية zwp_primary_selection_منبع_v1_listener primary_selection_منبع_listener = {
    primary_selection_منبع_send,
    primary_selection_منبع_cancelled,
};

SDL_Wayland_Primary_Selection_منبع *Wayland_Primary_Selection_منبع_Create(SDL_Video_داده *video_داده)
{
    SDL_Wayland_Primary_Selection_منبع *primary_selection_منبع = SDL_calloc(1, حجم(*primary_selection_منبع));
    إذا (!primary_selection_منبع) {
        أرجع عدم;
    }

    بنية zwp_primary_selection_منبع_v1 *id = zwp_primary_selection_device_manager_v1_create_منبع(video_داده->primary_selection_device_manager);
    primary_selection_منبع->منبع = id;
    zwp_primary_selection_منبع_v1_جمع_کن_listener(id, &primary_selection_منبع_listener, primary_selection_منبع);

    أرجع primary_selection_منبع;
}

ساكن size_t Send_داده(ثابت فراغ *داده, size_t درازی, صحيح fd)
{
    size_t نتیجه = 0;

    إذا (درازی > 0 && داده) {
        طالما (WritePipe(fd, داده, درازی, &نتیجه) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    أرجع نتیجه;
}

ssize_t Wayland_داده_منبع_Send(SDL_Wayland_داده_منبع *منبع, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *داده = عدم;
    size_t درازی = 0;

    إذا (SDL_strcmp(mime_type, SDL_داده_ORIGIN_MIME) == 0) {
        داده = منبع->داده_device->id_str;
        درازی = SDL_strlen(منبع->داده_device->id_str);
    } وإلا إذا (منبع->داده_callback) {
        داده = منبع->داده_callback(منبع->userdata.داده, mime_type, &درازی);
    }

    أرجع Send_داده(داده, درازی, fd);
}

ssize_t Wayland_Primary_Selection_منبع_Send(SDL_Wayland_Primary_Selection_منبع *منبع, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *داده = عدم;
    size_t درازی = 0;

    إذا (منبع->داده_callback) {
        داده = منبع->داده_callback(منبع->userdata.داده, mime_type, &درازی);
    }

    أرجع Send_داده(داده, درازی, fd);
}

فراغ Wayland_داده_منبع_مجموعه_Callback(SDL_Wayland_داده_منبع *منبع, SDL_Clipboard_داده_Callback داده_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence)
{
    إذا (منبع) {
        منبع->داده_callback = داده_callback;
        منبع->cleanup_callback = cleanup_callback;
        منبع->userdata.sequence = sequence;
        منبع->userdata.داده = userdata;
    }
}

فراغ Wayland_Primary_Selection_منبع_مجموعه_Callback(SDL_Wayland_Primary_Selection_منبع *منبع, SDL_Clipboard_داده_Callback داده_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata)
{
    إذا (منبع) {
        منبع->داده_callback = داده_callback;
        منبع->cleanup_callback = cleanup_callback;
        منبع->userdata.sequence = 0;
        منبع->userdata.داده = userdata;
    }
}

ساكن فراغ *Clone_داده_میانگیر(ثابت فراغ *میانگیر_2, ثابت size_t *len)
{
    فراغ *clone = عدم;
    إذا (*len > 0 && میانگیر_2) {
        clone = SDL_malloc((*len)+حجم(Uint32));
        إذا (clone) {
            SDL_memcpy(clone, میانگیر_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, حجم(Uint32));
        }
    }
    أرجع clone;
}

فراغ *Wayland_داده_منبع_Get_داده(SDL_Wayland_داده_منبع *منبع, ثابت حرف *mime_type, size_t *درازی)
{
    فراغ *میانگیر_2 = عدم;
    *درازی = 0;

    إذا (!منبع) {
        SDL_مجموعه_Error("Invalid data source");
    } وإلا إذا (منبع->داده_callback) {
        ثابت فراغ *داخلی_میانگیر = منبع->داده_callback(منبع->userdata.داده, mime_type, درازی);
        میانگیر_2 = Clone_داده_میانگیر(داخلی_میانگیر, درازی);
    }

    أرجع میانگیر_2;
}

فراغ *Wayland_Primary_Selection_منبع_Get_داده(SDL_Wayland_Primary_Selection_منبع *منبع, ثابت حرف *mime_type, size_t *درازی)
{
    فراغ *میانگیر_2 = عدم;
    *درازی = 0;

    إذا (!منبع) {
        SDL_مجموعه_Error("Invalid primary selection source");
    } وإلا إذا (منبع->داده_callback) {
        ثابت فراغ *داخلی_میانگیر = منبع->داده_callback(منبع->userdata.داده, mime_type, درازی);
        میانگیر_2 = Clone_داده_میانگیر(داخلی_میانگیر, درازی);
    }

    أرجع میانگیر_2;
}

فراغ Wayland_داده_منبع_Destroy(SDL_Wayland_داده_منبع *منبع)
{
    إذا (منبع) {
        SDL_Wayland_داده_Device *داده_device = منبع->داده_device;
        إذا (داده_device && (داده_device->selection_منبع == منبع)) {
            داده_device->selection_منبع = عدم;
        }
        wl_داده_منبع_destroy(منبع->منبع);
        إذا (منبع->userdata.sequence) {
            SDL_Cancel_Clipboard_داده(منبع->userdata.sequence);
        } وإلا إذا (منبع->cleanup_callback) {
            منبع->cleanup_callback(منبع->userdata.داده);
        }
        SDL_free(منبع);
    }
}

فراغ Wayland_Primary_Selection_منبع_Destroy(SDL_Wayland_Primary_Selection_منبع *منبع)
{
    إذا (منبع) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = منبع->primary_selection_device;
        إذا (primary_selection_device && (primary_selection_device->selection_منبع == منبع)) {
            primary_selection_device->selection_منبع = عدم;
        }
        zwp_primary_selection_منبع_v1_destroy(منبع->منبع);
        إذا (منبع->cleanup_callback) {
            منبع->cleanup_callback(منبع->userdata.داده);
        }
        SDL_free(منبع);
    }
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_داده_Device *داده_device, bool check_origin);

ساكن فراغ offer_منبع_انجامشده_handler(فراغ *داده, بنية wl_callback *callback, uint32_t callback_داده)
{
    إذا (!callback) {
        أرجع;
    }

    SDL_Wayland_داده_Offer *offer = (SDL_Wayland_داده_Offer *)داده;
    حرف *id = عدم;
    size_t درازی = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = عدم;

    طالما (ReadPipe(offer->read_fd, (فراغ **)&id, &درازی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    إذا (id) {
        ثابت bool منبع_is_external = SDL_strncmp(offer->داده_device->id_str, id, درازی) != 0;
        SDL_free(id);
        إذا (منبع_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->داده_device, false);
        } وإلا {
            // Recursive data offer; just destroy it.
            SDL_Wayland_داده_Device *داده_device = offer->داده_device;
            Wayland_داده_Offer_Destroy(offer);
            داده_device->selection_offer = عدم;
        }
    }
}

ساكن ثابت بنية wl_callback_listener offer_منبع_listener = {
    offer_منبع_انجامشده_handler
};

ساكن فراغ UpdateSeatOffers(SDL_Wayland_داده_Device *داده_device)
{
    SDL_WaylandSeat *offer_seat = داده_device->seat;
    SDL_Video_داده *video_داده = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_داده->seat_list, link) {
        إذا (s->داده_device) {
            Wayland_داده_منبع_Destroy(s->داده_device->selection_منبع);
            s->داده_device->selection_منبع = عدم;

            // Don't clear the offer that is about to be set.
            إذا (s != offer_seat) {
                Wayland_داده_Offer_Destroy(s->داده_device->selection_offer);
                s->داده_device->selection_offer = عدم;
            }
        }
    }

    video_داده->current_داده_offer_seat = offer_seat;
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_Wayland_داده_Device *داده_device, bool check_origin)
{
    SDL_Wayland_داده_Offer *offer = داده_device->selection_offer;
    حرف **new_mime_types = عدم;
    size_t رقم_formats = 0;

    إذا (offer) {
        size_t alloc_اندازه_2 = 0;

        // Do a first pass to compute allocation size.
        ثابت حرف **قلم;
        wl_array_for_each(قلم, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            إذا (check_origin && SDL_strcmp(*قلم, SDL_داده_ORIGIN_MIME) == 0) {
                Wayland_داده_Offer_Request_داده_From_Self(offer, *قلم, &offer_منبع_listener, offer);
                أرجع;
            }

            ++رقم_formats;
            alloc_اندازه_2 += SDL_strlen(*قلم) + 1;
        }

        alloc_اندازه_2 += (رقم_formats + 1) * حجم(حرف *);

        new_mime_types = SDL_Allocate_Temporary_حافظه(alloc_اندازه_2);
        إذا (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_درون_داد, "unable to allocate new_mime_types");
            أرجع;
        }

        // Second pass to fill.
        حرف *strPtr = (حرف *)(new_mime_types + رقم_formats + 1);
        alloc_اندازه_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        قلم = عدم;
        صحيح i = 0;
        wl_array_for_each(قلم, &offer->mimes) {
            إذا (!قلم) {
                استمر;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *قلم, alloc_اندازه_2) + 1;
            strPtr += len;
            alloc_اندازه_2 -= len;
        }
        new_mime_types[رقم_formats] = عدم;
    }

    UpdateSeatOffers(داده_device);
    SDL_SendClipboardUpdate(false, new_mime_types, رقم_formats);
}

فراغ Wayland_داده_Device_مجموعه_Selection_Offer(SDL_Wayland_داده_Device *داده_device, SDL_Wayland_داده_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && داده_device->selection_offer && (!داده_device->selection_offer->callback || !داده_device->selection_منبع));
    Wayland_داده_Offer_Destroy(داده_device->selection_offer);
    داده_device->selection_offer = offer;
    إذا (notify) {
        SelectionOfferNotifyFromMIMEs(داده_device, true);
    }
}

فراغ *Wayland_داده_Offer_Get_داده_From_Self(SDL_Wayland_داده_Offer *offer, size_t *درازی)
{
    إذا (!offer) {
        SDL_مجموعه_Error("Invalid data offer");
        أرجع عدم;
    }

    إذا (offer->read_fd < 0) {
        SDL_مجموعه_Error("Pipe closed");
        أرجع عدم;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    فراغ *میانگیر_2 = عدم;
    طالما (ReadPipe(offer->read_fd, &میانگیر_2, درازی, 0) > 0) {
    }

    أرجع میانگیر_2;
}

bool Wayland_داده_Offer_Request_داده_From_Self(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata)
{
    صحيح pipefd[2];

    إذا (!offer) {
        SDL_مجموعه_Error("Invalid data offer");
        أرجع false;
    }

    SDL_Wayland_داده_Device *داده_device = offer->داده_device;
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
        wl_داده_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(داده_device->seat->display->display);
        wl_callback_جمع_کن_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(داده_device->seat->display->display);
    } وإلا {
        أرجع SDL_مجموعه_Error("Could not create pipe");
    }

    أرجع true;
}

فراغ *Wayland_داده_Offer_Receive(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type, size_t *درازی)
{
    صحيح pipefd[2];
    فراغ *میانگیر_2 = عدم;
    *درازی = 0;

    إذا (!offer) {
        SDL_مجموعه_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_Wayland_داده_Device *داده_device = offer->داده_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_داده_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(داده_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &میانگیر_2, درازی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } وإلا {
        SDL_مجموعه_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *درازی, میانگیر_2);

    أرجع میانگیر_2;
}

فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *درازی)
{
    صحيح pipefd[2];
    فراغ *میانگیر_2 = عدم;
    *درازی = 0;

    إذا (!offer) {
        SDL_مجموعه_Error("Invalid data offer");
        أرجع عدم;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    إذا (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &میانگیر_2, درازی, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } وإلا {
        SDL_مجموعه_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *درازی, میانگیر_2);

    أرجع میانگیر_2;
}

bool Wayland_داده_Offer_جمع_کن_MIME(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جمع_کن(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_جمع_کن_MIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEData_List_جمع_کن(&offer->mimes, mime_type);
}

bool Wayland_داده_Offer_Has_MIME(SDL_Wayland_داده_Offer *offer, ثابت حرف *mime_type)
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

فراغ Wayland_داده_Offer_Destroy(SDL_Wayland_داده_Offer *offer)
{
    إذا (offer) {
        إذا (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        إذا (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_داده_offer_destroy(offer->offer);
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

bool Wayland_داده_Device_مجموعه_Selection_منبع(SDL_Wayland_داده_Device *داده_device, SDL_Wayland_داده_منبع *منبع, ثابت حرف **mime_types, size_t mime_شمار)
{
    إذا (!داده_device) {
        أرجع SDL_مجموعه_Error("Invalid Data Device");
    }
    إذا (!منبع) {
        أرجع SDL_مجموعه_Error("Invalid source");
    }

    إذا (mime_شمار) {
        لكل (size_t شاخص = 0; شاخص < mime_شمار; ++شاخص) {
            ثابت حرف *mime_type = mime_types[شاخص];
            wl_داده_منبع_offer(منبع->منبع, mime_type);
        }

        // Advertise the data origin MIME
        wl_داده_منبع_offer(منبع->منبع, SDL_داده_ORIGIN_MIME);

        wl_داده_device_مجموعه_selection(داده_device->داده_device, منبع->منبع, داده_device->seat->آخرین_implicit_grab_serial);
        إذا (داده_device->selection_منبع) {
            Wayland_داده_منبع_Destroy(داده_device->selection_منبع);
        }
        داده_device->selection_منبع = منبع;
        منبع->داده_device = داده_device;

    } وإلا {
        Wayland_داده_منبع_Destroy(داده_device->selection_منبع);
        داده_device->selection_منبع = عدم;
        أرجع SDL_مجموعه_Error("No mime data");
    }

    أرجع true;
}

bool Wayland_Primary_Selection_Device_مجموعه_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_Wayland_Primary_Selection_منبع *منبع,
                                                ثابت حرف *ثابت *mime_types, size_t mime_شمار)
{
    إذا (!primary_selection_device) {
        أرجع SDL_مجموعه_Error("Invalid Primary Selection Device");
    }
    إذا (!منبع) {
        أرجع SDL_مجموعه_Error("Invalid source");
    }

    إذا (mime_شمار) {
        لكل (size_t شاخص = 0; شاخص < mime_شمار; ++شاخص) {
            ثابت حرف *mime_type = mime_types[شاخص];
            zwp_primary_selection_منبع_v1_offer(منبع->منبع, mime_type);
        }

        zwp_primary_selection_device_v1_مجموعه_selection(primary_selection_device->primary_selection_device,
                                                      منبع->منبع,
                                                      primary_selection_device->seat->آخرین_implicit_grab_serial);
        إذا (primary_selection_device->selection_منبع) {
            Wayland_Primary_Selection_منبع_Destroy(primary_selection_device->selection_منبع);
        }
        primary_selection_device->selection_منبع = منبع;
        منبع->primary_selection_device = primary_selection_device;
    } وإلا {
        Wayland_Primary_Selection_منبع_Destroy(primary_selection_device->selection_منبع);
        primary_selection_device->selection_منبع = عدم;
        أرجع SDL_مجموعه_Error("No mime data");
    }

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND

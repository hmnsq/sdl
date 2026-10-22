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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <unistd.h>
#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <signal.h>

#অন্তর্ভাব "../../core/unix/SDL_poll.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../SDL_clipboard_c.h"

#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandevents_c.h"
#অন্তর্ভাব "SDL_waylanddatamanager.h"
#অন্তর্ভাব "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <time.h>
স্থির পূর্ণসংখ্যা sigtimedwait(ধ্রুবক sigset_t *set, siginfo_t *info, ধ্রুবক কাঠামো timespec *timeout)
{
    কাঠামো timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    করো {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        জন্য (পূর্ণসংখ্যা signo = 1; signo < NSIG; ++signo) {
            যদি (sigismember(set, signo) && sigismember(&pending, signo)) {
                যদি (!sigwait(set, &signo)) {
                    যদি (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    ফেরত signo;
                } অন্যথা {
                    ফেরত -1;
                }
            }
        }

        যদি (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(কাঠামো timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } যখন (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    ফেরত -1;
}
#endif

স্থির ssize_t WritePipe(পূর্ণসংখ্যা fd, ধ্রুবক শূন্য *বাফার_2, size_t যোগ_দৈর্ঘ্য, size_t *pos)
{
    ssize_t bytes_written = 0;
    ধ্রুবক ssize_t দৈর্ঘ্য = যোগ_দৈর্ঘ্য - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    কাঠামো timespec zerotime = { 0 };

    ধ্রুবক পূর্ণসংখ্যা ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#অন্যথা
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    যদি (ready > 0) {
        যদি (দৈর্ঘ্য > 0) {
            bytes_written = লিখ(fd, (Uint8 *)বাফার_2 + *pos, SDL_min(দৈর্ঘ্য, PIPE_BUF));
        }

        যদি (bytes_written > 0) {
            *pos += bytes_written;
        }
    } অন্যথা যদি (ready == 0) {
        SDL_SetError("Pipe timeout");
    } অন্যথা  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, ফাঁকা, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, ফাঁকা);
#অন্যথা
    pthread_sigmask(SIG_SETMASK, &old_sig_set, ফাঁকা);
#endif

    ফেরত bytes_written;
}

স্থির ssize_t ReadPipe(পূর্ণসংখ্যা fd, শূন্য **বাফার_2, size_t *যোগ_দৈর্ঘ্য, Sint64 timeout_ns)
{
    শূন্য *output_বাফার = ফাঁকা;
    অক্ষর অস্থায়ী[PIPE_BUF];
    ssize_t bytes_read = 0;

    ধ্রুবক পূর্ণসংখ্যা ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    যদি (ready > 0) {
        bytes_read = পঠ(fd, অস্থায়ী, আকার(অস্থায়ী));
    } অন্যথা যদি (ready == 0) {
        SDL_SetError("Pipe timeout");
    } অন্যথা {
        SDL_SetError("Pipe poll error");
    }

    যদি (bytes_read > 0) {
        ধ্রুবক size_t pos = *যোগ_দৈর্ঘ্য;
        *যোগ_দৈর্ঘ্য += bytes_read;

        ধ্রুবক size_t new_বাফার_দৈর্ঘ্য = *যোগ_দৈর্ঘ্য + আকার(Uint32);

        যদি (!*বাফার_2) {
            output_বাফার = SDL_malloc(new_বাফার_দৈর্ঘ্য);
        } অন্যথা {
            output_বাফার = SDL_realloc(*বাফার_2, new_বাফার_দৈর্ঘ্য);
        }

        যদি (!output_বাফার) {
            bytes_read = -1;
        } অন্যথা {
            SDL_memcpy((Uint8 *)output_বাফার + pos, অস্থায়ী, bytes_read);
            SDL_memset((Uint8 *)output_বাফার + (new_বাফার_দৈর্ঘ্য - আকার(Uint32)), 0, আকার(Uint32));

            *বাফার_2 = output_বাফার;
        }
    }

    ফেরত bytes_read;
}

স্থির bool MIMEDataListHasType(কাঠামো wl_array *list, ধ্রুবক অক্ষর *mime_type)
{
    ধ্রুবক অক্ষর **item;
    wl_array_for_each(item, list) {
        যদি (SDL_strcmp(*item, mime_type) == 0) {
            ফেরত true;
        }
    }

    ফেরত false;
}

স্থির bool MIMEDataListAdd(কাঠামো wl_array *list, ধ্রুবক অক্ষর *mime_type)
{
    যদি (!MIMEDataListHasType(list, mime_type)) {
        অক্ষর **item = WAYLAND_wl_array_add(list, আকার(অক্ষর *));
        *item = SDL_strdup(mime_type);
    }

    ফেরত true;
}

স্থির শূন্য MIMEDataListFree(কাঠামো wl_array *list)
{
    অক্ষর **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

স্থির শূন্য তথ্য_source_handle_target(শূন্য *তথ্য, কাঠামো wl_তথ্য_source *wl_তথ্য_source, ধ্রুবক অক্ষর *mime_type)
{
}

স্থির শূন্য তথ্য_source_handle_send(শূন্য *তথ্য, কাঠামো wl_তথ্য_source *wl_তথ্য_source, ধ্রুবক অক্ষর *mime_type, int32_t fd)
{
    Wayland_তথ্য_Source_Send((SDL_Wayland_তথ্য_Source *)তথ্য, mime_type, fd);
}

স্থির শূন্য তথ্য_source_handle_cancelled(শূন্য *তথ্য, কাঠামো wl_তথ্য_source *wl_তথ্য_source)
{
    SDL_Wayland_তথ্য_Source *source = তথ্য;
    যদি (source) {
        Wayland_তথ্য_Source_Destroy(source);
    }
}

স্থির শূন্য তথ্য_source_handle_dnd_drop_performed(শূন্য *তথ্য, কাঠামো wl_তথ্য_source *wl_তথ্য_source)
{
}

স্থির শূন্য তথ্য_source_handle_dnd_finished(শূন্য *তথ্য, কাঠামো wl_তথ্য_source *wl_তথ্য_source)
{
    SDL_Wayland_তথ্য_Source *source = তথ্য;
    যদি (source) {
        Wayland_তথ্য_Source_Destroy(source);
    }
}

স্থির শূন্য তথ্য_source_handle_action(শূন্য *তথ্য, কাঠামো wl_তথ্য_source *wl_তথ্য_source, uint32_t dnd_action)
{
}

স্থির ধ্রুবক কাঠামো wl_তথ্য_source_listener তথ্য_source_listener = {
    তথ্য_source_handle_target,
    তথ্য_source_handle_send,
    তথ্য_source_handle_cancelled,
    তথ্য_source_handle_dnd_drop_performed, // Version 3
    তথ্য_source_handle_dnd_finished,       // Version 3
    তথ্য_source_handle_action,             // Version 3
};

SDL_Wayland_তথ্য_Source *Wayland_তথ্য_Source_Create(SDL_Video_তথ্য *video_তথ্য)
{
    SDL_Wayland_তথ্য_Source *তথ্য_source = SDL_calloc(1, আকার(*তথ্য_source));
    যদি (!তথ্য_source) {
        ফেরত ফাঁকা;
    }

    কাঠামো wl_তথ্য_source *id = wl_তথ্য_device_manager_create_তথ্য_source(video_তথ্য->তথ্য_device_manager);
    তথ্য_source->source = id;
    wl_তথ্য_source_set_user_তথ্য(id, তথ্য_source);
    wl_তথ্য_source_add_listener(id, &তথ্য_source_listener, তথ্য_source);

    ফেরত তথ্য_source;
}

স্থির শূন্য primary_selection_source_send(শূন্য *তথ্য, কাঠামো zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ধ্রুবক অক্ষর *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)তথ্য, mime_type, fd);
}

স্থির শূন্য primary_selection_source_cancelled(শূন্য *তথ্য, কাঠামো zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(তথ্য);
}

স্থির ধ্রুবক কাঠামো zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_Video_তথ্য *video_তথ্য)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, আকার(*primary_selection_source));
    যদি (!primary_selection_source) {
        ফেরত ফাঁকা;
    }

    কাঠামো zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_তথ্য->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    ফেরত primary_selection_source;
}

স্থির size_t Send_তথ্য(ধ্রুবক শূন্য *তথ্য, size_t দৈর্ঘ্য, পূর্ণসংখ্যা fd)
{
    size_t ফলাফল = 0;

    যদি (দৈর্ঘ্য > 0 && তথ্য) {
        যখন (WritePipe(fd, তথ্য, দৈর্ঘ্য, &ফলাফল) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    ফেরত ফলাফল;
}

ssize_t Wayland_তথ্য_Source_Send(SDL_Wayland_তথ্য_Source *source, ধ্রুবক অক্ষর *mime_type, পূর্ণসংখ্যা fd)
{
    ধ্রুবক শূন্য *তথ্য = ফাঁকা;
    size_t দৈর্ঘ্য = 0;

    যদি (SDL_strcmp(mime_type, SDL_তথ্য_ORIGIN_MIME) == 0) {
        তথ্য = source->তথ্য_device->id_str;
        দৈর্ঘ্য = SDL_strlen(source->তথ্য_device->id_str);
    } অন্যথা যদি (source->তথ্য_callback) {
        তথ্য = source->তথ্য_callback(source->userdata.তথ্য, mime_type, &দৈর্ঘ্য);
    }

    ফেরত Send_তথ্য(তথ্য, দৈর্ঘ্য, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ধ্রুবক অক্ষর *mime_type, পূর্ণসংখ্যা fd)
{
    ধ্রুবক শূন্য *তথ্য = ফাঁকা;
    size_t দৈর্ঘ্য = 0;

    যদি (source->তথ্য_callback) {
        তথ্য = source->তথ্য_callback(source->userdata.তথ্য, mime_type, &দৈর্ঘ্য);
    }

    ফেরত Send_তথ্য(তথ্য, দৈর্ঘ্য, fd);
}

শূন্য Wayland_তথ্য_Source_Set_Callback(SDL_Wayland_তথ্য_Source *source, SDL_Clipboard_তথ্য_Callback তথ্য_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata, Uint32 sequence)
{
    যদি (source) {
        source->তথ্য_callback = তথ্য_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.তথ্য = userdata;
    }
}

শূন্য Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_Clipboard_তথ্য_Callback তথ্য_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata)
{
    যদি (source) {
        source->তথ্য_callback = তথ্য_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.তথ্য = userdata;
    }
}

স্থির শূন্য *Clone_তথ্য_বাফার(ধ্রুবক শূন্য *বাফার_2, ধ্রুবক size_t *len)
{
    শূন্য *clone = ফাঁকা;
    যদি (*len > 0 && বাফার_2) {
        clone = SDL_malloc((*len)+আকার(Uint32));
        যদি (clone) {
            SDL_memcpy(clone, বাফার_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, আকার(Uint32));
        }
    }
    ফেরত clone;
}

শূন্য *Wayland_তথ্য_Source_Get_তথ্য(SDL_Wayland_তথ্য_Source *source, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য)
{
    শূন্য *বাফার_2 = ফাঁকা;
    *দৈর্ঘ্য = 0;

    যদি (!source) {
        SDL_SetError("Invalid data source");
    } অন্যথা যদি (source->তথ্য_callback) {
        ধ্রুবক শূন্য *internal_বাফার = source->তথ্য_callback(source->userdata.তথ্য, mime_type, দৈর্ঘ্য);
        বাফার_2 = Clone_তথ্য_বাফার(internal_বাফার, দৈর্ঘ্য);
    }

    ফেরত বাফার_2;
}

শূন্য *Wayland_Primary_Selection_Source_Get_তথ্য(SDL_WaylandPrimarySelectionSource *source, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য)
{
    শূন্য *বাফার_2 = ফাঁকা;
    *দৈর্ঘ্য = 0;

    যদি (!source) {
        SDL_SetError("Invalid primary selection source");
    } অন্যথা যদি (source->তথ্য_callback) {
        ধ্রুবক শূন্য *internal_বাফার = source->তথ্য_callback(source->userdata.তথ্য, mime_type, দৈর্ঘ্য);
        বাফার_2 = Clone_তথ্য_বাফার(internal_বাফার, দৈর্ঘ্য);
    }

    ফেরত বাফার_2;
}

শূন্য Wayland_তথ্য_Source_Destroy(SDL_Wayland_তথ্য_Source *source)
{
    যদি (source) {
        SDL_Wayland_তথ্য_Device *তথ্য_device = source->তথ্য_device;
        যদি (তথ্য_device && (তথ্য_device->selection_source == source)) {
            তথ্য_device->selection_source = ফাঁকা;
        }
        wl_তথ্য_source_destroy(source->source);
        যদি (source->userdata.sequence) {
            SDL_Cancel_Clipboard_তথ্য(source->userdata.sequence);
        } অন্যথা যদি (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.তথ্য);
        }
        SDL_free(source);
    }
}

শূন্য Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    যদি (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        যদি (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = ফাঁকা;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        যদি (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.তথ্য);
        }
        SDL_free(source);
    }
}

স্থির শূন্য SelectionOfferNotifyFromMIMEs(SDL_Wayland_তথ্য_Device *তথ্য_device, bool check_origin);

স্থির শূন্য offer_source_done_handler(শূন্য *তথ্য, কাঠামো wl_callback *callback, uint32_t callback_তথ্য)
{
    যদি (!callback) {
        ফেরত;
    }

    SDL_Wayland_তথ্য_Offer *offer = (SDL_Wayland_তথ্য_Offer *)তথ্য;
    অক্ষর *id = ফাঁকা;
    size_t দৈর্ঘ্য = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ফাঁকা;

    যখন (ReadPipe(offer->read_fd, (শূন্য **)&id, &দৈর্ঘ্য, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    যদি (id) {
        ধ্রুবক bool source_is_external = SDL_strncmp(offer->তথ্য_device->id_str, id, দৈর্ঘ্য) != 0;
        SDL_free(id);
        যদি (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->তথ্য_device, false);
        } অন্যথা {
            // Recursive data offer; just destroy it.
            SDL_Wayland_তথ্য_Device *তথ্য_device = offer->তথ্য_device;
            Wayland_তথ্য_Offer_Destroy(offer);
            তথ্য_device->selection_offer = ফাঁকা;
        }
    }
}

স্থির ধ্রুবক কাঠামো wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

স্থির শূন্য UpdateSeatOffers(SDL_Wayland_তথ্য_Device *তথ্য_device)
{
    SDL_WaylandSeat *offer_seat = তথ্য_device->seat;
    SDL_Video_তথ্য *video_তথ্য = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_তথ্য->seat_list, link) {
        যদি (s->তথ্য_device) {
            Wayland_তথ্য_Source_Destroy(s->তথ্য_device->selection_source);
            s->তথ্য_device->selection_source = ফাঁকা;

            // Don't clear the offer that is about to be set.
            যদি (s != offer_seat) {
                Wayland_তথ্য_Offer_Destroy(s->তথ্য_device->selection_offer);
                s->তথ্য_device->selection_offer = ফাঁকা;
            }
        }
    }

    video_তথ্য->current_তথ্য_offer_seat = offer_seat;
}

স্থির শূন্য SelectionOfferNotifyFromMIMEs(SDL_Wayland_তথ্য_Device *তথ্য_device, bool check_origin)
{
    SDL_Wayland_তথ্য_Offer *offer = তথ্য_device->selection_offer;
    অক্ষর **new_mime_types = ফাঁকা;
    size_t অঙ্ক_formats = 0;

    যদি (offer) {
        size_t alloc_আকার_2 = 0;

        // Do a first pass to compute allocation size.
        ধ্রুবক অক্ষর **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            যদি (check_origin && SDL_strcmp(*item, SDL_তথ্য_ORIGIN_MIME) == 0) {
                Wayland_তথ্য_Offer_Request_তথ্য_From_Self(offer, *item, &offer_source_listener, offer);
                ফেরত;
            }

            ++অঙ্ক_formats;
            alloc_আকার_2 += SDL_strlen(*item) + 1;
        }

        alloc_আকার_2 += (অঙ্ক_formats + 1) * আকার(অক্ষর *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_আকার_2);
        যদি (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_প্রবেশ, "unable to allocate new_mime_types");
            ফেরত;
        }

        // Second pass to fill.
        অক্ষর *strPtr = (অক্ষর *)(new_mime_types + অঙ্ক_formats + 1);
        alloc_আকার_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = ফাঁকা;
        পূর্ণসংখ্যা i = 0;
        wl_array_for_each(item, &offer->mimes) {
            যদি (!item) {
                চালু;
            }

            new_mime_types[i++] = strPtr;
            ধ্রুবক size_t len = SDL_strlcpy(strPtr, *item, alloc_আকার_2) + 1;
            strPtr += len;
            alloc_আকার_2 -= len;
        }
        new_mime_types[অঙ্ক_formats] = ফাঁকা;
    }

    UpdateSeatOffers(তথ্য_device);
    SDL_SendClipboardUpdate(false, new_mime_types, অঙ্ক_formats);
}

শূন্য Wayland_তথ্য_Device_Set_Selection_Offer(SDL_Wayland_তথ্য_Device *তথ্য_device, SDL_Wayland_তথ্য_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ধ্রুবক bool notify = offer || (!offer && তথ্য_device->selection_offer && (!তথ্য_device->selection_offer->callback || !তথ্য_device->selection_source));
    Wayland_তথ্য_Offer_Destroy(তথ্য_device->selection_offer);
    তথ্য_device->selection_offer = offer;
    যদি (notify) {
        SelectionOfferNotifyFromMIMEs(তথ্য_device, true);
    }
}

শূন্য *Wayland_তথ্য_Offer_Get_তথ্য_From_Self(SDL_Wayland_তথ্য_Offer *offer, size_t *দৈর্ঘ্য)
{
    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        ফেরত ফাঁকা;
    }

    যদি (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        ফেরত ফাঁকা;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    শূন্য *বাফার_2 = ফাঁকা;
    যখন (ReadPipe(offer->read_fd, &বাফার_2, দৈর্ঘ্য, 0) > 0) {
    }

    ফেরত বাফার_2;
}

bool Wayland_তথ্য_Offer_Request_তথ্য_From_Self(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type, ধ্রুবক কাঠামো wl_callback_listener *completion_listener, শূন্য *userdata)
{
    পূর্ণসংখ্যা pipefd[2];

    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        ফেরত false;
    }

    SDL_Wayland_তথ্য_Device *তথ্য_device = offer->তথ্য_device;
    যদি (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    যদি (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ফাঁকা;
    }

    যদি (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_তথ্য_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(তথ্য_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(তথ্য_device->seat->display->display);
    } অন্যথা {
        ফেরত SDL_SetError("Could not create pipe");
    }

    ফেরত true;
}

শূন্য *Wayland_তথ্য_Offer_Receive(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য)
{
    পূর্ণসংখ্যা pipefd[2];
    শূন্য *বাফার_2 = ফাঁকা;
    *দৈর্ঘ্য = 0;

    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        ফেরত ফাঁকা;
    }

    SDL_Wayland_তথ্য_Device *তথ্য_device = offer->তথ্য_device;

    যদি (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_তথ্য_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(তথ্য_device->seat->display->display);

        যখন (ReadPipe(pipefd[0], &বাফার_2, দৈর্ঘ্য, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } অন্যথা {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_প্রবেশ,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *দৈর্ঘ্য, বাফার_2);

    ফেরত বাফার_2;
}

শূন্য *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুবক অক্ষর *mime_type, size_t *দৈর্ঘ্য)
{
    পূর্ণসংখ্যা pipefd[2];
    শূন্য *বাফার_2 = ফাঁকা;
    *দৈর্ঘ্য = 0;

    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        ফেরত ফাঁকা;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    যদি (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        যখন (ReadPipe(pipefd[0], &বাফার_2, দৈর্ঘ্য, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } অন্যথা {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_প্রবেশ,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *দৈর্ঘ্য, বাফার_2);

    ফেরত বাফার_2;
}

bool Wayland_তথ্য_Offer_Add_MIME(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type)
{
    ফেরত MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুবক অক্ষর *mime_type)
{
    ফেরত MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_তথ্য_Offer_Has_MIME(SDL_Wayland_তথ্য_Offer *offer, ধ্রুবক অক্ষর *mime_type)
{
    যদি (offer && mime_type) {
        ফেরত MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ফেরত false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুবক অক্ষর *mime_type)
{
    যদি (offer && mime_type) {
        ফেরত MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ফেরত false;
}

শূন্য Wayland_তথ্য_Offer_Destroy(SDL_Wayland_তথ্য_Offer *offer)
{
    যদি (offer) {
        যদি (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        যদি (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_তথ্য_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

শূন্য Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    যদি (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_তথ্য_Device_Set_Selection_Source(SDL_Wayland_তথ্য_Device *তথ্য_device, SDL_Wayland_তথ্য_Source *source, ধ্রুবক অক্ষর **mime_types, size_t mime_গুনতি)
{
    যদি (!তথ্য_device) {
        ফেরত SDL_SetError("Invalid Data Device");
    }
    যদি (!source) {
        ফেরত SDL_SetError("Invalid source");
    }

    যদি (mime_গুনতি) {
        জন্য (size_t সূচক = 0; সূচক < mime_গুনতি; ++সূচক) {
            ধ্রুবক অক্ষর *mime_type = mime_types[সূচক];
            wl_তথ্য_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_তথ্য_source_offer(source->source, SDL_তথ্য_ORIGIN_MIME);

        wl_তথ্য_device_set_selection(তথ্য_device->তথ্য_device, source->source, তথ্য_device->seat->last_implicit_grab_serial);
        যদি (তথ্য_device->selection_source) {
            Wayland_তথ্য_Source_Destroy(তথ্য_device->selection_source);
        }
        তথ্য_device->selection_source = source;
        source->তথ্য_device = তথ্য_device;

    } অন্যথা {
        Wayland_তথ্য_Source_Destroy(তথ্য_device->selection_source);
        তথ্য_device->selection_source = ফাঁকা;
        ফেরত SDL_SetError("No mime data");
    }

    ফেরত true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ধ্রুবক অক্ষর *ধ্রুবক *mime_types, size_t mime_গুনতি)
{
    যদি (!primary_selection_device) {
        ফেরত SDL_SetError("Invalid Primary Selection Device");
    }
    যদি (!source) {
        ফেরত SDL_SetError("Invalid source");
    }

    যদি (mime_গুনতি) {
        জন্য (size_t সূচক = 0; সূচক < mime_গুনতি; ++সূচক) {
            ধ্রুবক অক্ষর *mime_type = mime_types[সূচক];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        যদি (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } অন্যথা {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = ফাঁকা;
        ফেরত SDL_SetError("No mime data");
    }

    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

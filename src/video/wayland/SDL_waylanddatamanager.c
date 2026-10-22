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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

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
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <time.h>
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ sigtimedwait(ಧ್ರುವ sigset_t *set, siginfo_t *info, ಧ್ರುವ ಸಂರಚನಾ timespec *timeout)
{
    ಸಂರಚನಾ timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    ಕುರು {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ signo = 1; signo < NSIG; ++signo) {
            ಯದಿ (sigismember(set, signo) && sigismember(&pending, signo)) {
                ಯದಿ (!sigwait(set, &signo)) {
                    ಯದಿ (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    ಪ್ರತ್ಯಾಗಮ signo;
                } ಅನ್ಯಥಾ {
                    ಪ್ರತ್ಯಾಗಮ -1;
                }
            }
        }

        ಯದಿ (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ಸಂರಚನಾ timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } ಯಾವತ್ (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    ಪ್ರತ್ಯಾಗಮ -1;
}
#endif

ಸ್ಥಿರ ssize_t WritePipe(ಪೂರ್ಣಾಙ್ಕ fd, ಧ್ರುವ ಶೂನ್ಯ *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    ಧ್ರುವ ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    ಸಂರಚನಾ timespec zerotime = { 0 };

    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#ಅನ್ಯಥಾ
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    ಯದಿ (ready > 0) {
        ಯದಿ (length > 0) {
            bytes_written = ಲಿಖ(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        ಯದಿ (bytes_written > 0) {
            *pos += bytes_written;
        }
    } ಅನ್ಯಥಾ ಯದಿ (ready == 0) {
        SDL_SetError("Pipe timeout");
    } ಅನ್ಯಥಾ  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, ರಿಕ್ತ, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, ರಿಕ್ತ);
#ಅನ್ಯಥಾ
    pthread_sigmask(SIG_SETMASK, &old_sig_set, ರಿಕ್ತ);
#endif

    ಪ್ರತ್ಯಾಗಮ bytes_written;
}

ಸ್ಥಿರ ssize_t ReadPipe(ಪೂರ್ಣಾಙ್ಕ fd, ಶೂನ್ಯ **buffer, size_t *total_length, Sint64 timeout_ns)
{
    ಶೂನ್ಯ *output_buffer = ರಿಕ್ತ;
    ವರ್ಣ temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    ಯದಿ (ready > 0) {
        bytes_read = ಪಠ(fd, temp, ಪರಿಮಾಣ(temp));
    } ಅನ್ಯಥಾ ಯದಿ (ready == 0) {
        SDL_SetError("Pipe timeout");
    } ಅನ್ಯಥಾ {
        SDL_SetError("Pipe poll error");
    }

    ಯದಿ (bytes_read > 0) {
        ಧ್ರುವ size_t pos = *total_length;
        *total_length += bytes_read;

        ಧ್ರುವ size_t new_buffer_length = *total_length + ಪರಿಮಾಣ(Uint32);

        ಯದಿ (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } ಅನ್ಯಥಾ {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        ಯದಿ (!output_buffer) {
            bytes_read = -1;
        } ಅನ್ಯಥಾ {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - ಪರಿಮಾಣ(Uint32)), 0, ಪರಿಮಾಣ(Uint32));

            *buffer = output_buffer;
        }
    }

    ಪ್ರತ್ಯಾಗಮ bytes_read;
}

ಸ್ಥಿರ bool MIMEDataListHasType(ಸಂರಚನಾ wl_array *list, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಧ್ರುವ ವರ್ಣ **item;
    wl_array_for_each(item, list) {
        ಯದಿ (SDL_strcmp(*item, mime_type) == 0) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }

    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ bool MIMEDataListAdd(ಸಂರಚನಾ wl_array *list, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಯದಿ (!MIMEDataListHasType(list, mime_type)) {
        ವರ್ಣ **item = WAYLAND_wl_array_add(list, ಪರಿಮಾಣ(ವರ್ಣ *));
        *item = SDL_strdup(mime_type);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ MIMEDataListFree(ಸಂರಚನಾ wl_array *list)
{
    ವರ್ಣ **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

ಸ್ಥಿರ ಶೂನ್ಯ data_source_handle_target(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_source *wl_data_source, ಧ್ರುವ ವರ್ಣ *mime_type)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ data_source_handle_send(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_source *wl_data_source, ಧ್ರುವ ವರ್ಣ *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

ಸ್ಥಿರ ಶೂನ್ಯ data_source_handle_cancelled(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    ಯದಿ (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ data_source_handle_dnd_drop_performed(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_source *wl_data_source)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ data_source_handle_dnd_finished(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    ಯದಿ (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ data_source_handle_action(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, ಪರಿಮಾಣ(*data_source));
    ಯದಿ (!data_source) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಸಂರಚನಾ wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    ಪ್ರತ್ಯಾಗಮ data_source;
}

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_source_send(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ಧ್ರುವ ವರ್ಣ *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

ಸ್ಥಿರ ಶೂನ್ಯ primary_selection_source_cancelled(ಶೂನ್ಯ *data, ಸಂರಚನಾ zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, ಪರಿಮಾಣ(*primary_selection_source));
    ಯದಿ (!primary_selection_source) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಸಂರಚನಾ zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    ಪ್ರತ್ಯಾಗಮ primary_selection_source;
}

ಸ್ಥಿರ size_t SendData(ಧ್ರುವ ಶೂನ್ಯ *data, size_t length, ಪೂರ್ಣಾಙ್ಕ fd)
{
    size_t result = 0;

    ಯದಿ (length > 0 && data) {
        ಯಾವತ್ (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    ಪ್ರತ್ಯಾಗಮ result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, ಪೂರ್ಣಾಙ್ಕ fd)
{
    ಧ್ರುವ ಶೂನ್ಯ *data = ರಿಕ್ತ;
    size_t length = 0;

    ಯದಿ (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } ಅನ್ಯಥಾ ಯದಿ (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    ಪ್ರತ್ಯಾಗಮ SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, ಪೂರ್ಣಾಙ್ಕ fd)
{
    ಧ್ರುವ ಶೂನ್ಯ *data = ರಿಕ್ತ;
    size_t length = 0;

    ಯದಿ (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    ಪ್ರತ್ಯಾಗಮ SendData(data, length, fd);
}

ಶೂನ್ಯ Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata, Uint32 sequence)
{
    ಯದಿ (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

ಶೂನ್ಯ Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ಶೂನ್ಯ *userdata)
{
    ಯದಿ (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ *CloneDataBuffer(ಧ್ರುವ ಶೂನ್ಯ *buffer, ಧ್ರುವ size_t *len)
{
    ಶೂನ್ಯ *clone = ರಿಕ್ತ;
    ಯದಿ (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+ಪರಿಮಾಣ(Uint32));
        ಯದಿ (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, ಪರಿಮಾಣ(Uint32));
        }
    }
    ಪ್ರತ್ಯಾಗಮ clone;
}

ಶೂನ್ಯ *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;
    *length = 0;

    ಯದಿ (!source) {
        SDL_SetError("Invalid data source");
    } ಅನ್ಯಥಾ ಯದಿ (source->data_callback) {
        ಧ್ರುವ ಶೂನ್ಯ *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    ಪ್ರತ್ಯಾಗಮ buffer;
}

ಶೂನ್ಯ *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;
    *length = 0;

    ಯದಿ (!source) {
        SDL_SetError("Invalid primary selection source");
    } ಅನ್ಯಥಾ ಯದಿ (source->data_callback) {
        ಧ್ರುವ ಶೂನ್ಯ *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    ಪ್ರತ್ಯಾಗಮ buffer;
}

ಶೂನ್ಯ Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    ಯದಿ (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        ಯದಿ (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = ರಿಕ್ತ;
        }
        wl_data_source_destroy(source->source);
        ಯದಿ (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } ಅನ್ಯಥಾ ಯದಿ (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ಶೂನ್ಯ Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    ಯದಿ (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        ಯದಿ (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = ರಿಕ್ತ;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        ಯದಿ (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

ಸ್ಥಿರ ಶೂನ್ಯ offer_source_done_handler(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_callback *callback, uint32_t callback_data)
{
    ಯದಿ (!callback) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    ವರ್ಣ *id = ರಿಕ್ತ;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ರಿಕ್ತ;

    ಯಾವತ್ (ReadPipe(offer->read_fd, (ಶೂನ್ಯ **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    ಯದಿ (id) {
        ಧ್ರುವ bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        ಯದಿ (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } ಅನ್ಯಥಾ {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = ರಿಕ್ತ;
        }
    }
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

ಸ್ಥಿರ ಶೂನ್ಯ UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        ಯದಿ (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = ರಿಕ್ತ;

            // Don't clear the offer that is about to be set.
            ಯದಿ (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ರಿಕ್ತ;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

ಸ್ಥಿರ ಶೂನ್ಯ SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    ವರ್ಣ **new_mime_types = ರಿಕ್ತ;
    size_t ಅಂಕೆ_formats = 0;

    ಯದಿ (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        ಧ್ರುವ ವರ್ಣ **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            ಯದಿ (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                ಪ್ರತ್ಯಾಗಮ;
            }

            ++ಅಂಕೆ_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (ಅಂಕೆ_formats + 1) * ಪರಿಮಾಣ(ವರ್ಣ *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        ಯದಿ (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_ಒಳಹರಿವು, "unable to allocate new_mime_types");
            ಪ್ರತ್ಯಾಗಮ;
        }

        // Second pass to fill.
        ವರ್ಣ *strPtr = (ವರ್ಣ *)(new_mime_types + ಅಂಕೆ_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = ರಿಕ್ತ;
        ಪೂರ್ಣಾಙ್ಕ i = 0;
        wl_array_for_each(item, &offer->mimes) {
            ಯದಿ (!item) {
                ಅನುವರ್ತ;
            }

            new_mime_types[i++] = strPtr;
            ಧ್ರುವ size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[ಅಂಕೆ_formats] = ರಿಕ್ತ;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, ಅಂಕೆ_formats);
}

ಶೂನ್ಯ Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ಧ್ರುವ bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    ಯದಿ (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

ಶೂನ್ಯ *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    ಯದಿ (!offer) {
        SDL_SetError("Invalid data offer");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;
    ಯಾವತ್ (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    ಪ್ರತ್ಯಾಗಮ buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type, ಧ್ರುವ ಸಂರಚನಾ wl_callback_listener *completion_listener, ಶೂನ್ಯ *userdata)
{
    ಪೂರ್ಣಾಙ್ಕ pipefd[2];

    ಯದಿ (!offer) {
        SDL_SetError("Invalid data offer");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    ಯದಿ (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    ಯದಿ (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ರಿಕ್ತ;
    }

    ಯದಿ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create pipe");
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    ಪೂರ್ಣಾಙ್ಕ pipefd[2];
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;
    *length = 0;

    ಯದಿ (!offer) {
        SDL_SetError("Invalid data offer");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    ಯದಿ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        ಯಾವತ್ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } ಅನ್ಯಥಾ {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    ಪ್ರತ್ಯಾಗಮ buffer;
}

ಶೂನ್ಯ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type, size_t *length)
{
    ಪೂರ್ಣಾಙ್ಕ pipefd[2];
    ಶೂನ್ಯ *buffer = ರಿಕ್ತ;
    *length = 0;

    ಯದಿ (!offer) {
        SDL_SetError("Invalid data offer");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    ಯದಿ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        ಯಾವತ್ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } ಅನ್ಯಥಾ {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ಒಳಹರಿವು,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    ಪ್ರತ್ಯಾಗಮ buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಪ್ರತ್ಯಾಗಮ MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಪ್ರತ್ಯಾಗಮ MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಯದಿ (offer && mime_type) {
        ಪ್ರತ್ಯಾಗಮ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ಧ್ರುವ ವರ್ಣ *mime_type)
{
    ಯದಿ (offer && mime_type) {
        ಪ್ರತ್ಯಾಗಮ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಶೂನ್ಯ Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    ಯದಿ (offer) {
        ಯದಿ (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        ಯದಿ (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

ಶೂನ್ಯ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    ಯದಿ (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, ಧ್ರುವ ವರ್ಣ **mime_types, size_t mime_ಎಣಿಕೆ)
{
    ಯದಿ (!data_device) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid Data Device");
    }
    ಯದಿ (!source) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid source");
    }

    ಯದಿ (mime_ಎಣಿಕೆ) {
        ಪ್ರತಿ (size_t index = 0; index < mime_ಎಣಿಕೆ; ++index) {
            ಧ್ರುವ ವರ್ಣ *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        ಯದಿ (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } ಅನ್ಯಥಾ {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = ರಿಕ್ತ;
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No mime data");
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *mime_types, size_t mime_ಎಣಿಕೆ)
{
    ಯದಿ (!primary_selection_device) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid Primary Selection Device");
    }
    ಯದಿ (!source) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid source");
    }

    ಯದಿ (mime_ಎಣಿಕೆ) {
        ಪ್ರತಿ (size_t index = 0; index < mime_ಎಣಿಕೆ; ++index) {
            ಧ್ರುವ ವರ್ಣ *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        ಯದಿ (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } ಅನ್ಯಥಾ {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = ರಿಕ್ತ;
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No mime data");
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

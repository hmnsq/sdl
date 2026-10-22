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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <signal.h>

#ଅନ୍ତର୍ଭାଵ "../../core/unix/SDL_poll.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_clipboard_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylanddatamanager.h"
#ଅନ୍ତର୍ଭାଵ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <time.h>
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା sigtimedwait(ଅଚଳ sigset_t *set, siginfo_t *info, ଅଚଳ ସଂରଚନା timespec *timeout)
{
    ସଂରଚନା timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    କର {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା signo = 1; signo < NSIG; ++signo) {
            ଯଦି (sigismember(set, signo) && sigismember(&pending, signo)) {
                ଯଦି (!sigwait(set, &signo)) {
                    ଯଦି (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    ଫେରନ୍ତୁ signo;
                } ଅନ୍ୟଥା {
                    ଫେରନ୍ତୁ -1;
                }
            }
        }

        ଯଦି (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ସଂରଚନା timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } ଯେତେବେଳେ (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    ଫେରନ୍ତୁ -1;
}
#endif

ସ୍ଥିର ssize_t WritePipe(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, ଅଚଳ ଶୂନ୍ୟ *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    ଅଚଳ ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    ସଂରଚନା timespec zerotime = { 0 };

    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#ଅନ୍ୟଥା
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    ଯଦି (ready > 0) {
        ଯଦି (length > 0) {
            bytes_written = ଲିଖ(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        ଯଦି (bytes_written > 0) {
            *pos += bytes_written;
        }
    } ଅନ୍ୟଥା ଯଦି (ready == 0) {
        SDL_SetError("Pipe timeout");
    } ଅନ୍ୟଥା  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, ଖାଲି, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, ଖାଲି);
#ଅନ୍ୟଥା
    pthread_sigmask(SIG_SETMASK, &old_sig_set, ଖାଲି);
#endif

    ଫେରନ୍ତୁ bytes_written;
}

ସ୍ଥିର ssize_t ReadPipe(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, ଶୂନ୍ୟ **buffer, size_t *total_length, Sint64 timeout_ns)
{
    ଶୂନ୍ୟ *output_buffer = ଖାଲି;
    ଅକ୍ଷର temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    ଯଦି (ready > 0) {
        bytes_read = ପଠ(fd, temp, ଆକାର(temp));
    } ଅନ୍ୟଥା ଯଦି (ready == 0) {
        SDL_SetError("Pipe timeout");
    } ଅନ୍ୟଥା {
        SDL_SetError("Pipe poll error");
    }

    ଯଦି (bytes_read > 0) {
        ଅଚଳ size_t pos = *total_length;
        *total_length += bytes_read;

        ଅଚଳ size_t new_buffer_length = *total_length + ଆକାର(Uint32);

        ଯଦି (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } ଅନ୍ୟଥା {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        ଯଦି (!output_buffer) {
            bytes_read = -1;
        } ଅନ୍ୟଥା {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - ଆକାର(Uint32)), 0, ଆକାର(Uint32));

            *buffer = output_buffer;
        }
    }

    ଫେରନ୍ତୁ bytes_read;
}

ସ୍ଥିର bool MIMEDataListHasType(ସଂରଚନା wl_array *list, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଅଚଳ ଅକ୍ଷର **item;
    wl_array_for_each(item, list) {
        ଯଦି (SDL_strcmp(*item, mime_type) == 0) {
            ଫେରନ୍ତୁ true;
        }
    }

    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର bool MIMEDataListAdd(ସଂରଚନା wl_array *list, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଯଦି (!MIMEDataListHasType(list, mime_type)) {
        ଅକ୍ଷର **item = WAYLAND_wl_array_add(list, ଆକାର(ଅକ୍ଷର *));
        *item = SDL_strdup(mime_type);
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ MIMEDataListFree(ସଂରଚନା wl_array *list)
{
    ଅକ୍ଷର **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

ସ୍ଥିର ଶୂନ୍ୟ data_source_handle_target(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_source *wl_data_source, ଅଚଳ ଅକ୍ଷର *mime_type)
{
}

ସ୍ଥିର ଶୂନ୍ୟ data_source_handle_send(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_source *wl_data_source, ଅଚଳ ଅକ୍ଷର *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

ସ୍ଥିର ଶୂନ୍ୟ data_source_handle_cancelled(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    ଯଦି (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ data_source_handle_dnd_drop_performed(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_source *wl_data_source)
{
}

ସ୍ଥିର ଶୂନ୍ୟ data_source_handle_dnd_finished(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    ଯଦି (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ data_source_handle_action(ଶୂନ୍ୟ *data, ସଂରଚନା wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, ଆକାର(*data_source));
    ଯଦି (!data_source) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ସଂରଚନା wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    ଫେରନ୍ତୁ data_source;
}

ସ୍ଥିର ଶୂନ୍ୟ primary_selection_source_send(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ଅଚଳ ଅକ୍ଷର *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

ସ୍ଥିର ଶୂନ୍ୟ primary_selection_source_cancelled(ଶୂନ୍ୟ *data, ସଂରଚନା zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, ଆକାର(*primary_selection_source));
    ଯଦି (!primary_selection_source) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ସଂରଚନା zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    ଫେରନ୍ତୁ primary_selection_source;
}

ସ୍ଥିର size_t SendData(ଅଚଳ ଶୂନ୍ୟ *data, size_t length, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd)
{
    size_t result = 0;

    ଯଦି (length > 0 && data) {
        ଯେତେବେଳେ (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    ଫେରନ୍ତୁ result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd)
{
    ଅଚଳ ଶୂନ୍ୟ *data = ଖାଲି;
    size_t length = 0;

    ଯଦି (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } ଅନ୍ୟଥା ଯଦି (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    ଫେରନ୍ତୁ SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd)
{
    ଅଚଳ ଶୂନ୍ୟ *data = ଖାଲି;
    size_t length = 0;

    ଯଦି (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    ଫେରନ୍ତୁ SendData(data, length, fd);
}

ଶୂନ୍ୟ Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ଶୂନ୍ୟ *userdata, Uint32 sequence)
{
    ଯଦି (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

ଶୂନ୍ୟ Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ଶୂନ୍ୟ *userdata)
{
    ଯଦି (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ *CloneDataBuffer(ଅଚଳ ଶୂନ୍ୟ *buffer, ଅଚଳ size_t *len)
{
    ଶୂନ୍ୟ *clone = ଖାଲି;
    ଯଦି (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+ଆକାର(Uint32));
        ଯଦି (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, ଆକାର(Uint32));
        }
    }
    ଫେରନ୍ତୁ clone;
}

ଶୂନ୍ୟ *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    ଶୂନ୍ୟ *buffer = ଖାଲି;
    *length = 0;

    ଯଦି (!source) {
        SDL_SetError("Invalid data source");
    } ଅନ୍ୟଥା ଯଦି (source->data_callback) {
        ଅଚଳ ଶୂନ୍ୟ *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    ଫେରନ୍ତୁ buffer;
}

ଶୂନ୍ୟ *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    ଶୂନ୍ୟ *buffer = ଖାଲି;
    *length = 0;

    ଯଦି (!source) {
        SDL_SetError("Invalid primary selection source");
    } ଅନ୍ୟଥା ଯଦି (source->data_callback) {
        ଅଚଳ ଶୂନ୍ୟ *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    ଫେରନ୍ତୁ buffer;
}

ଶୂନ୍ୟ Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    ଯଦି (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        ଯଦି (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = ଖାଲି;
        }
        wl_data_source_destroy(source->source);
        ଯଦି (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } ଅନ୍ୟଥା ଯଦି (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ଶୂନ୍ୟ Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    ଯଦି (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        ଯଦି (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = ଖାଲି;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        ଯଦି (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

ସ୍ଥିର ଶୂନ୍ୟ offer_source_done_handler(ଶୂନ୍ୟ *data, ସଂରଚନା wl_callback *callback, uint32_t callback_data)
{
    ଯଦି (!callback) {
        ଫେରନ୍ତୁ;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    ଅକ୍ଷର *id = ଖାଲି;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ଖାଲି;

    ଯେତେବେଳେ (ReadPipe(offer->read_fd, (ଶୂନ୍ୟ **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    ଯଦି (id) {
        ଅଚଳ bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        ଯଦି (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } ଅନ୍ୟଥା {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = ଖାଲି;
        }
    }
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

ସ୍ଥିର ଶୂନ୍ୟ UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        ଯଦି (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = ଖାଲି;

            // Don't clear the offer that is about to be set.
            ଯଦି (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ଖାଲି;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

ସ୍ଥିର ଶୂନ୍ୟ SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    ଅକ୍ଷର **new_mime_types = ଖାଲି;
    size_t ଅଙ୍କ_formats = 0;

    ଯଦି (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        ଅଚଳ ଅକ୍ଷର **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            ଯଦି (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                ଫେରନ୍ତୁ;
            }

            ++ଅଙ୍କ_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (ଅଙ୍କ_formats + 1) * ଆକାର(ଅକ୍ଷର *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        ଯଦି (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_ନିବେଶ, "unable to allocate new_mime_types");
            ଫେରନ୍ତୁ;
        }

        // Second pass to fill.
        ଅକ୍ଷର *strPtr = (ଅକ୍ଷର *)(new_mime_types + ଅଙ୍କ_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = ଖାଲି;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
        wl_array_for_each(item, &offer->mimes) {
            ଯଦି (!item) {
                ଜାରି;
            }

            new_mime_types[i++] = strPtr;
            ଅଚଳ size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[ଅଙ୍କ_formats] = ଖାଲି;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, ଅଙ୍କ_formats);
}

ଶୂନ୍ୟ Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ଅଚଳ bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    ଯଦି (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

ଶୂନ୍ୟ *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    ଯଦି (!offer) {
        SDL_SetError("Invalid data offer");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    ଶୂନ୍ୟ *buffer = ଖାଲି;
    ଯେତେବେଳେ (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    ଫେରନ୍ତୁ buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type, ଅଚଳ ସଂରଚନା wl_callback_listener *completion_listener, ଶୂନ୍ୟ *userdata)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pipefd[2];

    ଯଦି (!offer) {
        SDL_SetError("Invalid data offer");
        ଫେରନ୍ତୁ false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    ଯଦି (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    ଯଦି (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ଖାଲି;
    }

    ଯଦି (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SetError("Could not create pipe");
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pipefd[2];
    ଶୂନ୍ୟ *buffer = ଖାଲି;
    *length = 0;

    ଯଦି (!offer) {
        SDL_SetError("Invalid data offer");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    ଯଦି (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        ଯେତେବେଳେ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } ଅନ୍ୟଥା {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    ଫେରନ୍ତୁ buffer;
}

ଶୂନ୍ୟ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type, size_t *length)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pipefd[2];
    ଶୂନ୍ୟ *buffer = ଖାଲି;
    *length = 0;

    ଯଦି (!offer) {
        SDL_SetError("Invalid data offer");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    ଯଦି (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        ଯେତେବେଳେ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } ଅନ୍ୟଥା {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_ନିବେଶ,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    ଫେରନ୍ତୁ buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଫେରନ୍ତୁ MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଫେରନ୍ତୁ MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଯଦି (offer && mime_type) {
        ଫେରନ୍ତୁ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ଫେରନ୍ତୁ false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ଅଚଳ ଅକ୍ଷର *mime_type)
{
    ଯଦି (offer && mime_type) {
        ଫେରନ୍ତୁ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ଫେରନ୍ତୁ false;
}

ଶୂନ୍ୟ Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    ଯଦି (offer) {
        ଯଦି (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        ଯଦି (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

ଶୂନ୍ୟ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    ଯଦି (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, ଅଚଳ ଅକ୍ଷର **mime_types, size_t mime_ଗଣନା)
{
    ଯଦି (!data_device) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid Data Device");
    }
    ଯଦି (!source) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid source");
    }

    ଯଦି (mime_ଗଣନା) {
        ପାଇଁ (size_t index = 0; index < mime_ଗଣନା; ++index) {
            ଅଚଳ ଅକ୍ଷର *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        ଯଦି (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } ଅନ୍ୟଥା {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = ଖାଲି;
        ଫେରନ୍ତୁ SDL_SetError("No mime data");
    }

    ଫେରନ୍ତୁ true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ଅଚଳ ଅକ୍ଷର *ଅଚଳ *mime_types, size_t mime_ଗଣନା)
{
    ଯଦି (!primary_selection_device) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid Primary Selection Device");
    }
    ଯଦି (!source) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid source");
    }

    ଯଦି (mime_ଗଣନା) {
        ପାଇଁ (size_t index = 0; index < mime_ଗଣନା; ++index) {
            ଅଚଳ ଅକ୍ଷର *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        ଯଦି (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } ଅନ୍ୟଥା {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = ଖାଲି;
        ଫେରନ୍ତୁ SDL_SetError("No mime data");
    }

    ଫେରନ୍ତୁ true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

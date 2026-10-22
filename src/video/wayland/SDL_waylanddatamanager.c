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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <signal.h>

#அந்தர்பாவ "../../core/unix/SDL_poll.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../SDL_clipboard_c.h"

#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"
#அந்தர்பாவ "SDL_waylanddatamanager.h"
#அந்தர்பாவ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <time.h>
நிலையான முழு sigtimedwait(மாறிலி sigset_t *set, siginfo_t *info, மாறிலி கட்டமைப்பு timespec *timeout)
{
    கட்டமைப்பு timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    செய் {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        க்கு (முழு signo = 1; signo < NSIG; ++signo) {
            எனில் (sigismember(set, signo) && sigismember(&pending, signo)) {
                எனில் (!sigwait(set, &signo)) {
                    எனில் (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    திரும்பு signo;
                } இல்லையெனில் {
                    திரும்பு -1;
                }
            }
        }

        எனில் (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(கட்டமைப்பு timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } போது (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    திரும்பு -1;
}
#endif

நிலையான ssize_t WritePipe(முழு fd, மாறிலி வெறுமை *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    மாறிலி ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    கட்டமைப்பு timespec zerotime = { 0 };

    மாறிலி முழு ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#இல்லையெனில்
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    எனில் (ready > 0) {
        எனில் (length > 0) {
            bytes_written = லிக(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        எனில் (bytes_written > 0) {
            *pos += bytes_written;
        }
    } இல்லையெனில் எனில் (ready == 0) {
        SDL_SetError("Pipe timeout");
    } இல்லையெனில்  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, வெற்று, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, வெற்று);
#இல்லையெனில்
    pthread_sigmask(SIG_SETMASK, &old_sig_set, வெற்று);
#endif

    திரும்பு bytes_written;
}

நிலையான ssize_t ReadPipe(முழு fd, வெறுமை **buffer, size_t *total_length, Sint64 timeout_ns)
{
    வெறுமை *output_buffer = வெற்று;
    எழுத்து temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    மாறிலி முழு ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    எனில் (ready > 0) {
        bytes_read = பட(fd, temp, அளவு(temp));
    } இல்லையெனில் எனில் (ready == 0) {
        SDL_SetError("Pipe timeout");
    } இல்லையெனில் {
        SDL_SetError("Pipe poll error");
    }

    எனில் (bytes_read > 0) {
        மாறிலி size_t pos = *total_length;
        *total_length += bytes_read;

        மாறிலி size_t new_buffer_length = *total_length + அளவு(Uint32);

        எனில் (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } இல்லையெனில் {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        எனில் (!output_buffer) {
            bytes_read = -1;
        } இல்லையெனில் {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - அளவு(Uint32)), 0, அளவு(Uint32));

            *buffer = output_buffer;
        }
    }

    திரும்பு bytes_read;
}

நிலையான bool MIMEDataListHasType(கட்டமைப்பு wl_array *list, மாறிலி எழுத்து *mime_type)
{
    மாறிலி எழுத்து **item;
    wl_array_for_each(item, list) {
        எனில் (SDL_strcmp(*item, mime_type) == 0) {
            திரும்பு true;
        }
    }

    திரும்பு false;
}

நிலையான bool MIMEDataListAdd(கட்டமைப்பு wl_array *list, மாறிலி எழுத்து *mime_type)
{
    எனில் (!MIMEDataListHasType(list, mime_type)) {
        எழுத்து **item = WAYLAND_wl_array_add(list, அளவு(எழுத்து *));
        *item = SDL_strdup(mime_type);
    }

    திரும்பு true;
}

நிலையான வெறுமை MIMEDataListFree(கட்டமைப்பு wl_array *list)
{
    எழுத்து **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

நிலையான வெறுமை data_source_handle_target(வெறுமை *data, கட்டமைப்பு wl_data_source *wl_data_source, மாறிலி எழுத்து *mime_type)
{
}

நிலையான வெறுமை data_source_handle_send(வெறுமை *data, கட்டமைப்பு wl_data_source *wl_data_source, மாறிலி எழுத்து *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

நிலையான வெறுமை data_source_handle_cancelled(வெறுமை *data, கட்டமைப்பு wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    எனில் (source) {
        Wayland_DataSourceDestroy(source);
    }
}

நிலையான வெறுமை data_source_handle_dnd_drop_performed(வெறுமை *data, கட்டமைப்பு wl_data_source *wl_data_source)
{
}

நிலையான வெறுமை data_source_handle_dnd_finished(வெறுமை *data, கட்டமைப்பு wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    எனில் (source) {
        Wayland_DataSourceDestroy(source);
    }
}

நிலையான வெறுமை data_source_handle_action(வெறுமை *data, கட்டமைப்பு wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

நிலையான மாறிலி கட்டமைப்பு wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, அளவு(*data_source));
    எனில் (!data_source) {
        திரும்பு வெற்று;
    }

    கட்டமைப்பு wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    திரும்பு data_source;
}

நிலையான வெறுமை primary_selection_source_send(வெறுமை *data, கட்டமைப்பு zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, மாறிலி எழுத்து *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

நிலையான வெறுமை primary_selection_source_cancelled(வெறுமை *data, கட்டமைப்பு zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

நிலையான மாறிலி கட்டமைப்பு zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, அளவு(*primary_selection_source));
    எனில் (!primary_selection_source) {
        திரும்பு வெற்று;
    }

    கட்டமைப்பு zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    திரும்பு primary_selection_source;
}

நிலையான size_t SendData(மாறிலி வெறுமை *data, size_t length, முழு fd)
{
    size_t result = 0;

    எனில் (length > 0 && data) {
        போது (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    திரும்பு result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, மாறிலி எழுத்து *mime_type, முழு fd)
{
    மாறிலி வெறுமை *data = வெற்று;
    size_t length = 0;

    எனில் (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } இல்லையெனில் எனில் (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    திரும்பு SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, மாறிலி எழுத்து *mime_type, முழு fd)
{
    மாறிலி வெறுமை *data = வெற்று;
    size_t length = 0;

    எனில் (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    திரும்பு SendData(data, length, fd);
}

வெறுமை Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, வெறுமை *userdata, Uint32 sequence)
{
    எனில் (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

வெறுமை Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, வெறுமை *userdata)
{
    எனில் (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

நிலையான வெறுமை *CloneDataBuffer(மாறிலி வெறுமை *buffer, மாறிலி size_t *len)
{
    வெறுமை *clone = வெற்று;
    எனில் (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+அளவு(Uint32));
        எனில் (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, அளவு(Uint32));
        }
    }
    திரும்பு clone;
}

வெறுமை *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, மாறிலி எழுத்து *mime_type, size_t *length)
{
    வெறுமை *buffer = வெற்று;
    *length = 0;

    எனில் (!source) {
        SDL_SetError("Invalid data source");
    } இல்லையெனில் எனில் (source->data_callback) {
        மாறிலி வெறுமை *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    திரும்பு buffer;
}

வெறுமை *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, மாறிலி எழுத்து *mime_type, size_t *length)
{
    வெறுமை *buffer = வெற்று;
    *length = 0;

    எனில் (!source) {
        SDL_SetError("Invalid primary selection source");
    } இல்லையெனில் எனில் (source->data_callback) {
        மாறிலி வெறுமை *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    திரும்பு buffer;
}

வெறுமை Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    எனில் (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        எனில் (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = வெற்று;
        }
        wl_data_source_destroy(source->source);
        எனில் (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } இல்லையெனில் எனில் (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

வெறுமை Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    எனில் (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        எனில் (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = வெற்று;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        எனில் (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

நிலையான வெறுமை SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

நிலையான வெறுமை offer_source_done_handler(வெறுமை *data, கட்டமைப்பு wl_callback *callback, uint32_t callback_data)
{
    எனில் (!callback) {
        திரும்பு;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    எழுத்து *id = வெற்று;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = வெற்று;

    போது (ReadPipe(offer->read_fd, (வெறுமை **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    எனில் (id) {
        மாறிலி bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        எனில் (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } இல்லையெனில் {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = வெற்று;
        }
    }
}

நிலையான மாறிலி கட்டமைப்பு wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

நிலையான வெறுமை UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        எனில் (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = வெற்று;

            // Don't clear the offer that is about to be set.
            எனில் (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = வெற்று;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

நிலையான வெறுமை SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    எழுத்து **new_mime_types = வெற்று;
    size_t இலக்கம்_formats = 0;

    எனில் (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        மாறிலி எழுத்து **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            எனில் (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                திரும்பு;
            }

            ++இலக்கம்_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (இலக்கம்_formats + 1) * அளவு(எழுத்து *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        எனில் (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_உள்ளீடு, "unable to allocate new_mime_types");
            திரும்பு;
        }

        // Second pass to fill.
        எழுத்து *strPtr = (எழுத்து *)(new_mime_types + இலக்கம்_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = வெற்று;
        முழு i = 0;
        wl_array_for_each(item, &offer->mimes) {
            எனில் (!item) {
                தொடர்;
            }

            new_mime_types[i++] = strPtr;
            மாறிலி size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[இலக்கம்_formats] = வெற்று;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, இலக்கம்_formats);
}

வெறுமை Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    மாறிலி bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    எனில் (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

வெறுமை *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    எனில் (!offer) {
        SDL_SetError("Invalid data offer");
        திரும்பு வெற்று;
    }

    எனில் (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        திரும்பு வெற்று;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    வெறுமை *buffer = வெற்று;
    போது (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    திரும்பு buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, மாறிலி எழுத்து *mime_type, மாறிலி கட்டமைப்பு wl_callback_listener *completion_listener, வெறுமை *userdata)
{
    முழு pipefd[2];

    எனில் (!offer) {
        SDL_SetError("Invalid data offer");
        திரும்பு false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    எனில் (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    எனில் (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = வெற்று;
    }

    எனில் (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } இல்லையெனில் {
        திரும்பு SDL_SetError("Could not create pipe");
    }

    திரும்பு true;
}

வெறுமை *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, மாறிலி எழுத்து *mime_type, size_t *length)
{
    முழு pipefd[2];
    வெறுமை *buffer = வெற்று;
    *length = 0;

    எனில் (!offer) {
        SDL_SetError("Invalid data offer");
        திரும்பு வெற்று;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    எனில் (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        போது (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } இல்லையெனில் {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    திரும்பு buffer;
}

வெறுமை *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, மாறிலி எழுத்து *mime_type, size_t *length)
{
    முழு pipefd[2];
    வெறுமை *buffer = வெற்று;
    *length = 0;

    எனில் (!offer) {
        SDL_SetError("Invalid data offer");
        திரும்பு வெற்று;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    எனில் (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        போது (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } இல்லையெனில் {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_உள்ளீடு,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    திரும்பு buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, மாறிலி எழுத்து *mime_type)
{
    திரும்பு MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, மாறிலி எழுத்து *mime_type)
{
    திரும்பு MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, மாறிலி எழுத்து *mime_type)
{
    எனில் (offer && mime_type) {
        திரும்பு MIMEDataListHasType(&offer->mimes, mime_type);
    }
    திரும்பு false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, மாறிலி எழுத்து *mime_type)
{
    எனில் (offer && mime_type) {
        திரும்பு MIMEDataListHasType(&offer->mimes, mime_type);
    }
    திரும்பு false;
}

வெறுமை Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    எனில் (offer) {
        எனில் (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        எனில் (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

வெறுமை Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    எனில் (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, மாறிலி எழுத்து **mime_types, size_t mime_மொத்தம்)
{
    எனில் (!data_device) {
        திரும்பு SDL_SetError("Invalid Data Device");
    }
    எனில் (!source) {
        திரும்பு SDL_SetError("Invalid source");
    }

    எனில் (mime_மொத்தம்) {
        க்கு (size_t index = 0; index < mime_மொத்தம்; ++index) {
            மாறிலி எழுத்து *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        எனில் (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } இல்லையெனில் {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = வெற்று;
        திரும்பு SDL_SetError("No mime data");
    }

    திரும்பு true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                மாறிலி எழுத்து *மாறிலி *mime_types, size_t mime_மொத்தம்)
{
    எனில் (!primary_selection_device) {
        திரும்பு SDL_SetError("Invalid Primary Selection Device");
    }
    எனில் (!source) {
        திரும்பு SDL_SetError("Invalid source");
    }

    எனில் (mime_மொத்தம்) {
        க்கு (size_t index = 0; index < mime_மொத்தம்; ++index) {
            மாறிலி எழுத்து *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        எனில் (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } இல்லையெனில் {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = வெற்று;
        திரும்பு SDL_SetError("No mime data");
    }

    திரும்பு true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <signal.h>

#અન્તર્ભાવ "../../core/unix/SDL_poll.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../SDL_clipboard_c.h"

#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "SDL_waylandevents_c.h"
#અન્તર્ભાવ "SDL_waylanddatamanager.h"
#અન્તર્ભાવ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <time.h>
સ્થિર પૂર્ણાંક sigtimedwait(અચલ sigset_t *set, siginfo_t *info, અચલ સંરચના timespec *timeout)
{
    સંરચના timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    કરો {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        માટે (પૂર્ણાંક signo = 1; signo < NSIG; ++signo) {
            જો (sigismember(set, signo) && sigismember(&pending, signo)) {
                જો (!sigwait(set, &signo)) {
                    જો (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    પાછા signo;
                } નહીંતર {
                    પાછા -1;
                }
            }
        }

        જો (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(સંરચના timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } જ્યારે (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    પાછા -1;
}
#endif

સ્થિર ssize_t WritePipe(પૂર્ણાંક fd, અચલ શૂન્ય *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    અચલ ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    સંરચના timespec zerotime = { 0 };

    અચલ પૂર્ણાંક ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#નહીંતર
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    જો (ready > 0) {
        જો (length > 0) {
            bytes_written = લિખ(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        જો (bytes_written > 0) {
            *pos += bytes_written;
        }
    } નહીંતર જો (ready == 0) {
        SDL_SetError("Pipe timeout");
    } નહીંતર  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, ખાલી, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, ખાલી);
#નહીંતર
    pthread_sigmask(SIG_SETMASK, &old_sig_set, ખાલી);
#endif

    પાછા bytes_written;
}

સ્થિર ssize_t ReadPipe(પૂર્ણાંક fd, શૂન્ય **buffer, size_t *total_length, Sint64 timeout_ns)
{
    શૂન્ય *output_buffer = ખાલી;
    અક્ષર temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    અચલ પૂર્ણાંક ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    જો (ready > 0) {
        bytes_read = પઠ(fd, temp, કદ(temp));
    } નહીંતર જો (ready == 0) {
        SDL_SetError("Pipe timeout");
    } નહીંતર {
        SDL_SetError("Pipe poll error");
    }

    જો (bytes_read > 0) {
        અચલ size_t pos = *total_length;
        *total_length += bytes_read;

        અચલ size_t new_buffer_length = *total_length + કદ(Uint32);

        જો (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } નહીંતર {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        જો (!output_buffer) {
            bytes_read = -1;
        } નહીંતર {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - કદ(Uint32)), 0, કદ(Uint32));

            *buffer = output_buffer;
        }
    }

    પાછા bytes_read;
}

સ્થિર bool MIMEDataListHasType(સંરચના wl_array *list, અચલ અક્ષર *mime_type)
{
    અચલ અક્ષર **item;
    wl_array_for_each(item, list) {
        જો (SDL_strcmp(*item, mime_type) == 0) {
            પાછા true;
        }
    }

    પાછા false;
}

સ્થિર bool MIMEDataListAdd(સંરચના wl_array *list, અચલ અક્ષર *mime_type)
{
    જો (!MIMEDataListHasType(list, mime_type)) {
        અક્ષર **item = WAYLAND_wl_array_add(list, કદ(અક્ષર *));
        *item = SDL_strdup(mime_type);
    }

    પાછા true;
}

સ્થિર શૂન્ય MIMEDataListFree(સંરચના wl_array *list)
{
    અક્ષર **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

સ્થિર શૂન્ય data_source_handle_target(શૂન્ય *data, સંરચના wl_data_source *wl_data_source, અચલ અક્ષર *mime_type)
{
}

સ્થિર શૂન્ય data_source_handle_send(શૂન્ય *data, સંરચના wl_data_source *wl_data_source, અચલ અક્ષર *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

સ્થિર શૂન્ય data_source_handle_cancelled(શૂન્ય *data, સંરચના wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    જો (source) {
        Wayland_DataSourceDestroy(source);
    }
}

સ્થિર શૂન્ય data_source_handle_dnd_drop_performed(શૂન્ય *data, સંરચના wl_data_source *wl_data_source)
{
}

સ્થિર શૂન્ય data_source_handle_dnd_finished(શૂન્ય *data, સંરચના wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    જો (source) {
        Wayland_DataSourceDestroy(source);
    }
}

સ્થિર શૂન્ય data_source_handle_action(શૂન્ય *data, સંરચના wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

સ્થિર અચલ સંરચના wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, કદ(*data_source));
    જો (!data_source) {
        પાછા ખાલી;
    }

    સંરચના wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    પાછા data_source;
}

સ્થિર શૂન્ય primary_selection_source_send(શૂન્ય *data, સંરચના zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, અચલ અક્ષર *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

સ્થિર શૂન્ય primary_selection_source_cancelled(શૂન્ય *data, સંરચના zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

સ્થિર અચલ સંરચના zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, કદ(*primary_selection_source));
    જો (!primary_selection_source) {
        પાછા ખાલી;
    }

    સંરચના zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    પાછા primary_selection_source;
}

સ્થિર size_t SendData(અચલ શૂન્ય *data, size_t length, પૂર્ણાંક fd)
{
    size_t result = 0;

    જો (length > 0 && data) {
        જ્યારે (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    પાછા result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, અચલ અક્ષર *mime_type, પૂર્ણાંક fd)
{
    અચલ શૂન્ય *data = ખાલી;
    size_t length = 0;

    જો (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } નહીંતર જો (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    પાછા SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, અચલ અક્ષર *mime_type, પૂર્ણાંક fd)
{
    અચલ શૂન્ય *data = ખાલી;
    size_t length = 0;

    જો (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    પાછા SendData(data, length, fd);
}

શૂન્ય Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, શૂન્ય *userdata, Uint32 sequence)
{
    જો (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

શૂન્ય Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, શૂન્ય *userdata)
{
    જો (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

સ્થિર શૂન્ય *CloneDataBuffer(અચલ શૂન્ય *buffer, અચલ size_t *len)
{
    શૂન્ય *clone = ખાલી;
    જો (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+કદ(Uint32));
        જો (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, કદ(Uint32));
        }
    }
    પાછા clone;
}

શૂન્ય *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, અચલ અક્ષર *mime_type, size_t *length)
{
    શૂન્ય *buffer = ખાલી;
    *length = 0;

    જો (!source) {
        SDL_SetError("Invalid data source");
    } નહીંતર જો (source->data_callback) {
        અચલ શૂન્ય *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    પાછા buffer;
}

શૂન્ય *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, અચલ અક્ષર *mime_type, size_t *length)
{
    શૂન્ય *buffer = ખાલી;
    *length = 0;

    જો (!source) {
        SDL_SetError("Invalid primary selection source");
    } નહીંતર જો (source->data_callback) {
        અચલ શૂન્ય *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    પાછા buffer;
}

શૂન્ય Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    જો (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        જો (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = ખાલી;
        }
        wl_data_source_destroy(source->source);
        જો (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } નહીંતર જો (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

શૂન્ય Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    જો (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        જો (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = ખાલી;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        જો (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

સ્થિર શૂન્ય SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

સ્થિર શૂન્ય offer_source_done_handler(શૂન્ય *data, સંરચના wl_callback *callback, uint32_t callback_data)
{
    જો (!callback) {
        પાછા;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    અક્ષર *id = ખાલી;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ખાલી;

    જ્યારે (ReadPipe(offer->read_fd, (શૂન્ય **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    જો (id) {
        અચલ bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        જો (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } નહીંતર {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = ખાલી;
        }
    }
}

સ્થિર અચલ સંરચના wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

સ્થિર શૂન્ય UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        જો (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = ખાલી;

            // Don't clear the offer that is about to be set.
            જો (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ખાલી;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

સ્થિર શૂન્ય SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    અક્ષર **new_mime_types = ખાલી;
    size_t અંક_formats = 0;

    જો (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        અચલ અક્ષર **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            જો (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                પાછા;
            }

            ++અંક_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (અંક_formats + 1) * કદ(અક્ષર *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        જો (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_આગત, "unable to allocate new_mime_types");
            પાછા;
        }

        // Second pass to fill.
        અક્ષર *strPtr = (અક્ષર *)(new_mime_types + અંક_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = ખાલી;
        પૂર્ણાંક i = 0;
        wl_array_for_each(item, &offer->mimes) {
            જો (!item) {
                ચાલુ;
            }

            new_mime_types[i++] = strPtr;
            અચલ size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[અંક_formats] = ખાલી;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, અંક_formats);
}

શૂન્ય Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    અચલ bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    જો (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

શૂન્ય *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    જો (!offer) {
        SDL_SetError("Invalid data offer");
        પાછા ખાલી;
    }

    જો (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        પાછા ખાલી;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    શૂન્ય *buffer = ખાલી;
    જ્યારે (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    પાછા buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type, અચલ સંરચના wl_callback_listener *completion_listener, શૂન્ય *userdata)
{
    પૂર્ણાંક pipefd[2];

    જો (!offer) {
        SDL_SetError("Invalid data offer");
        પાછા false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    જો (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    જો (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ખાલી;
    }

    જો (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } નહીંતર {
        પાછા SDL_SetError("Could not create pipe");
    }

    પાછા true;
}

શૂન્ય *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type, size_t *length)
{
    પૂર્ણાંક pipefd[2];
    શૂન્ય *buffer = ખાલી;
    *length = 0;

    જો (!offer) {
        SDL_SetError("Invalid data offer");
        પાછા ખાલી;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    જો (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        જ્યારે (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } નહીંતર {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    પાછા buffer;
}

શૂન્ય *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, અચલ અક્ષર *mime_type, size_t *length)
{
    પૂર્ણાંક pipefd[2];
    શૂન્ય *buffer = ખાલી;
    *length = 0;

    જો (!offer) {
        SDL_SetError("Invalid data offer");
        પાછા ખાલી;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    જો (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        જ્યારે (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } નહીંતર {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_આગત,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    પાછા buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type)
{
    પાછા MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, અચલ અક્ષર *mime_type)
{
    પાછા MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, અચલ અક્ષર *mime_type)
{
    જો (offer && mime_type) {
        પાછા MIMEDataListHasType(&offer->mimes, mime_type);
    }
    પાછા false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, અચલ અક્ષર *mime_type)
{
    જો (offer && mime_type) {
        પાછા MIMEDataListHasType(&offer->mimes, mime_type);
    }
    પાછા false;
}

શૂન્ય Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    જો (offer) {
        જો (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        જો (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

શૂન્ય Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    જો (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, અચલ અક્ષર **mime_types, size_t mime_ગણતરી)
{
    જો (!data_device) {
        પાછા SDL_SetError("Invalid Data Device");
    }
    જો (!source) {
        પાછા SDL_SetError("Invalid source");
    }

    જો (mime_ગણતરી) {
        માટે (size_t index = 0; index < mime_ગણતરી; ++index) {
            અચલ અક્ષર *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        જો (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } નહીંતર {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = ખાલી;
        પાછા SDL_SetError("No mime data");
    }

    પાછા true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                અચલ અક્ષર *અચલ *mime_types, size_t mime_ગણતરી)
{
    જો (!primary_selection_device) {
        પાછા SDL_SetError("Invalid Primary Selection Device");
    }
    જો (!source) {
        પાછા SDL_SetError("Invalid source");
    }

    જો (mime_ગણતરી) {
        માટે (size_t index = 0; index < mime_ગણતરી; ++index) {
            અચલ અક્ષર *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        જો (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } નહીંતર {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = ખાલી;
        પાછા SDL_SetError("No mime data");
    }

    પાછા true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#അന്തര്ഭാവ <fcntl.h>
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <signal.h>

#അന്തര്ഭാവ "../../core/unix/SDL_poll.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../SDL_clipboard_c.h"

#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "SDL_waylandevents_c.h"
#അന്തര്ഭാവ "SDL_waylanddatamanager.h"
#അന്തര്ഭാവ "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <time.h>
സ്ഥിതം പൂർണ്ണസംഖ്യ sigtimedwait(സ്ഥിരം sigset_t *set, siginfo_t *info, സ്ഥിരം ഘടന timespec *timeout)
{
    ഘടന timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    ചെയ്യുക {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        വേണ്ടി (പൂർണ്ണസംഖ്യ signo = 1; signo < NSIG; ++signo) {
            എങ്കിൽ (sigismember(set, signo) && sigismember(&pending, signo)) {
                എങ്കിൽ (!sigwait(set, &signo)) {
                    എങ്കിൽ (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    തിരികെ signo;
                } അല്ലെങ്കിൽ {
                    തിരികെ -1;
                }
            }
        }

        എങ്കിൽ (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ഘടന timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } ആകുമ്പോൾ (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    തിരികെ -1;
}
#endif

സ്ഥിതം ssize_t WritePipe(പൂർണ്ണസംഖ്യ fd, സ്ഥിരം ശൂന്യം *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    സ്ഥിരം ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    ഘടന timespec zerotime = { 0 };

    സ്ഥിരം പൂർണ്ണസംഖ്യ ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#അല്ലെങ്കിൽ
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    എങ്കിൽ (ready > 0) {
        എങ്കിൽ (length > 0) {
            bytes_written = ലിഖ(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        എങ്കിൽ (bytes_written > 0) {
            *pos += bytes_written;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (ready == 0) {
        SDL_SetError("Pipe timeout");
    } അല്ലെങ്കിൽ  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, ശൂന്യ, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, ശൂന്യ);
#അല്ലെങ്കിൽ
    pthread_sigmask(SIG_SETMASK, &old_sig_set, ശൂന്യ);
#endif

    തിരികെ bytes_written;
}

സ്ഥിതം ssize_t ReadPipe(പൂർണ്ണസംഖ്യ fd, ശൂന്യം **buffer, size_t *total_length, Sint64 timeout_ns)
{
    ശൂന്യം *output_buffer = ശൂന്യ;
    അക്ഷരം temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    സ്ഥിരം പൂർണ്ണസംഖ്യ ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    എങ്കിൽ (ready > 0) {
        bytes_read = പഠ(fd, temp, വലുപ്പം(temp));
    } അല്ലെങ്കിൽ എങ്കിൽ (ready == 0) {
        SDL_SetError("Pipe timeout");
    } അല്ലെങ്കിൽ {
        SDL_SetError("Pipe poll error");
    }

    എങ്കിൽ (bytes_read > 0) {
        സ്ഥിരം size_t pos = *total_length;
        *total_length += bytes_read;

        സ്ഥിരം size_t new_buffer_length = *total_length + വലുപ്പം(Uint32);

        എങ്കിൽ (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } അല്ലെങ്കിൽ {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        എങ്കിൽ (!output_buffer) {
            bytes_read = -1;
        } അല്ലെങ്കിൽ {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - വലുപ്പം(Uint32)), 0, വലുപ്പം(Uint32));

            *buffer = output_buffer;
        }
    }

    തിരികെ bytes_read;
}

സ്ഥിതം bool MIMEDataListHasType(ഘടന wl_array *list, സ്ഥിരം അക്ഷരം *mime_type)
{
    സ്ഥിരം അക്ഷരം **item;
    wl_array_for_each(item, list) {
        എങ്കിൽ (SDL_strcmp(*item, mime_type) == 0) {
            തിരികെ true;
        }
    }

    തിരികെ false;
}

സ്ഥിതം bool MIMEDataListAdd(ഘടന wl_array *list, സ്ഥിരം അക്ഷരം *mime_type)
{
    എങ്കിൽ (!MIMEDataListHasType(list, mime_type)) {
        അക്ഷരം **item = WAYLAND_wl_array_add(list, വലുപ്പം(അക്ഷരം *));
        *item = SDL_strdup(mime_type);
    }

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം MIMEDataListFree(ഘടന wl_array *list)
{
    അക്ഷരം **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

സ്ഥിതം ശൂന്യം data_source_handle_target(ശൂന്യം *data, ഘടന wl_data_source *wl_data_source, സ്ഥിരം അക്ഷരം *mime_type)
{
}

സ്ഥിതം ശൂന്യം data_source_handle_send(ശൂന്യം *data, ഘടന wl_data_source *wl_data_source, സ്ഥിരം അക്ഷരം *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

സ്ഥിതം ശൂന്യം data_source_handle_cancelled(ശൂന്യം *data, ഘടന wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    എങ്കിൽ (source) {
        Wayland_DataSourceDestroy(source);
    }
}

സ്ഥിതം ശൂന്യം data_source_handle_dnd_drop_performed(ശൂന്യം *data, ഘടന wl_data_source *wl_data_source)
{
}

സ്ഥിതം ശൂന്യം data_source_handle_dnd_finished(ശൂന്യം *data, ഘടന wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    എങ്കിൽ (source) {
        Wayland_DataSourceDestroy(source);
    }
}

സ്ഥിതം ശൂന്യം data_source_handle_action(ശൂന്യം *data, ഘടന wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

സ്ഥിതം സ്ഥിരം ഘടന wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, വലുപ്പം(*data_source));
    എങ്കിൽ (!data_source) {
        തിരികെ ശൂന്യ;
    }

    ഘടന wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    തിരികെ data_source;
}

സ്ഥിതം ശൂന്യം primary_selection_source_send(ശൂന്യം *data, ഘടന zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, സ്ഥിരം അക്ഷരം *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

സ്ഥിതം ശൂന്യം primary_selection_source_cancelled(ശൂന്യം *data, ഘടന zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

സ്ഥിതം സ്ഥിരം ഘടന zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, വലുപ്പം(*primary_selection_source));
    എങ്കിൽ (!primary_selection_source) {
        തിരികെ ശൂന്യ;
    }

    ഘടന zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    തിരികെ primary_selection_source;
}

സ്ഥിതം size_t SendData(സ്ഥിരം ശൂന്യം *data, size_t length, പൂർണ്ണസംഖ്യ fd)
{
    size_t result = 0;

    എങ്കിൽ (length > 0 && data) {
        ആകുമ്പോൾ (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    തിരികെ result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, സ്ഥിരം അക്ഷരം *mime_type, പൂർണ്ണസംഖ്യ fd)
{
    സ്ഥിരം ശൂന്യം *data = ശൂന്യ;
    size_t length = 0;

    എങ്കിൽ (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } അല്ലെങ്കിൽ എങ്കിൽ (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    തിരികെ SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, സ്ഥിരം അക്ഷരം *mime_type, പൂർണ്ണസംഖ്യ fd)
{
    സ്ഥിരം ശൂന്യം *data = ശൂന്യ;
    size_t length = 0;

    എങ്കിൽ (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    തിരികെ SendData(data, length, fd);
}

ശൂന്യം Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ശൂന്യം *userdata, Uint32 sequence)
{
    എങ്കിൽ (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

ശൂന്യം Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, ശൂന്യം *userdata)
{
    എങ്കിൽ (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

സ്ഥിതം ശൂന്യം *CloneDataBuffer(സ്ഥിരം ശൂന്യം *buffer, സ്ഥിരം size_t *len)
{
    ശൂന്യം *clone = ശൂന്യ;
    എങ്കിൽ (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+വലുപ്പം(Uint32));
        എങ്കിൽ (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, വലുപ്പം(Uint32));
        }
    }
    തിരികെ clone;
}

ശൂന്യം *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, സ്ഥിരം അക്ഷരം *mime_type, size_t *length)
{
    ശൂന്യം *buffer = ശൂന്യ;
    *length = 0;

    എങ്കിൽ (!source) {
        SDL_SetError("Invalid data source");
    } അല്ലെങ്കിൽ എങ്കിൽ (source->data_callback) {
        സ്ഥിരം ശൂന്യം *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    തിരികെ buffer;
}

ശൂന്യം *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, സ്ഥിരം അക്ഷരം *mime_type, size_t *length)
{
    ശൂന്യം *buffer = ശൂന്യ;
    *length = 0;

    എങ്കിൽ (!source) {
        SDL_SetError("Invalid primary selection source");
    } അല്ലെങ്കിൽ എങ്കിൽ (source->data_callback) {
        സ്ഥിരം ശൂന്യം *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    തിരികെ buffer;
}

ശൂന്യം Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    എങ്കിൽ (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        എങ്കിൽ (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = ശൂന്യ;
        }
        wl_data_source_destroy(source->source);
        എങ്കിൽ (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } അല്ലെങ്കിൽ എങ്കിൽ (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ശൂന്യം Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    എങ്കിൽ (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        എങ്കിൽ (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = ശൂന്യ;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        എങ്കിൽ (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

സ്ഥിതം ശൂന്യം SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

സ്ഥിതം ശൂന്യം offer_source_done_handler(ശൂന്യം *data, ഘടന wl_callback *callback, uint32_t callback_data)
{
    എങ്കിൽ (!callback) {
        തിരികെ;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    അക്ഷരം *id = ശൂന്യ;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = ശൂന്യ;

    ആകുമ്പോൾ (ReadPipe(offer->read_fd, (ശൂന്യം **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    എങ്കിൽ (id) {
        സ്ഥിരം bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        എങ്കിൽ (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } അല്ലെങ്കിൽ {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = ശൂന്യ;
        }
    }
}

സ്ഥിതം സ്ഥിരം ഘടന wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

സ്ഥിതം ശൂന്യം UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        എങ്കിൽ (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = ശൂന്യ;

            // Don't clear the offer that is about to be set.
            എങ്കിൽ (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = ശൂന്യ;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

സ്ഥിതം ശൂന്യം SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    അക്ഷരം **new_mime_types = ശൂന്യ;
    size_t അക്കം_formats = 0;

    എങ്കിൽ (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        സ്ഥിരം അക്ഷരം **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            എങ്കിൽ (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                തിരികെ;
            }

            ++അക്കം_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (അക്കം_formats + 1) * വലുപ്പം(അക്ഷരം *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        എങ്കിൽ (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_നിവേശം, "unable to allocate new_mime_types");
            തിരികെ;
        }

        // Second pass to fill.
        അക്ഷരം *strPtr = (അക്ഷരം *)(new_mime_types + അക്കം_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = ശൂന്യ;
        പൂർണ്ണസംഖ്യ i = 0;
        wl_array_for_each(item, &offer->mimes) {
            എങ്കിൽ (!item) {
                തുടരുക;
            }

            new_mime_types[i++] = strPtr;
            സ്ഥിരം size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[അക്കം_formats] = ശൂന്യ;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, അക്കം_formats);
}

ശൂന്യം Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    സ്ഥിരം bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    എങ്കിൽ (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

ശൂന്യം *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    എങ്കിൽ (!offer) {
        SDL_SetError("Invalid data offer");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        തിരികെ ശൂന്യ;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    ശൂന്യം *buffer = ശൂന്യ;
    ആകുമ്പോൾ (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    തിരികെ buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type, സ്ഥിരം ഘടന wl_callback_listener *completion_listener, ശൂന്യം *userdata)
{
    പൂർണ്ണസംഖ്യ pipefd[2];

    എങ്കിൽ (!offer) {
        SDL_SetError("Invalid data offer");
        തിരികെ false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    എങ്കിൽ (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    എങ്കിൽ (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = ശൂന്യ;
    }

    എങ്കിൽ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("Could not create pipe");
    }

    തിരികെ true;
}

ശൂന്യം *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type, size_t *length)
{
    പൂർണ്ണസംഖ്യ pipefd[2];
    ശൂന്യം *buffer = ശൂന്യ;
    *length = 0;

    എങ്കിൽ (!offer) {
        SDL_SetError("Invalid data offer");
        തിരികെ ശൂന്യ;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    എങ്കിൽ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        ആകുമ്പോൾ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } അല്ലെങ്കിൽ {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    തിരികെ buffer;
}

ശൂന്യം *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, സ്ഥിരം അക്ഷരം *mime_type, size_t *length)
{
    പൂർണ്ണസംഖ്യ pipefd[2];
    ശൂന്യം *buffer = ശൂന്യ;
    *length = 0;

    എങ്കിൽ (!offer) {
        SDL_SetError("Invalid data offer");
        തിരികെ ശൂന്യ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    എങ്കിൽ (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        ആകുമ്പോൾ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } അല്ലെങ്കിൽ {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_നിവേശം,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    തിരികെ buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type)
{
    തിരികെ MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, സ്ഥിരം അക്ഷരം *mime_type)
{
    തിരികെ MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, സ്ഥിരം അക്ഷരം *mime_type)
{
    എങ്കിൽ (offer && mime_type) {
        തിരികെ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    തിരികെ false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, സ്ഥിരം അക്ഷരം *mime_type)
{
    എങ്കിൽ (offer && mime_type) {
        തിരികെ MIMEDataListHasType(&offer->mimes, mime_type);
    }
    തിരികെ false;
}

ശൂന്യം Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    എങ്കിൽ (offer) {
        എങ്കിൽ (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        എങ്കിൽ (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

ശൂന്യം Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    എങ്കിൽ (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, സ്ഥിരം അക്ഷരം **mime_types, size_t mime_എണ്ണം)
{
    എങ്കിൽ (!data_device) {
        തിരികെ SDL_SetError("Invalid Data Device");
    }
    എങ്കിൽ (!source) {
        തിരികെ SDL_SetError("Invalid source");
    }

    എങ്കിൽ (mime_എണ്ണം) {
        വേണ്ടി (size_t index = 0; index < mime_എണ്ണം; ++index) {
            സ്ഥിരം അക്ഷരം *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        എങ്കിൽ (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } അല്ലെങ്കിൽ {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = ശൂന്യ;
        തിരികെ SDL_SetError("No mime data");
    }

    തിരികെ true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                സ്ഥിരം അക്ഷരം *സ്ഥിരം *mime_types, size_t mime_എണ്ണം)
{
    എങ്കിൽ (!primary_selection_device) {
        തിരികെ SDL_SetError("Invalid Primary Selection Device");
    }
    എങ്കിൽ (!source) {
        തിരികെ SDL_SetError("Invalid source");
    }

    എങ്കിൽ (mime_എണ്ണം) {
        വേണ്ടി (size_t index = 0; index < mime_എണ്ണം; ++index) {
            സ്ഥിരം അക്ഷരം *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        എങ്കിൽ (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } അല്ലെങ്കിൽ {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = ശൂന്യ;
        തിരികെ SDL_SetError("No mime data");
    }

    തിരികെ true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

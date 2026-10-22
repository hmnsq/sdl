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
স্থির পূর্ণাঙ্ক sigtimedwait(ধ্রুব sigset_t *set, siginfo_t *info, ধ্রুব সংরচনা timespec *timeout)
{
    সংরচনা timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    কুরু {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        প্রতি (পূর্ণাঙ্ক signo = 1; signo < NSIG; ++signo) {
            যদি (sigismember(set, signo) && sigismember(&pending, signo)) {
                যদি (!sigwait(set, &signo)) {
                    যদি (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    প্রত্যাগম signo;
                } অন্যথা {
                    প্রত্যাগম -1;
                }
            }
        }

        যদি (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(সংরচনা timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } যাবত্ (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    প্রত্যাগম -1;
}
#endif

স্থির ssize_t WritePipe(পূর্ণাঙ্ক fd, ধ্রুব শূন্য *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    ধ্রুব ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    সংরচনা timespec zerotime = { 0 };

    ধ্রুব পূর্ণাঙ্ক ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#অন্যথা
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    যদি (ready > 0) {
        যদি (length > 0) {
            bytes_written = লিখ(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        যদি (bytes_written > 0) {
            *pos += bytes_written;
        }
    } অন্যথা যদি (ready == 0) {
        SDL_SetError("Pipe timeout");
    } অন্যথা  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, রিক্ত, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, রিক্ত);
#অন্যথা
    pthread_sigmask(SIG_SETMASK, &old_sig_set, রিক্ত);
#endif

    প্রত্যাগম bytes_written;
}

স্থির ssize_t ReadPipe(পূর্ণাঙ্ক fd, শূন্য **buffer, size_t *total_length, Sint64 timeout_ns)
{
    শূন্য *output_buffer = রিক্ত;
    বর্ণ temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    ধ্রুব পূর্ণাঙ্ক ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    যদি (ready > 0) {
        bytes_read = পঠ(fd, temp, পরিমাণ(temp));
    } অন্যথা যদি (ready == 0) {
        SDL_SetError("Pipe timeout");
    } অন্যথা {
        SDL_SetError("Pipe poll error");
    }

    যদি (bytes_read > 0) {
        ধ্রুব size_t pos = *total_length;
        *total_length += bytes_read;

        ধ্রুব size_t new_buffer_length = *total_length + পরিমাণ(Uint32);

        যদি (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } অন্যথা {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        যদি (!output_buffer) {
            bytes_read = -1;
        } অন্যথা {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - পরিমাণ(Uint32)), 0, পরিমাণ(Uint32));

            *buffer = output_buffer;
        }
    }

    প্রত্যাগম bytes_read;
}

স্থির bool MIMEDataListHasType(সংরচনা wl_array *list, ধ্রুব বর্ণ *mime_type)
{
    ধ্রুব বর্ণ **item;
    wl_array_for_each(item, list) {
        যদি (SDL_strcmp(*item, mime_type) == 0) {
            প্রত্যাগম true;
        }
    }

    প্রত্যাগম false;
}

স্থির bool MIMEDataListAdd(সংরচনা wl_array *list, ধ্রুব বর্ণ *mime_type)
{
    যদি (!MIMEDataListHasType(list, mime_type)) {
        বর্ণ **item = WAYLAND_wl_array_add(list, পরিমাণ(বর্ণ *));
        *item = SDL_strdup(mime_type);
    }

    প্রত্যাগম true;
}

স্থির শূন্য MIMEDataListFree(সংরচনা wl_array *list)
{
    বর্ণ **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

স্থির শূন্য data_source_handle_target(শূন্য *data, সংরচনা wl_data_source *wl_data_source, ধ্রুব বর্ণ *mime_type)
{
}

স্থির শূন্য data_source_handle_send(শূন্য *data, সংরচনা wl_data_source *wl_data_source, ধ্রুব বর্ণ *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

স্থির শূন্য data_source_handle_cancelled(শূন্য *data, সংরচনা wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    যদি (source) {
        Wayland_DataSourceDestroy(source);
    }
}

স্থির শূন্য data_source_handle_dnd_drop_performed(শূন্য *data, সংরচনা wl_data_source *wl_data_source)
{
}

স্থির শূন্য data_source_handle_dnd_finished(শূন্য *data, সংরচনা wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    যদি (source) {
        Wayland_DataSourceDestroy(source);
    }
}

স্থির শূন্য data_source_handle_action(শূন্য *data, সংরচনা wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

স্থির ধ্রুব সংরচনা wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, পরিমাণ(*data_source));
    যদি (!data_source) {
        প্রত্যাগম রিক্ত;
    }

    সংরচনা wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    প্রত্যাগম data_source;
}

স্থির শূন্য primary_selection_source_send(শূন্য *data, সংরচনা zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ধ্রুব বর্ণ *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

স্থির শূন্য primary_selection_source_cancelled(শূন্য *data, সংরচনা zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

স্থির ধ্রুব সংরচনা zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, পরিমাণ(*primary_selection_source));
    যদি (!primary_selection_source) {
        প্রত্যাগম রিক্ত;
    }

    সংরচনা zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    প্রত্যাগম primary_selection_source;
}

স্থির size_t SendData(ধ্রুব শূন্য *data, size_t length, পূর্ণাঙ্ক fd)
{
    size_t result = 0;

    যদি (length > 0 && data) {
        যাবত্ (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    প্রত্যাগম result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ধ্রুব বর্ণ *mime_type, পূর্ণাঙ্ক fd)
{
    ধ্রুব শূন্য *data = রিক্ত;
    size_t length = 0;

    যদি (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } অন্যথা যদি (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    প্রত্যাগম SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ধ্রুব বর্ণ *mime_type, পূর্ণাঙ্ক fd)
{
    ধ্রুব শূন্য *data = রিক্ত;
    size_t length = 0;

    যদি (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    প্রত্যাগম SendData(data, length, fd);
}

শূন্য Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata, Uint32 sequence)
{
    যদি (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

শূন্য Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, শূন্য *userdata)
{
    যদি (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

স্থির শূন্য *CloneDataBuffer(ধ্রুব শূন্য *buffer, ধ্রুব size_t *len)
{
    শূন্য *clone = রিক্ত;
    যদি (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+পরিমাণ(Uint32));
        যদি (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, পরিমাণ(Uint32));
        }
    }
    প্রত্যাগম clone;
}

শূন্য *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ধ্রুব বর্ণ *mime_type, size_t *length)
{
    শূন্য *buffer = রিক্ত;
    *length = 0;

    যদি (!source) {
        SDL_SetError("Invalid data source");
    } অন্যথা যদি (source->data_callback) {
        ধ্রুব শূন্য *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    প্রত্যাগম buffer;
}

শূন্য *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ধ্রুব বর্ণ *mime_type, size_t *length)
{
    শূন্য *buffer = রিক্ত;
    *length = 0;

    যদি (!source) {
        SDL_SetError("Invalid primary selection source");
    } অন্যথা যদি (source->data_callback) {
        ধ্রুব শূন্য *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    প্রত্যাগম buffer;
}

শূন্য Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    যদি (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        যদি (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = রিক্ত;
        }
        wl_data_source_destroy(source->source);
        যদি (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } অন্যথা যদি (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

শূন্য Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    যদি (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        যদি (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = রিক্ত;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        যদি (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

স্থির শূন্য SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

স্থির শূন্য offer_source_done_handler(শূন্য *data, সংরচনা wl_callback *callback, uint32_t callback_data)
{
    যদি (!callback) {
        প্রত্যাগম;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    বর্ণ *id = রিক্ত;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = রিক্ত;

    যাবত্ (ReadPipe(offer->read_fd, (শূন্য **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    যদি (id) {
        ধ্রুব bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        যদি (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } অন্যথা {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = রিক্ত;
        }
    }
}

স্থির ধ্রুব সংরচনা wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

স্থির শূন্য UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        যদি (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = রিক্ত;

            // Don't clear the offer that is about to be set.
            যদি (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = রিক্ত;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

স্থির শূন্য SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    বর্ণ **new_mime_types = রিক্ত;
    size_t অঙ্ক_formats = 0;

    যদি (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        ধ্রুব বর্ণ **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            যদি (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                প্রত্যাগম;
            }

            ++অঙ্ক_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (অঙ্ক_formats + 1) * পরিমাণ(বর্ণ *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        যদি (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_প্রবেশ, "unable to allocate new_mime_types");
            প্রত্যাগম;
        }

        // Second pass to fill.
        বর্ণ *strPtr = (বর্ণ *)(new_mime_types + অঙ্ক_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = রিক্ত;
        পূর্ণাঙ্ক i = 0;
        wl_array_for_each(item, &offer->mimes) {
            যদি (!item) {
                অনুবর্ত;
            }

            new_mime_types[i++] = strPtr;
            ধ্রুব size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[অঙ্ক_formats] = রিক্ত;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, অঙ্ক_formats);
}

শূন্য Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ধ্রুব bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    যদি (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

শূন্য *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        প্রত্যাগম রিক্ত;
    }

    যদি (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        প্রত্যাগম রিক্ত;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    শূন্য *buffer = রিক্ত;
    যাবত্ (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    প্রত্যাগম buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ধ্রুব বর্ণ *mime_type, ধ্রুব সংরচনা wl_callback_listener *completion_listener, শূন্য *userdata)
{
    পূর্ণাঙ্ক pipefd[2];

    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        প্রত্যাগম false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    যদি (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    যদি (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = রিক্ত;
    }

    যদি (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } অন্যথা {
        প্রত্যাগম SDL_SetError("Could not create pipe");
    }

    প্রত্যাগম true;
}

শূন্য *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ধ্রুব বর্ণ *mime_type, size_t *length)
{
    পূর্ণাঙ্ক pipefd[2];
    শূন্য *buffer = রিক্ত;
    *length = 0;

    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        প্রত্যাগম রিক্ত;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    যদি (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        যাবত্ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } অন্যথা {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_প্রবেশ,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    প্রত্যাগম buffer;
}

শূন্য *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুব বর্ণ *mime_type, size_t *length)
{
    পূর্ণাঙ্ক pipefd[2];
    শূন্য *buffer = রিক্ত;
    *length = 0;

    যদি (!offer) {
        SDL_SetError("Invalid data offer");
        প্রত্যাগম রিক্ত;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    যদি (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        যাবত্ (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } অন্যথা {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_প্রবেশ,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    প্রত্যাগম buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ধ্রুব বর্ণ *mime_type)
{
    প্রত্যাগম MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুব বর্ণ *mime_type)
{
    প্রত্যাগম MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ধ্রুব বর্ণ *mime_type)
{
    যদি (offer && mime_type) {
        প্রত্যাগম MIMEDataListHasType(&offer->mimes, mime_type);
    }
    প্রত্যাগম false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ধ্রুব বর্ণ *mime_type)
{
    যদি (offer && mime_type) {
        প্রত্যাগম MIMEDataListHasType(&offer->mimes, mime_type);
    }
    প্রত্যাগম false;
}

শূন্য Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    যদি (offer) {
        যদি (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        যদি (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
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

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, ধ্রুব বর্ণ **mime_types, size_t mime_গুনতি)
{
    যদি (!data_device) {
        প্রত্যাগম SDL_SetError("Invalid Data Device");
    }
    যদি (!source) {
        প্রত্যাগম SDL_SetError("Invalid source");
    }

    যদি (mime_গুনতি) {
        প্রতি (size_t index = 0; index < mime_গুনতি; ++index) {
            ধ্রুব বর্ণ *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        যদি (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } অন্যথা {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = রিক্ত;
        প্রত্যাগম SDL_SetError("No mime data");
    }

    প্রত্যাগম true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ধ্রুব বর্ণ *ধ্রুব *mime_types, size_t mime_গুনতি)
{
    যদি (!primary_selection_device) {
        প্রত্যাগম SDL_SetError("Invalid Primary Selection Device");
    }
    যদি (!source) {
        প্রত্যাগম SDL_SetError("Invalid source");
    }

    যদি (mime_গুনতি) {
        প্রতি (size_t index = 0; index < mime_গুনতি; ++index) {
            ধ্রুব বর্ণ *mime_type = mime_types[index];
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
        primary_selection_device->selection_source = রিক্ত;
        প্রত্যাগম SDL_SetError("No mime data");
    }

    প্রত্যাগম true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

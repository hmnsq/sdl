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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <limits.h>
#अन्तर्भाव <signal.h>

#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../SDL_clipboard_c.h"

#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandevents_c.h"
#अन्तर्भाव "SDL_waylanddatamanager.h"
#अन्तर्भाव "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#अन्तर्भाव <errno.h>
#अन्तर्भाव <time.h>
स्थिर पूर्णाङ्क sigtimedwait(ध्रुव sigset_t *set, siginfo_t *info, ध्रुव संरचना timespec *timeout)
{
    संरचना timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    करोहि {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        अत्थाय (पूर्णाङ्क signo = 1; signo < NSIG; ++signo) {
            सचे (sigismember(set, signo) && sigismember(&pending, signo)) {
                सचे (!sigwait(set, &signo)) {
                    सचे (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    पटिनिवत्त signo;
                } अञ्ञथा {
                    पटिनिवत्त -1;
                }
            }
        }

        सचे (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(संरचना timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } याव (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    पटिनिवत्त -1;
}
#endif

स्थिर ssize_t WritePipe(पूर्णाङ्क fd, ध्रुव शून्य *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    ध्रुव ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    संरचना timespec zerotime = { 0 };

    ध्रुव पूर्णाङ्क ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#अञ्ञथा
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    सचे (ready > 0) {
        सचे (length > 0) {
            bytes_written = लिख(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        सचे (bytes_written > 0) {
            *pos += bytes_written;
        }
    } अञ्ञथा सचे (ready == 0) {
        SDL_SetError("Pipe timeout");
    } अञ्ञथा  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, रिक्त, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, रिक्त);
#अञ्ञथा
    pthread_sigmask(SIG_SETMASK, &old_sig_set, रिक्त);
#endif

    पटिनिवत्त bytes_written;
}

स्थिर ssize_t ReadPipe(पूर्णाङ्क fd, शून्य **buffer, size_t *total_length, Sint64 timeout_ns)
{
    शून्य *output_buffer = रिक्त;
    वर्ण temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    ध्रुव पूर्णाङ्क ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    सचे (ready > 0) {
        bytes_read = पठ(fd, temp, परिमाण(temp));
    } अञ्ञथा सचे (ready == 0) {
        SDL_SetError("Pipe timeout");
    } अञ्ञथा {
        SDL_SetError("Pipe poll error");
    }

    सचे (bytes_read > 0) {
        ध्रुव size_t pos = *total_length;
        *total_length += bytes_read;

        ध्रुव size_t new_buffer_length = *total_length + परिमाण(Uint32);

        सचे (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } अञ्ञथा {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        सचे (!output_buffer) {
            bytes_read = -1;
        } अञ्ञथा {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - परिमाण(Uint32)), 0, परिमाण(Uint32));

            *buffer = output_buffer;
        }
    }

    पटिनिवत्त bytes_read;
}

स्थिर bool MIMEDataListHasType(संरचना wl_array *list, ध्रुव वर्ण *mime_type)
{
    ध्रुव वर्ण **item;
    wl_array_for_each(item, list) {
        सचे (SDL_strcmp(*item, mime_type) == 0) {
            पटिनिवत्त true;
        }
    }

    पटिनिवत्त false;
}

स्थिर bool MIMEDataListAdd(संरचना wl_array *list, ध्रुव वर्ण *mime_type)
{
    सचे (!MIMEDataListHasType(list, mime_type)) {
        वर्ण **item = WAYLAND_wl_array_add(list, परिमाण(वर्ण *));
        *item = SDL_strdup(mime_type);
    }

    पटिनिवत्त true;
}

स्थिर शून्य MIMEDataListFree(संरचना wl_array *list)
{
    वर्ण **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

स्थिर शून्य data_source_handle_target(शून्य *data, संरचना wl_data_source *wl_data_source, ध्रुव वर्ण *mime_type)
{
}

स्थिर शून्य data_source_handle_send(शून्य *data, संरचना wl_data_source *wl_data_source, ध्रुव वर्ण *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

स्थिर शून्य data_source_handle_cancelled(शून्य *data, संरचना wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    सचे (source) {
        Wayland_DataSourceDestroy(source);
    }
}

स्थिर शून्य data_source_handle_dnd_drop_performed(शून्य *data, संरचना wl_data_source *wl_data_source)
{
}

स्थिर शून्य data_source_handle_dnd_finished(शून्य *data, संरचना wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    सचे (source) {
        Wayland_DataSourceDestroy(source);
    }
}

स्थिर शून्य data_source_handle_action(शून्य *data, संरचना wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

स्थिर ध्रुव संरचना wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, परिमाण(*data_source));
    सचे (!data_source) {
        पटिनिवत्त रिक्त;
    }

    संरचना wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    पटिनिवत्त data_source;
}

स्थिर शून्य primary_selection_source_send(शून्य *data, संरचना zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ध्रुव वर्ण *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

स्थिर शून्य primary_selection_source_cancelled(शून्य *data, संरचना zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

स्थिर ध्रुव संरचना zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, परिमाण(*primary_selection_source));
    सचे (!primary_selection_source) {
        पटिनिवत्त रिक्त;
    }

    संरचना zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    पटिनिवत्त primary_selection_source;
}

स्थिर size_t SendData(ध्रुव शून्य *data, size_t length, पूर्णाङ्क fd)
{
    size_t result = 0;

    सचे (length > 0 && data) {
        याव (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    पटिनिवत्त result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd)
{
    ध्रुव शून्य *data = रिक्त;
    size_t length = 0;

    सचे (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } अञ्ञथा सचे (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    पटिनिवत्त SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd)
{
    ध्रुव शून्य *data = रिक्त;
    size_t length = 0;

    सचे (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    पटिनिवत्त SendData(data, length, fd);
}

शून्य Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata, Uint32 sequence)
{
    सचे (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

शून्य Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata)
{
    सचे (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

स्थिर शून्य *CloneDataBuffer(ध्रुव शून्य *buffer, ध्रुव size_t *len)
{
    शून्य *clone = रिक्त;
    सचे (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+परिमाण(Uint32));
        सचे (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, परिमाण(Uint32));
        }
    }
    पटिनिवत्त clone;
}

शून्य *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ध्रुव वर्ण *mime_type, size_t *length)
{
    शून्य *buffer = रिक्त;
    *length = 0;

    सचे (!source) {
        SDL_SetError("Invalid data source");
    } अञ्ञथा सचे (source->data_callback) {
        ध्रुव शून्य *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    पटिनिवत्त buffer;
}

शून्य *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, size_t *length)
{
    शून्य *buffer = रिक्त;
    *length = 0;

    सचे (!source) {
        SDL_SetError("Invalid primary selection source");
    } अञ्ञथा सचे (source->data_callback) {
        ध्रुव शून्य *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    पटिनिवत्त buffer;
}

शून्य Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    सचे (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        सचे (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = रिक्त;
        }
        wl_data_source_destroy(source->source);
        सचे (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } अञ्ञथा सचे (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

शून्य Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    सचे (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        सचे (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = रिक्त;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        सचे (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

स्थिर शून्य SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

स्थिर शून्य offer_source_done_handler(शून्य *data, संरचना wl_callback *callback, uint32_t callback_data)
{
    सचे (!callback) {
        पटिनिवत्त;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    वर्ण *id = रिक्त;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = रिक्त;

    याव (ReadPipe(offer->read_fd, (शून्य **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    सचे (id) {
        ध्रुव bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        सचे (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } अञ्ञथा {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = रिक्त;
        }
    }
}

स्थिर ध्रुव संरचना wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

स्थिर शून्य UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        सचे (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = रिक्त;

            // Don't clear the offer that is about to be set.
            सचे (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = रिक्त;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

स्थिर शून्य SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    वर्ण **new_mime_types = रिक्त;
    size_t अङ्कः_formats = 0;

    सचे (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        ध्रुव वर्ण **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            सचे (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                पटिनिवत्त;
            }

            ++अङ्कः_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (अङ्कः_formats + 1) * परिमाण(वर्ण *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        सचे (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_निवेशः, "unable to allocate new_mime_types");
            पटिनिवत्त;
        }

        // Second pass to fill.
        वर्ण *strPtr = (वर्ण *)(new_mime_types + अङ्कः_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = रिक्त;
        पूर्णाङ्क i = 0;
        wl_array_for_each(item, &offer->mimes) {
            सचे (!item) {
                अनुवर्त;
            }

            new_mime_types[i++] = strPtr;
            ध्रुव size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[अङ्कः_formats] = रिक्त;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, अङ्कः_formats);
}

शून्य Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ध्रुव bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    सचे (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

शून्य *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    सचे (!offer) {
        SDL_SetError("Invalid data offer");
        पटिनिवत्त रिक्त;
    }

    सचे (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        पटिनिवत्त रिक्त;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    शून्य *buffer = रिक्त;
    याव (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    पटिनिवत्त buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type, ध्रुव संरचना wl_callback_listener *completion_listener, शून्य *userdata)
{
    पूर्णाङ्क pipefd[2];

    सचे (!offer) {
        SDL_SetError("Invalid data offer");
        पटिनिवत्त false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    सचे (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    सचे (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = रिक्त;
    }

    सचे (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } अञ्ञथा {
        पटिनिवत्त SDL_SetError("Could not create pipe");
    }

    पटिनिवत्त true;
}

शून्य *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type, size_t *length)
{
    पूर्णाङ्क pipefd[2];
    शून्य *buffer = रिक्त;
    *length = 0;

    सचे (!offer) {
        SDL_SetError("Invalid data offer");
        पटिनिवत्त रिक्त;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    सचे (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        याव (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } अञ्ञथा {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    पटिनिवत्त buffer;
}

शून्य *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type, size_t *length)
{
    पूर्णाङ्क pipefd[2];
    शून्य *buffer = रिक्त;
    *length = 0;

    सचे (!offer) {
        SDL_SetError("Invalid data offer");
        पटिनिवत्त रिक्त;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    सचे (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        याव (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } अञ्ञथा {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    पटिनिवत्त buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type)
{
    पटिनिवत्त MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type)
{
    पटिनिवत्त MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ध्रुव वर्ण *mime_type)
{
    सचे (offer && mime_type) {
        पटिनिवत्त MIMEDataListHasType(&offer->mimes, mime_type);
    }
    पटिनिवत्त false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type)
{
    सचे (offer && mime_type) {
        पटिनिवत्त MIMEDataListHasType(&offer->mimes, mime_type);
    }
    पटिनिवत्त false;
}

शून्य Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    सचे (offer) {
        सचे (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        सचे (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

शून्य Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    सचे (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, ध्रुव वर्ण **mime_types, size_t mime_गणनम्)
{
    सचे (!data_device) {
        पटिनिवत्त SDL_SetError("Invalid Data Device");
    }
    सचे (!source) {
        पटिनिवत्त SDL_SetError("Invalid source");
    }

    सचे (mime_गणनम्) {
        अत्थाय (size_t index = 0; index < mime_गणनम्; ++index) {
            ध्रुव वर्ण *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        सचे (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } अञ्ञथा {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = रिक्त;
        पटिनिवत्त SDL_SetError("No mime data");
    }

    पटिनिवत्त true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ध्रुव वर्ण *ध्रुव *mime_types, size_t mime_गणनम्)
{
    सचे (!primary_selection_device) {
        पटिनिवत्त SDL_SetError("Invalid Primary Selection Device");
    }
    सचे (!source) {
        पटिनिवत्त SDL_SetError("Invalid source");
    }

    सचे (mime_गणनम्) {
        अत्थाय (size_t index = 0; index < mime_गणनम्; ++index) {
            ध्रुव वर्ण *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        सचे (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } अञ्ञथा {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = रिक्त;
        पटिनिवत्त SDL_SetError("No mime data");
    }

    पटिनिवत्त true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

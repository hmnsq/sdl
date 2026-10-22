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

#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#شامل <fcntl.h>
#شامل <unistd.h>
#شامل <limits.h>
#شامل <signal.h>

#شامل "../../core/unix/SDL_poll.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../SDL_clipboard_c.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandevents_c.h"
#شامل "SDL_waylanddatamanager.h"
#شامل "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#شامل <errno.h>
#شامل <time.h>
ایستا صحیح sigtimedwait(ثابت sigset_t *set, siginfo_t *info, ثابت ساختار timespec *timeout)
{
    ساختار timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    انجامبده {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        برای (صحیح signo = 1; signo < NSIG; ++signo) {
            اگر (sigismember(set, signo) && sigismember(&pending, signo)) {
                اگر (!sigwait(set, &signo)) {
                    اگر (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    بازگشت signo;
                } وگرنه {
                    بازگشت -1;
                }
            }
        }

        اگر (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(ساختار timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } وقتی (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    بازگشت -1;
}
#endif

ایستا ssize_t WritePipe(صحیح fd, ثابت تهی *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    ثابت ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    ساختار timespec zerotime = { 0 };

    ثابت صحیح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#وگرنه
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    اگر (ready > 0) {
        اگر (length > 0) {
            bytes_written = اكتب(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        اگر (bytes_written > 0) {
            *pos += bytes_written;
        }
    } وگرنه اگر (ready == 0) {
        SDL_SetError("Pipe timeout");
    } وگرنه  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, پوچ, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, پوچ);
#وگرنه
    pthread_sigmask(SIG_SETMASK, &old_sig_set, پوچ);
#endif

    بازگشت bytes_written;
}

ایستا ssize_t ReadPipe(صحیح fd, تهی **buffer, size_t *total_length, Sint64 timeout_ns)
{
    تهی *output_buffer = پوچ;
    نویسه temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    ثابت صحیح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    اگر (ready > 0) {
        bytes_read = اقرأ(fd, temp, اندازه(temp));
    } وگرنه اگر (ready == 0) {
        SDL_SetError("Pipe timeout");
    } وگرنه {
        SDL_SetError("Pipe poll error");
    }

    اگر (bytes_read > 0) {
        ثابت size_t pos = *total_length;
        *total_length += bytes_read;

        ثابت size_t new_buffer_length = *total_length + اندازه(Uint32);

        اگر (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } وگرنه {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        اگر (!output_buffer) {
            bytes_read = -1;
        } وگرنه {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - اندازه(Uint32)), 0, اندازه(Uint32));

            *buffer = output_buffer;
        }
    }

    بازگشت bytes_read;
}

ایستا bool MIMEDataListHasType(ساختار wl_array *list, ثابت نویسه *mime_type)
{
    ثابت نویسه **item;
    wl_array_for_each(item, list) {
        اگر (SDL_strcmp(*item, mime_type) == 0) {
            بازگشت true;
        }
    }

    بازگشت false;
}

ایستا bool MIMEDataListAdd(ساختار wl_array *list, ثابت نویسه *mime_type)
{
    اگر (!MIMEDataListHasType(list, mime_type)) {
        نویسه **item = WAYLAND_wl_array_add(list, اندازه(نویسه *));
        *item = SDL_strdup(mime_type);
    }

    بازگشت true;
}

ایستا تهی MIMEDataListFree(ساختار wl_array *list)
{
    نویسه **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

ایستا تهی data_source_handle_target(تهی *data, ساختار wl_data_source *wl_data_source, ثابت نویسه *mime_type)
{
}

ایستا تهی data_source_handle_send(تهی *data, ساختار wl_data_source *wl_data_source, ثابت نویسه *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

ایستا تهی data_source_handle_cancelled(تهی *data, ساختار wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    اگر (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ایستا تهی data_source_handle_dnd_drop_performed(تهی *data, ساختار wl_data_source *wl_data_source)
{
}

ایستا تهی data_source_handle_dnd_finished(تهی *data, ساختار wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    اگر (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ایستا تهی data_source_handle_action(تهی *data, ساختار wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

ایستا ثابت ساختار wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, اندازه(*data_source));
    اگر (!data_source) {
        بازگشت پوچ;
    }

    ساختار wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    بازگشت data_source;
}

ایستا تهی primary_selection_source_send(تهی *data, ساختار zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ثابت نویسه *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

ایستا تهی primary_selection_source_cancelled(تهی *data, ساختار zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

ایستا ثابت ساختار zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, اندازه(*primary_selection_source));
    اگر (!primary_selection_source) {
        بازگشت پوچ;
    }

    ساختار zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    بازگشت primary_selection_source;
}

ایستا size_t SendData(ثابت تهی *data, size_t length, صحیح fd)
{
    size_t result = 0;

    اگر (length > 0 && data) {
        وقتی (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    بازگشت result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ثابت نویسه *mime_type, صحیح fd)
{
    ثابت تهی *data = پوچ;
    size_t length = 0;

    اگر (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } وگرنه اگر (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    بازگشت SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ثابت نویسه *mime_type, صحیح fd)
{
    ثابت تهی *data = پوچ;
    size_t length = 0;

    اگر (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    بازگشت SendData(data, length, fd);
}

تهی Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, تهی *userdata, Uint32 sequence)
{
    اگر (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

تهی Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, تهی *userdata)
{
    اگر (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

ایستا تهی *CloneDataBuffer(ثابت تهی *buffer, ثابت size_t *len)
{
    تهی *clone = پوچ;
    اگر (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+اندازه(Uint32));
        اگر (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, اندازه(Uint32));
        }
    }
    بازگشت clone;
}

تهی *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ثابت نویسه *mime_type, size_t *length)
{
    تهی *buffer = پوچ;
    *length = 0;

    اگر (!source) {
        SDL_SetError("Invalid data source");
    } وگرنه اگر (source->data_callback) {
        ثابت تهی *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    بازگشت buffer;
}

تهی *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ثابت نویسه *mime_type, size_t *length)
{
    تهی *buffer = پوچ;
    *length = 0;

    اگر (!source) {
        SDL_SetError("Invalid primary selection source");
    } وگرنه اگر (source->data_callback) {
        ثابت تهی *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    بازگشت buffer;
}

تهی Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    اگر (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        اگر (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = پوچ;
        }
        wl_data_source_destroy(source->source);
        اگر (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } وگرنه اگر (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

تهی Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    اگر (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        اگر (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = پوچ;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        اگر (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ایستا تهی SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

ایستا تهی offer_source_done_handler(تهی *data, ساختار wl_callback *callback, uint32_t callback_data)
{
    اگر (!callback) {
        بازگشت;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    نویسه *id = پوچ;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = پوچ;

    وقتی (ReadPipe(offer->read_fd, (تهی **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    اگر (id) {
        ثابت bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        اگر (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } وگرنه {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = پوچ;
        }
    }
}

ایستا ثابت ساختار wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

ایستا تهی UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        اگر (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = پوچ;

            // Don't clear the offer that is about to be set.
            اگر (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = پوچ;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

ایستا تهی SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    نویسه **new_mime_types = پوچ;
    size_t رقم_formats = 0;

    اگر (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        ثابت نویسه **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            اگر (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                بازگشت;
            }

            ++رقم_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (رقم_formats + 1) * اندازه(نویسه *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        اگر (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_درون_داد, "unable to allocate new_mime_types");
            بازگشت;
        }

        // Second pass to fill.
        نویسه *strPtr = (نویسه *)(new_mime_types + رقم_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = پوچ;
        صحیح i = 0;
        wl_array_for_each(item, &offer->mimes) {
            اگر (!item) {
                ادامه;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[رقم_formats] = پوچ;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, رقم_formats);
}

تهی Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    اگر (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

تهی *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    اگر (!offer) {
        SDL_SetError("Invalid data offer");
        بازگشت پوچ;
    }

    اگر (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        بازگشت پوچ;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    تهی *buffer = پوچ;
    وقتی (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    بازگشت buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type, ثابت ساختار wl_callback_listener *completion_listener, تهی *userdata)
{
    صحیح pipefd[2];

    اگر (!offer) {
        SDL_SetError("Invalid data offer");
        بازگشت false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    اگر (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    اگر (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = پوچ;
    }

    اگر (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } وگرنه {
        بازگشت SDL_SetError("Could not create pipe");
    }

    بازگشت true;
}

تهی *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type, size_t *length)
{
    صحیح pipefd[2];
    تهی *buffer = پوچ;
    *length = 0;

    اگر (!offer) {
        SDL_SetError("Invalid data offer");
        بازگشت پوچ;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    اگر (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        وقتی (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } وگرنه {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    بازگشت buffer;
}

تهی *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت نویسه *mime_type, size_t *length)
{
    صحیح pipefd[2];
    تهی *buffer = پوچ;
    *length = 0;

    اگر (!offer) {
        SDL_SetError("Invalid data offer");
        بازگشت پوچ;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    اگر (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        وقتی (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } وگرنه {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_درون_داد,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    بازگشت buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type)
{
    بازگشت MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت نویسه *mime_type)
{
    بازگشت MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ثابت نویسه *mime_type)
{
    اگر (offer && mime_type) {
        بازگشت MIMEDataListHasType(&offer->mimes, mime_type);
    }
    بازگشت false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت نویسه *mime_type)
{
    اگر (offer && mime_type) {
        بازگشت MIMEDataListHasType(&offer->mimes, mime_type);
    }
    بازگشت false;
}

تهی Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    اگر (offer) {
        اگر (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        اگر (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

تهی Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    اگر (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, ثابت نویسه **mime_types, size_t mime_شمار)
{
    اگر (!data_device) {
        بازگشت SDL_SetError("Invalid Data Device");
    }
    اگر (!source) {
        بازگشت SDL_SetError("Invalid source");
    }

    اگر (mime_شمار) {
        برای (size_t index = 0; index < mime_شمار; ++index) {
            ثابت نویسه *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        اگر (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } وگرنه {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = پوچ;
        بازگشت SDL_SetError("No mime data");
    }

    بازگشت true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ثابت نویسه *ثابت *mime_types, size_t mime_شمار)
{
    اگر (!primary_selection_device) {
        بازگشت SDL_SetError("Invalid Primary Selection Device");
    }
    اگر (!source) {
        بازگشت SDL_SetError("Invalid source");
    }

    اگر (mime_شمار) {
        برای (size_t index = 0; index < mime_شمار; ++index) {
            ثابت نویسه *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        اگر (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } وگرنه {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = پوچ;
        بازگشت SDL_SetError("No mime data");
    }

    بازگشت true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

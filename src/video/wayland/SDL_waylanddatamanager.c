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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

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
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#ضمن <errno.h>
#ضمن <time.h>
ساكن صحيح sigtimedwait(ثابت sigset_t *set, siginfo_t *info, ثابت بنية timespec *timeout)
{
    بنية timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    𐡏𐡁𐡃 {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        لكل (صحيح signo = 1; signo < NSIG; ++signo) {
            𐡄𐡍 (sigismember(set, signo) && sigismember(&pending, signo)) {
                𐡄𐡍 (!sigwait(set, &signo)) {
                    𐡄𐡍 (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    أرجع signo;
                } وإلا {
                    أرجع -1;
                }
            }
        }

        𐡄𐡍 (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(بنية timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } طالما (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    أرجع -1;
}
#endif

ساكن ssize_t WritePipe(صحيح fd, ثابت فراغ *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    ثابت ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    بنية timespec zerotime = { 0 };

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#وإلا
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    𐡄𐡍 (ready > 0) {
        𐡄𐡍 (length > 0) {
            bytes_written = اكتب(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        𐡄𐡍 (bytes_written > 0) {
            *pos += bytes_written;
        }
    } وإلا 𐡄𐡍 (ready == 0) {
        SDL_SetError("Pipe timeout");
    } وإلا  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, عدم, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, عدم);
#وإلا
    pthread_sigmask(SIG_SETMASK, &old_sig_set, عدم);
#endif

    أرجع bytes_written;
}

ساكن ssize_t ReadPipe(صحيح fd, فراغ **buffer, size_t *total_length, Sint64 timeout_ns)
{
    فراغ *output_buffer = عدم;
    حرف temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    ثابت صحيح ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    𐡄𐡍 (ready > 0) {
        bytes_read = اقرأ(fd, temp, حجم(temp));
    } وإلا 𐡄𐡍 (ready == 0) {
        SDL_SetError("Pipe timeout");
    } وإلا {
        SDL_SetError("Pipe poll error");
    }

    𐡄𐡍 (bytes_read > 0) {
        ثابت size_t pos = *total_length;
        *total_length += bytes_read;

        ثابت size_t new_buffer_length = *total_length + حجم(Uint32);

        𐡄𐡍 (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } وإلا {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        𐡄𐡍 (!output_buffer) {
            bytes_read = -1;
        } وإلا {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - حجم(Uint32)), 0, حجم(Uint32));

            *buffer = output_buffer;
        }
    }

    أرجع bytes_read;
}

ساكن bool MIMEDataListHasType(بنية wl_array *list, ثابت حرف *mime_type)
{
    ثابت حرف **item;
    wl_array_for_each(item, list) {
        𐡄𐡍 (SDL_strcmp(*item, mime_type) == 0) {
            أرجع true;
        }
    }

    أرجع false;
}

ساكن bool MIMEDataListAdd(بنية wl_array *list, ثابت حرف *mime_type)
{
    𐡄𐡍 (!MIMEDataListHasType(list, mime_type)) {
        حرف **item = WAYLAND_wl_array_add(list, حجم(حرف *));
        *item = SDL_strdup(mime_type);
    }

    أرجع true;
}

ساكن فراغ MIMEDataListFree(بنية wl_array *list)
{
    حرف **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

ساكن فراغ data_source_handle_target(فراغ *data, بنية wl_data_source *wl_data_source, ثابت حرف *mime_type)
{
}

ساكن فراغ data_source_handle_send(فراغ *data, بنية wl_data_source *wl_data_source, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

ساكن فراغ data_source_handle_cancelled(فراغ *data, بنية wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    𐡄𐡍 (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ساكن فراغ data_source_handle_dnd_drop_performed(فراغ *data, بنية wl_data_source *wl_data_source)
{
}

ساكن فراغ data_source_handle_dnd_finished(فراغ *data, بنية wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    𐡄𐡍 (source) {
        Wayland_DataSourceDestroy(source);
    }
}

ساكن فراغ data_source_handle_action(فراغ *data, بنية wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

ساكن ثابت بنية wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, حجم(*data_source));
    𐡄𐡍 (!data_source) {
        أرجع عدم;
    }

    بنية wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    أرجع data_source;
}

ساكن فراغ primary_selection_source_send(فراغ *data, بنية zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ثابت حرف *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

ساكن فراغ primary_selection_source_cancelled(فراغ *data, بنية zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

ساكن ثابت بنية zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, حجم(*primary_selection_source));
    𐡄𐡍 (!primary_selection_source) {
        أرجع عدم;
    }

    بنية zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    أرجع primary_selection_source;
}

ساكن size_t SendData(ثابت فراغ *data, size_t length, صحيح fd)
{
    size_t result = 0;

    𐡄𐡍 (length > 0 && data) {
        طالما (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    أرجع result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *data = عدم;
    size_t length = 0;

    𐡄𐡍 (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } وإلا 𐡄𐡍 (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    أرجع SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ثابت حرف *mime_type, صحيح fd)
{
    ثابت فراغ *data = عدم;
    size_t length = 0;

    𐡄𐡍 (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    أرجع SendData(data, length, fd);
}

فراغ Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata, Uint32 sequence)
{
    𐡄𐡍 (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

فراغ Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, فراغ *userdata)
{
    𐡄𐡍 (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

ساكن فراغ *CloneDataBuffer(ثابت فراغ *buffer, ثابت size_t *len)
{
    فراغ *clone = عدم;
    𐡄𐡍 (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+حجم(Uint32));
        𐡄𐡍 (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, حجم(Uint32));
        }
    }
    أرجع clone;
}

فراغ *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, ثابت حرف *mime_type, size_t *length)
{
    فراغ *buffer = عدم;
    *length = 0;

    𐡄𐡍 (!source) {
        SDL_SetError("Invalid data source");
    } وإلا 𐡄𐡍 (source->data_callback) {
        ثابت فراغ *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    أرجع buffer;
}

فراغ *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, ثابت حرف *mime_type, size_t *length)
{
    فراغ *buffer = عدم;
    *length = 0;

    𐡄𐡍 (!source) {
        SDL_SetError("Invalid primary selection source");
    } وإلا 𐡄𐡍 (source->data_callback) {
        ثابت فراغ *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    أرجع buffer;
}

فراغ Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    𐡄𐡍 (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        𐡄𐡍 (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = عدم;
        }
        wl_data_source_destroy(source->source);
        𐡄𐡍 (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } وإلا 𐡄𐡍 (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

فراغ Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    𐡄𐡍 (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        𐡄𐡍 (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = عدم;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        𐡄𐡍 (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

ساكن فراغ offer_source_done_handler(فراغ *data, بنية wl_callback *callback, uint32_t callback_data)
{
    𐡄𐡍 (!callback) {
        أرجع;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    حرف *id = عدم;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = عدم;

    طالما (ReadPipe(offer->read_fd, (فراغ **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    𐡄𐡍 (id) {
        ثابت bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        𐡄𐡍 (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } وإلا {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = عدم;
        }
    }
}

ساكن ثابت بنية wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

ساكن فراغ UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        𐡄𐡍 (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = عدم;

            // Don't clear the offer that is about to be set.
            𐡄𐡍 (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = عدم;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

ساكن فراغ SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    حرف **new_mime_types = عدم;
    size_t num_formats = 0;

    𐡄𐡍 (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        ثابت حرف **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            𐡄𐡍 (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                أرجع;
            }

            ++num_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (num_formats + 1) * حجم(حرف *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        𐡄𐡍 (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "unable to allocate new_mime_types");
            أرجع;
        }

        // Second pass to fill.
        حرف *strPtr = (حرف *)(new_mime_types + num_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = عدم;
        صحيح i = 0;
        wl_array_for_each(item, &offer->mimes) {
            𐡄𐡍 (!item) {
                استمر;
            }

            new_mime_types[i++] = strPtr;
            ثابت size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[num_formats] = عدم;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, num_formats);
}

فراغ Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ثابت bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    𐡄𐡍 (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

فراغ *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    𐡄𐡍 (!offer) {
        SDL_SetError("Invalid data offer");
        أرجع عدم;
    }

    𐡄𐡍 (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        أرجع عدم;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    فراغ *buffer = عدم;
    طالما (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    أرجع buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type, ثابت بنية wl_callback_listener *completion_listener, فراغ *userdata)
{
    صحيح pipefd[2];

    𐡄𐡍 (!offer) {
        SDL_SetError("Invalid data offer");
        أرجع false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    𐡄𐡍 (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    𐡄𐡍 (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = عدم;
    }

    𐡄𐡍 (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } وإلا {
        أرجع SDL_SetError("Could not create pipe");
    }

    أرجع true;
}

فراغ *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type, size_t *length)
{
    صحيح pipefd[2];
    فراغ *buffer = عدم;
    *length = 0;

    𐡄𐡍 (!offer) {
        SDL_SetError("Invalid data offer");
        أرجع عدم;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    𐡄𐡍 (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } وإلا {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    أرجع buffer;
}

فراغ *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type, size_t *length)
{
    صحيح pipefd[2];
    فراغ *buffer = عدم;
    *length = 0;

    𐡄𐡍 (!offer) {
        SDL_SetError("Invalid data offer");
        أرجع عدم;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    𐡄𐡍 (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        طالما (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } وإلا {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    أرجع buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    أرجع MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, ثابت حرف *mime_type)
{
    𐡄𐡍 (offer && mime_type) {
        أرجع MIMEDataListHasType(&offer->mimes, mime_type);
    }
    أرجع false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ثابت حرف *mime_type)
{
    𐡄𐡍 (offer && mime_type) {
        أرجع MIMEDataListHasType(&offer->mimes, mime_type);
    }
    أرجع false;
}

فراغ Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    𐡄𐡍 (offer) {
        𐡄𐡍 (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        𐡄𐡍 (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

فراغ Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    𐡄𐡍 (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, ثابت حرف **mime_types, size_t mime_count)
{
    𐡄𐡍 (!data_device) {
        أرجع SDL_SetError("Invalid Data Device");
    }
    𐡄𐡍 (!source) {
        أرجع SDL_SetError("Invalid source");
    }

    𐡄𐡍 (mime_count) {
        لكل (size_t index = 0; index < mime_count; ++index) {
            ثابت حرف *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        𐡄𐡍 (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } وإلا {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = عدم;
        أرجع SDL_SetError("No mime data");
    }

    أرجع true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ثابت حرف *ثابت *mime_types, size_t mime_count)
{
    𐡄𐡍 (!primary_selection_device) {
        أرجع SDL_SetError("Invalid Primary Selection Device");
    }
    𐡄𐡍 (!source) {
        أرجع SDL_SetError("Invalid source");
    }

    𐡄𐡍 (mime_count) {
        لكل (size_t index = 0; index < mime_count; ++index) {
            ثابت حرف *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        𐡄𐡍 (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } وإلا {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = عدم;
        أرجع SDL_SetError("No mime data");
    }

    أرجع true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

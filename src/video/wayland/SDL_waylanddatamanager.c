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
स्थिर पूर्णांक sigtimedwait(स्थिरांक sigset_t *set, siginfo_t *info, स्थिरांक संरचना timespec *timeout)
{
    संरचना timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    करा {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        संक_बाकी(&pending);
        साठी (पूर्णांक signo = 1; signo < NSIG; ++signo) {
            जर (sigismember(set, signo) && sigismember(&pending, signo)) {
                जर (!sigwait(set, &signo)) {
                    जर (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    परत signo;
                } अन्यथा {
                    परत -1;
                }
            }
        }

        जर (timeout->tv_sec || timeout->tv_nsec) {
            दीर्घ ns = 20000000L; // 2/100ths of a second
            nanosleep(&(संरचना timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } पर्यंत (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    त्रुटि_सं = EAGAIN;
    परत -1;
}
#endif

स्थिर ssize_t WritePipe(पूर्णांक fd, स्थिरांक शून्य *buffer, माप_प्रकार total_length, माप_प्रकार *pos)
{
    ssize_t bytes_written = 0;
    स्थिरांक ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    संरचना timespec zerotime = { 0 };

    स्थिरांक पूर्णांक ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#अन्यथा
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    जर (ready > 0) {
        जर (length > 0) {
            bytes_written = लिख(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        जर (bytes_written > 0) {
            *pos += bytes_written;
        }
    } अन्यथा जर (ready == 0) {
        SDL_SetError("Pipe timeout");
    } अन्यथा  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, रिक्त, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, रिक्त);
#अन्यथा
    pthread_sigmask(SIG_SETMASK, &old_sig_set, रिक्त);
#endif

    परत bytes_written;
}

स्थिर ssize_t ReadPipe(पूर्णांक fd, शून्य **buffer, माप_प्रकार *total_length, Sint64 timeout_ns)
{
    शून्य *output_buffer = रिक्त;
    अक्षर temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    स्थिरांक पूर्णांक ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    जर (ready > 0) {
        bytes_read = पठ(fd, temp, आकार(temp));
    } अन्यथा जर (ready == 0) {
        SDL_SetError("Pipe timeout");
    } अन्यथा {
        SDL_SetError("Pipe poll error");
    }

    जर (bytes_read > 0) {
        स्थिरांक माप_प्रकार pos = *total_length;
        *total_length += bytes_read;

        स्थिरांक माप_प्रकार new_buffer_length = *total_length + आकार(Uint32);

        जर (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } अन्यथा {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        जर (!output_buffer) {
            bytes_read = -1;
        } अन्यथा {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - आकार(Uint32)), 0, आकार(Uint32));

            *buffer = output_buffer;
        }
    }

    परत bytes_read;
}

स्थिर bool MIMEDataListHasType(संरचना wl_array *list, स्थिरांक अक्षर *mime_type)
{
    स्थिरांक अक्षर **item;
    wl_array_for_each(item, list) {
        जर (SDL_strcmp(*item, mime_type) == 0) {
            परत true;
        }
    }

    परत false;
}

स्थिर bool MIMEDataListAdd(संरचना wl_array *list, स्थिरांक अक्षर *mime_type)
{
    जर (!MIMEDataListHasType(list, mime_type)) {
        अक्षर **item = WAYLAND_wl_array_add(list, आकार(अक्षर *));
        *item = SDL_strdup(mime_type);
    }

    परत true;
}

स्थिर शून्य MIMEDataListFree(संरचना wl_array *list)
{
    अक्षर **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

स्थिर शून्य data_source_handle_target(शून्य *data, संरचना wl_data_source *wl_data_source, स्थिरांक अक्षर *mime_type)
{
}

स्थिर शून्य data_source_handle_send(शून्य *data, संरचना wl_data_source *wl_data_source, स्थिरांक अक्षर *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

स्थिर शून्य data_source_handle_cancelled(शून्य *data, संरचना wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    जर (source) {
        Wayland_DataSourceDestroy(source);
    }
}

स्थिर शून्य data_source_handle_dnd_drop_performed(शून्य *data, संरचना wl_data_source *wl_data_source)
{
}

स्थिर शून्य data_source_handle_dnd_finished(शून्य *data, संरचना wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    जर (source) {
        Wayland_DataSourceDestroy(source);
    }
}

स्थिर शून्य data_source_handle_action(शून्य *data, संरचना wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

स्थिर स्थिरांक संरचना wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, आकार(*data_source));
    जर (!data_source) {
        परत रिक्त;
    }

    संरचना wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    परत data_source;
}

स्थिर शून्य primary_selection_source_send(शून्य *data, संरचना zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, स्थिरांक अक्षर *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

स्थिर शून्य primary_selection_source_cancelled(शून्य *data, संरचना zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

स्थिर स्थिरांक संरचना zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, आकार(*primary_selection_source));
    जर (!primary_selection_source) {
        परत रिक्त;
    }

    संरचना zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    परत primary_selection_source;
}

स्थिर माप_प्रकार SendData(स्थिरांक शून्य *data, माप_प्रकार length, पूर्णांक fd)
{
    माप_प्रकार result = 0;

    जर (length > 0 && data) {
        पर्यंत (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    बंद(fd);

    परत result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, स्थिरांक अक्षर *mime_type, पूर्णांक fd)
{
    स्थिरांक शून्य *data = रिक्त;
    माप_प्रकार length = 0;

    जर (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } अन्यथा जर (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    परत SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, स्थिरांक अक्षर *mime_type, पूर्णांक fd)
{
    स्थिरांक शून्य *data = रिक्त;
    माप_प्रकार length = 0;

    जर (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    परत SendData(data, length, fd);
}

शून्य Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata, Uint32 sequence)
{
    जर (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

शून्य Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata)
{
    जर (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

स्थिर शून्य *CloneDataBuffer(स्थिरांक शून्य *buffer, स्थिरांक माप_प्रकार *len)
{
    शून्य *clone = रिक्त;
    जर (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+आकार(Uint32));
        जर (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, आकार(Uint32));
        }
    }
    परत clone;
}

शून्य *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, स्थिरांक अक्षर *mime_type, माप_प्रकार *length)
{
    शून्य *buffer = रिक्त;
    *length = 0;

    जर (!source) {
        SDL_SetError("Invalid data source");
    } अन्यथा जर (source->data_callback) {
        स्थिरांक शून्य *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    परत buffer;
}

शून्य *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, स्थिरांक अक्षर *mime_type, माप_प्रकार *length)
{
    शून्य *buffer = रिक्त;
    *length = 0;

    जर (!source) {
        SDL_SetError("Invalid primary selection source");
    } अन्यथा जर (source->data_callback) {
        स्थिरांक शून्य *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    परत buffer;
}

शून्य Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    जर (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        जर (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = रिक्त;
        }
        wl_data_source_destroy(source->source);
        जर (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } अन्यथा जर (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

शून्य Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    जर (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        जर (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = रिक्त;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        जर (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

स्थिर शून्य SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

स्थिर शून्य offer_source_done_handler(शून्य *data, संरचना wl_callback *callback, uint32_t callback_data)
{
    जर (!callback) {
        परत;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    अक्षर *id = रिक्त;
    माप_प्रकार length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = रिक्त;

    पर्यंत (ReadPipe(offer->read_fd, (शून्य **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    बंद(offer->read_fd);
    offer->read_fd = -1;

    जर (id) {
        स्थिरांक bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        जर (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } अन्यथा {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = रिक्त;
        }
    }
}

स्थिर स्थिरांक संरचना wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

स्थिर शून्य UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        जर (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = रिक्त;

            // Don't clear the offer that is about to be set.
            जर (s != offer_seat) {
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
    अक्षर **new_mime_types = रिक्त;
    माप_प्रकार अंक_formats = 0;

    जर (offer) {
        माप_प्रकार alloc_size = 0;

        // Do a first pass to compute allocation size.
        स्थिरांक अक्षर **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            जर (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                परत;
            }

            ++अंक_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (अंक_formats + 1) * आकार(अक्षर *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        जर (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_आदान, "unable to allocate new_mime_types");
            परत;
        }

        // Second pass to fill.
        अक्षर *strPtr = (अक्षर *)(new_mime_types + अंक_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = रिक्त;
        पूर्णांक i = 0;
        wl_array_for_each(item, &offer->mimes) {
            जर (!item) {
                सुरूठेवा;
            }

            new_mime_types[i++] = strPtr;
            स्थिरांक माप_प्रकार len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[अंक_formats] = रिक्त;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, अंक_formats);
}

शून्य Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    स्थिरांक bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    जर (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

शून्य *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, माप_प्रकार *length)
{
    जर (!offer) {
        SDL_SetError("Invalid data offer");
        परत रिक्त;
    }

    जर (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        परत रिक्त;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    शून्य *buffer = रिक्त;
    पर्यंत (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    परत buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, स्थिरांक अक्षर *mime_type, स्थिरांक संरचना wl_callback_listener *completion_listener, शून्य *userdata)
{
    पूर्णांक pipefd[2];

    जर (!offer) {
        SDL_SetError("Invalid data offer");
        परत false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    जर (offer->read_fd >= 0) {
        बंद(offer->read_fd);
        offer->read_fd = -1;
    }
    जर (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = रिक्त;
    }

    जर (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        बंद(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } अन्यथा {
        परत SDL_SetError("Could not create pipe");
    }

    परत true;
}

शून्य *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, स्थिरांक अक्षर *mime_type, माप_प्रकार *length)
{
    पूर्णांक pipefd[2];
    शून्य *buffer = रिक्त;
    *length = 0;

    जर (!offer) {
        SDL_SetError("Invalid data offer");
        परत रिक्त;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    जर (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        बंद(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        पर्यंत (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        बंद(pipefd[0]);
    } अन्यथा {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    परत buffer;
}

शून्य *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, स्थिरांक अक्षर *mime_type, माप_प्रकार *length)
{
    पूर्णांक pipefd[2];
    शून्य *buffer = रिक्त;
    *length = 0;

    जर (!offer) {
        SDL_SetError("Invalid data offer");
        परत रिक्त;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    जर (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        बंद(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        पर्यंत (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        बंद(pipefd[0]);

    } अन्यथा {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_आदान,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    परत buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, स्थिरांक अक्षर *mime_type)
{
    परत MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, स्थिरांक अक्षर *mime_type)
{
    परत MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, स्थिरांक अक्षर *mime_type)
{
    जर (offer && mime_type) {
        परत MIMEDataListHasType(&offer->mimes, mime_type);
    }
    परत false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, स्थिरांक अक्षर *mime_type)
{
    जर (offer && mime_type) {
        परत MIMEDataListHasType(&offer->mimes, mime_type);
    }
    परत false;
}

शून्य Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    जर (offer) {
        जर (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        जर (offer->read_fd >= 0) {
            बंद(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

शून्य Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    जर (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, स्थिरांक अक्षर **mime_types, माप_प्रकार mime_मोजणी)
{
    जर (!data_device) {
        परत SDL_SetError("Invalid Data Device");
    }
    जर (!source) {
        परत SDL_SetError("Invalid source");
    }

    जर (mime_मोजणी) {
        साठी (माप_प्रकार index = 0; index < mime_मोजणी; ++index) {
            स्थिरांक अक्षर *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        जर (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } अन्यथा {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = रिक्त;
        परत SDL_SetError("No mime data");
    }

    परत true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                स्थिरांक अक्षर *स्थिरांक *mime_types, माप_प्रकार mime_मोजणी)
{
    जर (!primary_selection_device) {
        परत SDL_SetError("Invalid Primary Selection Device");
    }
    जर (!source) {
        परत SDL_SetError("Invalid source");
    }

    जर (mime_मोजणी) {
        साठी (माप_प्रकार index = 0; index < mime_मोजणी; ++index) {
            स्थिरांक अक्षर *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        जर (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } अन्यथा {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = रिक्त;
        परत SDL_SetError("No mime data");
    }

    परत true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

#include "../../core/unix/SDL_poll.h"
#include "../../events/SDL_events_c.h"
#include "../SDL_clipboard_c.h"

#include "SDL_waylandvideo.h"
#include "SDL_waylandevents_c.h"
#include "SDL_waylanddatamanager.h"
#include "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#define DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#ifndef HAVE_SIGTIMEDWAIT
#include <errno.h>
#include <time.h>
static ཧྲིལ sigtimedwait(const sigset_t *set, siginfo_t *info, const sa_nracanaa timespec *timeout)
{
    sa_nracanaa timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    do {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        དོན་ལུ (ཧྲིལ signo = 1; signo < NSIG; ++signo) {
            གལ་སྲིད (sigismember(set, signo) && sigismember(&pending, signo)) {
                གལ་སྲིད (!sigwait(set, &signo)) {
                    གལ་སྲིད (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    ལོག signo;
                } དེ་མིན {
                    ལོག -1;
                }
            }
        }

        གལ་སྲིད (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(sa_nracanaa timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } སྐབས (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    ལོག -1;
}
#endif

static ssize_t WritePipe(ཧྲིལ fd, const void *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    const ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    sa_nracanaa timespec zerotime = { 0 };

    const ཧྲིལ ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#དེ་མིན
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    གལ་སྲིད (ready > 0) {
        གལ་སྲིད (length > 0) {
            bytes_written = write(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        གལ་སྲིད (bytes_written > 0) {
            *pos += bytes_written;
        }
    } དེ་མིན གལ་སྲིད (ready == 0) {
        SDL_SetError("Pipe timeout");
    } དེ་མིན  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, NULL, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, NULL);
#དེ་མིན
    pthread_sigmask(SIG_SETMASK, &old_sig_set, NULL);
#endif

    ལོག bytes_written;
}

static ssize_t ReadPipe(ཧྲིལ fd, void **buffer, size_t *total_length, Sint64 timeout_ns)
{
    void *output_buffer = NULL;
    var_na temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    const ཧྲིལ ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    གལ་སྲིད (ready > 0) {
        bytes_read = read(fd, temp, parimaa_na(temp));
    } དེ་མིན གལ་སྲིད (ready == 0) {
        SDL_SetError("Pipe timeout");
    } དེ་མིན {
        SDL_SetError("Pipe poll error");
    }

    གལ་སྲིད (bytes_read > 0) {
        const size_t pos = *total_length;
        *total_length += bytes_read;

        const size_t new_buffer_length = *total_length + parimaa_na(Uint32);

        གལ་སྲིད (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } དེ་མིན {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        གལ་སྲིད (!output_buffer) {
            bytes_read = -1;
        } དེ་མིན {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - parimaa_na(Uint32)), 0, parimaa_na(Uint32));

            *buffer = output_buffer;
        }
    }

    ལོག bytes_read;
}

static bool MIMEDataListHasType(sa_nracanaa wl_array *list, const var_na *mime_type)
{
    const var_na **item;
    wl_array_for_each(item, list) {
        གལ་སྲིད (SDL_strcmp(*item, mime_type) == 0) {
            ལོག true;
        }
    }

    ལོག false;
}

static bool MIMEDataListAdd(sa_nracanaa wl_array *list, const var_na *mime_type)
{
    གལ་སྲིད (!MIMEDataListHasType(list, mime_type)) {
        var_na **item = WAYLAND_wl_array_add(list, parimaa_na(var_na *));
        *item = SDL_strdup(mime_type);
    }

    ལོག true;
}

static void MIMEDataListFree(sa_nracanaa wl_array *list)
{
    var_na **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

static void data_source_handle_target(void *data, sa_nracanaa wl_data_source *wl_data_source, const var_na *mime_type)
{
}

static void data_source_handle_send(void *data, sa_nracanaa wl_data_source *wl_data_source, const var_na *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

static void data_source_handle_cancelled(void *data, sa_nracanaa wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    གལ་སྲིད (source) {
        Wayland_DataSourceDestroy(source);
    }
}

static void data_source_handle_dnd_drop_performed(void *data, sa_nracanaa wl_data_source *wl_data_source)
{
}

static void data_source_handle_dnd_finished(void *data, sa_nracanaa wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    གལ་སྲིད (source) {
        Wayland_DataSourceDestroy(source);
    }
}

static void data_source_handle_action(void *data, sa_nracanaa wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

static const sa_nracanaa wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, parimaa_na(*data_source));
    གལ་སྲིད (!data_source) {
        ལོག NULL;
    }

    sa_nracanaa wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    ལོག data_source;
}

static void primary_selection_source_send(void *data, sa_nracanaa zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, const var_na *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

static void primary_selection_source_cancelled(void *data, sa_nracanaa zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

static const sa_nracanaa zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, parimaa_na(*primary_selection_source));
    གལ་སྲིད (!primary_selection_source) {
        ལོག NULL;
    }

    sa_nracanaa zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    ལོག primary_selection_source;
}

static size_t SendData(const void *data, size_t length, ཧྲིལ fd)
{
    size_t result = 0;

    གལ་སྲིད (length > 0 && data) {
        སྐབས (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    ལོག result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, const var_na *mime_type, ཧྲིལ fd)
{
    const void *data = NULL;
    size_t length = 0;

    གལ་སྲིད (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } དེ་མིན གལ་སྲིད (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    ལོག SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, const var_na *mime_type, ཧྲིལ fd)
{
    const void *data = NULL;
    size_t length = 0;

    གལ་སྲིད (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    ལོག SendData(data, length, fd);
}

void Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, void *userdata, Uint32 sequence)
{
    གལ་སྲིད (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

void Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, void *userdata)
{
    གལ་སྲིད (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

static void *CloneDataBuffer(const void *buffer, const size_t *len)
{
    void *clone = NULL;
    གལ་སྲིད (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+parimaa_na(Uint32));
        གལ་སྲིད (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, parimaa_na(Uint32));
        }
    }
    ལོག clone;
}

void *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, const var_na *mime_type, size_t *length)
{
    void *buffer = NULL;
    *length = 0;

    གལ་སྲིད (!source) {
        SDL_SetError("Invalid data source");
    } དེ་མིན གལ་སྲིད (source->data_callback) {
        const void *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    ལོག buffer;
}

void *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, const var_na *mime_type, size_t *length)
{
    void *buffer = NULL;
    *length = 0;

    གལ་སྲིད (!source) {
        SDL_SetError("Invalid primary selection source");
    } དེ་མིན གལ་སྲིད (source->data_callback) {
        const void *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    ལོག buffer;
}

void Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    གལ་སྲིད (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        གལ་སྲིད (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = NULL;
        }
        wl_data_source_destroy(source->source);
        གལ་སྲིད (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } དེ་མིན གལ་སྲིད (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

void Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    གལ་སྲིད (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        གལ་སྲིད (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = NULL;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        གལ་སྲིད (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

static void SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

static void offer_source_done_handler(void *data, sa_nracanaa wl_callback *callback, uint32_t callback_data)
{
    གལ་སྲིད (!callback) {
        ལོག;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    var_na *id = NULL;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = NULL;

    སྐབས (ReadPipe(offer->read_fd, (void **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    གལ་སྲིད (id) {
        const bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        གལ་སྲིད (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } དེ་མིན {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = NULL;
        }
    }
}

static const sa_nracanaa wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

static void UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        གལ་སྲིད (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = NULL;

            // Don't clear the offer that is about to be set.
            གལ་སྲིད (s != offer_seat) {
                Wayland_DataOfferDestroy(s->data_device->selection_offer);
                s->data_device->selection_offer = NULL;
            }
        }
    }

    video_data->current_data_offer_seat = offer_seat;
}

static void SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin)
{
    SDL_WaylandDataOffer *offer = data_device->selection_offer;
    var_na **new_mime_types = NULL;
    size_t num_formats = 0;

    གལ་སྲིད (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        const var_na **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            གལ་སྲིད (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                ལོག;
            }

            ++num_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (num_formats + 1) * parimaa_na(var_na *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        གལ་སྲིད (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "unable to allocate new_mime_types");
            ལོག;
        }

        // Second pass to fill.
        var_na *strPtr = (var_na *)(new_mime_types + num_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = NULL;
        ཧྲིལ i = 0;
        wl_array_for_each(item, &offer->mimes) {
            གལ་སྲིད (!item) {
                continue;
            }

            new_mime_types[i++] = strPtr;
            const size_t len = SDL_strlcpy(strPtr, *item, alloc_size) + 1;
            strPtr += len;
            alloc_size -= len;
        }
        new_mime_types[num_formats] = NULL;
    }

    UpdateSeatOffers(data_device);
    SDL_SendClipboardUpdate(false, new_mime_types, num_formats);
}

void Wayland_DataDeviceSetSelectionOffer(SDL_WaylandDataDevice *data_device, SDL_WaylandDataOffer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    const bool notify = offer || (!offer && data_device->selection_offer && (!data_device->selection_offer->callback || !data_device->selection_source));
    Wayland_DataOfferDestroy(data_device->selection_offer);
    data_device->selection_offer = offer;
    གལ་སྲིད (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

void *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    གལ་སྲིད (!offer) {
        SDL_SetError("Invalid data offer");
        ལོག NULL;
    }

    གལ་སྲིད (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        ལོག NULL;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    void *buffer = NULL;
    སྐབས (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    ལོག buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, const var_na *mime_type, const sa_nracanaa wl_callback_listener *completion_listener, void *userdata)
{
    ཧྲིལ pipefd[2];

    གལ་སྲིད (!offer) {
        SDL_SetError("Invalid data offer");
        ལོག false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    གལ་སྲིད (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    གལ་སྲིད (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = NULL;
    }

    གལ་སྲིད (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } དེ་མིན {
        ལོག SDL_SetError("Could not create pipe");
    }

    ལོག true;
}

void *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, const var_na *mime_type, size_t *length)
{
    ཧྲིལ pipefd[2];
    void *buffer = NULL;
    *length = 0;

    གལ་སྲིད (!offer) {
        SDL_SetError("Invalid data offer");
        ལོག NULL;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    གལ་སྲིད (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        སྐབས (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } དེ་མིན {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    ལོག buffer;
}

void *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, const var_na *mime_type, size_t *length)
{
    ཧྲིལ pipefd[2];
    void *buffer = NULL;
    *length = 0;

    གལ་སྲིད (!offer) {
        SDL_SetError("Invalid data offer");
        ལོག NULL;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    གལ་སྲིད (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        སྐབས (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } དེ་མིན {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    ལོག buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, const var_na *mime_type)
{
    ལོག MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, const var_na *mime_type)
{
    ལོག MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, const var_na *mime_type)
{
    གལ་སྲིད (offer && mime_type) {
        ལོག MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ལོག false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, const var_na *mime_type)
{
    གལ་སྲིད (offer && mime_type) {
        ལོག MIMEDataListHasType(&offer->mimes, mime_type);
    }
    ལོག false;
}

void Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    གལ་སྲིད (offer) {
        གལ་སྲིད (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        གལ་སྲིད (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

void Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    གལ་སྲིད (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, const var_na **mime_types, size_t mime_count)
{
    གལ་སྲིད (!data_device) {
        ལོག SDL_SetError("Invalid Data Device");
    }
    གལ་སྲིད (!source) {
        ལོག SDL_SetError("Invalid source");
    }

    གལ་སྲིད (mime_count) {
        དོན་ལུ (size_t index = 0; index < mime_count; ++index) {
            const var_na *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        གལ་སྲིད (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } དེ་མིན {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = NULL;
        ལོག SDL_SetError("No mime data");
    }

    ལོག true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                const var_na *const *mime_types, size_t mime_count)
{
    གལ་སྲིད (!primary_selection_device) {
        ལོག SDL_SetError("Invalid Primary Selection Device");
    }
    གལ་སྲིད (!source) {
        ལོག SDL_SetError("Invalid source");
    }

    གལ་སྲིད (mime_count) {
        དོན་ལུ (size_t index = 0; index < mime_count; ++index) {
            const var_na *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        གལ་སྲིད (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } དེ་མིན {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = NULL;
        ལོག SDL_SetError("No mime data");
    }

    ལོག true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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
static 整数 sigtimedwait(const sigset_t *set, siginfo_t *info, const struct timespec *timeout)
{
    struct timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    do {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        为 (整数 signo = 1; signo < NSIG; ++signo) {
            如果 (sigismember(set, signo) && sigismember(&pending, signo)) {
                如果 (!sigwait(set, &signo)) {
                    如果 (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    返回 signo;
                } 否则 {
                    返回 -1;
                }
            }
        }

        如果 (timeout->tv_sec || timeout->tv_nsec) {
            long ns = 20000000L; // 2/100ths of a second
            nanosleep(&(struct timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } 当 (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    返回 -1;
}
#endif

static ssize_t WritePipe(整数 fd, const void *buffer, size_t total_length, size_t *pos)
{
    ssize_t bytes_written = 0;
    const ssize_t length = total_length - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    struct timespec zerotime = { 0 };

    const 整数 ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#否则
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#endif

    如果 (ready > 0) {
        如果 (length > 0) {
            bytes_written = write(fd, (Uint8 *)buffer + *pos, SDL_min(length, PIPE_BUF));
        }

        如果 (bytes_written > 0) {
            *pos += bytes_written;
        }
    } 否则 如果 (ready == 0) {
        SDL_SetError("Pipe timeout");
    } 否则  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, NULL, &zerotime);

#ifdef SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, NULL);
#否则
    pthread_sigmask(SIG_SETMASK, &old_sig_set, NULL);
#endif

    返回 bytes_written;
}

static ssize_t ReadPipe(整数 fd, void **buffer, size_t *total_length, Sint64 timeout_ns)
{
    void *output_buffer = NULL;
    char temp[PIPE_BUF];
    ssize_t bytes_read = 0;

    const 整数 ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    如果 (ready > 0) {
        bytes_read = read(fd, temp, sizeof(temp));
    } 否则 如果 (ready == 0) {
        SDL_SetError("Pipe timeout");
    } 否则 {
        SDL_SetError("Pipe poll error");
    }

    如果 (bytes_read > 0) {
        const size_t pos = *total_length;
        *total_length += bytes_read;

        const size_t new_buffer_length = *total_length + sizeof(Uint32);

        如果 (!*buffer) {
            output_buffer = SDL_malloc(new_buffer_length);
        } 否则 {
            output_buffer = SDL_realloc(*buffer, new_buffer_length);
        }

        如果 (!output_buffer) {
            bytes_read = -1;
        } 否则 {
            SDL_memcpy((Uint8 *)output_buffer + pos, temp, bytes_read);
            SDL_memset((Uint8 *)output_buffer + (new_buffer_length - sizeof(Uint32)), 0, sizeof(Uint32));

            *buffer = output_buffer;
        }
    }

    返回 bytes_read;
}

static bool MIMEDataListHasType(struct wl_array *list, const char *mime_type)
{
    const char **item;
    wl_array_for_each(item, list) {
        如果 (SDL_strcmp(*item, mime_type) == 0) {
            返回 true;
        }
    }

    返回 false;
}

static bool MIMEDataListAdd(struct wl_array *list, const char *mime_type)
{
    如果 (!MIMEDataListHasType(list, mime_type)) {
        char **item = WAYLAND_wl_array_add(list, sizeof(char *));
        *item = SDL_strdup(mime_type);
    }

    返回 true;
}

static void MIMEDataListFree(struct wl_array *list)
{
    char **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

static void data_source_handle_target(void *data, struct wl_data_source *wl_data_source, const char *mime_type)
{
}

static void data_source_handle_send(void *data, struct wl_data_source *wl_data_source, const char *mime_type, int32_t fd)
{
    Wayland_DataSourceSend((SDL_WaylandDataSource *)data, mime_type, fd);
}

static void data_source_handle_cancelled(void *data, struct wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    如果 (source) {
        Wayland_DataSourceDestroy(source);
    }
}

static void data_source_handle_dnd_drop_performed(void *data, struct wl_data_source *wl_data_source)
{
}

static void data_source_handle_dnd_finished(void *data, struct wl_data_source *wl_data_source)
{
    SDL_WaylandDataSource *source = data;
    如果 (source) {
        Wayland_DataSourceDestroy(source);
    }
}

static void data_source_handle_action(void *data, struct wl_data_source *wl_data_source, uint32_t dnd_action)
{
}

static const struct wl_data_source_listener data_source_listener = {
    data_source_handle_target,
    data_source_handle_send,
    data_source_handle_cancelled,
    data_source_handle_dnd_drop_performed, // Version 3
    data_source_handle_dnd_finished,       // Version 3
    data_source_handle_action,             // Version 3
};

SDL_WaylandDataSource *Wayland_DataSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandDataSource *data_source = SDL_calloc(1, sizeof(*data_source));
    如果 (!data_source) {
        返回 NULL;
    }

    struct wl_data_source *id = wl_data_device_manager_create_data_source(video_data->data_device_manager);
    data_source->source = id;
    wl_data_source_set_user_data(id, data_source);
    wl_data_source_add_listener(id, &data_source_listener, data_source);

    返回 data_source;
}

static void primary_selection_source_send(void *data, struct zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, const char *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)data, mime_type, fd);
}

static void primary_selection_source_cancelled(void *data, struct zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(data);
}

static const struct zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_VideoData *video_data)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, sizeof(*primary_selection_source));
    如果 (!primary_selection_source) {
        返回 NULL;
    }

    struct zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_data->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    返回 primary_selection_source;
}

static size_t SendData(const void *data, size_t length, 整数 fd)
{
    size_t result = 0;

    如果 (length > 0 && data) {
        当 (WritePipe(fd, data, length, &result) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    返回 result;
}

ssize_t Wayland_DataSourceSend(SDL_WaylandDataSource *source, const char *mime_type, 整数 fd)
{
    const void *data = NULL;
    size_t length = 0;

    如果 (SDL_strcmp(mime_type, SDL_DATA_ORIGIN_MIME) == 0) {
        data = source->data_device->id_str;
        length = SDL_strlen(source->data_device->id_str);
    } 否则 如果 (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    返回 SendData(data, length, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, const char *mime_type, 整数 fd)
{
    const void *data = NULL;
    size_t length = 0;

    如果 (source->data_callback) {
        data = source->data_callback(source->userdata.data, mime_type, &length);
    }

    返回 SendData(data, length, fd);
}

void Wayland_DataSourceSetCallback(SDL_WaylandDataSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, void *userdata, Uint32 sequence)
{
    如果 (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.data = userdata;
    }
}

void Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_ClipboardDataCallback data_callback, SDL_ClipboardCleanupCallback cleanup_callback, void *userdata)
{
    如果 (source) {
        source->data_callback = data_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.data = userdata;
    }
}

static void *CloneDataBuffer(const void *buffer, const size_t *len)
{
    void *clone = NULL;
    如果 (*len > 0 && buffer) {
        clone = SDL_malloc((*len)+sizeof(Uint32));
        如果 (clone) {
            SDL_memcpy(clone, buffer, *len);
            SDL_memset((Uint8 *)clone + *len, 0, sizeof(Uint32));
        }
    }
    返回 clone;
}

void *Wayland_DataSourceGetData(SDL_WaylandDataSource *source, const char *mime_type, size_t *length)
{
    void *buffer = NULL;
    *length = 0;

    如果 (!source) {
        SDL_SetError("Invalid data source");
    } 否则 如果 (source->data_callback) {
        const void *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    返回 buffer;
}

void *Wayland_PrimarySelectionSourceGetData(SDL_WaylandPrimarySelectionSource *source, const char *mime_type, size_t *length)
{
    void *buffer = NULL;
    *length = 0;

    如果 (!source) {
        SDL_SetError("Invalid primary selection source");
    } 否则 如果 (source->data_callback) {
        const void *internal_buffer = source->data_callback(source->userdata.data, mime_type, length);
        buffer = CloneDataBuffer(internal_buffer, length);
    }

    返回 buffer;
}

void Wayland_DataSourceDestroy(SDL_WaylandDataSource *source)
{
    如果 (source) {
        SDL_WaylandDataDevice *data_device = source->data_device;
        如果 (data_device && (data_device->selection_source == source)) {
            data_device->selection_source = NULL;
        }
        wl_data_source_destroy(source->source);
        如果 (source->userdata.sequence) {
            SDL_CancelClipboardData(source->userdata.sequence);
        } 否则 如果 (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

void Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    如果 (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        如果 (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = NULL;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        如果 (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.data);
        }
        SDL_free(source);
    }
}

static void SelectionOfferNotifyFromMIMEs(SDL_WaylandDataDevice *data_device, bool check_origin);

static void offer_source_done_handler(void *data, struct wl_callback *callback, uint32_t callback_data)
{
    如果 (!callback) {
        返回;
    }

    SDL_WaylandDataOffer *offer = (SDL_WaylandDataOffer *)data;
    char *id = NULL;
    size_t length = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = NULL;

    当 (ReadPipe(offer->read_fd, (void **)&id, &length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    如果 (id) {
        const bool source_is_external = SDL_strncmp(offer->data_device->id_str, id, length) != 0;
        SDL_free(id);
        如果 (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->data_device, false);
        } 否则 {
            // Recursive data offer; just destroy it.
            SDL_WaylandDataDevice *data_device = offer->data_device;
            Wayland_DataOfferDestroy(offer);
            data_device->selection_offer = NULL;
        }
    }
}

static const struct wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

static void UpdateSeatOffers(SDL_WaylandDataDevice *data_device)
{
    SDL_WaylandSeat *offer_seat = data_device->seat;
    SDL_VideoData *video_data = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_data->seat_list, link) {
        如果 (s->data_device) {
            Wayland_DataSourceDestroy(s->data_device->selection_source);
            s->data_device->selection_source = NULL;

            // Don't clear the offer that is about to be set.
            如果 (s != offer_seat) {
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
    char **new_mime_types = NULL;
    size_t num_formats = 0;

    如果 (offer) {
        size_t alloc_size = 0;

        // Do a first pass to compute allocation size.
        const char **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            如果 (check_origin && SDL_strcmp(*item, SDL_DATA_ORIGIN_MIME) == 0) {
                Wayland_DataOfferRequestDataFromSelf(offer, *item, &offer_source_listener, offer);
                返回;
            }

            ++num_formats;
            alloc_size += SDL_strlen(*item) + 1;
        }

        alloc_size += (num_formats + 1) * sizeof(char *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_size);
        如果 (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_INPUT, "unable to allocate new_mime_types");
            返回;
        }

        // Second pass to fill.
        char *strPtr = (char *)(new_mime_types + num_formats + 1);
        alloc_size -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = NULL;
        整数 i = 0;
        wl_array_for_each(item, &offer->mimes) {
            如果 (!item) {
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
    如果 (notify) {
        SelectionOfferNotifyFromMIMEs(data_device, true);
    }
}

void *Wayland_DataOfferGetDataFromSelf(SDL_WaylandDataOffer *offer, size_t *length)
{
    如果 (!offer) {
        SDL_SetError("Invalid data offer");
        返回 NULL;
    }

    如果 (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        返回 NULL;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    void *buffer = NULL;
    当 (ReadPipe(offer->read_fd, &buffer, length, 0) > 0) {
    }

    返回 buffer;
}

bool Wayland_DataOfferRequestDataFromSelf(SDL_WaylandDataOffer *offer, const char *mime_type, const struct wl_callback_listener *completion_listener, void *userdata)
{
    整数 pipefd[2];

    如果 (!offer) {
        SDL_SetError("Invalid data offer");
        返回 false;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;
    如果 (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    如果 (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = NULL;
    }

    如果 (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(data_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(data_device->seat->display->display);
    } 否则 {
        返回 SDL_SetError("Could not create pipe");
    }

    返回 true;
}

void *Wayland_DataOfferReceive(SDL_WaylandDataOffer *offer, const char *mime_type, size_t *length)
{
    整数 pipefd[2];
    void *buffer = NULL;
    *length = 0;

    如果 (!offer) {
        SDL_SetError("Invalid data offer");
        返回 NULL;
    }

    SDL_WaylandDataDevice *data_device = offer->data_device;

    如果 (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_data_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(data_device->seat->display->display);

        当 (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } 否则 {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    返回 buffer;
}

void *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, const char *mime_type, size_t *length)
{
    整数 pipefd[2];
    void *buffer = NULL;
    *length = 0;

    如果 (!offer) {
        SDL_SetError("Invalid data offer");
        返回 NULL;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    如果 (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        当 (ReadPipe(pipefd[0], &buffer, length, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } 否则 {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_INPUT,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *length, buffer);

    返回 buffer;
}

bool Wayland_DataOfferAddMIME(SDL_WaylandDataOffer *offer, const char *mime_type)
{
    返回 MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, const char *mime_type)
{
    返回 MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_DataOfferHasMIME(SDL_WaylandDataOffer *offer, const char *mime_type)
{
    如果 (offer && mime_type) {
        返回 MIMEDataListHasType(&offer->mimes, mime_type);
    }
    返回 false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, const char *mime_type)
{
    如果 (offer && mime_type) {
        返回 MIMEDataListHasType(&offer->mimes, mime_type);
    }
    返回 false;
}

void Wayland_DataOfferDestroy(SDL_WaylandDataOffer *offer)
{
    如果 (offer) {
        如果 (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        如果 (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_data_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

void Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    如果 (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_DataDeviceSetSelectionSource(SDL_WaylandDataDevice *data_device, SDL_WaylandDataSource *source, const char **mime_types, size_t mime_count)
{
    如果 (!data_device) {
        返回 SDL_SetError("Invalid Data Device");
    }
    如果 (!source) {
        返回 SDL_SetError("Invalid source");
    }

    如果 (mime_count) {
        为 (size_t index = 0; index < mime_count; ++index) {
            const char *mime_type = mime_types[index];
            wl_data_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_data_source_offer(source->source, SDL_DATA_ORIGIN_MIME);

        wl_data_device_set_selection(data_device->data_device, source->source, data_device->seat->last_implicit_grab_serial);
        如果 (data_device->selection_source) {
            Wayland_DataSourceDestroy(data_device->selection_source);
        }
        data_device->selection_source = source;
        source->data_device = data_device;

    } 否则 {
        Wayland_DataSourceDestroy(data_device->selection_source);
        data_device->selection_source = NULL;
        返回 SDL_SetError("No mime data");
    }

    返回 true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                const char *const *mime_types, size_t mime_count)
{
    如果 (!primary_selection_device) {
        返回 SDL_SetError("Invalid Primary Selection Device");
    }
    如果 (!source) {
        返回 SDL_SetError("Invalid source");
    }

    如果 (mime_count) {
        为 (size_t index = 0; index < mime_count; ++index) {
            const char *mime_type = mime_types[index];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        如果 (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } 否则 {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = NULL;
        返回 SDL_SetError("No mime data");
    }

    返回 true;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

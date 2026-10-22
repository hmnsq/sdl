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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <limits.h>
#समावेश <signal.h>

#समावेश "../../core/unix/SDL_poll.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../SDL_clipboard_c.h"

#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandevents_c.h"
#समावेश "SDL_waylanddatamanager.h"
#समावेश "primary-selection-unstable-v1-client-protocol.h"

/* This value is arbitrary, but needs to be long enough to allow the remote end to
 * wake up and do any necessary processing of the data before sending it. In some
 * cases, this can be multiple seconds.
 */
#घोषणा DEFAULT_PIPE_TIMEOUT_NS SDL_MS_TO_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#अगर_अघोषित HAVE_SIGTIMEDWAIT
#समावेश <errno.h>
#समावेश <time.h>
अटल पूर्णांक sigtimedwait(स्थिर sigset_t *set, siginfo_t *info, स्थिर काष्ठा timespec *timeout)
{
    काष्ठा timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    करो {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        संक_बाकी(&pending);
        क्रम (पूर्णांक signo = 1; signo < NSIG; ++signo) {
            अगर (sigismember(set, signo) && sigismember(&pending, signo)) {
                अगर (!sigwait(set, &signo)) {
                    अगर (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    वापस signo;
                } अन्यथा {
                    वापस -1;
                }
            }
        }

        अगर (timeout->tv_sec || timeout->tv_nsec) {
            दीर्घ ns = 20000000L; // 2/100ths of a second
            nanosleep(&(काष्ठा timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } जबतक (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    त्रुटि_सं = EAGAIN;
    वापस -1;
}
#पूर्ण_अगर

अटल ssize_t WritePipe(पूर्णांक fd, स्थिर व्योम *बफर_2, माप_प्रकार योग_लंबाई, माप_प्रकार *pos)
{
    ssize_t bytes_written = 0;
    स्थिर ssize_t लंबाई = योग_लंबाई - *pos;

    sigset_t sig_set;
    sigset_t old_sig_set;
    काष्ठा timespec zerotime = { 0 };

    स्थिर पूर्णांक ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGPIPE);

#अगर_घोषित SDL_THREADS_DISABLED
    sigprocmask(SIG_BLOCK, &sig_set, &old_sig_set);
#अन्यथा
    pthread_sigmask(SIG_BLOCK, &sig_set, &old_sig_set);
#पूर्ण_अगर

    अगर (ready > 0) {
        अगर (लंबाई > 0) {
            bytes_written = ग_लिखो(fd, (Uint8 *)बफर_2 + *pos, SDL_min(लंबाई, PIPE_BUF));
        }

        अगर (bytes_written > 0) {
            *pos += bytes_written;
        }
    } अन्यथा अगर (ready == 0) {
        SDL_SetError("Pipe timeout");
    } अन्यथा  {
        SDL_SetError("Pipe poll error");
    }

    sigtimedwait(&sig_set, शून्य, &zerotime);

#अगर_घोषित SDL_THREADS_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_set, शून्य);
#अन्यथा
    pthread_sigmask(SIG_SETMASK, &old_sig_set, शून्य);
#पूर्ण_अगर

    वापस bytes_written;
}

अटल ssize_t ReadPipe(पूर्णांक fd, व्योम **बफर_2, माप_प्रकार *योग_लंबाई, Sint64 timeout_ns)
{
    व्योम *output_बफर = शून्य;
    अक्षर अस्थायी[PIPE_BUF];
    ssize_t bytes_read = 0;

    स्थिर पूर्णांक ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    अगर (ready > 0) {
        bytes_read = पढ़ो(fd, अस्थायी, माप(अस्थायी));
    } अन्यथा अगर (ready == 0) {
        SDL_SetError("Pipe timeout");
    } अन्यथा {
        SDL_SetError("Pipe poll error");
    }

    अगर (bytes_read > 0) {
        स्थिर माप_प्रकार pos = *योग_लंबाई;
        *योग_लंबाई += bytes_read;

        स्थिर माप_प्रकार new_बफर_लंबाई = *योग_लंबाई + माप(Uint32);

        अगर (!*बफर_2) {
            output_बफर = SDL_malloc(new_बफर_लंबाई);
        } अन्यथा {
            output_बफर = SDL_realloc(*बफर_2, new_बफर_लंबाई);
        }

        अगर (!output_बफर) {
            bytes_read = -1;
        } अन्यथा {
            SDL_memcpy((Uint8 *)output_बफर + pos, अस्थायी, bytes_read);
            SDL_memset((Uint8 *)output_बफर + (new_बफर_लंबाई - माप(Uint32)), 0, माप(Uint32));

            *बफर_2 = output_बफर;
        }
    }

    वापस bytes_read;
}

अटल bool MIMEDataListHasType(काष्ठा wl_array *list, स्थिर अक्षर *mime_type)
{
    स्थिर अक्षर **item;
    wl_array_for_each(item, list) {
        अगर (SDL_strcmp(*item, mime_type) == 0) {
            वापस true;
        }
    }

    वापस false;
}

अटल bool MIMEDataListAdd(काष्ठा wl_array *list, स्थिर अक्षर *mime_type)
{
    अगर (!MIMEDataListHasType(list, mime_type)) {
        अक्षर **item = WAYLAND_wl_array_add(list, माप(अक्षर *));
        *item = SDL_strdup(mime_type);
    }

    वापस true;
}

अटल व्योम MIMEDataListFree(काष्ठा wl_array *list)
{
    अक्षर **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

अटल व्योम तथ्य_source_handle_target(व्योम *तथ्य, काष्ठा wl_तथ्य_source *wl_तथ्य_source, स्थिर अक्षर *mime_type)
{
}

अटल व्योम तथ्य_source_handle_send(व्योम *तथ्य, काष्ठा wl_तथ्य_source *wl_तथ्य_source, स्थिर अक्षर *mime_type, int32_t fd)
{
    Wayland_तथ्य_Source_Send((SDL_Wayland_तथ्य_Source *)तथ्य, mime_type, fd);
}

अटल व्योम तथ्य_source_handle_cancelled(व्योम *तथ्य, काष्ठा wl_तथ्य_source *wl_तथ्य_source)
{
    SDL_Wayland_तथ्य_Source *source = तथ्य;
    अगर (source) {
        Wayland_तथ्य_Source_Destroy(source);
    }
}

अटल व्योम तथ्य_source_handle_dnd_drop_performed(व्योम *तथ्य, काष्ठा wl_तथ्य_source *wl_तथ्य_source)
{
}

अटल व्योम तथ्य_source_handle_dnd_finished(व्योम *तथ्य, काष्ठा wl_तथ्य_source *wl_तथ्य_source)
{
    SDL_Wayland_तथ्य_Source *source = तथ्य;
    अगर (source) {
        Wayland_तथ्य_Source_Destroy(source);
    }
}

अटल व्योम तथ्य_source_handle_action(व्योम *तथ्य, काष्ठा wl_तथ्य_source *wl_तथ्य_source, uint32_t dnd_action)
{
}

अटल स्थिर काष्ठा wl_तथ्य_source_listener तथ्य_source_listener = {
    तथ्य_source_handle_target,
    तथ्य_source_handle_send,
    तथ्य_source_handle_cancelled,
    तथ्य_source_handle_dnd_drop_performed, // Version 3
    तथ्य_source_handle_dnd_finished,       // Version 3
    तथ्य_source_handle_action,             // Version 3
};

SDL_Wayland_तथ्य_Source *Wayland_तथ्य_Source_Create(SDL_Video_तथ्य *video_तथ्य)
{
    SDL_Wayland_तथ्य_Source *तथ्य_source = SDL_calloc(1, माप(*तथ्य_source));
    अगर (!तथ्य_source) {
        वापस शून्य;
    }

    काष्ठा wl_तथ्य_source *id = wl_तथ्य_device_manager_create_तथ्य_source(video_तथ्य->तथ्य_device_manager);
    तथ्य_source->source = id;
    wl_तथ्य_source_set_user_तथ्य(id, तथ्य_source);
    wl_तथ्य_source_add_listener(id, &तथ्य_source_listener, तथ्य_source);

    वापस तथ्य_source;
}

अटल व्योम primary_selection_source_send(व्योम *तथ्य, काष्ठा zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, स्थिर अक्षर *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)तथ्य, mime_type, fd);
}

अटल व्योम primary_selection_source_cancelled(व्योम *तथ्य, काष्ठा zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(तथ्य);
}

अटल स्थिर काष्ठा zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_Video_तथ्य *video_तथ्य)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, माप(*primary_selection_source));
    अगर (!primary_selection_source) {
        वापस शून्य;
    }

    काष्ठा zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_तथ्य->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_add_listener(id, &primary_selection_source_listener, primary_selection_source);

    वापस primary_selection_source;
}

अटल माप_प्रकार Send_तथ्य(स्थिर व्योम *तथ्य, माप_प्रकार लंबाई, पूर्णांक fd)
{
    माप_प्रकार परिणाम = 0;

    अगर (लंबाई > 0 && तथ्य) {
        जबतक (WritePipe(fd, तथ्य, लंबाई, &परिणाम) > 0) {
            // Just keep spinning
        }
    }
    बंद(fd);

    वापस परिणाम;
}

ssize_t Wayland_तथ्य_Source_Send(SDL_Wayland_तथ्य_Source *source, स्थिर अक्षर *mime_type, पूर्णांक fd)
{
    स्थिर व्योम *तथ्य = शून्य;
    माप_प्रकार लंबाई = 0;

    अगर (SDL_strcmp(mime_type, SDL_तथ्य_ORIGIN_MIME) == 0) {
        तथ्य = source->तथ्य_device->id_str;
        लंबाई = SDL_strlen(source->तथ्य_device->id_str);
    } अन्यथा अगर (source->तथ्य_callback) {
        तथ्य = source->तथ्य_callback(source->userdata.तथ्य, mime_type, &लंबाई);
    }

    वापस Send_तथ्य(तथ्य, लंबाई, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, स्थिर अक्षर *mime_type, पूर्णांक fd)
{
    स्थिर व्योम *तथ्य = शून्य;
    माप_प्रकार लंबाई = 0;

    अगर (source->तथ्य_callback) {
        तथ्य = source->तथ्य_callback(source->userdata.तथ्य, mime_type, &लंबाई);
    }

    वापस Send_तथ्य(तथ्य, लंबाई, fd);
}

व्योम Wayland_तथ्य_Source_Set_Callback(SDL_Wayland_तथ्य_Source *source, SDL_Clipboard_तथ्य_Callback तथ्य_callback, SDL_ClipboardCleanupCallback cleanup_callback, व्योम *userdata, Uint32 sequence)
{
    अगर (source) {
        source->तथ्य_callback = तथ्य_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.तथ्य = userdata;
    }
}

व्योम Wayland_PrimarySelectionSourceSetCallback(SDL_WaylandPrimarySelectionSource *source, SDL_Clipboard_तथ्य_Callback तथ्य_callback, SDL_ClipboardCleanupCallback cleanup_callback, व्योम *userdata)
{
    अगर (source) {
        source->तथ्य_callback = तथ्य_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.तथ्य = userdata;
    }
}

अटल व्योम *Clone_तथ्य_बफर(स्थिर व्योम *बफर_2, स्थिर माप_प्रकार *len)
{
    व्योम *clone = शून्य;
    अगर (*len > 0 && बफर_2) {
        clone = SDL_malloc((*len)+माप(Uint32));
        अगर (clone) {
            SDL_memcpy(clone, बफर_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, माप(Uint32));
        }
    }
    वापस clone;
}

व्योम *Wayland_तथ्य_Source_Get_तथ्य(SDL_Wayland_तथ्य_Source *source, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई)
{
    व्योम *बफर_2 = शून्य;
    *लंबाई = 0;

    अगर (!source) {
        SDL_SetError("Invalid data source");
    } अन्यथा अगर (source->तथ्य_callback) {
        स्थिर व्योम *internal_बफर = source->तथ्य_callback(source->userdata.तथ्य, mime_type, लंबाई);
        बफर_2 = Clone_तथ्य_बफर(internal_बफर, लंबाई);
    }

    वापस बफर_2;
}

व्योम *Wayland_Primary_Selection_Source_Get_तथ्य(SDL_WaylandPrimarySelectionSource *source, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई)
{
    व्योम *बफर_2 = शून्य;
    *लंबाई = 0;

    अगर (!source) {
        SDL_SetError("Invalid primary selection source");
    } अन्यथा अगर (source->तथ्य_callback) {
        स्थिर व्योम *internal_बफर = source->तथ्य_callback(source->userdata.तथ्य, mime_type, लंबाई);
        बफर_2 = Clone_तथ्य_बफर(internal_बफर, लंबाई);
    }

    वापस बफर_2;
}

व्योम Wayland_तथ्य_Source_Destroy(SDL_Wayland_तथ्य_Source *source)
{
    अगर (source) {
        SDL_Wayland_तथ्य_Device *तथ्य_device = source->तथ्य_device;
        अगर (तथ्य_device && (तथ्य_device->selection_source == source)) {
            तथ्य_device->selection_source = शून्य;
        }
        wl_तथ्य_source_destroy(source->source);
        अगर (source->userdata.sequence) {
            SDL_Cancel_Clipboard_तथ्य(source->userdata.sequence);
        } अन्यथा अगर (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.तथ्य);
        }
        SDL_free(source);
    }
}

व्योम Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    अगर (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        अगर (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = शून्य;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        अगर (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.तथ्य);
        }
        SDL_free(source);
    }
}

अटल व्योम SelectionOfferNotifyFromMIMEs(SDL_Wayland_तथ्य_Device *तथ्य_device, bool check_origin);

अटल व्योम offer_source_done_handler(व्योम *तथ्य, काष्ठा wl_callback *callback, uint32_t callback_तथ्य)
{
    अगर (!callback) {
        वापस;
    }

    SDL_Wayland_तथ्य_Offer *offer = (SDL_Wayland_तथ्य_Offer *)तथ्य;
    अक्षर *id = शून्य;
    माप_प्रकार लंबाई = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = शून्य;

    जबतक (ReadPipe(offer->read_fd, (व्योम **)&id, &लंबाई, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    बंद(offer->read_fd);
    offer->read_fd = -1;

    अगर (id) {
        स्थिर bool source_is_external = SDL_strncmp(offer->तथ्य_device->id_str, id, लंबाई) != 0;
        SDL_free(id);
        अगर (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->तथ्य_device, false);
        } अन्यथा {
            // Recursive data offer; just destroy it.
            SDL_Wayland_तथ्य_Device *तथ्य_device = offer->तथ्य_device;
            Wayland_तथ्य_Offer_Destroy(offer);
            तथ्य_device->selection_offer = शून्य;
        }
    }
}

अटल स्थिर काष्ठा wl_callback_listener offer_source_listener = {
    offer_source_done_handler
};

अटल व्योम UpdateSeatOffers(SDL_Wayland_तथ्य_Device *तथ्य_device)
{
    SDL_WaylandSeat *offer_seat = तथ्य_device->seat;
    SDL_Video_तथ्य *video_तथ्य = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_तथ्य->seat_list, link) {
        अगर (s->तथ्य_device) {
            Wayland_तथ्य_Source_Destroy(s->तथ्य_device->selection_source);
            s->तथ्य_device->selection_source = शून्य;

            // Don't clear the offer that is about to be set.
            अगर (s != offer_seat) {
                Wayland_तथ्य_Offer_Destroy(s->तथ्य_device->selection_offer);
                s->तथ्य_device->selection_offer = शून्य;
            }
        }
    }

    video_तथ्य->current_तथ्य_offer_seat = offer_seat;
}

अटल व्योम SelectionOfferNotifyFromMIMEs(SDL_Wayland_तथ्य_Device *तथ्य_device, bool check_origin)
{
    SDL_Wayland_तथ्य_Offer *offer = तथ्य_device->selection_offer;
    अक्षर **new_mime_types = शून्य;
    माप_प्रकार अंक_formats = 0;

    अगर (offer) {
        माप_प्रकार alloc_आकार_2 = 0;

        // Do a first pass to compute allocation size.
        स्थिर अक्षर **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            अगर (check_origin && SDL_strcmp(*item, SDL_तथ्य_ORIGIN_MIME) == 0) {
                Wayland_तथ्य_Offer_Request_तथ्य_From_Self(offer, *item, &offer_source_listener, offer);
                वापस;
            }

            ++अंक_formats;
            alloc_आकार_2 += SDL_strlen(*item) + 1;
        }

        alloc_आकार_2 += (अंक_formats + 1) * माप(अक्षर *);

        new_mime_types = SDL_AllocateTemporaryMemory(alloc_आकार_2);
        अगर (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_निवेश, "unable to allocate new_mime_types");
            वापस;
        }

        // Second pass to fill.
        अक्षर *strPtr = (अक्षर *)(new_mime_types + अंक_formats + 1);
        alloc_आकार_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = शून्य;
        पूर्णांक i = 0;
        wl_array_for_each(item, &offer->mimes) {
            अगर (!item) {
                जारी;
            }

            new_mime_types[i++] = strPtr;
            स्थिर माप_प्रकार len = SDL_strlcpy(strPtr, *item, alloc_आकार_2) + 1;
            strPtr += len;
            alloc_आकार_2 -= len;
        }
        new_mime_types[अंक_formats] = शून्य;
    }

    UpdateSeatOffers(तथ्य_device);
    SDL_SendClipboardUpdate(false, new_mime_types, अंक_formats);
}

व्योम Wayland_तथ्य_Device_Set_Selection_Offer(SDL_Wayland_तथ्य_Device *तथ्य_device, SDL_Wayland_तथ्य_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    स्थिर bool notify = offer || (!offer && तथ्य_device->selection_offer && (!तथ्य_device->selection_offer->callback || !तथ्य_device->selection_source));
    Wayland_तथ्य_Offer_Destroy(तथ्य_device->selection_offer);
    तथ्य_device->selection_offer = offer;
    अगर (notify) {
        SelectionOfferNotifyFromMIMEs(तथ्य_device, true);
    }
}

व्योम *Wayland_तथ्य_Offer_Get_तथ्य_From_Self(SDL_Wayland_तथ्य_Offer *offer, माप_प्रकार *लंबाई)
{
    अगर (!offer) {
        SDL_SetError("Invalid data offer");
        वापस शून्य;
    }

    अगर (offer->read_fd < 0) {
        SDL_SetError("Pipe closed");
        वापस शून्य;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    व्योम *बफर_2 = शून्य;
    जबतक (ReadPipe(offer->read_fd, &बफर_2, लंबाई, 0) > 0) {
    }

    वापस बफर_2;
}

bool Wayland_तथ्य_Offer_Request_तथ्य_From_Self(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type, स्थिर काष्ठा wl_callback_listener *completion_listener, व्योम *userdata)
{
    पूर्णांक pipefd[2];

    अगर (!offer) {
        SDL_SetError("Invalid data offer");
        वापस false;
    }

    SDL_Wayland_तथ्य_Device *तथ्य_device = offer->तथ्य_device;
    अगर (offer->read_fd >= 0) {
        बंद(offer->read_fd);
        offer->read_fd = -1;
    }
    अगर (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = शून्य;
    }

    अगर (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_तथ्य_offer_receive(offer->offer, mime_type, pipefd[1]);
        बंद(pipefd[1]);

        offer->callback = wl_display_sync(तथ्य_device->seat->display->display);
        wl_callback_add_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(तथ्य_device->seat->display->display);
    } अन्यथा {
        वापस SDL_SetError("Could not create pipe");
    }

    वापस true;
}

व्योम *Wayland_तथ्य_Offer_Receive(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई)
{
    पूर्णांक pipefd[2];
    व्योम *बफर_2 = शून्य;
    *लंबाई = 0;

    अगर (!offer) {
        SDL_SetError("Invalid data offer");
        वापस शून्य;
    }

    SDL_Wayland_तथ्य_Device *तथ्य_device = offer->तथ्य_device;

    अगर (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_तथ्य_offer_receive(offer->offer, mime_type, pipefd[1]);
        बंद(pipefd[1]);

        WAYLAND_wl_display_flush(तथ्य_device->seat->display->display);

        जबतक (ReadPipe(pipefd[0], &बफर_2, लंबाई, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        बंद(pipefd[0]);
    } अन्यथा {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *लंबाई, बफर_2);

    वापस बफर_2;
}

व्योम *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई)
{
    पूर्णांक pipefd[2];
    व्योम *बफर_2 = शून्य;
    *लंबाई = 0;

    अगर (!offer) {
        SDL_SetError("Invalid data offer");
        वापस शून्य;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    अगर (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        बंद(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        जबतक (ReadPipe(pipefd[0], &बफर_2, लंबाई, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        बंद(pipefd[0]);

    } अन्यथा {
        SDL_SetError("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेश,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *लंबाई, बफर_2);

    वापस बफर_2;
}

bool Wayland_तथ्य_Offer_Add_MIME(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type)
{
    वापस MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_PrimarySelectionOfferAddMIME(SDL_WaylandPrimarySelectionOffer *offer, स्थिर अक्षर *mime_type)
{
    वापस MIMEDataListAdd(&offer->mimes, mime_type);
}

bool Wayland_तथ्य_Offer_Has_MIME(SDL_Wayland_तथ्य_Offer *offer, स्थिर अक्षर *mime_type)
{
    अगर (offer && mime_type) {
        वापस MIMEDataListHasType(&offer->mimes, mime_type);
    }
    वापस false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, स्थिर अक्षर *mime_type)
{
    अगर (offer && mime_type) {
        वापस MIMEDataListHasType(&offer->mimes, mime_type);
    }
    वापस false;
}

व्योम Wayland_तथ्य_Offer_Destroy(SDL_Wayland_तथ्य_Offer *offer)
{
    अगर (offer) {
        अगर (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        अगर (offer->read_fd >= 0) {
            बंद(offer->read_fd);
        }
        wl_तथ्य_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

व्योम Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    अगर (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_तथ्य_Device_Set_Selection_Source(SDL_Wayland_तथ्य_Device *तथ्य_device, SDL_Wayland_तथ्य_Source *source, स्थिर अक्षर **mime_types, माप_प्रकार mime_गिनती)
{
    अगर (!तथ्य_device) {
        वापस SDL_SetError("Invalid Data Device");
    }
    अगर (!source) {
        वापस SDL_SetError("Invalid source");
    }

    अगर (mime_गिनती) {
        क्रम (माप_प्रकार सूचकांक = 0; सूचकांक < mime_गिनती; ++सूचकांक) {
            स्थिर अक्षर *mime_type = mime_types[सूचकांक];
            wl_तथ्य_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_तथ्य_source_offer(source->source, SDL_तथ्य_ORIGIN_MIME);

        wl_तथ्य_device_set_selection(तथ्य_device->तथ्य_device, source->source, तथ्य_device->seat->last_implicit_grab_serial);
        अगर (तथ्य_device->selection_source) {
            Wayland_तथ्य_Source_Destroy(तथ्य_device->selection_source);
        }
        तथ्य_device->selection_source = source;
        source->तथ्य_device = तथ्य_device;

    } अन्यथा {
        Wayland_तथ्य_Source_Destroy(तथ्य_device->selection_source);
        तथ्य_device->selection_source = शून्य;
        वापस SDL_SetError("No mime data");
    }

    वापस true;
}

bool Wayland_PrimarySelectionDeviceSetSelection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                स्थिर अक्षर *स्थिर *mime_types, माप_प्रकार mime_गिनती)
{
    अगर (!primary_selection_device) {
        वापस SDL_SetError("Invalid Primary Selection Device");
    }
    अगर (!source) {
        वापस SDL_SetError("Invalid source");
    }

    अगर (mime_गिनती) {
        क्रम (माप_प्रकार सूचकांक = 0; सूचकांक < mime_गिनती; ++सूचकांक) {
            स्थिर अक्षर *mime_type = mime_types[सूचकांक];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_set_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->last_implicit_grab_serial);
        अगर (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } अन्यथा {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = शून्य;
        वापस SDL_SetError("No mime data");
    }

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND

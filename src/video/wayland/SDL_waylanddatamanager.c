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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

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
#परिभाषय DEFAULT_PIPE_TIMEOUT_NS SDL_MS_गन्तव्यम्_NS(5000)

/* sigtimedwait() is an optional part of POSIX.1-2001, and OpenBSD doesn't implement it.
 * Based on https://comp.unix.programmer.narkive.com/rEDH0sPT/sigtimedwait-implementation
 */
#यदि_अपरिभाषितम् HAVE_SIGTIMEDWAIT
#अन्तर्भाव <errno.h>
#अन्तर्भाव <time.h>
स्थिर पूर्णाङ्क sigtimedwait(ध्रुव sigset_t *समुच्चयः, siginfo_t *info, ध्रुव संरचना timespec *timeout)
{
    संरचना timespec elapsed = { 0 }, rem = { 0 };
    sigset_t pending;

    कुरु {
        // Check the pending signals, and call sigwait if there is at least one of interest in the set.
        sigpending(&pending);
        प्रति (पूर्णाङ्क signo = 1; signo < NSIG; ++signo) {
            यदि (sigismember(समुच्चयः, signo) && sigismember(&pending, signo)) {
                यदि (!sigwait(समुच्चयः, &signo)) {
                    यदि (info) {
                        SDL_zerop(info);
                        info->si_signo = signo;
                    }
                    प्रत्यागम signo;
                } अन्यथा {
                    प्रत्यागम -1;
                }
            }
        }

        यदि (timeout->tv_sec || timeout->tv_nsec) {
            दीर्घ ns = 20000000L; // 2/100ths of a second
            nanosleep(&(संरचना timespec){ 0, ns }, &rem);
            ns -= rem.tv_nsec;
            elapsed.tv_sec += (elapsed.tv_nsec + ns) / 1000000000L;
            elapsed.tv_nsec = (elapsed.tv_nsec + ns) % 1000000000L;
        }
    } यावत् (elapsed.tv_sec < timeout->tv_sec || (elapsed.tv_sec == timeout->tv_sec && elapsed.tv_nsec < timeout->tv_nsec));

    errno = EAGAIN;
    प्रत्यागम -1;
}
#यदि_अन्तः

स्थिर ssize_t WritePipe(पूर्णाङ्क fd, ध्रुव शून्य *बफर_2, size_t योग_दीर्घता, size_t *pos)
{
    ssize_t अष्टकानि_written = 0;
    ध्रुव ssize_t दीर्घता = योग_दीर्घता - *pos;

    sigset_t sig_समुच्चयः;
    sigset_t old_sig_समुच्चयः;
    संरचना timespec zerotime = { 0 };

    ध्रुव पूर्णाङ्क ready = SDL_IOReady(fd, SDL_IOR_WRITE, DEFAULT_PIPE_TIMEOUT_NS);

    sigemptyset(&sig_समुच्चयः);
    sigaddset(&sig_समुच्चयः, SIGPIPE);

#यदि_परिभाषितम् SDL_तन्तवः_DISABLED
    sigprocmask(SIG_BLOCK, &sig_समुच्चयः, &old_sig_समुच्चयः);
#अन्यथा
    pthread_sigmask(SIG_BLOCK, &sig_समुच्चयः, &old_sig_समुच्चयः);
#यदि_अन्तः

    यदि (ready > 0) {
        यदि (दीर्घता > 0) {
            अष्टकानि_written = लिख(fd, (Uint8 *)बफर_2 + *pos, SDL_min(दीर्घता, PIPE_BUF));
        }

        यदि (अष्टकानि_written > 0) {
            *pos += अष्टकानि_written;
        }
    } अन्यथा यदि (ready == 0) {
        SDL_समुच्चयः_Error("Pipe timeout");
    } अन्यथा  {
        SDL_समुच्चयः_Error("Pipe poll error");
    }

    sigtimedwait(&sig_समुच्चयः, रिक्त, &zerotime);

#यदि_परिभाषितम् SDL_तन्तवः_DISABLED
    sigprocmask(SIG_SETMASK, &old_sig_समुच्चयः, रिक्त);
#अन्यथा
    pthread_sigmask(SIG_SETMASK, &old_sig_समुच्चयः, रिक्त);
#यदि_अन्तः

    प्रत्यागम अष्टकानि_written;
}

स्थिर ssize_t ReadPipe(पूर्णाङ्क fd, शून्य **बफर_2, size_t *योग_दीर्घता, Sint64 timeout_ns)
{
    शून्य *output_बफर = रिक्त;
    वर्ण अस्थायी[PIPE_BUF];
    ssize_t अष्टकानि_read = 0;

    ध्रुव पूर्णाङ्क ready = SDL_IOReady(fd, SDL_IOR_READ, timeout_ns);

    यदि (ready > 0) {
        अष्टकानि_read = पठ(fd, अस्थायी, परिमाण(अस्थायी));
    } अन्यथा यदि (ready == 0) {
        SDL_समुच्चयः_Error("Pipe timeout");
    } अन्यथा {
        SDL_समुच्चयः_Error("Pipe poll error");
    }

    यदि (अष्टकानि_read > 0) {
        ध्रुव size_t pos = *योग_दीर्घता;
        *योग_दीर्घता += अष्टकानि_read;

        ध्रुव size_t new_बफर_दीर्घता = *योग_दीर्घता + परिमाण(Uint32);

        यदि (!*बफर_2) {
            output_बफर = SDL_malloc(new_बफर_दीर्घता);
        } अन्यथा {
            output_बफर = SDL_realloc(*बफर_2, new_बफर_दीर्घता);
        }

        यदि (!output_बफर) {
            अष्टकानि_read = -1;
        } अन्यथा {
            SDL_memcpy((Uint8 *)output_बफर + pos, अस्थायी, अष्टकानि_read);
            SDL_memset((Uint8 *)output_बफर + (new_बफर_दीर्घता - परिमाण(Uint32)), 0, परिमाण(Uint32));

            *बफर_2 = output_बफर;
        }
    }

    प्रत्यागम अष्टकानि_read;
}

स्थिर bool MIMEDataListHasType(संरचना wl_array *list, ध्रुव वर्ण *mime_type)
{
    ध्रुव वर्ण **item;
    wl_array_for_each(item, list) {
        यदि (SDL_strcmp(*item, mime_type) == 0) {
            प्रत्यागम true;
        }
    }

    प्रत्यागम false;
}

स्थिर bool MIMEData_List_सङ्कलय(संरचना wl_array *list, ध्रुव वर्ण *mime_type)
{
    यदि (!MIMEDataListHasType(list, mime_type)) {
        वर्ण **item = WAYLAND_wl_array_सङ्कलय(list, परिमाण(वर्ण *));
        *item = SDL_strdup(mime_type);
    }

    प्रत्यागम true;
}

स्थिर शून्य MIMEDataListFree(संरचना wl_array *list)
{
    वर्ण **item;
    wl_array_for_each(item, list) {
        SDL_free(*item);
    }

    WAYLAND_wl_array_release(list);
}

स्थिर शून्य दत्त_source_handle_target(शून्य *दत्त, संरचना wl_दत्त_source *wl_दत्त_source, ध्रुव वर्ण *mime_type)
{
}

स्थिर शून्य दत्त_source_handle_send(शून्य *दत्त, संरचना wl_दत्त_source *wl_दत्त_source, ध्रुव वर्ण *mime_type, int32_t fd)
{
    Wayland_दत्त_Source_Send((SDL_Wayland_दत्त_Source *)दत्त, mime_type, fd);
}

स्थिर शून्य दत्त_source_handle_cancelled(शून्य *दत्त, संरचना wl_दत्त_source *wl_दत्त_source)
{
    SDL_Wayland_दत्त_Source *source = दत्त;
    यदि (source) {
        Wayland_दत्त_Source_Destroy(source);
    }
}

स्थिर शून्य दत्त_source_handle_dnd_drop_performed(शून्य *दत्त, संरचना wl_दत्त_source *wl_दत्त_source)
{
}

स्थिर शून्य दत्त_source_handle_dnd_परिसमाप्तम्(शून्य *दत्त, संरचना wl_दत्त_source *wl_दत्त_source)
{
    SDL_Wayland_दत्त_Source *source = दत्त;
    यदि (source) {
        Wayland_दत्त_Source_Destroy(source);
    }
}

स्थिर शून्य दत्त_source_handle_action(शून्य *दत्त, संरचना wl_दत्त_source *wl_दत्त_source, uint32_t dnd_action)
{
}

स्थिर ध्रुव संरचना wl_दत्त_source_listener दत्त_source_listener = {
    दत्त_source_handle_target,
    दत्त_source_handle_send,
    दत्त_source_handle_cancelled,
    दत्त_source_handle_dnd_drop_performed, // Version 3
    दत्त_source_handle_dnd_परिसमाप्तम्,       // Version 3
    दत्त_source_handle_action,             // Version 3
};

SDL_Wayland_दत्त_Source *Wayland_दत्त_Source_Create(SDL_Video_दत्त *video_दत्त)
{
    SDL_Wayland_दत्त_Source *दत्त_source = SDL_calloc(1, परिमाण(*दत्त_source));
    यदि (!दत्त_source) {
        प्रत्यागम रिक्त;
    }

    संरचना wl_दत्त_source *id = wl_दत्त_device_manager_create_दत्त_source(video_दत्त->दत्त_device_manager);
    दत्त_source->source = id;
    wl_दत्त_source_समुच्चयः_user_दत्त(id, दत्त_source);
    wl_दत्त_source_सङ्कलय_listener(id, &दत्त_source_listener, दत्त_source);

    प्रत्यागम दत्त_source;
}

स्थिर शून्य primary_selection_source_send(शून्य *दत्त, संरचना zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1, ध्रुव वर्ण *mime_type, int32_t fd)
{
    Wayland_PrimarySelectionSourceSend((SDL_WaylandPrimarySelectionSource *)दत्त, mime_type, fd);
}

स्थिर शून्य primary_selection_source_cancelled(शून्य *दत्त, संरचना zwp_primary_selection_source_v1 *zwp_primary_selection_source_v1)
{
    Wayland_PrimarySelectionSourceDestroy(दत्त);
}

स्थिर ध्रुव संरचना zwp_primary_selection_source_v1_listener primary_selection_source_listener = {
    primary_selection_source_send,
    primary_selection_source_cancelled,
};

SDL_WaylandPrimarySelectionSource *Wayland_PrimarySelectionSourceCreate(SDL_Video_दत्त *video_दत्त)
{
    SDL_WaylandPrimarySelectionSource *primary_selection_source = SDL_calloc(1, परिमाण(*primary_selection_source));
    यदि (!primary_selection_source) {
        प्रत्यागम रिक्त;
    }

    संरचना zwp_primary_selection_source_v1 *id = zwp_primary_selection_device_manager_v1_create_source(video_दत्त->primary_selection_device_manager);
    primary_selection_source->source = id;
    zwp_primary_selection_source_v1_सङ्कलय_listener(id, &primary_selection_source_listener, primary_selection_source);

    प्रत्यागम primary_selection_source;
}

स्थिर size_t Send_दत्त(ध्रुव शून्य *दत्त, size_t दीर्घता, पूर्णाङ्क fd)
{
    size_t परिणाम = 0;

    यदि (दीर्घता > 0 && दत्त) {
        यावत् (WritePipe(fd, दत्त, दीर्घता, &परिणाम) > 0) {
            // Just keep spinning
        }
    }
    close(fd);

    प्रत्यागम परिणाम;
}

ssize_t Wayland_दत्त_Source_Send(SDL_Wayland_दत्त_Source *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd)
{
    ध्रुव शून्य *दत्त = रिक्त;
    size_t दीर्घता = 0;

    यदि (SDL_strcmp(mime_type, SDL_दत्त_ORIGIN_MIME) == 0) {
        दत्त = source->दत्त_device->id_str;
        दीर्घता = SDL_strlen(source->दत्त_device->id_str);
    } अन्यथा यदि (source->दत्त_callback) {
        दत्त = source->दत्त_callback(source->userdata.दत्त, mime_type, &दीर्घता);
    }

    प्रत्यागम Send_दत्त(दत्त, दीर्घता, fd);
}

ssize_t Wayland_PrimarySelectionSourceSend(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, पूर्णाङ्क fd)
{
    ध्रुव शून्य *दत्त = रिक्त;
    size_t दीर्घता = 0;

    यदि (source->दत्त_callback) {
        दत्त = source->दत्त_callback(source->userdata.दत्त, mime_type, &दीर्घता);
    }

    प्रत्यागम Send_दत्त(दत्त, दीर्घता, fd);
}

शून्य Wayland_दत्त_Source_समुच्चयः_Callback(SDL_Wayland_दत्त_Source *source, SDL_Clipboard_दत्त_Callback दत्त_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata, Uint32 sequence)
{
    यदि (source) {
        source->दत्त_callback = दत्त_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = sequence;
        source->userdata.दत्त = userdata;
    }
}

शून्य Wayland_Primary_Selection_Source_समुच्चयः_Callback(SDL_WaylandPrimarySelectionSource *source, SDL_Clipboard_दत्त_Callback दत्त_callback, SDL_ClipboardCleanupCallback cleanup_callback, शून्य *userdata)
{
    यदि (source) {
        source->दत्त_callback = दत्त_callback;
        source->cleanup_callback = cleanup_callback;
        source->userdata.sequence = 0;
        source->userdata.दत्त = userdata;
    }
}

स्थिर शून्य *Clone_दत्त_बफर(ध्रुव शून्य *बफर_2, ध्रुव size_t *len)
{
    शून्य *clone = रिक्त;
    यदि (*len > 0 && बफर_2) {
        clone = SDL_malloc((*len)+परिमाण(Uint32));
        यदि (clone) {
            SDL_memcpy(clone, बफर_2, *len);
            SDL_memset((Uint8 *)clone + *len, 0, परिमाण(Uint32));
        }
    }
    प्रत्यागम clone;
}

शून्य *Wayland_दत्त_Source_Get_दत्त(SDL_Wayland_दत्त_Source *source, ध्रुव वर्ण *mime_type, size_t *दीर्घता)
{
    शून्य *बफर_2 = रिक्त;
    *दीर्घता = 0;

    यदि (!source) {
        SDL_समुच्चयः_Error("Invalid data source");
    } अन्यथा यदि (source->दत्त_callback) {
        ध्रुव शून्य *आन्तरिकम्_बफर = source->दत्त_callback(source->userdata.दत्त, mime_type, दीर्घता);
        बफर_2 = Clone_दत्त_बफर(आन्तरिकम्_बफर, दीर्घता);
    }

    प्रत्यागम बफर_2;
}

शून्य *Wayland_Primary_Selection_Source_Get_दत्त(SDL_WaylandPrimarySelectionSource *source, ध्रुव वर्ण *mime_type, size_t *दीर्घता)
{
    शून्य *बफर_2 = रिक्त;
    *दीर्घता = 0;

    यदि (!source) {
        SDL_समुच्चयः_Error("Invalid primary selection source");
    } अन्यथा यदि (source->दत्त_callback) {
        ध्रुव शून्य *आन्तरिकम्_बफर = source->दत्त_callback(source->userdata.दत्त, mime_type, दीर्घता);
        बफर_2 = Clone_दत्त_बफर(आन्तरिकम्_बफर, दीर्घता);
    }

    प्रत्यागम बफर_2;
}

शून्य Wayland_दत्त_Source_Destroy(SDL_Wayland_दत्त_Source *source)
{
    यदि (source) {
        SDL_Wayland_दत्त_Device *दत्त_device = source->दत्त_device;
        यदि (दत्त_device && (दत्त_device->selection_source == source)) {
            दत्त_device->selection_source = रिक्त;
        }
        wl_दत्त_source_destroy(source->source);
        यदि (source->userdata.sequence) {
            SDL_Cancel_Clipboard_दत्त(source->userdata.sequence);
        } अन्यथा यदि (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.दत्त);
        }
        SDL_free(source);
    }
}

शून्य Wayland_PrimarySelectionSourceDestroy(SDL_WaylandPrimarySelectionSource *source)
{
    यदि (source) {
        SDL_WaylandPrimarySelectionDevice *primary_selection_device = source->primary_selection_device;
        यदि (primary_selection_device && (primary_selection_device->selection_source == source)) {
            primary_selection_device->selection_source = रिक्त;
        }
        zwp_primary_selection_source_v1_destroy(source->source);
        यदि (source->cleanup_callback) {
            source->cleanup_callback(source->userdata.दत्त);
        }
        SDL_free(source);
    }
}

स्थिर शून्य SelectionOfferNotifyFromMIMEs(SDL_Wayland_दत्त_Device *दत्त_device, bool check_origin);

स्थिर शून्य offer_source_समाप्तम्_handler(शून्य *दत्त, संरचना wl_callback *callback, uint32_t callback_दत्त)
{
    यदि (!callback) {
        प्रत्यागम;
    }

    SDL_Wayland_दत्त_Offer *offer = (SDL_Wayland_दत्त_Offer *)दत्त;
    वर्ण *id = रिक्त;
    size_t दीर्घता = 0;

    wl_callback_destroy(offer->callback);
    offer->callback = रिक्त;

    यावत् (ReadPipe(offer->read_fd, (शून्य **)&id, &दीर्घता, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
    }
    close(offer->read_fd);
    offer->read_fd = -1;

    यदि (id) {
        ध्रुव bool source_is_external = SDL_strncmp(offer->दत्त_device->id_str, id, दीर्घता) != 0;
        SDL_free(id);
        यदि (source_is_external) {
            SelectionOfferNotifyFromMIMEs(offer->दत्त_device, false);
        } अन्यथा {
            // Recursive data offer; just destroy it.
            SDL_Wayland_दत्त_Device *दत्त_device = offer->दत्त_device;
            Wayland_दत्त_Offer_Destroy(offer);
            दत्त_device->selection_offer = रिक्त;
        }
    }
}

स्थिर ध्रुव संरचना wl_callback_listener offer_source_listener = {
    offer_source_समाप्तम्_handler
};

स्थिर शून्य UpdateSeatOffers(SDL_Wayland_दत्त_Device *दत्त_device)
{
    SDL_WaylandSeat *offer_seat = दत्त_device->seat;
    SDL_Video_दत्त *video_दत्त = offer_seat->display;

    // Clear any existing references to the existing clipboard data before replacing the current offer.
    SDL_WaylandSeat *s;
    wl_list_for_each (s, &video_दत्त->seat_list, link) {
        यदि (s->दत्त_device) {
            Wayland_दत्त_Source_Destroy(s->दत्त_device->selection_source);
            s->दत्त_device->selection_source = रिक्त;

            // Don't clear the offer that is about to be set.
            यदि (s != offer_seat) {
                Wayland_दत्त_Offer_Destroy(s->दत्त_device->selection_offer);
                s->दत्त_device->selection_offer = रिक्त;
            }
        }
    }

    video_दत्त->current_दत्त_offer_seat = offer_seat;
}

स्थिर शून्य SelectionOfferNotifyFromMIMEs(SDL_Wayland_दत्त_Device *दत्त_device, bool check_origin)
{
    SDL_Wayland_दत्त_Offer *offer = दत्त_device->selection_offer;
    वर्ण **new_mime_types = रिक्त;
    size_t अङ्कः_formats = 0;

    यदि (offer) {
        size_t alloc_आकार_2 = 0;

        // Do a first pass to compute allocation size.
        ध्रुव वर्ण **item;
        wl_array_for_each(item, &offer->mimes) {
            // If origin metadata is found, queue a check and wait for confirmation that this offer isn't recursive.
            यदि (check_origin && SDL_strcmp(*item, SDL_दत्त_ORIGIN_MIME) == 0) {
                Wayland_दत्त_Offer_Request_दत्त_From_Self(offer, *item, &offer_source_listener, offer);
                प्रत्यागम;
            }

            ++अङ्कः_formats;
            alloc_आकार_2 += SDL_strlen(*item) + 1;
        }

        alloc_आकार_2 += (अङ्कः_formats + 1) * परिमाण(वर्ण *);

        new_mime_types = SDL_Allocate_Temporary_स्मृतिः(alloc_आकार_2);
        यदि (!new_mime_types) {
            SDL_LogError(SDL_LOG_CATEGORY_निवेशः, "unable to allocate new_mime_types");
            प्रत्यागम;
        }

        // Second pass to fill.
        वर्ण *strPtr = (वर्ण *)(new_mime_types + अङ्कः_formats + 1);
        alloc_आकार_2 -= (uintptr_t)strPtr - (uintptr_t)new_mime_types;

        item = रिक्त;
        पूर्णाङ्क i = 0;
        wl_array_for_each(item, &offer->mimes) {
            यदि (!item) {
                अनुवर्त;
            }

            new_mime_types[i++] = strPtr;
            ध्रुव size_t len = SDL_strlcpy(strPtr, *item, alloc_आकार_2) + 1;
            strPtr += len;
            alloc_आकार_2 -= len;
        }
        new_mime_types[अङ्कः_formats] = रिक्त;
    }

    UpdateSeatOffers(दत्त_device);
    SDL_SendClipboardUpdate(false, new_mime_types, अङ्कः_formats);
}

शून्य Wayland_दत्त_Device_समुच्चयः_Selection_Offer(SDL_Wayland_दत्त_Device *दत्त_device, SDL_Wayland_दत्त_Offer *offer)
{
    // Don't notify when clearing the old selection offer if doing so will inadvertently clear the selection source.
    ध्रुव bool notify = offer || (!offer && दत्त_device->selection_offer && (!दत्त_device->selection_offer->callback || !दत्त_device->selection_source));
    Wayland_दत्त_Offer_Destroy(दत्त_device->selection_offer);
    दत्त_device->selection_offer = offer;
    यदि (notify) {
        SelectionOfferNotifyFromMIMEs(दत्त_device, true);
    }
}

शून्य *Wayland_दत्त_Offer_Get_दत्त_From_Self(SDL_Wayland_दत्त_Offer *offer, size_t *दीर्घता)
{
    यदि (!offer) {
        SDL_समुच्चयः_Error("Invalid data offer");
        प्रत्यागम रिक्त;
    }

    यदि (offer->read_fd < 0) {
        SDL_समुच्चयः_Error("Pipe closed");
        प्रत्यागम रिक्त;
    }

    // The timeout is 0, as the data will already be in the pipe if it is from this process.
    शून्य *बफर_2 = रिक्त;
    यावत् (ReadPipe(offer->read_fd, &बफर_2, दीर्घता, 0) > 0) {
    }

    प्रत्यागम बफर_2;
}

bool Wayland_दत्त_Offer_Request_दत्त_From_Self(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type, ध्रुव संरचना wl_callback_listener *completion_listener, शून्य *userdata)
{
    पूर्णाङ्क pipefd[2];

    यदि (!offer) {
        SDL_समुच्चयः_Error("Invalid data offer");
        प्रत्यागम false;
    }

    SDL_Wayland_दत्त_Device *दत्त_device = offer->दत्त_device;
    यदि (offer->read_fd >= 0) {
        close(offer->read_fd);
        offer->read_fd = -1;
    }
    यदि (offer->callback) {
        wl_callback_destroy(offer->callback);
        offer->callback = रिक्त;
    }

    यदि (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        offer->read_fd = pipefd[0];
        wl_दत्त_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        offer->callback = wl_display_sync(दत्त_device->seat->display->display);
        wl_callback_सङ्कलय_listener(offer->callback, completion_listener, userdata);

        WAYLAND_wl_display_flush(दत्त_device->seat->display->display);
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("Could not create pipe");
    }

    प्रत्यागम true;
}

शून्य *Wayland_दत्त_Offer_Receive(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type, size_t *दीर्घता)
{
    पूर्णाङ्क pipefd[2];
    शून्य *बफर_2 = रिक्त;
    *दीर्घता = 0;

    यदि (!offer) {
        SDL_समुच्चयः_Error("Invalid data offer");
        प्रत्यागम रिक्त;
    }

    SDL_Wayland_दत्त_Device *दत्त_device = offer->दत्त_device;

    यदि (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        wl_दत्त_offer_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(दत्त_device->seat->display->display);

        यावत् (ReadPipe(pipefd[0], &बफर_2, दीर्घता, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);
    } अन्यथा {
        SDL_समुच्चयः_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In Wayland_data_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *दीर्घता, बफर_2);

    प्रत्यागम बफर_2;
}

शून्य *Wayland_PrimarySelectionOfferReceive(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type, size_t *दीर्घता)
{
    पूर्णाङ्क pipefd[2];
    शून्य *बफर_2 = रिक्त;
    *दीर्घता = 0;

    यदि (!offer) {
        SDL_समुच्चयः_Error("Invalid data offer");
        प्रत्यागम रिक्त;
    }

    SDL_WaylandPrimarySelectionDevice *primary_selection_device = offer->primary_selection_device;

    यदि (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == 0) {
        zwp_primary_selection_offer_v1_receive(offer->offer, mime_type, pipefd[1]);
        close(pipefd[1]);

        WAYLAND_wl_display_flush(primary_selection_device->seat->display->display);

        यावत् (ReadPipe(pipefd[0], &बफर_2, दीर्घता, DEFAULT_PIPE_TIMEOUT_NS) > 0) {
        }
        close(pipefd[0]);

    } अन्यथा {
        SDL_समुच्चयः_Error("Could not create pipe");
    }

    SDL_LogTrace(SDL_LOG_CATEGORY_निवेशः,
                 ". In Wayland_primary_selection_offer_receive for '%s', buffer (%zu) at %p",
                 mime_type, *दीर्घता, बफर_2);

    प्रत्यागम बफर_2;
}

bool Wayland_दत्त_Offer_सङ्कलय_MIME(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type)
{
    प्रत्यागम MIMEData_List_सङ्कलय(&offer->mimes, mime_type);
}

bool Wayland_Primary_Selection_Offer_सङ्कलय_MIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type)
{
    प्रत्यागम MIMEData_List_सङ्कलय(&offer->mimes, mime_type);
}

bool Wayland_दत्त_Offer_Has_MIME(SDL_Wayland_दत्त_Offer *offer, ध्रुव वर्ण *mime_type)
{
    यदि (offer && mime_type) {
        प्रत्यागम MIMEDataListHasType(&offer->mimes, mime_type);
    }
    प्रत्यागम false;
}

bool Wayland_PrimarySelectionOfferHasMIME(SDL_WaylandPrimarySelectionOffer *offer, ध्रुव वर्ण *mime_type)
{
    यदि (offer && mime_type) {
        प्रत्यागम MIMEDataListHasType(&offer->mimes, mime_type);
    }
    प्रत्यागम false;
}

शून्य Wayland_दत्त_Offer_Destroy(SDL_Wayland_दत्त_Offer *offer)
{
    यदि (offer) {
        यदि (offer->callback) {
            wl_callback_destroy(offer->callback);
        }
        यदि (offer->read_fd >= 0) {
            close(offer->read_fd);
        }
        wl_दत्त_offer_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

शून्य Wayland_PrimarySelectionOfferDestroy(SDL_WaylandPrimarySelectionOffer *offer)
{
    यदि (offer) {
        zwp_primary_selection_offer_v1_destroy(offer->offer);
        MIMEDataListFree(&offer->mimes);
        SDL_free(offer);
    }
}

bool Wayland_दत्त_Device_समुच्चयः_Selection_Source(SDL_Wayland_दत्त_Device *दत्त_device, SDL_Wayland_दत्त_Source *source, ध्रुव वर्ण **mime_types, size_t mime_गणनम्)
{
    यदि (!दत्त_device) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid Data Device");
    }
    यदि (!source) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid source");
    }

    यदि (mime_गणनम्) {
        प्रति (size_t सूचकांक = 0; सूचकांक < mime_गणनम्; ++सूचकांक) {
            ध्रुव वर्ण *mime_type = mime_types[सूचकांक];
            wl_दत्त_source_offer(source->source, mime_type);
        }

        // Advertise the data origin MIME
        wl_दत्त_source_offer(source->source, SDL_दत्त_ORIGIN_MIME);

        wl_दत्त_device_समुच्चयः_selection(दत्त_device->दत्त_device, source->source, दत्त_device->seat->चरमः_implicit_grab_serial);
        यदि (दत्त_device->selection_source) {
            Wayland_दत्त_Source_Destroy(दत्त_device->selection_source);
        }
        दत्त_device->selection_source = source;
        source->दत्त_device = दत्त_device;

    } अन्यथा {
        Wayland_दत्त_Source_Destroy(दत्त_device->selection_source);
        दत्त_device->selection_source = रिक्त;
        प्रत्यागम SDL_समुच्चयः_Error("No mime data");
    }

    प्रत्यागम true;
}

bool Wayland_Primary_Selection_Device_समुच्चयः_Selection(SDL_WaylandPrimarySelectionDevice *primary_selection_device,
                                                SDL_WaylandPrimarySelectionSource *source,
                                                ध्रुव वर्ण *ध्रुव *mime_types, size_t mime_गणनम्)
{
    यदि (!primary_selection_device) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid Primary Selection Device");
    }
    यदि (!source) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid source");
    }

    यदि (mime_गणनम्) {
        प्रति (size_t सूचकांक = 0; सूचकांक < mime_गणनम्; ++सूचकांक) {
            ध्रुव वर्ण *mime_type = mime_types[सूचकांक];
            zwp_primary_selection_source_v1_offer(source->source, mime_type);
        }

        zwp_primary_selection_device_v1_समुच्चयः_selection(primary_selection_device->primary_selection_device,
                                                      source->source,
                                                      primary_selection_device->seat->चरमः_implicit_grab_serial);
        यदि (primary_selection_device->selection_source) {
            Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        }
        primary_selection_device->selection_source = source;
        source->primary_selection_device = primary_selection_device;
    } अन्यथा {
        Wayland_PrimarySelectionSourceDestroy(primary_selection_device->selection_source);
        primary_selection_device->selection_source = रिक्त;
        प्रत्यागम SDL_समुच्चयः_Error("No mime data");
    }

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND

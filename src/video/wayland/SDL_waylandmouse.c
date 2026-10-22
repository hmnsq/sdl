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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ଅନ୍ତର୍ଭାଵ <errno.h>

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_video_c.h"

#ଅନ୍ତର୍ଭାଵ "../../core/unix/SDL_poll.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandevents_c.h"

#ଅନ୍ତର୍ଭାଵ "wayland-cursor.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandmouse.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandshmbuffer.h"

#ଅନ୍ତର୍ଭାଵ "cursor-shape-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "pointer-constraints-unstable-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "viewporter-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "pointer-warp-v1-client-protocol.h"
#ଅନ୍ତର୍ଭାଵ "tablet-v2-client-protocol.h"

#ଅନ୍ତର୍ଭାଵ "../../SDL_hints_c.h"

ସ୍ଥିର SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ବାମ + 1];

ସ୍ଥିର bool Wayland_SetRelativeMouseMode(bool enabled);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
    ସଂରଚନା wl_buffer *buffer;
} CustomCursorImage;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    // The base dimensions of the cursor.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;
    ସଂରଚନା wl_list ଗଣ୍ଠି;
    ସଂରଚନା wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    SDL_SystemCursor id;
    ସଂରଚନା wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

ସଂରଚନା SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_frames;
    bool is_system_cursor;

    ସଂଘ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା dbus_cursor_size;
ସ୍ଥିର ଅକ୍ଷର *dbus_cursor_theme;

ସ୍ଥିର ଶୂନ୍ୟ Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < vdata->ଅଙ୍କ_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->ଅଙ୍କ_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ଖାଲି;
}

#ifdef SDL_USE_LIBDBUS

#ଅନ୍ତର୍ଭାଵ "../../core/linux/SDL_dbus.h"

#define CURSOR_ଗଣ୍ଠି        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_ଚାବି    "cursor-size"
#define CURSOR_THEME_ଚାବି   "cursor-theme"

ସ୍ଥିର DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ଅଚଳ ଅକ୍ଷର *ଚାବି)
{
    ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = ଖାଲି;
    DBusMessage *ସନ୍ଦେଶ = dbus->message_new_method_call(CURSOR_ଗଣ୍ଠି,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    ଯଦି (ସନ୍ଦେଶ) {
        ଯଦି (dbus->message_append_args(ସନ୍ଦେଶ, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &ଚାବି, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, ସନ୍ଦେଶ, DBUS_TIMEOUT_USE_DEFAULT, ଖାଲି);
        }
        dbus->message_unref(ସନ୍ଦେଶ);
    }

    ଫେରନ୍ତୁ reply;
}

ସ୍ଥିର bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, ପୂର୍ଣ୍ଣସଂଖ୍ୟା type, ଶୂନ୍ୟ *ମୂଲ୍ୟ)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    ଯଦି (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        ଫେରନ୍ତୁ false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    ଯଦି (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        ଫେରନ୍ତୁ false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    ଯଦି (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        ଫେରନ୍ତୁ false;
    }

    dbus->message_iter_get_basic(&iter[2], ମୂଲ୍ୟ);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *ସନ୍ଦେଶ, ଶୂନ୍ୟ *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    ଯଦି (dbus->message_is_signal(ସନ୍ଦେଶ, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        ଅଚଳ ଅକ୍ଷର *namespace, *ଚାବି;

        dbus->message_iter_init(ସନ୍ଦେଶ, &signal_iter);
        // Check if the parameters are what we expect
        ଯଦି (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ଯାଅ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        ଯଦି (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            ଯାଅ not_our_signal;
        }
        ଯଦି (!dbus->message_iter_next(&signal_iter)) {
            ଯାଅ not_our_signal;
        }
        ଯଦି (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ଯାଅ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &ଚାବି);
        ଯଦି (SDL_strcmp(CURSOR_SIZE_ଚାବି, ଚାବି) == 0) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_cursor_size;

            ଯଦି (!dbus->message_iter_next(&signal_iter)) {
                ଯାଅ not_our_signal;
            }
            ଯଦି (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ଯାଅ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            ଯଦି (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                ଯାଅ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            ଯଦି (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } ଅନ୍ୟଥା ଯଦି (SDL_strcmp(CURSOR_THEME_ଚାବି, ଚାବି) == 0) {
            ଅଚଳ ଅକ୍ଷର *new_cursor_theme = ଖାଲି;

            ଯଦି (!dbus->message_iter_next(&signal_iter)) {
                ଯାଅ not_our_signal;
            }
            ଯଦି (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ଯାଅ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            ଯଦି (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                ଯାଅ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            ଯଦି (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                ଯଦି (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } ଅନ୍ୟଥା {
                    dbus_cursor_theme = ଖାଲି;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } ଅନ୍ୟଥା {
            ଯାଅ not_our_signal;
        }

        ଫେରନ୍ତୁ DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    ଫେରନ୍ତୁ DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    ଯଦି (!dbus) {
        ଫେରନ୍ତୁ;
    }

    ଯଦି ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_ଚାବି))) {
        ଯଦି (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    ଯଦି ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_ଚାବି))) {
        ଅଚଳ ଅକ୍ଷର *temp = ଖାଲି;
        ଯଦି (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            ଯଦି (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    ଯଦି (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ଖାଲି);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, ଖାଲି);
        dbus->connection_flush(dbus->session_conn);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_DBusFinishCursorProperties(ଶୂନ୍ୟ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ଖାଲି;
}

#endif

ସ୍ଥିର ସଂରଚନା wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    ଯଦି (data) {
        ଯଦି (!data->is_system_cursor) {
            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ଖାଲି;
            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା closest_area = 0;
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            ଫେରନ୍ତୁ closest ? closest->buffer : ଖାଲି;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ cursor_frame_done(ଶୂନ୍ୟ *data, ସଂରଚନା wl_callback *cb, uint32_t time);
ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

ସ୍ଥିର ଶୂନ୍ୟ cursor_frame_done(ଶୂନ୍ୟ *data, ସଂରଚନା wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    ଯଦି (!state->current_cursor) {
        ଫେରନ୍ତୁ;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    ଅଚଳ Uint64 now = SDL_GetTicks();
    ଅଚଳ Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    ପାଇଁ (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->ଅଙ୍କ_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        ଯଦି (!frames[next]) {
            ଭାଙ୍ଗ;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = ଖାଲି;

    // Don't queue another callback if this frame time is infinite.
    ଯଦି (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    ସଂରଚନା wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    ଯଦି (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ଅନ୍ୟଥା {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

ଶୂନ୍ୟ Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, ଶୂନ୍ୟ *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ଶୂନ୍ୟ Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    ଯଦି (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = ଖାଲି;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    ଯଦି (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } ଅନ୍ୟଥା {
        Wayland_CursorStateResetAnimationState(state);
    }
}

ଶୂନ୍ୟ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    ଯଦି (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    ଯଦି (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    ଯଦି (state->surface) {
        wl_surface_attach(state->surface, ଖାଲି, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ସ୍ଥିର Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, ସଂରଚନା wl_cursor *cursor, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
    Wayland_CachedSystemCursor *cache = ଖାଲି;

    // Is this cursor already cached at the target scale?
    ଯଦି (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = ଖାଲି;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, ଗଣ୍ଠି) {
            ଯଦି (c->size == size) {
                cache = c;
                ଭାଙ୍ଗ;
            }
        }
    }

    ଯଦି (!cache) {
        cache = SDL_calloc(1, ଆକାର(Wayland_CachedSystemCursor) + (ଆକାର(ସଂରଚନା wl_buffer *) * cdata->ଅଙ୍କ_frames));

        cache->size = size;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < cdata->ଅଙ୍କ_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_ଭର୍ତ୍ତି(&cdata->cursor_data.system.cursor_buffer_cache, &cache->ଗଣ୍ଠି);
    }

    ଫେରନ୍ତୁ cache;
}

ସ୍ଥିର bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst_size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    ସଂରଚନା wl_cursor_theme *theme = ଖାଲି;
    ଅଚଳ ଅକ୍ଷର *css_name = "default";
    ଅଚଳ ଅକ୍ଷର *fallback_name = ଖାଲି;
    ଦ୍ୱିଗୁଣ scale_factor = state->scale;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    ଯଦି (theme_size <= 0) {
        ଅଚଳ ଅକ୍ଷର *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        ଯଦି (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    ଯଦି (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା scaled_size = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_lround(theme_size * scale_factor);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < vdata->ଅଙ୍କ_cursor_themes; ++i) {
        ଯଦି (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (!theme) {
        ଅଚଳ ଅକ୍ଷର *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                ଆକାର(SDL_WaylandCursorTheme) * (vdata->ଅଙ୍କ_cursor_themes + 1));
        ଯଦି (!new_cursor_themes) {
            ଫେରନ୍ତୁ false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        ଯଦି (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->ଅଙ୍କ_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->ଅଙ୍କ_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    ସଂରଚନା wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    ଯଦି (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    ଯଦି (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    ଯଦି (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    ଯଦି (!cursor) {
        ଫେରନ୍ତୁ false;
    }

    // ... Set the cursor data, finally.
    cdata->ଅଙ୍କ_frames = cursor->image_ଗଣନା_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    ଯଦି (cursor->image_ଗଣନା_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_ଗଣନା_2, ଆକାର(Uint32));

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < cursor->image_ଗଣନା_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା surface_sort_callback(ଅଚଳ ଶୂନ୍ୟ *a, ଅଚଳ ଶୂନ୍ୟ *b)
{
    ଅଚଳ SDL_Surface *s1 = *(ଅଚଳ SDL_Surface **)a;
    ଅଚଳ SDL_Surface *s2 = *(ଅଚଳ SDL_Surface **)b;

    ଫେରନ୍ତୁ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ସ୍ଥିର SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_ଗଣନା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, ଆକାର(*cursor));
    ଯଦି (!cursor) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_CursorData *data = ଖାଲି;
    Wayland_SHMPool *shm_pool = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pool_size = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_images = 0;
    bool is_ଗଦା = false;
    ସଂରଚନା SurfaceArray
    {
        SDL_Surface **surfaces;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2;
    } *surfaces = SDL_small_alloc(ସଂରଚନା SurfaceArray, frame_ଗଣନା, &is_ଗଦା);
    ଯଦି (!surfaces) {
        ଯାଅ failed;
    }
    SDL_memset(surfaces, 0, ଆକାର(ସଂରଚନା SurfaceArray) * frame_ଗଣନା);

    // Calculate the total allocation size.
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame_ଗଣନା; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].ଗଣନା_2);
        ଯଦି (!surfaces[i].surfaces) {
            ଯାଅ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].ଗଣନା_2, ଆକାର(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].ଗଣନା_2);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < surfaces[i].ଗଣନା_2; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, ଆକାର(*data) + (ଆକାର(CustomCursorImage) * max_images * frame_ଗଣନା));
    ଯଦି (!data) {
        ଯାଅ failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_ଗଣନା, ଆକାର(Uint32));
    ଯଦି (!data->frame_durations_ms) {
        ଯାଅ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    ଯଦି (!shm_pool) {
        ଯାଅ failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->ଅଙ୍କ_frames = frame_ଗଣନା;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame_ଗଣନା; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        ଯଦି (data->total_duration_ms < SDL_MAX_UINT32) {
            ଯଦି (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } ଅନ୍ୟଥା {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset = i * max_images;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < surfaces[i].ଗଣନା_2; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            ଯଦି (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                ଯଦି (!surface) {
                    ଯାଅ failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            ଶୂନ୍ୟ *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            ଯଦି (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ଗଦା);
    Wayland_ReleaseSHMPool(shm_pool);

    ଫେରନ୍ତୁ cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    ଯଦି (data) {
        SDL_free(data->frame_durations_ms);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < data->cursor_data.custom.images_per_frame * frame_ଗଣନା; ++i) {
            ଯଦି (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    ଯଦି (surfaces) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame_ଗଣନା; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ଗଦା);
    }

    SDL_free(cursor);

    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    ଫେରନ୍ତୁ Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

ସ୍ଥିର SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, ଆକାର(*cursor));

    ଯଦି (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, ଆକାର(*cdata));
        ଯଦି (!cdata) {
            SDL_free(cursor);
            ଫେରନ୍ତୁ ଖାଲି;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *Wayland_CreateDefaultCursor(ଶୂନ୍ୟ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ଫେରନ୍ତୁ Wayland_CreateSystemCursor(id);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        ଯଦି (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            ଯଦି (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, ଖାଲି, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = ଖାଲି;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ଯଦି (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                ଯଦି (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, ଖାଲି, 0, 0);
                }

                tool->cursor_state.current_cursor = ଖାଲି;
            }
        }
    }

    ଯଦି (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, ଗଣ୍ଠି) {
            SDL_free(c);
        }
    } ଅନ୍ୟଥା {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < d->ଅଙ୍କ_frames * d->cursor_data.custom.images_per_frame; ++i) {
            ଯଦି (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    ଯଦି (!cursor) {
        ଫେରନ୍ତୁ;
    }

    // Probably not a cursor we own
    ଯଦି (!cursor->internal) {
        ଫେରନ୍ତୁ;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ସ୍ଥିର ଗଣନା wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    ବାଛ (id) {
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    ଫେରନ୍ତୁ shape;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Wayland_PointerObject
{
    ସଂଘ
    {
        ସଂରଚନା wl_pointer *wl_pointer;
        ସଂରଚନା zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

ସ୍ଥିର ଶୂନ୍ୟ Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, ଅଚଳ Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_width = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_height = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y;

    // Stop the frame callback for old animated cursors.
    ଯଦି (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    ଯଦି (cursor) {
        ଯଦି (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            ଯଦି (cursor_data->ଅଙ୍କ_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            ଫେରନ୍ତୁ;
        }

        ଯଦି (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            ଯଦି (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                ଯଦି (state->surface) {
                    wl_surface_attach(state->surface, ଖାଲି, 0, 0);
                    wl_surface_commit(state->surface);

                    ଯଦି (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, ଖାଲି, 0, 0);
                    } ଅନ୍ୟଥା {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ଖାଲି, 0, 0);
                    }

                    ଯଦି (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ଖାଲି;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ଖାଲି;
                }

                ଅଚଳ ଗଣନା wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                ଫେରନ୍ତୁ;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            ଯଦି (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                ଫେରନ୍ତୁ;
            }

            dst_height = dst_width;
        } ଅନ୍ୟଥା {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            ଯଦି (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } ଅନ୍ୟଥା {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_lround((ଦ୍ୱିଗୁଣ)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_lround((ଦ୍ୱିଗୁଣ)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_lround((ଦ୍ୱିଗୁଣ)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_lround((ଦ୍ୱିଗୁଣ)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        ଯଦି (!state->surface) {
            ସଂରଚନା wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ସଂରଚନା wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        ଯଦି (state->scale != 1.0) {
            ଯଦି (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } ଅନ୍ୟଥା ଯଦି (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ଖାଲି;
        }

        ଯଦି (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } ଅନ୍ୟଥା {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        ଯଦି (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ଅନ୍ୟଥା {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        ଯଦି (cursor_data->ଅଙ୍କ_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } ଅନ୍ୟଥା {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = ଖାଲି;

        ଯଦି (state->surface) {
            wl_surface_attach(state->surface, ଖାଲି, 0, 0);
            wl_surface_commit(state->surface);
        }

        ଯଦି (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, ଖାଲି, 0, 0);
        } ଅନ୍ୟଥା {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ଖାଲି, 0, 0);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

ଶୂନ୍ୟ Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    ଅଚଳ ଦ୍ୱିଗୁଣ new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        ଯଦି (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            ଯଦି (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ଯଦି (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                ଯଦି (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ସ୍ଥିର bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        ଯଦି (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            ଯଦି (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } ଅନ୍ୟଥା ଯଦି (!seat->pointer.focus) {
                Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_pointer = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            ଯଦି (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } ଅନ୍ୟଥା ଯଦି (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, ଦଶମିକ x, ଦଶମିକ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    ଯଦି (seat->pointer.wl_pointer) {
        ଯଦି (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ଅଚଳ wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            ଅଚଳ wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } ଅନ୍ୟଥା {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            ଯଦି (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ଖାଲି;
                update_grabs = true;
            }
            ଯଦି (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = ଖାଲି;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ସଂରଚନା zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, ଖାଲି,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ଅଚଳ wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            ଅଚଳ wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            ଯଦି (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        ଯଦି (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

ସ୍ଥିର bool Wayland_WarpMouseRelative(SDL_Window *window, ଦଶମିକ x, ଦଶମିକ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    ଯଦି (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            ଯଦି (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool Wayland_WarpMouseGlobal(ଦଶମିକ x, ଦଶମିକ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    ଯଦି (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            ଯଦି (wind) {
                SDL_Window *window = wind->sdlwindow;

                ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                ଅଚଳ SDL_FPoint p = { x, y };
                ଅଚଳ SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                ଯଦି (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    ଯଦି (!data->relative_pointer_manager) {
        ଫେରନ୍ତୁ SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    ଯଦି (!data->pointer_constraints) {
        ଫେରନ୍ତୁ SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, ଖାଲି);
    ଫେରନ୍ତୁ true;
}

/* Wayland doesn't support getting the true global cursor position, but it can
 * be faked well enough for what most applications use it for: querying the
 * global cursor coordinates and transforming them to the window-relative
 * coordinates manually.
 *
 * The global position is derived by taking the cursor position relative to the
 * toplevel window, and offsetting it by the origin of the output the window is
 * currently considered to be on. The cursor position and button state when the
 * cursor is outside an application window are unknown, but this gives 'correct'
 * coordinates when the window has focus, which is good enough for most
 * applications.
 */
ସ୍ଥିର SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(ଦଶମିକ *x, ଦଶମିକ *y)
{
    ଅଚଳ SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    ଯଦି (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } ଅନ୍ୟଥା {
        *x = 0.f;
        *y = 0.f;
    }

    ଫେରନ୍ତୁ result;
}

#ଯଦି 0  // TODO RECONNECT: See waylandvideo.c for more information!
ସ୍ଥିର ଶୂନ୍ୟ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    ଯଦି (cdata == ଖାଲି) {
        ଫେରନ୍ତୁ;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    ଯଦି (cdata->shm_data != ଖାଲି) {
        ଶୂନ୍ୟ *old_data_pointer = cdata->shm_data;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, ଖାଲି);
}

ଶୂନ୍ୟ Wayland_RecreateCursors(ଶୂନ୍ୟ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    ଯଦି (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ଖାଲି;
        vdata->ଅଙ୍କ_cursor_themes = 0;
    }

    ଯଦି (mouse == ଖାଲି) {
        ଫେରନ୍ତୁ;
    }

    ପାଇଁ (cursor = mouse->cursors; cursor != ଖାଲି; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    ଯଦି (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    ଯଦି (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        ଯଦି (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

ଶୂନ୍ୟ Wayland_InitMouse(SDL_VideoData *data)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->SetRelativeMouseMode = Wayland_SetRelativeMouseMode;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_HitTestResult r = SDL_HITTEST_NORMAL;
    ଯେତେବେଳେ (r <= SDL_HITTEST_RESIZE_ବାମ) {
        ବାଛ (r) {
        ସ୍ଥିତି SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ଶୀର୍ଷ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ଡାହାଣ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ବାମ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            ଭାଙ୍ଗ;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    ଯଦି (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

ଶୂନ୍ୟ Wayland_FiniMouse(SDL_VideoData *data)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ଖାଲି;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

ଶୂନ୍ୟ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

ଶୂନ୍ୟ Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ଅଚଳ Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

ଶୂନ୍ୟ Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ଅଚଳ Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    ଯଦି (pointer_focus) {
        ଯଦି (mouse->cursor_visible) {
            ଯଦି (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                ଅଚଳ SDL_HitTestResult rc = pointer_focus->hit_test_result;

                ଯଦି (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } ଅନ୍ୟଥା {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } ଅନ୍ୟଥା {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ଖାଲି);
            }
        } ଅନ୍ୟଥା {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ଖାଲି);
        }
    } ଅନ୍ୟଥା {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

ଶୂନ୍ୟ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    ଅଚଳ Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    ଯଦି (tool_focus) {
        ଯଦି (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ଅଚଳ bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            ଯଦି (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } ଅନ୍ୟଥା {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ଖାଲି);
            }
        } ଅନ୍ୟଥା {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ଖାଲି);
        }
    } ଅନ୍ୟଥା {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

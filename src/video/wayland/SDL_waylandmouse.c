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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ <errno.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"

#ಅನ್ತರ್ಭಾವ "wayland-cursor.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandshmbuffer.h"

#ಅನ್ತರ್ಭಾವ "cursor-shape-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-constraints-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "viewporter-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "pointer-warp-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "tablet-v2-client-protocol.h"

#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"

ಸ್ಥಿರ SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ಎಡ + 1];

ಸ್ಥಿರ bool Wayland_SetRelativeMouseMode(bool enabled);

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಪೂರ್ಣಾಙ್ಕ width;
    ಪೂರ್ಣಾಙ್ಕ height;
    ಸಂರಚನಾ wl_buffer *buffer;
} CustomCursorImage;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    // The base dimensions of the cursor.
    ಪೂರ್ಣಾಙ್ಕ width;
    ಪೂರ್ಣಾಙ್ಕ height;
    ಪೂರ್ಣಾಙ್ಕ hot_x;
    ಪೂರ್ಣಾಙ್ಕ hot_y;

    ಪೂರ್ಣಾಙ್ಕ images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಪೂರ್ಣಾಙ್ಕ size;
    ಸಂರಚನಾ wl_list ಗಂಟು;
    ಸಂರಚನಾ wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    SDL_SystemCursor id;
    ಸಂರಚನಾ wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

ಸಂರಚನಾ SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_frames;
    bool is_system_cursor;

    ಸಙ್ಘ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ dbus_cursor_size;
ಸ್ಥಿರ ವರ್ಣ *dbus_cursor_theme;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < vdata->ಅಂಕೆ_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->ಅಂಕೆ_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ರಿಕ್ತ;
}

#ifdef SDL_USE_LIBDBUS

#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_dbus.h"

#define CURSOR_ಗಂಟು        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_ಕೀಲಿ    "cursor-size"
#define CURSOR_THEME_ಕೀಲಿ   "cursor-theme"

ಸ್ಥಿರ DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ)
{
    ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = ರಿಕ್ತ;
    DBusMessage *ಸಂದೇಶ = dbus->message_new_method_call(CURSOR_ಗಂಟು,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    ಯದಿ (ಸಂದೇಶ) {
        ಯದಿ (dbus->message_append_args(ಸಂದೇಶ, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &ಕೀಲಿ, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, ಸಂದೇಶ, DBUS_TIMEOUT_USE_DEFAULT, ರಿಕ್ತ);
        }
        dbus->message_unref(ಸಂದೇಶ);
    }

    ಪ್ರತ್ಯಾಗಮ reply;
}

ಸ್ಥಿರ bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, ಪೂರ್ಣಾಙ್ಕ type, ಶೂನ್ಯ *ಮೌಲ್ಯ)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    ಯದಿ (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    ಯದಿ (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    ಯದಿ (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    dbus->message_iter_get_basic(&iter[2], ಮೌಲ್ಯ);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *ಸಂದೇಶ, ಶೂನ್ಯ *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    ಯದಿ (dbus->message_is_signal(ಸಂದೇಶ, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        ಧ್ರುವ ವರ್ಣ *namespace, *ಕೀಲಿ;

        dbus->message_iter_init(ಸಂದೇಶ, &signal_iter);
        // Check if the parameters are what we expect
        ಯದಿ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ಗಚ್ಛ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        ಯದಿ (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            ಗಚ್ಛ not_our_signal;
        }
        ಯದಿ (!dbus->message_iter_next(&signal_iter)) {
            ಗಚ್ಛ not_our_signal;
        }
        ಯದಿ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            ಗಚ್ಛ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &ಕೀಲಿ);
        ಯದಿ (SDL_strcmp(CURSOR_SIZE_ಕೀಲಿ, ಕೀಲಿ) == 0) {
            ಪೂರ್ಣಾಙ್ಕ new_cursor_size;

            ಯದಿ (!dbus->message_iter_next(&signal_iter)) {
                ಗಚ್ಛ not_our_signal;
            }
            ಯದಿ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ಗಚ್ಛ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            ಯದಿ (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                ಗಚ್ಛ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            ಯದಿ (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } ಅನ್ಯಥಾ ಯದಿ (SDL_strcmp(CURSOR_THEME_ಕೀಲಿ, ಕೀಲಿ) == 0) {
            ಧ್ರುವ ವರ್ಣ *new_cursor_theme = ರಿಕ್ತ;

            ಯದಿ (!dbus->message_iter_next(&signal_iter)) {
                ಗಚ್ಛ not_our_signal;
            }
            ಯದಿ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                ಗಚ್ಛ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            ಯದಿ (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                ಗಚ್ಛ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            ಯದಿ (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                ಯದಿ (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } ಅನ್ಯಥಾ {
                    dbus_cursor_theme = ರಿಕ್ತ;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } ಅನ್ಯಥಾ {
            ಗಚ್ಛ not_our_signal;
        }

        ಪ್ರತ್ಯಾಗಮ DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    ಪ್ರತ್ಯಾಗಮ DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    ಯದಿ (!dbus) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_ಕೀಲಿ))) {
        ಯದಿ (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    ಯದಿ ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_ಕೀಲಿ))) {
        ಧ್ರುವ ವರ್ಣ *temp = ರಿಕ್ತ;
        ಯದಿ (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            ಯದಿ (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    ಯದಿ (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ರಿಕ್ತ);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, ರಿಕ್ತ);
        dbus->connection_flush(dbus->session_conn);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DBusFinishCursorProperties(ಶೂನ್ಯ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ರಿಕ್ತ;
}

#endif

ಸ್ಥಿರ ಸಂರಚನಾ wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, ಪೂರ್ಣಾಙ್ಕ frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    ಯದಿ (data) {
        ಯದಿ (!data->is_system_cursor) {
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ರಿಕ್ತ;
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            ಪೂರ್ಣಾಙ್ಕ closest_area = 0;
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            ಪ್ರತ್ಯಾಗಮ closest ? closest->buffer : ರಿಕ್ತ;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ cursor_frame_done(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_callback *cb, uint32_t time);
ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

ಸ್ಥಿರ ಶೂನ್ಯ cursor_frame_done(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    ಯದಿ (!state->current_cursor) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    ಧ್ರುವ Uint64 now = SDL_GetTicks();
    ಧ್ರುವ Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    ಪೂರ್ಣಾಙ್ಕ next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    ಪ್ರತಿ (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->ಅಂಕೆ_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        ಯದಿ (!frames[next]) {
            ಭಙ್ಗ;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = ರಿಕ್ತ;

    // Don't queue another callback if this frame time is infinite.
    ಯದಿ (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    ಸಂರಚನಾ wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    ಯದಿ (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ಅನ್ಯಥಾ {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

ಶೂನ್ಯ Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, ಶೂನ್ಯ *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ಶೂನ್ಯ Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    ಯದಿ (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = ರಿಕ್ತ;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    ಯದಿ (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } ಅನ್ಯಥಾ {
        Wayland_CursorStateResetAnimationState(state);
    }
}

ಶೂನ್ಯ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    ಯದಿ (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    ಯದಿ (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    ಯದಿ (state->surface) {
        wl_surface_attach(state->surface, ರಿಕ್ತ, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ಸ್ಥಿರ Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, ಸಂರಚನಾ wl_cursor *cursor, ಪೂರ್ಣಾಙ್ಕ size)
{
    Wayland_CachedSystemCursor *cache = ರಿಕ್ತ;

    // Is this cursor already cached at the target scale?
    ಯದಿ (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = ರಿಕ್ತ;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, ಗಂಟು) {
            ಯದಿ (c->size == size) {
                cache = c;
                ಭಙ್ಗ;
            }
        }
    }

    ಯದಿ (!cache) {
        cache = SDL_calloc(1, ಪರಿಮಾಣ(Wayland_CachedSystemCursor) + (ಪರಿಮಾಣ(ಸಂರಚನಾ wl_buffer *) * cdata->ಅಂಕೆ_frames));

        cache->size = size;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < cdata->ಅಂಕೆ_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_ಸೇರಿಸು(&cdata->cursor_data.system.cursor_buffer_cache, &cache->ಗಂಟು);
    }

    ಪ್ರತ್ಯಾಗಮ cache;
}

ಸ್ಥಿರ bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, ಪೂರ್ಣಾಙ್ಕ *dst_size, ಪೂರ್ಣಾಙ್ಕ *hot_x, ಪೂರ್ಣಾಙ್ಕ *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    ಸಂರಚನಾ wl_cursor_theme *theme = ರಿಕ್ತ;
    ಧ್ರುವ ವರ್ಣ *css_name = "default";
    ಧ್ರುವ ವರ್ಣ *fallback_name = ರಿಕ್ತ;
    ದ್ವಿಗುಣ scale_factor = state->scale;
    ಪೂರ್ಣಾಙ್ಕ theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    ಯದಿ (theme_size <= 0) {
        ಧ್ರುವ ವರ್ಣ *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        ಯದಿ (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    ಯದಿ (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ scaled_size = (ಪೂರ್ಣಾಙ್ಕ)SDL_lround(theme_size * scale_factor);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < vdata->ಅಂಕೆ_cursor_themes; ++i) {
        ಯದಿ (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            ಭಙ್ಗ;
        }
    }
    ಯದಿ (!theme) {
        ಧ್ರುವ ವರ್ಣ *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                ಪರಿಮಾಣ(SDL_WaylandCursorTheme) * (vdata->ಅಂಕೆ_cursor_themes + 1));
        ಯದಿ (!new_cursor_themes) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        ಯದಿ (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->ಅಂಕೆ_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->ಅಂಕೆ_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    ಸಂರಚನಾ wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    ಯದಿ (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    ಯದಿ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    ಯದಿ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    ಯದಿ (!cursor) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // ... Set the cursor data, finally.
    cdata->ಅಂಕೆ_frames = cursor->image_ಎಣಿಕೆ_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    ಯದಿ (cursor->image_ಎಣಿಕೆ_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_ಎಣಿಕೆ_2, ಪರಿಮಾಣ(Uint32));

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < cursor->image_ಎಣಿಕೆ_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ surface_sort_callback(ಧ್ರುವ ಶೂನ್ಯ *a, ಧ್ರುವ ಶೂನ್ಯ *b)
{
    ಧ್ರುವ SDL_Surface *s1 = *(ಧ್ರುವ SDL_Surface **)a;
    ಧ್ರುವ SDL_Surface *s2 = *(ಧ್ರುವ SDL_Surface **)b;

    ಪ್ರತ್ಯಾಗಮ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ಪೂರ್ಣಾಙ್ಕ frame_ಎಣಿಕೆ, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, ಪರಿಮಾಣ(*cursor));
    ಯದಿ (!cursor) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_CursorData *data = ರಿಕ್ತ;
    Wayland_SHMPool *shm_pool = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ pool_size = 0;
    ಪೂರ್ಣಾಙ್ಕ max_images = 0;
    bool is_ರಾಶಿ = false;
    ಸಂರಚನಾ SurfaceArray
    {
        SDL_Surface **surfaces;
        ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ;
    } *surfaces = SDL_small_alloc(ಸಂರಚನಾ SurfaceArray, frame_ಎಣಿಕೆ, &is_ರಾಶಿ);
    ಯದಿ (!surfaces) {
        ಗಚ್ಛ failed;
    }
    SDL_memset(surfaces, 0, ಪರಿಮಾಣ(ಸಂರಚನಾ SurfaceArray) * frame_ಎಣಿಕೆ);

    // Calculate the total allocation size.
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame_ಎಣಿಕೆ; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].ಎಣಿಕೆ);
        ಯದಿ (!surfaces[i].surfaces) {
            ಗಚ್ಛ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].ಎಣಿಕೆ, ಪರಿಮಾಣ(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].ಎಣಿಕೆ);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < surfaces[i].ಎಣಿಕೆ; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, ಪರಿಮಾಣ(*data) + (ಪರಿಮಾಣ(CustomCursorImage) * max_images * frame_ಎಣಿಕೆ));
    ಯದಿ (!data) {
        ಗಚ್ಛ failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_ಎಣಿಕೆ, ಪರಿಮಾಣ(Uint32));
    ಯದಿ (!data->frame_durations_ms) {
        ಗಚ್ಛ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    ಯದಿ (!shm_pool) {
        ಗಚ್ಛ failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->ಅಂಕೆ_frames = frame_ಎಣಿಕೆ;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame_ಎಣಿಕೆ; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        ಯದಿ (data->total_duration_ms < SDL_MAX_UINT32) {
            ಯದಿ (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } ಅನ್ಯಥಾ {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ offset = i * max_images;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < surfaces[i].ಎಣಿಕೆ; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            ಯದಿ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                ಯದಿ (!surface) {
                    ಗಚ್ಛ failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            ಶೂನ್ಯ *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            ಯದಿ (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ರಾಶಿ);
    Wayland_ReleaseSHMPool(shm_pool);

    ಪ್ರತ್ಯಾಗಮ cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    ಯದಿ (data) {
        SDL_free(data->frame_durations_ms);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < data->cursor_data.custom.images_per_frame * frame_ಎಣಿಕೆ; ++i) {
            ಯದಿ (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    ಯದಿ (surfaces) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame_ಎಣಿಕೆ; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ರಾಶಿ);
    }

    SDL_free(cursor);

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    ಪ್ರತ್ಯಾಗಮ Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, ಪರಿಮಾಣ(*cursor));

    ಯದಿ (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, ಪರಿಮಾಣ(*cdata));
        ಯದಿ (!cdata) {
            SDL_free(cursor);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *Wayland_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಪ್ರತ್ಯಾಗಮ Wayland_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        ಯದಿ (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            ಯದಿ (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, ರಿಕ್ತ, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = ರಿಕ್ತ;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ಯದಿ (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                ಯದಿ (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, ರಿಕ್ತ, 0, 0);
                }

                tool->cursor_state.current_cursor = ರಿಕ್ತ;
            }
        }
    }

    ಯದಿ (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, ಗಂಟು) {
            SDL_free(c);
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < d->ಅಂಕೆ_frames * d->cursor_data.custom.images_per_frame; ++i) {
            ಯದಿ (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    ಯದಿ (!cursor) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Probably not a cursor we own
    ಯದಿ (!cursor->internal) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ಸ್ಥಿರ ಗಣನಾ wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    ವಿಕಲ್ಪ (id) {
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    ಪ್ರತ್ಯಾಗಮ shape;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Wayland_PointerObject
{
    ಸಙ್ಘ
    {
        ಸಂರಚನಾ wl_pointer *wl_pointer;
        ಸಂರಚನಾ zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, ಧ್ರುವ Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ dst_width = 0;
    ಪೂರ್ಣಾಙ್ಕ dst_height = 0;
    ಪೂರ್ಣಾಙ್ಕ hot_x;
    ಪೂರ್ಣಾಙ್ಕ hot_y;

    // Stop the frame callback for old animated cursors.
    ಯದಿ (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    ಯದಿ (cursor) {
        ಯದಿ (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            ಯದಿ (cursor_data->ಅಂಕೆ_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            ಪ್ರತ್ಯಾಗಮ;
        }

        ಯದಿ (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            ಯದಿ (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                ಯದಿ (state->surface) {
                    wl_surface_attach(state->surface, ರಿಕ್ತ, 0, 0);
                    wl_surface_commit(state->surface);

                    ಯದಿ (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, ರಿಕ್ತ, 0, 0);
                    } ಅನ್ಯಥಾ {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ರಿಕ್ತ, 0, 0);
                    }

                    ಯದಿ (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ರಿಕ್ತ;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ರಿಕ್ತ;
                }

                ಧ್ರುವ ಗಣನಾ wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                ಪ್ರತ್ಯಾಗಮ;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            ಯದಿ (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                ಪ್ರತ್ಯಾಗಮ;
            }

            dst_height = dst_width;
        } ಅನ್ಯಥಾ {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            ಯದಿ (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } ಅನ್ಯಥಾ {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((ಪೂರ್ಣಾಙ್ಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((ಪೂರ್ಣಾಙ್ಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (ಪೂರ್ಣಾಙ್ಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (ಪೂರ್ಣಾಙ್ಕ)SDL_lround((ದ್ವಿಗುಣ)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        ಯದಿ (!state->surface) {
            ಸಂರಚನಾ wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ಸಂರಚನಾ wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        ಯದಿ (state->scale != 1.0) {
            ಯದಿ (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } ಅನ್ಯಥಾ ಯದಿ (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ರಿಕ್ತ;
        }

        ಯದಿ (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } ಅನ್ಯಥಾ {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        ಯದಿ (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ಅನ್ಯಥಾ {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        ಯದಿ (cursor_data->ಅಂಕೆ_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } ಅನ್ಯಥಾ {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = ರಿಕ್ತ;

        ಯದಿ (state->surface) {
            wl_surface_attach(state->surface, ರಿಕ್ತ, 0, 0);
            wl_surface_commit(state->surface);
        }

        ಯದಿ (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, ರಿಕ್ತ, 0, 0);
        } ಅನ್ಯಥಾ {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ರಿಕ್ತ, 0, 0);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

ಶೂನ್ಯ Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    ಧ್ರುವ ದ್ವಿಗುಣ new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        ಯದಿ (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            ಯದಿ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ಯದಿ (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                ಯದಿ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ಸ್ಥಿರ bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        ಯದಿ (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            ಯದಿ (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } ಅನ್ಯಥಾ ಯದಿ (!seat->pointer.focus) {
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
            ಯದಿ (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } ಅನ್ಯಥಾ ಯದಿ (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    ಯದಿ (seat->pointer.wl_pointer) {
        ಯದಿ (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ಧ್ರುವ wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            ಧ್ರುವ wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } ಅನ್ಯಥಾ {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            ಯದಿ (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ರಿಕ್ತ;
                update_grabs = true;
            }
            ಯದಿ (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = ರಿಕ್ತ;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ಸಂರಚನಾ zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, ರಿಕ್ತ,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ಧ್ರುವ wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            ಧ್ರುವ wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            ಯದಿ (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        ಯದಿ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

ಸ್ಥಿರ bool Wayland_WarpMouseRelative(SDL_Window *window, ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    ಯದಿ (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            ಯದಿ (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool Wayland_WarpMouseGlobal(ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    ಯದಿ (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            ಯದಿ (wind) {
                SDL_Window *window = wind->sdlwindow;

                ಪೂರ್ಣಾಙ್ಕ abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                ಧ್ರುವ SDL_FPoint p = { x, y };
                ಧ್ರುವ SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                ಯದಿ (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    ಯದಿ (!data->relative_pointer_manager) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    ಯದಿ (!data->pointer_constraints) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, ರಿಕ್ತ);
    ಪ್ರತ್ಯಾಗಮ true;
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
ಸ್ಥಿರ SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(ಭಿನ್ನ *x, ಭಿನ್ನ *y)
{
    ಧ್ರುವ SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    ಯದಿ (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        ಪೂರ್ಣಾಙ್ಕ off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } ಅನ್ಯಥಾ {
        *x = 0.f;
        *y = 0.f;
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

#ಯದಿ 0  // TODO RECONNECT: See waylandvideo.c for more information!
ಸ್ಥಿರ ಶೂನ್ಯ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    ಯದಿ (cdata == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    ಯದಿ (cdata->shm_data != ರಿಕ್ತ) {
        ಶೂನ್ಯ *old_data_pointer = cdata->shm_data;
        ಪೂರ್ಣಾಙ್ಕ stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, ರಿಕ್ತ);
}

ಶೂನ್ಯ Wayland_RecreateCursors(ಶೂನ್ಯ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    ಯದಿ (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ರಿಕ್ತ;
        vdata->ಅಂಕೆ_cursor_themes = 0;
    }

    ಯದಿ (mouse == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಪ್ರತಿ (cursor = mouse->cursors; cursor != ರಿಕ್ತ; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    ಯದಿ (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    ಯದಿ (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        ಯದಿ (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

ಶೂನ್ಯ Wayland_InitMouse(SDL_VideoData *data)
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
    ಯಾವತ್ (r <= SDL_HITTEST_RESIZE_ಎಡ) {
        ವಿಕಲ್ಪ (r) {
        ಪಕ್ಷ SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ತುದಿ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಬಲ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಎಡ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            ಭಙ್ಗ;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    ಯದಿ (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

ಶೂನ್ಯ Wayland_FiniMouse(SDL_VideoData *data)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ರಿಕ್ತ;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

ಶೂನ್ಯ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

ಶೂನ್ಯ Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ಧ್ರುವ Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

ಶೂನ್ಯ Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ಧ್ರುವ Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    ಯದಿ (pointer_focus) {
        ಯದಿ (mouse->cursor_visible) {
            ಯದಿ (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                ಧ್ರುವ SDL_HitTestResult rc = pointer_focus->hit_test_result;

                ಯದಿ (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } ಅನ್ಯಥಾ {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } ಅನ್ಯಥಾ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ರಿಕ್ತ);
            }
        } ಅನ್ಯಥಾ {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ರಿಕ್ತ);
        }
    } ಅನ್ಯಥಾ {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

ಶೂನ್ಯ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    ಧ್ರುವ Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    ಯದಿ (tool_focus) {
        ಯದಿ (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ಧ್ರುವ bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            ಯದಿ (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } ಅನ್ಯಥಾ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ರಿಕ್ತ);
            }
        } ಅನ್ಯಥಾ {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ರಿಕ್ತ);
        }
    } ಅನ್ಯಥಾ {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

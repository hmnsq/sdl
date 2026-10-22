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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব <errno.h>

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../SDL_video_c.h"

#অন্তর্ভাব "../../core/unix/SDL_poll.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "../SDL_pixels_c.h"
#অন্তর্ভাব "SDL_waylandevents_c.h"

#অন্তর্ভাব "wayland-cursor.h"
#অন্তর্ভাব "SDL_waylandmouse.h"
#অন্তর্ভাব "SDL_waylandshmbuffer.h"

#অন্তর্ভাব "cursor-shape-v1-client-protocol.h"
#অন্তর্ভাব "pointer-constraints-unstable-v1-client-protocol.h"
#অন্তর্ভাব "viewporter-client-protocol.h"
#অন্তর্ভাব "pointer-warp-v1-client-protocol.h"
#অন্তর্ভাব "tablet-v2-client-protocol.h"

#অন্তর্ভাব "../../SDL_hints_c.h"

স্থির SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_বাম + 1];

স্থির bool Wayland_SetRelativeMouseMode(bool enabled);

প্রকারনির্দেশ সংরচনা
{
    পূর্ণাঙ্ক width;
    পূর্ণাঙ্ক height;
    সংরচনা wl_buffer *buffer;
} CustomCursorImage;

প্রকারনির্দেশ সংরচনা
{
    // The base dimensions of the cursor.
    পূর্ণাঙ্ক width;
    পূর্ণাঙ্ক height;
    পূর্ণাঙ্ক hot_x;
    পূর্ণাঙ্ক hot_y;

    পূর্ণাঙ্ক images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

প্রকারনির্দেশ সংরচনা
{
    পূর্ণাঙ্ক size;
    সংরচনা wl_list গ্রন্থি;
    সংরচনা wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

প্রকারনির্দেশ সংরচনা
{
    SDL_SystemCursor id;
    সংরচনা wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

সংরচনা SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    পূর্ণাঙ্ক অঙ্ক_frames;
    bool is_system_cursor;

    সঙ্ঘ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

স্থির পূর্ণাঙ্ক dbus_cursor_size;
স্থির বর্ণ *dbus_cursor_theme;

স্থির শূন্য Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < vdata->অঙ্ক_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->অঙ্ক_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = রিক্ত;
}

#ifdef SDL_USE_LIBDBUS

#অন্তর্ভাব "../../core/linux/SDL_dbus.h"

#define CURSOR_গ্রন্থি        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_চাবি    "cursor-size"
#define CURSOR_THEME_চাবি   "cursor-theme"

স্থির DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ধ্রুব বর্ণ *চাবি)
{
    স্থির ধ্রুব বর্ণ *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = রিক্ত;
    DBusMessage *বার্তা = dbus->message_new_method_call(CURSOR_গ্রন্থি,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    যদি (বার্তা) {
        যদি (dbus->message_append_args(বার্তা, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &চাবি, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, বার্তা, DBUS_TIMEOUT_USE_DEFAULT, রিক্ত);
        }
        dbus->message_unref(বার্তা);
    }

    প্রত্যাগম reply;
}

স্থির bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, পূর্ণাঙ্ক type, শূন্য *মান)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    যদি (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        প্রত্যাগম false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    যদি (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        প্রত্যাগম false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    যদি (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        প্রত্যাগম false;
    }

    dbus->message_iter_get_basic(&iter[2], মান);

    প্রত্যাগম true;
}

স্থির DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *বার্তা, শূন্য *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    যদি (dbus->message_is_signal(বার্তা, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        ধ্রুব বর্ণ *namespace, *চাবি;

        dbus->message_iter_init(বার্তা, &signal_iter);
        // Check if the parameters are what we expect
        যদি (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            গচ্ছ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        যদি (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            গচ্ছ not_our_signal;
        }
        যদি (!dbus->message_iter_next(&signal_iter)) {
            গচ্ছ not_our_signal;
        }
        যদি (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            গচ্ছ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &চাবি);
        যদি (SDL_strcmp(CURSOR_SIZE_চাবি, চাবি) == 0) {
            পূর্ণাঙ্ক new_cursor_size;

            যদি (!dbus->message_iter_next(&signal_iter)) {
                গচ্ছ not_our_signal;
            }
            যদি (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                গচ্ছ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            যদি (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                গচ্ছ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            যদি (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } অন্যথা যদি (SDL_strcmp(CURSOR_THEME_চাবি, চাবি) == 0) {
            ধ্রুব বর্ণ *new_cursor_theme = রিক্ত;

            যদি (!dbus->message_iter_next(&signal_iter)) {
                গচ্ছ not_our_signal;
            }
            যদি (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                গচ্ছ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            যদি (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                গচ্ছ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            যদি (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                যদি (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } অন্যথা {
                    dbus_cursor_theme = রিক্ত;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } অন্যথা {
            গচ্ছ not_our_signal;
        }

        প্রত্যাগম DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    প্রত্যাগম DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

স্থির শূন্য Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    যদি (!dbus) {
        প্রত্যাগম;
    }

    যদি ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_চাবি))) {
        যদি (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    যদি ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_চাবি))) {
        ধ্রুব বর্ণ *temp = রিক্ত;
        যদি (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            যদি (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    যদি (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            রিক্ত);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, রিক্ত);
        dbus->connection_flush(dbus->session_conn);
    }
}

স্থির শূন্য Wayland_DBusFinishCursorProperties(শূন্য)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = রিক্ত;
}

#endif

স্থির সংরচনা wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, পূর্ণাঙ্ক frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    যদি (data) {
        যদি (!data->is_system_cursor) {
            ধ্রুব পূর্ণাঙ্ক offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = রিক্ত;
            ধ্রুব পূর্ণাঙ্ক target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            পূর্ণাঙ্ক closest_area = 0;
            প্রতি (পূর্ণাঙ্ক i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            প্রত্যাগম closest ? closest->buffer : রিক্ত;
        } অন্যথা {
            প্রত্যাগম ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    প্রত্যাগম রিক্ত;
}

স্থির শূন্য cursor_frame_done(শূন্য *data, সংরচনা wl_callback *cb, uint32_t time);
স্থির ধ্রুব সংরচনা wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

স্থির শূন্য cursor_frame_done(শূন্য *data, সংরচনা wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    যদি (!state->current_cursor) {
        প্রত্যাগম;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    ধ্রুব Uint64 now = SDL_GetTicks();
    ধ্রুব Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    পূর্ণাঙ্ক next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    প্রতি (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->অঙ্ক_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        যদি (!frames[next]) {
            ভঙ্গ;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = রিক্ত;

    // Don't queue another callback if this frame time is infinite.
    যদি (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    সংরচনা wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    যদি (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } অন্যথা {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

শূন্য Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, শূন্য *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

শূন্য Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    যদি (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = রিক্ত;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

স্থির শূন্য Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

স্থির শূন্য Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    যদি (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } অন্যথা {
        Wayland_CursorStateResetAnimationState(state);
    }
}

শূন্য Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    যদি (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    যদি (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    যদি (state->surface) {
        wl_surface_attach(state->surface, রিক্ত, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

স্থির Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, সংরচনা wl_cursor *cursor, পূর্ণাঙ্ক size)
{
    Wayland_CachedSystemCursor *cache = রিক্ত;

    // Is this cursor already cached at the target scale?
    যদি (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = রিক্ত;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, গ্রন্থি) {
            যদি (c->size == size) {
                cache = c;
                ভঙ্গ;
            }
        }
    }

    যদি (!cache) {
        cache = SDL_calloc(1, পরিমাণ(Wayland_CachedSystemCursor) + (পরিমাণ(সংরচনা wl_buffer *) * cdata->অঙ্ক_frames));

        cache->size = size;
        প্রতি (পূর্ণাঙ্ক i = 0; i < cdata->অঙ্ক_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_ঢোকাও(&cdata->cursor_data.system.cursor_buffer_cache, &cache->গ্রন্থি);
    }

    প্রত্যাগম cache;
}

স্থির bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, পূর্ণাঙ্ক *dst_size, পূর্ণাঙ্ক *hot_x, পূর্ণাঙ্ক *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    সংরচনা wl_cursor_theme *theme = রিক্ত;
    ধ্রুব বর্ণ *css_name = "default";
    ধ্রুব বর্ণ *fallback_name = রিক্ত;
    দ্বিগুণ scale_factor = state->scale;
    পূর্ণাঙ্ক theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    যদি (theme_size <= 0) {
        ধ্রুব বর্ণ *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        যদি (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    যদি (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ধ্রুব পূর্ণাঙ্ক scaled_size = (পূর্ণাঙ্ক)SDL_lround(theme_size * scale_factor);
    প্রতি (পূর্ণাঙ্ক i = 0; i < vdata->অঙ্ক_cursor_themes; ++i) {
        যদি (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            ভঙ্গ;
        }
    }
    যদি (!theme) {
        ধ্রুব বর্ণ *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                পরিমাণ(SDL_WaylandCursorTheme) * (vdata->অঙ্ক_cursor_themes + 1));
        যদি (!new_cursor_themes) {
            প্রত্যাগম false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        যদি (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->অঙ্ক_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->অঙ্ক_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    সংরচনা wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    যদি (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    যদি (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    যদি (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    যদি (!cursor) {
        প্রত্যাগম false;
    }

    // ... Set the cursor data, finally.
    cdata->অঙ্ক_frames = cursor->image_গুনতি_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    যদি (cursor->image_গুনতি_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_গুনতি_2, পরিমাণ(Uint32));

        প্রতি (পূর্ণাঙ্ক i = 0; i < cursor->image_গুনতি_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    প্রত্যাগম true;
}

স্থির পূর্ণাঙ্ক surface_sort_callback(ধ্রুব শূন্য *a, ধ্রুব শূন্য *b)
{
    ধ্রুব SDL_Surface *s1 = *(ধ্রুব SDL_Surface **)a;
    ধ্রুব SDL_Surface *s2 = *(ধ্রুব SDL_Surface **)b;

    প্রত্যাগম (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

স্থির SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, পূর্ণাঙ্ক frame_গুনতি, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, পরিমাণ(*cursor));
    যদি (!cursor) {
        প্রত্যাগম রিক্ত;
    }

    SDL_CursorData *data = রিক্ত;
    Wayland_SHMPool *shm_pool = রিক্ত;
    পূর্ণাঙ্ক pool_size = 0;
    পূর্ণাঙ্ক max_images = 0;
    bool is_স্তূপ = false;
    সংরচনা SurfaceArray
    {
        SDL_Surface **surfaces;
        পূর্ণাঙ্ক গুনতি;
    } *surfaces = SDL_small_alloc(সংরচনা SurfaceArray, frame_গুনতি, &is_স্তূপ);
    যদি (!surfaces) {
        গচ্ছ failed;
    }
    SDL_memset(surfaces, 0, পরিমাণ(সংরচনা SurfaceArray) * frame_গুনতি);

    // Calculate the total allocation size.
    প্রতি (পূর্ণাঙ্ক i = 0; i < frame_গুনতি; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].গুনতি);
        যদি (!surfaces[i].surfaces) {
            গচ্ছ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].গুনতি, পরিমাণ(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].গুনতি);
        প্রতি (পূর্ণাঙ্ক j = 0; j < surfaces[i].গুনতি; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, পরিমাণ(*data) + (পরিমাণ(CustomCursorImage) * max_images * frame_গুনতি));
    যদি (!data) {
        গচ্ছ failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_গুনতি, পরিমাণ(Uint32));
    যদি (!data->frame_durations_ms) {
        গচ্ছ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    যদি (!shm_pool) {
        গচ্ছ failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->অঙ্ক_frames = frame_গুনতি;

    প্রতি (পূর্ণাঙ্ক i = 0; i < frame_গুনতি; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        যদি (data->total_duration_ms < SDL_MAX_UINT32) {
            যদি (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } অন্যথা {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        ধ্রুব পূর্ণাঙ্ক offset = i * max_images;
        প্রতি (পূর্ণাঙ্ক j = 0; j < surfaces[i].গুনতি; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            যদি (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                যদি (!surface) {
                    গচ্ছ failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            শূন্য *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            যদি (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_স্তূপ);
    Wayland_ReleaseSHMPool(shm_pool);

    প্রত্যাগম cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    যদি (data) {
        SDL_free(data->frame_durations_ms);
        প্রতি (পূর্ণাঙ্ক i = 0; i < data->cursor_data.custom.images_per_frame * frame_গুনতি; ++i) {
            যদি (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    যদি (surfaces) {
        প্রতি (পূর্ণাঙ্ক i = 0; i < frame_গুনতি; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_স্তূপ);
    }

    SDL_free(cursor);

    প্রত্যাগম রিক্ত;
}

স্থির SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    প্রত্যাগম Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

স্থির SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, পরিমাণ(*cursor));

    যদি (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, পরিমাণ(*cdata));
        যদি (!cdata) {
            SDL_free(cursor);
            প্রত্যাগম রিক্ত;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    প্রত্যাগম cursor;
}

স্থির SDL_Cursor *Wayland_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    প্রত্যাগম Wayland_CreateSystemCursor(id);
}

স্থির শূন্য Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        যদি (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            যদি (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, রিক্ত, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = রিক্ত;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            যদি (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                যদি (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, রিক্ত, 0, 0);
                }

                tool->cursor_state.current_cursor = রিক্ত;
            }
        }
    }

    যদি (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, গ্রন্থি) {
            SDL_free(c);
        }
    } অন্যথা {
        প্রতি (পূর্ণাঙ্ক i = 0; i < d->অঙ্ক_frames * d->cursor_data.custom.images_per_frame; ++i) {
            যদি (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

স্থির শূন্য Wayland_FreeCursor(SDL_Cursor *cursor)
{
    যদি (!cursor) {
        প্রত্যাগম;
    }

    // Probably not a cursor we own
    যদি (!cursor->internal) {
        প্রত্যাগম;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

স্থির গণনা wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    বিকল্প (id) {
    পক্ষ SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        ভঙ্গ;
    স্বভাব:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    প্রত্যাগম shape;
}

প্রকারনির্দেশ সংরচনা Wayland_PointerObject
{
    সঙ্ঘ
    {
        সংরচনা wl_pointer *wl_pointer;
        সংরচনা zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

স্থির শূন্য Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, ধ্রুব Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : রিক্ত;
    পূর্ণাঙ্ক dst_width = 0;
    পূর্ণাঙ্ক dst_height = 0;
    পূর্ণাঙ্ক hot_x;
    পূর্ণাঙ্ক hot_y;

    // Stop the frame callback for old animated cursors.
    যদি (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    যদি (cursor) {
        যদি (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            যদি (cursor_data->অঙ্ক_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            প্রত্যাগম;
        }

        যদি (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            যদি (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                যদি (state->surface) {
                    wl_surface_attach(state->surface, রিক্ত, 0, 0);
                    wl_surface_commit(state->surface);

                    যদি (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, রিক্ত, 0, 0);
                    } অন্যথা {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, রিক্ত, 0, 0);
                    }

                    যদি (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = রিক্ত;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = রিক্ত;
                }

                ধ্রুব গণনা wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                প্রত্যাগম;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            যদি (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                প্রত্যাগম;
            }

            dst_height = dst_width;
        } অন্যথা {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            যদি (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } অন্যথা {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((পূর্ণাঙ্ক)SDL_lround((দ্বিগুণ)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((পূর্ণাঙ্ক)SDL_lround((দ্বিগুণ)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (পূর্ণাঙ্ক)SDL_lround((দ্বিগুণ)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (পূর্ণাঙ্ক)SDL_lround((দ্বিগুণ)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        যদি (!state->surface) {
            সংরচনা wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        সংরচনা wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        যদি (state->scale != 1.0) {
            যদি (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } অন্যথা যদি (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = রিক্ত;
        }

        যদি (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } অন্যথা {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        যদি (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } অন্যথা {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        যদি (cursor_data->অঙ্ক_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } অন্যথা {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = রিক্ত;

        যদি (state->surface) {
            wl_surface_attach(state->surface, রিক্ত, 0, 0);
            wl_surface_commit(state->surface);
        }

        যদি (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, রিক্ত, 0, 0);
        } অন্যথা {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, রিক্ত, 0, 0);
        }
    }
}

স্থির শূন্য Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

শূন্য Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    ধ্রুব দ্বিগুণ new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        যদি (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            যদি (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            যদি (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                যদি (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

স্থির bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        যদি (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            যদি (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } অন্যথা যদি (!seat->pointer.focus) {
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
            যদি (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } অন্যথা যদি (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    প্রত্যাগম true;
}

শূন্য Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, ভিন্ন x, ভিন্ন y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    যদি (seat->pointer.wl_pointer) {
        যদি (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ধ্রুব wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            ধ্রুব wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } অন্যথা {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            যদি (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = রিক্ত;
                update_grabs = true;
            }
            যদি (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = রিক্ত;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            সংরচনা zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, রিক্ত,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ধ্রুব wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            ধ্রুব wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            যদি (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        যদি (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

স্থির bool Wayland_WarpMouseRelative(SDL_Window *window, ভিন্ন x, ভিন্ন y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    যদি (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            যদি (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } অন্যথা {
        প্রত্যাগম SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    প্রত্যাগম true;
}

স্থির bool Wayland_WarpMouseGlobal(ভিন্ন x, ভিন্ন y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    যদি (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            যদি (wind) {
                SDL_Window *window = wind->sdlwindow;

                পূর্ণাঙ্ক abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                ধ্রুব SDL_FPoint p = { x, y };
                ধ্রুব SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                যদি (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } অন্যথা {
        প্রত্যাগম SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    প্রত্যাগম true;
}

স্থির bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    যদি (!data->relative_pointer_manager) {
        প্রত্যাগম SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    যদি (!data->pointer_constraints) {
        প্রত্যাগম SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, রিক্ত);
    প্রত্যাগম true;
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
স্থির SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(ভিন্ন *x, ভিন্ন *y)
{
    ধ্রুব SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    যদি (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        পূর্ণাঙ্ক off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } অন্যথা {
        *x = 0.f;
        *y = 0.f;
    }

    প্রত্যাগম result;
}

#যদি 0  // TODO RECONNECT: See waylandvideo.c for more information!
স্থির শূন্য Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    যদি (cdata == রিক্ত) {
        প্রত্যাগম;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    যদি (cdata->shm_data != রিক্ত) {
        শূন্য *old_data_pointer = cdata->shm_data;
        পূর্ণাঙ্ক stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, রিক্ত);
}

শূন্য Wayland_RecreateCursors(শূন্য)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    যদি (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = রিক্ত;
        vdata->অঙ্ক_cursor_themes = 0;
    }

    যদি (mouse == রিক্ত) {
        প্রত্যাগম;
    }

    প্রতি (cursor = mouse->cursors; cursor != রিক্ত; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    যদি (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    যদি (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        যদি (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

শূন্য Wayland_InitMouse(SDL_VideoData *data)
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
    যাবত্ (r <= SDL_HITTEST_RESIZE_বাম) {
        বিকল্প (r) {
        পক্ষ SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_শীর্ষ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_ডান:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_বাম:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            ভঙ্গ;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    যদি (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

শূন্য Wayland_FiniMouse(SDL_VideoData *data)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = রিক্ত;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

শূন্য Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

শূন্য Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ধ্রুব Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

শূন্য Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ধ্রুব Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    যদি (pointer_focus) {
        যদি (mouse->cursor_visible) {
            যদি (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                ধ্রুব SDL_HitTestResult rc = pointer_focus->hit_test_result;

                যদি (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } অন্যথা {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } অন্যথা {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, রিক্ত);
            }
        } অন্যথা {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, রিক্ত);
        }
    } অন্যথা {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

শূন্য Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    ধ্রুব Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    যদি (tool_focus) {
        যদি (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ধ্রুব bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            যদি (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } অন্যথা {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, রিক্ত);
            }
        } অন্যথা {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, রিক্ত);
        }
    } অন্যথা {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#અન્તર્ભાવ <errno.h>

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../SDL_video_c.h"

#અન્તર્ભાવ "../../core/unix/SDL_poll.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "../SDL_pixels_c.h"
#અન્તર્ભાવ "SDL_waylandevents_c.h"

#અન્તર્ભાવ "wayland-cursor.h"
#અન્તર્ભાવ "SDL_waylandmouse.h"
#અન્તર્ભાવ "SDL_waylandshmbuffer.h"

#અન્તર્ભાવ "cursor-shape-v1-client-protocol.h"
#અન્તર્ભાવ "pointer-constraints-unstable-v1-client-protocol.h"
#અન્તર્ભાવ "viewporter-client-protocol.h"
#અન્તર્ભાવ "pointer-warp-v1-client-protocol.h"
#અન્તર્ભાવ "tablet-v2-client-protocol.h"

#અન્તર્ભાવ "../../SDL_hints_c.h"

સ્થિર SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ડાબું + 1];

સ્થિર bool Wayland_SetRelativeMouseMode(bool enabled);

પ્રકારવ્યાખ્યા સંરચના
{
    પૂર્ણાંક width;
    પૂર્ણાંક height;
    સંરચના wl_buffer *buffer;
} CustomCursorImage;

પ્રકારવ્યાખ્યા સંરચના
{
    // The base dimensions of the cursor.
    પૂર્ણાંક width;
    પૂર્ણાંક height;
    પૂર્ણાંક hot_x;
    પૂર્ણાંક hot_y;

    પૂર્ણાંક images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

પ્રકારવ્યાખ્યા સંરચના
{
    પૂર્ણાંક size;
    સંરચના wl_list ગાંઠ;
    સંરચના wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

પ્રકારવ્યાખ્યા સંરચના
{
    SDL_SystemCursor id;
    સંરચના wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

સંરચના SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    પૂર્ણાંક અંક_frames;
    bool is_system_cursor;

    સંઘ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

સ્થિર પૂર્ણાંક dbus_cursor_size;
સ્થિર અક્ષર *dbus_cursor_theme;

સ્થિર શૂન્ય Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    માટે (પૂર્ણાંક i = 0; i < vdata->અંક_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->અંક_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ખાલી;
}

#ifdef SDL_USE_LIBDBUS

#અન્તર્ભાવ "../../core/linux/SDL_dbus.h"

#define CURSOR_ગાંઠ        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_ચાવી    "cursor-size"
#define CURSOR_THEME_ચાવી   "cursor-theme"

સ્થિર DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, અચલ અક્ષર *ચાવી)
{
    સ્થિર અચલ અક્ષર *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = ખાલી;
    DBusMessage *સંદેશ = dbus->message_new_method_call(CURSOR_ગાંઠ,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    જો (સંદેશ) {
        જો (dbus->message_append_args(સંદેશ, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &ચાવી, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, સંદેશ, DBUS_TIMEOUT_USE_DEFAULT, ખાલી);
        }
        dbus->message_unref(સંદેશ);
    }

    પાછા reply;
}

સ્થિર bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, પૂર્ણાંક type, શૂન્ય *કિંમત)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    જો (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        પાછા false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    જો (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        પાછા false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    જો (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        પાછા false;
    }

    dbus->message_iter_get_basic(&iter[2], કિંમત);

    પાછા true;
}

સ્થિર DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *સંદેશ, શૂન્ય *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    જો (dbus->message_is_signal(સંદેશ, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        અચલ અક્ષર *namespace, *ચાવી;

        dbus->message_iter_init(સંદેશ, &signal_iter);
        // Check if the parameters are what we expect
        જો (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            જાઓ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        જો (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            જાઓ not_our_signal;
        }
        જો (!dbus->message_iter_next(&signal_iter)) {
            જાઓ not_our_signal;
        }
        જો (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            જાઓ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &ચાવી);
        જો (SDL_strcmp(CURSOR_SIZE_ચાવી, ચાવી) == 0) {
            પૂર્ણાંક new_cursor_size;

            જો (!dbus->message_iter_next(&signal_iter)) {
                જાઓ not_our_signal;
            }
            જો (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                જાઓ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            જો (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                જાઓ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            જો (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } નહીંતર જો (SDL_strcmp(CURSOR_THEME_ચાવી, ચાવી) == 0) {
            અચલ અક્ષર *new_cursor_theme = ખાલી;

            જો (!dbus->message_iter_next(&signal_iter)) {
                જાઓ not_our_signal;
            }
            જો (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                જાઓ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            જો (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                જાઓ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            જો (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                જો (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } નહીંતર {
                    dbus_cursor_theme = ખાલી;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } નહીંતર {
            જાઓ not_our_signal;
        }

        પાછા DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    પાછા DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

સ્થિર શૂન્ય Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    જો (!dbus) {
        પાછા;
    }

    જો ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_ચાવી))) {
        જો (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    જો ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_ચાવી))) {
        અચલ અક્ષર *temp = ખાલી;
        જો (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            જો (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    જો (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ખાલી);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, ખાલી);
        dbus->connection_flush(dbus->session_conn);
    }
}

સ્થિર શૂન્ય Wayland_DBusFinishCursorProperties(શૂન્ય)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ખાલી;
}

#endif

સ્થિર સંરચના wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, પૂર્ણાંક frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    જો (data) {
        જો (!data->is_system_cursor) {
            અચલ પૂર્ણાંક offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ખાલી;
            અચલ પૂર્ણાંક target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            પૂર્ણાંક closest_area = 0;
            માટે (પૂર્ણાંક i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            પાછા closest ? closest->buffer : ખાલી;
        } નહીંતર {
            પાછા ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    પાછા ખાલી;
}

સ્થિર શૂન્ય cursor_frame_done(શૂન્ય *data, સંરચના wl_callback *cb, uint32_t time);
સ્થિર અચલ સંરચના wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

સ્થિર શૂન્ય cursor_frame_done(શૂન્ય *data, સંરચના wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    જો (!state->current_cursor) {
        પાછા;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    અચલ Uint64 now = SDL_GetTicks();
    અચલ Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    પૂર્ણાંક next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    માટે (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->અંક_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        જો (!frames[next]) {
            તોડો;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = ખાલી;

    // Don't queue another callback if this frame time is infinite.
    જો (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    સંરચના wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    જો (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } નહીંતર {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

શૂન્ય Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, શૂન્ય *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

શૂન્ય Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    જો (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = ખાલી;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

સ્થિર શૂન્ય Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

સ્થિર શૂન્ય Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    જો (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } નહીંતર {
        Wayland_CursorStateResetAnimationState(state);
    }
}

શૂન્ય Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    જો (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    જો (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    જો (state->surface) {
        wl_surface_attach(state->surface, ખાલી, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

સ્થિર Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, સંરચના wl_cursor *cursor, પૂર્ણાંક size)
{
    Wayland_CachedSystemCursor *cache = ખાલી;

    // Is this cursor already cached at the target scale?
    જો (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = ખાલી;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, ગાંઠ) {
            જો (c->size == size) {
                cache = c;
                તોડો;
            }
        }
    }

    જો (!cache) {
        cache = SDL_calloc(1, કદ(Wayland_CachedSystemCursor) + (કદ(સંરચના wl_buffer *) * cdata->અંક_frames));

        cache->size = size;
        માટે (પૂર્ણાંક i = 0; i < cdata->અંક_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_ઉમેરો(&cdata->cursor_data.system.cursor_buffer_cache, &cache->ગાંઠ);
    }

    પાછા cache;
}

સ્થિર bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, પૂર્ણાંક *dst_size, પૂર્ણાંક *hot_x, પૂર્ણાંક *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    સંરચના wl_cursor_theme *theme = ખાલી;
    અચલ અક્ષર *css_name = "default";
    અચલ અક્ષર *fallback_name = ખાલી;
    દ્વિગુણ scale_factor = state->scale;
    પૂર્ણાંક theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    જો (theme_size <= 0) {
        અચલ અક્ષર *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        જો (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    જો (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    અચલ પૂર્ણાંક scaled_size = (પૂર્ણાંક)SDL_lround(theme_size * scale_factor);
    માટે (પૂર્ણાંક i = 0; i < vdata->અંક_cursor_themes; ++i) {
        જો (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            તોડો;
        }
    }
    જો (!theme) {
        અચલ અક્ષર *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                કદ(SDL_WaylandCursorTheme) * (vdata->અંક_cursor_themes + 1));
        જો (!new_cursor_themes) {
            પાછા false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        જો (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->અંક_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->અંક_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    સંરચના wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    જો (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    જો (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    જો (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    જો (!cursor) {
        પાછા false;
    }

    // ... Set the cursor data, finally.
    cdata->અંક_frames = cursor->image_ગણતરી_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    જો (cursor->image_ગણતરી_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_ગણતરી_2, કદ(Uint32));

        માટે (પૂર્ણાંક i = 0; i < cursor->image_ગણતરી_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    પાછા true;
}

સ્થિર પૂર્ણાંક surface_sort_callback(અચલ શૂન્ય *a, અચલ શૂન્ય *b)
{
    અચલ SDL_Surface *s1 = *(અચલ SDL_Surface **)a;
    અચલ SDL_Surface *s2 = *(અચલ SDL_Surface **)b;

    પાછા (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

સ્થિર SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, પૂર્ણાંક frame_ગણતરી, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, કદ(*cursor));
    જો (!cursor) {
        પાછા ખાલી;
    }

    SDL_CursorData *data = ખાલી;
    Wayland_SHMPool *shm_pool = ખાલી;
    પૂર્ણાંક pool_size = 0;
    પૂર્ણાંક max_images = 0;
    bool is_ઢગલો = false;
    સંરચના SurfaceArray
    {
        SDL_Surface **surfaces;
        પૂર્ણાંક ગણતરી;
    } *surfaces = SDL_small_alloc(સંરચના SurfaceArray, frame_ગણતરી, &is_ઢગલો);
    જો (!surfaces) {
        જાઓ failed;
    }
    SDL_memset(surfaces, 0, કદ(સંરચના SurfaceArray) * frame_ગણતરી);

    // Calculate the total allocation size.
    માટે (પૂર્ણાંક i = 0; i < frame_ગણતરી; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].ગણતરી);
        જો (!surfaces[i].surfaces) {
            જાઓ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].ગણતરી, કદ(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].ગણતરી);
        માટે (પૂર્ણાંક j = 0; j < surfaces[i].ગણતરી; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, કદ(*data) + (કદ(CustomCursorImage) * max_images * frame_ગણતરી));
    જો (!data) {
        જાઓ failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_ગણતરી, કદ(Uint32));
    જો (!data->frame_durations_ms) {
        જાઓ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    જો (!shm_pool) {
        જાઓ failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->અંક_frames = frame_ગણતરી;

    માટે (પૂર્ણાંક i = 0; i < frame_ગણતરી; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        જો (data->total_duration_ms < SDL_MAX_UINT32) {
            જો (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } નહીંતર {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        અચલ પૂર્ણાંક offset = i * max_images;
        માટે (પૂર્ણાંક j = 0; j < surfaces[i].ગણતરી; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            જો (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                જો (!surface) {
                    જાઓ failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            શૂન્ય *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            જો (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ઢગલો);
    Wayland_ReleaseSHMPool(shm_pool);

    પાછા cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    જો (data) {
        SDL_free(data->frame_durations_ms);
        માટે (પૂર્ણાંક i = 0; i < data->cursor_data.custom.images_per_frame * frame_ગણતરી; ++i) {
            જો (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    જો (surfaces) {
        માટે (પૂર્ણાંક i = 0; i < frame_ગણતરી; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ઢગલો);
    }

    SDL_free(cursor);

    પાછા ખાલી;
}

સ્થિર SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    પાછા Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

સ્થિર SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, કદ(*cursor));

    જો (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, કદ(*cdata));
        જો (!cdata) {
            SDL_free(cursor);
            પાછા ખાલી;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    પાછા cursor;
}

સ્થિર SDL_Cursor *Wayland_CreateDefaultCursor(શૂન્ય)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    પાછા Wayland_CreateSystemCursor(id);
}

સ્થિર શૂન્ય Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        જો (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            જો (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, ખાલી, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = ખાલી;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            જો (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                જો (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, ખાલી, 0, 0);
                }

                tool->cursor_state.current_cursor = ખાલી;
            }
        }
    }

    જો (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, ગાંઠ) {
            SDL_free(c);
        }
    } નહીંતર {
        માટે (પૂર્ણાંક i = 0; i < d->અંક_frames * d->cursor_data.custom.images_per_frame; ++i) {
            જો (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

સ્થિર શૂન્ય Wayland_FreeCursor(SDL_Cursor *cursor)
{
    જો (!cursor) {
        પાછા;
    }

    // Probably not a cursor we own
    જો (!cursor->internal) {
        પાછા;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

સ્થિર ગણના wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    પસંદગી (id) {
    સ્થિતિ SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        તોડો;
    મૂળભૂત:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    પાછા shape;
}

પ્રકારવ્યાખ્યા સંરચના Wayland_PointerObject
{
    સંઘ
    {
        સંરચના wl_pointer *wl_pointer;
        સંરચના zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

સ્થિર શૂન્ય Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, અચલ Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : ખાલી;
    પૂર્ણાંક dst_width = 0;
    પૂર્ણાંક dst_height = 0;
    પૂર્ણાંક hot_x;
    પૂર્ણાંક hot_y;

    // Stop the frame callback for old animated cursors.
    જો (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    જો (cursor) {
        જો (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            જો (cursor_data->અંક_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            પાછા;
        }

        જો (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            જો (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                જો (state->surface) {
                    wl_surface_attach(state->surface, ખાલી, 0, 0);
                    wl_surface_commit(state->surface);

                    જો (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, ખાલી, 0, 0);
                    } નહીંતર {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ખાલી, 0, 0);
                    }

                    જો (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ખાલી;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ખાલી;
                }

                અચલ ગણના wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                પાછા;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            જો (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                પાછા;
            }

            dst_height = dst_width;
        } નહીંતર {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            જો (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } નહીંતર {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((પૂર્ણાંક)SDL_lround((દ્વિગુણ)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((પૂર્ણાંક)SDL_lround((દ્વિગુણ)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (પૂર્ણાંક)SDL_lround((દ્વિગુણ)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (પૂર્ણાંક)SDL_lround((દ્વિગુણ)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        જો (!state->surface) {
            સંરચના wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        સંરચના wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        જો (state->scale != 1.0) {
            જો (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } નહીંતર જો (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ખાલી;
        }

        જો (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } નહીંતર {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        જો (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } નહીંતર {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        જો (cursor_data->અંક_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } નહીંતર {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = ખાલી;

        જો (state->surface) {
            wl_surface_attach(state->surface, ખાલી, 0, 0);
            wl_surface_commit(state->surface);
        }

        જો (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, ખાલી, 0, 0);
        } નહીંતર {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ખાલી, 0, 0);
        }
    }
}

સ્થિર શૂન્ય Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

શૂન્ય Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    અચલ દ્વિગુણ new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        જો (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            જો (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            જો (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                જો (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

સ્થિર bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        જો (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            જો (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } નહીંતર જો (!seat->pointer.focus) {
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
            જો (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } નહીંતર જો (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    પાછા true;
}

શૂન્ય Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, દશાંશ x, દશાંશ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    જો (seat->pointer.wl_pointer) {
        જો (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            અચલ wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            અચલ wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } નહીંતર {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            જો (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ખાલી;
                update_grabs = true;
            }
            જો (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = ખાલી;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            સંરચના zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, ખાલી,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            અચલ wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            અચલ wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            જો (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        જો (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

સ્થિર bool Wayland_WarpMouseRelative(SDL_Window *window, દશાંશ x, દશાંશ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    જો (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            જો (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } નહીંતર {
        પાછા SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    પાછા true;
}

સ્થિર bool Wayland_WarpMouseGlobal(દશાંશ x, દશાંશ y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    જો (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            જો (wind) {
                SDL_Window *window = wind->sdlwindow;

                પૂર્ણાંક abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                અચલ SDL_FPoint p = { x, y };
                અચલ SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                જો (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } નહીંતર {
        પાછા SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    પાછા true;
}

સ્થિર bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    જો (!data->relative_pointer_manager) {
        પાછા SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    જો (!data->pointer_constraints) {
        પાછા SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, ખાલી);
    પાછા true;
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
સ્થિર SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(દશાંશ *x, દશાંશ *y)
{
    અચલ SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    જો (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        પૂર્ણાંક off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } નહીંતર {
        *x = 0.f;
        *y = 0.f;
    }

    પાછા result;
}

#જો 0  // TODO RECONNECT: See waylandvideo.c for more information!
સ્થિર શૂન્ય Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    જો (cdata == ખાલી) {
        પાછા;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    જો (cdata->shm_data != ખાલી) {
        શૂન્ય *old_data_pointer = cdata->shm_data;
        પૂર્ણાંક stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, ખાલી);
}

શૂન્ય Wayland_RecreateCursors(શૂન્ય)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    જો (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ખાલી;
        vdata->અંક_cursor_themes = 0;
    }

    જો (mouse == ખાલી) {
        પાછા;
    }

    માટે (cursor = mouse->cursors; cursor != ખાલી; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    જો (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    જો (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        જો (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

શૂન્ય Wayland_InitMouse(SDL_VideoData *data)
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
    જ્યારે (r <= SDL_HITTEST_RESIZE_ડાબું) {
        પસંદગી (r) {
        સ્થિતિ SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            તોડો;
        સ્થિતિ SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_ટોચ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_જમણું:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_ડાબું:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            તોડો;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    જો (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

શૂન્ય Wayland_FiniMouse(SDL_VideoData *data)
{
    માટે (પૂર્ણાંક i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ખાલી;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

શૂન્ય Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

શૂન્ય Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    અચલ Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

શૂન્ય Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    અચલ Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    જો (pointer_focus) {
        જો (mouse->cursor_visible) {
            જો (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                અચલ SDL_HitTestResult rc = pointer_focus->hit_test_result;

                જો (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } નહીંતર {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } નહીંતર {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ખાલી);
            }
        } નહીંતર {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ખાલી);
        }
    } નહીંતર {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

શૂન્ય Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    અચલ Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    જો (tool_focus) {
        જો (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            અચલ bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            જો (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } નહીંતર {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ખાલી);
            }
        } નહીંતર {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ખાલી);
        }
    } નહીંતર {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

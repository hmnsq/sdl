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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ <errno.h>

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../SDL_video_c.h"

#அந்தர்பாவ "../../core/unix/SDL_poll.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "../SDL_pixels_c.h"
#அந்தர்பாவ "SDL_waylandevents_c.h"

#அந்தர்பாவ "wayland-cursor.h"
#அந்தர்பாவ "SDL_waylandmouse.h"
#அந்தர்பாவ "SDL_waylandshmbuffer.h"

#அந்தர்பாவ "cursor-shape-v1-client-protocol.h"
#அந்தர்பாவ "pointer-constraints-unstable-v1-client-protocol.h"
#அந்தர்பாவ "viewporter-client-protocol.h"
#அந்தர்பாவ "pointer-warp-v1-client-protocol.h"
#அந்தர்பாவ "tablet-v2-client-protocol.h"

#அந்தர்பாவ "../../SDL_hints_c.h"

நிலையான SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_இடது + 1];

நிலையான bool Wayland_SetRelativeMouseMode(bool enabled);

வகைவரை கட்டமைப்பு
{
    முழு width;
    முழு height;
    கட்டமைப்பு wl_buffer *buffer;
} CustomCursorImage;

வகைவரை கட்டமைப்பு
{
    // The base dimensions of the cursor.
    முழு width;
    முழு height;
    முழு hot_x;
    முழு hot_y;

    முழு images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

வகைவரை கட்டமைப்பு
{
    முழு size;
    கட்டமைப்பு wl_list முனை;
    கட்டமைப்பு wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

வகைவரை கட்டமைப்பு
{
    SDL_SystemCursor id;
    கட்டமைப்பு wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

கட்டமைப்பு SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    முழு இலக்கம்_frames;
    bool is_system_cursor;

    ஒன்றிப்பு
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

நிலையான முழு dbus_cursor_size;
நிலையான எழுத்து *dbus_cursor_theme;

நிலையான வெறுமை Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    க்கு (முழு i = 0; i < vdata->இலக்கம்_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->இலக்கம்_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = வெற்று;
}

#ifdef SDL_USE_LIBDBUS

#அந்தர்பாவ "../../core/linux/SDL_dbus.h"

#define CURSOR_முனை        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_சாவி    "cursor-size"
#define CURSOR_THEME_சாவி   "cursor-theme"

நிலையான DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, மாறிலி எழுத்து *சாவி)
{
    நிலையான மாறிலி எழுத்து *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = வெற்று;
    DBusMessage *செய்தி = dbus->message_new_method_call(CURSOR_முனை,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    எனில் (செய்தி) {
        எனில் (dbus->message_append_args(செய்தி, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &சாவி, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, செய்தி, DBUS_TIMEOUT_USE_DEFAULT, வெற்று);
        }
        dbus->message_unref(செய்தி);
    }

    திரும்பு reply;
}

நிலையான bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, முழு type, வெறுமை *மதிப்பு)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    எனில் (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        திரும்பு false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    எனில் (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        திரும்பு false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    எனில் (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        திரும்பு false;
    }

    dbus->message_iter_get_basic(&iter[2], மதிப்பு);

    திரும்பு true;
}

நிலையான DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *செய்தி, வெறுமை *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    எனில் (dbus->message_is_signal(செய்தி, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        மாறிலி எழுத்து *namespace, *சாவி;

        dbus->message_iter_init(செய்தி, &signal_iter);
        // Check if the parameters are what we expect
        எனில் (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            செல் not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        எனில் (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            செல் not_our_signal;
        }
        எனில் (!dbus->message_iter_next(&signal_iter)) {
            செல் not_our_signal;
        }
        எனில் (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            செல் not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &சாவி);
        எனில் (SDL_strcmp(CURSOR_SIZE_சாவி, சாவி) == 0) {
            முழு new_cursor_size;

            எனில் (!dbus->message_iter_next(&signal_iter)) {
                செல் not_our_signal;
            }
            எனில் (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                செல் not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            எனில் (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                செல் not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            எனில் (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } இல்லையெனில் எனில் (SDL_strcmp(CURSOR_THEME_சாவி, சாவி) == 0) {
            மாறிலி எழுத்து *new_cursor_theme = வெற்று;

            எனில் (!dbus->message_iter_next(&signal_iter)) {
                செல் not_our_signal;
            }
            எனில் (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                செல் not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            எனில் (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                செல் not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            எனில் (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                எனில் (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } இல்லையெனில் {
                    dbus_cursor_theme = வெற்று;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } இல்லையெனில் {
            செல் not_our_signal;
        }

        திரும்பு DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    திரும்பு DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

நிலையான வெறுமை Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    எனில் (!dbus) {
        திரும்பு;
    }

    எனில் ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_சாவி))) {
        எனில் (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    எனில் ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_சாவி))) {
        மாறிலி எழுத்து *temp = வெற்று;
        எனில் (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            எனில் (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    எனில் (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            வெற்று);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, வெற்று);
        dbus->connection_flush(dbus->session_conn);
    }
}

நிலையான வெறுமை Wayland_DBusFinishCursorProperties(வெறுமை)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = வெற்று;
}

#endif

நிலையான கட்டமைப்பு wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, முழு frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    எனில் (data) {
        எனில் (!data->is_system_cursor) {
            மாறிலி முழு offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = வெற்று;
            மாறிலி முழு target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            முழு closest_area = 0;
            க்கு (முழு i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            திரும்பு closest ? closest->buffer : வெற்று;
        } இல்லையெனில் {
            திரும்பு ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    திரும்பு வெற்று;
}

நிலையான வெறுமை cursor_frame_done(வெறுமை *data, கட்டமைப்பு wl_callback *cb, uint32_t time);
நிலையான மாறிலி கட்டமைப்பு wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

நிலையான வெறுமை cursor_frame_done(வெறுமை *data, கட்டமைப்பு wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    எனில் (!state->current_cursor) {
        திரும்பு;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    மாறிலி Uint64 now = SDL_GetTicks();
    மாறிலி Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    முழு next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    க்கு (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->இலக்கம்_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        எனில் (!frames[next]) {
            நிறுத்து;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = வெற்று;

    // Don't queue another callback if this frame time is infinite.
    எனில் (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    கட்டமைப்பு wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    எனில் (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } இல்லையெனில் {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

வெறுமை Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, வெறுமை *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

வெறுமை Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    எனில் (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = வெற்று;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

நிலையான வெறுமை Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

நிலையான வெறுமை Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    எனில் (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } இல்லையெனில் {
        Wayland_CursorStateResetAnimationState(state);
    }
}

வெறுமை Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    எனில் (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    எனில் (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    எனில் (state->surface) {
        wl_surface_attach(state->surface, வெற்று, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

நிலையான Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, கட்டமைப்பு wl_cursor *cursor, முழு size)
{
    Wayland_CachedSystemCursor *cache = வெற்று;

    // Is this cursor already cached at the target scale?
    எனில் (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = வெற்று;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, முனை) {
            எனில் (c->size == size) {
                cache = c;
                நிறுத்து;
            }
        }
    }

    எனில் (!cache) {
        cache = SDL_calloc(1, அளவு(Wayland_CachedSystemCursor) + (அளவு(கட்டமைப்பு wl_buffer *) * cdata->இலக்கம்_frames));

        cache->size = size;
        க்கு (முழு i = 0; i < cdata->இலக்கம்_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_செருகு(&cdata->cursor_data.system.cursor_buffer_cache, &cache->முனை);
    }

    திரும்பு cache;
}

நிலையான bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, முழு *dst_size, முழு *hot_x, முழு *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    கட்டமைப்பு wl_cursor_theme *theme = வெற்று;
    மாறிலி எழுத்து *css_name = "default";
    மாறிலி எழுத்து *fallback_name = வெற்று;
    இரட்டை scale_factor = state->scale;
    முழு theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    எனில் (theme_size <= 0) {
        மாறிலி எழுத்து *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        எனில் (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    எனில் (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    மாறிலி முழு scaled_size = (முழு)SDL_lround(theme_size * scale_factor);
    க்கு (முழு i = 0; i < vdata->இலக்கம்_cursor_themes; ++i) {
        எனில் (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            நிறுத்து;
        }
    }
    எனில் (!theme) {
        மாறிலி எழுத்து *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                அளவு(SDL_WaylandCursorTheme) * (vdata->இலக்கம்_cursor_themes + 1));
        எனில் (!new_cursor_themes) {
            திரும்பு false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        எனில் (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->இலக்கம்_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->இலக்கம்_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    கட்டமைப்பு wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    எனில் (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    எனில் (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    எனில் (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    எனில் (!cursor) {
        திரும்பு false;
    }

    // ... Set the cursor data, finally.
    cdata->இலக்கம்_frames = cursor->image_மொத்தம்_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    எனில் (cursor->image_மொத்தம்_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_மொத்தம்_2, அளவு(Uint32));

        க்கு (முழு i = 0; i < cursor->image_மொத்தம்_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    திரும்பு true;
}

நிலையான முழு surface_sort_callback(மாறிலி வெறுமை *a, மாறிலி வெறுமை *b)
{
    மாறிலி SDL_Surface *s1 = *(மாறிலி SDL_Surface **)a;
    மாறிலி SDL_Surface *s2 = *(மாறிலி SDL_Surface **)b;

    திரும்பு (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

நிலையான SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, முழு frame_மொத்தம், முழு hot_x, முழு hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, அளவு(*cursor));
    எனில் (!cursor) {
        திரும்பு வெற்று;
    }

    SDL_CursorData *data = வெற்று;
    Wayland_SHMPool *shm_pool = வெற்று;
    முழு pool_size = 0;
    முழு max_images = 0;
    bool is_அடுக்கு = false;
    கட்டமைப்பு SurfaceArray
    {
        SDL_Surface **surfaces;
        முழு மொத்தம்;
    } *surfaces = SDL_small_alloc(கட்டமைப்பு SurfaceArray, frame_மொத்தம், &is_அடுக்கு);
    எனில் (!surfaces) {
        செல் failed;
    }
    SDL_memset(surfaces, 0, அளவு(கட்டமைப்பு SurfaceArray) * frame_மொத்தம்);

    // Calculate the total allocation size.
    க்கு (முழு i = 0; i < frame_மொத்தம்; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].மொத்தம்);
        எனில் (!surfaces[i].surfaces) {
            செல் failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].மொத்தம், அளவு(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].மொத்தம்);
        க்கு (முழு j = 0; j < surfaces[i].மொத்தம்; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, அளவு(*data) + (அளவு(CustomCursorImage) * max_images * frame_மொத்தம்));
    எனில் (!data) {
        செல் failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_மொத்தம், அளவு(Uint32));
    எனில் (!data->frame_durations_ms) {
        செல் failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    எனில் (!shm_pool) {
        செல் failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->இலக்கம்_frames = frame_மொத்தம்;

    க்கு (முழு i = 0; i < frame_மொத்தம்; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        எனில் (data->total_duration_ms < SDL_MAX_UINT32) {
            எனில் (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } இல்லையெனில் {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        மாறிலி முழு offset = i * max_images;
        க்கு (முழு j = 0; j < surfaces[i].மொத்தம்; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            எனில் (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                எனில் (!surface) {
                    செல் failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            வெறுமை *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            எனில் (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_அடுக்கு);
    Wayland_ReleaseSHMPool(shm_pool);

    திரும்பு cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    எனில் (data) {
        SDL_free(data->frame_durations_ms);
        க்கு (முழு i = 0; i < data->cursor_data.custom.images_per_frame * frame_மொத்தம்; ++i) {
            எனில் (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    எனில் (surfaces) {
        க்கு (முழு i = 0; i < frame_மொத்தம்; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_அடுக்கு);
    }

    SDL_free(cursor);

    திரும்பு வெற்று;
}

நிலையான SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    திரும்பு Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

நிலையான SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, அளவு(*cursor));

    எனில் (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, அளவு(*cdata));
        எனில் (!cdata) {
            SDL_free(cursor);
            திரும்பு வெற்று;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    திரும்பு cursor;
}

நிலையான SDL_Cursor *Wayland_CreateDefaultCursor(வெறுமை)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    திரும்பு Wayland_CreateSystemCursor(id);
}

நிலையான வெறுமை Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        எனில் (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            எனில் (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, வெற்று, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = வெற்று;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            எனில் (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                எனில் (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, வெற்று, 0, 0);
                }

                tool->cursor_state.current_cursor = வெற்று;
            }
        }
    }

    எனில் (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, முனை) {
            SDL_free(c);
        }
    } இல்லையெனில் {
        க்கு (முழு i = 0; i < d->இலக்கம்_frames * d->cursor_data.custom.images_per_frame; ++i) {
            எனில் (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

நிலையான வெறுமை Wayland_FreeCursor(SDL_Cursor *cursor)
{
    எனில் (!cursor) {
        திரும்பு;
    }

    // Probably not a cursor we own
    எனில் (!cursor->internal) {
        திரும்பு;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

நிலையான எண்ணிக்கை wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    தேர்வு (id) {
    நிலை SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        நிறுத்து;
    இயல்பு:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    திரும்பு shape;
}

வகைவரை கட்டமைப்பு Wayland_PointerObject
{
    ஒன்றிப்பு
    {
        கட்டமைப்பு wl_pointer *wl_pointer;
        கட்டமைப்பு zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

நிலையான வெறுமை Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, மாறிலி Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : வெற்று;
    முழு dst_width = 0;
    முழு dst_height = 0;
    முழு hot_x;
    முழு hot_y;

    // Stop the frame callback for old animated cursors.
    எனில் (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    எனில் (cursor) {
        எனில் (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            எனில் (cursor_data->இலக்கம்_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            திரும்பு;
        }

        எனில் (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            எனில் (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                எனில் (state->surface) {
                    wl_surface_attach(state->surface, வெற்று, 0, 0);
                    wl_surface_commit(state->surface);

                    எனில் (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, வெற்று, 0, 0);
                    } இல்லையெனில் {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, வெற்று, 0, 0);
                    }

                    எனில் (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = வெற்று;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = வெற்று;
                }

                மாறிலி எண்ணிக்கை wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                திரும்பு;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            எனில் (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                திரும்பு;
            }

            dst_height = dst_width;
        } இல்லையெனில் {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            எனில் (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } இல்லையெனில் {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((முழு)SDL_lround((இரட்டை)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((முழு)SDL_lround((இரட்டை)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (முழு)SDL_lround((இரட்டை)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (முழு)SDL_lround((இரட்டை)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        எனில் (!state->surface) {
            கட்டமைப்பு wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        கட்டமைப்பு wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        எனில் (state->scale != 1.0) {
            எனில் (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } இல்லையெனில் எனில் (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = வெற்று;
        }

        எனில் (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } இல்லையெனில் {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        எனில் (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } இல்லையெனில் {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        எனில் (cursor_data->இலக்கம்_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } இல்லையெனில் {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = வெற்று;

        எனில் (state->surface) {
            wl_surface_attach(state->surface, வெற்று, 0, 0);
            wl_surface_commit(state->surface);
        }

        எனில் (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, வெற்று, 0, 0);
        } இல்லையெனில் {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, வெற்று, 0, 0);
        }
    }
}

நிலையான வெறுமை Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

வெறுமை Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    மாறிலி இரட்டை new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        எனில் (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            எனில் (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            எனில் (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                எனில் (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

நிலையான bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        எனில் (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            எனில் (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } இல்லையெனில் எனில் (!seat->pointer.focus) {
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
            எனில் (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } இல்லையெனில் எனில் (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    திரும்பு true;
}

வெறுமை Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, தசம x, தசம y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    எனில் (seat->pointer.wl_pointer) {
        எனில் (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            மாறிலி wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            மாறிலி wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } இல்லையெனில் {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            எனில் (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = வெற்று;
                update_grabs = true;
            }
            எனில் (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = வெற்று;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            கட்டமைப்பு zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, வெற்று,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            மாறிலி wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            மாறிலி wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            எனில் (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        எனில் (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

நிலையான bool Wayland_WarpMouseRelative(SDL_Window *window, தசம x, தசம y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    எனில் (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            எனில் (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } இல்லையெனில் {
        திரும்பு SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    திரும்பு true;
}

நிலையான bool Wayland_WarpMouseGlobal(தசம x, தசம y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    எனில் (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            எனில் (wind) {
                SDL_Window *window = wind->sdlwindow;

                முழு abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                மாறிலி SDL_FPoint p = { x, y };
                மாறிலி SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                எனில் (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } இல்லையெனில் {
        திரும்பு SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    திரும்பு true;
}

நிலையான bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    எனில் (!data->relative_pointer_manager) {
        திரும்பு SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    எனில் (!data->pointer_constraints) {
        திரும்பு SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, வெற்று);
    திரும்பு true;
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
நிலையான SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(தசம *x, தசம *y)
{
    மாறிலி SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    எனில் (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        முழு off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } இல்லையெனில் {
        *x = 0.f;
        *y = 0.f;
    }

    திரும்பு result;
}

#எனில் 0  // TODO RECONNECT: See waylandvideo.c for more information!
நிலையான வெறுமை Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    எனில் (cdata == வெற்று) {
        திரும்பு;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    எனில் (cdata->shm_data != வெற்று) {
        வெறுமை *old_data_pointer = cdata->shm_data;
        முழு stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, வெற்று);
}

வெறுமை Wayland_RecreateCursors(வெறுமை)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    எனில் (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = வெற்று;
        vdata->இலக்கம்_cursor_themes = 0;
    }

    எனில் (mouse == வெற்று) {
        திரும்பு;
    }

    க்கு (cursor = mouse->cursors; cursor != வெற்று; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    எனில் (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    எனில் (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        எனில் (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

வெறுமை Wayland_InitMouse(SDL_VideoData *data)
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
    போது (r <= SDL_HITTEST_RESIZE_இடது) {
        தேர்வு (r) {
        நிலை SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            நிறுத்து;
        நிலை SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_உச்சி:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_வலது:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_இடது:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            நிறுத்து;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    எனில் (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

வெறுமை Wayland_FiniMouse(SDL_VideoData *data)
{
    க்கு (முழு i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = வெற்று;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

வெறுமை Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

வெறுமை Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    மாறிலி Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

வெறுமை Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    மாறிலி Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    எனில் (pointer_focus) {
        எனில் (mouse->cursor_visible) {
            எனில் (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                மாறிலி SDL_HitTestResult rc = pointer_focus->hit_test_result;

                எனில் (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } இல்லையெனில் {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } இல்லையெனில் {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, வெற்று);
            }
        } இல்லையெனில் {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, வெற்று);
        }
    } இல்லையெனில் {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

வெறுமை Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    மாறிலி Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    எனில் (tool_focus) {
        எனில் (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            மாறிலி bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            எனில் (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } இல்லையெனில் {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, வெற்று);
            }
        } இல்லையெனில் {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, வெற்று);
        }
    } இல்லையெனில் {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

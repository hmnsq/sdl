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

#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ضمن <errno.h>

#ضمن "../SDL_sysvideo.h"
#ضمن "../SDL_video_c.h"

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "SDL_waylandvideo.h"
#ضمن "../SDL_pixels_c.h"
#ضمن "SDL_waylandevents_c.h"

#ضمن "wayland-cursor.h"
#ضمن "SDL_waylandmouse.h"
#ضمن "SDL_waylandshmbuffer.h"

#ضمن "cursor-shape-v1-client-protocol.h"
#ضمن "pointer-constraints-unstable-v1-client-protocol.h"
#ضمن "viewporter-client-protocol.h"
#ضمن "pointer-warp-v1-client-protocol.h"
#ضمن "tablet-v2-client-protocol.h"

#ضمن "../../SDL_hints_c.h"

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_يسار + 1];

ساكن bool Wayland_SetRelativeMouseMode(bool enabled);

تعريفنوع بنية
{
    صحيح width;
    صحيح height;
    بنية wl_buffer *buffer;
} CustomCursorImage;

تعريفنوع بنية
{
    // The base dimensions of the cursor.
    صحيح width;
    صحيح height;
    صحيح hot_x;
    صحيح hot_y;

    صحيح images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

تعريفنوع بنية
{
    صحيح size;
    بنية wl_list عقدة;
    بنية wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

تعريفنوع بنية
{
    SDL_SystemCursor id;
    بنية wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

بنية SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    صحيح رقم_frames;
    bool is_system_cursor;

    اتحاد
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

ساكن صحيح dbus_cursor_size;
ساكن حرف *dbus_cursor_theme;

ساكن فراغ Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    لكل (صحيح i = 0; i < vdata->رقم_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->رقم_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = عدم;
}

#ifdef SDL_USE_LIBDBUS

#ضمن "../../core/linux/SDL_dbus.h"

#define CURSOR_عقدة        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_مفتاح    "cursor-size"
#define CURSOR_THEME_مفتاح   "cursor-theme"

ساكن DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت حرف *مفتاح)
{
    ساكن ثابت حرف *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = عدم;
    DBusMessage *رسالة = dbus->message_new_method_call(CURSOR_عقدة,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    إذا (رسالة) {
        إذا (dbus->message_append_وسائط(رسالة, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &مفتاح, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, رسالة, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        }
        dbus->message_unref(رسالة);
    }

    أرجع reply;
}

ساكن bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, صحيح type, فراغ *قيمة)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    إذا (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    إذا (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    إذا (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        أرجع false;
    }

    dbus->message_iter_get_basic(&iter[2], قيمة);

    أرجع true;
}

ساكن DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *رسالة, فراغ *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    إذا (dbus->message_is_signal(رسالة, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        ثابت حرف *namespace, *مفتاح;

        dbus->message_iter_init(رسالة, &signal_iter);
        // Check if the parameters are what we expect
        إذا (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        إذا (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            اذهب not_our_signal;
        }
        إذا (!dbus->message_iter_next(&signal_iter)) {
            اذهب not_our_signal;
        }
        إذا (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &مفتاح);
        إذا (SDL_strcmp(CURSOR_SIZE_مفتاح, مفتاح) == 0) {
            صحيح new_cursor_size;

            إذا (!dbus->message_iter_next(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                اذهب not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            إذا (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } وإلا إذا (SDL_strcmp(CURSOR_THEME_مفتاح, مفتاح) == 0) {
            ثابت حرف *new_cursor_theme = عدم;

            إذا (!dbus->message_iter_next(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                اذهب not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            إذا (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                إذا (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } وإلا {
                    dbus_cursor_theme = عدم;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } وإلا {
            اذهب not_our_signal;
        }

        أرجع DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    أرجع DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

ساكن فراغ Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    إذا (!dbus) {
        أرجع;
    }

    إذا ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_مفتاح))) {
        إذا (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    إذا ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_مفتاح))) {
        ثابت حرف *temp = عدم;
        إذا (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            إذا (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    إذا (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            عدم);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, عدم);
        dbus->connection_flush(dbus->session_conn);
    }
}

ساكن فراغ Wayland_DBusFinishCursorProperties(فراغ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = عدم;
}

#endif

ساكن بنية wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, صحيح frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    إذا (data) {
        إذا (!data->is_system_cursor) {
            ثابت صحيح offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = عدم;
            ثابت صحيح target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            صحيح closest_area = 0;
            لكل (صحيح i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            أرجع closest ? closest->buffer : عدم;
        } وإلا {
            أرجع ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    أرجع عدم;
}

ساكن فراغ cursor_frame_done(فراغ *data, بنية wl_callback *cb, uint32_t time);
ساكن ثابت بنية wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

ساكن فراغ cursor_frame_done(فراغ *data, بنية wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    إذا (!state->current_cursor) {
        أرجع;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    صحيح next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    لكل (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->رقم_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        إذا (!frames[next]) {
            اكسر;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = عدم;

    // Don't queue another callback if this frame time is infinite.
    إذا (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    بنية wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    إذا (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

فراغ Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, فراغ *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

فراغ Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    إذا (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = عدم;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ساكن فراغ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

ساكن فراغ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    إذا (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } وإلا {
        Wayland_CursorStateResetAnimationState(state);
    }
}

فراغ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    إذا (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    إذا (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    إذا (state->surface) {
        wl_surface_attach(state->surface, عدم, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ساكن Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, بنية wl_cursor *cursor, صحيح size)
{
    Wayland_CachedSystemCursor *cache = عدم;

    // Is this cursor already cached at the target scale?
    إذا (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = عدم;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, عقدة) {
            إذا (c->size == size) {
                cache = c;
                اكسر;
            }
        }
    }

    إذا (!cache) {
        cache = SDL_calloc(1, حجم(Wayland_CachedSystemCursor) + (حجم(بنية wl_buffer *) * cdata->رقم_frames));

        cache->size = size;
        لكل (صحيح i = 0; i < cdata->رقم_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_أدرج(&cdata->cursor_data.system.cursor_buffer_cache, &cache->عقدة);
    }

    أرجع cache;
}

ساكن bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, صحيح *dst_size, صحيح *hot_x, صحيح *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    بنية wl_cursor_theme *theme = عدم;
    ثابت حرف *css_name = "default";
    ثابت حرف *fallback_name = عدم;
    مزدوج scale_factor = state->scale;
    صحيح theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    إذا (theme_size <= 0) {
        ثابت حرف *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        إذا (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    إذا (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ثابت صحيح scaled_size = (صحيح)SDL_lround(theme_size * scale_factor);
    لكل (صحيح i = 0; i < vdata->رقم_cursor_themes; ++i) {
        إذا (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            اكسر;
        }
    }
    إذا (!theme) {
        ثابت حرف *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                حجم(SDL_WaylandCursorTheme) * (vdata->رقم_cursor_themes + 1));
        إذا (!new_cursor_themes) {
            أرجع false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        إذا (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->رقم_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->رقم_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    بنية wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    إذا (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    إذا (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    إذا (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    إذا (!cursor) {
        أرجع false;
    }

    // ... Set the cursor data, finally.
    cdata->رقم_frames = cursor->image_عدد_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    إذا (cursor->image_عدد_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_عدد_2, حجم(Uint32));

        لكل (صحيح i = 0; i < cursor->image_عدد_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    أرجع true;
}

ساكن صحيح surface_sort_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ساكن SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, صحيح frame_عدد, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_CursorData *data = عدم;
    Wayland_SHMPool *shm_pool = عدم;
    صحيح pool_size = 0;
    صحيح max_images = 0;
    bool is_مكدس = false;
    بنية SurfaceArray
    {
        SDL_Surface **surfaces;
        صحيح عدد;
    } *surfaces = SDL_small_alloc(بنية SurfaceArray, frame_عدد, &is_مكدس);
    إذا (!surfaces) {
        اذهب failed;
    }
    SDL_memset(surfaces, 0, حجم(بنية SurfaceArray) * frame_عدد);

    // Calculate the total allocation size.
    لكل (صحيح i = 0; i < frame_عدد; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].عدد);
        إذا (!surfaces[i].surfaces) {
            اذهب failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].عدد, حجم(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].عدد);
        لكل (صحيح j = 0; j < surfaces[i].عدد; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, حجم(*data) + (حجم(CustomCursorImage) * max_images * frame_عدد));
    إذا (!data) {
        اذهب failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_عدد, حجم(Uint32));
    إذا (!data->frame_durations_ms) {
        اذهب failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    إذا (!shm_pool) {
        اذهب failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->رقم_frames = frame_عدد;

    لكل (صحيح i = 0; i < frame_عدد; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        إذا (data->total_duration_ms < SDL_MAX_UINT32) {
            إذا (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } وإلا {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحيح offset = i * max_images;
        لكل (صحيح j = 0; j < surfaces[i].عدد; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                إذا (!surface) {
                    اذهب failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            فراغ *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            إذا (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_مكدس);
    Wayland_ReleaseSHMPool(shm_pool);

    أرجع cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    إذا (data) {
        SDL_free(data->frame_durations_ms);
        لكل (صحيح i = 0; i < data->cursor_data.custom.images_per_frame * frame_عدد; ++i) {
            إذا (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    إذا (surfaces) {
        لكل (صحيح i = 0; i < frame_عدد; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_مكدس);
    }

    SDL_free(cursor);

    أرجع عدم;
}

ساكن SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    أرجع Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));

    إذا (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, حجم(*cdata));
        إذا (!cdata) {
            SDL_free(cursor);
            أرجع عدم;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    أرجع cursor;
}

ساكن SDL_Cursor *Wayland_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع Wayland_CreateSystemCursor(id);
}

ساكن فراغ Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        إذا (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            إذا (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, عدم, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = عدم;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                إذا (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, عدم, 0, 0);
                }

                tool->cursor_state.current_cursor = عدم;
            }
        }
    }

    إذا (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, عقدة) {
            SDL_free(c);
        }
    } وإلا {
        لكل (صحيح i = 0; i < d->رقم_frames * d->cursor_data.custom.images_per_frame; ++i) {
            إذا (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

ساكن فراغ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        أرجع;
    }

    // Probably not a cursor we own
    إذا (!cursor->internal) {
        أرجع;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ساكن تعداد wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    بدل (id) {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        اكسر;
    افتراضي:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    أرجع shape;
}

تعريفنوع بنية Wayland_PointerObject
{
    اتحاد
    {
        بنية wl_pointer *wl_pointer;
        بنية zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

ساكن فراغ Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, ثابت Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : عدم;
    صحيح dst_width = 0;
    صحيح dst_height = 0;
    صحيح hot_x;
    صحيح hot_y;

    // Stop the frame callback for old animated cursors.
    إذا (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    إذا (cursor) {
        إذا (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            إذا (cursor_data->رقم_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            أرجع;
        }

        إذا (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            إذا (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                إذا (state->surface) {
                    wl_surface_attach(state->surface, عدم, 0, 0);
                    wl_surface_commit(state->surface);

                    إذا (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, عدم, 0, 0);
                    } وإلا {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, عدم, 0, 0);
                    }

                    إذا (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = عدم;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = عدم;
                }

                ثابت تعداد wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                أرجع;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            إذا (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                أرجع;
            }

            dst_height = dst_width;
        } وإلا {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            إذا (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } وإلا {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((صحيح)SDL_lround((مزدوج)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((صحيح)SDL_lround((مزدوج)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (صحيح)SDL_lround((مزدوج)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (صحيح)SDL_lround((مزدوج)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        إذا (!state->surface) {
            بنية wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        بنية wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        إذا (state->scale != 1.0) {
            إذا (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } وإلا إذا (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = عدم;
        }

        إذا (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } وإلا {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        إذا (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        إذا (cursor_data->رقم_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } وإلا {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = عدم;

        إذا (state->surface) {
            wl_surface_attach(state->surface, عدم, 0, 0);
            wl_surface_commit(state->surface);
        }

        إذا (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, عدم, 0, 0);
        } وإلا {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, عدم, 0, 0);
        }
    }
}

ساكن فراغ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

فراغ Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    ثابت مزدوج new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        إذا (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            إذا (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                إذا (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ساكن bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            إذا (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } وإلا إذا (!seat->pointer.focus) {
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
            إذا (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا إذا (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    أرجع true;
}

فراغ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    إذا (seat->pointer.wl_pointer) {
        إذا (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } وإلا {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            إذا (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = عدم;
                update_grabs = true;
            }
            إذا (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = عدم;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            بنية zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, عدم,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            إذا (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        إذا (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

ساكن bool Wayland_WarpMouseRelative(SDL_Window *window, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    إذا (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } وإلا {
        أرجع SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    إذا (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            إذا (wind) {
                SDL_Window *window = wind->sdlwindow;

                صحيح abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                إذا (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } وإلا {
        أرجع SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    إذا (!data->relative_pointer_manager) {
        أرجع SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    إذا (!data->pointer_constraints) {
        أرجع SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, عدم);
    أرجع true;
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
ساكن SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(عائم *x, عائم *y)
{
    ثابت SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    إذا (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        صحيح off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } وإلا {
        *x = 0.f;
        *y = 0.f;
    }

    أرجع result;
}

#إذا 0  // TODO RECONNECT: See waylandvideo.c for more information!
ساكن فراغ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    إذا (cdata == عدم) {
        أرجع;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    إذا (cdata->shm_data != عدم) {
        فراغ *old_data_pointer = cdata->shm_data;
        صحيح stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, عدم);
}

فراغ Wayland_RecreateCursors(فراغ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    إذا (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = عدم;
        vdata->رقم_cursor_themes = 0;
    }

    إذا (mouse == عدم) {
        أرجع;
    }

    لكل (cursor = mouse->cursors; cursor != عدم; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    إذا (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    إذا (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        إذا (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

فراغ Wayland_InitMouse(SDL_VideoData *data)
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
    طالما (r <= SDL_HITTEST_RESIZE_يسار) {
        بدل (r) {
        حالة SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_قمة:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_يمين:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_يسار:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            اكسر;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    إذا (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

فراغ Wayland_FiniMouse(SDL_VideoData *data)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = عدم;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

فراغ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

فراغ Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ثابت Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

فراغ Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ثابت Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    إذا (pointer_focus) {
        إذا (mouse->cursor_visible) {
            إذا (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                ثابت SDL_HitTestResult rc = pointer_focus->hit_test_result;

                إذا (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } وإلا {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, عدم);
            }
        } وإلا {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

فراغ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    ثابت Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    إذا (tool_focus) {
        إذا (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            إذا (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
            }
        } وإلا {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#شامل <errno.h>

#شامل "../SDL_sysvideo.h"
#شامل "../SDL_video_c.h"

#شامل "../../core/unix/SDL_poll.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "SDL_waylandvideo.h"
#شامل "../SDL_pixels_c.h"
#شامل "SDL_waylandevents_c.h"

#شامل "wayland-cursor.h"
#شامل "SDL_waylandmouse.h"
#شامل "SDL_waylandshmbuffer.h"

#شامل "cursor-shape-v1-client-protocol.h"
#شامل "pointer-constraints-unstable-v1-client-protocol.h"
#شامل "viewporter-client-protocol.h"
#شامل "pointer-warp-v1-client-protocol.h"
#شامل "tablet-v2-client-protocol.h"

#شامل "../../SDL_hints_c.h"

ایستا SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_چپ + 1];

ایستا bool Wayland_SetRelativeMouseMode(bool enabled);

تعریفنوع ساختار
{
    صحیح width;
    صحیح height;
    ساختار wl_buffer *buffer;
} CustomCursorImage;

تعریفنوع ساختار
{
    // The base dimensions of the cursor.
    صحیح width;
    صحیح height;
    صحیح hot_x;
    صحیح hot_y;

    صحیح images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

تعریفنوع ساختار
{
    صحیح size;
    ساختار wl_list گره;
    ساختار wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

تعریفنوع ساختار
{
    SDL_SystemCursor id;
    ساختار wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

ساختار SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    صحیح رقم_frames;
    bool is_system_cursor;

    اجتماع
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

ایستا صحیح dbus_cursor_size;
ایستا نویسه *dbus_cursor_theme;

ایستا تهی Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    برای (صحیح i = 0; i < vdata->رقم_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->رقم_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = پوچ;
}

#ifdef SDL_USE_LIBDBUS

#شامل "../../core/linux/SDL_dbus.h"

#define CURSOR_گره        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_کلید    "cursor-size"
#define CURSOR_THEME_کلید   "cursor-theme"

ایستا DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت نویسه *کلید)
{
    ایستا ثابت نویسه *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = پوچ;
    DBusMessage *پیام = dbus->message_new_method_call(CURSOR_گره,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    اگر (پیام) {
        اگر (dbus->message_append_args(پیام, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &کلید, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, پیام, DBUS_TIMEOUT_USE_DEFAULT, پوچ);
        }
        dbus->message_unref(پیام);
    }

    بازگشت reply;
}

ایستا bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, صحیح type, تهی *مقدار)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    اگر (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        بازگشت false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    اگر (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        بازگشت false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    اگر (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        بازگشت false;
    }

    dbus->message_iter_get_basic(&iter[2], مقدار);

    بازگشت true;
}

ایستا DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *پیام, تهی *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    اگر (dbus->message_is_signal(پیام, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        ثابت نویسه *namespace, *کلید;

        dbus->message_iter_init(پیام, &signal_iter);
        // Check if the parameters are what we expect
        اگر (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            برو not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        اگر (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            برو not_our_signal;
        }
        اگر (!dbus->message_iter_next(&signal_iter)) {
            برو not_our_signal;
        }
        اگر (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            برو not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &کلید);
        اگر (SDL_strcmp(CURSOR_SIZE_کلید, کلید) == 0) {
            صحیح new_cursor_size;

            اگر (!dbus->message_iter_next(&signal_iter)) {
                برو not_our_signal;
            }
            اگر (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                برو not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            اگر (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                برو not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            اگر (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } وگرنه اگر (SDL_strcmp(CURSOR_THEME_کلید, کلید) == 0) {
            ثابت نویسه *new_cursor_theme = پوچ;

            اگر (!dbus->message_iter_next(&signal_iter)) {
                برو not_our_signal;
            }
            اگر (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                برو not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            اگر (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                برو not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            اگر (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                اگر (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } وگرنه {
                    dbus_cursor_theme = پوچ;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } وگرنه {
            برو not_our_signal;
        }

        بازگشت DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    بازگشت DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

ایستا تهی Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    اگر (!dbus) {
        بازگشت;
    }

    اگر ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_کلید))) {
        اگر (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    اگر ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_کلید))) {
        ثابت نویسه *temp = پوچ;
        اگر (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            اگر (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    اگر (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            پوچ);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, پوچ);
        dbus->connection_flush(dbus->session_conn);
    }
}

ایستا تهی Wayland_DBusFinishCursorProperties(تهی)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = پوچ;
}

#endif

ایستا ساختار wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, صحیح frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    اگر (data) {
        اگر (!data->is_system_cursor) {
            ثابت صحیح offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = پوچ;
            ثابت صحیح target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            صحیح closest_area = 0;
            برای (صحیح i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            بازگشت closest ? closest->buffer : پوچ;
        } وگرنه {
            بازگشت ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    بازگشت پوچ;
}

ایستا تهی cursor_frame_done(تهی *data, ساختار wl_callback *cb, uint32_t time);
ایستا ثابت ساختار wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

ایستا تهی cursor_frame_done(تهی *data, ساختار wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    اگر (!state->current_cursor) {
        بازگشت;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    صحیح next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    برای (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->رقم_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        اگر (!frames[next]) {
            بشکن;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = پوچ;

    // Don't queue another callback if this frame time is infinite.
    اگر (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    ساختار wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    اگر (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وگرنه {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

تهی Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, تهی *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

تهی Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    اگر (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = پوچ;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ایستا تهی Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

ایستا تهی Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    اگر (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } وگرنه {
        Wayland_CursorStateResetAnimationState(state);
    }
}

تهی Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    اگر (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    اگر (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    اگر (state->surface) {
        wl_surface_attach(state->surface, پوچ, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ایستا Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, ساختار wl_cursor *cursor, صحیح size)
{
    Wayland_CachedSystemCursor *cache = پوچ;

    // Is this cursor already cached at the target scale?
    اگر (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = پوچ;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, گره) {
            اگر (c->size == size) {
                cache = c;
                بشکن;
            }
        }
    }

    اگر (!cache) {
        cache = SDL_calloc(1, اندازه(Wayland_CachedSystemCursor) + (اندازه(ساختار wl_buffer *) * cdata->رقم_frames));

        cache->size = size;
        برای (صحیح i = 0; i < cdata->رقم_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_درج(&cdata->cursor_data.system.cursor_buffer_cache, &cache->گره);
    }

    بازگشت cache;
}

ایستا bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, صحیح *dst_size, صحیح *hot_x, صحیح *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    ساختار wl_cursor_theme *theme = پوچ;
    ثابت نویسه *css_name = "default";
    ثابت نویسه *fallback_name = پوچ;
    دوگانه scale_factor = state->scale;
    صحیح theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    اگر (theme_size <= 0) {
        ثابت نویسه *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        اگر (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    اگر (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ثابت صحیح scaled_size = (صحیح)SDL_lround(theme_size * scale_factor);
    برای (صحیح i = 0; i < vdata->رقم_cursor_themes; ++i) {
        اگر (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            بشکن;
        }
    }
    اگر (!theme) {
        ثابت نویسه *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                اندازه(SDL_WaylandCursorTheme) * (vdata->رقم_cursor_themes + 1));
        اگر (!new_cursor_themes) {
            بازگشت false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        اگر (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->رقم_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->رقم_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    ساختار wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    اگر (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    اگر (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    اگر (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    اگر (!cursor) {
        بازگشت false;
    }

    // ... Set the cursor data, finally.
    cdata->رقم_frames = cursor->image_شمار_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    اگر (cursor->image_شمار_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_شمار_2, اندازه(Uint32));

        برای (صحیح i = 0; i < cursor->image_شمار_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    بازگشت true;
}

ایستا صحیح surface_sort_callback(ثابت تهی *a, ثابت تهی *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    بازگشت (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ایستا SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, صحیح frame_شمار, صحیح hot_x, صحیح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, اندازه(*cursor));
    اگر (!cursor) {
        بازگشت پوچ;
    }

    SDL_CursorData *data = پوچ;
    Wayland_SHMPool *shm_pool = پوچ;
    صحیح pool_size = 0;
    صحیح max_images = 0;
    bool is_پشته = false;
    ساختار SurfaceArray
    {
        SDL_Surface **surfaces;
        صحیح شمار;
    } *surfaces = SDL_small_alloc(ساختار SurfaceArray, frame_شمار, &is_پشته);
    اگر (!surfaces) {
        برو failed;
    }
    SDL_memset(surfaces, 0, اندازه(ساختار SurfaceArray) * frame_شمار);

    // Calculate the total allocation size.
    برای (صحیح i = 0; i < frame_شمار; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].شمار);
        اگر (!surfaces[i].surfaces) {
            برو failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].شمار, اندازه(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].شمار);
        برای (صحیح j = 0; j < surfaces[i].شمار; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, اندازه(*data) + (اندازه(CustomCursorImage) * max_images * frame_شمار));
    اگر (!data) {
        برو failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_شمار, اندازه(Uint32));
    اگر (!data->frame_durations_ms) {
        برو failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    اگر (!shm_pool) {
        برو failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->رقم_frames = frame_شمار;

    برای (صحیح i = 0; i < frame_شمار; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        اگر (data->total_duration_ms < SDL_MAX_UINT32) {
            اگر (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } وگرنه {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحیح offset = i * max_images;
        برای (صحیح j = 0; j < surfaces[i].شمار; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            اگر (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                اگر (!surface) {
                    برو failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            تهی *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            اگر (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_پشته);
    Wayland_ReleaseSHMPool(shm_pool);

    بازگشت cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    اگر (data) {
        SDL_free(data->frame_durations_ms);
        برای (صحیح i = 0; i < data->cursor_data.custom.images_per_frame * frame_شمار; ++i) {
            اگر (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    اگر (surfaces) {
        برای (صحیح i = 0; i < frame_شمار; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_پشته);
    }

    SDL_free(cursor);

    بازگشت پوچ;
}

ایستا SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    بازگشت Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

ایستا SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, اندازه(*cursor));

    اگر (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, اندازه(*cdata));
        اگر (!cdata) {
            SDL_free(cursor);
            بازگشت پوچ;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    بازگشت cursor;
}

ایستا SDL_Cursor *Wayland_CreateDefaultCursor(تهی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    بازگشت Wayland_CreateSystemCursor(id);
}

ایستا تهی Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        اگر (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            اگر (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, پوچ, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = پوچ;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            اگر (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                اگر (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, پوچ, 0, 0);
                }

                tool->cursor_state.current_cursor = پوچ;
            }
        }
    }

    اگر (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, گره) {
            SDL_free(c);
        }
    } وگرنه {
        برای (صحیح i = 0; i < d->رقم_frames * d->cursor_data.custom.images_per_frame; ++i) {
            اگر (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

ایستا تهی Wayland_FreeCursor(SDL_Cursor *cursor)
{
    اگر (!cursor) {
        بازگشت;
    }

    // Probably not a cursor we own
    اگر (!cursor->internal) {
        بازگشت;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ایستا شمارش wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    انتخاب (id) {
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        بشکن;
    پیشفرض:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    بازگشت shape;
}

تعریفنوع ساختار Wayland_PointerObject
{
    اجتماع
    {
        ساختار wl_pointer *wl_pointer;
        ساختار zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

ایستا تهی Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, ثابت Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : پوچ;
    صحیح dst_width = 0;
    صحیح dst_height = 0;
    صحیح hot_x;
    صحیح hot_y;

    // Stop the frame callback for old animated cursors.
    اگر (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    اگر (cursor) {
        اگر (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            اگر (cursor_data->رقم_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            بازگشت;
        }

        اگر (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            اگر (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                اگر (state->surface) {
                    wl_surface_attach(state->surface, پوچ, 0, 0);
                    wl_surface_commit(state->surface);

                    اگر (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, پوچ, 0, 0);
                    } وگرنه {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, پوچ, 0, 0);
                    }

                    اگر (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = پوچ;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = پوچ;
                }

                ثابت شمارش wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                بازگشت;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            اگر (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                بازگشت;
            }

            dst_height = dst_width;
        } وگرنه {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            اگر (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } وگرنه {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((صحیح)SDL_lround((دوگانه)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((صحیح)SDL_lround((دوگانه)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (صحیح)SDL_lround((دوگانه)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (صحیح)SDL_lround((دوگانه)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        اگر (!state->surface) {
            ساختار wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ساختار wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        اگر (state->scale != 1.0) {
            اگر (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } وگرنه اگر (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = پوچ;
        }

        اگر (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } وگرنه {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        اگر (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وگرنه {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        اگر (cursor_data->رقم_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } وگرنه {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = پوچ;

        اگر (state->surface) {
            wl_surface_attach(state->surface, پوچ, 0, 0);
            wl_surface_commit(state->surface);
        }

        اگر (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, پوچ, 0, 0);
        } وگرنه {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, پوچ, 0, 0);
        }
    }
}

ایستا تهی Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

تهی Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    ثابت دوگانه new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        اگر (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            اگر (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            اگر (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                اگر (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ایستا bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        اگر (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            اگر (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } وگرنه اگر (!seat->pointer.focus) {
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
            اگر (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } وگرنه اگر (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    بازگشت true;
}

تهی Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, اعشاری x, اعشاری y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    اگر (seat->pointer.wl_pointer) {
        اگر (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } وگرنه {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            اگر (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = پوچ;
                update_grabs = true;
            }
            اگر (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = پوچ;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ساختار zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, پوچ,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            اگر (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        اگر (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

ایستا bool Wayland_WarpMouseRelative(SDL_Window *window, اعشاری x, اعشاری y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    اگر (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            اگر (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } وگرنه {
        بازگشت SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    بازگشت true;
}

ایستا bool Wayland_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    اگر (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            اگر (wind) {
                SDL_Window *window = wind->sdlwindow;

                صحیح abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                اگر (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } وگرنه {
        بازگشت SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    بازگشت true;
}

ایستا bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    اگر (!data->relative_pointer_manager) {
        بازگشت SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    اگر (!data->pointer_constraints) {
        بازگشت SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, پوچ);
    بازگشت true;
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
ایستا SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(اعشاری *x, اعشاری *y)
{
    ثابت SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    اگر (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        صحیح off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } وگرنه {
        *x = 0.f;
        *y = 0.f;
    }

    بازگشت result;
}

#اگر 0  // TODO RECONNECT: See waylandvideo.c for more information!
ایستا تهی Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    اگر (cdata == پوچ) {
        بازگشت;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    اگر (cdata->shm_data != پوچ) {
        تهی *old_data_pointer = cdata->shm_data;
        صحیح stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, پوچ);
}

تهی Wayland_RecreateCursors(تهی)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    اگر (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = پوچ;
        vdata->رقم_cursor_themes = 0;
    }

    اگر (mouse == پوچ) {
        بازگشت;
    }

    برای (cursor = mouse->cursors; cursor != پوچ; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    اگر (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    اگر (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        اگر (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

تهی Wayland_InitMouse(SDL_VideoData *data)
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
    وقتی (r <= SDL_HITTEST_RESIZE_چپ) {
        انتخاب (r) {
        حالت SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            بشکن;
        حالت SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            بشکن;
        حالت SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_بالاترین:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_راست:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            بشکن;
        حالت SDL_HITTEST_RESIZE_چپ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            بشکن;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    اگر (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

تهی Wayland_FiniMouse(SDL_VideoData *data)
{
    برای (صحیح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = پوچ;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

تهی Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

تهی Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ثابت Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

تهی Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    ثابت Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    اگر (pointer_focus) {
        اگر (mouse->cursor_visible) {
            اگر (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                ثابت SDL_HitTestResult rc = pointer_focus->hit_test_result;

                اگر (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } وگرنه {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } وگرنه {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, پوچ);
            }
        } وگرنه {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, پوچ);
        }
    } وگرنه {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

تهی Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    ثابت Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    اگر (tool_focus) {
        اگر (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            اگر (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } وگرنه {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, پوچ);
            }
        } وگرنه {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, پوچ);
        }
    } وگرنه {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

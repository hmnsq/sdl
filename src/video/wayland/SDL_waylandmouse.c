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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव <errno.h>

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../SDL_video_c.h"

#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "../SDL_pixels_c.h"
#अन्तर्भाव "SDL_waylandevents_c.h"

#अन्तर्भाव "wayland-cursor.h"
#अन्तर्भाव "SDL_waylandmouse.h"
#अन्तर्भाव "SDL_waylandshmbuffer.h"

#अन्तर्भाव "cursor-shape-v1-client-protocol.h"
#अन्तर्भाव "pointer-constraints-unstable-v1-client-protocol.h"
#अन्तर्भाव "viewporter-client-protocol.h"
#अन्तर्भाव "pointer-warp-v1-client-protocol.h"
#अन्तर्भाव "tablet-v2-client-protocol.h"

#अन्तर्भाव "../../SDL_hints_c.h"

स्थिर SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_डावा + 1];

स्थिर bool Wayland_SetRelativeMouseMode(bool enabled);

प्रकारव्याख्या संरचना
{
    पूर्णांक width;
    पूर्णांक height;
    संरचना wl_buffer *buffer;
} CustomCursorImage;

प्रकारव्याख्या संरचना
{
    // The base dimensions of the cursor.
    पूर्णांक width;
    पूर्णांक height;
    पूर्णांक hot_x;
    पूर्णांक hot_y;

    पूर्णांक images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

प्रकारव्याख्या संरचना
{
    पूर्णांक size;
    संरचना wl_list गाठ;
    संरचना wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

प्रकारव्याख्या संरचना
{
    SDL_SystemCursor id;
    संरचना wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

संरचना SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    पूर्णांक अंक_frames;
    bool is_system_cursor;

    संघ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor प्रणाली;
    } cursor_data;
};

स्थिर पूर्णांक dbus_cursor_size;
स्थिर अक्षर *dbus_cursor_theme;

स्थिर शून्य Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    साठी (पूर्णांक i = 0; i < vdata->अंक_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->अंक_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = रिक्त;
}

#ifdef SDL_USE_LIBDBUS

#अन्तर्भाव "../../core/linux/SDL_dbus.h"

#define CURSOR_गाठ        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_किल्ली    "cursor-size"
#define CURSOR_THEME_किल्ली   "cursor-theme"

स्थिर DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, स्थिरांक अक्षर *किल्ली)
{
    स्थिर स्थिरांक अक्षर *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = रिक्त;
    DBusMessage *संदेश = dbus->message_new_method_call(CURSOR_गाठ,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    जर (संदेश) {
        जर (dbus->message_append_args(संदेश, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &किल्ली, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, संदेश, DBUS_TIMEOUT_USE_DEFAULT, रिक्त);
        }
        dbus->message_unref(संदेश);
    }

    परत reply;
}

स्थिर bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, पूर्णांक type, शून्य *मूल्य)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    जर (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        परत false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    जर (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        परत false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    जर (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        परत false;
    }

    dbus->message_iter_get_basic(&iter[2], मूल्य);

    परत true;
}

स्थिर DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *संदेश, शून्य *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    जर (dbus->message_is_signal(संदेश, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        स्थिरांक अक्षर *namespace, *किल्ली;

        dbus->message_iter_init(संदेश, &signal_iter);
        // Check if the parameters are what we expect
        जर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            जा not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        जर (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            जा not_our_signal;
        }
        जर (!dbus->message_iter_next(&signal_iter)) {
            जा not_our_signal;
        }
        जर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            जा not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &किल्ली);
        जर (SDL_strcmp(CURSOR_SIZE_किल्ली, किल्ली) == 0) {
            पूर्णांक new_cursor_size;

            जर (!dbus->message_iter_next(&signal_iter)) {
                जा not_our_signal;
            }
            जर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                जा not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            जर (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                जा not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            जर (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } अन्यथा जर (SDL_strcmp(CURSOR_THEME_किल्ली, किल्ली) == 0) {
            स्थिरांक अक्षर *new_cursor_theme = रिक्त;

            जर (!dbus->message_iter_next(&signal_iter)) {
                जा not_our_signal;
            }
            जर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                जा not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            जर (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                जा not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            जर (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                जर (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } अन्यथा {
                    dbus_cursor_theme = रिक्त;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } अन्यथा {
            जा not_our_signal;
        }

        परत DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    परत DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

स्थिर शून्य Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    जर (!dbus) {
        परत;
    }

    जर ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_किल्ली))) {
        जर (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    जर ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_किल्ली))) {
        स्थिरांक अक्षर *temp = रिक्त;
        जर (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            जर (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    जर (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            रिक्त);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, रिक्त);
        dbus->connection_flush(dbus->session_conn);
    }
}

स्थिर शून्य Wayland_DBusFinishCursorProperties(शून्य)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = रिक्त;
}

#endif

स्थिर संरचना wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, पूर्णांक frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    जर (data) {
        जर (!data->is_system_cursor) {
            स्थिरांक पूर्णांक offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = रिक्त;
            स्थिरांक पूर्णांक target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            पूर्णांक closest_area = 0;
            साठी (पूर्णांक i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            परत closest ? closest->buffer : रिक्त;
        } अन्यथा {
            परत ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    परत रिक्त;
}

स्थिर शून्य cursor_frame_done(शून्य *data, संरचना wl_callback *cb, uint32_t समय);
स्थिर स्थिरांक संरचना wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

स्थिर शून्य cursor_frame_done(शून्य *data, संरचना wl_callback *cb, uint32_t समय)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    जर (!state->current_cursor) {
        परत;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    स्थिरांक Uint64 now = SDL_GetTicks();
    स्थिरांक Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    पूर्णांक next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    साठी (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->अंक_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        जर (!frames[next]) {
            थांबा;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = रिक्त;

    // Don't queue another callback if this frame time is infinite.
    जर (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    संरचना wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    जर (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } अन्यथा {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

शून्य Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, शून्य *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

शून्य Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    जर (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = रिक्त;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

स्थिर शून्य Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

स्थिर शून्य Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    जर (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } अन्यथा {
        Wayland_CursorStateResetAnimationState(state);
    }
}

शून्य Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    जर (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    जर (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    जर (state->surface) {
        wl_surface_attach(state->surface, रिक्त, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

स्थिर Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, संरचना wl_cursor *cursor, पूर्णांक size)
{
    Wayland_CachedSystemCursor *cache = रिक्त;

    // Is this cursor already cached at the target scale?
    जर (!WAYLAND_wl_list_empty(&cdata->cursor_data.प्रणाली.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = रिक्त;
        wl_list_for_each (c, &cdata->cursor_data.प्रणाली.cursor_buffer_cache, गाठ) {
            जर (c->size == size) {
                cache = c;
                थांबा;
            }
        }
    }

    जर (!cache) {
        cache = SDL_calloc(1, आकार(Wayland_CachedSystemCursor) + (आकार(संरचना wl_buffer *) * cdata->अंक_frames));

        cache->size = size;
        साठी (पूर्णांक i = 0; i < cdata->अंक_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_घाला(&cdata->cursor_data.प्रणाली.cursor_buffer_cache, &cache->गाठ);
    }

    परत cache;
}

स्थिर bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, पूर्णांक *dst_size, पूर्णांक *hot_x, पूर्णांक *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    संरचना wl_cursor_theme *theme = रिक्त;
    स्थिरांक अक्षर *css_name = "default";
    स्थिरांक अक्षर *fallback_name = रिक्त;
    द्विगुण scale_factor = state->scale;
    पूर्णांक theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    जर (theme_size <= 0) {
        स्थिरांक अक्षर *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        जर (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    जर (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    स्थिरांक पूर्णांक scaled_size = (पूर्णांक)SDL_lround(theme_size * scale_factor);
    साठी (पूर्णांक i = 0; i < vdata->अंक_cursor_themes; ++i) {
        जर (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            थांबा;
        }
    }
    जर (!theme) {
        स्थिरांक अक्षर *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                आकार(SDL_WaylandCursorTheme) * (vdata->अंक_cursor_themes + 1));
        जर (!new_cursor_themes) {
            परत false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        जर (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->अंक_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->अंक_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.प्रणाली.id, &fallback_name);
    संरचना wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    जर (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    जर (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    जर (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    जर (!cursor) {
        परत false;
    }

    // ... Set the cursor data, finally.
    cdata->अंक_frames = cursor->image_मोजणी_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    जर (cursor->image_मोजणी_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_मोजणी_2, आकार(Uint32));

        साठी (पूर्णांक i = 0; i < cursor->image_मोजणी_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    परत true;
}

स्थिर पूर्णांक surface_sort_callback(स्थिरांक शून्य *a, स्थिरांक शून्य *b)
{
    स्थिरांक SDL_Surface *s1 = *(स्थिरांक SDL_Surface **)a;
    स्थिरांक SDL_Surface *s2 = *(स्थिरांक SDL_Surface **)b;

    परत (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

स्थिर SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णांक frame_मोजणी, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, आकार(*cursor));
    जर (!cursor) {
        परत रिक्त;
    }

    SDL_CursorData *data = रिक्त;
    Wayland_SHMPool *shm_pool = रिक्त;
    पूर्णांक pool_size = 0;
    पूर्णांक max_images = 0;
    bool is_चळत = false;
    संरचना SurfaceArray
    {
        SDL_Surface **surfaces;
        पूर्णांक मोजणी;
    } *surfaces = SDL_small_alloc(संरचना SurfaceArray, frame_मोजणी, &is_चळत);
    जर (!surfaces) {
        जा failed;
    }
    SDL_memset(surfaces, 0, आकार(संरचना SurfaceArray) * frame_मोजणी);

    // Calculate the total allocation size.
    साठी (पूर्णांक i = 0; i < frame_मोजणी; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].मोजणी);
        जर (!surfaces[i].surfaces) {
            जा failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].मोजणी, आकार(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].मोजणी);
        साठी (पूर्णांक j = 0; j < surfaces[i].मोजणी; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, आकार(*data) + (आकार(CustomCursorImage) * max_images * frame_मोजणी));
    जर (!data) {
        जा failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_मोजणी, आकार(Uint32));
    जर (!data->frame_durations_ms) {
        जा failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    जर (!shm_pool) {
        जा failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->अंक_frames = frame_मोजणी;

    साठी (पूर्णांक i = 0; i < frame_मोजणी; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        जर (data->total_duration_ms < SDL_MAX_UINT32) {
            जर (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } अन्यथा {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        स्थिरांक पूर्णांक offset = i * max_images;
        साठी (पूर्णांक j = 0; j < surfaces[i].मोजणी; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            जर (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                जर (!surface) {
                    जा failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            शून्य *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            जर (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_चळत);
    Wayland_ReleaseSHMPool(shm_pool);

    परत cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    जर (data) {
        SDL_free(data->frame_durations_ms);
        साठी (पूर्णांक i = 0; i < data->cursor_data.custom.images_per_frame * frame_मोजणी; ++i) {
            जर (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    जर (surfaces) {
        साठी (पूर्णांक i = 0; i < frame_मोजणी; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_चळत);
    }

    SDL_free(cursor);

    परत रिक्त;
}

स्थिर SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    परत Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

स्थिर SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, आकार(*cursor));

    जर (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, आकार(*cdata));
        जर (!cdata) {
            SDL_free(cursor);
            परत रिक्त;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.प्रणाली.cursor_buffer_cache);
        cdata->cursor_data.प्रणाली.id = id;
        cdata->is_system_cursor = true;
    }

    परत cursor;
}

स्थिर SDL_Cursor *Wayland_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    परत Wayland_CreateSystemCursor(id);
}

स्थिर शून्य Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        जर (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            जर (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, रिक्त, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = रिक्त;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            जर (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                जर (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, रिक्त, 0, 0);
                }

                tool->cursor_state.current_cursor = रिक्त;
            }
        }
    }

    जर (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.प्रणाली.cursor_buffer_cache, गाठ) {
            SDL_free(c);
        }
    } अन्यथा {
        साठी (पूर्णांक i = 0; i < d->अंक_frames * d->cursor_data.custom.images_per_frame; ++i) {
            जर (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

स्थिर शून्य Wayland_FreeCursor(SDL_Cursor *cursor)
{
    जर (!cursor) {
        परत;
    }

    // Probably not a cursor we own
    जर (!cursor->internal) {
        परत;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

स्थिर गणना wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    निवड (id) {
    स्थिती SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        थांबा;
    स्थिती SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        थांबा;
    पूर्वनिर्धारित:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    परत shape;
}

प्रकारव्याख्या संरचना Wayland_PointerObject
{
    संघ
    {
        संरचना wl_pointer *wl_pointer;
        संरचना zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

स्थिर शून्य Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, स्थिरांक Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : रिक्त;
    पूर्णांक dst_width = 0;
    पूर्णांक dst_height = 0;
    पूर्णांक hot_x;
    पूर्णांक hot_y;

    // Stop the frame callback for old animated cursors.
    जर (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    जर (cursor) {
        जर (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            जर (cursor_data->अंक_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            परत;
        }

        जर (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            जर (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                जर (state->surface) {
                    wl_surface_attach(state->surface, रिक्त, 0, 0);
                    wl_surface_commit(state->surface);

                    जर (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, रिक्त, 0, 0);
                    } अन्यथा {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, रिक्त, 0, 0);
                    }

                    जर (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = रिक्त;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = रिक्त;
                }

                स्थिरांक गणना wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.प्रणाली.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                परत;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            जर (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                परत;
            }

            dst_height = dst_width;
        } अन्यथा {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            जर (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } अन्यथा {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((पूर्णांक)SDL_lround((द्विगुण)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((पूर्णांक)SDL_lround((द्विगुण)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (पूर्णांक)SDL_lround((द्विगुण)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (पूर्णांक)SDL_lround((द्विगुण)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        जर (!state->surface) {
            संरचना wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        संरचना wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        जर (state->scale != 1.0) {
            जर (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } अन्यथा जर (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = रिक्त;
        }

        जर (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } अन्यथा {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        जर (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } अन्यथा {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        जर (cursor_data->अंक_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } अन्यथा {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = रिक्त;

        जर (state->surface) {
            wl_surface_attach(state->surface, रिक्त, 0, 0);
            wl_surface_commit(state->surface);
        }

        जर (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, रिक्त, 0, 0);
        } अन्यथा {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, रिक्त, 0, 0);
        }
    }
}

स्थिर शून्य Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

शून्य Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    स्थिरांक द्विगुण new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        जर (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            जर (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            जर (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                जर (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

स्थिर bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        जर (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            जर (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } अन्यथा जर (!seat->pointer.focus) {
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
            जर (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } अन्यथा जर (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    परत true;
}

शून्य Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, दशांश x, दशांश y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    जर (seat->pointer.wl_pointer) {
        जर (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            स्थिरांक wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            स्थिरांक wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } अन्यथा {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            जर (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = रिक्त;
                update_grabs = true;
            }
            जर (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = रिक्त;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            संरचना zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, रिक्त,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            स्थिरांक wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            स्थिरांक wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            जर (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        जर (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

स्थिर bool Wayland_WarpMouseRelative(SDL_Window *window, दशांश x, दशांश y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    जर (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            जर (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } अन्यथा {
        परत SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    परत true;
}

स्थिर bool Wayland_WarpMouseGlobal(दशांश x, दशांश y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    जर (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            जर (wind) {
                SDL_Window *window = wind->sdlwindow;

                पूर्णांक abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                स्थिरांक SDL_FPoint p = { x, y };
                स्थिरांक SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                जर (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } अन्यथा {
        परत SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    परत true;
}

स्थिर bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    जर (!data->relative_pointer_manager) {
        परत SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    जर (!data->pointer_constraints) {
        परत SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, रिक्त);
    परत true;
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
स्थिर SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(दशांश *x, दशांश *y)
{
    स्थिरांक SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    जर (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        पूर्णांक off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } अन्यथा {
        *x = 0.f;
        *y = 0.f;
    }

    परत result;
}

#जर 0  // TODO RECONNECT: See waylandvideo.c for more information!
स्थिर शून्य Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    जर (cdata == रिक्त) {
        परत;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    जर (cdata->shm_data != रिक्त) {
        शून्य *old_data_pointer = cdata->shm_data;
        पूर्णांक stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, रिक्त);
}

शून्य Wayland_RecreateCursors(शून्य)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    जर (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = रिक्त;
        vdata->अंक_cursor_themes = 0;
    }

    जर (mouse == रिक्त) {
        परत;
    }

    साठी (cursor = mouse->cursors; cursor != रिक्त; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    जर (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    जर (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        जर (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

शून्य Wayland_InitMouse(SDL_VideoData *data)
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
    पर्यंत (r <= SDL_HITTEST_RESIZE_डावा) {
        निवड (r) {
        स्थिती SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            थांबा;
        स्थिती SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_शीर्ष:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_उजवा:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            थांबा;
        स्थिती SDL_HITTEST_RESIZE_डावा:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            थांबा;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    जर (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

शून्य Wayland_FiniMouse(SDL_VideoData *data)
{
    साठी (पूर्णांक i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = रिक्त;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

शून्य Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

शून्य Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    स्थिरांक Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

शून्य Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    स्थिरांक Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    जर (pointer_focus) {
        जर (mouse->cursor_visible) {
            जर (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                स्थिरांक SDL_HitTestResult rc = pointer_focus->hit_test_result;

                जर (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } अन्यथा {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } अन्यथा {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, रिक्त);
            }
        } अन्यथा {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, रिक्त);
        }
    } अन्यथा {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

शून्य Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    स्थिरांक Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    जर (tool_focus) {
        जर (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            स्थिरांक bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            जर (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } अन्यथा {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, रिक्त);
            }
        } अन्यथा {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, रिक्त);
        }
    } अन्यथा {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

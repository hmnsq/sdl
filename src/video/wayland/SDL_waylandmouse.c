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

#समावेश <errno.h>

#समावेश "../SDL_sysvideo.h"
#समावेश "../SDL_video_c.h"

#समावेश "../../core/unix/SDL_poll.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "SDL_waylandvideo.h"
#समावेश "../SDL_pixels_c.h"
#समावेश "SDL_waylandevents_c.h"

#समावेश "wayland-cursor.h"
#समावेश "SDL_waylandmouse.h"
#समावेश "SDL_waylandshmbuffer.h"

#समावेश "cursor-shape-v1-client-protocol.h"
#समावेश "pointer-constraints-unstable-v1-client-protocol.h"
#समावेश "viewporter-client-protocol.h"
#समावेश "pointer-warp-v1-client-protocol.h"
#समावेश "tablet-v2-client-protocol.h"

#समावेश "../../SDL_hints_c.h"

अटल SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_बायाँ + 1];

अटल bool Wayland_SetRelativeMouseMode(bool enabled);

प्रकार काष्ठा
{
    पूर्णांक width;
    पूर्णांक height;
    काष्ठा wl_बफर *बफर_2;
} CustomCursorImage;

प्रकार काष्ठा
{
    // The base dimensions of the cursor.
    पूर्णांक width;
    पूर्णांक height;
    पूर्णांक hot_x;
    पूर्णांक hot_y;

    पूर्णांक images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

प्रकार काष्ठा
{
    पूर्णांक आकार;
    काष्ठा wl_list गाँठ;
    काष्ठा wl_बफर *buffers[];
} Wayland_CachedSystemCursor;

प्रकार काष्ठा
{
    SDL_SystemCursor id;
    काष्ठा wl_list cursor_बफर_cache;
} Wayland_SystemCursor;

काष्ठा SDL_Cursor_तथ्य
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 योग_duration_ms;
    पूर्णांक अंक_frames;
    bool is_system_cursor;

    जोड़
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor प्रणाली;
    } cursor_तथ्य;
};

अटल पूर्णांक dbus_cursor_आकार;
अटल अक्षर *dbus_cursor_theme;

अटल व्योम Wayland_FreeCursorThemes(SDL_Video_तथ्य *vdata)
{
    क्रम (पूर्णांक i = 0; i < vdata->अंक_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->अंक_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = शून्य;
}

#अगर_घोषित SDL_USE_LIBDBUS

#समावेश "../../core/linux/SDL_dbus.h"

#घोषणा CURSOR_गाँठ        "org.freedesktop.portal.Desktop"
#घोषणा CURSOR_PATH        "/org/freedesktop/portal/desktop"
#घोषणा CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#घोषणा CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#घोषणा CURSOR_SIGNAL_NAME "SettingChanged"
#घोषणा CURSOR_आकार_कुंजी    "cursor-size"
#घोषणा CURSOR_THEME_कुंजी   "cursor-theme"

अटल DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, स्थिर अक्षर *कुंजी)
{
    अटल स्थिर अक्षर *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = शून्य;
    DBusMessage *संदेश = dbus->message_new_method_call(CURSOR_गाँठ,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    अगर (संदेश) {
        अगर (dbus->message_append_args(संदेश, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &कुंजी, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, संदेश, DBUS_TIMEOUT_USE_DEFAULT, शून्य);
        }
        dbus->message_unref(संदेश);
    }

    वापस reply;
}

अटल bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, पूर्णांक type, व्योम *मूल्य)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    अगर (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        वापस false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    अगर (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        वापस false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    अगर (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        वापस false;
    }

    dbus->message_iter_get_basic(&iter[2], मूल्य);

    वापस true;
}

अटल DBus_Handler_परिणाम Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *संदेश, व्योम *तथ्य)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_तथ्य *vdata = (SDL_Video_तथ्य *)तथ्य;

    अगर (dbus->message_is_signal(संदेश, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        स्थिर अक्षर *namespace, *कुंजी;

        dbus->message_iter_init(संदेश, &signal_iter);
        // Check if the parameters are what we expect
        अगर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            जाओ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        अगर (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            जाओ not_our_signal;
        }
        अगर (!dbus->message_iter_अग्र(&signal_iter)) {
            जाओ not_our_signal;
        }
        अगर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            जाओ not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &कुंजी);
        अगर (SDL_strcmp(CURSOR_आकार_कुंजी, कुंजी) == 0) {
            पूर्णांक new_cursor_आकार;

            अगर (!dbus->message_iter_अग्र(&signal_iter)) {
                जाओ not_our_signal;
            }
            अगर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                जाओ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            अगर (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                जाओ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_आकार);

            अगर (dbus_cursor_आकार != new_cursor_आकार) {
                dbus_cursor_आकार = new_cursor_आकार;
                SDL_RedrawCursor(); // Force cursor update
            }
        } अन्यथा अगर (SDL_strcmp(CURSOR_THEME_कुंजी, कुंजी) == 0) {
            स्थिर अक्षर *new_cursor_theme = शून्य;

            अगर (!dbus->message_iter_अग्र(&signal_iter)) {
                जाओ not_our_signal;
            }
            अगर (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                जाओ not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            अगर (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                जाओ not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            अगर (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                अगर (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } अन्यथा {
                    dbus_cursor_theme = शून्य;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } अन्यथा {
            जाओ not_our_signal;
        }

        वापस DBUS_HANDLER_परिणाम_HANDLED;
    }

not_our_signal:
    वापस DBUS_HANDLER_परिणाम_NOT_YET_HANDLED;
}

अटल व्योम Wayland_DBusInitCursorProperties(SDL_Video_तथ्य *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    अगर (!dbus) {
        वापस;
    }

    अगर ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_आकार_कुंजी))) {
        अगर (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_आकार)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    अगर ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_कुंजी))) {
        स्थिर अक्षर *अस्थायी = शून्य;
        अगर (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &अस्थायी)) {
            add_filter = true;

            अगर (अस्थायी) {
                dbus_cursor_theme = SDL_strdup(अस्थायी);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    अगर (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            शून्य);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, शून्य);
        dbus->connection_flush(dbus->session_conn);
    }
}

अटल व्योम Wayland_DBusFinishCursorProperties(व्योम)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = शून्य;
}

#पूर्ण_अगर

अटल काष्ठा wl_बफर *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, पूर्णांक frame_सूचकांक_2)
{
    SDL_Cursor_तथ्य *तथ्य = state->current_cursor;

    अगर (तथ्य) {
        अगर (!तथ्य->is_system_cursor) {
            स्थिर पूर्णांक offset = तथ्य->cursor_तथ्य.custom.images_per_frame * frame_सूचकांक_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = शून्य;
            स्थिर पूर्णांक target_area = SDL_lround(तथ्य->cursor_तथ्य.custom.width * तथ्य->cursor_तथ्य.custom.height * state->scale);
            पूर्णांक closest_area = 0;
            क्रम (पूर्णांक i = 0; i < तथ्य->cursor_तथ्य.custom.images_per_frame && closest_area < target_area && तथ्य->cursor_तथ्य.custom.images[offset + i].बफर_2; ++i) {
                closest = &तथ्य->cursor_तथ्य.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            वापस closest ? closest->बफर_2 : शून्य;
        } अन्यथा {
            वापस ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_सूचकांक_2];
        }
    }

    वापस शून्य;
}

अटल व्योम cursor_frame_done(व्योम *तथ्य, काष्ठा wl_callback *cb, uint32_t समय);
अटल स्थिर काष्ठा wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

अटल व्योम cursor_frame_done(व्योम *तथ्य, काष्ठा wl_callback *cb, uint32_t समय)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)तथ्य;
    अगर (!state->current_cursor) {
        वापस;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_Cursor_तथ्य *c = state->current_cursor;

    स्थिर Uint64 now = SDL_GetTicks();
    स्थिर Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->योग_duration_ms;
    Uint32 advance = 0;
    पूर्णांक अग्र = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    क्रम (Uint32 t = frames[अग्र]; t <= state->current_frame_time_ms; t += frames[अग्र]) {
        अग्र = (अग्र + 1) % c->अंक_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        अगर (!frames[अग्र]) {
            अवरोध;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = शून्य;

    // Don't queue another callback if this frame time is infinite.
    अगर (frames[अग्र]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, तथ्य);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = अग्र;

    काष्ठा wl_बफर *बफर_2 = Wayland_CursorStateGetFrame(state, अग्र);
    wl_surface_attach(state->surface, बफर_2, 0, 0);

    अगर (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_VERSION) {
        wl_surface_damage_बफर(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } अन्यथा {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

व्योम Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, व्योम *userdata)
{
    SDL_Video_तथ्य *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

व्योम Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_Video_तथ्य *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    अगर (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = शून्य;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

अटल व्योम Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

अटल व्योम Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    अगर (lock) {
        SDL_Video_तथ्य *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } अन्यथा {
        Wayland_CursorStateResetAnimationState(state);
    }
}

व्योम Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    अगर (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    अगर (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    अगर (state->surface) {
        wl_surface_attach(state->surface, शून्य, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

अटल Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_तथ्य *cdata, काष्ठा wl_cursor *cursor, पूर्णांक आकार)
{
    Wayland_CachedSystemCursor *cache = शून्य;

    // Is this cursor already cached at the target scale?
    अगर (!WAYLAND_wl_list_empty(&cdata->cursor_तथ्य.प्रणाली.cursor_बफर_cache)) {
        Wayland_CachedSystemCursor *c = शून्य;
        wl_list_for_each (c, &cdata->cursor_तथ्य.प्रणाली.cursor_बफर_cache, गाँठ) {
            अगर (c->आकार == आकार) {
                cache = c;
                अवरोध;
            }
        }
    }

    अगर (!cache) {
        cache = SDL_calloc(1, माप(Wayland_CachedSystemCursor) + (माप(काष्ठा wl_बफर *) * cdata->अंक_frames));

        cache->आकार = आकार;
        क्रम (पूर्णांक i = 0; i < cdata->अंक_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_बफर(cursor->images[i]);
        }

        WAYLAND_wl_list_जोड़ो(&cdata->cursor_तथ्य.प्रणाली.cursor_बफर_cache, &cache->गाँठ);
    }

    वापस cache;
}

अटल bool Wayland_GetSystemCursor(SDL_Cursor_तथ्य *cdata, SDL_WaylandCursorState *state, पूर्णांक *dst_आकार, पूर्णांक *hot_x, पूर्णांक *hot_y)
{
    SDL_Video_तथ्य *vdata = SDL_GetVideoDevice()->internal;
    काष्ठा wl_cursor_theme *theme = शून्य;
    स्थिर अक्षर *css_name = "default";
    स्थिर अक्षर *fallback_name = शून्य;
    द्विगुन scale_factor = state->scale;
    पूर्णांक theme_आकार = dbus_cursor_आकार;

    // Fallback envvar if the DBus properties don't exist
    अगर (theme_आकार <= 0) {
        स्थिर अक्षर *xcursor_आकार = SDL_getenv("XCURSOR_SIZE");
        अगर (xcursor_आकार) {
            theme_आकार = SDL_atoi(xcursor_आकार);
        }
    }
    अगर (theme_आकार <= 0) {
        theme_आकार = 24;
    }

    // First, find the appropriate theme based on the current scale...
    स्थिर पूर्णांक scaled_आकार = (पूर्णांक)SDL_lround(theme_आकार * scale_factor);
    क्रम (पूर्णांक i = 0; i < vdata->अंक_cursor_themes; ++i) {
        अगर (vdata->cursor_themes[i].आकार == scaled_आकार) {
            theme = vdata->cursor_themes[i].theme;
            अवरोध;
        }
    }
    अगर (!theme) {
        स्थिर अक्षर *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                माप(SDL_WaylandCursorTheme) * (vdata->अंक_cursor_themes + 1));
        अगर (!new_cursor_themes) {
            वापस false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        अगर (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_आकार, vdata->shm);
        vdata->cursor_themes[vdata->अंक_cursor_themes].आकार = scaled_आकार;
        vdata->cursor_themes[vdata->अंक_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_तथ्य.प्रणाली.id, &fallback_name);
    काष्ठा wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    अगर (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    अगर (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    अगर (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    अगर (!cursor) {
        वापस false;
    }

    // ... Set the cursor data, finally.
    cdata->अंक_frames = cursor->image_गिनती_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_आकार);
    state->system_cursor_handle = c;

    अगर (cursor->image_गिनती_2 > 1 && !cdata->frame_durations_ms) {
        cdata->योग_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_गिनती_2, माप(Uint32));

        क्रम (पूर्णांक i = 0; i < cursor->image_गिनती_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->योग_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_आकार = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    वापस true;
}

अटल पूर्णांक surface_sort_callback(स्थिर व्योम *a, स्थिर व्योम *b)
{
    स्थिर SDL_Surface *s1 = *(स्थिर SDL_Surface **)a;
    स्थिर SDL_Surface *s2 = *(स्थिर SDL_Surface **)b;

    वापस (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

अटल SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णांक frame_गिनती, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, माप(*cursor));
    अगर (!cursor) {
        वापस शून्य;
    }

    SDL_Cursor_तथ्य *तथ्य = शून्य;
    Wayland_SHMPool *shm_pool = शून्य;
    पूर्णांक pool_आकार = 0;
    पूर्णांक max_images = 0;
    bool is_ढेर = false;
    काष्ठा SurfaceArray
    {
        SDL_Surface **surfaces;
        पूर्णांक गिनती;
    } *surfaces = SDL_small_alloc(काष्ठा SurfaceArray, frame_गिनती, &is_ढेर);
    अगर (!surfaces) {
        जाओ failed;
    }
    SDL_memset(surfaces, 0, माप(काष्ठा SurfaceArray) * frame_गिनती);

    // Calculate the total allocation size.
    क्रम (पूर्णांक i = 0; i < frame_गिनती; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].गिनती);
        अगर (!surfaces[i].surfaces) {
            जाओ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].गिनती, माप(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].गिनती);
        क्रम (पूर्णांक j = 0; j < surfaces[i].गिनती; ++j) {
            pool_आकार += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    तथ्य = SDL_calloc(1, माप(*तथ्य) + (माप(CustomCursorImage) * max_images * frame_गिनती));
    अगर (!तथ्य) {
        जाओ failed;
    }

    तथ्य->frame_durations_ms = SDL_calloc(frame_गिनती, माप(Uint32));
    अगर (!तथ्य->frame_durations_ms) {
        जाओ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_आकार);
    अगर (!shm_pool) {
        जाओ failed;
    }

    cursor->internal = तथ्य;
    तथ्य->cursor_तथ्य.custom.width = frames[0].surface->w;
    तथ्य->cursor_तथ्य.custom.height = frames[0].surface->h;
    तथ्य->cursor_तथ्य.custom.hot_x = hot_x;
    तथ्य->cursor_तथ्य.custom.hot_y = hot_y;
    तथ्य->cursor_तथ्य.custom.images_per_frame = max_images;
    तथ्य->अंक_frames = frame_गिनती;

    क्रम (पूर्णांक i = 0; i < frame_गिनती; ++i) {
        तथ्य->frame_durations_ms[i] = frames[i].duration;
        अगर (तथ्य->योग_duration_ms < SDL_MAX_UINT32) {
            अगर (तथ्य->frame_durations_ms[i] > 0) {
                तथ्य->योग_duration_ms += तथ्य->frame_durations_ms[i];
            } अन्यथा {
                तथ्य->योग_duration_ms = SDL_MAX_UINT32;
            }
        }

        स्थिर पूर्णांक offset = i * max_images;
        क्रम (पूर्णांक j = 0; j < surfaces[i].गिनती; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            अगर (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                अगर (!surface) {
                    जाओ failed;
                }
            }

            तथ्य->cursor_तथ्य.custom.images[offset + j].width = surface->w;
            तथ्य->cursor_तथ्य.custom.images[offset + j].height = surface->h;

            व्योम *buf_तथ्य;
            तथ्य->cursor_तथ्य.custom.images[offset + j].बफर_2 = Wayland_Alloc_बफर_From_Pool(shm_pool, surface->w, surface->h, &buf_तथ्य);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_तथ्य, surface->w * 4, true);

            अगर (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ढेर);
    Wayland_ReleaseSHMPool(shm_pool);

    वापस cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    अगर (तथ्य) {
        SDL_free(तथ्य->frame_durations_ms);
        क्रम (पूर्णांक i = 0; i < तथ्य->cursor_तथ्य.custom.images_per_frame * frame_गिनती; ++i) {
            अगर (तथ्य->cursor_तथ्य.custom.images[i].बफर_2) {
                wl_बफर_destroy(तथ्य->cursor_तथ्य.custom.images[i].बफर_2);
            }
        }
    }

    SDL_free(तथ्य);

    अगर (surfaces) {
        क्रम (पूर्णांक i = 0; i < frame_गिनती; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ढेर);
    }

    SDL_free(cursor);

    वापस शून्य;
}

अटल SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    वापस Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

अटल SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, माप(*cursor));

    अगर (cursor) {
        SDL_Cursor_तथ्य *cdata = SDL_calloc(1, माप(*cdata));
        अगर (!cdata) {
            SDL_free(cursor);
            वापस शून्य;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_तथ्य.प्रणाली.cursor_बफर_cache);
        cdata->cursor_तथ्य.प्रणाली.id = id;
        cdata->is_system_cursor = true;
    }

    वापस cursor;
}

अटल SDL_Cursor *Wayland_CreateDefaultCursor(व्योम)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    वापस Wayland_CreateSystemCursor(id);
}

अटल व्योम Wayland_Free_Cursor_तथ्य(SDL_Cursor_तथ्य *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_तथ्य *video_तथ्य = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_तथ्य->seat_list, link)
    {
        अगर (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            अगर (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, शून्य, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = शून्य;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            अगर (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                अगर (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, शून्य, 0, 0);
                }

                tool->cursor_state.current_cursor = शून्य;
            }
        }
    }

    अगर (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *अस्थायी;
        wl_list_for_each_safe(c, अस्थायी, &d->cursor_तथ्य.प्रणाली.cursor_बफर_cache, गाँठ) {
            SDL_free(c);
        }
    } अन्यथा {
        क्रम (पूर्णांक i = 0; i < d->अंक_frames * d->cursor_तथ्य.custom.images_per_frame; ++i) {
            अगर (d->cursor_तथ्य.custom.images[i].बफर_2) {
                wl_बफर_destroy(d->cursor_तथ्य.custom.images[i].बफर_2);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

अटल व्योम Wayland_FreeCursor(SDL_Cursor *cursor)
{
    अगर (!cursor) {
        वापस;
    }

    // Probably not a cursor we own
    अगर (!cursor->internal) {
        वापस;
    }

    Wayland_Free_Cursor_तथ्य(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

अटल क्रमागत wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    चयन (id) {
    हाल SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        अवरोध;
    शेष:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    वापस shape;
}

प्रकार काष्ठा Wayland_PointerObject
{
    जोड़
    {
        काष्ठा wl_pointer *wl_pointer;
        काष्ठा zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

अटल व्योम Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, स्थिर Wayland_PointerObject *obj, SDL_Window_तथ्य *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_तथ्य *viddata = SDL_GetVideoDevice()->internal;
    SDL_Cursor_तथ्य *cursor_तथ्य = cursor ? cursor->internal : शून्य;
    पूर्णांक dst_width = 0;
    पूर्णांक dst_height = 0;
    पूर्णांक hot_x;
    पूर्णांक hot_y;

    // Stop the frame callback for old animated cursors.
    अगर (cursor_तथ्य != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    अगर (cursor) {
        अगर (cursor_तथ्य == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            अगर (cursor_तथ्य->अंक_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            वापस;
        }

        अगर (cursor_तथ्य->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            अगर (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                अगर (state->surface) {
                    wl_surface_attach(state->surface, शून्य, 0, 0);
                    wl_surface_commit(state->surface);

                    अगर (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, शून्य, 0, 0);
                    } अन्यथा {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, शून्य, 0, 0);
                    }

                    अगर (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = शून्य;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = शून्य;
                }

                स्थिर क्रमागत wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_तथ्य->cursor_तथ्य.प्रणाली.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_तथ्य;
                state->current_frame = 0;

                वापस;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            अगर (!Wayland_GetSystemCursor(cursor_तथ्य, state, &dst_width, &hot_x, &hot_y)) {
                वापस;
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
            अगर (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_तथ्य->cursor_तथ्य.custom.width;
                dst_height = cursor_तथ्य->cursor_तथ्य.custom.height;
                hot_x = cursor_तथ्य->cursor_तथ्य.custom.hot_x;
                hot_y = cursor_तथ्य->cursor_तथ्य.custom.hot_y;
            } अन्यथा {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((पूर्णांक)SDL_lround((द्विगुन)cursor_तथ्य->cursor_तथ्य.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((पूर्णांक)SDL_lround((द्विगुन)cursor_तथ्य->cursor_तथ्य.custom.height / focus->pointer_scale.y), 1);
                hot_x = (पूर्णांक)SDL_lround((द्विगुन)cursor_तथ्य->cursor_तथ्य.custom.hot_x / focus->pointer_scale.x);
                hot_y = (पूर्णांक)SDL_lround((द्विगुन)cursor_तथ्य->cursor_तथ्य.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_तथ्य;

        अगर (!state->surface) {
            काष्ठा wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        काष्ठा wl_बफर *बफर_2 = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, बफर_2, 0, 0);
        state->current_frame = 0;

        अगर (state->scale != 1.0) {
            अगर (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } अन्यथा अगर (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = शून्य;
        }

        अगर (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } अन्यथा {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        अगर (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_VERSION) {
            wl_surface_damage_बफर(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } अन्यथा {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        अगर (cursor_तथ्य->अंक_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } अन्यथा {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = शून्य;

        अगर (state->surface) {
            wl_surface_attach(state->surface, शून्य, 0, 0);
            wl_surface_commit(state->surface);
        }

        अगर (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, शून्य, 0, 0);
        } अन्यथा {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, शून्य, 0, 0);
        }
    }
}

अटल व्योम Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

व्योम Wayland_DisplayUpdatePointerFocusedScale(SDL_Window_तथ्य *updated_window)
{
    SDL_Video_तथ्य *viddata = updated_window->wayland_तथ्य;
    SDL_WaylandSeat *seat;
    स्थिर द्विगुन new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        अगर (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            अगर (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            अगर (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                अगर (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

अटल bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        अगर (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            अगर (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } अन्यथा अगर (!seat->pointer.focus) {
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
            अगर (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } अन्यथा अगर (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    वापस true;
}

व्योम Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_Window_तथ्य *window, भग्न x, भग्न y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *d = vd->internal;

    अगर (seat->pointer.wl_pointer) {
        अगर (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            स्थिर wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            स्थिर wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } अन्यथा {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            अगर (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = शून्य;
                update_grabs = true;
            }
            अगर (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = शून्य;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            काष्ठा zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, शून्य,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            स्थिर wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            स्थिर wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            अगर (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        अगर (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

अटल bool Wayland_WarpMouseRelative(SDL_Window *window, भग्न x, भग्न y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *d = vd->internal;
    SDL_Window_तथ्य *wind = window->internal;
    SDL_WaylandSeat *seat;

    अगर (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            अगर (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } अन्यथा {
        वापस SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    वापस true;
}

अटल bool Wayland_WarpMouseGlobal(भग्न x, भग्न y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *d = vd->internal;
    SDL_WaylandSeat *seat;

    अगर (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_Window_तथ्य *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            अगर (wind) {
                SDL_Window *window = wind->sdlwindow;

                पूर्णांक abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                स्थिर SDL_FPoint p = { x, y };
                स्थिर SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                अगर (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } अन्यथा {
        वापस SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    वापस true;
}

अटल bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *तथ्य = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    अगर (!तथ्य->relative_pointer_manager) {
        वापस SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    अगर (!तथ्य->pointer_constraints) {
        वापस SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(तथ्य, शून्य);
    वापस true;
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
अटल SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(भग्न *x, भग्न *y)
{
    स्थिर SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags परिणाम = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    अगर (mouse->focus) {
        SDL_Video_तथ्य *video_तथ्य = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        पूर्णांक off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_तथ्य->seat_list, link) {
            परिणाम |= seat->pointer.buttons_pressed;
        }
    } अन्यथा {
        *x = 0.f;
        *y = 0.f;
    }

    वापस परिणाम;
}

#अगर 0  // TODO RECONNECT: See waylandvideo.c for more information!
अटल व्योम Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_तथ्य *vdata)
{
    SDL_Cursor_तथ्य *cdata = cursor->internal;

    // Probably not a cursor we own
    अगर (cdata == शून्य) {
        वापस;
    }

    Wayland_Free_Cursor_तथ्य(cdata);

    // We're not currently freeing this, so... yolo?
    अगर (cdata->shm_तथ्य != शून्य) {
        व्योम *old_तथ्य_pointer = cdata->shm_तथ्य;
        पूर्णांक stride = cdata->w * 4;

        create_बफर_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_तथ्य, old_तथ्य_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_तथ्य(cdata->surface, शून्य);
}

व्योम Wayland_RecreateCursors(व्योम)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_तथ्य *vdata = SDL_GetVideoDevice()->internal;

    अगर (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = शून्य;
        vdata->अंक_cursor_themes = 0;
    }

    अगर (mouse == शून्य) {
        वापस;
    }

    क्रम (cursor = mouse->cursors; cursor != शून्य; cursor = cursor->अग्र) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    अगर (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    अगर (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        अगर (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#पूर्ण_अगर // 0

व्योम Wayland_InitMouse(SDL_Video_तथ्य *तथ्य)
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

    SDL_Hit_Test_परिणाम r = SDL_HITTEST_NORMAL;
    जबतक (r <= SDL_HITTEST_RESIZE_बायाँ) {
        चयन (r) {
        हाल SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            अवरोध;
        हाल SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_शीर्ष:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_दायाँ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            अवरोध;
        हाल SDL_HITTEST_RESIZE_बायाँ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            अवरोध;
        }
        r++;
    }

#अगर_घोषित SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_तथ्य *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    अगर (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#पूर्ण_अगर

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

व्योम Wayland_FiniMouse(SDL_Video_तथ्य *तथ्य)
{
    क्रम (पूर्णांक i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = शून्य;
    }

    Wayland_FreeCursorThemes(तथ्य);

#अगर_घोषित SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#पूर्ण_अगर
}

व्योम Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

व्योम Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Window_तथ्य *pointer_focus = seat->pointer.focus;
    स्थिर Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

व्योम Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Window_तथ्य *pointer_focus = seat->pointer.focus;
    स्थिर Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    अगर (pointer_focus) {
        अगर (mouse->cursor_visible) {
            अगर (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                स्थिर SDL_Hit_Test_परिणाम rc = pointer_focus->hit_test_परिणाम;

                अगर (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } अन्यथा {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } अन्यथा {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, शून्य);
            }
        } अन्यथा {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, शून्य);
        }
    } अन्यथा {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

व्योम Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Window_तथ्य *tool_focus = tool->focus;
    स्थिर Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    अगर (tool_focus) {
        अगर (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            स्थिर bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            अगर (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } अन्यथा {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, शून्य);
            }
        } अन्यथा {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, शून्य);
        }
    } अन्यथा {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND

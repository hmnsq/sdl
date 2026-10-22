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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#അന്തര്ഭാവ <errno.h>

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../SDL_video_c.h"

#അന്തര്ഭാവ "../../core/unix/SDL_poll.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"
#അന്തര്ഭാവ "SDL_waylandevents_c.h"

#അന്തര്ഭാവ "wayland-cursor.h"
#അന്തര്ഭാവ "SDL_waylandmouse.h"
#അന്തര്ഭാവ "SDL_waylandshmbuffer.h"

#അന്തര്ഭാവ "cursor-shape-v1-client-protocol.h"
#അന്തര്ഭാവ "pointer-constraints-unstable-v1-client-protocol.h"
#അന്തര്ഭാവ "viewporter-client-protocol.h"
#അന്തര്ഭാവ "pointer-warp-v1-client-protocol.h"
#അന്തര്ഭാവ "tablet-v2-client-protocol.h"

#അന്തര്ഭാവ "../../SDL_hints_c.h"

സ്ഥിതം SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ഇടത് + 1];

സ്ഥിതം bool Wayland_SetRelativeMouseMode(bool enabled);

തരനിർവചനം ഘടന
{
    പൂർണ്ണസംഖ്യ width;
    പൂർണ്ണസംഖ്യ height;
    ഘടന wl_buffer *buffer;
} CustomCursorImage;

തരനിർവചനം ഘടന
{
    // The base dimensions of the cursor.
    പൂർണ്ണസംഖ്യ width;
    പൂർണ്ണസംഖ്യ height;
    പൂർണ്ണസംഖ്യ hot_x;
    പൂർണ്ണസംഖ്യ hot_y;

    പൂർണ്ണസംഖ്യ images_per_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

തരനിർവചനം ഘടന
{
    പൂർണ്ണസംഖ്യ size;
    ഘടന wl_list കണ്ണി;
    ഘടന wl_buffer *buffers[];
} Wayland_CachedSystemCursor;

തരനിർവചനം ഘടന
{
    SDL_SystemCursor id;
    ഘടന wl_list cursor_buffer_cache;
} Wayland_SystemCursor;

ഘടന SDL_CursorData
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 total_duration_ms;
    പൂർണ്ണസംഖ്യ അക്കം_frames;
    bool is_system_cursor;

    സംഘം
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_data;
};

സ്ഥിതം പൂർണ്ണസംഖ്യ dbus_cursor_size;
സ്ഥിതം അക്ഷരം *dbus_cursor_theme;

സ്ഥിതം ശൂന്യം Wayland_FreeCursorThemes(SDL_VideoData *vdata)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < vdata->അക്കം_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->അക്കം_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ശൂന്യ;
}

#ifdef SDL_USE_LIBDBUS

#അന്തര്ഭാവ "../../core/linux/SDL_dbus.h"

#define CURSOR_കണ്ണി        "org.freedesktop.portal.Desktop"
#define CURSOR_PATH        "/org/freedesktop/portal/desktop"
#define CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#define CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#define CURSOR_SIGNAL_NAME "SettingChanged"
#define CURSOR_SIZE_താക്കോൽ    "cursor-size"
#define CURSOR_THEME_താക്കോൽ   "cursor-theme"

സ്ഥിതം DBusMessage *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, സ്ഥിരം അക്ഷരം *താക്കോൽ)
{
    സ്ഥിതം സ്ഥിരം അക്ഷരം *iface = "org.gnome.desktop.interface";

    DBusMessage *reply = ശൂന്യ;
    DBusMessage *സന്ദേശം = dbus->message_new_method_call(CURSOR_കണ്ണി,
                                                     CURSOR_PATH,
                                                     CURSOR_INTERFACE,
                                                     "Read"); // Method

    എങ്കിൽ (സന്ദേശം) {
        എങ്കിൽ (dbus->message_append_args(സന്ദേശം, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &താക്കോൽ, DBUS_TYPE_INVALID)) {
            reply = dbus->connection_send_with_reply_and_block(dbus->session_conn, സന്ദേശം, DBUS_TIMEOUT_USE_DEFAULT, ശൂന്യ);
        }
        dbus->message_unref(സന്ദേശം);
    }

    തിരികെ reply;
}

സ്ഥിതം bool Wayland_ParseDBusReply(SDL_DBusContext *dbus, DBusMessage *reply, പൂർണ്ണസംഖ്യ type, ശൂന്യം *മൂല്യം)
{
    DBusMessageIter iter[3];

    dbus->message_iter_init(reply, &iter[0]);
    എങ്കിൽ (dbus->message_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        തിരികെ false;
    }

    dbus->message_iter_recurse(&iter[0], &iter[1]);
    എങ്കിൽ (dbus->message_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        തിരികെ false;
    }

    dbus->message_iter_recurse(&iter[1], &iter[2]);
    എങ്കിൽ (dbus->message_iter_get_arg_type(&iter[2]) != type) {
        തിരികെ false;
    }

    dbus->message_iter_get_basic(&iter[2], മൂല്യം);

    തിരികെ true;
}

സ്ഥിതം DBusHandlerResult Wayland_DBusCursorMessageFilter(DBusConnection *conn, DBusMessage *സന്ദേശം, ശൂന്യം *data)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_VideoData *vdata = (SDL_VideoData *)data;

    എങ്കിൽ (dbus->message_is_signal(സന്ദേശം, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBusMessageIter signal_iter, variant_iter;
        സ്ഥിരം അക്ഷരം *namespace, *താക്കോൽ;

        dbus->message_iter_init(സന്ദേശം, &signal_iter);
        // Check if the parameters are what we expect
        എങ്കിൽ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            പോകുക not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &namespace);
        എങ്കിൽ (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            പോകുക not_our_signal;
        }
        എങ്കിൽ (!dbus->message_iter_next(&signal_iter)) {
            പോകുക not_our_signal;
        }
        എങ്കിൽ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            പോകുക not_our_signal;
        }
        dbus->message_iter_get_basic(&signal_iter, &താക്കോൽ);
        എങ്കിൽ (SDL_strcmp(CURSOR_SIZE_താക്കോൽ, താക്കോൽ) == 0) {
            പൂർണ്ണസംഖ്യ new_cursor_size;

            എങ്കിൽ (!dbus->message_iter_next(&signal_iter)) {
                പോകുക not_our_signal;
            }
            എങ്കിൽ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                പോകുക not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            എങ്കിൽ (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                പോകുക not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_size);

            എങ്കിൽ (dbus_cursor_size != new_cursor_size) {
                dbus_cursor_size = new_cursor_size;
                SDL_RedrawCursor(); // Force cursor update
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strcmp(CURSOR_THEME_താക്കോൽ, താക്കോൽ) == 0) {
            സ്ഥിരം അക്ഷരം *new_cursor_theme = ശൂന്യ;

            എങ്കിൽ (!dbus->message_iter_next(&signal_iter)) {
                പോകുക not_our_signal;
            }
            എങ്കിൽ (dbus->message_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                പോകുക not_our_signal;
            }
            dbus->message_iter_recurse(&signal_iter, &variant_iter);
            എങ്കിൽ (dbus->message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                പോകുക not_our_signal;
            }
            dbus->message_iter_get_basic(&variant_iter, &new_cursor_theme);

            എങ്കിൽ (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                എങ്കിൽ (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } അല്ലെങ്കിൽ {
                    dbus_cursor_theme = ശൂന്യ;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } അല്ലെങ്കിൽ {
            പോകുക not_our_signal;
        }

        തിരികെ DBUS_HANDLER_RESULT_HANDLED;
    }

not_our_signal:
    തിരികെ DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

സ്ഥിതം ശൂന്യം Wayland_DBusInitCursorProperties(SDL_VideoData *vdata)
{
    DBusMessage *reply;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool add_filter = false;

    എങ്കിൽ (!dbus) {
        തിരികെ;
    }

    എങ്കിൽ ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_SIZE_താക്കോൽ))) {
        എങ്കിൽ (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_INT32, &dbus_cursor_size)) {
            add_filter = true;
        }
        dbus->message_unref(reply);
    }

    എങ്കിൽ ((reply = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_താക്കോൽ))) {
        സ്ഥിരം അക്ഷരം *temp = ശൂന്യ;
        എങ്കിൽ (Wayland_ParseDBusReply(dbus, reply, DBUS_TYPE_STRING, &temp)) {
            add_filter = true;

            എങ്കിൽ (temp) {
                dbus_cursor_theme = SDL_strdup(temp);
            }
        }
        dbus->message_unref(reply);
    }

    // Only add the filter if at least one of the settings we want is present.
    എങ്കിൽ (add_filter) {
        dbus->bus_add_match(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ശൂന്യ);
        dbus->connection_add_filter(dbus->session_conn, &Wayland_DBusCursorMessageFilter, vdata, ശൂന്യ);
        dbus->connection_flush(dbus->session_conn);
    }
}

സ്ഥിതം ശൂന്യം Wayland_DBusFinishCursorProperties(ശൂന്യം)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ശൂന്യ;
}

#endif

സ്ഥിതം ഘടന wl_buffer *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, പൂർണ്ണസംഖ്യ frame_index)
{
    SDL_CursorData *data = state->current_cursor;

    എങ്കിൽ (data) {
        എങ്കിൽ (!data->is_system_cursor) {
            സ്ഥിരം പൂർണ്ണസംഖ്യ offset = data->cursor_data.custom.images_per_frame * frame_index;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ശൂന്യ;
            സ്ഥിരം പൂർണ്ണസംഖ്യ target_area = SDL_lround(data->cursor_data.custom.width * data->cursor_data.custom.height * state->scale);
            പൂർണ്ണസംഖ്യ closest_area = 0;
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < data->cursor_data.custom.images_per_frame && closest_area < target_area && data->cursor_data.custom.images[offset + i].buffer; ++i) {
                closest = &data->cursor_data.custom.images[offset + i];
                closest_area = closest->width * closest->height;
            }

            തിരികെ closest ? closest->buffer : ശൂന്യ;
        } അല്ലെങ്കിൽ {
            തിരികെ ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_index];
        }
    }

    തിരികെ ശൂന്യ;
}

സ്ഥിതം ശൂന്യം cursor_frame_done(ശൂന്യം *data, ഘടന wl_callback *cb, uint32_t time);
സ്ഥിതം സ്ഥിരം ഘടന wl_callback_listener cursor_frame_listener = {
    cursor_frame_done
};

സ്ഥിതം ശൂന്യം cursor_frame_done(ശൂന്യം *data, ഘടന wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)data;
    എങ്കിൽ (!state->current_cursor) {
        തിരികെ;
    }

    Uint32 *frames = state->current_cursor->frame_durations_ms;
    SDL_CursorData *c = state->current_cursor;

    സ്ഥിരം Uint64 now = SDL_GetTicks();
    സ്ഥിരം Uint32 elapsed = (now - state->last_frame_callback_time_ms) % c->total_duration_ms;
    Uint32 advance = 0;
    പൂർണ്ണസംഖ്യ next = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    വേണ്ടി (Uint32 t = frames[next]; t <= state->current_frame_time_ms; t += frames[next]) {
        next = (next + 1) % c->അക്കം_frames;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        എങ്കിൽ (!frames[next]) {
            നിർത്തുക;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = ശൂന്യ;

    // Don't queue another callback if this frame time is infinite.
    എങ്കിൽ (frames[next]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, data);
    }

    state->current_frame_time_ms -= advance;
    state->last_frame_callback_time_ms = now;
    state->current_frame = next;

    ഘടന wl_buffer *buffer = Wayland_CursorStateGetFrame(state, next);
    wl_surface_attach(state->surface, buffer, 0, 0);

    എങ്കിൽ (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } അല്ലെങ്കിൽ {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

ശൂന്യം Wayland_CursorStateSetFrameCallback(SDL_WaylandCursorState *state, ശൂന്യം *userdata)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_add_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ശൂന്യം Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    Wayland_LockEventThread(viddata->event_thread_context);

    എങ്കിൽ (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = ശൂന്യ;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

സ്ഥിതം ശൂന്യം Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->last_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

സ്ഥിതം ശൂന്യം Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool lock)
{
    എങ്കിൽ (lock) {
        SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
        Wayland_LockEventThread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } അല്ലെങ്കിൽ {
        Wayland_CursorStateResetAnimationState(state);
    }
}

ശൂന്യം Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    എങ്കിൽ (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    എങ്കിൽ (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    എങ്കിൽ (state->surface) {
        wl_surface_attach(state->surface, ശൂന്യ, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

സ്ഥിതം Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_CursorData *cdata, ഘടന wl_cursor *cursor, പൂർണ്ണസംഖ്യ size)
{
    Wayland_CachedSystemCursor *cache = ശൂന്യ;

    // Is this cursor already cached at the target scale?
    എങ്കിൽ (!WAYLAND_wl_list_empty(&cdata->cursor_data.system.cursor_buffer_cache)) {
        Wayland_CachedSystemCursor *c = ശൂന്യ;
        wl_list_for_each (c, &cdata->cursor_data.system.cursor_buffer_cache, കണ്ണി) {
            എങ്കിൽ (c->size == size) {
                cache = c;
                നിർത്തുക;
            }
        }
    }

    എങ്കിൽ (!cache) {
        cache = SDL_calloc(1, വലുപ്പം(Wayland_CachedSystemCursor) + (വലുപ്പം(ഘടന wl_buffer *) * cdata->അക്കം_frames));

        cache->size = size;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < cdata->അക്കം_frames; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_buffer(cursor->images[i]);
        }

        WAYLAND_wl_list_തിരുകുക(&cdata->cursor_data.system.cursor_buffer_cache, &cache->കണ്ണി);
    }

    തിരികെ cache;
}

സ്ഥിതം bool Wayland_GetSystemCursor(SDL_CursorData *cdata, SDL_WaylandCursorState *state, പൂർണ്ണസംഖ്യ *dst_size, പൂർണ്ണസംഖ്യ *hot_x, പൂർണ്ണസംഖ്യ *hot_y)
{
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;
    ഘടന wl_cursor_theme *theme = ശൂന്യ;
    സ്ഥിരം അക്ഷരം *css_name = "default";
    സ്ഥിരം അക്ഷരം *fallback_name = ശൂന്യ;
    ഇരട്ട scale_factor = state->scale;
    പൂർണ്ണസംഖ്യ theme_size = dbus_cursor_size;

    // Fallback envvar if the DBus properties don't exist
    എങ്കിൽ (theme_size <= 0) {
        സ്ഥിരം അക്ഷരം *xcursor_size = SDL_getenv("XCURSOR_SIZE");
        എങ്കിൽ (xcursor_size) {
            theme_size = SDL_atoi(xcursor_size);
        }
    }
    എങ്കിൽ (theme_size <= 0) {
        theme_size = 24;
    }

    // First, find the appropriate theme based on the current scale...
    സ്ഥിരം പൂർണ്ണസംഖ്യ scaled_size = (പൂർണ്ണസംഖ്യ)SDL_lround(theme_size * scale_factor);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < vdata->അക്കം_cursor_themes; ++i) {
        എങ്കിൽ (vdata->cursor_themes[i].size == scaled_size) {
            theme = vdata->cursor_themes[i].theme;
            നിർത്തുക;
        }
    }
    എങ്കിൽ (!theme) {
        സ്ഥിരം അക്ഷരം *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                വലുപ്പം(SDL_WaylandCursorTheme) * (vdata->അക്കം_cursor_themes + 1));
        എങ്കിൽ (!new_cursor_themes) {
            തിരികെ false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        എങ്കിൽ (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_load(xcursor_theme, scaled_size, vdata->shm);
        vdata->cursor_themes[vdata->അക്കം_cursor_themes].size = scaled_size;
        vdata->cursor_themes[vdata->അക്കം_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_data.system.id, &fallback_name);
    ഘടന wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    എങ്കിൽ (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    എങ്കിൽ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    എങ്കിൽ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    എങ്കിൽ (!cursor) {
        തിരികെ false;
    }

    // ... Set the cursor data, finally.
    cdata->അക്കം_frames = cursor->image_എണ്ണം_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_size);
    state->system_cursor_handle = c;

    എങ്കിൽ (cursor->image_എണ്ണം_2 > 1 && !cdata->frame_durations_ms) {
        cdata->total_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_എണ്ണം_2, വലുപ്പം(Uint32));

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < cursor->image_എണ്ണം_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->total_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_size = SDL_lround(cursor->images[0]->width / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    തിരികെ true;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ surface_sort_callback(സ്ഥിരം ശൂന്യം *a, സ്ഥിരം ശൂന്യം *b)
{
    സ്ഥിരം SDL_Surface *s1 = *(സ്ഥിരം SDL_Surface **)a;
    സ്ഥിരം SDL_Surface *s2 = *(സ്ഥിരം SDL_Surface **)b;

    തിരികെ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

സ്ഥിതം SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, പൂർണ്ണസംഖ്യ frame_എണ്ണം, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (!cursor) {
        തിരികെ ശൂന്യ;
    }

    SDL_CursorData *data = ശൂന്യ;
    Wayland_SHMPool *shm_pool = ശൂന്യ;
    പൂർണ്ണസംഖ്യ pool_size = 0;
    പൂർണ്ണസംഖ്യ max_images = 0;
    bool is_അട്ടി = false;
    ഘടന SurfaceArray
    {
        SDL_Surface **surfaces;
        പൂർണ്ണസംഖ്യ എണ്ണം;
    } *surfaces = SDL_small_alloc(ഘടന SurfaceArray, frame_എണ്ണം, &is_അട്ടി);
    എങ്കിൽ (!surfaces) {
        പോകുക failed;
    }
    SDL_memset(surfaces, 0, വലുപ്പം(ഘടന SurfaceArray) * frame_എണ്ണം);

    // Calculate the total allocation size.
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame_എണ്ണം; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(frames[i].surface, &surfaces[i].എണ്ണം);
        എങ്കിൽ (!surfaces[i].surfaces) {
            പോകുക failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].എണ്ണം, വലുപ്പം(SDL_Surface *), surface_sort_callback);
        max_images = SDL_max(max_images, surfaces[i].എണ്ണം);
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < surfaces[i].എണ്ണം; ++j) {
            pool_size += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    data = SDL_calloc(1, വലുപ്പം(*data) + (വലുപ്പം(CustomCursorImage) * max_images * frame_എണ്ണം));
    എങ്കിൽ (!data) {
        പോകുക failed;
    }

    data->frame_durations_ms = SDL_calloc(frame_എണ്ണം, വലുപ്പം(Uint32));
    എങ്കിൽ (!data->frame_durations_ms) {
        പോകുക failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_size);
    എങ്കിൽ (!shm_pool) {
        പോകുക failed;
    }

    cursor->internal = data;
    data->cursor_data.custom.width = frames[0].surface->w;
    data->cursor_data.custom.height = frames[0].surface->h;
    data->cursor_data.custom.hot_x = hot_x;
    data->cursor_data.custom.hot_y = hot_y;
    data->cursor_data.custom.images_per_frame = max_images;
    data->അക്കം_frames = frame_എണ്ണം;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame_എണ്ണം; ++i) {
        data->frame_durations_ms[i] = frames[i].duration;
        എങ്കിൽ (data->total_duration_ms < SDL_MAX_UINT32) {
            എങ്കിൽ (data->frame_durations_ms[i] > 0) {
                data->total_duration_ms += data->frame_durations_ms[i];
            } അല്ലെങ്കിൽ {
                data->total_duration_ms = SDL_MAX_UINT32;
            }
        }

        സ്ഥിരം പൂർണ്ണസംഖ്യ offset = i * max_images;
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < surfaces[i].എണ്ണം; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            എങ്കിൽ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                എങ്കിൽ (!surface) {
                    പോകുക failed;
                }
            }

            data->cursor_data.custom.images[offset + j].width = surface->w;
            data->cursor_data.custom.images[offset + j].height = surface->h;

            ശൂന്യം *buf_data;
            data->cursor_data.custom.images[offset + j].buffer = Wayland_AllocBufferFromPool(shm_pool, surface->w, surface->h, &buf_data);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_data, surface->w * 4, true);

            എങ്കിൽ (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_അട്ടി);
    Wayland_ReleaseSHMPool(shm_pool);

    തിരികെ cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    എങ്കിൽ (data) {
        SDL_free(data->frame_durations_ms);
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < data->cursor_data.custom.images_per_frame * frame_എണ്ണം; ++i) {
            എങ്കിൽ (data->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(data->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(data);

    എങ്കിൽ (surfaces) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame_എണ്ണം; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_അട്ടി);
    }

    SDL_free(cursor);

    തിരികെ ശൂന്യ;
}

സ്ഥിതം SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    തിരികെ Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

സ്ഥിതം SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, വലുപ്പം(*cursor));

    എങ്കിൽ (cursor) {
        SDL_CursorData *cdata = SDL_calloc(1, വലുപ്പം(*cdata));
        എങ്കിൽ (!cdata) {
            SDL_free(cursor);
            തിരികെ ശൂന്യ;
        }
        cursor->internal = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_data.system.cursor_buffer_cache);
        cdata->cursor_data.system.id = id;
        cdata->is_system_cursor = true;
    }

    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *Wayland_CreateDefaultCursor(ശൂന്യം)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    തിരികെ Wayland_CreateSystemCursor(id);
}

സ്ഥിതം ശൂന്യം Wayland_FreeCursorData(SDL_CursorData *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_VideoData *video_data = video_device->internal;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_data->seat_list, link)
    {
        എങ്കിൽ (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            എങ്കിൽ (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, ശൂന്യ, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = ശൂന്യ;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            എങ്കിൽ (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                എങ്കിൽ (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, ശൂന്യ, 0, 0);
                }

                tool->cursor_state.current_cursor = ശൂന്യ;
            }
        }
    }

    എങ്കിൽ (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *temp;
        wl_list_for_each_safe(c, temp, &d->cursor_data.system.cursor_buffer_cache, കണ്ണി) {
            SDL_free(c);
        }
    } അല്ലെങ്കിൽ {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < d->അക്കം_frames * d->cursor_data.custom.images_per_frame; ++i) {
            എങ്കിൽ (d->cursor_data.custom.images[i].buffer) {
                wl_buffer_destroy(d->cursor_data.custom.images[i].buffer);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

സ്ഥിതം ശൂന്യം Wayland_FreeCursor(SDL_Cursor *cursor)
{
    എങ്കിൽ (!cursor) {
        തിരികെ;
    }

    // Probably not a cursor we own
    എങ്കിൽ (!cursor->internal) {
        തിരികെ;
    }

    Wayland_FreeCursorData(cursor->internal);

    SDL_free(cursor->internal);
    SDL_free(cursor);
}

സ്ഥിതം എണ്ണൽ wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    തിരഞ്ഞെടുപ്പ് (id) {
    അവസ്ഥ SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_PROGRESS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_PROGRESS;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_IN:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_IN;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_OUT;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    തിരികെ shape;
}

തരനിർവചനം ഘടന Wayland_PointerObject
{
    സംഘം
    {
        ഘടന wl_pointer *wl_pointer;
        ഘടന zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

സ്ഥിതം ശൂന്യം Wayland_CursorStateSetCursor(SDL_WaylandCursorState *state, സ്ഥിരം Wayland_PointerObject *obj, SDL_WindowData *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;
    SDL_CursorData *cursor_data = cursor ? cursor->internal : ശൂന്യ;
    പൂർണ്ണസംഖ്യ dst_width = 0;
    പൂർണ്ണസംഖ്യ dst_height = 0;
    പൂർണ്ണസംഖ്യ hot_x;
    പൂർണ്ണസംഖ്യ hot_y;

    // Stop the frame callback for old animated cursors.
    എങ്കിൽ (cursor_data != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    എങ്കിൽ (cursor) {
        എങ്കിൽ (cursor_data == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            എങ്കിൽ (cursor_data->അക്കം_frames > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            തിരികെ;
        }

        എങ്കിൽ (cursor_data->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            എങ്കിൽ (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                എങ്കിൽ (state->surface) {
                    wl_surface_attach(state->surface, ശൂന്യ, 0, 0);
                    wl_surface_commit(state->surface);

                    എങ്കിൽ (obj->is_pointer) {
                        wl_pointer_set_cursor(obj->wl_pointer, serial, ശൂന്യ, 0, 0);
                    } അല്ലെങ്കിൽ {
                        zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ശൂന്യ, 0, 0);
                    }

                    എങ്കിൽ (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ശൂന്യ;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ശൂന്യ;
                }

                സ്ഥിരം എണ്ണൽ wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_data->cursor_data.system.id);
                wp_cursor_shape_device_v1_set_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_data;
                state->current_frame = 0;

                തിരികെ;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
            എങ്കിൽ (!Wayland_GetSystemCursor(cursor_data, state, &dst_width, &hot_x, &hot_y)) {
                തിരികെ;
            }

            dst_height = dst_width;
        } അല്ലെങ്കിൽ {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            എങ്കിൽ (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_factor : 1.0;
                dst_width = cursor_data->cursor_data.custom.width;
                dst_height = cursor_data->cursor_data.custom.height;
                hot_x = cursor_data->cursor_data.custom.hot_x;
                hot_y = cursor_data->cursor_data.custom.hot_y;
            } അല്ലെങ്കിൽ {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_width = SDL_max((പൂർണ്ണസംഖ്യ)SDL_lround((ഇരട്ട)cursor_data->cursor_data.custom.width / focus->pointer_scale.x), 1);
                dst_height = SDL_max((പൂർണ്ണസംഖ്യ)SDL_lround((ഇരട്ട)cursor_data->cursor_data.custom.height / focus->pointer_scale.y), 1);
                hot_x = (പൂർണ്ണസംഖ്യ)SDL_lround((ഇരട്ട)cursor_data->cursor_data.custom.hot_x / focus->pointer_scale.x);
                hot_y = (പൂർണ്ണസംഖ്യ)SDL_lround((ഇരട്ട)cursor_data->cursor_data.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_data;

        എങ്കിൽ (!state->surface) {
            ഘടന wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ഘടന wl_buffer *buffer = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, buffer, 0, 0);
        state->current_frame = 0;

        എങ്കിൽ (state->scale != 1.0) {
            എങ്കിൽ (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_set_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_set_destination(state->viewport, dst_width, dst_height);
        } അല്ലെങ്കിൽ എങ്കിൽ (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ശൂന്യ;
        }

        എങ്കിൽ (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } അല്ലെങ്കിൽ {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        എങ്കിൽ (wl_surface_get_version(state->surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } അല്ലെങ്കിൽ {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        എങ്കിൽ (cursor_data->അക്കം_frames > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_CursorStateSetFrameCallback(state, state);
        }

        wl_surface_commit(state->surface);
    } അല്ലെങ്കിൽ {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = ശൂന്യ;

        എങ്കിൽ (state->surface) {
            wl_surface_attach(state->surface, ശൂന്യ, 0, 0);
            wl_surface_commit(state->surface);
        }

        എങ്കിൽ (obj->is_pointer) {
            wl_pointer_set_cursor(obj->wl_pointer, serial, ശൂന്യ, 0, 0);
        } അല്ലെങ്കിൽ {
            zwp_tablet_tool_v2_set_cursor(obj->wl_tool, serial, ശൂന്യ, 0, 0);
        }
    }
}

സ്ഥിതം ശൂന്യം Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

ശൂന്യം Wayland_DisplayUpdatePointerFocusedScale(SDL_WindowData *updated_window)
{
    SDL_VideoData *viddata = updated_window->waylandData;
    SDL_WaylandSeat *seat;
    സ്ഥിരം ഇരട്ട new_scale = SDL_min(updated_window->pointer_scale.x, updated_window->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        എങ്കിൽ (seat->pointer.focus == updated_window) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            എങ്കിൽ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            എങ്കിൽ (tool->focus == updated_window) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                എങ്കിൽ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

സ്ഥിതം bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        എങ്കിൽ (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            എങ്കിൽ (mouse->focus && mouse->focus->internal == seat->pointer.focus) {
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } അല്ലെങ്കിൽ എങ്കിൽ (!seat->pointer.focus) {
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
            എങ്കിൽ (tool->focus && (!mouse->focus || mouse->focus->internal == tool->focus)) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } അല്ലെങ്കിൽ എങ്കിൽ (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    തിരികെ true;
}

ശൂന്യം Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_WindowData *window, ദശാംശം x, ദശാംശം y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    എങ്കിൽ (seat->pointer.wl_pointer) {
        എങ്കിൽ (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            സ്ഥിരം wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / window->pointer_scale.x, 0, window->current.logical_width));
            സ്ഥിരം wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / window->pointer_scale.y, 0, window->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, window->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } അല്ലെങ്കിൽ {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            എങ്കിൽ (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = ശൂന്യ;
                update_grabs = true;
            }
            എങ്കിൽ (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = ശൂന്യ;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ഘടന zwp_locked_pointer_v1 *warp_lock =
                zwp_pointer_constraints_v1_lock_pointer(d->pointer_constraints, window->surface,
                                                        seat->pointer.wl_pointer, ശൂന്യ,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            സ്ഥിരം wl_fixed_t f_x = wl_fixed_from_double(x / window->pointer_scale.x);
            സ്ഥിരം wl_fixed_t f_y = wl_fixed_from_double(y / window->pointer_scale.y);
            zwp_locked_pointer_v1_set_cursor_position_hint(warp_lock, f_x, f_y);
            wl_surface_commit(window->surface);

            zwp_locked_pointer_v1_destroy(warp_lock);

            എങ്കിൽ (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        എങ്കിൽ (wl_pointer_get_version(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_VERSION) {
            SDL_SendMouseWarp(0, window->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

സ്ഥിതം bool Wayland_WarpMouseRelative(SDL_Window *window, ദശാംശം x, ദശാംശം y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat;

    എങ്കിൽ (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            എങ്കിൽ (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    തിരികെ true;
}

സ്ഥിതം bool Wayland_WarpMouseGlobal(ദശാംശം x, ദശാംശം y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;
    SDL_WaylandSeat *seat;

    എങ്കിൽ (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_WindowData *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            എങ്കിൽ (wind) {
                SDL_Window *window = wind->sdlwindow;

                പൂർണ്ണസംഖ്യ abs_x, abs_y;
                SDL_RelativeToGlobalForWindow(window, window->x, window->y, &abs_x, &abs_y);

                സ്ഥിരം SDL_FPoint p = { x, y };
                സ്ഥിരം SDL_FRect r = { abs_x, abs_y, window->w, window->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                എങ്കിൽ (SDL_PointInRectFloat(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    തിരികെ true;
}

സ്ഥിതം bool Wayland_SetRelativeMouseMode(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *data = vd->internal;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    എങ്കിൽ (!data->relative_pointer_manager) {
        തിരികെ SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    എങ്കിൽ (!data->pointer_constraints) {
        തിരികെ SDL_SetError("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(data, ശൂന്യ);
    തിരികെ true;
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
സ്ഥിതം SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(ദശാംശം *x, ദശാംശം *y)
{
    സ്ഥിരം SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags result = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    എങ്കിൽ (mouse->focus) {
        SDL_VideoData *video_data = SDL_GetVideoDevice()->internal;
        SDL_WaylandSeat *seat;
        പൂർണ്ണസംഖ്യ off_x, off_y;
        SDL_RelativeToGlobalForWindow(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_data->seat_list, link) {
            result |= seat->pointer.buttons_pressed;
        }
    } അല്ലെങ്കിൽ {
        *x = 0.f;
        *y = 0.f;
    }

    തിരികെ result;
}

#എങ്കിൽ 0  // TODO RECONNECT: See waylandvideo.c for more information!
സ്ഥിതം ശൂന്യം Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_VideoData *vdata)
{
    SDL_CursorData *cdata = cursor->internal;

    // Probably not a cursor we own
    എങ്കിൽ (cdata == ശൂന്യ) {
        തിരികെ;
    }

    Wayland_FreeCursorData(cdata);

    // We're not currently freeing this, so... yolo?
    എങ്കിൽ (cdata->shm_data != ശൂന്യ) {
        ശൂന്യം *old_data_pointer = cdata->shm_data;
        പൂർണ്ണസംഖ്യ stride = cdata->w * 4;

        create_buffer_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_data, old_data_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_set_user_data(cdata->surface, ശൂന്യ);
}

ശൂന്യം Wayland_RecreateCursors(ശൂന്യം)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_VideoData *vdata = SDL_GetVideoDevice()->internal;

    എങ്കിൽ (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ശൂന്യ;
        vdata->അക്കം_cursor_themes = 0;
    }

    എങ്കിൽ (mouse == ശൂന്യ) {
        തിരികെ;
    }

    വേണ്ടി (cursor = mouse->cursors; cursor != ശൂന്യ; cursor = cursor->next) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    എങ്കിൽ (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    എങ്കിൽ (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        എങ്കിൽ (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#endif // 0

ശൂന്യം Wayland_InitMouse(SDL_VideoData *data)
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
    ആകുമ്പോൾ (r <= SDL_HITTEST_RESIZE_ഇടത്) {
        തിരഞ്ഞെടുപ്പ് (r) {
        അവസ്ഥ SDL_HITTEST_NORMAL:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_മുകൾ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_വലത്:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_ഇടത്:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            നിർത്തുക;
        }
        r++;
    }

#ifdef SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_VideoData *d = vd->internal;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    എങ്കിൽ (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#endif

    SDL_SetDefaultCursor(Wayland_CreateDefaultCursor());
}

ശൂന്യം Wayland_FiniMouse(SDL_VideoData *data)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ശൂന്യ;
    }

    Wayland_FreeCursorThemes(data);

#ifdef SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#endif
}

ശൂന്യം Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

ശൂന്യം Wayland_SeatSetDefaultCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    സ്ഥിരം Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

ശൂന്യം Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *pointer_focus = seat->pointer.focus;
    സ്ഥിരം Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    എങ്കിൽ (pointer_focus) {
        എങ്കിൽ (mouse->cursor_visible) {
            എങ്കിൽ (!seat->pointer.relative_pointer || !mouse->relative_mode_hide_cursor) {
                സ്ഥിരം SDL_HitTestResult rc = pointer_focus->hit_test_result;

                എങ്കിൽ (seat->pointer.relative_pointer || rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } അല്ലെങ്കിൽ {
                    Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } അല്ലെങ്കിൽ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ശൂന്യ);
            }
        } അല്ലെങ്കിൽ {
            Wayland_CursorStateSetCursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, ശൂന്യ);
        }
    } അല്ലെങ്കിൽ {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

ശൂന്യം Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WindowData *tool_focus = tool->focus;
    സ്ഥിരം Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    എങ്കിൽ (tool_focus) {
        എങ്കിൽ (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            സ്ഥിരം bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE);

            എങ്കിൽ (!relative || !mouse->relative_mode_hide_cursor) {
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } അല്ലെങ്കിൽ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ശൂന്യ);
            }
        } അല്ലെങ്കിൽ {
            Wayland_CursorStateSetCursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ശൂന്യ);
        }
    } അല്ലെങ്കിൽ {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

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

ساکن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_بایاں + 1];

ساکن bool Wayland_سیٹ_Relative_Mouse_منوال(bool enabled);

قسمتعریف ساخت
{
    صحیح چوڑائی;
    صحیح اونچائی;
    ساخت wl_بفر *بفر_2;
} CustomCursorImage;

قسمتعریف ساخت
{
    // The base dimensions of the cursor.
    صحیح چوڑائی;
    صحیح اونچائی;
    صحیح hot_x;
    صحیح hot_y;

    صحیح images_فی_چوکھٹا;
    CustomCursorImage images[];
} Wayland_CustomCursor;

قسمتعریف ساخت
{
    صحیح سائز;
    ساخت wl_list گرہ;
    ساخت wl_بفر *buffers[];
} Wayland_CachedSystemCursor;

قسمتعریف ساخت
{
    SDL_SystemCursor id;
    ساخت wl_list cursor_بفر_cache;
} Wayland_SystemCursor;

ساخت SDL_Cursor_ڈیٹا
{
    // Cursor animation data.
    Uint32 *چوکھٹا_durations_ms;
    Uint32 کل_duration_ms;
    صحیح عدد_چوکھٹے;
    bool is_system_cursor;

    اتحاد
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_ڈیٹا;
};

ساکن صحیح dbus_cursor_سائز;
ساکن حرف *dbus_cursor_theme;

ساکن خالی Wayland_FreeCursorThemes(SDL_Video_ڈیٹا *vdata)
{
    برائے (صحیح i = 0; i < vdata->عدد_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->عدد_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = تہی;
}

#اگر_تعریف_شدہ SDL_USE_LIBDBUS

#شامل "../../core/linux/SDL_dbus.h"

#تعریف_کرو CURSOR_گرہ        "org.freedesktop.portal.Desktop"
#تعریف_کرو CURSOR_راستہ        "/org/freedesktop/portal/desktop"
#تعریف_کرو CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#تعریف_کرو CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#تعریف_کرو CURSOR_SIGNAL_NAME "SettingChanged"
#تعریف_کرو CURSOR_سائز_کلید    "cursor-size"
#تعریف_کرو CURSOR_THEME_کلید   "cursor-theme"

ساکن DBus_پیغام *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت حرف *کلید)
{
    ساکن ثابت حرف *iface = "org.gnome.desktop.interface";

    DBus_پیغام *جواب = تہی;
    DBus_پیغام *پیغام_2 = dbus->پیغام_new_طریقہ_call(CURSOR_گرہ,
                                                     CURSOR_راستہ,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //طریقہ

    اگر (پیغام_2) {
        اگر (dbus->پیغام_append_دلائل(پیغام_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &کلید, DBUS_TYPE_INVALID)) {
            جواب = dbus->connection_send_with_جواب_and_بلاک(dbus->session_conn, پیغام_2, DBUS_TIMEOUT_USE_DEFAULT, تہی);
        }
        dbus->پیغام_unref(پیغام_2);
    }

    واپس جواب;
}

ساکن bool Wayland_Parse_DBus_جواب(SDL_DBusContext *dbus, DBus_پیغام *جواب, صحیح type, خالی *قدر)
{
    DBus_پیغام_Iter iter[3];

    dbus->پیغام_iter_init(جواب, &iter[0]);
    اگر (dbus->پیغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        واپس false;
    }

    dbus->پیغام_iter_recurse(&iter[0], &iter[1]);
    اگر (dbus->پیغام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        واپس false;
    }

    dbus->پیغام_iter_recurse(&iter[1], &iter[2]);
    اگر (dbus->پیغام_iter_get_arg_type(&iter[2]) != type) {
        واپس false;
    }

    dbus->پیغام_iter_get_basic(&iter[2], قدر);

    واپس true;
}

ساکن DBus_Handler_نتیجہ Wayland_DBus_Cursor_پیغام_Filter(DBusConnection *conn, DBus_پیغام *پیغام_2, خالی *ڈیٹا)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_ڈیٹا *vdata = (SDL_Video_ڈیٹا *)ڈیٹا;

    اگر (dbus->پیغام_is_signal(پیغام_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_پیغام_Iter signal_iter, variant_iter;
        ثابت حرف *namespace, *کلید;

        dbus->پیغام_iter_init(پیغام_2, &signal_iter);
        // Check if the parameters are what we expect
        اگر (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            جاؤ not_our_signal;
        }
        dbus->پیغام_iter_get_basic(&signal_iter, &namespace);
        اگر (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            جاؤ not_our_signal;
        }
        اگر (!dbus->پیغام_iter_اگلا(&signal_iter)) {
            جاؤ not_our_signal;
        }
        اگر (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            جاؤ not_our_signal;
        }
        dbus->پیغام_iter_get_basic(&signal_iter, &کلید);
        اگر (SDL_strcmp(CURSOR_سائز_کلید, کلید) == 0) {
            صحیح new_cursor_سائز;

            اگر (!dbus->پیغام_iter_اگلا(&signal_iter)) {
                جاؤ not_our_signal;
            }
            اگر (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                جاؤ not_our_signal;
            }
            dbus->پیغام_iter_recurse(&signal_iter, &variant_iter);
            اگر (dbus->پیغام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                جاؤ not_our_signal;
            }
            dbus->پیغام_iter_get_basic(&variant_iter, &new_cursor_سائز);

            اگر (dbus_cursor_سائز != new_cursor_سائز) {
                dbus_cursor_سائز = new_cursor_سائز;
                SDL_RedrawCursor(); // Force cursor update
            }
        } ورنہ اگر (SDL_strcmp(CURSOR_THEME_کلید, کلید) == 0) {
            ثابت حرف *new_cursor_theme = تہی;

            اگر (!dbus->پیغام_iter_اگلا(&signal_iter)) {
                جاؤ not_our_signal;
            }
            اگر (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                جاؤ not_our_signal;
            }
            dbus->پیغام_iter_recurse(&signal_iter, &variant_iter);
            اگر (dbus->پیغام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                جاؤ not_our_signal;
            }
            dbus->پیغام_iter_get_basic(&variant_iter, &new_cursor_theme);

            اگر (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                اگر (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } ورنہ {
                    dbus_cursor_theme = تہی;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } ورنہ {
            جاؤ not_our_signal;
        }

        واپس DBUS_HANDLER_نتیجہ_HANDLED;
    }

not_our_signal:
    واپس DBUS_HANDLER_نتیجہ_NOT_YET_HANDLED;
}

ساکن خالی Wayland_DBusInitCursorProperties(SDL_Video_ڈیٹا *vdata)
{
    DBus_پیغام *جواب;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool جوڑو_filter = false;

    اگر (!dbus) {
        واپس;
    }

    اگر ((جواب = Wayland_ReadDBusProperty(dbus, CURSOR_سائز_کلید))) {
        اگر (Wayland_Parse_DBus_جواب(dbus, جواب, DBUS_TYPE_INT32, &dbus_cursor_سائز)) {
            جوڑو_filter = true;
        }
        dbus->پیغام_unref(جواب);
    }

    اگر ((جواب = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_کلید))) {
        ثابت حرف *عارضی = تہی;
        اگر (Wayland_Parse_DBus_جواب(dbus, جواب, DBUS_TYPE_STRING, &عارضی)) {
            جوڑو_filter = true;

            اگر (عارضی) {
                dbus_cursor_theme = SDL_strdup(عارضی);
            }
        }
        dbus->پیغام_unref(جواب);
    }

    // Only add the filter if at least one of the settings we want is present.
    اگر (جوڑو_filter) {
        dbus->bus_جوڑو_مطابقت(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            تہی);
        dbus->connection_جوڑو_filter(dbus->session_conn, &Wayland_DBus_Cursor_پیغام_Filter, vdata, تہی);
        dbus->connection_flush(dbus->session_conn);
    }
}

ساکن خالی Wayland_DBus_اختتام_Cursor_Properties(خالی)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = تہی;
}

#اگر_ختم

ساکن ساخت wl_بفر *Wayland_Cursor_State_Get_چوکھٹا(SDL_WaylandCursorState *state, صحیح چوکھٹا_اشاریہ_2)
{
    SDL_Cursor_ڈیٹا *ڈیٹا = state->current_cursor;

    اگر (ڈیٹا) {
        اگر (!ڈیٹا->is_system_cursor) {
            ثابت صحیح انحراف_2 = ڈیٹا->cursor_ڈیٹا.custom.images_فی_چوکھٹا * چوکھٹا_اشاریہ_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = تہی;
            ثابت صحیح ہدف_area = SDL_lround(ڈیٹا->cursor_ڈیٹا.custom.چوڑائی * ڈیٹا->cursor_ڈیٹا.custom.اونچائی * state->scale);
            صحیح closest_area = 0;
            برائے (صحیح i = 0; i < ڈیٹا->cursor_ڈیٹا.custom.images_فی_چوکھٹا && closest_area < ہدف_area && ڈیٹا->cursor_ڈیٹا.custom.images[انحراف_2 + i].بفر_2; ++i) {
                closest = &ڈیٹا->cursor_ڈیٹا.custom.images[انحراف_2 + i];
                closest_area = closest->چوڑائی * closest->اونچائی;
            }

            واپس closest ? closest->بفر_2 : تہی;
        } ورنہ {
            واپس ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[چوکھٹا_اشاریہ_2];
        }
    }

    واپس تہی;
}

ساکن خالی cursor_چوکھٹا_مکمل(خالی *ڈیٹا, ساخت wl_callback *cb, uint32_t وقت);
ساکن ثابت ساخت wl_callback_listener cursor_چوکھٹا_listener = {
    cursor_چوکھٹا_مکمل
};

ساکن خالی cursor_چوکھٹا_مکمل(خالی *ڈیٹا, ساخت wl_callback *cb, uint32_t وقت)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)ڈیٹا;
    اگر (!state->current_cursor) {
        واپس;
    }

    Uint32 *چوکھٹے = state->current_cursor->چوکھٹا_durations_ms;
    SDL_Cursor_ڈیٹا *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->آخری_چوکھٹا_callback_وقت_ms) % c->کل_duration_ms;
    Uint32 advance = 0;
    صحیح اگلا = state->current_چوکھٹا;

    state->current_چوکھٹا_وقت_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    برائے (Uint32 t = چوکھٹے[اگلا]; t <= state->current_چوکھٹا_وقت_ms; t += چوکھٹے[اگلا]) {
        اگلا = (اگلا + 1) % c->عدد_چوکھٹے;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        اگر (!چوکھٹے[اگلا]) {
            توڑو;
        }
    }

    wl_callback_destroy(cb);
    state->چوکھٹا_callback = تہی;

    // Don't queue another callback if this frame time is infinite.
    اگر (چوکھٹے[اگلا]) {
        state->چوکھٹا_callback = wl_surface_چوکھٹا(state->surface);
        wl_callback_جوڑو_listener(state->چوکھٹا_callback, &cursor_چوکھٹا_listener, ڈیٹا);
    }

    state->current_چوکھٹا_وقت_ms -= advance;
    state->آخری_چوکھٹا_callback_وقت_ms = now;
    state->current_چوکھٹا = اگلا;

    ساخت wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکھٹا(state, اگلا);
    wl_surface_attach(state->surface, بفر_2, 0, 0);

    اگر (wl_surface_get_نسخہ(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
        wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ورنہ {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

خالی Wayland_Cursor_State_سیٹ_چوکھٹا_Callback(SDL_WaylandCursorState *state, خالی *userdata)
{
    SDL_Video_ڈیٹا *viddata = SDL_GetVideoDevice()->اندرونی_2;
    Wayland_تالا_Event_Thread(viddata->event_thread_context);

    state->چوکھٹا_callback = wl_surface_چوکھٹا(state->surface);
    wl_callback_جوڑو_listener(state->چوکھٹا_callback, &cursor_چوکھٹا_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

خالی Wayland_Cursor_State_Destroy_چوکھٹا_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_ڈیٹا *viddata = SDL_GetVideoDevice()->اندرونی_2;
    Wayland_تالا_Event_Thread(viddata->event_thread_context);

    اگر (state->چوکھٹا_callback) {
        wl_callback_destroy(state->چوکھٹا_callback);
        state->چوکھٹا_callback = تہی;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ساکن خالی Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->آخری_چوکھٹا_callback_وقت_ms = SDL_GetTicks();
    state->current_چوکھٹا_وقت_ms = 0;
    state->current_چوکھٹا = 0;
}

ساکن خالی Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool تالا_2)
{
    اگر (تالا_2) {
        SDL_Video_ڈیٹا *viddata = SDL_GetVideoDevice()->اندرونی_2;
        Wayland_تالا_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } ورنہ {
        Wayland_CursorStateResetAnimationState(state);
    }
}

خالی Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
    اگر (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    اگر (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    اگر (state->surface) {
        wl_surface_attach(state->surface, تہی, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

ساکن Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_ڈیٹا *cdata, ساخت wl_cursor *cursor, صحیح سائز)
{
    Wayland_CachedSystemCursor *cache = تہی;

    // Is this cursor already cached at the target scale?
    اگر (!WAYLAND_wl_list_خالی_خانے(&cdata->cursor_ڈیٹا.system.cursor_بفر_cache)) {
        Wayland_CachedSystemCursor *c = تہی;
        wl_list_for_each (c, &cdata->cursor_ڈیٹا.system.cursor_بفر_cache, گرہ) {
            اگر (c->سائز == سائز) {
                cache = c;
                توڑو;
            }
        }
    }

    اگر (!cache) {
        cache = SDL_calloc(1, حجم(Wayland_CachedSystemCursor) + (حجم(ساخت wl_بفر *) * cdata->عدد_چوکھٹے));

        cache->سائز = سائز;
        برائے (صحیح i = 0; i < cdata->عدد_چوکھٹے; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_بفر(cursor->images[i]);
        }

        WAYLAND_wl_list_داخل_کرو(&cdata->cursor_ڈیٹا.system.cursor_بفر_cache, &cache->گرہ);
    }

    واپس cache;
}

ساکن bool Wayland_GetSystemCursor(SDL_Cursor_ڈیٹا *cdata, SDL_WaylandCursorState *state, صحیح *dst_سائز, صحیح *hot_x, صحیح *hot_y)
{
    SDL_Video_ڈیٹا *vdata = SDL_GetVideoDevice()->اندرونی_2;
    ساخت wl_cursor_theme *theme = تہی;
    ثابت حرف *css_name = "default";
    ثابت حرف *fallback_name = تہی;
    دوہرا scale_ضربی_عدد_2 = state->scale;
    صحیح theme_سائز = dbus_cursor_سائز;

    // Fallback envvar if the DBus properties don't exist
    اگر (theme_سائز <= 0) {
        ثابت حرف *xcursor_سائز = SDL_getenv("XCURSOR_SIZE");
        اگر (xcursor_سائز) {
            theme_سائز = SDL_atoi(xcursor_سائز);
        }
    }
    اگر (theme_سائز <= 0) {
        theme_سائز = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ثابت صحیح scaled_سائز = (صحیح)SDL_lround(theme_سائز * scale_ضربی_عدد_2);
    برائے (صحیح i = 0; i < vdata->عدد_cursor_themes; ++i) {
        اگر (vdata->cursor_themes[i].سائز == scaled_سائز) {
            theme = vdata->cursor_themes[i].theme;
            توڑو;
        }
    }
    اگر (!theme) {
        ثابت حرف *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                حجم(SDL_WaylandCursorTheme) * (vdata->عدد_cursor_themes + 1));
        اگر (!new_cursor_themes) {
            واپس false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        اگر (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_بھرو(xcursor_theme, scaled_سائز, vdata->shm);
        vdata->cursor_themes[vdata->عدد_cursor_themes].سائز = scaled_سائز;
        vdata->cursor_themes[vdata->عدد_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_ڈیٹا.system.id, &fallback_name);
    ساخت wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
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
        واپس false;
    }

    // ... Set the cursor data, finally.
    cdata->عدد_چوکھٹے = cursor->image_گنتی_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_سائز);
    state->system_cursor_handle = c;

    اگر (cursor->image_گنتی_2 > 1 && !cdata->چوکھٹا_durations_ms) {
        cdata->کل_duration_ms = 0;
        cdata->چوکھٹا_durations_ms = SDL_calloc(cursor->image_گنتی_2, حجم(Uint32));

        برائے (صحیح i = 0; i < cursor->image_گنتی_2; ++i) {
            cdata->چوکھٹا_durations_ms[i] = cursor->images[i]->delay;
            cdata->کل_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_سائز = SDL_lround(cursor->images[0]->چوڑائی / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    واپس true;
}

ساکن صحیح surface_ترتیب_دو_callback(ثابت خالی *a, ثابت خالی *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    واپس (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ساکن SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحیح چوکھٹا_گنتی, صحیح hot_x, صحیح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));
    اگر (!cursor) {
        واپس تہی;
    }

    SDL_Cursor_ڈیٹا *ڈیٹا = تہی;
    Wayland_SHMPool *shm_pool = تہی;
    صحیح pool_سائز = 0;
    صحیح max_images = 0;
    bool is_ڈھیر = false;
    ساخت SurfaceArray
    {
        SDL_Surface **surfaces;
        صحیح گنتی;
    } *surfaces = SDL_small_alloc(ساخت SurfaceArray, چوکھٹا_گنتی, &is_ڈھیر);
    اگر (!surfaces) {
        جاؤ failed;
    }
    SDL_memset(surfaces, 0, حجم(ساخت SurfaceArray) * چوکھٹا_گنتی);

    // Calculate the total allocation size.
    برائے (صحیح i = 0; i < چوکھٹا_گنتی; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(چوکھٹے[i].surface, &surfaces[i].گنتی);
        اگر (!surfaces[i].surfaces) {
            جاؤ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].گنتی, حجم(SDL_Surface *), surface_ترتیب_دو_callback);
        max_images = SDL_max(max_images, surfaces[i].گنتی);
        برائے (صحیح j = 0; j < surfaces[i].گنتی; ++j) {
            pool_سائز += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    ڈیٹا = SDL_calloc(1, حجم(*ڈیٹا) + (حجم(CustomCursorImage) * max_images * چوکھٹا_گنتی));
    اگر (!ڈیٹا) {
        جاؤ failed;
    }

    ڈیٹا->چوکھٹا_durations_ms = SDL_calloc(چوکھٹا_گنتی, حجم(Uint32));
    اگر (!ڈیٹا->چوکھٹا_durations_ms) {
        جاؤ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_سائز);
    اگر (!shm_pool) {
        جاؤ failed;
    }

    cursor->اندرونی_2 = ڈیٹا;
    ڈیٹا->cursor_ڈیٹا.custom.چوڑائی = چوکھٹے[0].surface->w;
    ڈیٹا->cursor_ڈیٹا.custom.اونچائی = چوکھٹے[0].surface->h;
    ڈیٹا->cursor_ڈیٹا.custom.hot_x = hot_x;
    ڈیٹا->cursor_ڈیٹا.custom.hot_y = hot_y;
    ڈیٹا->cursor_ڈیٹا.custom.images_فی_چوکھٹا = max_images;
    ڈیٹا->عدد_چوکھٹے = چوکھٹا_گنتی;

    برائے (صحیح i = 0; i < چوکھٹا_گنتی; ++i) {
        ڈیٹا->چوکھٹا_durations_ms[i] = چوکھٹے[i].duration;
        اگر (ڈیٹا->کل_duration_ms < SDL_MAX_UINT32) {
            اگر (ڈیٹا->چوکھٹا_durations_ms[i] > 0) {
                ڈیٹا->کل_duration_ms += ڈیٹا->چوکھٹا_durations_ms[i];
            } ورنہ {
                ڈیٹا->کل_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحیح انحراف_2 = i * max_images;
        برائے (صحیح j = 0; j < surfaces[i].گنتی; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            اگر (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                اگر (!surface) {
                    جاؤ failed;
                }
            }

            ڈیٹا->cursor_ڈیٹا.custom.images[انحراف_2 + j].چوڑائی = surface->w;
            ڈیٹا->cursor_ڈیٹا.custom.images[انحراف_2 + j].اونچائی = surface->h;

            خالی *buf_ڈیٹا;
            ڈیٹا->cursor_ڈیٹا.custom.images[انحراف_2 + j].بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, surface->w, surface->h, &buf_ڈیٹا);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_ڈیٹا, surface->w * 4, true);

            اگر (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ڈھیر);
    Wayland_ReleaseSHMPool(shm_pool);

    واپس cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    اگر (ڈیٹا) {
        SDL_free(ڈیٹا->چوکھٹا_durations_ms);
        برائے (صحیح i = 0; i < ڈیٹا->cursor_ڈیٹا.custom.images_فی_چوکھٹا * چوکھٹا_گنتی; ++i) {
            اگر (ڈیٹا->cursor_ڈیٹا.custom.images[i].بفر_2) {
                wl_بفر_destroy(ڈیٹا->cursor_ڈیٹا.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(ڈیٹا);

    اگر (surfaces) {
        برائے (صحیح i = 0; i < چوکھٹا_گنتی; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ڈھیر);
    }

    SDL_free(cursor);

    واپس تہی;
}

ساکن SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    SDL_Cursor_چوکھٹا_Info چوکھٹا = {
        surface, 0
    };

    واپس Wayland_CreateAnimatedCursor(&چوکھٹا, 1, hot_x, hot_y);
}

ساکن SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));

    اگر (cursor) {
        SDL_Cursor_ڈیٹا *cdata = SDL_calloc(1, حجم(*cdata));
        اگر (!cdata) {
            SDL_free(cursor);
            واپس تہی;
        }
        cursor->اندرونی_2 = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_ڈیٹا.system.cursor_بفر_cache);
        cdata->cursor_ڈیٹا.system.id = id;
        cdata->is_system_cursor = true;
    }

    واپس cursor;
}

ساکن SDL_Cursor *Wayland_CreateDefaultCursor(خالی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    واپس Wayland_CreateSystemCursor(id);
}

ساکن خالی Wayland_Free_Cursor_ڈیٹا(SDL_Cursor_ڈیٹا *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *video_ڈیٹا = video_device->اندرونی_2;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_ڈیٹا->seat_list, link)
    {
        اگر (seat->اشارہ_گر_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_چوکھٹا_Callback(&seat->اشارہ_گر_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            اگر (!d->is_system_cursor && seat->اشارہ_گر_2.cursor_state.surface) {
                wl_surface_attach(seat->اشارہ_گر_2.cursor_state.surface, تہی, 0, 0);
            }

            seat->اشارہ_گر_2.cursor_state.current_cursor = تہی;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            اگر (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_چوکھٹا_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                اگر (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->اشارہ_گر_2.cursor_state.surface, تہی, 0, 0);
                }

                tool->cursor_state.current_cursor = تہی;
            }
        }
    }

    اگر (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *عارضی;
        wl_list_for_each_محفوظ(c, عارضی, &d->cursor_ڈیٹا.system.cursor_بفر_cache, گرہ) {
            SDL_free(c);
        }
    } ورنہ {
        برائے (صحیح i = 0; i < d->عدد_چوکھٹے * d->cursor_ڈیٹا.custom.images_فی_چوکھٹا; ++i) {
            اگر (d->cursor_ڈیٹا.custom.images[i].بفر_2) {
                wl_بفر_destroy(d->cursor_ڈیٹا.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(d->چوکھٹا_durations_ms);
}

ساکن خالی Wayland_FreeCursor(SDL_Cursor *cursor)
{
    اگر (!cursor) {
        واپس;
    }

    // Probably not a cursor we own
    اگر (!cursor->اندرونی_2) {
        واپس;
    }

    Wayland_Free_Cursor_ڈیٹا(cursor->اندرونی_2);

    SDL_free(cursor->اندرونی_2);
    SDL_free(cursor);
}

ساکن شمار wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    انتخاب (id) {
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_متن:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_متن;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_پیش_رفت:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_پیش_رفت;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_اشارہ_گر:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_اشارہ_گر;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_VERTICAL_متن:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_متن;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ستون_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ستون_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_صف_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_صف_RESIZE;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ZOOM_اندر:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_اندر;
        توڑو;
    حالت SDL_SYSTEM_CURSOR_ZOOM_برآمد:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_برآمد;
        توڑو;
    طےشدہ:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    واپس shape;
}

قسمتعریف ساخت Wayland_اشارہ_گر_Object
{
    اتحاد
    {
        ساخت wl_اشارہ_گر *wl_اشارہ_گر;
        ساخت zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_اشارہ_گر;
} Wayland_اشارہ_گر_Object;

ساکن خالی Wayland_Cursor_State_سیٹ_Cursor(SDL_WaylandCursorState *state, ثابت Wayland_اشارہ_گر_Object *obj, SDL_کھڑکی_ڈیٹا *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_ڈیٹا *viddata = SDL_GetVideoDevice()->اندرونی_2;
    SDL_Cursor_ڈیٹا *cursor_ڈیٹا = cursor ? cursor->اندرونی_2 : تہی;
    صحیح dst_چوڑائی = 0;
    صحیح dst_اونچائی = 0;
    صحیح hot_x;
    صحیح hot_y;

    // Stop the frame callback for old animated cursors.
    اگر (cursor_ڈیٹا != state->current_cursor) {
        Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
    }

    اگر (cursor) {
        اگر (cursor_ڈیٹا == state->current_cursor && state->current_چوکھٹا >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            اگر (cursor_ڈیٹا->عدد_چوکھٹے > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            واپس;
        }

        اگر (cursor_ڈیٹا->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            اگر (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                اگر (state->surface) {
                    wl_surface_attach(state->surface, تہی, 0, 0);
                    wl_surface_commit(state->surface);

                    اگر (obj->is_اشارہ_گر) {
                        wl_اشارہ_گر_سیٹ_cursor(obj->wl_اشارہ_گر, serial, تہی, 0, 0);
                    } ورنہ {
                        zwp_tablet_tool_v2_سیٹ_cursor(obj->wl_tool, serial, تہی, 0, 0);
                    }

                    اگر (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = تہی;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = تہی;
                }

                ثابت شمار wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_ڈیٹا->cursor_ڈیٹا.system.id);
                wp_cursor_shape_device_v1_سیٹ_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_ڈیٹا;
                state->current_چوکھٹا = 0;

                واپس;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ضربی_عدد_2 : 1.0;
            اگر (!Wayland_GetSystemCursor(cursor_ڈیٹا, state, &dst_چوڑائی, &hot_x, &hot_y)) {
                واپس;
            }

            dst_اونچائی = dst_چوڑائی;
        } ورنہ {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            اگر (!focus || (focus->اشارہ_گر_scale.x == 1.0 && focus->اشارہ_گر_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ضربی_عدد_2 : 1.0;
                dst_چوڑائی = cursor_ڈیٹا->cursor_ڈیٹا.custom.چوڑائی;
                dst_اونچائی = cursor_ڈیٹا->cursor_ڈیٹا.custom.اونچائی;
                hot_x = cursor_ڈیٹا->cursor_ڈیٹا.custom.hot_x;
                hot_y = cursor_ڈیٹا->cursor_ڈیٹا.custom.hot_y;
            } ورنہ {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->اشارہ_گر_scale.x, focus->اشارہ_گر_scale.y);
                dst_چوڑائی = SDL_max((صحیح)SDL_lround((دوہرا)cursor_ڈیٹا->cursor_ڈیٹا.custom.چوڑائی / focus->اشارہ_گر_scale.x), 1);
                dst_اونچائی = SDL_max((صحیح)SDL_lround((دوہرا)cursor_ڈیٹا->cursor_ڈیٹا.custom.اونچائی / focus->اشارہ_گر_scale.y), 1);
                hot_x = (صحیح)SDL_lround((دوہرا)cursor_ڈیٹا->cursor_ڈیٹا.custom.hot_x / focus->اشارہ_گر_scale.x);
                hot_y = (صحیح)SDL_lround((دوہرا)cursor_ڈیٹا->cursor_ڈیٹا.custom.hot_y / focus->اشارہ_گر_scale.y);
            }

        }

        state->current_cursor = cursor_ڈیٹا;

        اگر (!state->surface) {
            ساخت wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        ساخت wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکھٹا(state, 0);
        wl_surface_attach(state->surface, بفر_2, 0, 0);
        state->current_چوکھٹا = 0;

        اگر (state->scale != 1.0) {
            اگر (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_سیٹ_ماخذ(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_سیٹ_destination(state->viewport, dst_چوڑائی, dst_اونچائی);
        } ورنہ اگر (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = تہی;
        }

        اگر (obj->is_اشارہ_گر) {
            wl_اشارہ_گر_سیٹ_cursor(obj->wl_اشارہ_گر, serial, state->surface, hot_x, hot_y);
        } ورنہ {
            zwp_tablet_tool_v2_سیٹ_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        اگر (wl_surface_get_نسخہ(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
            wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ورنہ {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        اگر (cursor_ڈیٹا->عدد_چوکھٹے > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_سیٹ_چوکھٹا_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } ورنہ {
        Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
        state->current_cursor = تہی;

        اگر (state->surface) {
            wl_surface_attach(state->surface, تہی, 0, 0);
            wl_surface_commit(state->surface);
        }

        اگر (obj->is_اشارہ_گر) {
            wl_اشارہ_گر_سیٹ_cursor(obj->wl_اشارہ_گر, serial, تہی, 0, 0);
        } ورنہ {
            zwp_tablet_tool_v2_سیٹ_cursor(obj->wl_tool, serial, تہی, 0, 0);
        }
    }
}

ساکن خالی Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
    state->current_چوکھٹا = -1;
}

خالی Wayland_Display_Update_اشارہ_گر_Focused_Scale(SDL_کھڑکی_ڈیٹا *updated_کھڑکی)
{
    SDL_Video_ڈیٹا *viddata = updated_کھڑکی->wayland_ڈیٹا;
    SDL_WaylandSeat *seat;
    ثابت دوہرا new_scale = SDL_min(updated_کھڑکی->اشارہ_گر_scale.x, updated_کھڑکی->اشارہ_گر_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        اگر (seat->اشارہ_گر_2.focus == updated_کھڑکی) {
            SDL_WaylandCursorState *state = &seat->اشارہ_گر_2.cursor_state;
            اگر (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            اگر (tool->focus == updated_کھڑکی) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                اگر (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

ساکن bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *d = vd->اندرونی_2;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_اشارہ_گر_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        اگر (seat->اشارہ_گر_2.wl_اشارہ_گر) {
            obj.wl_اشارہ_گر = seat->اشارہ_گر_2.wl_اشارہ_گر;
            obj.is_اشارہ_گر = true;
            اگر (mouse->focus && mouse->focus->اندرونی_2 == seat->اشارہ_گر_2.focus) {
                Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, seat->اشارہ_گر_2.focus, seat->اشارہ_گر_2.enter_serial, cursor);
            } ورنہ اگر (!seat->اشارہ_گر_2.focus) {
                Wayland_CursorStateResetCursor(&seat->اشارہ_گر_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_اشارہ_گر = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            اگر (tool->focus && (!mouse->focus || mouse->focus->اندرونی_2 == tool->focus)) {
                Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } ورنہ اگر (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    واپس true;
}

خالی Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_کھڑکی_ڈیٹا *کھڑکی, اعشاری x, اعشاری y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *d = vd->اندرونی_2;

    اگر (seat->اشارہ_گر_2.wl_اشارہ_گر) {
        اگر (d->wp_اشارہ_گر_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / کھڑکی->اشارہ_گر_scale.x, 0, کھڑکی->current.logical_چوڑائی));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / کھڑکی->اشارہ_گر_scale.y, 0, کھڑکی->current.logical_اونچائی));
            wp_اشارہ_گر_warp_v1_warp_اشارہ_گر(d->wp_اشارہ_گر_warp_v1, کھڑکی->surface, seat->اشارہ_گر_2.wl_اشارہ_گر, f_x, f_y, seat->اشارہ_گر_2.enter_serial);
        } ورنہ {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            اگر (seat->اشارہ_گر_2.confined_اشارہ_گر) {
                zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
                seat->اشارہ_گر_2.confined_اشارہ_گر = تہی;
                update_grabs = true;
            }
            اگر (seat->اشارہ_گر_2.locked_اشارہ_گر) {
                zwp_locked_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.locked_اشارہ_گر);
                seat->اشارہ_گر_2.locked_اشارہ_گر = تہی;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            ساخت zwp_locked_اشارہ_گر_v1 *warp_تالا =
                zwp_اشارہ_گر_constraints_v1_تالا_اشارہ_گر(d->اشارہ_گر_constraints, کھڑکی->surface,
                                                        seat->اشارہ_گر_2.wl_اشارہ_گر, تہی,
                                                        ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / کھڑکی->اشارہ_گر_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / کھڑکی->اشارہ_گر_scale.y);
            zwp_locked_اشارہ_گر_v1_سیٹ_cursor_position_hint(warp_تالا, f_x, f_y);
            wl_surface_commit(کھڑکی->surface);

            zwp_locked_اشارہ_گر_v1_destroy(warp_تالا);

            اگر (update_grabs) {
                Wayland_Seat_Update_اشارہ_گر_Grab(seat);
            }
        }

        اگر (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) < WL_اشارہ_گر_WARP_SINCE_نسخہ) {
            SDL_SendMouseWarp(0, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, x, y);
        }
    }
}

ساکن bool Wayland_WarpMouseRelative(SDL_کھڑکی *کھڑکی, اعشاری x, اعشاری y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *d = vd->اندرونی_2;
    SDL_کھڑکی_ڈیٹا *wind = کھڑکی->اندرونی_2;
    SDL_WaylandSeat *seat;

    اگر (d->wp_اشارہ_گر_warp_v1 || d->اشارہ_گر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            اگر (wind == seat->اشارہ_گر_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } ورنہ {
        واپس SDL_سیٹ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    واپس true;
}

ساکن bool Wayland_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *d = vd->اندرونی_2;
    SDL_WaylandSeat *seat;

    اگر (d->wp_اشارہ_گر_warp_v1 || d->اشارہ_گر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_کھڑکی_ڈیٹا *wind = seat->اشارہ_گر_2.focus ? seat->اشارہ_گر_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            اگر (wind) {
                SDL_کھڑکی *کھڑکی = wind->sdlwindow;

                صحیح abs_x, abs_y;
                SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, کھڑکی->x, کھڑکی->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, کھڑکی->w, کھڑکی->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                اگر (SDL_نقطہ_اندر_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } ورنہ {
        واپس SDL_سیٹ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    واپس true;
}

ساکن bool Wayland_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *ڈیٹا = vd->اندرونی_2;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    اگر (!ڈیٹا->relative_اشارہ_گر_manager) {
        واپس SDL_سیٹ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    اگر (!ڈیٹا->اشارہ_گر_constraints) {
        واپس SDL_سیٹ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_اشارہ_گر_Grabs(ڈیٹا, تہی);
    واپس true;
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
ساکن SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(اعشاری *x, اعشاری *y)
{
    ثابت SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags نتیجہ = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    اگر (mouse->focus) {
        SDL_Video_ڈیٹا *video_ڈیٹا = SDL_GetVideoDevice()->اندرونی_2;
        SDL_WaylandSeat *seat;
        صحیح off_x, off_y;
        SDL_Relative_مقصد_Global_For_کھڑکی(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_ڈیٹا->seat_list, link) {
            نتیجہ |= seat->اشارہ_گر_2.buttons_pressed;
        }
    } ورنہ {
        *x = 0.f;
        *y = 0.f;
    }

    واپس نتیجہ;
}

#اگر 0  // TODO RECONNECT: See waylandvideo.c for more information!
ساکن خالی Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_ڈیٹا *vdata)
{
    SDL_Cursor_ڈیٹا *cdata = cursor->اندرونی_2;

    // Probably not a cursor we own
    اگر (cdata == تہی) {
        واپس;
    }

    Wayland_Free_Cursor_ڈیٹا(cdata);

    // We're not currently freeing this, so... yolo?
    اگر (cdata->shm_ڈیٹا != تہی) {
        خالی *old_ڈیٹا_اشارہ_گر = cdata->shm_ڈیٹا;
        صحیح stride = cdata->w * 4;

        create_بفر_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_ڈیٹا, old_ڈیٹا_اشارہ_گر, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_سیٹ_user_ڈیٹا(cdata->surface, تہی);
}

خالی Wayland_RecreateCursors(خالی)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_ڈیٹا *vdata = SDL_GetVideoDevice()->اندرونی_2;

    اگر (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = تہی;
        vdata->عدد_cursor_themes = 0;
    }

    اگر (mouse == تہی) {
        واپس;
    }

    برائے (cursor = mouse->cursors; cursor != تہی; cursor = cursor->اگلا) {
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
#اگر_ختم // 0

خالی Wayland_InitMouse(SDL_Video_ڈیٹا *ڈیٹا)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->سیٹ_Relative_Mouse_منوال = Wayland_سیٹ_Relative_Mouse_منوال;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_کامیابی_Test_نتیجہ r = SDL_HITTEST_معمول;
    جب (r <= SDL_HITTEST_RESIZE_بایاں) {
        انتخاب (r) {
        حالت SDL_HITTEST_معمول:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            توڑو;
        حالت SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            توڑو;
        حالت SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_چوٹی:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_دایاں:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            توڑو;
        حالت SDL_HITTEST_RESIZE_بایاں:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            توڑو;
        }
        r++;
    }

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_ڈیٹا *d = vd->اندرونی_2;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    اگر (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#اگر_ختم

    SDL_سیٹ_Default_Cursor(Wayland_CreateDefaultCursor());
}

خالی Wayland_FiniMouse(SDL_Video_ڈیٹا *ڈیٹا)
{
    برائے (صحیح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = تہی;
    }

    Wayland_FreeCursorThemes(ڈیٹا);

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    Wayland_DBus_اختتام_Cursor_Properties();
#اگر_ختم
}

خالی Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->اشارہ_گر_2.cursor_state);
}

خالی Wayland_Seat_سیٹ_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کھڑکی_ڈیٹا *اشارہ_گر_focus = seat->اشارہ_گر_2.focus;
    ثابت Wayland_اشارہ_گر_Object obj = {
        .wl_اشارہ_گر = seat->اشارہ_گر_2.wl_اشارہ_گر,
        .is_اشارہ_گر = true
    };

    Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, mouse->def_cursor);
}

خالی Wayland_Seat_Update_اشارہ_گر_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کھڑکی_ڈیٹا *اشارہ_گر_focus = seat->اشارہ_گر_2.focus;
    ثابت Wayland_اشارہ_گر_Object obj = {
        .wl_اشارہ_گر = seat->اشارہ_گر_2.wl_اشارہ_گر,
        .is_اشارہ_گر = true
    };

    اگر (اشارہ_گر_focus) {
        اگر (mouse->cursor_visible) {
            اگر (!seat->اشارہ_گر_2.relative_اشارہ_گر || !mouse->relative_منوال_hide_cursor) {
                ثابت SDL_کامیابی_Test_نتیجہ rc = اشارہ_گر_focus->کامیابی_test_نتیجہ;

                اگر (seat->اشارہ_گر_2.relative_اشارہ_گر || rc == SDL_HITTEST_معمول || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, mouse->cur_cursor);
                } ورنہ {
                    Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, sys_cursors[rc]);
                }
            } ورنہ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, تہی);
            }
        } ورنہ {
            Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, تہی);
        }
    } ورنہ {
        Wayland_CursorStateResetCursor(&seat->اشارہ_گر_2.cursor_state);
    }
}

خالی Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کھڑکی_ڈیٹا *tool_focus = tool->focus;
    ثابت Wayland_اشارہ_گر_Object obj = {
        .wl_tool = tool->wltool,
        .is_اشارہ_گر = false
    };

    اگر (tool_focus) {
        اگر (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال);

            اگر (!relative || !mouse->relative_منوال_hide_cursor) {
                Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } ورنہ {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, تہی);
            }
        } ورنہ {
            Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, تہی);
        }
    } ورنہ {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND

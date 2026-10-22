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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND

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

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_کاٻو + 1];

ساكن bool Wayland_سيٽ_Relative_Mouse_گهڻائي(bool enabled);

تعريفنوع بنية
{
    صحيح ويڪر;
    صحيح اوچائي;
    بنية wl_بفر *بفر_2;
} CustomCursorImage;

تعريفنوع بنية
{
    // The base dimensions of the cursor.
    صحيح ويڪر;
    صحيح اوچائي;
    صحيح hot_x;
    صحيح hot_y;

    صحيح images_في_چوکٺو;
    CustomCursorImage images[];
} Wayland_CustomCursor;

تعريفنوع بنية
{
    صحيح سائيز;
    بنية wl_list ڳنڍ;
    بنية wl_بفر *buffers[];
} Wayland_CachedSystemCursor;

تعريفنوع بنية
{
    SDL_SystemCursor id;
    بنية wl_list cursor_بفر_cache;
} Wayland_SystemCursor;

بنية SDL_Cursor_معلومات
{
    // Cursor animation data.
    Uint32 *چوکٺو_durations_ms;
    Uint32 ڪل_duration_ms;
    صحيح انگ_چوکٺا;
    bool is_system_cursor;

    اتحاد
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_معلومات;
};

ساكن صحيح dbus_cursor_سائيز;
ساكن حرف *dbus_cursor_theme;

ساكن فراغ Wayland_FreeCursorThemes(SDL_Video_معلومات *vdata)
{
    لكل (صحيح i = 0; i < vdata->انگ_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->انگ_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = عدم;
}

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS

#ضمن "../../core/linux/SDL_dbus.h"

#وصف_ڪريو CURSOR_ڳنڍ        "org.freedesktop.portal.Desktop"
#وصف_ڪريو CURSOR_رستو        "/org/freedesktop/portal/desktop"
#وصف_ڪريو CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#وصف_ڪريو CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#وصف_ڪريو CURSOR_SIGNAL_NAME "SettingChanged"
#وصف_ڪريو CURSOR_سائيز_ڪنجي    "cursor-size"
#وصف_ڪريو CURSOR_THEME_ڪنجي   "cursor-theme"

ساكن DBus_پيغام *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت حرف *ڪنجي)
{
    ساكن ثابت حرف *iface = "org.gnome.desktop.interface";

    DBus_پيغام *جواب = عدم;
    DBus_پيغام *نياپو = dbus->پيغام_new_طريقو_call(CURSOR_ڳنڍ,
                                                     CURSOR_رستو,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //طريقو

    إذا (نياپو) {
        إذا (dbus->پيغام_append_دليلون(نياپو, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &ڪنجي, DBUS_TYPE_INVALID)) {
            جواب = dbus->connection_send_with_جواب_and_بلاڪ(dbus->session_conn, نياپو, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        }
        dbus->پيغام_unref(نياپو);
    }

    أرجع جواب;
}

ساكن bool Wayland_Parse_DBus_جواب(SDL_DBusContext *dbus, DBus_پيغام *جواب, صحيح type, فراغ *قدر)
{
    DBus_پيغام_Iter iter[3];

    dbus->پيغام_iter_init(جواب, &iter[0]);
    إذا (dbus->پيغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->پيغام_iter_recurse(&iter[0], &iter[1]);
    إذا (dbus->پيغام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->پيغام_iter_recurse(&iter[1], &iter[2]);
    إذا (dbus->پيغام_iter_get_arg_type(&iter[2]) != type) {
        أرجع false;
    }

    dbus->پيغام_iter_get_basic(&iter[2], قدر);

    أرجع true;
}

ساكن DBus_Handler_نتيجو Wayland_DBus_Cursor_پيغام_Filter(DBusConnection *conn, DBus_پيغام *نياپو, فراغ *معلومات)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_معلومات *vdata = (SDL_Video_معلومات *)معلومات;

    إذا (dbus->پيغام_is_signal(نياپو, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_پيغام_Iter signal_iter, variant_iter;
        ثابت حرف *namespace, *ڪنجي;

        dbus->پيغام_iter_init(نياپو, &signal_iter);
        // Check if the parameters are what we expect
        إذا (dbus->پيغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->پيغام_iter_get_basic(&signal_iter, &namespace);
        إذا (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            اذهب not_our_signal;
        }
        إذا (!dbus->پيغام_iter_ايندڙ(&signal_iter)) {
            اذهب not_our_signal;
        }
        إذا (dbus->پيغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->پيغام_iter_get_basic(&signal_iter, &ڪنجي);
        إذا (SDL_strcmp(CURSOR_سائيز_ڪنجي, ڪنجي) == 0) {
            صحيح new_cursor_سائيز;

            إذا (!dbus->پيغام_iter_ايندڙ(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->پيغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->پيغام_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->پيغام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                اذهب not_our_signal;
            }
            dbus->پيغام_iter_get_basic(&variant_iter, &new_cursor_سائيز);

            إذا (dbus_cursor_سائيز != new_cursor_سائيز) {
                dbus_cursor_سائيز = new_cursor_سائيز;
                SDL_RedrawCursor(); // Force cursor update
            }
        } وإلا إذا (SDL_strcmp(CURSOR_THEME_ڪنجي, ڪنجي) == 0) {
            ثابت حرف *new_cursor_theme = عدم;

            إذا (!dbus->پيغام_iter_ايندڙ(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->پيغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->پيغام_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->پيغام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                اذهب not_our_signal;
            }
            dbus->پيغام_iter_get_basic(&variant_iter, &new_cursor_theme);

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

        أرجع DBUS_HANDLER_نتيجو_HANDLED;
    }

not_our_signal:
    أرجع DBUS_HANDLER_نتيجو_NOT_YET_HANDLED;
}

ساكن فراغ Wayland_DBusInitCursorProperties(SDL_Video_معلومات *vdata)
{
    DBus_پيغام *جواب;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool جوڙيو_filter = false;

    إذا (!dbus) {
        أرجع;
    }

    إذا ((جواب = Wayland_ReadDBusProperty(dbus, CURSOR_سائيز_ڪنجي))) {
        إذا (Wayland_Parse_DBus_جواب(dbus, جواب, DBUS_TYPE_INT32, &dbus_cursor_سائيز)) {
            جوڙيو_filter = true;
        }
        dbus->پيغام_unref(جواب);
    }

    إذا ((جواب = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_ڪنجي))) {
        ثابت حرف *عارضي = عدم;
        إذا (Wayland_Parse_DBus_جواب(dbus, جواب, DBUS_TYPE_STRING, &عارضي)) {
            جوڙيو_filter = true;

            إذا (عارضي) {
                dbus_cursor_theme = SDL_strdup(عارضي);
            }
        }
        dbus->پيغام_unref(جواب);
    }

    // Only add the filter if at least one of the settings we want is present.
    إذا (جوڙيو_filter) {
        dbus->bus_جوڙيو_ميلاپ(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            عدم);
        dbus->connection_جوڙيو_filter(dbus->session_conn, &Wayland_DBus_Cursor_پيغام_Filter, vdata, عدم);
        dbus->connection_flush(dbus->session_conn);
    }
}

ساكن فراغ Wayland_DBus_پڄاڻي_Cursor_Properties(فراغ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = عدم;
}

#جيڪڏهن_پورو

ساكن بنية wl_بفر *Wayland_Cursor_State_Get_چوکٺو(SDL_WaylandCursorState *state, صحيح چوکٺو_اشاريو_2)
{
    SDL_Cursor_معلومات *معلومات = state->current_cursor;

    إذا (معلومات) {
        إذا (!معلومات->is_system_cursor) {
            ثابت صحيح وٿي_2 = معلومات->cursor_معلومات.custom.images_في_چوکٺو * چوکٺو_اشاريو_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = عدم;
            ثابت صحيح هدف_area = SDL_lround(معلومات->cursor_معلومات.custom.ويڪر * معلومات->cursor_معلومات.custom.اوچائي * state->scale);
            صحيح closest_area = 0;
            لكل (صحيح i = 0; i < معلومات->cursor_معلومات.custom.images_في_چوکٺو && closest_area < هدف_area && معلومات->cursor_معلومات.custom.images[وٿي_2 + i].بفر_2; ++i) {
                closest = &معلومات->cursor_معلومات.custom.images[وٿي_2 + i];
                closest_area = closest->ويڪر * closest->اوچائي;
            }

            أرجع closest ? closest->بفر_2 : عدم;
        } وإلا {
            أرجع ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[چوکٺو_اشاريو_2];
        }
    }

    أرجع عدم;
}

ساكن فراغ cursor_چوکٺو_پورو(فراغ *معلومات, بنية wl_callback *cb, uint32_t وقت);
ساكن ثابت بنية wl_callback_listener cursor_چوکٺو_listener = {
    cursor_چوکٺو_پورو
};

ساكن فراغ cursor_چوکٺو_پورو(فراغ *معلومات, بنية wl_callback *cb, uint32_t وقت)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)معلومات;
    إذا (!state->current_cursor) {
        أرجع;
    }

    Uint32 *چوکٺا = state->current_cursor->چوکٺو_durations_ms;
    SDL_Cursor_معلومات *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->آخري_چوکٺو_callback_وقت_ms) % c->ڪل_duration_ms;
    Uint32 advance = 0;
    صحيح ايندڙ = state->current_چوکٺو;

    state->current_چوکٺو_وقت_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    لكل (Uint32 t = چوکٺا[ايندڙ]; t <= state->current_چوکٺو_وقت_ms; t += چوکٺا[ايندڙ]) {
        ايندڙ = (ايندڙ + 1) % c->انگ_چوکٺا;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        إذا (!چوکٺا[ايندڙ]) {
            اكسر;
        }
    }

    wl_callback_destroy(cb);
    state->چوکٺو_callback = عدم;

    // Don't queue another callback if this frame time is infinite.
    إذا (چوکٺا[ايندڙ]) {
        state->چوکٺو_callback = wl_surface_چوکٺو(state->surface);
        wl_callback_جوڙيو_listener(state->چوکٺو_callback, &cursor_چوکٺو_listener, معلومات);
    }

    state->current_چوکٺو_وقت_ms -= advance;
    state->آخري_چوکٺو_callback_وقت_ms = now;
    state->current_چوکٺو = ايندڙ;

    بنية wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکٺو(state, ايندڙ);
    wl_surface_attach(state->surface, بفر_2, 0, 0);

    إذا (wl_surface_get_نسخو(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخو) {
        wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

فراغ Wayland_Cursor_State_سيٽ_چوکٺو_Callback(SDL_WaylandCursorState *state, فراغ *userdata)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->اندروني;
    Wayland_تالو_Event_Thread(viddata->event_thread_context);

    state->چوکٺو_callback = wl_surface_چوکٺو(state->surface);
    wl_callback_جوڙيو_listener(state->چوکٺو_callback, &cursor_چوکٺو_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

فراغ Wayland_Cursor_State_Destroy_چوکٺو_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->اندروني;
    Wayland_تالو_Event_Thread(viddata->event_thread_context);

    إذا (state->چوکٺو_callback) {
        wl_callback_destroy(state->چوکٺو_callback);
        state->چوکٺو_callback = عدم;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ساكن فراغ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->آخري_چوکٺو_callback_وقت_ms = SDL_GetTicks();
    state->current_چوکٺو_وقت_ms = 0;
    state->current_چوکٺو = 0;
}

ساكن فراغ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool تالو_2)
{
    إذا (تالو_2) {
        SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->اندروني;
        Wayland_تالو_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } وإلا {
        Wayland_CursorStateResetAnimationState(state);
    }
}

فراغ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_چوکٺو_Callback(state);
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

ساكن Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_معلومات *cdata, بنية wl_cursor *cursor, صحيح سائيز)
{
    Wayland_CachedSystemCursor *cache = عدم;

    // Is this cursor already cached at the target scale?
    إذا (!WAYLAND_wl_list_خالي_جايون(&cdata->cursor_معلومات.system.cursor_بفر_cache)) {
        Wayland_CachedSystemCursor *c = عدم;
        wl_list_for_each (c, &cdata->cursor_معلومات.system.cursor_بفر_cache, ڳنڍ) {
            إذا (c->سائيز == سائيز) {
                cache = c;
                اكسر;
            }
        }
    }

    إذا (!cache) {
        cache = SDL_calloc(1, حجم(Wayland_CachedSystemCursor) + (حجم(بنية wl_بفر *) * cdata->انگ_چوکٺا));

        cache->سائيز = سائيز;
        لكل (صحيح i = 0; i < cdata->انگ_چوکٺا; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_بفر(cursor->images[i]);
        }

        WAYLAND_wl_list_وجهو(&cdata->cursor_معلومات.system.cursor_بفر_cache, &cache->ڳنڍ);
    }

    أرجع cache;
}

ساكن bool Wayland_GetSystemCursor(SDL_Cursor_معلومات *cdata, SDL_WaylandCursorState *state, صحيح *dst_سائيز, صحيح *hot_x, صحيح *hot_y)
{
    SDL_Video_معلومات *vdata = SDL_GetVideoDevice()->اندروني;
    بنية wl_cursor_theme *theme = عدم;
    ثابت حرف *css_name = "default";
    ثابت حرف *fallback_name = عدم;
    مزدوج scale_ضرب_ڪندڙ_2 = state->scale;
    صحيح theme_سائيز = dbus_cursor_سائيز;

    // Fallback envvar if the DBus properties don't exist
    إذا (theme_سائيز <= 0) {
        ثابت حرف *xcursor_سائيز = SDL_getenv("XCURSOR_SIZE");
        إذا (xcursor_سائيز) {
            theme_سائيز = SDL_atoi(xcursor_سائيز);
        }
    }
    إذا (theme_سائيز <= 0) {
        theme_سائيز = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ثابت صحيح scaled_سائيز = (صحيح)SDL_lround(theme_سائيز * scale_ضرب_ڪندڙ_2);
    لكل (صحيح i = 0; i < vdata->انگ_cursor_themes; ++i) {
        إذا (vdata->cursor_themes[i].سائيز == scaled_سائيز) {
            theme = vdata->cursor_themes[i].theme;
            اكسر;
        }
    }
    إذا (!theme) {
        ثابت حرف *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                حجم(SDL_WaylandCursorTheme) * (vdata->انگ_cursor_themes + 1));
        إذا (!new_cursor_themes) {
            أرجع false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        إذا (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_ڀريو(xcursor_theme, scaled_سائيز, vdata->shm);
        vdata->cursor_themes[vdata->انگ_cursor_themes].سائيز = scaled_سائيز;
        vdata->cursor_themes[vdata->انگ_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_معلومات.system.id, &fallback_name);
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
    cdata->انگ_چوکٺا = cursor->image_ڳڻپ_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_سائيز);
    state->system_cursor_handle = c;

    إذا (cursor->image_ڳڻپ_2 > 1 && !cdata->چوکٺو_durations_ms) {
        cdata->ڪل_duration_ms = 0;
        cdata->چوکٺو_durations_ms = SDL_calloc(cursor->image_ڳڻپ_2, حجم(Uint32));

        لكل (صحيح i = 0; i < cursor->image_ڳڻپ_2; ++i) {
            cdata->چوکٺو_durations_ms[i] = cursor->images[i]->delay;
            cdata->ڪل_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_سائيز = SDL_lround(cursor->images[0]->ويڪر / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    أرجع true;
}

ساكن صحيح surface_ترتيب_ڏيو_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ساكن SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_چوکٺو_Info *چوکٺا, صحيح چوکٺو_ڳڻپ, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_معلومات *معلومات = عدم;
    Wayland_SHMPool *shm_pool = عدم;
    صحيح pool_سائيز = 0;
    صحيح max_images = 0;
    bool is_ڍير = false;
    بنية SurfaceArray
    {
        SDL_Surface **surfaces;
        صحيح ڳڻپ;
    } *surfaces = SDL_small_alloc(بنية SurfaceArray, چوکٺو_ڳڻپ, &is_ڍير);
    إذا (!surfaces) {
        اذهب failed;
    }
    SDL_memset(surfaces, 0, حجم(بنية SurfaceArray) * چوکٺو_ڳڻپ);

    // Calculate the total allocation size.
    لكل (صحيح i = 0; i < چوکٺو_ڳڻپ; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(چوکٺا[i].surface, &surfaces[i].ڳڻپ);
        إذا (!surfaces[i].surfaces) {
            اذهب failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].ڳڻپ, حجم(SDL_Surface *), surface_ترتيب_ڏيو_callback);
        max_images = SDL_max(max_images, surfaces[i].ڳڻپ);
        لكل (صحيح j = 0; j < surfaces[i].ڳڻپ; ++j) {
            pool_سائيز += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    معلومات = SDL_calloc(1, حجم(*معلومات) + (حجم(CustomCursorImage) * max_images * چوکٺو_ڳڻپ));
    إذا (!معلومات) {
        اذهب failed;
    }

    معلومات->چوکٺو_durations_ms = SDL_calloc(چوکٺو_ڳڻپ, حجم(Uint32));
    إذا (!معلومات->چوکٺو_durations_ms) {
        اذهب failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_سائيز);
    إذا (!shm_pool) {
        اذهب failed;
    }

    cursor->اندروني = معلومات;
    معلومات->cursor_معلومات.custom.ويڪر = چوکٺا[0].surface->w;
    معلومات->cursor_معلومات.custom.اوچائي = چوکٺا[0].surface->h;
    معلومات->cursor_معلومات.custom.hot_x = hot_x;
    معلومات->cursor_معلومات.custom.hot_y = hot_y;
    معلومات->cursor_معلومات.custom.images_في_چوکٺو = max_images;
    معلومات->انگ_چوکٺا = چوکٺو_ڳڻپ;

    لكل (صحيح i = 0; i < چوکٺو_ڳڻپ; ++i) {
        معلومات->چوکٺو_durations_ms[i] = چوکٺا[i].duration;
        إذا (معلومات->ڪل_duration_ms < SDL_MAX_UINT32) {
            إذا (معلومات->چوکٺو_durations_ms[i] > 0) {
                معلومات->ڪل_duration_ms += معلومات->چوکٺو_durations_ms[i];
            } وإلا {
                معلومات->ڪل_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحيح وٿي_2 = i * max_images;
        لكل (صحيح j = 0; j < surfaces[i].ڳڻپ; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                إذا (!surface) {
                    اذهب failed;
                }
            }

            معلومات->cursor_معلومات.custom.images[وٿي_2 + j].ويڪر = surface->w;
            معلومات->cursor_معلومات.custom.images[وٿي_2 + j].اوچائي = surface->h;

            فراغ *buf_معلومات;
            معلومات->cursor_معلومات.custom.images[وٿي_2 + j].بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, surface->w, surface->h, &buf_معلومات);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_معلومات, surface->w * 4, true);

            إذا (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ڍير);
    Wayland_ReleaseSHMPool(shm_pool);

    أرجع cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    إذا (معلومات) {
        SDL_free(معلومات->چوکٺو_durations_ms);
        لكل (صحيح i = 0; i < معلومات->cursor_معلومات.custom.images_في_چوکٺو * چوکٺو_ڳڻپ; ++i) {
            إذا (معلومات->cursor_معلومات.custom.images[i].بفر_2) {
                wl_بفر_destroy(معلومات->cursor_معلومات.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(معلومات);

    إذا (surfaces) {
        لكل (صحيح i = 0; i < چوکٺو_ڳڻپ; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ڍير);
    }

    SDL_free(cursor);

    أرجع عدم;
}

ساكن SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_چوکٺو_Info چوکٺو = {
        surface, 0
    };

    أرجع Wayland_CreateAnimatedCursor(&چوکٺو, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));

    إذا (cursor) {
        SDL_Cursor_معلومات *cdata = SDL_calloc(1, حجم(*cdata));
        إذا (!cdata) {
            SDL_free(cursor);
            أرجع عدم;
        }
        cursor->اندروني = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_معلومات.system.cursor_بفر_cache);
        cdata->cursor_معلومات.system.id = id;
        cdata->is_system_cursor = true;
    }

    أرجع cursor;
}

ساكن SDL_Cursor *Wayland_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع Wayland_CreateSystemCursor(id);
}

ساكن فراغ Wayland_Free_Cursor_معلومات(SDL_Cursor_معلومات *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_معلومات *video_معلومات = video_device->اندروني;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_معلومات->seat_list, link)
    {
        إذا (seat->اشارو_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_چوکٺو_Callback(&seat->اشارو_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            إذا (!d->is_system_cursor && seat->اشارو_2.cursor_state.surface) {
                wl_surface_attach(seat->اشارو_2.cursor_state.surface, عدم, 0, 0);
            }

            seat->اشارو_2.cursor_state.current_cursor = عدم;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_چوکٺو_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                إذا (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->اشارو_2.cursor_state.surface, عدم, 0, 0);
                }

                tool->cursor_state.current_cursor = عدم;
            }
        }
    }

    إذا (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *عارضي;
        wl_list_for_each_محفوظ(c, عارضي, &d->cursor_معلومات.system.cursor_بفر_cache, ڳنڍ) {
            SDL_free(c);
        }
    } وإلا {
        لكل (صحيح i = 0; i < d->انگ_چوکٺا * d->cursor_معلومات.custom.images_في_چوکٺو; ++i) {
            إذا (d->cursor_معلومات.custom.images[i].بفر_2) {
                wl_بفر_destroy(d->cursor_معلومات.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(d->چوکٺو_durations_ms);
}

ساكن فراغ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        أرجع;
    }

    // Probably not a cursor we own
    إذا (!cursor->اندروني) {
        أرجع;
    }

    Wayland_Free_Cursor_معلومات(cursor->اندروني);

    SDL_free(cursor->اندروني);
    SDL_free(cursor);
}

ساكن تعداد wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    بدل (id) {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_متن:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_متن;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ترقي:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ترقي;
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
    حالة SDL_SYSTEM_CURSOR_اشارو:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_اشارو;
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
    حالة SDL_SYSTEM_CURSOR_VERTICAL_متن:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_متن;
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
    حالة SDL_SYSTEM_CURSOR_کانو_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_کانو_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_صف_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_صف_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_اندريون:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_اندريون;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_ٻاهريون:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_ٻاهريون;
        اكسر;
    افتراضي:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    أرجع shape;
}

تعريفنوع بنية Wayland_اشارو_Object
{
    اتحاد
    {
        بنية wl_اشارو *wl_اشارو;
        بنية zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_اشارو;
} Wayland_اشارو_Object;

ساكن فراغ Wayland_Cursor_State_سيٽ_Cursor(SDL_WaylandCursorState *state, ثابت Wayland_اشارو_Object *obj, SDL_دري_معلومات *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->اندروني;
    SDL_Cursor_معلومات *cursor_معلومات = cursor ? cursor->اندروني : عدم;
    صحيح dst_ويڪر = 0;
    صحيح dst_اوچائي = 0;
    صحيح hot_x;
    صحيح hot_y;

    // Stop the frame callback for old animated cursors.
    إذا (cursor_معلومات != state->current_cursor) {
        Wayland_Cursor_State_Destroy_چوکٺو_Callback(state);
    }

    إذا (cursor) {
        إذا (cursor_معلومات == state->current_cursor && state->current_چوکٺو >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            إذا (cursor_معلومات->انگ_چوکٺا > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            أرجع;
        }

        إذا (cursor_معلومات->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            إذا (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                إذا (state->surface) {
                    wl_surface_attach(state->surface, عدم, 0, 0);
                    wl_surface_commit(state->surface);

                    إذا (obj->is_اشارو) {
                        wl_اشارو_سيٽ_cursor(obj->wl_اشارو, serial, عدم, 0, 0);
                    } وإلا {
                        zwp_tablet_tool_v2_سيٽ_cursor(obj->wl_tool, serial, عدم, 0, 0);
                    }

                    إذا (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = عدم;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = عدم;
                }

                ثابت تعداد wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_معلومات->cursor_معلومات.system.id);
                wp_cursor_shape_device_v1_سيٽ_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_معلومات;
                state->current_چوکٺو = 0;

                أرجع;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ضرب_ڪندڙ_2 : 1.0;
            إذا (!Wayland_GetSystemCursor(cursor_معلومات, state, &dst_ويڪر, &hot_x, &hot_y)) {
                أرجع;
            }

            dst_اوچائي = dst_ويڪر;
        } وإلا {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            إذا (!focus || (focus->اشارو_scale.x == 1.0 && focus->اشارو_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ضرب_ڪندڙ_2 : 1.0;
                dst_ويڪر = cursor_معلومات->cursor_معلومات.custom.ويڪر;
                dst_اوچائي = cursor_معلومات->cursor_معلومات.custom.اوچائي;
                hot_x = cursor_معلومات->cursor_معلومات.custom.hot_x;
                hot_y = cursor_معلومات->cursor_معلومات.custom.hot_y;
            } وإلا {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->اشارو_scale.x, focus->اشارو_scale.y);
                dst_ويڪر = SDL_max((صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.ويڪر / focus->اشارو_scale.x), 1);
                dst_اوچائي = SDL_max((صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.اوچائي / focus->اشارو_scale.y), 1);
                hot_x = (صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.hot_x / focus->اشارو_scale.x);
                hot_y = (صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.hot_y / focus->اشارو_scale.y);
            }

        }

        state->current_cursor = cursor_معلومات;

        إذا (!state->surface) {
            بنية wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        بنية wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکٺو(state, 0);
        wl_surface_attach(state->surface, بفر_2, 0, 0);
        state->current_چوکٺو = 0;

        إذا (state->scale != 1.0) {
            إذا (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_سيٽ_ذريعو(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_سيٽ_destination(state->viewport, dst_ويڪر, dst_اوچائي);
        } وإلا إذا (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = عدم;
        }

        إذا (obj->is_اشارو) {
            wl_اشارو_سيٽ_cursor(obj->wl_اشارو, serial, state->surface, hot_x, hot_y);
        } وإلا {
            zwp_tablet_tool_v2_سيٽ_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        إذا (wl_surface_get_نسخو(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخو) {
            wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        إذا (cursor_معلومات->انگ_چوکٺا > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_سيٽ_چوکٺو_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } وإلا {
        Wayland_Cursor_State_Destroy_چوکٺو_Callback(state);
        state->current_cursor = عدم;

        إذا (state->surface) {
            wl_surface_attach(state->surface, عدم, 0, 0);
            wl_surface_commit(state->surface);
        }

        إذا (obj->is_اشارو) {
            wl_اشارو_سيٽ_cursor(obj->wl_اشارو, serial, عدم, 0, 0);
        } وإلا {
            zwp_tablet_tool_v2_سيٽ_cursor(obj->wl_tool, serial, عدم, 0, 0);
        }
    }
}

ساكن فراغ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_چوکٺو_Callback(state);
    state->current_چوکٺو = -1;
}

فراغ Wayland_Display_Update_اشارو_Focused_Scale(SDL_دري_معلومات *updated_دري)
{
    SDL_Video_معلومات *viddata = updated_دري->wayland_معلومات;
    SDL_WaylandSeat *seat;
    ثابت مزدوج new_scale = SDL_min(updated_دري->اشارو_scale.x, updated_دري->اشارو_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        إذا (seat->اشارو_2.focus == updated_دري) {
            SDL_WaylandCursorState *state = &seat->اشارو_2.cursor_state;
            إذا (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_اشارو_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == updated_دري) {
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
    SDL_Video_معلومات *d = vd->اندروني;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_اشارو_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->اشارو_2.wl_اشارو) {
            obj.wl_اشارو = seat->اشارو_2.wl_اشارو;
            obj.is_اشارو = true;
            إذا (mouse->focus && mouse->focus->اندروني == seat->اشارو_2.focus) {
                Wayland_Cursor_State_سيٽ_Cursor(&seat->اشارو_2.cursor_state, &obj, seat->اشارو_2.focus, seat->اشارو_2.enter_serial, cursor);
            } وإلا إذا (!seat->اشارو_2.focus) {
                Wayland_CursorStateResetCursor(&seat->اشارو_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_اشارو = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            إذا (tool->focus && (!mouse->focus || mouse->focus->اندروني == tool->focus)) {
                Wayland_Cursor_State_سيٽ_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا إذا (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    أرجع true;
}

فراغ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_دري_معلومات *دري, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->اندروني;

    إذا (seat->اشارو_2.wl_اشارو) {
        إذا (d->wp_اشارو_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / دري->اشارو_scale.x, 0, دري->current.logical_ويڪر));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / دري->اشارو_scale.y, 0, دري->current.logical_اوچائي));
            wp_اشارو_warp_v1_warp_اشارو(d->wp_اشارو_warp_v1, دري->surface, seat->اشارو_2.wl_اشارو, f_x, f_y, seat->اشارو_2.enter_serial);
        } وإلا {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            إذا (seat->اشارو_2.confined_اشارو) {
                zwp_confined_اشارو_v1_destroy(seat->اشارو_2.confined_اشارو);
                seat->اشارو_2.confined_اشارو = عدم;
                update_grabs = true;
            }
            إذا (seat->اشارو_2.locked_اشارو) {
                zwp_locked_اشارو_v1_destroy(seat->اشارو_2.locked_اشارو);
                seat->اشارو_2.locked_اشارو = عدم;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            بنية zwp_locked_اشارو_v1 *warp_تالو =
                zwp_اشارو_constraints_v1_تالو_اشارو(d->اشارو_constraints, دري->surface,
                                                        seat->اشارو_2.wl_اشارو, عدم,
                                                        ZWP_اشارو_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / دري->اشارو_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / دري->اشارو_scale.y);
            zwp_locked_اشارو_v1_سيٽ_cursor_position_hint(warp_تالو, f_x, f_y);
            wl_surface_commit(دري->surface);

            zwp_locked_اشارو_v1_destroy(warp_تالو);

            إذا (update_grabs) {
                Wayland_Seat_Update_اشارو_Grab(seat);
            }
        }

        إذا (wl_اشارو_get_نسخو(seat->اشارو_2.wl_اشارو) < WL_اشارو_WARP_SINCE_نسخو) {
            SDL_SendMouseWarp(0, دري->sdlwindow, seat->اشارو_2.sdl_id, x, y);
        }
    }
}

ساكن bool Wayland_WarpMouseRelative(SDL_دري *دري, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->اندروني;
    SDL_دري_معلومات *wind = دري->اندروني;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشارو_warp_v1 || d->اشارو_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (wind == seat->اشارو_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } وإلا {
        أرجع SDL_سيٽ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->اندروني;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشارو_warp_v1 || d->اشارو_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_دري_معلومات *wind = seat->اشارو_2.focus ? seat->اشارو_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            إذا (wind) {
                SDL_دري *دري = wind->sdlwindow;

                صحيح abs_x, abs_y;
                SDL_Relative_منزل_Global_For_دري(دري, دري->x, دري->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, دري->w, دري->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                إذا (SDL_نقطو_اندريون_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } وإلا {
        أرجع SDL_سيٽ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_سيٽ_Relative_Mouse_گهڻائي(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *معلومات = vd->اندروني;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    إذا (!معلومات->relative_اشارو_manager) {
        أرجع SDL_سيٽ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    إذا (!معلومات->اشارو_constraints) {
        أرجع SDL_سيٽ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_اشارو_Grabs(معلومات, عدم);
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
    SDL_MouseButtonFlags نتيجو = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    إذا (mouse->focus) {
        SDL_Video_معلومات *video_معلومات = SDL_GetVideoDevice()->اندروني;
        SDL_WaylandSeat *seat;
        صحيح off_x, off_y;
        SDL_Relative_منزل_Global_For_دري(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_معلومات->seat_list, link) {
            نتيجو |= seat->اشارو_2.buttons_pressed;
        }
    } وإلا {
        *x = 0.f;
        *y = 0.f;
    }

    أرجع نتيجو;
}

#إذا 0  // TODO RECONNECT: See waylandvideo.c for more information!
ساكن فراغ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_معلومات *vdata)
{
    SDL_Cursor_معلومات *cdata = cursor->اندروني;

    // Probably not a cursor we own
    إذا (cdata == عدم) {
        أرجع;
    }

    Wayland_Free_Cursor_معلومات(cdata);

    // We're not currently freeing this, so... yolo?
    إذا (cdata->shm_معلومات != عدم) {
        فراغ *old_معلومات_اشارو = cdata->shm_معلومات;
        صحيح stride = cdata->w * 4;

        create_بفر_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_معلومات, old_معلومات_اشارو, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_سيٽ_user_معلومات(cdata->surface, عدم);
}

فراغ Wayland_RecreateCursors(فراغ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_معلومات *vdata = SDL_GetVideoDevice()->اندروني;

    إذا (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = عدم;
        vdata->انگ_cursor_themes = 0;
    }

    إذا (mouse == عدم) {
        أرجع;
    }

    لكل (cursor = mouse->cursors; cursor != عدم; cursor = cursor->ايندڙ) {
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
#جيڪڏهن_پورو // 0

فراغ Wayland_InitMouse(SDL_Video_معلومات *معلومات)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->سيٽ_Relative_Mouse_گهڻائي = Wayland_سيٽ_Relative_Mouse_گهڻائي;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_ڪاميابي_Test_نتيجو r = SDL_HITTEST_عام;
    طالما (r <= SDL_HITTEST_RESIZE_کاٻو) {
        بدل (r) {
        حالة SDL_HITTEST_عام:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_چوٽي:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_ساڄو:
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
        حالة SDL_HITTEST_RESIZE_کاٻو:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            اكسر;
        }
        r++;
    }

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->اندروني;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    إذا (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#جيڪڏهن_پورو

    SDL_سيٽ_Default_Cursor(Wayland_CreateDefaultCursor());
}

فراغ Wayland_FiniMouse(SDL_Video_معلومات *معلومات)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = عدم;
    }

    Wayland_FreeCursorThemes(معلومات);

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    Wayland_DBus_پڄاڻي_Cursor_Properties();
#جيڪڏهن_پورو
}

فراغ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->اشارو_2.cursor_state);
}

فراغ Wayland_Seat_سيٽ_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_دري_معلومات *اشارو_focus = seat->اشارو_2.focus;
    ثابت Wayland_اشارو_Object obj = {
        .wl_اشارو = seat->اشارو_2.wl_اشارو,
        .is_اشارو = true
    };

    Wayland_Cursor_State_سيٽ_Cursor(&seat->اشارو_2.cursor_state, &obj, اشارو_focus, seat->اشارو_2.enter_serial, mouse->def_cursor);
}

فراغ Wayland_Seat_Update_اشارو_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_دري_معلومات *اشارو_focus = seat->اشارو_2.focus;
    ثابت Wayland_اشارو_Object obj = {
        .wl_اشارو = seat->اشارو_2.wl_اشارو,
        .is_اشارو = true
    };

    إذا (اشارو_focus) {
        إذا (mouse->cursor_visible) {
            إذا (!seat->اشارو_2.relative_اشارو || !mouse->relative_گهڻائي_hide_cursor) {
                ثابت SDL_ڪاميابي_Test_نتيجو rc = اشارو_focus->ڪاميابي_test_نتيجو;

                إذا (seat->اشارو_2.relative_اشارو || rc == SDL_HITTEST_عام || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_سيٽ_Cursor(&seat->اشارو_2.cursor_state, &obj, اشارو_focus, seat->اشارو_2.enter_serial, mouse->cur_cursor);
                } وإلا {
                    Wayland_Cursor_State_سيٽ_Cursor(&seat->اشارو_2.cursor_state, &obj, اشارو_focus, seat->اشارو_2.enter_serial, sys_cursors[rc]);
                }
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سيٽ_Cursor(&seat->اشارو_2.cursor_state, &obj, اشارو_focus, seat->اشارو_2.enter_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_سيٽ_Cursor(&seat->اشارو_2.cursor_state, &obj, اشارو_focus, seat->اشارو_2.enter_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&seat->اشارو_2.cursor_state);
    }
}

فراغ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_دري_معلومات *tool_focus = tool->focus;
    ثابت Wayland_اشارو_Object obj = {
        .wl_tool = tool->wltool,
        .is_اشارو = false
    };

    إذا (tool_focus) {
        إذا (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_دري_MOUSE_RELATIVE_گهڻائي);

            إذا (!relative || !mouse->relative_گهڻائي_hide_cursor) {
                Wayland_Cursor_State_سيٽ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سيٽ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_سيٽ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND

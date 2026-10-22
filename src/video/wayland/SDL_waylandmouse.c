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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

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

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_کیڼ + 1];

ساكن bool Wayland_سېټ_Relative_Mouse_ډېرپېښ(bool enabled);

تعريفنوع بنية
{
    صحيح پلنوالی;
    صحيح لوړوالی;
    بنية wl_بفر *بفر_2;
} CustomCursorImage;

تعريفنوع بنية
{
    // The base dimensions of the cursor.
    صحيح پلنوالی;
    صحيح لوړوالی;
    صحيح hot_x;
    صحيح hot_y;

    صحيح images_فی_چوکاټ;
    CustomCursorImage images[];
} Wayland_CustomCursor;

تعريفنوع بنية
{
    صحيح اندازه;
    بنية wl_list غوټه;
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
    Uint32 *چوکاټ_durations_ms;
    Uint32 ټول_duration_ms;
    صحيح عدد_چوکاټونه;
    bool is_system_cursor;

    اتحاد
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_معلومات;
};

ساكن صحيح dbus_cursor_اندازه;
ساكن حرف *dbus_cursor_theme;

ساكن فراغ Wayland_FreeCursorThemes(SDL_Video_معلومات *vdata)
{
    لكل (صحيح i = 0; i < vdata->عدد_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->عدد_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = عدم;
}

#که_تعریف_شوی SDL_USE_LIBDBUS

#ضمن "../../core/linux/SDL_dbus.h"

#تعریف_کړه CURSOR_غوټه        "org.freedesktop.portal.Desktop"
#تعریف_کړه CURSOR_لار        "/org/freedesktop/portal/desktop"
#تعریف_کړه CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#تعریف_کړه CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#تعریف_کړه CURSOR_SIGNAL_NAME "SettingChanged"
#تعریف_کړه CURSOR_اندازه_کلی    "cursor-size"
#تعریف_کړه CURSOR_THEME_کلی   "cursor-theme"

ساكن DBus_پیغام *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت حرف *کلی)
{
    ساكن ثابت حرف *iface = "org.gnome.desktop.interface";

    DBus_پیغام *ځواب = عدم;
    DBus_پیغام *پیغام_2 = dbus->پیغام_new_لاره_call(CURSOR_غوټه,
                                                     CURSOR_لار,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //لاره

    إذا (پیغام_2) {
        إذا (dbus->پیغام_append_دلیلونه(پیغام_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &کلی, DBUS_TYPE_INVALID)) {
            ځواب = dbus->connection_send_with_ځواب_and_بلاک(dbus->session_conn, پیغام_2, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        }
        dbus->پیغام_unref(پیغام_2);
    }

    أرجع ځواب;
}

ساكن bool Wayland_Parse_DBus_ځواب(SDL_DBusContext *dbus, DBus_پیغام *ځواب, صحيح type, فراغ *ارزښت)
{
    DBus_پیغام_Iter iter[3];

    dbus->پیغام_iter_init(ځواب, &iter[0]);
    إذا (dbus->پیغام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->پیغام_iter_recurse(&iter[0], &iter[1]);
    إذا (dbus->پیغام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->پیغام_iter_recurse(&iter[1], &iter[2]);
    إذا (dbus->پیغام_iter_get_arg_type(&iter[2]) != type) {
        أرجع false;
    }

    dbus->پیغام_iter_get_basic(&iter[2], ارزښت);

    أرجع true;
}

ساكن DBus_Handler_پایله Wayland_DBus_Cursor_پیغام_Filter(DBusConnection *conn, DBus_پیغام *پیغام_2, فراغ *معلومات)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_معلومات *vdata = (SDL_Video_معلومات *)معلومات;

    إذا (dbus->پیغام_is_signal(پیغام_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_پیغام_Iter signal_iter, variant_iter;
        ثابت حرف *namespace, *کلی;

        dbus->پیغام_iter_init(پیغام_2, &signal_iter);
        // Check if the parameters are what we expect
        إذا (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->پیغام_iter_get_basic(&signal_iter, &namespace);
        إذا (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            اذهب not_our_signal;
        }
        إذا (!dbus->پیغام_iter_بل(&signal_iter)) {
            اذهب not_our_signal;
        }
        إذا (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->پیغام_iter_get_basic(&signal_iter, &کلی);
        إذا (SDL_strcmp(CURSOR_اندازه_کلی, کلی) == 0) {
            صحيح new_cursor_اندازه;

            إذا (!dbus->پیغام_iter_بل(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->پیغام_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->پیغام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                اذهب not_our_signal;
            }
            dbus->پیغام_iter_get_basic(&variant_iter, &new_cursor_اندازه);

            إذا (dbus_cursor_اندازه != new_cursor_اندازه) {
                dbus_cursor_اندازه = new_cursor_اندازه;
                SDL_RedrawCursor(); // Force cursor update
            }
        } وإلا إذا (SDL_strcmp(CURSOR_THEME_کلی, کلی) == 0) {
            ثابت حرف *new_cursor_theme = عدم;

            إذا (!dbus->پیغام_iter_بل(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->پیغام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->پیغام_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->پیغام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                اذهب not_our_signal;
            }
            dbus->پیغام_iter_get_basic(&variant_iter, &new_cursor_theme);

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

        أرجع DBUS_HANDLER_پایله_HANDLED;
    }

not_our_signal:
    أرجع DBUS_HANDLER_پایله_NOT_YET_HANDLED;
}

ساكن فراغ Wayland_DBusInitCursorProperties(SDL_Video_معلومات *vdata)
{
    DBus_پیغام *ځواب;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool جمع_کړه_filter = false;

    إذا (!dbus) {
        أرجع;
    }

    إذا ((ځواب = Wayland_ReadDBusProperty(dbus, CURSOR_اندازه_کلی))) {
        إذا (Wayland_Parse_DBus_ځواب(dbus, ځواب, DBUS_TYPE_INT32, &dbus_cursor_اندازه)) {
            جمع_کړه_filter = true;
        }
        dbus->پیغام_unref(ځواب);
    }

    إذا ((ځواب = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_کلی))) {
        ثابت حرف *لنډمهاله = عدم;
        إذا (Wayland_Parse_DBus_ځواب(dbus, ځواب, DBUS_TYPE_STRING, &لنډمهاله)) {
            جمع_کړه_filter = true;

            إذا (لنډمهاله) {
                dbus_cursor_theme = SDL_strdup(لنډمهاله);
            }
        }
        dbus->پیغام_unref(ځواب);
    }

    // Only add the filter if at least one of the settings we want is present.
    إذا (جمع_کړه_filter) {
        dbus->bus_جمع_کړه_سمون(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            عدم);
        dbus->connection_جمع_کړه_filter(dbus->session_conn, &Wayland_DBus_Cursor_پیغام_Filter, vdata, عدم);
        dbus->connection_flush(dbus->session_conn);
    }
}

ساكن فراغ Wayland_DBus_پای_Cursor_Properties(فراغ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = عدم;
}

#د_که_پای

ساكن بنية wl_بفر *Wayland_Cursor_State_Get_چوکاټ(SDL_WaylandCursorState *state, صحيح چوکاټ_شاخص_2)
{
    SDL_Cursor_معلومات *معلومات = state->current_cursor;

    إذا (معلومات) {
        إذا (!معلومات->is_system_cursor) {
            ثابت صحيح دننه_واټن_2 = معلومات->cursor_معلومات.custom.images_فی_چوکاټ * چوکاټ_شاخص_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = عدم;
            ثابت صحيح موخه_area = SDL_lround(معلومات->cursor_معلومات.custom.پلنوالی * معلومات->cursor_معلومات.custom.لوړوالی * state->scale);
            صحيح closest_area = 0;
            لكل (صحيح i = 0; i < معلومات->cursor_معلومات.custom.images_فی_چوکاټ && closest_area < موخه_area && معلومات->cursor_معلومات.custom.images[دننه_واټن_2 + i].بفر_2; ++i) {
                closest = &معلومات->cursor_معلومات.custom.images[دننه_واټن_2 + i];
                closest_area = closest->پلنوالی * closest->لوړوالی;
            }

            أرجع closest ? closest->بفر_2 : عدم;
        } وإلا {
            أرجع ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[چوکاټ_شاخص_2];
        }
    }

    أرجع عدم;
}

ساكن فراغ cursor_چوکاټ_بشپړ(فراغ *معلومات, بنية wl_callback *cb, uint32_t وخت);
ساكن ثابت بنية wl_callback_listener cursor_چوکاټ_listener = {
    cursor_چوکاټ_بشپړ
};

ساكن فراغ cursor_چوکاټ_بشپړ(فراغ *معلومات, بنية wl_callback *cb, uint32_t وخت)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)معلومات;
    إذا (!state->current_cursor) {
        أرجع;
    }

    Uint32 *چوکاټونه = state->current_cursor->چوکاټ_durations_ms;
    SDL_Cursor_معلومات *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->وروستی_چوکاټ_callback_وخت_ms) % c->ټول_duration_ms;
    Uint32 advance = 0;
    صحيح بل = state->current_چوکاټ;

    state->current_چوکاټ_وخت_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    لكل (Uint32 t = چوکاټونه[بل]; t <= state->current_چوکاټ_وخت_ms; t += چوکاټونه[بل]) {
        بل = (بل + 1) % c->عدد_چوکاټونه;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        إذا (!چوکاټونه[بل]) {
            اكسر;
        }
    }

    wl_callback_destroy(cb);
    state->چوکاټ_callback = عدم;

    // Don't queue another callback if this frame time is infinite.
    إذا (چوکاټونه[بل]) {
        state->چوکاټ_callback = wl_surface_چوکاټ(state->surface);
        wl_callback_جمع_کړه_listener(state->چوکاټ_callback, &cursor_چوکاټ_listener, معلومات);
    }

    state->current_چوکاټ_وخت_ms -= advance;
    state->وروستی_چوکاټ_callback_وخت_ms = now;
    state->current_چوکاټ = بل;

    بنية wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکاټ(state, بل);
    wl_surface_attach(state->surface, بفر_2, 0, 0);

    إذا (wl_surface_get_نسخه(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخه) {
        wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

فراغ Wayland_Cursor_State_سېټ_چوکاټ_Callback(SDL_WaylandCursorState *state, فراغ *userdata)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->دننی;
    Wayland_قلف_Event_Thread(viddata->event_thread_context);

    state->چوکاټ_callback = wl_surface_چوکاټ(state->surface);
    wl_callback_جمع_کړه_listener(state->چوکاټ_callback, &cursor_چوکاټ_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

فراغ Wayland_Cursor_State_Destroy_چوکاټ_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->دننی;
    Wayland_قلف_Event_Thread(viddata->event_thread_context);

    إذا (state->چوکاټ_callback) {
        wl_callback_destroy(state->چوکاټ_callback);
        state->چوکاټ_callback = عدم;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ساكن فراغ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->وروستی_چوکاټ_callback_وخت_ms = SDL_GetTicks();
    state->current_چوکاټ_وخت_ms = 0;
    state->current_چوکاټ = 0;
}

ساكن فراغ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool قلف_2)
{
    إذا (قلف_2) {
        SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->دننی;
        Wayland_قلف_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } وإلا {
        Wayland_CursorStateResetAnimationState(state);
    }
}

فراغ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_چوکاټ_Callback(state);
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

ساكن Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_معلومات *cdata, بنية wl_cursor *cursor, صحيح اندازه)
{
    Wayland_CachedSystemCursor *cache = عدم;

    // Is this cursor already cached at the target scale?
    إذا (!WAYLAND_wl_list_تشه(&cdata->cursor_معلومات.system.cursor_بفر_cache)) {
        Wayland_CachedSystemCursor *c = عدم;
        wl_list_for_each (c, &cdata->cursor_معلومات.system.cursor_بفر_cache, غوټه) {
            إذا (c->اندازه == اندازه) {
                cache = c;
                اكسر;
            }
        }
    }

    إذا (!cache) {
        cache = SDL_calloc(1, حجم(Wayland_CachedSystemCursor) + (حجم(بنية wl_بفر *) * cdata->عدد_چوکاټونه));

        cache->اندازه = اندازه;
        لكل (صحيح i = 0; i < cdata->عدد_چوکاټونه; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_بفر(cursor->images[i]);
        }

        WAYLAND_wl_list_ورننباسه(&cdata->cursor_معلومات.system.cursor_بفر_cache, &cache->غوټه);
    }

    أرجع cache;
}

ساكن bool Wayland_GetSystemCursor(SDL_Cursor_معلومات *cdata, SDL_WaylandCursorState *state, صحيح *dst_اندازه, صحيح *hot_x, صحيح *hot_y)
{
    SDL_Video_معلومات *vdata = SDL_GetVideoDevice()->دننی;
    بنية wl_cursor_theme *theme = عدم;
    ثابت حرف *css_name = "default";
    ثابت حرف *fallback_name = عدم;
    مزدوج scale_ضریب_2 = state->scale;
    صحيح theme_اندازه = dbus_cursor_اندازه;

    // Fallback envvar if the DBus properties don't exist
    إذا (theme_اندازه <= 0) {
        ثابت حرف *xcursor_اندازه = SDL_getenv("XCURSOR_SIZE");
        إذا (xcursor_اندازه) {
            theme_اندازه = SDL_atoi(xcursor_اندازه);
        }
    }
    إذا (theme_اندازه <= 0) {
        theme_اندازه = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ثابت صحيح scaled_اندازه = (صحيح)SDL_lround(theme_اندازه * scale_ضریب_2);
    لكل (صحيح i = 0; i < vdata->عدد_cursor_themes; ++i) {
        إذا (vdata->cursor_themes[i].اندازه == scaled_اندازه) {
            theme = vdata->cursor_themes[i].theme;
            اكسر;
        }
    }
    إذا (!theme) {
        ثابت حرف *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                حجم(SDL_WaylandCursorTheme) * (vdata->عدد_cursor_themes + 1));
        إذا (!new_cursor_themes) {
            أرجع false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        إذا (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_بارول(xcursor_theme, scaled_اندازه, vdata->shm);
        vdata->cursor_themes[vdata->عدد_cursor_themes].اندازه = scaled_اندازه;
        vdata->cursor_themes[vdata->عدد_cursor_themes++].theme = theme;
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
    cdata->عدد_چوکاټونه = cursor->image_شمېر_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_اندازه);
    state->system_cursor_handle = c;

    إذا (cursor->image_شمېر_2 > 1 && !cdata->چوکاټ_durations_ms) {
        cdata->ټول_duration_ms = 0;
        cdata->چوکاټ_durations_ms = SDL_calloc(cursor->image_شمېر_2, حجم(Uint32));

        لكل (صحيح i = 0; i < cursor->image_شمېر_2; ++i) {
            cdata->چوکاټ_durations_ms[i] = cursor->images[i]->delay;
            cdata->ټول_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_اندازه = SDL_lround(cursor->images[0]->پلنوالی / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    أرجع true;
}

ساكن صحيح surface_ترتیبول_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ساكن SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_چوکاټ_Info *چوکاټونه, صحيح چوکاټ_شمېر, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_معلومات *معلومات = عدم;
    Wayland_SHMPool *shm_pool = عدم;
    صحيح pool_اندازه = 0;
    صحيح max_images = 0;
    bool is_ډېری = false;
    بنية SurfaceArray
    {
        SDL_Surface **surfaces;
        صحيح شمېر;
    } *surfaces = SDL_small_alloc(بنية SurfaceArray, چوکاټ_شمېر, &is_ډېری);
    إذا (!surfaces) {
        اذهب failed;
    }
    SDL_memset(surfaces, 0, حجم(بنية SurfaceArray) * چوکاټ_شمېر);

    // Calculate the total allocation size.
    لكل (صحيح i = 0; i < چوکاټ_شمېر; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(چوکاټونه[i].surface, &surfaces[i].شمېر);
        إذا (!surfaces[i].surfaces) {
            اذهب failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].شمېر, حجم(SDL_Surface *), surface_ترتیبول_callback);
        max_images = SDL_max(max_images, surfaces[i].شمېر);
        لكل (صحيح j = 0; j < surfaces[i].شمېر; ++j) {
            pool_اندازه += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    معلومات = SDL_calloc(1, حجم(*معلومات) + (حجم(CustomCursorImage) * max_images * چوکاټ_شمېر));
    إذا (!معلومات) {
        اذهب failed;
    }

    معلومات->چوکاټ_durations_ms = SDL_calloc(چوکاټ_شمېر, حجم(Uint32));
    إذا (!معلومات->چوکاټ_durations_ms) {
        اذهب failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_اندازه);
    إذا (!shm_pool) {
        اذهب failed;
    }

    cursor->دننی = معلومات;
    معلومات->cursor_معلومات.custom.پلنوالی = چوکاټونه[0].surface->w;
    معلومات->cursor_معلومات.custom.لوړوالی = چوکاټونه[0].surface->h;
    معلومات->cursor_معلومات.custom.hot_x = hot_x;
    معلومات->cursor_معلومات.custom.hot_y = hot_y;
    معلومات->cursor_معلومات.custom.images_فی_چوکاټ = max_images;
    معلومات->عدد_چوکاټونه = چوکاټ_شمېر;

    لكل (صحيح i = 0; i < چوکاټ_شمېر; ++i) {
        معلومات->چوکاټ_durations_ms[i] = چوکاټونه[i].duration;
        إذا (معلومات->ټول_duration_ms < SDL_MAX_UINT32) {
            إذا (معلومات->چوکاټ_durations_ms[i] > 0) {
                معلومات->ټول_duration_ms += معلومات->چوکاټ_durations_ms[i];
            } وإلا {
                معلومات->ټول_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحيح دننه_واټن_2 = i * max_images;
        لكل (صحيح j = 0; j < surfaces[i].شمېر; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                إذا (!surface) {
                    اذهب failed;
                }
            }

            معلومات->cursor_معلومات.custom.images[دننه_واټن_2 + j].پلنوالی = surface->w;
            معلومات->cursor_معلومات.custom.images[دننه_واټن_2 + j].لوړوالی = surface->h;

            فراغ *buf_معلومات;
            معلومات->cursor_معلومات.custom.images[دننه_واټن_2 + j].بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, surface->w, surface->h, &buf_معلومات);
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

    SDL_small_free(surfaces, is_ډېری);
    Wayland_ReleaseSHMPool(shm_pool);

    أرجع cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    إذا (معلومات) {
        SDL_free(معلومات->چوکاټ_durations_ms);
        لكل (صحيح i = 0; i < معلومات->cursor_معلومات.custom.images_فی_چوکاټ * چوکاټ_شمېر; ++i) {
            إذا (معلومات->cursor_معلومات.custom.images[i].بفر_2) {
                wl_بفر_destroy(معلومات->cursor_معلومات.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(معلومات);

    إذا (surfaces) {
        لكل (صحيح i = 0; i < چوکاټ_شمېر; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ډېری);
    }

    SDL_free(cursor);

    أرجع عدم;
}

ساكن SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_چوکاټ_Info چوکاټ = {
        surface, 0
    };

    أرجع Wayland_CreateAnimatedCursor(&چوکاټ, 1, hot_x, hot_y);
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
        cursor->دننی = cdata;

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
    SDL_Video_معلومات *video_معلومات = video_device->دننی;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_معلومات->seat_list, link)
    {
        إذا (seat->اشاره_ګر_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_چوکاټ_Callback(&seat->اشاره_ګر_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            إذا (!d->is_system_cursor && seat->اشاره_ګر_2.cursor_state.surface) {
                wl_surface_attach(seat->اشاره_ګر_2.cursor_state.surface, عدم, 0, 0);
            }

            seat->اشاره_ګر_2.cursor_state.current_cursor = عدم;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_چوکاټ_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                إذا (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->اشاره_ګر_2.cursor_state.surface, عدم, 0, 0);
                }

                tool->cursor_state.current_cursor = عدم;
            }
        }
    }

    إذا (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *لنډمهاله;
        wl_list_for_each_خوندي(c, لنډمهاله, &d->cursor_معلومات.system.cursor_بفر_cache, غوټه) {
            SDL_free(c);
        }
    } وإلا {
        لكل (صحيح i = 0; i < d->عدد_چوکاټونه * d->cursor_معلومات.custom.images_فی_چوکاټ; ++i) {
            إذا (d->cursor_معلومات.custom.images[i].بفر_2) {
                wl_بفر_destroy(d->cursor_معلومات.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(d->چوکاټ_durations_ms);
}

ساكن فراغ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        أرجع;
    }

    // Probably not a cursor we own
    إذا (!cursor->دننی) {
        أرجع;
    }

    Wayland_Free_Cursor_معلومات(cursor->دننی);

    SDL_free(cursor->دننی);
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
    حالة SDL_SYSTEM_CURSOR_پرمختګ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_پرمختګ;
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
    حالة SDL_SYSTEM_CURSOR_اشاره_ګر:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_اشاره_ګر;
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
    حالة SDL_SYSTEM_CURSOR_ستون_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ستون_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_لیکه_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_لیکه_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_دننه:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_دننه;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_بهر:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_بهر;
        اكسر;
    افتراضي:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    أرجع shape;
}

تعريفنوع بنية Wayland_اشاره_ګر_Object
{
    اتحاد
    {
        بنية wl_اشاره_ګر *wl_اشاره_ګر;
        بنية zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_اشاره_ګر;
} Wayland_اشاره_ګر_Object;

ساكن فراغ Wayland_Cursor_State_سېټ_Cursor(SDL_WaylandCursorState *state, ثابت Wayland_اشاره_ګر_Object *obj, SDL_کړکۍ_معلومات *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->دننی;
    SDL_Cursor_معلومات *cursor_معلومات = cursor ? cursor->دننی : عدم;
    صحيح dst_پلنوالی = 0;
    صحيح dst_لوړوالی = 0;
    صحيح hot_x;
    صحيح hot_y;

    // Stop the frame callback for old animated cursors.
    إذا (cursor_معلومات != state->current_cursor) {
        Wayland_Cursor_State_Destroy_چوکاټ_Callback(state);
    }

    إذا (cursor) {
        إذا (cursor_معلومات == state->current_cursor && state->current_چوکاټ >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            إذا (cursor_معلومات->عدد_چوکاټونه > 1) {
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

                    إذا (obj->is_اشاره_ګر) {
                        wl_اشاره_ګر_سېټ_cursor(obj->wl_اشاره_ګر, serial, عدم, 0, 0);
                    } وإلا {
                        zwp_tablet_tool_v2_سېټ_cursor(obj->wl_tool, serial, عدم, 0, 0);
                    }

                    إذا (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = عدم;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = عدم;
                }

                ثابت تعداد wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_معلومات->cursor_معلومات.system.id);
                wp_cursor_shape_device_v1_سېټ_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_معلومات;
                state->current_چوکاټ = 0;

                أرجع;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ضریب_2 : 1.0;
            إذا (!Wayland_GetSystemCursor(cursor_معلومات, state, &dst_پلنوالی, &hot_x, &hot_y)) {
                أرجع;
            }

            dst_لوړوالی = dst_پلنوالی;
        } وإلا {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            إذا (!focus || (focus->اشاره_ګر_scale.x == 1.0 && focus->اشاره_ګر_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ضریب_2 : 1.0;
                dst_پلنوالی = cursor_معلومات->cursor_معلومات.custom.پلنوالی;
                dst_لوړوالی = cursor_معلومات->cursor_معلومات.custom.لوړوالی;
                hot_x = cursor_معلومات->cursor_معلومات.custom.hot_x;
                hot_y = cursor_معلومات->cursor_معلومات.custom.hot_y;
            } وإلا {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->اشاره_ګر_scale.x, focus->اشاره_ګر_scale.y);
                dst_پلنوالی = SDL_max((صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.پلنوالی / focus->اشاره_ګر_scale.x), 1);
                dst_لوړوالی = SDL_max((صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.لوړوالی / focus->اشاره_ګر_scale.y), 1);
                hot_x = (صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.hot_x / focus->اشاره_ګر_scale.x);
                hot_y = (صحيح)SDL_lround((مزدوج)cursor_معلومات->cursor_معلومات.custom.hot_y / focus->اشاره_ګر_scale.y);
            }

        }

        state->current_cursor = cursor_معلومات;

        إذا (!state->surface) {
            بنية wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        بنية wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکاټ(state, 0);
        wl_surface_attach(state->surface, بفر_2, 0, 0);
        state->current_چوکاټ = 0;

        إذا (state->scale != 1.0) {
            إذا (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_سېټ_سرچینه(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_سېټ_destination(state->viewport, dst_پلنوالی, dst_لوړوالی);
        } وإلا إذا (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = عدم;
        }

        إذا (obj->is_اشاره_ګر) {
            wl_اشاره_ګر_سېټ_cursor(obj->wl_اشاره_ګر, serial, state->surface, hot_x, hot_y);
        } وإلا {
            zwp_tablet_tool_v2_سېټ_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        إذا (wl_surface_get_نسخه(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخه) {
            wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        إذا (cursor_معلومات->عدد_چوکاټونه > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_سېټ_چوکاټ_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } وإلا {
        Wayland_Cursor_State_Destroy_چوکاټ_Callback(state);
        state->current_cursor = عدم;

        إذا (state->surface) {
            wl_surface_attach(state->surface, عدم, 0, 0);
            wl_surface_commit(state->surface);
        }

        إذا (obj->is_اشاره_ګر) {
            wl_اشاره_ګر_سېټ_cursor(obj->wl_اشاره_ګر, serial, عدم, 0, 0);
        } وإلا {
            zwp_tablet_tool_v2_سېټ_cursor(obj->wl_tool, serial, عدم, 0, 0);
        }
    }
}

ساكن فراغ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_چوکاټ_Callback(state);
    state->current_چوکاټ = -1;
}

فراغ Wayland_Display_Update_اشاره_ګر_Focused_Scale(SDL_کړکۍ_معلومات *updated_کړکۍ)
{
    SDL_Video_معلومات *viddata = updated_کړکۍ->wayland_معلومات;
    SDL_WaylandSeat *seat;
    ثابت مزدوج new_scale = SDL_min(updated_کړکۍ->اشاره_ګر_scale.x, updated_کړکۍ->اشاره_ګر_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        إذا (seat->اشاره_ګر_2.focus == updated_کړکۍ) {
            SDL_WaylandCursorState *state = &seat->اشاره_ګر_2.cursor_state;
            إذا (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_اشاره_ګر_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == updated_کړکۍ) {
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
    SDL_Video_معلومات *d = vd->دننی;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_اشاره_ګر_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->اشاره_ګر_2.wl_اشاره_ګر) {
            obj.wl_اشاره_ګر = seat->اشاره_ګر_2.wl_اشاره_ګر;
            obj.is_اشاره_ګر = true;
            إذا (mouse->focus && mouse->focus->دننی == seat->اشاره_ګر_2.focus) {
                Wayland_Cursor_State_سېټ_Cursor(&seat->اشاره_ګر_2.cursor_state, &obj, seat->اشاره_ګر_2.focus, seat->اشاره_ګر_2.enter_serial, cursor);
            } وإلا إذا (!seat->اشاره_ګر_2.focus) {
                Wayland_CursorStateResetCursor(&seat->اشاره_ګر_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_اشاره_ګر = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            إذا (tool->focus && (!mouse->focus || mouse->focus->دننی == tool->focus)) {
                Wayland_Cursor_State_سېټ_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا إذا (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    أرجع true;
}

فراغ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_کړکۍ_معلومات *کړکۍ, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->دننی;

    إذا (seat->اشاره_ګر_2.wl_اشاره_ګر) {
        إذا (d->wp_اشاره_ګر_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / کړکۍ->اشاره_ګر_scale.x, 0, کړکۍ->current.logical_پلنوالی));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / کړکۍ->اشاره_ګر_scale.y, 0, کړکۍ->current.logical_لوړوالی));
            wp_اشاره_ګر_warp_v1_warp_اشاره_ګر(d->wp_اشاره_ګر_warp_v1, کړکۍ->surface, seat->اشاره_ګر_2.wl_اشاره_ګر, f_x, f_y, seat->اشاره_ګر_2.enter_serial);
        } وإلا {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            إذا (seat->اشاره_ګر_2.confined_اشاره_ګر) {
                zwp_confined_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.confined_اشاره_ګر);
                seat->اشاره_ګر_2.confined_اشاره_ګر = عدم;
                update_grabs = true;
            }
            إذا (seat->اشاره_ګر_2.locked_اشاره_ګر) {
                zwp_locked_اشاره_ګر_v1_destroy(seat->اشاره_ګر_2.locked_اشاره_ګر);
                seat->اشاره_ګر_2.locked_اشاره_ګر = عدم;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            بنية zwp_locked_اشاره_ګر_v1 *warp_قلف =
                zwp_اشاره_ګر_constraints_v1_قلف_اشاره_ګر(d->اشاره_ګر_constraints, کړکۍ->surface,
                                                        seat->اشاره_ګر_2.wl_اشاره_ګر, عدم,
                                                        ZWP_اشاره_ګر_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / کړکۍ->اشاره_ګر_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / کړکۍ->اشاره_ګر_scale.y);
            zwp_locked_اشاره_ګر_v1_سېټ_cursor_position_hint(warp_قلف, f_x, f_y);
            wl_surface_commit(کړکۍ->surface);

            zwp_locked_اشاره_ګر_v1_destroy(warp_قلف);

            إذا (update_grabs) {
                Wayland_Seat_Update_اشاره_ګر_Grab(seat);
            }
        }

        إذا (wl_اشاره_ګر_get_نسخه(seat->اشاره_ګر_2.wl_اشاره_ګر) < WL_اشاره_ګر_WARP_SINCE_نسخه) {
            SDL_SendMouseWarp(0, کړکۍ->sdlwindow, seat->اشاره_ګر_2.sdl_id, x, y);
        }
    }
}

ساكن bool Wayland_WarpMouseRelative(SDL_کړکۍ *کړکۍ, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->دننی;
    SDL_کړکۍ_معلومات *wind = کړکۍ->دننی;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشاره_ګر_warp_v1 || d->اشاره_ګر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (wind == seat->اشاره_ګر_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } وإلا {
        أرجع SDL_سېټ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->دننی;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشاره_ګر_warp_v1 || d->اشاره_ګر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_کړکۍ_معلومات *wind = seat->اشاره_ګر_2.focus ? seat->اشاره_ګر_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            إذا (wind) {
                SDL_کړکۍ *کړکۍ = wind->sdlwindow;

                صحيح abs_x, abs_y;
                SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, کړکۍ->x, کړکۍ->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, کړکۍ->w, کړکۍ->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                إذا (SDL_ټکی_دننه_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } وإلا {
        أرجع SDL_سېټ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_سېټ_Relative_Mouse_ډېرپېښ(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *معلومات = vd->دننی;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    إذا (!معلومات->relative_اشاره_ګر_manager) {
        أرجع SDL_سېټ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    إذا (!معلومات->اشاره_ګر_constraints) {
        أرجع SDL_سېټ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_اشاره_ګر_Grabs(معلومات, عدم);
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
    SDL_MouseButtonFlags پایله = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    إذا (mouse->focus) {
        SDL_Video_معلومات *video_معلومات = SDL_GetVideoDevice()->دننی;
        SDL_WaylandSeat *seat;
        صحيح off_x, off_y;
        SDL_Relative_منزل_Global_For_کړکۍ(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_معلومات->seat_list, link) {
            پایله |= seat->اشاره_ګر_2.buttons_pressed;
        }
    } وإلا {
        *x = 0.f;
        *y = 0.f;
    }

    أرجع پایله;
}

#إذا 0  // TODO RECONNECT: See waylandvideo.c for more information!
ساكن فراغ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_معلومات *vdata)
{
    SDL_Cursor_معلومات *cdata = cursor->دننی;

    // Probably not a cursor we own
    إذا (cdata == عدم) {
        أرجع;
    }

    Wayland_Free_Cursor_معلومات(cdata);

    // We're not currently freeing this, so... yolo?
    إذا (cdata->shm_معلومات != عدم) {
        فراغ *old_معلومات_اشاره_ګر = cdata->shm_معلومات;
        صحيح stride = cdata->w * 4;

        create_بفر_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_معلومات, old_معلومات_اشاره_ګر, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_سېټ_user_معلومات(cdata->surface, عدم);
}

فراغ Wayland_RecreateCursors(فراغ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_معلومات *vdata = SDL_GetVideoDevice()->دننی;

    إذا (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = عدم;
        vdata->عدد_cursor_themes = 0;
    }

    إذا (mouse == عدم) {
        أرجع;
    }

    لكل (cursor = mouse->cursors; cursor != عدم; cursor = cursor->بل) {
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
#د_که_پای // 0

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
    mouse->سېټ_Relative_Mouse_ډېرپېښ = Wayland_سېټ_Relative_Mouse_ډېرپېښ;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_موندنه_Test_پایله r = SDL_HITTEST_نورمال;
    طالما (r <= SDL_HITTEST_RESIZE_کیڼ) {
        بدل (r) {
        حالة SDL_HITTEST_نورمال:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_سر:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_ښی:
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
        حالة SDL_HITTEST_RESIZE_کیڼ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            اكسر;
        }
        r++;
    }

#که_تعریف_شوی SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_معلومات *d = vd->دننی;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    إذا (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#د_که_پای

    SDL_سېټ_Default_Cursor(Wayland_CreateDefaultCursor());
}

فراغ Wayland_FiniMouse(SDL_Video_معلومات *معلومات)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = عدم;
    }

    Wayland_FreeCursorThemes(معلومات);

#که_تعریف_شوی SDL_USE_LIBDBUS
    Wayland_DBus_پای_Cursor_Properties();
#د_که_پای
}

فراغ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->اشاره_ګر_2.cursor_state);
}

فراغ Wayland_Seat_سېټ_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کړکۍ_معلومات *اشاره_ګر_focus = seat->اشاره_ګر_2.focus;
    ثابت Wayland_اشاره_ګر_Object obj = {
        .wl_اشاره_ګر = seat->اشاره_ګر_2.wl_اشاره_ګر,
        .is_اشاره_ګر = true
    };

    Wayland_Cursor_State_سېټ_Cursor(&seat->اشاره_ګر_2.cursor_state, &obj, اشاره_ګر_focus, seat->اشاره_ګر_2.enter_serial, mouse->def_cursor);
}

فراغ Wayland_Seat_Update_اشاره_ګر_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کړکۍ_معلومات *اشاره_ګر_focus = seat->اشاره_ګر_2.focus;
    ثابت Wayland_اشاره_ګر_Object obj = {
        .wl_اشاره_ګر = seat->اشاره_ګر_2.wl_اشاره_ګر,
        .is_اشاره_ګر = true
    };

    إذا (اشاره_ګر_focus) {
        إذا (mouse->cursor_visible) {
            إذا (!seat->اشاره_ګر_2.relative_اشاره_ګر || !mouse->relative_ډېرپېښ_hide_cursor) {
                ثابت SDL_موندنه_Test_پایله rc = اشاره_ګر_focus->موندنه_test_پایله;

                إذا (seat->اشاره_ګر_2.relative_اشاره_ګر || rc == SDL_HITTEST_نورمال || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_سېټ_Cursor(&seat->اشاره_ګر_2.cursor_state, &obj, اشاره_ګر_focus, seat->اشاره_ګر_2.enter_serial, mouse->cur_cursor);
                } وإلا {
                    Wayland_Cursor_State_سېټ_Cursor(&seat->اشاره_ګر_2.cursor_state, &obj, اشاره_ګر_focus, seat->اشاره_ګر_2.enter_serial, sys_cursors[rc]);
                }
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سېټ_Cursor(&seat->اشاره_ګر_2.cursor_state, &obj, اشاره_ګر_focus, seat->اشاره_ګر_2.enter_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_سېټ_Cursor(&seat->اشاره_ګر_2.cursor_state, &obj, اشاره_ګر_focus, seat->اشاره_ګر_2.enter_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&seat->اشاره_ګر_2.cursor_state);
    }
}

فراغ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کړکۍ_معلومات *tool_focus = tool->focus;
    ثابت Wayland_اشاره_ګر_Object obj = {
        .wl_tool = tool->wltool,
        .is_اشاره_ګر = false
    };

    إذا (tool_focus) {
        إذا (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ);

            إذا (!relative || !mouse->relative_ډېرپېښ_hide_cursor) {
                Wayland_Cursor_State_سېټ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سېټ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_سېټ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND

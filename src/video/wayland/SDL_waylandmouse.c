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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

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

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_بایاں + 1];

ساكن bool Wayland_سیٹ_Relative_Mouse_منوال(bool enabled);

تعريفنوع بنية
{
    صحيح چوڑائی;
    صحيح اچائی;
    بنية wl_بفر *بفر_2;
} CustomCursorImage;

تعريفنوع بنية
{
    // The base dimensions of the cursor.
    صحيح چوڑائی;
    صحيح اچائی;
    صحيح hot_x;
    صحيح hot_y;

    صحيح images_فی_چوکھٹا;
    CustomCursorImage images[];
} Wayland_CustomCursor;

تعريفنوع بنية
{
    صحيح ناپ;
    بنية wl_list گرہ;
    بنية wl_بفر *buffers[];
} Wayland_CachedSystemCursor;

تعريفنوع بنية
{
    SDL_SystemCursor id;
    بنية wl_list cursor_بفر_cache;
} Wayland_SystemCursor;

بنية SDL_Cursor_انکڑے
{
    // Cursor animation data.
    Uint32 *چوکھٹا_durations_ms;
    Uint32 کل_duration_ms;
    صحيح عدد_چوکھٹے;
    bool is_system_cursor;

    اتحاد
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_انکڑے;
};

ساكن صحيح dbus_cursor_ناپ;
ساكن حرف *dbus_cursor_theme;

ساكن فراغ Wayland_FreeCursorThemes(SDL_Video_انکڑے *vdata)
{
    لكل (صحيح i = 0; i < vdata->عدد_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->عدد_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = عدم;
}

#جے_تعریف_شدہ SDL_USE_LIBDBUS

#ضمن "../../core/linux/SDL_dbus.h"

#تعریف_کرو CURSOR_گرہ        "org.freedesktop.portal.Desktop"
#تعریف_کرو CURSOR_رستہ        "/org/freedesktop/portal/desktop"
#تعریف_کرو CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#تعریف_کرو CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#تعریف_کرو CURSOR_SIGNAL_NAME "SettingChanged"
#تعریف_کرو CURSOR_ناپ_کلید    "cursor-size"
#تعریف_کرو CURSOR_THEME_کلید   "cursor-theme"

ساكن DBus_سنیہا *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت حرف *کلید)
{
    ساكن ثابت حرف *iface = "org.gnome.desktop.interface";

    DBus_سنیہا *جواب = عدم;
    DBus_سنیہا *پیغام = dbus->سنیہا_new_طریقہ_call(CURSOR_گرہ,
                                                     CURSOR_رستہ,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //طریقہ

    إذا (پیغام) {
        إذا (dbus->سنیہا_append_دلیلاں(پیغام, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &کلید, DBUS_TYPE_INVALID)) {
            جواب = dbus->connection_send_with_جواب_and_بلاک(dbus->session_conn, پیغام, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        }
        dbus->سنیہا_unref(پیغام);
    }

    أرجع جواب;
}

ساكن bool Wayland_Parse_DBus_جواب(SDL_DBusContext *dbus, DBus_سنیہا *جواب, صحيح type, فراغ *قدر)
{
    DBus_سنیہا_Iter iter[3];

    dbus->سنیہا_iter_init(جواب, &iter[0]);
    إذا (dbus->سنیہا_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->سنیہا_iter_recurse(&iter[0], &iter[1]);
    إذا (dbus->سنیہا_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->سنیہا_iter_recurse(&iter[1], &iter[2]);
    إذا (dbus->سنیہا_iter_get_arg_type(&iter[2]) != type) {
        أرجع false;
    }

    dbus->سنیہا_iter_get_basic(&iter[2], قدر);

    أرجع true;
}

ساكن DBus_Handler_نتیجہ Wayland_DBus_Cursor_سنیہا_Filter(DBusConnection *conn, DBus_سنیہا *پیغام, فراغ *انکڑے)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_انکڑے *vdata = (SDL_Video_انکڑے *)انکڑے;

    إذا (dbus->سنیہا_is_signal(پیغام, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_سنیہا_Iter signal_iter, variant_iter;
        ثابت حرف *namespace, *کلید;

        dbus->سنیہا_iter_init(پیغام, &signal_iter);
        // Check if the parameters are what we expect
        إذا (dbus->سنیہا_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->سنیہا_iter_get_basic(&signal_iter, &namespace);
        إذا (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            اذهب not_our_signal;
        }
        إذا (!dbus->سنیہا_iter_اگلا(&signal_iter)) {
            اذهب not_our_signal;
        }
        إذا (dbus->سنیہا_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->سنیہا_iter_get_basic(&signal_iter, &کلید);
        إذا (SDL_strcmp(CURSOR_ناپ_کلید, کلید) == 0) {
            صحيح new_cursor_ناپ;

            إذا (!dbus->سنیہا_iter_اگلا(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->سنیہا_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->سنیہا_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->سنیہا_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                اذهب not_our_signal;
            }
            dbus->سنیہا_iter_get_basic(&variant_iter, &new_cursor_ناپ);

            إذا (dbus_cursor_ناپ != new_cursor_ناپ) {
                dbus_cursor_ناپ = new_cursor_ناپ;
                SDL_RedrawCursor(); // Force cursor update
            }
        } وإلا إذا (SDL_strcmp(CURSOR_THEME_کلید, کلید) == 0) {
            ثابت حرف *new_cursor_theme = عدم;

            إذا (!dbus->سنیہا_iter_اگلا(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->سنیہا_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->سنیہا_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->سنیہا_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                اذهب not_our_signal;
            }
            dbus->سنیہا_iter_get_basic(&variant_iter, &new_cursor_theme);

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

        أرجع DBUS_HANDLER_نتیجہ_HANDLED;
    }

not_our_signal:
    أرجع DBUS_HANDLER_نتیجہ_NOT_YET_HANDLED;
}

ساكن فراغ Wayland_DBusInitCursorProperties(SDL_Video_انکڑے *vdata)
{
    DBus_سنیہا *جواب;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool جوڑو_filter = false;

    إذا (!dbus) {
        أرجع;
    }

    إذا ((جواب = Wayland_ReadDBusProperty(dbus, CURSOR_ناپ_کلید))) {
        إذا (Wayland_Parse_DBus_جواب(dbus, جواب, DBUS_TYPE_INT32, &dbus_cursor_ناپ)) {
            جوڑو_filter = true;
        }
        dbus->سنیہا_unref(جواب);
    }

    إذا ((جواب = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_کلید))) {
        ثابت حرف *عارضی = عدم;
        إذا (Wayland_Parse_DBus_جواب(dbus, جواب, DBUS_TYPE_STRING, &عارضی)) {
            جوڑو_filter = true;

            إذا (عارضی) {
                dbus_cursor_theme = SDL_strdup(عارضی);
            }
        }
        dbus->سنیہا_unref(جواب);
    }

    // Only add the filter if at least one of the settings we want is present.
    إذا (جوڑو_filter) {
        dbus->bus_جوڑو_میل(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            عدم);
        dbus->connection_جوڑو_filter(dbus->session_conn, &Wayland_DBus_Cursor_سنیہا_Filter, vdata, عدم);
        dbus->connection_flush(dbus->session_conn);
    }
}

ساكن فراغ Wayland_DBus_انت_Cursor_Properties(فراغ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = عدم;
}

#جے_انت

ساكن بنية wl_بفر *Wayland_Cursor_State_Get_چوکھٹا(SDL_WaylandCursorState *state, صحيح چوکھٹا_اشاریہ_2)
{
    SDL_Cursor_انکڑے *انکڑے = state->current_cursor;

    إذا (انکڑے) {
        إذا (!انکڑے->is_system_cursor) {
            ثابت صحيح وتھ_2 = انکڑے->cursor_انکڑے.custom.images_فی_چوکھٹا * چوکھٹا_اشاریہ_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = عدم;
            ثابت صحيح نشانہ_area = SDL_lround(انکڑے->cursor_انکڑے.custom.چوڑائی * انکڑے->cursor_انکڑے.custom.اچائی * state->scale);
            صحيح closest_area = 0;
            لكل (صحيح i = 0; i < انکڑے->cursor_انکڑے.custom.images_فی_چوکھٹا && closest_area < نشانہ_area && انکڑے->cursor_انکڑے.custom.images[وتھ_2 + i].بفر_2; ++i) {
                closest = &انکڑے->cursor_انکڑے.custom.images[وتھ_2 + i];
                closest_area = closest->چوڑائی * closest->اچائی;
            }

            أرجع closest ? closest->بفر_2 : عدم;
        } وإلا {
            أرجع ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[چوکھٹا_اشاریہ_2];
        }
    }

    أرجع عدم;
}

ساكن فراغ cursor_چوکھٹا_پورا(فراغ *انکڑے, بنية wl_callback *cb, uint32_t ویلا);
ساكن ثابت بنية wl_callback_listener cursor_چوکھٹا_listener = {
    cursor_چوکھٹا_پورا
};

ساكن فراغ cursor_چوکھٹا_پورا(فراغ *انکڑے, بنية wl_callback *cb, uint32_t ویلا)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)انکڑے;
    إذا (!state->current_cursor) {
        أرجع;
    }

    Uint32 *چوکھٹے = state->current_cursor->چوکھٹا_durations_ms;
    SDL_Cursor_انکڑے *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->آخری_چوکھٹا_callback_ویلا_ms) % c->کل_duration_ms;
    Uint32 advance = 0;
    صحيح اگلا = state->current_چوکھٹا;

    state->current_چوکھٹا_ویلا_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    لكل (Uint32 t = چوکھٹے[اگلا]; t <= state->current_چوکھٹا_ویلا_ms; t += چوکھٹے[اگلا]) {
        اگلا = (اگلا + 1) % c->عدد_چوکھٹے;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        إذا (!چوکھٹے[اگلا]) {
            اكسر;
        }
    }

    wl_callback_destroy(cb);
    state->چوکھٹا_callback = عدم;

    // Don't queue another callback if this frame time is infinite.
    إذا (چوکھٹے[اگلا]) {
        state->چوکھٹا_callback = wl_surface_چوکھٹا(state->surface);
        wl_callback_جوڑو_listener(state->چوکھٹا_callback, &cursor_چوکھٹا_listener, انکڑے);
    }

    state->current_چوکھٹا_ویلا_ms -= advance;
    state->آخری_چوکھٹا_callback_ویلا_ms = now;
    state->current_چوکھٹا = اگلا;

    بنية wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکھٹا(state, اگلا);
    wl_surface_attach(state->surface, بفر_2, 0, 0);

    إذا (wl_surface_get_نسخہ(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
        wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

فراغ Wayland_Cursor_State_سیٹ_چوکھٹا_Callback(SDL_WaylandCursorState *state, فراغ *userdata)
{
    SDL_Video_انکڑے *viddata = SDL_GetVideoDevice()->اندرونی;
    Wayland_جندرا_Event_Thread(viddata->event_thread_context);

    state->چوکھٹا_callback = wl_surface_چوکھٹا(state->surface);
    wl_callback_جوڑو_listener(state->چوکھٹا_callback, &cursor_چوکھٹا_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

فراغ Wayland_Cursor_State_Destroy_چوکھٹا_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_انکڑے *viddata = SDL_GetVideoDevice()->اندرونی;
    Wayland_جندرا_Event_Thread(viddata->event_thread_context);

    إذا (state->چوکھٹا_callback) {
        wl_callback_destroy(state->چوکھٹا_callback);
        state->چوکھٹا_callback = عدم;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ساكن فراغ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->آخری_چوکھٹا_callback_ویلا_ms = SDL_GetTicks();
    state->current_چوکھٹا_ویلا_ms = 0;
    state->current_چوکھٹا = 0;
}

ساكن فراغ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool جندرا_2)
{
    إذا (جندرا_2) {
        SDL_Video_انکڑے *viddata = SDL_GetVideoDevice()->اندرونی;
        Wayland_جندرا_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } وإلا {
        Wayland_CursorStateResetAnimationState(state);
    }
}

فراغ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
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

ساكن Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_انکڑے *cdata, بنية wl_cursor *cursor, صحيح ناپ)
{
    Wayland_CachedSystemCursor *cache = عدم;

    // Is this cursor already cached at the target scale?
    إذا (!WAYLAND_wl_list_خالی_تھاواں(&cdata->cursor_انکڑے.system.cursor_بفر_cache)) {
        Wayland_CachedSystemCursor *c = عدم;
        wl_list_for_each (c, &cdata->cursor_انکڑے.system.cursor_بفر_cache, گرہ) {
            إذا (c->ناپ == ناپ) {
                cache = c;
                اكسر;
            }
        }
    }

    إذا (!cache) {
        cache = SDL_calloc(1, حجم(Wayland_CachedSystemCursor) + (حجم(بنية wl_بفر *) * cdata->عدد_چوکھٹے));

        cache->ناپ = ناپ;
        لكل (صحيح i = 0; i < cdata->عدد_چوکھٹے; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_بفر(cursor->images[i]);
        }

        WAYLAND_wl_list_داخل_کرو(&cdata->cursor_انکڑے.system.cursor_بفر_cache, &cache->گرہ);
    }

    أرجع cache;
}

ساكن bool Wayland_GetSystemCursor(SDL_Cursor_انکڑے *cdata, SDL_WaylandCursorState *state, صحيح *dst_ناپ, صحيح *hot_x, صحيح *hot_y)
{
    SDL_Video_انکڑے *vdata = SDL_GetVideoDevice()->اندرونی;
    بنية wl_cursor_theme *theme = عدم;
    ثابت حرف *css_name = "default";
    ثابت حرف *fallback_name = عدم;
    مزدوج scale_ضارب_2 = state->scale;
    صحيح theme_ناپ = dbus_cursor_ناپ;

    // Fallback envvar if the DBus properties don't exist
    إذا (theme_ناپ <= 0) {
        ثابت حرف *xcursor_ناپ = SDL_getenv("XCURSOR_SIZE");
        إذا (xcursor_ناپ) {
            theme_ناپ = SDL_atoi(xcursor_ناپ);
        }
    }
    إذا (theme_ناپ <= 0) {
        theme_ناپ = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ثابت صحيح scaled_ناپ = (صحيح)SDL_lround(theme_ناپ * scale_ضارب_2);
    لكل (صحيح i = 0; i < vdata->عدد_cursor_themes; ++i) {
        إذا (vdata->cursor_themes[i].ناپ == scaled_ناپ) {
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

        theme = WAYLAND_wl_cursor_theme_لدو(xcursor_theme, scaled_ناپ, vdata->shm);
        vdata->cursor_themes[vdata->عدد_cursor_themes].ناپ = scaled_ناپ;
        vdata->cursor_themes[vdata->عدد_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_انکڑے.system.id, &fallback_name);
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
    cdata->عدد_چوکھٹے = cursor->image_گنتی_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_ناپ);
    state->system_cursor_handle = c;

    إذا (cursor->image_گنتی_2 > 1 && !cdata->چوکھٹا_durations_ms) {
        cdata->کل_duration_ms = 0;
        cdata->چوکھٹا_durations_ms = SDL_calloc(cursor->image_گنتی_2, حجم(Uint32));

        لكل (صحيح i = 0; i < cursor->image_گنتی_2; ++i) {
            cdata->چوکھٹا_durations_ms[i] = cursor->images[i]->delay;
            cdata->کل_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_ناپ = SDL_lround(cursor->images[0]->چوڑائی / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    أرجع true;
}

ساكن صحيح surface_ترتیب_دیو_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ساكن SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحيح چوکھٹا_گنتی, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_انکڑے *انکڑے = عدم;
    Wayland_SHMPool *shm_pool = عدم;
    صحيح pool_ناپ = 0;
    صحيح max_images = 0;
    bool is_ڈھیر = false;
    بنية SurfaceArray
    {
        SDL_Surface **surfaces;
        صحيح گنتی;
    } *surfaces = SDL_small_alloc(بنية SurfaceArray, چوکھٹا_گنتی, &is_ڈھیر);
    إذا (!surfaces) {
        اذهب failed;
    }
    SDL_memset(surfaces, 0, حجم(بنية SurfaceArray) * چوکھٹا_گنتی);

    // Calculate the total allocation size.
    لكل (صحيح i = 0; i < چوکھٹا_گنتی; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(چوکھٹے[i].surface, &surfaces[i].گنتی);
        إذا (!surfaces[i].surfaces) {
            اذهب failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].گنتی, حجم(SDL_Surface *), surface_ترتیب_دیو_callback);
        max_images = SDL_max(max_images, surfaces[i].گنتی);
        لكل (صحيح j = 0; j < surfaces[i].گنتی; ++j) {
            pool_ناپ += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    انکڑے = SDL_calloc(1, حجم(*انکڑے) + (حجم(CustomCursorImage) * max_images * چوکھٹا_گنتی));
    إذا (!انکڑے) {
        اذهب failed;
    }

    انکڑے->چوکھٹا_durations_ms = SDL_calloc(چوکھٹا_گنتی, حجم(Uint32));
    إذا (!انکڑے->چوکھٹا_durations_ms) {
        اذهب failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_ناپ);
    إذا (!shm_pool) {
        اذهب failed;
    }

    cursor->اندرونی = انکڑے;
    انکڑے->cursor_انکڑے.custom.چوڑائی = چوکھٹے[0].surface->w;
    انکڑے->cursor_انکڑے.custom.اچائی = چوکھٹے[0].surface->h;
    انکڑے->cursor_انکڑے.custom.hot_x = hot_x;
    انکڑے->cursor_انکڑے.custom.hot_y = hot_y;
    انکڑے->cursor_انکڑے.custom.images_فی_چوکھٹا = max_images;
    انکڑے->عدد_چوکھٹے = چوکھٹا_گنتی;

    لكل (صحيح i = 0; i < چوکھٹا_گنتی; ++i) {
        انکڑے->چوکھٹا_durations_ms[i] = چوکھٹے[i].duration;
        إذا (انکڑے->کل_duration_ms < SDL_MAX_UINT32) {
            إذا (انکڑے->چوکھٹا_durations_ms[i] > 0) {
                انکڑے->کل_duration_ms += انکڑے->چوکھٹا_durations_ms[i];
            } وإلا {
                انکڑے->کل_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحيح وتھ_2 = i * max_images;
        لكل (صحيح j = 0; j < surfaces[i].گنتی; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                إذا (!surface) {
                    اذهب failed;
                }
            }

            انکڑے->cursor_انکڑے.custom.images[وتھ_2 + j].چوڑائی = surface->w;
            انکڑے->cursor_انکڑے.custom.images[وتھ_2 + j].اچائی = surface->h;

            فراغ *buf_انکڑے;
            انکڑے->cursor_انکڑے.custom.images[وتھ_2 + j].بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, surface->w, surface->h, &buf_انکڑے);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_انکڑے, surface->w * 4, true);

            إذا (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_ڈھیر);
    Wayland_ReleaseSHMPool(shm_pool);

    أرجع cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    إذا (انکڑے) {
        SDL_free(انکڑے->چوکھٹا_durations_ms);
        لكل (صحيح i = 0; i < انکڑے->cursor_انکڑے.custom.images_فی_چوکھٹا * چوکھٹا_گنتی; ++i) {
            إذا (انکڑے->cursor_انکڑے.custom.images[i].بفر_2) {
                wl_بفر_destroy(انکڑے->cursor_انکڑے.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(انکڑے);

    إذا (surfaces) {
        لكل (صحيح i = 0; i < چوکھٹا_گنتی; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_ڈھیر);
    }

    SDL_free(cursor);

    أرجع عدم;
}

ساكن SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_چوکھٹا_Info چوکھٹا = {
        surface, 0
    };

    أرجع Wayland_CreateAnimatedCursor(&چوکھٹا, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));

    إذا (cursor) {
        SDL_Cursor_انکڑے *cdata = SDL_calloc(1, حجم(*cdata));
        إذا (!cdata) {
            SDL_free(cursor);
            أرجع عدم;
        }
        cursor->اندرونی = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_انکڑے.system.cursor_بفر_cache);
        cdata->cursor_انکڑے.system.id = id;
        cdata->is_system_cursor = true;
    }

    أرجع cursor;
}

ساكن SDL_Cursor *Wayland_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع Wayland_CreateSystemCursor(id);
}

ساكن فراغ Wayland_Free_Cursor_انکڑے(SDL_Cursor_انکڑے *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_انکڑے *video_انکڑے = video_device->اندرونی;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_انکڑے->seat_list, link)
    {
        إذا (seat->اشارہ_گر_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_چوکھٹا_Callback(&seat->اشارہ_گر_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            إذا (!d->is_system_cursor && seat->اشارہ_گر_2.cursor_state.surface) {
                wl_surface_attach(seat->اشارہ_گر_2.cursor_state.surface, عدم, 0, 0);
            }

            seat->اشارہ_گر_2.cursor_state.current_cursor = عدم;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_چوکھٹا_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                إذا (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->اشارہ_گر_2.cursor_state.surface, عدم, 0, 0);
                }

                tool->cursor_state.current_cursor = عدم;
            }
        }
    }

    إذا (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *عارضی;
        wl_list_for_each_محفوظ(c, عارضی, &d->cursor_انکڑے.system.cursor_بفر_cache, گرہ) {
            SDL_free(c);
        }
    } وإلا {
        لكل (صحيح i = 0; i < d->عدد_چوکھٹے * d->cursor_انکڑے.custom.images_فی_چوکھٹا; ++i) {
            إذا (d->cursor_انکڑے.custom.images[i].بفر_2) {
                wl_بفر_destroy(d->cursor_انکڑے.custom.images[i].بفر_2);
            }
        }
    }

    SDL_free(d->چوکھٹا_durations_ms);
}

ساكن فراغ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        أرجع;
    }

    // Probably not a cursor we own
    إذا (!cursor->اندرونی) {
        أرجع;
    }

    Wayland_Free_Cursor_انکڑے(cursor->اندرونی);

    SDL_free(cursor->اندرونی);
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
    حالة SDL_SYSTEM_CURSOR_ترقی:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ترقی;
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
    حالة SDL_SYSTEM_CURSOR_اشارہ_گر:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_اشارہ_گر;
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
    حالة SDL_SYSTEM_CURSOR_خانہ_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_خانہ_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_صف_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_صف_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_وچ:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_وچ;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_باہرلا:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_باہرلا;
        اكسر;
    افتراضي:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    أرجع shape;
}

تعريفنوع بنية Wayland_اشارہ_گر_Object
{
    اتحاد
    {
        بنية wl_اشارہ_گر *wl_اشارہ_گر;
        بنية zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_اشارہ_گر;
} Wayland_اشارہ_گر_Object;

ساكن فراغ Wayland_Cursor_State_سیٹ_Cursor(SDL_WaylandCursorState *state, ثابت Wayland_اشارہ_گر_Object *obj, SDL_کھڑکی_انکڑے *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_انکڑے *viddata = SDL_GetVideoDevice()->اندرونی;
    SDL_Cursor_انکڑے *cursor_انکڑے = cursor ? cursor->اندرونی : عدم;
    صحيح dst_چوڑائی = 0;
    صحيح dst_اچائی = 0;
    صحيح hot_x;
    صحيح hot_y;

    // Stop the frame callback for old animated cursors.
    إذا (cursor_انکڑے != state->current_cursor) {
        Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
    }

    إذا (cursor) {
        إذا (cursor_انکڑے == state->current_cursor && state->current_چوکھٹا >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            إذا (cursor_انکڑے->عدد_چوکھٹے > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            أرجع;
        }

        إذا (cursor_انکڑے->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            إذا (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                إذا (state->surface) {
                    wl_surface_attach(state->surface, عدم, 0, 0);
                    wl_surface_commit(state->surface);

                    إذا (obj->is_اشارہ_گر) {
                        wl_اشارہ_گر_سیٹ_cursor(obj->wl_اشارہ_گر, serial, عدم, 0, 0);
                    } وإلا {
                        zwp_tablet_tool_v2_سیٹ_cursor(obj->wl_tool, serial, عدم, 0, 0);
                    }

                    إذا (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = عدم;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = عدم;
                }

                ثابت تعداد wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_انکڑے->cursor_انکڑے.system.id);
                wp_cursor_shape_device_v1_سیٹ_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_انکڑے;
                state->current_چوکھٹا = 0;

                أرجع;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ضارب_2 : 1.0;
            إذا (!Wayland_GetSystemCursor(cursor_انکڑے, state, &dst_چوڑائی, &hot_x, &hot_y)) {
                أرجع;
            }

            dst_اچائی = dst_چوڑائی;
        } وإلا {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            إذا (!focus || (focus->اشارہ_گر_scale.x == 1.0 && focus->اشارہ_گر_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ضارب_2 : 1.0;
                dst_چوڑائی = cursor_انکڑے->cursor_انکڑے.custom.چوڑائی;
                dst_اچائی = cursor_انکڑے->cursor_انکڑے.custom.اچائی;
                hot_x = cursor_انکڑے->cursor_انکڑے.custom.hot_x;
                hot_y = cursor_انکڑے->cursor_انکڑے.custom.hot_y;
            } وإلا {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->اشارہ_گر_scale.x, focus->اشارہ_گر_scale.y);
                dst_چوڑائی = SDL_max((صحيح)SDL_lround((مزدوج)cursor_انکڑے->cursor_انکڑے.custom.چوڑائی / focus->اشارہ_گر_scale.x), 1);
                dst_اچائی = SDL_max((صحيح)SDL_lround((مزدوج)cursor_انکڑے->cursor_انکڑے.custom.اچائی / focus->اشارہ_گر_scale.y), 1);
                hot_x = (صحيح)SDL_lround((مزدوج)cursor_انکڑے->cursor_انکڑے.custom.hot_x / focus->اشارہ_گر_scale.x);
                hot_y = (صحيح)SDL_lround((مزدوج)cursor_انکڑے->cursor_انکڑے.custom.hot_y / focus->اشارہ_گر_scale.y);
            }

        }

        state->current_cursor = cursor_انکڑے;

        إذا (!state->surface) {
            بنية wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        بنية wl_بفر *بفر_2 = Wayland_Cursor_State_Get_چوکھٹا(state, 0);
        wl_surface_attach(state->surface, بفر_2, 0, 0);
        state->current_چوکھٹا = 0;

        إذا (state->scale != 1.0) {
            إذا (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_سیٹ_سروت(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_سیٹ_destination(state->viewport, dst_چوڑائی, dst_اچائی);
        } وإلا إذا (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = عدم;
        }

        إذا (obj->is_اشارہ_گر) {
            wl_اشارہ_گر_سیٹ_cursor(obj->wl_اشارہ_گر, serial, state->surface, hot_x, hot_y);
        } وإلا {
            zwp_tablet_tool_v2_سیٹ_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        إذا (wl_surface_get_نسخہ(state->surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخہ) {
            wl_surface_damage_بفر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        إذا (cursor_انکڑے->عدد_چوکھٹے > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_سیٹ_چوکھٹا_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } وإلا {
        Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
        state->current_cursor = عدم;

        إذا (state->surface) {
            wl_surface_attach(state->surface, عدم, 0, 0);
            wl_surface_commit(state->surface);
        }

        إذا (obj->is_اشارہ_گر) {
            wl_اشارہ_گر_سیٹ_cursor(obj->wl_اشارہ_گر, serial, عدم, 0, 0);
        } وإلا {
            zwp_tablet_tool_v2_سیٹ_cursor(obj->wl_tool, serial, عدم, 0, 0);
        }
    }
}

ساكن فراغ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_چوکھٹا_Callback(state);
    state->current_چوکھٹا = -1;
}

فراغ Wayland_Display_Update_اشارہ_گر_Focused_Scale(SDL_کھڑکی_انکڑے *updated_کھڑکی)
{
    SDL_Video_انکڑے *viddata = updated_کھڑکی->wayland_انکڑے;
    SDL_WaylandSeat *seat;
    ثابت مزدوج new_scale = SDL_min(updated_کھڑکی->اشارہ_گر_scale.x, updated_کھڑکی->اشارہ_گر_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        إذا (seat->اشارہ_گر_2.focus == updated_کھڑکی) {
            SDL_WaylandCursorState *state = &seat->اشارہ_گر_2.cursor_state;
            إذا (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_اشارہ_گر_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == updated_کھڑکی) {
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
    SDL_Video_انکڑے *d = vd->اندرونی;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_اشارہ_گر_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->اشارہ_گر_2.wl_اشارہ_گر) {
            obj.wl_اشارہ_گر = seat->اشارہ_گر_2.wl_اشارہ_گر;
            obj.is_اشارہ_گر = true;
            إذا (mouse->focus && mouse->focus->اندرونی == seat->اشارہ_گر_2.focus) {
                Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, seat->اشارہ_گر_2.focus, seat->اشارہ_گر_2.enter_serial, cursor);
            } وإلا إذا (!seat->اشارہ_گر_2.focus) {
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
            إذا (tool->focus && (!mouse->focus || mouse->focus->اندرونی == tool->focus)) {
                Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا إذا (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    أرجع true;
}

فراغ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_کھڑکی_انکڑے *کھڑکی, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_انکڑے *d = vd->اندرونی;

    إذا (seat->اشارہ_گر_2.wl_اشارہ_گر) {
        إذا (d->wp_اشارہ_گر_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / کھڑکی->اشارہ_گر_scale.x, 0, کھڑکی->current.logical_چوڑائی));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / کھڑکی->اشارہ_گر_scale.y, 0, کھڑکی->current.logical_اچائی));
            wp_اشارہ_گر_warp_v1_warp_اشارہ_گر(d->wp_اشارہ_گر_warp_v1, کھڑکی->surface, seat->اشارہ_گر_2.wl_اشارہ_گر, f_x, f_y, seat->اشارہ_گر_2.enter_serial);
        } وإلا {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            إذا (seat->اشارہ_گر_2.confined_اشارہ_گر) {
                zwp_confined_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.confined_اشارہ_گر);
                seat->اشارہ_گر_2.confined_اشارہ_گر = عدم;
                update_grabs = true;
            }
            إذا (seat->اشارہ_گر_2.locked_اشارہ_گر) {
                zwp_locked_اشارہ_گر_v1_destroy(seat->اشارہ_گر_2.locked_اشارہ_گر);
                seat->اشارہ_گر_2.locked_اشارہ_گر = عدم;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            بنية zwp_locked_اشارہ_گر_v1 *warp_جندرا =
                zwp_اشارہ_گر_constraints_v1_جندرا_اشارہ_گر(d->اشارہ_گر_constraints, کھڑکی->surface,
                                                        seat->اشارہ_گر_2.wl_اشارہ_گر, عدم,
                                                        ZWP_اشارہ_گر_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / کھڑکی->اشارہ_گر_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / کھڑکی->اشارہ_گر_scale.y);
            zwp_locked_اشارہ_گر_v1_سیٹ_cursor_position_hint(warp_جندرا, f_x, f_y);
            wl_surface_commit(کھڑکی->surface);

            zwp_locked_اشارہ_گر_v1_destroy(warp_جندرا);

            إذا (update_grabs) {
                Wayland_Seat_Update_اشارہ_گر_Grab(seat);
            }
        }

        إذا (wl_اشارہ_گر_get_نسخہ(seat->اشارہ_گر_2.wl_اشارہ_گر) < WL_اشارہ_گر_WARP_SINCE_نسخہ) {
            SDL_SendMouseWarp(0, کھڑکی->sdlwindow, seat->اشارہ_گر_2.sdl_id, x, y);
        }
    }
}

ساكن bool Wayland_WarpMouseRelative(SDL_کھڑکی *کھڑکی, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_انکڑے *d = vd->اندرونی;
    SDL_کھڑکی_انکڑے *wind = کھڑکی->اندرونی;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشارہ_گر_warp_v1 || d->اشارہ_گر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (wind == seat->اشارہ_گر_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } وإلا {
        أرجع SDL_سیٹ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_انکڑے *d = vd->اندرونی;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشارہ_گر_warp_v1 || d->اشارہ_گر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_کھڑکی_انکڑے *wind = seat->اشارہ_گر_2.focus ? seat->اشارہ_گر_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            إذا (wind) {
                SDL_کھڑکی *کھڑکی = wind->sdlwindow;

                صحيح abs_x, abs_y;
                SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, کھڑکی->x, کھڑکی->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, کھڑکی->w, کھڑکی->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                إذا (SDL_نقطہ_وچ_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } وإلا {
        أرجع SDL_سیٹ_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_انکڑے *انکڑے = vd->اندرونی;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    إذا (!انکڑے->relative_اشارہ_گر_manager) {
        أرجع SDL_سیٹ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    إذا (!انکڑے->اشارہ_گر_constraints) {
        أرجع SDL_سیٹ_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_اشارہ_گر_Grabs(انکڑے, عدم);
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
    SDL_MouseButtonFlags نتیجہ = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    إذا (mouse->focus) {
        SDL_Video_انکڑے *video_انکڑے = SDL_GetVideoDevice()->اندرونی;
        SDL_WaylandSeat *seat;
        صحيح off_x, off_y;
        SDL_Relative_منزل_Global_For_کھڑکی(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_انکڑے->seat_list, link) {
            نتیجہ |= seat->اشارہ_گر_2.buttons_pressed;
        }
    } وإلا {
        *x = 0.f;
        *y = 0.f;
    }

    أرجع نتیجہ;
}

#إذا 0  // TODO RECONNECT: See waylandvideo.c for more information!
ساكن فراغ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_انکڑے *vdata)
{
    SDL_Cursor_انکڑے *cdata = cursor->اندرونی;

    // Probably not a cursor we own
    إذا (cdata == عدم) {
        أرجع;
    }

    Wayland_Free_Cursor_انکڑے(cdata);

    // We're not currently freeing this, so... yolo?
    إذا (cdata->shm_انکڑے != عدم) {
        فراغ *old_انکڑے_اشارہ_گر = cdata->shm_انکڑے;
        صحيح stride = cdata->w * 4;

        create_بفر_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_انکڑے, old_انکڑے_اشارہ_گر, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_سیٹ_user_انکڑے(cdata->surface, عدم);
}

فراغ Wayland_RecreateCursors(فراغ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_انکڑے *vdata = SDL_GetVideoDevice()->اندرونی;

    إذا (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = عدم;
        vdata->عدد_cursor_themes = 0;
    }

    إذا (mouse == عدم) {
        أرجع;
    }

    لكل (cursor = mouse->cursors; cursor != عدم; cursor = cursor->اگلا) {
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
#جے_انت // 0

فراغ Wayland_InitMouse(SDL_Video_انکڑے *انکڑے)
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

    SDL_کامیابی_Test_نتیجہ r = SDL_HITTEST_عام;
    طالما (r <= SDL_HITTEST_RESIZE_بایاں) {
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
        حالة SDL_HITTEST_RESIZE_چوٹی:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_دایاں:
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
        حالة SDL_HITTEST_RESIZE_بایاں:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            اكسر;
        }
        r++;
    }

#جے_تعریف_شدہ SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_انکڑے *d = vd->اندرونی;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    إذا (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#جے_انت

    SDL_سیٹ_Default_Cursor(Wayland_CreateDefaultCursor());
}

فراغ Wayland_FiniMouse(SDL_Video_انکڑے *انکڑے)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = عدم;
    }

    Wayland_FreeCursorThemes(انکڑے);

#جے_تعریف_شدہ SDL_USE_LIBDBUS
    Wayland_DBus_انت_Cursor_Properties();
#جے_انت
}

فراغ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->اشارہ_گر_2.cursor_state);
}

فراغ Wayland_Seat_سیٹ_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کھڑکی_انکڑے *اشارہ_گر_focus = seat->اشارہ_گر_2.focus;
    ثابت Wayland_اشارہ_گر_Object obj = {
        .wl_اشارہ_گر = seat->اشارہ_گر_2.wl_اشارہ_گر,
        .is_اشارہ_گر = true
    };

    Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, mouse->def_cursor);
}

فراغ Wayland_Seat_Update_اشارہ_گر_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کھڑکی_انکڑے *اشارہ_گر_focus = seat->اشارہ_گر_2.focus;
    ثابت Wayland_اشارہ_گر_Object obj = {
        .wl_اشارہ_گر = seat->اشارہ_گر_2.wl_اشارہ_گر,
        .is_اشارہ_گر = true
    };

    إذا (اشارہ_گر_focus) {
        إذا (mouse->cursor_visible) {
            إذا (!seat->اشارہ_گر_2.relative_اشارہ_گر || !mouse->relative_منوال_hide_cursor) {
                ثابت SDL_کامیابی_Test_نتیجہ rc = اشارہ_گر_focus->کامیابی_test_نتیجہ;

                إذا (seat->اشارہ_گر_2.relative_اشارہ_گر || rc == SDL_HITTEST_عام || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, mouse->cur_cursor);
                } وإلا {
                    Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, sys_cursors[rc]);
                }
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_سیٹ_Cursor(&seat->اشارہ_گر_2.cursor_state, &obj, اشارہ_گر_focus, seat->اشارہ_گر_2.enter_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&seat->اشارہ_گر_2.cursor_state);
    }
}

فراغ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_کھڑکی_انکڑے *tool_focus = tool->focus;
    ثابت Wayland_اشارہ_گر_Object obj = {
        .wl_tool = tool->wltool,
        .is_اشارہ_گر = false
    };

    إذا (tool_focus) {
        إذا (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال);

            إذا (!relative || !mouse->relative_منوال_hide_cursor) {
                Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_سیٹ_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND

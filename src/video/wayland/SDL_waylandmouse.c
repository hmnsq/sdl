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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

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

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_چپ + 1];

ساكن bool Wayland_مجموعه_Relative_Mouse_نما(bool enabled);

تعريفنوع بنية
{
    صحيح عرض;
    صحيح ارتفاع;
    بنية wl_میانگیر *میانگیر_2;
} CustomCursorImage;

تعريفنوع بنية
{
    // The base dimensions of the cursor.
    صحيح عرض;
    صحيح ارتفاع;
    صحيح hot_x;
    صحيح hot_y;

    صحيح images_در_هر_قاب;
    CustomCursorImage images[];
} Wayland_CustomCursor;

تعريفنوع بنية
{
    صحيح اندازه;
    بنية wl_list گره;
    بنية wl_میانگیر *buffers[];
} Wayland_CachedSystemCursor;

تعريفنوع بنية
{
    SDL_SystemCursor id;
    بنية wl_list cursor_میانگیر_cache;
} Wayland_SystemCursor;

بنية SDL_Cursor_داده
{
    // Cursor animation data.
    Uint32 *قاب_durations_ms;
    Uint32 مجموع_duration_ms;
    صحيح رقم_قابها;
    bool is_system_cursor;

    اتحاد
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_داده;
};

ساكن صحيح dbus_cursor_اندازه;
ساكن حرف *dbus_cursor_theme;

ساكن فراغ Wayland_FreeCursorThemes(SDL_Video_داده *vdata)
{
    لكل (صحيح i = 0; i < vdata->رقم_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->رقم_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = عدم;
}

#اگر_تعریف_شده SDL_USE_LIBDBUS

#ضمن "../../core/linux/SDL_dbus.h"

#تعریف_کن CURSOR_گره        "org.freedesktop.portal.Desktop"
#تعریف_کن CURSOR_مسیر        "/org/freedesktop/portal/desktop"
#تعریف_کن CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#تعریف_کن CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#تعریف_کن CURSOR_SIGNAL_NAME "SettingChanged"
#تعریف_کن CURSOR_اندازه_کلید    "cursor-size"
#تعریف_کن CURSOR_THEME_کلید   "cursor-theme"

ساكن DBus_پیام *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ثابت حرف *کلید)
{
    ساكن ثابت حرف *iface = "org.gnome.desktop.interface";

    DBus_پیام *پاسخ = عدم;
    DBus_پیام *پیام_2 = dbus->پیام_new_روش_call(CURSOR_گره,
                                                     CURSOR_مسیر,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //روش

    إذا (پیام_2) {
        إذا (dbus->پیام_append_آرگومانها(پیام_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &کلید, DBUS_TYPE_INVALID)) {
            پاسخ = dbus->connection_send_with_پاسخ_and_بلوک(dbus->session_conn, پیام_2, DBUS_TIMEOUT_USE_DEFAULT, عدم);
        }
        dbus->پیام_unref(پیام_2);
    }

    أرجع پاسخ;
}

ساكن bool Wayland_Parse_DBus_پاسخ(SDL_DBusContext *dbus, DBus_پیام *پاسخ, صحيح type, فراغ *مقدار)
{
    DBus_پیام_Iter iter[3];

    dbus->پیام_iter_init(پاسخ, &iter[0]);
    إذا (dbus->پیام_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->پیام_iter_recurse(&iter[0], &iter[1]);
    إذا (dbus->پیام_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        أرجع false;
    }

    dbus->پیام_iter_recurse(&iter[1], &iter[2]);
    إذا (dbus->پیام_iter_get_arg_type(&iter[2]) != type) {
        أرجع false;
    }

    dbus->پیام_iter_get_basic(&iter[2], مقدار);

    أرجع true;
}

ساكن DBus_Handler_نتیجه Wayland_DBus_Cursor_پیام_Filter(DBusConnection *conn, DBus_پیام *پیام_2, فراغ *داده)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_داده *vdata = (SDL_Video_داده *)داده;

    إذا (dbus->پیام_is_signal(پیام_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_پیام_Iter signal_iter, variant_iter;
        ثابت حرف *namespace, *کلید;

        dbus->پیام_iter_init(پیام_2, &signal_iter);
        // Check if the parameters are what we expect
        إذا (dbus->پیام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->پیام_iter_get_basic(&signal_iter, &namespace);
        إذا (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            اذهب not_our_signal;
        }
        إذا (!dbus->پیام_iter_بعدی(&signal_iter)) {
            اذهب not_our_signal;
        }
        إذا (dbus->پیام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            اذهب not_our_signal;
        }
        dbus->پیام_iter_get_basic(&signal_iter, &کلید);
        إذا (SDL_strcmp(CURSOR_اندازه_کلید, کلید) == 0) {
            صحيح new_cursor_اندازه;

            إذا (!dbus->پیام_iter_بعدی(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->پیام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->پیام_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->پیام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                اذهب not_our_signal;
            }
            dbus->پیام_iter_get_basic(&variant_iter, &new_cursor_اندازه);

            إذا (dbus_cursor_اندازه != new_cursor_اندازه) {
                dbus_cursor_اندازه = new_cursor_اندازه;
                SDL_RedrawCursor(); // Force cursor update
            }
        } وإلا إذا (SDL_strcmp(CURSOR_THEME_کلید, کلید) == 0) {
            ثابت حرف *new_cursor_theme = عدم;

            إذا (!dbus->پیام_iter_بعدی(&signal_iter)) {
                اذهب not_our_signal;
            }
            إذا (dbus->پیام_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                اذهب not_our_signal;
            }
            dbus->پیام_iter_recurse(&signal_iter, &variant_iter);
            إذا (dbus->پیام_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                اذهب not_our_signal;
            }
            dbus->پیام_iter_get_basic(&variant_iter, &new_cursor_theme);

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

        أرجع DBUS_HANDLER_نتیجه_HANDLED;
    }

not_our_signal:
    أرجع DBUS_HANDLER_نتیجه_NOT_YET_HANDLED;
}

ساكن فراغ Wayland_DBusInitCursorProperties(SDL_Video_داده *vdata)
{
    DBus_پیام *پاسخ;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool جمع_کن_filter = false;

    إذا (!dbus) {
        أرجع;
    }

    إذا ((پاسخ = Wayland_ReadDBusProperty(dbus, CURSOR_اندازه_کلید))) {
        إذا (Wayland_Parse_DBus_پاسخ(dbus, پاسخ, DBUS_TYPE_INT32, &dbus_cursor_اندازه)) {
            جمع_کن_filter = true;
        }
        dbus->پیام_unref(پاسخ);
    }

    إذا ((پاسخ = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_کلید))) {
        ثابت حرف *موقت = عدم;
        إذا (Wayland_Parse_DBus_پاسخ(dbus, پاسخ, DBUS_TYPE_STRING, &موقت)) {
            جمع_کن_filter = true;

            إذا (موقت) {
                dbus_cursor_theme = SDL_strdup(موقت);
            }
        }
        dbus->پیام_unref(پاسخ);
    }

    // Only add the filter if at least one of the settings we want is present.
    إذا (جمع_کن_filter) {
        dbus->bus_جمع_کن_تطابق(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            عدم);
        dbus->connection_جمع_کن_filter(dbus->session_conn, &Wayland_DBus_Cursor_پیام_Filter, vdata, عدم);
        dbus->connection_flush(dbus->session_conn);
    }
}

ساكن فراغ Wayland_DBus_پایان_Cursor_Properties(فراغ)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = عدم;
}

#پایان_اگر

ساكن بنية wl_میانگیر *Wayland_Cursor_State_Get_قاب(SDL_WaylandCursorState *state, صحيح قاب_شاخص_2)
{
    SDL_Cursor_داده *داده = state->current_cursor;

    إذا (داده) {
        إذا (!داده->is_system_cursor) {
            ثابت صحيح جابه_جایی_2 = داده->cursor_داده.custom.images_در_هر_قاب * قاب_شاخص_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = عدم;
            ثابت صحيح هدف_area = SDL_lround(داده->cursor_داده.custom.عرض * داده->cursor_داده.custom.ارتفاع * state->scale);
            صحيح closest_area = 0;
            لكل (صحيح i = 0; i < داده->cursor_داده.custom.images_در_هر_قاب && closest_area < هدف_area && داده->cursor_داده.custom.images[جابه_جایی_2 + i].میانگیر_2; ++i) {
                closest = &داده->cursor_داده.custom.images[جابه_جایی_2 + i];
                closest_area = closest->عرض * closest->ارتفاع;
            }

            أرجع closest ? closest->میانگیر_2 : عدم;
        } وإلا {
            أرجع ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[قاب_شاخص_2];
        }
    }

    أرجع عدم;
}

ساكن فراغ cursor_قاب_انجامشده(فراغ *داده, بنية wl_callback *cb, uint32_t زمان);
ساكن ثابت بنية wl_callback_listener cursor_قاب_listener = {
    cursor_قاب_انجامشده
};

ساكن فراغ cursor_قاب_انجامشده(فراغ *داده, بنية wl_callback *cb, uint32_t زمان)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)داده;
    إذا (!state->current_cursor) {
        أرجع;
    }

    Uint32 *قابها = state->current_cursor->قاب_durations_ms;
    SDL_Cursor_داده *c = state->current_cursor;

    ثابت Uint64 now = SDL_GetTicks();
    ثابت Uint32 elapsed = (now - state->آخرین_قاب_callback_زمان_ms) % c->مجموع_duration_ms;
    Uint32 advance = 0;
    صحيح بعدی = state->current_قاب;

    state->current_قاب_زمان_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    لكل (Uint32 t = قابها[بعدی]; t <= state->current_قاب_زمان_ms; t += قابها[بعدی]) {
        بعدی = (بعدی + 1) % c->رقم_قابها;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        إذا (!قابها[بعدی]) {
            اكسر;
        }
    }

    wl_callback_destroy(cb);
    state->قاب_callback = عدم;

    // Don't queue another callback if this frame time is infinite.
    إذا (قابها[بعدی]) {
        state->قاب_callback = wl_surface_قاب(state->surface);
        wl_callback_جمع_کن_listener(state->قاب_callback, &cursor_قاب_listener, داده);
    }

    state->current_قاب_زمان_ms -= advance;
    state->آخرین_قاب_callback_زمان_ms = now;
    state->current_قاب = بعدی;

    بنية wl_میانگیر *میانگیر_2 = Wayland_Cursor_State_Get_قاب(state, بعدی);
    wl_surface_attach(state->surface, میانگیر_2, 0, 0);

    إذا (wl_surface_get_نسخه(state->surface) >= WL_SURFACE_DAMAGE_میانگیر_SINCE_نسخه) {
        wl_surface_damage_میانگیر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

فراغ Wayland_Cursor_State_مجموعه_قاب_Callback(SDL_WaylandCursorState *state, فراغ *userdata)
{
    SDL_Video_داده *viddata = SDL_GetVideoDevice()->داخلی;
    Wayland_قفل_Event_Thread(viddata->event_thread_context);

    state->قاب_callback = wl_surface_قاب(state->surface);
    wl_callback_جمع_کن_listener(state->قاب_callback, &cursor_قاب_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

فراغ Wayland_Cursor_State_Destroy_قاب_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_داده *viddata = SDL_GetVideoDevice()->داخلی;
    Wayland_قفل_Event_Thread(viddata->event_thread_context);

    إذا (state->قاب_callback) {
        wl_callback_destroy(state->قاب_callback);
        state->قاب_callback = عدم;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

ساكن فراغ Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->آخرین_قاب_callback_زمان_ms = SDL_GetTicks();
    state->current_قاب_زمان_ms = 0;
    state->current_قاب = 0;
}

ساكن فراغ Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool قفل_2)
{
    إذا (قفل_2) {
        SDL_Video_داده *viddata = SDL_GetVideoDevice()->داخلی;
        Wayland_قفل_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } وإلا {
        Wayland_CursorStateResetAnimationState(state);
    }
}

فراغ Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_قاب_Callback(state);
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

ساكن Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_داده *cdata, بنية wl_cursor *cursor, صحيح اندازه)
{
    Wayland_CachedSystemCursor *cache = عدم;

    // Is this cursor already cached at the target scale?
    إذا (!WAYLAND_wl_list_خالی(&cdata->cursor_داده.system.cursor_میانگیر_cache)) {
        Wayland_CachedSystemCursor *c = عدم;
        wl_list_for_each (c, &cdata->cursor_داده.system.cursor_میانگیر_cache, گره) {
            إذا (c->اندازه == اندازه) {
                cache = c;
                اكسر;
            }
        }
    }

    إذا (!cache) {
        cache = SDL_calloc(1, حجم(Wayland_CachedSystemCursor) + (حجم(بنية wl_میانگیر *) * cdata->رقم_قابها));

        cache->اندازه = اندازه;
        لكل (صحيح i = 0; i < cdata->رقم_قابها; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_میانگیر(cursor->images[i]);
        }

        WAYLAND_wl_list_درج(&cdata->cursor_داده.system.cursor_میانگیر_cache, &cache->گره);
    }

    أرجع cache;
}

ساكن bool Wayland_GetSystemCursor(SDL_Cursor_داده *cdata, SDL_WaylandCursorState *state, صحيح *dst_اندازه, صحيح *hot_x, صحيح *hot_y)
{
    SDL_Video_داده *vdata = SDL_GetVideoDevice()->داخلی;
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
    لكل (صحيح i = 0; i < vdata->رقم_cursor_themes; ++i) {
        إذا (vdata->cursor_themes[i].اندازه == scaled_اندازه) {
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

        theme = WAYLAND_wl_cursor_theme_بارگیری(xcursor_theme, scaled_اندازه, vdata->shm);
        vdata->cursor_themes[vdata->رقم_cursor_themes].اندازه = scaled_اندازه;
        vdata->cursor_themes[vdata->رقم_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_داده.system.id, &fallback_name);
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
    cdata->رقم_قابها = cursor->image_شمار_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_اندازه);
    state->system_cursor_handle = c;

    إذا (cursor->image_شمار_2 > 1 && !cdata->قاب_durations_ms) {
        cdata->مجموع_duration_ms = 0;
        cdata->قاب_durations_ms = SDL_calloc(cursor->image_شمار_2, حجم(Uint32));

        لكل (صحيح i = 0; i < cursor->image_شمار_2; ++i) {
            cdata->قاب_durations_ms[i] = cursor->images[i]->delay;
            cdata->مجموع_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_اندازه = SDL_lround(cursor->images[0]->عرض / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    أرجع true;
}

ساكن صحيح surface_مرتب_سازی_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

ساكن SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_قاب_Info *قابها, صحيح قاب_شمار, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_داده *داده = عدم;
    Wayland_SHMPool *shm_pool = عدم;
    صحيح pool_اندازه = 0;
    صحيح max_images = 0;
    bool is_پشته = false;
    بنية SurfaceArray
    {
        SDL_Surface **surfaces;
        صحيح شمار;
    } *surfaces = SDL_small_alloc(بنية SurfaceArray, قاب_شمار, &is_پشته);
    إذا (!surfaces) {
        اذهب failed;
    }
    SDL_memset(surfaces, 0, حجم(بنية SurfaceArray) * قاب_شمار);

    // Calculate the total allocation size.
    لكل (صحيح i = 0; i < قاب_شمار; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(قابها[i].surface, &surfaces[i].شمار);
        إذا (!surfaces[i].surfaces) {
            اذهب failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].شمار, حجم(SDL_Surface *), surface_مرتب_سازی_callback);
        max_images = SDL_max(max_images, surfaces[i].شمار);
        لكل (صحيح j = 0; j < surfaces[i].شمار; ++j) {
            pool_اندازه += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    داده = SDL_calloc(1, حجم(*داده) + (حجم(CustomCursorImage) * max_images * قاب_شمار));
    إذا (!داده) {
        اذهب failed;
    }

    داده->قاب_durations_ms = SDL_calloc(قاب_شمار, حجم(Uint32));
    إذا (!داده->قاب_durations_ms) {
        اذهب failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_اندازه);
    إذا (!shm_pool) {
        اذهب failed;
    }

    cursor->داخلی = داده;
    داده->cursor_داده.custom.عرض = قابها[0].surface->w;
    داده->cursor_داده.custom.ارتفاع = قابها[0].surface->h;
    داده->cursor_داده.custom.hot_x = hot_x;
    داده->cursor_داده.custom.hot_y = hot_y;
    داده->cursor_داده.custom.images_در_هر_قاب = max_images;
    داده->رقم_قابها = قاب_شمار;

    لكل (صحيح i = 0; i < قاب_شمار; ++i) {
        داده->قاب_durations_ms[i] = قابها[i].duration;
        إذا (داده->مجموع_duration_ms < SDL_MAX_UINT32) {
            إذا (داده->قاب_durations_ms[i] > 0) {
                داده->مجموع_duration_ms += داده->قاب_durations_ms[i];
            } وإلا {
                داده->مجموع_duration_ms = SDL_MAX_UINT32;
            }
        }

        ثابت صحيح جابه_جایی_2 = i * max_images;
        لكل (صحيح j = 0; j < surfaces[i].شمار; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                إذا (!surface) {
                    اذهب failed;
                }
            }

            داده->cursor_داده.custom.images[جابه_جایی_2 + j].عرض = surface->w;
            داده->cursor_داده.custom.images[جابه_جایی_2 + j].ارتفاع = surface->h;

            فراغ *buf_داده;
            داده->cursor_داده.custom.images[جابه_جایی_2 + j].میانگیر_2 = Wayland_Alloc_میانگیر_From_Pool(shm_pool, surface->w, surface->h, &buf_داده);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_داده, surface->w * 4, true);

            إذا (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_پشته);
    Wayland_ReleaseSHMPool(shm_pool);

    أرجع cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    إذا (داده) {
        SDL_free(داده->قاب_durations_ms);
        لكل (صحيح i = 0; i < داده->cursor_داده.custom.images_در_هر_قاب * قاب_شمار; ++i) {
            إذا (داده->cursor_داده.custom.images[i].میانگیر_2) {
                wl_میانگیر_destroy(داده->cursor_داده.custom.images[i].میانگیر_2);
            }
        }
    }

    SDL_free(داده);

    إذا (surfaces) {
        لكل (صحيح i = 0; i < قاب_شمار; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_پشته);
    }

    SDL_free(cursor);

    أرجع عدم;
}

ساكن SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_قاب_Info قاب = {
        surface, 0
    };

    أرجع Wayland_CreateAnimatedCursor(&قاب, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, حجم(*cursor));

    إذا (cursor) {
        SDL_Cursor_داده *cdata = SDL_calloc(1, حجم(*cdata));
        إذا (!cdata) {
            SDL_free(cursor);
            أرجع عدم;
        }
        cursor->داخلی = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_داده.system.cursor_میانگیر_cache);
        cdata->cursor_داده.system.id = id;
        cdata->is_system_cursor = true;
    }

    أرجع cursor;
}

ساكن SDL_Cursor *Wayland_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع Wayland_CreateSystemCursor(id);
}

ساكن فراغ Wayland_Free_Cursor_داده(SDL_Cursor_داده *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_داده *video_داده = video_device->داخلی;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_داده->seat_list, link)
    {
        إذا (seat->اشاره_گر_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_قاب_Callback(&seat->اشاره_گر_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            إذا (!d->is_system_cursor && seat->اشاره_گر_2.cursor_state.surface) {
                wl_surface_attach(seat->اشاره_گر_2.cursor_state.surface, عدم, 0, 0);
            }

            seat->اشاره_گر_2.cursor_state.current_cursor = عدم;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_قاب_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                إذا (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->اشاره_گر_2.cursor_state.surface, عدم, 0, 0);
                }

                tool->cursor_state.current_cursor = عدم;
            }
        }
    }

    إذا (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *موقت;
        wl_list_for_each_امن(c, موقت, &d->cursor_داده.system.cursor_میانگیر_cache, گره) {
            SDL_free(c);
        }
    } وإلا {
        لكل (صحيح i = 0; i < d->رقم_قابها * d->cursor_داده.custom.images_در_هر_قاب; ++i) {
            إذا (d->cursor_داده.custom.images[i].میانگیر_2) {
                wl_میانگیر_destroy(d->cursor_داده.custom.images[i].میانگیر_2);
            }
        }
    }

    SDL_free(d->قاب_durations_ms);
}

ساكن فراغ Wayland_FreeCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        أرجع;
    }

    // Probably not a cursor we own
    إذا (!cursor->داخلی) {
        أرجع;
    }

    Wayland_Free_Cursor_داده(cursor->داخلی);

    SDL_free(cursor->داخلی);
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
    حالة SDL_SYSTEM_CURSOR_پیشرفت:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_پیشرفت;
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
    حالة SDL_SYSTEM_CURSOR_اشاره_گر:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_اشاره_گر;
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
    حالة SDL_SYSTEM_CURSOR_ردیف_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ردیف_RESIZE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_درون:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_درون;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ZOOM_بیرون:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_بیرون;
        اكسر;
    افتراضي:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    أرجع shape;
}

تعريفنوع بنية Wayland_اشاره_گر_Object
{
    اتحاد
    {
        بنية wl_اشاره_گر *wl_اشاره_گر;
        بنية zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_اشاره_گر;
} Wayland_اشاره_گر_Object;

ساكن فراغ Wayland_Cursor_State_مجموعه_Cursor(SDL_WaylandCursorState *state, ثابت Wayland_اشاره_گر_Object *obj, SDL_پنجره_داده *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_داده *viddata = SDL_GetVideoDevice()->داخلی;
    SDL_Cursor_داده *cursor_داده = cursor ? cursor->داخلی : عدم;
    صحيح dst_عرض = 0;
    صحيح dst_ارتفاع = 0;
    صحيح hot_x;
    صحيح hot_y;

    // Stop the frame callback for old animated cursors.
    إذا (cursor_داده != state->current_cursor) {
        Wayland_Cursor_State_Destroy_قاب_Callback(state);
    }

    إذا (cursor) {
        إذا (cursor_داده == state->current_cursor && state->current_قاب >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            إذا (cursor_داده->رقم_قابها > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            أرجع;
        }

        إذا (cursor_داده->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            إذا (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                إذا (state->surface) {
                    wl_surface_attach(state->surface, عدم, 0, 0);
                    wl_surface_commit(state->surface);

                    إذا (obj->is_اشاره_گر) {
                        wl_اشاره_گر_مجموعه_cursor(obj->wl_اشاره_گر, serial, عدم, 0, 0);
                    } وإلا {
                        zwp_tablet_tool_v2_مجموعه_cursor(obj->wl_tool, serial, عدم, 0, 0);
                    }

                    إذا (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = عدم;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = عدم;
                }

                ثابت تعداد wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_داده->cursor_داده.system.id);
                wp_cursor_shape_device_v1_مجموعه_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_داده;
                state->current_قاب = 0;

                أرجع;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_ضریب_2 : 1.0;
            إذا (!Wayland_GetSystemCursor(cursor_داده, state, &dst_عرض, &hot_x, &hot_y)) {
                أرجع;
            }

            dst_ارتفاع = dst_عرض;
        } وإلا {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            إذا (!focus || (focus->اشاره_گر_scale.x == 1.0 && focus->اشاره_گر_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_ضریب_2 : 1.0;
                dst_عرض = cursor_داده->cursor_داده.custom.عرض;
                dst_ارتفاع = cursor_داده->cursor_داده.custom.ارتفاع;
                hot_x = cursor_داده->cursor_داده.custom.hot_x;
                hot_y = cursor_داده->cursor_داده.custom.hot_y;
            } وإلا {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->اشاره_گر_scale.x, focus->اشاره_گر_scale.y);
                dst_عرض = SDL_max((صحيح)SDL_lround((مزدوج)cursor_داده->cursor_داده.custom.عرض / focus->اشاره_گر_scale.x), 1);
                dst_ارتفاع = SDL_max((صحيح)SDL_lround((مزدوج)cursor_داده->cursor_داده.custom.ارتفاع / focus->اشاره_گر_scale.y), 1);
                hot_x = (صحيح)SDL_lround((مزدوج)cursor_داده->cursor_داده.custom.hot_x / focus->اشاره_گر_scale.x);
                hot_y = (صحيح)SDL_lround((مزدوج)cursor_داده->cursor_داده.custom.hot_y / focus->اشاره_گر_scale.y);
            }

        }

        state->current_cursor = cursor_داده;

        إذا (!state->surface) {
            بنية wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        بنية wl_میانگیر *میانگیر_2 = Wayland_Cursor_State_Get_قاب(state, 0);
        wl_surface_attach(state->surface, میانگیر_2, 0, 0);
        state->current_قاب = 0;

        إذا (state->scale != 1.0) {
            إذا (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_مجموعه_منبع(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_مجموعه_destination(state->viewport, dst_عرض, dst_ارتفاع);
        } وإلا إذا (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = عدم;
        }

        إذا (obj->is_اشاره_گر) {
            wl_اشاره_گر_مجموعه_cursor(obj->wl_اشاره_گر, serial, state->surface, hot_x, hot_y);
        } وإلا {
            zwp_tablet_tool_v2_مجموعه_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        إذا (wl_surface_get_نسخه(state->surface) >= WL_SURFACE_DAMAGE_میانگیر_SINCE_نسخه) {
            wl_surface_damage_میانگیر(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        إذا (cursor_داده->رقم_قابها > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_مجموعه_قاب_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } وإلا {
        Wayland_Cursor_State_Destroy_قاب_Callback(state);
        state->current_cursor = عدم;

        إذا (state->surface) {
            wl_surface_attach(state->surface, عدم, 0, 0);
            wl_surface_commit(state->surface);
        }

        إذا (obj->is_اشاره_گر) {
            wl_اشاره_گر_مجموعه_cursor(obj->wl_اشاره_گر, serial, عدم, 0, 0);
        } وإلا {
            zwp_tablet_tool_v2_مجموعه_cursor(obj->wl_tool, serial, عدم, 0, 0);
        }
    }
}

ساكن فراغ Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_قاب_Callback(state);
    state->current_قاب = -1;
}

فراغ Wayland_Display_Update_اشاره_گر_Focused_Scale(SDL_پنجره_داده *updated_پنجره)
{
    SDL_Video_داده *viddata = updated_پنجره->wayland_داده;
    SDL_WaylandSeat *seat;
    ثابت مزدوج new_scale = SDL_min(updated_پنجره->اشاره_گر_scale.x, updated_پنجره->اشاره_گر_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        إذا (seat->اشاره_گر_2.focus == updated_پنجره) {
            SDL_WaylandCursorState *state = &seat->اشاره_گر_2.cursor_state;
            إذا (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_اشاره_گر_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            إذا (tool->focus == updated_پنجره) {
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
    SDL_Video_داده *d = vd->داخلی;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_اشاره_گر_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        إذا (seat->اشاره_گر_2.wl_اشاره_گر) {
            obj.wl_اشاره_گر = seat->اشاره_گر_2.wl_اشاره_گر;
            obj.is_اشاره_گر = true;
            إذا (mouse->focus && mouse->focus->داخلی == seat->اشاره_گر_2.focus) {
                Wayland_Cursor_State_مجموعه_Cursor(&seat->اشاره_گر_2.cursor_state, &obj, seat->اشاره_گر_2.focus, seat->اشاره_گر_2.enter_serial, cursor);
            } وإلا إذا (!seat->اشاره_گر_2.focus) {
                Wayland_CursorStateResetCursor(&seat->اشاره_گر_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_اشاره_گر = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            إذا (tool->focus && (!mouse->focus || mouse->focus->داخلی == tool->focus)) {
                Wayland_Cursor_State_مجموعه_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا إذا (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    أرجع true;
}

فراغ Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_پنجره_داده *پنجره, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_داده *d = vd->داخلی;

    إذا (seat->اشاره_گر_2.wl_اشاره_گر) {
        إذا (d->wp_اشاره_گر_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ثابت wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / پنجره->اشاره_گر_scale.x, 0, پنجره->current.logical_عرض));
            ثابت wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / پنجره->اشاره_گر_scale.y, 0, پنجره->current.logical_ارتفاع));
            wp_اشاره_گر_warp_v1_warp_اشاره_گر(d->wp_اشاره_گر_warp_v1, پنجره->surface, seat->اشاره_گر_2.wl_اشاره_گر, f_x, f_y, seat->اشاره_گر_2.enter_serial);
        } وإلا {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            إذا (seat->اشاره_گر_2.confined_اشاره_گر) {
                zwp_confined_اشاره_گر_v1_destroy(seat->اشاره_گر_2.confined_اشاره_گر);
                seat->اشاره_گر_2.confined_اشاره_گر = عدم;
                update_grabs = true;
            }
            إذا (seat->اشاره_گر_2.locked_اشاره_گر) {
                zwp_locked_اشاره_گر_v1_destroy(seat->اشاره_گر_2.locked_اشاره_گر);
                seat->اشاره_گر_2.locked_اشاره_گر = عدم;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            بنية zwp_locked_اشاره_گر_v1 *warp_قفل =
                zwp_اشاره_گر_constraints_v1_قفل_اشاره_گر(d->اشاره_گر_constraints, پنجره->surface,
                                                        seat->اشاره_گر_2.wl_اشاره_گر, عدم,
                                                        ZWP_اشاره_گر_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ثابت wl_fixed_t f_x = wl_fixed_from_double(x / پنجره->اشاره_گر_scale.x);
            ثابت wl_fixed_t f_y = wl_fixed_from_double(y / پنجره->اشاره_گر_scale.y);
            zwp_locked_اشاره_گر_v1_مجموعه_cursor_position_hint(warp_قفل, f_x, f_y);
            wl_surface_commit(پنجره->surface);

            zwp_locked_اشاره_گر_v1_destroy(warp_قفل);

            إذا (update_grabs) {
                Wayland_Seat_Update_اشاره_گر_Grab(seat);
            }
        }

        إذا (wl_اشاره_گر_get_نسخه(seat->اشاره_گر_2.wl_اشاره_گر) < WL_اشاره_گر_WARP_SINCE_نسخه) {
            SDL_SendMouseWarp(0, پنجره->sdlwindow, seat->اشاره_گر_2.sdl_id, x, y);
        }
    }
}

ساكن bool Wayland_WarpMouseRelative(SDL_پنجره *پنجره, عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_داده *d = vd->داخلی;
    SDL_پنجره_داده *wind = پنجره->داخلی;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشاره_گر_warp_v1 || d->اشاره_گر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            إذا (wind == seat->اشاره_گر_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } وإلا {
        أرجع SDL_مجموعه_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_WarpMouseGlobal(عائم x, عائم y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_داده *d = vd->داخلی;
    SDL_WaylandSeat *seat;

    إذا (d->wp_اشاره_گر_warp_v1 || d->اشاره_گر_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_پنجره_داده *wind = seat->اشاره_گر_2.focus ? seat->اشاره_گر_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            إذا (wind) {
                SDL_پنجره *پنجره = wind->sdlwindow;

                صحيح abs_x, abs_y;
                SDL_Relative_مقصد_Global_For_پنجره(پنجره, پنجره->x, پنجره->y, &abs_x, &abs_y);

                ثابت SDL_FPoint p = { x, y };
                ثابت SDL_FRect r = { abs_x, abs_y, پنجره->w, پنجره->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                إذا (SDL_نقطه_درون_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } وإلا {
        أرجع SDL_مجموعه_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    أرجع true;
}

ساكن bool Wayland_مجموعه_Relative_Mouse_نما(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_داده *داده = vd->داخلی;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    إذا (!داده->relative_اشاره_گر_manager) {
        أرجع SDL_مجموعه_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    إذا (!داده->اشاره_گر_constraints) {
        أرجع SDL_مجموعه_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_اشاره_گر_Grabs(داده, عدم);
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
    SDL_MouseButtonFlags نتیجه = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    إذا (mouse->focus) {
        SDL_Video_داده *video_داده = SDL_GetVideoDevice()->داخلی;
        SDL_WaylandSeat *seat;
        صحيح off_x, off_y;
        SDL_Relative_مقصد_Global_For_پنجره(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_داده->seat_list, link) {
            نتیجه |= seat->اشاره_گر_2.buttons_pressed;
        }
    } وإلا {
        *x = 0.f;
        *y = 0.f;
    }

    أرجع نتیجه;
}

#إذا 0  // TODO RECONNECT: See waylandvideo.c for more information!
ساكن فراغ Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_داده *vdata)
{
    SDL_Cursor_داده *cdata = cursor->داخلی;

    // Probably not a cursor we own
    إذا (cdata == عدم) {
        أرجع;
    }

    Wayland_Free_Cursor_داده(cdata);

    // We're not currently freeing this, so... yolo?
    إذا (cdata->shm_داده != عدم) {
        فراغ *old_داده_اشاره_گر = cdata->shm_داده;
        صحيح stride = cdata->w * 4;

        create_میانگیر_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_داده, old_داده_اشاره_گر, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_مجموعه_user_داده(cdata->surface, عدم);
}

فراغ Wayland_RecreateCursors(فراغ)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_داده *vdata = SDL_GetVideoDevice()->داخلی;

    إذا (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = عدم;
        vdata->رقم_cursor_themes = 0;
    }

    إذا (mouse == عدم) {
        أرجع;
    }

    لكل (cursor = mouse->cursors; cursor != عدم; cursor = cursor->بعدی) {
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
#پایان_اگر // 0

فراغ Wayland_InitMouse(SDL_Video_داده *داده)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->مجموعه_Relative_Mouse_نما = Wayland_مجموعه_Relative_Mouse_نما;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_اصابت_Test_نتیجه r = SDL_HITTEST_نرمال;
    طالما (r <= SDL_HITTEST_RESIZE_چپ) {
        بدل (r) {
        حالة SDL_HITTEST_نرمال:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_بالاترین:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            اكسر;
        حالة SDL_HITTEST_RESIZE_راست:
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
        حالة SDL_HITTEST_RESIZE_چپ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            اكسر;
        }
        r++;
    }

#اگر_تعریف_شده SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_داده *d = vd->داخلی;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    إذا (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#پایان_اگر

    SDL_مجموعه_Default_Cursor(Wayland_CreateDefaultCursor());
}

فراغ Wayland_FiniMouse(SDL_Video_داده *داده)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = عدم;
    }

    Wayland_FreeCursorThemes(داده);

#اگر_تعریف_شده SDL_USE_LIBDBUS
    Wayland_DBus_پایان_Cursor_Properties();
#پایان_اگر
}

فراغ Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->اشاره_گر_2.cursor_state);
}

فراغ Wayland_Seat_مجموعه_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_پنجره_داده *اشاره_گر_focus = seat->اشاره_گر_2.focus;
    ثابت Wayland_اشاره_گر_Object obj = {
        .wl_اشاره_گر = seat->اشاره_گر_2.wl_اشاره_گر,
        .is_اشاره_گر = true
    };

    Wayland_Cursor_State_مجموعه_Cursor(&seat->اشاره_گر_2.cursor_state, &obj, اشاره_گر_focus, seat->اشاره_گر_2.enter_serial, mouse->def_cursor);
}

فراغ Wayland_Seat_Update_اشاره_گر_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_پنجره_داده *اشاره_گر_focus = seat->اشاره_گر_2.focus;
    ثابت Wayland_اشاره_گر_Object obj = {
        .wl_اشاره_گر = seat->اشاره_گر_2.wl_اشاره_گر,
        .is_اشاره_گر = true
    };

    إذا (اشاره_گر_focus) {
        إذا (mouse->cursor_visible) {
            إذا (!seat->اشاره_گر_2.relative_اشاره_گر || !mouse->relative_نما_hide_cursor) {
                ثابت SDL_اصابت_Test_نتیجه rc = اشاره_گر_focus->اصابت_test_نتیجه;

                إذا (seat->اشاره_گر_2.relative_اشاره_گر || rc == SDL_HITTEST_نرمال || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_مجموعه_Cursor(&seat->اشاره_گر_2.cursor_state, &obj, اشاره_گر_focus, seat->اشاره_گر_2.enter_serial, mouse->cur_cursor);
                } وإلا {
                    Wayland_Cursor_State_مجموعه_Cursor(&seat->اشاره_گر_2.cursor_state, &obj, اشاره_گر_focus, seat->اشاره_گر_2.enter_serial, sys_cursors[rc]);
                }
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_مجموعه_Cursor(&seat->اشاره_گر_2.cursor_state, &obj, اشاره_گر_focus, seat->اشاره_گر_2.enter_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_مجموعه_Cursor(&seat->اشاره_گر_2.cursor_state, &obj, اشاره_گر_focus, seat->اشاره_گر_2.enter_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&seat->اشاره_گر_2.cursor_state);
    }
}

فراغ Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_پنجره_داده *tool_focus = tool->focus;
    ثابت Wayland_اشاره_گر_Object obj = {
        .wl_tool = tool->wltool,
        .is_اشاره_گر = false
    };

    إذا (tool_focus) {
        إذا (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ثابت bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_پنجره_MOUSE_RELATIVE_نما);

            إذا (!relative || !mouse->relative_نما_hide_cursor) {
                Wayland_Cursor_State_مجموعه_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } وإلا {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_مجموعه_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
            }
        } وإلا {
            Wayland_Cursor_State_مجموعه_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, عدم);
        }
    } وإلا {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND

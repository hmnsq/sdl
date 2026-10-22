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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ <errno.h>

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../SDL_video_c.h"

#అన్తర్భావ "../../core/unix/SDL_poll.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "../SDL_pixels_c.h"
#అన్తర్భావ "SDL_waylandevents_c.h"

#అన్తర్భావ "wayland-cursor.h"
#అన్తర్భావ "SDL_waylandmouse.h"
#అన్తర్భావ "SDL_waylandshmbuffer.h"

#అన్తర్భావ "cursor-shape-v1-client-protocol.h"
#అన్తర్భావ "pointer-constraints-unstable-v1-client-protocol.h"
#అన్తర్భావ "viewporter-client-protocol.h"
#అన్తర్భావ "pointer-warp-v1-client-protocol.h"
#అన్తర్భావ "tablet-v2-client-protocol.h"

#అన్తర్భావ "../../SDL_hints_c.h"

స్థిర SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ఎడమ + 1];

స్థిర bool Wayland_సమితి_Relative_Mouse_బహుళకం(bool enabled);

రకనిర్వచనం నిర్మాణం
{
    పూర్ణాంకం వెడల్పు;
    పూర్ణాంకం ఎత్తు;
    నిర్మాణం wl_బఫరు *బఫరు_2;
} CustomCursorImage;

రకనిర్వచనం నిర్మాణం
{
    // The base dimensions of the cursor.
    పూర్ణాంకం వెడల్పు;
    పూర్ణాంకం ఎత్తు;
    పూర్ణాంకం hot_x;
    పూర్ణాంకం hot_y;

    పూర్ణాంకం images_చొప్పున_చట్రం;
    CustomCursorImage images[];
} Wayland_CustomCursor;

రకనిర్వచనం నిర్మాణం
{
    పూర్ణాంకం కొలత;
    నిర్మాణం wl_list కణుపు;
    నిర్మాణం wl_బఫరు *buffers[];
} Wayland_CachedSystemCursor;

రకనిర్వచనం నిర్మాణం
{
    SDL_SystemCursor id;
    నిర్మాణం wl_list cursor_బఫరు_cache;
} Wayland_SystemCursor;

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    // Cursor animation data.
    Uint32 *చట్రం_durations_ms;
    Uint32 మొత్తం_duration_ms;
    పూర్ణాంకం అంకె_చట్రాలు;
    bool is_system_cursor;

    సంఘం
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_దత్తాంశం;
};

స్థిర పూర్ణాంకం dbus_cursor_కొలత;
స్థిర అక్షరం *dbus_cursor_theme;

స్థిర శూన్య Wayland_FreeCursorThemes(SDL_Video_దత్తాంశం *vdata)
{
    కొరకు (పూర్ణాంకం i = 0; i < vdata->అంకె_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->అంకె_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = ఖాళీ;
}

#నిర్వచితమైతే SDL_USE_LIBDBUS

#అన్తర్భావ "../../core/linux/SDL_dbus.h"

#నిర్వచించు CURSOR_కణుపు        "org.freedesktop.portal.Desktop"
#నిర్వచించు CURSOR_మార్గం        "/org/freedesktop/portal/desktop"
#నిర్వచించు CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#నిర్వచించు CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#నిర్వచించు CURSOR_SIGNAL_NAME "SettingChanged"
#నిర్వచించు CURSOR_కొలత_కీలకం    "cursor-size"
#నిర్వచించు CURSOR_THEME_కీలకం   "cursor-theme"

స్థిర DBus_సందేశం *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, స్థిరరాశి అక్షరం *కీలకం)
{
    స్థిర స్థిరరాశి అక్షరం *iface = "org.gnome.desktop.interface";

    DBus_సందేశం *జవాబు = ఖాళీ;
    DBus_సందేశం *సందేశం_2 = dbus->సందేశం_new_పద్ధతి_call(CURSOR_కణుపు,
                                                     CURSOR_మార్గం,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //పద్ధతి

    ఒకవేళ (సందేశం_2) {
        ఒకవేళ (dbus->సందేశం_append_వాదనలు(సందేశం_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &కీలకం, DBUS_TYPE_INVALID)) {
            జవాబు = dbus->connection_send_with_జవాబు_and_ఖండం(dbus->session_conn, సందేశం_2, DBUS_TIMEOUT_USE_DEFAULT, ఖాళీ);
        }
        dbus->సందేశం_unref(సందేశం_2);
    }

    తిరిగి జవాబు;
}

స్థిర bool Wayland_Parse_DBus_జవాబు(SDL_DBusContext *dbus, DBus_సందేశం *జవాబు, పూర్ణాంకం type, శూన్య *విలువ)
{
    DBus_సందేశం_Iter iter[3];

    dbus->సందేశం_iter_init(జవాబు, &iter[0]);
    ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        తిరిగి false;
    }

    dbus->సందేశం_iter_recurse(&iter[0], &iter[1]);
    ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        తిరిగి false;
    }

    dbus->సందేశం_iter_recurse(&iter[1], &iter[2]);
    ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&iter[2]) != type) {
        తిరిగి false;
    }

    dbus->సందేశం_iter_get_basic(&iter[2], విలువ);

    తిరిగి true;
}

స్థిర DBus_Handler_ఫలితం Wayland_DBus_Cursor_సందేశం_Filter(DBusConnection *conn, DBus_సందేశం *సందేశం_2, శూన్య *దత్తాంశం)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_దత్తాంశం *vdata = (SDL_Video_దత్తాంశం *)దత్తాంశం;

    ఒకవేళ (dbus->సందేశం_is_signal(సందేశం_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_సందేశం_Iter signal_iter, variant_iter;
        స్థిరరాశి అక్షరం *namespace, *కీలకం;

        dbus->సందేశం_iter_init(సందేశం_2, &signal_iter);
        // Check if the parameters are what we expect
        ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            వెళ్ళు not_our_signal;
        }
        dbus->సందేశం_iter_get_basic(&signal_iter, &namespace);
        ఒకవేళ (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            వెళ్ళు not_our_signal;
        }
        ఒకవేళ (!dbus->సందేశం_iter_తదుపరి(&signal_iter)) {
            వెళ్ళు not_our_signal;
        }
        ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            వెళ్ళు not_our_signal;
        }
        dbus->సందేశం_iter_get_basic(&signal_iter, &కీలకం);
        ఒకవేళ (SDL_strcmp(CURSOR_కొలత_కీలకం, కీలకం) == 0) {
            పూర్ణాంకం new_cursor_కొలత;

            ఒకవేళ (!dbus->సందేశం_iter_తదుపరి(&signal_iter)) {
                వెళ్ళు not_our_signal;
            }
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                వెళ్ళు not_our_signal;
            }
            dbus->సందేశం_iter_recurse(&signal_iter, &variant_iter);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                వెళ్ళు not_our_signal;
            }
            dbus->సందేశం_iter_get_basic(&variant_iter, &new_cursor_కొలత);

            ఒకవేళ (dbus_cursor_కొలత != new_cursor_కొలత) {
                dbus_cursor_కొలత = new_cursor_కొలత;
                SDL_RedrawCursor(); // Force cursor update
            }
        } లేకపోతే ఒకవేళ (SDL_strcmp(CURSOR_THEME_కీలకం, కీలకం) == 0) {
            స్థిరరాశి అక్షరం *new_cursor_theme = ఖాళీ;

            ఒకవేళ (!dbus->సందేశం_iter_తదుపరి(&signal_iter)) {
                వెళ్ళు not_our_signal;
            }
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                వెళ్ళు not_our_signal;
            }
            dbus->సందేశం_iter_recurse(&signal_iter, &variant_iter);
            ఒకవేళ (dbus->సందేశం_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                వెళ్ళు not_our_signal;
            }
            dbus->సందేశం_iter_get_basic(&variant_iter, &new_cursor_theme);

            ఒకవేళ (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                ఒకవేళ (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } లేకపోతే {
                    dbus_cursor_theme = ఖాళీ;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } లేకపోతే {
            వెళ్ళు not_our_signal;
        }

        తిరిగి DBUS_HANDLER_ఫలితం_HANDLED;
    }

not_our_signal:
    తిరిగి DBUS_HANDLER_ఫలితం_NOT_YET_HANDLED;
}

స్థిర శూన్య Wayland_DBusInitCursorProperties(SDL_Video_దత్తాంశం *vdata)
{
    DBus_సందేశం *జవాబు;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool కూడు_filter = false;

    ఒకవేళ (!dbus) {
        తిరిగి;
    }

    ఒకవేళ ((జవాబు = Wayland_ReadDBusProperty(dbus, CURSOR_కొలత_కీలకం))) {
        ఒకవేళ (Wayland_Parse_DBus_జవాబు(dbus, జవాబు, DBUS_TYPE_INT32, &dbus_cursor_కొలత)) {
            కూడు_filter = true;
        }
        dbus->సందేశం_unref(జవాబు);
    }

    ఒకవేళ ((జవాబు = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_కీలకం))) {
        స్థిరరాశి అక్షరం *తాత్కాలిక = ఖాళీ;
        ఒకవేళ (Wayland_Parse_DBus_జవాబు(dbus, జవాబు, DBUS_TYPE_STRING, &తాత్కాలిక)) {
            కూడు_filter = true;

            ఒకవేళ (తాత్కాలిక) {
                dbus_cursor_theme = SDL_strdup(తాత్కాలిక);
            }
        }
        dbus->సందేశం_unref(జవాబు);
    }

    // Only add the filter if at least one of the settings we want is present.
    ఒకవేళ (కూడు_filter) {
        dbus->bus_కూడు_సరిపోలిక(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            ఖాళీ);
        dbus->connection_కూడు_filter(dbus->session_conn, &Wayland_DBus_Cursor_సందేశం_Filter, vdata, ఖాళీ);
        dbus->connection_flush(dbus->session_conn);
    }
}

స్థిర శూన్య Wayland_DBus_ముగింపు_Cursor_Properties(శూన్య)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = ఖాళీ;
}

#అయితే_ముగింపు

స్థిర నిర్మాణం wl_బఫరు *Wayland_Cursor_State_Get_చట్రం(SDL_WaylandCursorState *state, పూర్ణాంకం చట్రం_సూచీ_2)
{
    SDL_Cursor_దత్తాంశం *దత్తాంశం = state->current_cursor;

    ఒకవేళ (దత్తాంశం) {
        ఒకవేళ (!దత్తాంశం->is_system_cursor) {
            స్థిరరాశి పూర్ణాంకం స్థానభ్రంశం_2 = దత్తాంశం->cursor_దత్తాంశం.custom.images_చొప్పున_చట్రం * చట్రం_సూచీ_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = ఖాళీ;
            స్థిరరాశి పూర్ణాంకం లక్ష్యం_area = SDL_lround(దత్తాంశం->cursor_దత్తాంశం.custom.వెడల్పు * దత్తాంశం->cursor_దత్తాంశం.custom.ఎత్తు * state->scale);
            పూర్ణాంకం closest_area = 0;
            కొరకు (పూర్ణాంకం i = 0; i < దత్తాంశం->cursor_దత్తాంశం.custom.images_చొప్పున_చట్రం && closest_area < లక్ష్యం_area && దత్తాంశం->cursor_దత్తాంశం.custom.images[స్థానభ్రంశం_2 + i].బఫరు_2; ++i) {
                closest = &దత్తాంశం->cursor_దత్తాంశం.custom.images[స్థానభ్రంశం_2 + i];
                closest_area = closest->వెడల్పు * closest->ఎత్తు;
            }

            తిరిగి closest ? closest->బఫరు_2 : ఖాళీ;
        } లేకపోతే {
            తిరిగి ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[చట్రం_సూచీ_2];
        }
    }

    తిరిగి ఖాళీ;
}

స్థిర శూన్య cursor_చట్రం_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *cb, uint32_t సమయం);
స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener cursor_చట్రం_listener = {
    cursor_చట్రం_పూర్తి
};

స్థిర శూన్య cursor_చట్రం_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *cb, uint32_t సమయం)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)దత్తాంశం;
    ఒకవేళ (!state->current_cursor) {
        తిరిగి;
    }

    Uint32 *చట్రాలు = state->current_cursor->చట్రం_durations_ms;
    SDL_Cursor_దత్తాంశం *c = state->current_cursor;

    స్థిరరాశి Uint64 now = SDL_GetTicks();
    స్థిరరాశి Uint32 elapsed = (now - state->చివరి_చట్రం_callback_సమయం_ms) % c->మొత్తం_duration_ms;
    Uint32 advance = 0;
    పూర్ణాంకం తదుపరి = state->current_చట్రం;

    state->current_చట్రం_సమయం_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    కొరకు (Uint32 t = చట్రాలు[తదుపరి]; t <= state->current_చట్రం_సమయం_ms; t += చట్రాలు[తదుపరి]) {
        తదుపరి = (తదుపరి + 1) % c->అంకె_చట్రాలు;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        ఒకవేళ (!చట్రాలు[తదుపరి]) {
            ఆపు;
        }
    }

    wl_callback_destroy(cb);
    state->చట్రం_callback = ఖాళీ;

    // Don't queue another callback if this frame time is infinite.
    ఒకవేళ (చట్రాలు[తదుపరి]) {
        state->చట్రం_callback = wl_surface_చట్రం(state->surface);
        wl_callback_కూడు_listener(state->చట్రం_callback, &cursor_చట్రం_listener, దత్తాంశం);
    }

    state->current_చట్రం_సమయం_ms -= advance;
    state->చివరి_చట్రం_callback_సమయం_ms = now;
    state->current_చట్రం = తదుపరి;

    నిర్మాణం wl_బఫరు *బఫరు_2 = Wayland_Cursor_State_Get_చట్రం(state, తదుపరి);
    wl_surface_attach(state->surface, బఫరు_2, 0, 0);

    ఒకవేళ (wl_surface_get_సంస్కరణ(state->surface) >= WL_SURFACE_DAMAGE_బఫరు_SINCE_సంస్కరణ) {
        wl_surface_damage_బఫరు(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } లేకపోతే {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

శూన్య Wayland_Cursor_State_సమితి_చట్రం_Callback(SDL_WaylandCursorState *state, శూన్య *userdata)
{
    SDL_Video_దత్తాంశం *viddata = SDL_GetVideoDevice()->అంతర్గత;
    Wayland_తాళం_Event_Thread(viddata->event_thread_context);

    state->చట్రం_callback = wl_surface_చట్రం(state->surface);
    wl_callback_కూడు_listener(state->చట్రం_callback, &cursor_చట్రం_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

శూన్య Wayland_Cursor_State_Destroy_చట్రం_Callback(SDL_WaylandCursorState *state)
{
    SDL_Video_దత్తాంశం *viddata = SDL_GetVideoDevice()->అంతర్గత;
    Wayland_తాళం_Event_Thread(viddata->event_thread_context);

    ఒకవేళ (state->చట్రం_callback) {
        wl_callback_destroy(state->చట్రం_callback);
        state->చట్రం_callback = ఖాళీ;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

స్థిర శూన్య Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->చివరి_చట్రం_callback_సమయం_ms = SDL_GetTicks();
    state->current_చట్రం_సమయం_ms = 0;
    state->current_చట్రం = 0;
}

స్థిర శూన్య Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool తాళం_2)
{
    ఒకవేళ (తాళం_2) {
        SDL_Video_దత్తాంశం *viddata = SDL_GetVideoDevice()->అంతర్గత;
        Wayland_తాళం_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } లేకపోతే {
        Wayland_CursorStateResetAnimationState(state);
    }
}

శూన్య Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_Cursor_State_Destroy_చట్రం_Callback(state);
    ఒకవేళ (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    ఒకవేళ (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    ఒకవేళ (state->surface) {
        wl_surface_attach(state->surface, ఖాళీ, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

స్థిర Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_దత్తాంశం *cdata, నిర్మాణం wl_cursor *cursor, పూర్ణాంకం కొలత)
{
    Wayland_CachedSystemCursor *cache = ఖాళీ;

    // Is this cursor already cached at the target scale?
    ఒకవేళ (!WAYLAND_wl_list_ఖాళీలు(&cdata->cursor_దత్తాంశం.system.cursor_బఫరు_cache)) {
        Wayland_CachedSystemCursor *c = ఖాళీ;
        wl_list_for_each (c, &cdata->cursor_దత్తాంశం.system.cursor_బఫరు_cache, కణుపు) {
            ఒకవేళ (c->కొలత == కొలత) {
                cache = c;
                ఆపు;
            }
        }
    }

    ఒకవేళ (!cache) {
        cache = SDL_calloc(1, పరిమాణం(Wayland_CachedSystemCursor) + (పరిమాణం(నిర్మాణం wl_బఫరు *) * cdata->అంకె_చట్రాలు));

        cache->కొలత = కొలత;
        కొరకు (పూర్ణాంకం i = 0; i < cdata->అంకె_చట్రాలు; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_బఫరు(cursor->images[i]);
        }

        WAYLAND_wl_list_చొప్పించు(&cdata->cursor_దత్తాంశం.system.cursor_బఫరు_cache, &cache->కణుపు);
    }

    తిరిగి cache;
}

స్థిర bool Wayland_GetSystemCursor(SDL_Cursor_దత్తాంశం *cdata, SDL_WaylandCursorState *state, పూర్ణాంకం *dst_కొలత, పూర్ణాంకం *hot_x, పూర్ణాంకం *hot_y)
{
    SDL_Video_దత్తాంశం *vdata = SDL_GetVideoDevice()->అంతర్గత;
    నిర్మాణం wl_cursor_theme *theme = ఖాళీ;
    స్థిరరాశి అక్షరం *css_name = "default";
    స్థిరరాశి అక్షరం *fallback_name = ఖాళీ;
    ద్విగుణ scale_గుణకం_2 = state->scale;
    పూర్ణాంకం theme_కొలత = dbus_cursor_కొలత;

    // Fallback envvar if the DBus properties don't exist
    ఒకవేళ (theme_కొలత <= 0) {
        స్థిరరాశి అక్షరం *xcursor_కొలత = SDL_getenv("XCURSOR_SIZE");
        ఒకవేళ (xcursor_కొలత) {
            theme_కొలత = SDL_atoi(xcursor_కొలత);
        }
    }
    ఒకవేళ (theme_కొలత <= 0) {
        theme_కొలత = 24;
    }

    // First, find the appropriate theme based on the current scale...
    స్థిరరాశి పూర్ణాంకం scaled_కొలత = (పూర్ణాంకం)SDL_lround(theme_కొలత * scale_గుణకం_2);
    కొరకు (పూర్ణాంకం i = 0; i < vdata->అంకె_cursor_themes; ++i) {
        ఒకవేళ (vdata->cursor_themes[i].కొలత == scaled_కొలత) {
            theme = vdata->cursor_themes[i].theme;
            ఆపు;
        }
    }
    ఒకవేళ (!theme) {
        స్థిరరాశి అక్షరం *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                పరిమాణం(SDL_WaylandCursorTheme) * (vdata->అంకె_cursor_themes + 1));
        ఒకవేళ (!new_cursor_themes) {
            తిరిగి false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        ఒకవేళ (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_ఎక్కించు(xcursor_theme, scaled_కొలత, vdata->shm);
        vdata->cursor_themes[vdata->అంకె_cursor_themes].కొలత = scaled_కొలత;
        vdata->cursor_themes[vdata->అంకె_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_దత్తాంశం.system.id, &fallback_name);
    నిర్మాణం wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    ఒకవేళ (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    ఒకవేళ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    ఒకవేళ (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    ఒకవేళ (!cursor) {
        తిరిగి false;
    }

    // ... Set the cursor data, finally.
    cdata->అంకె_చట్రాలు = cursor->image_లెక్క_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_కొలత);
    state->system_cursor_handle = c;

    ఒకవేళ (cursor->image_లెక్క_2 > 1 && !cdata->చట్రం_durations_ms) {
        cdata->మొత్తం_duration_ms = 0;
        cdata->చట్రం_durations_ms = SDL_calloc(cursor->image_లెక్క_2, పరిమాణం(Uint32));

        కొరకు (పూర్ణాంకం i = 0; i < cursor->image_లెక్క_2; ++i) {
            cdata->చట్రం_durations_ms[i] = cursor->images[i]->delay;
            cdata->మొత్తం_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_కొలత = SDL_lround(cursor->images[0]->వెడల్పు / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    తిరిగి true;
}

స్థిర పూర్ణాంకం surface_క్రమీకరించు_callback(స్థిరరాశి శూన్య *a, స్థిరరాశి శూన్య *b)
{
    స్థిరరాశి SDL_Surface *s1 = *(స్థిరరాశి SDL_Surface **)a;
    స్థిరరాశి SDL_Surface *s2 = *(స్థిరరాశి SDL_Surface **)b;

    తిరిగి (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

స్థిర SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_Cursor_చట్రం_Info *చట్రాలు, పూర్ణాంకం చట్రం_లెక్క, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (!cursor) {
        తిరిగి ఖాళీ;
    }

    SDL_Cursor_దత్తాంశం *దత్తాంశం = ఖాళీ;
    Wayland_SHMPool *shm_pool = ఖాళీ;
    పూర్ణాంకం pool_కొలత = 0;
    పూర్ణాంకం max_images = 0;
    bool is_దొంతర = false;
    నిర్మాణం SurfaceArray
    {
        SDL_Surface **surfaces;
        పూర్ణాంకం లెక్క;
    } *surfaces = SDL_small_alloc(నిర్మాణం SurfaceArray, చట్రం_లెక్క, &is_దొంతర);
    ఒకవేళ (!surfaces) {
        వెళ్ళు failed;
    }
    SDL_memset(surfaces, 0, పరిమాణం(నిర్మాణం SurfaceArray) * చట్రం_లెక్క);

    // Calculate the total allocation size.
    కొరకు (పూర్ణాంకం i = 0; i < చట్రం_లెక్క; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(చట్రాలు[i].surface, &surfaces[i].లెక్క);
        ఒకవేళ (!surfaces[i].surfaces) {
            వెళ్ళు failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].లెక్క, పరిమాణం(SDL_Surface *), surface_క్రమీకరించు_callback);
        max_images = SDL_max(max_images, surfaces[i].లెక్క);
        కొరకు (పూర్ణాంకం j = 0; j < surfaces[i].లెక్క; ++j) {
            pool_కొలత += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    దత్తాంశం = SDL_calloc(1, పరిమాణం(*దత్తాంశం) + (పరిమాణం(CustomCursorImage) * max_images * చట్రం_లెక్క));
    ఒకవేళ (!దత్తాంశం) {
        వెళ్ళు failed;
    }

    దత్తాంశం->చట్రం_durations_ms = SDL_calloc(చట్రం_లెక్క, పరిమాణం(Uint32));
    ఒకవేళ (!దత్తాంశం->చట్రం_durations_ms) {
        వెళ్ళు failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_కొలత);
    ఒకవేళ (!shm_pool) {
        వెళ్ళు failed;
    }

    cursor->అంతర్గత = దత్తాంశం;
    దత్తాంశం->cursor_దత్తాంశం.custom.వెడల్పు = చట్రాలు[0].surface->w;
    దత్తాంశం->cursor_దత్తాంశం.custom.ఎత్తు = చట్రాలు[0].surface->h;
    దత్తాంశం->cursor_దత్తాంశం.custom.hot_x = hot_x;
    దత్తాంశం->cursor_దత్తాంశం.custom.hot_y = hot_y;
    దత్తాంశం->cursor_దత్తాంశం.custom.images_చొప్పున_చట్రం = max_images;
    దత్తాంశం->అంకె_చట్రాలు = చట్రం_లెక్క;

    కొరకు (పూర్ణాంకం i = 0; i < చట్రం_లెక్క; ++i) {
        దత్తాంశం->చట్రం_durations_ms[i] = చట్రాలు[i].duration;
        ఒకవేళ (దత్తాంశం->మొత్తం_duration_ms < SDL_MAX_UINT32) {
            ఒకవేళ (దత్తాంశం->చట్రం_durations_ms[i] > 0) {
                దత్తాంశం->మొత్తం_duration_ms += దత్తాంశం->చట్రం_durations_ms[i];
            } లేకపోతే {
                దత్తాంశం->మొత్తం_duration_ms = SDL_MAX_UINT32;
            }
        }

        స్థిరరాశి పూర్ణాంకం స్థానభ్రంశం_2 = i * max_images;
        కొరకు (పూర్ణాంకం j = 0; j < surfaces[i].లెక్క; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            ఒకవేళ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                ఒకవేళ (!surface) {
                    వెళ్ళు failed;
                }
            }

            దత్తాంశం->cursor_దత్తాంశం.custom.images[స్థానభ్రంశం_2 + j].వెడల్పు = surface->w;
            దత్తాంశం->cursor_దత్తాంశం.custom.images[స్థానభ్రంశం_2 + j].ఎత్తు = surface->h;

            శూన్య *buf_దత్తాంశం;
            దత్తాంశం->cursor_దత్తాంశం.custom.images[స్థానభ్రంశం_2 + j].బఫరు_2 = Wayland_Alloc_బఫరు_From_Pool(shm_pool, surface->w, surface->h, &buf_దత్తాంశం);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_దత్తాంశం, surface->w * 4, true);

            ఒకవేళ (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_దొంతర);
    Wayland_ReleaseSHMPool(shm_pool);

    తిరిగి cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    ఒకవేళ (దత్తాంశం) {
        SDL_free(దత్తాంశం->చట్రం_durations_ms);
        కొరకు (పూర్ణాంకం i = 0; i < దత్తాంశం->cursor_దత్తాంశం.custom.images_చొప్పున_చట్రం * చట్రం_లెక్క; ++i) {
            ఒకవేళ (దత్తాంశం->cursor_దత్తాంశం.custom.images[i].బఫరు_2) {
                wl_బఫరు_destroy(దత్తాంశం->cursor_దత్తాంశం.custom.images[i].బఫరు_2);
            }
        }
    }

    SDL_free(దత్తాంశం);

    ఒకవేళ (surfaces) {
        కొరకు (పూర్ణాంకం i = 0; i < చట్రం_లెక్క; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_దొంతర);
    }

    SDL_free(cursor);

    తిరిగి ఖాళీ;
}

స్థిర SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Cursor_చట్రం_Info చట్రం = {
        surface, 0
    };

    తిరిగి Wayland_CreateAnimatedCursor(&చట్రం, 1, hot_x, hot_y);
}

స్థిర SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, పరిమాణం(*cursor));

    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *cdata = SDL_calloc(1, పరిమాణం(*cdata));
        ఒకవేళ (!cdata) {
            SDL_free(cursor);
            తిరిగి ఖాళీ;
        }
        cursor->అంతర్గత = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_దత్తాంశం.system.cursor_బఫరు_cache);
        cdata->cursor_దత్తాంశం.system.id = id;
        cdata->is_system_cursor = true;
    }

    తిరిగి cursor;
}

స్థిర SDL_Cursor *Wayland_CreateDefaultCursor(శూన్య)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    తిరిగి Wayland_CreateSystemCursor(id);
}

స్థిర శూన్య Wayland_Free_Cursor_దత్తాంశం(SDL_Cursor_దత్తాంశం *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *video_దత్తాంశం = video_device->అంతర్గత;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_దత్తాంశం->seat_list, link)
    {
        ఒకవేళ (seat->సూచిక_2.cursor_state.current_cursor == d) {
            Wayland_Cursor_State_Destroy_చట్రం_Callback(&seat->సూచిక_2.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            ఒకవేళ (!d->is_system_cursor && seat->సూచిక_2.cursor_state.surface) {
                wl_surface_attach(seat->సూచిక_2.cursor_state.surface, ఖాళీ, 0, 0);
            }

            seat->సూచిక_2.cursor_state.current_cursor = ఖాళీ;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ఒకవేళ (tool->cursor_state.current_cursor == d) {
                Wayland_Cursor_State_Destroy_చట్రం_Callback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                ఒకవేళ (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->సూచిక_2.cursor_state.surface, ఖాళీ, 0, 0);
                }

                tool->cursor_state.current_cursor = ఖాళీ;
            }
        }
    }

    ఒకవేళ (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *తాత్కాలిక;
        wl_list_for_each_సురక్షిత(c, తాత్కాలిక, &d->cursor_దత్తాంశం.system.cursor_బఫరు_cache, కణుపు) {
            SDL_free(c);
        }
    } లేకపోతే {
        కొరకు (పూర్ణాంకం i = 0; i < d->అంకె_చట్రాలు * d->cursor_దత్తాంశం.custom.images_చొప్పున_చట్రం; ++i) {
            ఒకవేళ (d->cursor_దత్తాంశం.custom.images[i].బఫరు_2) {
                wl_బఫరు_destroy(d->cursor_దత్తాంశం.custom.images[i].బఫరు_2);
            }
        }
    }

    SDL_free(d->చట్రం_durations_ms);
}

స్థిర శూన్య Wayland_FreeCursor(SDL_Cursor *cursor)
{
    ఒకవేళ (!cursor) {
        తిరిగి;
    }

    // Probably not a cursor we own
    ఒకవేళ (!cursor->అంతర్గత) {
        తిరిగి;
    }

    Wayland_Free_Cursor_దత్తాంశం(cursor->అంతర్గత);

    SDL_free(cursor->అంతర్గత);
    SDL_free(cursor);
}

స్థిర గణన wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    ఎంపిక (id) {
    స్థితి SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_పాఠ్యం:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_పాఠ్యం;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_పురోగతి:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_పురోగతి;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_సూచిక:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_సూచిక;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_VERTICAL_పాఠ్యం:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_పాఠ్యం;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_నిలువు_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_నిలువు_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_అడ్డువరుస_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_అడ్డువరుస_RESIZE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_ZOOM_లోపల:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_లోపల;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_ZOOM_బహిర్గతం:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_బహిర్గతం;
        ఆపు;
    అప్రమేయ:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    తిరిగి shape;
}

రకనిర్వచనం నిర్మాణం Wayland_సూచిక_Object
{
    సంఘం
    {
        నిర్మాణం wl_సూచిక *wl_సూచిక;
        నిర్మాణం zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_సూచిక;
} Wayland_సూచిక_Object;

స్థిర శూన్య Wayland_Cursor_State_సమితి_Cursor(SDL_WaylandCursorState *state, స్థిరరాశి Wayland_సూచిక_Object *obj, SDL_కిటికీ_దత్తాంశం *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_దత్తాంశం *viddata = SDL_GetVideoDevice()->అంతర్గత;
    SDL_Cursor_దత్తాంశం *cursor_దత్తాంశం = cursor ? cursor->అంతర్గత : ఖాళీ;
    పూర్ణాంకం dst_వెడల్పు = 0;
    పూర్ణాంకం dst_ఎత్తు = 0;
    పూర్ణాంకం hot_x;
    పూర్ణాంకం hot_y;

    // Stop the frame callback for old animated cursors.
    ఒకవేళ (cursor_దత్తాంశం != state->current_cursor) {
        Wayland_Cursor_State_Destroy_చట్రం_Callback(state);
    }

    ఒకవేళ (cursor) {
        ఒకవేళ (cursor_దత్తాంశం == state->current_cursor && state->current_చట్రం >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            ఒకవేళ (cursor_దత్తాంశం->అంకె_చట్రాలు > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            తిరిగి;
        }

        ఒకవేళ (cursor_దత్తాంశం->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            ఒకవేళ (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                ఒకవేళ (state->surface) {
                    wl_surface_attach(state->surface, ఖాళీ, 0, 0);
                    wl_surface_commit(state->surface);

                    ఒకవేళ (obj->is_సూచిక) {
                        wl_సూచిక_సమితి_cursor(obj->wl_సూచిక, serial, ఖాళీ, 0, 0);
                    } లేకపోతే {
                        zwp_tablet_tool_v2_సమితి_cursor(obj->wl_tool, serial, ఖాళీ, 0, 0);
                    }

                    ఒకవేళ (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = ఖాళీ;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = ఖాళీ;
                }

                స్థిరరాశి గణన wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_దత్తాంశం->cursor_దత్తాంశం.system.id);
                wp_cursor_shape_device_v1_సమితి_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_దత్తాంశం;
                state->current_చట్రం = 0;

                తిరిగి;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_గుణకం_2 : 1.0;
            ఒకవేళ (!Wayland_GetSystemCursor(cursor_దత్తాంశం, state, &dst_వెడల్పు, &hot_x, &hot_y)) {
                తిరిగి;
            }

            dst_ఎత్తు = dst_వెడల్పు;
        } లేకపోతే {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            ఒకవేళ (!focus || (focus->సూచిక_scale.x == 1.0 && focus->సూచిక_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_గుణకం_2 : 1.0;
                dst_వెడల్పు = cursor_దత్తాంశం->cursor_దత్తాంశం.custom.వెడల్పు;
                dst_ఎత్తు = cursor_దత్తాంశం->cursor_దత్తాంశం.custom.ఎత్తు;
                hot_x = cursor_దత్తాంశం->cursor_దత్తాంశం.custom.hot_x;
                hot_y = cursor_దత్తాంశం->cursor_దత్తాంశం.custom.hot_y;
            } లేకపోతే {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->సూచిక_scale.x, focus->సూచిక_scale.y);
                dst_వెడల్పు = SDL_max((పూర్ణాంకం)SDL_lround((ద్విగుణ)cursor_దత్తాంశం->cursor_దత్తాంశం.custom.వెడల్పు / focus->సూచిక_scale.x), 1);
                dst_ఎత్తు = SDL_max((పూర్ణాంకం)SDL_lround((ద్విగుణ)cursor_దత్తాంశం->cursor_దత్తాంశం.custom.ఎత్తు / focus->సూచిక_scale.y), 1);
                hot_x = (పూర్ణాంకం)SDL_lround((ద్విగుణ)cursor_దత్తాంశం->cursor_దత్తాంశం.custom.hot_x / focus->సూచిక_scale.x);
                hot_y = (పూర్ణాంకం)SDL_lround((ద్విగుణ)cursor_దత్తాంశం->cursor_దత్తాంశం.custom.hot_y / focus->సూచిక_scale.y);
            }

        }

        state->current_cursor = cursor_దత్తాంశం;

        ఒకవేళ (!state->surface) {
            నిర్మాణం wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        నిర్మాణం wl_బఫరు *బఫరు_2 = Wayland_Cursor_State_Get_చట్రం(state, 0);
        wl_surface_attach(state->surface, బఫరు_2, 0, 0);
        state->current_చట్రం = 0;

        ఒకవేళ (state->scale != 1.0) {
            ఒకవేళ (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_సమితి_ఆధారం(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_సమితి_destination(state->viewport, dst_వెడల్పు, dst_ఎత్తు);
        } లేకపోతే ఒకవేళ (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = ఖాళీ;
        }

        ఒకవేళ (obj->is_సూచిక) {
            wl_సూచిక_సమితి_cursor(obj->wl_సూచిక, serial, state->surface, hot_x, hot_y);
        } లేకపోతే {
            zwp_tablet_tool_v2_సమితి_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        ఒకవేళ (wl_surface_get_సంస్కరణ(state->surface) >= WL_SURFACE_DAMAGE_బఫరు_SINCE_సంస్కరణ) {
            wl_surface_damage_బఫరు(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } లేకపోతే {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        ఒకవేళ (cursor_దత్తాంశం->అంకె_చట్రాలు > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_సమితి_చట్రం_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } లేకపోతే {
        Wayland_Cursor_State_Destroy_చట్రం_Callback(state);
        state->current_cursor = ఖాళీ;

        ఒకవేళ (state->surface) {
            wl_surface_attach(state->surface, ఖాళీ, 0, 0);
            wl_surface_commit(state->surface);
        }

        ఒకవేళ (obj->is_సూచిక) {
            wl_సూచిక_సమితి_cursor(obj->wl_సూచిక, serial, ఖాళీ, 0, 0);
        } లేకపోతే {
            zwp_tablet_tool_v2_సమితి_cursor(obj->wl_tool, serial, ఖాళీ, 0, 0);
        }
    }
}

స్థిర శూన్య Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_Cursor_State_Destroy_చట్రం_Callback(state);
    state->current_చట్రం = -1;
}

శూన్య Wayland_Display_Update_సూచిక_Focused_Scale(SDL_కిటికీ_దత్తాంశం *updated_కిటికీ)
{
    SDL_Video_దత్తాంశం *viddata = updated_కిటికీ->wayland_దత్తాంశం;
    SDL_WaylandSeat *seat;
    స్థిరరాశి ద్విగుణ new_scale = SDL_min(updated_కిటికీ->సూచిక_scale.x, updated_కిటికీ->సూచిక_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        ఒకవేళ (seat->సూచిక_2.focus == updated_కిటికీ) {
            SDL_WaylandCursorState *state = &seat->సూచిక_2.cursor_state;
            ఒకవేళ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_Seat_Update_సూచిక_Cursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            ఒకవేళ (tool->focus == updated_కిటికీ) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                ఒకవేళ (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                    Wayland_CursorStateResetCursor(&tool->cursor_state);
                    Wayland_TabletToolUpdateCursor(tool);
                }
            }
        }
    }
}

స్థిర bool Wayland_ShowCursor(SDL_Cursor *cursor)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *d = vd->అంతర్గత;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_సూచిక_Object obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        ఒకవేళ (seat->సూచిక_2.wl_సూచిక) {
            obj.wl_సూచిక = seat->సూచిక_2.wl_సూచిక;
            obj.is_సూచిక = true;
            ఒకవేళ (mouse->focus && mouse->focus->అంతర్గత == seat->సూచిక_2.focus) {
                Wayland_Cursor_State_సమితి_Cursor(&seat->సూచిక_2.cursor_state, &obj, seat->సూచిక_2.focus, seat->సూచిక_2.enter_serial, cursor);
            } లేకపోతే ఒకవేళ (!seat->సూచిక_2.focus) {
                Wayland_CursorStateResetCursor(&seat->సూచిక_2.cursor_state);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each(tool, &seat->tablet.tool_list, link) {
            obj.wl_tool = tool->wltool;
            obj.is_సూచిక = false;

            /* The current cursor is explicitly set on tablet tools, as there may be no pointer device, or
             * the pointer may not have focus, which would instead cause the default cursor to be set.
             */
            ఒకవేళ (tool->focus && (!mouse->focus || mouse->focus->అంతర్గత == tool->focus)) {
                Wayland_Cursor_State_సమితి_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } లేకపోతే ఒకవేళ (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    తిరిగి true;
}

శూన్య Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_కిటికీ_దత్తాంశం *కిటికీ, దశాంశం x, దశాంశం y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *d = vd->అంతర్గత;

    ఒకవేళ (seat->సూచిక_2.wl_సూచిక) {
        ఒకవేళ (d->wp_సూచిక_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            స్థిరరాశి wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / కిటికీ->సూచిక_scale.x, 0, కిటికీ->current.logical_వెడల్పు));
            స్థిరరాశి wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / కిటికీ->సూచిక_scale.y, 0, కిటికీ->current.logical_ఎత్తు));
            wp_సూచిక_warp_v1_warp_సూచిక(d->wp_సూచిక_warp_v1, కిటికీ->surface, seat->సూచిక_2.wl_సూచిక, f_x, f_y, seat->సూచిక_2.enter_serial);
        } లేకపోతే {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            ఒకవేళ (seat->సూచిక_2.confined_సూచిక) {
                zwp_confined_సూచిక_v1_destroy(seat->సూచిక_2.confined_సూచిక);
                seat->సూచిక_2.confined_సూచిక = ఖాళీ;
                update_grabs = true;
            }
            ఒకవేళ (seat->సూచిక_2.locked_సూచిక) {
                zwp_locked_సూచిక_v1_destroy(seat->సూచిక_2.locked_సూచిక);
                seat->సూచిక_2.locked_సూచిక = ఖాళీ;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            నిర్మాణం zwp_locked_సూచిక_v1 *warp_తాళం =
                zwp_సూచిక_constraints_v1_తాళం_సూచిక(d->సూచిక_constraints, కిటికీ->surface,
                                                        seat->సూచిక_2.wl_సూచిక, ఖాళీ,
                                                        ZWP_సూచిక_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            స్థిరరాశి wl_fixed_t f_x = wl_fixed_from_double(x / కిటికీ->సూచిక_scale.x);
            స్థిరరాశి wl_fixed_t f_y = wl_fixed_from_double(y / కిటికీ->సూచిక_scale.y);
            zwp_locked_సూచిక_v1_సమితి_cursor_position_hint(warp_తాళం, f_x, f_y);
            wl_surface_commit(కిటికీ->surface);

            zwp_locked_సూచిక_v1_destroy(warp_తాళం);

            ఒకవేళ (update_grabs) {
                Wayland_Seat_Update_సూచిక_Grab(seat);
            }
        }

        ఒకవేళ (wl_సూచిక_get_సంస్కరణ(seat->సూచిక_2.wl_సూచిక) < WL_సూచిక_WARP_SINCE_సంస్కరణ) {
            SDL_SendMouseWarp(0, కిటికీ->sdlwindow, seat->సూచిక_2.sdl_id, x, y);
        }
    }
}

స్థిర bool Wayland_WarpMouseRelative(SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *d = vd->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    SDL_WaylandSeat *seat;

    ఒకవేళ (d->wp_సూచిక_warp_v1 || d->సూచిక_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            ఒకవేళ (wind == seat->సూచిక_2.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    తిరిగి true;
}

స్థిర bool Wayland_WarpMouseGlobal(దశాంశం x, దశాంశం y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *d = vd->అంతర్గత;
    SDL_WaylandSeat *seat;

    ఒకవేళ (d->wp_సూచిక_warp_v1 || d->సూచిక_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_కిటికీ_దత్తాంశం *wind = seat->సూచిక_2.focus ? seat->సూచిక_2.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            ఒకవేళ (wind) {
                SDL_కిటికీ *కిటికీ = wind->sdlwindow;

                పూర్ణాంకం abs_x, abs_y;
                SDL_Relative_గమ్యం_Global_For_కిటికీ(కిటికీ, కిటికీ->x, కిటికీ->y, &abs_x, &abs_y);

                స్థిరరాశి SDL_FPoint p = { x, y };
                స్థిరరాశి SDL_FRect r = { abs_x, abs_y, కిటికీ->w, కిటికీ->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                ఒకవేళ (SDL_బిందువు_లోపల_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } లేకపోతే {
        తిరిగి SDL_సమితి_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    తిరిగి true;
}

స్థిర bool Wayland_సమితి_Relative_Mouse_బహుళకం(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *దత్తాంశం = vd->అంతర్గత;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    ఒకవేళ (!దత్తాంశం->relative_సూచిక_manager) {
        తిరిగి SDL_సమితి_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    ఒకవేళ (!దత్తాంశం->సూచిక_constraints) {
        తిరిగి SDL_సమితి_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_Display_Update_సూచిక_Grabs(దత్తాంశం, ఖాళీ);
    తిరిగి true;
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
స్థిర SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(దశాంశం *x, దశాంశం *y)
{
    స్థిరరాశి SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags ఫలితం = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    ఒకవేళ (mouse->focus) {
        SDL_Video_దత్తాంశం *video_దత్తాంశం = SDL_GetVideoDevice()->అంతర్గత;
        SDL_WaylandSeat *seat;
        పూర్ణాంకం off_x, off_y;
        SDL_Relative_గమ్యం_Global_For_కిటికీ(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_దత్తాంశం->seat_list, link) {
            ఫలితం |= seat->సూచిక_2.buttons_pressed;
        }
    } లేకపోతే {
        *x = 0.f;
        *y = 0.f;
    }

    తిరిగి ఫలితం;
}

#ఒకవేళ 0  // TODO RECONNECT: See waylandvideo.c for more information!
స్థిర శూన్య Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_దత్తాంశం *vdata)
{
    SDL_Cursor_దత్తాంశం *cdata = cursor->అంతర్గత;

    // Probably not a cursor we own
    ఒకవేళ (cdata == ఖాళీ) {
        తిరిగి;
    }

    Wayland_Free_Cursor_దత్తాంశం(cdata);

    // We're not currently freeing this, so... yolo?
    ఒకవేళ (cdata->shm_దత్తాంశం != ఖాళీ) {
        శూన్య *old_దత్తాంశం_సూచిక = cdata->shm_దత్తాంశం;
        పూర్ణాంకం stride = cdata->w * 4;

        create_బఫరు_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_దత్తాంశం, old_దత్తాంశం_సూచిక, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_సమితి_user_దత్తాంశం(cdata->surface, ఖాళీ);
}

శూన్య Wayland_RecreateCursors(శూన్య)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_దత్తాంశం *vdata = SDL_GetVideoDevice()->అంతర్గత;

    ఒకవేళ (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = ఖాళీ;
        vdata->అంకె_cursor_themes = 0;
    }

    ఒకవేళ (mouse == ఖాళీ) {
        తిరిగి;
    }

    కొరకు (cursor = mouse->cursors; cursor != ఖాళీ; cursor = cursor->తదుపరి) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    ఒకవేళ (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    ఒకవేళ (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        ఒకవేళ (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#అయితే_ముగింపు // 0

శూన్య Wayland_InitMouse(SDL_Video_దత్తాంశం *దత్తాంశం)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->సమితి_Relative_Mouse_బహుళకం = Wayland_సమితి_Relative_Mouse_బహుళకం;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_తగిలింది_Test_ఫలితం r = SDL_HITTEST_సాధారణ;
    అయితే (r <= SDL_HITTEST_RESIZE_ఎడమ) {
        ఎంపిక (r) {
        స్థితి SDL_HITTEST_సాధారణ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ఆపు;
        స్థితి SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_శిఖరం:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_కుడి:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            ఆపు;
        స్థితి SDL_HITTEST_RESIZE_ఎడమ:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            ఆపు;
        }
        r++;
    }

#నిర్వచితమైతే SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_దత్తాంశం *d = vd->అంతర్గత;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    ఒకవేళ (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#అయితే_ముగింపు

    SDL_సమితి_Default_Cursor(Wayland_CreateDefaultCursor());
}

శూన్య Wayland_FiniMouse(SDL_Video_దత్తాంశం *దత్తాంశం)
{
    కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = ఖాళీ;
    }

    Wayland_FreeCursorThemes(దత్తాంశం);

#నిర్వచితమైతే SDL_USE_LIBDBUS
    Wayland_DBus_ముగింపు_Cursor_Properties();
#అయితే_ముగింపు
}

శూన్య Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->సూచిక_2.cursor_state);
}

శూన్య Wayland_Seat_సమితి_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_కిటికీ_దత్తాంశం *సూచిక_focus = seat->సూచిక_2.focus;
    స్థిరరాశి Wayland_సూచిక_Object obj = {
        .wl_సూచిక = seat->సూచిక_2.wl_సూచిక,
        .is_సూచిక = true
    };

    Wayland_Cursor_State_సమితి_Cursor(&seat->సూచిక_2.cursor_state, &obj, సూచిక_focus, seat->సూచిక_2.enter_serial, mouse->def_cursor);
}

శూన్య Wayland_Seat_Update_సూచిక_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_కిటికీ_దత్తాంశం *సూచిక_focus = seat->సూచిక_2.focus;
    స్థిరరాశి Wayland_సూచిక_Object obj = {
        .wl_సూచిక = seat->సూచిక_2.wl_సూచిక,
        .is_సూచిక = true
    };

    ఒకవేళ (సూచిక_focus) {
        ఒకవేళ (mouse->cursor_visible) {
            ఒకవేళ (!seat->సూచిక_2.relative_సూచిక || !mouse->relative_బహుళకం_hide_cursor) {
                స్థిరరాశి SDL_తగిలింది_Test_ఫలితం rc = సూచిక_focus->తగిలింది_test_ఫలితం;

                ఒకవేళ (seat->సూచిక_2.relative_సూచిక || rc == SDL_HITTEST_సాధారణ || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_సమితి_Cursor(&seat->సూచిక_2.cursor_state, &obj, సూచిక_focus, seat->సూచిక_2.enter_serial, mouse->cur_cursor);
                } లేకపోతే {
                    Wayland_Cursor_State_సమితి_Cursor(&seat->సూచిక_2.cursor_state, &obj, సూచిక_focus, seat->సూచిక_2.enter_serial, sys_cursors[rc]);
                }
            } లేకపోతే {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_సమితి_Cursor(&seat->సూచిక_2.cursor_state, &obj, సూచిక_focus, seat->సూచిక_2.enter_serial, ఖాళీ);
            }
        } లేకపోతే {
            Wayland_Cursor_State_సమితి_Cursor(&seat->సూచిక_2.cursor_state, &obj, సూచిక_focus, seat->సూచిక_2.enter_serial, ఖాళీ);
        }
    } లేకపోతే {
        Wayland_CursorStateResetCursor(&seat->సూచిక_2.cursor_state);
    }
}

శూన్య Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_కిటికీ_దత్తాంశం *tool_focus = tool->focus;
    స్థిరరాశి Wayland_సూచిక_Object obj = {
        .wl_tool = tool->wltool,
        .is_సూచిక = false
    };

    ఒకవేళ (tool_focus) {
        ఒకవేళ (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            స్థిరరాశి bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_కిటికీ_MOUSE_RELATIVE_బహుళకం);

            ఒకవేళ (!relative || !mouse->relative_బహుళకం_hide_cursor) {
                Wayland_Cursor_State_సమితి_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } లేకపోతే {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_సమితి_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ఖాళీ);
            }
        } లేకపోతే {
            Wayland_Cursor_State_సమితి_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, ఖాళీ);
        }
    } లేకపోతే {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND

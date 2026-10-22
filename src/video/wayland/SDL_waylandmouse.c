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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

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

स्थिर SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_वामः + 1];

स्थिर bool Wayland_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled);

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क विस्तारः;
    पूर्णाङ्क height;
    संरचना wl_बफर *बफर_2;
} CustomCursorImage;

प्रकारनिर्देश संरचना
{
    // The base dimensions of the cursor.
    पूर्णाङ्क विस्तारः;
    पूर्णाङ्क height;
    पूर्णाङ्क hot_x;
    पूर्णाङ्क hot_y;

    पूर्णाङ्क images_प्रत्येकम्_frame;
    CustomCursorImage images[];
} Wayland_CustomCursor;

प्रकारनिर्देश संरचना
{
    पूर्णाङ्क आकार;
    संरचना wl_list ग्रन्थिः;
    संरचना wl_बफर *buffers[];
} Wayland_CachedSystemCursor;

प्रकारनिर्देश संरचना
{
    SDL_SystemCursor id;
    संरचना wl_list cursor_बफर_cache;
} Wayland_SystemCursor;

संरचना SDL_Cursor_दत्त
{
    // Cursor animation data.
    Uint32 *frame_durations_ms;
    Uint32 योग_duration_ms;
    पूर्णाङ्क अङ्कः_चौकटाः;
    bool is_system_cursor;

    सङ्घ
    {
        Wayland_CustomCursor custom;
        Wayland_SystemCursor system;
    } cursor_दत्त;
};

स्थिर पूर्णाङ्क dbus_cursor_आकार;
स्थिर वर्ण *dbus_cursor_theme;

स्थिर शून्य Wayland_FreeCursorThemes(SDL_Video_दत्त *vdata)
{
    प्रति (पूर्णाङ्क i = 0; i < vdata->अङ्कः_cursor_themes; i += 1) {
        WAYLAND_wl_cursor_theme_destroy(vdata->cursor_themes[i].theme);
    }
    vdata->अङ्कः_cursor_themes = 0;
    SDL_free(vdata->cursor_themes);
    vdata->cursor_themes = रिक्त;
}

#यदि_परिभाषितम् SDL_USE_LIBDBUS

#अन्तर्भाव "../../core/linux/SDL_dbus.h"

#परिभाषय CURSOR_ग्रन्थिः        "org.freedesktop.portal.Desktop"
#परिभाषय CURSOR_मार्गः        "/org/freedesktop/portal/desktop"
#परिभाषय CURSOR_INTERFACE   "org.freedesktop.portal.Settings"
#परिभाषय CURSOR_NAMESPACE   "org.gnome.desktop.interface"
#परिभाषय CURSOR_SIGNAL_NAME "SettingChanged"
#परिभाषय CURSOR_आकार_कुञ्चिका    "cursor-size"
#परिभाषय CURSOR_THEME_कुञ्चिका   "cursor-theme"

स्थिर DBus_सन्देशः *Wayland_ReadDBusProperty(SDL_DBusContext *dbus, ध्रुव वर्ण *कुञ्चिका)
{
    स्थिर ध्रुव वर्ण *iface = "org.gnome.desktop.interface";

    DBus_सन्देशः *प्रत्युत्तरम् = रिक्त;
    DBus_सन्देशः *सन्देशः_2 = dbus->सन्देशः_new_विधानम्_call(CURSOR_ग्रन्थिः,
                                                     CURSOR_मार्गः,
                                                     CURSOR_INTERFACE,
                                                     "Read"); //विधानम्

    यदि (सन्देशः_2) {
        यदि (dbus->सन्देशः_append_तर्काः(सन्देशः_2, DBUS_TYPE_STRING, &iface, DBUS_TYPE_STRING, &कुञ्चिका, DBUS_TYPE_INVALID)) {
            प्रत्युत्तरम् = dbus->connection_send_with_प्रत्युत्तरम्_and_खण्डम्(dbus->session_conn, सन्देशः_2, DBUS_TIMEOUT_USE_DEFAULT, रिक्त);
        }
        dbus->सन्देशः_unref(सन्देशः_2);
    }

    प्रत्यागम प्रत्युत्तरम्;
}

स्थिर bool Wayland_Parse_DBus_प्रत्युत्तरम्(SDL_DBusContext *dbus, DBus_सन्देशः *प्रत्युत्तरम्, पूर्णाङ्क type, शून्य *मानम्)
{
    DBus_सन्देशः_Iter iter[3];

    dbus->सन्देशः_iter_init(प्रत्युत्तरम्, &iter[0]);
    यदि (dbus->सन्देशः_iter_get_arg_type(&iter[0]) != DBUS_TYPE_VARIANT) {
        प्रत्यागम false;
    }

    dbus->सन्देशः_iter_recurse(&iter[0], &iter[1]);
    यदि (dbus->सन्देशः_iter_get_arg_type(&iter[1]) != DBUS_TYPE_VARIANT) {
        प्रत्यागम false;
    }

    dbus->सन्देशः_iter_recurse(&iter[1], &iter[2]);
    यदि (dbus->सन्देशः_iter_get_arg_type(&iter[2]) != type) {
        प्रत्यागम false;
    }

    dbus->सन्देशः_iter_get_basic(&iter[2], मानम्);

    प्रत्यागम true;
}

स्थिर DBus_Handler_परिणाम Wayland_DBus_Cursor_सन्देशः_Filter(DBusConnection *conn, DBus_सन्देशः *सन्देशः_2, शून्य *दत्त)
{
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    SDL_Video_दत्त *vdata = (SDL_Video_दत्त *)दत्त;

    यदि (dbus->सन्देशः_is_signal(सन्देशः_2, CURSOR_INTERFACE, CURSOR_SIGNAL_NAME)) {
        DBus_सन्देशः_Iter signal_iter, variant_iter;
        ध्रुव वर्ण *namespace, *कुञ्चिका;

        dbus->सन्देशः_iter_init(सन्देशः_2, &signal_iter);
        // Check if the parameters are what we expect
        यदि (dbus->सन्देशः_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            गच्छ not_our_signal;
        }
        dbus->सन्देशः_iter_get_basic(&signal_iter, &namespace);
        यदि (SDL_strcmp(CURSOR_NAMESPACE, namespace) != 0) {
            गच्छ not_our_signal;
        }
        यदि (!dbus->सन्देशः_iter_अग्र(&signal_iter)) {
            गच्छ not_our_signal;
        }
        यदि (dbus->सन्देशः_iter_get_arg_type(&signal_iter) != DBUS_TYPE_STRING) {
            गच्छ not_our_signal;
        }
        dbus->सन्देशः_iter_get_basic(&signal_iter, &कुञ्चिका);
        यदि (SDL_strcmp(CURSOR_आकार_कुञ्चिका, कुञ्चिका) == 0) {
            पूर्णाङ्क new_cursor_आकार;

            यदि (!dbus->सन्देशः_iter_अग्र(&signal_iter)) {
                गच्छ not_our_signal;
            }
            यदि (dbus->सन्देशः_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                गच्छ not_our_signal;
            }
            dbus->सन्देशः_iter_recurse(&signal_iter, &variant_iter);
            यदि (dbus->सन्देशः_iter_get_arg_type(&variant_iter) != DBUS_TYPE_INT32) {
                गच्छ not_our_signal;
            }
            dbus->सन्देशः_iter_get_basic(&variant_iter, &new_cursor_आकार);

            यदि (dbus_cursor_आकार != new_cursor_आकार) {
                dbus_cursor_आकार = new_cursor_आकार;
                SDL_RedrawCursor(); // Force cursor update
            }
        } अन्यथा यदि (SDL_strcmp(CURSOR_THEME_कुञ्चिका, कुञ्चिका) == 0) {
            ध्रुव वर्ण *new_cursor_theme = रिक्त;

            यदि (!dbus->सन्देशः_iter_अग्र(&signal_iter)) {
                गच्छ not_our_signal;
            }
            यदि (dbus->सन्देशः_iter_get_arg_type(&signal_iter) != DBUS_TYPE_VARIANT) {
                गच्छ not_our_signal;
            }
            dbus->सन्देशः_iter_recurse(&signal_iter, &variant_iter);
            यदि (dbus->सन्देशः_iter_get_arg_type(&variant_iter) != DBUS_TYPE_STRING) {
                गच्छ not_our_signal;
            }
            dbus->सन्देशः_iter_get_basic(&variant_iter, &new_cursor_theme);

            यदि (!dbus_cursor_theme || !new_cursor_theme || SDL_strcmp(dbus_cursor_theme, new_cursor_theme) != 0) {
                SDL_free(dbus_cursor_theme);
                यदि (new_cursor_theme) {
                    dbus_cursor_theme = SDL_strdup(new_cursor_theme);
                } अन्यथा {
                    dbus_cursor_theme = रिक्त;
                }

                // Purge the current cached themes and force a cursor refresh.
                Wayland_FreeCursorThemes(vdata);
                SDL_RedrawCursor();
            }
        } अन्यथा {
            गच्छ not_our_signal;
        }

        प्रत्यागम DBUS_HANDLER_परिणाम_HANDLED;
    }

not_our_signal:
    प्रत्यागम DBUS_HANDLER_परिणाम_NOT_YET_HANDLED;
}

स्थिर शून्य Wayland_DBusInitCursorProperties(SDL_Video_दत्त *vdata)
{
    DBus_सन्देशः *प्रत्युत्तरम्;
    SDL_DBusContext *dbus = SDL_DBus_GetContext();
    bool सङ्कलय_filter = false;

    यदि (!dbus) {
        प्रत्यागम;
    }

    यदि ((प्रत्युत्तरम् = Wayland_ReadDBusProperty(dbus, CURSOR_आकार_कुञ्चिका))) {
        यदि (Wayland_Parse_DBus_प्रत्युत्तरम्(dbus, प्रत्युत्तरम्, DBUS_TYPE_INT32, &dbus_cursor_आकार)) {
            सङ्कलय_filter = true;
        }
        dbus->सन्देशः_unref(प्रत्युत्तरम्);
    }

    यदि ((प्रत्युत्तरम् = Wayland_ReadDBusProperty(dbus, CURSOR_THEME_कुञ्चिका))) {
        ध्रुव वर्ण *अस्थायी = रिक्त;
        यदि (Wayland_Parse_DBus_प्रत्युत्तरम्(dbus, प्रत्युत्तरम्, DBUS_TYPE_STRING, &अस्थायी)) {
            सङ्कलय_filter = true;

            यदि (अस्थायी) {
                dbus_cursor_theme = SDL_strdup(अस्थायी);
            }
        }
        dbus->सन्देशः_unref(प्रत्युत्तरम्);
    }

    // Only add the filter if at least one of the settings we want is present.
    यदि (सङ्कलय_filter) {
        dbus->bus_सङ्कलय_मेलनम्(dbus->session_conn,
                            "type='signal', interface='" CURSOR_INTERFACE "',"
                            "member='" CURSOR_SIGNAL_NAME "', arg0='" CURSOR_NAMESPACE "'",
                            रिक्त);
        dbus->connection_सङ्कलय_filter(dbus->session_conn, &Wayland_DBus_Cursor_सन्देशः_Filter, vdata, रिक्त);
        dbus->connection_flush(dbus->session_conn);
    }
}

स्थिर शून्य Wayland_DBusFinishCursorProperties(शून्य)
{
    SDL_free(dbus_cursor_theme);
    dbus_cursor_theme = रिक्त;
}

#यदि_अन्तः

स्थिर संरचना wl_बफर *Wayland_CursorStateGetFrame(SDL_WaylandCursorState *state, पूर्णाङ्क frame_सूचकांक_2)
{
    SDL_Cursor_दत्त *दत्त = state->current_cursor;

    यदि (दत्त) {
        यदि (!दत्त->is_system_cursor) {
            ध्रुव पूर्णाङ्क विस्थापनम्_2 = दत्त->cursor_दत्त.custom.images_प्रत्येकम्_frame * frame_सूचकांक_2;

            /* Find the closest image. Images that are larger than the
             * desired size are preferred over images that are smaller.
             */
            CustomCursorImage *closest = रिक्त;
            ध्रुव पूर्णाङ्क target_area = SDL_lround(दत्त->cursor_दत्त.custom.विस्तारः * दत्त->cursor_दत्त.custom.height * state->scale);
            पूर्णाङ्क closest_area = 0;
            प्रति (पूर्णाङ्क i = 0; i < दत्त->cursor_दत्त.custom.images_प्रत्येकम्_frame && closest_area < target_area && दत्त->cursor_दत्त.custom.images[विस्थापनम्_2 + i].बफर_2; ++i) {
                closest = &दत्त->cursor_दत्त.custom.images[विस्थापनम्_2 + i];
                closest_area = closest->विस्तारः * closest->height;
            }

            प्रत्यागम closest ? closest->बफर_2 : रिक्त;
        } अन्यथा {
            प्रत्यागम ((Wayland_CachedSystemCursor *)(state->system_cursor_handle))->buffers[frame_सूचकांक_2];
        }
    }

    प्रत्यागम रिक्त;
}

स्थिर शून्य cursor_frame_समाप्तम्(शून्य *दत्त, संरचना wl_callback *cb, uint32_t time);
स्थिर ध्रुव संरचना wl_callback_listener cursor_frame_listener = {
    cursor_frame_समाप्तम्
};

स्थिर शून्य cursor_frame_समाप्तम्(शून्य *दत्त, संरचना wl_callback *cb, uint32_t time)
{
    SDL_WaylandCursorState *state = (SDL_WaylandCursorState *)दत्त;
    यदि (!state->current_cursor) {
        प्रत्यागम;
    }

    Uint32 *चौकटाः = state->current_cursor->frame_durations_ms;
    SDL_Cursor_दत्त *c = state->current_cursor;

    ध्रुव Uint64 now = SDL_GetTicks();
    ध्रुव Uint32 elapsed = (now - state->चरमः_frame_callback_time_ms) % c->योग_duration_ms;
    Uint32 advance = 0;
    पूर्णाङ्क अग्र = state->current_frame;

    state->current_frame_time_ms += elapsed;

    // Calculate the next frame based on the elapsed duration.
    प्रति (Uint32 t = चौकटाः[अग्र]; t <= state->current_frame_time_ms; t += चौकटाः[अग्र]) {
        अग्र = (अग्र + 1) % c->अङ्कः_चौकटाः;
        advance = t;

        // Make sure we don't end up in an infinite loop if a cursor has frame durations of 0.
        यदि (!चौकटाः[अग्र]) {
            भङ्ग;
        }
    }

    wl_callback_destroy(cb);
    state->frame_callback = रिक्त;

    // Don't queue another callback if this frame time is infinite.
    यदि (चौकटाः[अग्र]) {
        state->frame_callback = wl_surface_frame(state->surface);
        wl_callback_सङ्कलय_listener(state->frame_callback, &cursor_frame_listener, दत्त);
    }

    state->current_frame_time_ms -= advance;
    state->चरमः_frame_callback_time_ms = now;
    state->current_frame = अग्र;

    संरचना wl_बफर *बफर_2 = Wayland_CursorStateGetFrame(state, अग्र);
    wl_surface_attach(state->surface, बफर_2, 0, 0);

    यदि (wl_surface_get_संस्करणम्(state->surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_संस्करणम्) {
        wl_surface_damage_बफर(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } अन्यथा {
        wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }
    wl_surface_commit(state->surface);
}

शून्य Wayland_Cursor_State_समुच्चयः_Frame_Callback(SDL_WaylandCursorState *state, शून्य *userdata)
{
    SDL_Video_दत्त *viddata = SDL_GetVideoDevice()->आन्तरिकम्;
    Wayland_तालकम्_Event_Thread(viddata->event_thread_context);

    state->frame_callback = wl_surface_frame(state->surface);
    wl_callback_सङ्कलय_listener(state->frame_callback, &cursor_frame_listener, userdata);

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

शून्य Wayland_CursorStateDestroyFrameCallback(SDL_WaylandCursorState *state)
{
    SDL_Video_दत्त *viddata = SDL_GetVideoDevice()->आन्तरिकम्;
    Wayland_तालकम्_Event_Thread(viddata->event_thread_context);

    यदि (state->frame_callback) {
        wl_callback_destroy(state->frame_callback);
        state->frame_callback = रिक्त;
    }

    Wayland_UnlockEventThread(viddata->event_thread_context);
}

स्थिर शून्य Wayland_CursorStateResetAnimationState(SDL_WaylandCursorState *state)
{
    state->चरमः_frame_callback_time_ms = SDL_GetTicks();
    state->current_frame_time_ms = 0;
    state->current_frame = 0;
}

स्थिर शून्य Wayland_CursorStateResetAnimation(SDL_WaylandCursorState *state, bool तालकम्_2)
{
    यदि (तालकम्_2) {
        SDL_Video_दत्त *viddata = SDL_GetVideoDevice()->आन्तरिकम्;
        Wayland_तालकम्_Event_Thread(viddata->event_thread_context);
        Wayland_CursorStateResetAnimationState(state);
        Wayland_UnlockEventThread(viddata->event_thread_context);
    } अन्यथा {
        Wayland_CursorStateResetAnimationState(state);
    }
}

शून्य Wayland_CursorStateRelease(SDL_WaylandCursorState *state)
{
    Wayland_CursorStateDestroyFrameCallback(state);
    यदि (state->cursor_shape) {
        wp_cursor_shape_device_v1_destroy(state->cursor_shape);
    }
    यदि (state->viewport) {
        wp_viewport_destroy(state->viewport);
    }
    यदि (state->surface) {
        wl_surface_attach(state->surface, रिक्त, 0, 0);
        wl_surface_commit(state->surface);
        wl_surface_destroy(state->surface);
    }

    SDL_zerop(state);
}

स्थिर Wayland_CachedSystemCursor *Wayland_CacheSystemCursor(SDL_Cursor_दत्त *cdata, संरचना wl_cursor *cursor, पूर्णाङ्क आकार)
{
    Wayland_CachedSystemCursor *cache = रिक्त;

    // Is this cursor already cached at the target scale?
    यदि (!WAYLAND_wl_list_रिक्तानि(&cdata->cursor_दत्त.system.cursor_बफर_cache)) {
        Wayland_CachedSystemCursor *c = रिक्त;
        wl_list_for_each (c, &cdata->cursor_दत्त.system.cursor_बफर_cache, ग्रन्थिः) {
            यदि (c->आकार == आकार) {
                cache = c;
                भङ्ग;
            }
        }
    }

    यदि (!cache) {
        cache = SDL_calloc(1, परिमाण(Wayland_CachedSystemCursor) + (परिमाण(संरचना wl_बफर *) * cdata->अङ्कः_चौकटाः));

        cache->आकार = आकार;
        प्रति (पूर्णाङ्क i = 0; i < cdata->अङ्कः_चौकटाः; ++i) {
            cache->buffers[i] = WAYLAND_wl_cursor_image_get_बफर(cursor->images[i]);
        }

        WAYLAND_wl_list_निवेशय(&cdata->cursor_दत्त.system.cursor_बफर_cache, &cache->ग्रन्थिः);
    }

    प्रत्यागम cache;
}

स्थिर bool Wayland_GetSystemCursor(SDL_Cursor_दत्त *cdata, SDL_WaylandCursorState *state, पूर्णाङ्क *dst_आकार, पूर्णाङ्क *hot_x, पूर्णाङ्क *hot_y)
{
    SDL_Video_दत्त *vdata = SDL_GetVideoDevice()->आन्तरिकम्;
    संरचना wl_cursor_theme *theme = रिक्त;
    ध्रुव वर्ण *css_name = "default";
    ध्रुव वर्ण *fallback_name = रिक्त;
    द्विगुण scale_गुणकः_2 = state->scale;
    पूर्णाङ्क theme_आकार = dbus_cursor_आकार;

    // Fallback envvar if the DBus properties don't exist
    यदि (theme_आकार <= 0) {
        ध्रुव वर्ण *xcursor_आकार = SDL_getenv("XCURSOR_SIZE");
        यदि (xcursor_आकार) {
            theme_आकार = SDL_atoi(xcursor_आकार);
        }
    }
    यदि (theme_आकार <= 0) {
        theme_आकार = 24;
    }

    // First, find the appropriate theme based on the current scale...
    ध्रुव पूर्णाङ्क scaled_आकार = (पूर्णाङ्क)SDL_lround(theme_आकार * scale_गुणकः_2);
    प्रति (पूर्णाङ्क i = 0; i < vdata->अङ्कः_cursor_themes; ++i) {
        यदि (vdata->cursor_themes[i].आकार == scaled_आकार) {
            theme = vdata->cursor_themes[i].theme;
            भङ्ग;
        }
    }
    यदि (!theme) {
        ध्रुव वर्ण *xcursor_theme = dbus_cursor_theme;

        SDL_WaylandCursorTheme *new_cursor_themes = SDL_realloc(vdata->cursor_themes,
                                                                परिमाण(SDL_WaylandCursorTheme) * (vdata->अङ्कः_cursor_themes + 1));
        यदि (!new_cursor_themes) {
            प्रत्यागम false;
        }
        vdata->cursor_themes = new_cursor_themes;

        // Fallback envvar if the DBus properties don't exist
        यदि (!xcursor_theme) {
            xcursor_theme = SDL_getenv("XCURSOR_THEME");
        }

        theme = WAYLAND_wl_cursor_theme_आरोपय(xcursor_theme, scaled_आकार, vdata->shm);
        vdata->cursor_themes[vdata->अङ्कः_cursor_themes].आकार = scaled_आकार;
        vdata->cursor_themes[vdata->अङ्कः_cursor_themes++].theme = theme;
    }

    css_name = SDL_GetCSSCursorName(cdata->cursor_दत्त.system.id, &fallback_name);
    संरचना wl_cursor *cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, css_name);
    यदि (!cursor && fallback_name) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, fallback_name);
    }

    // Fallback to the default cursor if the chosen one wasn't found
    यदि (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "default");
    }
    // Try the old X11 name as a last resort
    यदि (!cursor) {
        cursor = WAYLAND_wl_cursor_theme_get_cursor(theme, "left_ptr");
    }
    यदि (!cursor) {
        प्रत्यागम false;
    }

    // ... Set the cursor data, finally.
    cdata->अङ्कः_चौकटाः = cursor->image_गणनम्_2;
    Wayland_CachedSystemCursor *c = Wayland_CacheSystemCursor(cdata, cursor, theme_आकार);
    state->system_cursor_handle = c;

    यदि (cursor->image_गणनम्_2 > 1 && !cdata->frame_durations_ms) {
        cdata->योग_duration_ms = 0;
        cdata->frame_durations_ms = SDL_calloc(cursor->image_गणनम्_2, परिमाण(Uint32));

        प्रति (पूर्णाङ्क i = 0; i < cursor->image_गणनम्_2; ++i) {
            cdata->frame_durations_ms[i] = cursor->images[i]->delay;
            cdata->योग_duration_ms += cursor->images[i]->delay;
        }
    }

    *dst_आकार = SDL_lround(cursor->images[0]->विस्तारः / state->scale);
    *hot_x = SDL_lround(cursor->images[0]->hotspot_x / state->scale);
    *hot_y = SDL_lround(cursor->images[0]->hotspot_y / state->scale);

    प्रत्यागम true;
}

स्थिर पूर्णाङ्क surface_क्रमय_callback(ध्रुव शून्य *a, ध्रुव शून्य *b)
{
    ध्रुव SDL_Surface *s1 = *(ध्रुव SDL_Surface **)a;
    ध्रुव SDL_Surface *s2 = *(ध्रुव SDL_Surface **)b;

    प्रत्यागम (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

स्थिर SDL_Cursor *Wayland_CreateAnimatedCursor(SDL_CursorFrameInfo *चौकटाः, पूर्णाङ्क frame_गणनम्, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_Cursor *cursor = SDL_calloc(1, परिमाण(*cursor));
    यदि (!cursor) {
        प्रत्यागम रिक्त;
    }

    SDL_Cursor_दत्त *दत्त = रिक्त;
    Wayland_SHMPool *shm_pool = रिक्त;
    पूर्णाङ्क pool_आकार = 0;
    पूर्णाङ्क max_images = 0;
    bool is_राशिः = false;
    संरचना SurfaceArray
    {
        SDL_Surface **surfaces;
        पूर्णाङ्क गणनम्;
    } *surfaces = SDL_small_alloc(संरचना SurfaceArray, frame_गणनम्, &is_राशिः);
    यदि (!surfaces) {
        गच्छ failed;
    }
    SDL_memset(surfaces, 0, परिमाण(संरचना SurfaceArray) * frame_गणनम्);

    // Calculate the total allocation size.
    प्रति (पूर्णाङ्क i = 0; i < frame_गणनम्; ++i) {
        surfaces[i].surfaces = SDL_GetSurfaceImages(चौकटाः[i].surface, &surfaces[i].गणनम्);
        यदि (!surfaces[i].surfaces) {
            गच्छ failed;
        }

        SDL_qsort(surfaces[i].surfaces, surfaces[i].गणनम्, परिमाण(SDL_Surface *), surface_क्रमय_callback);
        max_images = SDL_max(max_images, surfaces[i].गणनम्);
        प्रति (पूर्णाङ्क j = 0; j < surfaces[i].गणनम्; ++j) {
            pool_आकार += surfaces[i].surfaces[j]->w * surfaces[i].surfaces[j]->h * 4;
        }
    }

    दत्त = SDL_calloc(1, परिमाण(*दत्त) + (परिमाण(CustomCursorImage) * max_images * frame_गणनम्));
    यदि (!दत्त) {
        गच्छ failed;
    }

    दत्त->frame_durations_ms = SDL_calloc(frame_गणनम्, परिमाण(Uint32));
    यदि (!दत्त->frame_durations_ms) {
        गच्छ failed;
    }

    shm_pool = Wayland_AllocSHMPool(pool_आकार);
    यदि (!shm_pool) {
        गच्छ failed;
    }

    cursor->आन्तरिकम् = दत्त;
    दत्त->cursor_दत्त.custom.विस्तारः = चौकटाः[0].surface->w;
    दत्त->cursor_दत्त.custom.height = चौकटाः[0].surface->h;
    दत्त->cursor_दत्त.custom.hot_x = hot_x;
    दत्त->cursor_दत्त.custom.hot_y = hot_y;
    दत्त->cursor_दत्त.custom.images_प्रत्येकम्_frame = max_images;
    दत्त->अङ्कः_चौकटाः = frame_गणनम्;

    प्रति (पूर्णाङ्क i = 0; i < frame_गणनम्; ++i) {
        दत्त->frame_durations_ms[i] = चौकटाः[i].duration;
        यदि (दत्त->योग_duration_ms < SDL_MAX_UINT32) {
            यदि (दत्त->frame_durations_ms[i] > 0) {
                दत्त->योग_duration_ms += दत्त->frame_durations_ms[i];
            } अन्यथा {
                दत्त->योग_duration_ms = SDL_MAX_UINT32;
            }
        }

        ध्रुव पूर्णाङ्क विस्थापनम्_2 = i * max_images;
        प्रति (पूर्णाङ्क j = 0; j < surfaces[i].गणनम्; ++j) {
            SDL_Surface *surface = surfaces[i].surfaces[j];

            // Convert the surface format, if required.
            यदि (surface->format != SDL_PIXELFORMAT_ARGB8888) {
                surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
                यदि (!surface) {
                    गच्छ failed;
                }
            }

            दत्त->cursor_दत्त.custom.images[विस्थापनम्_2 + j].विस्तारः = surface->w;
            दत्त->cursor_दत्त.custom.images[विस्थापनम्_2 + j].height = surface->h;

            शून्य *buf_दत्त;
            दत्त->cursor_दत्त.custom.images[विस्थापनम्_2 + j].बफर_2 = Wayland_Alloc_बफर_From_Pool(shm_pool, surface->w, surface->h, &buf_दत्त);
            // Wayland requires premultiplied alpha for its surfaces.
            SDL_PremultiplyAlpha(surface->w, surface->h,
                                 surface->format, surface->pixels, surface->pitch,
                                 SDL_PIXELFORMAT_ARGB8888, buf_दत्त, surface->w * 4, true);

            यदि (surface != surfaces[i].surfaces[j]) {
                SDL_DestroySurface(surface);
            }
        }

        // Free the memory returned by SDL_GetSurfaceImages().
        SDL_free(surfaces[i].surfaces);
    }

    SDL_small_free(surfaces, is_राशिः);
    Wayland_ReleaseSHMPool(shm_pool);

    प्रत्यागम cursor;

failed:
    Wayland_ReleaseSHMPool(shm_pool);
    यदि (दत्त) {
        SDL_free(दत्त->frame_durations_ms);
        प्रति (पूर्णाङ्क i = 0; i < दत्त->cursor_दत्त.custom.images_प्रत्येकम्_frame * frame_गणनम्; ++i) {
            यदि (दत्त->cursor_दत्त.custom.images[i].बफर_2) {
                wl_बफर_destroy(दत्त->cursor_दत्त.custom.images[i].बफर_2);
            }
        }
    }

    SDL_free(दत्त);

    यदि (surfaces) {
        प्रति (पूर्णाङ्क i = 0; i < frame_गणनम्; ++i) {
            SDL_free(surfaces[i].surfaces);
        }
        SDL_small_free(surfaces, is_राशिः);
    }

    SDL_free(cursor);

    प्रत्यागम रिक्त;
}

स्थिर SDL_Cursor *Wayland_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_CursorFrameInfo frame = {
        surface, 0
    };

    प्रत्यागम Wayland_CreateAnimatedCursor(&frame, 1, hot_x, hot_y);
}

स्थिर SDL_Cursor *Wayland_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = SDL_calloc(1, परिमाण(*cursor));

    यदि (cursor) {
        SDL_Cursor_दत्त *cdata = SDL_calloc(1, परिमाण(*cdata));
        यदि (!cdata) {
            SDL_free(cursor);
            प्रत्यागम रिक्त;
        }
        cursor->आन्तरिकम् = cdata;

        WAYLAND_wl_list_init(&cdata->cursor_दत्त.system.cursor_बफर_cache);
        cdata->cursor_दत्त.system.id = id;
        cdata->is_system_cursor = true;
    }

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *Wayland_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम Wayland_CreateSystemCursor(id);
}

स्थिर शून्य Wayland_Free_Cursor_दत्त(SDL_Cursor_दत्त *d)
{
    SDL_VideoDevice *video_device = SDL_GetVideoDevice();
    SDL_Video_दत्त *video_दत्त = video_device->आन्तरिकम्;
    SDL_WaylandSeat *seat;

    // Stop any frame callbacks and detach buffers associated with the cursor being destroyed.
    wl_list_for_each (seat, &video_दत्त->seat_list, link)
    {
        यदि (seat->pointer.cursor_state.current_cursor == d) {
            Wayland_CursorStateDestroyFrameCallback(&seat->pointer.cursor_state);

            // Custom cursor buffers are about to be destroyed, so ensure they are detached.
            यदि (!d->is_system_cursor && seat->pointer.cursor_state.surface) {
                wl_surface_attach(seat->pointer.cursor_state.surface, रिक्त, 0, 0);
            }

            seat->pointer.cursor_state.current_cursor = रिक्त;
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            यदि (tool->cursor_state.current_cursor == d) {
                Wayland_CursorStateDestroyFrameCallback(&tool->cursor_state);

                // Custom cursor buffers are about to be destroyed, so ensure they are detached.
                यदि (!d->is_system_cursor && tool->cursor_state.surface) {
                    wl_surface_attach(seat->pointer.cursor_state.surface, रिक्त, 0, 0);
                }

                tool->cursor_state.current_cursor = रिक्त;
            }
        }
    }

    यदि (d->is_system_cursor) {
        Wayland_CachedSystemCursor *c, *अस्थायी;
        wl_list_for_each_safe(c, अस्थायी, &d->cursor_दत्त.system.cursor_बफर_cache, ग्रन्थिः) {
            SDL_free(c);
        }
    } अन्यथा {
        प्रति (पूर्णाङ्क i = 0; i < d->अङ्कः_चौकटाः * d->cursor_दत्त.custom.images_प्रत्येकम्_frame; ++i) {
            यदि (d->cursor_दत्त.custom.images[i].बफर_2) {
                wl_बफर_destroy(d->cursor_दत्त.custom.images[i].बफर_2);
            }
        }
    }

    SDL_free(d->frame_durations_ms);
}

स्थिर शून्य Wayland_FreeCursor(SDL_Cursor *cursor)
{
    यदि (!cursor) {
        प्रत्यागम;
    }

    // Probably not a cursor we own
    यदि (!cursor->आन्तरिकम्) {
        प्रत्यागम;
    }

    Wayland_Free_Cursor_दत्त(cursor->आन्तरिकम्);

    SDL_free(cursor->आन्तरिकम्);
    SDL_free(cursor);
}

स्थिर गणना wp_cursor_shape_device_v1_shape Wayland_GetSystemCursorShape(SDL_SystemCursor id)
{
    Uint32 shape;

    विकल्प (id) {
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_WAIT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_WAIT;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CROSSHAIR;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_प्रगतिः:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_प्रगतिः;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_EW_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NS_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_MOVE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_MOVE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NOT_ALLOWED;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_POINTER:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NW_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NE_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SE_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_SW_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CONTEXT_MENU;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_HELP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_HELP;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_CELL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_CELL;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_VERTICAL_TEXT;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALIAS;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_COPY:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COPY;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NO_DROP;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_GRAB:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRAB;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_GRABBING;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_COL_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ROW_RESIZE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ALL_SCROLL;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_अन्तर्:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_अन्तर्;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_बहिर्गमनम्:
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_ZOOM_बहिर्गमनम्;
        भङ्ग;
    स्वभाव:
        SDL_assert(0); // Should never be here...
        shape = WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }

    प्रत्यागम shape;
}

प्रकारनिर्देश संरचना Wayland_PointerObject
{
    सङ्घ
    {
        संरचना wl_pointer *wl_pointer;
        संरचना zwp_tablet_tool_v2 *wl_tool;
    };

    bool is_pointer;
} Wayland_PointerObject;

स्थिर शून्य Wayland_Cursor_State_समुच्चयः_Cursor(SDL_WaylandCursorState *state, ध्रुव Wayland_PointerObject *obj, SDL_गवाक्षः_दत्त *focus, Uint32 serial, SDL_Cursor *cursor)
{
    SDL_Video_दत्त *viddata = SDL_GetVideoDevice()->आन्तरिकम्;
    SDL_Cursor_दत्त *cursor_दत्त = cursor ? cursor->आन्तरिकम् : रिक्त;
    पूर्णाङ्क dst_विस्तारः = 0;
    पूर्णाङ्क dst_height = 0;
    पूर्णाङ्क hot_x;
    पूर्णाङ्क hot_y;

    // Stop the frame callback for old animated cursors.
    यदि (cursor_दत्त != state->current_cursor) {
        Wayland_CursorStateDestroyFrameCallback(state);
    }

    यदि (cursor) {
        यदि (cursor_दत्त == state->current_cursor && state->current_frame >= 0) {
            // Restart the animation sequence if the cursor didn't change.
            यदि (cursor_दत्त->अङ्कः_चौकटाः > 1) {
                Wayland_CursorStateResetAnimation(state, true);
            }

            प्रत्यागम;
        }

        यदि (cursor_दत्त->is_system_cursor) {
            // If the cursor shape protocol is supported, the compositor will draw nicely scaled cursors for us, so nothing more to do.
            यदि (state->cursor_shape) {
                // Don't need the surface or viewport if using the cursor shape protocol.
                यदि (state->surface) {
                    wl_surface_attach(state->surface, रिक्त, 0, 0);
                    wl_surface_commit(state->surface);

                    यदि (obj->is_pointer) {
                        wl_pointer_समुच्चयः_cursor(obj->wl_pointer, serial, रिक्त, 0, 0);
                    } अन्यथा {
                        zwp_tablet_tool_v2_समुच्चयः_cursor(obj->wl_tool, serial, रिक्त, 0, 0);
                    }

                    यदि (state->viewport) {
                        wp_viewport_destroy(state->viewport);
                        state->viewport = रिक्त;
                    }

                    wl_surface_destroy(state->surface);
                    state->surface = रिक्त;
                }

                ध्रुव गणना wp_cursor_shape_device_v1_shape shape = Wayland_GetSystemCursorShape(cursor_दत्त->cursor_दत्त.system.id);
                wp_cursor_shape_device_v1_समुच्चयः_shape(state->cursor_shape, serial, shape);
                state->current_cursor = cursor_दत्त;
                state->current_frame = 0;

                प्रत्यागम;
            }

            // If viewports aren't available, the scale is always 1.0.
            state->scale = viddata->viewporter && focus ? focus->scale_गुणकः_2 : 1.0;
            यदि (!Wayland_GetSystemCursor(cursor_दत्त, state, &dst_विस्तारः, &hot_x, &hot_y)) {
                प्रत्यागम;
            }

            dst_height = dst_विस्तारः;
        } अन्यथा {
            /* If viewports aren't available, the scale is always 1.0.
             *
             * If the pointer scale values are 1.0, the preferred backing buffer scale is the window scale.
             *
             * If the pointer is scaled, the dimensions are scaled by the pointer scale, so custom cursors will be scaled
             * relative to the viewport size.
             */
            यदि (!focus || (focus->pointer_scale.x == 1.0 && focus->pointer_scale.y == 1.0)) {
                state->scale = viddata->viewporter && focus ? focus->scale_गुणकः_2 : 1.0;
                dst_विस्तारः = cursor_दत्त->cursor_दत्त.custom.विस्तारः;
                dst_height = cursor_दत्त->cursor_दत्त.custom.height;
                hot_x = cursor_दत्त->cursor_दत्त.custom.hot_x;
                hot_y = cursor_दत्त->cursor_दत्त.custom.hot_y;
            } अन्यथा {
                // The preferred buffer scale is the inverse of the pointer scale.
                state->scale = 1.0 / SDL_min(focus->pointer_scale.x, focus->pointer_scale.y);
                dst_विस्तारः = SDL_max((पूर्णाङ्क)SDL_lround((द्विगुण)cursor_दत्त->cursor_दत्त.custom.विस्तारः / focus->pointer_scale.x), 1);
                dst_height = SDL_max((पूर्णाङ्क)SDL_lround((द्विगुण)cursor_दत्त->cursor_दत्त.custom.height / focus->pointer_scale.y), 1);
                hot_x = (पूर्णाङ्क)SDL_lround((द्विगुण)cursor_दत्त->cursor_दत्त.custom.hot_x / focus->pointer_scale.x);
                hot_y = (पूर्णाङ्क)SDL_lround((द्विगुण)cursor_दत्त->cursor_दत्त.custom.hot_y / focus->pointer_scale.y);
            }

        }

        state->current_cursor = cursor_दत्त;

        यदि (!state->surface) {
            संरचना wl_compositor *compositor_wrapper = Wayland_CreateEventThreadProxyWrapper(viddata->event_thread_context, viddata->compositor);
            state->surface = wl_compositor_create_surface(compositor_wrapper);
            WAYLAND_wl_proxy_wrapper_destroy(compositor_wrapper);
        }

        संरचना wl_बफर *बफर_2 = Wayland_CursorStateGetFrame(state, 0);
        wl_surface_attach(state->surface, बफर_2, 0, 0);
        state->current_frame = 0;

        यदि (state->scale != 1.0) {
            यदि (!state->viewport) {
                state->viewport = wp_viewporter_get_viewport(viddata->viewporter, state->surface);
            }

            wp_viewport_समुच्चयः_source(state->viewport, wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1), wl_fixed_from_int(-1));
            wp_viewport_समुच्चयः_destination(state->viewport, dst_विस्तारः, dst_height);
        } अन्यथा यदि (state->viewport) {
            wp_viewport_destroy(state->viewport);
            state->viewport = रिक्त;
        }

        यदि (obj->is_pointer) {
            wl_pointer_समुच्चयः_cursor(obj->wl_pointer, serial, state->surface, hot_x, hot_y);
        } अन्यथा {
            zwp_tablet_tool_v2_समुच्चयः_cursor(obj->wl_tool, serial, state->surface, hot_x, hot_y);
        }

        यदि (wl_surface_get_संस्करणम्(state->surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_संस्करणम्) {
            wl_surface_damage_बफर(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } अन्यथा {
            wl_surface_damage(state->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        // If more than one frame is available, create a frame callback to run the animation.
        यदि (cursor_दत्त->अङ्कः_चौकटाः > 1) {
            Wayland_CursorStateResetAnimation(state, false);
            Wayland_Cursor_State_समुच्चयः_Frame_Callback(state, state);
        }

        wl_surface_commit(state->surface);
    } अन्यथा {
        Wayland_CursorStateDestroyFrameCallback(state);
        state->current_cursor = रिक्त;

        यदि (state->surface) {
            wl_surface_attach(state->surface, रिक्त, 0, 0);
            wl_surface_commit(state->surface);
        }

        यदि (obj->is_pointer) {
            wl_pointer_समुच्चयः_cursor(obj->wl_pointer, serial, रिक्त, 0, 0);
        } अन्यथा {
            zwp_tablet_tool_v2_समुच्चयः_cursor(obj->wl_tool, serial, रिक्त, 0, 0);
        }
    }
}

स्थिर शून्य Wayland_CursorStateResetCursor(SDL_WaylandCursorState *state)
{
    // Stop the frame callback and set the reset status.
    Wayland_CursorStateDestroyFrameCallback(state);
    state->current_frame = -1;
}

शून्य Wayland_DisplayUpdatePointerFocusedScale(SDL_गवाक्षः_दत्त *updated_गवाक्षः)
{
    SDL_Video_दत्त *viddata = updated_गवाक्षः->wayland_दत्त;
    SDL_WaylandSeat *seat;
    ध्रुव द्विगुण new_scale = SDL_min(updated_गवाक्षः->pointer_scale.x, updated_गवाक्षः->pointer_scale.y);

    wl_list_for_each (seat, &viddata->seat_list, link) {
        यदि (seat->pointer.focus == updated_गवाक्षः) {
            SDL_WaylandCursorState *state = &seat->pointer.cursor_state;
            यदि (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
                Wayland_CursorStateResetCursor(state);
                Wayland_SeatUpdatePointerCursor(seat);
            }
        }

        SDL_WaylandPenTool *tool;
        wl_list_for_each (tool, &seat->tablet.tool_list, link) {
            यदि (tool->focus == updated_गवाक्षः) {
                SDL_WaylandCursorState *state = &tool->cursor_state;
                यदि (state->current_cursor && !state->current_cursor->is_system_cursor && state->scale != new_scale) {
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
    SDL_Video_दत्त *d = vd->आन्तरिकम्;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_WaylandSeat *seat;
    Wayland_PointerObject obj;

    wl_list_for_each (seat, &d->seat_list, link) {
        यदि (seat->pointer.wl_pointer) {
            obj.wl_pointer = seat->pointer.wl_pointer;
            obj.is_pointer = true;
            यदि (mouse->focus && mouse->focus->आन्तरिकम् == seat->pointer.focus) {
                Wayland_Cursor_State_समुच्चयः_Cursor(&seat->pointer.cursor_state, &obj, seat->pointer.focus, seat->pointer.enter_serial, cursor);
            } अन्यथा यदि (!seat->pointer.focus) {
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
            यदि (tool->focus && (!mouse->focus || mouse->focus->आन्तरिकम् == tool->focus)) {
                Wayland_Cursor_State_समुच्चयः_Cursor(&tool->cursor_state, &obj, tool->focus, tool->proximity_serial, mouse->cur_cursor);
            } अन्यथा यदि (!tool->focus) {
                Wayland_CursorStateResetCursor(&tool->cursor_state);
            }
        }
    }

    प्रत्यागम true;
}

शून्य Wayland_SeatWarpMouse(SDL_WaylandSeat *seat, SDL_गवाक्षः_दत्त *गवाक्षः, भिन्न x, भिन्न y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_दत्त *d = vd->आन्तरिकम्;

    यदि (seat->pointer.wl_pointer) {
        यदि (d->wp_pointer_warp_v1) {
            // It's a protocol error to warp the pointer outside of the surface, so clamp the position.
            ध्रुव wl_fixed_t f_x = wl_fixed_from_double(SDL_clamp(x / गवाक्षः->pointer_scale.x, 0, गवाक्षः->current.logical_विस्तारः));
            ध्रुव wl_fixed_t f_y = wl_fixed_from_double(SDL_clamp(y / गवाक्षः->pointer_scale.y, 0, गवाक्षः->current.logical_height));
            wp_pointer_warp_v1_warp_pointer(d->wp_pointer_warp_v1, गवाक्षः->surface, seat->pointer.wl_pointer, f_x, f_y, seat->pointer.enter_serial);
        } अन्यथा {
            bool update_grabs = false;

            // Pointers can only have one confinement type active on a surface at one time.
            यदि (seat->pointer.confined_pointer) {
                zwp_confined_pointer_v1_destroy(seat->pointer.confined_pointer);
                seat->pointer.confined_pointer = रिक्त;
                update_grabs = true;
            }
            यदि (seat->pointer.locked_pointer) {
                zwp_locked_pointer_v1_destroy(seat->pointer.locked_pointer);
                seat->pointer.locked_pointer = रिक्त;
                update_grabs = true;
            }

            /* The pointer confinement protocol allows setting a hint to warp the pointer,
             * but only when the pointer is locked.
             *
             * Lock the pointer, set the position hint, unlock, and hope for the best.
             */
            संरचना zwp_locked_pointer_v1 *warp_तालकम् =
                zwp_pointer_constraints_v1_तालकम्_pointer(d->pointer_constraints, गवाक्षः->surface,
                                                        seat->pointer.wl_pointer, रिक्त,
                                                        ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_ONESHOT);

            ध्रुव wl_fixed_t f_x = wl_fixed_from_double(x / गवाक्षः->pointer_scale.x);
            ध्रुव wl_fixed_t f_y = wl_fixed_from_double(y / गवाक्षः->pointer_scale.y);
            zwp_locked_pointer_v1_समुच्चयः_cursor_position_hint(warp_तालकम्, f_x, f_y);
            wl_surface_commit(गवाक्षः->surface);

            zwp_locked_pointer_v1_destroy(warp_तालकम्);

            यदि (update_grabs) {
                Wayland_SeatUpdatePointerGrab(seat);
            }
        }

        यदि (wl_pointer_get_संस्करणम्(seat->pointer.wl_pointer) < WL_POINTER_WARP_SINCE_संस्करणम्) {
            SDL_SendMouseWarp(0, गवाक्षः->sdlwindow, seat->pointer.sdl_id, x, y);
        }
    }
}

स्थिर bool Wayland_WarpMouseRelative(SDL_गवाक्षः *गवाक्षः, भिन्न x, भिन्न y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_दत्त *d = vd->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    SDL_WaylandSeat *seat;

    यदि (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            यदि (wind == seat->pointer.focus) {
                Wayland_SeatWarpMouse(seat, wind, x, y);
            }
        }
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    प्रत्यागम true;
}

स्थिर bool Wayland_WarpMouseGlobal(भिन्न x, भिन्न y)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_दत्त *d = vd->आन्तरिकम्;
    SDL_WaylandSeat *seat;

    यदि (d->wp_pointer_warp_v1 || d->pointer_constraints) {
        wl_list_for_each (seat, &d->seat_list, link) {
            SDL_गवाक्षः_दत्त *wind = seat->pointer.focus ? seat->pointer.focus : seat->keyboard.focus;

            // If the client wants the coordinates warped to within a focused window, just convert the coordinates to relative.
            यदि (wind) {
                SDL_गवाक्षः *गवाक्षः = wind->sdlwindow;

                पूर्णाङ्क abs_x, abs_y;
                SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, गवाक्षः->x, गवाक्षः->y, &abs_x, &abs_y);

                ध्रुव SDL_FPoint p = { x, y };
                ध्रुव SDL_FRect r = { abs_x, abs_y, गवाक्षः->w, गवाक्षः->h };

                // Try to warp the cursor if the point is within the seat's focused window.
                यदि (SDL_Point_अन्तर्_Rect_Float(&p, &r)) {
                    Wayland_SeatWarpMouse(seat, wind, p.x - abs_x, p.y - abs_y);
                }
            }
        }
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("wayland: mouse warp failed; compositor lacks support for the required wp_pointer_warp_v1 or zwp_pointer_confinement_v1 protocol");
    }

    प्रत्यागम true;
}

स्थिर bool Wayland_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled)
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_दत्त *दत्त = vd->आन्तरिकम्;

    // Relative mode requires both the relative motion and pointer confinement protocols.
    यदि (!दत्त->relative_pointer_manager) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to enable relative mode: compositor lacks support for the required zwp_relative_pointer_manager_v1 protocol");
    }
    यदि (!दत्त->pointer_constraints) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to enable relative mode: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }

    // Windows have a relative mode flag, so just update the grabs on a state change.
    Wayland_DisplayUpdatePointerGrabs(दत्त, रिक्त);
    प्रत्यागम true;
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
स्थिर SDL_MouseButtonFlags SDLCALL Wayland_GetGlobalMouseState(भिन्न *x, भिन्न *y)
{
    ध्रुव SDL_Mouse *mouse = SDL_GetMouse();
    SDL_MouseButtonFlags परिणाम = 0;

    // If there is no window with mouse focus, we have no idea what the actual position or button state is.
    यदि (mouse->focus) {
        SDL_Video_दत्त *video_दत्त = SDL_GetVideoDevice()->आन्तरिकम्;
        SDL_WaylandSeat *seat;
        पूर्णाङ्क off_x, off_y;
        SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(mouse->focus, mouse->focus->x, mouse->focus->y, &off_x, &off_y);
        *x = mouse->x + off_x;
        *y = mouse->y + off_y;

        // Query the buttons from the seats directly, as this may be called from within a hit test handler.
        wl_list_for_each (seat, &video_दत्त->seat_list, link) {
            परिणाम |= seat->pointer.buttons_pressed;
        }
    } अन्यथा {
        *x = 0.f;
        *y = 0.f;
    }

    प्रत्यागम परिणाम;
}

#यदि 0  // TODO RECONNECT: See waylandvideo.c for more information!
स्थिर शून्य Wayland_RecreateCursor(SDL_Cursor *cursor, SDL_Video_दत्त *vdata)
{
    SDL_Cursor_दत्त *cdata = cursor->आन्तरिकम्;

    // Probably not a cursor we own
    यदि (cdata == रिक्त) {
        प्रत्यागम;
    }

    Wayland_Free_Cursor_दत्त(cdata);

    // We're not currently freeing this, so... yolo?
    यदि (cdata->shm_दत्त != रिक्त) {
        शून्य *old_दत्त_pointer = cdata->shm_दत्त;
        पूर्णाङ्क stride = cdata->w * 4;

        create_बफर_from_shm(cdata, cdata->w, cdata->h, WL_SHM_FORMAT_ARGB8888);

        SDL_memcpy(cdata->shm_दत्त, old_दत्त_pointer, stride * cdata->h);
    }
    cdata->surface = wl_compositor_create_surface(vdata->compositor);
    wl_surface_समुच्चयः_user_दत्त(cdata->surface, रिक्त);
}

शून्य Wayland_RecreateCursors(शून्य)
{
    SDL_Cursor *cursor;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Video_दत्त *vdata = SDL_GetVideoDevice()->आन्तरिकम्;

    यदि (vdata && vdata->cursor_themes) {
        SDL_free(vdata->cursor_themes);
        vdata->cursor_themes = रिक्त;
        vdata->अङ्कः_cursor_themes = 0;
    }

    यदि (mouse == रिक्त) {
        प्रत्यागम;
    }

    प्रति (cursor = mouse->cursors; cursor != रिक्त; cursor = cursor->अग्र) {
        Wayland_RecreateCursor(cursor, vdata);
    }
    यदि (mouse->def_cursor) {
        Wayland_RecreateCursor(mouse->def_cursor, vdata);
    }
    यदि (mouse->cur_cursor) {
        Wayland_RecreateCursor(mouse->cur_cursor, vdata);
        यदि (mouse->cursor_visible) {
            Wayland_ShowCursor(mouse->cur_cursor);
        }
    }
}
#यदि_अन्तः // 0

शून्य Wayland_InitMouse(SDL_Video_दत्त *दत्त)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Wayland_CreateCursor;
    mouse->CreateAnimatedCursor = Wayland_CreateAnimatedCursor;
    mouse->CreateSystemCursor = Wayland_CreateSystemCursor;
    mouse->ShowCursor = Wayland_ShowCursor;
    mouse->FreeCursor = Wayland_FreeCursor;
    mouse->WarpMouse = Wayland_WarpMouseRelative;
    mouse->WarpMouseGlobal = Wayland_WarpMouseGlobal;
    mouse->समुच्चयः_Relative_Mouse_बहुलकम् = Wayland_समुच्चयः_Relative_Mouse_बहुलकम्;
    mouse->GetGlobalMouseState = Wayland_GetGlobalMouseState;

    mouse->have_explicit_warp_event = true;

    SDL_लब्धम्_Test_परिणाम r = SDL_HITTEST_प्रसामान्यम्;
    यावत् (r <= SDL_HITTEST_RESIZE_वामः) {
        विकल्प (r) {
        पक्ष SDL_HITTEST_प्रसामान्यम्:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            भङ्ग;
        पक्ष SDL_HITTEST_DRAGGABLE:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_TOPLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_शिखरम्:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_TOPRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_दक्षिणः:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOM:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE);
            भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_वामः:
            sys_cursors[r] = Wayland_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE);
            भङ्ग;
        }
        r++;
    }

#यदि_परिभाषितम् SDL_USE_LIBDBUS
    SDL_VideoDevice *vd = SDL_GetVideoDevice();
    SDL_Video_दत्त *d = vd->आन्तरिकम्;

    /* The D-Bus cursor properties are only needed when manually loading themes and system cursors.
     * If the cursor shape protocol is present, the compositor will handle it internally.
     */
    यदि (!d->cursor_shape_manager) {
        Wayland_DBusInitCursorProperties(d);
    }
#यदि_अन्तः

    SDL_समुच्चयः_Default_Cursor(Wayland_CreateDefaultCursor());
}

शून्य Wayland_FiniMouse(SDL_Video_दत्त *दत्त)
{
    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(sys_cursors); i++) {
        Wayland_FreeCursor(sys_cursors[i]);
        sys_cursors[i] = रिक्त;
    }

    Wayland_FreeCursorThemes(दत्त);

#यदि_परिभाषितम् SDL_USE_LIBDBUS
    Wayland_DBusFinishCursorProperties();
#यदि_अन्तः
}

शून्य Wayland_SeatResetCursor(SDL_WaylandSeat *seat)
{
    Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
}

शून्य Wayland_Seat_समुच्चयः_Default_Cursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_गवाक्षः_दत्त *pointer_focus = seat->pointer.focus;
    ध्रुव Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    Wayland_Cursor_State_समुच्चयः_Cursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->def_cursor);
}

शून्य Wayland_SeatUpdatePointerCursor(SDL_WaylandSeat *seat)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_गवाक्षः_दत्त *pointer_focus = seat->pointer.focus;
    ध्रुव Wayland_PointerObject obj = {
        .wl_pointer = seat->pointer.wl_pointer,
        .is_pointer = true
    };

    यदि (pointer_focus) {
        यदि (mouse->cursor_visible) {
            यदि (!seat->pointer.relative_pointer || !mouse->relative_बहुलकम्_hide_cursor) {
                ध्रुव SDL_लब्धम्_Test_परिणाम rc = pointer_focus->लब्धम्_test_परिणाम;

                यदि (seat->pointer.relative_pointer || rc == SDL_HITTEST_प्रसामान्यम् || rc == SDL_HITTEST_DRAGGABLE) {
                    Wayland_Cursor_State_समुच्चयः_Cursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, mouse->cur_cursor);
                } अन्यथा {
                    Wayland_Cursor_State_समुच्चयः_Cursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, sys_cursors[rc]);
                }
            } अन्यथा {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_समुच्चयः_Cursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, रिक्त);
            }
        } अन्यथा {
            Wayland_Cursor_State_समुच्चयः_Cursor(&seat->pointer.cursor_state, &obj, pointer_focus, seat->pointer.enter_serial, रिक्त);
        }
    } अन्यथा {
        Wayland_CursorStateResetCursor(&seat->pointer.cursor_state);
    }
}

शून्य Wayland_TabletToolUpdateCursor(SDL_WaylandPenTool *tool)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_गवाक्षः_दत्त *tool_focus = tool->focus;
    ध्रुव Wayland_PointerObject obj = {
        .wl_tool = tool->wltool,
        .is_pointer = false
    };

    यदि (tool_focus) {
        यदि (mouse->cursor_visible) {
            // Relative mode is only relevant if the tool sends pointer events.
            ध्रुव bool relative = mouse->pen_mouse_events && (tool_focus->sdlwindow->flags & SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्);

            यदि (!relative || !mouse->relative_बहुलकम्_hide_cursor) {
                Wayland_Cursor_State_समुच्चयः_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, mouse->cur_cursor);
            } अन्यथा {
                // Hide the cursor in relative mode, unless requested otherwise by the hint.
                Wayland_Cursor_State_समुच्चयः_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, रिक्त);
            }
        } अन्यथा {
            Wayland_Cursor_State_समुच्चयः_Cursor(&tool->cursor_state, &obj, tool_focus, tool->proximity_serial, रिक्त);
        }
    } अन्यथा {
        Wayland_CursorStateResetCursor(&tool->cursor_state);
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND

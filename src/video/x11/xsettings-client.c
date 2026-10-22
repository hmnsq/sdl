/*
 * Copyright © 2001, 2007 Red Hat, Inc.
 * Copyright 2024 Igalia S.L.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Red Hat not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Red Hat makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * RED HAT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL RED HAT
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Owen Taylor, Red Hat, Inc.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "xsettings-client.h"

ਬਣਤਰ _XSettingsClient
{
  Display *display;
  ਪੂਰਨ screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  ਖਾਲੀ *cb_ਅੰਕੜੇ;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  ਖਿੜਕੀ_2 manager_ਖਿੜਕੀ;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ਸਥਿਰ ਖਾਲੀ
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  ਜੇ (!client->notify)
    ਵਾਪਸ;

  ਜਦੋਂ (old_iter || new_iter)
    {
      ਪੂਰਨ cmp;

      ਜੇ (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      ਨਹੀਂਤਾਂ ਜੇ (old_iter)
        cmp = -1;
      ਨਹੀਂਤਾਂ
        cmp = 1;

      ਜੇ (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ਨਿਰਾ,
                          client->cb_ਅੰਕੜੇ);
        }
      ਨਹੀਂਤਾਂ ਜੇ (cmp == 0)
        {
          ਜੇ (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_ਬਦਲਿਆ,
                            new_iter->setting,
                            client->cb_ਅੰਕੜੇ);
        }
      ਨਹੀਂਤਾਂ
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_ਅੰਕੜੇ);
        }

      ਜੇ (old_iter)
        old_iter = old_iter->ਅਗਲਾ;
      ਜੇ (new_iter)
        new_iter = new_iter->ਅਗਲਾ;
    }
}

ਸਥਿਰ ਪੂਰਨ
ignore_errors (Display *display, XErrorEvent *event)
{
  ਵਾਪਸ True;
}

ਸਥਿਰ ਅੱਖਰ local_byte_ਕ੍ਰਮ = '\0';

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਬਾਈਟਾਂ_ਖੱਬਾ_2(ਬਫਰ_2) ((ਬਫਰ_2)->ਅੰਕੜੇ + (ਬਫਰ_2)->len - (ਬਫਰ_2)->pos)

ਸਥਿਰ XSettings_ਨਤੀਜਾ
fetch_card16 (XSettings_ਬਫਰ *ਬਫਰ_2,
              CARD16          *ਨਤੀਜਾ)
{
  CARD16 x;

  ਜੇ (ਬਾਈਟਾਂ_ਖੱਬਾ_2 (ਬਫਰ_2) < 2)
    ਵਾਪਸ XSETTINGS_ACCESS;

  x = *(CARD16 *)ਬਫਰ_2->pos;
  ਬਫਰ_2->pos += 2;

  ਜੇ (ਬਫਰ_2->byte_ਕ੍ਰਮ == local_byte_ਕ੍ਰਮ)
    *ਨਤੀਜਾ = x;
  ਨਹੀਂਤਾਂ
    *ਨਤੀਜਾ = (x << 8) | (x >> 8);

  ਵਾਪਸ XSETTINGS_SUCCESS;
}

ਸਥਿਰ XSettings_ਨਤੀਜਾ
fetch_ushort (XSettings_ਬਫਰ *ਬਫਰ_2,
              ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ  *ਨਤੀਜਾ)
{
  CARD16 x;
  XSettings_ਨਤੀਜਾ r;

  r = fetch_card16 (ਬਫਰ_2, &x);
  ਜੇ (r == XSETTINGS_SUCCESS)
    *ਨਤੀਜਾ = x;

  ਵਾਪਸ r;
}

ਸਥਿਰ XSettings_ਨਤੀਜਾ
fetch_card32 (XSettings_ਬਫਰ *ਬਫਰ_2,
              CARD32          *ਨਤੀਜਾ)
{
  CARD32 x;

  ਜੇ (ਬਾਈਟਾਂ_ਖੱਬਾ_2 (ਬਫਰ_2) < 4)
    ਵਾਪਸ XSETTINGS_ACCESS;

  x = *(CARD32 *)ਬਫਰ_2->pos;
  ਬਫਰ_2->pos += 4;

  ਜੇ (ਬਫਰ_2->byte_ਕ੍ਰਮ == local_byte_ਕ੍ਰਮ)
    *ਨਤੀਜਾ = x;
  ਨਹੀਂਤਾਂ
    *ਨਤੀਜਾ = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ਵਾਪਸ XSETTINGS_SUCCESS;
}

ਸਥਿਰ XSettings_ਨਤੀਜਾ
fetch_card8 (XSettings_ਬਫਰ *ਬਫਰ_2,
             CARD8           *ਨਤੀਜਾ)
{
  ਜੇ (ਬਾਈਟਾਂ_ਖੱਬਾ_2 (ਬਫਰ_2) < 1)
    ਵਾਪਸ XSETTINGS_ACCESS;

  *ਨਤੀਜਾ = *(CARD8 *)ਬਫਰ_2->pos;
  ਬਫਰ_2->pos += 1;

  ਵਾਪਸ XSETTINGS_SUCCESS;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ਸਥਿਰ XSettingsList *
parse_settings (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅੰਕੜੇ,
                size_t         len)
{
  XSettings_ਬਫਰ ਬਫਰ_2;
  XSettings_ਨਤੀਜਾ ਨਤੀਜਾ = XSETTINGS_SUCCESS;
  XSettingsList *settings = ਨਿਰਾ;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ਨਿਰਾ;
  ਅੱਖਰ ਬਫਰ_byte_ਕ੍ਰਮ = '\0';

  local_byte_ਕ੍ਰਮ = xsettings_byte_ਕ੍ਰਮ ();

  ਬਫਰ_2.pos = ਬਫਰ_2.ਅੰਕੜੇ = ਅੰਕੜੇ;
  ਬਫਰ_2.len = len;
  ਬਫਰ_2.byte_ਕ੍ਰਮ = '\0';

  ਨਤੀਜਾ = fetch_card8 (&ਬਫਰ_2, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) &ਬਫਰ_byte_ਕ੍ਰਮ);
  ਜੇ (ਬਫਰ_byte_ਕ੍ਰਮ != MSBFirst &&
      ਬਫਰ_byte_ਕ੍ਰਮ != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      ਨਤੀਜਾ = XSETTINGS_FAILED;
      ਜਾਓ ਬਾਹਰਲਾ;
    }

  ਬਫਰ_2.byte_ਕ੍ਰਮ = ਬਫਰ_byte_ਕ੍ਰਮ;
  ਬਫਰ_2.pos += 3;

  ਨਤੀਜਾ = fetch_card32 (&ਬਫਰ_2, &serial);
  ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
    ਜਾਓ ਬਾਹਰਲਾ;

  ਨਤੀਜਾ = fetch_card32 (&ਬਫਰ_2, &n_entries);
  ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
    ਜਾਓ ਬਾਹਰਲਾ;

  ਲਈ (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      ਨਤੀਜਾ = fetch_card8 (&ਬਫਰ_2, &type);
      ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
        ਜਾਓ ਬਾਹਰਲਾ;

      ਬਫਰ_2.pos += 1;

      ਨਤੀਜਾ = fetch_card16 (&ਬਫਰ_2, &name_len);
      ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
        ਜਾਓ ਬਾਹਰਲਾ;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ਜੇ (ਬਾਈਟਾਂ_ਖੱਬਾ_2 (&ਬਫਰ_2) < pad_len)
        {
          ਨਤੀਜਾ = XSETTINGS_ACCESS;
          ਜਾਓ ਬਾਹਰਲਾ;
        }

      setting = ਸਮ੍ਰਿਤੀ_ਦਿਓ (ਆਕਾਰ *setting);
      ਜੇ (!setting)
        {
          ਨਤੀਜਾ = XSETTINGS_NO_MEM;
          ਜਾਓ ਬਾਹਰਲਾ;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = ਸਮ੍ਰਿਤੀ_ਦਿਓ (name_len + 1);
      ਜੇ (!setting->name)
        {
          ਨਤੀਜਾ = XSETTINGS_NO_MEM;
          ਜਾਓ ਬਾਹਰਲਾ;
        }

      ਸਮ੍ਰਿਤੀ_ਨਕਲ (setting->name, ਬਫਰ_2.pos, name_len);
      setting->name[name_len] = '\0';
      ਬਫਰ_2.pos += pad_len;

      ਨਤੀਜਾ = fetch_card32 (&ਬਫਰ_2, &v_int);
      ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
        ਜਾਓ ਬਾਹਰਲਾ;
      setting->ਆਖਰੀ_change_serial = v_int;

      ਚੋਣ (type)
        {
        ਹਾਲਤ XSETTINGS_TYPE_INT:
          ਨਤੀਜਾ = fetch_card32 (&ਬਫਰ_2, &v_int);
          ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
            ਜਾਓ ਬਾਹਰਲਾ;

          setting->ਅੰਕੜੇ.v_int = (INT32)v_int;
          ਰੋਕੋ;
        ਹਾਲਤ XSETTINGS_TYPE_STRING:
          ਨਤੀਜਾ = fetch_card32 (&ਬਫਰ_2, &v_int);
          ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
            ਜਾਓ ਬਾਹਰਲਾ;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ਜੇ (v_int + 1 == 0 || /* Guard against wrap-around */
              ਬਾਈਟਾਂ_ਖੱਬਾ_2 (&ਬਫਰ_2) < pad_len)
            {
              ਨਤੀਜਾ = XSETTINGS_ACCESS;
              ਜਾਓ ਬਾਹਰਲਾ;
            }

          setting->ਅੰਕੜੇ.v_string = ਸਮ੍ਰਿਤੀ_ਦਿਓ (v_int + 1);
          ਜੇ (!setting->ਅੰਕੜੇ.v_string)
            {
              ਨਤੀਜਾ = XSETTINGS_NO_MEM;
              ਜਾਓ ਬਾਹਰਲਾ;
            }

          ਸਮ੍ਰਿਤੀ_ਨਕਲ (setting->ਅੰਕੜੇ.v_string, ਬਫਰ_2.pos, v_int);
          setting->ਅੰਕੜੇ.v_string[v_int] = '\0';
          ਬਫਰ_2.pos += pad_len;

          ਰੋਕੋ;
        ਹਾਲਤ XSETTINGS_TYPE_COLOR:
          ਨਤੀਜਾ = fetch_ushort (&ਬਫਰ_2, &setting->ਅੰਕੜੇ.v_color.red);
          ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
            ਜਾਓ ਬਾਹਰਲਾ;
          ਨਤੀਜਾ = fetch_ushort (&ਬਫਰ_2, &setting->ਅੰਕੜੇ.v_color.green);
          ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
            ਜਾਓ ਬਾਹਰਲਾ;
          ਨਤੀਜਾ = fetch_ushort (&ਬਫਰ_2, &setting->ਅੰਕੜੇ.v_color.blue);
          ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
            ਜਾਓ ਬਾਹਰਲਾ;
          ਨਤੀਜਾ = fetch_ushort (&ਬਫਰ_2, &setting->ਅੰਕੜੇ.v_color.alpha);
          ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
            ਜਾਓ ਬਾਹਰਲਾ;

          ਰੋਕੋ;
        ਮੂਲ:
          /* Quietly ignore unknown types */
          ਰੋਕੋ;
        }

      setting->type = type;

      ਨਤੀਜਾ = xsettings_list_ਪਾਓ (&settings, setting);
      ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
        ਜਾਓ ਬਾਹਰਲਾ;

      setting = ਨਿਰਾ;
    }

 ਬਾਹਰਲਾ:

  ਜੇ (ਨਤੀਜਾ != XSETTINGS_SUCCESS)
    {
      ਚੋਣ (ਨਤੀਜਾ)
        {
        ਹਾਲਤ XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          ਰੋਕੋ;
        ਹਾਲਤ XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          ਰੋਕੋ;
        ਹਾਲਤ XSETTINGS_DUPLICATE_ਇੰਦਰਾਜ:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        ਹਾਲਤ XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        ਹਾਲਤ XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        ਹਾਲਤ XSETTINGS_NO_ਇੰਦਰਾਜ:
          ਰੋਕੋ;
        }

      ਜੇ (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ਨਿਰਾ;

    }

  ਵਾਪਸ settings;
}

ਸਥਿਰ ਖਾਲੀ
read_settings (XSettingsClient *client)
{
  Atom type;
  ਪੂਰਨ format;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ n_ਚੀਜ਼ਾਂ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਬਾਈਟਾਂ_after;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅੰਕੜੇ;
  ਪੂਰਨ ਨਤੀਜਾ;

  ਪੂਰਨ (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ਨਿਰਾ;

  ਜੇ (client->manager_ਖਿੜਕੀ)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      ਨਤੀਜਾ = X11_XGet_ਖਿੜਕੀ_Property (client->display, client->manager_ਖਿੜਕੀ,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_ਚੀਜ਼ਾਂ, &ਬਾਈਟਾਂ_after, &ਅੰਕੜੇ);
      X11_XSetErrorHandler (old_handler);

      ਜੇ (ਨਤੀਜਾ == Success && type != None)
        {
          ਜੇ (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          ਨਹੀਂਤਾਂ ਜੇ (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          ਨਹੀਂਤਾਂ
            client->settings = parse_settings (ਅੰਕੜੇ, n_ਚੀਜ਼ਾਂ);

          X11_XFree (ਅੰਕੜੇ);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ਸਥਿਰ ਖਾਲੀ
ਜੋੜੋ_events (Display *display,
            ਖਿੜਕੀ_2   ਖਿੜਕੀ,
            ਲੰਮਾ     ਨਕਾਬ)
{
  XWindow_ਗੁਣ attr;

  X11_XGet_ਖਿੜਕੀ_ਗੁਣ (display, ਖਿੜਕੀ, &attr);
  X11_XSelect_ਨਿਵੇਸ਼ (display, ਖਿੜਕੀ, attr.your_event_ਨਕਾਬ | ਨਕਾਬ);
}

ਸਥਿਰ ਖਾਲੀ
check_manager_ਖਿੜਕੀ (XSettingsClient *client)
{
  ਜੇ (client->manager_ਖਿੜਕੀ && client->watch)
    client->watch (client->manager_ਖਿੜਕੀ, False, 0, client->cb_ਅੰਕੜੇ);

  ਜੇ (client->grab)
    client->grab (client->display);
  ਨਹੀਂਤਾਂ
    X11_XGrabServer (client->display);

  client->manager_ਖਿੜਕੀ = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ਜੇ (client->manager_ਖਿੜਕੀ)
    X11_XSelect_ਨਿਵੇਸ਼ (client->display, client->manager_ਖਿੜਕੀ,
                      Property_Change_ਨਕਾਬ | Structure_Notify_ਨਕਾਬ);

  ਜੇ (client->ungrab)
    client->ungrab (client->display);
  ਨਹੀਂਤਾਂ
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ਜੇ (client->manager_ਖਿੜਕੀ && client->watch)
    {
      ਜੇ (!client->watch (client->manager_ਖਿੜਕੀ, True,
                          Property_Change_ਨਕਾਬ | Structure_Notify_ਨਕਾਬ,
                          client->cb_ਅੰਕੜੇ))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_ਖਿੜਕੀ = None;
          ਵਾਪਸ;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      ਪੂਰਨ                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      ਖਾਲੀ                *cb_ਅੰਕੜੇ)
{
  ਵਾਪਸ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_ਅੰਕੜੇ,
                                               ਨਿਰਾ, ਨਿਰਾ);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      ਪੂਰਨ                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      ਖਾਲੀ                *cb_ਅੰਕੜੇ,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  ਅੱਖਰ ਬਫਰ_2[256];
  ਅੱਖਰ *atom_ਨਾਂ[3];
  Atom atoms[3];

  client = ਸਮ੍ਰਿਤੀ_ਦਿਓ (ਆਕਾਰ *client);
  ਜੇ (!client)
    ਵਾਪਸ ਨਿਰਾ;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_ਅੰਕੜੇ = cb_ਅੰਕੜੇ;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_ਖਿੜਕੀ = None;
  client->settings = ਨਿਰਾ;

  SDL_snprintf(ਬਫਰ_2, ਆਕਾਰ(ਬਫਰ_2), "_XSETTINGS_S%d", screen);
  atom_ਨਾਂ[0] = ਬਫਰ_2;
  atom_ਨਾਂ[1] = "_XSETTINGS_SETTINGS";
  atom_ਨਾਂ[2] = "MANAGER";

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_XINTERNATOMS
  XInternAtoms (display, atom_ਨਾਂ, 3, False, atoms);
#ਨਹੀਂਤਾਂ
  atoms[0] = X11_XInternAtom (display, atom_ਨਾਂ[0], False);
  atoms[1] = X11_XInternAtom (display, atom_ਨਾਂ[1], False);
  atoms[2] = X11_XInternAtom (display, atom_ਨਾਂ[2], False);
#ਜੇ_ਅੰਤ

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  ਜੋੜੋ_events (display, ਜੜ੍ਹ_ਖਿੜਕੀ (display, screen), Structure_Notify_ਨਕਾਬ);

  ਜੇ (client->watch)
    client->watch (ਜੜ੍ਹ_ਖਿੜਕੀ (display, screen), True, Structure_Notify_ਨਕਾਬ,
                   client->cb_ਅੰਕੜੇ);

  check_manager_ਖਿੜਕੀ (client);

  ਵਾਪਸ client;
}


ਖਾਲੀ
xsettings_client_ਸੈੱਟ_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

ਖਾਲੀ
xsettings_client_ਸੈੱਟ_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

ਖਾਲੀ
xsettings_client_destroy (XSettingsClient *client)
{
  ਜੇ (client->watch)
    client->watch (ਜੜ੍ਹ_ਖਿੜਕੀ (client->display, client->screen),
                   False, 0, client->cb_ਅੰਕੜੇ);
  ਜੇ (client->manager_ਖਿੜਕੀ && client->watch)
    client->watch (client->manager_ਖਿੜਕੀ, False, 0, client->cb_ਅੰਕੜੇ);

  xsettings_list_free (client->settings);
  ਮੁਕਤ (client);
}

XSettings_ਨਤੀਜਾ
xsettings_client_get_setting (XSettingsClient   *client,
                              ਅਚਲ ਅੱਖਰ        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *ਖੋਜ = xsettings_list_lookup (client->settings, name);
  ਜੇ (ਖੋਜ)
    {
      *setting = xsettings_setting_copy (ਖੋਜ);
      ਵਾਪਸ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ XSETTINGS_NO_ਇੰਦਰਾਜ;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ਅਚਲ XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ਜੇ (xev->xany.ਖਿੜਕੀ == ਜੜ੍ਹ_ਖਿੜਕੀ (client->display, client->screen))
    {
      ਜੇ (xev->xany.type == Client_ਸੁਨੇਹਾ &&
          xev->xclient.ਸੁਨੇਹਾ_type == client->manager_atom &&
          xev->xclient.ਅੰਕੜੇ.l[1] == client->selection_atom)
        {
          check_manager_ਖਿੜਕੀ (client);
          ਵਾਪਸ True;
        }
    }
  ਨਹੀਂਤਾਂ ਜੇ (xev->xany.ਖਿੜਕੀ == client->manager_ਖਿੜਕੀ)
    {
      ਜੇ (xev->xany.type == DestroyNotify)
        {
          check_manager_ਖਿੜਕੀ (client);
          ਵਾਪਸ False;
        }
      ਨਹੀਂਤਾਂ ਜੇ (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ਵਾਪਸ True;
        }
    }

  ਵਾਪਸ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *ਨਤੀਜਾ;
  size_t str_len;

  ਨਤੀਜਾ = ਸਮ੍ਰਿਤੀ_ਦਿਓ (ਆਕਾਰ *ਨਤੀਜਾ);
  ਜੇ (!ਨਤੀਜਾ)
    ਵਾਪਸ ਨਿਰਾ;

  str_len = ਲੜੀ_ਲੰਬਾਈ (setting->name);
  ਨਤੀਜਾ->name = ਸਮ੍ਰਿਤੀ_ਦਿਓ (str_len + 1);
  ਜੇ (!ਨਤੀਜਾ->name)
    ਜਾਓ err;

  ਸਮ੍ਰਿਤੀ_ਨਕਲ (ਨਤੀਜਾ->name, setting->name, str_len + 1);

  ਨਤੀਜਾ->type = setting->type;

  ਚੋਣ (setting->type)
    {
    ਹਾਲਤ XSETTINGS_TYPE_INT:
      ਨਤੀਜਾ->ਅੰਕੜੇ.v_int = setting->ਅੰਕੜੇ.v_int;
      ਰੋਕੋ;
    ਹਾਲਤ XSETTINGS_TYPE_COLOR:
      ਨਤੀਜਾ->ਅੰਕੜੇ.v_color = setting->ਅੰਕੜੇ.v_color;
      ਰੋਕੋ;
    ਹਾਲਤ XSETTINGS_TYPE_STRING:
      str_len = ਲੜੀ_ਲੰਬਾਈ (setting->ਅੰਕੜੇ.v_string);
      ਨਤੀਜਾ->ਅੰਕੜੇ.v_string = ਸਮ੍ਰਿਤੀ_ਦਿਓ (str_len + 1);
      ਜੇ (!ਨਤੀਜਾ->ਅੰਕੜੇ.v_string)
        ਜਾਓ err;

      ਸਮ੍ਰਿਤੀ_ਨਕਲ (ਨਤੀਜਾ->ਅੰਕੜੇ.v_string, setting->ਅੰਕੜੇ.v_string, str_len + 1);
      ਰੋਕੋ;
    }

  ਨਤੀਜਾ->ਆਖਰੀ_change_serial = setting->ਆਖਰੀ_change_serial;

  ਵਾਪਸ ਨਤੀਜਾ;

 err:
  ਮੁਕਤ(ਨਤੀਜਾ->name); // This should NOT be SDL_free()
  ਮੁਕਤ(ਨਤੀਜਾ); // This should NOT be SDL_free()

  ਵਾਪਸ ਨਿਰਾ;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ਨਿਰਾ;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ਨਿਰਾ;

  ਜਦੋਂ (old_iter)
    {
      XSettingsList *new_ਗੰਢ;

      new_ਗੰਢ = ਸਮ੍ਰਿਤੀ_ਦਿਓ (ਆਕਾਰ *new_ਗੰਢ);
      ਜੇ (!new_ਗੰਢ)
        ਜਾਓ error;

      new_ਗੰਢ->setting = xsettings_setting_copy (old_iter->setting);
      ਜੇ (!new_ਗੰਢ->setting)
        {
          ਮੁਕਤ (new_ਗੰਢ);
          ਜਾਓ error;
        }

      ਜੇ (new_iter)
        new_iter->ਅਗਲਾ = new_ਗੰਢ;
      ਨਹੀਂਤਾਂ
        {
          new = new_ਗੰਢ;
          new->ਅਗਲਾ = ਨਿਰਾ;
        }


      new_iter = new_ਗੰਢ;

      old_iter = old_iter->ਅਗਲਾ;
    }

  ਵਾਪਸ new;

 error:
  xsettings_list_free (new);
  ਵਾਪਸ ਨਿਰਾ;
}

ਪੂਰਨ
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ਜੇ (setting_a->type != setting_b->type)
    ਵਾਪਸ 0;

  ਜੇ (strcmp (setting_a->name, setting_b->name) != 0)
    ਵਾਪਸ 0;

  ਚੋਣ (setting_a->type)
    {
    ਹਾਲਤ XSETTINGS_TYPE_INT:
      ਵਾਪਸ setting_a->ਅੰਕੜੇ.v_int == setting_b->ਅੰਕੜੇ.v_int;
    ਹਾਲਤ XSETTINGS_TYPE_COLOR:
      ਵਾਪਸ (setting_a->ਅੰਕੜੇ.v_color.red == setting_b->ਅੰਕੜੇ.v_color.red &&
              setting_a->ਅੰਕੜੇ.v_color.green == setting_b->ਅੰਕੜੇ.v_color.green &&
              setting_a->ਅੰਕੜੇ.v_color.blue == setting_b->ਅੰਕੜੇ.v_color.blue &&
              setting_a->ਅੰਕੜੇ.v_color.alpha == setting_b->ਅੰਕੜੇ.v_color.alpha);
    ਹਾਲਤ XSETTINGS_TYPE_STRING:
      ਵਾਪਸ strcmp (setting_a->ਅੰਕੜੇ.v_string, setting_b->ਅੰਕੜੇ.v_string) == 0;
    }

  ਵਾਪਸ 0;
}

ਖਾਲੀ
xsettings_setting_free (XSettingsSetting *setting)
{
  ਜੇ (setting->type == XSETTINGS_TYPE_STRING)
    ਮੁਕਤ (setting->ਅੰਕੜੇ.v_string);

  ਮੁਕਤ(setting->name); // This should NOT be SDL_free()
  ਮੁਕਤ(setting); // This should NOT be SDL_free()
}

ਖਾਲੀ
xsettings_list_free (XSettingsList *list)
{
  ਜਦੋਂ (list)
    {
      XSettingsList *ਅਗਲਾ = list->ਅਗਲਾ;

      xsettings_setting_free (list->setting);
      ਮੁਕਤ (list);

      list = ਅਗਲਾ;
    }
}

XSettings_ਨਤੀਜਾ
xsettings_list_ਪਾਓ (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ਗੰਢ;
  XSettingsList *iter;
  XSettingsList *ਆਖਰੀ = ਨਿਰਾ;

  ਗੰਢ = ਸਮ੍ਰਿਤੀ_ਦਿਓ (ਆਕਾਰ *ਗੰਢ);
  ਜੇ (!ਗੰਢ)
    ਵਾਪਸ XSETTINGS_NO_MEM;
  ਗੰਢ->setting = setting;

  iter = *list;
  ਜਦੋਂ (iter)
    {
      ਪੂਰਨ cmp = strcmp (setting->name, iter->setting->name);

      ਜੇ (cmp < 0)
        ਰੋਕੋ;
      ਨਹੀਂਤਾਂ ਜੇ (cmp == 0)
        {
          ਮੁਕਤ (ਗੰਢ);
          ਵਾਪਸ XSETTINGS_DUPLICATE_ਇੰਦਰਾਜ;
        }

      ਆਖਰੀ = iter;
      iter = iter->ਅਗਲਾ;
    }

  ਜੇ (ਆਖਰੀ)
    ਆਖਰੀ->ਅਗਲਾ = ਗੰਢ;
  ਨਹੀਂਤਾਂ
    *list = ਗੰਢ;

  ਗੰਢ->ਅਗਲਾ = iter;

  ਵਾਪਸ XSETTINGS_SUCCESS;
}

XSettings_ਨਤੀਜਾ
xsettings_list_delete (XSettingsList **list,
                       ਅਚਲ ਅੱਖਰ     *name)
{
  XSettingsList *iter;
  XSettingsList *ਆਖਰੀ = ਨਿਰਾ;

  iter = *list;
  ਜਦੋਂ (iter)
    {
      ਜੇ (strcmp (name, iter->setting->name) == 0)
        {
          ਜੇ (ਆਖਰੀ)
            ਆਖਰੀ->ਅਗਲਾ = iter->ਅਗਲਾ;
          ਨਹੀਂਤਾਂ
            *list = iter->ਅਗਲਾ;

          xsettings_setting_free (iter->setting);
          ਮੁਕਤ (iter);

          ਵਾਪਸ XSETTINGS_SUCCESS;
        }

      ਆਖਰੀ = iter;
      iter = iter->ਅਗਲਾ;
    }

  ਵਾਪਸ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ਅਚਲ ਅੱਖਰ    *name)
{
  XSettingsList *iter;

  iter = list;
  ਜਦੋਂ (iter)
    {
      ਜੇ (strcmp (name, iter->setting->name) == 0)
        ਵਾਪਸ iter->setting;

      iter = iter->ਅਗਲਾ;
    }

  ਵਾਪਸ ਨਿਰਾ;
}

ਅੱਖਰ
xsettings_byte_ਕ੍ਰਮ (ਖਾਲੀ)
{
  CARD32 myint = 0x01020304;
  ਵਾਪਸ (*(ਅੱਖਰ *)&myint == 1) ? MSBFirst : LSBFirst;
}

#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11 */

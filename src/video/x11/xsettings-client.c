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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "xsettings-client.h"

ರಚನೆ _XSettingsClient
{
  Display *display;
  ಪೂರ್ಣಾಂಕ screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  ಶೂನ್ಯ *cb_ದತ್ತಾಂಶ;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  ಕಿಟಕಿ_2 manager_ಕಿಟಕಿ;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ಸ್ಥಿರ ಶೂನ್ಯ
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  ಆದರೆ (!client->notify)
    ಹಿಂತಿರುಗಿ;

  ಆಗ (old_iter || new_iter)
    {
      ಪೂರ್ಣಾಂಕ cmp;

      ಆದರೆ (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (old_iter)
        cmp = -1;
      ಇಲ್ಲದಿದ್ದರೆ
        cmp = 1;

      ಆದರೆ (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ಖಾಲಿ,
                          client->cb_ದತ್ತಾಂಶ);
        }
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cmp == 0)
        {
          ಆದರೆ (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_ಬದಲಾಯಿತು,
                            new_iter->setting,
                            client->cb_ದತ್ತಾಂಶ);
        }
      ಇಲ್ಲದಿದ್ದರೆ
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_ದತ್ತಾಂಶ);
        }

      ಆದರೆ (old_iter)
        old_iter = old_iter->ಮುಂದಿನ;
      ಆದರೆ (new_iter)
        new_iter = new_iter->ಮುಂದಿನ;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
ignore_errors (Display *display, XErrorEvent *event)
{
  ಹಿಂತಿರುಗಿ True;
}

ಸ್ಥಿರ ಅಕ್ಷರ local_byte_ಕ್ರಮ = '\0';

#ವ್ಯಾಖ್ಯಾನಿಸು ಬೈಟುಗಳು_ಎಡ_2(ಬಫರ್_2) ((ಬಫರ್_2)->ದತ್ತಾಂಶ + (ಬಫರ್_2)->len - (ಬಫರ್_2)->pos)

ಸ್ಥಿರ XSettings_ಫಲಿತಾಂಶ
fetch_card16 (XSettings_ಬಫರ್ *ಬಫರ್_2,
              CARD16          *ಫಲಿತಾಂಶ)
{
  CARD16 x;

  ಆದರೆ (ಬೈಟುಗಳು_ಎಡ_2 (ಬಫರ್_2) < 2)
    ಹಿಂತಿರುಗಿ XSETTINGS_ACCESS;

  x = *(CARD16 *)ಬಫರ್_2->pos;
  ಬಫರ್_2->pos += 2;

  ಆದರೆ (ಬಫರ್_2->byte_ಕ್ರಮ == local_byte_ಕ್ರಮ)
    *ಫಲಿತಾಂಶ = x;
  ಇಲ್ಲದಿದ್ದರೆ
    *ಫಲಿತಾಂಶ = (x << 8) | (x >> 8);

  ಹಿಂತಿರುಗಿ XSETTINGS_SUCCESS;
}

ಸ್ಥಿರ XSettings_ಫಲಿತಾಂಶ
fetch_ushort (XSettings_ಬಫರ್ *ಬಫರ್_2,
              ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ  *ಫಲಿತಾಂಶ)
{
  CARD16 x;
  XSettings_ಫಲಿತಾಂಶ r;

  r = fetch_card16 (ಬಫರ್_2, &x);
  ಆದರೆ (r == XSETTINGS_SUCCESS)
    *ಫಲಿತಾಂಶ = x;

  ಹಿಂತಿರುಗಿ r;
}

ಸ್ಥಿರ XSettings_ಫಲಿತಾಂಶ
fetch_card32 (XSettings_ಬಫರ್ *ಬಫರ್_2,
              CARD32          *ಫಲಿತಾಂಶ)
{
  CARD32 x;

  ಆದರೆ (ಬೈಟುಗಳು_ಎಡ_2 (ಬಫರ್_2) < 4)
    ಹಿಂತಿರುಗಿ XSETTINGS_ACCESS;

  x = *(CARD32 *)ಬಫರ್_2->pos;
  ಬಫರ್_2->pos += 4;

  ಆದರೆ (ಬಫರ್_2->byte_ಕ್ರಮ == local_byte_ಕ್ರಮ)
    *ಫಲಿತಾಂಶ = x;
  ಇಲ್ಲದಿದ್ದರೆ
    *ಫಲಿತಾಂಶ = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ಹಿಂತಿರುಗಿ XSETTINGS_SUCCESS;
}

ಸ್ಥಿರ XSettings_ಫಲಿತಾಂಶ
fetch_card8 (XSettings_ಬಫರ್ *ಬಫರ್_2,
             CARD8           *ಫಲಿತಾಂಶ)
{
  ಆದರೆ (ಬೈಟುಗಳು_ಎಡ_2 (ಬಫರ್_2) < 1)
    ಹಿಂತಿರುಗಿ XSETTINGS_ACCESS;

  *ಫಲಿತಾಂಶ = *(CARD8 *)ಬಫರ್_2->pos;
  ಬಫರ್_2->pos += 1;

  ಹಿಂತಿರುಗಿ XSETTINGS_SUCCESS;
}

#ವ್ಯಾಖ್ಯಾನಿಸು XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ಸ್ಥಿರ XSettingsList *
parse_settings (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ದತ್ತಾಂಶ,
                size_t         len)
{
  XSettings_ಬಫರ್ ಬಫರ್_2;
  XSettings_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ = XSETTINGS_SUCCESS;
  XSettingsList *settings = ಖಾಲಿ;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ಖಾಲಿ;
  ಅಕ್ಷರ ಬಫರ್_byte_ಕ್ರಮ = '\0';

  local_byte_ಕ್ರಮ = xsettings_byte_ಕ್ರಮ ();

  ಬಫರ್_2.pos = ಬಫರ್_2.ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;
  ಬಫರ್_2.len = len;
  ಬಫರ್_2.byte_ಕ್ರಮ = '\0';

  ಫಲಿತಾಂಶ = fetch_card8 (&ಬಫರ್_2, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) &ಬಫರ್_byte_ಕ್ರಮ);
  ಆದರೆ (ಬಫರ್_byte_ಕ್ರಮ != MSBFirst &&
      ಬಫರ್_byte_ಕ್ರಮ != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      ಫಲಿತಾಂಶ = XSETTINGS_FAILED;
      ಹೋಗು ಹೊರಹೋಗು;
    }

  ಬಫರ್_2.byte_ಕ್ರಮ = ಬಫರ್_byte_ಕ್ರಮ;
  ಬಫರ್_2.pos += 3;

  ಫಲಿತಾಂಶ = fetch_card32 (&ಬಫರ್_2, &serial);
  ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
    ಹೋಗು ಹೊರಹೋಗು;

  ಫಲಿತಾಂಶ = fetch_card32 (&ಬಫರ್_2, &n_entries);
  ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
    ಹೋಗು ಹೊರಹೋಗು;

  ಗಾಗಿ (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      ಫಲಿತಾಂಶ = fetch_card8 (&ಬಫರ್_2, &type);
      ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
        ಹೋಗು ಹೊರಹೋಗು;

      ಬಫರ್_2.pos += 1;

      ಫಲಿತಾಂಶ = fetch_card16 (&ಬಫರ್_2, &name_len);
      ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
        ಹೋಗು ಹೊರಹೋಗು;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ಆದರೆ (ಬೈಟುಗಳು_ಎಡ_2 (&ಬಫರ್_2) < pad_len)
        {
          ಫಲಿತಾಂಶ = XSETTINGS_ACCESS;
          ಹೋಗು ಹೊರಹೋಗು;
        }

      setting = ಸ್ಮರಣೆ_ಕೊಡು (ಗಾತ್ರ *setting);
      ಆದರೆ (!setting)
        {
          ಫಲಿತಾಂಶ = XSETTINGS_NO_MEM;
          ಹೋಗು ಹೊರಹೋಗು;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = ಸ್ಮರಣೆ_ಕೊಡು (name_len + 1);
      ಆದರೆ (!setting->name)
        {
          ಫಲಿತಾಂಶ = XSETTINGS_NO_MEM;
          ಹೋಗು ಹೊರಹೋಗು;
        }

      ಸ್ಮರಣೆ_ನಕಲು (setting->name, ಬಫರ್_2.pos, name_len);
      setting->name[name_len] = '\0';
      ಬಫರ್_2.pos += pad_len;

      ಫಲಿತಾಂಶ = fetch_card32 (&ಬಫರ್_2, &v_int);
      ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
        ಹೋಗು ಹೊರಹೋಗು;
      setting->ಕೊನೆಯ_change_serial = v_int;

      ಆಯ್ಕೆ (type)
        {
        ಸ್ಥಿತಿ XSETTINGS_TYPE_INT:
          ಫಲಿತಾಂಶ = fetch_card32 (&ಬಫರ್_2, &v_int);
          ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
            ಹೋಗು ಹೊರಹೋಗು;

          setting->ದತ್ತಾಂಶ.v_int = (INT32)v_int;
          ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XSETTINGS_TYPE_STRING:
          ಫಲಿತಾಂಶ = fetch_card32 (&ಬಫರ್_2, &v_int);
          ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
            ಹೋಗು ಹೊರಹೋಗು;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ಆದರೆ (v_int + 1 == 0 || /* Guard against wrap-around */
              ಬೈಟುಗಳು_ಎಡ_2 (&ಬಫರ್_2) < pad_len)
            {
              ಫಲಿತಾಂಶ = XSETTINGS_ACCESS;
              ಹೋಗು ಹೊರಹೋಗು;
            }

          setting->ದತ್ತಾಂಶ.v_string = ಸ್ಮರಣೆ_ಕೊಡು (v_int + 1);
          ಆದರೆ (!setting->ದತ್ತಾಂಶ.v_string)
            {
              ಫಲಿತಾಂಶ = XSETTINGS_NO_MEM;
              ಹೋಗು ಹೊರಹೋಗು;
            }

          ಸ್ಮರಣೆ_ನಕಲು (setting->ದತ್ತಾಂಶ.v_string, ಬಫರ್_2.pos, v_int);
          setting->ದತ್ತಾಂಶ.v_string[v_int] = '\0';
          ಬಫರ್_2.pos += pad_len;

          ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XSETTINGS_TYPE_COLOR:
          ಫಲಿತಾಂಶ = fetch_ushort (&ಬಫರ್_2, &setting->ದತ್ತಾಂಶ.v_color.red);
          ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
            ಹೋಗು ಹೊರಹೋಗು;
          ಫಲಿತಾಂಶ = fetch_ushort (&ಬಫರ್_2, &setting->ದತ್ತಾಂಶ.v_color.green);
          ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
            ಹೋಗು ಹೊರಹೋಗು;
          ಫಲಿತಾಂಶ = fetch_ushort (&ಬಫರ್_2, &setting->ದತ್ತಾಂಶ.v_color.blue);
          ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
            ಹೋಗು ಹೊರಹೋಗು;
          ಫಲಿತಾಂಶ = fetch_ushort (&ಬಫರ್_2, &setting->ದತ್ತಾಂಶ.v_color.alpha);
          ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
            ಹೋಗು ಹೊರಹೋಗು;

          ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
          /* Quietly ignore unknown types */
          ನಿಲ್ಲಿಸು;
        }

      setting->type = type;

      ಫಲಿತಾಂಶ = xsettings_list_ಸೇರಿಸು (&settings, setting);
      ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
        ಹೋಗು ಹೊರಹೋಗು;

      setting = ಖಾಲಿ;
    }

 ಹೊರಹೋಗು:

  ಆದರೆ (ಫಲಿತಾಂಶ != XSETTINGS_SUCCESS)
    {
      ಆಯ್ಕೆ (ಫಲಿತಾಂಶ)
        {
        ಸ್ಥಿತಿ XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XSETTINGS_DUPLICATE_ನಮೂದು:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ XSETTINGS_NO_ನಮೂದು:
          ನಿಲ್ಲಿಸು;
        }

      ಆದರೆ (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ಖಾಲಿ;

    }

  ಹಿಂತಿರುಗಿ settings;
}

ಸ್ಥಿರ ಶೂನ್ಯ
read_settings (XSettingsClient *client)
{
  Atom type;
  ಪೂರ್ಣಾಂಕ format;
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ n_ವಸ್ತುಗಳು;
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬೈಟುಗಳು_after;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ದತ್ತಾಂಶ;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;

  ಪೂರ್ಣಾಂಕ (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ಖಾಲಿ;

  ಆದರೆ (client->manager_ಕಿಟಕಿ)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      ಫಲಿತಾಂಶ = X11_XGet_ಕಿಟಕಿ_Property (client->display, client->manager_ಕಿಟಕಿ,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_ವಸ್ತುಗಳು, &ಬೈಟುಗಳು_after, &ದತ್ತಾಂಶ);
      X11_XSetErrorHandler (old_handler);

      ಆದರೆ (ಫಲಿತಾಂಶ == Success && type != None)
        {
          ಆದರೆ (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          ಇಲ್ಲದಿದ್ದರೆ
            client->settings = parse_settings (ದತ್ತಾಂಶ, n_ವಸ್ತುಗಳು);

          X11_XFree (ದತ್ತಾಂಶ);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ಸ್ಥಿರ ಶೂನ್ಯ
ಕೂಡಿಸು_events (Display *display,
            ಕಿಟಕಿ_2   ಕಿಟಕಿ,
            ದೀರ್ಘ     ಮುಖವಾಡ)
{
  XWindow_ಗುಣಲಕ್ಷಣಗಳು attr;

  X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು (display, ಕಿಟಕಿ, &attr);
  X11_XSelect_ಒಳಹರಿವು (display, ಕಿಟಕಿ, attr.your_event_ಮುಖವಾಡ | ಮುಖವಾಡ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check_manager_ಕಿಟಕಿ (XSettingsClient *client)
{
  ಆದರೆ (client->manager_ಕಿಟಕಿ && client->watch)
    client->watch (client->manager_ಕಿಟಕಿ, False, 0, client->cb_ದತ್ತಾಂಶ);

  ಆದರೆ (client->grab)
    client->grab (client->display);
  ಇಲ್ಲದಿದ್ದರೆ
    X11_XGrabServer (client->display);

  client->manager_ಕಿಟಕಿ = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ಆದರೆ (client->manager_ಕಿಟಕಿ)
    X11_XSelect_ಒಳಹರಿವು (client->display, client->manager_ಕಿಟಕಿ,
                      Property_Change_ಮುಖವಾಡ | Structure_Notify_ಮುಖವಾಡ);

  ಆದರೆ (client->ungrab)
    client->ungrab (client->display);
  ಇಲ್ಲದಿದ್ದರೆ
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ಆದರೆ (client->manager_ಕಿಟಕಿ && client->watch)
    {
      ಆದರೆ (!client->watch (client->manager_ಕಿಟಕಿ, True,
                          Property_Change_ಮುಖವಾಡ | Structure_Notify_ಮುಖವಾಡ,
                          client->cb_ದತ್ತಾಂಶ))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_ಕಿಟಕಿ = None;
          ಹಿಂತಿರುಗಿ;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      ಪೂರ್ಣಾಂಕ                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      ಶೂನ್ಯ                *cb_ದತ್ತಾಂಶ)
{
  ಹಿಂತಿರುಗಿ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_ದತ್ತಾಂಶ,
                                               ಖಾಲಿ, ಖಾಲಿ);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      ಪೂರ್ಣಾಂಕ                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      ಶೂನ್ಯ                *cb_ದತ್ತಾಂಶ,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  ಅಕ್ಷರ ಬಫರ್_2[256];
  ಅಕ್ಷರ *atom_ಹೆಸರುಗಳು[3];
  Atom atoms[3];

  client = ಸ್ಮರಣೆ_ಕೊಡು (ಗಾತ್ರ *client);
  ಆದರೆ (!client)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_ದತ್ತಾಂಶ = cb_ದತ್ತಾಂಶ;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_ಕಿಟಕಿ = None;
  client->settings = ಖಾಲಿ;

  SDL_snprintf(ಬಫರ್_2, ಗಾತ್ರ(ಬಫರ್_2), "_XSETTINGS_S%d", screen);
  atom_ಹೆಸರುಗಳು[0] = ಬಫರ್_2;
  atom_ಹೆಸರುಗಳು[1] = "_XSETTINGS_SETTINGS";
  atom_ಹೆಸರುಗಳು[2] = "MANAGER";

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_XINTERNATOMS
  XInternAtoms (display, atom_ಹೆಸರುಗಳು, 3, False, atoms);
#ಇಲ್ಲದಿದ್ದರೆ
  atoms[0] = X11_XInternAtom (display, atom_ಹೆಸರುಗಳು[0], False);
  atoms[1] = X11_XInternAtom (display, atom_ಹೆಸರುಗಳು[1], False);
  atoms[2] = X11_XInternAtom (display, atom_ಹೆಸರುಗಳು[2], False);
#ಆದರೆ_ಅಂತ್ಯ

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  ಕೂಡಿಸು_events (display, ಬೇರು_ಕಿಟಕಿ (display, screen), Structure_Notify_ಮುಖವಾಡ);

  ಆದರೆ (client->watch)
    client->watch (ಬೇರು_ಕಿಟಕಿ (display, screen), True, Structure_Notify_ಮುಖವಾಡ,
                   client->cb_ದತ್ತಾಂಶ);

  check_manager_ಕಿಟಕಿ (client);

  ಹಿಂತಿರುಗಿ client;
}


ಶೂನ್ಯ
xsettings_client_ಗಣ_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

ಶೂನ್ಯ
xsettings_client_ಗಣ_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

ಶೂನ್ಯ
xsettings_client_destroy (XSettingsClient *client)
{
  ಆದರೆ (client->watch)
    client->watch (ಬೇರು_ಕಿಟಕಿ (client->display, client->screen),
                   False, 0, client->cb_ದತ್ತಾಂಶ);
  ಆದರೆ (client->manager_ಕಿಟಕಿ && client->watch)
    client->watch (client->manager_ಕಿಟಕಿ, False, 0, client->cb_ದತ್ತಾಂಶ);

  xsettings_list_free (client->settings);
  ಬಿಡುಗಡೆ (client);
}

XSettings_ಫಲಿತಾಂಶ
xsettings_client_get_setting (XSettingsClient   *client,
                              ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *ಹುಡುಕು = xsettings_list_lookup (client->settings, name);
  ಆದರೆ (ಹುಡುಕು)
    {
      *setting = xsettings_setting_copy (ಹುಡುಕು);
      ಹಿಂತಿರುಗಿ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ XSETTINGS_NO_ನಮೂದು;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ಸ್ಥಿರಾಂಕ XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ಆದರೆ (xev->xany.ಕಿಟಕಿ == ಬೇರು_ಕಿಟಕಿ (client->display, client->screen))
    {
      ಆದರೆ (xev->xany.type == Client_ಸಂದೇಶ &&
          xev->xclient.ಸಂದೇಶ_type == client->manager_atom &&
          xev->xclient.ದತ್ತಾಂಶ.l[1] == client->selection_atom)
        {
          check_manager_ಕಿಟಕಿ (client);
          ಹಿಂತಿರುಗಿ True;
        }
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xev->xany.ಕಿಟಕಿ == client->manager_ಕಿಟಕಿ)
    {
      ಆದರೆ (xev->xany.type == DestroyNotify)
        {
          check_manager_ಕಿಟಕಿ (client);
          ಹಿಂತಿರುಗಿ False;
        }
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ಹಿಂತಿರುಗಿ True;
        }
    }

  ಹಿಂತಿರುಗಿ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *ಫಲಿತಾಂಶ;
  size_t str_len;

  ಫಲಿತಾಂಶ = ಸ್ಮರಣೆ_ಕೊಡು (ಗಾತ್ರ *ಫಲಿತಾಂಶ);
  ಆದರೆ (!ಫಲಿತಾಂಶ)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  str_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (setting->name);
  ಫಲಿತಾಂಶ->name = ಸ್ಮರಣೆ_ಕೊಡು (str_len + 1);
  ಆದರೆ (!ಫಲಿತಾಂಶ->name)
    ಹೋಗು err;

  ಸ್ಮರಣೆ_ನಕಲು (ಫಲಿತಾಂಶ->name, setting->name, str_len + 1);

  ಫಲಿತಾಂಶ->type = setting->type;

  ಆಯ್ಕೆ (setting->type)
    {
    ಸ್ಥಿತಿ XSETTINGS_TYPE_INT:
      ಫಲಿತಾಂಶ->ದತ್ತಾಂಶ.v_int = setting->ದತ್ತಾಂಶ.v_int;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ XSETTINGS_TYPE_COLOR:
      ಫಲಿತಾಂಶ->ದತ್ತಾಂಶ.v_color = setting->ದತ್ತಾಂಶ.v_color;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ XSETTINGS_TYPE_STRING:
      str_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (setting->ದತ್ತಾಂಶ.v_string);
      ಫಲಿತಾಂಶ->ದತ್ತಾಂಶ.v_string = ಸ್ಮರಣೆ_ಕೊಡು (str_len + 1);
      ಆದರೆ (!ಫಲಿತಾಂಶ->ದತ್ತಾಂಶ.v_string)
        ಹೋಗು err;

      ಸ್ಮರಣೆ_ನಕಲು (ಫಲಿತಾಂಶ->ದತ್ತಾಂಶ.v_string, setting->ದತ್ತಾಂಶ.v_string, str_len + 1);
      ನಿಲ್ಲಿಸು;
    }

  ಫಲಿತಾಂಶ->ಕೊನೆಯ_change_serial = setting->ಕೊನೆಯ_change_serial;

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;

 err:
  ಬಿಡುಗಡೆ(ಫಲಿತಾಂಶ->name); // This should NOT be SDL_free()
  ಬಿಡುಗಡೆ(ಫಲಿತಾಂಶ); // This should NOT be SDL_free()

  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ಖಾಲಿ;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ಖಾಲಿ;

  ಆಗ (old_iter)
    {
      XSettingsList *new_ಗಂಟು;

      new_ಗಂಟು = ಸ್ಮರಣೆ_ಕೊಡು (ಗಾತ್ರ *new_ಗಂಟು);
      ಆದರೆ (!new_ಗಂಟು)
        ಹೋಗು error;

      new_ಗಂಟು->setting = xsettings_setting_copy (old_iter->setting);
      ಆದರೆ (!new_ಗಂಟು->setting)
        {
          ಬಿಡುಗಡೆ (new_ಗಂಟು);
          ಹೋಗು error;
        }

      ಆದರೆ (new_iter)
        new_iter->ಮುಂದಿನ = new_ಗಂಟು;
      ಇಲ್ಲದಿದ್ದರೆ
        {
          new = new_ಗಂಟು;
          new->ಮುಂದಿನ = ಖಾಲಿ;
        }


      new_iter = new_ಗಂಟು;

      old_iter = old_iter->ಮುಂದಿನ;
    }

  ಹಿಂತಿರುಗಿ new;

 error:
  xsettings_list_free (new);
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ಆದರೆ (setting_a->type != setting_b->type)
    ಹಿಂತಿರುಗಿ 0;

  ಆದರೆ (strcmp (setting_a->name, setting_b->name) != 0)
    ಹಿಂತಿರುಗಿ 0;

  ಆಯ್ಕೆ (setting_a->type)
    {
    ಸ್ಥಿತಿ XSETTINGS_TYPE_INT:
      ಹಿಂತಿರುಗಿ setting_a->ದತ್ತಾಂಶ.v_int == setting_b->ದತ್ತಾಂಶ.v_int;
    ಸ್ಥಿತಿ XSETTINGS_TYPE_COLOR:
      ಹಿಂತಿರುಗಿ (setting_a->ದತ್ತಾಂಶ.v_color.red == setting_b->ದತ್ತಾಂಶ.v_color.red &&
              setting_a->ದತ್ತಾಂಶ.v_color.green == setting_b->ದತ್ತಾಂಶ.v_color.green &&
              setting_a->ದತ್ತಾಂಶ.v_color.blue == setting_b->ದತ್ತಾಂಶ.v_color.blue &&
              setting_a->ದತ್ತಾಂಶ.v_color.alpha == setting_b->ದತ್ತಾಂಶ.v_color.alpha);
    ಸ್ಥಿತಿ XSETTINGS_TYPE_STRING:
      ಹಿಂತಿರುಗಿ strcmp (setting_a->ದತ್ತಾಂಶ.v_string, setting_b->ದತ್ತಾಂಶ.v_string) == 0;
    }

  ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ
xsettings_setting_free (XSettingsSetting *setting)
{
  ಆದರೆ (setting->type == XSETTINGS_TYPE_STRING)
    ಬಿಡುಗಡೆ (setting->ದತ್ತಾಂಶ.v_string);

  ಬಿಡುಗಡೆ(setting->name); // This should NOT be SDL_free()
  ಬಿಡುಗಡೆ(setting); // This should NOT be SDL_free()
}

ಶೂನ್ಯ
xsettings_list_free (XSettingsList *list)
{
  ಆಗ (list)
    {
      XSettingsList *ಮುಂದಿನ = list->ಮುಂದಿನ;

      xsettings_setting_free (list->setting);
      ಬಿಡುಗಡೆ (list);

      list = ಮುಂದಿನ;
    }
}

XSettings_ಫಲಿತಾಂಶ
xsettings_list_ಸೇರಿಸು (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ಗಂಟು;
  XSettingsList *iter;
  XSettingsList *ಕೊನೆಯ = ಖಾಲಿ;

  ಗಂಟು = ಸ್ಮರಣೆ_ಕೊಡು (ಗಾತ್ರ *ಗಂಟು);
  ಆದರೆ (!ಗಂಟು)
    ಹಿಂತಿರುಗಿ XSETTINGS_NO_MEM;
  ಗಂಟು->setting = setting;

  iter = *list;
  ಆಗ (iter)
    {
      ಪೂರ್ಣಾಂಕ cmp = strcmp (setting->name, iter->setting->name);

      ಆದರೆ (cmp < 0)
        ನಿಲ್ಲಿಸು;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cmp == 0)
        {
          ಬಿಡುಗಡೆ (ಗಂಟು);
          ಹಿಂತಿರುಗಿ XSETTINGS_DUPLICATE_ನಮೂದು;
        }

      ಕೊನೆಯ = iter;
      iter = iter->ಮುಂದಿನ;
    }

  ಆದರೆ (ಕೊನೆಯ)
    ಕೊನೆಯ->ಮುಂದಿನ = ಗಂಟು;
  ಇಲ್ಲದಿದ್ದರೆ
    *list = ಗಂಟು;

  ಗಂಟು->ಮುಂದಿನ = iter;

  ಹಿಂತಿರುಗಿ XSETTINGS_SUCCESS;
}

XSettings_ಫಲಿತಾಂಶ
xsettings_list_delete (XSettingsList **list,
                       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ     *name)
{
  XSettingsList *iter;
  XSettingsList *ಕೊನೆಯ = ಖಾಲಿ;

  iter = *list;
  ಆಗ (iter)
    {
      ಆದರೆ (strcmp (name, iter->setting->name) == 0)
        {
          ಆದರೆ (ಕೊನೆಯ)
            ಕೊನೆಯ->ಮುಂದಿನ = iter->ಮುಂದಿನ;
          ಇಲ್ಲದಿದ್ದರೆ
            *list = iter->ಮುಂದಿನ;

          xsettings_setting_free (iter->setting);
          ಬಿಡುಗಡೆ (iter);

          ಹಿಂತಿರುಗಿ XSETTINGS_SUCCESS;
        }

      ಕೊನೆಯ = iter;
      iter = iter->ಮುಂದಿನ;
    }

  ಹಿಂತಿರುಗಿ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ    *name)
{
  XSettingsList *iter;

  iter = list;
  ಆಗ (iter)
    {
      ಆದರೆ (strcmp (name, iter->setting->name) == 0)
        ಹಿಂತಿರುಗಿ iter->setting;

      iter = iter->ಮುಂದಿನ;
    }

  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಅಕ್ಷರ
xsettings_byte_ಕ್ರಮ (ಶೂನ್ಯ)
{
  CARD32 myint = 0x01020304;
  ಹಿಂತಿರುಗಿ (*(ಅಕ್ಷರ *)&myint == 1) ? MSBFirst : LSBFirst;
}

#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11 */

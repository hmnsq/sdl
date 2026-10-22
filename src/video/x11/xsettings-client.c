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

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "xsettings-client.h"

ಸಂರಚನಾ _XSettingsClient
{
  Display *display;
  ಪೂರ್ಣಾಙ್ಕ screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  ಶೂನ್ಯ *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
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

  ಯದಿ (!client->notify)
    ಪ್ರತ್ಯಾಗಮ;

  ಯಾವತ್ (old_iter || new_iter)
    {
      ಪೂರ್ಣಾಙ್ಕ cmp;

      ಯದಿ (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      ಅನ್ಯಥಾ ಯದಿ (old_iter)
        cmp = -1;
      ಅನ್ಯಥಾ
        cmp = 1;

      ಯದಿ (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ರಿಕ್ತ,
                          client->cb_data);
        }
      ಅನ್ಯಥಾ ಯದಿ (cmp == 0)
        {
          ಯದಿ (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      ಅನ್ಯಥಾ
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      ಯದಿ (old_iter)
        old_iter = old_iter->next;
      ಯದಿ (new_iter)
        new_iter = new_iter->next;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
ignore_errors (Display *display, XErrorEvent *event)
{
  ಪ್ರತ್ಯಾಗಮ True;
}

ಸ್ಥಿರ ವರ್ಣ local_byte_order = '\0';

#define BYTES_ಎಡ(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

ಸ್ಥಿರ XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  ಯದಿ (BYTES_ಎಡ (buffer) < 2)
    ಪ್ರತ್ಯಾಗಮ XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  ಯದಿ (buffer->byte_order == local_byte_order)
    *result = x;
  ಅನ್ಯಥಾ
    *result = (x << 8) | (x >> 8);

  ಪ್ರತ್ಯಾಗಮ XSETTINGS_SUCCESS;
}

ಸ್ಥಿರ XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  ಯದಿ (r == XSETTINGS_SUCCESS)
    *result = x;

  ಪ್ರತ್ಯಾಗಮ r;
}

ಸ್ಥಿರ XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  ಯದಿ (BYTES_ಎಡ (buffer) < 4)
    ಪ್ರತ್ಯಾಗಮ XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  ಯದಿ (buffer->byte_order == local_byte_order)
    *result = x;
  ಅನ್ಯಥಾ
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ಪ್ರತ್ಯಾಗಮ XSETTINGS_SUCCESS;
}

ಸ್ಥಿರ XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  ಯದಿ (BYTES_ಎಡ (buffer) < 1)
    ಪ್ರತ್ಯಾಗಮ XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  ಪ್ರತ್ಯಾಗಮ XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ಸ್ಥಿರ XSettingsList *
parse_settings (unsigned ವರ್ಣ *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = ರಿಕ್ತ;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ರಿಕ್ತ;
  ವರ್ಣ buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned ವರ್ಣ *) &buffer_byte_order);
  ಯದಿ (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      ಗಚ್ಛ out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  ಯದಿ (result != XSETTINGS_SUCCESS)
    ಗಚ್ಛ out;

  result = fetch_card32 (&buffer, &n_entries);
  ಯದಿ (result != XSETTINGS_SUCCESS)
    ಗಚ್ಛ out;

  ಪ್ರತಿ (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      ಯದಿ (result != XSETTINGS_SUCCESS)
        ಗಚ್ಛ out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      ಯದಿ (result != XSETTINGS_SUCCESS)
        ಗಚ್ಛ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ಯದಿ (BYTES_ಎಡ (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          ಗಚ್ಛ out;
        }

      setting = malloc (ಪರಿಮಾಣ *setting);
      ಯದಿ (!setting)
        {
          result = XSETTINGS_NO_MEM;
          ಗಚ್ಛ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      ಯದಿ (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          ಗಚ್ಛ out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      ಯದಿ (result != XSETTINGS_SUCCESS)
        ಗಚ್ಛ out;
      setting->last_change_serial = v_int;

      ವಿಕಲ್ಪ (type)
        {
        ಪಕ್ಷ XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          ಯದಿ (result != XSETTINGS_SUCCESS)
            ಗಚ್ಛ out;

          setting->data.v_int = (INT32)v_int;
          ಭಙ್ಗ;
        ಪಕ್ಷ XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          ಯದಿ (result != XSETTINGS_SUCCESS)
            ಗಚ್ಛ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ಯದಿ (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_ಎಡ (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              ಗಚ್ಛ out;
            }

          setting->data.v_string = malloc (v_int + 1);
          ಯದಿ (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              ಗಚ್ಛ out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          ಭಙ್ಗ;
        ಪಕ್ಷ XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          ಯದಿ (result != XSETTINGS_SUCCESS)
            ಗಚ್ಛ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          ಯದಿ (result != XSETTINGS_SUCCESS)
            ಗಚ್ಛ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          ಯದಿ (result != XSETTINGS_SUCCESS)
            ಗಚ್ಛ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          ಯದಿ (result != XSETTINGS_SUCCESS)
            ಗಚ್ಛ out;

          ಭಙ್ಗ;
        ಸ್ವಭಾವ:
          /* Quietly ignore unknown types */
          ಭಙ್ಗ;
        }

      setting->type = type;

      result = xsettings_list_ಸೇರಿಸು (&settings, setting);
      ಯದಿ (result != XSETTINGS_SUCCESS)
        ಗಚ್ಛ out;

      setting = ರಿಕ್ತ;
    }

 out:

  ಯದಿ (result != XSETTINGS_SUCCESS)
    {
      ವಿಕಲ್ಪ (result)
        {
        ಪಕ್ಷ XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          ಭಙ್ಗ;
        ಪಕ್ಷ XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          ಭಙ್ಗ;
        ಪಕ್ಷ XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        ಪಕ್ಷ XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        ಪಕ್ಷ XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        ಪಕ್ಷ XSETTINGS_NO_ENTRY:
          ಭಙ್ಗ;
        }

      ಯದಿ (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ರಿಕ್ತ;

    }

  ಪ್ರತ್ಯಾಗಮ settings;
}

ಸ್ಥಿರ ಶೂನ್ಯ
read_settings (XSettingsClient *client)
{
  Atom type;
  ಪೂರ್ಣಾಙ್ಕ format;
  unsigned long n_ವಸ್ತುಗಳು;
  unsigned long bytes_after;
  unsigned ವರ್ಣ *data;
  ಪೂರ್ಣಾಙ್ಕ result;

  ಪೂರ್ಣಾಙ್ಕ (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ರಿಕ್ತ;

  ಯದಿ (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_ವಸ್ತುಗಳು, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      ಯದಿ (result == Success && type != None)
        {
          ಯದಿ (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          ಅನ್ಯಥಾ ಯದಿ (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          ಅನ್ಯಥಾ
            client->settings = parse_settings (data, n_ವಸ್ತುಗಳು);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ಸ್ಥಿರ ಶೂನ್ಯ
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_ಒಳಹರಿವು (display, window, attr.your_event_mask | mask);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check_manager_window (XSettingsClient *client)
{
  ಯದಿ (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  ಯದಿ (client->grab)
    client->grab (client->display);
  ಅನ್ಯಥಾ
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ಯದಿ (client->manager_window)
    X11_XSelect_ಒಳಹರಿವು (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  ಯದಿ (client->ungrab)
    client->ungrab (client->display);
  ಅನ್ಯಥಾ
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ಯದಿ (client->manager_window && client->watch)
    {
      ಯದಿ (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          ಪ್ರತ್ಯಾಗಮ;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      ಪೂರ್ಣಾಙ್ಕ                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      ಶೂನ್ಯ                *cb_data)
{
  ಪ್ರತ್ಯಾಗಮ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               ರಿಕ್ತ, ರಿಕ್ತ);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      ಪೂರ್ಣಾಙ್ಕ                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      ಶೂನ್ಯ                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  ವರ್ಣ buffer[256];
  ವರ್ಣ *atom_names[3];
  Atom atoms[3];

  client = malloc (ಪರಿಮಾಣ *client);
  ಯದಿ (!client)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = ರಿಕ್ತ;

  SDL_snprintf(buffer, ಪರಿಮಾಣ(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#ಅನ್ಯಥಾ
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, ಬೇರು_Window (display, screen), StructureNotifyMask);

  ಯದಿ (client->watch)
    client->watch (ಬೇರು_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  ಪ್ರತ್ಯಾಗಮ client;
}


ಶೂನ್ಯ
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

ಶೂನ್ಯ
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

ಶೂನ್ಯ
xsettings_client_destroy (XSettingsClient *client)
{
  ಯದಿ (client->watch)
    client->watch (ಬೇರು_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  ಯದಿ (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  ಮುಕ್ತ (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              ಧ್ರುವ ವರ್ಣ        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *ಹುಡುಕು = xsettings_list_lookup (client->settings, name);
  ಯದಿ (ಹುಡುಕು)
    {
      *setting = xsettings_setting_copy (ಹುಡುಕು);
      ಪ್ರತ್ಯಾಗಮ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ಧ್ರುವ XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ಯದಿ (xev->xany.window == ಬೇರು_Window (client->display, client->screen))
    {
      ಯದಿ (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          ಪ್ರತ್ಯಾಗಮ True;
        }
    }
  ಅನ್ಯಥಾ ಯದಿ (xev->xany.window == client->manager_window)
    {
      ಯದಿ (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          ಪ್ರತ್ಯಾಗಮ False;
        }
      ಅನ್ಯಥಾ ಯದಿ (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ಪ್ರತ್ಯಾಗಮ True;
        }
    }

  ಪ್ರತ್ಯಾಗಮ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (ಪರಿಮಾಣ *result);
  ಯದಿ (!result)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  ಯದಿ (!result->name)
    ಗಚ್ಛ err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  ವಿಕಲ್ಪ (setting->type)
    {
    ಪಕ್ಷ XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      ಭಙ್ಗ;
    ಪಕ್ಷ XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      ಭಙ್ಗ;
    ಪಕ್ಷ XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      ಯದಿ (!result->data.v_string)
        ಗಚ್ಛ err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      ಭಙ್ಗ;
    }

  result->last_change_serial = setting->last_change_serial;

  ಪ್ರತ್ಯಾಗಮ result;

 err:
  ಮುಕ್ತ(result->name); // This should NOT be SDL_free()
  ಮುಕ್ತ(result); // This should NOT be SDL_free()

  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ರಿಕ್ತ;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ರಿಕ್ತ;

  ಯಾವತ್ (old_iter)
    {
      XSettingsList *new_ಗಂಟು;

      new_ಗಂಟು = malloc (ಪರಿಮಾಣ *new_ಗಂಟು);
      ಯದಿ (!new_ಗಂಟು)
        ಗಚ್ಛ error;

      new_ಗಂಟು->setting = xsettings_setting_copy (old_iter->setting);
      ಯದಿ (!new_ಗಂಟು->setting)
        {
          ಮುಕ್ತ (new_ಗಂಟು);
          ಗಚ್ಛ error;
        }

      ಯದಿ (new_iter)
        new_iter->next = new_ಗಂಟು;
      ಅನ್ಯಥಾ
        {
          new = new_ಗಂಟು;
          new->next = ರಿಕ್ತ;
        }


      new_iter = new_ಗಂಟು;

      old_iter = old_iter->next;
    }

  ಪ್ರತ್ಯಾಗಮ new;

 error:
  xsettings_list_free (new);
  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಪೂರ್ಣಾಙ್ಕ
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ಯದಿ (setting_a->type != setting_b->type)
    ಪ್ರತ್ಯಾಗಮ 0;

  ಯದಿ (strcmp (setting_a->name, setting_b->name) != 0)
    ಪ್ರತ್ಯಾಗಮ 0;

  ವಿಕಲ್ಪ (setting_a->type)
    {
    ಪಕ್ಷ XSETTINGS_TYPE_INT:
      ಪ್ರತ್ಯಾಗಮ setting_a->data.v_int == setting_b->data.v_int;
    ಪಕ್ಷ XSETTINGS_TYPE_COLOR:
      ಪ್ರತ್ಯಾಗಮ (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    ಪಕ್ಷ XSETTINGS_TYPE_STRING:
      ಪ್ರತ್ಯಾಗಮ strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ
xsettings_setting_free (XSettingsSetting *setting)
{
  ಯದಿ (setting->type == XSETTINGS_TYPE_STRING)
    ಮುಕ್ತ (setting->data.v_string);

  ಮುಕ್ತ(setting->name); // This should NOT be SDL_free()
  ಮುಕ್ತ(setting); // This should NOT be SDL_free()
}

ಶೂನ್ಯ
xsettings_list_free (XSettingsList *list)
{
  ಯಾವತ್ (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      ಮುಕ್ತ (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_ಸೇರಿಸು (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ಗಂಟು;
  XSettingsList *iter;
  XSettingsList *last = ರಿಕ್ತ;

  ಗಂಟು = malloc (ಪರಿಮಾಣ *ಗಂಟು);
  ಯದಿ (!ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ XSETTINGS_NO_MEM;
  ಗಂಟು->setting = setting;

  iter = *list;
  ಯಾವತ್ (iter)
    {
      ಪೂರ್ಣಾಙ್ಕ cmp = strcmp (setting->name, iter->setting->name);

      ಯದಿ (cmp < 0)
        ಭಙ್ಗ;
      ಅನ್ಯಥಾ ಯದಿ (cmp == 0)
        {
          ಮುಕ್ತ (ಗಂಟು);
          ಪ್ರತ್ಯಾಗಮ XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  ಯದಿ (last)
    last->next = ಗಂಟು;
  ಅನ್ಯಥಾ
    *list = ಗಂಟು;

  ಗಂಟು->next = iter;

  ಪ್ರತ್ಯಾಗಮ XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       ಧ್ರುವ ವರ್ಣ     *name)
{
  XSettingsList *iter;
  XSettingsList *last = ರಿಕ್ತ;

  iter = *list;
  ಯಾವತ್ (iter)
    {
      ಯದಿ (strcmp (name, iter->setting->name) == 0)
        {
          ಯದಿ (last)
            last->next = iter->next;
          ಅನ್ಯಥಾ
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          ಮುಕ್ತ (iter);

          ಪ್ರತ್ಯಾಗಮ XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  ಪ್ರತ್ಯಾಗಮ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ಧ್ರುವ ವರ್ಣ    *name)
{
  XSettingsList *iter;

  iter = list;
  ಯಾವತ್ (iter)
    {
      ಯದಿ (strcmp (name, iter->setting->name) == 0)
        ಪ್ರತ್ಯಾಗಮ iter->setting;

      iter = iter->next;
    }

  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ವರ್ಣ
xsettings_byte_order (ಶೂನ್ಯ)
{
  CARD32 myint = 0x01020304;
  ಪ್ರತ್ಯಾಗಮ (*(ವರ್ಣ *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "SDL_x11video.h"

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "xsettings-client.h"

ഘടന _XSettingsClient
{
  Display *display;
  പൂർണ്ണസംഖ്യ screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  ശൂന്യം *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

സ്ഥിതം ശൂന്യം
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  എങ്കിൽ (!client->notify)
    തിരികെ;

  ആകുമ്പോൾ (old_iter || new_iter)
    {
      പൂർണ്ണസംഖ്യ cmp;

      എങ്കിൽ (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      അല്ലെങ്കിൽ എങ്കിൽ (old_iter)
        cmp = -1;
      അല്ലെങ്കിൽ
        cmp = 1;

      എങ്കിൽ (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ശൂന്യ,
                          client->cb_data);
        }
      അല്ലെങ്കിൽ എങ്കിൽ (cmp == 0)
        {
          എങ്കിൽ (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      അല്ലെങ്കിൽ
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      എങ്കിൽ (old_iter)
        old_iter = old_iter->next;
      എങ്കിൽ (new_iter)
        new_iter = new_iter->next;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
ignore_errors (Display *display, XErrorEvent *event)
{
  തിരികെ True;
}

സ്ഥിതം അക്ഷരം local_byte_order = '\0';

#define BYTES_ഇടത്(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

സ്ഥിതം XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  എങ്കിൽ (BYTES_ഇടത് (buffer) < 2)
    തിരികെ XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  എങ്കിൽ (buffer->byte_order == local_byte_order)
    *result = x;
  അല്ലെങ്കിൽ
    *result = (x << 8) | (x >> 8);

  തിരികെ XSETTINGS_SUCCESS;
}

സ്ഥിതം XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  എങ്കിൽ (r == XSETTINGS_SUCCESS)
    *result = x;

  തിരികെ r;
}

സ്ഥിതം XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  എങ്കിൽ (BYTES_ഇടത് (buffer) < 4)
    തിരികെ XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  എങ്കിൽ (buffer->byte_order == local_byte_order)
    *result = x;
  അല്ലെങ്കിൽ
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  തിരികെ XSETTINGS_SUCCESS;
}

സ്ഥിതം XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  എങ്കിൽ (BYTES_ഇടത് (buffer) < 1)
    തിരികെ XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  തിരികെ XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

സ്ഥിതം XSettingsList *
parse_settings (unsigned അക്ഷരം *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = ശൂന്യ;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ശൂന്യ;
  അക്ഷരം buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned അക്ഷരം *) &buffer_byte_order);
  എങ്കിൽ (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      പോകുക out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  എങ്കിൽ (result != XSETTINGS_SUCCESS)
    പോകുക out;

  result = fetch_card32 (&buffer, &n_entries);
  എങ്കിൽ (result != XSETTINGS_SUCCESS)
    പോകുക out;

  വേണ്ടി (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      എങ്കിൽ (result != XSETTINGS_SUCCESS)
        പോകുക out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      എങ്കിൽ (result != XSETTINGS_SUCCESS)
        പോകുക out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      എങ്കിൽ (BYTES_ഇടത് (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          പോകുക out;
        }

      setting = malloc (വലുപ്പം *setting);
      എങ്കിൽ (!setting)
        {
          result = XSETTINGS_NO_MEM;
          പോകുക out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      എങ്കിൽ (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          പോകുക out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      എങ്കിൽ (result != XSETTINGS_SUCCESS)
        പോകുക out;
      setting->last_change_serial = v_int;

      തിരഞ്ഞെടുപ്പ് (type)
        {
        അവസ്ഥ XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          എങ്കിൽ (result != XSETTINGS_SUCCESS)
            പോകുക out;

          setting->data.v_int = (INT32)v_int;
          നിർത്തുക;
        അവസ്ഥ XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          എങ്കിൽ (result != XSETTINGS_SUCCESS)
            പോകുക out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          എങ്കിൽ (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_ഇടത് (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              പോകുക out;
            }

          setting->data.v_string = malloc (v_int + 1);
          എങ്കിൽ (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              പോകുക out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          നിർത്തുക;
        അവസ്ഥ XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          എങ്കിൽ (result != XSETTINGS_SUCCESS)
            പോകുക out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          എങ്കിൽ (result != XSETTINGS_SUCCESS)
            പോകുക out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          എങ്കിൽ (result != XSETTINGS_SUCCESS)
            പോകുക out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          എങ്കിൽ (result != XSETTINGS_SUCCESS)
            പോകുക out;

          നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
          /* Quietly ignore unknown types */
          നിർത്തുക;
        }

      setting->type = type;

      result = xsettings_list_തിരുകുക (&settings, setting);
      എങ്കിൽ (result != XSETTINGS_SUCCESS)
        പോകുക out;

      setting = ശൂന്യ;
    }

 out:

  എങ്കിൽ (result != XSETTINGS_SUCCESS)
    {
      തിരഞ്ഞെടുപ്പ് (result)
        {
        അവസ്ഥ XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          നിർത്തുക;
        അവസ്ഥ XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          നിർത്തുക;
        അവസ്ഥ XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        അവസ്ഥ XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        അവസ്ഥ XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        അവസ്ഥ XSETTINGS_NO_ENTRY:
          നിർത്തുക;
        }

      എങ്കിൽ (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ശൂന്യ;

    }

  തിരികെ settings;
}

സ്ഥിതം ശൂന്യം
read_settings (XSettingsClient *client)
{
  Atom type;
  പൂർണ്ണസംഖ്യ format;
  unsigned long n_ഇനങ്ങൾ;
  unsigned long bytes_after;
  unsigned അക്ഷരം *data;
  പൂർണ്ണസംഖ്യ result;

  പൂർണ്ണസംഖ്യ (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ശൂന്യ;

  എങ്കിൽ (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_ഇനങ്ങൾ, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      എങ്കിൽ (result == Success && type != None)
        {
          എങ്കിൽ (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          അല്ലെങ്കിൽ എങ്കിൽ (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          അല്ലെങ്കിൽ
            client->settings = parse_settings (data, n_ഇനങ്ങൾ);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

സ്ഥിതം ശൂന്യം
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_നിവേശം (display, window, attr.your_event_mask | mask);
}

സ്ഥിതം ശൂന്യം
check_manager_window (XSettingsClient *client)
{
  എങ്കിൽ (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  എങ്കിൽ (client->grab)
    client->grab (client->display);
  അല്ലെങ്കിൽ
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  എങ്കിൽ (client->manager_window)
    X11_XSelect_നിവേശം (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  എങ്കിൽ (client->ungrab)
    client->ungrab (client->display);
  അല്ലെങ്കിൽ
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  എങ്കിൽ (client->manager_window && client->watch)
    {
      എങ്കിൽ (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          തിരികെ;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      പൂർണ്ണസംഖ്യ                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      ശൂന്യം                *cb_data)
{
  തിരികെ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               ശൂന്യ, ശൂന്യ);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      പൂർണ്ണസംഖ്യ                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      ശൂന്യം                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  അക്ഷരം buffer[256];
  അക്ഷരം *atom_names[3];
  Atom atoms[3];

  client = malloc (വലുപ്പം *client);
  എങ്കിൽ (!client)
    തിരികെ ശൂന്യ;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = ശൂന്യ;

  SDL_snprintf(buffer, വലുപ്പം(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#അല്ലെങ്കിൽ
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, വേര്_Window (display, screen), StructureNotifyMask);

  എങ്കിൽ (client->watch)
    client->watch (വേര്_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  തിരികെ client;
}


ശൂന്യം
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

ശൂന്യം
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

ശൂന്യം
xsettings_client_destroy (XSettingsClient *client)
{
  എങ്കിൽ (client->watch)
    client->watch (വേര്_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  എങ്കിൽ (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  സ്വതന്ത്രം (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              സ്ഥിരം അക്ഷരം        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *തിരയൽ = xsettings_list_lookup (client->settings, name);
  എങ്കിൽ (തിരയൽ)
    {
      *setting = xsettings_setting_copy (തിരയൽ);
      തിരികെ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  അല്ലെങ്കിൽ
    തിരികെ XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                സ്ഥിരം XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  എങ്കിൽ (xev->xany.window == വേര്_Window (client->display, client->screen))
    {
      എങ്കിൽ (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          തിരികെ True;
        }
    }
  അല്ലെങ്കിൽ എങ്കിൽ (xev->xany.window == client->manager_window)
    {
      എങ്കിൽ (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          തിരികെ False;
        }
      അല്ലെങ്കിൽ എങ്കിൽ (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          തിരികെ True;
        }
    }

  തിരികെ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (വലുപ്പം *result);
  എങ്കിൽ (!result)
    തിരികെ ശൂന്യ;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  എങ്കിൽ (!result->name)
    പോകുക err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  തിരഞ്ഞെടുപ്പ് (setting->type)
    {
    അവസ്ഥ XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      നിർത്തുക;
    അവസ്ഥ XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      നിർത്തുക;
    അവസ്ഥ XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      എങ്കിൽ (!result->data.v_string)
        പോകുക err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      നിർത്തുക;
    }

  result->last_change_serial = setting->last_change_serial;

  തിരികെ result;

 err:
  സ്വതന്ത്രം(result->name); // This should NOT be SDL_free()
  സ്വതന്ത്രം(result); // This should NOT be SDL_free()

  തിരികെ ശൂന്യ;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ശൂന്യ;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ശൂന്യ;

  ആകുമ്പോൾ (old_iter)
    {
      XSettingsList *new_കണ്ണി;

      new_കണ്ണി = malloc (വലുപ്പം *new_കണ്ണി);
      എങ്കിൽ (!new_കണ്ണി)
        പോകുക error;

      new_കണ്ണി->setting = xsettings_setting_copy (old_iter->setting);
      എങ്കിൽ (!new_കണ്ണി->setting)
        {
          സ്വതന്ത്രം (new_കണ്ണി);
          പോകുക error;
        }

      എങ്കിൽ (new_iter)
        new_iter->next = new_കണ്ണി;
      അല്ലെങ്കിൽ
        {
          new = new_കണ്ണി;
          new->next = ശൂന്യ;
        }


      new_iter = new_കണ്ണി;

      old_iter = old_iter->next;
    }

  തിരികെ new;

 error:
  xsettings_list_free (new);
  തിരികെ ശൂന്യ;
}

പൂർണ്ണസംഖ്യ
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  എങ്കിൽ (setting_a->type != setting_b->type)
    തിരികെ 0;

  എങ്കിൽ (strcmp (setting_a->name, setting_b->name) != 0)
    തിരികെ 0;

  തിരഞ്ഞെടുപ്പ് (setting_a->type)
    {
    അവസ്ഥ XSETTINGS_TYPE_INT:
      തിരികെ setting_a->data.v_int == setting_b->data.v_int;
    അവസ്ഥ XSETTINGS_TYPE_COLOR:
      തിരികെ (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    അവസ്ഥ XSETTINGS_TYPE_STRING:
      തിരികെ strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  തിരികെ 0;
}

ശൂന്യം
xsettings_setting_free (XSettingsSetting *setting)
{
  എങ്കിൽ (setting->type == XSETTINGS_TYPE_STRING)
    സ്വതന്ത്രം (setting->data.v_string);

  സ്വതന്ത്രം(setting->name); // This should NOT be SDL_free()
  സ്വതന്ത്രം(setting); // This should NOT be SDL_free()
}

ശൂന്യം
xsettings_list_free (XSettingsList *list)
{
  ആകുമ്പോൾ (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      സ്വതന്ത്രം (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_തിരുകുക (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *കണ്ണി;
  XSettingsList *iter;
  XSettingsList *last = ശൂന്യ;

  കണ്ണി = malloc (വലുപ്പം *കണ്ണി);
  എങ്കിൽ (!കണ്ണി)
    തിരികെ XSETTINGS_NO_MEM;
  കണ്ണി->setting = setting;

  iter = *list;
  ആകുമ്പോൾ (iter)
    {
      പൂർണ്ണസംഖ്യ cmp = strcmp (setting->name, iter->setting->name);

      എങ്കിൽ (cmp < 0)
        നിർത്തുക;
      അല്ലെങ്കിൽ എങ്കിൽ (cmp == 0)
        {
          സ്വതന്ത്രം (കണ്ണി);
          തിരികെ XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  എങ്കിൽ (last)
    last->next = കണ്ണി;
  അല്ലെങ്കിൽ
    *list = കണ്ണി;

  കണ്ണി->next = iter;

  തിരികെ XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       സ്ഥിരം അക്ഷരം     *name)
{
  XSettingsList *iter;
  XSettingsList *last = ശൂന്യ;

  iter = *list;
  ആകുമ്പോൾ (iter)
    {
      എങ്കിൽ (strcmp (name, iter->setting->name) == 0)
        {
          എങ്കിൽ (last)
            last->next = iter->next;
          അല്ലെങ്കിൽ
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          സ്വതന്ത്രം (iter);

          തിരികെ XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  തിരികെ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       സ്ഥിരം അക്ഷരം    *name)
{
  XSettingsList *iter;

  iter = list;
  ആകുമ്പോൾ (iter)
    {
      എങ്കിൽ (strcmp (name, iter->setting->name) == 0)
        തിരികെ iter->setting;

      iter = iter->next;
    }

  തിരികെ ശൂന്യ;
}

അക്ഷരം
xsettings_byte_order (ശൂന്യം)
{
  CARD32 myint = 0x01020304;
  തിരികെ (*(അക്ഷരം *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

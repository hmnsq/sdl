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

#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাৱ "SDL_x11video.h"

#অন্তর্ভাৱ <limits.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "xsettings-client.h"

সংরচনা _XSettingsClient
{
  Display *display;
  পূর্ণাঙ্ক screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  শূন্য *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

স্থির শূন্য
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  যদি (!client->notify)
    ঘূৰাই;

  যেতিয়ালৈ (old_iter || new_iter)
    {
      পূর্ণাঙ্ক cmp;

      যদি (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      অন্যথা যদি (old_iter)
        cmp = -1;
      অন্যথা
        cmp = 1;

      যদি (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          রিক্ত,
                          client->cb_data);
        }
      অন্যথা যদি (cmp == 0)
        {
          যদি (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      অন্যথা
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      যদি (old_iter)
        old_iter = old_iter->next;
      যদি (new_iter)
        new_iter = new_iter->next;
    }
}

স্থির পূর্ণাঙ্ক
ignore_errors (Display *display, XErrorEvent *event)
{
  ঘূৰাই True;
}

স্থির ৱর্ণ local_byte_order = '\0';

#define BYTES_বাম(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

স্থির XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  যদি (BYTES_বাম (buffer) < 2)
    ঘূৰাই XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  যদি (buffer->byte_order == local_byte_order)
    *result = x;
  অন্যথা
    *result = (x << 8) | (x >> 8);

  ঘূৰাই XSETTINGS_SUCCESS;
}

স্থির XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  যদি (r == XSETTINGS_SUCCESS)
    *result = x;

  ঘূৰাই r;
}

স্থির XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  যদি (BYTES_বাম (buffer) < 4)
    ঘূৰাই XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  যদি (buffer->byte_order == local_byte_order)
    *result = x;
  অন্যথা
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ঘূৰাই XSETTINGS_SUCCESS;
}

স্থির XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  যদি (BYTES_বাম (buffer) < 1)
    ঘূৰাই XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  ঘূৰাই XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

স্থির XSettingsList *
parse_settings (unsigned ৱর্ণ *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = রিক্ত;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = রিক্ত;
  ৱর্ণ buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned ৱর্ণ *) &buffer_byte_order);
  যদি (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      গচ্ছ out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  যদি (result != XSETTINGS_SUCCESS)
    গচ্ছ out;

  result = fetch_card32 (&buffer, &n_entries);
  যদি (result != XSETTINGS_SUCCESS)
    গচ্ছ out;

  বাবে (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      যদি (result != XSETTINGS_SUCCESS)
        গচ্ছ out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      যদি (result != XSETTINGS_SUCCESS)
        গচ্ছ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      যদি (BYTES_বাম (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          গচ্ছ out;
        }

      setting = malloc (পরিমাণ *setting);
      যদি (!setting)
        {
          result = XSETTINGS_NO_MEM;
          গচ্ছ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      যদি (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          গচ্ছ out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      যদি (result != XSETTINGS_SUCCESS)
        গচ্ছ out;
      setting->last_change_serial = v_int;

      ৱিকল্প (type)
        {
        পক্ষ XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          যদি (result != XSETTINGS_SUCCESS)
            গচ্ছ out;

          setting->data.v_int = (INT32)v_int;
          ভঙ্গ;
        পক্ষ XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          যদি (result != XSETTINGS_SUCCESS)
            গচ্ছ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          যদি (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_বাম (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              গচ্ছ out;
            }

          setting->data.v_string = malloc (v_int + 1);
          যদি (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              গচ্ছ out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          ভঙ্গ;
        পক্ষ XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          যদি (result != XSETTINGS_SUCCESS)
            গচ্ছ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          যদি (result != XSETTINGS_SUCCESS)
            গচ্ছ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          যদি (result != XSETTINGS_SUCCESS)
            গচ্ছ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          যদি (result != XSETTINGS_SUCCESS)
            গচ্ছ out;

          ভঙ্গ;
        স্ৱভাৱ:
          /* Quietly ignore unknown types */
          ভঙ্গ;
        }

      setting->type = type;

      result = xsettings_list_ঢোকাও (&settings, setting);
      যদি (result != XSETTINGS_SUCCESS)
        গচ্ছ out;

      setting = রিক্ত;
    }

 out:

  যদি (result != XSETTINGS_SUCCESS)
    {
      ৱিকল্প (result)
        {
        পক্ষ XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          ভঙ্গ;
        পক্ষ XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          ভঙ্গ;
        পক্ষ XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        পক্ষ XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        পক্ষ XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        পক্ষ XSETTINGS_NO_ENTRY:
          ভঙ্গ;
        }

      যদি (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = রিক্ত;

    }

  ঘূৰাই settings;
}

স্থির শূন্য
read_settings (XSettingsClient *client)
{
  Atom type;
  পূর্ণাঙ্ক format;
  unsigned long n_বস্তুসমূহ;
  unsigned long bytes_after;
  unsigned ৱর্ণ *data;
  পূর্ণাঙ্ক result;

  পূর্ণাঙ্ক (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = রিক্ত;

  যদি (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_বস্তুসমূহ, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      যদি (result == Success && type != None)
        {
          যদি (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          অন্যথা যদি (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          অন্যথা
            client->settings = parse_settings (data, n_বস্তুসমূহ);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

স্থির শূন্য
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_প্ৰবেশ (display, window, attr.your_event_mask | mask);
}

স্থির শূন্য
check_manager_window (XSettingsClient *client)
{
  যদি (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  যদি (client->grab)
    client->grab (client->display);
  অন্যথা
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  যদি (client->manager_window)
    X11_XSelect_প্ৰবেশ (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  যদি (client->ungrab)
    client->ungrab (client->display);
  অন্যথা
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  যদি (client->manager_window && client->watch)
    {
      যদি (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          ঘূৰাই;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      পূর্ণাঙ্ক                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      শূন্য                *cb_data)
{
  ঘূৰাই xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               রিক্ত, রিক্ত);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      পূর্ণাঙ্ক                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      শূন্য                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  ৱর্ণ buffer[256];
  ৱর্ণ *atom_names[3];
  Atom atoms[3];

  client = malloc (পরিমাণ *client);
  যদি (!client)
    ঘূৰাই রিক্ত;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = রিক্ত;

  SDL_snprintf(buffer, পরিমাণ(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#অন্যথা
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, মূল_Window (display, screen), StructureNotifyMask);

  যদি (client->watch)
    client->watch (মূল_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  ঘূৰাই client;
}


শূন্য
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

শূন্য
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

শূন্য
xsettings_client_destroy (XSettingsClient *client)
{
  যদি (client->watch)
    client->watch (মূল_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  যদি (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  মুক্ত (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              ধ্রুৱ ৱর্ণ        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *অনুসন্ধান = xsettings_list_lookup (client->settings, name);
  যদি (অনুসন্ধান)
    {
      *setting = xsettings_setting_copy (অনুসন্ধান);
      ঘূৰাই *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  অন্যথা
    ঘূৰাই XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ধ্রুৱ XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  যদি (xev->xany.window == মূল_Window (client->display, client->screen))
    {
      যদি (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          ঘূৰাই True;
        }
    }
  অন্যথা যদি (xev->xany.window == client->manager_window)
    {
      যদি (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          ঘূৰাই False;
        }
      অন্যথা যদি (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ঘূৰাই True;
        }
    }

  ঘূৰাই False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (পরিমাণ *result);
  যদি (!result)
    ঘূৰাই রিক্ত;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  যদি (!result->name)
    গচ্ছ err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  ৱিকল্প (setting->type)
    {
    পক্ষ XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      ভঙ্গ;
    পক্ষ XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      ভঙ্গ;
    পক্ষ XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      যদি (!result->data.v_string)
        গচ্ছ err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      ভঙ্গ;
    }

  result->last_change_serial = setting->last_change_serial;

  ঘূৰাই result;

 err:
  মুক্ত(result->name); // This should NOT be SDL_free()
  মুক্ত(result); // This should NOT be SDL_free()

  ঘূৰাই রিক্ত;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = রিক্ত;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = রিক্ত;

  যেতিয়ালৈ (old_iter)
    {
      XSettingsList *new_গ্ৰন্থি;

      new_গ্ৰন্থি = malloc (পরিমাণ *new_গ্ৰন্থি);
      যদি (!new_গ্ৰন্থি)
        গচ্ছ error;

      new_গ্ৰন্থি->setting = xsettings_setting_copy (old_iter->setting);
      যদি (!new_গ্ৰন্থি->setting)
        {
          মুক্ত (new_গ্ৰন্থি);
          গচ্ছ error;
        }

      যদি (new_iter)
        new_iter->next = new_গ্ৰন্থি;
      অন্যথা
        {
          new = new_গ্ৰন্থি;
          new->next = রিক্ত;
        }


      new_iter = new_গ্ৰন্থি;

      old_iter = old_iter->next;
    }

  ঘূৰাই new;

 error:
  xsettings_list_free (new);
  ঘূৰাই রিক্ত;
}

পূর্ণাঙ্ক
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  যদি (setting_a->type != setting_b->type)
    ঘূৰাই 0;

  যদি (strcmp (setting_a->name, setting_b->name) != 0)
    ঘূৰাই 0;

  ৱিকল্প (setting_a->type)
    {
    পক্ষ XSETTINGS_TYPE_INT:
      ঘূৰাই setting_a->data.v_int == setting_b->data.v_int;
    পক্ষ XSETTINGS_TYPE_COLOR:
      ঘূৰাই (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    পক্ষ XSETTINGS_TYPE_STRING:
      ঘূৰাই strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  ঘূৰাই 0;
}

শূন্য
xsettings_setting_free (XSettingsSetting *setting)
{
  যদি (setting->type == XSETTINGS_TYPE_STRING)
    মুক্ত (setting->data.v_string);

  মুক্ত(setting->name); // This should NOT be SDL_free()
  মুক্ত(setting); // This should NOT be SDL_free()
}

শূন্য
xsettings_list_free (XSettingsList *list)
{
  যেতিয়ালৈ (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      মুক্ত (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_ঢোকাও (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *গ্ৰন্থি;
  XSettingsList *iter;
  XSettingsList *last = রিক্ত;

  গ্ৰন্থি = malloc (পরিমাণ *গ্ৰন্থি);
  যদি (!গ্ৰন্থি)
    ঘূৰাই XSETTINGS_NO_MEM;
  গ্ৰন্থি->setting = setting;

  iter = *list;
  যেতিয়ালৈ (iter)
    {
      পূর্ণাঙ্ক cmp = strcmp (setting->name, iter->setting->name);

      যদি (cmp < 0)
        ভঙ্গ;
      অন্যথা যদি (cmp == 0)
        {
          মুক্ত (গ্ৰন্থি);
          ঘূৰাই XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  যদি (last)
    last->next = গ্ৰন্থি;
  অন্যথা
    *list = গ্ৰন্থি;

  গ্ৰন্থি->next = iter;

  ঘূৰাই XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       ধ্রুৱ ৱর্ণ     *name)
{
  XSettingsList *iter;
  XSettingsList *last = রিক্ত;

  iter = *list;
  যেতিয়ালৈ (iter)
    {
      যদি (strcmp (name, iter->setting->name) == 0)
        {
          যদি (last)
            last->next = iter->next;
          অন্যথা
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          মুক্ত (iter);

          ঘূৰাই XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  ঘূৰাই XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ধ্রুৱ ৱর্ণ    *name)
{
  XSettingsList *iter;

  iter = list;
  যেতিয়ালৈ (iter)
    {
      যদি (strcmp (name, iter->setting->name) == 0)
        ঘূৰাই iter->setting;

      iter = iter->next;
    }

  ঘূৰাই রিক্ত;
}

ৱর্ণ
xsettings_byte_order (শূন্য)
{
  CARD32 myint = 0x01020304;
  ঘূৰাই (*(ৱর্ণ *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

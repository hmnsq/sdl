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

#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن <limits.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "xsettings-client.h"

بنية _XSettingsClient
{
  Display *display;
  صحيح screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  فراغ *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ساكن فراغ
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  ܐܢ (!client->notify)
    ܦܢܐ;

  ܟܡܐ (old_iter || new_iter)
    {
      صحيح cmp;

      ܐܢ (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      ܐܚܪܢܐ ܐܢ (old_iter)
        cmp = -1;
      ܐܚܪܢܐ
        cmp = 1;

      ܐܢ (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          عدم,
                          client->cb_data);
        }
      ܐܚܪܢܐ ܐܢ (cmp == 0)
        {
          ܐܢ (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      ܐܚܪܢܐ
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      ܐܢ (old_iter)
        old_iter = old_iter->next;
      ܐܢ (new_iter)
        new_iter = new_iter->next;
    }
}

ساكن صحيح
ignore_errors (Display *display, XErrorEvent *event)
{
  ܦܢܐ True;
}

ساكن حرف local_byte_order = '\0';

#define BYTES_LEFT(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

ساكن XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  ܐܢ (BYTES_LEFT (buffer) < 2)
    ܦܢܐ XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  ܐܢ (buffer->byte_order == local_byte_order)
    *result = x;
  ܐܚܪܢܐ
    *result = (x << 8) | (x >> 8);

  ܦܢܐ XSETTINGS_SUCCESS;
}

ساكن XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  ܐܢ (r == XSETTINGS_SUCCESS)
    *result = x;

  ܦܢܐ r;
}

ساكن XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  ܐܢ (BYTES_LEFT (buffer) < 4)
    ܦܢܐ XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  ܐܢ (buffer->byte_order == local_byte_order)
    *result = x;
  ܐܚܪܢܐ
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ܦܢܐ XSETTINGS_SUCCESS;
}

ساكن XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  ܐܢ (BYTES_LEFT (buffer) < 1)
    ܦܢܐ XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  ܦܢܐ XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ساكن XSettingsList *
parse_settings (unsigned حرف *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = عدم;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = عدم;
  حرف buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned حرف *) &buffer_byte_order);
  ܐܢ (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      اذهب out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  ܐܢ (result != XSETTINGS_SUCCESS)
    اذهب out;

  result = fetch_card32 (&buffer, &n_entries);
  ܐܢ (result != XSETTINGS_SUCCESS)
    اذهب out;

  لكل (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      ܐܢ (result != XSETTINGS_SUCCESS)
        اذهب out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      ܐܢ (result != XSETTINGS_SUCCESS)
        اذهب out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ܐܢ (BYTES_LEFT (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          اذهب out;
        }

      setting = malloc (حجم *setting);
      ܐܢ (!setting)
        {
          result = XSETTINGS_NO_MEM;
          اذهب out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      ܐܢ (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          اذهب out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      ܐܢ (result != XSETTINGS_SUCCESS)
        اذهب out;
      setting->last_change_serial = v_int;

      بدل (type)
        {
        حالة XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          ܐܢ (result != XSETTINGS_SUCCESS)
            اذهب out;

          setting->data.v_int = (INT32)v_int;
          اكسر;
        حالة XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          ܐܢ (result != XSETTINGS_SUCCESS)
            اذهب out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ܐܢ (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_LEFT (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              اذهب out;
            }

          setting->data.v_string = malloc (v_int + 1);
          ܐܢ (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              اذهب out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          اكسر;
        حالة XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          ܐܢ (result != XSETTINGS_SUCCESS)
            اذهب out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          ܐܢ (result != XSETTINGS_SUCCESS)
            اذهب out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          ܐܢ (result != XSETTINGS_SUCCESS)
            اذهب out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          ܐܢ (result != XSETTINGS_SUCCESS)
            اذهب out;

          اكسر;
        افتراضي:
          /* Quietly ignore unknown types */
          اكسر;
        }

      setting->type = type;

      result = xsettings_list_insert (&settings, setting);
      ܐܢ (result != XSETTINGS_SUCCESS)
        اذهب out;

      setting = عدم;
    }

 out:

  ܐܢ (result != XSETTINGS_SUCCESS)
    {
      بدل (result)
        {
        حالة XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          اكسر;
        حالة XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          اكسر;
        حالة XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالة XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_NO_ENTRY:
          اكسر;
        }

      ܐܢ (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = عدم;

    }

  ܦܢܐ settings;
}

ساكن فراغ
read_settings (XSettingsClient *client)
{
  Atom type;
  صحيح format;
  unsigned long n_items;
  unsigned long bytes_after;
  unsigned حرف *data;
  صحيح result;

  صحيح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = عدم;

  ܐܢ (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_items, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      ܐܢ (result == Success && type != None)
        {
          ܐܢ (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          ܐܚܪܢܐ ܐܢ (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          ܐܚܪܢܐ
            client->settings = parse_settings (data, n_items);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ساكن فراغ
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelectInput (display, window, attr.your_event_mask | mask);
}

ساكن فراغ
check_manager_window (XSettingsClient *client)
{
  ܐܢ (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  ܐܢ (client->grab)
    client->grab (client->display);
  ܐܚܪܢܐ
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ܐܢ (client->manager_window)
    X11_XSelectInput (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  ܐܢ (client->ungrab)
    client->ungrab (client->display);
  ܐܚܪܢܐ
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ܐܢ (client->manager_window && client->watch)
    {
      ܐܢ (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          ܦܢܐ;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      صحيح                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      فراغ                *cb_data)
{
  ܦܢܐ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               عدم, عدم);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      صحيح                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      فراغ                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  حرف buffer[256];
  حرف *atom_names[3];
  Atom atoms[3];

  client = malloc (حجم *client);
  ܐܢ (!client)
    ܦܢܐ عدم;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = عدم;

  SDL_snprintf(buffer, حجم(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#ܐܚܪܢܐ
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, RootWindow (display, screen), StructureNotifyMask);

  ܐܢ (client->watch)
    client->watch (RootWindow (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  ܦܢܐ client;
}


فراغ
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

فراغ
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

فراغ
xsettings_client_destroy (XSettingsClient *client)
{
  ܐܢ (client->watch)
    client->watch (RootWindow (client->display, client->screen),
                   False, 0, client->cb_data);
  ܐܢ (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  حرر (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت حرف        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *search = xsettings_list_lookup (client->settings, name);
  ܐܢ (search)
    {
      *setting = xsettings_setting_copy (search);
      ܦܢܐ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  ܐܚܪܢܐ
    ܦܢܐ XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ثابت XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ܐܢ (xev->xany.window == RootWindow (client->display, client->screen))
    {
      ܐܢ (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          ܦܢܐ True;
        }
    }
  ܐܚܪܢܐ ܐܢ (xev->xany.window == client->manager_window)
    {
      ܐܢ (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          ܦܢܐ False;
        }
      ܐܚܪܢܐ ܐܢ (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ܦܢܐ True;
        }
    }

  ܦܢܐ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (حجم *result);
  ܐܢ (!result)
    ܦܢܐ عدم;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  ܐܢ (!result->name)
    اذهب err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  بدل (setting->type)
    {
    حالة XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      اكسر;
    حالة XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      اكسر;
    حالة XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      ܐܢ (!result->data.v_string)
        اذهب err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      اكسر;
    }

  result->last_change_serial = setting->last_change_serial;

  ܦܢܐ result;

 err:
  حرر(result->name); // This should NOT be SDL_free()
  حرر(result); // This should NOT be SDL_free()

  ܦܢܐ عدم;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = عدم;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = عدم;

  ܟܡܐ (old_iter)
    {
      XSettingsList *new_node;

      new_node = malloc (حجم *new_node);
      ܐܢ (!new_node)
        اذهب error;

      new_node->setting = xsettings_setting_copy (old_iter->setting);
      ܐܢ (!new_node->setting)
        {
          حرر (new_node);
          اذهب error;
        }

      ܐܢ (new_iter)
        new_iter->next = new_node;
      ܐܚܪܢܐ
        {
          new = new_node;
          new->next = عدم;
        }


      new_iter = new_node;

      old_iter = old_iter->next;
    }

  ܦܢܐ new;

 error:
  xsettings_list_free (new);
  ܦܢܐ عدم;
}

صحيح
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ܐܢ (setting_a->type != setting_b->type)
    ܦܢܐ 0;

  ܐܢ (strcmp (setting_a->name, setting_b->name) != 0)
    ܦܢܐ 0;

  بدل (setting_a->type)
    {
    حالة XSETTINGS_TYPE_INT:
      ܦܢܐ setting_a->data.v_int == setting_b->data.v_int;
    حالة XSETTINGS_TYPE_COLOR:
      ܦܢܐ (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    حالة XSETTINGS_TYPE_STRING:
      ܦܢܐ strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  ܦܢܐ 0;
}

فراغ
xsettings_setting_free (XSettingsSetting *setting)
{
  ܐܢ (setting->type == XSETTINGS_TYPE_STRING)
    حرر (setting->data.v_string);

  حرر(setting->name); // This should NOT be SDL_free()
  حرر(setting); // This should NOT be SDL_free()
}

فراغ
xsettings_list_free (XSettingsList *list)
{
  ܟܡܐ (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      حرر (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_insert (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *node;
  XSettingsList *iter;
  XSettingsList *last = عدم;

  node = malloc (حجم *node);
  ܐܢ (!node)
    ܦܢܐ XSETTINGS_NO_MEM;
  node->setting = setting;

  iter = *list;
  ܟܡܐ (iter)
    {
      صحيح cmp = strcmp (setting->name, iter->setting->name);

      ܐܢ (cmp < 0)
        اكسر;
      ܐܚܪܢܐ ܐܢ (cmp == 0)
        {
          حرر (node);
          ܦܢܐ XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  ܐܢ (last)
    last->next = node;
  ܐܚܪܢܐ
    *list = node;

  node->next = iter;

  ܦܢܐ XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       ثابت حرف     *name)
{
  XSettingsList *iter;
  XSettingsList *last = عدم;

  iter = *list;
  ܟܡܐ (iter)
    {
      ܐܢ (strcmp (name, iter->setting->name) == 0)
        {
          ܐܢ (last)
            last->next = iter->next;
          ܐܚܪܢܐ
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          حرر (iter);

          ܦܢܐ XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  ܦܢܐ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ثابت حرف    *name)
{
  XSettingsList *iter;

  iter = list;
  ܟܡܐ (iter)
    {
      ܐܢ (strcmp (name, iter->setting->name) == 0)
        ܦܢܐ iter->setting;

      iter = iter->next;
    }

  ܦܢܐ عدم;
}

حرف
xsettings_byte_order (فراغ)
{
  CARD32 myint = 0x01020304;
  ܦܢܐ (*(حرف *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

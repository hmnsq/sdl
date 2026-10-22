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

#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11video.h"

#شامل <limits.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>

#شامل "xsettings-client.h"

ساختار _XSettingsClient
{
  Display *display;
  صحیح screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  تهی *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ایستا تهی
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  اگر (!client->notify)
    بازگشت;

  وقتی (old_iter || new_iter)
    {
      صحیح cmp;

      اگر (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      وگرنه اگر (old_iter)
        cmp = -1;
      وگرنه
        cmp = 1;

      اگر (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          پوچ,
                          client->cb_data);
        }
      وگرنه اگر (cmp == 0)
        {
          اگر (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      وگرنه
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      اگر (old_iter)
        old_iter = old_iter->next;
      اگر (new_iter)
        new_iter = new_iter->next;
    }
}

ایستا صحیح
ignore_errors (Display *display, XErrorEvent *event)
{
  بازگشت True;
}

ایستا نویسه local_byte_order = '\0';

#define BYTES_چپ(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

ایستا XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  اگر (BYTES_چپ (buffer) < 2)
    بازگشت XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  اگر (buffer->byte_order == local_byte_order)
    *result = x;
  وگرنه
    *result = (x << 8) | (x >> 8);

  بازگشت XSETTINGS_SUCCESS;
}

ایستا XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  اگر (r == XSETTINGS_SUCCESS)
    *result = x;

  بازگشت r;
}

ایستا XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  اگر (BYTES_چپ (buffer) < 4)
    بازگشت XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  اگر (buffer->byte_order == local_byte_order)
    *result = x;
  وگرنه
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  بازگشت XSETTINGS_SUCCESS;
}

ایستا XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  اگر (BYTES_چپ (buffer) < 1)
    بازگشت XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  بازگشت XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ایستا XSettingsList *
parse_settings (unsigned نویسه *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = پوچ;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = پوچ;
  نویسه buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned نویسه *) &buffer_byte_order);
  اگر (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      برو out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  اگر (result != XSETTINGS_SUCCESS)
    برو out;

  result = fetch_card32 (&buffer, &n_entries);
  اگر (result != XSETTINGS_SUCCESS)
    برو out;

  برای (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      اگر (result != XSETTINGS_SUCCESS)
        برو out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      اگر (result != XSETTINGS_SUCCESS)
        برو out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      اگر (BYTES_چپ (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          برو out;
        }

      setting = malloc (اندازه *setting);
      اگر (!setting)
        {
          result = XSETTINGS_NO_MEM;
          برو out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      اگر (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          برو out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      اگر (result != XSETTINGS_SUCCESS)
        برو out;
      setting->last_change_serial = v_int;

      انتخاب (type)
        {
        حالت XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          اگر (result != XSETTINGS_SUCCESS)
            برو out;

          setting->data.v_int = (INT32)v_int;
          بشکن;
        حالت XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          اگر (result != XSETTINGS_SUCCESS)
            برو out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          اگر (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_چپ (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              برو out;
            }

          setting->data.v_string = malloc (v_int + 1);
          اگر (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              برو out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          بشکن;
        حالت XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          اگر (result != XSETTINGS_SUCCESS)
            برو out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          اگر (result != XSETTINGS_SUCCESS)
            برو out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          اگر (result != XSETTINGS_SUCCESS)
            برو out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          اگر (result != XSETTINGS_SUCCESS)
            برو out;

          بشکن;
        پیشفرض:
          /* Quietly ignore unknown types */
          بشکن;
        }

      setting->type = type;

      result = xsettings_list_درج (&settings, setting);
      اگر (result != XSETTINGS_SUCCESS)
        برو out;

      setting = پوچ;
    }

 out:

  اگر (result != XSETTINGS_SUCCESS)
    {
      انتخاب (result)
        {
        حالت XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          بشکن;
        حالت XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          بشکن;
        حالت XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالت XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالت XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالت XSETTINGS_NO_ENTRY:
          بشکن;
        }

      اگر (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = پوچ;

    }

  بازگشت settings;
}

ایستا تهی
read_settings (XSettingsClient *client)
{
  Atom type;
  صحیح format;
  unsigned long n_اقلام;
  unsigned long bytes_after;
  unsigned نویسه *data;
  صحیح result;

  صحیح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = پوچ;

  اگر (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_اقلام, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      اگر (result == Success && type != None)
        {
          اگر (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          وگرنه اگر (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          وگرنه
            client->settings = parse_settings (data, n_اقلام);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ایستا تهی
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_درون_داد (display, window, attr.your_event_mask | mask);
}

ایستا تهی
check_manager_window (XSettingsClient *client)
{
  اگر (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  اگر (client->grab)
    client->grab (client->display);
  وگرنه
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  اگر (client->manager_window)
    X11_XSelect_درون_داد (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  اگر (client->ungrab)
    client->ungrab (client->display);
  وگرنه
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  اگر (client->manager_window && client->watch)
    {
      اگر (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          بازگشت;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      صحیح                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      تهی                *cb_data)
{
  بازگشت xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               پوچ, پوچ);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      صحیح                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      تهی                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  نویسه buffer[256];
  نویسه *atom_names[3];
  Atom atoms[3];

  client = malloc (اندازه *client);
  اگر (!client)
    بازگشت پوچ;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = پوچ;

  SDL_snprintf(buffer, اندازه(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#وگرنه
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, ریشه_Window (display, screen), StructureNotifyMask);

  اگر (client->watch)
    client->watch (ریشه_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  بازگشت client;
}


تهی
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

تهی
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

تهی
xsettings_client_destroy (XSettingsClient *client)
{
  اگر (client->watch)
    client->watch (ریشه_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  اگر (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  آزاد (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت نویسه        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *جستجو = xsettings_list_lookup (client->settings, name);
  اگر (جستجو)
    {
      *setting = xsettings_setting_copy (جستجو);
      بازگشت *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  وگرنه
    بازگشت XSETTINGS_NO_ENTRY;
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
  اگر (xev->xany.window == ریشه_Window (client->display, client->screen))
    {
      اگر (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          بازگشت True;
        }
    }
  وگرنه اگر (xev->xany.window == client->manager_window)
    {
      اگر (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          بازگشت False;
        }
      وگرنه اگر (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          بازگشت True;
        }
    }

  بازگشت False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (اندازه *result);
  اگر (!result)
    بازگشت پوچ;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  اگر (!result->name)
    برو err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  انتخاب (setting->type)
    {
    حالت XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      بشکن;
    حالت XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      بشکن;
    حالت XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      اگر (!result->data.v_string)
        برو err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      بشکن;
    }

  result->last_change_serial = setting->last_change_serial;

  بازگشت result;

 err:
  آزاد(result->name); // This should NOT be SDL_free()
  آزاد(result); // This should NOT be SDL_free()

  بازگشت پوچ;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = پوچ;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = پوچ;

  وقتی (old_iter)
    {
      XSettingsList *new_گره;

      new_گره = malloc (اندازه *new_گره);
      اگر (!new_گره)
        برو error;

      new_گره->setting = xsettings_setting_copy (old_iter->setting);
      اگر (!new_گره->setting)
        {
          آزاد (new_گره);
          برو error;
        }

      اگر (new_iter)
        new_iter->next = new_گره;
      وگرنه
        {
          new = new_گره;
          new->next = پوچ;
        }


      new_iter = new_گره;

      old_iter = old_iter->next;
    }

  بازگشت new;

 error:
  xsettings_list_free (new);
  بازگشت پوچ;
}

صحیح
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  اگر (setting_a->type != setting_b->type)
    بازگشت 0;

  اگر (strcmp (setting_a->name, setting_b->name) != 0)
    بازگشت 0;

  انتخاب (setting_a->type)
    {
    حالت XSETTINGS_TYPE_INT:
      بازگشت setting_a->data.v_int == setting_b->data.v_int;
    حالت XSETTINGS_TYPE_COLOR:
      بازگشت (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    حالت XSETTINGS_TYPE_STRING:
      بازگشت strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  بازگشت 0;
}

تهی
xsettings_setting_free (XSettingsSetting *setting)
{
  اگر (setting->type == XSETTINGS_TYPE_STRING)
    آزاد (setting->data.v_string);

  آزاد(setting->name); // This should NOT be SDL_free()
  آزاد(setting); // This should NOT be SDL_free()
}

تهی
xsettings_list_free (XSettingsList *list)
{
  وقتی (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      آزاد (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_درج (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *گره;
  XSettingsList *iter;
  XSettingsList *last = پوچ;

  گره = malloc (اندازه *گره);
  اگر (!گره)
    بازگشت XSETTINGS_NO_MEM;
  گره->setting = setting;

  iter = *list;
  وقتی (iter)
    {
      صحیح cmp = strcmp (setting->name, iter->setting->name);

      اگر (cmp < 0)
        بشکن;
      وگرنه اگر (cmp == 0)
        {
          آزاد (گره);
          بازگشت XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  اگر (last)
    last->next = گره;
  وگرنه
    *list = گره;

  گره->next = iter;

  بازگشت XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       ثابت نویسه     *name)
{
  XSettingsList *iter;
  XSettingsList *last = پوچ;

  iter = *list;
  وقتی (iter)
    {
      اگر (strcmp (name, iter->setting->name) == 0)
        {
          اگر (last)
            last->next = iter->next;
          وگرنه
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          آزاد (iter);

          بازگشت XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  بازگشت XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ثابت نویسه    *name)
{
  XSettingsList *iter;

  iter = list;
  وقتی (iter)
    {
      اگر (strcmp (name, iter->setting->name) == 0)
        بازگشت iter->setting;

      iter = iter->next;
    }

  بازگشت پوچ;
}

نویسه
xsettings_byte_order (تهی)
{
  CARD32 myint = 0x01020304;
  بازگشت (*(نویسه *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

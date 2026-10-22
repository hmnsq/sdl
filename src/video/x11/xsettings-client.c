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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "SDL_x11video.h"

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "xsettings-client.h"

கட்டமைப்பு _XSettingsClient
{
  Display *display;
  முழு screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  வெறுமை *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

நிலையான வெறுமை
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  எனில் (!client->notify)
    திரும்பு;

  போது (old_iter || new_iter)
    {
      முழு cmp;

      எனில் (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      இல்லையெனில் எனில் (old_iter)
        cmp = -1;
      இல்லையெனில்
        cmp = 1;

      எனில் (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          வெற்று,
                          client->cb_data);
        }
      இல்லையெனில் எனில் (cmp == 0)
        {
          எனில் (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      இல்லையெனில்
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      எனில் (old_iter)
        old_iter = old_iter->next;
      எனில் (new_iter)
        new_iter = new_iter->next;
    }
}

நிலையான முழு
ignore_errors (Display *display, XErrorEvent *event)
{
  திரும்பு True;
}

நிலையான எழுத்து local_byte_order = '\0';

#define BYTES_இடது(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

நிலையான XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  எனில் (BYTES_இடது (buffer) < 2)
    திரும்பு XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  எனில் (buffer->byte_order == local_byte_order)
    *result = x;
  இல்லையெனில்
    *result = (x << 8) | (x >> 8);

  திரும்பு XSETTINGS_SUCCESS;
}

நிலையான XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  எனில் (r == XSETTINGS_SUCCESS)
    *result = x;

  திரும்பு r;
}

நிலையான XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  எனில் (BYTES_இடது (buffer) < 4)
    திரும்பு XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  எனில் (buffer->byte_order == local_byte_order)
    *result = x;
  இல்லையெனில்
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  திரும்பு XSETTINGS_SUCCESS;
}

நிலையான XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  எனில் (BYTES_இடது (buffer) < 1)
    திரும்பு XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  திரும்பு XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

நிலையான XSettingsList *
parse_settings (unsigned எழுத்து *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = வெற்று;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = வெற்று;
  எழுத்து buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned எழுத்து *) &buffer_byte_order);
  எனில் (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      செல் out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  எனில் (result != XSETTINGS_SUCCESS)
    செல் out;

  result = fetch_card32 (&buffer, &n_entries);
  எனில் (result != XSETTINGS_SUCCESS)
    செல் out;

  க்கு (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      எனில் (result != XSETTINGS_SUCCESS)
        செல் out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      எனில் (result != XSETTINGS_SUCCESS)
        செல் out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      எனில் (BYTES_இடது (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          செல் out;
        }

      setting = malloc (அளவு *setting);
      எனில் (!setting)
        {
          result = XSETTINGS_NO_MEM;
          செல் out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      எனில் (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          செல் out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      எனில் (result != XSETTINGS_SUCCESS)
        செல் out;
      setting->last_change_serial = v_int;

      தேர்வு (type)
        {
        நிலை XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          எனில் (result != XSETTINGS_SUCCESS)
            செல் out;

          setting->data.v_int = (INT32)v_int;
          நிறுத்து;
        நிலை XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          எனில் (result != XSETTINGS_SUCCESS)
            செல் out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          எனில் (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_இடது (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              செல் out;
            }

          setting->data.v_string = malloc (v_int + 1);
          எனில் (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              செல் out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          நிறுத்து;
        நிலை XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          எனில் (result != XSETTINGS_SUCCESS)
            செல் out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          எனில் (result != XSETTINGS_SUCCESS)
            செல் out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          எனில் (result != XSETTINGS_SUCCESS)
            செல் out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          எனில் (result != XSETTINGS_SUCCESS)
            செல் out;

          நிறுத்து;
        இயல்பு:
          /* Quietly ignore unknown types */
          நிறுத்து;
        }

      setting->type = type;

      result = xsettings_list_செருகு (&settings, setting);
      எனில் (result != XSETTINGS_SUCCESS)
        செல் out;

      setting = வெற்று;
    }

 out:

  எனில் (result != XSETTINGS_SUCCESS)
    {
      தேர்வு (result)
        {
        நிலை XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          நிறுத்து;
        நிலை XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          நிறுத்து;
        நிலை XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        நிலை XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        நிலை XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        நிலை XSETTINGS_NO_ENTRY:
          நிறுத்து;
        }

      எனில் (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = வெற்று;

    }

  திரும்பு settings;
}

நிலையான வெறுமை
read_settings (XSettingsClient *client)
{
  Atom type;
  முழு format;
  unsigned long n_பொருட்கள்;
  unsigned long bytes_after;
  unsigned எழுத்து *data;
  முழு result;

  முழு (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = வெற்று;

  எனில் (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_பொருட்கள், &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      எனில் (result == Success && type != None)
        {
          எனில் (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          இல்லையெனில் எனில் (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          இல்லையெனில்
            client->settings = parse_settings (data, n_பொருட்கள்);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

நிலையான வெறுமை
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_உள்ளீடு (display, window, attr.your_event_mask | mask);
}

நிலையான வெறுமை
check_manager_window (XSettingsClient *client)
{
  எனில் (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  எனில் (client->grab)
    client->grab (client->display);
  இல்லையெனில்
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  எனில் (client->manager_window)
    X11_XSelect_உள்ளீடு (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  எனில் (client->ungrab)
    client->ungrab (client->display);
  இல்லையெனில்
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  எனில் (client->manager_window && client->watch)
    {
      எனில் (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          திரும்பு;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      முழு                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      வெறுமை                *cb_data)
{
  திரும்பு xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               வெற்று, வெற்று);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      முழு                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      வெறுமை                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  எழுத்து buffer[256];
  எழுத்து *atom_names[3];
  Atom atoms[3];

  client = malloc (அளவு *client);
  எனில் (!client)
    திரும்பு வெற்று;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = வெற்று;

  SDL_snprintf(buffer, அளவு(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#இல்லையெனில்
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, வேர்_Window (display, screen), StructureNotifyMask);

  எனில் (client->watch)
    client->watch (வேர்_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  திரும்பு client;
}


வெறுமை
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

வெறுமை
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

வெறுமை
xsettings_client_destroy (XSettingsClient *client)
{
  எனில் (client->watch)
    client->watch (வேர்_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  எனில் (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  விடுவி (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              மாறிலி எழுத்து        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *தேடல் = xsettings_list_lookup (client->settings, name);
  எனில் (தேடல்)
    {
      *setting = xsettings_setting_copy (தேடல்);
      திரும்பு *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  இல்லையெனில்
    திரும்பு XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                மாறிலி XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  எனில் (xev->xany.window == வேர்_Window (client->display, client->screen))
    {
      எனில் (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          திரும்பு True;
        }
    }
  இல்லையெனில் எனில் (xev->xany.window == client->manager_window)
    {
      எனில் (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          திரும்பு False;
        }
      இல்லையெனில் எனில் (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          திரும்பு True;
        }
    }

  திரும்பு False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (அளவு *result);
  எனில் (!result)
    திரும்பு வெற்று;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  எனில் (!result->name)
    செல் err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  தேர்வு (setting->type)
    {
    நிலை XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      நிறுத்து;
    நிலை XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      நிறுத்து;
    நிலை XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      எனில் (!result->data.v_string)
        செல் err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      நிறுத்து;
    }

  result->last_change_serial = setting->last_change_serial;

  திரும்பு result;

 err:
  விடுவி(result->name); // This should NOT be SDL_free()
  விடுவி(result); // This should NOT be SDL_free()

  திரும்பு வெற்று;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = வெற்று;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = வெற்று;

  போது (old_iter)
    {
      XSettingsList *new_முனை;

      new_முனை = malloc (அளவு *new_முனை);
      எனில் (!new_முனை)
        செல் error;

      new_முனை->setting = xsettings_setting_copy (old_iter->setting);
      எனில் (!new_முனை->setting)
        {
          விடுவி (new_முனை);
          செல் error;
        }

      எனில் (new_iter)
        new_iter->next = new_முனை;
      இல்லையெனில்
        {
          new = new_முனை;
          new->next = வெற்று;
        }


      new_iter = new_முனை;

      old_iter = old_iter->next;
    }

  திரும்பு new;

 error:
  xsettings_list_free (new);
  திரும்பு வெற்று;
}

முழு
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  எனில் (setting_a->type != setting_b->type)
    திரும்பு 0;

  எனில் (strcmp (setting_a->name, setting_b->name) != 0)
    திரும்பு 0;

  தேர்வு (setting_a->type)
    {
    நிலை XSETTINGS_TYPE_INT:
      திரும்பு setting_a->data.v_int == setting_b->data.v_int;
    நிலை XSETTINGS_TYPE_COLOR:
      திரும்பு (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    நிலை XSETTINGS_TYPE_STRING:
      திரும்பு strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  திரும்பு 0;
}

வெறுமை
xsettings_setting_free (XSettingsSetting *setting)
{
  எனில் (setting->type == XSETTINGS_TYPE_STRING)
    விடுவி (setting->data.v_string);

  விடுவி(setting->name); // This should NOT be SDL_free()
  விடுவி(setting); // This should NOT be SDL_free()
}

வெறுமை
xsettings_list_free (XSettingsList *list)
{
  போது (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      விடுவி (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_செருகு (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *முனை;
  XSettingsList *iter;
  XSettingsList *last = வெற்று;

  முனை = malloc (அளவு *முனை);
  எனில் (!முனை)
    திரும்பு XSETTINGS_NO_MEM;
  முனை->setting = setting;

  iter = *list;
  போது (iter)
    {
      முழு cmp = strcmp (setting->name, iter->setting->name);

      எனில் (cmp < 0)
        நிறுத்து;
      இல்லையெனில் எனில் (cmp == 0)
        {
          விடுவி (முனை);
          திரும்பு XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  எனில் (last)
    last->next = முனை;
  இல்லையெனில்
    *list = முனை;

  முனை->next = iter;

  திரும்பு XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       மாறிலி எழுத்து     *name)
{
  XSettingsList *iter;
  XSettingsList *last = வெற்று;

  iter = *list;
  போது (iter)
    {
      எனில் (strcmp (name, iter->setting->name) == 0)
        {
          எனில் (last)
            last->next = iter->next;
          இல்லையெனில்
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          விடுவி (iter);

          திரும்பு XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  திரும்பு XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       மாறிலி எழுத்து    *name)
{
  XSettingsList *iter;

  iter = list;
  போது (iter)
    {
      எனில் (strcmp (name, iter->setting->name) == 0)
        திரும்பு iter->setting;

      iter = iter->next;
    }

  திரும்பு வெற்று;
}

எழுத்து
xsettings_byte_order (வெறுமை)
{
  CARD32 myint = 0x01020304;
  திரும்பு (*(எழுத்து *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

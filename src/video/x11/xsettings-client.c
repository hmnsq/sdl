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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "SDL_x11video.h"

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "xsettings-client.h"

સંરચના _XSettingsClient
{
  Display *display;
  પૂર્ણાંક screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  શૂન્ય *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

સ્થિર શૂન્ય
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  જો (!client->notify)
    પાછા;

  જ્યારે (old_iter || new_iter)
    {
      પૂર્ણાંક cmp;

      જો (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      નહીંતર જો (old_iter)
        cmp = -1;
      નહીંતર
        cmp = 1;

      જો (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ખાલી,
                          client->cb_data);
        }
      નહીંતર જો (cmp == 0)
        {
          જો (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      નહીંતર
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      જો (old_iter)
        old_iter = old_iter->next;
      જો (new_iter)
        new_iter = new_iter->next;
    }
}

સ્થિર પૂર્ણાંક
ignore_errors (Display *display, XErrorEvent *event)
{
  પાછા True;
}

સ્થિર અક્ષર local_byte_order = '\0';

#define BYTES_ડાબું(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

સ્થિર XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  જો (BYTES_ડાબું (buffer) < 2)
    પાછા XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  જો (buffer->byte_order == local_byte_order)
    *result = x;
  નહીંતર
    *result = (x << 8) | (x >> 8);

  પાછા XSETTINGS_SUCCESS;
}

સ્થિર XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  જો (r == XSETTINGS_SUCCESS)
    *result = x;

  પાછા r;
}

સ્થિર XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  જો (BYTES_ડાબું (buffer) < 4)
    પાછા XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  જો (buffer->byte_order == local_byte_order)
    *result = x;
  નહીંતર
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  પાછા XSETTINGS_SUCCESS;
}

સ્થિર XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  જો (BYTES_ડાબું (buffer) < 1)
    પાછા XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  પાછા XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

સ્થિર XSettingsList *
parse_settings (unsigned અક્ષર *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = ખાલી;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ખાલી;
  અક્ષર buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned અક્ષર *) &buffer_byte_order);
  જો (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      જાઓ out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  જો (result != XSETTINGS_SUCCESS)
    જાઓ out;

  result = fetch_card32 (&buffer, &n_entries);
  જો (result != XSETTINGS_SUCCESS)
    જાઓ out;

  માટે (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      જો (result != XSETTINGS_SUCCESS)
        જાઓ out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      જો (result != XSETTINGS_SUCCESS)
        જાઓ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      જો (BYTES_ડાબું (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          જાઓ out;
        }

      setting = malloc (કદ *setting);
      જો (!setting)
        {
          result = XSETTINGS_NO_MEM;
          જાઓ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      જો (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          જાઓ out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      જો (result != XSETTINGS_SUCCESS)
        જાઓ out;
      setting->last_change_serial = v_int;

      પસંદગી (type)
        {
        સ્થિતિ XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          જો (result != XSETTINGS_SUCCESS)
            જાઓ out;

          setting->data.v_int = (INT32)v_int;
          તોડો;
        સ્થિતિ XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          જો (result != XSETTINGS_SUCCESS)
            જાઓ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          જો (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_ડાબું (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              જાઓ out;
            }

          setting->data.v_string = malloc (v_int + 1);
          જો (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              જાઓ out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          તોડો;
        સ્થિતિ XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          જો (result != XSETTINGS_SUCCESS)
            જાઓ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          જો (result != XSETTINGS_SUCCESS)
            જાઓ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          જો (result != XSETTINGS_SUCCESS)
            જાઓ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          જો (result != XSETTINGS_SUCCESS)
            જાઓ out;

          તોડો;
        મૂળભૂત:
          /* Quietly ignore unknown types */
          તોડો;
        }

      setting->type = type;

      result = xsettings_list_ઉમેરો (&settings, setting);
      જો (result != XSETTINGS_SUCCESS)
        જાઓ out;

      setting = ખાલી;
    }

 out:

  જો (result != XSETTINGS_SUCCESS)
    {
      પસંદગી (result)
        {
        સ્થિતિ XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          તોડો;
        સ્થિતિ XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          તોડો;
        સ્થિતિ XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        સ્થિતિ XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        સ્થિતિ XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        સ્થિતિ XSETTINGS_NO_ENTRY:
          તોડો;
        }

      જો (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ખાલી;

    }

  પાછા settings;
}

સ્થિર શૂન્ય
read_settings (XSettingsClient *client)
{
  Atom type;
  પૂર્ણાંક format;
  unsigned long n_વસ્તુઓ;
  unsigned long bytes_after;
  unsigned અક્ષર *data;
  પૂર્ણાંક result;

  પૂર્ણાંક (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ખાલી;

  જો (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_વસ્તુઓ, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      જો (result == Success && type != None)
        {
          જો (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          નહીંતર જો (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          નહીંતર
            client->settings = parse_settings (data, n_વસ્તુઓ);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

સ્થિર શૂન્ય
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_આગત (display, window, attr.your_event_mask | mask);
}

સ્થિર શૂન્ય
check_manager_window (XSettingsClient *client)
{
  જો (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  જો (client->grab)
    client->grab (client->display);
  નહીંતર
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  જો (client->manager_window)
    X11_XSelect_આગત (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  જો (client->ungrab)
    client->ungrab (client->display);
  નહીંતર
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  જો (client->manager_window && client->watch)
    {
      જો (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          પાછા;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      પૂર્ણાંક                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      શૂન્ય                *cb_data)
{
  પાછા xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               ખાલી, ખાલી);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      પૂર્ણાંક                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      શૂન્ય                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  અક્ષર buffer[256];
  અક્ષર *atom_names[3];
  Atom atoms[3];

  client = malloc (કદ *client);
  જો (!client)
    પાછા ખાલી;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = ખાલી;

  SDL_snprintf(buffer, કદ(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#નહીંતર
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, મૂળ_Window (display, screen), StructureNotifyMask);

  જો (client->watch)
    client->watch (મૂળ_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  પાછા client;
}


શૂન્ય
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

શૂન્ય
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

શૂન્ય
xsettings_client_destroy (XSettingsClient *client)
{
  જો (client->watch)
    client->watch (મૂળ_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  જો (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  મુક્ત (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              અચલ અક્ષર        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *શોધ = xsettings_list_lookup (client->settings, name);
  જો (શોધ)
    {
      *setting = xsettings_setting_copy (શોધ);
      પાછા *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  નહીંતર
    પાછા XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                અચલ XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  જો (xev->xany.window == મૂળ_Window (client->display, client->screen))
    {
      જો (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          પાછા True;
        }
    }
  નહીંતર જો (xev->xany.window == client->manager_window)
    {
      જો (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          પાછા False;
        }
      નહીંતર જો (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          પાછા True;
        }
    }

  પાછા False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (કદ *result);
  જો (!result)
    પાછા ખાલી;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  જો (!result->name)
    જાઓ err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  પસંદગી (setting->type)
    {
    સ્થિતિ XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      તોડો;
    સ્થિતિ XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      તોડો;
    સ્થિતિ XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      જો (!result->data.v_string)
        જાઓ err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      તોડો;
    }

  result->last_change_serial = setting->last_change_serial;

  પાછા result;

 err:
  મુક્ત(result->name); // This should NOT be SDL_free()
  મુક્ત(result); // This should NOT be SDL_free()

  પાછા ખાલી;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ખાલી;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ખાલી;

  જ્યારે (old_iter)
    {
      XSettingsList *new_ગાંઠ;

      new_ગાંઠ = malloc (કદ *new_ગાંઠ);
      જો (!new_ગાંઠ)
        જાઓ error;

      new_ગાંઠ->setting = xsettings_setting_copy (old_iter->setting);
      જો (!new_ગાંઠ->setting)
        {
          મુક્ત (new_ગાંઠ);
          જાઓ error;
        }

      જો (new_iter)
        new_iter->next = new_ગાંઠ;
      નહીંતર
        {
          new = new_ગાંઠ;
          new->next = ખાલી;
        }


      new_iter = new_ગાંઠ;

      old_iter = old_iter->next;
    }

  પાછા new;

 error:
  xsettings_list_free (new);
  પાછા ખાલી;
}

પૂર્ણાંક
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  જો (setting_a->type != setting_b->type)
    પાછા 0;

  જો (strcmp (setting_a->name, setting_b->name) != 0)
    પાછા 0;

  પસંદગી (setting_a->type)
    {
    સ્થિતિ XSETTINGS_TYPE_INT:
      પાછા setting_a->data.v_int == setting_b->data.v_int;
    સ્થિતિ XSETTINGS_TYPE_COLOR:
      પાછા (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    સ્થિતિ XSETTINGS_TYPE_STRING:
      પાછા strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  પાછા 0;
}

શૂન્ય
xsettings_setting_free (XSettingsSetting *setting)
{
  જો (setting->type == XSETTINGS_TYPE_STRING)
    મુક્ત (setting->data.v_string);

  મુક્ત(setting->name); // This should NOT be SDL_free()
  મુક્ત(setting); // This should NOT be SDL_free()
}

શૂન્ય
xsettings_list_free (XSettingsList *list)
{
  જ્યારે (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      મુક્ત (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_ઉમેરો (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ગાંઠ;
  XSettingsList *iter;
  XSettingsList *last = ખાલી;

  ગાંઠ = malloc (કદ *ગાંઠ);
  જો (!ગાંઠ)
    પાછા XSETTINGS_NO_MEM;
  ગાંઠ->setting = setting;

  iter = *list;
  જ્યારે (iter)
    {
      પૂર્ણાંક cmp = strcmp (setting->name, iter->setting->name);

      જો (cmp < 0)
        તોડો;
      નહીંતર જો (cmp == 0)
        {
          મુક્ત (ગાંઠ);
          પાછા XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  જો (last)
    last->next = ગાંઠ;
  નહીંતર
    *list = ગાંઠ;

  ગાંઠ->next = iter;

  પાછા XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       અચલ અક્ષર     *name)
{
  XSettingsList *iter;
  XSettingsList *last = ખાલી;

  iter = *list;
  જ્યારે (iter)
    {
      જો (strcmp (name, iter->setting->name) == 0)
        {
          જો (last)
            last->next = iter->next;
          નહીંતર
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          મુક્ત (iter);

          પાછા XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  પાછા XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       અચલ અક્ષર    *name)
{
  XSettingsList *iter;

  iter = list;
  જ્યારે (iter)
    {
      જો (strcmp (name, iter->setting->name) == 0)
        પાછા iter->setting;

      iter = iter->next;
    }

  પાછા ખાલી;
}

અક્ષર
xsettings_byte_order (શૂન્ય)
{
  CARD32 myint = 0x01020304;
  પાછા (*(અક્ષર *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

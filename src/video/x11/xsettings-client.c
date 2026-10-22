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

#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "SDL_x11video.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xsettings-client.h"

sa_nracanaa _XSettingsClient
{
  Display *display;
  จำนวนเต็ม screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  void *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

static void
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  ถ้า (!client->notify)
    คืน;

  ขณะ (old_iter || new_iter)
    {
      จำนวนเต็ม cmp;

      ถ้า (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      มิฉะนั้น ถ้า (old_iter)
        cmp = -1;
      มิฉะนั้น
        cmp = 1;

      ถ้า (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          NULL,
                          client->cb_data);
        }
      มิฉะนั้น ถ้า (cmp == 0)
        {
          ถ้า (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      มิฉะนั้น
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      ถ้า (old_iter)
        old_iter = old_iter->next;
      ถ้า (new_iter)
        new_iter = new_iter->next;
    }
}

static จำนวนเต็ม
ignore_errors (Display *display, XErrorEvent *event)
{
  คืน True;
}

static var_na local_byte_order = '\0';

#define BYTES_LEFT(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

static XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  ถ้า (BYTES_LEFT (buffer) < 2)
    คืน XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  ถ้า (buffer->byte_order == local_byte_order)
    *result = x;
  มิฉะนั้น
    *result = (x << 8) | (x >> 8);

  คืน XSETTINGS_SUCCESS;
}

static XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  ถ้า (r == XSETTINGS_SUCCESS)
    *result = x;

  คืน r;
}

static XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  ถ้า (BYTES_LEFT (buffer) < 4)
    คืน XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  ถ้า (buffer->byte_order == local_byte_order)
    *result = x;
  มิฉะนั้น
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  คืน XSETTINGS_SUCCESS;
}

static XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  ถ้า (BYTES_LEFT (buffer) < 1)
    คืน XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  คืน XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

static XSettingsList *
parse_settings (unsigned var_na *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = NULL;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = NULL;
  var_na buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned var_na *) &buffer_byte_order);
  ถ้า (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      goto out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  ถ้า (result != XSETTINGS_SUCCESS)
    goto out;

  result = fetch_card32 (&buffer, &n_entries);
  ถ้า (result != XSETTINGS_SUCCESS)
    goto out;

  สำหรับ (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      ถ้า (result != XSETTINGS_SUCCESS)
        goto out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      ถ้า (result != XSETTINGS_SUCCESS)
        goto out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ถ้า (BYTES_LEFT (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          goto out;
        }

      setting = malloc (parimaa_na *setting);
      ถ้า (!setting)
        {
          result = XSETTINGS_NO_MEM;
          goto out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      ถ้า (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          goto out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      ถ้า (result != XSETTINGS_SUCCESS)
        goto out;
      setting->last_change_serial = v_int;

      switch (type)
        {
        pak_sa XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          ถ้า (result != XSETTINGS_SUCCESS)
            goto out;

          setting->data.v_int = (INT32)v_int;
          bha_nga;
        pak_sa XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          ถ้า (result != XSETTINGS_SUCCESS)
            goto out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ถ้า (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_LEFT (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              goto out;
            }

          setting->data.v_string = malloc (v_int + 1);
          ถ้า (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              goto out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          bha_nga;
        pak_sa XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          ถ้า (result != XSETTINGS_SUCCESS)
            goto out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          ถ้า (result != XSETTINGS_SUCCESS)
            goto out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          ถ้า (result != XSETTINGS_SUCCESS)
            goto out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          ถ้า (result != XSETTINGS_SUCCESS)
            goto out;

          bha_nga;
        default:
          /* Quietly ignore unknown types */
          bha_nga;
        }

      setting->type = type;

      result = xsettings_list_insert (&settings, setting);
      ถ้า (result != XSETTINGS_SUCCESS)
        goto out;

      setting = NULL;
    }

 out:

  ถ้า (result != XSETTINGS_SUCCESS)
    {
      switch (result)
        {
        pak_sa XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          bha_nga;
        pak_sa XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          bha_nga;
        pak_sa XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        pak_sa XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        pak_sa XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        pak_sa XSETTINGS_NO_ENTRY:
          bha_nga;
        }

      ถ้า (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = NULL;

    }

  คืน settings;
}

static void
read_settings (XSettingsClient *client)
{
  Atom type;
  จำนวนเต็ม format;
  unsigned long n_items;
  unsigned long bytes_after;
  unsigned var_na *data;
  จำนวนเต็ม result;

  จำนวนเต็ม (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = NULL;

  ถ้า (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_items, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      ถ้า (result == Success && type != None)
        {
          ถ้า (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          มิฉะนั้น ถ้า (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          มิฉะนั้น
            client->settings = parse_settings (data, n_items);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

static void
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelectInput (display, window, attr.your_event_mask | mask);
}

static void
check_manager_window (XSettingsClient *client)
{
  ถ้า (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  ถ้า (client->grab)
    client->grab (client->display);
  มิฉะนั้น
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ถ้า (client->manager_window)
    X11_XSelectInput (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  ถ้า (client->ungrab)
    client->ungrab (client->display);
  มิฉะนั้น
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ถ้า (client->manager_window && client->watch)
    {
      ถ้า (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          คืน;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      จำนวนเต็ม                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      void                *cb_data)
{
  คืน xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               NULL, NULL);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      จำนวนเต็ม                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      void                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  var_na buffer[256];
  var_na *atom_names[3];
  Atom atoms[3];

  client = malloc (parimaa_na *client);
  ถ้า (!client)
    คืน NULL;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = NULL;

  SDL_snprintf(buffer, parimaa_na(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#มิฉะนั้น
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

  ถ้า (client->watch)
    client->watch (RootWindow (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  คืน client;
}


void
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

void
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

void
xsettings_client_destroy (XSettingsClient *client)
{
  ถ้า (client->watch)
    client->watch (RootWindow (client->display, client->screen),
                   False, 0, client->cb_data);
  ถ้า (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  free (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              const var_na        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *search = xsettings_list_lookup (client->settings, name);
  ถ้า (search)
    {
      *setting = xsettings_setting_copy (search);
      คืน *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  มิฉะนั้น
    คืน XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                const XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ถ้า (xev->xany.window == RootWindow (client->display, client->screen))
    {
      ถ้า (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          คืน True;
        }
    }
  มิฉะนั้น ถ้า (xev->xany.window == client->manager_window)
    {
      ถ้า (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          คืน False;
        }
      มิฉะนั้น ถ้า (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          คืน True;
        }
    }

  คืน False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (parimaa_na *result);
  ถ้า (!result)
    คืน NULL;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  ถ้า (!result->name)
    goto err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  switch (setting->type)
    {
    pak_sa XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      bha_nga;
    pak_sa XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      bha_nga;
    pak_sa XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      ถ้า (!result->data.v_string)
        goto err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      bha_nga;
    }

  result->last_change_serial = setting->last_change_serial;

  คืน result;

 err:
  free(result->name); // This should NOT be SDL_free()
  free(result); // This should NOT be SDL_free()

  คืน NULL;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = NULL;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = NULL;

  ขณะ (old_iter)
    {
      XSettingsList *new_node;

      new_node = malloc (parimaa_na *new_node);
      ถ้า (!new_node)
        goto error;

      new_node->setting = xsettings_setting_copy (old_iter->setting);
      ถ้า (!new_node->setting)
        {
          free (new_node);
          goto error;
        }

      ถ้า (new_iter)
        new_iter->next = new_node;
      มิฉะนั้น
        {
          new = new_node;
          new->next = NULL;
        }


      new_iter = new_node;

      old_iter = old_iter->next;
    }

  คืน new;

 error:
  xsettings_list_free (new);
  คืน NULL;
}

จำนวนเต็ม
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ถ้า (setting_a->type != setting_b->type)
    คืน 0;

  ถ้า (strcmp (setting_a->name, setting_b->name) != 0)
    คืน 0;

  switch (setting_a->type)
    {
    pak_sa XSETTINGS_TYPE_INT:
      คืน setting_a->data.v_int == setting_b->data.v_int;
    pak_sa XSETTINGS_TYPE_COLOR:
      คืน (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    pak_sa XSETTINGS_TYPE_STRING:
      คืน strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  คืน 0;
}

void
xsettings_setting_free (XSettingsSetting *setting)
{
  ถ้า (setting->type == XSETTINGS_TYPE_STRING)
    free (setting->data.v_string);

  free(setting->name); // This should NOT be SDL_free()
  free(setting); // This should NOT be SDL_free()
}

void
xsettings_list_free (XSettingsList *list)
{
  ขณะ (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      free (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_insert (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *node;
  XSettingsList *iter;
  XSettingsList *last = NULL;

  node = malloc (parimaa_na *node);
  ถ้า (!node)
    คืน XSETTINGS_NO_MEM;
  node->setting = setting;

  iter = *list;
  ขณะ (iter)
    {
      จำนวนเต็ม cmp = strcmp (setting->name, iter->setting->name);

      ถ้า (cmp < 0)
        bha_nga;
      มิฉะนั้น ถ้า (cmp == 0)
        {
          free (node);
          คืน XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  ถ้า (last)
    last->next = node;
  มิฉะนั้น
    *list = node;

  node->next = iter;

  คืน XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       const var_na     *name)
{
  XSettingsList *iter;
  XSettingsList *last = NULL;

  iter = *list;
  ขณะ (iter)
    {
      ถ้า (strcmp (name, iter->setting->name) == 0)
        {
          ถ้า (last)
            last->next = iter->next;
          มิฉะนั้น
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          free (iter);

          คืน XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  คืน XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       const var_na    *name)
{
  XSettingsList *iter;

  iter = list;
  ขณะ (iter)
    {
      ถ้า (strcmp (name, iter->setting->name) == 0)
        คืน iter->setting;

      iter = iter->next;
    }

  คืน NULL;
}

var_na
xsettings_byte_order (void)
{
  CARD32 myint = 0x01020304;
  คืน (*(var_na *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

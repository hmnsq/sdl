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

struct _XSettingsClient
{
  Display *display;
  整数 screen;
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

  如果 (!client->notify)
    返回;

  当 (old_iter || new_iter)
    {
      整数 cmp;

      如果 (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      否则 如果 (old_iter)
        cmp = -1;
      否则
        cmp = 1;

      如果 (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          NULL,
                          client->cb_data);
        }
      否则 如果 (cmp == 0)
        {
          如果 (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      否则
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      如果 (old_iter)
        old_iter = old_iter->next;
      如果 (new_iter)
        new_iter = new_iter->next;
    }
}

static 整数
ignore_errors (Display *display, XErrorEvent *event)
{
  返回 True;
}

static char local_byte_order = '\0';

#define BYTES_LEFT(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

static XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  如果 (BYTES_LEFT (buffer) < 2)
    返回 XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  如果 (buffer->byte_order == local_byte_order)
    *result = x;
  否则
    *result = (x << 8) | (x >> 8);

  返回 XSETTINGS_SUCCESS;
}

static XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  如果 (r == XSETTINGS_SUCCESS)
    *result = x;

  返回 r;
}

static XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  如果 (BYTES_LEFT (buffer) < 4)
    返回 XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  如果 (buffer->byte_order == local_byte_order)
    *result = x;
  否则
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  返回 XSETTINGS_SUCCESS;
}

static XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  如果 (BYTES_LEFT (buffer) < 1)
    返回 XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  返回 XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

static XSettingsList *
parse_settings (unsigned char *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = NULL;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = NULL;
  char buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned char *) &buffer_byte_order);
  如果 (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      goto out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  如果 (result != XSETTINGS_SUCCESS)
    goto out;

  result = fetch_card32 (&buffer, &n_entries);
  如果 (result != XSETTINGS_SUCCESS)
    goto out;

  为 (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      如果 (result != XSETTINGS_SUCCESS)
        goto out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      如果 (result != XSETTINGS_SUCCESS)
        goto out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      如果 (BYTES_LEFT (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          goto out;
        }

      setting = malloc (sizeof *setting);
      如果 (!setting)
        {
          result = XSETTINGS_NO_MEM;
          goto out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      如果 (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          goto out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      如果 (result != XSETTINGS_SUCCESS)
        goto out;
      setting->last_change_serial = v_int;

      switch (type)
        {
        case XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          如果 (result != XSETTINGS_SUCCESS)
            goto out;

          setting->data.v_int = (INT32)v_int;
          break;
        case XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          如果 (result != XSETTINGS_SUCCESS)
            goto out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          如果 (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_LEFT (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              goto out;
            }

          setting->data.v_string = malloc (v_int + 1);
          如果 (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              goto out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          break;
        case XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          如果 (result != XSETTINGS_SUCCESS)
            goto out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          如果 (result != XSETTINGS_SUCCESS)
            goto out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          如果 (result != XSETTINGS_SUCCESS)
            goto out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          如果 (result != XSETTINGS_SUCCESS)
            goto out;

          break;
        default:
          /* Quietly ignore unknown types */
          break;
        }

      setting->type = type;

      result = xsettings_list_insert (&settings, setting);
      如果 (result != XSETTINGS_SUCCESS)
        goto out;

      setting = NULL;
    }

 out:

  如果 (result != XSETTINGS_SUCCESS)
    {
      switch (result)
        {
        case XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          break;
        case XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          break;
        case XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        case XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        case XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        case XSETTINGS_NO_ENTRY:
          break;
        }

      如果 (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = NULL;

    }

  返回 settings;
}

static void
read_settings (XSettingsClient *client)
{
  Atom type;
  整数 format;
  unsigned long n_items;
  unsigned long bytes_after;
  unsigned char *data;
  整数 result;

  整数 (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = NULL;

  如果 (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_items, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      如果 (result == Success && type != None)
        {
          如果 (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          否则 如果 (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          否则
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
  如果 (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  如果 (client->grab)
    client->grab (client->display);
  否则
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  如果 (client->manager_window)
    X11_XSelectInput (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  如果 (client->ungrab)
    client->ungrab (client->display);
  否则
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  如果 (client->manager_window && client->watch)
    {
      如果 (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          返回;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      整数                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      void                *cb_data)
{
  返回 xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               NULL, NULL);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      整数                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      void                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  char buffer[256];
  char *atom_names[3];
  Atom atoms[3];

  client = malloc (sizeof *client);
  如果 (!client)
    返回 NULL;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = NULL;

  SDL_snprintf(buffer, sizeof(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#否则
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

  如果 (client->watch)
    client->watch (RootWindow (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  返回 client;
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
  如果 (client->watch)
    client->watch (RootWindow (client->display, client->screen),
                   False, 0, client->cb_data);
  如果 (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  free (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              const char        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *search = xsettings_list_lookup (client->settings, name);
  如果 (search)
    {
      *setting = xsettings_setting_copy (search);
      返回 *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  否则
    返回 XSETTINGS_NO_ENTRY;
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
  如果 (xev->xany.window == RootWindow (client->display, client->screen))
    {
      如果 (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          返回 True;
        }
    }
  否则 如果 (xev->xany.window == client->manager_window)
    {
      如果 (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          返回 False;
        }
      否则 如果 (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          返回 True;
        }
    }

  返回 False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (sizeof *result);
  如果 (!result)
    返回 NULL;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  如果 (!result->name)
    goto err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  switch (setting->type)
    {
    case XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      break;
    case XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      break;
    case XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      如果 (!result->data.v_string)
        goto err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      break;
    }

  result->last_change_serial = setting->last_change_serial;

  返回 result;

 err:
  free(result->name); // This should NOT be SDL_free()
  free(result); // This should NOT be SDL_free()

  返回 NULL;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = NULL;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = NULL;

  当 (old_iter)
    {
      XSettingsList *new_node;

      new_node = malloc (sizeof *new_node);
      如果 (!new_node)
        goto error;

      new_node->setting = xsettings_setting_copy (old_iter->setting);
      如果 (!new_node->setting)
        {
          free (new_node);
          goto error;
        }

      如果 (new_iter)
        new_iter->next = new_node;
      否则
        {
          new = new_node;
          new->next = NULL;
        }


      new_iter = new_node;

      old_iter = old_iter->next;
    }

  返回 new;

 error:
  xsettings_list_free (new);
  返回 NULL;
}

整数
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  如果 (setting_a->type != setting_b->type)
    返回 0;

  如果 (strcmp (setting_a->name, setting_b->name) != 0)
    返回 0;

  switch (setting_a->type)
    {
    case XSETTINGS_TYPE_INT:
      返回 setting_a->data.v_int == setting_b->data.v_int;
    case XSETTINGS_TYPE_COLOR:
      返回 (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    case XSETTINGS_TYPE_STRING:
      返回 strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  返回 0;
}

void
xsettings_setting_free (XSettingsSetting *setting)
{
  如果 (setting->type == XSETTINGS_TYPE_STRING)
    free (setting->data.v_string);

  free(setting->name); // This should NOT be SDL_free()
  free(setting); // This should NOT be SDL_free()
}

void
xsettings_list_free (XSettingsList *list)
{
  当 (list)
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

  node = malloc (sizeof *node);
  如果 (!node)
    返回 XSETTINGS_NO_MEM;
  node->setting = setting;

  iter = *list;
  当 (iter)
    {
      整数 cmp = strcmp (setting->name, iter->setting->name);

      如果 (cmp < 0)
        break;
      否则 如果 (cmp == 0)
        {
          free (node);
          返回 XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  如果 (last)
    last->next = node;
  否则
    *list = node;

  node->next = iter;

  返回 XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       const char     *name)
{
  XSettingsList *iter;
  XSettingsList *last = NULL;

  iter = *list;
  当 (iter)
    {
      如果 (strcmp (name, iter->setting->name) == 0)
        {
          如果 (last)
            last->next = iter->next;
          否则
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          free (iter);

          返回 XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  返回 XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       const char    *name)
{
  XSettingsList *iter;

  iter = list;
  当 (iter)
    {
      如果 (strcmp (name, iter->setting->name) == 0)
        返回 iter->setting;

      iter = iter->next;
    }

  返回 NULL;
}

char
xsettings_byte_order (void)
{
  CARD32 myint = 0x01020304;
  返回 (*(char *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

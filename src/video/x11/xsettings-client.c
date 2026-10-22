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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "xsettings-client.h"

संरचना _XSettingsClient
{
  Display *display;
  पूर्णाङ्क screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  शून्य *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

स्थिर शून्य
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  सचे (!client->notify)
    पटिनिवत्त;

  याव (old_iter || new_iter)
    {
      पूर्णाङ्क cmp;

      सचे (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      अञ्ञथा सचे (old_iter)
        cmp = -1;
      अञ्ञथा
        cmp = 1;

      सचे (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          रिक्त,
                          client->cb_data);
        }
      अञ्ञथा सचे (cmp == 0)
        {
          सचे (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      अञ्ञथा
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      सचे (old_iter)
        old_iter = old_iter->next;
      सचे (new_iter)
        new_iter = new_iter->next;
    }
}

स्थिर पूर्णाङ्क
ignore_errors (Display *display, XErrorEvent *event)
{
  पटिनिवत्त True;
}

स्थिर वर्ण local_byte_order = '\0';

#define BYTES_वामः(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

स्थिर XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  सचे (BYTES_वामः (buffer) < 2)
    पटिनिवत्त XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  सचे (buffer->byte_order == local_byte_order)
    *result = x;
  अञ्ञथा
    *result = (x << 8) | (x >> 8);

  पटिनिवत्त XSETTINGS_SUCCESS;
}

स्थिर XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  सचे (r == XSETTINGS_SUCCESS)
    *result = x;

  पटिनिवत्त r;
}

स्थिर XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  सचे (BYTES_वामः (buffer) < 4)
    पटिनिवत्त XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  सचे (buffer->byte_order == local_byte_order)
    *result = x;
  अञ्ञथा
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  पटिनिवत्त XSETTINGS_SUCCESS;
}

स्थिर XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  सचे (BYTES_वामः (buffer) < 1)
    पटिनिवत्त XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  पटिनिवत्त XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

स्थिर XSettingsList *
parse_settings (unsigned वर्ण *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = रिक्त;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = रिक्त;
  वर्ण buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned वर्ण *) &buffer_byte_order);
  सचे (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      गच्छ out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  सचे (result != XSETTINGS_SUCCESS)
    गच्छ out;

  result = fetch_card32 (&buffer, &n_entries);
  सचे (result != XSETTINGS_SUCCESS)
    गच्छ out;

  अत्थाय (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      सचे (result != XSETTINGS_SUCCESS)
        गच्छ out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      सचे (result != XSETTINGS_SUCCESS)
        गच्छ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      सचे (BYTES_वामः (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          गच्छ out;
        }

      setting = malloc (परिमाण *setting);
      सचे (!setting)
        {
          result = XSETTINGS_NO_MEM;
          गच्छ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      सचे (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          गच्छ out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      सचे (result != XSETTINGS_SUCCESS)
        गच्छ out;
      setting->last_change_serial = v_int;

      विकल्प (type)
        {
        पक्ष XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          सचे (result != XSETTINGS_SUCCESS)
            गच्छ out;

          setting->data.v_int = (INT32)v_int;
          भङ्ग;
        पक्ष XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          सचे (result != XSETTINGS_SUCCESS)
            गच्छ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          सचे (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_वामः (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              गच्छ out;
            }

          setting->data.v_string = malloc (v_int + 1);
          सचे (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              गच्छ out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          भङ्ग;
        पक्ष XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          सचे (result != XSETTINGS_SUCCESS)
            गच्छ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          सचे (result != XSETTINGS_SUCCESS)
            गच्छ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          सचे (result != XSETTINGS_SUCCESS)
            गच्छ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          सचे (result != XSETTINGS_SUCCESS)
            गच्छ out;

          भङ्ग;
        स्वभाव:
          /* Quietly ignore unknown types */
          भङ्ग;
        }

      setting->type = type;

      result = xsettings_list_निवेशय (&settings, setting);
      सचे (result != XSETTINGS_SUCCESS)
        गच्छ out;

      setting = रिक्त;
    }

 out:

  सचे (result != XSETTINGS_SUCCESS)
    {
      विकल्प (result)
        {
        पक्ष XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          भङ्ग;
        पक्ष XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          भङ्ग;
        पक्ष XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_NO_ENTRY:
          भङ्ग;
        }

      सचे (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = रिक्त;

    }

  पटिनिवत्त settings;
}

स्थिर शून्य
read_settings (XSettingsClient *client)
{
  Atom type;
  पूर्णाङ्क format;
  unsigned long n_वस्तूनि;
  unsigned long bytes_after;
  unsigned वर्ण *data;
  पूर्णाङ्क result;

  पूर्णाङ्क (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = रिक्त;

  सचे (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_वस्तूनि, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      सचे (result == Success && type != None)
        {
          सचे (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          अञ्ञथा सचे (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          अञ्ञथा
            client->settings = parse_settings (data, n_वस्तूनि);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

स्थिर शून्य
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_निवेशः (display, window, attr.your_event_mask | mask);
}

स्थिर शून्य
check_manager_window (XSettingsClient *client)
{
  सचे (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  सचे (client->grab)
    client->grab (client->display);
  अञ्ञथा
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  सचे (client->manager_window)
    X11_XSelect_निवेशः (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  सचे (client->ungrab)
    client->ungrab (client->display);
  अञ्ञथा
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  सचे (client->manager_window && client->watch)
    {
      सचे (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          पटिनिवत्त;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      पूर्णाङ्क                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      शून्य                *cb_data)
{
  पटिनिवत्त xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               रिक्त, रिक्त);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      पूर्णाङ्क                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      शून्य                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  वर्ण buffer[256];
  वर्ण *atom_names[3];
  Atom atoms[3];

  client = malloc (परिमाण *client);
  सचे (!client)
    पटिनिवत्त रिक्त;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = रिक्त;

  SDL_snprintf(buffer, परिमाण(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#अञ्ञथा
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, मूलम्_Window (display, screen), StructureNotifyMask);

  सचे (client->watch)
    client->watch (मूलम्_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  पटिनिवत्त client;
}


शून्य
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

शून्य
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

शून्य
xsettings_client_destroy (XSettingsClient *client)
{
  सचे (client->watch)
    client->watch (मूलम्_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  सचे (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  मुक्त (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              ध्रुव वर्ण        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *अन्वेषणम् = xsettings_list_lookup (client->settings, name);
  सचे (अन्वेषणम्)
    {
      *setting = xsettings_setting_copy (अन्वेषणम्);
      पटिनिवत्त *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  अञ्ञथा
    पटिनिवत्त XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ध्रुव XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  सचे (xev->xany.window == मूलम्_Window (client->display, client->screen))
    {
      सचे (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          पटिनिवत्त True;
        }
    }
  अञ्ञथा सचे (xev->xany.window == client->manager_window)
    {
      सचे (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          पटिनिवत्त False;
        }
      अञ्ञथा सचे (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          पटिनिवत्त True;
        }
    }

  पटिनिवत्त False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (परिमाण *result);
  सचे (!result)
    पटिनिवत्त रिक्त;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  सचे (!result->name)
    गच्छ err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  विकल्प (setting->type)
    {
    पक्ष XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      भङ्ग;
    पक्ष XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      भङ्ग;
    पक्ष XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      सचे (!result->data.v_string)
        गच्छ err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      भङ्ग;
    }

  result->last_change_serial = setting->last_change_serial;

  पटिनिवत्त result;

 err:
  मुक्त(result->name); // This should NOT be SDL_free()
  मुक्त(result); // This should NOT be SDL_free()

  पटिनिवत्त रिक्त;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = रिक्त;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = रिक्त;

  याव (old_iter)
    {
      XSettingsList *new_ग्रन्थिः;

      new_ग्रन्थिः = malloc (परिमाण *new_ग्रन्थिः);
      सचे (!new_ग्रन्थिः)
        गच्छ error;

      new_ग्रन्थिः->setting = xsettings_setting_copy (old_iter->setting);
      सचे (!new_ग्रन्थिः->setting)
        {
          मुक्त (new_ग्रन्थिः);
          गच्छ error;
        }

      सचे (new_iter)
        new_iter->next = new_ग्रन्थिः;
      अञ्ञथा
        {
          new = new_ग्रन्थिः;
          new->next = रिक्त;
        }


      new_iter = new_ग्रन्थिः;

      old_iter = old_iter->next;
    }

  पटिनिवत्त new;

 error:
  xsettings_list_free (new);
  पटिनिवत्त रिक्त;
}

पूर्णाङ्क
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  सचे (setting_a->type != setting_b->type)
    पटिनिवत्त 0;

  सचे (strcmp (setting_a->name, setting_b->name) != 0)
    पटिनिवत्त 0;

  विकल्प (setting_a->type)
    {
    पक्ष XSETTINGS_TYPE_INT:
      पटिनिवत्त setting_a->data.v_int == setting_b->data.v_int;
    पक्ष XSETTINGS_TYPE_COLOR:
      पटिनिवत्त (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    पक्ष XSETTINGS_TYPE_STRING:
      पटिनिवत्त strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  पटिनिवत्त 0;
}

शून्य
xsettings_setting_free (XSettingsSetting *setting)
{
  सचे (setting->type == XSETTINGS_TYPE_STRING)
    मुक्त (setting->data.v_string);

  मुक्त(setting->name); // This should NOT be SDL_free()
  मुक्त(setting); // This should NOT be SDL_free()
}

शून्य
xsettings_list_free (XSettingsList *list)
{
  याव (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      मुक्त (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_निवेशय (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ग्रन्थिः;
  XSettingsList *iter;
  XSettingsList *last = रिक्त;

  ग्रन्थिः = malloc (परिमाण *ग्रन्थिः);
  सचे (!ग्रन्थिः)
    पटिनिवत्त XSETTINGS_NO_MEM;
  ग्रन्थिः->setting = setting;

  iter = *list;
  याव (iter)
    {
      पूर्णाङ्क cmp = strcmp (setting->name, iter->setting->name);

      सचे (cmp < 0)
        भङ्ग;
      अञ्ञथा सचे (cmp == 0)
        {
          मुक्त (ग्रन्थिः);
          पटिनिवत्त XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  सचे (last)
    last->next = ग्रन्थिः;
  अञ्ञथा
    *list = ग्रन्थिः;

  ग्रन्थिः->next = iter;

  पटिनिवत्त XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       ध्रुव वर्ण     *name)
{
  XSettingsList *iter;
  XSettingsList *last = रिक्त;

  iter = *list;
  याव (iter)
    {
      सचे (strcmp (name, iter->setting->name) == 0)
        {
          सचे (last)
            last->next = iter->next;
          अञ्ञथा
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          मुक्त (iter);

          पटिनिवत्त XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  पटिनिवत्त XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ध्रुव वर्ण    *name)
{
  XSettingsList *iter;

  iter = list;
  याव (iter)
    {
      सचे (strcmp (name, iter->setting->name) == 0)
        पटिनिवत्त iter->setting;

      iter = iter->next;
    }

  पटिनिवत्त रिक्त;
}

वर्ण
xsettings_byte_order (शून्य)
{
  CARD32 myint = 0x01020304;
  पटिनिवत्त (*(वर्ण *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

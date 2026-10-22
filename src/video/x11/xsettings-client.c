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

  यदि (!client->notify)
    फर्काऊ;

  जबसम्म (old_iter || new_iter)
    {
      पूर्णाङ्क cmp;

      यदि (old_iter && new_iter)
        cmp = म_भेद (old_iter->setting->name, new_iter->setting->name);
      अन्यथा यदि (old_iter)
        cmp = -1;
      अन्यथा
        cmp = 1;

      यदि (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          रिक्त,
                          client->cb_data);
        }
      अन्यथा यदि (cmp == 0)
        {
          यदि (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      अन्यथा
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      यदि (old_iter)
        old_iter = old_iter->next;
      यदि (new_iter)
        new_iter = new_iter->next;
    }
}

स्थिर पूर्णाङ्क
ignore_errors (Display *display, XErrorEvent *event)
{
  फर्काऊ True;
}

स्थिर वर्ण local_byte_order = '\0';

#define BYTES_बायाँ(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

स्थिर XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  यदि (BYTES_बायाँ (buffer) < 2)
    फर्काऊ XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  यदि (buffer->byte_order == local_byte_order)
    *result = x;
  अन्यथा
    *result = (x << 8) | (x >> 8);

  फर्काऊ XSETTINGS_SUCCESS;
}

स्थिर XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              अचिन्हित लघु  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  यदि (r == XSETTINGS_SUCCESS)
    *result = x;

  फर्काऊ r;
}

स्थिर XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  यदि (BYTES_बायाँ (buffer) < 4)
    फर्काऊ XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  यदि (buffer->byte_order == local_byte_order)
    *result = x;
  अन्यथा
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  फर्काऊ XSETTINGS_SUCCESS;
}

स्थिर XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  यदि (BYTES_बायाँ (buffer) < 1)
    फर्काऊ XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  फर्काऊ XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

स्थिर XSettingsList *
parse_settings (अचिन्हित वर्ण *data,
                माप_प्रकार         len)
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

  result = fetch_card8 (&buffer, (अचिन्हित वर्ण *) &buffer_byte_order);
  यदि (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      ख_लिखो (मानक_त्रुटि, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      गच्छ out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  यदि (result != XSETTINGS_SUCCESS)
    गच्छ out;

  result = fetch_card32 (&buffer, &n_entries);
  यदि (result != XSETTINGS_SUCCESS)
    गच्छ out;

  लागि (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      माप_प्रकार pad_len;

      result = fetch_card8 (&buffer, &type);
      यदि (result != XSETTINGS_SUCCESS)
        गच्छ out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      यदि (result != XSETTINGS_SUCCESS)
        गच्छ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      यदि (BYTES_बायाँ (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          गच्छ out;
        }

      setting = दो_स्मृति (परिमाण *setting);
      यदि (!setting)
        {
          result = XSETTINGS_NO_MEM;
          गच्छ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = दो_स्मृति (name_len + 1);
      यदि (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          गच्छ out;
        }

      स_नकल (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      यदि (result != XSETTINGS_SUCCESS)
        गच्छ out;
      setting->last_change_serial = v_int;

      विकल्प (type)
        {
        पक्ष XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          यदि (result != XSETTINGS_SUCCESS)
            गच्छ out;

          setting->data.v_int = (INT32)v_int;
          रोक;
        पक्ष XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          यदि (result != XSETTINGS_SUCCESS)
            गच्छ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          यदि (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_बायाँ (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              गच्छ out;
            }

          setting->data.v_string = दो_स्मृति (v_int + 1);
          यदि (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              गच्छ out;
            }

          स_नकल (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          रोक;
        पक्ष XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          यदि (result != XSETTINGS_SUCCESS)
            गच्छ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          यदि (result != XSETTINGS_SUCCESS)
            गच्छ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          यदि (result != XSETTINGS_SUCCESS)
            गच्छ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          यदि (result != XSETTINGS_SUCCESS)
            गच्छ out;

          रोक;
        स्वभाव:
          /* Quietly ignore unknown types */
          रोक;
        }

      setting->type = type;

      result = xsettings_list_घुसाउ (&settings, setting);
      यदि (result != XSETTINGS_SUCCESS)
        गच्छ out;

      setting = रिक्त;
    }

 out:

  यदि (result != XSETTINGS_SUCCESS)
    {
      विकल्प (result)
        {
        पक्ष XSETTINGS_NO_MEM:
          ख_लिखो(मानक_त्रुटि, "Out of memory reading XSETTINGS property\n");
          रोक;
        पक्ष XSETTINGS_ACCESS:
          ख_लिखो(मानक_त्रुटि, "Invalid XSETTINGS property (read off end)\n");
          रोक;
        पक्ष XSETTINGS_DUPLICATE_ENTRY:
          ख_लिखो (मानक_त्रुटि, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_NO_ENTRY:
          रोक;
        }

      यदि (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = रिक्त;

    }

  फर्काऊ settings;
}

स्थिर शून्य
read_settings (XSettingsClient *client)
{
  Atom type;
  पूर्णाङ्क format;
  अचिन्हित दीर्घ n_वस्तुहरू;
  अचिन्हित दीर्घ bytes_after;
  अचिन्हित वर्ण *data;
  पूर्णाङ्क result;

  पूर्णाङ्क (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = रिक्त;

  यदि (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, दीर्घ_उच्च,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_वस्तुहरू, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      यदि (result == Success && type != None)
        {
          यदि (type != client->xsettings_atom)
            {
              ख_लिखो (मानक_त्रुटि, "Invalid type for XSETTINGS property");
            }
          अन्यथा यदि (format != 8)
            {
              ख_लिखो (मानक_त्रुटि, "Invalid format for XSETTINGS property %d", format);
            }
          अन्यथा
            client->settings = parse_settings (data, n_वस्तुहरू);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

स्थिर शून्य
add_events (Display *display,
            Window   window,
            दीर्घ     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_आगत (display, window, attr.your_event_mask | mask);
}

स्थिर शून्य
check_manager_window (XSettingsClient *client)
{
  यदि (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  यदि (client->grab)
    client->grab (client->display);
  अन्यथा
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  यदि (client->manager_window)
    X11_XSelect_आगत (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  यदि (client->ungrab)
    client->ungrab (client->display);
  अन्यथा
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  यदि (client->manager_window && client->watch)
    {
      यदि (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          फर्काऊ;
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
  फर्काऊ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
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

  client = दो_स्मृति (परिमाण *client);
  यदि (!client)
    फर्काऊ रिक्त;

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
#अन्यथा
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, जरा_Window (display, screen), StructureNotifyMask);

  यदि (client->watch)
    client->watch (जरा_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  फर्काऊ client;
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
  यदि (client->watch)
    client->watch (जरा_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  यदि (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  मुक्त (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              अचर वर्ण        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *खोज = xsettings_list_lookup (client->settings, name);
  यदि (खोज)
    {
      *setting = xsettings_setting_copy (खोज);
      फर्काऊ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  अन्यथा
    फर्काऊ XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                अचर XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  यदि (xev->xany.window == जरा_Window (client->display, client->screen))
    {
      यदि (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          फर्काऊ True;
        }
    }
  अन्यथा यदि (xev->xany.window == client->manager_window)
    {
      यदि (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          फर्काऊ False;
        }
      अन्यथा यदि (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          फर्काऊ True;
        }
    }

  फर्काऊ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  माप_प्रकार str_len;

  result = दो_स्मृति (परिमाण *result);
  यदि (!result)
    फर्काऊ रिक्त;

  str_len = म_माप (setting->name);
  result->name = दो_स्मृति (str_len + 1);
  यदि (!result->name)
    गच्छ err;

  स_नकल (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  विकल्प (setting->type)
    {
    पक्ष XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      रोक;
    पक्ष XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      रोक;
    पक्ष XSETTINGS_TYPE_STRING:
      str_len = म_माप (setting->data.v_string);
      result->data.v_string = दो_स्मृति (str_len + 1);
      यदि (!result->data.v_string)
        गच्छ err;

      स_नकल (result->data.v_string, setting->data.v_string, str_len + 1);
      रोक;
    }

  result->last_change_serial = setting->last_change_serial;

  फर्काऊ result;

 err:
  मुक्त(result->name); // This should NOT be SDL_free()
  मुक्त(result); // This should NOT be SDL_free()

  फर्काऊ रिक्त;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = रिक्त;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = रिक्त;

  जबसम्म (old_iter)
    {
      XSettingsList *new_गाँठो;

      new_गाँठो = दो_स्मृति (परिमाण *new_गाँठो);
      यदि (!new_गाँठो)
        गच्छ error;

      new_गाँठो->setting = xsettings_setting_copy (old_iter->setting);
      यदि (!new_गाँठो->setting)
        {
          मुक्त (new_गाँठो);
          गच्छ error;
        }

      यदि (new_iter)
        new_iter->next = new_गाँठो;
      अन्यथा
        {
          new = new_गाँठो;
          new->next = रिक्त;
        }


      new_iter = new_गाँठो;

      old_iter = old_iter->next;
    }

  फर्काऊ new;

 error:
  xsettings_list_free (new);
  फर्काऊ रिक्त;
}

पूर्णाङ्क
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  यदि (setting_a->type != setting_b->type)
    फर्काऊ 0;

  यदि (म_भेद (setting_a->name, setting_b->name) != 0)
    फर्काऊ 0;

  विकल्प (setting_a->type)
    {
    पक्ष XSETTINGS_TYPE_INT:
      फर्काऊ setting_a->data.v_int == setting_b->data.v_int;
    पक्ष XSETTINGS_TYPE_COLOR:
      फर्काऊ (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    पक्ष XSETTINGS_TYPE_STRING:
      फर्काऊ म_भेद (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  फर्काऊ 0;
}

शून्य
xsettings_setting_free (XSettingsSetting *setting)
{
  यदि (setting->type == XSETTINGS_TYPE_STRING)
    मुक्त (setting->data.v_string);

  मुक्त(setting->name); // This should NOT be SDL_free()
  मुक्त(setting); // This should NOT be SDL_free()
}

शून्य
xsettings_list_free (XSettingsList *list)
{
  जबसम्म (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      मुक्त (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_घुसाउ (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *गाँठो;
  XSettingsList *iter;
  XSettingsList *last = रिक्त;

  गाँठो = दो_स्मृति (परिमाण *गाँठो);
  यदि (!गाँठो)
    फर्काऊ XSETTINGS_NO_MEM;
  गाँठो->setting = setting;

  iter = *list;
  जबसम्म (iter)
    {
      पूर्णाङ्क cmp = म_भेद (setting->name, iter->setting->name);

      यदि (cmp < 0)
        रोक;
      अन्यथा यदि (cmp == 0)
        {
          मुक्त (गाँठो);
          फर्काऊ XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  यदि (last)
    last->next = गाँठो;
  अन्यथा
    *list = गाँठो;

  गाँठो->next = iter;

  फर्काऊ XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       अचर वर्ण     *name)
{
  XSettingsList *iter;
  XSettingsList *last = रिक्त;

  iter = *list;
  जबसम्म (iter)
    {
      यदि (म_भेद (name, iter->setting->name) == 0)
        {
          यदि (last)
            last->next = iter->next;
          अन्यथा
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          मुक्त (iter);

          फर्काऊ XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  फर्काऊ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       अचर वर्ण    *name)
{
  XSettingsList *iter;

  iter = list;
  जबसम्म (iter)
    {
      यदि (म_भेद (name, iter->setting->name) == 0)
        फर्काऊ iter->setting;

      iter = iter->next;
    }

  फर्काऊ रिक्त;
}

वर्ण
xsettings_byte_order (शून्य)
{
  CARD32 myint = 0x01020304;
  फर्काऊ (*(वर्ण *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

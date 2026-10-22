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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "xsettings-client.h"

ସଂରଚନା _XSettingsClient
{
  Display *display;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  ଶୂନ୍ୟ *cb_data;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ସ୍ଥିର ଶୂନ୍ୟ
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  ଯଦି (!client->notify)
    ଫେରନ୍ତୁ;

  ଯେତେବେଳେ (old_iter || new_iter)
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmp;

      ଯଦି (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      ଅନ୍ୟଥା ଯଦି (old_iter)
        cmp = -1;
      ଅନ୍ୟଥା
        cmp = 1;

      ଯଦି (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ଖାଲି,
                          client->cb_data);
        }
      ଅନ୍ୟଥା ଯଦି (cmp == 0)
        {
          ଯଦି (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_data);
        }
      ଅନ୍ୟଥା
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_data);
        }

      ଯଦି (old_iter)
        old_iter = old_iter->next;
      ଯଦି (new_iter)
        new_iter = new_iter->next;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
ignore_errors (Display *display, XErrorEvent *event)
{
  ଫେରନ୍ତୁ True;
}

ସ୍ଥିର ଅକ୍ଷର local_byte_order = '\0';

#define BYTES_ବାମ(buffer) ((buffer)->data + (buffer)->len - (buffer)->pos)

ସ୍ଥିର XSettingsResult
fetch_card16 (XSettingsBuffer *buffer,
              CARD16          *result)
{
  CARD16 x;

  ଯଦି (BYTES_ବାମ (buffer) < 2)
    ଫେରନ୍ତୁ XSETTINGS_ACCESS;

  x = *(CARD16 *)buffer->pos;
  buffer->pos += 2;

  ଯଦି (buffer->byte_order == local_byte_order)
    *result = x;
  ଅନ୍ୟଥା
    *result = (x << 8) | (x >> 8);

  ଫେରନ୍ତୁ XSETTINGS_SUCCESS;
}

ସ୍ଥିର XSettingsResult
fetch_ushort (XSettingsBuffer *buffer,
              unsigned short  *result)
{
  CARD16 x;
  XSettingsResult r;

  r = fetch_card16 (buffer, &x);
  ଯଦି (r == XSETTINGS_SUCCESS)
    *result = x;

  ଫେରନ୍ତୁ r;
}

ସ୍ଥିର XSettingsResult
fetch_card32 (XSettingsBuffer *buffer,
              CARD32          *result)
{
  CARD32 x;

  ଯଦି (BYTES_ବାମ (buffer) < 4)
    ଫେରନ୍ତୁ XSETTINGS_ACCESS;

  x = *(CARD32 *)buffer->pos;
  buffer->pos += 4;

  ଯଦି (buffer->byte_order == local_byte_order)
    *result = x;
  ଅନ୍ୟଥା
    *result = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ଫେରନ୍ତୁ XSETTINGS_SUCCESS;
}

ସ୍ଥିର XSettingsResult
fetch_card8 (XSettingsBuffer *buffer,
             CARD8           *result)
{
  ଯଦି (BYTES_ବାମ (buffer) < 1)
    ଫେରନ୍ତୁ XSETTINGS_ACCESS;

  *result = *(CARD8 *)buffer->pos;
  buffer->pos += 1;

  ଫେରନ୍ତୁ XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ସ୍ଥିର XSettingsList *
parse_settings (unsigned ଅକ୍ଷର *data,
                size_t         len)
{
  XSettingsBuffer buffer;
  XSettingsResult result = XSETTINGS_SUCCESS;
  XSettingsList *settings = ଖାଲି;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ଖାଲି;
  ଅକ୍ଷର buffer_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  buffer.pos = buffer.data = data;
  buffer.len = len;
  buffer.byte_order = '\0';

  result = fetch_card8 (&buffer, (unsigned ଅକ୍ଷର *) &buffer_byte_order);
  ଯଦି (buffer_byte_order != MSBFirst &&
      buffer_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      result = XSETTINGS_FAILED;
      ଯାଅ out;
    }

  buffer.byte_order = buffer_byte_order;
  buffer.pos += 3;

  result = fetch_card32 (&buffer, &serial);
  ଯଦି (result != XSETTINGS_SUCCESS)
    ଯାଅ out;

  result = fetch_card32 (&buffer, &n_entries);
  ଯଦି (result != XSETTINGS_SUCCESS)
    ଯାଅ out;

  ପାଇଁ (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      result = fetch_card8 (&buffer, &type);
      ଯଦି (result != XSETTINGS_SUCCESS)
        ଯାଅ out;

      buffer.pos += 1;

      result = fetch_card16 (&buffer, &name_len);
      ଯଦି (result != XSETTINGS_SUCCESS)
        ଯାଅ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ଯଦି (BYTES_ବାମ (&buffer) < pad_len)
        {
          result = XSETTINGS_ACCESS;
          ଯାଅ out;
        }

      setting = malloc (ଆକାର *setting);
      ଯଦି (!setting)
        {
          result = XSETTINGS_NO_MEM;
          ଯାଅ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      ଯଦି (!setting->name)
        {
          result = XSETTINGS_NO_MEM;
          ଯାଅ out;
        }

      memcpy (setting->name, buffer.pos, name_len);
      setting->name[name_len] = '\0';
      buffer.pos += pad_len;

      result = fetch_card32 (&buffer, &v_int);
      ଯଦି (result != XSETTINGS_SUCCESS)
        ଯାଅ out;
      setting->last_change_serial = v_int;

      ବାଛ (type)
        {
        ସ୍ଥିତି XSETTINGS_TYPE_INT:
          result = fetch_card32 (&buffer, &v_int);
          ଯଦି (result != XSETTINGS_SUCCESS)
            ଯାଅ out;

          setting->data.v_int = (INT32)v_int;
          ଭାଙ୍ଗ;
        ସ୍ଥିତି XSETTINGS_TYPE_STRING:
          result = fetch_card32 (&buffer, &v_int);
          ଯଦି (result != XSETTINGS_SUCCESS)
            ଯାଅ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ଯଦି (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_ବାମ (&buffer) < pad_len)
            {
              result = XSETTINGS_ACCESS;
              ଯାଅ out;
            }

          setting->data.v_string = malloc (v_int + 1);
          ଯଦି (!setting->data.v_string)
            {
              result = XSETTINGS_NO_MEM;
              ଯାଅ out;
            }

          memcpy (setting->data.v_string, buffer.pos, v_int);
          setting->data.v_string[v_int] = '\0';
          buffer.pos += pad_len;

          ଭାଙ୍ଗ;
        ସ୍ଥିତି XSETTINGS_TYPE_COLOR:
          result = fetch_ushort (&buffer, &setting->data.v_color.red);
          ଯଦି (result != XSETTINGS_SUCCESS)
            ଯାଅ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.green);
          ଯଦି (result != XSETTINGS_SUCCESS)
            ଯାଅ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.blue);
          ଯଦି (result != XSETTINGS_SUCCESS)
            ଯାଅ out;
          result = fetch_ushort (&buffer, &setting->data.v_color.alpha);
          ଯଦି (result != XSETTINGS_SUCCESS)
            ଯାଅ out;

          ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
          /* Quietly ignore unknown types */
          ଭାଙ୍ଗ;
        }

      setting->type = type;

      result = xsettings_list_ଭର୍ତ୍ତି (&settings, setting);
      ଯଦି (result != XSETTINGS_SUCCESS)
        ଯାଅ out;

      setting = ଖାଲି;
    }

 out:

  ଯଦି (result != XSETTINGS_SUCCESS)
    {
      ବାଛ (result)
        {
        ସ୍ଥିତି XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          ଭାଙ୍ଗ;
        ସ୍ଥିତି XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          ଭାଙ୍ଗ;
        ସ୍ଥିତି XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        ସ୍ଥିତି XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        ସ୍ଥିତି XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        ସ୍ଥିତି XSETTINGS_NO_ENTRY:
          ଭାଙ୍ଗ;
        }

      ଯଦି (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ଖାଲି;

    }

  ଫେରନ୍ତୁ settings;
}

ସ୍ଥିର ଶୂନ୍ୟ
read_settings (XSettingsClient *client)
{
  Atom type;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା format;
  unsigned long n_ବସ୍ତୁଗୁଡ଼ିକ;
  unsigned long bytes_after;
  unsigned ଅକ୍ଷର *data;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ଖାଲି;

  ଯଦି (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      result = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_ବସ୍ତୁଗୁଡ଼ିକ, &bytes_after, &data);
      X11_XSetErrorHandler (old_handler);

      ଯଦି (result == Success && type != None)
        {
          ଯଦି (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          ଅନ୍ୟଥା ଯଦି (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          ଅନ୍ୟଥା
            client->settings = parse_settings (data, n_ବସ୍ତୁଗୁଡ଼ିକ);

          X11_XFree (data);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ସ୍ଥିର ଶୂନ୍ୟ
add_events (Display *display,
            Window   window,
            long     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_ନିବେଶ (display, window, attr.your_event_mask | mask);
}

ସ୍ଥିର ଶୂନ୍ୟ
check_manager_window (XSettingsClient *client)
{
  ଯଦି (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  ଯଦି (client->grab)
    client->grab (client->display);
  ଅନ୍ୟଥା
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ଯଦି (client->manager_window)
    X11_XSelect_ନିବେଶ (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  ଯଦି (client->ungrab)
    client->ungrab (client->display);
  ଅନ୍ୟଥା
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ଯଦି (client->manager_window && client->watch)
    {
      ଯଦି (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_data))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          ଫେରନ୍ତୁ;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      ଶୂନ୍ୟ                *cb_data)
{
  ଫେରନ୍ତୁ xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_data,
                                               ଖାଲି, ଖାଲି);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      ଶୂନ୍ୟ                *cb_data,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  ଅକ୍ଷର buffer[256];
  ଅକ୍ଷର *atom_names[3];
  Atom atoms[3];

  client = malloc (ଆକାର *client);
  ଯଦି (!client)
    ଫେରନ୍ତୁ ଖାଲି;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_data = cb_data;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = ଖାଲି;

  SDL_snprintf(buffer, ଆକାର(buffer), "_XSETTINGS_S%d", screen);
  atom_names[0] = buffer;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#ifdef HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#ଅନ୍ୟଥା
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#endif

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, ମୂଳ_Window (display, screen), StructureNotifyMask);

  ଯଦି (client->watch)
    client->watch (ମୂଳ_Window (display, screen), True, StructureNotifyMask,
                   client->cb_data);

  check_manager_window (client);

  ଫେରନ୍ତୁ client;
}


ଶୂନ୍ୟ
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

ଶୂନ୍ୟ
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

ଶୂନ୍ୟ
xsettings_client_destroy (XSettingsClient *client)
{
  ଯଦି (client->watch)
    client->watch (ମୂଳ_Window (client->display, client->screen),
                   False, 0, client->cb_data);
  ଯଦି (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_data);

  xsettings_list_free (client->settings);
  ମୁକ୍ତ (client);
}

XSettingsResult
xsettings_client_get_setting (XSettingsClient   *client,
                              ଅଚଳ ଅକ୍ଷର        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *ସନ୍ଧାନ = xsettings_list_lookup (client->settings, name);
  ଯଦି (ସନ୍ଧାନ)
    {
      *setting = xsettings_setting_copy (ସନ୍ଧାନ);
      ଫେରନ୍ତୁ *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ଅଚଳ XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ଯଦି (xev->xany.window == ମୂଳ_Window (client->display, client->screen))
    {
      ଯଦି (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.data.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          ଫେରନ୍ତୁ True;
        }
    }
  ଅନ୍ୟଥା ଯଦି (xev->xany.window == client->manager_window)
    {
      ଯଦି (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          ଫେରନ୍ତୁ False;
        }
      ଅନ୍ୟଥା ଯଦି (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ଫେରନ୍ତୁ True;
        }
    }

  ଫେରନ୍ତୁ False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *result;
  size_t str_len;

  result = malloc (ଆକାର *result);
  ଯଦି (!result)
    ଫେରନ୍ତୁ ଖାଲି;

  str_len = strlen (setting->name);
  result->name = malloc (str_len + 1);
  ଯଦି (!result->name)
    ଯାଅ err;

  memcpy (result->name, setting->name, str_len + 1);

  result->type = setting->type;

  ବାଛ (setting->type)
    {
    ସ୍ଥିତି XSETTINGS_TYPE_INT:
      result->data.v_int = setting->data.v_int;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି XSETTINGS_TYPE_COLOR:
      result->data.v_color = setting->data.v_color;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->data.v_string);
      result->data.v_string = malloc (str_len + 1);
      ଯଦି (!result->data.v_string)
        ଯାଅ err;

      memcpy (result->data.v_string, setting->data.v_string, str_len + 1);
      ଭାଙ୍ଗ;
    }

  result->last_change_serial = setting->last_change_serial;

  ଫେରନ୍ତୁ result;

 err:
  ମୁକ୍ତ(result->name); // This should NOT be SDL_free()
  ମୁକ୍ତ(result); // This should NOT be SDL_free()

  ଫେରନ୍ତୁ ଖାଲି;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ଖାଲି;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ଖାଲି;

  ଯେତେବେଳେ (old_iter)
    {
      XSettingsList *new_ଗଣ୍ଠି;

      new_ଗଣ୍ଠି = malloc (ଆକାର *new_ଗଣ୍ଠି);
      ଯଦି (!new_ଗଣ୍ଠି)
        ଯାଅ error;

      new_ଗଣ୍ଠି->setting = xsettings_setting_copy (old_iter->setting);
      ଯଦି (!new_ଗଣ୍ଠି->setting)
        {
          ମୁକ୍ତ (new_ଗଣ୍ଠି);
          ଯାଅ error;
        }

      ଯଦି (new_iter)
        new_iter->next = new_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
        {
          new = new_ଗଣ୍ଠି;
          new->next = ଖାଲି;
        }


      new_iter = new_ଗଣ୍ଠି;

      old_iter = old_iter->next;
    }

  ଫେରନ୍ତୁ new;

 error:
  xsettings_list_free (new);
  ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ଯଦି (setting_a->type != setting_b->type)
    ଫେରନ୍ତୁ 0;

  ଯଦି (strcmp (setting_a->name, setting_b->name) != 0)
    ଫେରନ୍ତୁ 0;

  ବାଛ (setting_a->type)
    {
    ସ୍ଥିତି XSETTINGS_TYPE_INT:
      ଫେରନ୍ତୁ setting_a->data.v_int == setting_b->data.v_int;
    ସ୍ଥିତି XSETTINGS_TYPE_COLOR:
      ଫେରନ୍ତୁ (setting_a->data.v_color.red == setting_b->data.v_color.red &&
              setting_a->data.v_color.green == setting_b->data.v_color.green &&
              setting_a->data.v_color.blue == setting_b->data.v_color.blue &&
              setting_a->data.v_color.alpha == setting_b->data.v_color.alpha);
    ସ୍ଥିତି XSETTINGS_TYPE_STRING:
      ଫେରନ୍ତୁ strcmp (setting_a->data.v_string, setting_b->data.v_string) == 0;
    }

  ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ
xsettings_setting_free (XSettingsSetting *setting)
{
  ଯଦି (setting->type == XSETTINGS_TYPE_STRING)
    ମୁକ୍ତ (setting->data.v_string);

  ମୁକ୍ତ(setting->name); // This should NOT be SDL_free()
  ମୁକ୍ତ(setting); // This should NOT be SDL_free()
}

ଶୂନ୍ୟ
xsettings_list_free (XSettingsList *list)
{
  ଯେତେବେଳେ (list)
    {
      XSettingsList *next = list->next;

      xsettings_setting_free (list->setting);
      ମୁକ୍ତ (list);

      list = next;
    }
}

XSettingsResult
xsettings_list_ଭର୍ତ୍ତି (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ଗଣ୍ଠି;
  XSettingsList *iter;
  XSettingsList *last = ଖାଲି;

  ଗଣ୍ଠି = malloc (ଆକାର *ଗଣ୍ଠି);
  ଯଦି (!ଗଣ୍ଠି)
    ଫେରନ୍ତୁ XSETTINGS_NO_MEM;
  ଗଣ୍ଠି->setting = setting;

  iter = *list;
  ଯେତେବେଳେ (iter)
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmp = strcmp (setting->name, iter->setting->name);

      ଯଦି (cmp < 0)
        ଭାଙ୍ଗ;
      ଅନ୍ୟଥା ଯଦି (cmp == 0)
        {
          ମୁକ୍ତ (ଗଣ୍ଠି);
          ଫେରନ୍ତୁ XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->next;
    }

  ଯଦି (last)
    last->next = ଗଣ୍ଠି;
  ଅନ୍ୟଥା
    *list = ଗଣ୍ଠି;

  ଗଣ୍ଠି->next = iter;

  ଫେରନ୍ତୁ XSETTINGS_SUCCESS;
}

XSettingsResult
xsettings_list_delete (XSettingsList **list,
                       ଅଚଳ ଅକ୍ଷର     *name)
{
  XSettingsList *iter;
  XSettingsList *last = ଖାଲି;

  iter = *list;
  ଯେତେବେଳେ (iter)
    {
      ଯଦି (strcmp (name, iter->setting->name) == 0)
        {
          ଯଦି (last)
            last->next = iter->next;
          ଅନ୍ୟଥା
            *list = iter->next;

          xsettings_setting_free (iter->setting);
          ମୁକ୍ତ (iter);

          ଫେରନ୍ତୁ XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->next;
    }

  ଫେରନ୍ତୁ XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ଅଚଳ ଅକ୍ଷର    *name)
{
  XSettingsList *iter;

  iter = list;
  ଯେତେବେଳେ (iter)
    {
      ଯଦି (strcmp (name, iter->setting->name) == 0)
        ଫେରନ୍ତୁ iter->setting;

      iter = iter->next;
    }

  ଫେରନ୍ତୁ ଖାଲି;
}

ଅକ୍ଷର
xsettings_byte_order (ଶୂନ୍ୟ)
{
  CARD32 myint = 0x01020304;
  ଫେରନ୍ତୁ (*(ଅକ୍ଷର *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

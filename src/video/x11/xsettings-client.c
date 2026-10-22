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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব "SDL_x11video.h"

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "xsettings-client.h"

কাঠামো _XSettingsClient
{
  Display *display;
  পূর্ণসংখ্যা screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  শূন্য *cb_তথ্য;

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
    ফেরত;

  যখন (old_iter || new_iter)
    {
      পূর্ণসংখ্যা cmp;

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
                          ফাঁকা,
                          client->cb_তথ্য);
        }
      অন্যথা যদি (cmp == 0)
        {
          যদি (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_তথ্য);
        }
      অন্যথা
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_তথ্য);
        }

      যদি (old_iter)
        old_iter = old_iter->পরবর্তী;
      যদি (new_iter)
        new_iter = new_iter->পরবর্তী;
    }
}

স্থির পূর্ণসংখ্যা
ignore_errors (Display *display, XErrorEvent *event)
{
  ফেরত True;
}

স্থির অক্ষর local_byte_order = '\0';

#define BYTES_বাম(বাফার_2) ((বাফার_2)->তথ্য + (বাফার_2)->len - (বাফার_2)->pos)

স্থির XSettings_ফলাফল
fetch_card16 (XSettings_বাফার *বাফার_2,
              CARD16          *ফলাফল)
{
  CARD16 x;

  যদি (BYTES_বাম (বাফার_2) < 2)
    ফেরত XSETTINGS_ACCESS;

  x = *(CARD16 *)বাফার_2->pos;
  বাফার_2->pos += 2;

  যদি (বাফার_2->byte_order == local_byte_order)
    *ফলাফল = x;
  অন্যথা
    *ফলাফল = (x << 8) | (x >> 8);

  ফেরত XSETTINGS_SUCCESS;
}

স্থির XSettings_ফলাফল
fetch_ushort (XSettings_বাফার *বাফার_2,
              unsigned short  *ফলাফল)
{
  CARD16 x;
  XSettings_ফলাফল r;

  r = fetch_card16 (বাফার_2, &x);
  যদি (r == XSETTINGS_SUCCESS)
    *ফলাফল = x;

  ফেরত r;
}

স্থির XSettings_ফলাফল
fetch_card32 (XSettings_বাফার *বাফার_2,
              CARD32          *ফলাফল)
{
  CARD32 x;

  যদি (BYTES_বাম (বাফার_2) < 4)
    ফেরত XSETTINGS_ACCESS;

  x = *(CARD32 *)বাফার_2->pos;
  বাফার_2->pos += 4;

  যদি (বাফার_2->byte_order == local_byte_order)
    *ফলাফল = x;
  অন্যথা
    *ফলাফল = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  ফেরত XSETTINGS_SUCCESS;
}

স্থির XSettings_ফলাফল
fetch_card8 (XSettings_বাফার *বাফার_2,
             CARD8           *ফলাফল)
{
  যদি (BYTES_বাম (বাফার_2) < 1)
    ফেরত XSETTINGS_ACCESS;

  *ফলাফল = *(CARD8 *)বাফার_2->pos;
  বাফার_2->pos += 1;

  ফেরত XSETTINGS_SUCCESS;
}

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

স্থির XSettingsList *
parse_settings (unsigned অক্ষর *তথ্য,
                size_t         len)
{
  XSettings_বাফার বাফার_2;
  XSettings_ফলাফল ফলাফল = XSETTINGS_SUCCESS;
  XSettingsList *settings = ফাঁকা;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ফাঁকা;
  অক্ষর বাফার_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  বাফার_2.pos = বাফার_2.তথ্য = তথ্য;
  বাফার_2.len = len;
  বাফার_2.byte_order = '\0';

  ফলাফল = fetch_card8 (&বাফার_2, (unsigned অক্ষর *) &বাফার_byte_order);
  যদি (বাফার_byte_order != MSBFirst &&
      বাফার_byte_order != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      ফলাফল = XSETTINGS_FAILED;
      যাও out;
    }

  বাফার_2.byte_order = বাফার_byte_order;
  বাফার_2.pos += 3;

  ফলাফল = fetch_card32 (&বাফার_2, &serial);
  যদি (ফলাফল != XSETTINGS_SUCCESS)
    যাও out;

  ফলাফল = fetch_card32 (&বাফার_2, &n_entries);
  যদি (ফলাফল != XSETTINGS_SUCCESS)
    যাও out;

  জন্য (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      ফলাফল = fetch_card8 (&বাফার_2, &type);
      যদি (ফলাফল != XSETTINGS_SUCCESS)
        যাও out;

      বাফার_2.pos += 1;

      ফলাফল = fetch_card16 (&বাফার_2, &name_len);
      যদি (ফলাফল != XSETTINGS_SUCCESS)
        যাও out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      যদি (BYTES_বাম (&বাফার_2) < pad_len)
        {
          ফলাফল = XSETTINGS_ACCESS;
          যাও out;
        }

      setting = malloc (আকার *setting);
      যদি (!setting)
        {
          ফলাফল = XSETTINGS_NO_MEM;
          যাও out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = malloc (name_len + 1);
      যদি (!setting->name)
        {
          ফলাফল = XSETTINGS_NO_MEM;
          যাও out;
        }

      memcpy (setting->name, বাফার_2.pos, name_len);
      setting->name[name_len] = '\0';
      বাফার_2.pos += pad_len;

      ফলাফল = fetch_card32 (&বাফার_2, &v_int);
      যদি (ফলাফল != XSETTINGS_SUCCESS)
        যাও out;
      setting->last_change_serial = v_int;

      নির্বাচন (type)
        {
        ক্ষেত্র XSETTINGS_TYPE_INT:
          ফলাফল = fetch_card32 (&বাফার_2, &v_int);
          যদি (ফলাফল != XSETTINGS_SUCCESS)
            যাও out;

          setting->তথ্য.v_int = (INT32)v_int;
          বিরতি;
        ক্ষেত্র XSETTINGS_TYPE_STRING:
          ফলাফল = fetch_card32 (&বাফার_2, &v_int);
          যদি (ফলাফল != XSETTINGS_SUCCESS)
            যাও out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          যদি (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_বাম (&বাফার_2) < pad_len)
            {
              ফলাফল = XSETTINGS_ACCESS;
              যাও out;
            }

          setting->তথ্য.v_string = malloc (v_int + 1);
          যদি (!setting->তথ্য.v_string)
            {
              ফলাফল = XSETTINGS_NO_MEM;
              যাও out;
            }

          memcpy (setting->তথ্য.v_string, বাফার_2.pos, v_int);
          setting->তথ্য.v_string[v_int] = '\0';
          বাফার_2.pos += pad_len;

          বিরতি;
        ক্ষেত্র XSETTINGS_TYPE_COLOR:
          ফলাফল = fetch_ushort (&বাফার_2, &setting->তথ্য.v_color.red);
          যদি (ফলাফল != XSETTINGS_SUCCESS)
            যাও out;
          ফলাফল = fetch_ushort (&বাফার_2, &setting->তথ্য.v_color.green);
          যদি (ফলাফল != XSETTINGS_SUCCESS)
            যাও out;
          ফলাফল = fetch_ushort (&বাফার_2, &setting->তথ্য.v_color.blue);
          যদি (ফলাফল != XSETTINGS_SUCCESS)
            যাও out;
          ফলাফল = fetch_ushort (&বাফার_2, &setting->তথ্য.v_color.alpha);
          যদি (ফলাফল != XSETTINGS_SUCCESS)
            যাও out;

          বিরতি;
        পূর্বনির্ধারিত:
          /* Quietly ignore unknown types */
          বিরতি;
        }

      setting->type = type;

      ফলাফল = xsettings_list_ঢোকাও (&settings, setting);
      যদি (ফলাফল != XSETTINGS_SUCCESS)
        যাও out;

      setting = ফাঁকা;
    }

 out:

  যদি (ফলাফল != XSETTINGS_SUCCESS)
    {
      নির্বাচন (ফলাফল)
        {
        ক্ষেত্র XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          বিরতি;
        ক্ষেত্র XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          বিরতি;
        ক্ষেত্র XSETTINGS_DUPLICATE_ENTRY:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        ক্ষেত্র XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        ক্ষেত্র XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        ক্ষেত্র XSETTINGS_NO_ENTRY:
          বিরতি;
        }

      যদি (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ফাঁকা;

    }

  ফেরত settings;
}

স্থির শূন্য
read_settings (XSettingsClient *client)
{
  Atom type;
  পূর্ণসংখ্যা format;
  unsigned long n_বস্তুসমূহ;
  unsigned long bytes_after;
  unsigned অক্ষর *তথ্য;
  পূর্ণসংখ্যা ফলাফল;

  পূর্ণসংখ্যা (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ফাঁকা;

  যদি (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      ফলাফল = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_বস্তুসমূহ, &bytes_after, &তথ্য);
      X11_XSetErrorHandler (old_handler);

      যদি (ফলাফল == Success && type != None)
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
            client->settings = parse_settings (তথ্য, n_বস্তুসমূহ);

          X11_XFree (তথ্য);
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
  X11_XSelect_প্রবেশ (display, window, attr.your_event_mask | mask);
}

স্থির শূন্য
check_manager_window (XSettingsClient *client)
{
  যদি (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_তথ্য);

  যদি (client->grab)
    client->grab (client->display);
  অন্যথা
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  যদি (client->manager_window)
    X11_XSelect_প্রবেশ (client->display, client->manager_window,
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
                          client->cb_তথ্য))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          ফেরত;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      পূর্ণসংখ্যা                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      শূন্য                *cb_তথ্য)
{
  ফেরত xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_তথ্য,
                                               ফাঁকা, ফাঁকা);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      পূর্ণসংখ্যা                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      শূন্য                *cb_তথ্য,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  অক্ষর বাফার_2[256];
  অক্ষর *atom_names[3];
  Atom atoms[3];

  client = malloc (আকার *client);
  যদি (!client)
    ফেরত ফাঁকা;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_তথ্য = cb_তথ্য;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = ফাঁকা;

  SDL_snprintf(বাফার_2, আকার(বাফার_2), "_XSETTINGS_S%d", screen);
  atom_names[0] = বাফার_2;
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
                   client->cb_তথ্য);

  check_manager_window (client);

  ফেরত client;
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
                   False, 0, client->cb_তথ্য);
  যদি (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_তথ্য);

  xsettings_list_free (client->settings);
  মুক্ত (client);
}

XSettings_ফলাফল
xsettings_client_get_setting (XSettingsClient   *client,
                              ধ্রুবক অক্ষর        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *অনুসন্ধান = xsettings_list_lookup (client->settings, name);
  যদি (অনুসন্ধান)
    {
      *setting = xsettings_setting_copy (অনুসন্ধান);
      ফেরত *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  অন্যথা
    ফেরত XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                ধ্রুবক XEvent    *xev)
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
          xev->xclient.তথ্য.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          ফেরত True;
        }
    }
  অন্যথা যদি (xev->xany.window == client->manager_window)
    {
      যদি (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          ফেরত False;
        }
      অন্যথা যদি (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          ফেরত True;
        }
    }

  ফেরত False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *ফলাফল;
  size_t str_len;

  ফলাফল = malloc (আকার *ফলাফল);
  যদি (!ফলাফল)
    ফেরত ফাঁকা;

  str_len = strlen (setting->name);
  ফলাফল->name = malloc (str_len + 1);
  যদি (!ফলাফল->name)
    যাও err;

  memcpy (ফলাফল->name, setting->name, str_len + 1);

  ফলাফল->type = setting->type;

  নির্বাচন (setting->type)
    {
    ক্ষেত্র XSETTINGS_TYPE_INT:
      ফলাফল->তথ্য.v_int = setting->তথ্য.v_int;
      বিরতি;
    ক্ষেত্র XSETTINGS_TYPE_COLOR:
      ফলাফল->তথ্য.v_color = setting->তথ্য.v_color;
      বিরতি;
    ক্ষেত্র XSETTINGS_TYPE_STRING:
      str_len = strlen (setting->তথ্য.v_string);
      ফলাফল->তথ্য.v_string = malloc (str_len + 1);
      যদি (!ফলাফল->তথ্য.v_string)
        যাও err;

      memcpy (ফলাফল->তথ্য.v_string, setting->তথ্য.v_string, str_len + 1);
      বিরতি;
    }

  ফলাফল->last_change_serial = setting->last_change_serial;

  ফেরত ফলাফল;

 err:
  মুক্ত(ফলাফল->name); // This should NOT be SDL_free()
  মুক্ত(ফলাফল); // This should NOT be SDL_free()

  ফেরত ফাঁকা;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ফাঁকা;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ফাঁকা;

  যখন (old_iter)
    {
      XSettingsList *new_গ্রন্থি;

      new_গ্রন্থি = malloc (আকার *new_গ্রন্থি);
      যদি (!new_গ্রন্থি)
        যাও error;

      new_গ্রন্থি->setting = xsettings_setting_copy (old_iter->setting);
      যদি (!new_গ্রন্থি->setting)
        {
          মুক্ত (new_গ্রন্থি);
          যাও error;
        }

      যদি (new_iter)
        new_iter->পরবর্তী = new_গ্রন্থি;
      অন্যথা
        {
          new = new_গ্রন্থি;
          new->পরবর্তী = ফাঁকা;
        }


      new_iter = new_গ্রন্থি;

      old_iter = old_iter->পরবর্তী;
    }

  ফেরত new;

 error:
  xsettings_list_free (new);
  ফেরত ফাঁকা;
}

পূর্ণসংখ্যা
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  যদি (setting_a->type != setting_b->type)
    ফেরত 0;

  যদি (strcmp (setting_a->name, setting_b->name) != 0)
    ফেরত 0;

  নির্বাচন (setting_a->type)
    {
    ক্ষেত্র XSETTINGS_TYPE_INT:
      ফেরত setting_a->তথ্য.v_int == setting_b->তথ্য.v_int;
    ক্ষেত্র XSETTINGS_TYPE_COLOR:
      ফেরত (setting_a->তথ্য.v_color.red == setting_b->তথ্য.v_color.red &&
              setting_a->তথ্য.v_color.green == setting_b->তথ্য.v_color.green &&
              setting_a->তথ্য.v_color.blue == setting_b->তথ্য.v_color.blue &&
              setting_a->তথ্য.v_color.alpha == setting_b->তথ্য.v_color.alpha);
    ক্ষেত্র XSETTINGS_TYPE_STRING:
      ফেরত strcmp (setting_a->তথ্য.v_string, setting_b->তথ্য.v_string) == 0;
    }

  ফেরত 0;
}

শূন্য
xsettings_setting_free (XSettingsSetting *setting)
{
  যদি (setting->type == XSETTINGS_TYPE_STRING)
    মুক্ত (setting->তথ্য.v_string);

  মুক্ত(setting->name); // This should NOT be SDL_free()
  মুক্ত(setting); // This should NOT be SDL_free()
}

শূন্য
xsettings_list_free (XSettingsList *list)
{
  যখন (list)
    {
      XSettingsList *পরবর্তী = list->পরবর্তী;

      xsettings_setting_free (list->setting);
      মুক্ত (list);

      list = পরবর্তী;
    }
}

XSettings_ফলাফল
xsettings_list_ঢোকাও (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *গ্রন্থি;
  XSettingsList *iter;
  XSettingsList *last = ফাঁকা;

  গ্রন্থি = malloc (আকার *গ্রন্থি);
  যদি (!গ্রন্থি)
    ফেরত XSETTINGS_NO_MEM;
  গ্রন্থি->setting = setting;

  iter = *list;
  যখন (iter)
    {
      পূর্ণসংখ্যা cmp = strcmp (setting->name, iter->setting->name);

      যদি (cmp < 0)
        বিরতি;
      অন্যথা যদি (cmp == 0)
        {
          মুক্ত (গ্রন্থি);
          ফেরত XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->পরবর্তী;
    }

  যদি (last)
    last->পরবর্তী = গ্রন্থি;
  অন্যথা
    *list = গ্রন্থি;

  গ্রন্থি->পরবর্তী = iter;

  ফেরত XSETTINGS_SUCCESS;
}

XSettings_ফলাফল
xsettings_list_delete (XSettingsList **list,
                       ধ্রুবক অক্ষর     *name)
{
  XSettingsList *iter;
  XSettingsList *last = ফাঁকা;

  iter = *list;
  যখন (iter)
    {
      যদি (strcmp (name, iter->setting->name) == 0)
        {
          যদি (last)
            last->পরবর্তী = iter->পরবর্তী;
          অন্যথা
            *list = iter->পরবর্তী;

          xsettings_setting_free (iter->setting);
          মুক্ত (iter);

          ফেরত XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->পরবর্তী;
    }

  ফেরত XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ধ্রুবক অক্ষর    *name)
{
  XSettingsList *iter;

  iter = list;
  যখন (iter)
    {
      যদি (strcmp (name, iter->setting->name) == 0)
        ফেরত iter->setting;

      iter = iter->পরবর্তী;
    }

  ফেরত ফাঁকা;
}

অক্ষর
xsettings_byte_order (শূন্য)
{
  CARD32 myint = 0x01020304;
  ফেরত (*(অক্ষর *)&myint == 1) ? MSBFirst : LSBFirst;
}

#endif /* SDL_VIDEO_DRIVER_X11 */

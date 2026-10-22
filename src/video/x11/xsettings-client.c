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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11video.h"

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "xsettings-client.h"

నిర్మాణం _XSettingsClient
{
  Display *display;
  పూర్ణాంకం screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  శూన్య *cb_దత్తాంశం;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  కిటికీ_2 manager_కిటికీ;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

స్థిర శూన్య
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  ఒకవేళ (!client->notify)
    తిరిగి;

  అయితే (old_iter || new_iter)
    {
      పూర్ణాంకం cmp;

      ఒకవేళ (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      లేకపోతే ఒకవేళ (old_iter)
        cmp = -1;
      లేకపోతే
        cmp = 1;

      ఒకవేళ (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          ఖాళీ,
                          client->cb_దత్తాంశం);
        }
      లేకపోతే ఒకవేళ (cmp == 0)
        {
          ఒకవేళ (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_మారింది,
                            new_iter->setting,
                            client->cb_దత్తాంశం);
        }
      లేకపోతే
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_దత్తాంశం);
        }

      ఒకవేళ (old_iter)
        old_iter = old_iter->తదుపరి;
      ఒకవేళ (new_iter)
        new_iter = new_iter->తదుపరి;
    }
}

స్థిర పూర్ణాంకం
ignore_errors (Display *display, XErrorEvent *event)
{
  తిరిగి True;
}

స్థిర అక్షరం local_byte_క్రమం = '\0';

#నిర్వచించు బైట్లు_ఎడమ_2(బఫరు_2) ((బఫరు_2)->దత్తాంశం + (బఫరు_2)->len - (బఫరు_2)->pos)

స్థిర XSettings_ఫలితం
fetch_card16 (XSettings_బఫరు *బఫరు_2,
              CARD16          *ఫలితం)
{
  CARD16 x;

  ఒకవేళ (బైట్లు_ఎడమ_2 (బఫరు_2) < 2)
    తిరిగి XSETTINGS_ACCESS;

  x = *(CARD16 *)బఫరు_2->pos;
  బఫరు_2->pos += 2;

  ఒకవేళ (బఫరు_2->byte_క్రమం == local_byte_క్రమం)
    *ఫలితం = x;
  లేకపోతే
    *ఫలితం = (x << 8) | (x >> 8);

  తిరిగి XSETTINGS_SUCCESS;
}

స్థిర XSettings_ఫలితం
fetch_ushort (XSettings_బఫరు *బఫరు_2,
              గుర్తులేని పొట్టి  *ఫలితం)
{
  CARD16 x;
  XSettings_ఫలితం r;

  r = fetch_card16 (బఫరు_2, &x);
  ఒకవేళ (r == XSETTINGS_SUCCESS)
    *ఫలితం = x;

  తిరిగి r;
}

స్థిర XSettings_ఫలితం
fetch_card32 (XSettings_బఫరు *బఫరు_2,
              CARD32          *ఫలితం)
{
  CARD32 x;

  ఒకవేళ (బైట్లు_ఎడమ_2 (బఫరు_2) < 4)
    తిరిగి XSETTINGS_ACCESS;

  x = *(CARD32 *)బఫరు_2->pos;
  బఫరు_2->pos += 4;

  ఒకవేళ (బఫరు_2->byte_క్రమం == local_byte_క్రమం)
    *ఫలితం = x;
  లేకపోతే
    *ఫలితం = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  తిరిగి XSETTINGS_SUCCESS;
}

స్థిర XSettings_ఫలితం
fetch_card8 (XSettings_బఫరు *బఫరు_2,
             CARD8           *ఫలితం)
{
  ఒకవేళ (బైట్లు_ఎడమ_2 (బఫరు_2) < 1)
    తిరిగి XSETTINGS_ACCESS;

  *ఫలితం = *(CARD8 *)బఫరు_2->pos;
  బఫరు_2->pos += 1;

  తిరిగి XSETTINGS_SUCCESS;
}

#నిర్వచించు XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

స్థిర XSettingsList *
parse_settings (గుర్తులేని అక్షరం *దత్తాంశం,
                size_t         len)
{
  XSettings_బఫరు బఫరు_2;
  XSettings_ఫలితం ఫలితం = XSETTINGS_SUCCESS;
  XSettingsList *settings = ఖాళీ;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = ఖాళీ;
  అక్షరం బఫరు_byte_క్రమం = '\0';

  local_byte_క్రమం = xsettings_byte_క్రమం ();

  బఫరు_2.pos = బఫరు_2.దత్తాంశం = దత్తాంశం;
  బఫరు_2.len = len;
  బఫరు_2.byte_క్రమం = '\0';

  ఫలితం = fetch_card8 (&బఫరు_2, (గుర్తులేని అక్షరం *) &బఫరు_byte_క్రమం);
  ఒకవేళ (బఫరు_byte_క్రమం != MSBFirst &&
      బఫరు_byte_క్రమం != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      ఫలితం = XSETTINGS_FAILED;
      వెళ్ళు బహిర్గతం;
    }

  బఫరు_2.byte_క్రమం = బఫరు_byte_క్రమం;
  బఫరు_2.pos += 3;

  ఫలితం = fetch_card32 (&బఫరు_2, &serial);
  ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
    వెళ్ళు బహిర్గతం;

  ఫలితం = fetch_card32 (&బఫరు_2, &n_entries);
  ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
    వెళ్ళు బహిర్గతం;

  కొరకు (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      ఫలితం = fetch_card8 (&బఫరు_2, &type);
      ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
        వెళ్ళు బహిర్గతం;

      బఫరు_2.pos += 1;

      ఫలితం = fetch_card16 (&బఫరు_2, &name_len);
      ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
        వెళ్ళు బహిర్గతం;

      pad_len = XSETTINGS_PAD(name_len, 4);
      ఒకవేళ (బైట్లు_ఎడమ_2 (&బఫరు_2) < pad_len)
        {
          ఫలితం = XSETTINGS_ACCESS;
          వెళ్ళు బహిర్గతం;
        }

      setting = జ్ఞాపకం_ఇవ్వు (పరిమాణం *setting);
      ఒకవేళ (!setting)
        {
          ఫలితం = XSETTINGS_NO_MEM;
          వెళ్ళు బహిర్గతం;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = జ్ఞాపకం_ఇవ్వు (name_len + 1);
      ఒకవేళ (!setting->name)
        {
          ఫలితం = XSETTINGS_NO_MEM;
          వెళ్ళు బహిర్గతం;
        }

      జ్ఞాపకం_నకలు (setting->name, బఫరు_2.pos, name_len);
      setting->name[name_len] = '\0';
      బఫరు_2.pos += pad_len;

      ఫలితం = fetch_card32 (&బఫరు_2, &v_int);
      ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
        వెళ్ళు బహిర్గతం;
      setting->చివరి_change_serial = v_int;

      ఎంపిక (type)
        {
        స్థితి XSETTINGS_TYPE_INT:
          ఫలితం = fetch_card32 (&బఫరు_2, &v_int);
          ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
            వెళ్ళు బహిర్గతం;

          setting->దత్తాంశం.v_int = (INT32)v_int;
          ఆపు;
        స్థితి XSETTINGS_TYPE_STRING:
          ఫలితం = fetch_card32 (&బఫరు_2, &v_int);
          ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
            వెళ్ళు బహిర్గతం;

          pad_len = XSETTINGS_PAD (v_int, 4);
          ఒకవేళ (v_int + 1 == 0 || /* Guard against wrap-around */
              బైట్లు_ఎడమ_2 (&బఫరు_2) < pad_len)
            {
              ఫలితం = XSETTINGS_ACCESS;
              వెళ్ళు బహిర్గతం;
            }

          setting->దత్తాంశం.v_string = జ్ఞాపకం_ఇవ్వు (v_int + 1);
          ఒకవేళ (!setting->దత్తాంశం.v_string)
            {
              ఫలితం = XSETTINGS_NO_MEM;
              వెళ్ళు బహిర్గతం;
            }

          జ్ఞాపకం_నకలు (setting->దత్తాంశం.v_string, బఫరు_2.pos, v_int);
          setting->దత్తాంశం.v_string[v_int] = '\0';
          బఫరు_2.pos += pad_len;

          ఆపు;
        స్థితి XSETTINGS_TYPE_COLOR:
          ఫలితం = fetch_ushort (&బఫరు_2, &setting->దత్తాంశం.v_color.red);
          ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
            వెళ్ళు బహిర్గతం;
          ఫలితం = fetch_ushort (&బఫరు_2, &setting->దత్తాంశం.v_color.green);
          ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
            వెళ్ళు బహిర్గతం;
          ఫలితం = fetch_ushort (&బఫరు_2, &setting->దత్తాంశం.v_color.blue);
          ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
            వెళ్ళు బహిర్గతం;
          ఫలితం = fetch_ushort (&బఫరు_2, &setting->దత్తాంశం.v_color.alpha);
          ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
            వెళ్ళు బహిర్గతం;

          ఆపు;
        అప్రమేయ:
          /* Quietly ignore unknown types */
          ఆపు;
        }

      setting->type = type;

      ఫలితం = xsettings_list_చొప్పించు (&settings, setting);
      ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
        వెళ్ళు బహిర్గతం;

      setting = ఖాళీ;
    }

 బహిర్గతం:

  ఒకవేళ (ఫలితం != XSETTINGS_SUCCESS)
    {
      ఎంపిక (ఫలితం)
        {
        స్థితి XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          ఆపు;
        స్థితి XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          ఆపు;
        స్థితి XSETTINGS_DUPLICATE_నమోదు:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        స్థితి XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        స్థితి XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        స్థితి XSETTINGS_NO_నమోదు:
          ఆపు;
        }

      ఒకవేళ (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = ఖాళీ;

    }

  తిరిగి settings;
}

స్థిర శూన్య
read_settings (XSettingsClient *client)
{
  Atom type;
  పూర్ణాంకం format;
  గుర్తులేని దీర్ఘ n_వస్తువులు;
  గుర్తులేని దీర్ఘ బైట్లు_after;
  గుర్తులేని అక్షరం *దత్తాంశం;
  పూర్ణాంకం ఫలితం;

  పూర్ణాంకం (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = ఖాళీ;

  ఒకవేళ (client->manager_కిటికీ)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      ఫలితం = X11_XGet_కిటికీ_Property (client->display, client->manager_కిటికీ,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_వస్తువులు, &బైట్లు_after, &దత్తాంశం);
      X11_XSetErrorHandler (old_handler);

      ఒకవేళ (ఫలితం == Success && type != None)
        {
          ఒకవేళ (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          లేకపోతే ఒకవేళ (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          లేకపోతే
            client->settings = parse_settings (దత్తాంశం, n_వస్తువులు);

          X11_XFree (దత్తాంశం);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

స్థిర శూన్య
కూడు_events (Display *display,
            కిటికీ_2   కిటికీ,
            దీర్ఘ     ముసుగు)
{
  XWindow_లక్షణాలు attr;

  X11_XGet_కిటికీ_లక్షణాలు (display, కిటికీ, &attr);
  X11_XSelect_ఆదానం (display, కిటికీ, attr.your_event_ముసుగు | ముసుగు);
}

స్థిర శూన్య
check_manager_కిటికీ (XSettingsClient *client)
{
  ఒకవేళ (client->manager_కిటికీ && client->watch)
    client->watch (client->manager_కిటికీ, False, 0, client->cb_దత్తాంశం);

  ఒకవేళ (client->grab)
    client->grab (client->display);
  లేకపోతే
    X11_XGrabServer (client->display);

  client->manager_కిటికీ = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  ఒకవేళ (client->manager_కిటికీ)
    X11_XSelect_ఆదానం (client->display, client->manager_కిటికీ,
                      Property_Change_ముసుగు | Structure_Notify_ముసుగు);

  ఒకవేళ (client->ungrab)
    client->ungrab (client->display);
  లేకపోతే
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  ఒకవేళ (client->manager_కిటికీ && client->watch)
    {
      ఒకవేళ (!client->watch (client->manager_కిటికీ, True,
                          Property_Change_ముసుగు | Structure_Notify_ముసుగు,
                          client->cb_దత్తాంశం))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_కిటికీ = None;
          తిరిగి;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      పూర్ణాంకం                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      శూన్య                *cb_దత్తాంశం)
{
  తిరిగి xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_దత్తాంశం,
                                               ఖాళీ, ఖాళీ);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      పూర్ణాంకం                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      శూన్య                *cb_దత్తాంశం,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  అక్షరం బఫరు_2[256];
  అక్షరం *atom_పేర్లు[3];
  Atom atoms[3];

  client = జ్ఞాపకం_ఇవ్వు (పరిమాణం *client);
  ఒకవేళ (!client)
    తిరిగి ఖాళీ;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_దత్తాంశం = cb_దత్తాంశం;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_కిటికీ = None;
  client->settings = ఖాళీ;

  SDL_snprintf(బఫరు_2, పరిమాణం(బఫరు_2), "_XSETTINGS_S%d", screen);
  atom_పేర్లు[0] = బఫరు_2;
  atom_పేర్లు[1] = "_XSETTINGS_SETTINGS";
  atom_పేర్లు[2] = "MANAGER";

#నిర్వచితమైతే HAVE_XINTERNATOMS
  XInternAtoms (display, atom_పేర్లు, 3, False, atoms);
#లేకపోతే
  atoms[0] = X11_XInternAtom (display, atom_పేర్లు[0], False);
  atoms[1] = X11_XInternAtom (display, atom_పేర్లు[1], False);
  atoms[2] = X11_XInternAtom (display, atom_పేర్లు[2], False);
#అయితే_ముగింపు

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  కూడు_events (display, మూలం_కిటికీ (display, screen), Structure_Notify_ముసుగు);

  ఒకవేళ (client->watch)
    client->watch (మూలం_కిటికీ (display, screen), True, Structure_Notify_ముసుగు,
                   client->cb_దత్తాంశం);

  check_manager_కిటికీ (client);

  తిరిగి client;
}


శూన్య
xsettings_client_సమితి_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

శూన్య
xsettings_client_సమితి_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

శూన్య
xsettings_client_destroy (XSettingsClient *client)
{
  ఒకవేళ (client->watch)
    client->watch (మూలం_కిటికీ (client->display, client->screen),
                   False, 0, client->cb_దత్తాంశం);
  ఒకవేళ (client->manager_కిటికీ && client->watch)
    client->watch (client->manager_కిటికీ, False, 0, client->cb_దత్తాంశం);

  xsettings_list_free (client->settings);
  విడుదల (client);
}

XSettings_ఫలితం
xsettings_client_get_setting (XSettingsClient   *client,
                              స్థిరరాశి అక్షరం        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *శోధన = xsettings_list_lookup (client->settings, name);
  ఒకవేళ (శోధన)
    {
      *setting = xsettings_setting_copy (శోధన);
      తిరిగి *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  లేకపోతే
    తిరిగి XSETTINGS_NO_నమోదు;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                స్థిరరాశి XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  ఒకవేళ (xev->xany.కిటికీ == మూలం_కిటికీ (client->display, client->screen))
    {
      ఒకవేళ (xev->xany.type == Client_సందేశం &&
          xev->xclient.సందేశం_type == client->manager_atom &&
          xev->xclient.దత్తాంశం.l[1] == client->selection_atom)
        {
          check_manager_కిటికీ (client);
          తిరిగి True;
        }
    }
  లేకపోతే ఒకవేళ (xev->xany.కిటికీ == client->manager_కిటికీ)
    {
      ఒకవేళ (xev->xany.type == DestroyNotify)
        {
          check_manager_కిటికీ (client);
          తిరిగి False;
        }
      లేకపోతే ఒకవేళ (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          తిరిగి True;
        }
    }

  తిరిగి False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *ఫలితం;
  size_t str_len;

  ఫలితం = జ్ఞాపకం_ఇవ్వు (పరిమాణం *ఫలితం);
  ఒకవేళ (!ఫలితం)
    తిరిగి ఖాళీ;

  str_len = అక్షరశ్రేణి_పొడవు (setting->name);
  ఫలితం->name = జ్ఞాపకం_ఇవ్వు (str_len + 1);
  ఒకవేళ (!ఫలితం->name)
    వెళ్ళు err;

  జ్ఞాపకం_నకలు (ఫలితం->name, setting->name, str_len + 1);

  ఫలితం->type = setting->type;

  ఎంపిక (setting->type)
    {
    స్థితి XSETTINGS_TYPE_INT:
      ఫలితం->దత్తాంశం.v_int = setting->దత్తాంశం.v_int;
      ఆపు;
    స్థితి XSETTINGS_TYPE_COLOR:
      ఫలితం->దత్తాంశం.v_color = setting->దత్తాంశం.v_color;
      ఆపు;
    స్థితి XSETTINGS_TYPE_STRING:
      str_len = అక్షరశ్రేణి_పొడవు (setting->దత్తాంశం.v_string);
      ఫలితం->దత్తాంశం.v_string = జ్ఞాపకం_ఇవ్వు (str_len + 1);
      ఒకవేళ (!ఫలితం->దత్తాంశం.v_string)
        వెళ్ళు err;

      జ్ఞాపకం_నకలు (ఫలితం->దత్తాంశం.v_string, setting->దత్తాంశం.v_string, str_len + 1);
      ఆపు;
    }

  ఫలితం->చివరి_change_serial = setting->చివరి_change_serial;

  తిరిగి ఫలితం;

 err:
  విడుదల(ఫలితం->name); // This should NOT be SDL_free()
  విడుదల(ఫలితం); // This should NOT be SDL_free()

  తిరిగి ఖాళీ;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = ఖాళీ;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = ఖాళీ;

  అయితే (old_iter)
    {
      XSettingsList *new_కణుపు;

      new_కణుపు = జ్ఞాపకం_ఇవ్వు (పరిమాణం *new_కణుపు);
      ఒకవేళ (!new_కణుపు)
        వెళ్ళు error;

      new_కణుపు->setting = xsettings_setting_copy (old_iter->setting);
      ఒకవేళ (!new_కణుపు->setting)
        {
          విడుదల (new_కణుపు);
          వెళ్ళు error;
        }

      ఒకవేళ (new_iter)
        new_iter->తదుపరి = new_కణుపు;
      లేకపోతే
        {
          new = new_కణుపు;
          new->తదుపరి = ఖాళీ;
        }


      new_iter = new_కణుపు;

      old_iter = old_iter->తదుపరి;
    }

  తిరిగి new;

 error:
  xsettings_list_free (new);
  తిరిగి ఖాళీ;
}

పూర్ణాంకం
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  ఒకవేళ (setting_a->type != setting_b->type)
    తిరిగి 0;

  ఒకవేళ (strcmp (setting_a->name, setting_b->name) != 0)
    తిరిగి 0;

  ఎంపిక (setting_a->type)
    {
    స్థితి XSETTINGS_TYPE_INT:
      తిరిగి setting_a->దత్తాంశం.v_int == setting_b->దత్తాంశం.v_int;
    స్థితి XSETTINGS_TYPE_COLOR:
      తిరిగి (setting_a->దత్తాంశం.v_color.red == setting_b->దత్తాంశం.v_color.red &&
              setting_a->దత్తాంశం.v_color.green == setting_b->దత్తాంశం.v_color.green &&
              setting_a->దత్తాంశం.v_color.blue == setting_b->దత్తాంశం.v_color.blue &&
              setting_a->దత్తాంశం.v_color.alpha == setting_b->దత్తాంశం.v_color.alpha);
    స్థితి XSETTINGS_TYPE_STRING:
      తిరిగి strcmp (setting_a->దత్తాంశం.v_string, setting_b->దత్తాంశం.v_string) == 0;
    }

  తిరిగి 0;
}

శూన్య
xsettings_setting_free (XSettingsSetting *setting)
{
  ఒకవేళ (setting->type == XSETTINGS_TYPE_STRING)
    విడుదల (setting->దత్తాంశం.v_string);

  విడుదల(setting->name); // This should NOT be SDL_free()
  విడుదల(setting); // This should NOT be SDL_free()
}

శూన్య
xsettings_list_free (XSettingsList *list)
{
  అయితే (list)
    {
      XSettingsList *తదుపరి = list->తదుపరి;

      xsettings_setting_free (list->setting);
      విడుదల (list);

      list = తదుపరి;
    }
}

XSettings_ఫలితం
xsettings_list_చొప్పించు (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *కణుపు;
  XSettingsList *iter;
  XSettingsList *చివరి = ఖాళీ;

  కణుపు = జ్ఞాపకం_ఇవ్వు (పరిమాణం *కణుపు);
  ఒకవేళ (!కణుపు)
    తిరిగి XSETTINGS_NO_MEM;
  కణుపు->setting = setting;

  iter = *list;
  అయితే (iter)
    {
      పూర్ణాంకం cmp = strcmp (setting->name, iter->setting->name);

      ఒకవేళ (cmp < 0)
        ఆపు;
      లేకపోతే ఒకవేళ (cmp == 0)
        {
          విడుదల (కణుపు);
          తిరిగి XSETTINGS_DUPLICATE_నమోదు;
        }

      చివరి = iter;
      iter = iter->తదుపరి;
    }

  ఒకవేళ (చివరి)
    చివరి->తదుపరి = కణుపు;
  లేకపోతే
    *list = కణుపు;

  కణుపు->తదుపరి = iter;

  తిరిగి XSETTINGS_SUCCESS;
}

XSettings_ఫలితం
xsettings_list_delete (XSettingsList **list,
                       స్థిరరాశి అక్షరం     *name)
{
  XSettingsList *iter;
  XSettingsList *చివరి = ఖాళీ;

  iter = *list;
  అయితే (iter)
    {
      ఒకవేళ (strcmp (name, iter->setting->name) == 0)
        {
          ఒకవేళ (చివరి)
            చివరి->తదుపరి = iter->తదుపరి;
          లేకపోతే
            *list = iter->తదుపరి;

          xsettings_setting_free (iter->setting);
          విడుదల (iter);

          తిరిగి XSETTINGS_SUCCESS;
        }

      చివరి = iter;
      iter = iter->తదుపరి;
    }

  తిరిగి XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       స్థిరరాశి అక్షరం    *name)
{
  XSettingsList *iter;

  iter = list;
  అయితే (iter)
    {
      ఒకవేళ (strcmp (name, iter->setting->name) == 0)
        తిరిగి iter->setting;

      iter = iter->తదుపరి;
    }

  తిరిగి ఖాళీ;
}

అక్షరం
xsettings_byte_క్రమం (శూన్య)
{
  CARD32 myint = 0x01020304;
  తిరిగి (*(అక్షరం *)&myint == 1) ? MSBFirst : LSBFirst;
}

#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11 */

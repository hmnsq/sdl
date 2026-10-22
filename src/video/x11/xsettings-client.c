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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل "SDL_x11video.h"

#شامل <limits.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>

#شامل "xsettings-client.h"

ساخت _XSettingsClient
{
  Display *display;
  صحیح screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  خالی *cb_ڈیٹا;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  کھڑکی_2 manager_کھڑکی;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ساکن خالی
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  اگر (!client->notify)
    واپس;

  جب (old_iter || new_iter)
    {
      صحیح cmp;

      اگر (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      ورنہ اگر (old_iter)
        cmp = -1;
      ورنہ
        cmp = 1;

      اگر (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          تہی,
                          client->cb_ڈیٹا);
        }
      ورنہ اگر (cmp == 0)
        {
          اگر (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_بدلا,
                            new_iter->setting,
                            client->cb_ڈیٹا);
        }
      ورنہ
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_ڈیٹا);
        }

      اگر (old_iter)
        old_iter = old_iter->اگلا;
      اگر (new_iter)
        new_iter = new_iter->اگلا;
    }
}

ساکن صحیح
ignore_errors (Display *display, XErrorEvent *event)
{
  واپس True;
}

ساکن حرف local_byte_ترتیب = '\0';

#تعریف_کرو بائٹیں_بایاں_2(بفر_2) ((بفر_2)->ڈیٹا + (بفر_2)->len - (بفر_2)->pos)

ساکن XSettings_نتیجہ
fetch_card16 (XSettings_بفر *بفر_2,
              CARD16          *نتیجہ)
{
  CARD16 x;

  اگر (بائٹیں_بایاں_2 (بفر_2) < 2)
    واپس XSETTINGS_ACCESS;

  x = *(CARD16 *)بفر_2->pos;
  بفر_2->pos += 2;

  اگر (بفر_2->byte_ترتیب == local_byte_ترتیب)
    *نتیجہ = x;
  ورنہ
    *نتیجہ = (x << 8) | (x >> 8);

  واپس XSETTINGS_SUCCESS;
}

ساکن XSettings_نتیجہ
fetch_ushort (XSettings_بفر *بفر_2,
              غیرعلامتی مختصر  *نتیجہ)
{
  CARD16 x;
  XSettings_نتیجہ r;

  r = fetch_card16 (بفر_2, &x);
  اگر (r == XSETTINGS_SUCCESS)
    *نتیجہ = x;

  واپس r;
}

ساکن XSettings_نتیجہ
fetch_card32 (XSettings_بفر *بفر_2,
              CARD32          *نتیجہ)
{
  CARD32 x;

  اگر (بائٹیں_بایاں_2 (بفر_2) < 4)
    واپس XSETTINGS_ACCESS;

  x = *(CARD32 *)بفر_2->pos;
  بفر_2->pos += 4;

  اگر (بفر_2->byte_ترتیب == local_byte_ترتیب)
    *نتیجہ = x;
  ورنہ
    *نتیجہ = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  واپس XSETTINGS_SUCCESS;
}

ساکن XSettings_نتیجہ
fetch_card8 (XSettings_بفر *بفر_2,
             CARD8           *نتیجہ)
{
  اگر (بائٹیں_بایاں_2 (بفر_2) < 1)
    واپس XSETTINGS_ACCESS;

  *نتیجہ = *(CARD8 *)بفر_2->pos;
  بفر_2->pos += 1;

  واپس XSETTINGS_SUCCESS;
}

#تعریف_کرو XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ساکن XSettingsList *
parse_settings (غیرعلامتی حرف *ڈیٹا,
                size_t         len)
{
  XSettings_بفر بفر_2;
  XSettings_نتیجہ نتیجہ = XSETTINGS_SUCCESS;
  XSettingsList *settings = تہی;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = تہی;
  حرف بفر_byte_ترتیب = '\0';

  local_byte_ترتیب = xsettings_byte_ترتیب ();

  بفر_2.pos = بفر_2.ڈیٹا = ڈیٹا;
  بفر_2.len = len;
  بفر_2.byte_ترتیب = '\0';

  نتیجہ = fetch_card8 (&بفر_2, (غیرعلامتی حرف *) &بفر_byte_ترتیب);
  اگر (بفر_byte_ترتیب != MSBFirst &&
      بفر_byte_ترتیب != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      نتیجہ = XSETTINGS_FAILED;
      جاؤ برآمد;
    }

  بفر_2.byte_ترتیب = بفر_byte_ترتیب;
  بفر_2.pos += 3;

  نتیجہ = fetch_card32 (&بفر_2, &serial);
  اگر (نتیجہ != XSETTINGS_SUCCESS)
    جاؤ برآمد;

  نتیجہ = fetch_card32 (&بفر_2, &n_entries);
  اگر (نتیجہ != XSETTINGS_SUCCESS)
    جاؤ برآمد;

  برائے (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      نتیجہ = fetch_card8 (&بفر_2, &type);
      اگر (نتیجہ != XSETTINGS_SUCCESS)
        جاؤ برآمد;

      بفر_2.pos += 1;

      نتیجہ = fetch_card16 (&بفر_2, &name_len);
      اگر (نتیجہ != XSETTINGS_SUCCESS)
        جاؤ برآمد;

      pad_len = XSETTINGS_PAD(name_len, 4);
      اگر (بائٹیں_بایاں_2 (&بفر_2) < pad_len)
        {
          نتیجہ = XSETTINGS_ACCESS;
          جاؤ برآمد;
        }

      setting = حافظہ_دو (حجم *setting);
      اگر (!setting)
        {
          نتیجہ = XSETTINGS_NO_MEM;
          جاؤ برآمد;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = حافظہ_دو (name_len + 1);
      اگر (!setting->name)
        {
          نتیجہ = XSETTINGS_NO_MEM;
          جاؤ برآمد;
        }

      حافظہ_نقل (setting->name, بفر_2.pos, name_len);
      setting->name[name_len] = '\0';
      بفر_2.pos += pad_len;

      نتیجہ = fetch_card32 (&بفر_2, &v_int);
      اگر (نتیجہ != XSETTINGS_SUCCESS)
        جاؤ برآمد;
      setting->آخری_change_serial = v_int;

      انتخاب (type)
        {
        حالت XSETTINGS_TYPE_INT:
          نتیجہ = fetch_card32 (&بفر_2, &v_int);
          اگر (نتیجہ != XSETTINGS_SUCCESS)
            جاؤ برآمد;

          setting->ڈیٹا.v_int = (INT32)v_int;
          توڑو;
        حالت XSETTINGS_TYPE_STRING:
          نتیجہ = fetch_card32 (&بفر_2, &v_int);
          اگر (نتیجہ != XSETTINGS_SUCCESS)
            جاؤ برآمد;

          pad_len = XSETTINGS_PAD (v_int, 4);
          اگر (v_int + 1 == 0 || /* Guard against wrap-around */
              بائٹیں_بایاں_2 (&بفر_2) < pad_len)
            {
              نتیجہ = XSETTINGS_ACCESS;
              جاؤ برآمد;
            }

          setting->ڈیٹا.v_string = حافظہ_دو (v_int + 1);
          اگر (!setting->ڈیٹا.v_string)
            {
              نتیجہ = XSETTINGS_NO_MEM;
              جاؤ برآمد;
            }

          حافظہ_نقل (setting->ڈیٹا.v_string, بفر_2.pos, v_int);
          setting->ڈیٹا.v_string[v_int] = '\0';
          بفر_2.pos += pad_len;

          توڑو;
        حالت XSETTINGS_TYPE_COLOR:
          نتیجہ = fetch_ushort (&بفر_2, &setting->ڈیٹا.v_color.red);
          اگر (نتیجہ != XSETTINGS_SUCCESS)
            جاؤ برآمد;
          نتیجہ = fetch_ushort (&بفر_2, &setting->ڈیٹا.v_color.green);
          اگر (نتیجہ != XSETTINGS_SUCCESS)
            جاؤ برآمد;
          نتیجہ = fetch_ushort (&بفر_2, &setting->ڈیٹا.v_color.blue);
          اگر (نتیجہ != XSETTINGS_SUCCESS)
            جاؤ برآمد;
          نتیجہ = fetch_ushort (&بفر_2, &setting->ڈیٹا.v_color.alpha);
          اگر (نتیجہ != XSETTINGS_SUCCESS)
            جاؤ برآمد;

          توڑو;
        طےشدہ:
          /* Quietly ignore unknown types */
          توڑو;
        }

      setting->type = type;

      نتیجہ = xsettings_list_داخل_کرو (&settings, setting);
      اگر (نتیجہ != XSETTINGS_SUCCESS)
        جاؤ برآمد;

      setting = تہی;
    }

 برآمد:

  اگر (نتیجہ != XSETTINGS_SUCCESS)
    {
      انتخاب (نتیجہ)
        {
        حالت XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          توڑو;
        حالت XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          توڑو;
        حالت XSETTINGS_DUPLICATE_اندراج:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالت XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالت XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالت XSETTINGS_NO_اندراج:
          توڑو;
        }

      اگر (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = تہی;

    }

  واپس settings;
}

ساکن خالی
read_settings (XSettingsClient *client)
{
  Atom type;
  صحیح format;
  غیرعلامتی طویل n_اشیاء;
  غیرعلامتی طویل بائٹیں_after;
  غیرعلامتی حرف *ڈیٹا;
  صحیح نتیجہ;

  صحیح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = تہی;

  اگر (client->manager_کھڑکی)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      نتیجہ = X11_XGet_کھڑکی_Property (client->display, client->manager_کھڑکی,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_اشیاء, &بائٹیں_after, &ڈیٹا);
      X11_XSetErrorHandler (old_handler);

      اگر (نتیجہ == Success && type != None)
        {
          اگر (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          ورنہ اگر (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          ورنہ
            client->settings = parse_settings (ڈیٹا, n_اشیاء);

          X11_XFree (ڈیٹا);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ساکن خالی
جوڑو_events (Display *display,
            کھڑکی_2   کھڑکی,
            طویل     نقاب)
{
  XWindow_اوصاف attr;

  X11_XGet_کھڑکی_اوصاف (display, کھڑکی, &attr);
  X11_XSelect_داخلہ (display, کھڑکی, attr.your_event_نقاب | نقاب);
}

ساکن خالی
check_manager_کھڑکی (XSettingsClient *client)
{
  اگر (client->manager_کھڑکی && client->watch)
    client->watch (client->manager_کھڑکی, False, 0, client->cb_ڈیٹا);

  اگر (client->grab)
    client->grab (client->display);
  ورنہ
    X11_XGrabServer (client->display);

  client->manager_کھڑکی = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  اگر (client->manager_کھڑکی)
    X11_XSelect_داخلہ (client->display, client->manager_کھڑکی,
                      Property_Change_نقاب | Structure_Notify_نقاب);

  اگر (client->ungrab)
    client->ungrab (client->display);
  ورنہ
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  اگر (client->manager_کھڑکی && client->watch)
    {
      اگر (!client->watch (client->manager_کھڑکی, True,
                          Property_Change_نقاب | Structure_Notify_نقاب,
                          client->cb_ڈیٹا))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_کھڑکی = None;
          واپس;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      صحیح                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      خالی                *cb_ڈیٹا)
{
  واپس xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_ڈیٹا,
                                               تہی, تہی);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      صحیح                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      خالی                *cb_ڈیٹا,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  حرف بفر_2[256];
  حرف *atom_نام[3];
  Atom atoms[3];

  client = حافظہ_دو (حجم *client);
  اگر (!client)
    واپس تہی;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_ڈیٹا = cb_ڈیٹا;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_کھڑکی = None;
  client->settings = تہی;

  SDL_snprintf(بفر_2, حجم(بفر_2), "_XSETTINGS_S%d", screen);
  atom_نام[0] = بفر_2;
  atom_نام[1] = "_XSETTINGS_SETTINGS";
  atom_نام[2] = "MANAGER";

#اگر_تعریف_شدہ HAVE_XINTERNATOMS
  XInternAtoms (display, atom_نام, 3, False, atoms);
#ورنہ
  atoms[0] = X11_XInternAtom (display, atom_نام[0], False);
  atoms[1] = X11_XInternAtom (display, atom_نام[1], False);
  atoms[2] = X11_XInternAtom (display, atom_نام[2], False);
#اگر_ختم

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  جوڑو_events (display, جڑ_کھڑکی (display, screen), Structure_Notify_نقاب);

  اگر (client->watch)
    client->watch (جڑ_کھڑکی (display, screen), True, Structure_Notify_نقاب,
                   client->cb_ڈیٹا);

  check_manager_کھڑکی (client);

  واپس client;
}


خالی
xsettings_client_سیٹ_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

خالی
xsettings_client_سیٹ_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

خالی
xsettings_client_destroy (XSettingsClient *client)
{
  اگر (client->watch)
    client->watch (جڑ_کھڑکی (client->display, client->screen),
                   False, 0, client->cb_ڈیٹا);
  اگر (client->manager_کھڑکی && client->watch)
    client->watch (client->manager_کھڑکی, False, 0, client->cb_ڈیٹا);

  xsettings_list_free (client->settings);
  آزاد (client);
}

XSettings_نتیجہ
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت حرف        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *تلاش = xsettings_list_lookup (client->settings, name);
  اگر (تلاش)
    {
      *setting = xsettings_setting_copy (تلاش);
      واپس *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  ورنہ
    واپس XSETTINGS_NO_اندراج;
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
  اگر (xev->xany.کھڑکی == جڑ_کھڑکی (client->display, client->screen))
    {
      اگر (xev->xany.type == Client_پیغام &&
          xev->xclient.پیغام_type == client->manager_atom &&
          xev->xclient.ڈیٹا.l[1] == client->selection_atom)
        {
          check_manager_کھڑکی (client);
          واپس True;
        }
    }
  ورنہ اگر (xev->xany.کھڑکی == client->manager_کھڑکی)
    {
      اگر (xev->xany.type == DestroyNotify)
        {
          check_manager_کھڑکی (client);
          واپس False;
        }
      ورنہ اگر (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          واپس True;
        }
    }

  واپس False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *نتیجہ;
  size_t str_len;

  نتیجہ = حافظہ_دو (حجم *نتیجہ);
  اگر (!نتیجہ)
    واپس تہی;

  str_len = لڑی_لمبائی (setting->name);
  نتیجہ->name = حافظہ_دو (str_len + 1);
  اگر (!نتیجہ->name)
    جاؤ err;

  حافظہ_نقل (نتیجہ->name, setting->name, str_len + 1);

  نتیجہ->type = setting->type;

  انتخاب (setting->type)
    {
    حالت XSETTINGS_TYPE_INT:
      نتیجہ->ڈیٹا.v_int = setting->ڈیٹا.v_int;
      توڑو;
    حالت XSETTINGS_TYPE_COLOR:
      نتیجہ->ڈیٹا.v_color = setting->ڈیٹا.v_color;
      توڑو;
    حالت XSETTINGS_TYPE_STRING:
      str_len = لڑی_لمبائی (setting->ڈیٹا.v_string);
      نتیجہ->ڈیٹا.v_string = حافظہ_دو (str_len + 1);
      اگر (!نتیجہ->ڈیٹا.v_string)
        جاؤ err;

      حافظہ_نقل (نتیجہ->ڈیٹا.v_string, setting->ڈیٹا.v_string, str_len + 1);
      توڑو;
    }

  نتیجہ->آخری_change_serial = setting->آخری_change_serial;

  واپس نتیجہ;

 err:
  آزاد(نتیجہ->name); // This should NOT be SDL_free()
  آزاد(نتیجہ); // This should NOT be SDL_free()

  واپس تہی;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = تہی;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = تہی;

  جب (old_iter)
    {
      XSettingsList *new_گرہ;

      new_گرہ = حافظہ_دو (حجم *new_گرہ);
      اگر (!new_گرہ)
        جاؤ error;

      new_گرہ->setting = xsettings_setting_copy (old_iter->setting);
      اگر (!new_گرہ->setting)
        {
          آزاد (new_گرہ);
          جاؤ error;
        }

      اگر (new_iter)
        new_iter->اگلا = new_گرہ;
      ورنہ
        {
          new = new_گرہ;
          new->اگلا = تہی;
        }


      new_iter = new_گرہ;

      old_iter = old_iter->اگلا;
    }

  واپس new;

 error:
  xsettings_list_free (new);
  واپس تہی;
}

صحیح
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  اگر (setting_a->type != setting_b->type)
    واپس 0;

  اگر (strcmp (setting_a->name, setting_b->name) != 0)
    واپس 0;

  انتخاب (setting_a->type)
    {
    حالت XSETTINGS_TYPE_INT:
      واپس setting_a->ڈیٹا.v_int == setting_b->ڈیٹا.v_int;
    حالت XSETTINGS_TYPE_COLOR:
      واپس (setting_a->ڈیٹا.v_color.red == setting_b->ڈیٹا.v_color.red &&
              setting_a->ڈیٹا.v_color.green == setting_b->ڈیٹا.v_color.green &&
              setting_a->ڈیٹا.v_color.blue == setting_b->ڈیٹا.v_color.blue &&
              setting_a->ڈیٹا.v_color.alpha == setting_b->ڈیٹا.v_color.alpha);
    حالت XSETTINGS_TYPE_STRING:
      واپس strcmp (setting_a->ڈیٹا.v_string, setting_b->ڈیٹا.v_string) == 0;
    }

  واپس 0;
}

خالی
xsettings_setting_free (XSettingsSetting *setting)
{
  اگر (setting->type == XSETTINGS_TYPE_STRING)
    آزاد (setting->ڈیٹا.v_string);

  آزاد(setting->name); // This should NOT be SDL_free()
  آزاد(setting); // This should NOT be SDL_free()
}

خالی
xsettings_list_free (XSettingsList *list)
{
  جب (list)
    {
      XSettingsList *اگلا = list->اگلا;

      xsettings_setting_free (list->setting);
      آزاد (list);

      list = اگلا;
    }
}

XSettings_نتیجہ
xsettings_list_داخل_کرو (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *گرہ;
  XSettingsList *iter;
  XSettingsList *آخری = تہی;

  گرہ = حافظہ_دو (حجم *گرہ);
  اگر (!گرہ)
    واپس XSETTINGS_NO_MEM;
  گرہ->setting = setting;

  iter = *list;
  جب (iter)
    {
      صحیح cmp = strcmp (setting->name, iter->setting->name);

      اگر (cmp < 0)
        توڑو;
      ورنہ اگر (cmp == 0)
        {
          آزاد (گرہ);
          واپس XSETTINGS_DUPLICATE_اندراج;
        }

      آخری = iter;
      iter = iter->اگلا;
    }

  اگر (آخری)
    آخری->اگلا = گرہ;
  ورنہ
    *list = گرہ;

  گرہ->اگلا = iter;

  واپس XSETTINGS_SUCCESS;
}

XSettings_نتیجہ
xsettings_list_delete (XSettingsList **list,
                       ثابت حرف     *name)
{
  XSettingsList *iter;
  XSettingsList *آخری = تہی;

  iter = *list;
  جب (iter)
    {
      اگر (strcmp (name, iter->setting->name) == 0)
        {
          اگر (آخری)
            آخری->اگلا = iter->اگلا;
          ورنہ
            *list = iter->اگلا;

          xsettings_setting_free (iter->setting);
          آزاد (iter);

          واپس XSETTINGS_SUCCESS;
        }

      آخری = iter;
      iter = iter->اگلا;
    }

  واپس XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ثابت حرف    *name)
{
  XSettingsList *iter;

  iter = list;
  جب (iter)
    {
      اگر (strcmp (name, iter->setting->name) == 0)
        واپس iter->setting;

      iter = iter->اگلا;
    }

  واپس تہی;
}

حرف
xsettings_byte_ترتیب (خالی)
{
  CARD32 myint = 0x01020304;
  واپس (*(حرف *)&myint == 1) ? MSBFirst : LSBFirst;
}

#اگر_ختم /* SDL_VIDEO_DRIVER_X11 */

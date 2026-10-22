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

#ضمن "SDL_internal.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"

#ضمن <limits.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "xsettings-client.h"

بنية _XSettingsClient
{
  Display *display;
  صحيح screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  فراغ *cb_انکڑے;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  کھڑکی_2 manager_کھڑکی;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

ساكن فراغ
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  إذا (!client->notify)
    أرجع;

  طالما (old_iter || new_iter)
    {
      صحيح cmp;

      إذا (old_iter && new_iter)
        cmp = strcmp (old_iter->setting->name, new_iter->setting->name);
      وإلا إذا (old_iter)
        cmp = -1;
      وإلا
        cmp = 1;

      إذا (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          عدم,
                          client->cb_انکڑے);
        }
      وإلا إذا (cmp == 0)
        {
          إذا (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_بدلیا,
                            new_iter->setting,
                            client->cb_انکڑے);
        }
      وإلا
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_انکڑے);
        }

      إذا (old_iter)
        old_iter = old_iter->اگلا;
      إذا (new_iter)
        new_iter = new_iter->اگلا;
    }
}

ساكن صحيح
ignore_errors (Display *display, XErrorEvent *event)
{
  أرجع True;
}

ساكن حرف local_byte_ترتیب = '\0';

#تعریف_کرو بائٹاں_بایاں_2(بفر_2) ((بفر_2)->انکڑے + (بفر_2)->len - (بفر_2)->pos)

ساكن XSettings_نتیجہ
fetch_card16 (XSettings_بفر *بفر_2,
              CARD16          *نتیجہ)
{
  CARD16 x;

  إذا (بائٹاں_بایاں_2 (بفر_2) < 2)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD16 *)بفر_2->pos;
  بفر_2->pos += 2;

  إذا (بفر_2->byte_ترتیب == local_byte_ترتیب)
    *نتیجہ = x;
  وإلا
    *نتیجہ = (x << 8) | (x >> 8);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_نتیجہ
fetch_ushort (XSettings_بفر *بفر_2,
              بنانشانی چھوٹا  *نتیجہ)
{
  CARD16 x;
  XSettings_نتیجہ r;

  r = fetch_card16 (بفر_2, &x);
  إذا (r == XSETTINGS_SUCCESS)
    *نتیجہ = x;

  أرجع r;
}

ساكن XSettings_نتیجہ
fetch_card32 (XSettings_بفر *بفر_2,
              CARD32          *نتیجہ)
{
  CARD32 x;

  إذا (بائٹاں_بایاں_2 (بفر_2) < 4)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD32 *)بفر_2->pos;
  بفر_2->pos += 4;

  إذا (بفر_2->byte_ترتیب == local_byte_ترتیب)
    *نتیجہ = x;
  وإلا
    *نتیجہ = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_نتیجہ
fetch_card8 (XSettings_بفر *بفر_2,
             CARD8           *نتیجہ)
{
  إذا (بائٹاں_بایاں_2 (بفر_2) < 1)
    أرجع XSETTINGS_ACCESS;

  *نتیجہ = *(CARD8 *)بفر_2->pos;
  بفر_2->pos += 1;

  أرجع XSETTINGS_SUCCESS;
}

#تعریف_کرو XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ساكن XSettingsList *
parse_settings (بنانشانی حرف *انکڑے,
                size_t         len)
{
  XSettings_بفر بفر_2;
  XSettings_نتیجہ نتیجہ = XSETTINGS_SUCCESS;
  XSettingsList *settings = عدم;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = عدم;
  حرف بفر_byte_ترتیب = '\0';

  local_byte_ترتیب = xsettings_byte_ترتیب ();

  بفر_2.pos = بفر_2.انکڑے = انکڑے;
  بفر_2.len = len;
  بفر_2.byte_ترتیب = '\0';

  نتیجہ = fetch_card8 (&بفر_2, (بنانشانی حرف *) &بفر_byte_ترتیب);
  إذا (بفر_byte_ترتیب != MSBFirst &&
      بفر_byte_ترتیب != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      نتیجہ = XSETTINGS_FAILED;
      اذهب باہرلا;
    }

  بفر_2.byte_ترتیب = بفر_byte_ترتیب;
  بفر_2.pos += 3;

  نتیجہ = fetch_card32 (&بفر_2, &serial);
  إذا (نتیجہ != XSETTINGS_SUCCESS)
    اذهب باہرلا;

  نتیجہ = fetch_card32 (&بفر_2, &n_entries);
  إذا (نتیجہ != XSETTINGS_SUCCESS)
    اذهب باہرلا;

  لكل (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      نتیجہ = fetch_card8 (&بفر_2, &type);
      إذا (نتیجہ != XSETTINGS_SUCCESS)
        اذهب باہرلا;

      بفر_2.pos += 1;

      نتیجہ = fetch_card16 (&بفر_2, &name_len);
      إذا (نتیجہ != XSETTINGS_SUCCESS)
        اذهب باہرلا;

      pad_len = XSETTINGS_PAD(name_len, 4);
      إذا (بائٹاں_بایاں_2 (&بفر_2) < pad_len)
        {
          نتیجہ = XSETTINGS_ACCESS;
          اذهب باہرلا;
        }

      setting = حافظہ_دیو (حجم *setting);
      إذا (!setting)
        {
          نتیجہ = XSETTINGS_NO_MEM;
          اذهب باہرلا;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = حافظہ_دیو (name_len + 1);
      إذا (!setting->name)
        {
          نتیجہ = XSETTINGS_NO_MEM;
          اذهب باہرلا;
        }

      حافظہ_نقل (setting->name, بفر_2.pos, name_len);
      setting->name[name_len] = '\0';
      بفر_2.pos += pad_len;

      نتیجہ = fetch_card32 (&بفر_2, &v_int);
      إذا (نتیجہ != XSETTINGS_SUCCESS)
        اذهب باہرلا;
      setting->آخری_change_serial = v_int;

      بدل (type)
        {
        حالة XSETTINGS_TYPE_INT:
          نتیجہ = fetch_card32 (&بفر_2, &v_int);
          إذا (نتیجہ != XSETTINGS_SUCCESS)
            اذهب باہرلا;

          setting->انکڑے.v_int = (INT32)v_int;
          اكسر;
        حالة XSETTINGS_TYPE_STRING:
          نتیجہ = fetch_card32 (&بفر_2, &v_int);
          إذا (نتیجہ != XSETTINGS_SUCCESS)
            اذهب باہرلا;

          pad_len = XSETTINGS_PAD (v_int, 4);
          إذا (v_int + 1 == 0 || /* Guard against wrap-around */
              بائٹاں_بایاں_2 (&بفر_2) < pad_len)
            {
              نتیجہ = XSETTINGS_ACCESS;
              اذهب باہرلا;
            }

          setting->انکڑے.v_string = حافظہ_دیو (v_int + 1);
          إذا (!setting->انکڑے.v_string)
            {
              نتیجہ = XSETTINGS_NO_MEM;
              اذهب باہرلا;
            }

          حافظہ_نقل (setting->انکڑے.v_string, بفر_2.pos, v_int);
          setting->انکڑے.v_string[v_int] = '\0';
          بفر_2.pos += pad_len;

          اكسر;
        حالة XSETTINGS_TYPE_COLOR:
          نتیجہ = fetch_ushort (&بفر_2, &setting->انکڑے.v_color.red);
          إذا (نتیجہ != XSETTINGS_SUCCESS)
            اذهب باہرلا;
          نتیجہ = fetch_ushort (&بفر_2, &setting->انکڑے.v_color.green);
          إذا (نتیجہ != XSETTINGS_SUCCESS)
            اذهب باہرلا;
          نتیجہ = fetch_ushort (&بفر_2, &setting->انکڑے.v_color.blue);
          إذا (نتیجہ != XSETTINGS_SUCCESS)
            اذهب باہرلا;
          نتیجہ = fetch_ushort (&بفر_2, &setting->انکڑے.v_color.alpha);
          إذا (نتیجہ != XSETTINGS_SUCCESS)
            اذهب باہرلا;

          اكسر;
        افتراضي:
          /* Quietly ignore unknown types */
          اكسر;
        }

      setting->type = type;

      نتیجہ = xsettings_list_داخل_کرو (&settings, setting);
      إذا (نتیجہ != XSETTINGS_SUCCESS)
        اذهب باہرلا;

      setting = عدم;
    }

 باہرلا:

  إذا (نتیجہ != XSETTINGS_SUCCESS)
    {
      بدل (نتیجہ)
        {
        حالة XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          اكسر;
        حالة XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          اكسر;
        حالة XSETTINGS_DUPLICATE_اندراج:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالة XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_NO_اندراج:
          اكسر;
        }

      إذا (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = عدم;

    }

  أرجع settings;
}

ساكن فراغ
read_settings (XSettingsClient *client)
{
  Atom type;
  صحيح format;
  بنانشانی لما n_اشیاء;
  بنانشانی لما بائٹاں_after;
  بنانشانی حرف *انکڑے;
  صحيح نتیجہ;

  صحيح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = عدم;

  إذا (client->manager_کھڑکی)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      نتیجہ = X11_XGet_کھڑکی_Property (client->display, client->manager_کھڑکی,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_اشیاء, &بائٹاں_after, &انکڑے);
      X11_XSetErrorHandler (old_handler);

      إذا (نتیجہ == Success && type != None)
        {
          إذا (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          وإلا إذا (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          وإلا
            client->settings = parse_settings (انکڑے, n_اشیاء);

          X11_XFree (انکڑے);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ساكن فراغ
جوڑو_events (Display *display,
            کھڑکی_2   کھڑکی,
            لما     نقاب)
{
  XWindow_گن attr;

  X11_XGet_کھڑکی_گن (display, کھڑکی, &attr);
  X11_XSelect_داخلہ (display, کھڑکی, attr.your_event_نقاب | نقاب);
}

ساكن فراغ
check_manager_کھڑکی (XSettingsClient *client)
{
  إذا (client->manager_کھڑکی && client->watch)
    client->watch (client->manager_کھڑکی, False, 0, client->cb_انکڑے);

  إذا (client->grab)
    client->grab (client->display);
  وإلا
    X11_XGrabServer (client->display);

  client->manager_کھڑکی = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  إذا (client->manager_کھڑکی)
    X11_XSelect_داخلہ (client->display, client->manager_کھڑکی,
                      Property_Change_نقاب | Structure_Notify_نقاب);

  إذا (client->ungrab)
    client->ungrab (client->display);
  وإلا
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  إذا (client->manager_کھڑکی && client->watch)
    {
      إذا (!client->watch (client->manager_کھڑکی, True,
                          Property_Change_نقاب | Structure_Notify_نقاب,
                          client->cb_انکڑے))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_کھڑکی = None;
          أرجع;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      صحيح                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      فراغ                *cb_انکڑے)
{
  أرجع xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_انکڑے,
                                               عدم, عدم);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      صحيح                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      فراغ                *cb_انکڑے,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  حرف بفر_2[256];
  حرف *atom_ناں[3];
  Atom atoms[3];

  client = حافظہ_دیو (حجم *client);
  إذا (!client)
    أرجع عدم;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_انکڑے = cb_انکڑے;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_کھڑکی = None;
  client->settings = عدم;

  SDL_snprintf(بفر_2, حجم(بفر_2), "_XSETTINGS_S%d", screen);
  atom_ناں[0] = بفر_2;
  atom_ناں[1] = "_XSETTINGS_SETTINGS";
  atom_ناں[2] = "MANAGER";

#جے_تعریف_شدہ HAVE_XINTERNATOMS
  XInternAtoms (display, atom_ناں, 3, False, atoms);
#وإلا
  atoms[0] = X11_XInternAtom (display, atom_ناں[0], False);
  atoms[1] = X11_XInternAtom (display, atom_ناں[1], False);
  atoms[2] = X11_XInternAtom (display, atom_ناں[2], False);
#جے_انت

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  جوڑو_events (display, جڑ_کھڑکی (display, screen), Structure_Notify_نقاب);

  إذا (client->watch)
    client->watch (جڑ_کھڑکی (display, screen), True, Structure_Notify_نقاب,
                   client->cb_انکڑے);

  check_manager_کھڑکی (client);

  أرجع client;
}


فراغ
xsettings_client_سیٹ_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

فراغ
xsettings_client_سیٹ_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

فراغ
xsettings_client_destroy (XSettingsClient *client)
{
  إذا (client->watch)
    client->watch (جڑ_کھڑکی (client->display, client->screen),
                   False, 0, client->cb_انکڑے);
  إذا (client->manager_کھڑکی && client->watch)
    client->watch (client->manager_کھڑکی, False, 0, client->cb_انکڑے);

  xsettings_list_free (client->settings);
  حرر (client);
}

XSettings_نتیجہ
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت حرف        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *تلاش = xsettings_list_lookup (client->settings, name);
  إذا (تلاش)
    {
      *setting = xsettings_setting_copy (تلاش);
      أرجع *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  وإلا
    أرجع XSETTINGS_NO_اندراج;
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
  إذا (xev->xany.کھڑکی == جڑ_کھڑکی (client->display, client->screen))
    {
      إذا (xev->xany.type == Client_سنیہا &&
          xev->xclient.سنیہا_type == client->manager_atom &&
          xev->xclient.انکڑے.l[1] == client->selection_atom)
        {
          check_manager_کھڑکی (client);
          أرجع True;
        }
    }
  وإلا إذا (xev->xany.کھڑکی == client->manager_کھڑکی)
    {
      إذا (xev->xany.type == DestroyNotify)
        {
          check_manager_کھڑکی (client);
          أرجع False;
        }
      وإلا إذا (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          أرجع True;
        }
    }

  أرجع False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *نتیجہ;
  size_t str_len;

  نتیجہ = حافظہ_دیو (حجم *نتیجہ);
  إذا (!نتیجہ)
    أرجع عدم;

  str_len = لڑی_لمبائی (setting->name);
  نتیجہ->name = حافظہ_دیو (str_len + 1);
  إذا (!نتیجہ->name)
    اذهب err;

  حافظہ_نقل (نتیجہ->name, setting->name, str_len + 1);

  نتیجہ->type = setting->type;

  بدل (setting->type)
    {
    حالة XSETTINGS_TYPE_INT:
      نتیجہ->انکڑے.v_int = setting->انکڑے.v_int;
      اكسر;
    حالة XSETTINGS_TYPE_COLOR:
      نتیجہ->انکڑے.v_color = setting->انکڑے.v_color;
      اكسر;
    حالة XSETTINGS_TYPE_STRING:
      str_len = لڑی_لمبائی (setting->انکڑے.v_string);
      نتیجہ->انکڑے.v_string = حافظہ_دیو (str_len + 1);
      إذا (!نتیجہ->انکڑے.v_string)
        اذهب err;

      حافظہ_نقل (نتیجہ->انکڑے.v_string, setting->انکڑے.v_string, str_len + 1);
      اكسر;
    }

  نتیجہ->آخری_change_serial = setting->آخری_change_serial;

  أرجع نتیجہ;

 err:
  حرر(نتیجہ->name); // This should NOT be SDL_free()
  حرر(نتیجہ); // This should NOT be SDL_free()

  أرجع عدم;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = عدم;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = عدم;

  طالما (old_iter)
    {
      XSettingsList *new_گرہ;

      new_گرہ = حافظہ_دیو (حجم *new_گرہ);
      إذا (!new_گرہ)
        اذهب error;

      new_گرہ->setting = xsettings_setting_copy (old_iter->setting);
      إذا (!new_گرہ->setting)
        {
          حرر (new_گرہ);
          اذهب error;
        }

      إذا (new_iter)
        new_iter->اگلا = new_گرہ;
      وإلا
        {
          new = new_گرہ;
          new->اگلا = عدم;
        }


      new_iter = new_گرہ;

      old_iter = old_iter->اگلا;
    }

  أرجع new;

 error:
  xsettings_list_free (new);
  أرجع عدم;
}

صحيح
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  إذا (setting_a->type != setting_b->type)
    أرجع 0;

  إذا (strcmp (setting_a->name, setting_b->name) != 0)
    أرجع 0;

  بدل (setting_a->type)
    {
    حالة XSETTINGS_TYPE_INT:
      أرجع setting_a->انکڑے.v_int == setting_b->انکڑے.v_int;
    حالة XSETTINGS_TYPE_COLOR:
      أرجع (setting_a->انکڑے.v_color.red == setting_b->انکڑے.v_color.red &&
              setting_a->انکڑے.v_color.green == setting_b->انکڑے.v_color.green &&
              setting_a->انکڑے.v_color.blue == setting_b->انکڑے.v_color.blue &&
              setting_a->انکڑے.v_color.alpha == setting_b->انکڑے.v_color.alpha);
    حالة XSETTINGS_TYPE_STRING:
      أرجع strcmp (setting_a->انکڑے.v_string, setting_b->انکڑے.v_string) == 0;
    }

  أرجع 0;
}

فراغ
xsettings_setting_free (XSettingsSetting *setting)
{
  إذا (setting->type == XSETTINGS_TYPE_STRING)
    حرر (setting->انکڑے.v_string);

  حرر(setting->name); // This should NOT be SDL_free()
  حرر(setting); // This should NOT be SDL_free()
}

فراغ
xsettings_list_free (XSettingsList *list)
{
  طالما (list)
    {
      XSettingsList *اگلا = list->اگلا;

      xsettings_setting_free (list->setting);
      حرر (list);

      list = اگلا;
    }
}

XSettings_نتیجہ
xsettings_list_داخل_کرو (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *گرہ;
  XSettingsList *iter;
  XSettingsList *آخری = عدم;

  گرہ = حافظہ_دیو (حجم *گرہ);
  إذا (!گرہ)
    أرجع XSETTINGS_NO_MEM;
  گرہ->setting = setting;

  iter = *list;
  طالما (iter)
    {
      صحيح cmp = strcmp (setting->name, iter->setting->name);

      إذا (cmp < 0)
        اكسر;
      وإلا إذا (cmp == 0)
        {
          حرر (گرہ);
          أرجع XSETTINGS_DUPLICATE_اندراج;
        }

      آخری = iter;
      iter = iter->اگلا;
    }

  إذا (آخری)
    آخری->اگلا = گرہ;
  وإلا
    *list = گرہ;

  گرہ->اگلا = iter;

  أرجع XSETTINGS_SUCCESS;
}

XSettings_نتیجہ
xsettings_list_delete (XSettingsList **list,
                       ثابت حرف     *name)
{
  XSettingsList *iter;
  XSettingsList *آخری = عدم;

  iter = *list;
  طالما (iter)
    {
      إذا (strcmp (name, iter->setting->name) == 0)
        {
          إذا (آخری)
            آخری->اگلا = iter->اگلا;
          وإلا
            *list = iter->اگلا;

          xsettings_setting_free (iter->setting);
          حرر (iter);

          أرجع XSETTINGS_SUCCESS;
        }

      آخری = iter;
      iter = iter->اگلا;
    }

  أرجع XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ثابت حرف    *name)
{
  XSettingsList *iter;

  iter = list;
  طالما (iter)
    {
      إذا (strcmp (name, iter->setting->name) == 0)
        أرجع iter->setting;

      iter = iter->اگلا;
    }

  أرجع عدم;
}

حرف
xsettings_byte_ترتیب (فراغ)
{
  CARD32 myint = 0x01020304;
  أرجع (*(حرف *)&myint == 1) ? MSBFirst : LSBFirst;
}

#جے_انت /* SDL_VIDEO_DRIVER_X11 */

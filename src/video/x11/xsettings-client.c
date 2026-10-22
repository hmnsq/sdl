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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

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
  فراغ *cb_معلومات;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  دري_2 manager_دري;
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
                          client->cb_معلومات);
        }
      وإلا إذا (cmp == 0)
        {
          إذا (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_بدليو,
                            new_iter->setting,
                            client->cb_معلومات);
        }
      وإلا
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_معلومات);
        }

      إذا (old_iter)
        old_iter = old_iter->ايندڙ;
      إذا (new_iter)
        new_iter = new_iter->ايندڙ;
    }
}

ساكن صحيح
ignore_errors (Display *display, XErrorEvent *event)
{
  أرجع True;
}

ساكن حرف local_byte_ترتيب = '\0';

#وصف_ڪريو بائيٽون_کاٻو_2(بفر_2) ((بفر_2)->معلومات + (بفر_2)->len - (بفر_2)->pos)

ساكن XSettings_نتيجو
fetch_card16 (XSettings_بفر *بفر_2,
              CARD16          *نتيجو)
{
  CARD16 x;

  إذا (بائيٽون_کاٻو_2 (بفر_2) < 2)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD16 *)بفر_2->pos;
  بفر_2->pos += 2;

  إذا (بفر_2->byte_ترتيب == local_byte_ترتيب)
    *نتيجو = x;
  وإلا
    *نتيجو = (x << 8) | (x >> 8);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_نتيجو
fetch_ushort (XSettings_بفر *بفر_2,
              بنانشان ننڍو  *نتيجو)
{
  CARD16 x;
  XSettings_نتيجو r;

  r = fetch_card16 (بفر_2, &x);
  إذا (r == XSETTINGS_SUCCESS)
    *نتيجو = x;

  أرجع r;
}

ساكن XSettings_نتيجو
fetch_card32 (XSettings_بفر *بفر_2,
              CARD32          *نتيجو)
{
  CARD32 x;

  إذا (بائيٽون_کاٻو_2 (بفر_2) < 4)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD32 *)بفر_2->pos;
  بفر_2->pos += 4;

  إذا (بفر_2->byte_ترتيب == local_byte_ترتيب)
    *نتيجو = x;
  وإلا
    *نتيجو = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_نتيجو
fetch_card8 (XSettings_بفر *بفر_2,
             CARD8           *نتيجو)
{
  إذا (بائيٽون_کاٻو_2 (بفر_2) < 1)
    أرجع XSETTINGS_ACCESS;

  *نتيجو = *(CARD8 *)بفر_2->pos;
  بفر_2->pos += 1;

  أرجع XSETTINGS_SUCCESS;
}

#وصف_ڪريو XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ساكن XSettingsList *
parse_settings (بنانشان حرف *معلومات,
                size_t         len)
{
  XSettings_بفر بفر_2;
  XSettings_نتيجو نتيجو = XSETTINGS_SUCCESS;
  XSettingsList *settings = عدم;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = عدم;
  حرف بفر_byte_ترتيب = '\0';

  local_byte_ترتيب = xsettings_byte_ترتيب ();

  بفر_2.pos = بفر_2.معلومات = معلومات;
  بفر_2.len = len;
  بفر_2.byte_ترتيب = '\0';

  نتيجو = fetch_card8 (&بفر_2, (بنانشان حرف *) &بفر_byte_ترتيب);
  إذا (بفر_byte_ترتيب != MSBFirst &&
      بفر_byte_ترتيب != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      نتيجو = XSETTINGS_FAILED;
      اذهب ٻاهريون;
    }

  بفر_2.byte_ترتيب = بفر_byte_ترتيب;
  بفر_2.pos += 3;

  نتيجو = fetch_card32 (&بفر_2, &serial);
  إذا (نتيجو != XSETTINGS_SUCCESS)
    اذهب ٻاهريون;

  نتيجو = fetch_card32 (&بفر_2, &n_entries);
  إذا (نتيجو != XSETTINGS_SUCCESS)
    اذهب ٻاهريون;

  لكل (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      نتيجو = fetch_card8 (&بفر_2, &type);
      إذا (نتيجو != XSETTINGS_SUCCESS)
        اذهب ٻاهريون;

      بفر_2.pos += 1;

      نتيجو = fetch_card16 (&بفر_2, &name_len);
      إذا (نتيجو != XSETTINGS_SUCCESS)
        اذهب ٻاهريون;

      pad_len = XSETTINGS_PAD(name_len, 4);
      إذا (بائيٽون_کاٻو_2 (&بفر_2) < pad_len)
        {
          نتيجو = XSETTINGS_ACCESS;
          اذهب ٻاهريون;
        }

      setting = يادگيري_ڏيو (حجم *setting);
      إذا (!setting)
        {
          نتيجو = XSETTINGS_NO_MEM;
          اذهب ٻاهريون;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = يادگيري_ڏيو (name_len + 1);
      إذا (!setting->name)
        {
          نتيجو = XSETTINGS_NO_MEM;
          اذهب ٻاهريون;
        }

      يادگيري_نقل (setting->name, بفر_2.pos, name_len);
      setting->name[name_len] = '\0';
      بفر_2.pos += pad_len;

      نتيجو = fetch_card32 (&بفر_2, &v_int);
      إذا (نتيجو != XSETTINGS_SUCCESS)
        اذهب ٻاهريون;
      setting->آخري_change_serial = v_int;

      بدل (type)
        {
        حالة XSETTINGS_TYPE_INT:
          نتيجو = fetch_card32 (&بفر_2, &v_int);
          إذا (نتيجو != XSETTINGS_SUCCESS)
            اذهب ٻاهريون;

          setting->معلومات.v_int = (INT32)v_int;
          اكسر;
        حالة XSETTINGS_TYPE_STRING:
          نتيجو = fetch_card32 (&بفر_2, &v_int);
          إذا (نتيجو != XSETTINGS_SUCCESS)
            اذهب ٻاهريون;

          pad_len = XSETTINGS_PAD (v_int, 4);
          إذا (v_int + 1 == 0 || /* Guard against wrap-around */
              بائيٽون_کاٻو_2 (&بفر_2) < pad_len)
            {
              نتيجو = XSETTINGS_ACCESS;
              اذهب ٻاهريون;
            }

          setting->معلومات.v_string = يادگيري_ڏيو (v_int + 1);
          إذا (!setting->معلومات.v_string)
            {
              نتيجو = XSETTINGS_NO_MEM;
              اذهب ٻاهريون;
            }

          يادگيري_نقل (setting->معلومات.v_string, بفر_2.pos, v_int);
          setting->معلومات.v_string[v_int] = '\0';
          بفر_2.pos += pad_len;

          اكسر;
        حالة XSETTINGS_TYPE_COLOR:
          نتيجو = fetch_ushort (&بفر_2, &setting->معلومات.v_color.red);
          إذا (نتيجو != XSETTINGS_SUCCESS)
            اذهب ٻاهريون;
          نتيجو = fetch_ushort (&بفر_2, &setting->معلومات.v_color.green);
          إذا (نتيجو != XSETTINGS_SUCCESS)
            اذهب ٻاهريون;
          نتيجو = fetch_ushort (&بفر_2, &setting->معلومات.v_color.blue);
          إذا (نتيجو != XSETTINGS_SUCCESS)
            اذهب ٻاهريون;
          نتيجو = fetch_ushort (&بفر_2, &setting->معلومات.v_color.alpha);
          إذا (نتيجو != XSETTINGS_SUCCESS)
            اذهب ٻاهريون;

          اكسر;
        افتراضي:
          /* Quietly ignore unknown types */
          اكسر;
        }

      setting->type = type;

      نتيجو = xsettings_list_وجهو (&settings, setting);
      إذا (نتيجو != XSETTINGS_SUCCESS)
        اذهب ٻاهريون;

      setting = عدم;
    }

 ٻاهريون:

  إذا (نتيجو != XSETTINGS_SUCCESS)
    {
      بدل (نتيجو)
        {
        حالة XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          اكسر;
        حالة XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          اكسر;
        حالة XSETTINGS_DUPLICATE_داخلا:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالة XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_NO_داخلا:
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
  بنانشان ڊگهو n_شيون;
  بنانشان ڊگهو بائيٽون_after;
  بنانشان حرف *معلومات;
  صحيح نتيجو;

  صحيح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = عدم;

  إذا (client->manager_دري)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      نتيجو = X11_XGet_دري_Property (client->display, client->manager_دري,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_شيون, &بائيٽون_after, &معلومات);
      X11_XSetErrorHandler (old_handler);

      إذا (نتيجو == Success && type != None)
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
            client->settings = parse_settings (معلومات, n_شيون);

          X11_XFree (معلومات);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ساكن فراغ
جوڙيو_events (Display *display,
            دري_2   دري,
            ڊگهو     نقاب)
{
  XWindow_خاصيتون attr;

  X11_XGet_دري_خاصيتون (display, دري, &attr);
  X11_XSelect_داخلا (display, دري, attr.your_event_نقاب | نقاب);
}

ساكن فراغ
check_manager_دري (XSettingsClient *client)
{
  إذا (client->manager_دري && client->watch)
    client->watch (client->manager_دري, False, 0, client->cb_معلومات);

  إذا (client->grab)
    client->grab (client->display);
  وإلا
    X11_XGrabServer (client->display);

  client->manager_دري = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  إذا (client->manager_دري)
    X11_XSelect_داخلا (client->display, client->manager_دري,
                      Property_Change_نقاب | Structure_Notify_نقاب);

  إذا (client->ungrab)
    client->ungrab (client->display);
  وإلا
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  إذا (client->manager_دري && client->watch)
    {
      إذا (!client->watch (client->manager_دري, True,
                          Property_Change_نقاب | Structure_Notify_نقاب,
                          client->cb_معلومات))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_دري = None;
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
                      فراغ                *cb_معلومات)
{
  أرجع xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_معلومات,
                                               عدم, عدم);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      صحيح                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      فراغ                *cb_معلومات,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  حرف بفر_2[256];
  حرف *atom_نالا[3];
  Atom atoms[3];

  client = يادگيري_ڏيو (حجم *client);
  إذا (!client)
    أرجع عدم;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_معلومات = cb_معلومات;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_دري = None;
  client->settings = عدم;

  SDL_snprintf(بفر_2, حجم(بفر_2), "_XSETTINGS_S%d", screen);
  atom_نالا[0] = بفر_2;
  atom_نالا[1] = "_XSETTINGS_SETTINGS";
  atom_نالا[2] = "MANAGER";

#جيڪڏهن_وصف_ٿيل HAVE_XINTERNATOMS
  XInternAtoms (display, atom_نالا, 3, False, atoms);
#وإلا
  atoms[0] = X11_XInternAtom (display, atom_نالا[0], False);
  atoms[1] = X11_XInternAtom (display, atom_نالا[1], False);
  atoms[2] = X11_XInternAtom (display, atom_نالا[2], False);
#جيڪڏهن_پورو

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  جوڙيو_events (display, پاڙ_دري (display, screen), Structure_Notify_نقاب);

  إذا (client->watch)
    client->watch (پاڙ_دري (display, screen), True, Structure_Notify_نقاب,
                   client->cb_معلومات);

  check_manager_دري (client);

  أرجع client;
}


فراغ
xsettings_client_سيٽ_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

فراغ
xsettings_client_سيٽ_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

فراغ
xsettings_client_destroy (XSettingsClient *client)
{
  إذا (client->watch)
    client->watch (پاڙ_دري (client->display, client->screen),
                   False, 0, client->cb_معلومات);
  إذا (client->manager_دري && client->watch)
    client->watch (client->manager_دري, False, 0, client->cb_معلومات);

  xsettings_list_free (client->settings);
  حرر (client);
}

XSettings_نتيجو
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت حرف        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *ڳولا = xsettings_list_lookup (client->settings, name);
  إذا (ڳولا)
    {
      *setting = xsettings_setting_copy (ڳولا);
      أرجع *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  وإلا
    أرجع XSETTINGS_NO_داخلا;
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
  إذا (xev->xany.دري == پاڙ_دري (client->display, client->screen))
    {
      إذا (xev->xany.type == Client_پيغام &&
          xev->xclient.پيغام_type == client->manager_atom &&
          xev->xclient.معلومات.l[1] == client->selection_atom)
        {
          check_manager_دري (client);
          أرجع True;
        }
    }
  وإلا إذا (xev->xany.دري == client->manager_دري)
    {
      إذا (xev->xany.type == DestroyNotify)
        {
          check_manager_دري (client);
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
  XSettingsSetting *نتيجو;
  size_t str_len;

  نتيجو = يادگيري_ڏيو (حجم *نتيجو);
  إذا (!نتيجو)
    أرجع عدم;

  str_len = لڙي_ڊيگهه (setting->name);
  نتيجو->name = يادگيري_ڏيو (str_len + 1);
  إذا (!نتيجو->name)
    اذهب err;

  يادگيري_نقل (نتيجو->name, setting->name, str_len + 1);

  نتيجو->type = setting->type;

  بدل (setting->type)
    {
    حالة XSETTINGS_TYPE_INT:
      نتيجو->معلومات.v_int = setting->معلومات.v_int;
      اكسر;
    حالة XSETTINGS_TYPE_COLOR:
      نتيجو->معلومات.v_color = setting->معلومات.v_color;
      اكسر;
    حالة XSETTINGS_TYPE_STRING:
      str_len = لڙي_ڊيگهه (setting->معلومات.v_string);
      نتيجو->معلومات.v_string = يادگيري_ڏيو (str_len + 1);
      إذا (!نتيجو->معلومات.v_string)
        اذهب err;

      يادگيري_نقل (نتيجو->معلومات.v_string, setting->معلومات.v_string, str_len + 1);
      اكسر;
    }

  نتيجو->آخري_change_serial = setting->آخري_change_serial;

  أرجع نتيجو;

 err:
  حرر(نتيجو->name); // This should NOT be SDL_free()
  حرر(نتيجو); // This should NOT be SDL_free()

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
      XSettingsList *new_ڳنڍ;

      new_ڳنڍ = يادگيري_ڏيو (حجم *new_ڳنڍ);
      إذا (!new_ڳنڍ)
        اذهب error;

      new_ڳنڍ->setting = xsettings_setting_copy (old_iter->setting);
      إذا (!new_ڳنڍ->setting)
        {
          حرر (new_ڳنڍ);
          اذهب error;
        }

      إذا (new_iter)
        new_iter->ايندڙ = new_ڳنڍ;
      وإلا
        {
          new = new_ڳنڍ;
          new->ايندڙ = عدم;
        }


      new_iter = new_ڳنڍ;

      old_iter = old_iter->ايندڙ;
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
      أرجع setting_a->معلومات.v_int == setting_b->معلومات.v_int;
    حالة XSETTINGS_TYPE_COLOR:
      أرجع (setting_a->معلومات.v_color.red == setting_b->معلومات.v_color.red &&
              setting_a->معلومات.v_color.green == setting_b->معلومات.v_color.green &&
              setting_a->معلومات.v_color.blue == setting_b->معلومات.v_color.blue &&
              setting_a->معلومات.v_color.alpha == setting_b->معلومات.v_color.alpha);
    حالة XSETTINGS_TYPE_STRING:
      أرجع strcmp (setting_a->معلومات.v_string, setting_b->معلومات.v_string) == 0;
    }

  أرجع 0;
}

فراغ
xsettings_setting_free (XSettingsSetting *setting)
{
  إذا (setting->type == XSETTINGS_TYPE_STRING)
    حرر (setting->معلومات.v_string);

  حرر(setting->name); // This should NOT be SDL_free()
  حرر(setting); // This should NOT be SDL_free()
}

فراغ
xsettings_list_free (XSettingsList *list)
{
  طالما (list)
    {
      XSettingsList *ايندڙ = list->ايندڙ;

      xsettings_setting_free (list->setting);
      حرر (list);

      list = ايندڙ;
    }
}

XSettings_نتيجو
xsettings_list_وجهو (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ڳنڍ;
  XSettingsList *iter;
  XSettingsList *آخري = عدم;

  ڳنڍ = يادگيري_ڏيو (حجم *ڳنڍ);
  إذا (!ڳنڍ)
    أرجع XSETTINGS_NO_MEM;
  ڳنڍ->setting = setting;

  iter = *list;
  طالما (iter)
    {
      صحيح cmp = strcmp (setting->name, iter->setting->name);

      إذا (cmp < 0)
        اكسر;
      وإلا إذا (cmp == 0)
        {
          حرر (ڳنڍ);
          أرجع XSETTINGS_DUPLICATE_داخلا;
        }

      آخري = iter;
      iter = iter->ايندڙ;
    }

  إذا (آخري)
    آخري->ايندڙ = ڳنڍ;
  وإلا
    *list = ڳنڍ;

  ڳنڍ->ايندڙ = iter;

  أرجع XSETTINGS_SUCCESS;
}

XSettings_نتيجو
xsettings_list_delete (XSettingsList **list,
                       ثابت حرف     *name)
{
  XSettingsList *iter;
  XSettingsList *آخري = عدم;

  iter = *list;
  طالما (iter)
    {
      إذا (strcmp (name, iter->setting->name) == 0)
        {
          إذا (آخري)
            آخري->ايندڙ = iter->ايندڙ;
          وإلا
            *list = iter->ايندڙ;

          xsettings_setting_free (iter->setting);
          حرر (iter);

          أرجع XSETTINGS_SUCCESS;
        }

      آخري = iter;
      iter = iter->ايندڙ;
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

      iter = iter->ايندڙ;
    }

  أرجع عدم;
}

حرف
xsettings_byte_ترتيب (فراغ)
{
  CARD32 myint = 0x01020304;
  أرجع (*(حرف *)&myint == 1) ? MSBFirst : LSBFirst;
}

#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11 */

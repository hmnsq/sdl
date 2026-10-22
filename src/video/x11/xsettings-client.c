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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

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

  کړکۍ_2 manager_کړکۍ;
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
                            XSETTINGS_ACTION_بدل_شوی,
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
        old_iter = old_iter->بل;
      إذا (new_iter)
        new_iter = new_iter->بل;
    }
}

ساكن صحيح
ignore_errors (Display *display, XErrorEvent *event)
{
  أرجع True;
}

ساكن حرف local_byte_ترتیب = '\0';

#تعریف_کړه بایټونه_کیڼ_2(بفر_2) ((بفر_2)->معلومات + (بفر_2)->len - (بفر_2)->pos)

ساكن XSettings_پایله
fetch_card16 (XSettings_بفر *بفر_2,
              CARD16          *پایله)
{
  CARD16 x;

  إذا (بایټونه_کیڼ_2 (بفر_2) < 2)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD16 *)بفر_2->pos;
  بفر_2->pos += 2;

  إذا (بفر_2->byte_ترتیب == local_byte_ترتیب)
    *پایله = x;
  وإلا
    *پایله = (x << 8) | (x >> 8);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_پایله
fetch_ushort (XSettings_بفر *بفر_2,
              بینښه لنډ  *پایله)
{
  CARD16 x;
  XSettings_پایله r;

  r = fetch_card16 (بفر_2, &x);
  إذا (r == XSETTINGS_SUCCESS)
    *پایله = x;

  أرجع r;
}

ساكن XSettings_پایله
fetch_card32 (XSettings_بفر *بفر_2,
              CARD32          *پایله)
{
  CARD32 x;

  إذا (بایټونه_کیڼ_2 (بفر_2) < 4)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD32 *)بفر_2->pos;
  بفر_2->pos += 4;

  إذا (بفر_2->byte_ترتیب == local_byte_ترتیب)
    *پایله = x;
  وإلا
    *پایله = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_پایله
fetch_card8 (XSettings_بفر *بفر_2,
             CARD8           *پایله)
{
  إذا (بایټونه_کیڼ_2 (بفر_2) < 1)
    أرجع XSETTINGS_ACCESS;

  *پایله = *(CARD8 *)بفر_2->pos;
  بفر_2->pos += 1;

  أرجع XSETTINGS_SUCCESS;
}

#تعریف_کړه XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ساكن XSettingsList *
parse_settings (بینښه حرف *معلومات,
                size_t         len)
{
  XSettings_بفر بفر_2;
  XSettings_پایله پایله = XSETTINGS_SUCCESS;
  XSettingsList *settings = عدم;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = عدم;
  حرف بفر_byte_ترتیب = '\0';

  local_byte_ترتیب = xsettings_byte_ترتیب ();

  بفر_2.pos = بفر_2.معلومات = معلومات;
  بفر_2.len = len;
  بفر_2.byte_ترتیب = '\0';

  پایله = fetch_card8 (&بفر_2, (بینښه حرف *) &بفر_byte_ترتیب);
  إذا (بفر_byte_ترتیب != MSBFirst &&
      بفر_byte_ترتیب != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      پایله = XSETTINGS_FAILED;
      اذهب بهر;
    }

  بفر_2.byte_ترتیب = بفر_byte_ترتیب;
  بفر_2.pos += 3;

  پایله = fetch_card32 (&بفر_2, &serial);
  إذا (پایله != XSETTINGS_SUCCESS)
    اذهب بهر;

  پایله = fetch_card32 (&بفر_2, &n_entries);
  إذا (پایله != XSETTINGS_SUCCESS)
    اذهب بهر;

  لكل (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      پایله = fetch_card8 (&بفر_2, &type);
      إذا (پایله != XSETTINGS_SUCCESS)
        اذهب بهر;

      بفر_2.pos += 1;

      پایله = fetch_card16 (&بفر_2, &name_len);
      إذا (پایله != XSETTINGS_SUCCESS)
        اذهب بهر;

      pad_len = XSETTINGS_PAD(name_len, 4);
      إذا (بایټونه_کیڼ_2 (&بفر_2) < pad_len)
        {
          پایله = XSETTINGS_ACCESS;
          اذهب بهر;
        }

      setting = حافظه_ورکړه (حجم *setting);
      إذا (!setting)
        {
          پایله = XSETTINGS_NO_MEM;
          اذهب بهر;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = حافظه_ورکړه (name_len + 1);
      إذا (!setting->name)
        {
          پایله = XSETTINGS_NO_MEM;
          اذهب بهر;
        }

      حافظه_نقل (setting->name, بفر_2.pos, name_len);
      setting->name[name_len] = '\0';
      بفر_2.pos += pad_len;

      پایله = fetch_card32 (&بفر_2, &v_int);
      إذا (پایله != XSETTINGS_SUCCESS)
        اذهب بهر;
      setting->وروستی_change_serial = v_int;

      بدل (type)
        {
        حالة XSETTINGS_TYPE_INT:
          پایله = fetch_card32 (&بفر_2, &v_int);
          إذا (پایله != XSETTINGS_SUCCESS)
            اذهب بهر;

          setting->معلومات.v_int = (INT32)v_int;
          اكسر;
        حالة XSETTINGS_TYPE_STRING:
          پایله = fetch_card32 (&بفر_2, &v_int);
          إذا (پایله != XSETTINGS_SUCCESS)
            اذهب بهر;

          pad_len = XSETTINGS_PAD (v_int, 4);
          إذا (v_int + 1 == 0 || /* Guard against wrap-around */
              بایټونه_کیڼ_2 (&بفر_2) < pad_len)
            {
              پایله = XSETTINGS_ACCESS;
              اذهب بهر;
            }

          setting->معلومات.v_string = حافظه_ورکړه (v_int + 1);
          إذا (!setting->معلومات.v_string)
            {
              پایله = XSETTINGS_NO_MEM;
              اذهب بهر;
            }

          حافظه_نقل (setting->معلومات.v_string, بفر_2.pos, v_int);
          setting->معلومات.v_string[v_int] = '\0';
          بفر_2.pos += pad_len;

          اكسر;
        حالة XSETTINGS_TYPE_COLOR:
          پایله = fetch_ushort (&بفر_2, &setting->معلومات.v_color.red);
          إذا (پایله != XSETTINGS_SUCCESS)
            اذهب بهر;
          پایله = fetch_ushort (&بفر_2, &setting->معلومات.v_color.green);
          إذا (پایله != XSETTINGS_SUCCESS)
            اذهب بهر;
          پایله = fetch_ushort (&بفر_2, &setting->معلومات.v_color.blue);
          إذا (پایله != XSETTINGS_SUCCESS)
            اذهب بهر;
          پایله = fetch_ushort (&بفر_2, &setting->معلومات.v_color.alpha);
          إذا (پایله != XSETTINGS_SUCCESS)
            اذهب بهر;

          اكسر;
        افتراضي:
          /* Quietly ignore unknown types */
          اكسر;
        }

      setting->type = type;

      پایله = xsettings_list_ورننباسه (&settings, setting);
      إذا (پایله != XSETTINGS_SUCCESS)
        اذهب بهر;

      setting = عدم;
    }

 بهر:

  إذا (پایله != XSETTINGS_SUCCESS)
    {
      بدل (پایله)
        {
        حالة XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          اكسر;
        حالة XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          اكسر;
        حالة XSETTINGS_DUPLICATE_ثبت:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالة XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_NO_ثبت:
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
  بینښه اوږد n_توکي;
  بینښه اوږد بایټونه_after;
  بینښه حرف *معلومات;
  صحيح پایله;

  صحيح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = عدم;

  إذا (client->manager_کړکۍ)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      پایله = X11_XGet_کړکۍ_Property (client->display, client->manager_کړکۍ,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_توکي, &بایټونه_after, &معلومات);
      X11_XSetErrorHandler (old_handler);

      إذا (پایله == Success && type != None)
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
            client->settings = parse_settings (معلومات, n_توکي);

          X11_XFree (معلومات);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ساكن فراغ
جمع_کړه_events (Display *display,
            کړکۍ_2   کړکۍ,
            اوږد     ماسک)
{
  XWindow_ځانګړتیاوې attr;

  X11_XGet_کړکۍ_ځانګړتیاوې (display, کړکۍ, &attr);
  X11_XSelect_ننوت (display, کړکۍ, attr.your_event_ماسک | ماسک);
}

ساكن فراغ
check_manager_کړکۍ (XSettingsClient *client)
{
  إذا (client->manager_کړکۍ && client->watch)
    client->watch (client->manager_کړکۍ, False, 0, client->cb_معلومات);

  إذا (client->grab)
    client->grab (client->display);
  وإلا
    X11_XGrabServer (client->display);

  client->manager_کړکۍ = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  إذا (client->manager_کړکۍ)
    X11_XSelect_ننوت (client->display, client->manager_کړکۍ,
                      Property_Change_ماسک | Structure_Notify_ماسک);

  إذا (client->ungrab)
    client->ungrab (client->display);
  وإلا
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  إذا (client->manager_کړکۍ && client->watch)
    {
      إذا (!client->watch (client->manager_کړکۍ, True,
                          Property_Change_ماسک | Structure_Notify_ماسک,
                          client->cb_معلومات))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_کړکۍ = None;
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
  حرف *atom_نومونه[3];
  Atom atoms[3];

  client = حافظه_ورکړه (حجم *client);
  إذا (!client)
    أرجع عدم;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_معلومات = cb_معلومات;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_کړکۍ = None;
  client->settings = عدم;

  SDL_snprintf(بفر_2, حجم(بفر_2), "_XSETTINGS_S%d", screen);
  atom_نومونه[0] = بفر_2;
  atom_نومونه[1] = "_XSETTINGS_SETTINGS";
  atom_نومونه[2] = "MANAGER";

#که_تعریف_شوی HAVE_XINTERNATOMS
  XInternAtoms (display, atom_نومونه, 3, False, atoms);
#وإلا
  atoms[0] = X11_XInternAtom (display, atom_نومونه[0], False);
  atoms[1] = X11_XInternAtom (display, atom_نومونه[1], False);
  atoms[2] = X11_XInternAtom (display, atom_نومونه[2], False);
#د_که_پای

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  جمع_کړه_events (display, ریښه_کړکۍ (display, screen), Structure_Notify_ماسک);

  إذا (client->watch)
    client->watch (ریښه_کړکۍ (display, screen), True, Structure_Notify_ماسک,
                   client->cb_معلومات);

  check_manager_کړکۍ (client);

  أرجع client;
}


فراغ
xsettings_client_سېټ_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

فراغ
xsettings_client_سېټ_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

فراغ
xsettings_client_destroy (XSettingsClient *client)
{
  إذا (client->watch)
    client->watch (ریښه_کړکۍ (client->display, client->screen),
                   False, 0, client->cb_معلومات);
  إذا (client->manager_کړکۍ && client->watch)
    client->watch (client->manager_کړکۍ, False, 0, client->cb_معلومات);

  xsettings_list_free (client->settings);
  حرر (client);
}

XSettings_پایله
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت حرف        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *پلټنه = xsettings_list_lookup (client->settings, name);
  إذا (پلټنه)
    {
      *setting = xsettings_setting_copy (پلټنه);
      أرجع *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  وإلا
    أرجع XSETTINGS_NO_ثبت;
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
  إذا (xev->xany.کړکۍ == ریښه_کړکۍ (client->display, client->screen))
    {
      إذا (xev->xany.type == Client_پیغام &&
          xev->xclient.پیغام_type == client->manager_atom &&
          xev->xclient.معلومات.l[1] == client->selection_atom)
        {
          check_manager_کړکۍ (client);
          أرجع True;
        }
    }
  وإلا إذا (xev->xany.کړکۍ == client->manager_کړکۍ)
    {
      إذا (xev->xany.type == DestroyNotify)
        {
          check_manager_کړکۍ (client);
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
  XSettingsSetting *پایله;
  size_t str_len;

  پایله = حافظه_ورکړه (حجم *پایله);
  إذا (!پایله)
    أرجع عدم;

  str_len = مزي_اوږدوالی (setting->name);
  پایله->name = حافظه_ورکړه (str_len + 1);
  إذا (!پایله->name)
    اذهب err;

  حافظه_نقل (پایله->name, setting->name, str_len + 1);

  پایله->type = setting->type;

  بدل (setting->type)
    {
    حالة XSETTINGS_TYPE_INT:
      پایله->معلومات.v_int = setting->معلومات.v_int;
      اكسر;
    حالة XSETTINGS_TYPE_COLOR:
      پایله->معلومات.v_color = setting->معلومات.v_color;
      اكسر;
    حالة XSETTINGS_TYPE_STRING:
      str_len = مزي_اوږدوالی (setting->معلومات.v_string);
      پایله->معلومات.v_string = حافظه_ورکړه (str_len + 1);
      إذا (!پایله->معلومات.v_string)
        اذهب err;

      حافظه_نقل (پایله->معلومات.v_string, setting->معلومات.v_string, str_len + 1);
      اكسر;
    }

  پایله->وروستی_change_serial = setting->وروستی_change_serial;

  أرجع پایله;

 err:
  حرر(پایله->name); // This should NOT be SDL_free()
  حرر(پایله); // This should NOT be SDL_free()

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
      XSettingsList *new_غوټه;

      new_غوټه = حافظه_ورکړه (حجم *new_غوټه);
      إذا (!new_غوټه)
        اذهب error;

      new_غوټه->setting = xsettings_setting_copy (old_iter->setting);
      إذا (!new_غوټه->setting)
        {
          حرر (new_غوټه);
          اذهب error;
        }

      إذا (new_iter)
        new_iter->بل = new_غوټه;
      وإلا
        {
          new = new_غوټه;
          new->بل = عدم;
        }


      new_iter = new_غوټه;

      old_iter = old_iter->بل;
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
      XSettingsList *بل = list->بل;

      xsettings_setting_free (list->setting);
      حرر (list);

      list = بل;
    }
}

XSettings_پایله
xsettings_list_ورننباسه (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *غوټه;
  XSettingsList *iter;
  XSettingsList *وروستی = عدم;

  غوټه = حافظه_ورکړه (حجم *غوټه);
  إذا (!غوټه)
    أرجع XSETTINGS_NO_MEM;
  غوټه->setting = setting;

  iter = *list;
  طالما (iter)
    {
      صحيح cmp = strcmp (setting->name, iter->setting->name);

      إذا (cmp < 0)
        اكسر;
      وإلا إذا (cmp == 0)
        {
          حرر (غوټه);
          أرجع XSETTINGS_DUPLICATE_ثبت;
        }

      وروستی = iter;
      iter = iter->بل;
    }

  إذا (وروستی)
    وروستی->بل = غوټه;
  وإلا
    *list = غوټه;

  غوټه->بل = iter;

  أرجع XSETTINGS_SUCCESS;
}

XSettings_پایله
xsettings_list_delete (XSettingsList **list,
                       ثابت حرف     *name)
{
  XSettingsList *iter;
  XSettingsList *وروستی = عدم;

  iter = *list;
  طالما (iter)
    {
      إذا (strcmp (name, iter->setting->name) == 0)
        {
          إذا (وروستی)
            وروستی->بل = iter->بل;
          وإلا
            *list = iter->بل;

          xsettings_setting_free (iter->setting);
          حرر (iter);

          أرجع XSETTINGS_SUCCESS;
        }

      وروستی = iter;
      iter = iter->بل;
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

      iter = iter->بل;
    }

  أرجع عدم;
}

حرف
xsettings_byte_ترتیب (فراغ)
{
  CARD32 myint = 0x01020304;
  أرجع (*(حرف *)&myint == 1) ? MSBFirst : LSBFirst;
}

#د_که_پای /* SDL_VIDEO_DRIVER_X11 */

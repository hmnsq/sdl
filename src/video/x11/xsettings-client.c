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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

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
  فراغ *cb_داده;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  پنجره_2 manager_پنجره;
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
                          client->cb_داده);
        }
      وإلا إذا (cmp == 0)
        {
          إذا (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_تغییریافته,
                            new_iter->setting,
                            client->cb_داده);
        }
      وإلا
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_داده);
        }

      إذا (old_iter)
        old_iter = old_iter->بعدی;
      إذا (new_iter)
        new_iter = new_iter->بعدی;
    }
}

ساكن صحيح
ignore_errors (Display *display, XErrorEvent *event)
{
  أرجع True;
}

ساكن حرف local_byte_ترتیب = '\0';

#تعریف_کن بایتها_چپ_2(میانگیر_2) ((میانگیر_2)->داده + (میانگیر_2)->len - (میانگیر_2)->pos)

ساكن XSettings_نتیجه
fetch_card16 (XSettings_میانگیر *میانگیر_2,
              CARD16          *نتیجه)
{
  CARD16 x;

  إذا (بایتها_چپ_2 (میانگیر_2) < 2)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD16 *)میانگیر_2->pos;
  میانگیر_2->pos += 2;

  إذا (میانگیر_2->byte_ترتیب == local_byte_ترتیب)
    *نتیجه = x;
  وإلا
    *نتیجه = (x << 8) | (x >> 8);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_نتیجه
fetch_ushort (XSettings_میانگیر *میانگیر_2,
              بیعلامت کوتاه  *نتیجه)
{
  CARD16 x;
  XSettings_نتیجه r;

  r = fetch_card16 (میانگیر_2, &x);
  إذا (r == XSETTINGS_SUCCESS)
    *نتیجه = x;

  أرجع r;
}

ساكن XSettings_نتیجه
fetch_card32 (XSettings_میانگیر *میانگیر_2,
              CARD32          *نتیجه)
{
  CARD32 x;

  إذا (بایتها_چپ_2 (میانگیر_2) < 4)
    أرجع XSETTINGS_ACCESS;

  x = *(CARD32 *)میانگیر_2->pos;
  میانگیر_2->pos += 4;

  إذا (میانگیر_2->byte_ترتیب == local_byte_ترتیب)
    *نتیجه = x;
  وإلا
    *نتیجه = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  أرجع XSETTINGS_SUCCESS;
}

ساكن XSettings_نتیجه
fetch_card8 (XSettings_میانگیر *میانگیر_2,
             CARD8           *نتیجه)
{
  إذا (بایتها_چپ_2 (میانگیر_2) < 1)
    أرجع XSETTINGS_ACCESS;

  *نتیجه = *(CARD8 *)میانگیر_2->pos;
  میانگیر_2->pos += 1;

  أرجع XSETTINGS_SUCCESS;
}

#تعریف_کن XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ساكن XSettingsList *
parse_settings (بیعلامت حرف *داده,
                size_t         len)
{
  XSettings_میانگیر میانگیر_2;
  XSettings_نتیجه نتیجه = XSETTINGS_SUCCESS;
  XSettingsList *settings = عدم;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = عدم;
  حرف میانگیر_byte_ترتیب = '\0';

  local_byte_ترتیب = xsettings_byte_ترتیب ();

  میانگیر_2.pos = میانگیر_2.داده = داده;
  میانگیر_2.len = len;
  میانگیر_2.byte_ترتیب = '\0';

  نتیجه = fetch_card8 (&میانگیر_2, (بیعلامت حرف *) &میانگیر_byte_ترتیب);
  إذا (میانگیر_byte_ترتیب != MSBFirst &&
      میانگیر_byte_ترتیب != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      نتیجه = XSETTINGS_FAILED;
      اذهب بیرون;
    }

  میانگیر_2.byte_ترتیب = میانگیر_byte_ترتیب;
  میانگیر_2.pos += 3;

  نتیجه = fetch_card32 (&میانگیر_2, &serial);
  إذا (نتیجه != XSETTINGS_SUCCESS)
    اذهب بیرون;

  نتیجه = fetch_card32 (&میانگیر_2, &n_entries);
  إذا (نتیجه != XSETTINGS_SUCCESS)
    اذهب بیرون;

  لكل (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      نتیجه = fetch_card8 (&میانگیر_2, &type);
      إذا (نتیجه != XSETTINGS_SUCCESS)
        اذهب بیرون;

      میانگیر_2.pos += 1;

      نتیجه = fetch_card16 (&میانگیر_2, &name_len);
      إذا (نتیجه != XSETTINGS_SUCCESS)
        اذهب بیرون;

      pad_len = XSETTINGS_PAD(name_len, 4);
      إذا (بایتها_چپ_2 (&میانگیر_2) < pad_len)
        {
          نتیجه = XSETTINGS_ACCESS;
          اذهب بیرون;
        }

      setting = حافظه_بده (حجم *setting);
      إذا (!setting)
        {
          نتیجه = XSETTINGS_NO_MEM;
          اذهب بیرون;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = حافظه_بده (name_len + 1);
      إذا (!setting->name)
        {
          نتیجه = XSETTINGS_NO_MEM;
          اذهب بیرون;
        }

      کپی_حافظه (setting->name, میانگیر_2.pos, name_len);
      setting->name[name_len] = '\0';
      میانگیر_2.pos += pad_len;

      نتیجه = fetch_card32 (&میانگیر_2, &v_int);
      إذا (نتیجه != XSETTINGS_SUCCESS)
        اذهب بیرون;
      setting->آخرین_change_serial = v_int;

      بدل (type)
        {
        حالة XSETTINGS_TYPE_INT:
          نتیجه = fetch_card32 (&میانگیر_2, &v_int);
          إذا (نتیجه != XSETTINGS_SUCCESS)
            اذهب بیرون;

          setting->داده.v_int = (INT32)v_int;
          اكسر;
        حالة XSETTINGS_TYPE_STRING:
          نتیجه = fetch_card32 (&میانگیر_2, &v_int);
          إذا (نتیجه != XSETTINGS_SUCCESS)
            اذهب بیرون;

          pad_len = XSETTINGS_PAD (v_int, 4);
          إذا (v_int + 1 == 0 || /* Guard against wrap-around */
              بایتها_چپ_2 (&میانگیر_2) < pad_len)
            {
              نتیجه = XSETTINGS_ACCESS;
              اذهب بیرون;
            }

          setting->داده.v_string = حافظه_بده (v_int + 1);
          إذا (!setting->داده.v_string)
            {
              نتیجه = XSETTINGS_NO_MEM;
              اذهب بیرون;
            }

          کپی_حافظه (setting->داده.v_string, میانگیر_2.pos, v_int);
          setting->داده.v_string[v_int] = '\0';
          میانگیر_2.pos += pad_len;

          اكسر;
        حالة XSETTINGS_TYPE_COLOR:
          نتیجه = fetch_ushort (&میانگیر_2, &setting->داده.v_color.red);
          إذا (نتیجه != XSETTINGS_SUCCESS)
            اذهب بیرون;
          نتیجه = fetch_ushort (&میانگیر_2, &setting->داده.v_color.green);
          إذا (نتیجه != XSETTINGS_SUCCESS)
            اذهب بیرون;
          نتیجه = fetch_ushort (&میانگیر_2, &setting->داده.v_color.blue);
          إذا (نتیجه != XSETTINGS_SUCCESS)
            اذهب بیرون;
          نتیجه = fetch_ushort (&میانگیر_2, &setting->داده.v_color.alpha);
          إذا (نتیجه != XSETTINGS_SUCCESS)
            اذهب بیرون;

          اكسر;
        افتراضي:
          /* Quietly ignore unknown types */
          اكسر;
        }

      setting->type = type;

      نتیجه = xsettings_list_درج (&settings, setting);
      إذا (نتیجه != XSETTINGS_SUCCESS)
        اذهب بیرون;

      setting = عدم;
    }

 بیرون:

  إذا (نتیجه != XSETTINGS_SUCCESS)
    {
      بدل (نتیجه)
        {
        حالة XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          اكسر;
        حالة XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          اكسر;
        حالة XSETTINGS_DUPLICATE_مدخل:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        حالة XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        حالة XSETTINGS_NO_مدخل:
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
  بیعلامت دراز n_اقلام;
  بیعلامت دراز بایتها_after;
  بیعلامت حرف *داده;
  صحيح نتیجه;

  صحيح (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = عدم;

  إذا (client->manager_پنجره)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      نتیجه = X11_XGet_پنجره_Property (client->display, client->manager_پنجره,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_اقلام, &بایتها_after, &داده);
      X11_XSetErrorHandler (old_handler);

      إذا (نتیجه == Success && type != None)
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
            client->settings = parse_settings (داده, n_اقلام);

          X11_XFree (داده);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

ساكن فراغ
جمع_کن_events (Display *display,
            پنجره_2   پنجره,
            دراز     ماسک)
{
  XWindow_صفات attr;

  X11_XGet_پنجره_صفات (display, پنجره, &attr);
  X11_XSelect_درون_داد (display, پنجره, attr.your_event_ماسک | ماسک);
}

ساكن فراغ
check_manager_پنجره (XSettingsClient *client)
{
  إذا (client->manager_پنجره && client->watch)
    client->watch (client->manager_پنجره, False, 0, client->cb_داده);

  إذا (client->grab)
    client->grab (client->display);
  وإلا
    X11_XGrabServer (client->display);

  client->manager_پنجره = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  إذا (client->manager_پنجره)
    X11_XSelect_درون_داد (client->display, client->manager_پنجره,
                      Property_Change_ماسک | Structure_Notify_ماسک);

  إذا (client->ungrab)
    client->ungrab (client->display);
  وإلا
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  إذا (client->manager_پنجره && client->watch)
    {
      إذا (!client->watch (client->manager_پنجره, True,
                          Property_Change_ماسک | Structure_Notify_ماسک,
                          client->cb_داده))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_پنجره = None;
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
                      فراغ                *cb_داده)
{
  أرجع xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_داده,
                                               عدم, عدم);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      صحيح                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      فراغ                *cb_داده,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  حرف میانگیر_2[256];
  حرف *atom_نامها[3];
  Atom atoms[3];

  client = حافظه_بده (حجم *client);
  إذا (!client)
    أرجع عدم;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_داده = cb_داده;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_پنجره = None;
  client->settings = عدم;

  SDL_snprintf(میانگیر_2, حجم(میانگیر_2), "_XSETTINGS_S%d", screen);
  atom_نامها[0] = میانگیر_2;
  atom_نامها[1] = "_XSETTINGS_SETTINGS";
  atom_نامها[2] = "MANAGER";

#اگر_تعریف_شده HAVE_XINTERNATOMS
  XInternAtoms (display, atom_نامها, 3, False, atoms);
#وإلا
  atoms[0] = X11_XInternAtom (display, atom_نامها[0], False);
  atoms[1] = X11_XInternAtom (display, atom_نامها[1], False);
  atoms[2] = X11_XInternAtom (display, atom_نامها[2], False);
#پایان_اگر

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  جمع_کن_events (display, ریشه_پنجره (display, screen), Structure_Notify_ماسک);

  إذا (client->watch)
    client->watch (ریشه_پنجره (display, screen), True, Structure_Notify_ماسک,
                   client->cb_داده);

  check_manager_پنجره (client);

  أرجع client;
}


فراغ
xsettings_client_مجموعه_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

فراغ
xsettings_client_مجموعه_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

فراغ
xsettings_client_destroy (XSettingsClient *client)
{
  إذا (client->watch)
    client->watch (ریشه_پنجره (client->display, client->screen),
                   False, 0, client->cb_داده);
  إذا (client->manager_پنجره && client->watch)
    client->watch (client->manager_پنجره, False, 0, client->cb_داده);

  xsettings_list_free (client->settings);
  حرر (client);
}

XSettings_نتیجه
xsettings_client_get_setting (XSettingsClient   *client,
                              ثابت حرف        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *جستجو = xsettings_list_lookup (client->settings, name);
  إذا (جستجو)
    {
      *setting = xsettings_setting_copy (جستجو);
      أرجع *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  وإلا
    أرجع XSETTINGS_NO_مدخل;
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
  إذا (xev->xany.پنجره == ریشه_پنجره (client->display, client->screen))
    {
      إذا (xev->xany.type == Client_پیام &&
          xev->xclient.پیام_type == client->manager_atom &&
          xev->xclient.داده.l[1] == client->selection_atom)
        {
          check_manager_پنجره (client);
          أرجع True;
        }
    }
  وإلا إذا (xev->xany.پنجره == client->manager_پنجره)
    {
      إذا (xev->xany.type == DestroyNotify)
        {
          check_manager_پنجره (client);
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
  XSettingsSetting *نتیجه;
  size_t str_len;

  نتیجه = حافظه_بده (حجم *نتیجه);
  إذا (!نتیجه)
    أرجع عدم;

  str_len = طول_رشته (setting->name);
  نتیجه->name = حافظه_بده (str_len + 1);
  إذا (!نتیجه->name)
    اذهب err;

  کپی_حافظه (نتیجه->name, setting->name, str_len + 1);

  نتیجه->type = setting->type;

  بدل (setting->type)
    {
    حالة XSETTINGS_TYPE_INT:
      نتیجه->داده.v_int = setting->داده.v_int;
      اكسر;
    حالة XSETTINGS_TYPE_COLOR:
      نتیجه->داده.v_color = setting->داده.v_color;
      اكسر;
    حالة XSETTINGS_TYPE_STRING:
      str_len = طول_رشته (setting->داده.v_string);
      نتیجه->داده.v_string = حافظه_بده (str_len + 1);
      إذا (!نتیجه->داده.v_string)
        اذهب err;

      کپی_حافظه (نتیجه->داده.v_string, setting->داده.v_string, str_len + 1);
      اكسر;
    }

  نتیجه->آخرین_change_serial = setting->آخرین_change_serial;

  أرجع نتیجه;

 err:
  حرر(نتیجه->name); // This should NOT be SDL_free()
  حرر(نتیجه); // This should NOT be SDL_free()

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
      XSettingsList *new_گره;

      new_گره = حافظه_بده (حجم *new_گره);
      إذا (!new_گره)
        اذهب error;

      new_گره->setting = xsettings_setting_copy (old_iter->setting);
      إذا (!new_گره->setting)
        {
          حرر (new_گره);
          اذهب error;
        }

      إذا (new_iter)
        new_iter->بعدی = new_گره;
      وإلا
        {
          new = new_گره;
          new->بعدی = عدم;
        }


      new_iter = new_گره;

      old_iter = old_iter->بعدی;
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
      أرجع setting_a->داده.v_int == setting_b->داده.v_int;
    حالة XSETTINGS_TYPE_COLOR:
      أرجع (setting_a->داده.v_color.red == setting_b->داده.v_color.red &&
              setting_a->داده.v_color.green == setting_b->داده.v_color.green &&
              setting_a->داده.v_color.blue == setting_b->داده.v_color.blue &&
              setting_a->داده.v_color.alpha == setting_b->داده.v_color.alpha);
    حالة XSETTINGS_TYPE_STRING:
      أرجع strcmp (setting_a->داده.v_string, setting_b->داده.v_string) == 0;
    }

  أرجع 0;
}

فراغ
xsettings_setting_free (XSettingsSetting *setting)
{
  إذا (setting->type == XSETTINGS_TYPE_STRING)
    حرر (setting->داده.v_string);

  حرر(setting->name); // This should NOT be SDL_free()
  حرر(setting); // This should NOT be SDL_free()
}

فراغ
xsettings_list_free (XSettingsList *list)
{
  طالما (list)
    {
      XSettingsList *بعدی = list->بعدی;

      xsettings_setting_free (list->setting);
      حرر (list);

      list = بعدی;
    }
}

XSettings_نتیجه
xsettings_list_درج (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *گره;
  XSettingsList *iter;
  XSettingsList *آخرین = عدم;

  گره = حافظه_بده (حجم *گره);
  إذا (!گره)
    أرجع XSETTINGS_NO_MEM;
  گره->setting = setting;

  iter = *list;
  طالما (iter)
    {
      صحيح cmp = strcmp (setting->name, iter->setting->name);

      إذا (cmp < 0)
        اكسر;
      وإلا إذا (cmp == 0)
        {
          حرر (گره);
          أرجع XSETTINGS_DUPLICATE_مدخل;
        }

      آخرین = iter;
      iter = iter->بعدی;
    }

  إذا (آخرین)
    آخرین->بعدی = گره;
  وإلا
    *list = گره;

  گره->بعدی = iter;

  أرجع XSETTINGS_SUCCESS;
}

XSettings_نتیجه
xsettings_list_delete (XSettingsList **list,
                       ثابت حرف     *name)
{
  XSettingsList *iter;
  XSettingsList *آخرین = عدم;

  iter = *list;
  طالما (iter)
    {
      إذا (strcmp (name, iter->setting->name) == 0)
        {
          إذا (آخرین)
            آخرین->بعدی = iter->بعدی;
          وإلا
            *list = iter->بعدی;

          xsettings_setting_free (iter->setting);
          حرر (iter);

          أرجع XSETTINGS_SUCCESS;
        }

      آخرین = iter;
      iter = iter->بعدی;
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

      iter = iter->بعدی;
    }

  أرجع عدم;
}

حرف
xsettings_byte_ترتیب (فراغ)
{
  CARD32 myint = 0x01020304;
  أرجع (*(حرف *)&myint == 1) ? MSBFirst : LSBFirst;
}

#پایان_اگر /* SDL_VIDEO_DRIVER_X11 */

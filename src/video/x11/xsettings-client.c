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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

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
  शून्य *cb_दत्त;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  गवाक्षः_2 manager_गवाक्षः;
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
    प्रत्यागम;

  यावत् (old_iter || new_iter)
    {
      पूर्णाङ्क cmp;

      यदि (old_iter && new_iter)
        cmp = वाक्यं_तुलय (old_iter->setting->name, new_iter->setting->name);
      अन्यथा यदि (old_iter)
        cmp = -1;
      अन्यथा
        cmp = 1;

      यदि (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          रिक्त,
                          client->cb_दत्त);
        }
      अन्यथा यदि (cmp == 0)
        {
          यदि (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_परिवर्तितम्,
                            new_iter->setting,
                            client->cb_दत्त);
        }
      अन्यथा
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_दत्त);
        }

      यदि (old_iter)
        old_iter = old_iter->अग्र;
      यदि (new_iter)
        new_iter = new_iter->अग्र;
    }
}

स्थिर पूर्णाङ्क
ignore_errors (Display *display, XErrorEvent *event)
{
  प्रत्यागम True;
}

स्थिर वर्ण local_byte_क्रमः = '\0';

#परिभाषय अष्टकानि_वामः_2(बफर_2) ((बफर_2)->दत्त + (बफर_2)->len - (बफर_2)->pos)

स्थिर XSettings_परिणाम
fetch_card16 (XSettings_बफर *बफर_2,
              CARD16          *परिणाम)
{
  CARD16 x;

  यदि (अष्टकानि_वामः_2 (बफर_2) < 2)
    प्रत्यागम XSETTINGS_ACCESS;

  x = *(CARD16 *)बफर_2->pos;
  बफर_2->pos += 2;

  यदि (बफर_2->byte_क्रमः == local_byte_क्रमः)
    *परिणाम = x;
  अन्यथा
    *परिणाम = (x << 8) | (x >> 8);

  प्रत्यागम XSETTINGS_SUCCESS;
}

स्थिर XSettings_परिणाम
fetch_ushort (XSettings_बफर *बफर_2,
              अचिह्नित ह्रस्व  *परिणाम)
{
  CARD16 x;
  XSettings_परिणाम r;

  r = fetch_card16 (बफर_2, &x);
  यदि (r == XSETTINGS_SUCCESS)
    *परिणाम = x;

  प्रत्यागम r;
}

स्थिर XSettings_परिणाम
fetch_card32 (XSettings_बफर *बफर_2,
              CARD32          *परिणाम)
{
  CARD32 x;

  यदि (अष्टकानि_वामः_2 (बफर_2) < 4)
    प्रत्यागम XSETTINGS_ACCESS;

  x = *(CARD32 *)बफर_2->pos;
  बफर_2->pos += 4;

  यदि (बफर_2->byte_क्रमः == local_byte_क्रमः)
    *परिणाम = x;
  अन्यथा
    *परिणाम = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  प्रत्यागम XSETTINGS_SUCCESS;
}

स्थिर XSettings_परिणाम
fetch_card8 (XSettings_बफर *बफर_2,
             CARD8           *परिणाम)
{
  यदि (अष्टकानि_वामः_2 (बफर_2) < 1)
    प्रत्यागम XSETTINGS_ACCESS;

  *परिणाम = *(CARD8 *)बफर_2->pos;
  बफर_2->pos += 1;

  प्रत्यागम XSETTINGS_SUCCESS;
}

#परिभाषय XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

स्थिर XSettingsList *
parse_settings (अचिह्नित वर्ण *दत्त,
                size_t         len)
{
  XSettings_बफर बफर_2;
  XSettings_परिणाम परिणाम = XSETTINGS_SUCCESS;
  XSettingsList *settings = रिक्त;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = रिक्त;
  वर्ण बफर_byte_क्रमः = '\0';

  local_byte_क्रमः = xsettings_byte_क्रमः ();

  बफर_2.pos = बफर_2.दत्त = दत्त;
  बफर_2.len = len;
  बफर_2.byte_क्रमः = '\0';

  परिणाम = fetch_card8 (&बफर_2, (अचिह्नित वर्ण *) &बफर_byte_क्रमः);
  यदि (बफर_byte_क्रमः != MSBFirst &&
      बफर_byte_क्रमः != LSBFirst)
    {
      fprintf (stderr, "Invalid byte order in XSETTINGS property\n");
      परिणाम = XSETTINGS_FAILED;
      गच्छ बहिर्गमनम्;
    }

  बफर_2.byte_क्रमः = बफर_byte_क्रमः;
  बफर_2.pos += 3;

  परिणाम = fetch_card32 (&बफर_2, &serial);
  यदि (परिणाम != XSETTINGS_SUCCESS)
    गच्छ बहिर्गमनम्;

  परिणाम = fetch_card32 (&बफर_2, &n_entries);
  यदि (परिणाम != XSETTINGS_SUCCESS)
    गच्छ बहिर्गमनम्;

  प्रति (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      size_t pad_len;

      परिणाम = fetch_card8 (&बफर_2, &type);
      यदि (परिणाम != XSETTINGS_SUCCESS)
        गच्छ बहिर्गमनम्;

      बफर_2.pos += 1;

      परिणाम = fetch_card16 (&बफर_2, &name_len);
      यदि (परिणाम != XSETTINGS_SUCCESS)
        गच्छ बहिर्गमनम्;

      pad_len = XSETTINGS_PAD(name_len, 4);
      यदि (अष्टकानि_वामः_2 (&बफर_2) < pad_len)
        {
          परिणाम = XSETTINGS_ACCESS;
          गच्छ बहिर्गमनम्;
        }

      setting = स्मृतिं_देहि (परिमाण *setting);
      यदि (!setting)
        {
          परिणाम = XSETTINGS_NO_MEM;
          गच्छ बहिर्गमनम्;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = स्मृतिं_देहि (name_len + 1);
      यदि (!setting->name)
        {
          परिणाम = XSETTINGS_NO_MEM;
          गच्छ बहिर्गमनम्;
        }

      स्मृतिं_प्रतिलिख (setting->name, बफर_2.pos, name_len);
      setting->name[name_len] = '\0';
      बफर_2.pos += pad_len;

      परिणाम = fetch_card32 (&बफर_2, &v_int);
      यदि (परिणाम != XSETTINGS_SUCCESS)
        गच्छ बहिर्गमनम्;
      setting->चरमः_change_serial = v_int;

      विकल्प (type)
        {
        पक्ष XSETTINGS_TYPE_INT:
          परिणाम = fetch_card32 (&बफर_2, &v_int);
          यदि (परिणाम != XSETTINGS_SUCCESS)
            गच्छ बहिर्गमनम्;

          setting->दत्त.v_int = (INT32)v_int;
          भङ्ग;
        पक्ष XSETTINGS_TYPE_STRING:
          परिणाम = fetch_card32 (&बफर_2, &v_int);
          यदि (परिणाम != XSETTINGS_SUCCESS)
            गच्छ बहिर्गमनम्;

          pad_len = XSETTINGS_PAD (v_int, 4);
          यदि (v_int + 1 == 0 || /* Guard against wrap-around */
              अष्टकानि_वामः_2 (&बफर_2) < pad_len)
            {
              परिणाम = XSETTINGS_ACCESS;
              गच्छ बहिर्गमनम्;
            }

          setting->दत्त.v_string = स्मृतिं_देहि (v_int + 1);
          यदि (!setting->दत्त.v_string)
            {
              परिणाम = XSETTINGS_NO_MEM;
              गच्छ बहिर्गमनम्;
            }

          स्मृतिं_प्रतिलिख (setting->दत्त.v_string, बफर_2.pos, v_int);
          setting->दत्त.v_string[v_int] = '\0';
          बफर_2.pos += pad_len;

          भङ्ग;
        पक्ष XSETTINGS_TYPE_COLOR:
          परिणाम = fetch_ushort (&बफर_2, &setting->दत्त.v_color.red);
          यदि (परिणाम != XSETTINGS_SUCCESS)
            गच्छ बहिर्गमनम्;
          परिणाम = fetch_ushort (&बफर_2, &setting->दत्त.v_color.green);
          यदि (परिणाम != XSETTINGS_SUCCESS)
            गच्छ बहिर्गमनम्;
          परिणाम = fetch_ushort (&बफर_2, &setting->दत्त.v_color.blue);
          यदि (परिणाम != XSETTINGS_SUCCESS)
            गच्छ बहिर्गमनम्;
          परिणाम = fetch_ushort (&बफर_2, &setting->दत्त.v_color.alpha);
          यदि (परिणाम != XSETTINGS_SUCCESS)
            गच्छ बहिर्गमनम्;

          भङ्ग;
        स्वभाव:
          /* Quietly ignore unknown types */
          भङ्ग;
        }

      setting->type = type;

      परिणाम = xsettings_list_निवेशय (&settings, setting);
      यदि (परिणाम != XSETTINGS_SUCCESS)
        गच्छ बहिर्गमनम्;

      setting = रिक्त;
    }

 बहिर्गमनम्:

  यदि (परिणाम != XSETTINGS_SUCCESS)
    {
      विकल्प (परिणाम)
        {
        पक्ष XSETTINGS_NO_MEM:
          fprintf(stderr, "Out of memory reading XSETTINGS property\n");
          भङ्ग;
        पक्ष XSETTINGS_ACCESS:
          fprintf(stderr, "Invalid XSETTINGS property (read off end)\n");
          भङ्ग;
        पक्ष XSETTINGS_DUPLICATE_प्रविष्टिः:
          fprintf (stderr, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        पक्ष XSETTINGS_NO_प्रविष्टिः:
          भङ्ग;
        }

      यदि (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = रिक्त;

    }

  प्रत्यागम settings;
}

स्थिर शून्य
read_settings (XSettingsClient *client)
{
  Atom type;
  पूर्णाङ्क format;
  अचिह्नित दीर्घ n_वस्तूनि;
  अचिह्नित दीर्घ अष्टकानि_after;
  अचिह्नित वर्ण *दत्त;
  पूर्णाङ्क परिणाम;

  पूर्णाङ्क (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = रिक्त;

  यदि (client->manager_गवाक्षः)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      परिणाम = X11_XGet_गवाक्षः_Property (client->display, client->manager_गवाक्षः,
                                       client->xsettings_atom, 0, LONG_MAX,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_वस्तूनि, &अष्टकानि_after, &दत्त);
      X11_XSetErrorHandler (old_handler);

      यदि (परिणाम == Success && type != None)
        {
          यदि (type != client->xsettings_atom)
            {
              fprintf (stderr, "Invalid type for XSETTINGS property");
            }
          अन्यथा यदि (format != 8)
            {
              fprintf (stderr, "Invalid format for XSETTINGS property %d", format);
            }
          अन्यथा
            client->settings = parse_settings (दत्त, n_वस्तूनि);

          X11_XFree (दत्त);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

स्थिर शून्य
सङ्कलय_events (Display *display,
            गवाक्षः_2   गवाक्षः,
            दीर्घ     आवरणम्)
{
  XWindow_गुणाः attr;

  X11_XGet_गवाक्षः_गुणाः (display, गवाक्षः, &attr);
  X11_XSelect_निवेशः (display, गवाक्षः, attr.your_event_आवरणम् | आवरणम्);
}

स्थिर शून्य
check_manager_गवाक्षः (XSettingsClient *client)
{
  यदि (client->manager_गवाक्षः && client->watch)
    client->watch (client->manager_गवाक्षः, False, 0, client->cb_दत्त);

  यदि (client->grab)
    client->grab (client->display);
  अन्यथा
    X11_XGrabServer (client->display);

  client->manager_गवाक्षः = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  यदि (client->manager_गवाक्षः)
    X11_XSelect_निवेशः (client->display, client->manager_गवाक्षः,
                      Property_Change_आवरणम् | Structure_Notify_आवरणम्);

  यदि (client->ungrab)
    client->ungrab (client->display);
  अन्यथा
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  यदि (client->manager_गवाक्षः && client->watch)
    {
      यदि (!client->watch (client->manager_गवाक्षः, True,
                          Property_Change_आवरणम् | Structure_Notify_आवरणम्,
                          client->cb_दत्त))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_गवाक्षः = None;
          प्रत्यागम;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      पूर्णाङ्क                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      शून्य                *cb_दत्त)
{
  प्रत्यागम xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_दत्त,
                                               रिक्त, रिक्त);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      पूर्णाङ्क                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      शून्य                *cb_दत्त,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  वर्ण बफर_2[256];
  वर्ण *atom_नामानि[3];
  Atom atoms[3];

  client = स्मृतिं_देहि (परिमाण *client);
  यदि (!client)
    प्रत्यागम रिक्त;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_दत्त = cb_दत्त;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_गवाक्षः = None;
  client->settings = रिक्त;

  SDL_snprintf(बफर_2, परिमाण(बफर_2), "_XSETTINGS_S%d", screen);
  atom_नामानि[0] = बफर_2;
  atom_नामानि[1] = "_XSETTINGS_SETTINGS";
  atom_नामानि[2] = "MANAGER";

#यदि_परिभाषितम् HAVE_XINTERNATOMS
  XInternAtoms (display, atom_नामानि, 3, False, atoms);
#अन्यथा
  atoms[0] = X11_XInternAtom (display, atom_नामानि[0], False);
  atoms[1] = X11_XInternAtom (display, atom_नामानि[1], False);
  atoms[2] = X11_XInternAtom (display, atom_नामानि[2], False);
#यदि_अन्तः

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  सङ्कलय_events (display, मूलम्_गवाक्षः (display, screen), Structure_Notify_आवरणम्);

  यदि (client->watch)
    client->watch (मूलम्_गवाक्षः (display, screen), True, Structure_Notify_आवरणम्,
                   client->cb_दत्त);

  check_manager_गवाक्षः (client);

  प्रत्यागम client;
}


शून्य
xsettings_client_समुच्चयः_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

शून्य
xsettings_client_समुच्चयः_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

शून्य
xsettings_client_destroy (XSettingsClient *client)
{
  यदि (client->watch)
    client->watch (मूलम्_गवाक्षः (client->display, client->screen),
                   False, 0, client->cb_दत्त);
  यदि (client->manager_गवाक्षः && client->watch)
    client->watch (client->manager_गवाक्षः, False, 0, client->cb_दत्त);

  xsettings_list_free (client->settings);
  मुक्त (client);
}

XSettings_परिणाम
xsettings_client_get_setting (XSettingsClient   *client,
                              ध्रुव वर्ण        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *अन्वेषणम् = xsettings_list_lookup (client->settings, name);
  यदि (अन्वेषणम्)
    {
      *setting = xsettings_setting_copy (अन्वेषणम्);
      प्रत्यागम *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  अन्यथा
    प्रत्यागम XSETTINGS_NO_प्रविष्टिः;
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
  यदि (xev->xany.गवाक्षः == मूलम्_गवाक्षः (client->display, client->screen))
    {
      यदि (xev->xany.type == Client_सन्देशः &&
          xev->xclient.सन्देशः_type == client->manager_atom &&
          xev->xclient.दत्त.l[1] == client->selection_atom)
        {
          check_manager_गवाक्षः (client);
          प्रत्यागम True;
        }
    }
  अन्यथा यदि (xev->xany.गवाक्षः == client->manager_गवाक्षः)
    {
      यदि (xev->xany.type == DestroyNotify)
        {
          check_manager_गवाक्षः (client);
          प्रत्यागम False;
        }
      अन्यथा यदि (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          प्रत्यागम True;
        }
    }

  प्रत्यागम False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *परिणाम;
  size_t str_len;

  परिणाम = स्मृतिं_देहि (परिमाण *परिणाम);
  यदि (!परिणाम)
    प्रत्यागम रिक्त;

  str_len = वाक्यदैर्घ्यम् (setting->name);
  परिणाम->name = स्मृतिं_देहि (str_len + 1);
  यदि (!परिणाम->name)
    गच्छ err;

  स्मृतिं_प्रतिलिख (परिणाम->name, setting->name, str_len + 1);

  परिणाम->type = setting->type;

  विकल्प (setting->type)
    {
    पक्ष XSETTINGS_TYPE_INT:
      परिणाम->दत्त.v_int = setting->दत्त.v_int;
      भङ्ग;
    पक्ष XSETTINGS_TYPE_COLOR:
      परिणाम->दत्त.v_color = setting->दत्त.v_color;
      भङ्ग;
    पक्ष XSETTINGS_TYPE_STRING:
      str_len = वाक्यदैर्घ्यम् (setting->दत्त.v_string);
      परिणाम->दत्त.v_string = स्मृतिं_देहि (str_len + 1);
      यदि (!परिणाम->दत्त.v_string)
        गच्छ err;

      स्मृतिं_प्रतिलिख (परिणाम->दत्त.v_string, setting->दत्त.v_string, str_len + 1);
      भङ्ग;
    }

  परिणाम->चरमः_change_serial = setting->चरमः_change_serial;

  प्रत्यागम परिणाम;

 err:
  मुक्त(परिणाम->name); // This should NOT be SDL_free()
  मुक्त(परिणाम); // This should NOT be SDL_free()

  प्रत्यागम रिक्त;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = रिक्त;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = रिक्त;

  यावत् (old_iter)
    {
      XSettingsList *new_ग्रन्थिः;

      new_ग्रन्थिः = स्मृतिं_देहि (परिमाण *new_ग्रन्थिः);
      यदि (!new_ग्रन्थिः)
        गच्छ error;

      new_ग्रन्थिः->setting = xsettings_setting_copy (old_iter->setting);
      यदि (!new_ग्रन्थिः->setting)
        {
          मुक्त (new_ग्रन्थिः);
          गच्छ error;
        }

      यदि (new_iter)
        new_iter->अग्र = new_ग्रन्थिः;
      अन्यथा
        {
          new = new_ग्रन्थिः;
          new->अग्र = रिक्त;
        }


      new_iter = new_ग्रन्थिः;

      old_iter = old_iter->अग्र;
    }

  प्रत्यागम new;

 error:
  xsettings_list_free (new);
  प्रत्यागम रिक्त;
}

पूर्णाङ्क
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  यदि (setting_a->type != setting_b->type)
    प्रत्यागम 0;

  यदि (वाक्यं_तुलय (setting_a->name, setting_b->name) != 0)
    प्रत्यागम 0;

  विकल्प (setting_a->type)
    {
    पक्ष XSETTINGS_TYPE_INT:
      प्रत्यागम setting_a->दत्त.v_int == setting_b->दत्त.v_int;
    पक्ष XSETTINGS_TYPE_COLOR:
      प्रत्यागम (setting_a->दत्त.v_color.red == setting_b->दत्त.v_color.red &&
              setting_a->दत्त.v_color.green == setting_b->दत्त.v_color.green &&
              setting_a->दत्त.v_color.blue == setting_b->दत्त.v_color.blue &&
              setting_a->दत्त.v_color.alpha == setting_b->दत्त.v_color.alpha);
    पक्ष XSETTINGS_TYPE_STRING:
      प्रत्यागम वाक्यं_तुलय (setting_a->दत्त.v_string, setting_b->दत्त.v_string) == 0;
    }

  प्रत्यागम 0;
}

शून्य
xsettings_setting_free (XSettingsSetting *setting)
{
  यदि (setting->type == XSETTINGS_TYPE_STRING)
    मुक्त (setting->दत्त.v_string);

  मुक्त(setting->name); // This should NOT be SDL_free()
  मुक्त(setting); // This should NOT be SDL_free()
}

शून्य
xsettings_list_free (XSettingsList *list)
{
  यावत् (list)
    {
      XSettingsList *अग्र = list->अग्र;

      xsettings_setting_free (list->setting);
      मुक्त (list);

      list = अग्र;
    }
}

XSettings_परिणाम
xsettings_list_निवेशय (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *ग्रन्थिः;
  XSettingsList *iter;
  XSettingsList *चरमः = रिक्त;

  ग्रन्थिः = स्मृतिं_देहि (परिमाण *ग्रन्थिः);
  यदि (!ग्रन्थिः)
    प्रत्यागम XSETTINGS_NO_MEM;
  ग्रन्थिः->setting = setting;

  iter = *list;
  यावत् (iter)
    {
      पूर्णाङ्क cmp = वाक्यं_तुलय (setting->name, iter->setting->name);

      यदि (cmp < 0)
        भङ्ग;
      अन्यथा यदि (cmp == 0)
        {
          मुक्त (ग्रन्थिः);
          प्रत्यागम XSETTINGS_DUPLICATE_प्रविष्टिः;
        }

      चरमः = iter;
      iter = iter->अग्र;
    }

  यदि (चरमः)
    चरमः->अग्र = ग्रन्थिः;
  अन्यथा
    *list = ग्रन्थिः;

  ग्रन्थिः->अग्र = iter;

  प्रत्यागम XSETTINGS_SUCCESS;
}

XSettings_परिणाम
xsettings_list_delete (XSettingsList **list,
                       ध्रुव वर्ण     *name)
{
  XSettingsList *iter;
  XSettingsList *चरमः = रिक्त;

  iter = *list;
  यावत् (iter)
    {
      यदि (वाक्यं_तुलय (name, iter->setting->name) == 0)
        {
          यदि (चरमः)
            चरमः->अग्र = iter->अग्र;
          अन्यथा
            *list = iter->अग्र;

          xsettings_setting_free (iter->setting);
          मुक्त (iter);

          प्रत्यागम XSETTINGS_SUCCESS;
        }

      चरमः = iter;
      iter = iter->अग्र;
    }

  प्रत्यागम XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       ध्रुव वर्ण    *name)
{
  XSettingsList *iter;

  iter = list;
  यावत् (iter)
    {
      यदि (वाक्यं_तुलय (name, iter->setting->name) == 0)
        प्रत्यागम iter->setting;

      iter = iter->अग्र;
    }

  प्रत्यागम रिक्त;
}

वर्ण
xsettings_byte_क्रमः (शून्य)
{
  CARD32 myint = 0x01020304;
  प्रत्यागम (*(वर्ण *)&myint == 1) ? MSBFirst : LSBFirst;
}

#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11 */

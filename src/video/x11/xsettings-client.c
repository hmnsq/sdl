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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11video.h"

#समावेश <limits.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "xsettings-client.h"

काष्ठा _XSettingsClient
{
  Display *display;
  पूर्णांक screen;
  XSettingsNotifyFunc notify;
  XSettingsWatchFunc watch;
  व्योम *cb_तथ्य;

  XSettingsGrabFunc grab;
  XSettingsGrabFunc ungrab;

  Window manager_window;
  Atom manager_atom;
  Atom selection_atom;
  Atom xsettings_atom;

  XSettingsList *settings;
};

अटल व्योम
notify_changes (XSettingsClient *client,
                XSettingsList   *old_list)
{
  XSettingsList *old_iter = old_list;
  XSettingsList *new_iter = client->settings;

  अगर (!client->notify)
    वापस;

  जबतक (old_iter || new_iter)
    {
      पूर्णांक cmp;

      अगर (old_iter && new_iter)
        cmp = म_भेद (old_iter->setting->name, new_iter->setting->name);
      अन्यथा अगर (old_iter)
        cmp = -1;
      अन्यथा
        cmp = 1;

      अगर (cmp < 0)
        {
          client->notify (old_iter->setting->name,
                          XSETTINGS_ACTION_DELETED,
                          शून्य,
                          client->cb_तथ्य);
        }
      अन्यथा अगर (cmp == 0)
        {
          अगर (!xsettings_setting_equal (old_iter->setting,
                                        new_iter->setting))
            client->notify (old_iter->setting->name,
                            XSETTINGS_ACTION_CHANGED,
                            new_iter->setting,
                            client->cb_तथ्य);
        }
      अन्यथा
        {
          client->notify (new_iter->setting->name,
                          XSETTINGS_ACTION_NEW,
                          new_iter->setting,
                          client->cb_तथ्य);
        }

      अगर (old_iter)
        old_iter = old_iter->अग्र;
      अगर (new_iter)
        new_iter = new_iter->अग्र;
    }
}

अटल पूर्णांक
ignore_errors (Display *display, XErrorEvent *event)
{
  वापस True;
}

अटल अक्षर local_byte_order = '\0';

#घोषणा BYTES_बायाँ(बफर_2) ((बफर_2)->तथ्य + (बफर_2)->len - (बफर_2)->pos)

अटल XSettings_परिणाम
fetch_card16 (XSettings_बफर *बफर_2,
              CARD16          *परिणाम)
{
  CARD16 x;

  अगर (BYTES_बायाँ (बफर_2) < 2)
    वापस XSETTINGS_ACCESS;

  x = *(CARD16 *)बफर_2->pos;
  बफर_2->pos += 2;

  अगर (बफर_2->byte_order == local_byte_order)
    *परिणाम = x;
  अन्यथा
    *परिणाम = (x << 8) | (x >> 8);

  वापस XSETTINGS_SUCCESS;
}

अटल XSettings_परिणाम
fetch_ushort (XSettings_बफर *बफर_2,
              अचिन्हित लघु  *परिणाम)
{
  CARD16 x;
  XSettings_परिणाम r;

  r = fetch_card16 (बफर_2, &x);
  अगर (r == XSETTINGS_SUCCESS)
    *परिणाम = x;

  वापस r;
}

अटल XSettings_परिणाम
fetch_card32 (XSettings_बफर *बफर_2,
              CARD32          *परिणाम)
{
  CARD32 x;

  अगर (BYTES_बायाँ (बफर_2) < 4)
    वापस XSETTINGS_ACCESS;

  x = *(CARD32 *)बफर_2->pos;
  बफर_2->pos += 4;

  अगर (बफर_2->byte_order == local_byte_order)
    *परिणाम = x;
  अन्यथा
    *परिणाम = (x << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | (x >> 24);

  वापस XSETTINGS_SUCCESS;
}

अटल XSettings_परिणाम
fetch_card8 (XSettings_बफर *बफर_2,
             CARD8           *परिणाम)
{
  अगर (BYTES_बायाँ (बफर_2) < 1)
    वापस XSETTINGS_ACCESS;

  *परिणाम = *(CARD8 *)बफर_2->pos;
  बफर_2->pos += 1;

  वापस XSETTINGS_SUCCESS;
}

#घोषणा XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

अटल XSettingsList *
parse_settings (अचिन्हित अक्षर *तथ्य,
                माप_प्रकार         len)
{
  XSettings_बफर बफर_2;
  XSettings_परिणाम परिणाम = XSETTINGS_SUCCESS;
  XSettingsList *settings = शून्य;
  CARD32 serial;
  CARD32 n_entries;
  CARD32 i;
  XSettingsSetting *setting = शून्य;
  अक्षर बफर_byte_order = '\0';

  local_byte_order = xsettings_byte_order ();

  बफर_2.pos = बफर_2.तथ्य = तथ्य;
  बफर_2.len = len;
  बफर_2.byte_order = '\0';

  परिणाम = fetch_card8 (&बफर_2, (अचिन्हित अक्षर *) &बफर_byte_order);
  अगर (बफर_byte_order != MSBFirst &&
      बफर_byte_order != LSBFirst)
    {
      ख_लिखो (मानक_त्रुटि, "Invalid byte order in XSETTINGS property\n");
      परिणाम = XSETTINGS_FAILED;
      जाओ out;
    }

  बफर_2.byte_order = बफर_byte_order;
  बफर_2.pos += 3;

  परिणाम = fetch_card32 (&बफर_2, &serial);
  अगर (परिणाम != XSETTINGS_SUCCESS)
    जाओ out;

  परिणाम = fetch_card32 (&बफर_2, &n_entries);
  अगर (परिणाम != XSETTINGS_SUCCESS)
    जाओ out;

  क्रम (i = 0; i < n_entries; i++)
    {
      CARD8 type;
      CARD16 name_len;
      CARD32 v_int;
      माप_प्रकार pad_len;

      परिणाम = fetch_card8 (&बफर_2, &type);
      अगर (परिणाम != XSETTINGS_SUCCESS)
        जाओ out;

      बफर_2.pos += 1;

      परिणाम = fetch_card16 (&बफर_2, &name_len);
      अगर (परिणाम != XSETTINGS_SUCCESS)
        जाओ out;

      pad_len = XSETTINGS_PAD(name_len, 4);
      अगर (BYTES_बायाँ (&बफर_2) < pad_len)
        {
          परिणाम = XSETTINGS_ACCESS;
          जाओ out;
        }

      setting = दो_स्मृति (माप *setting);
      अगर (!setting)
        {
          परिणाम = XSETTINGS_NO_MEM;
          जाओ out;
        }
      setting->type = XSETTINGS_TYPE_INT; /* No allocated memory */

      setting->name = दो_स्मृति (name_len + 1);
      अगर (!setting->name)
        {
          परिणाम = XSETTINGS_NO_MEM;
          जाओ out;
        }

      स_नकल (setting->name, बफर_2.pos, name_len);
      setting->name[name_len] = '\0';
      बफर_2.pos += pad_len;

      परिणाम = fetch_card32 (&बफर_2, &v_int);
      अगर (परिणाम != XSETTINGS_SUCCESS)
        जाओ out;
      setting->last_change_serial = v_int;

      चयन (type)
        {
        हाल XSETTINGS_TYPE_INT:
          परिणाम = fetch_card32 (&बफर_2, &v_int);
          अगर (परिणाम != XSETTINGS_SUCCESS)
            जाओ out;

          setting->तथ्य.v_int = (INT32)v_int;
          अवरोध;
        हाल XSETTINGS_TYPE_STRING:
          परिणाम = fetch_card32 (&बफर_2, &v_int);
          अगर (परिणाम != XSETTINGS_SUCCESS)
            जाओ out;

          pad_len = XSETTINGS_PAD (v_int, 4);
          अगर (v_int + 1 == 0 || /* Guard against wrap-around */
              BYTES_बायाँ (&बफर_2) < pad_len)
            {
              परिणाम = XSETTINGS_ACCESS;
              जाओ out;
            }

          setting->तथ्य.v_string = दो_स्मृति (v_int + 1);
          अगर (!setting->तथ्य.v_string)
            {
              परिणाम = XSETTINGS_NO_MEM;
              जाओ out;
            }

          स_नकल (setting->तथ्य.v_string, बफर_2.pos, v_int);
          setting->तथ्य.v_string[v_int] = '\0';
          बफर_2.pos += pad_len;

          अवरोध;
        हाल XSETTINGS_TYPE_COLOR:
          परिणाम = fetch_ushort (&बफर_2, &setting->तथ्य.v_color.red);
          अगर (परिणाम != XSETTINGS_SUCCESS)
            जाओ out;
          परिणाम = fetch_ushort (&बफर_2, &setting->तथ्य.v_color.green);
          अगर (परिणाम != XSETTINGS_SUCCESS)
            जाओ out;
          परिणाम = fetch_ushort (&बफर_2, &setting->तथ्य.v_color.blue);
          अगर (परिणाम != XSETTINGS_SUCCESS)
            जाओ out;
          परिणाम = fetch_ushort (&बफर_2, &setting->तथ्य.v_color.alpha);
          अगर (परिणाम != XSETTINGS_SUCCESS)
            जाओ out;

          अवरोध;
        शेष:
          /* Quietly ignore unknown types */
          अवरोध;
        }

      setting->type = type;

      परिणाम = xsettings_list_जोड़ो (&settings, setting);
      अगर (परिणाम != XSETTINGS_SUCCESS)
        जाओ out;

      setting = शून्य;
    }

 out:

  अगर (परिणाम != XSETTINGS_SUCCESS)
    {
      चयन (परिणाम)
        {
        हाल XSETTINGS_NO_MEM:
          ख_लिखो(मानक_त्रुटि, "Out of memory reading XSETTINGS property\n");
          अवरोध;
        हाल XSETTINGS_ACCESS:
          ख_लिखो(मानक_त्रुटि, "Invalid XSETTINGS property (read off end)\n");
          अवरोध;
        हाल XSETTINGS_DUPLICATE_ENTRY:
          ख_लिखो (मानक_त्रुटि, "Duplicate XSETTINGS entry for '%s'\n", setting->name);
          SDL_FALLTHROUGH;
        हाल XSETTINGS_FAILED:
          SDL_FALLTHROUGH;
        हाल XSETTINGS_SUCCESS:
          SDL_FALLTHROUGH;
        हाल XSETTINGS_NO_ENTRY:
          अवरोध;
        }

      अगर (setting)
        xsettings_setting_free (setting);

      xsettings_list_free (settings);
      settings = शून्य;

    }

  वापस settings;
}

अटल व्योम
read_settings (XSettingsClient *client)
{
  Atom type;
  पूर्णांक format;
  अचिन्हित दीर्घ n_वस्तुएँ;
  अचिन्हित दीर्घ bytes_after;
  अचिन्हित अक्षर *तथ्य;
  पूर्णांक परिणाम;

  पूर्णांक (*old_handler) (Display *, XErrorEvent *);

  XSettingsList *old_list = client->settings;

  client->settings = शून्य;

  अगर (client->manager_window)
    {
      old_handler = X11_XSetErrorHandler (ignore_errors);
      परिणाम = X11_XGetWindowProperty (client->display, client->manager_window,
                                       client->xsettings_atom, 0, दीर्घ_उच्च,
                                       False, client->xsettings_atom,
                                       &type, &format, &n_वस्तुएँ, &bytes_after, &तथ्य);
      X11_XSetErrorHandler (old_handler);

      अगर (परिणाम == Success && type != None)
        {
          अगर (type != client->xsettings_atom)
            {
              ख_लिखो (मानक_त्रुटि, "Invalid type for XSETTINGS property");
            }
          अन्यथा अगर (format != 8)
            {
              ख_लिखो (मानक_त्रुटि, "Invalid format for XSETTINGS property %d", format);
            }
          अन्यथा
            client->settings = parse_settings (तथ्य, n_वस्तुएँ);

          X11_XFree (तथ्य);
        }
    }

  notify_changes (client, old_list);
  xsettings_list_free (old_list);
}

अटल व्योम
add_events (Display *display,
            Window   window,
            दीर्घ     mask)
{
  XWindowAttributes attr;

  X11_XGetWindowAttributes (display, window, &attr);
  X11_XSelect_निवेश (display, window, attr.your_event_mask | mask);
}

अटल व्योम
check_manager_window (XSettingsClient *client)
{
  अगर (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_तथ्य);

  अगर (client->grab)
    client->grab (client->display);
  अन्यथा
    X11_XGrabServer (client->display);

  client->manager_window = X11_XGetSelectionOwner (client->display,
                                                   client->selection_atom);
  अगर (client->manager_window)
    X11_XSelect_निवेश (client->display, client->manager_window,
                      PropertyChangeMask | StructureNotifyMask);

  अगर (client->ungrab)
    client->ungrab (client->display);
  अन्यथा
    X11_XUngrabServer (client->display);

  X11_XFlush (client->display);

  अगर (client->manager_window && client->watch)
    {
      अगर (!client->watch (client->manager_window, True,
                          PropertyChangeMask | StructureNotifyMask,
                          client->cb_तथ्य))
        {
          /* Inability to watch the window probably means that it was destroyed
           * after we ungrabbed
           */
          client->manager_window = None;
          वापस;
        }
    }


  read_settings (client);
}

XSettingsClient *
xsettings_client_new (Display             *display,
                      पूर्णांक                  screen,
                      XSettingsNotifyFunc  notify,
                      XSettingsWatchFunc   watch,
                      व्योम                *cb_तथ्य)
{
  वापस xsettings_client_new_with_grab_funcs (display, screen, notify, watch, cb_तथ्य,
                                               शून्य, शून्य);
}

XSettingsClient *
xsettings_client_new_with_grab_funcs (Display             *display,
                                      पूर्णांक                  screen,
                                      XSettingsNotifyFunc  notify,
                                      XSettingsWatchFunc   watch,
                                      व्योम                *cb_तथ्य,
                                      XSettingsGrabFunc    grab,
                                      XSettingsGrabFunc    ungrab)
{
  XSettingsClient *client;
  अक्षर बफर_2[256];
  अक्षर *atom_names[3];
  Atom atoms[3];

  client = दो_स्मृति (माप *client);
  अगर (!client)
    वापस शून्य;

  client->display = display;
  client->screen = screen;
  client->notify = notify;
  client->watch = watch;
  client->cb_तथ्य = cb_तथ्य;
  client->grab = grab;
  client->ungrab = ungrab;

  client->manager_window = None;
  client->settings = शून्य;

  SDL_snprintf(बफर_2, माप(बफर_2), "_XSETTINGS_S%d", screen);
  atom_names[0] = बफर_2;
  atom_names[1] = "_XSETTINGS_SETTINGS";
  atom_names[2] = "MANAGER";

#अगर_घोषित HAVE_XINTERNATOMS
  XInternAtoms (display, atom_names, 3, False, atoms);
#अन्यथा
  atoms[0] = X11_XInternAtom (display, atom_names[0], False);
  atoms[1] = X11_XInternAtom (display, atom_names[1], False);
  atoms[2] = X11_XInternAtom (display, atom_names[2], False);
#पूर्ण_अगर

  client->selection_atom = atoms[0];
  client->xsettings_atom = atoms[1];
  client->manager_atom = atoms[2];

  /* Select on StructureNotify so we get MANAGER events
   */
  add_events (display, मूल_Window (display, screen), StructureNotifyMask);

  अगर (client->watch)
    client->watch (मूल_Window (display, screen), True, StructureNotifyMask,
                   client->cb_तथ्य);

  check_manager_window (client);

  वापस client;
}


व्योम
xsettings_client_set_grab_func   (XSettingsClient      *client,
                                  XSettingsGrabFunc     grab)
{
  client->grab = grab;
}

व्योम
xsettings_client_set_ungrab_func (XSettingsClient      *client,
                                  XSettingsGrabFunc     ungrab)
{
  client->ungrab = ungrab;
}

व्योम
xsettings_client_destroy (XSettingsClient *client)
{
  अगर (client->watch)
    client->watch (मूल_Window (client->display, client->screen),
                   False, 0, client->cb_तथ्य);
  अगर (client->manager_window && client->watch)
    client->watch (client->manager_window, False, 0, client->cb_तथ्य);

  xsettings_list_free (client->settings);
  मुक्त (client);
}

XSettings_परिणाम
xsettings_client_get_setting (XSettingsClient   *client,
                              स्थिर अक्षर        *name,
                              XSettingsSetting **setting)
{
  XSettingsSetting *खोज = xsettings_list_lookup (client->settings, name);
  अगर (खोज)
    {
      *setting = xsettings_setting_copy (खोज);
      वापस *setting ? XSETTINGS_SUCCESS : XSETTINGS_NO_MEM;
    }
  अन्यथा
    वापस XSETTINGS_NO_ENTRY;
}

Bool
xsettings_client_process_event (XSettingsClient *client,
                                स्थिर XEvent    *xev)
{
  /* The checks here will not unlikely cause us to reread
   * the properties from the manager window a number of
   * times when the manager changes from A->B. But manager changes
   * are going to be pretty rare.
   */
  अगर (xev->xany.window == मूल_Window (client->display, client->screen))
    {
      अगर (xev->xany.type == ClientMessage &&
          xev->xclient.message_type == client->manager_atom &&
          xev->xclient.तथ्य.l[1] == client->selection_atom)
        {
          check_manager_window (client);
          वापस True;
        }
    }
  अन्यथा अगर (xev->xany.window == client->manager_window)
    {
      अगर (xev->xany.type == DestroyNotify)
        {
          check_manager_window (client);
          वापस False;
        }
      अन्यथा अगर (xev->xany.type == PropertyNotify)
        {
          read_settings (client);
          वापस True;
        }
    }

  वापस False;
}

XSettingsSetting *
xsettings_setting_copy (XSettingsSetting *setting)
{
  XSettingsSetting *परिणाम;
  माप_प्रकार str_len;

  परिणाम = दो_स्मृति (माप *परिणाम);
  अगर (!परिणाम)
    वापस शून्य;

  str_len = म_माप (setting->name);
  परिणाम->name = दो_स्मृति (str_len + 1);
  अगर (!परिणाम->name)
    जाओ err;

  स_नकल (परिणाम->name, setting->name, str_len + 1);

  परिणाम->type = setting->type;

  चयन (setting->type)
    {
    हाल XSETTINGS_TYPE_INT:
      परिणाम->तथ्य.v_int = setting->तथ्य.v_int;
      अवरोध;
    हाल XSETTINGS_TYPE_COLOR:
      परिणाम->तथ्य.v_color = setting->तथ्य.v_color;
      अवरोध;
    हाल XSETTINGS_TYPE_STRING:
      str_len = म_माप (setting->तथ्य.v_string);
      परिणाम->तथ्य.v_string = दो_स्मृति (str_len + 1);
      अगर (!परिणाम->तथ्य.v_string)
        जाओ err;

      स_नकल (परिणाम->तथ्य.v_string, setting->तथ्य.v_string, str_len + 1);
      अवरोध;
    }

  परिणाम->last_change_serial = setting->last_change_serial;

  वापस परिणाम;

 err:
  मुक्त(परिणाम->name); // This should NOT be SDL_free()
  मुक्त(परिणाम); // This should NOT be SDL_free()

  वापस शून्य;
}

XSettingsList *
xsettings_list_copy (XSettingsList *list)
{
  XSettingsList *new = शून्य;
  XSettingsList *old_iter = list;
  XSettingsList *new_iter = शून्य;

  जबतक (old_iter)
    {
      XSettingsList *new_गाँठ;

      new_गाँठ = दो_स्मृति (माप *new_गाँठ);
      अगर (!new_गाँठ)
        जाओ error;

      new_गाँठ->setting = xsettings_setting_copy (old_iter->setting);
      अगर (!new_गाँठ->setting)
        {
          मुक्त (new_गाँठ);
          जाओ error;
        }

      अगर (new_iter)
        new_iter->अग्र = new_गाँठ;
      अन्यथा
        {
          new = new_गाँठ;
          new->अग्र = शून्य;
        }


      new_iter = new_गाँठ;

      old_iter = old_iter->अग्र;
    }

  वापस new;

 error:
  xsettings_list_free (new);
  वापस शून्य;
}

पूर्णांक
xsettings_setting_equal (XSettingsSetting *setting_a,
                         XSettingsSetting *setting_b)
{
  अगर (setting_a->type != setting_b->type)
    वापस 0;

  अगर (म_भेद (setting_a->name, setting_b->name) != 0)
    वापस 0;

  चयन (setting_a->type)
    {
    हाल XSETTINGS_TYPE_INT:
      वापस setting_a->तथ्य.v_int == setting_b->तथ्य.v_int;
    हाल XSETTINGS_TYPE_COLOR:
      वापस (setting_a->तथ्य.v_color.red == setting_b->तथ्य.v_color.red &&
              setting_a->तथ्य.v_color.green == setting_b->तथ्य.v_color.green &&
              setting_a->तथ्य.v_color.blue == setting_b->तथ्य.v_color.blue &&
              setting_a->तथ्य.v_color.alpha == setting_b->तथ्य.v_color.alpha);
    हाल XSETTINGS_TYPE_STRING:
      वापस म_भेद (setting_a->तथ्य.v_string, setting_b->तथ्य.v_string) == 0;
    }

  वापस 0;
}

व्योम
xsettings_setting_free (XSettingsSetting *setting)
{
  अगर (setting->type == XSETTINGS_TYPE_STRING)
    मुक्त (setting->तथ्य.v_string);

  मुक्त(setting->name); // This should NOT be SDL_free()
  मुक्त(setting); // This should NOT be SDL_free()
}

व्योम
xsettings_list_free (XSettingsList *list)
{
  जबतक (list)
    {
      XSettingsList *अग्र = list->अग्र;

      xsettings_setting_free (list->setting);
      मुक्त (list);

      list = अग्र;
    }
}

XSettings_परिणाम
xsettings_list_जोड़ो (XSettingsList    **list,
                       XSettingsSetting  *setting)
{
  XSettingsList *गाँठ;
  XSettingsList *iter;
  XSettingsList *last = शून्य;

  गाँठ = दो_स्मृति (माप *गाँठ);
  अगर (!गाँठ)
    वापस XSETTINGS_NO_MEM;
  गाँठ->setting = setting;

  iter = *list;
  जबतक (iter)
    {
      पूर्णांक cmp = म_भेद (setting->name, iter->setting->name);

      अगर (cmp < 0)
        अवरोध;
      अन्यथा अगर (cmp == 0)
        {
          मुक्त (गाँठ);
          वापस XSETTINGS_DUPLICATE_ENTRY;
        }

      last = iter;
      iter = iter->अग्र;
    }

  अगर (last)
    last->अग्र = गाँठ;
  अन्यथा
    *list = गाँठ;

  गाँठ->अग्र = iter;

  वापस XSETTINGS_SUCCESS;
}

XSettings_परिणाम
xsettings_list_delete (XSettingsList **list,
                       स्थिर अक्षर     *name)
{
  XSettingsList *iter;
  XSettingsList *last = शून्य;

  iter = *list;
  जबतक (iter)
    {
      अगर (म_भेद (name, iter->setting->name) == 0)
        {
          अगर (last)
            last->अग्र = iter->अग्र;
          अन्यथा
            *list = iter->अग्र;

          xsettings_setting_free (iter->setting);
          मुक्त (iter);

          वापस XSETTINGS_SUCCESS;
        }

      last = iter;
      iter = iter->अग्र;
    }

  वापस XSETTINGS_FAILED;
}

XSettingsSetting *
xsettings_list_lookup (XSettingsList *list,
                       स्थिर अक्षर    *name)
{
  XSettingsList *iter;

  iter = list;
  जबतक (iter)
    {
      अगर (म_भेद (name, iter->setting->name) == 0)
        वापस iter->setting;

      iter = iter->अग्र;
    }

  वापस शून्य;
}

अक्षर
xsettings_byte_order (व्योम)
{
  CARD32 myint = 0x01020304;
  वापस (*(अक्षर *)&myint == 1) ? MSBFirst : LSBFirst;
}

#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11 */

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
#ifndef XSETTINGS_CLIENT_H
#define XSETTINGS_CLIENT_H

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif /* __cplusplus */

തരനിർവചനം ഘടന _XSettingsBuffer  XSettingsBuffer;
തരനിർവചനം ഘടന _XSettingsColor   XSettingsColor;
തരനിർവചനം ഘടന _XSettingsList    XSettingsList;
തരനിർവചനം ഘടന _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
തരനിർവചനം എണ്ണൽ
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

തരനിർവചനം എണ്ണൽ
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

ഘടന _XSettingsBuffer
{
  അക്ഷരം byte_order;
  size_t len;
  unsigned അക്ഷരം *data;
  unsigned അക്ഷരം *pos;
};

ഘടന _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

ഘടന _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

ഘടന _XSettingsSetting
{
  അക്ഷരം *name;
  XSettingsType type;

  സംഘം {
    പൂർണ്ണസംഖ്യ v_int;
    അക്ഷരം *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
ശൂന്യം              xsettings_setting_free  (XSettingsSetting *setting);
പൂർണ്ണസംഖ്യ               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

ശൂന്യം              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_തിരുകുക (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         സ്ഥിരം അക്ഷരം        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         സ്ഥിരം അക്ഷരം        *name);

അക്ഷരം xsettings_byte_order (ശൂന്യം);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

തരനിർവചനം ഘടന _XSettingsClient XSettingsClient;

തരനിർവചനം എണ്ണൽ
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

തരനിർവചനം ശൂന്യം (*XSettingsNotifyFunc) (സ്ഥിരം അക്ഷരം       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     ശൂന്യം             *cb_data);
തരനിർവചനം Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     ശൂന്യം             *cb_data);
തരനിർവചനം ശൂന്യം (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   പൂർണ്ണസംഖ്യ                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   ശൂന്യം                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       പൂർണ്ണസംഖ്യ                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       ശൂന്യം                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
ശൂന്യം             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
ശൂന്യം             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
ശൂന്യം             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   സ്ഥിരം XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   സ്ഥിരം അക്ഷരം          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

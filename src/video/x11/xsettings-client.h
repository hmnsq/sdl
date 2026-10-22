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
બાહ્ય "C" {
#endif /* __cplusplus */

પ્રકારવ્યાખ્યા સંરચના _XSettingsBuffer  XSettingsBuffer;
પ્રકારવ્યાખ્યા સંરચના _XSettingsColor   XSettingsColor;
પ્રકારવ્યાખ્યા સંરચના _XSettingsList    XSettingsList;
પ્રકારવ્યાખ્યા સંરચના _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
પ્રકારવ્યાખ્યા ગણના
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

પ્રકારવ્યાખ્યા ગણના
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

સંરચના _XSettingsBuffer
{
  અક્ષર byte_order;
  size_t len;
  unsigned અક્ષર *data;
  unsigned અક્ષર *pos;
};

સંરચના _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

સંરચના _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

સંરચના _XSettingsSetting
{
  અક્ષર *name;
  XSettingsType type;

  સંઘ {
    પૂર્ણાંક v_int;
    અક્ષર *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
શૂન્ય              xsettings_setting_free  (XSettingsSetting *setting);
પૂર્ણાંક               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

શૂન્ય              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_ઉમેરો (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         અચલ અક્ષર        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         અચલ અક્ષર        *name);

અક્ષર xsettings_byte_order (શૂન્ય);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

પ્રકારવ્યાખ્યા સંરચના _XSettingsClient XSettingsClient;

પ્રકારવ્યાખ્યા ગણના
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

પ્રકારવ્યાખ્યા શૂન્ય (*XSettingsNotifyFunc) (અચલ અક્ષર       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     શૂન્ય             *cb_data);
પ્રકારવ્યાખ્યા Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     શૂન્ય             *cb_data);
પ્રકારવ્યાખ્યા શૂન્ય (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   પૂર્ણાંક                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   શૂન્ય                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       પૂર્ણાંક                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       શૂન્ય                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
શૂન્ય             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
શૂન્ય             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
શૂન્ય             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   અચલ XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   અચલ અક્ષર          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

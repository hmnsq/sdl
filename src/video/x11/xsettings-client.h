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
বাহ্য "C" {
#endif /* __cplusplus */

প্রকারনির্দেশ সংরচনা _XSettingsBuffer  XSettingsBuffer;
প্রকারনির্দেশ সংরচনা _XSettingsColor   XSettingsColor;
প্রকারনির্দেশ সংরচনা _XSettingsList    XSettingsList;
প্রকারনির্দেশ সংরচনা _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
প্রকারনির্দেশ গণনা
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

প্রকারনির্দেশ গণনা
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

সংরচনা _XSettingsBuffer
{
  বর্ণ byte_order;
  size_t len;
  unsigned বর্ণ *data;
  unsigned বর্ণ *pos;
};

সংরচনা _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

সংরচনা _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

সংরচনা _XSettingsSetting
{
  বর্ণ *name;
  XSettingsType type;

  সঙ্ঘ {
    পূর্ণাঙ্ক v_int;
    বর্ণ *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
শূন্য              xsettings_setting_free  (XSettingsSetting *setting);
পূর্ণাঙ্ক               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

শূন্য              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_ঢোকাও (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ধ্রুব বর্ণ        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         ধ্রুব বর্ণ        *name);

বর্ণ xsettings_byte_order (শূন্য);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

প্রকারনির্দেশ সংরচনা _XSettingsClient XSettingsClient;

প্রকারনির্দেশ গণনা
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

প্রকারনির্দেশ শূন্য (*XSettingsNotifyFunc) (ধ্রুব বর্ণ       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     শূন্য             *cb_data);
প্রকারনির্দেশ Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     শূন্য             *cb_data);
প্রকারনির্দেশ শূন্য (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   পূর্ণাঙ্ক                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   শূন্য                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       পূর্ণাঙ্ক                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       শূন্য                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
শূন্য             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
শূন্য             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
শূন্য             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ধ্রুব XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ধ্রুব বর্ণ          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

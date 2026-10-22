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
#اگر_غیر_تعریف_شدہ XSETTINGS_CLIENT_H
#تعریف_کرو XSETTINGS_CLIENT_H

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم /* __cplusplus */

قسمتعریف ساخت XSettings_بفر_2  XSettings_بفر;
قسمتعریف ساخت _XSettingsColor   XSettingsColor;
قسمتعریف ساخت _XSettingsList    XSettingsList;
قسمتعریف ساخت _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
قسمتعریف شمار
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

قسمتعریف شمار
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_اندراج,
  XSETTINGS_DUPLICATE_اندراج
} XSettings_نتیجہ;

ساخت XSettings_بفر_2
{
  حرف byte_ترتیب;
  size_t len;
  غیرعلامتی حرف *ڈیٹا;
  غیرعلامتی حرف *pos;
};

ساخت _XSettingsColor
{
  غیرعلامتی مختصر red, green, blue, alpha;
};

ساخت _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *اگلا;
};

ساخت _XSettingsSetting
{
  حرف *name;
  XSettingsType type;

  اتحاد {
    صحیح v_int;
    حرف *v_string;
    XSettingsColor v_color;
  } ڈیٹا;

  غیرعلامتی طویل آخری_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
خالی              xsettings_setting_free  (XSettingsSetting *setting);
صحیح               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

خالی              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_نتیجہ   xsettings_list_داخل_کرو (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ثابت حرف        *name);
XSettings_نتیجہ   xsettings_list_delete (XSettingsList    **list,
                                         ثابت حرف        *name);

حرف xsettings_byte_ترتیب (خالی);

#تعریف_کرو XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

قسمتعریف ساخت _XSettingsClient XSettingsClient;

قسمتعریف شمار
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_بدلا,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

قسمتعریف خالی (*XSettingsNotifyFunc) (ثابت حرف       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     خالی             *cb_ڈیٹا);
قسمتعریف Bool (*XSettingsWatchFunc)  (کھڑکی_2            کھڑکی,
                                     Bool              is_آغاز,
                                     طویل              نقاب,
                                     خالی             *cb_ڈیٹا);
قسمتعریف خالی (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   صحیح                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   خالی                *cb_ڈیٹا);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       صحیح                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       خالی                *cb_ڈیٹا,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
خالی             xsettings_client_سیٹ_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
خالی             xsettings_client_سیٹ_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
خالی             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ثابت XEvent        *xev);
XSettings_نتیجہ  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ثابت حرف          *name,
                                                   XSettingsSetting   **setting);

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم /* __cplusplus */

#اگر_ختم /* XSETTINGS_CLIENT_H */

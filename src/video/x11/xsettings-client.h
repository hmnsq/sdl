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
#جيڪڏهن_وصف_نه_ٿيل XSETTINGS_CLIENT_H
#وصف_ڪريو XSETTINGS_CLIENT_H

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو /* __cplusplus */

تعريفنوع بنية XSettings_بفر_2  XSettings_بفر;
تعريفنوع بنية _XSettingsColor   XSettingsColor;
تعريفنوع بنية _XSettingsList    XSettingsList;
تعريفنوع بنية _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
تعريفنوع تعداد
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

تعريفنوع تعداد
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_داخلا,
  XSETTINGS_DUPLICATE_داخلا
} XSettings_نتيجو;

بنية XSettings_بفر_2
{
  حرف byte_ترتيب;
  size_t len;
  بنانشان حرف *معلومات;
  بنانشان حرف *pos;
};

بنية _XSettingsColor
{
  بنانشان ننڍو red, green, blue, alpha;
};

بنية _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *ايندڙ;
};

بنية _XSettingsSetting
{
  حرف *name;
  XSettingsType type;

  اتحاد {
    صحيح v_int;
    حرف *v_string;
    XSettingsColor v_color;
  } معلومات;

  بنانشان ڊگهو آخري_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
فراغ              xsettings_setting_free  (XSettingsSetting *setting);
صحيح               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

فراغ              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_نتيجو   xsettings_list_وجهو (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ثابت حرف        *name);
XSettings_نتيجو   xsettings_list_delete (XSettingsList    **list,
                                         ثابت حرف        *name);

حرف xsettings_byte_ترتيب (فراغ);

#وصف_ڪريو XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

تعريفنوع بنية _XSettingsClient XSettingsClient;

تعريفنوع تعداد
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_بدليو,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

تعريفنوع فراغ (*XSettingsNotifyFunc) (ثابت حرف       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     فراغ             *cb_معلومات);
تعريفنوع Bool (*XSettingsWatchFunc)  (دري_2            دري,
                                     Bool              is_شروعات,
                                     ڊگهو              نقاب,
                                     فراغ             *cb_معلومات);
تعريفنوع فراغ (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   صحيح                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   فراغ                *cb_معلومات);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       صحيح                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       فراغ                *cb_معلومات,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
فراغ             xsettings_client_سيٽ_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
فراغ             xsettings_client_سيٽ_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
فراغ             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ثابت XEvent        *xev);
XSettings_نتيجو  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ثابت حرف          *name,
                                                   XSettingsSetting   **setting);

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو /* __cplusplus */

#جيڪڏهن_پورو /* XSETTINGS_CLIENT_H */

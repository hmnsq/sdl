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
#اگر_تعریف_نشده XSETTINGS_CLIENT_H
#تعریف_کن XSETTINGS_CLIENT_H

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر /* __cplusplus */

تعريفنوع بنية XSettings_میانگیر_2  XSettings_میانگیر;
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
  XSETTINGS_NO_مدخل,
  XSETTINGS_DUPLICATE_مدخل
} XSettings_نتیجه;

بنية XSettings_میانگیر_2
{
  حرف byte_ترتیب;
  size_t len;
  بیعلامت حرف *داده;
  بیعلامت حرف *pos;
};

بنية _XSettingsColor
{
  بیعلامت کوتاه red, green, blue, alpha;
};

بنية _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *بعدی;
};

بنية _XSettingsSetting
{
  حرف *name;
  XSettingsType type;

  اتحاد {
    صحيح v_int;
    حرف *v_string;
    XSettingsColor v_color;
  } داده;

  بیعلامت دراز آخرین_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
فراغ              xsettings_setting_free  (XSettingsSetting *setting);
صحيح               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

فراغ              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_نتیجه   xsettings_list_درج (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ثابت حرف        *name);
XSettings_نتیجه   xsettings_list_delete (XSettingsList    **list,
                                         ثابت حرف        *name);

حرف xsettings_byte_ترتیب (فراغ);

#تعریف_کن XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

تعريفنوع بنية _XSettingsClient XSettingsClient;

تعريفنوع تعداد
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_تغییریافته,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

تعريفنوع فراغ (*XSettingsNotifyFunc) (ثابت حرف       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     فراغ             *cb_داده);
تعريفنوع Bool (*XSettingsWatchFunc)  (پنجره_2            پنجره,
                                     Bool              is_شروع,
                                     دراز              ماسک,
                                     فراغ             *cb_داده);
تعريفنوع فراغ (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   صحيح                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   فراغ                *cb_داده);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       صحيح                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       فراغ                *cb_داده,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
فراغ             xsettings_client_مجموعه_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
فراغ             xsettings_client_مجموعه_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
فراغ             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ثابت XEvent        *xev);
XSettings_نتیجه  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ثابت حرف          *name,
                                                   XSettingsSetting   **setting);

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر /* __cplusplus */

#پایان_اگر /* XSETTINGS_CLIENT_H */

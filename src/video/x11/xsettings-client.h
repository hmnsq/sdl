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
বাহ্যিক "C" {
#endif /* __cplusplus */

প্রকারলেখ কাঠামো XSettings_বাফার_2  XSettings_বাফার;
প্রকারলেখ কাঠামো _XSettingsColor   XSettingsColor;
প্রকারলেখ কাঠামো _XSettingsList    XSettingsList;
প্রকারলেখ কাঠামো _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
প্রকারলেখ গণনা
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

প্রকারলেখ গণনা
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettings_ফলাফল;

কাঠামো XSettings_বাফার_2
{
  অক্ষর byte_order;
  size_t len;
  unsigned অক্ষর *তথ্য;
  unsigned অক্ষর *pos;
};

কাঠামো _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

কাঠামো _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *পরবর্তী;
};

কাঠামো _XSettingsSetting
{
  অক্ষর *name;
  XSettingsType type;

  সংঘ {
    পূর্ণসংখ্যা v_int;
    অক্ষর *v_string;
    XSettingsColor v_color;
  } তথ্য;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
শূন্য              xsettings_setting_free  (XSettingsSetting *setting);
পূর্ণসংখ্যা               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

শূন্য              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_ফলাফল   xsettings_list_ঢোকাও (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ধ্রুবক অক্ষর        *name);
XSettings_ফলাফল   xsettings_list_delete (XSettingsList    **list,
                                         ধ্রুবক অক্ষর        *name);

অক্ষর xsettings_byte_order (শূন্য);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

প্রকারলেখ কাঠামো _XSettingsClient XSettingsClient;

প্রকারলেখ গণনা
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

প্রকারলেখ শূন্য (*XSettingsNotifyFunc) (ধ্রুবক অক্ষর       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     শূন্য             *cb_তথ্য);
প্রকারলেখ Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     শূন্য             *cb_তথ্য);
প্রকারলেখ শূন্য (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   পূর্ণসংখ্যা                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   শূন্য                *cb_তথ্য);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       পূর্ণসংখ্যা                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       শূন্য                *cb_তথ্য,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
শূন্য             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
শূন্য             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
শূন্য             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ধ্রুবক XEvent        *xev);
XSettings_ফলাফল  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ধ্রুবক অক্ষর          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

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
ಬಾಹ್ಯ "C" {
#endif /* __cplusplus */

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _XSettingsBuffer  XSettingsBuffer;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _XSettingsColor   XSettingsColor;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _XSettingsList    XSettingsList;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

ಸಂರಚನಾ _XSettingsBuffer
{
  ವರ್ಣ byte_order;
  size_t len;
  unsigned ವರ್ಣ *data;
  unsigned ವರ್ಣ *pos;
};

ಸಂರಚನಾ _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

ಸಂರಚನಾ _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

ಸಂರಚನಾ _XSettingsSetting
{
  ವರ್ಣ *name;
  XSettingsType type;

  ಸಙ್ಘ {
    ಪೂರ್ಣಾಙ್ಕ v_int;
    ವರ್ಣ *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
ಶೂನ್ಯ              xsettings_setting_free  (XSettingsSetting *setting);
ಪೂರ್ಣಾಙ್ಕ               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

ಶೂನ್ಯ              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_ಸೇರಿಸು (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ಧ್ರುವ ವರ್ಣ        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         ಧ್ರುವ ವರ್ಣ        *name);

ವರ್ಣ xsettings_byte_order (ಶೂನ್ಯ);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _XSettingsClient XSettingsClient;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*XSettingsNotifyFunc) (ಧ್ರುವ ವರ್ಣ       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     ಶೂನ್ಯ             *cb_data);
ಪ್ರಕಾರನಿರ್ದೇಶ Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     ಶೂನ್ಯ             *cb_data);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   ಪೂರ್ಣಾಙ್ಕ                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   ಶೂನ್ಯ                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       ಪೂರ್ಣಾಙ್ಕ                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       ಶೂನ್ಯ                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
ಶೂನ್ಯ             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
ಶೂನ್ಯ             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
ಶೂನ್ಯ             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ಧ್ರುವ XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ಧ್ರುವ ವರ್ಣ          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

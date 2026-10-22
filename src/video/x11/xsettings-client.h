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
बाह्य "C" {
#endif /* __cplusplus */

प्रकारनिर्देश संरचना _XSettingsBuffer  XSettingsBuffer;
प्रकारनिर्देश संरचना _XSettingsColor   XSettingsColor;
प्रकारनिर्देश संरचना _XSettingsList    XSettingsList;
प्रकारनिर्देश संरचना _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
प्रकारनिर्देश गणना
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

प्रकारनिर्देश गणना
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

संरचना _XSettingsBuffer
{
  वर्ण byte_order;
  size_t len;
  unsigned वर्ण *data;
  unsigned वर्ण *pos;
};

संरचना _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

संरचना _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

संरचना _XSettingsSetting
{
  वर्ण *name;
  XSettingsType type;

  सङ्घ {
    पूर्णाङ्क v_int;
    वर्ण *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
शून्य              xsettings_setting_free  (XSettingsSetting *setting);
पूर्णाङ्क               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

शून्य              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_घाला (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ध्रुव वर्ण        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         ध्रुव वर्ण        *name);

वर्ण xsettings_byte_order (शून्य);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

प्रकारनिर्देश संरचना _XSettingsClient XSettingsClient;

प्रकारनिर्देश गणना
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

प्रकारनिर्देश शून्य (*XSettingsNotifyFunc) (ध्रुव वर्ण       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     शून्य             *cb_data);
प्रकारनिर्देश Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     शून्य             *cb_data);
प्रकारनिर्देश शून्य (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   पूर्णाङ्क                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   शून्य                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       पूर्णाङ्क                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       शून्य                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
शून्य             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
शून्य             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
शून्य             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ध्रुव XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ध्रुव वर्ण          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

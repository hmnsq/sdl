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

प्रकारव्याख्या संरचना _XSettingsBuffer  XSettingsBuffer;
प्रकारव्याख्या संरचना _XSettingsColor   XSettingsColor;
प्रकारव्याख्या संरचना _XSettingsList    XSettingsList;
प्रकारव्याख्या संरचना _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
प्रकारव्याख्या गणना
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

प्रकारव्याख्या गणना
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
  अक्षर byte_order;
  माप_प्रकार len;
  अचिन्हित अक्षर *data;
  अचिन्हित अक्षर *pos;
};

संरचना _XSettingsColor
{
  अचिन्हित लघु red, green, blue, alpha;
};

संरचना _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

संरचना _XSettingsSetting
{
  अक्षर *name;
  XSettingsType type;

  संघ {
    पूर्णांक v_int;
    अक्षर *v_string;
    XSettingsColor v_color;
  } data;

  अचिन्हित दीर्घ last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
शून्य              xsettings_setting_free  (XSettingsSetting *setting);
पूर्णांक               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

शून्य              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_घाला (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         स्थिरांक अक्षर        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         स्थिरांक अक्षर        *name);

अक्षर xsettings_byte_order (शून्य);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

प्रकारव्याख्या संरचना _XSettingsClient XSettingsClient;

प्रकारव्याख्या गणना
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

प्रकारव्याख्या शून्य (*XSettingsNotifyFunc) (स्थिरांक अक्षर       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     शून्य             *cb_data);
प्रकारव्याख्या Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     दीर्घ              mask,
                                     शून्य             *cb_data);
प्रकारव्याख्या शून्य (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   पूर्णांक                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   शून्य                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       पूर्णांक                  screen,
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
                                                   स्थिरांक XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   स्थिरांक अक्षर          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

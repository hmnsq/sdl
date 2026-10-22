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
#अगर_अघोषित XSETTINGS_CLIENT_H
#घोषणा XSETTINGS_CLIENT_H

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर /* __cplusplus */

प्रकार काष्ठा XSettings_बफर_2  XSettings_बफर;
प्रकार काष्ठा _XSettingsColor   XSettingsColor;
प्रकार काष्ठा _XSettingsList    XSettingsList;
प्रकार काष्ठा _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
प्रकार क्रमागत
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

प्रकार क्रमागत
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettings_परिणाम;

काष्ठा XSettings_बफर_2
{
  अक्षर byte_order;
  माप_प्रकार len;
  अचिन्हित अक्षर *तथ्य;
  अचिन्हित अक्षर *pos;
};

काष्ठा _XSettingsColor
{
  अचिन्हित लघु red, green, blue, alpha;
};

काष्ठा _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *अग्र;
};

काष्ठा _XSettingsSetting
{
  अक्षर *name;
  XSettingsType type;

  जोड़ {
    पूर्णांक v_int;
    अक्षर *v_string;
    XSettingsColor v_color;
  } तथ्य;

  अचिन्हित दीर्घ last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
व्योम              xsettings_setting_free  (XSettingsSetting *setting);
पूर्णांक               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

व्योम              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_परिणाम   xsettings_list_जोड़ो (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         स्थिर अक्षर        *name);
XSettings_परिणाम   xsettings_list_delete (XSettingsList    **list,
                                         स्थिर अक्षर        *name);

अक्षर xsettings_byte_order (व्योम);

#घोषणा XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

प्रकार काष्ठा _XSettingsClient XSettingsClient;

प्रकार क्रमागत
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

प्रकार व्योम (*XSettingsNotifyFunc) (स्थिर अक्षर       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     व्योम             *cb_तथ्य);
प्रकार Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     दीर्घ              mask,
                                     व्योम             *cb_तथ्य);
प्रकार व्योम (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   पूर्णांक                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   व्योम                *cb_तथ्य);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       पूर्णांक                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       व्योम                *cb_तथ्य,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
व्योम             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
व्योम             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
व्योम             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   स्थिर XEvent        *xev);
XSettings_परिणाम  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   स्थिर अक्षर          *name,
                                                   XSettingsSetting   **setting);

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर /* __cplusplus */

#पूर्ण_अगर /* XSETTINGS_CLIENT_H */

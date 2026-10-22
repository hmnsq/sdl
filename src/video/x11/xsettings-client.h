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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XSETTINGS_CLIENT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XSETTINGS_CLIENT_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ /* __cplusplus */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XSettings_ਬਫਰ_2  XSettings_ਬਫਰ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _XSettingsColor   XSettingsColor;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _XSettingsList    XSettingsList;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ਇੰਦਰਾਜ,
  XSETTINGS_DUPLICATE_ਇੰਦਰਾਜ
} XSettings_ਨਤੀਜਾ;

ਬਣਤਰ XSettings_ਬਫਰ_2
{
  ਅੱਖਰ byte_ਕ੍ਰਮ;
  size_t len;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅੰਕੜੇ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pos;
};

ਬਣਤਰ _XSettingsColor
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ red, green, blue, alpha;
};

ਬਣਤਰ _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *ਅਗਲਾ;
};

ਬਣਤਰ _XSettingsSetting
{
  ਅੱਖਰ *name;
  XSettingsType type;

  ਸੰਘ {
    ਪੂਰਨ v_int;
    ਅੱਖਰ *v_string;
    XSettingsColor v_color;
  } ਅੰਕੜੇ;

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਆਖਰੀ_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
ਖਾਲੀ              xsettings_setting_free  (XSettingsSetting *setting);
ਪੂਰਨ               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

ਖਾਲੀ              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_ਨਤੀਜਾ   xsettings_list_ਪਾਓ (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ਅਚਲ ਅੱਖਰ        *name);
XSettings_ਨਤੀਜਾ   xsettings_list_delete (XSettingsList    **list,
                                         ਅਚਲ ਅੱਖਰ        *name);

ਅੱਖਰ xsettings_byte_ਕ੍ਰਮ (ਖਾਲੀ);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _XSettingsClient XSettingsClient;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_ਬਦਲਿਆ,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*XSettingsNotifyFunc) (ਅਚਲ ਅੱਖਰ       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     ਖਾਲੀ             *cb_ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Bool (*XSettingsWatchFunc)  (ਖਿੜਕੀ_2            ਖਿੜਕੀ,
                                     Bool              is_ਸ਼ੁਰੂ,
                                     ਲੰਮਾ              ਨਕਾਬ,
                                     ਖਾਲੀ             *cb_ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   ਪੂਰਨ                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   ਖਾਲੀ                *cb_ਅੰਕੜੇ);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       ਪੂਰਨ                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       ਖਾਲੀ                *cb_ਅੰਕੜੇ,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
ਖਾਲੀ             xsettings_client_ਸੈੱਟ_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
ਖਾਲੀ             xsettings_client_ਸੈੱਟ_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
ਖਾਲੀ             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ਅਚਲ XEvent        *xev);
XSettings_ਨਤੀਜਾ  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ਅਚਲ ਅੱਖਰ          *name,
                                                   XSettingsSetting   **setting);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ /* __cplusplus */

#ਜੇ_ਅੰਤ /* XSETTINGS_CLIENT_H */

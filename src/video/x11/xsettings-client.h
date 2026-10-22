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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XSETTINGS_CLIENT_H
#ವ್ಯಾಖ್ಯಾನಿಸು XSETTINGS_CLIENT_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ /* __cplusplus */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XSettings_ಬಫರ್_2  XSettings_ಬಫರ್;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _XSettingsColor   XSettingsColor;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _XSettingsList    XSettingsList;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ನಮೂದು,
  XSETTINGS_DUPLICATE_ನಮೂದು
} XSettings_ಫಲಿತಾಂಶ;

ರಚನೆ XSettings_ಬಫರ್_2
{
  ಅಕ್ಷರ byte_ಕ್ರಮ;
  size_t len;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ದತ್ತಾಂಶ;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pos;
};

ರಚನೆ _XSettingsColor
{
  ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ red, green, blue, alpha;
};

ರಚನೆ _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *ಮುಂದಿನ;
};

ರಚನೆ _XSettingsSetting
{
  ಅಕ್ಷರ *name;
  XSettingsType type;

  ಒಕ್ಕೂಟ {
    ಪೂರ್ಣಾಂಕ v_int;
    ಅಕ್ಷರ *v_string;
    XSettingsColor v_color;
  } ದತ್ತಾಂಶ;

  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಕೊನೆಯ_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
ಶೂನ್ಯ              xsettings_setting_free  (XSettingsSetting *setting);
ಪೂರ್ಣಾಂಕ               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

ಶೂನ್ಯ              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_ಫಲಿತಾಂಶ   xsettings_list_ಸೇರಿಸು (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ        *name);
XSettings_ಫಲಿತಾಂಶ   xsettings_list_delete (XSettingsList    **list,
                                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ        *name);

ಅಕ್ಷರ xsettings_byte_ಕ್ರಮ (ಶೂನ್ಯ);

#ವ್ಯಾಖ್ಯಾನಿಸು XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _XSettingsClient XSettingsClient;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_ಬದಲಾಯಿತು,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*XSettingsNotifyFunc) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     ಶೂನ್ಯ             *cb_ದತ್ತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Bool (*XSettingsWatchFunc)  (ಕಿಟಕಿ_2            ಕಿಟಕಿ,
                                     Bool              is_ಆರಂಭ,
                                     ದೀರ್ಘ              ಮುಖವಾಡ,
                                     ಶೂನ್ಯ             *cb_ದತ್ತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   ಪೂರ್ಣಾಂಕ                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   ಶೂನ್ಯ                *cb_ದತ್ತಾಂಶ);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       ಪೂರ್ಣಾಂಕ                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       ಶೂನ್ಯ                *cb_ದತ್ತಾಂಶ,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
ಶೂನ್ಯ             xsettings_client_ಗಣ_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
ಶೂನ್ಯ             xsettings_client_ಗಣ_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
ಶೂನ್ಯ             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ಸ್ಥಿರಾಂಕ XEvent        *xev);
XSettings_ಫಲಿತಾಂಶ  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ          *name,
                                                   XSettingsSetting   **setting);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ /* __cplusplus */

#ಆದರೆ_ಅಂತ್ಯ /* XSETTINGS_CLIENT_H */

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
வெளி "C" {
#endif /* __cplusplus */

வகைவரை கட்டமைப்பு _XSettingsBuffer  XSettingsBuffer;
வகைவரை கட்டமைப்பு _XSettingsColor   XSettingsColor;
வகைவரை கட்டமைப்பு _XSettingsList    XSettingsList;
வகைவரை கட்டமைப்பு _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
வகைவரை எண்ணிக்கை
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

வகைவரை எண்ணிக்கை
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

கட்டமைப்பு _XSettingsBuffer
{
  எழுத்து byte_order;
  size_t len;
  unsigned எழுத்து *data;
  unsigned எழுத்து *pos;
};

கட்டமைப்பு _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

கட்டமைப்பு _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

கட்டமைப்பு _XSettingsSetting
{
  எழுத்து *name;
  XSettingsType type;

  ஒன்றிப்பு {
    முழு v_int;
    எழுத்து *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
வெறுமை              xsettings_setting_free  (XSettingsSetting *setting);
முழு               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

வெறுமை              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_செருகு (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         மாறிலி எழுத்து        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         மாறிலி எழுத்து        *name);

எழுத்து xsettings_byte_order (வெறுமை);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

வகைவரை கட்டமைப்பு _XSettingsClient XSettingsClient;

வகைவரை எண்ணிக்கை
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

வகைவரை வெறுமை (*XSettingsNotifyFunc) (மாறிலி எழுத்து       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     வெறுமை             *cb_data);
வகைவரை Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     வெறுமை             *cb_data);
வகைவரை வெறுமை (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   முழு                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   வெறுமை                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       முழு                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       வெறுமை                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
வெறுமை             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
வெறுமை             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
வெறுமை             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   மாறிலி XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   மாறிலி எழுத்து          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

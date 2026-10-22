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
#నిర్వచితం_కాకపోతే XSETTINGS_CLIENT_H
#నిర్వచించు XSETTINGS_CLIENT_H

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు /* __cplusplus */

రకనిర్వచనం నిర్మాణం XSettings_బఫరు_2  XSettings_బఫరు;
రకనిర్వచనం నిర్మాణం _XSettingsColor   XSettingsColor;
రకనిర్వచనం నిర్మాణం _XSettingsList    XSettingsList;
రకనిర్వచనం నిర్మాణం _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
రకనిర్వచనం గణన
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

రకనిర్వచనం గణన
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_నమోదు,
  XSETTINGS_DUPLICATE_నమోదు
} XSettings_ఫలితం;

నిర్మాణం XSettings_బఫరు_2
{
  అక్షరం byte_క్రమం;
  size_t len;
  గుర్తులేని అక్షరం *దత్తాంశం;
  గుర్తులేని అక్షరం *pos;
};

నిర్మాణం _XSettingsColor
{
  గుర్తులేని పొట్టి red, green, blue, alpha;
};

నిర్మాణం _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *తదుపరి;
};

నిర్మాణం _XSettingsSetting
{
  అక్షరం *name;
  XSettingsType type;

  సంఘం {
    పూర్ణాంకం v_int;
    అక్షరం *v_string;
    XSettingsColor v_color;
  } దత్తాంశం;

  గుర్తులేని దీర్ఘ చివరి_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
శూన్య              xsettings_setting_free  (XSettingsSetting *setting);
పూర్ణాంకం               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

శూన్య              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettings_ఫలితం   xsettings_list_చొప్పించు (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         స్థిరరాశి అక్షరం        *name);
XSettings_ఫలితం   xsettings_list_delete (XSettingsList    **list,
                                         స్థిరరాశి అక్షరం        *name);

అక్షరం xsettings_byte_క్రమం (శూన్య);

#నిర్వచించు XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

రకనిర్వచనం నిర్మాణం _XSettingsClient XSettingsClient;

రకనిర్వచనం గణన
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_మారింది,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

రకనిర్వచనం శూన్య (*XSettingsNotifyFunc) (స్థిరరాశి అక్షరం       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     శూన్య             *cb_దత్తాంశం);
రకనిర్వచనం Bool (*XSettingsWatchFunc)  (కిటికీ_2            కిటికీ,
                                     Bool              is_ప్రారంభం,
                                     దీర్ఘ              ముసుగు,
                                     శూన్య             *cb_దత్తాంశం);
రకనిర్వచనం శూన్య (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   పూర్ణాంకం                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   శూన్య                *cb_దత్తాంశం);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       పూర్ణాంకం                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       శూన్య                *cb_దత్తాంశం,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
శూన్య             xsettings_client_సమితి_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
శూన్య             xsettings_client_సమితి_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
శూన్య             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   స్థిరరాశి XEvent        *xev);
XSettings_ఫలితం  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   స్థిరరాశి అక్షరం          *name,
                                                   XSettingsSetting   **setting);

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు /* __cplusplus */

#అయితే_ముగింపు /* XSETTINGS_CLIENT_H */

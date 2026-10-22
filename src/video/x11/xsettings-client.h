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
ବାହ୍ୟ "C" {
#endif /* __cplusplus */

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _XSettingsBuffer  XSettingsBuffer;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _XSettingsColor   XSettingsColor;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _XSettingsList    XSettingsList;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

ସଂରଚନା _XSettingsBuffer
{
  ଅକ୍ଷର byte_order;
  size_t len;
  unsigned ଅକ୍ଷର *data;
  unsigned ଅକ୍ଷର *pos;
};

ସଂରଚନା _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

ସଂରଚନା _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

ସଂରଚନା _XSettingsSetting
{
  ଅକ୍ଷର *name;
  XSettingsType type;

  ସଂଘ {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v_int;
    ଅକ୍ଷର *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
ଶୂନ୍ୟ              xsettings_setting_free  (XSettingsSetting *setting);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

ଶୂନ୍ୟ              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_ଭର୍ତ୍ତି (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         ଅଚଳ ଅକ୍ଷର        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         ଅଚଳ ଅକ୍ଷର        *name);

ଅକ୍ଷର xsettings_byte_order (ଶୂନ୍ୟ);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା _XSettingsClient XSettingsClient;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*XSettingsNotifyFunc) (ଅଚଳ ଅକ୍ଷର       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     ଶୂନ୍ୟ             *cb_data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     ଶୂନ୍ୟ             *cb_data);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   ପୂର୍ଣ୍ଣସଂଖ୍ୟା                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   ଶୂନ୍ୟ                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       ପୂର୍ଣ୍ଣସଂଖ୍ୟା                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       ଶୂନ୍ୟ                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
ଶୂନ୍ୟ             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
ଶୂନ୍ୟ             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
ଶୂନ୍ୟ             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   ଅଚଳ XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   ଅଚଳ ଅକ୍ଷର          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

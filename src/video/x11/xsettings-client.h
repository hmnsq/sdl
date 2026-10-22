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
extern "C" {
#endif /* __cplusplus */

typedef sa_nracanaa _XSettingsBuffer  XSettingsBuffer;
typedef sa_nracanaa _XSettingsColor   XSettingsColor;
typedef sa_nracanaa _XSettingsList    XSettingsList;
typedef sa_nracanaa _XSettingsSetting XSettingsSetting;

/* Types of settings possible. Enum values correspond to
 * protocol values.
 */
typedef ga_nanaa
{
  XSETTINGS_TYPE_INT     = 0,
  XSETTINGS_TYPE_STRING  = 1,
  XSETTINGS_TYPE_COLOR   = 2
} XSettingsType;

typedef ga_nanaa
{
  XSETTINGS_SUCCESS,
  XSETTINGS_NO_MEM,
  XSETTINGS_ACCESS,
  XSETTINGS_FAILED,
  XSETTINGS_NO_ENTRY,
  XSETTINGS_DUPLICATE_ENTRY
} XSettingsResult;

sa_nracanaa _XSettingsBuffer
{
  var_na byte_order;
  size_t len;
  unsigned var_na *data;
  unsigned var_na *pos;
};

sa_nracanaa _XSettingsColor
{
  unsigned short red, green, blue, alpha;
};

sa_nracanaa _XSettingsList
{
  XSettingsSetting *setting;
  XSettingsList *next;
};

sa_nracanaa _XSettingsSetting
{
  var_na *name;
  XSettingsType type;

  sa_ngha {
    ຈຳນວນເຕັມ v_int;
    var_na *v_string;
    XSettingsColor v_color;
  } data;

  unsigned long last_change_serial;
};

XSettingsSetting *xsettings_setting_copy  (XSettingsSetting *setting);
void              xsettings_setting_free  (XSettingsSetting *setting);
ຈຳນວນເຕັມ               xsettings_setting_equal (XSettingsSetting *setting_a,
                                           XSettingsSetting *setting_b);

void              xsettings_list_free   (XSettingsList     *list);
XSettingsList    *xsettings_list_copy   (XSettingsList     *list);
XSettingsResult   xsettings_list_insert (XSettingsList    **list,
                                         XSettingsSetting  *setting);
XSettingsSetting *xsettings_list_lookup (XSettingsList     *list,
                                         const var_na        *name);
XSettingsResult   xsettings_list_delete (XSettingsList    **list,
                                         const var_na        *name);

var_na xsettings_byte_order (void);

#define XSETTINGS_PAD(n,m) ((n + m - 1) & (~(m-1)))

typedef sa_nracanaa _XSettingsClient XSettingsClient;

typedef ga_nanaa
{
  XSETTINGS_ACTION_NEW,
  XSETTINGS_ACTION_CHANGED,
  XSETTINGS_ACTION_DELETED
} XSettingsAction;

typedef void (*XSettingsNotifyFunc) (const var_na       *name,
                                     XSettingsAction   action,
                                     XSettingsSetting *setting,
                                     void             *cb_data);
typedef Bool (*XSettingsWatchFunc)  (Window            window,
                                     Bool              is_start,
                                     long              mask,
                                     void             *cb_data);
typedef void (*XSettingsGrabFunc)   (Display          *display);

XSettingsClient *xsettings_client_new             (Display             *display,
                                                   ຈຳນວນເຕັມ                  screen,
                                                   XSettingsNotifyFunc  notify,
                                                   XSettingsWatchFunc   watch,
                                                   void                *cb_data);
XSettingsClient *xsettings_client_new_with_grab_funcs (Display             *display,
                                                       ຈຳນວນເຕັມ                  screen,
                                                       XSettingsNotifyFunc  notify,
                                                       XSettingsWatchFunc   watch,
                                                       void                *cb_data,
                                                       XSettingsGrabFunc    grab,
                                                       XSettingsGrabFunc    ungrab);
void             xsettings_client_set_grab_func   (XSettingsClient     *client,
                                                   XSettingsGrabFunc    grab);
void             xsettings_client_set_ungrab_func (XSettingsClient     *client,
                                                   XSettingsGrabFunc    ungrab);
void             xsettings_client_destroy         (XSettingsClient     *client);
Bool             xsettings_client_process_event   (XSettingsClient     *client,
                                                   const XEvent        *xev);
XSettingsResult  xsettings_client_get_setting     (XSettingsClient     *client,
                                                   const var_na          *name,
                                                   XSettingsSetting   **setting);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XSETTINGS_CLIENT_H */

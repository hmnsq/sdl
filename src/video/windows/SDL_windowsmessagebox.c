/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شدہ HAVE_LIMITS_H
#شامل <limits.h>
#اگر_ختم
#اگر_غیر_تعریف_شدہ SIZE_MAX
#تعریف_کرو SIZE_MAX ((size_t)-1)
#اگر_ختم

#شامل "../../core/windows/SDL_windows.h"

#شامل "SDL_windowsvideo.h"

#اگر_غیر_تعریف_شدہ SS_EDITCONTROL
#تعریف_کرو SS_EDITCONTROL 0x2000
#اگر_ختم

#اگر_غیر_تعریف_شدہ IDOK
#تعریف_کرو IDOK 1
#اگر_ختم

#اگر_غیر_تعریف_شدہ IDCANCEL
#تعریف_کرو IDCANCEL 2
#اگر_ختم

// Custom dialog return codes
#تعریف_کرو IDCLOSED           20
#تعریف_کرو IDINVALPTRINIT     50
#تعریف_کرو IDINVALPTRCOMMAND  51
#تعریف_کرو IDINVALPTRSETFOCUS 52
#تعریف_کرو IDINVALPTRDLGITEM  53
// First button ID
#تعریف_کرو IDBUTTONINDEX0 100

#تعریف_کرو DLGITEMTYPEBUTTON 0x0080
#تعریف_کرو DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#تعریف_کرو MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

قسمتعریف HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT پیغام_2, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_ڈیٹا);

شمار _TASKDIALOG_FLAGS
{
    TDF_ENABLE_HYPERLINKS = 0x0001,
    TDF_USE_HICON_MAIN = 0x0002,
    TDF_USE_HICON_FOOTER = 0x0004,
    TDF_ALLOW_DIALOG_CANCELLATION = 0x0008,
    TDF_USE_COMMAND_LINKS = 0x0010,
    TDF_USE_COMMAND_LINKS_NO_ICON = 0x0020,
    TDF_EXPAND_FOOTER_AREA = 0x0040,
    TDF_EXPANDED_BY_DEFAULT = 0x0080,
    TDF_VERIFICATION_FLAG_CHECKED = 0x0100,
    TDF_SHOW_پیش_رفت_BAR = 0x0200,
    TDF_SHOW_MARQUEE_پیش_رفت_BAR = 0x0400,
    TDF_CALLBACK_TIMER = 0x0800,
    TDF_POSITION_RELATIVE_مقصد_کھڑکی = 0x1000,
    TDF_RTL_LAYOUT = 0x2000,
    TDF_NO_DEFAULT_RADIO_BUTTON = 0x4000,
    TDF_CAN_BE_MINIMIZED = 0x8000,
    // #if (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_NO_سیٹ_FOREGROUND = 0x00010000, // Don't call SetForegroundWindow() when activating the dialog
                                        // #endif // (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_سائز_مقصد_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
قسمتعریف صحیح TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

قسمتعریف شمار _TASKDIALOG_MESSAGES
{
    TDM_NAVIGATE_صفحہ = WM_USER + 101,
    TDM_CLICK_BUTTON = WM_USER + 102,                        // wParam = Button ID
    TDM_سیٹ_MARQUEE_پیش_رفت_BAR = WM_USER + 103,            // wParam = 0 (nonMarque) wParam != 0 (Marquee)
    TDM_سیٹ_پیش_رفت_BAR_STATE = WM_USER + 104,              // wParam = new progress state
    TDM_سیٹ_پیش_رفت_BAR_RANGE = WM_USER + 105,              // lParam = MAKELPARAM(nMinRange, nMaxRange)
    TDM_سیٹ_پیش_رفت_BAR_POS = WM_USER + 106,                // wParam = new position
    TDM_سیٹ_پیش_رفت_BAR_MARQUEE = WM_USER + 107,            // wParam = 0 (stop marquee), wParam != 0 (start marquee), lparam = speed (milliseconds between repaints)
    TDM_سیٹ_ELEMENT_متن = WM_USER + 108,                    // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_CLICK_RADIO_BUTTON = WM_USER + 110,                  // wParam = Radio Button ID
    TDM_ENABLE_BUTTON = WM_USER + 111,                       // lParam = 0 (disable), lParam != 0 (enable), wParam = Button ID
    TDM_ENABLE_RADIO_BUTTON = WM_USER + 112,                 // lParam = 0 (disable), lParam != 0 (enable), wParam = Radio Button ID
    TDM_CLICK_VERIFICATION = WM_USER + 113,                  // wParam = 0 (unchecked), 1 (checked), lParam = 1 (set key focus)
    TDM_UPDATE_ELEMENT_متن = WM_USER + 114,                 // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_سیٹ_BUTTON_ELEVATION_REQUIRED_STATE = WM_USER + 115, // wParam = Button ID, lParam = 0 (elevation not required), lParam != 0 (elevation required)
    TDM_UPDATE_ICON = WM_USER + 116                          // wParam = icon element (TASKDIALOG_ICON_ELEMENTS), lParam = new icon (hIcon if TDF_USE_HICON_* was set, PCWSTR otherwise)
} TASKDIALOG_MESSAGES;

قسمتعریف شمار _TASKDIALOG_NOTIFICATIONS
{
    TDN_CREATED = 0,
    TDN_NAVIGATED = 1,
    TDN_BUTTON_CLICKED = 2,    // wParam = Button ID
    TDN_HYPERLINK_CLICKED = 3, // lParam = (LPCWSTR)pszHREF
    TDN_TIMER = 4,             // wParam = Milliseconds since dialog created or timer reset
    TDN_DESTROYED = 5,
    TDN_RADIO_BUTTON_CLICKED = 6, // wParam = Radio Button ID
    TDN_DIALOG_CONSTRUCTED = 7,
    TDN_VERIFICATION_CLICKED = 8, // wParam = 1 if checkbox checked, 0 if not, lParam is unused and always 0
    TDN_HELP = 9,
    TDN_EXPANDO_BUTTON_CLICKED = 10 // wParam = 0 (dialog is now collapsed), wParam != 0 (dialog is now expanded)
} TASKDIALOG_NOTIFICATIONS;

قسمتعریف شمار _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

قسمتعریف شمار _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#تعریف_کرو TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#تعریف_کرو TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#تعریف_کرو TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#تعریف_کرو TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

شمار _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
قسمتعریف صحیح TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#ہدایت pack(ڈالو, 1)

قسمتعریف ساخت _TASKDIALOG_BUTTON
{
    صحیح nButtonID;
    PCWSTR psz_Button_متن;
} TASKDIALOG_BUTTON;

قسمتعریف ساخت _TASKDIALOGCONFIG
{
    UINT cb_سائز;
    HWND hwnd_والد;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR psz_کھڑکی_Title;                          // string or MAKEINTRESOURCE()
    اتحاد
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    ثابت TASKDIALOG_BUTTON *pButtons;
    صحیح nDefaultButton;
    UINT cRadioButtons;
    ثابت TASKDIALOG_BUTTON *pRadioButtons;
    صحیح nDefaultRadioButton;
    PCWSTR psz_Verification_متن;
    PCWSTR pszExpandedInformation;
    PCWSTR psz_Expanded_Control_متن;
    PCWSTR psz_Collapsed_Control_متن;
    اتحاد
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lp_Callback_ڈیٹا;
    UINT cx_چوڑائی; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

قسمتعریف ساخت
{
    لفظ dlgVer;
    لفظ signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    لفظ c_Dlg_اشیاء;
    مختصر x;
    مختصر y;
    مختصر cx;
    مختصر cy;
} DLGTEMPLATEEX;

قسمتعریف ساخت
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    مختصر x;
    مختصر y;
    مختصر cx;
    مختصر cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#ہدایت pack(نکالو)

قسمتعریف ساخت
{
    DLGTEMPLATEEX *lpDialog;
    خالی *ڈیٹا;
    size_t سائز;
    size_t مستعمل;
    لفظ numbuttons;
} WIN_Dialog_ڈیٹا;

ساکن bool Get_Button_اشاریہ(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, SDL_پیغام_Box_Button_Flags flags, size_t *i)
{
    برائے (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        اگر (messageboxdata->buttons[*i].flags & flags) {
            واپس true;
        }
    }
    واپس false;
}

ساکن INT_PTR CALLBACK پیغام_Box_Dialog_Proc(HWND hDlg, UINT i_پیغام, WPARAM wParam, LPARAM lParam)
{
    ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata;
    size_t buttonindex;

    انتخاب (i_پیغام) {
    حالت WM_INITDIALOG:
        اگر (lParam == 0) {
            انتہا_Dialog(hDlg, IDINVALPTRINIT);
            واپس TRUE;
        }
        messageboxdata = (ثابت SDL_پیغام_Box_ڈیٹا *)lParam;
        سیٹ_کھڑکی_Long_Ptr(hDlg, GWLP_USERDATA, lParam);

        اگر (Get_Button_اشاریہ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = Get_Dlg_شے(hDlg, (صحیح)(IDBUTTONINDEX0 + buttonindex));
            اگر (!buttonctl) {
                انتہا_Dialog(hDlg, IDINVALPTRDLGITEM);
            }
            Post_پیغام(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } ورنہ {
            // Give the focus to the dialog window instead
            سیٹ_Focus(hDlg);
        }
        واپس FALSE;
    حالت WM_SETFOCUS:
        messageboxdata = (ثابت SDL_پیغام_Box_ڈیٹا *)Get_کھڑکی_Long_Ptr(hDlg, GWLP_USERDATA);
        اگر (!messageboxdata) {
            انتہا_Dialog(hDlg, IDINVALPTRSETFOCUS);
            واپس TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        اگر (Get_Button_اشاریہ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            واپس FALSE;
        }
        واپس TRUE;
    حالت WM_COMMAND:
        messageboxdata = (ثابت SDL_پیغام_Box_ڈیٹا *)Get_کھڑکی_Long_Ptr(hDlg, GWLP_USERDATA);
        اگر (!messageboxdata) {
            انتہا_Dialog(hDlg, IDINVALPTRCOMMAND);
            واپس TRUE;
        }

        // Return the ID of the button that was pushed
        اگر (wParam == IDOK) {
            اگر (Get_Button_اشاریہ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                انتہا_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } ورنہ اگر (wParam == IDCANCEL) {
            اگر (Get_Button_اشاریہ(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                انتہا_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } ورنہ {
                // Closing of window was requested by user or system. It would be rude not to comply.
                انتہا_Dialog(hDlg, IDCLOSED);
            }
        } ورنہ اگر (wParam >= IDBUTTONINDEX0 && (صحیح)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            انتہا_Dialog(hDlg, wParam);
        }
        واپس TRUE;

    طےشدہ:
        توڑو;
    }
    واپس FALSE;
}

ساکن bool ExpandDialogSpace(WIN_Dialog_ڈیٹا *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    ثابت size_t sizestep = 0x10000;
    size_t سائز = dialog->سائز;

    اگر (سائز == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        سائز = 0x1000;
        اگر (SIZE_MAX - sizestep < space) {
            سائز = space;
        } ورنہ اگر (space > سائز) {
            سائز = (space + sizestep) & ~(sizestep - 1);
        }
    } ورنہ اگر (SIZE_MAX - dialog->مستعمل < space) {
        SDL_برآمد_کا_حافظہ();
        واپس false;
    } ورنہ اگر (SIZE_MAX - (dialog->مستعمل + space) < sizestep) {
        // Close to the maximum.
        سائز = dialog->مستعمل + space;
    } ورنہ اگر (سائز < dialog->مستعمل + space) {
        // Round up to the next 64 KiB block.
        سائز = dialog->مستعمل + space;
        سائز += sizestep - سائز % sizestep;
    }

    اگر (سائز > dialog->سائز) {
        خالی *ڈیٹا = SDL_realloc(dialog->ڈیٹا, سائز);
        اگر (!ڈیٹا) {
            واپس false;
        }
        dialog->ڈیٹا = ڈیٹا;
        dialog->سائز = سائز;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->ڈیٹا;
    }
    واپس true;
}

ساکن bool Align_Dialog_ڈیٹا(WIN_Dialog_ڈیٹا *dialog, size_t سائز)
{
    size_t padding = (dialog->مستعمل % سائز);

    اگر (!ExpandDialogSpace(dialog, padding)) {
        واپس false;
    }

    dialog->مستعمل += padding;

    واپس true;
}

ساکن bool جوڑو_Dialog_ڈیٹا(WIN_Dialog_ڈیٹا *dialog, ثابت خالی *ڈیٹا, size_t سائز)
{
    اگر (!ExpandDialogSpace(dialog, سائز)) {
        واپس false;
    }

    SDL_memcpy((Uint8 *)dialog->ڈیٹا + dialog->مستعمل, ڈیٹا, سائز);
    dialog->مستعمل += سائز;

    واپس true;
}

ساکن bool جوڑو_Dialog_String(WIN_Dialog_ڈیٹا *dialog, ثابت حرف *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t گنتی;
    bool حالت_2;

    اگر (!string) {
        string = "";
    }

    wstring = WIN_UTF8_مقصد_String_W(string);
    اگر (!wstring) {
        واپس false;
    }

    // Find out how many characters we have, including null terminator
    گنتی = 0;
    برائے (p = wstring; *p; ++p) {
        ++گنتی;
    }
    ++گنتی;

    حالت_2 = جوڑو_Dialog_ڈیٹا(dialog, wstring, گنتی * حجم(WCHAR));
    SDL_free(wstring);
    واپس حالت_2;
}

ساکن صحیح s_بنیاد_Units_X;
ساکن صحیح s_بنیاد_Units_Y;
ساکن خالی Vec2_مقصد_DLU(مختصر *x, مختصر *y)
{
    SDL_assert(s_بنیاد_Units_X != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (مختصر)MulDiv(*x, 4, s_بنیاد_Units_X);
    *y = (مختصر)MulDiv(*y, 8, s_بنیاد_Units_Y);
}

ساکن bool جوڑو_Dialog_Control(WIN_Dialog_ڈیٹا *dialog, لفظ type, DWORD style, DWORD exStyle, صحیح x, صحیح y, صحیح w, صحیح h, صحیح id, ثابت حرف *caption, لفظ ordinal)
{
    DLGITEMTEMPLATEEX شے;
    لفظ marker = 0xFFFF;
    لفظ extra_ڈیٹا = 0;

    SDL_zero(شے);
    شے.style = style;
    شے.exStyle = exStyle;
    شے.x = (مختصر)x;
    شے.y = (مختصر)y;
    شے.cx = (مختصر)w;
    شے.cy = (مختصر)h;
    شے.id = id;

    Vec2_مقصد_DLU(&شے.x, &شے.y);
    Vec2_مقصد_DLU(&شے.cx, &شے.cy);

    اگر (!Align_Dialog_ڈیٹا(dialog, حجم(DWORD))) {
        واپس false;
    }
    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &شے, حجم(شے))) {
        واپس false;
    }
    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &marker, حجم(marker))) {
        واپس false;
    }
    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &type, حجم(type))) {
        واپس false;
    }
    اگر (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        اگر (!جوڑو_Dialog_String(dialog, caption)) {
            واپس false;
        }
    } ورنہ {
        اگر (!جوڑو_Dialog_ڈیٹا(dialog, &marker, حجم(marker))) {
            واپس false;
        }
        اگر (!جوڑو_Dialog_ڈیٹا(dialog, &ordinal, حجم(ordinal))) {
            واپس false;
        }
    }
    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &extra_ڈیٹا, حجم(extra_ڈیٹا))) {
        واپس false;
    }
    اگر (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_اشیاء;

    واپس true;
}

ساکن bool جوڑو_Dialog_Static_متن(WIN_Dialog_ڈیٹا *dialog, صحیح x, صحیح y, صحیح w, صحیح h, ثابت حرف *متن)
{
    DWORD style = WS_VISIBLE | WS_بچہ | SS_بایاں | SS_NOPREFIX | SS_EDITCONTROL | WS_گروہ;
    واپس جوڑو_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, متن, 0);
}

ساکن bool جوڑو_Dialog_Static_Icon(WIN_Dialog_ڈیٹا *dialog, صحیح x, صحیح y, صحیح w, صحیح h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_بچہ | SS_ICON | WS_گروہ;
    واپس جوڑو_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, تہی, ordinal);
}

ساکن bool جوڑو_Dialog_Button(WIN_Dialog_ڈیٹا *dialog, صحیح x, صحیح y, صحیح w, صحیح h, ثابت حرف *متن, صحیح id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_بچہ | WS_TABSTOP;
    اگر (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } ورنہ {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    اگر (dialog->numbuttons == 0) {
        style |= WS_گروہ;
    }
    واپس جوڑو_Dialog_Control(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, متن, 0);
}

ساکن خالی Free_Dialog_ڈیٹا(WIN_Dialog_ڈیٹا *dialog)
{
    SDL_free(dialog->ڈیٹا);
    SDL_free(dialog);
}

ساکن WIN_Dialog_ڈیٹا *Create_Dialog_ڈیٹا(صحیح w, صحیح h, ثابت حرف *caption)
{
    WIN_Dialog_ڈیٹا *dialog;
    DLGTEMPLATEEX dialogTemplate;
    لفظ لفظ_مقصد_Pass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (مختصر)w;
    dialogTemplate.cy = (مختصر)h;
    Vec2_مقصد_DLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_ڈیٹا *)SDL_calloc(1, حجم(*dialog));
    اگر (!dialog) {
        واپس تہی;
    }

    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &dialogTemplate, حجم(dialogTemplate))) {
        Free_Dialog_ڈیٹا(dialog);
        واپس تہی;
    }

    // No menu
    لفظ_مقصد_Pass = 0;
    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &لفظ_مقصد_Pass, 2)) {
        Free_Dialog_ڈیٹا(dialog);
        واپس تہی;
    }

    // No custom class
    اگر (!جوڑو_Dialog_ڈیٹا(dialog, &لفظ_مقصد_Pass, 2)) {
        Free_Dialog_ڈیٹا(dialog);
        واپس تہی;
    }

    // title
    اگر (!جوڑو_Dialog_String(dialog, caption)) {
        Free_Dialog_ڈیٹا(dialog);
        واپس تہی;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE مقصد_Pass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_سائز = حجم(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(تہی);
            صحیح LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            اگر (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            لفظ_مقصد_Pass = (لفظ)(-72 * NCM.lf_پیغام_Font.lf_اونچائی / LogicalPixelsY);
            ReleaseDC(تہی, ScreenDC);
        }

        اگر (!جوڑو_Dialog_ڈیٹا(dialog, &لفظ_مقصد_Pass, 2)) {
            Free_Dialog_ڈیٹا(dialog);
            واپس تہی;
        }

        // Font weight
        لفظ_مقصد_Pass = (لفظ)NCM.lf_پیغام_Font.lf_وزن;
        اگر (!جوڑو_Dialog_ڈیٹا(dialog, &لفظ_مقصد_Pass, 2)) {
            Free_Dialog_ڈیٹا(dialog);
            واپس تہی;
        }

        // italic?
        مقصد_Pass = NCM.lf_پیغام_Font.lfItalic;
        اگر (!جوڑو_Dialog_ڈیٹا(dialog, &مقصد_Pass, 1)) {
            Free_Dialog_ڈیٹا(dialog);
            واپس تہی;
        }

        // charset?
        مقصد_Pass = NCM.lf_پیغام_Font.lf_Char_سیٹ;
        اگر (!جوڑو_Dialog_ڈیٹا(dialog, &مقصد_Pass, 1)) {
            Free_Dialog_ڈیٹا(dialog);
            واپس تہی;
        }

        // font typeface.
        اگر (!جوڑو_Dialog_String(dialog, NCM.lf_پیغام_Font.lfFaceName)) {
            Free_Dialog_ڈیٹا(dialog);
            واپس تہی;
        }
    }

    واپس dialog;
}

/* Escaping ampersands is necessary to disable mnemonics in dialog controls.
 * The caller provides a char** for dst and a size_t* for dstlen where the
 * address of the work buffer and its size will be stored. Their values must be
 * NULL and 0 on the first call. src is the string to be escaped. On error, the
 * function returns NULL and, on success, returns a pointer to the escaped
 * sequence as a read-only string that is valid until the next call or until the
 * work buffer is freed. Once all strings have been processed, it's the caller's
 * responsibility to free the work buffer with SDL_free, even on errors.
 */
ساکن ثابت حرف *EscapeAmpersands(حرف **dst, size_t *dstlen, ثابت حرف *src)
{
    حرف *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    اگر (!src) {
        واپس تہی;
    }

    جب (src[srclen]) {
        اگر (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    اگر (ampcount == 0) {
        // Nothing to do.
        واپس src;
    }
    اگر (SIZE_MAX - srclen < ampcount) {
        واپس تہی;
    }
    اگر (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        اگر (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = تہی;
        newdst = (حرف *)SDL_malloc(*dstlen);
        اگر (!newdst) {
            واپس تہی;
        }
        *dst = newdst;
    } ورنہ {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    جب (srclen--) {
        اگر (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    واپس *dst;
}

ساکن اعشاری WIN_GetContentScale(خالی)
{
    صحیح dpi = 0;

#اگر 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    اگر (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (صحیح)hdpi_uint;
    }
#اگر_ختم
    اگر (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(تہی);
        اگر (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(تہی, hdc);
        }
    }
    اگر (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    واپس dpi / (اعشاری)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
ساکن bool WIN_Show_Old_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
    WIN_Dialog_ڈیٹا *dialog;
    صحیح i, x, y;
    HFONT DialogFont;
    سائز_3 سائز_2;
    RECT متن_سائز;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    حرف *ampescape = تہی;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool نتیجہ;

    HWND والد_کھڑکی_2 = تہی;

    ثابت اعشاری scale = WIN_GetContentScale();
    ثابت صحیح Button_چوڑائی = (صحیح)SDL_roundf(88 * scale);
    ثابت صحیح Button_اونچائی = (صحیح)SDL_roundf(26 * scale);
    ثابت صحیح متن_Margin = (صحیح)SDL_roundf(16 * scale);
    ثابت صحیح ButtonMargin = (صحیح)SDL_roundf(12 * scale);
    ثابت صحیح Icon_چوڑائی = GetSystemMetrics(SM_CXICON);
    ثابت صحیح Icon_اونچائی = GetSystemMetrics(SM_CYICON);
    ثابت صحیح IconMargin = (صحیح)SDL_roundf(20 * scale);

    اگر (messageboxdata->numbuttons > MAX_BUTTONS) {
        واپس SDL_سیٹ_Error("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    انتخاب (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    حالت SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        توڑو;
    حالت SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        توڑو;
    حالت SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        توڑو;
    }

    /* Jan 25th, 2013 - dant@fleetsa.com
     *
     * I've tried to make this more reasonable, but I've run in to a lot
     * of nonsense.
     *
     * The original issue is the code was written in pixels and not
     * dialog units (DLUs). All DialogBox functions use DLUs, which
     * vary based on the selected font (yay).
     *
     * According to MSDN, the most reliable way to convert is via
     * MapDialogUnits, which requires an HWND, which we don't have
     * at time of template creation.
     *
     * We do however have:
     *  The system font (DLU width 8 for me)
     *  The font we select for the dialog (DLU width 6 for me)
     *
     * Based on experimentation, *neither* of these return the value
     * actually used. Stepping in to MapDialogUnits(), the conversion
     * is fairly clear, and uses 7 for me.
     *
     * As a result, some of this is hacky to ensure the sizing is
     * somewhat correct.
     *
     * Honestly, a long term solution is to use CreateWindow, not CreateDialog.
     *
     * In order to get text dimensions we need to have a DC with the desired font.
     * I'm assuming a dialog box in SDL is rare enough we can to the create.
     */
    FontDC = CreateCompatibleDC(0);

    {
        // Create a duplicate of the font used in system message boxes.
        LOGFONT lf;
        NONCLIENTMETRICS NCM;
        NCM.cb_سائز = حجم(NCM);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);
        lf = NCM.lf_پیغام_Font;
        DialogFont = Create_Font_بالواسطہ(&lf);
    }

    // Select the font in to our DC
    SelectObject(FontDC, DialogFont);

    {
        // Get the metrics to try and figure our DLU conversion.
        Get_متن_Metrics(FontDC, &TM);

        /* Calculation from the following documentation:
         * https://support.microsoft.com/en-gb/help/125681/how-to-calculate-dialog-base-units-with-non-system-based-font
         * This fixes bug 2137, dialog box calculation with a fixed-width system font
         */
        {
            سائز_3 extent;
            Get_متن_Extent_Point32_A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_بنیاد_Units_X = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_بنیاد_Units_Y = TM.tm_اونچائی;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8_مقصد_String_W(messageboxdata->پیغام);
    SDL_zero(متن_سائز);
    Draw_متن_W(FontDC, wmessage, -1, &متن_سائز, DT_CALCRECT | DT_بایاں | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    متن_سائز.بایاں += متن_Margin;
    متن_سائز.دایاں += متن_Margin + 2;
    متن_سائز.چوٹی += متن_Margin;
    متن_سائز.bottom += متن_Margin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    سائز_2.cx = متن_سائز.دایاں - متن_سائز.بایاں;
    سائز_2.cy = متن_سائز.bottom - متن_سائز.چوٹی;
    سائز_2.cx += متن_Margin * 2;
    سائز_2.cy += متن_Margin * 2;

    // Make dialog wider and shift text over for the icon.
    اگر (icon) {
        سائز_2.cx += IconMargin + Icon_چوڑائی;
        متن_سائز.بایاں += IconMargin + Icon_چوڑائی;
        متن_سائز.دایاں += IconMargin + Icon_چوڑائی;
    }

    // Ensure the size is wide enough for all of the buttons.
    اگر (سائز_2.cx < (LONG)messageboxdata->numbuttons * (Button_چوڑائی + ButtonMargin) + ButtonMargin) {
        سائز_2.cx = (LONG)messageboxdata->numbuttons * (Button_چوڑائی + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    اگر (icon && سائز_2.cy < (LONG)IconMargin * 2 + Icon_اونچائی) {
        سائز_2.cy = (LONG)IconMargin * 2 + Icon_اونچائی;
    }

    // Add vertical space for the buttons and border.
    سائز_2.cy += Button_اونچائی + متن_Margin;

    dialog = Create_Dialog_ڈیٹا(سائز_2.cx, سائز_2.cy, messageboxdata->title);
    اگر (!dialog) {
        واپس false;
    }

    اگر (icon && !جوڑو_Dialog_Static_Icon(dialog, IconMargin, IconMargin, Icon_چوڑائی, Icon_اونچائی, icon)) {
        Free_Dialog_ڈیٹا(dialog);
        واپس false;
    }

    اگر (!جوڑو_Dialog_Static_متن(dialog, متن_سائز.بایاں, متن_سائز.چوٹی, متن_سائز.دایاں - متن_سائز.بایاں, متن_سائز.bottom - متن_سائز.چوٹی, messageboxdata->پیغام)) {
        Free_Dialog_ڈیٹا(dialog);
        واپس false;
    }

    // Align the buttons to the right/bottom.
    x = سائز_2.cx - (Button_چوڑائی + ButtonMargin) * messageboxdata->numbuttons;
    y = سائز_2.cy - Button_اونچائی - ButtonMargin;
    برائے (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        ثابت حرف *buttontext;
        ثابت SDL_پیغام_Box_Button_ڈیٹا *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        اگر (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_بایاں_مقصد_دایاں) {
            sdlButton = &messageboxdata->buttons[i];
        } ورنہ {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        اگر (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            اگر (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->متن);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        اگر (!buttontext || !جوڑو_Dialog_Button(dialog, x, y, Button_چوڑائی, Button_اونچائی, buttontext, IDBUTTONINDEX0 + (صحیح)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_ڈیٹا(dialog);
            SDL_free(ampescape);
            واپس false;
        }

        x += Button_چوڑائی + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    اگر (messageboxdata->کھڑکی) {
        والد_کھڑکی_2 = messageboxdata->کھڑکی->اندرونی_2->hwnd;
    }

    rc = Dialog_Box_بالواسطہ_Param(تہی, (DLGTEMPLATE *)dialog->lpDialog, والد_کھڑکی_2, پیغام_Box_Dialog_Proc, (LPARAM)messageboxdata);
    اگر (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        نتیجہ = true;
    } ورنہ اگر (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        نتیجہ = true;
        *buttonID = -1;
    } ورنہ {
        اگر (rc == 0) {
            SDL_سیٹ_Error("Invalid parent window handle");
        } ورنہ اگر (rc == -1) {
            SDL_سیٹ_Error("The message box encountered an error.");
        } ورنہ اگر (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_سیٹ_Error("Invalid message box pointer in dialog procedure");
        } ورنہ اگر (rc == IDINVALPTRDLGITEM) {
            SDL_سیٹ_Error("Couldn't find dialog control of the default enter-key button");
        } ورنہ {
            SDL_سیٹ_Error("An unknown error occurred");
        }
        نتیجہ = false;
    }

    Free_Dialog_ڈیٹا(dialog);
    واپس نتیجہ;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
قسمتعریف HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(ثابت TASKDIALOGCONFIG *pTaskConfig, صحیح *pnButton, صحیح *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
    HWND والد_کھڑکی_2 = تہی;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC p_Task_Dialog_بالواسطہ;
    HRESULT hr;
    حرف *ampescape = تہی;
    size_t ampescapesize = 0;
    صحیح nButton;
    صحیح nCancelButton;
    صحیح i;
    bool نتیجہ = false;

    اگر (SIZE_MAX / حجم(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        واپس SDL_برآمد_کا_حافظہ();
    }

    HMODULE hUser32 = GetModuleHandle(متن_2("user32.dll"));
    قسمتعریف DPI_AWARENESS_CONTEXT (WINAPI *pfn_سیٹ_Thread_Dpi_Awareness_Context)(DPI_AWARENESS_CONTEXT);
    pfn_سیٹ_Thread_Dpi_Awareness_Context p_سیٹ_Thread_Dpi_Awareness_Context = (pfn_سیٹ_Thread_Dpi_Awareness_Context)Get_Proc_پتہ(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT پچھلا_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    اگر (p_سیٹ_Thread_Dpi_Awareness_Context) {
        پچھلا_context = p_سیٹ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_فی_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = بھرو_Library(متن_2("comctl32.dll"));
    اگر (!hComctl32) {
        نتیجہ = WIN_Show_Old_پیغام_Box(messageboxdata, buttonID);
        جاؤ مکمل;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    p_Task_Dialog_بالواسطہ = (TASKDIALOGINDIRECTPROC)Get_Proc_پتہ(hComctl32, "TaskDialogIndirect");
    اگر (!p_Task_Dialog_بالواسطہ) {
        FreeLibrary(hComctl32);
        نتیجہ = WIN_Show_Old_پیغام_Box(messageboxdata, buttonID);
        جاؤ مکمل;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    اگر (messageboxdata->کھڑکی) {
        والد_کھڑکی_2 = messageboxdata->کھڑکی->اندرونی_2->hwnd;
    }

    wmessage = WIN_UTF8_مقصد_String_W(messageboxdata->پیغام);
    wtitle = WIN_UTF8_مقصد_String_W(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_سائز = حجم(TASKDIALOGCONFIG);
    TaskConfig.hwnd_والد = والد_کھڑکی_2;
    TaskConfig.dwFlags = TDF_سائز_مقصد_CONTENT;
    TaskConfig.psz_کھڑکی_Title = wtitle;
    اگر (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } ورنہ اگر (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } ورنہ اگر (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } ورنہ {
        TaskConfig.pszMainIcon = تہی;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(حجم(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    برائے (i = 0; i < messageboxdata->numbuttons; i++) {
        ثابت حرف *buttontext;
        اگر (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_بایاں_مقصد_دایاں) {
            pButton = &pButtons[i];
        } ورنہ {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        اگر (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } ورنہ {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].متن);
        اگر (!buttontext) {
            صحیح j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            برائے (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].psz_Button_متن);
            }
            SDL_free(pButtons);
            واپس false;
        }
        pButton->psz_Button_متن = WIN_UTF8_مقصد_String_W(buttontext);
        اگر (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = p_Task_Dialog_بالواسطہ(&TaskConfig, &nButton, تہی, تہی);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    برائے (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].psz_Button_متن);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    اگر (SUCCEEDED(hr)) {
        اگر (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } ورنہ اگر (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } ورنہ {
            *buttonID = -1;
        }
        نتیجہ = true;
    } ورنہ {
        // We failed showing the Task Dialog, use the old message box!
        نتیجہ = WIN_Show_Old_پیغام_Box(messageboxdata, buttonID);
    }

مکمل:
    اگر (p_سیٹ_Thread_Dpi_Awareness_Context) {
        p_سیٹ_Thread_Dpi_Awareness_Context(پچھلا_context);
    }
    واپس نتیجہ;
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS

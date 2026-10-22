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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#اگر_تعریف_شده HAVE_LIMITS_H
#ضمن <limits.h>
#پایان_اگر
#اگر_تعریف_نشده SIZE_MAX
#تعریف_کن SIZE_MAX ((size_t)-1)
#پایان_اگر

#ضمن "../../core/windows/SDL_windows.h"

#ضمن "SDL_windowsvideo.h"

#اگر_تعریف_نشده SS_EDITCONTROL
#تعریف_کن SS_EDITCONTROL 0x2000
#پایان_اگر

#اگر_تعریف_نشده IDOK
#تعریف_کن IDOK 1
#پایان_اگر

#اگر_تعریف_نشده IDCANCEL
#تعریف_کن IDCANCEL 2
#پایان_اگر

// Custom dialog return codes
#تعریف_کن IDCLOSED           20
#تعریف_کن IDINVALPTRINIT     50
#تعریف_کن IDINVALPTRCOMMAND  51
#تعریف_کن IDINVALPTRSETFOCUS 52
#تعریف_کن IDINVALPTRDLGITEM  53
// First button ID
#تعریف_کن IDBUTTONINDEX0 100

#تعریف_کن DLGITEMTYPEBUTTON 0x0080
#تعریف_کن DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#تعریف_کن MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

تعريفنوع HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT پیام_2, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_داده);

تعداد _TASKDIALOG_FLAGS
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
    TDF_SHOW_پیشرفت_BAR = 0x0200,
    TDF_SHOW_MARQUEE_پیشرفت_BAR = 0x0400,
    TDF_CALLBACK_TIMER = 0x0800,
    TDF_POSITION_RELATIVE_مقصد_پنجره = 0x1000,
    TDF_RTL_LAYOUT = 0x2000,
    TDF_NO_DEFAULT_RADIO_BUTTON = 0x4000,
    TDF_CAN_BE_MINIMIZED = 0x8000,
    // #if (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_NO_مجموعه_FOREGROUND = 0x00010000, // Don't call SetForegroundWindow() when activating the dialog
                                        // #endif // (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_اندازه_مقصد_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
تعريفنوع صحيح TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

تعريفنوع تعداد _TASKDIALOG_MESSAGES
{
    TDM_NAVIGATE_صفحه = WM_USER + 101,
    TDM_CLICK_BUTTON = WM_USER + 102,                        // wParam = Button ID
    TDM_مجموعه_MARQUEE_پیشرفت_BAR = WM_USER + 103,            // wParam = 0 (nonMarque) wParam != 0 (Marquee)
    TDM_مجموعه_پیشرفت_BAR_STATE = WM_USER + 104,              // wParam = new progress state
    TDM_مجموعه_پیشرفت_BAR_RANGE = WM_USER + 105,              // lParam = MAKELPARAM(nMinRange, nMaxRange)
    TDM_مجموعه_پیشرفت_BAR_POS = WM_USER + 106,                // wParam = new position
    TDM_مجموعه_پیشرفت_BAR_MARQUEE = WM_USER + 107,            // wParam = 0 (stop marquee), wParam != 0 (start marquee), lparam = speed (milliseconds between repaints)
    TDM_مجموعه_ELEMENT_متن = WM_USER + 108,                    // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_CLICK_RADIO_BUTTON = WM_USER + 110,                  // wParam = Radio Button ID
    TDM_ENABLE_BUTTON = WM_USER + 111,                       // lParam = 0 (disable), lParam != 0 (enable), wParam = Button ID
    TDM_ENABLE_RADIO_BUTTON = WM_USER + 112,                 // lParam = 0 (disable), lParam != 0 (enable), wParam = Radio Button ID
    TDM_CLICK_VERIFICATION = WM_USER + 113,                  // wParam = 0 (unchecked), 1 (checked), lParam = 1 (set key focus)
    TDM_UPDATE_ELEMENT_متن = WM_USER + 114,                 // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_مجموعه_BUTTON_ELEVATION_REQUIRED_STATE = WM_USER + 115, // wParam = Button ID, lParam = 0 (elevation not required), lParam != 0 (elevation required)
    TDM_UPDATE_ICON = WM_USER + 116                          // wParam = icon element (TASKDIALOG_ICON_ELEMENTS), lParam = new icon (hIcon if TDF_USE_HICON_* was set, PCWSTR otherwise)
} TASKDIALOG_MESSAGES;

تعريفنوع تعداد _TASKDIALOG_NOTIFICATIONS
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

تعريفنوع تعداد _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

تعريفنوع تعداد _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#تعریف_کن TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#تعریف_کن TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#تعریف_کن TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#تعریف_کن TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

تعداد _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
تعريفنوع صحيح TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#رهنمود pack(افزودن, 1)

تعريفنوع بنية _TASKDIALOG_BUTTON
{
    صحيح nButtonID;
    PCWSTR psz_Button_متن;
} TASKDIALOG_BUTTON;

تعريفنوع بنية _TASKDIALOGCONFIG
{
    UINT cb_اندازه;
    HWND hwnd_والد;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR psz_پنجره_Title;                          // string or MAKEINTRESOURCE()
    اتحاد
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    ثابت TASKDIALOG_BUTTON *pButtons;
    صحيح nDefaultButton;
    UINT cRadioButtons;
    ثابت TASKDIALOG_BUTTON *pRadioButtons;
    صحيح nDefaultRadioButton;
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
    LONG_PTR lp_Callback_داده;
    UINT cx_عرض; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

تعريفنوع بنية
{
    کلمه dlgVer;
    کلمه signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    کلمه c_Dlg_اقلام;
    کوتاه x;
    کوتاه y;
    کوتاه cx;
    کوتاه cy;
} DLGTEMPLATEEX;

تعريفنوع بنية
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    کوتاه x;
    کوتاه y;
    کوتاه cx;
    کوتاه cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#رهنمود pack(برداشت)

تعريفنوع بنية
{
    DLGTEMPLATEEX *lpDialog;
    فراغ *داده;
    size_t اندازه;
    size_t استفاده_شده;
    کلمه numbuttons;
} WIN_Dialog_داده;

ساكن bool Get_Button_شاخص(ثابت SDL_پیام_Box_داده *messageboxdata, SDL_پیام_Box_Button_Flags flags, size_t *i)
{
    لكل (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        إذا (messageboxdata->buttons[*i].flags & flags) {
            أرجع true;
        }
    }
    أرجع false;
}

ساكن INT_PTR CALLBACK پیام_Box_Dialog_Proc(HWND hDlg, UINT i_پیام, WPARAM wParam, LPARAM lParam)
{
    ثابت SDL_پیام_Box_داده *messageboxdata;
    size_t buttonindex;

    بدل (i_پیام) {
    حالة WM_INITDIALOG:
        إذا (lParam == 0) {
            انتها_Dialog(hDlg, IDINVALPTRINIT);
            أرجع TRUE;
        }
        messageboxdata = (ثابت SDL_پیام_Box_داده *)lParam;
        مجموعه_پنجره_Long_Ptr(hDlg, GWLP_USERDATA, lParam);

        إذا (Get_Button_شاخص(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = Get_Dlg_قلم(hDlg, (صحيح)(IDBUTTONINDEX0 + buttonindex));
            إذا (!buttonctl) {
                انتها_Dialog(hDlg, IDINVALPTRDLGITEM);
            }
            Post_پیام(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } وإلا {
            // Give the focus to the dialog window instead
            مجموعه_Focus(hDlg);
        }
        أرجع FALSE;
    حالة WM_SETFOCUS:
        messageboxdata = (ثابت SDL_پیام_Box_داده *)Get_پنجره_Long_Ptr(hDlg, GWLP_USERDATA);
        إذا (!messageboxdata) {
            انتها_Dialog(hDlg, IDINVALPTRSETFOCUS);
            أرجع TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        إذا (Get_Button_شاخص(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            أرجع FALSE;
        }
        أرجع TRUE;
    حالة WM_COMMAND:
        messageboxdata = (ثابت SDL_پیام_Box_داده *)Get_پنجره_Long_Ptr(hDlg, GWLP_USERDATA);
        إذا (!messageboxdata) {
            انتها_Dialog(hDlg, IDINVALPTRCOMMAND);
            أرجع TRUE;
        }

        // Return the ID of the button that was pushed
        إذا (wParam == IDOK) {
            إذا (Get_Button_شاخص(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                انتها_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } وإلا إذا (wParam == IDCANCEL) {
            إذا (Get_Button_شاخص(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                انتها_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } وإلا {
                // Closing of window was requested by user or system. It would be rude not to comply.
                انتها_Dialog(hDlg, IDCLOSED);
            }
        } وإلا إذا (wParam >= IDBUTTONINDEX0 && (صحيح)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            انتها_Dialog(hDlg, wParam);
        }
        أرجع TRUE;

    افتراضي:
        اكسر;
    }
    أرجع FALSE;
}

ساكن bool ExpandDialogSpace(WIN_Dialog_داده *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    ثابت size_t sizestep = 0x10000;
    size_t اندازه = dialog->اندازه;

    إذا (اندازه == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        اندازه = 0x1000;
        إذا (SIZE_MAX - sizestep < space) {
            اندازه = space;
        } وإلا إذا (space > اندازه) {
            اندازه = (space + sizestep) & ~(sizestep - 1);
        }
    } وإلا إذا (SIZE_MAX - dialog->استفاده_شده < space) {
        SDL_بیرون_از_حافظه();
        أرجع false;
    } وإلا إذا (SIZE_MAX - (dialog->استفاده_شده + space) < sizestep) {
        // Close to the maximum.
        اندازه = dialog->استفاده_شده + space;
    } وإلا إذا (اندازه < dialog->استفاده_شده + space) {
        // Round up to the next 64 KiB block.
        اندازه = dialog->استفاده_شده + space;
        اندازه += sizestep - اندازه % sizestep;
    }

    إذا (اندازه > dialog->اندازه) {
        فراغ *داده = SDL_realloc(dialog->داده, اندازه);
        إذا (!داده) {
            أرجع false;
        }
        dialog->داده = داده;
        dialog->اندازه = اندازه;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->داده;
    }
    أرجع true;
}

ساكن bool Align_Dialog_داده(WIN_Dialog_داده *dialog, size_t اندازه)
{
    size_t padding = (dialog->استفاده_شده % اندازه);

    إذا (!ExpandDialogSpace(dialog, padding)) {
        أرجع false;
    }

    dialog->استفاده_شده += padding;

    أرجع true;
}

ساكن bool جمع_کن_Dialog_داده(WIN_Dialog_داده *dialog, ثابت فراغ *داده, size_t اندازه)
{
    إذا (!ExpandDialogSpace(dialog, اندازه)) {
        أرجع false;
    }

    SDL_memcpy((Uint8 *)dialog->داده + dialog->استفاده_شده, داده, اندازه);
    dialog->استفاده_شده += اندازه;

    أرجع true;
}

ساكن bool جمع_کن_Dialog_String(WIN_Dialog_داده *dialog, ثابت حرف *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t شمار;
    bool وضعیت;

    إذا (!string) {
        string = "";
    }

    wstring = WIN_UTF8_مقصد_String_W(string);
    إذا (!wstring) {
        أرجع false;
    }

    // Find out how many characters we have, including null terminator
    شمار = 0;
    لكل (p = wstring; *p; ++p) {
        ++شمار;
    }
    ++شمار;

    وضعیت = جمع_کن_Dialog_داده(dialog, wstring, شمار * حجم(WCHAR));
    SDL_free(wstring);
    أرجع وضعیت;
}

ساكن صحيح s_پایه_Units_X;
ساكن صحيح s_پایه_Units_Y;
ساكن فراغ Vec2_مقصد_DLU(کوتاه *x, کوتاه *y)
{
    SDL_assert(s_پایه_Units_X != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (کوتاه)MulDiv(*x, 4, s_پایه_Units_X);
    *y = (کوتاه)MulDiv(*y, 8, s_پایه_Units_Y);
}

ساكن bool جمع_کن_Dialog_Control(WIN_Dialog_داده *dialog, کلمه type, DWORD style, DWORD exStyle, صحيح x, صحيح y, صحيح w, صحيح h, صحيح id, ثابت حرف *caption, کلمه ordinal)
{
    DLGITEMTEMPLATEEX قلم;
    کلمه marker = 0xFFFF;
    کلمه extra_داده = 0;

    SDL_zero(قلم);
    قلم.style = style;
    قلم.exStyle = exStyle;
    قلم.x = (کوتاه)x;
    قلم.y = (کوتاه)y;
    قلم.cx = (کوتاه)w;
    قلم.cy = (کوتاه)h;
    قلم.id = id;

    Vec2_مقصد_DLU(&قلم.x, &قلم.y);
    Vec2_مقصد_DLU(&قلم.cx, &قلم.cy);

    إذا (!Align_Dialog_داده(dialog, حجم(DWORD))) {
        أرجع false;
    }
    إذا (!جمع_کن_Dialog_داده(dialog, &قلم, حجم(قلم))) {
        أرجع false;
    }
    إذا (!جمع_کن_Dialog_داده(dialog, &marker, حجم(marker))) {
        أرجع false;
    }
    إذا (!جمع_کن_Dialog_داده(dialog, &type, حجم(type))) {
        أرجع false;
    }
    إذا (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        إذا (!جمع_کن_Dialog_String(dialog, caption)) {
            أرجع false;
        }
    } وإلا {
        إذا (!جمع_کن_Dialog_داده(dialog, &marker, حجم(marker))) {
            أرجع false;
        }
        إذا (!جمع_کن_Dialog_داده(dialog, &ordinal, حجم(ordinal))) {
            أرجع false;
        }
    }
    إذا (!جمع_کن_Dialog_داده(dialog, &extra_داده, حجم(extra_داده))) {
        أرجع false;
    }
    إذا (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_اقلام;

    أرجع true;
}

ساكن bool جمع_کن_Dialog_Static_متن(WIN_Dialog_داده *dialog, صحيح x, صحيح y, صحيح w, صحيح h, ثابت حرف *متن)
{
    DWORD style = WS_VISIBLE | WS_فرزند | SS_چپ | SS_NOPREFIX | SS_EDITCONTROL | WS_گروه;
    أرجع جمع_کن_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, متن, 0);
}

ساكن bool جمع_کن_Dialog_Static_Icon(WIN_Dialog_داده *dialog, صحيح x, صحيح y, صحيح w, صحيح h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_فرزند | SS_ICON | WS_گروه;
    أرجع جمع_کن_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, عدم, ordinal);
}

ساكن bool جمع_کن_Dialog_Button(WIN_Dialog_داده *dialog, صحيح x, صحيح y, صحيح w, صحيح h, ثابت حرف *متن, صحيح id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_فرزند | WS_TABSTOP;
    إذا (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } وإلا {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    إذا (dialog->numbuttons == 0) {
        style |= WS_گروه;
    }
    أرجع جمع_کن_Dialog_Control(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, متن, 0);
}

ساكن فراغ Free_Dialog_داده(WIN_Dialog_داده *dialog)
{
    SDL_free(dialog->داده);
    SDL_free(dialog);
}

ساكن WIN_Dialog_داده *Create_Dialog_داده(صحيح w, صحيح h, ثابت حرف *caption)
{
    WIN_Dialog_داده *dialog;
    DLGTEMPLATEEX dialogTemplate;
    کلمه کلمه_مقصد_Pass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (کوتاه)w;
    dialogTemplate.cy = (کوتاه)h;
    Vec2_مقصد_DLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_داده *)SDL_calloc(1, حجم(*dialog));
    إذا (!dialog) {
        أرجع عدم;
    }

    إذا (!جمع_کن_Dialog_داده(dialog, &dialogTemplate, حجم(dialogTemplate))) {
        Free_Dialog_داده(dialog);
        أرجع عدم;
    }

    // No menu
    کلمه_مقصد_Pass = 0;
    إذا (!جمع_کن_Dialog_داده(dialog, &کلمه_مقصد_Pass, 2)) {
        Free_Dialog_داده(dialog);
        أرجع عدم;
    }

    // No custom class
    إذا (!جمع_کن_Dialog_داده(dialog, &کلمه_مقصد_Pass, 2)) {
        Free_Dialog_داده(dialog);
        أرجع عدم;
    }

    // title
    إذا (!جمع_کن_Dialog_String(dialog, caption)) {
        Free_Dialog_داده(dialog);
        أرجع عدم;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE مقصد_Pass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_اندازه = حجم(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(عدم);
            صحيح LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            إذا (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            کلمه_مقصد_Pass = (کلمه)(-72 * NCM.lf_پیام_Font.lf_ارتفاع / LogicalPixelsY);
            ReleaseDC(عدم, ScreenDC);
        }

        إذا (!جمع_کن_Dialog_داده(dialog, &کلمه_مقصد_Pass, 2)) {
            Free_Dialog_داده(dialog);
            أرجع عدم;
        }

        // Font weight
        کلمه_مقصد_Pass = (کلمه)NCM.lf_پیام_Font.lf_وزن;
        إذا (!جمع_کن_Dialog_داده(dialog, &کلمه_مقصد_Pass, 2)) {
            Free_Dialog_داده(dialog);
            أرجع عدم;
        }

        // italic?
        مقصد_Pass = NCM.lf_پیام_Font.lfItalic;
        إذا (!جمع_کن_Dialog_داده(dialog, &مقصد_Pass, 1)) {
            Free_Dialog_داده(dialog);
            أرجع عدم;
        }

        // charset?
        مقصد_Pass = NCM.lf_پیام_Font.lf_Char_مجموعه;
        إذا (!جمع_کن_Dialog_داده(dialog, &مقصد_Pass, 1)) {
            Free_Dialog_داده(dialog);
            أرجع عدم;
        }

        // font typeface.
        إذا (!جمع_کن_Dialog_String(dialog, NCM.lf_پیام_Font.lfFaceName)) {
            Free_Dialog_داده(dialog);
            أرجع عدم;
        }
    }

    أرجع dialog;
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
ساكن ثابت حرف *EscapeAmpersands(حرف **dst, size_t *dstlen, ثابت حرف *src)
{
    حرف *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    إذا (!src) {
        أرجع عدم;
    }

    طالما (src[srclen]) {
        إذا (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    إذا (ampcount == 0) {
        // Nothing to do.
        أرجع src;
    }
    إذا (SIZE_MAX - srclen < ampcount) {
        أرجع عدم;
    }
    إذا (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        إذا (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = عدم;
        newdst = (حرف *)SDL_malloc(*dstlen);
        إذا (!newdst) {
            أرجع عدم;
        }
        *dst = newdst;
    } وإلا {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    طالما (srclen--) {
        إذا (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    أرجع *dst;
}

ساكن عائم WIN_GetContentScale(فراغ)
{
    صحيح dpi = 0;

#إذا 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    إذا (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (صحيح)hdpi_uint;
    }
#پایان_اگر
    إذا (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(عدم);
        إذا (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(عدم, hdc);
        }
    }
    إذا (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    أرجع dpi / (عائم)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
ساكن bool WIN_Show_Old_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
    WIN_Dialog_داده *dialog;
    صحيح i, x, y;
    HFONT DialogFont;
    اندازه_3 اندازه_2;
    RECT متن_اندازه;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    حرف *ampescape = عدم;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool نتیجه;

    HWND والد_پنجره_2 = عدم;

    ثابت عائم scale = WIN_GetContentScale();
    ثابت صحيح Button_عرض = (صحيح)SDL_roundf(88 * scale);
    ثابت صحيح Button_ارتفاع = (صحيح)SDL_roundf(26 * scale);
    ثابت صحيح متن_Margin = (صحيح)SDL_roundf(16 * scale);
    ثابت صحيح ButtonMargin = (صحيح)SDL_roundf(12 * scale);
    ثابت صحيح Icon_عرض = GetSystemMetrics(SM_CXICON);
    ثابت صحيح Icon_ارتفاع = GetSystemMetrics(SM_CYICON);
    ثابت صحيح IconMargin = (صحيح)SDL_roundf(20 * scale);

    إذا (messageboxdata->numbuttons > MAX_BUTTONS) {
        أرجع SDL_مجموعه_Error("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    بدل (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    حالة SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        اكسر;
    حالة SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        اكسر;
    حالة SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        اكسر;
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
        NCM.cb_اندازه = حجم(NCM);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);
        lf = NCM.lf_پیام_Font;
        DialogFont = Create_Font_غیرمستقیم(&lf);
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
            اندازه_3 extent;
            Get_متن_Extent_Point32_A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_پایه_Units_X = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_پایه_Units_Y = TM.tm_ارتفاع;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8_مقصد_String_W(messageboxdata->پیام);
    SDL_zero(متن_اندازه);
    Draw_متن_W(FontDC, wmessage, -1, &متن_اندازه, DT_CALCRECT | DT_چپ | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    متن_اندازه.چپ += متن_Margin;
    متن_اندازه.راست += متن_Margin + 2;
    متن_اندازه.بالاترین += متن_Margin;
    متن_اندازه.bottom += متن_Margin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    اندازه_2.cx = متن_اندازه.راست - متن_اندازه.چپ;
    اندازه_2.cy = متن_اندازه.bottom - متن_اندازه.بالاترین;
    اندازه_2.cx += متن_Margin * 2;
    اندازه_2.cy += متن_Margin * 2;

    // Make dialog wider and shift text over for the icon.
    إذا (icon) {
        اندازه_2.cx += IconMargin + Icon_عرض;
        متن_اندازه.چپ += IconMargin + Icon_عرض;
        متن_اندازه.راست += IconMargin + Icon_عرض;
    }

    // Ensure the size is wide enough for all of the buttons.
    إذا (اندازه_2.cx < (LONG)messageboxdata->numbuttons * (Button_عرض + ButtonMargin) + ButtonMargin) {
        اندازه_2.cx = (LONG)messageboxdata->numbuttons * (Button_عرض + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    إذا (icon && اندازه_2.cy < (LONG)IconMargin * 2 + Icon_ارتفاع) {
        اندازه_2.cy = (LONG)IconMargin * 2 + Icon_ارتفاع;
    }

    // Add vertical space for the buttons and border.
    اندازه_2.cy += Button_ارتفاع + متن_Margin;

    dialog = Create_Dialog_داده(اندازه_2.cx, اندازه_2.cy, messageboxdata->title);
    إذا (!dialog) {
        أرجع false;
    }

    إذا (icon && !جمع_کن_Dialog_Static_Icon(dialog, IconMargin, IconMargin, Icon_عرض, Icon_ارتفاع, icon)) {
        Free_Dialog_داده(dialog);
        أرجع false;
    }

    إذا (!جمع_کن_Dialog_Static_متن(dialog, متن_اندازه.چپ, متن_اندازه.بالاترین, متن_اندازه.راست - متن_اندازه.چپ, متن_اندازه.bottom - متن_اندازه.بالاترین, messageboxdata->پیام)) {
        Free_Dialog_داده(dialog);
        أرجع false;
    }

    // Align the buttons to the right/bottom.
    x = اندازه_2.cx - (Button_عرض + ButtonMargin) * messageboxdata->numbuttons;
    y = اندازه_2.cy - Button_ارتفاع - ButtonMargin;
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        ثابت حرف *buttontext;
        ثابت SDL_پیام_Box_Button_داده *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        إذا (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_چپ_مقصد_راست) {
            sdlButton = &messageboxdata->buttons[i];
        } وإلا {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        إذا (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            إذا (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->متن);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        إذا (!buttontext || !جمع_کن_Dialog_Button(dialog, x, y, Button_عرض, Button_ارتفاع, buttontext, IDBUTTONINDEX0 + (صحيح)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_داده(dialog);
            SDL_free(ampescape);
            أرجع false;
        }

        x += Button_عرض + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    إذا (messageboxdata->پنجره) {
        والد_پنجره_2 = messageboxdata->پنجره->داخلی->hwnd;
    }

    rc = Dialog_Box_غیرمستقیم_Param(عدم, (DLGTEMPLATE *)dialog->lpDialog, والد_پنجره_2, پیام_Box_Dialog_Proc, (LPARAM)messageboxdata);
    إذا (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        نتیجه = true;
    } وإلا إذا (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        نتیجه = true;
        *buttonID = -1;
    } وإلا {
        إذا (rc == 0) {
            SDL_مجموعه_Error("Invalid parent window handle");
        } وإلا إذا (rc == -1) {
            SDL_مجموعه_Error("The message box encountered an error.");
        } وإلا إذا (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_مجموعه_Error("Invalid message box pointer in dialog procedure");
        } وإلا إذا (rc == IDINVALPTRDLGITEM) {
            SDL_مجموعه_Error("Couldn't find dialog control of the default enter-key button");
        } وإلا {
            SDL_مجموعه_Error("An unknown error occurred");
        }
        نتیجه = false;
    }

    Free_Dialog_داده(dialog);
    أرجع نتیجه;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
تعريفنوع HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(ثابت TASKDIALOGCONFIG *pTaskConfig, صحيح *pnButton, صحيح *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_Show_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
    HWND والد_پنجره_2 = عدم;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC p_Task_Dialog_غیرمستقیم;
    HRESULT hr;
    حرف *ampescape = عدم;
    size_t ampescapesize = 0;
    صحيح nButton;
    صحيح nCancelButton;
    صحيح i;
    bool نتیجه = false;

    إذا (SIZE_MAX / حجم(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        أرجع SDL_بیرون_از_حافظه();
    }

    HMODULE hUser32 = GetModuleHandle(متن_2("user32.dll"));
    تعريفنوع DPI_AWARENESS_CONTEXT (WINAPI *pfn_مجموعه_Thread_Dpi_Awareness_Context)(DPI_AWARENESS_CONTEXT);
    pfn_مجموعه_Thread_Dpi_Awareness_Context p_مجموعه_Thread_Dpi_Awareness_Context = (pfn_مجموعه_Thread_Dpi_Awareness_Context)Get_Proc_آدرس(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT قبلی_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    إذا (p_مجموعه_Thread_Dpi_Awareness_Context) {
        قبلی_context = p_مجموعه_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_در_هر_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = بارگیری_Library(متن_2("comctl32.dll"));
    إذا (!hComctl32) {
        نتیجه = WIN_Show_Old_پیام_Box(messageboxdata, buttonID);
        اذهب انجامشده;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    p_Task_Dialog_غیرمستقیم = (TASKDIALOGINDIRECTPROC)Get_Proc_آدرس(hComctl32, "TaskDialogIndirect");
    إذا (!p_Task_Dialog_غیرمستقیم) {
        FreeLibrary(hComctl32);
        نتیجه = WIN_Show_Old_پیام_Box(messageboxdata, buttonID);
        اذهب انجامشده;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    إذا (messageboxdata->پنجره) {
        والد_پنجره_2 = messageboxdata->پنجره->داخلی->hwnd;
    }

    wmessage = WIN_UTF8_مقصد_String_W(messageboxdata->پیام);
    wtitle = WIN_UTF8_مقصد_String_W(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_اندازه = حجم(TASKDIALOGCONFIG);
    TaskConfig.hwnd_والد = والد_پنجره_2;
    TaskConfig.dwFlags = TDF_اندازه_مقصد_CONTENT;
    TaskConfig.psz_پنجره_Title = wtitle;
    إذا (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } وإلا إذا (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } وإلا إذا (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } وإلا {
        TaskConfig.pszMainIcon = عدم;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(حجم(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        ثابت حرف *buttontext;
        إذا (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_چپ_مقصد_راست) {
            pButton = &pButtons[i];
        } وإلا {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        إذا (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } وإلا {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].متن);
        إذا (!buttontext) {
            صحيح j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            لكل (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].psz_Button_متن);
            }
            SDL_free(pButtons);
            أرجع false;
        }
        pButton->psz_Button_متن = WIN_UTF8_مقصد_String_W(buttontext);
        إذا (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = p_Task_Dialog_غیرمستقیم(&TaskConfig, &nButton, عدم, عدم);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    لكل (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].psz_Button_متن);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    إذا (SUCCEEDED(hr)) {
        إذا (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } وإلا إذا (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } وإلا {
            *buttonID = -1;
        }
        نتیجه = true;
    } وإلا {
        // We failed showing the Task Dialog, use the old message box!
        نتیجه = WIN_Show_Old_پیام_Box(messageboxdata, buttonID);
    }

انجامشده:
    إذا (p_مجموعه_Thread_Dpi_Awareness_Context) {
        p_مجموعه_Thread_Dpi_Awareness_Context(قبلی_context);
    }
    أرجع نتیجه;
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS

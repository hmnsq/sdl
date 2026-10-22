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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef HAVE_LIMITS_H
#অন্তর্ভাব <limits.h>
#endif
#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

#অন্তর্ভাব "../../core/windows/SDL_windows.h"

#অন্তর্ভাব "SDL_windowsvideo.h"

#ifndef SS_EDITCONTROL
#define SS_EDITCONTROL 0x2000
#endif

#ifndef IDOK
#define IDOK 1
#endif

#ifndef IDCANCEL
#define IDCANCEL 2
#endif

// Custom dialog return codes
#define IDCLOSED           20
#define IDINVALPTRINIT     50
#define IDINVALPTRCOMMAND  51
#define IDINVALPTRSETFOCUS 52
#define IDINVALPTRDLGITEM  53
// First button ID
#define IDBUTTONINDEX0 100

#define DLGITEMTYPEBUTTON 0x0080
#define DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#define MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

প্রকারলেখ HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT বার্তা, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_তথ্য);

গণনা _TASKDIALOG_FLAGS
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
    TDF_SHOW_PROGRESS_BAR = 0x0200,
    TDF_SHOW_MARQUEE_PROGRESS_BAR = 0x0400,
    TDF_CALLBACK_TIMER = 0x0800,
    TDF_POSITION_RELATIVE_TO_WINDOW = 0x1000,
    TDF_RTL_LAYOUT = 0x2000,
    TDF_NO_DEFAULT_RADIO_BUTTON = 0x4000,
    TDF_CAN_BE_MINIMIZED = 0x8000,
    // #if (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_NO_SET_FOREGROUND = 0x00010000, // Don't call SetForegroundWindow() when activating the dialog
                                        // #endif // (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_আকার_TO_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
প্রকারলেখ পূর্ণসংখ্যা TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

প্রকারলেখ গণনা _TASKDIALOG_MESSAGES
{
    TDM_NAVIGATE_PAGE = WM_USER + 101,
    TDM_CLICK_BUTTON = WM_USER + 102,                        // wParam = Button ID
    TDM_SET_MARQUEE_PROGRESS_BAR = WM_USER + 103,            // wParam = 0 (nonMarque) wParam != 0 (Marquee)
    TDM_SET_PROGRESS_BAR_STATE = WM_USER + 104,              // wParam = new progress state
    TDM_SET_PROGRESS_BAR_RANGE = WM_USER + 105,              // lParam = MAKELPARAM(nMinRange, nMaxRange)
    TDM_SET_PROGRESS_BAR_POS = WM_USER + 106,                // wParam = new position
    TDM_SET_PROGRESS_BAR_MARQUEE = WM_USER + 107,            // wParam = 0 (stop marquee), wParam != 0 (start marquee), lparam = speed (milliseconds between repaints)
    TDM_SET_ELEMENT_TEXT = WM_USER + 108,                    // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_CLICK_RADIO_BUTTON = WM_USER + 110,                  // wParam = Radio Button ID
    TDM_ENABLE_BUTTON = WM_USER + 111,                       // lParam = 0 (disable), lParam != 0 (enable), wParam = Button ID
    TDM_ENABLE_RADIO_BUTTON = WM_USER + 112,                 // lParam = 0 (disable), lParam != 0 (enable), wParam = Radio Button ID
    TDM_CLICK_VERIFICATION = WM_USER + 113,                  // wParam = 0 (unchecked), 1 (checked), lParam = 1 (set key focus)
    TDM_UPDATE_ELEMENT_TEXT = WM_USER + 114,                 // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE = WM_USER + 115, // wParam = Button ID, lParam = 0 (elevation not required), lParam != 0 (elevation required)
    TDM_UPDATE_ICON = WM_USER + 116                          // wParam = icon element (TASKDIALOG_ICON_ELEMENTS), lParam = new icon (hIcon if TDF_USE_HICON_* was set, PCWSTR otherwise)
} TASKDIALOG_MESSAGES;

প্রকারলেখ গণনা _TASKDIALOG_NOTIFICATIONS
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

প্রকারলেখ গণনা _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

প্রকারলেখ গণনা _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#define TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#define TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#define TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#define TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

গণনা _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
প্রকারলেখ পূর্ণসংখ্যা TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#pragma pack(ঠেলো, 1)

প্রকারলেখ কাঠামো _TASKDIALOG_BUTTON
{
    পূর্ণসংখ্যা nButtonID;
    PCWSTR pszButtonText;
} TASKDIALOG_BUTTON;

প্রকারলেখ কাঠামো _TASKDIALOGCONFIG
{
    UINT cb_আকার;
    HWND hwndParent;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR pszWindowTitle;                          // string or MAKEINTRESOURCE()
    সংঘ
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    ধ্রুবক TASKDIALOG_BUTTON *pButtons;
    পূর্ণসংখ্যা nDefaultButton;
    UINT cRadioButtons;
    ধ্রুবক TASKDIALOG_BUTTON *pRadioButtons;
    পূর্ণসংখ্যা nDefaultRadioButton;
    PCWSTR pszVerificationText;
    PCWSTR pszExpandedInformation;
    PCWSTR pszExpandedControlText;
    PCWSTR pszCollapsedControlText;
    সংঘ
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lp_Callback_তথ্য;
    UINT cxWidth; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

প্রকারলেখ কাঠামো
{
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD c_Dlg_বস্তুসমূহ;
    short x;
    short y;
    short cx;
    short cy;
} DLGTEMPLATEEX;

প্রকারলেখ কাঠামো
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    short x;
    short y;
    short cx;
    short cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#pragma pack(বের_করো)

প্রকারলেখ কাঠামো
{
    DLGTEMPLATEEX *lpDialog;
    শূন্য *তথ্য;
    size_t আকার_2;
    size_t used;
    WORD numbuttons;
} WIN_Dialog_তথ্য;

স্থির bool Get_Button_সূচক(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, SDL_MessageBoxButtonFlags flags, size_t *i)
{
    জন্য (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        যদি (messageboxdata->buttons[*i].flags & flags) {
            ফেরত true;
        }
    }
    ফেরত false;
}

স্থির INT_PTR CALLBACK MessageBoxDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata;
    size_t buttonindex;

    নির্বাচন (iMessage) {
    ক্ষেত্র WM_INITDIALOG:
        যদি (lParam == 0) {
            EndDialog(hDlg, IDINVALPTRINIT);
            ফেরত TRUE;
        }
        messageboxdata = (ধ্রুবক SDL_Message_Box_তথ্য *)lParam;
        SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);

        যদি (Get_Button_সূচক(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = GetDlgItem(hDlg, (পূর্ণসংখ্যা)(IDBUTTONINDEX0 + buttonindex));
            যদি (!buttonctl) {
                EndDialog(hDlg, IDINVALPTRDLGITEM);
            }
            PostMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } অন্যথা {
            // Give the focus to the dialog window instead
            SetFocus(hDlg);
        }
        ফেরত FALSE;
    ক্ষেত্র WM_SETFOCUS:
        messageboxdata = (ধ্রুবক SDL_Message_Box_তথ্য *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        যদি (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRSETFOCUS);
            ফেরত TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        যদি (Get_Button_সূচক(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            ফেরত FALSE;
        }
        ফেরত TRUE;
    ক্ষেত্র WM_COMMAND:
        messageboxdata = (ধ্রুবক SDL_Message_Box_তথ্য *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        যদি (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRCOMMAND);
            ফেরত TRUE;
        }

        // Return the ID of the button that was pushed
        যদি (wParam == IDOK) {
            যদি (Get_Button_সূচক(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } অন্যথা যদি (wParam == IDCANCEL) {
            যদি (Get_Button_সূচক(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } অন্যথা {
                // Closing of window was requested by user or system. It would be rude not to comply.
                EndDialog(hDlg, IDCLOSED);
            }
        } অন্যথা যদি (wParam >= IDBUTTONINDEX0 && (পূর্ণসংখ্যা)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            EndDialog(hDlg, wParam);
        }
        ফেরত TRUE;

    পূর্বনির্ধারিত:
        বিরতি;
    }
    ফেরত FALSE;
}

স্থির bool ExpandDialogSpace(WIN_Dialog_তথ্য *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    ধ্রুবক size_t sizestep = 0x10000;
    size_t আকার_2 = dialog->আকার_2;

    যদি (আকার_2 == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        আকার_2 = 0x1000;
        যদি (SIZE_MAX - sizestep < space) {
            আকার_2 = space;
        } অন্যথা যদি (space > আকার_2) {
            আকার_2 = (space + sizestep) & ~(sizestep - 1);
        }
    } অন্যথা যদি (SIZE_MAX - dialog->used < space) {
        SDL_OutOfMemory();
        ফেরত false;
    } অন্যথা যদি (SIZE_MAX - (dialog->used + space) < sizestep) {
        // Close to the maximum.
        আকার_2 = dialog->used + space;
    } অন্যথা যদি (আকার_2 < dialog->used + space) {
        // Round up to the next 64 KiB block.
        আকার_2 = dialog->used + space;
        আকার_2 += sizestep - আকার_2 % sizestep;
    }

    যদি (আকার_2 > dialog->আকার_2) {
        শূন্য *তথ্য = SDL_realloc(dialog->তথ্য, আকার_2);
        যদি (!তথ্য) {
            ফেরত false;
        }
        dialog->তথ্য = তথ্য;
        dialog->আকার_2 = আকার_2;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->তথ্য;
    }
    ফেরত true;
}

স্থির bool Align_Dialog_তথ্য(WIN_Dialog_তথ্য *dialog, size_t আকার_2)
{
    size_t padding = (dialog->used % আকার_2);

    যদি (!ExpandDialogSpace(dialog, padding)) {
        ফেরত false;
    }

    dialog->used += padding;

    ফেরত true;
}

স্থির bool Add_Dialog_তথ্য(WIN_Dialog_তথ্য *dialog, ধ্রুবক শূন্য *তথ্য, size_t আকার_2)
{
    যদি (!ExpandDialogSpace(dialog, আকার_2)) {
        ফেরত false;
    }

    SDL_memcpy((Uint8 *)dialog->তথ্য + dialog->used, তথ্য, আকার_2);
    dialog->used += আকার_2;

    ফেরত true;
}

স্থির bool AddDialogString(WIN_Dialog_তথ্য *dialog, ধ্রুবক অক্ষর *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t গুনতি;
    bool status;

    যদি (!string) {
        string = "";
    }

    wstring = WIN_UTF8ToStringW(string);
    যদি (!wstring) {
        ফেরত false;
    }

    // Find out how many characters we have, including null terminator
    গুনতি = 0;
    জন্য (p = wstring; *p; ++p) {
        ++গুনতি;
    }
    ++গুনতি;

    status = Add_Dialog_তথ্য(dialog, wstring, গুনতি * আকার(WCHAR));
    SDL_free(wstring);
    ফেরত status;
}

স্থির পূর্ণসংখ্যা s_BaseUnitsX;
স্থির পূর্ণসংখ্যা s_BaseUnitsY;
স্থির শূন্য Vec2ToDLU(short *x, short *y)
{
    SDL_assert(s_BaseUnitsX != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (short)MulDiv(*x, 4, s_BaseUnitsX);
    *y = (short)MulDiv(*y, 8, s_BaseUnitsY);
}

স্থির bool AddDialogControl(WIN_Dialog_তথ্য *dialog, WORD type, DWORD style, DWORD exStyle, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, পূর্ণসংখ্যা id, ধ্রুবক অক্ষর *caption, WORD ordinal)
{
    DLGITEMTEMPLATEEX item;
    WORD marker = 0xFFFF;
    WORD extra_তথ্য = 0;

    SDL_zero(item);
    item.style = style;
    item.exStyle = exStyle;
    item.x = (short)x;
    item.y = (short)y;
    item.cx = (short)w;
    item.cy = (short)h;
    item.id = id;

    Vec2ToDLU(&item.x, &item.y);
    Vec2ToDLU(&item.cx, &item.cy);

    যদি (!Align_Dialog_তথ্য(dialog, আকার(DWORD))) {
        ফেরত false;
    }
    যদি (!Add_Dialog_তথ্য(dialog, &item, আকার(item))) {
        ফেরত false;
    }
    যদি (!Add_Dialog_তথ্য(dialog, &marker, আকার(marker))) {
        ফেরত false;
    }
    যদি (!Add_Dialog_তথ্য(dialog, &type, আকার(type))) {
        ফেরত false;
    }
    যদি (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        যদি (!AddDialogString(dialog, caption)) {
            ফেরত false;
        }
    } অন্যথা {
        যদি (!Add_Dialog_তথ্য(dialog, &marker, আকার(marker))) {
            ফেরত false;
        }
        যদি (!Add_Dialog_তথ্য(dialog, &ordinal, আকার(ordinal))) {
            ফেরত false;
        }
    }
    যদি (!Add_Dialog_তথ্য(dialog, &extra_তথ্য, আকার(extra_তথ্য))) {
        ফেরত false;
    }
    যদি (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_বস্তুসমূহ;

    ফেরত true;
}

স্থির bool AddDialogStaticText(WIN_Dialog_তথ্য *dialog, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, ধ্রুবক অক্ষর *text)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_বাম | SS_NOPREFIX | SS_EDITCONTROL | WS_GROUP;
    ফেরত AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, text, 0);
}

স্থির bool AddDialogStaticIcon(WIN_Dialog_তথ্য *dialog, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_ICON | WS_GROUP;
    ফেরত AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, ফাঁকা, ordinal);
}

স্থির bool AddDialogButton(WIN_Dialog_তথ্য *dialog, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, ধ্রুবক অক্ষর *text, পূর্ণসংখ্যা id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP;
    যদি (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } অন্যথা {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    যদি (dialog->numbuttons == 0) {
        style |= WS_GROUP;
    }
    ফেরত AddDialogControl(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, text, 0);
}

স্থির শূন্য Free_Dialog_তথ্য(WIN_Dialog_তথ্য *dialog)
{
    SDL_free(dialog->তথ্য);
    SDL_free(dialog);
}

স্থির WIN_Dialog_তথ্য *Create_Dialog_তথ্য(পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, ধ্রুবক অক্ষর *caption)
{
    WIN_Dialog_তথ্য *dialog;
    DLGTEMPLATEEX dialogTemplate;
    WORD WordToPass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (short)w;
    dialogTemplate.cy = (short)h;
    Vec2ToDLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_তথ্য *)SDL_calloc(1, আকার(*dialog));
    যদি (!dialog) {
        ফেরত ফাঁকা;
    }

    যদি (!Add_Dialog_তথ্য(dialog, &dialogTemplate, আকার(dialogTemplate))) {
        Free_Dialog_তথ্য(dialog);
        ফেরত ফাঁকা;
    }

    // No menu
    WordToPass = 0;
    যদি (!Add_Dialog_তথ্য(dialog, &WordToPass, 2)) {
        Free_Dialog_তথ্য(dialog);
        ফেরত ফাঁকা;
    }

    // No custom class
    যদি (!Add_Dialog_তথ্য(dialog, &WordToPass, 2)) {
        Free_Dialog_তথ্য(dialog);
        ফেরত ফাঁকা;
    }

    // title
    যদি (!AddDialogString(dialog, caption)) {
        Free_Dialog_তথ্য(dialog);
        ফেরত ফাঁকা;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ToPass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_আকার = আকার(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(ফাঁকা);
            পূর্ণসংখ্যা LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            যদি (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            WordToPass = (WORD)(-72 * NCM.lfMessageFont.lfHeight / LogicalPixelsY);
            ReleaseDC(ফাঁকা, ScreenDC);
        }

        যদি (!Add_Dialog_তথ্য(dialog, &WordToPass, 2)) {
            Free_Dialog_তথ্য(dialog);
            ফেরত ফাঁকা;
        }

        // Font weight
        WordToPass = (WORD)NCM.lfMessageFont.lfWeight;
        যদি (!Add_Dialog_তথ্য(dialog, &WordToPass, 2)) {
            Free_Dialog_তথ্য(dialog);
            ফেরত ফাঁকা;
        }

        // italic?
        ToPass = NCM.lfMessageFont.lfItalic;
        যদি (!Add_Dialog_তথ্য(dialog, &ToPass, 1)) {
            Free_Dialog_তথ্য(dialog);
            ফেরত ফাঁকা;
        }

        // charset?
        ToPass = NCM.lfMessageFont.lfCharSet;
        যদি (!Add_Dialog_তথ্য(dialog, &ToPass, 1)) {
            Free_Dialog_তথ্য(dialog);
            ফেরত ফাঁকা;
        }

        // font typeface.
        যদি (!AddDialogString(dialog, NCM.lfMessageFont.lfFaceName)) {
            Free_Dialog_তথ্য(dialog);
            ফেরত ফাঁকা;
        }
    }

    ফেরত dialog;
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
স্থির ধ্রুবক অক্ষর *EscapeAmpersands(অক্ষর **dst, size_t *dstlen, ধ্রুবক অক্ষর *src)
{
    অক্ষর *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    যদি (!src) {
        ফেরত ফাঁকা;
    }

    যখন (src[srclen]) {
        যদি (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    যদি (ampcount == 0) {
        // Nothing to do.
        ফেরত src;
    }
    যদি (SIZE_MAX - srclen < ampcount) {
        ফেরত ফাঁকা;
    }
    যদি (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        যদি (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = ফাঁকা;
        newdst = (অক্ষর *)SDL_malloc(*dstlen);
        যদি (!newdst) {
            ফেরত ফাঁকা;
        }
        *dst = newdst;
    } অন্যথা {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    যখন (srclen--) {
        যদি (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    ফেরত *dst;
}

স্থির দশমিক WIN_GetContentScale(শূন্য)
{
    পূর্ণসংখ্যা dpi = 0;

#যদি 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    যদি (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (পূর্ণসংখ্যা)hdpi_uint;
    }
#endif
    যদি (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ফাঁকা);
        যদি (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ফাঁকা, hdc);
        }
    }
    যদি (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ফেরত dpi / (দশমিক)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
স্থির bool WIN_ShowOldMessageBox(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID)
{
    WIN_Dialog_তথ্য *dialog;
    পূর্ণসংখ্যা i, x, y;
    HFONT DialogFont;
    আকার_4 আকার_3;
    RECT Text_আকার;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    অক্ষর *ampescape = ফাঁকা;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool ফলাফল;

    HWND ParentWindow = ফাঁকা;

    ধ্রুবক দশমিক scale = WIN_GetContentScale();
    ধ্রুবক পূর্ণসংখ্যা ButtonWidth = (পূর্ণসংখ্যা)SDL_roundf(88 * scale);
    ধ্রুবক পূর্ণসংখ্যা ButtonHeight = (পূর্ণসংখ্যা)SDL_roundf(26 * scale);
    ধ্রুবক পূর্ণসংখ্যা TextMargin = (পূর্ণসংখ্যা)SDL_roundf(16 * scale);
    ধ্রুবক পূর্ণসংখ্যা ButtonMargin = (পূর্ণসংখ্যা)SDL_roundf(12 * scale);
    ধ্রুবক পূর্ণসংখ্যা IconWidth = GetSystemMetrics(SM_CXICON);
    ধ্রুবক পূর্ণসংখ্যা IconHeight = GetSystemMetrics(SM_CYICON);
    ধ্রুবক পূর্ণসংখ্যা IconMargin = (পূর্ণসংখ্যা)SDL_roundf(20 * scale);

    যদি (messageboxdata->numbuttons > MAX_BUTTONS) {
        ফেরত SDL_SetError("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    নির্বাচন (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ক্ষেত্র SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        বিরতি;
    ক্ষেত্র SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        বিরতি;
    ক্ষেত্র SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        বিরতি;
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
        NCM.cb_আকার = আকার(NCM);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);
        lf = NCM.lfMessageFont;
        DialogFont = CreateFontIndirect(&lf);
    }

    // Select the font in to our DC
    SelectObject(FontDC, DialogFont);

    {
        // Get the metrics to try and figure our DLU conversion.
        GetTextMetrics(FontDC, &TM);

        /* Calculation from the following documentation:
         * https://support.microsoft.com/en-gb/help/125681/how-to-calculate-dialog-base-units-with-non-system-based-font
         * This fixes bug 2137, dialog box calculation with a fixed-width system font
         */
        {
            আকার_4 extent;
            GetTextExtentPoint32A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_BaseUnitsX = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_BaseUnitsY = TM.tmHeight;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    SDL_zero(Text_আকার);
    DrawTextW(FontDC, wmessage, -1, &Text_আকার, DT_CALCRECT | DT_বাম | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    Text_আকার.বাম += TextMargin;
    Text_আকার.ডান += TextMargin + 2;
    Text_আকার.শীর্ষ += TextMargin;
    Text_আকার.bottom += TextMargin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    আকার_3.cx = Text_আকার.ডান - Text_আকার.বাম;
    আকার_3.cy = Text_আকার.bottom - Text_আকার.শীর্ষ;
    আকার_3.cx += TextMargin * 2;
    আকার_3.cy += TextMargin * 2;

    // Make dialog wider and shift text over for the icon.
    যদি (icon) {
        আকার_3.cx += IconMargin + IconWidth;
        Text_আকার.বাম += IconMargin + IconWidth;
        Text_আকার.ডান += IconMargin + IconWidth;
    }

    // Ensure the size is wide enough for all of the buttons.
    যদি (আকার_3.cx < (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin) {
        আকার_3.cx = (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    যদি (icon && আকার_3.cy < (LONG)IconMargin * 2 + IconHeight) {
        আকার_3.cy = (LONG)IconMargin * 2 + IconHeight;
    }

    // Add vertical space for the buttons and border.
    আকার_3.cy += ButtonHeight + TextMargin;

    dialog = Create_Dialog_তথ্য(আকার_3.cx, আকার_3.cy, messageboxdata->title);
    যদি (!dialog) {
        ফেরত false;
    }

    যদি (icon && !AddDialogStaticIcon(dialog, IconMargin, IconMargin, IconWidth, IconHeight, icon)) {
        Free_Dialog_তথ্য(dialog);
        ফেরত false;
    }

    যদি (!AddDialogStaticText(dialog, Text_আকার.বাম, Text_আকার.শীর্ষ, Text_আকার.ডান - Text_আকার.বাম, Text_আকার.bottom - Text_আকার.শীর্ষ, messageboxdata->message)) {
        Free_Dialog_তথ্য(dialog);
        ফেরত false;
    }

    // Align the buttons to the right/bottom.
    x = আকার_3.cx - (ButtonWidth + ButtonMargin) * messageboxdata->numbuttons;
    y = আকার_3.cy - ButtonHeight - ButtonMargin;
    জন্য (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        ধ্রুবক অক্ষর *buttontext;
        ধ্রুবক SDL_Message_Box_Button_তথ্য *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        যদি (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_বাম_TO_ডান) {
            sdlButton = &messageboxdata->buttons[i];
        } অন্যথা {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        যদি (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            যদি (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->text);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        যদি (!buttontext || !AddDialogButton(dialog, x, y, ButtonWidth, ButtonHeight, buttontext, IDBUTTONINDEX0 + (পূর্ণসংখ্যা)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_তথ্য(dialog);
            SDL_free(ampescape);
            ফেরত false;
        }

        x += ButtonWidth + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    যদি (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    rc = DialogBoxIndirectParam(ফাঁকা, (DLGTEMPLATE *)dialog->lpDialog, ParentWindow, MessageBoxDialogProc, (LPARAM)messageboxdata);
    যদি (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        ফলাফল = true;
    } অন্যথা যদি (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        ফলাফল = true;
        *buttonID = -1;
    } অন্যথা {
        যদি (rc == 0) {
            SDL_SetError("Invalid parent window handle");
        } অন্যথা যদি (rc == -1) {
            SDL_SetError("The message box encountered an error.");
        } অন্যথা যদি (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_SetError("Invalid message box pointer in dialog procedure");
        } অন্যথা যদি (rc == IDINVALPTRDLGITEM) {
            SDL_SetError("Couldn't find dialog control of the default enter-key button");
        } অন্যথা {
            SDL_SetError("An unknown error occurred");
        }
        ফলাফল = false;
    }

    Free_Dialog_তথ্য(dialog);
    ফেরত ফলাফল;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
প্রকারলেখ HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(ধ্রুবক TASKDIALOGCONFIG *pTaskConfig, পূর্ণসংখ্যা *pnButton, পূর্ণসংখ্যা *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_ShowMessageBox(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID)
{
    HWND ParentWindow = ফাঁকা;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC pTaskDialogIndirect;
    HRESULT hr;
    অক্ষর *ampescape = ফাঁকা;
    size_t ampescapesize = 0;
    পূর্ণসংখ্যা nButton;
    পূর্ণসংখ্যা nCancelButton;
    পূর্ণসংখ্যা i;
    bool ফলাফল = false;

    যদি (SIZE_MAX / আকার(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        ফেরত SDL_OutOfMemory();
    }

    HMODULE hUser32 = GetModuleHandle(TEXT("user32.dll"));
    প্রকারলেখ DPI_AWARENESS_CONTEXT (WINAPI *pfnSetThreadDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    pfnSetThreadDpiAwarenessContext pSetThreadDpiAwarenessContext = (pfnSetThreadDpiAwarenessContext)GetProcAddress(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT previous_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    যদি (pSetThreadDpiAwarenessContext) {
        previous_context = pSetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = LoadLibrary(TEXT("comctl32.dll"));
    যদি (!hComctl32) {
        ফলাফল = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        যাও done;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    pTaskDialogIndirect = (TASKDIALOGINDIRECTPROC)GetProcAddress(hComctl32, "TaskDialogIndirect");
    যদি (!pTaskDialogIndirect) {
        FreeLibrary(hComctl32);
        ফলাফল = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        যাও done;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    যদি (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    wtitle = WIN_UTF8ToStringW(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_আকার = আকার(TASKDIALOGCONFIG);
    TaskConfig.hwndParent = ParentWindow;
    TaskConfig.dwFlags = TDF_আকার_TO_CONTENT;
    TaskConfig.pszWindowTitle = wtitle;
    যদি (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } অন্যথা যদি (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } অন্যথা যদি (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } অন্যথা {
        TaskConfig.pszMainIcon = ফাঁকা;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(আকার(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    জন্য (i = 0; i < messageboxdata->numbuttons; i++) {
        ধ্রুবক অক্ষর *buttontext;
        যদি (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_বাম_TO_ডান) {
            pButton = &pButtons[i];
        } অন্যথা {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        যদি (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } অন্যথা {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].text);
        যদি (!buttontext) {
            পূর্ণসংখ্যা j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            জন্য (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].pszButtonText);
            }
            SDL_free(pButtons);
            ফেরত false;
        }
        pButton->pszButtonText = WIN_UTF8ToStringW(buttontext);
        যদি (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = pTaskDialogIndirect(&TaskConfig, &nButton, ফাঁকা, ফাঁকা);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    জন্য (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].pszButtonText);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    যদি (SUCCEEDED(hr)) {
        যদি (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } অন্যথা যদি (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } অন্যথা {
            *buttonID = -1;
        }
        ফলাফল = true;
    } অন্যথা {
        // We failed showing the Task Dialog, use the old message box!
        ফলাফল = WIN_ShowOldMessageBox(messageboxdata, buttonID);
    }

done:
    যদি (pSetThreadDpiAwarenessContext) {
        pSetThreadDpiAwarenessContext(previous_context);
    }
    ফেরত ফলাফল;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

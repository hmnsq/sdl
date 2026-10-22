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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಯದಿ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef HAVE_LIMITS_H
#ಅನ್ತರ್ಭಾವ <limits.h>
#endif
#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"

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

ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT ಸಂದೇಶ, WPARAM wParam, LPARAM lParam, LONG_PTR lpRefData);

ಗಣನಾ _TASKDIALOG_FLAGS
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
    TDF_SIZE_TO_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ _TASKDIALOG_MESSAGES
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

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ _TASKDIALOG_NOTIFICATIONS
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

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#define TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#define TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#define TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#define TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

ಗಣನಾ _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#pragma pack(ತಳ್ಳು, 1)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _TASKDIALOG_BUTTON
{
    ಪೂರ್ಣಾಙ್ಕ nButtonID;
    PCWSTR pszButtonText;
} TASKDIALOG_BUTTON;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ _TASKDIALOGCONFIG
{
    UINT cbSize;
    HWND hwndParent;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR pszWindowTitle;                          // string or MAKEINTRESOURCE()
    ಸಙ್ಘ
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    ಧ್ರುವ TASKDIALOG_BUTTON *pButtons;
    ಪೂರ್ಣಾಙ್ಕ nDefaultButton;
    UINT cRadioButtons;
    ಧ್ರುವ TASKDIALOG_BUTTON *pRadioButtons;
    ಪೂರ್ಣಾಙ್ಕ nDefaultRadioButton;
    PCWSTR pszVerificationText;
    PCWSTR pszExpandedInformation;
    PCWSTR pszExpandedControlText;
    PCWSTR pszCollapsedControlText;
    ಸಙ್ಘ
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lpCallbackData;
    UINT cxWidth; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD c_Dlg_ವಸ್ತುಗಳು;
    short x;
    short y;
    short cx;
    short cy;
} DLGTEMPLATEEX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
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

#pragma pack(ತೆಗೆ)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    DLGTEMPLATEEX *lpDialog;
    ಶೂನ್ಯ *data;
    size_t size;
    size_t used;
    WORD numbuttons;
} WIN_DialogData;

ಸ್ಥಿರ bool GetButtonIndex(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, SDL_MessageBoxButtonFlags flags, size_t *i)
{
    ಪ್ರತಿ (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        ಯದಿ (messageboxdata->buttons[*i].flags & flags) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ INT_PTR CALLBACK MessageBoxDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    ಧ್ರುವ SDL_MessageBoxData *messageboxdata;
    size_t buttonindex;

    ವಿಕಲ್ಪ (iMessage) {
    ಪಕ್ಷ WM_INITDIALOG:
        ಯದಿ (lParam == 0) {
            EndDialog(hDlg, IDINVALPTRINIT);
            ಪ್ರತ್ಯಾಗಮ TRUE;
        }
        messageboxdata = (ಧ್ರುವ SDL_MessageBoxData *)lParam;
        SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);

        ಯದಿ (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = GetDlgItem(hDlg, (ಪೂರ್ಣಾಙ್ಕ)(IDBUTTONINDEX0 + buttonindex));
            ಯದಿ (!buttonctl) {
                EndDialog(hDlg, IDINVALPTRDLGITEM);
            }
            PostMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } ಅನ್ಯಥಾ {
            // Give the focus to the dialog window instead
            SetFocus(hDlg);
        }
        ಪ್ರತ್ಯಾಗಮ FALSE;
    ಪಕ್ಷ WM_SETFOCUS:
        messageboxdata = (ಧ್ರುವ SDL_MessageBoxData *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        ಯದಿ (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRSETFOCUS);
            ಪ್ರತ್ಯಾಗಮ TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        ಯದಿ (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            ಪ್ರತ್ಯಾಗಮ FALSE;
        }
        ಪ್ರತ್ಯಾಗಮ TRUE;
    ಪಕ್ಷ WM_COMMAND:
        messageboxdata = (ಧ್ರುವ SDL_MessageBoxData *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        ಯದಿ (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRCOMMAND);
            ಪ್ರತ್ಯಾಗಮ TRUE;
        }

        // Return the ID of the button that was pushed
        ಯದಿ (wParam == IDOK) {
            ಯದಿ (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } ಅನ್ಯಥಾ ಯದಿ (wParam == IDCANCEL) {
            ಯದಿ (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } ಅನ್ಯಥಾ {
                // Closing of window was requested by user or system. It would be rude not to comply.
                EndDialog(hDlg, IDCLOSED);
            }
        } ಅನ್ಯಥಾ ಯದಿ (wParam >= IDBUTTONINDEX0 && (ಪೂರ್ಣಾಙ್ಕ)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            EndDialog(hDlg, wParam);
        }
        ಪ್ರತ್ಯಾಗಮ TRUE;

    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ FALSE;
}

ಸ್ಥಿರ bool ExpandDialogSpace(WIN_DialogData *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    ಧ್ರುವ size_t sizestep = 0x10000;
    size_t size = dialog->size;

    ಯದಿ (size == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        size = 0x1000;
        ಯದಿ (SIZE_MAX - sizestep < space) {
            size = space;
        } ಅನ್ಯಥಾ ಯದಿ (space > size) {
            size = (space + sizestep) & ~(sizestep - 1);
        }
    } ಅನ್ಯಥಾ ಯದಿ (SIZE_MAX - dialog->used < space) {
        SDL_OutOfMemory();
        ಪ್ರತ್ಯಾಗಮ false;
    } ಅನ್ಯಥಾ ಯದಿ (SIZE_MAX - (dialog->used + space) < sizestep) {
        // Close to the maximum.
        size = dialog->used + space;
    } ಅನ್ಯಥಾ ಯದಿ (size < dialog->used + space) {
        // Round up to the next 64 KiB block.
        size = dialog->used + space;
        size += sizestep - size % sizestep;
    }

    ಯದಿ (size > dialog->size) {
        ಶೂನ್ಯ *data = SDL_realloc(dialog->data, size);
        ಯದಿ (!data) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        dialog->data = data;
        dialog->size = size;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->data;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool AlignDialogData(WIN_DialogData *dialog, size_t size)
{
    size_t padding = (dialog->used % size);

    ಯದಿ (!ExpandDialogSpace(dialog, padding)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    dialog->used += padding;

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool AddDialogData(WIN_DialogData *dialog, ಧ್ರುವ ಶೂನ್ಯ *data, size_t size)
{
    ಯದಿ (!ExpandDialogSpace(dialog, size)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    SDL_memcpy((Uint8 *)dialog->data + dialog->used, data, size);
    dialog->used += size;

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool AddDialogString(WIN_DialogData *dialog, ಧ್ರುವ ವರ್ಣ *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t ಎಣಿಕೆ;
    bool status;

    ಯದಿ (!string) {
        string = "";
    }

    wstring = WIN_UTF8ToStringW(string);
    ಯದಿ (!wstring) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Find out how many characters we have, including null terminator
    ಎಣಿಕೆ = 0;
    ಪ್ರತಿ (p = wstring; *p; ++p) {
        ++ಎಣಿಕೆ;
    }
    ++ಎಣಿಕೆ;

    status = AddDialogData(dialog, wstring, ಎಣಿಕೆ * ಪರಿಮಾಣ(WCHAR));
    SDL_free(wstring);
    ಪ್ರತ್ಯಾಗಮ status;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ s_BaseUnitsX;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ s_BaseUnitsY;
ಸ್ಥಿರ ಶೂನ್ಯ Vec2ToDLU(short *x, short *y)
{
    SDL_assert(s_BaseUnitsX != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (short)MulDiv(*x, 4, s_BaseUnitsX);
    *y = (short)MulDiv(*y, 8, s_BaseUnitsY);
}

ಸ್ಥಿರ bool AddDialogControl(WIN_DialogData *dialog, WORD type, DWORD style, DWORD exStyle, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ id, ಧ್ರುವ ವರ್ಣ *caption, WORD ordinal)
{
    DLGITEMTEMPLATEEX item;
    WORD marker = 0xFFFF;
    WORD extraData = 0;

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

    ಯದಿ (!AlignDialogData(dialog, ಪರಿಮಾಣ(DWORD))) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (!AddDialogData(dialog, &item, ಪರಿಮಾಣ(item))) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (!AddDialogData(dialog, &marker, ಪರಿಮಾಣ(marker))) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (!AddDialogData(dialog, &type, ಪರಿಮಾಣ(type))) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        ಯದಿ (!AddDialogString(dialog, caption)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!AddDialogData(dialog, &marker, ಪರಿಮಾಣ(marker))) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ (!AddDialogData(dialog, &ordinal, ಪರಿಮಾಣ(ordinal))) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಯದಿ (!AddDialogData(dialog, &extraData, ಪರಿಮಾಣ(extraData))) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_ವಸ್ತುಗಳು;

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool AddDialogStaticText(WIN_DialogData *dialog, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಧ್ರುವ ವರ್ಣ *text)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_ಎಡ | SS_NOPREFIX | SS_EDITCONTROL | WS_GROUP;
    ಪ್ರತ್ಯಾಗಮ AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, text, 0);
}

ಸ್ಥಿರ bool AddDialogStaticIcon(WIN_DialogData *dialog, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_ICON | WS_GROUP;
    ಪ್ರತ್ಯಾಗಮ AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, ರಿಕ್ತ, ordinal);
}

ಸ್ಥಿರ bool AddDialogButton(WIN_DialogData *dialog, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಧ್ರುವ ವರ್ಣ *text, ಪೂರ್ಣಾಙ್ಕ id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP;
    ಯದಿ (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } ಅನ್ಯಥಾ {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    ಯದಿ (dialog->numbuttons == 0) {
        style |= WS_GROUP;
    }
    ಪ್ರತ್ಯಾಗಮ AddDialogControl(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, text, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ FreeDialogData(WIN_DialogData *dialog)
{
    SDL_free(dialog->data);
    SDL_free(dialog);
}

ಸ್ಥಿರ WIN_DialogData *CreateDialogData(ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಧ್ರುವ ವರ್ಣ *caption)
{
    WIN_DialogData *dialog;
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

    dialog = (WIN_DialogData *)SDL_calloc(1, ಪರಿಮಾಣ(*dialog));
    ಯದಿ (!dialog) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!AddDialogData(dialog, &dialogTemplate, ಪರಿಮಾಣ(dialogTemplate))) {
        FreeDialogData(dialog);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // No menu
    WordToPass = 0;
    ಯದಿ (!AddDialogData(dialog, &WordToPass, 2)) {
        FreeDialogData(dialog);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // No custom class
    ಯದಿ (!AddDialogData(dialog, &WordToPass, 2)) {
        FreeDialogData(dialog);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // title
    ಯದಿ (!AddDialogString(dialog, caption)) {
        FreeDialogData(dialog);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ToPass;

        NONCLIENTMETRICSA NCM;
        NCM.cbSize = ಪರಿಮಾಣ(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(ರಿಕ್ತ);
            ಪೂರ್ಣಾಙ್ಕ LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            ಯದಿ (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            WordToPass = (WORD)(-72 * NCM.lfMessageFont.lfHeight / LogicalPixelsY);
            ReleaseDC(ರಿಕ್ತ, ScreenDC);
        }

        ಯದಿ (!AddDialogData(dialog, &WordToPass, 2)) {
            FreeDialogData(dialog);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // Font weight
        WordToPass = (WORD)NCM.lfMessageFont.lfWeight;
        ಯದಿ (!AddDialogData(dialog, &WordToPass, 2)) {
            FreeDialogData(dialog);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // italic?
        ToPass = NCM.lfMessageFont.lfItalic;
        ಯದಿ (!AddDialogData(dialog, &ToPass, 1)) {
            FreeDialogData(dialog);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // charset?
        ToPass = NCM.lfMessageFont.lfCharSet;
        ಯದಿ (!AddDialogData(dialog, &ToPass, 1)) {
            FreeDialogData(dialog);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // font typeface.
        ಯದಿ (!AddDialogString(dialog, NCM.lfMessageFont.lfFaceName)) {
            FreeDialogData(dialog);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ dialog;
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
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *EscapeAmpersands(ವರ್ಣ **dst, size_t *dstlen, ಧ್ರುವ ವರ್ಣ *src)
{
    ವರ್ಣ *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    ಯದಿ (!src) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯಾವತ್ (src[srclen]) {
        ಯದಿ (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    ಯದಿ (ampcount == 0) {
        // Nothing to do.
        ಪ್ರತ್ಯಾಗಮ src;
    }
    ಯದಿ (SIZE_MAX - srclen < ampcount) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        ಯದಿ (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = ರಿಕ್ತ;
        newdst = (ವರ್ಣ *)SDL_malloc(*dstlen);
        ಯದಿ (!newdst) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        *dst = newdst;
    } ಅನ್ಯಥಾ {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    ಯಾವತ್ (srclen--) {
        ಯದಿ (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    ಪ್ರತ್ಯಾಗಮ *dst;
}

ಸ್ಥಿರ ಭಿನ್ನ WIN_GetContentScale(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ dpi = 0;

#ಯದಿ 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    ಯದಿ (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (ಪೂರ್ಣಾಙ್ಕ)hdpi_uint;
    }
#endif
    ಯದಿ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ರಿಕ್ತ);
        ಯದಿ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ರಿಕ್ತ, hdc);
        }
    }
    ಯದಿ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ಪ್ರತ್ಯಾಗಮ dpi / (ಭಿನ್ನ)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
ಸ್ಥಿರ bool WIN_ShowOldMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
    WIN_DialogData *dialog;
    ಪೂರ್ಣಾಙ್ಕ i, x, y;
    HFONT DialogFont;
    SIZE Size;
    RECT TextSize;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    ವರ್ಣ *ampescape = ರಿಕ್ತ;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool result;

    HWND ParentWindow = ರಿಕ್ತ;

    ಧ್ರುವ ಭಿನ್ನ scale = WIN_GetContentScale();
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ ButtonWidth = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(88 * scale);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ ButtonHeight = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(26 * scale);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ TextMargin = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(16 * scale);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ ButtonMargin = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(12 * scale);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ IconWidth = GetSystemMetrics(SM_CXICON);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ IconHeight = GetSystemMetrics(SM_CYICON);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ IconMargin = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(20 * scale);

    ಯದಿ (messageboxdata->numbuttons > MAX_BUTTONS) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    ವಿಕಲ್ಪ (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ಪಕ್ಷ SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        ಭಙ್ಗ;
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
        NCM.cbSize = ಪರಿಮಾಣ(NCM);
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
            SIZE extent;
            GetTextExtentPoint32A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_BaseUnitsX = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_BaseUnitsY = TM.tmHeight;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    SDL_zero(TextSize);
    DrawTextW(FontDC, wmessage, -1, &TextSize, DT_CALCRECT | DT_ಎಡ | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    TextSize.ಎಡ += TextMargin;
    TextSize.ಬಲ += TextMargin + 2;
    TextSize.ತುದಿ += TextMargin;
    TextSize.bottom += TextMargin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    Size.cx = TextSize.ಬಲ - TextSize.ಎಡ;
    Size.cy = TextSize.bottom - TextSize.ತುದಿ;
    Size.cx += TextMargin * 2;
    Size.cy += TextMargin * 2;

    // Make dialog wider and shift text over for the icon.
    ಯದಿ (icon) {
        Size.cx += IconMargin + IconWidth;
        TextSize.ಎಡ += IconMargin + IconWidth;
        TextSize.ಬಲ += IconMargin + IconWidth;
    }

    // Ensure the size is wide enough for all of the buttons.
    ಯದಿ (Size.cx < (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin) {
        Size.cx = (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    ಯದಿ (icon && Size.cy < (LONG)IconMargin * 2 + IconHeight) {
        Size.cy = (LONG)IconMargin * 2 + IconHeight;
    }

    // Add vertical space for the buttons and border.
    Size.cy += ButtonHeight + TextMargin;

    dialog = CreateDialogData(Size.cx, Size.cy, messageboxdata->title);
    ಯದಿ (!dialog) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (icon && !AddDialogStaticIcon(dialog, IconMargin, IconMargin, IconWidth, IconHeight, icon)) {
        FreeDialogData(dialog);
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!AddDialogStaticText(dialog, TextSize.ಎಡ, TextSize.ತುದಿ, TextSize.ಬಲ - TextSize.ಎಡ, TextSize.bottom - TextSize.ತುದಿ, messageboxdata->message)) {
        FreeDialogData(dialog);
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Align the buttons to the right/bottom.
    x = Size.cx - (ButtonWidth + ButtonMargin) * messageboxdata->numbuttons;
    y = Size.cy - ButtonHeight - ButtonMargin;
    ಪ್ರತಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        ಧ್ರುವ ವರ್ಣ *buttontext;
        ಧ್ರುವ SDL_MessageBoxButtonData *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        ಯದಿ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಎಡ_TO_ಬಲ) {
            sdlButton = &messageboxdata->buttons[i];
        } ಅನ್ಯಥಾ {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        ಯದಿ (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            ಯದಿ (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->text);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        ಯದಿ (!buttontext || !AddDialogButton(dialog, x, y, ButtonWidth, ButtonHeight, buttontext, IDBUTTONINDEX0 + (ಪೂರ್ಣಾಙ್ಕ)(sdlButton - messageboxdata->buttons), isdefault)) {
            FreeDialogData(dialog);
            SDL_free(ampescape);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        x += ButtonWidth + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    ಯದಿ (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    rc = DialogBoxIndirectParam(ರಿಕ್ತ, (DLGTEMPLATE *)dialog->lpDialog, ParentWindow, MessageBoxDialogProc, (LPARAM)messageboxdata);
    ಯದಿ (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        result = true;
    } ಅನ್ಯಥಾ ಯದಿ (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        result = true;
        *buttonID = -1;
    } ಅನ್ಯಥಾ {
        ಯದಿ (rc == 0) {
            SDL_SetError("Invalid parent window handle");
        } ಅನ್ಯಥಾ ಯದಿ (rc == -1) {
            SDL_SetError("The message box encountered an error.");
        } ಅನ್ಯಥಾ ಯದಿ (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_SetError("Invalid message box pointer in dialog procedure");
        } ಅನ್ಯಥಾ ಯದಿ (rc == IDINVALPTRDLGITEM) {
            SDL_SetError("Couldn't find dialog control of the default enter-key button");
        } ಅನ್ಯಥಾ {
            SDL_SetError("An unknown error occurred");
        }
        result = false;
    }

    FreeDialogData(dialog);
    ಪ್ರತ್ಯಾಗಮ result;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
ಪ್ರಕಾರನಿರ್ದೇಶ HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(ಧ್ರುವ TASKDIALOGCONFIG *pTaskConfig, ಪೂರ್ಣಾಙ್ಕ *pnButton, ಪೂರ್ಣಾಙ್ಕ *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_ShowMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
    HWND ParentWindow = ರಿಕ್ತ;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC pTaskDialogIndirect;
    HRESULT hr;
    ವರ್ಣ *ampescape = ರಿಕ್ತ;
    size_t ampescapesize = 0;
    ಪೂರ್ಣಾಙ್ಕ nButton;
    ಪೂರ್ಣಾಙ್ಕ nCancelButton;
    ಪೂರ್ಣಾಙ್ಕ i;
    bool result = false;

    ಯದಿ (SIZE_MAX / ಪರಿಮಾಣ(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        ಪ್ರತ್ಯಾಗಮ SDL_OutOfMemory();
    }

    HMODULE hUser32 = GetModuleHandle(TEXT("user32.dll"));
    ಪ್ರಕಾರನಿರ್ದೇಶ DPI_AWARENESS_CONTEXT (WINAPI *pfnSetThreadDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    pfnSetThreadDpiAwarenessContext pSetThreadDpiAwarenessContext = (pfnSetThreadDpiAwarenessContext)GetProcAddress(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT previous_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    ಯದಿ (pSetThreadDpiAwarenessContext) {
        previous_context = pSetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = LoadLibrary(TEXT("comctl32.dll"));
    ಯದಿ (!hComctl32) {
        result = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        ಗಚ್ಛ done;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    pTaskDialogIndirect = (TASKDIALOGINDIRECTPROC)GetProcAddress(hComctl32, "TaskDialogIndirect");
    ಯದಿ (!pTaskDialogIndirect) {
        FreeLibrary(hComctl32);
        result = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        ಗಚ್ಛ done;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    ಯದಿ (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    wtitle = WIN_UTF8ToStringW(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cbSize = ಪರಿಮಾಣ(TASKDIALOGCONFIG);
    TaskConfig.hwndParent = ParentWindow;
    TaskConfig.dwFlags = TDF_SIZE_TO_CONTENT;
    TaskConfig.pszWindowTitle = wtitle;
    ಯದಿ (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } ಅನ್ಯಥಾ ಯದಿ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } ಅನ್ಯಥಾ ಯದಿ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } ಅನ್ಯಥಾ {
        TaskConfig.pszMainIcon = ರಿಕ್ತ;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(ಪರಿಮಾಣ(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    ಪ್ರತಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        ಧ್ರುವ ವರ್ಣ *buttontext;
        ಯದಿ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಎಡ_TO_ಬಲ) {
            pButton = &pButtons[i];
        } ಅನ್ಯಥಾ {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        ಯದಿ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } ಅನ್ಯಥಾ {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].text);
        ಯದಿ (!buttontext) {
            ಪೂರ್ಣಾಙ್ಕ j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            ಪ್ರತಿ (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].pszButtonText);
            }
            SDL_free(pButtons);
            ಪ್ರತ್ಯಾಗಮ false;
        }
        pButton->pszButtonText = WIN_UTF8ToStringW(buttontext);
        ಯದಿ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = pTaskDialogIndirect(&TaskConfig, &nButton, ರಿಕ್ತ, ರಿಕ್ತ);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    ಪ್ರತಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].pszButtonText);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    ಯದಿ (SUCCEEDED(hr)) {
        ಯದಿ (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } ಅನ್ಯಥಾ ಯದಿ (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } ಅನ್ಯಥಾ {
            *buttonID = -1;
        }
        result = true;
    } ಅನ್ಯಥಾ {
        // We failed showing the Task Dialog, use the old message box!
        result = WIN_ShowOldMessageBox(messageboxdata, buttonID);
    }

done:
    ಯದಿ (pSetThreadDpiAwarenessContext) {
        pSetThreadDpiAwarenessContext(previous_context);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

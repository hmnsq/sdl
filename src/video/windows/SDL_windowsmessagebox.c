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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIMITS_H
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SIZE_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು SIZE_MAX ((size_t)-1)
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h"

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SS_EDITCONTROL
#ವ್ಯಾಖ್ಯಾನಿಸು SS_EDITCONTROL 0x2000
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ IDOK
#ವ್ಯಾಖ್ಯಾನಿಸು IDOK 1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ IDCANCEL
#ವ್ಯಾಖ್ಯಾನಿಸು IDCANCEL 2
#ಆದರೆ_ಅಂತ್ಯ

// Custom dialog return codes
#ವ್ಯಾಖ್ಯಾನಿಸು IDCLOSED           20
#ವ್ಯಾಖ್ಯಾನಿಸು IDINVALPTRINIT     50
#ವ್ಯಾಖ್ಯಾನಿಸು IDINVALPTRCOMMAND  51
#ವ್ಯಾಖ್ಯಾನಿಸು IDINVALPTRSETFOCUS 52
#ವ್ಯಾಖ್ಯಾನಿಸು IDINVALPTRDLGITEM  53
// First button ID
#ವ್ಯಾಖ್ಯಾನಿಸು IDBUTTONINDEX0 100

#ವ್ಯಾಖ್ಯಾನಿಸು DLGITEMTYPEBUTTON 0x0080
#ವ್ಯಾಖ್ಯಾನಿಸು DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT ಸಂದೇಶ_2, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_ದತ್ತಾಂಶ);

ಎಣಿಕೆ _TASKDIALOG_FLAGS
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
    TDF_SHOW_ಪ್ರಗತಿ_BAR = 0x0200,
    TDF_SHOW_MARQUEE_ಪ್ರಗತಿ_BAR = 0x0400,
    TDF_CALLBACK_TIMER = 0x0800,
    TDF_POSITION_RELATIVE_ಗಮ್ಯ_ಕಿಟಕಿ = 0x1000,
    TDF_RTL_LAYOUT = 0x2000,
    TDF_NO_DEFAULT_RADIO_BUTTON = 0x4000,
    TDF_CAN_BE_MINIMIZED = 0x8000,
    // #if (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_NO_ಗಣ_FOREGROUND = 0x00010000, // Don't call SetForegroundWindow() when activating the dialog
                                        // #endif // (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_ಗಾತ್ರ_ಗಮ್ಯ_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ _TASKDIALOG_MESSAGES
{
    TDM_NAVIGATE_ಪುಟ = WM_USER + 101,
    TDM_CLICK_BUTTON = WM_USER + 102,                        // wParam = Button ID
    TDM_ಗಣ_MARQUEE_ಪ್ರಗತಿ_BAR = WM_USER + 103,            // wParam = 0 (nonMarque) wParam != 0 (Marquee)
    TDM_ಗಣ_ಪ್ರಗತಿ_BAR_STATE = WM_USER + 104,              // wParam = new progress state
    TDM_ಗಣ_ಪ್ರಗತಿ_BAR_RANGE = WM_USER + 105,              // lParam = MAKELPARAM(nMinRange, nMaxRange)
    TDM_ಗಣ_ಪ್ರಗತಿ_BAR_POS = WM_USER + 106,                // wParam = new position
    TDM_ಗಣ_ಪ್ರಗತಿ_BAR_MARQUEE = WM_USER + 107,            // wParam = 0 (stop marquee), wParam != 0 (start marquee), lparam = speed (milliseconds between repaints)
    TDM_ಗಣ_ELEMENT_ಪಠ್ಯ = WM_USER + 108,                    // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_CLICK_RADIO_BUTTON = WM_USER + 110,                  // wParam = Radio Button ID
    TDM_ENABLE_BUTTON = WM_USER + 111,                       // lParam = 0 (disable), lParam != 0 (enable), wParam = Button ID
    TDM_ENABLE_RADIO_BUTTON = WM_USER + 112,                 // lParam = 0 (disable), lParam != 0 (enable), wParam = Radio Button ID
    TDM_CLICK_VERIFICATION = WM_USER + 113,                  // wParam = 0 (unchecked), 1 (checked), lParam = 1 (set key focus)
    TDM_UPDATE_ELEMENT_ಪಠ್ಯ = WM_USER + 114,                 // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_ಗಣ_BUTTON_ELEVATION_REQUIRED_STATE = WM_USER + 115, // wParam = Button ID, lParam = 0 (elevation not required), lParam != 0 (elevation required)
    TDM_UPDATE_ICON = WM_USER + 116                          // wParam = icon element (TASKDIALOG_ICON_ELEMENTS), lParam = new icon (hIcon if TDF_USE_HICON_* was set, PCWSTR otherwise)
} TASKDIALOG_MESSAGES;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ _TASKDIALOG_NOTIFICATIONS
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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#ವ್ಯಾಖ್ಯಾನಿಸು TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#ವ್ಯಾಖ್ಯಾನಿಸು TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#ವ್ಯಾಖ್ಯಾನಿಸು TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#ವ್ಯಾಖ್ಯಾನಿಸು TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

ಎಣಿಕೆ _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#ಸೂಚನೆ pack(ತಳ್ಳು, 1)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _TASKDIALOG_BUTTON
{
    ಪೂರ್ಣಾಂಕ nButtonID;
    PCWSTR psz_Button_ಪಠ್ಯ;
} TASKDIALOG_BUTTON;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ _TASKDIALOGCONFIG
{
    UINT cb_ಗಾತ್ರ;
    HWND hwnd_ಪೋಷಕ;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR psz_ಕಿಟಕಿ_Title;                          // string or MAKEINTRESOURCE()
    ಒಕ್ಕೂಟ
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    ಸ್ಥಿರಾಂಕ TASKDIALOG_BUTTON *pButtons;
    ಪೂರ್ಣಾಂಕ nDefaultButton;
    UINT cRadioButtons;
    ಸ್ಥಿರಾಂಕ TASKDIALOG_BUTTON *pRadioButtons;
    ಪೂರ್ಣಾಂಕ nDefaultRadioButton;
    PCWSTR psz_Verification_ಪಠ್ಯ;
    PCWSTR pszExpandedInformation;
    PCWSTR psz_Expanded_Control_ಪಠ್ಯ;
    PCWSTR psz_Collapsed_Control_ಪಠ್ಯ;
    ಒಕ್ಕೂಟ
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lp_Callback_ದತ್ತಾಂಶ;
    UINT cx_ಅಗಲ; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಶಬ್ದ dlgVer;
    ಶಬ್ದ signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    ಶಬ್ದ c_Dlg_ವಸ್ತುಗಳು;
    ಗಿಡ್ಡ x;
    ಗಿಡ್ಡ y;
    ಗಿಡ್ಡ cx;
    ಗಿಡ್ಡ cy;
} DLGTEMPLATEEX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    ಗಿಡ್ಡ x;
    ಗಿಡ್ಡ y;
    ಗಿಡ್ಡ cx;
    ಗಿಡ್ಡ cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#ಸೂಚನೆ pack(ತೆಗೆ)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    DLGTEMPLATEEX *lpDialog;
    ಶೂನ್ಯ *ದತ್ತಾಂಶ;
    size_t ಗಾತ್ರ_2;
    size_t ಬಳಸಿದ;
    ಶಬ್ದ numbuttons;
} WIN_Dialog_ದತ್ತಾಂಶ;

ಸ್ಥಿರ bool Get_Button_ಸೂಚ್ಯಂಕ(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, SDL_ಸಂದೇಶ_Box_Button_Flags flags, size_t *i)
{
    ಗಾಗಿ (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        ಆದರೆ (messageboxdata->buttons[*i].flags & flags) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ INT_PTR CALLBACK ಸಂದೇಶ_Box_Dialog_Proc(HWND hDlg, UINT i_ಸಂದೇಶ, WPARAM wParam, LPARAM lParam)
{
    ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata;
    size_t buttonindex;

    ಆಯ್ಕೆ (i_ಸಂದೇಶ) {
    ಸ್ಥಿತಿ WM_INITDIALOG:
        ಆದರೆ (lParam == 0) {
            ಕೊನೆ_Dialog(hDlg, IDINVALPTRINIT);
            ಹಿಂತಿರುಗಿ TRUE;
        }
        messageboxdata = (ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *)lParam;
        ಗಣ_ಕಿಟಕಿ_Long_Ptr(hDlg, GWLP_USERDATA, lParam);

        ಆದರೆ (Get_Button_ಸೂಚ್ಯಂಕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = Get_Dlg_ಅಂಶ(hDlg, (ಪೂರ್ಣಾಂಕ)(IDBUTTONINDEX0 + buttonindex));
            ಆದರೆ (!buttonctl) {
                ಕೊನೆ_Dialog(hDlg, IDINVALPTRDLGITEM);
            }
            Post_ಸಂದೇಶ(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Give the focus to the dialog window instead
            ಗಣ_Focus(hDlg);
        }
        ಹಿಂತಿರುಗಿ FALSE;
    ಸ್ಥಿತಿ WM_SETFOCUS:
        messageboxdata = (ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *)Get_ಕಿಟಕಿ_Long_Ptr(hDlg, GWLP_USERDATA);
        ಆದರೆ (!messageboxdata) {
            ಕೊನೆ_Dialog(hDlg, IDINVALPTRSETFOCUS);
            ಹಿಂತಿರುಗಿ TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        ಆದರೆ (Get_Button_ಸೂಚ್ಯಂಕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            ಹಿಂತಿರುಗಿ FALSE;
        }
        ಹಿಂತಿರುಗಿ TRUE;
    ಸ್ಥಿತಿ WM_COMMAND:
        messageboxdata = (ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *)Get_ಕಿಟಕಿ_Long_Ptr(hDlg, GWLP_USERDATA);
        ಆದರೆ (!messageboxdata) {
            ಕೊನೆ_Dialog(hDlg, IDINVALPTRCOMMAND);
            ಹಿಂತಿರುಗಿ TRUE;
        }

        // Return the ID of the button that was pushed
        ಆದರೆ (wParam == IDOK) {
            ಆದರೆ (Get_Button_ಸೂಚ್ಯಂಕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                ಕೊನೆ_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wParam == IDCANCEL) {
            ಆದರೆ (Get_Button_ಸೂಚ್ಯಂಕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                ಕೊನೆ_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Closing of window was requested by user or system. It would be rude not to comply.
                ಕೊನೆ_Dialog(hDlg, IDCLOSED);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wParam >= IDBUTTONINDEX0 && (ಪೂರ್ಣಾಂಕ)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            ಕೊನೆ_Dialog(hDlg, wParam);
        }
        ಹಿಂತಿರುಗಿ TRUE;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ FALSE;
}

ಸ್ಥಿರ bool ExpandDialogSpace(WIN_Dialog_ದತ್ತಾಂಶ *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    ಸ್ಥಿರಾಂಕ size_t sizestep = 0x10000;
    size_t ಗಾತ್ರ_2 = dialog->ಗಾತ್ರ_2;

    ಆದರೆ (ಗಾತ್ರ_2 == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        ಗಾತ್ರ_2 = 0x1000;
        ಆದರೆ (SIZE_MAX - sizestep < space) {
            ಗಾತ್ರ_2 = space;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (space > ಗಾತ್ರ_2) {
            ಗಾತ್ರ_2 = (space + sizestep) & ~(sizestep - 1);
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SIZE_MAX - dialog->ಬಳಸಿದ < space) {
        SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        ಹಿಂತಿರುಗಿ false;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SIZE_MAX - (dialog->ಬಳಸಿದ + space) < sizestep) {
        // Close to the maximum.
        ಗಾತ್ರ_2 = dialog->ಬಳಸಿದ + space;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಗಾತ್ರ_2 < dialog->ಬಳಸಿದ + space) {
        // Round up to the next 64 KiB block.
        ಗಾತ್ರ_2 = dialog->ಬಳಸಿದ + space;
        ಗಾತ್ರ_2 += sizestep - ಗಾತ್ರ_2 % sizestep;
    }

    ಆದರೆ (ಗಾತ್ರ_2 > dialog->ಗಾತ್ರ_2) {
        ಶೂನ್ಯ *ದತ್ತಾಂಶ = SDL_realloc(dialog->ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
        ಆದರೆ (!ದತ್ತಾಂಶ) {
            ಹಿಂತಿರುಗಿ false;
        }
        dialog->ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;
        dialog->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->ದತ್ತಾಂಶ;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Align_Dialog_ದತ್ತಾಂಶ(WIN_Dialog_ದತ್ತಾಂಶ *dialog, size_t ಗಾತ್ರ_2)
{
    size_t padding = (dialog->ಬಳಸಿದ % ಗಾತ್ರ_2);

    ಆದರೆ (!ExpandDialogSpace(dialog, padding)) {
        ಹಿಂತಿರುಗಿ false;
    }

    dialog->ಬಳಸಿದ += padding;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(WIN_Dialog_ದತ್ತಾಂಶ *dialog, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ, size_t ಗಾತ್ರ_2)
{
    ಆದರೆ (!ExpandDialogSpace(dialog, ಗಾತ್ರ_2)) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_memcpy((Uint8 *)dialog->ದತ್ತಾಂಶ + dialog->ಬಳಸಿದ, ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
    dialog->ಬಳಸಿದ += ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool ಕೂಡಿಸು_Dialog_String(WIN_Dialog_ದತ್ತಾಂಶ *dialog, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t ಎಣಿಕೆ_2;
    bool ಸ್ಥಿತಿ_2;

    ಆದರೆ (!string) {
        string = "";
    }

    wstring = WIN_UTF8_ಗಮ್ಯ_String_W(string);
    ಆದರೆ (!wstring) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Find out how many characters we have, including null terminator
    ಎಣಿಕೆ_2 = 0;
    ಗಾಗಿ (p = wstring; *p; ++p) {
        ++ಎಣಿಕೆ_2;
    }
    ++ಎಣಿಕೆ_2;

    ಸ್ಥಿತಿ_2 = ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, wstring, ಎಣಿಕೆ_2 * ಗಾತ್ರ(WCHAR));
    SDL_free(wstring);
    ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ s_ತಳ_Units_X;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ s_ತಳ_Units_Y;
ಸ್ಥಿರ ಶೂನ್ಯ Vec2_ಗಮ್ಯ_DLU(ಗಿಡ್ಡ *x, ಗಿಡ್ಡ *y)
{
    SDL_assert(s_ತಳ_Units_X != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (ಗಿಡ್ಡ)MulDiv(*x, 4, s_ತಳ_Units_X);
    *y = (ಗಿಡ್ಡ)MulDiv(*y, 8, s_ತಳ_Units_Y);
}

ಸ್ಥಿರ bool ಕೂಡಿಸು_Dialog_Control(WIN_Dialog_ದತ್ತಾಂಶ *dialog, ಶಬ್ದ type, DWORD style, DWORD exStyle, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ id, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *caption, ಶಬ್ದ ordinal)
{
    DLGITEMTEMPLATEEX ಅಂಶ;
    ಶಬ್ದ marker = 0xFFFF;
    ಶಬ್ದ extra_ದತ್ತಾಂಶ = 0;

    SDL_zero(ಅಂಶ);
    ಅಂಶ.style = style;
    ಅಂಶ.exStyle = exStyle;
    ಅಂಶ.x = (ಗಿಡ್ಡ)x;
    ಅಂಶ.y = (ಗಿಡ್ಡ)y;
    ಅಂಶ.cx = (ಗಿಡ್ಡ)w;
    ಅಂಶ.cy = (ಗಿಡ್ಡ)h;
    ಅಂಶ.id = id;

    Vec2_ಗಮ್ಯ_DLU(&ಅಂಶ.x, &ಅಂಶ.y);
    Vec2_ಗಮ್ಯ_DLU(&ಅಂಶ.cx, &ಅಂಶ.cy);

    ಆದರೆ (!Align_Dialog_ದತ್ತಾಂಶ(dialog, ಗಾತ್ರ(DWORD))) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಅಂಶ, ಗಾತ್ರ(ಅಂಶ))) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &marker, ಗಾತ್ರ(marker))) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &type, ಗಾತ್ರ(type))) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_String(dialog, caption)) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &marker, ಗಾತ್ರ(marker))) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ordinal, ಗಾತ್ರ(ordinal))) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &extra_ದತ್ತಾಂಶ, ಗಾತ್ರ(extra_ದತ್ತಾಂಶ))) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_ವಸ್ತುಗಳು;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool ಕೂಡಿಸು_Dialog_Static_ಪಠ್ಯ(WIN_Dialog_ದತ್ತಾಂಶ *dialog, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    DWORD style = WS_VISIBLE | WS_ಮಗು | SS_ಎಡ | SS_NOPREFIX | SS_EDITCONTROL | WS_ಗುಂಪು;
    ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, ಪಠ್ಯ, 0);
}

ಸ್ಥಿರ bool ಕೂಡಿಸು_Dialog_Static_Icon(WIN_Dialog_ದತ್ತಾಂಶ *dialog, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_ಮಗು | SS_ICON | WS_ಗುಂಪು;
    ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, ಖಾಲಿ, ordinal);
}

ಸ್ಥಿರ bool ಕೂಡಿಸು_Dialog_Button(WIN_Dialog_ದತ್ತಾಂಶ *dialog, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ, ಪೂರ್ಣಾಂಕ id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_ಮಗು | WS_TABSTOP;
    ಆದರೆ (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } ಇಲ್ಲದಿದ್ದರೆ {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    ಆದರೆ (dialog->numbuttons == 0) {
        style |= WS_ಗುಂಪು;
    }
    ಹಿಂತಿರುಗಿ ಕೂಡಿಸು_Dialog_Control(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, ಪಠ್ಯ, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ Free_Dialog_ದತ್ತಾಂಶ(WIN_Dialog_ದತ್ತಾಂಶ *dialog)
{
    SDL_free(dialog->ದತ್ತಾಂಶ);
    SDL_free(dialog);
}

ಸ್ಥಿರ WIN_Dialog_ದತ್ತಾಂಶ *Create_Dialog_ದತ್ತಾಂಶ(ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *caption)
{
    WIN_Dialog_ದತ್ತಾಂಶ *dialog;
    DLGTEMPLATEEX dialogTemplate;
    ಶಬ್ದ ಶಬ್ದ_ಗಮ್ಯ_Pass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (ಗಿಡ್ಡ)w;
    dialogTemplate.cy = (ಗಿಡ್ಡ)h;
    Vec2_ಗಮ್ಯ_DLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*dialog));
    ಆದರೆ (!dialog) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &dialogTemplate, ಗಾತ್ರ(dialogTemplate))) {
        Free_Dialog_ದತ್ತಾಂಶ(dialog);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // No menu
    ಶಬ್ದ_ಗಮ್ಯ_Pass = 0;
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಶಬ್ದ_ಗಮ್ಯ_Pass, 2)) {
        Free_Dialog_ದತ್ತಾಂಶ(dialog);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // No custom class
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಶಬ್ದ_ಗಮ್ಯ_Pass, 2)) {
        Free_Dialog_ದತ್ತಾಂಶ(dialog);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // title
    ಆದರೆ (!ಕೂಡಿಸು_Dialog_String(dialog, caption)) {
        Free_Dialog_ದತ್ತಾಂಶ(dialog);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ಗಮ್ಯ_Pass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_ಗಾತ್ರ = ಗಾತ್ರ(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(ಖಾಲಿ);
            ಪೂರ್ಣಾಂಕ LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            ಆದರೆ (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            ಶಬ್ದ_ಗಮ್ಯ_Pass = (ಶಬ್ದ)(-72 * NCM.lf_ಸಂದೇಶ_Font.lf_ಎತ್ತರ / LogicalPixelsY);
            ReleaseDC(ಖಾಲಿ, ScreenDC);
        }

        ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಶಬ್ದ_ಗಮ್ಯ_Pass, 2)) {
            Free_Dialog_ದತ್ತಾಂಶ(dialog);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // Font weight
        ಶಬ್ದ_ಗಮ್ಯ_Pass = (ಶಬ್ದ)NCM.lf_ಸಂದೇಶ_Font.lf_ತೂಕ;
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಶಬ್ದ_ಗಮ್ಯ_Pass, 2)) {
            Free_Dialog_ದತ್ತಾಂಶ(dialog);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // italic?
        ಗಮ್ಯ_Pass = NCM.lf_ಸಂದೇಶ_Font.lfItalic;
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಗಮ್ಯ_Pass, 1)) {
            Free_Dialog_ದತ್ತಾಂಶ(dialog);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // charset?
        ಗಮ್ಯ_Pass = NCM.lf_ಸಂದೇಶ_Font.lf_Char_ಗಣ;
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_ದತ್ತಾಂಶ(dialog, &ಗಮ್ಯ_Pass, 1)) {
            Free_Dialog_ದತ್ತಾಂಶ(dialog);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // font typeface.
        ಆದರೆ (!ಕೂಡಿಸು_Dialog_String(dialog, NCM.lf_ಸಂದೇಶ_Font.lfFaceName)) {
            Free_Dialog_ದತ್ತಾಂಶ(dialog);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಹಿಂತಿರುಗಿ dialog;
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
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *EscapeAmpersands(ಅಕ್ಷರ **dst, size_t *dstlen, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src)
{
    ಅಕ್ಷರ *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    ಆದರೆ (!src) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆಗ (src[srclen]) {
        ಆದರೆ (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    ಆದರೆ (ampcount == 0) {
        // Nothing to do.
        ಹಿಂತಿರುಗಿ src;
    }
    ಆದರೆ (SIZE_MAX - srclen < ampcount) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        ಆದರೆ (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = ಖಾಲಿ;
        newdst = (ಅಕ್ಷರ *)SDL_malloc(*dstlen);
        ಆದರೆ (!newdst) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        *dst = newdst;
    } ಇಲ್ಲದಿದ್ದರೆ {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    ಆಗ (srclen--) {
        ಆದರೆ (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    ಹಿಂತಿರುಗಿ *dst;
}

ಸ್ಥಿರ ದಶಮಾಂಶ WIN_GetContentScale(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ dpi = 0;

#ಆದರೆ 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    ಆದರೆ (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (ಪೂರ್ಣಾಂಕ)hdpi_uint;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ಖಾಲಿ);
        ಆದರೆ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ಖಾಲಿ, hdc);
        }
    }
    ಆದರೆ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ಹಿಂತಿರುಗಿ dpi / (ದಶಮಾಂಶ)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
ಸ್ಥಿರ bool WIN_Show_Old_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
    WIN_Dialog_ದತ್ತಾಂಶ *dialog;
    ಪೂರ್ಣಾಂಕ i, x, y;
    HFONT DialogFont;
    ಗಾತ್ರ_4 ಗಾತ್ರ_3;
    RECT ಪಠ್ಯ_ಗಾತ್ರ;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    ಅಕ್ಷರ *ampescape = ಖಾಲಿ;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool ಫಲಿತಾಂಶ;

    HWND ಪೋಷಕ_ಕಿಟಕಿ_2 = ಖಾಲಿ;

    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ scale = WIN_GetContentScale();
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ Button_ಅಗಲ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(88 * scale);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ Button_ಎತ್ತರ = (ಪೂರ್ಣಾಂಕ)SDL_roundf(26 * scale);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಪಠ್ಯ_Margin = (ಪೂರ್ಣಾಂಕ)SDL_roundf(16 * scale);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ButtonMargin = (ಪೂರ್ಣಾಂಕ)SDL_roundf(12 * scale);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ Icon_ಅಗಲ = GetSystemMetrics(SM_CXICON);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ Icon_ಎತ್ತರ = GetSystemMetrics(SM_CYICON);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ IconMargin = (ಪೂರ್ಣಾಂಕ)SDL_roundf(20 * scale);

    ಆದರೆ (messageboxdata->numbuttons > MAX_BUTTONS) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    ಆಯ್ಕೆ (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ಸ್ಥಿತಿ SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        ನಿಲ್ಲಿಸು;
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
        NCM.cb_ಗಾತ್ರ = ಗಾತ್ರ(NCM);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);
        lf = NCM.lf_ಸಂದೇಶ_Font;
        DialogFont = Create_Font_ಪರೋಕ್ಷ(&lf);
    }

    // Select the font in to our DC
    SelectObject(FontDC, DialogFont);

    {
        // Get the metrics to try and figure our DLU conversion.
        Get_ಪಠ್ಯ_Metrics(FontDC, &TM);

        /* Calculation from the following documentation:
         * https://support.microsoft.com/en-gb/help/125681/how-to-calculate-dialog-base-units-with-non-system-based-font
         * This fixes bug 2137, dialog box calculation with a fixed-width system font
         */
        {
            ಗಾತ್ರ_4 extent;
            Get_ಪಠ್ಯ_Extent_Point32_A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_ತಳ_Units_X = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_ತಳ_Units_Y = TM.tm_ಎತ್ತರ;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8_ಗಮ್ಯ_String_W(messageboxdata->ಸಂದೇಶ);
    SDL_zero(ಪಠ್ಯ_ಗಾತ್ರ);
    Draw_ಪಠ್ಯ_W(FontDC, wmessage, -1, &ಪಠ್ಯ_ಗಾತ್ರ, DT_CALCRECT | DT_ಎಡ | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    ಪಠ್ಯ_ಗಾತ್ರ.ಎಡ += ಪಠ್ಯ_Margin;
    ಪಠ್ಯ_ಗಾತ್ರ.ಬಲ += ಪಠ್ಯ_Margin + 2;
    ಪಠ್ಯ_ಗಾತ್ರ.ತುದಿ += ಪಠ್ಯ_Margin;
    ಪಠ್ಯ_ಗಾತ್ರ.bottom += ಪಠ್ಯ_Margin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    ಗಾತ್ರ_3.cx = ಪಠ್ಯ_ಗಾತ್ರ.ಬಲ - ಪಠ್ಯ_ಗಾತ್ರ.ಎಡ;
    ಗಾತ್ರ_3.cy = ಪಠ್ಯ_ಗಾತ್ರ.bottom - ಪಠ್ಯ_ಗಾತ್ರ.ತುದಿ;
    ಗಾತ್ರ_3.cx += ಪಠ್ಯ_Margin * 2;
    ಗಾತ್ರ_3.cy += ಪಠ್ಯ_Margin * 2;

    // Make dialog wider and shift text over for the icon.
    ಆದರೆ (icon) {
        ಗಾತ್ರ_3.cx += IconMargin + Icon_ಅಗಲ;
        ಪಠ್ಯ_ಗಾತ್ರ.ಎಡ += IconMargin + Icon_ಅಗಲ;
        ಪಠ್ಯ_ಗಾತ್ರ.ಬಲ += IconMargin + Icon_ಅಗಲ;
    }

    // Ensure the size is wide enough for all of the buttons.
    ಆದರೆ (ಗಾತ್ರ_3.cx < (LONG)messageboxdata->numbuttons * (Button_ಅಗಲ + ButtonMargin) + ButtonMargin) {
        ಗಾತ್ರ_3.cx = (LONG)messageboxdata->numbuttons * (Button_ಅಗಲ + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    ಆದರೆ (icon && ಗಾತ್ರ_3.cy < (LONG)IconMargin * 2 + Icon_ಎತ್ತರ) {
        ಗಾತ್ರ_3.cy = (LONG)IconMargin * 2 + Icon_ಎತ್ತರ;
    }

    // Add vertical space for the buttons and border.
    ಗಾತ್ರ_3.cy += Button_ಎತ್ತರ + ಪಠ್ಯ_Margin;

    dialog = Create_Dialog_ದತ್ತಾಂಶ(ಗಾತ್ರ_3.cx, ಗಾತ್ರ_3.cy, messageboxdata->title);
    ಆದರೆ (!dialog) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (icon && !ಕೂಡಿಸು_Dialog_Static_Icon(dialog, IconMargin, IconMargin, Icon_ಅಗಲ, Icon_ಎತ್ತರ, icon)) {
        Free_Dialog_ದತ್ತಾಂಶ(dialog);
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!ಕೂಡಿಸು_Dialog_Static_ಪಠ್ಯ(dialog, ಪಠ್ಯ_ಗಾತ್ರ.ಎಡ, ಪಠ್ಯ_ಗಾತ್ರ.ತುದಿ, ಪಠ್ಯ_ಗಾತ್ರ.ಬಲ - ಪಠ್ಯ_ಗಾತ್ರ.ಎಡ, ಪಠ್ಯ_ಗಾತ್ರ.bottom - ಪಠ್ಯ_ಗಾತ್ರ.ತುದಿ, messageboxdata->ಸಂದೇಶ)) {
        Free_Dialog_ದತ್ತಾಂಶ(dialog);
        ಹಿಂತಿರುಗಿ false;
    }

    // Align the buttons to the right/bottom.
    x = ಗಾತ್ರ_3.cx - (Button_ಅಗಲ + ButtonMargin) * messageboxdata->numbuttons;
    y = ಗಾತ್ರ_3.cy - Button_ಎತ್ತರ - ButtonMargin;
    ಗಾಗಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *buttontext;
        ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಎಡ_ಗಮ್ಯ_ಬಲ) {
            sdlButton = &messageboxdata->buttons[i];
        } ಇಲ್ಲದಿದ್ದರೆ {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        ಆದರೆ (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            ಆದರೆ (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->ಪಠ್ಯ);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        ಆದರೆ (!buttontext || !ಕೂಡಿಸು_Dialog_Button(dialog, x, y, Button_ಅಗಲ, Button_ಎತ್ತರ, buttontext, IDBUTTONINDEX0 + (ಪೂರ್ಣಾಂಕ)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_ದತ್ತಾಂಶ(dialog);
            SDL_free(ampescape);
            ಹಿಂತಿರುಗಿ false;
        }

        x += Button_ಅಗಲ + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    ಆದರೆ (messageboxdata->ಕಿಟಕಿ) {
        ಪೋಷಕ_ಕಿಟಕಿ_2 = messageboxdata->ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    }

    rc = Dialog_Box_ಪರೋಕ್ಷ_Param(ಖಾಲಿ, (DLGTEMPLATE *)dialog->lpDialog, ಪೋಷಕ_ಕಿಟಕಿ_2, ಸಂದೇಶ_Box_Dialog_Proc, (LPARAM)messageboxdata);
    ಆದರೆ (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        ಫಲಿತಾಂಶ = true;
        *buttonID = -1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (rc == 0) {
            SDL_ಗಣ_Error("Invalid parent window handle");
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rc == -1) {
            SDL_ಗಣ_Error("The message box encountered an error.");
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_ಗಣ_Error("Invalid message box pointer in dialog procedure");
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rc == IDINVALPTRDLGITEM) {
            SDL_ಗಣ_Error("Couldn't find dialog control of the default enter-key button");
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_ಗಣ_Error("An unknown error occurred");
        }
        ಫಲಿತಾಂಶ = false;
    }

    Free_Dialog_ದತ್ತಾಂಶ(dialog);
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(ಸ್ಥಿರಾಂಕ TASKDIALOGCONFIG *pTaskConfig, ಪೂರ್ಣಾಂಕ *pnButton, ಪೂರ್ಣಾಂಕ *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
    HWND ಪೋಷಕ_ಕಿಟಕಿ_2 = ಖಾಲಿ;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC p_Task_Dialog_ಪರೋಕ್ಷ;
    HRESULT hr;
    ಅಕ್ಷರ *ampescape = ಖಾಲಿ;
    size_t ampescapesize = 0;
    ಪೂರ್ಣಾಂಕ nButton;
    ಪೂರ್ಣಾಂಕ nCancelButton;
    ಪೂರ್ಣಾಂಕ i;
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ (SIZE_MAX / ಗಾತ್ರ(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        ಹಿಂತಿರುಗಿ SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
    }

    HMODULE hUser32 = GetModuleHandle(ಪಠ್ಯ_2("user32.dll"));
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ DPI_AWARENESS_CONTEXT (WINAPI *pfn_ಗಣ_Thread_Dpi_Awareness_Context)(DPI_AWARENESS_CONTEXT);
    pfn_ಗಣ_Thread_Dpi_Awareness_Context p_ಗಣ_Thread_Dpi_Awareness_Context = (pfn_ಗಣ_Thread_Dpi_Awareness_Context)Get_Proc_ವಿಳಾಸ(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT ಹಿಂದಿನ_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    ಆದರೆ (p_ಗಣ_Thread_Dpi_Awareness_Context) {
        ಹಿಂದಿನ_context = p_ಗಣ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ಪ್ರತಿ_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = ತುಂಬು_Library(ಪಠ್ಯ_2("comctl32.dll"));
    ಆದರೆ (!hComctl32) {
        ಫಲಿತಾಂಶ = WIN_Show_Old_ಸಂದೇಶ_Box(messageboxdata, buttonID);
        ಹೋಗು ಮುಗಿದ;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    p_Task_Dialog_ಪರೋಕ್ಷ = (TASKDIALOGINDIRECTPROC)Get_Proc_ವಿಳಾಸ(hComctl32, "TaskDialogIndirect");
    ಆದರೆ (!p_Task_Dialog_ಪರೋಕ್ಷ) {
        FreeLibrary(hComctl32);
        ಫಲಿತಾಂಶ = WIN_Show_Old_ಸಂದೇಶ_Box(messageboxdata, buttonID);
        ಹೋಗು ಮುಗಿದ;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    ಆದರೆ (messageboxdata->ಕಿಟಕಿ) {
        ಪೋಷಕ_ಕಿಟಕಿ_2 = messageboxdata->ಕಿಟಕಿ->ಆಂತರಿಕ->hwnd;
    }

    wmessage = WIN_UTF8_ಗಮ್ಯ_String_W(messageboxdata->ಸಂದೇಶ);
    wtitle = WIN_UTF8_ಗಮ್ಯ_String_W(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_ಗಾತ್ರ = ಗಾತ್ರ(TASKDIALOGCONFIG);
    TaskConfig.hwnd_ಪೋಷಕ = ಪೋಷಕ_ಕಿಟಕಿ_2;
    TaskConfig.dwFlags = TDF_ಗಾತ್ರ_ಗಮ್ಯ_CONTENT;
    TaskConfig.psz_ಕಿಟಕಿ_Title = wtitle;
    ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } ಇಲ್ಲದಿದ್ದರೆ {
        TaskConfig.pszMainIcon = ಖಾಲಿ;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(ಗಾತ್ರ(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    ಗಾಗಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *buttontext;
        ಆದರೆ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ಎಡ_ಗಮ್ಯ_ಬಲ) {
            pButton = &pButtons[i];
        } ಇಲ್ಲದಿದ್ದರೆ {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        ಆದರೆ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } ಇಲ್ಲದಿದ್ದರೆ {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].ಪಠ್ಯ);
        ಆದರೆ (!buttontext) {
            ಪೂರ್ಣಾಂಕ j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            ಗಾಗಿ (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].psz_Button_ಪಠ್ಯ);
            }
            SDL_free(pButtons);
            ಹಿಂತಿರುಗಿ false;
        }
        pButton->psz_Button_ಪಠ್ಯ = WIN_UTF8_ಗಮ್ಯ_String_W(buttontext);
        ಆದರೆ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = p_Task_Dialog_ಪರೋಕ್ಷ(&TaskConfig, &nButton, ಖಾಲಿ, ಖಾಲಿ);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    ಗಾಗಿ (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].psz_Button_ಪಠ್ಯ);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    ಆದರೆ (SUCCEEDED(hr)) {
        ಆದರೆ (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *buttonID = -1;
        }
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // We failed showing the Task Dialog, use the old message box!
        ಫಲಿತಾಂಶ = WIN_Show_Old_ಸಂದೇಶ_Box(messageboxdata, buttonID);
    }

ಮುಗಿದ:
    ಆದರೆ (p_ಗಣ_Thread_Dpi_Awareness_Context) {
        p_ಗಣ_Thread_Dpi_Awareness_Context(ಹಿಂದಿನ_context);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS

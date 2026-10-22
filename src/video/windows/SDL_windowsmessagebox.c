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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIMITS_H
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SIZE_MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SIZE_MAX ((size_t)-1)
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/windows/SDL_windows.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SS_EDITCONTROL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SS_EDITCONTROL 0x2000
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ IDOK
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDOK 1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ IDCANCEL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDCANCEL 2
#ਜੇ_ਅੰਤ

// Custom dialog return codes
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDCLOSED           20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDINVALPTRINIT     50
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDINVALPTRCOMMAND  51
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDINVALPTRSETFOCUS 52
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDINVALPTRDLGITEM  53
// First button ID
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDBUTTONINDEX0 100

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DLGITEMTYPEBUTTON 0x0080
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT ਸੁਨੇਹਾ_2, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_ਅੰਕੜੇ);

ਗਿਣਤੀ _TASKDIALOG_FLAGS
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
    TDF_SHOW_ਤਰੱਕੀ_BAR = 0x0200,
    TDF_SHOW_MARQUEE_ਤਰੱਕੀ_BAR = 0x0400,
    TDF_CALLBACK_TIMER = 0x0800,
    TDF_POSITION_RELATIVE_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ = 0x1000,
    TDF_RTL_LAYOUT = 0x2000,
    TDF_NO_DEFAULT_RADIO_BUTTON = 0x4000,
    TDF_CAN_BE_MINIMIZED = 0x8000,
    // #if (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_NO_ਸੈੱਟ_FOREGROUND = 0x00010000, // Don't call SetForegroundWindow() when activating the dialog
                                        // #endif // (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_ਮਾਪ_ਮੰਜ਼ਿਲ_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ _TASKDIALOG_MESSAGES
{
    TDM_NAVIGATE_ਪੰਨਾ = WM_USER + 101,
    TDM_CLICK_BUTTON = WM_USER + 102,                        // wParam = Button ID
    TDM_ਸੈੱਟ_MARQUEE_ਤਰੱਕੀ_BAR = WM_USER + 103,            // wParam = 0 (nonMarque) wParam != 0 (Marquee)
    TDM_ਸੈੱਟ_ਤਰੱਕੀ_BAR_STATE = WM_USER + 104,              // wParam = new progress state
    TDM_ਸੈੱਟ_ਤਰੱਕੀ_BAR_RANGE = WM_USER + 105,              // lParam = MAKELPARAM(nMinRange, nMaxRange)
    TDM_ਸੈੱਟ_ਤਰੱਕੀ_BAR_POS = WM_USER + 106,                // wParam = new position
    TDM_ਸੈੱਟ_ਤਰੱਕੀ_BAR_MARQUEE = WM_USER + 107,            // wParam = 0 (stop marquee), wParam != 0 (start marquee), lparam = speed (milliseconds between repaints)
    TDM_ਸੈੱਟ_ELEMENT_ਪਾਠ = WM_USER + 108,                    // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_CLICK_RADIO_BUTTON = WM_USER + 110,                  // wParam = Radio Button ID
    TDM_ENABLE_BUTTON = WM_USER + 111,                       // lParam = 0 (disable), lParam != 0 (enable), wParam = Button ID
    TDM_ENABLE_RADIO_BUTTON = WM_USER + 112,                 // lParam = 0 (disable), lParam != 0 (enable), wParam = Radio Button ID
    TDM_CLICK_VERIFICATION = WM_USER + 113,                  // wParam = 0 (unchecked), 1 (checked), lParam = 1 (set key focus)
    TDM_UPDATE_ELEMENT_ਪਾਠ = WM_USER + 114,                 // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_ਸੈੱਟ_BUTTON_ELEVATION_REQUIRED_STATE = WM_USER + 115, // wParam = Button ID, lParam = 0 (elevation not required), lParam != 0 (elevation required)
    TDM_UPDATE_ICON = WM_USER + 116                          // wParam = icon element (TASKDIALOG_ICON_ELEMENTS), lParam = new icon (hIcon if TDF_USE_HICON_* was set, PCWSTR otherwise)
} TASKDIALOG_MESSAGES;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ _TASKDIALOG_NOTIFICATIONS
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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

ਗਿਣਤੀ _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#ਹਦਾਇਤ pack(ਧੱਕੋ, 1)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _TASKDIALOG_BUTTON
{
    ਪੂਰਨ nButtonID;
    PCWSTR psz_Button_ਪਾਠ;
} TASKDIALOG_BUTTON;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ _TASKDIALOGCONFIG
{
    UINT cb_ਮਾਪ;
    HWND hwnd_ਮਾਪਾ;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR psz_ਖਿੜਕੀ_Title;                          // string or MAKEINTRESOURCE()
    ਸੰਘ
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    ਅਚਲ TASKDIALOG_BUTTON *pButtons;
    ਪੂਰਨ nDefaultButton;
    UINT cRadioButtons;
    ਅਚਲ TASKDIALOG_BUTTON *pRadioButtons;
    ਪੂਰਨ nDefaultRadioButton;
    PCWSTR psz_Verification_ਪਾਠ;
    PCWSTR pszExpandedInformation;
    PCWSTR psz_Expanded_Control_ਪਾਠ;
    PCWSTR psz_Collapsed_Control_ਪਾਠ;
    ਸੰਘ
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lp_Callback_ਅੰਕੜੇ;
    UINT cx_ਚੌੜਾਈ; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਸ਼ਬਦ_2 dlgVer;
    ਸ਼ਬਦ_2 signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    ਸ਼ਬਦ_2 c_Dlg_ਚੀਜ਼ਾਂ;
    ਛੋਟਾ x;
    ਛੋਟਾ y;
    ਛੋਟਾ cx;
    ਛੋਟਾ cy;
} DLGTEMPLATEEX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    ਛੋਟਾ x;
    ਛੋਟਾ y;
    ਛੋਟਾ cx;
    ਛੋਟਾ cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#ਹਦਾਇਤ pack(ਕੱਢੋ)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    DLGTEMPLATEEX *lpDialog;
    ਖਾਲੀ *ਅੰਕੜੇ;
    size_t ਮਾਪ;
    size_t ਵਰਤਿਆ;
    ਸ਼ਬਦ_2 numbuttons;
} WIN_Dialog_ਅੰਕੜੇ;

ਸਥਿਰ bool Get_Button_ਸੂਚਕਾਂਕ(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, SDL_ਸੁਨੇਹਾ_Box_Button_Flags flags, size_t *i)
{
    ਲਈ (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        ਜੇ (messageboxdata->buttons[*i].flags & flags) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ INT_PTR CALLBACK ਸੁਨੇਹਾ_Box_Dialog_Proc(HWND hDlg, UINT i_ਸੁਨੇਹਾ, WPARAM wParam, LPARAM lParam)
{
    ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata;
    size_t buttonindex;

    ਚੋਣ (i_ਸੁਨੇਹਾ) {
    ਹਾਲਤ WM_INITDIALOG:
        ਜੇ (lParam == 0) {
            ਸਿਰਾ_Dialog(hDlg, IDINVALPTRINIT);
            ਵਾਪਸ TRUE;
        }
        messageboxdata = (ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *)lParam;
        ਸੈੱਟ_ਖਿੜਕੀ_Long_Ptr(hDlg, GWLP_USERDATA, lParam);

        ਜੇ (Get_Button_ਸੂਚਕਾਂਕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = Get_Dlg_ਵਸਤੂ(hDlg, (ਪੂਰਨ)(IDBUTTONINDEX0 + buttonindex));
            ਜੇ (!buttonctl) {
                ਸਿਰਾ_Dialog(hDlg, IDINVALPTRDLGITEM);
            }
            Post_ਸੁਨੇਹਾ(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } ਨਹੀਂਤਾਂ {
            // Give the focus to the dialog window instead
            ਸੈੱਟ_Focus(hDlg);
        }
        ਵਾਪਸ FALSE;
    ਹਾਲਤ WM_SETFOCUS:
        messageboxdata = (ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *)Get_ਖਿੜਕੀ_Long_Ptr(hDlg, GWLP_USERDATA);
        ਜੇ (!messageboxdata) {
            ਸਿਰਾ_Dialog(hDlg, IDINVALPTRSETFOCUS);
            ਵਾਪਸ TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        ਜੇ (Get_Button_ਸੂਚਕਾਂਕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            ਵਾਪਸ FALSE;
        }
        ਵਾਪਸ TRUE;
    ਹਾਲਤ WM_COMMAND:
        messageboxdata = (ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *)Get_ਖਿੜਕੀ_Long_Ptr(hDlg, GWLP_USERDATA);
        ਜੇ (!messageboxdata) {
            ਸਿਰਾ_Dialog(hDlg, IDINVALPTRCOMMAND);
            ਵਾਪਸ TRUE;
        }

        // Return the ID of the button that was pushed
        ਜੇ (wParam == IDOK) {
            ਜੇ (Get_Button_ਸੂਚਕਾਂਕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                ਸਿਰਾ_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (wParam == IDCANCEL) {
            ਜੇ (Get_Button_ਸੂਚਕਾਂਕ(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                ਸਿਰਾ_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } ਨਹੀਂਤਾਂ {
                // Closing of window was requested by user or system. It would be rude not to comply.
                ਸਿਰਾ_Dialog(hDlg, IDCLOSED);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (wParam >= IDBUTTONINDEX0 && (ਪੂਰਨ)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            ਸਿਰਾ_Dialog(hDlg, wParam);
        }
        ਵਾਪਸ TRUE;

    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਵਾਪਸ FALSE;
}

ਸਥਿਰ bool ExpandDialogSpace(WIN_Dialog_ਅੰਕੜੇ *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    ਅਚਲ size_t sizestep = 0x10000;
    size_t ਮਾਪ = dialog->ਮਾਪ;

    ਜੇ (ਮਾਪ == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        ਮਾਪ = 0x1000;
        ਜੇ (SIZE_MAX - sizestep < space) {
            ਮਾਪ = space;
        } ਨਹੀਂਤਾਂ ਜੇ (space > ਮਾਪ) {
            ਮਾਪ = (space + sizestep) & ~(sizestep - 1);
        }
    } ਨਹੀਂਤਾਂ ਜੇ (SIZE_MAX - dialog->ਵਰਤਿਆ < space) {
        SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        ਵਾਪਸ false;
    } ਨਹੀਂਤਾਂ ਜੇ (SIZE_MAX - (dialog->ਵਰਤਿਆ + space) < sizestep) {
        // Close to the maximum.
        ਮਾਪ = dialog->ਵਰਤਿਆ + space;
    } ਨਹੀਂਤਾਂ ਜੇ (ਮਾਪ < dialog->ਵਰਤਿਆ + space) {
        // Round up to the next 64 KiB block.
        ਮਾਪ = dialog->ਵਰਤਿਆ + space;
        ਮਾਪ += sizestep - ਮਾਪ % sizestep;
    }

    ਜੇ (ਮਾਪ > dialog->ਮਾਪ) {
        ਖਾਲੀ *ਅੰਕੜੇ = SDL_realloc(dialog->ਅੰਕੜੇ, ਮਾਪ);
        ਜੇ (!ਅੰਕੜੇ) {
            ਵਾਪਸ false;
        }
        dialog->ਅੰਕੜੇ = ਅੰਕੜੇ;
        dialog->ਮਾਪ = ਮਾਪ;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->ਅੰਕੜੇ;
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool Align_Dialog_ਅੰਕੜੇ(WIN_Dialog_ਅੰਕੜੇ *dialog, size_t ਮਾਪ)
{
    size_t padding = (dialog->ਵਰਤਿਆ % ਮਾਪ);

    ਜੇ (!ExpandDialogSpace(dialog, padding)) {
        ਵਾਪਸ false;
    }

    dialog->ਵਰਤਿਆ += padding;

    ਵਾਪਸ true;
}

ਸਥਿਰ bool ਜੋੜੋ_Dialog_ਅੰਕੜੇ(WIN_Dialog_ਅੰਕੜੇ *dialog, ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ, size_t ਮਾਪ)
{
    ਜੇ (!ExpandDialogSpace(dialog, ਮਾਪ)) {
        ਵਾਪਸ false;
    }

    SDL_memcpy((Uint8 *)dialog->ਅੰਕੜੇ + dialog->ਵਰਤਿਆ, ਅੰਕੜੇ, ਮਾਪ);
    dialog->ਵਰਤਿਆ += ਮਾਪ;

    ਵਾਪਸ true;
}

ਸਥਿਰ bool ਜੋੜੋ_Dialog_String(WIN_Dialog_ਅੰਕੜੇ *dialog, ਅਚਲ ਅੱਖਰ *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t ਗਿਣਤੀ_2;
    bool ਸਥਿਤੀ;

    ਜੇ (!string) {
        string = "";
    }

    wstring = WIN_UTF8_ਮੰਜ਼ਿਲ_String_W(string);
    ਜੇ (!wstring) {
        ਵਾਪਸ false;
    }

    // Find out how many characters we have, including null terminator
    ਗਿਣਤੀ_2 = 0;
    ਲਈ (p = wstring; *p; ++p) {
        ++ਗਿਣਤੀ_2;
    }
    ++ਗਿਣਤੀ_2;

    ਸਥਿਤੀ = ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, wstring, ਗਿਣਤੀ_2 * ਆਕਾਰ(WCHAR));
    SDL_free(wstring);
    ਵਾਪਸ ਸਥਿਤੀ;
}

ਸਥਿਰ ਪੂਰਨ s_ਅਧਾਰ_Units_X;
ਸਥਿਰ ਪੂਰਨ s_ਅਧਾਰ_Units_Y;
ਸਥਿਰ ਖਾਲੀ Vec2_ਮੰਜ਼ਿਲ_DLU(ਛੋਟਾ *x, ਛੋਟਾ *y)
{
    SDL_assert(s_ਅਧਾਰ_Units_X != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (ਛੋਟਾ)MulDiv(*x, 4, s_ਅਧਾਰ_Units_X);
    *y = (ਛੋਟਾ)MulDiv(*y, 8, s_ਅਧਾਰ_Units_Y);
}

ਸਥਿਰ bool ਜੋੜੋ_Dialog_Control(WIN_Dialog_ਅੰਕੜੇ *dialog, ਸ਼ਬਦ_2 type, DWORD style, DWORD exStyle, ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ id, ਅਚਲ ਅੱਖਰ *caption, ਸ਼ਬਦ_2 ordinal)
{
    DLGITEMTEMPLATEEX ਵਸਤੂ;
    ਸ਼ਬਦ_2 marker = 0xFFFF;
    ਸ਼ਬਦ_2 extra_ਅੰਕੜੇ = 0;

    SDL_zero(ਵਸਤੂ);
    ਵਸਤੂ.style = style;
    ਵਸਤੂ.exStyle = exStyle;
    ਵਸਤੂ.x = (ਛੋਟਾ)x;
    ਵਸਤੂ.y = (ਛੋਟਾ)y;
    ਵਸਤੂ.cx = (ਛੋਟਾ)w;
    ਵਸਤੂ.cy = (ਛੋਟਾ)h;
    ਵਸਤੂ.id = id;

    Vec2_ਮੰਜ਼ਿਲ_DLU(&ਵਸਤੂ.x, &ਵਸਤੂ.y);
    Vec2_ਮੰਜ਼ਿਲ_DLU(&ਵਸਤੂ.cx, &ਵਸਤੂ.cy);

    ਜੇ (!Align_Dialog_ਅੰਕੜੇ(dialog, ਆਕਾਰ(DWORD))) {
        ਵਾਪਸ false;
    }
    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਵਸਤੂ, ਆਕਾਰ(ਵਸਤੂ))) {
        ਵਾਪਸ false;
    }
    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &marker, ਆਕਾਰ(marker))) {
        ਵਾਪਸ false;
    }
    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &type, ਆਕਾਰ(type))) {
        ਵਾਪਸ false;
    }
    ਜੇ (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        ਜੇ (!ਜੋੜੋ_Dialog_String(dialog, caption)) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &marker, ਆਕਾਰ(marker))) {
            ਵਾਪਸ false;
        }
        ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ordinal, ਆਕਾਰ(ordinal))) {
            ਵਾਪਸ false;
        }
    }
    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &extra_ਅੰਕੜੇ, ਆਕਾਰ(extra_ਅੰਕੜੇ))) {
        ਵਾਪਸ false;
    }
    ਜੇ (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_ਚੀਜ਼ਾਂ;

    ਵਾਪਸ true;
}

ਸਥਿਰ bool ਜੋੜੋ_Dialog_Static_ਪਾਠ(WIN_Dialog_ਅੰਕੜੇ *dialog, ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ w, ਪੂਰਨ h, ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    DWORD style = WS_VISIBLE | WS_ਬੱਚਾ | SS_ਖੱਬਾ | SS_NOPREFIX | SS_EDITCONTROL | WS_ਸਮੂਹ;
    ਵਾਪਸ ਜੋੜੋ_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, ਪਾਠ, 0);
}

ਸਥਿਰ bool ਜੋੜੋ_Dialog_Static_Icon(WIN_Dialog_ਅੰਕੜੇ *dialog, ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ w, ਪੂਰਨ h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_ਬੱਚਾ | SS_ICON | WS_ਸਮੂਹ;
    ਵਾਪਸ ਜੋੜੋ_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, ਨਿਰਾ, ordinal);
}

ਸਥਿਰ bool ਜੋੜੋ_Dialog_Button(WIN_Dialog_ਅੰਕੜੇ *dialog, ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ w, ਪੂਰਨ h, ਅਚਲ ਅੱਖਰ *ਪਾਠ, ਪੂਰਨ id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_ਬੱਚਾ | WS_TABSTOP;
    ਜੇ (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } ਨਹੀਂਤਾਂ {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    ਜੇ (dialog->numbuttons == 0) {
        style |= WS_ਸਮੂਹ;
    }
    ਵਾਪਸ ਜੋੜੋ_Dialog_Control(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, ਪਾਠ, 0);
}

ਸਥਿਰ ਖਾਲੀ Free_Dialog_ਅੰਕੜੇ(WIN_Dialog_ਅੰਕੜੇ *dialog)
{
    SDL_free(dialog->ਅੰਕੜੇ);
    SDL_free(dialog);
}

ਸਥਿਰ WIN_Dialog_ਅੰਕੜੇ *Create_Dialog_ਅੰਕੜੇ(ਪੂਰਨ w, ਪੂਰਨ h, ਅਚਲ ਅੱਖਰ *caption)
{
    WIN_Dialog_ਅੰਕੜੇ *dialog;
    DLGTEMPLATEEX dialogTemplate;
    ਸ਼ਬਦ_2 ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (ਛੋਟਾ)w;
    dialogTemplate.cy = (ਛੋਟਾ)h;
    Vec2_ਮੰਜ਼ਿਲ_DLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*dialog));
    ਜੇ (!dialog) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &dialogTemplate, ਆਕਾਰ(dialogTemplate))) {
        Free_Dialog_ਅੰਕੜੇ(dialog);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // No menu
    ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass = 0;
    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass, 2)) {
        Free_Dialog_ਅੰਕੜੇ(dialog);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // No custom class
    ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass, 2)) {
        Free_Dialog_ਅੰਕੜੇ(dialog);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // title
    ਜੇ (!ਜੋੜੋ_Dialog_String(dialog, caption)) {
        Free_Dialog_ਅੰਕੜੇ(dialog);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ਮੰਜ਼ਿਲ_Pass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_ਮਾਪ = ਆਕਾਰ(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(ਨਿਰਾ);
            ਪੂਰਨ LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            ਜੇ (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass = (ਸ਼ਬਦ_2)(-72 * NCM.lf_ਸੁਨੇਹਾ_Font.lf_ਉਚਾਈ / LogicalPixelsY);
            ReleaseDC(ਨਿਰਾ, ScreenDC);
        }

        ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass, 2)) {
            Free_Dialog_ਅੰਕੜੇ(dialog);
            ਵਾਪਸ ਨਿਰਾ;
        }

        // Font weight
        ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass = (ਸ਼ਬਦ_2)NCM.lf_ਸੁਨੇਹਾ_Font.lf_ਭਾਰ;
        ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਸ਼ਬਦ_ਮੰਜ਼ਿਲ_Pass, 2)) {
            Free_Dialog_ਅੰਕੜੇ(dialog);
            ਵਾਪਸ ਨਿਰਾ;
        }

        // italic?
        ਮੰਜ਼ਿਲ_Pass = NCM.lf_ਸੁਨੇਹਾ_Font.lfItalic;
        ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਮੰਜ਼ਿਲ_Pass, 1)) {
            Free_Dialog_ਅੰਕੜੇ(dialog);
            ਵਾਪਸ ਨਿਰਾ;
        }

        // charset?
        ਮੰਜ਼ਿਲ_Pass = NCM.lf_ਸੁਨੇਹਾ_Font.lf_Char_ਸੈੱਟ;
        ਜੇ (!ਜੋੜੋ_Dialog_ਅੰਕੜੇ(dialog, &ਮੰਜ਼ਿਲ_Pass, 1)) {
            Free_Dialog_ਅੰਕੜੇ(dialog);
            ਵਾਪਸ ਨਿਰਾ;
        }

        // font typeface.
        ਜੇ (!ਜੋੜੋ_Dialog_String(dialog, NCM.lf_ਸੁਨੇਹਾ_Font.lfFaceName)) {
            Free_Dialog_ਅੰਕੜੇ(dialog);
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਵਾਪਸ dialog;
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
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *EscapeAmpersands(ਅੱਖਰ **dst, size_t *dstlen, ਅਚਲ ਅੱਖਰ *src)
{
    ਅੱਖਰ *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    ਜੇ (!src) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜਦੋਂ (src[srclen]) {
        ਜੇ (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    ਜੇ (ampcount == 0) {
        // Nothing to do.
        ਵਾਪਸ src;
    }
    ਜੇ (SIZE_MAX - srclen < ampcount) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        ਜੇ (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = ਨਿਰਾ;
        newdst = (ਅੱਖਰ *)SDL_malloc(*dstlen);
        ਜੇ (!newdst) {
            ਵਾਪਸ ਨਿਰਾ;
        }
        *dst = newdst;
    } ਨਹੀਂਤਾਂ {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    ਜਦੋਂ (srclen--) {
        ਜੇ (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    ਵਾਪਸ *dst;
}

ਸਥਿਰ ਦਸ਼ਮਲਵ WIN_GetContentScale(ਖਾਲੀ)
{
    ਪੂਰਨ dpi = 0;

#ਜੇ 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    ਜੇ (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (ਪੂਰਨ)hdpi_uint;
    }
#ਜੇ_ਅੰਤ
    ਜੇ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ਨਿਰਾ);
        ਜੇ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ਨਿਰਾ, hdc);
        }
    }
    ਜੇ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    ਵਾਪਸ dpi / (ਦਸ਼ਮਲਵ)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
ਸਥਿਰ bool WIN_Show_Old_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    WIN_Dialog_ਅੰਕੜੇ *dialog;
    ਪੂਰਨ i, x, y;
    HFONT DialogFont;
    ਮਾਪ_3 ਮਾਪ_2;
    RECT ਪਾਠ_ਮਾਪ;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    ਅੱਖਰ *ampescape = ਨਿਰਾ;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool ਨਤੀਜਾ;

    HWND ਮਾਪਾ_ਖਿੜਕੀ_2 = ਨਿਰਾ;

    ਅਚਲ ਦਸ਼ਮਲਵ scale = WIN_GetContentScale();
    ਅਚਲ ਪੂਰਨ Button_ਚੌੜਾਈ = (ਪੂਰਨ)SDL_roundf(88 * scale);
    ਅਚਲ ਪੂਰਨ Button_ਉਚਾਈ = (ਪੂਰਨ)SDL_roundf(26 * scale);
    ਅਚਲ ਪੂਰਨ ਪਾਠ_Margin = (ਪੂਰਨ)SDL_roundf(16 * scale);
    ਅਚਲ ਪੂਰਨ ButtonMargin = (ਪੂਰਨ)SDL_roundf(12 * scale);
    ਅਚਲ ਪੂਰਨ Icon_ਚੌੜਾਈ = GetSystemMetrics(SM_CXICON);
    ਅਚਲ ਪੂਰਨ Icon_ਉਚਾਈ = GetSystemMetrics(SM_CYICON);
    ਅਚਲ ਪੂਰਨ IconMargin = (ਪੂਰਨ)SDL_roundf(20 * scale);

    ਜੇ (messageboxdata->numbuttons > MAX_BUTTONS) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    ਚੋਣ (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ਹਾਲਤ SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        ਰੋਕੋ;
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
        NCM.cb_ਮਾਪ = ਆਕਾਰ(NCM);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);
        lf = NCM.lf_ਸੁਨੇਹਾ_Font;
        DialogFont = Create_Font_ਅਸਿੱਧਾ(&lf);
    }

    // Select the font in to our DC
    SelectObject(FontDC, DialogFont);

    {
        // Get the metrics to try and figure our DLU conversion.
        Get_ਪਾਠ_Metrics(FontDC, &TM);

        /* Calculation from the following documentation:
         * https://support.microsoft.com/en-gb/help/125681/how-to-calculate-dialog-base-units-with-non-system-based-font
         * This fixes bug 2137, dialog box calculation with a fixed-width system font
         */
        {
            ਮਾਪ_3 extent;
            Get_ਪਾਠ_Extent_Point32_A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_ਅਧਾਰ_Units_X = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_ਅਧਾਰ_Units_Y = TM.tm_ਉਚਾਈ;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8_ਮੰਜ਼ਿਲ_String_W(messageboxdata->ਸੁਨੇਹਾ);
    SDL_zero(ਪਾਠ_ਮਾਪ);
    Draw_ਪਾਠ_W(FontDC, wmessage, -1, &ਪਾਠ_ਮਾਪ, DT_CALCRECT | DT_ਖੱਬਾ | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    ਪਾਠ_ਮਾਪ.ਖੱਬਾ += ਪਾਠ_Margin;
    ਪਾਠ_ਮਾਪ.ਸੱਜਾ += ਪਾਠ_Margin + 2;
    ਪਾਠ_ਮਾਪ.ਸਿਖਰ += ਪਾਠ_Margin;
    ਪਾਠ_ਮਾਪ.bottom += ਪਾਠ_Margin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    ਮਾਪ_2.cx = ਪਾਠ_ਮਾਪ.ਸੱਜਾ - ਪਾਠ_ਮਾਪ.ਖੱਬਾ;
    ਮਾਪ_2.cy = ਪਾਠ_ਮਾਪ.bottom - ਪਾਠ_ਮਾਪ.ਸਿਖਰ;
    ਮਾਪ_2.cx += ਪਾਠ_Margin * 2;
    ਮਾਪ_2.cy += ਪਾਠ_Margin * 2;

    // Make dialog wider and shift text over for the icon.
    ਜੇ (icon) {
        ਮਾਪ_2.cx += IconMargin + Icon_ਚੌੜਾਈ;
        ਪਾਠ_ਮਾਪ.ਖੱਬਾ += IconMargin + Icon_ਚੌੜਾਈ;
        ਪਾਠ_ਮਾਪ.ਸੱਜਾ += IconMargin + Icon_ਚੌੜਾਈ;
    }

    // Ensure the size is wide enough for all of the buttons.
    ਜੇ (ਮਾਪ_2.cx < (LONG)messageboxdata->numbuttons * (Button_ਚੌੜਾਈ + ButtonMargin) + ButtonMargin) {
        ਮਾਪ_2.cx = (LONG)messageboxdata->numbuttons * (Button_ਚੌੜਾਈ + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    ਜੇ (icon && ਮਾਪ_2.cy < (LONG)IconMargin * 2 + Icon_ਉਚਾਈ) {
        ਮਾਪ_2.cy = (LONG)IconMargin * 2 + Icon_ਉਚਾਈ;
    }

    // Add vertical space for the buttons and border.
    ਮਾਪ_2.cy += Button_ਉਚਾਈ + ਪਾਠ_Margin;

    dialog = Create_Dialog_ਅੰਕੜੇ(ਮਾਪ_2.cx, ਮਾਪ_2.cy, messageboxdata->title);
    ਜੇ (!dialog) {
        ਵਾਪਸ false;
    }

    ਜੇ (icon && !ਜੋੜੋ_Dialog_Static_Icon(dialog, IconMargin, IconMargin, Icon_ਚੌੜਾਈ, Icon_ਉਚਾਈ, icon)) {
        Free_Dialog_ਅੰਕੜੇ(dialog);
        ਵਾਪਸ false;
    }

    ਜੇ (!ਜੋੜੋ_Dialog_Static_ਪਾਠ(dialog, ਪਾਠ_ਮਾਪ.ਖੱਬਾ, ਪਾਠ_ਮਾਪ.ਸਿਖਰ, ਪਾਠ_ਮਾਪ.ਸੱਜਾ - ਪਾਠ_ਮਾਪ.ਖੱਬਾ, ਪਾਠ_ਮਾਪ.bottom - ਪਾਠ_ਮਾਪ.ਸਿਖਰ, messageboxdata->ਸੁਨੇਹਾ)) {
        Free_Dialog_ਅੰਕੜੇ(dialog);
        ਵਾਪਸ false;
    }

    // Align the buttons to the right/bottom.
    x = ਮਾਪ_2.cx - (Button_ਚੌੜਾਈ + ButtonMargin) * messageboxdata->numbuttons;
    y = ਮਾਪ_2.cy - Button_ਉਚਾਈ - ButtonMargin;
    ਲਈ (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        ਅਚਲ ਅੱਖਰ *buttontext;
        ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ਖੱਬਾ_ਮੰਜ਼ਿਲ_ਸੱਜਾ) {
            sdlButton = &messageboxdata->buttons[i];
        } ਨਹੀਂਤਾਂ {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        ਜੇ (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            ਜੇ (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->ਪਾਠ);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        ਜੇ (!buttontext || !ਜੋੜੋ_Dialog_Button(dialog, x, y, Button_ਚੌੜਾਈ, Button_ਉਚਾਈ, buttontext, IDBUTTONINDEX0 + (ਪੂਰਨ)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_ਅੰਕੜੇ(dialog);
            SDL_free(ampescape);
            ਵਾਪਸ false;
        }

        x += Button_ਚੌੜਾਈ + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    ਜੇ (messageboxdata->ਖਿੜਕੀ) {
        ਮਾਪਾ_ਖਿੜਕੀ_2 = messageboxdata->ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    }

    rc = Dialog_Box_ਅਸਿੱਧਾ_Param(ਨਿਰਾ, (DLGTEMPLATE *)dialog->lpDialog, ਮਾਪਾ_ਖਿੜਕੀ_2, ਸੁਨੇਹਾ_Box_Dialog_Proc, (LPARAM)messageboxdata);
    ਜੇ (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ ਜੇ (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        ਨਤੀਜਾ = true;
        *buttonID = -1;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (rc == 0) {
            SDL_ਸੈੱਟ_Error("Invalid parent window handle");
        } ਨਹੀਂਤਾਂ ਜੇ (rc == -1) {
            SDL_ਸੈੱਟ_Error("The message box encountered an error.");
        } ਨਹੀਂਤਾਂ ਜੇ (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_ਸੈੱਟ_Error("Invalid message box pointer in dialog procedure");
        } ਨਹੀਂਤਾਂ ਜੇ (rc == IDINVALPTRDLGITEM) {
            SDL_ਸੈੱਟ_Error("Couldn't find dialog control of the default enter-key button");
        } ਨਹੀਂਤਾਂ {
            SDL_ਸੈੱਟ_Error("An unknown error occurred");
        }
        ਨਤੀਜਾ = false;
    }

    Free_Dialog_ਅੰਕੜੇ(dialog);
    ਵਾਪਸ ਨਤੀਜਾ;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
ਕਿਸਮਪਰਿਭਾਸ਼ਾ HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(ਅਚਲ TASKDIALOGCONFIG *pTaskConfig, ਪੂਰਨ *pnButton, ਪੂਰਨ *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    HWND ਮਾਪਾ_ਖਿੜਕੀ_2 = ਨਿਰਾ;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC p_Task_Dialog_ਅਸਿੱਧਾ;
    HRESULT hr;
    ਅੱਖਰ *ampescape = ਨਿਰਾ;
    size_t ampescapesize = 0;
    ਪੂਰਨ nButton;
    ਪੂਰਨ nCancelButton;
    ਪੂਰਨ i;
    bool ਨਤੀਜਾ = false;

    ਜੇ (SIZE_MAX / ਆਕਾਰ(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        ਵਾਪਸ SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
    }

    HMODULE hUser32 = GetModuleHandle(ਪਾਠ_2("user32.dll"));
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ DPI_AWARENESS_CONTEXT (WINAPI *pfn_ਸੈੱਟ_Thread_Dpi_Awareness_Context)(DPI_AWARENESS_CONTEXT);
    pfn_ਸੈੱਟ_Thread_Dpi_Awareness_Context p_ਸੈੱਟ_Thread_Dpi_Awareness_Context = (pfn_ਸੈੱਟ_Thread_Dpi_Awareness_Context)Get_Proc_ਪਤਾ(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT ਪਿਛਲਾ_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    ਜੇ (p_ਸੈੱਟ_Thread_Dpi_Awareness_Context) {
        ਪਿਛਲਾ_context = p_ਸੈੱਟ_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_ਪ੍ਰਤੀ_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = ਲੱਦੋ_Library(ਪਾਠ_2("comctl32.dll"));
    ਜੇ (!hComctl32) {
        ਨਤੀਜਾ = WIN_Show_Old_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID);
        ਜਾਓ ਪੂਰਾ;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    p_Task_Dialog_ਅਸਿੱਧਾ = (TASKDIALOGINDIRECTPROC)Get_Proc_ਪਤਾ(hComctl32, "TaskDialogIndirect");
    ਜੇ (!p_Task_Dialog_ਅਸਿੱਧਾ) {
        FreeLibrary(hComctl32);
        ਨਤੀਜਾ = WIN_Show_Old_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID);
        ਜਾਓ ਪੂਰਾ;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    ਜੇ (messageboxdata->ਖਿੜਕੀ) {
        ਮਾਪਾ_ਖਿੜਕੀ_2 = messageboxdata->ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->hwnd;
    }

    wmessage = WIN_UTF8_ਮੰਜ਼ਿਲ_String_W(messageboxdata->ਸੁਨੇਹਾ);
    wtitle = WIN_UTF8_ਮੰਜ਼ਿਲ_String_W(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_ਮਾਪ = ਆਕਾਰ(TASKDIALOGCONFIG);
    TaskConfig.hwnd_ਮਾਪਾ = ਮਾਪਾ_ਖਿੜਕੀ_2;
    TaskConfig.dwFlags = TDF_ਮਾਪ_ਮੰਜ਼ਿਲ_CONTENT;
    TaskConfig.psz_ਖਿੜਕੀ_Title = wtitle;
    ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } ਨਹੀਂਤਾਂ ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } ਨਹੀਂਤਾਂ ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } ਨਹੀਂਤਾਂ {
        TaskConfig.pszMainIcon = ਨਿਰਾ;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(ਆਕਾਰ(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    ਲਈ (i = 0; i < messageboxdata->numbuttons; i++) {
        ਅਚਲ ਅੱਖਰ *buttontext;
        ਜੇ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ਖੱਬਾ_ਮੰਜ਼ਿਲ_ਸੱਜਾ) {
            pButton = &pButtons[i];
        } ਨਹੀਂਤਾਂ {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        ਜੇ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } ਨਹੀਂਤਾਂ {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].ਪਾਠ);
        ਜੇ (!buttontext) {
            ਪੂਰਨ j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            ਲਈ (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].psz_Button_ਪਾਠ);
            }
            SDL_free(pButtons);
            ਵਾਪਸ false;
        }
        pButton->psz_Button_ਪਾਠ = WIN_UTF8_ਮੰਜ਼ਿਲ_String_W(buttontext);
        ਜੇ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = p_Task_Dialog_ਅਸਿੱਧਾ(&TaskConfig, &nButton, ਨਿਰਾ, ਨਿਰਾ);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    ਲਈ (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].psz_Button_ਪਾਠ);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    ਜੇ (SUCCEEDED(hr)) {
        ਜੇ (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } ਨਹੀਂਤਾਂ ਜੇ (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } ਨਹੀਂਤਾਂ {
            *buttonID = -1;
        }
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ {
        // We failed showing the Task Dialog, use the old message box!
        ਨਤੀਜਾ = WIN_Show_Old_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID);
    }

ਪੂਰਾ:
    ਜੇ (p_ਸੈੱਟ_Thread_Dpi_Awareness_Context) {
        p_ਸੈੱਟ_Thread_Dpi_Awareness_Context(ਪਿਛਲਾ_context);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS

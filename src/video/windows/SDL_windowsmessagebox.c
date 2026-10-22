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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#నిర్వచితమైతే HAVE_LIMITS_H
#అన్తర్భావ <limits.h>
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే SIZE_MAX
#నిర్వచించు SIZE_MAX ((size_t)-1)
#అయితే_ముగింపు

#అన్తర్భావ "../../core/windows/SDL_windows.h"

#అన్తర్భావ "SDL_windowsvideo.h"

#నిర్వచితం_కాకపోతే SS_EDITCONTROL
#నిర్వచించు SS_EDITCONTROL 0x2000
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే IDOK
#నిర్వచించు IDOK 1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే IDCANCEL
#నిర్వచించు IDCANCEL 2
#అయితే_ముగింపు

// Custom dialog return codes
#నిర్వచించు IDCLOSED           20
#నిర్వచించు IDINVALPTRINIT     50
#నిర్వచించు IDINVALPTRCOMMAND  51
#నిర్వచించు IDINVALPTRSETFOCUS 52
#నిర్వచించు IDINVALPTRDLGITEM  53
// First button ID
#నిర్వచించు IDBUTTONINDEX0 100

#నిర్వచించు DLGITEMTYPEBUTTON 0x0080
#నిర్వచించు DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#నిర్వచించు MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

రకనిర్వచనం HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT సందేశం_2, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_దత్తాంశం);

గణన _TASKDIALOG_FLAGS
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
    TDF_SHOW_పురోగతి_BAR = 0x0200,
    TDF_SHOW_MARQUEE_పురోగతి_BAR = 0x0400,
    TDF_CALLBACK_TIMER = 0x0800,
    TDF_POSITION_RELATIVE_గమ్యం_కిటికీ = 0x1000,
    TDF_RTL_LAYOUT = 0x2000,
    TDF_NO_DEFAULT_RADIO_BUTTON = 0x4000,
    TDF_CAN_BE_MINIMIZED = 0x8000,
    // #if (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_NO_సమితి_FOREGROUND = 0x00010000, // Don't call SetForegroundWindow() when activating the dialog
                                        // #endif // (NTDDI_VERSION >= NTDDI_WIN8)
    TDF_కొలత_గమ్యం_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
రకనిర్వచనం పూర్ణాంకం TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

రకనిర్వచనం గణన _TASKDIALOG_MESSAGES
{
    TDM_NAVIGATE_పుట = WM_USER + 101,
    TDM_CLICK_BUTTON = WM_USER + 102,                        // wParam = Button ID
    TDM_సమితి_MARQUEE_పురోగతి_BAR = WM_USER + 103,            // wParam = 0 (nonMarque) wParam != 0 (Marquee)
    TDM_సమితి_పురోగతి_BAR_STATE = WM_USER + 104,              // wParam = new progress state
    TDM_సమితి_పురోగతి_BAR_RANGE = WM_USER + 105,              // lParam = MAKELPARAM(nMinRange, nMaxRange)
    TDM_సమితి_పురోగతి_BAR_POS = WM_USER + 106,                // wParam = new position
    TDM_సమితి_పురోగతి_BAR_MARQUEE = WM_USER + 107,            // wParam = 0 (stop marquee), wParam != 0 (start marquee), lparam = speed (milliseconds between repaints)
    TDM_సమితి_ELEMENT_పాఠ్యం = WM_USER + 108,                    // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_CLICK_RADIO_BUTTON = WM_USER + 110,                  // wParam = Radio Button ID
    TDM_ENABLE_BUTTON = WM_USER + 111,                       // lParam = 0 (disable), lParam != 0 (enable), wParam = Button ID
    TDM_ENABLE_RADIO_BUTTON = WM_USER + 112,                 // lParam = 0 (disable), lParam != 0 (enable), wParam = Radio Button ID
    TDM_CLICK_VERIFICATION = WM_USER + 113,                  // wParam = 0 (unchecked), 1 (checked), lParam = 1 (set key focus)
    TDM_UPDATE_ELEMENT_పాఠ్యం = WM_USER + 114,                 // wParam = element (TASKDIALOG_ELEMENTS), lParam = new element text (LPCWSTR)
    TDM_సమితి_BUTTON_ELEVATION_REQUIRED_STATE = WM_USER + 115, // wParam = Button ID, lParam = 0 (elevation not required), lParam != 0 (elevation required)
    TDM_UPDATE_ICON = WM_USER + 116                          // wParam = icon element (TASKDIALOG_ICON_ELEMENTS), lParam = new icon (hIcon if TDF_USE_HICON_* was set, PCWSTR otherwise)
} TASKDIALOG_MESSAGES;

రకనిర్వచనం గణన _TASKDIALOG_NOTIFICATIONS
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

రకనిర్వచనం గణన _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

రకనిర్వచనం గణన _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#నిర్వచించు TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#నిర్వచించు TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#నిర్వచించు TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#నిర్వచించు TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

గణన _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
రకనిర్వచనం పూర్ణాంకం TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#సూచన pack(నెట్టు, 1)

రకనిర్వచనం నిర్మాణం _TASKDIALOG_BUTTON
{
    పూర్ణాంకం nButtonID;
    PCWSTR psz_Button_పాఠ్యం;
} TASKDIALOG_BUTTON;

రకనిర్వచనం నిర్మాణం _TASKDIALOGCONFIG
{
    UINT cb_కొలత;
    HWND hwnd_మాతృ;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR psz_కిటికీ_Title;                          // string or MAKEINTRESOURCE()
    సంఘం
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    స్థిరరాశి TASKDIALOG_BUTTON *pButtons;
    పూర్ణాంకం nDefaultButton;
    UINT cRadioButtons;
    స్థిరరాశి TASKDIALOG_BUTTON *pRadioButtons;
    పూర్ణాంకం nDefaultRadioButton;
    PCWSTR psz_Verification_పాఠ్యం;
    PCWSTR pszExpandedInformation;
    PCWSTR psz_Expanded_Control_పాఠ్యం;
    PCWSTR psz_Collapsed_Control_పాఠ్యం;
    సంఘం
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lp_Callback_దత్తాంశం;
    UINT cx_వెడల్పు; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

రకనిర్వచనం నిర్మాణం
{
    మాట dlgVer;
    మాట signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    మాట c_Dlg_వస్తువులు;
    పొట్టి x;
    పొట్టి y;
    పొట్టి cx;
    పొట్టి cy;
} DLGTEMPLATEEX;

రకనిర్వచనం నిర్మాణం
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    పొట్టి x;
    పొట్టి y;
    పొట్టి cx;
    పొట్టి cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#సూచన pack(తీయి)

రకనిర్వచనం నిర్మాణం
{
    DLGTEMPLATEEX *lpDialog;
    శూన్య *దత్తాంశం;
    size_t కొలత;
    size_t వాడిన;
    మాట numbuttons;
} WIN_Dialog_దత్తాంశం;

స్థిర bool Get_Button_సూచీ(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, SDL_సందేశం_Box_Button_Flags flags, size_t *i)
{
    కొరకు (*i = 0; *i < (size_t)messageboxdata->numbuttons; ++*i) {
        ఒకవేళ (messageboxdata->buttons[*i].flags & flags) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

స్థిర INT_PTR CALLBACK సందేశం_Box_Dialog_Proc(HWND hDlg, UINT i_సందేశం, WPARAM wParam, LPARAM lParam)
{
    స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata;
    size_t buttonindex;

    ఎంపిక (i_సందేశం) {
    స్థితి WM_INITDIALOG:
        ఒకవేళ (lParam == 0) {
            చివర_Dialog(hDlg, IDINVALPTRINIT);
            తిరిగి TRUE;
        }
        messageboxdata = (స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *)lParam;
        సమితి_కిటికీ_Long_Ptr(hDlg, GWLP_USERDATA, lParam);

        ఒకవేళ (Get_Button_సూచీ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = Get_Dlg_అంశం(hDlg, (పూర్ణాంకం)(IDBUTTONINDEX0 + buttonindex));
            ఒకవేళ (!buttonctl) {
                చివర_Dialog(hDlg, IDINVALPTRDLGITEM);
            }
            Post_సందేశం(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } లేకపోతే {
            // Give the focus to the dialog window instead
            సమితి_Focus(hDlg);
        }
        తిరిగి FALSE;
    స్థితి WM_SETFOCUS:
        messageboxdata = (స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *)Get_కిటికీ_Long_Ptr(hDlg, GWLP_USERDATA);
        ఒకవేళ (!messageboxdata) {
            చివర_Dialog(hDlg, IDINVALPTRSETFOCUS);
            తిరిగి TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        ఒకవేళ (Get_Button_సూచీ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            తిరిగి FALSE;
        }
        తిరిగి TRUE;
    స్థితి WM_COMMAND:
        messageboxdata = (స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *)Get_కిటికీ_Long_Ptr(hDlg, GWLP_USERDATA);
        ఒకవేళ (!messageboxdata) {
            చివర_Dialog(hDlg, IDINVALPTRCOMMAND);
            తిరిగి TRUE;
        }

        // Return the ID of the button that was pushed
        ఒకవేళ (wParam == IDOK) {
            ఒకవేళ (Get_Button_సూచీ(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                చివర_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } లేకపోతే ఒకవేళ (wParam == IDCANCEL) {
            ఒకవేళ (Get_Button_సూచీ(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                చివర_Dialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } లేకపోతే {
                // Closing of window was requested by user or system. It would be rude not to comply.
                చివర_Dialog(hDlg, IDCLOSED);
            }
        } లేకపోతే ఒకవేళ (wParam >= IDBUTTONINDEX0 && (పూర్ణాంకం)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            చివర_Dialog(hDlg, wParam);
        }
        తిరిగి TRUE;

    అప్రమేయ:
        ఆపు;
    }
    తిరిగి FALSE;
}

స్థిర bool ExpandDialogSpace(WIN_Dialog_దత్తాంశం *dialog, size_t space)
{
    // Growing memory in 64 KiB steps.
    స్థిరరాశి size_t sizestep = 0x10000;
    size_t కొలత = dialog->కొలత;

    ఒకవేళ (కొలత == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        కొలత = 0x1000;
        ఒకవేళ (SIZE_MAX - sizestep < space) {
            కొలత = space;
        } లేకపోతే ఒకవేళ (space > కొలత) {
            కొలత = (space + sizestep) & ~(sizestep - 1);
        }
    } లేకపోతే ఒకవేళ (SIZE_MAX - dialog->వాడిన < space) {
        SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        తిరిగి false;
    } లేకపోతే ఒకవేళ (SIZE_MAX - (dialog->వాడిన + space) < sizestep) {
        // Close to the maximum.
        కొలత = dialog->వాడిన + space;
    } లేకపోతే ఒకవేళ (కొలత < dialog->వాడిన + space) {
        // Round up to the next 64 KiB block.
        కొలత = dialog->వాడిన + space;
        కొలత += sizestep - కొలత % sizestep;
    }

    ఒకవేళ (కొలత > dialog->కొలత) {
        శూన్య *దత్తాంశం = SDL_realloc(dialog->దత్తాంశం, కొలత);
        ఒకవేళ (!దత్తాంశం) {
            తిరిగి false;
        }
        dialog->దత్తాంశం = దత్తాంశం;
        dialog->కొలత = కొలత;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->దత్తాంశం;
    }
    తిరిగి true;
}

స్థిర bool Align_Dialog_దత్తాంశం(WIN_Dialog_దత్తాంశం *dialog, size_t కొలత)
{
    size_t padding = (dialog->వాడిన % కొలత);

    ఒకవేళ (!ExpandDialogSpace(dialog, padding)) {
        తిరిగి false;
    }

    dialog->వాడిన += padding;

    తిరిగి true;
}

స్థిర bool కూడు_Dialog_దత్తాంశం(WIN_Dialog_దత్తాంశం *dialog, స్థిరరాశి శూన్య *దత్తాంశం, size_t కొలత)
{
    ఒకవేళ (!ExpandDialogSpace(dialog, కొలత)) {
        తిరిగి false;
    }

    SDL_memcpy((Uint8 *)dialog->దత్తాంశం + dialog->వాడిన, దత్తాంశం, కొలత);
    dialog->వాడిన += కొలత;

    తిరిగి true;
}

స్థిర bool కూడు_Dialog_String(WIN_Dialog_దత్తాంశం *dialog, స్థిరరాశి అక్షరం *string)
{
    WCHAR *wstring;
    WCHAR *p;
    size_t లెక్క;
    bool స్థితి_2;

    ఒకవేళ (!string) {
        string = "";
    }

    wstring = WIN_UTF8_గమ్యం_String_W(string);
    ఒకవేళ (!wstring) {
        తిరిగి false;
    }

    // Find out how many characters we have, including null terminator
    లెక్క = 0;
    కొరకు (p = wstring; *p; ++p) {
        ++లెక్క;
    }
    ++లెక్క;

    స్థితి_2 = కూడు_Dialog_దత్తాంశం(dialog, wstring, లెక్క * పరిమాణం(WCHAR));
    SDL_free(wstring);
    తిరిగి స్థితి_2;
}

స్థిర పూర్ణాంకం s_పునాది_Units_X;
స్థిర పూర్ణాంకం s_పునాది_Units_Y;
స్థిర శూన్య Vec2_గమ్యం_DLU(పొట్టి *x, పొట్టి *y)
{
    SDL_assert(s_పునాది_Units_X != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (పొట్టి)MulDiv(*x, 4, s_పునాది_Units_X);
    *y = (పొట్టి)MulDiv(*y, 8, s_పునాది_Units_Y);
}

స్థిర bool కూడు_Dialog_Control(WIN_Dialog_దత్తాంశం *dialog, మాట type, DWORD style, DWORD exStyle, పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం id, స్థిరరాశి అక్షరం *caption, మాట ordinal)
{
    DLGITEMTEMPLATEEX అంశం;
    మాట marker = 0xFFFF;
    మాట extra_దత్తాంశం = 0;

    SDL_zero(అంశం);
    అంశం.style = style;
    అంశం.exStyle = exStyle;
    అంశం.x = (పొట్టి)x;
    అంశం.y = (పొట్టి)y;
    అంశం.cx = (పొట్టి)w;
    అంశం.cy = (పొట్టి)h;
    అంశం.id = id;

    Vec2_గమ్యం_DLU(&అంశం.x, &అంశం.y);
    Vec2_గమ్యం_DLU(&అంశం.cx, &అంశం.cy);

    ఒకవేళ (!Align_Dialog_దత్తాంశం(dialog, పరిమాణం(DWORD))) {
        తిరిగి false;
    }
    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &అంశం, పరిమాణం(అంశం))) {
        తిరిగి false;
    }
    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &marker, పరిమాణం(marker))) {
        తిరిగి false;
    }
    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &type, పరిమాణం(type))) {
        తిరిగి false;
    }
    ఒకవేళ (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        ఒకవేళ (!కూడు_Dialog_String(dialog, caption)) {
            తిరిగి false;
        }
    } లేకపోతే {
        ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &marker, పరిమాణం(marker))) {
            తిరిగి false;
        }
        ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &ordinal, పరిమాణం(ordinal))) {
            తిరిగి false;
        }
    }
    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &extra_దత్తాంశం, పరిమాణం(extra_దత్తాంశం))) {
        తిరిగి false;
    }
    ఒకవేళ (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_వస్తువులు;

    తిరిగి true;
}

స్థిర bool కూడు_Dialog_Static_పాఠ్యం(WIN_Dialog_దత్తాంశం *dialog, పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం w, పూర్ణాంకం h, స్థిరరాశి అక్షరం *పాఠ్యం)
{
    DWORD style = WS_VISIBLE | WS_బిడ్డ | SS_ఎడమ | SS_NOPREFIX | SS_EDITCONTROL | WS_సమూహం;
    తిరిగి కూడు_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, పాఠ్యం, 0);
}

స్థిర bool కూడు_Dialog_Static_Icon(WIN_Dialog_దత్తాంశం *dialog, పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం w, పూర్ణాంకం h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_బిడ్డ | SS_ICON | WS_సమూహం;
    తిరిగి కూడు_Dialog_Control(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, ఖాళీ, ordinal);
}

స్థిర bool కూడు_Dialog_Button(WIN_Dialog_దత్తాంశం *dialog, పూర్ణాంకం x, పూర్ణాంకం y, పూర్ణాంకం w, పూర్ణాంకం h, స్థిరరాశి అక్షరం *పాఠ్యం, పూర్ణాంకం id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_బిడ్డ | WS_TABSTOP;
    ఒకవేళ (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } లేకపోతే {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    ఒకవేళ (dialog->numbuttons == 0) {
        style |= WS_సమూహం;
    }
    తిరిగి కూడు_Dialog_Control(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, పాఠ్యం, 0);
}

స్థిర శూన్య Free_Dialog_దత్తాంశం(WIN_Dialog_దత్తాంశం *dialog)
{
    SDL_free(dialog->దత్తాంశం);
    SDL_free(dialog);
}

స్థిర WIN_Dialog_దత్తాంశం *Create_Dialog_దత్తాంశం(పూర్ణాంకం w, పూర్ణాంకం h, స్థిరరాశి అక్షరం *caption)
{
    WIN_Dialog_దత్తాంశం *dialog;
    DLGTEMPLATEEX dialogTemplate;
    మాట మాట_గమ్యం_Pass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (పొట్టి)w;
    dialogTemplate.cy = (పొట్టి)h;
    Vec2_గమ్యం_DLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*dialog));
    ఒకవేళ (!dialog) {
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &dialogTemplate, పరిమాణం(dialogTemplate))) {
        Free_Dialog_దత్తాంశం(dialog);
        తిరిగి ఖాళీ;
    }

    // No menu
    మాట_గమ్యం_Pass = 0;
    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &మాట_గమ్యం_Pass, 2)) {
        Free_Dialog_దత్తాంశం(dialog);
        తిరిగి ఖాళీ;
    }

    // No custom class
    ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &మాట_గమ్యం_Pass, 2)) {
        Free_Dialog_దత్తాంశం(dialog);
        తిరిగి ఖాళీ;
    }

    // title
    ఒకవేళ (!కూడు_Dialog_String(dialog, caption)) {
        Free_Dialog_దత్తాంశం(dialog);
        తిరిగి ఖాళీ;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE గమ్యం_Pass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_కొలత = పరిమాణం(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(ఖాళీ);
            పూర్ణాంకం LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            ఒకవేళ (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            మాట_గమ్యం_Pass = (మాట)(-72 * NCM.lf_సందేశం_Font.lf_ఎత్తు / LogicalPixelsY);
            ReleaseDC(ఖాళీ, ScreenDC);
        }

        ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &మాట_గమ్యం_Pass, 2)) {
            Free_Dialog_దత్తాంశం(dialog);
            తిరిగి ఖాళీ;
        }

        // Font weight
        మాట_గమ్యం_Pass = (మాట)NCM.lf_సందేశం_Font.lf_బరువు;
        ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &మాట_గమ్యం_Pass, 2)) {
            Free_Dialog_దత్తాంశం(dialog);
            తిరిగి ఖాళీ;
        }

        // italic?
        గమ్యం_Pass = NCM.lf_సందేశం_Font.lfItalic;
        ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &గమ్యం_Pass, 1)) {
            Free_Dialog_దత్తాంశం(dialog);
            తిరిగి ఖాళీ;
        }

        // charset?
        గమ్యం_Pass = NCM.lf_సందేశం_Font.lf_Char_సమితి;
        ఒకవేళ (!కూడు_Dialog_దత్తాంశం(dialog, &గమ్యం_Pass, 1)) {
            Free_Dialog_దత్తాంశం(dialog);
            తిరిగి ఖాళీ;
        }

        // font typeface.
        ఒకవేళ (!కూడు_Dialog_String(dialog, NCM.lf_సందేశం_Font.lfFaceName)) {
            Free_Dialog_దత్తాంశం(dialog);
            తిరిగి ఖాళీ;
        }
    }

    తిరిగి dialog;
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
స్థిర స్థిరరాశి అక్షరం *EscapeAmpersands(అక్షరం **dst, size_t *dstlen, స్థిరరాశి అక్షరం *src)
{
    అక్షరం *newdst;
    size_t ampcount = 0;
    size_t srclen = 0;

    ఒకవేళ (!src) {
        తిరిగి ఖాళీ;
    }

    అయితే (src[srclen]) {
        ఒకవేళ (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    ఒకవేళ (ampcount == 0) {
        // Nothing to do.
        తిరిగి src;
    }
    ఒకవేళ (SIZE_MAX - srclen < ampcount) {
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        size_t extraspace = SIZE_MAX - (srclen + ampcount);
        ఒకవేళ (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = ఖాళీ;
        newdst = (అక్షరం *)SDL_malloc(*dstlen);
        ఒకవేళ (!newdst) {
            తిరిగి ఖాళీ;
        }
        *dst = newdst;
    } లేకపోతే {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    అయితే (srclen--) {
        ఒకవేళ (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    తిరిగి *dst;
}

స్థిర దశాంశం WIN_GetContentScale(శూన్య)
{
    పూర్ణాంకం dpi = 0;

#ఒకవేళ 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    ఒకవేళ (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (పూర్ణాంకం)hdpi_uint;
    }
#అయితే_ముగింపు
    ఒకవేళ (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(ఖాళీ);
        ఒకవేళ (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(ఖాళీ, hdc);
        }
    }
    ఒకవేళ (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    తిరిగి dpi / (దశాంశం)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
స్థిర bool WIN_Show_Old_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
    WIN_Dialog_దత్తాంశం *dialog;
    పూర్ణాంకం i, x, y;
    HFONT DialogFont;
    కొలత_3 కొలత_2;
    RECT పాఠ్యం_కొలత;
    wchar_t *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    అక్షరం *ampescape = ఖాళీ;
    size_t ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool ఫలితం;

    HWND మాతృ_కిటికీ_2 = ఖాళీ;

    స్థిరరాశి దశాంశం scale = WIN_GetContentScale();
    స్థిరరాశి పూర్ణాంకం Button_వెడల్పు = (పూర్ణాంకం)SDL_roundf(88 * scale);
    స్థిరరాశి పూర్ణాంకం Button_ఎత్తు = (పూర్ణాంకం)SDL_roundf(26 * scale);
    స్థిరరాశి పూర్ణాంకం పాఠ్యం_Margin = (పూర్ణాంకం)SDL_roundf(16 * scale);
    స్థిరరాశి పూర్ణాంకం ButtonMargin = (పూర్ణాంకం)SDL_roundf(12 * scale);
    స్థిరరాశి పూర్ణాంకం Icon_వెడల్పు = GetSystemMetrics(SM_CXICON);
    స్థిరరాశి పూర్ణాంకం Icon_ఎత్తు = GetSystemMetrics(SM_CYICON);
    స్థిరరాశి పూర్ణాంకం IconMargin = (పూర్ణాంకం)SDL_roundf(20 * scale);

    ఒకవేళ (messageboxdata->numbuttons > MAX_BUTTONS) {
        తిరిగి SDL_సమితి_Error("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    ఎంపిక (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    స్థితి SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(size_t)IDI_ERROR;
        ఆపు;
    స్థితి SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(size_t)IDI_WARNING;
        ఆపు;
    స్థితి SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(size_t)IDI_INFORMATION;
        ఆపు;
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
        NCM.cb_కొలత = పరిమాణం(NCM);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);
        lf = NCM.lf_సందేశం_Font;
        DialogFont = Create_Font_పరోక్ష(&lf);
    }

    // Select the font in to our DC
    SelectObject(FontDC, DialogFont);

    {
        // Get the metrics to try and figure our DLU conversion.
        Get_పాఠ్యం_Metrics(FontDC, &TM);

        /* Calculation from the following documentation:
         * https://support.microsoft.com/en-gb/help/125681/how-to-calculate-dialog-base-units-with-non-system-based-font
         * This fixes bug 2137, dialog box calculation with a fixed-width system font
         */
        {
            కొలత_3 extent;
            Get_పాఠ్యం_Extent_Point32_A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_పునాది_Units_X = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_పునాది_Units_Y = TM.tm_ఎత్తు;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8_గమ్యం_String_W(messageboxdata->సందేశం);
    SDL_zero(పాఠ్యం_కొలత);
    Draw_పాఠ్యం_W(FontDC, wmessage, -1, &పాఠ్యం_కొలత, DT_CALCRECT | DT_ఎడమ | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    పాఠ్యం_కొలత.ఎడమ += పాఠ్యం_Margin;
    పాఠ్యం_కొలత.కుడి += పాఠ్యం_Margin + 2;
    పాఠ్యం_కొలత.శిఖరం += పాఠ్యం_Margin;
    పాఠ్యం_కొలత.bottom += పాఠ్యం_Margin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    కొలత_2.cx = పాఠ్యం_కొలత.కుడి - పాఠ్యం_కొలత.ఎడమ;
    కొలత_2.cy = పాఠ్యం_కొలత.bottom - పాఠ్యం_కొలత.శిఖరం;
    కొలత_2.cx += పాఠ్యం_Margin * 2;
    కొలత_2.cy += పాఠ్యం_Margin * 2;

    // Make dialog wider and shift text over for the icon.
    ఒకవేళ (icon) {
        కొలత_2.cx += IconMargin + Icon_వెడల్పు;
        పాఠ్యం_కొలత.ఎడమ += IconMargin + Icon_వెడల్పు;
        పాఠ్యం_కొలత.కుడి += IconMargin + Icon_వెడల్పు;
    }

    // Ensure the size is wide enough for all of the buttons.
    ఒకవేళ (కొలత_2.cx < (LONG)messageboxdata->numbuttons * (Button_వెడల్పు + ButtonMargin) + ButtonMargin) {
        కొలత_2.cx = (LONG)messageboxdata->numbuttons * (Button_వెడల్పు + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    ఒకవేళ (icon && కొలత_2.cy < (LONG)IconMargin * 2 + Icon_ఎత్తు) {
        కొలత_2.cy = (LONG)IconMargin * 2 + Icon_ఎత్తు;
    }

    // Add vertical space for the buttons and border.
    కొలత_2.cy += Button_ఎత్తు + పాఠ్యం_Margin;

    dialog = Create_Dialog_దత్తాంశం(కొలత_2.cx, కొలత_2.cy, messageboxdata->title);
    ఒకవేళ (!dialog) {
        తిరిగి false;
    }

    ఒకవేళ (icon && !కూడు_Dialog_Static_Icon(dialog, IconMargin, IconMargin, Icon_వెడల్పు, Icon_ఎత్తు, icon)) {
        Free_Dialog_దత్తాంశం(dialog);
        తిరిగి false;
    }

    ఒకవేళ (!కూడు_Dialog_Static_పాఠ్యం(dialog, పాఠ్యం_కొలత.ఎడమ, పాఠ్యం_కొలత.శిఖరం, పాఠ్యం_కొలత.కుడి - పాఠ్యం_కొలత.ఎడమ, పాఠ్యం_కొలత.bottom - పాఠ్యం_కొలత.శిఖరం, messageboxdata->సందేశం)) {
        Free_Dialog_దత్తాంశం(dialog);
        తిరిగి false;
    }

    // Align the buttons to the right/bottom.
    x = కొలత_2.cx - (Button_వెడల్పు + ButtonMargin) * messageboxdata->numbuttons;
    y = కొలత_2.cy - Button_ఎత్తు - ButtonMargin;
    కొరకు (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        స్థిరరాశి అక్షరం *buttontext;
        స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ఎడమ_గమ్యం_కుడి) {
            sdlButton = &messageboxdata->buttons[i];
        } లేకపోతే {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        ఒకవేళ (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            ఒకవేళ (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->పాఠ్యం);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        ఒకవేళ (!buttontext || !కూడు_Dialog_Button(dialog, x, y, Button_వెడల్పు, Button_ఎత్తు, buttontext, IDBUTTONINDEX0 + (పూర్ణాంకం)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_దత్తాంశం(dialog);
            SDL_free(ampescape);
            తిరిగి false;
        }

        x += Button_వెడల్పు + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    ఒకవేళ (messageboxdata->కిటికీ) {
        మాతృ_కిటికీ_2 = messageboxdata->కిటికీ->అంతర్గత->hwnd;
    }

    rc = Dialog_Box_పరోక్ష_Param(ఖాళీ, (DLGTEMPLATE *)dialog->lpDialog, మాతృ_కిటికీ_2, సందేశం_Box_Dialog_Proc, (LPARAM)messageboxdata);
    ఒకవేళ (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        ఫలితం = true;
    } లేకపోతే ఒకవేళ (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        ఫలితం = true;
        *buttonID = -1;
    } లేకపోతే {
        ఒకవేళ (rc == 0) {
            SDL_సమితి_Error("Invalid parent window handle");
        } లేకపోతే ఒకవేళ (rc == -1) {
            SDL_సమితి_Error("The message box encountered an error.");
        } లేకపోతే ఒకవేళ (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_సమితి_Error("Invalid message box pointer in dialog procedure");
        } లేకపోతే ఒకవేళ (rc == IDINVALPTRDLGITEM) {
            SDL_సమితి_Error("Couldn't find dialog control of the default enter-key button");
        } లేకపోతే {
            SDL_సమితి_Error("An unknown error occurred");
        }
        ఫలితం = false;
    }

    Free_Dialog_దత్తాంశం(dialog);
    తిరిగి ఫలితం;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
రకనిర్వచనం HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(స్థిరరాశి TASKDIALOGCONFIG *pTaskConfig, పూర్ణాంకం *pnButton, పూర్ణాంకం *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
    HWND మాతృ_కిటికీ_2 = ఖాళీ;
    wchar_t *wmessage;
    wchar_t *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC p_Task_Dialog_పరోక్ష;
    HRESULT hr;
    అక్షరం *ampescape = ఖాళీ;
    size_t ampescapesize = 0;
    పూర్ణాంకం nButton;
    పూర్ణాంకం nCancelButton;
    పూర్ణాంకం i;
    bool ఫలితం = false;

    ఒకవేళ (SIZE_MAX / పరిమాణం(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        తిరిగి SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
    }

    HMODULE hUser32 = GetModuleHandle(పాఠ్యం_2("user32.dll"));
    రకనిర్వచనం DPI_AWARENESS_CONTEXT (WINAPI *pfn_సమితి_Thread_Dpi_Awareness_Context)(DPI_AWARENESS_CONTEXT);
    pfn_సమితి_Thread_Dpi_Awareness_Context p_సమితి_Thread_Dpi_Awareness_Context = (pfn_సమితి_Thread_Dpi_Awareness_Context)Get_Proc_చిరునామా(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT మునుపటి_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    ఒకవేళ (p_సమితి_Thread_Dpi_Awareness_Context) {
        మునుపటి_context = p_సమితి_Thread_Dpi_Awareness_Context(DPI_AWARENESS_CONTEXT_చొప్పున_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = ఎక్కించు_Library(పాఠ్యం_2("comctl32.dll"));
    ఒకవేళ (!hComctl32) {
        ఫలితం = WIN_Show_Old_సందేశం_Box(messageboxdata, buttonID);
        వెళ్ళు పూర్తి;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    p_Task_Dialog_పరోక్ష = (TASKDIALOGINDIRECTPROC)Get_Proc_చిరునామా(hComctl32, "TaskDialogIndirect");
    ఒకవేళ (!p_Task_Dialog_పరోక్ష) {
        FreeLibrary(hComctl32);
        ఫలితం = WIN_Show_Old_సందేశం_Box(messageboxdata, buttonID);
        వెళ్ళు పూర్తి;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    ఒకవేళ (messageboxdata->కిటికీ) {
        మాతృ_కిటికీ_2 = messageboxdata->కిటికీ->అంతర్గత->hwnd;
    }

    wmessage = WIN_UTF8_గమ్యం_String_W(messageboxdata->సందేశం);
    wtitle = WIN_UTF8_గమ్యం_String_W(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_కొలత = పరిమాణం(TASKDIALOGCONFIG);
    TaskConfig.hwnd_మాతృ = మాతృ_కిటికీ_2;
    TaskConfig.dwFlags = TDF_కొలత_గమ్యం_CONTENT;
    TaskConfig.psz_కిటికీ_Title = wtitle;
    ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } లేకపోతే ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } లేకపోతే ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } లేకపోతే {
        TaskConfig.pszMainIcon = ఖాళీ;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(పరిమాణం(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    కొరకు (i = 0; i < messageboxdata->numbuttons; i++) {
        స్థిరరాశి అక్షరం *buttontext;
        ఒకవేళ (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_ఎడమ_గమ్యం_కుడి) {
            pButton = &pButtons[i];
        } లేకపోతే {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        ఒకవేళ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } లేకపోతే {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].పాఠ్యం);
        ఒకవేళ (!buttontext) {
            పూర్ణాంకం j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            కొరకు (j = 0; j < i; j++) {
                SDL_free((wchar_t *)pButtons[j].psz_Button_పాఠ్యం);
            }
            SDL_free(pButtons);
            తిరిగి false;
        }
        pButton->psz_Button_పాఠ్యం = WIN_UTF8_గమ్యం_String_W(buttontext);
        ఒకవేళ (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = p_Task_Dialog_పరోక్ష(&TaskConfig, &nButton, ఖాళీ, ఖాళీ);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    కొరకు (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((wchar_t *)pButtons[i].psz_Button_పాఠ్యం);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    ఒకవేళ (SUCCEEDED(hr)) {
        ఒకవేళ (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } లేకపోతే ఒకవేళ (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } లేకపోతే {
            *buttonID = -1;
        }
        ఫలితం = true;
    } లేకపోతే {
        // We failed showing the Task Dialog, use the old message box!
        ఫలితం = WIN_Show_Old_సందేశం_Box(messageboxdata, buttonID);
    }

పూర్తి:
    ఒకవేళ (p_సమితి_Thread_Dpi_Awareness_Context) {
        p_సమితి_Thread_Dpi_Awareness_Context(మునుపటి_context);
    }
    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS

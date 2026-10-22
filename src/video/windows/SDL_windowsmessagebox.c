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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अगर_घोषित HAVE_LIMITS_H
#समावेश <limits.h>
#पूर्ण_अगर
#अगर_अघोषित SIZE_MAX
#घोषणा SIZE_MAX ((माप_प्रकार)-1)
#पूर्ण_अगर

#समावेश "../../core/windows/SDL_windows.h"

#समावेश "SDL_windowsvideo.h"

#अगर_अघोषित SS_EDITCONTROL
#घोषणा SS_EDITCONTROL 0x2000
#पूर्ण_अगर

#अगर_अघोषित IDOK
#घोषणा IDOK 1
#पूर्ण_अगर

#अगर_अघोषित IDCANCEL
#घोषणा IDCANCEL 2
#पूर्ण_अगर

// Custom dialog return codes
#घोषणा IDCLOSED           20
#घोषणा IDINVALPTRINIT     50
#घोषणा IDINVALPTRCOMMAND  51
#घोषणा IDINVALPTRSETFOCUS 52
#घोषणा IDINVALPTRDLGITEM  53
// First button ID
#घोषणा IDBUTTONINDEX0 100

#घोषणा DLGITEMTYPEBUTTON 0x0080
#घोषणा DLGITEMTYPESTATIC 0x0082

/* Windows only sends the lower 16 bits of the control ID when a button
 * gets clicked. There are also some predefined and custom IDs that lower
 * the available number further. 2^16 - 101 buttons should be enough for
 * everyone, no need to make the code more complex.
 */
#घोषणा MAX_BUTTONS (0xffff - 100)

// Display a Windows message box

प्रकार HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam, LONG_PTR lp_Ref_तथ्य);

क्रमागत _TASKDIALOG_FLAGS
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
    TDF_आकार_TO_CONTENT = 0x01000000    // used by ShellMessageBox to emulate MessageBox sizing behavior
};
प्रकार पूर्णांक TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

प्रकार क्रमागत _TASKDIALOG_MESSAGES
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

प्रकार क्रमागत _TASKDIALOG_NOTIFICATIONS
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

प्रकार क्रमागत _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

प्रकार क्रमागत _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#घोषणा TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#घोषणा TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#घोषणा TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#घोषणा TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

क्रमागत _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
प्रकार पूर्णांक TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#आशय pack(धकेलो, 1)

प्रकार काष्ठा _TASKDIALOG_BUTTON
{
    पूर्णांक nButtonID;
    PCWSTR pszButtonText;
} TASKDIALOG_BUTTON;

प्रकार काष्ठा _TASKDIALOGCONFIG
{
    UINT cb_आकार;
    HWND hwndParent;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR pszWindowTitle;                          // string or MAKEINTRESOURCE()
    जोड़
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    स्थिर TASKDIALOG_BUTTON *pButtons;
    पूर्णांक nDefaultButton;
    UINT cRadioButtons;
    स्थिर TASKDIALOG_BUTTON *pRadioButtons;
    पूर्णांक nDefaultRadioButton;
    PCWSTR pszVerificationText;
    PCWSTR pszExpandedInformation;
    PCWSTR pszExpandedControlText;
    PCWSTR pszCollapsedControlText;
    जोड़
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lp_Callback_तथ्य;
    UINT cxWidth; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

प्रकार काष्ठा
{
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD c_Dlg_वस्तुएँ;
    लघु x;
    लघु y;
    लघु cx;
    लघु cy;
} DLGTEMPLATEEX;

प्रकार काष्ठा
{
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    लघु x;
    लघु y;
    लघु cx;
    लघु cy;
    DWORD id;
} DLGITEMTEMPLATEEX;

#आशय pack(निकालो)

प्रकार काष्ठा
{
    DLGTEMPLATEEX *lpDialog;
    व्योम *तथ्य;
    माप_प्रकार आकार;
    माप_प्रकार used;
    WORD numbuttons;
} WIN_Dialog_तथ्य;

अटल bool Get_Button_सूचकांक(स्थिर SDL_Message_Box_तथ्य *messageboxdata, SDL_MessageBoxButtonFlags flags, माप_प्रकार *i)
{
    क्रम (*i = 0; *i < (माप_प्रकार)messageboxdata->numbuttons; ++*i) {
        अगर (messageboxdata->buttons[*i].flags & flags) {
            वापस true;
        }
    }
    वापस false;
}

अटल INT_PTR CALLBACK MessageBoxDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    स्थिर SDL_Message_Box_तथ्य *messageboxdata;
    माप_प्रकार buttonindex;

    चयन (iMessage) {
    हाल WM_INITDIALOG:
        अगर (lParam == 0) {
            EndDialog(hDlg, IDINVALPTRINIT);
            वापस TRUE;
        }
        messageboxdata = (स्थिर SDL_Message_Box_तथ्य *)lParam;
        SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);

        अगर (Get_Button_सूचकांक(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = GetDlgItem(hDlg, (पूर्णांक)(IDBUTTONINDEX0 + buttonindex));
            अगर (!buttonctl) {
                EndDialog(hDlg, IDINVALPTRDLGITEM);
            }
            PostMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } अन्यथा {
            // Give the focus to the dialog window instead
            SetFocus(hDlg);
        }
        वापस FALSE;
    हाल WM_SETFOCUS:
        messageboxdata = (स्थिर SDL_Message_Box_तथ्य *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        अगर (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRSETFOCUS);
            वापस TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        अगर (Get_Button_सूचकांक(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            वापस FALSE;
        }
        वापस TRUE;
    हाल WM_COMMAND:
        messageboxdata = (स्थिर SDL_Message_Box_तथ्य *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        अगर (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRCOMMAND);
            वापस TRUE;
        }

        // Return the ID of the button that was pushed
        अगर (wParam == IDOK) {
            अगर (Get_Button_सूचकांक(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } अन्यथा अगर (wParam == IDCANCEL) {
            अगर (Get_Button_सूचकांक(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } अन्यथा {
                // Closing of window was requested by user or system. It would be rude not to comply.
                EndDialog(hDlg, IDCLOSED);
            }
        } अन्यथा अगर (wParam >= IDBUTTONINDEX0 && (पूर्णांक)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            EndDialog(hDlg, wParam);
        }
        वापस TRUE;

    शेष:
        अवरोध;
    }
    वापस FALSE;
}

अटल bool ExpandDialogSpace(WIN_Dialog_तथ्य *dialog, माप_प्रकार space)
{
    // Growing memory in 64 KiB steps.
    स्थिर माप_प्रकार sizestep = 0x10000;
    माप_प्रकार आकार = dialog->आकार;

    अगर (आकार == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        आकार = 0x1000;
        अगर (SIZE_MAX - sizestep < space) {
            आकार = space;
        } अन्यथा अगर (space > आकार) {
            आकार = (space + sizestep) & ~(sizestep - 1);
        }
    } अन्यथा अगर (SIZE_MAX - dialog->used < space) {
        SDL_OutOfMemory();
        वापस false;
    } अन्यथा अगर (SIZE_MAX - (dialog->used + space) < sizestep) {
        // Close to the maximum.
        आकार = dialog->used + space;
    } अन्यथा अगर (आकार < dialog->used + space) {
        // Round up to the next 64 KiB block.
        आकार = dialog->used + space;
        आकार += sizestep - आकार % sizestep;
    }

    अगर (आकार > dialog->आकार) {
        व्योम *तथ्य = SDL_realloc(dialog->तथ्य, आकार);
        अगर (!तथ्य) {
            वापस false;
        }
        dialog->तथ्य = तथ्य;
        dialog->आकार = आकार;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->तथ्य;
    }
    वापस true;
}

अटल bool Align_Dialog_तथ्य(WIN_Dialog_तथ्य *dialog, माप_प्रकार आकार)
{
    माप_प्रकार padding = (dialog->used % आकार);

    अगर (!ExpandDialogSpace(dialog, padding)) {
        वापस false;
    }

    dialog->used += padding;

    वापस true;
}

अटल bool Add_Dialog_तथ्य(WIN_Dialog_तथ्य *dialog, स्थिर व्योम *तथ्य, माप_प्रकार आकार)
{
    अगर (!ExpandDialogSpace(dialog, आकार)) {
        वापस false;
    }

    SDL_memcpy((Uint8 *)dialog->तथ्य + dialog->used, तथ्य, आकार);
    dialog->used += आकार;

    वापस true;
}

अटल bool AddDialogString(WIN_Dialog_तथ्य *dialog, स्थिर अक्षर *string)
{
    WCHAR *wstring;
    WCHAR *p;
    माप_प्रकार गिनती;
    bool status;

    अगर (!string) {
        string = "";
    }

    wstring = WIN_UTF8ToStringW(string);
    अगर (!wstring) {
        वापस false;
    }

    // Find out how many characters we have, including null terminator
    गिनती = 0;
    क्रम (p = wstring; *p; ++p) {
        ++गिनती;
    }
    ++गिनती;

    status = Add_Dialog_तथ्य(dialog, wstring, गिनती * माप(WCHAR));
    SDL_free(wstring);
    वापस status;
}

अटल पूर्णांक s_BaseUnitsX;
अटल पूर्णांक s_BaseUnitsY;
अटल व्योम Vec2ToDLU(लघु *x, लघु *y)
{
    SDL_assert(s_BaseUnitsX != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (लघु)MulDiv(*x, 4, s_BaseUnitsX);
    *y = (लघु)MulDiv(*y, 8, s_BaseUnitsY);
}

अटल bool AddDialogControl(WIN_Dialog_तथ्य *dialog, WORD type, DWORD style, DWORD exStyle, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, पूर्णांक id, स्थिर अक्षर *caption, WORD ordinal)
{
    DLGITEMTEMPLATEEX item;
    WORD marker = 0xFFFF;
    WORD extra_तथ्य = 0;

    SDL_zero(item);
    item.style = style;
    item.exStyle = exStyle;
    item.x = (लघु)x;
    item.y = (लघु)y;
    item.cx = (लघु)w;
    item.cy = (लघु)h;
    item.id = id;

    Vec2ToDLU(&item.x, &item.y);
    Vec2ToDLU(&item.cx, &item.cy);

    अगर (!Align_Dialog_तथ्य(dialog, माप(DWORD))) {
        वापस false;
    }
    अगर (!Add_Dialog_तथ्य(dialog, &item, माप(item))) {
        वापस false;
    }
    अगर (!Add_Dialog_तथ्य(dialog, &marker, माप(marker))) {
        वापस false;
    }
    अगर (!Add_Dialog_तथ्य(dialog, &type, माप(type))) {
        वापस false;
    }
    अगर (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        अगर (!AddDialogString(dialog, caption)) {
            वापस false;
        }
    } अन्यथा {
        अगर (!Add_Dialog_तथ्य(dialog, &marker, माप(marker))) {
            वापस false;
        }
        अगर (!Add_Dialog_तथ्य(dialog, &ordinal, माप(ordinal))) {
            वापस false;
        }
    }
    अगर (!Add_Dialog_तथ्य(dialog, &extra_तथ्य, माप(extra_तथ्य))) {
        वापस false;
    }
    अगर (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_वस्तुएँ;

    वापस true;
}

अटल bool AddDialogStaticText(WIN_Dialog_तथ्य *dialog, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, स्थिर अक्षर *text)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_बायाँ | SS_NOPREFIX | SS_EDITCONTROL | WS_GROUP;
    वापस AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, text, 0);
}

अटल bool AddDialogStaticIcon(WIN_Dialog_तथ्य *dialog, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_ICON | WS_GROUP;
    वापस AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, शून्य, ordinal);
}

अटल bool AddDialogButton(WIN_Dialog_तथ्य *dialog, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, स्थिर अक्षर *text, पूर्णांक id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP;
    अगर (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } अन्यथा {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    अगर (dialog->numbuttons == 0) {
        style |= WS_GROUP;
    }
    वापस AddDialogControl(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, text, 0);
}

अटल व्योम Free_Dialog_तथ्य(WIN_Dialog_तथ्य *dialog)
{
    SDL_free(dialog->तथ्य);
    SDL_free(dialog);
}

अटल WIN_Dialog_तथ्य *Create_Dialog_तथ्य(पूर्णांक w, पूर्णांक h, स्थिर अक्षर *caption)
{
    WIN_Dialog_तथ्य *dialog;
    DLGTEMPLATEEX dialogTemplate;
    WORD WordToPass;

    SDL_zero(dialogTemplate);
    dialogTemplate.dlgVer = 1;
    dialogTemplate.signature = 0xffff;
    dialogTemplate.style = (WS_CAPTION | DS_CENTER | DS_SHELLFONT);
    dialogTemplate.x = 0;
    dialogTemplate.y = 0;
    dialogTemplate.cx = (लघु)w;
    dialogTemplate.cy = (लघु)h;
    Vec2ToDLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_Dialog_तथ्य *)SDL_calloc(1, माप(*dialog));
    अगर (!dialog) {
        वापस शून्य;
    }

    अगर (!Add_Dialog_तथ्य(dialog, &dialogTemplate, माप(dialogTemplate))) {
        Free_Dialog_तथ्य(dialog);
        वापस शून्य;
    }

    // No menu
    WordToPass = 0;
    अगर (!Add_Dialog_तथ्य(dialog, &WordToPass, 2)) {
        Free_Dialog_तथ्य(dialog);
        वापस शून्य;
    }

    // No custom class
    अगर (!Add_Dialog_तथ्य(dialog, &WordToPass, 2)) {
        Free_Dialog_तथ्य(dialog);
        वापस शून्य;
    }

    // title
    अगर (!AddDialogString(dialog, caption)) {
        Free_Dialog_तथ्य(dialog);
        वापस शून्य;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ToPass;

        NONCLIENTMETRICSA NCM;
        NCM.cb_आकार = माप(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(शून्य);
            पूर्णांक LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            अगर (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            WordToPass = (WORD)(-72 * NCM.lfMessageFont.lfHeight / LogicalPixelsY);
            ReleaseDC(शून्य, ScreenDC);
        }

        अगर (!Add_Dialog_तथ्य(dialog, &WordToPass, 2)) {
            Free_Dialog_तथ्य(dialog);
            वापस शून्य;
        }

        // Font weight
        WordToPass = (WORD)NCM.lfMessageFont.lfWeight;
        अगर (!Add_Dialog_तथ्य(dialog, &WordToPass, 2)) {
            Free_Dialog_तथ्य(dialog);
            वापस शून्य;
        }

        // italic?
        ToPass = NCM.lfMessageFont.lfItalic;
        अगर (!Add_Dialog_तथ्य(dialog, &ToPass, 1)) {
            Free_Dialog_तथ्य(dialog);
            वापस शून्य;
        }

        // charset?
        ToPass = NCM.lfMessageFont.lfCharSet;
        अगर (!Add_Dialog_तथ्य(dialog, &ToPass, 1)) {
            Free_Dialog_तथ्य(dialog);
            वापस शून्य;
        }

        // font typeface.
        अगर (!AddDialogString(dialog, NCM.lfMessageFont.lfFaceName)) {
            Free_Dialog_तथ्य(dialog);
            वापस शून्य;
        }
    }

    वापस dialog;
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
अटल स्थिर अक्षर *EscapeAmpersands(अक्षर **dst, माप_प्रकार *dstlen, स्थिर अक्षर *src)
{
    अक्षर *newdst;
    माप_प्रकार ampcount = 0;
    माप_प्रकार srclen = 0;

    अगर (!src) {
        वापस शून्य;
    }

    जबतक (src[srclen]) {
        अगर (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    अगर (ampcount == 0) {
        // Nothing to do.
        वापस src;
    }
    अगर (SIZE_MAX - srclen < ampcount) {
        वापस शून्य;
    }
    अगर (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        माप_प्रकार extraspace = SIZE_MAX - (srclen + ampcount);
        अगर (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = शून्य;
        newdst = (अक्षर *)SDL_malloc(*dstlen);
        अगर (!newdst) {
            वापस शून्य;
        }
        *dst = newdst;
    } अन्यथा {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    जबतक (srclen--) {
        अगर (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    वापस *dst;
}

अटल भग्न WIN_GetContentScale(व्योम)
{
    पूर्णांक dpi = 0;

#अगर 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    अगर (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (पूर्णांक)hdpi_uint;
    }
#पूर्ण_अगर
    अगर (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(शून्य);
        अगर (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(शून्य, hdc);
        }
    }
    अगर (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    वापस dpi / (भग्न)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
अटल bool WIN_ShowOldMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
    WIN_Dialog_तथ्य *dialog;
    पूर्णांक i, x, y;
    HFONT DialogFont;
    आकार_3 आकार_2;
    RECT Text_आकार;
    ब_अक्षर_प्रकार *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    अक्षर *ampescape = शून्य;
    माप_प्रकार ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool परिणाम;

    HWND ParentWindow = शून्य;

    स्थिर भग्न scale = WIN_GetContentScale();
    स्थिर पूर्णांक ButtonWidth = (पूर्णांक)SDL_roundf(88 * scale);
    स्थिर पूर्णांक ButtonHeight = (पूर्णांक)SDL_roundf(26 * scale);
    स्थिर पूर्णांक TextMargin = (पूर्णांक)SDL_roundf(16 * scale);
    स्थिर पूर्णांक ButtonMargin = (पूर्णांक)SDL_roundf(12 * scale);
    स्थिर पूर्णांक IconWidth = GetSystemMetrics(SM_CXICON);
    स्थिर पूर्णांक IconHeight = GetSystemMetrics(SM_CYICON);
    स्थिर पूर्णांक IconMargin = (पूर्णांक)SDL_roundf(20 * scale);

    अगर (messageboxdata->numbuttons > MAX_BUTTONS) {
        वापस SDL_SetError("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    चयन (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    हाल SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(माप_प्रकार)IDI_ERROR;
        अवरोध;
    हाल SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(माप_प्रकार)IDI_WARNING;
        अवरोध;
    हाल SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(माप_प्रकार)IDI_INFORMATION;
        अवरोध;
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
        NCM.cb_आकार = माप(NCM);
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
            आकार_3 extent;
            GetTextExtentPoint32A(FontDC, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, &extent);
            s_BaseUnitsX = (extent.cx / 26 + 1) / 2;
        }
        // s_BaseUnitsX = TM.tmAveCharWidth + 1;
        s_BaseUnitsY = TM.tmHeight;
    }

    /* Measure the *pixel* size of the string. */
    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    SDL_zero(Text_आकार);
    DrawTextW(FontDC, wmessage, -1, &Text_आकार, DT_CALCRECT | DT_बायाँ | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    Text_आकार.बायाँ += TextMargin;
    Text_आकार.दायाँ += TextMargin + 2;
    Text_आकार.शीर्ष += TextMargin;
    Text_आकार.bottom += TextMargin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    आकार_2.cx = Text_आकार.दायाँ - Text_आकार.बायाँ;
    आकार_2.cy = Text_आकार.bottom - Text_आकार.शीर्ष;
    आकार_2.cx += TextMargin * 2;
    आकार_2.cy += TextMargin * 2;

    // Make dialog wider and shift text over for the icon.
    अगर (icon) {
        आकार_2.cx += IconMargin + IconWidth;
        Text_आकार.बायाँ += IconMargin + IconWidth;
        Text_आकार.दायाँ += IconMargin + IconWidth;
    }

    // Ensure the size is wide enough for all of the buttons.
    अगर (आकार_2.cx < (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin) {
        आकार_2.cx = (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    अगर (icon && आकार_2.cy < (LONG)IconMargin * 2 + IconHeight) {
        आकार_2.cy = (LONG)IconMargin * 2 + IconHeight;
    }

    // Add vertical space for the buttons and border.
    आकार_2.cy += ButtonHeight + TextMargin;

    dialog = Create_Dialog_तथ्य(आकार_2.cx, आकार_2.cy, messageboxdata->title);
    अगर (!dialog) {
        वापस false;
    }

    अगर (icon && !AddDialogStaticIcon(dialog, IconMargin, IconMargin, IconWidth, IconHeight, icon)) {
        Free_Dialog_तथ्य(dialog);
        वापस false;
    }

    अगर (!AddDialogStaticText(dialog, Text_आकार.बायाँ, Text_आकार.शीर्ष, Text_आकार.दायाँ - Text_आकार.बायाँ, Text_आकार.bottom - Text_आकार.शीर्ष, messageboxdata->message)) {
        Free_Dialog_तथ्य(dialog);
        वापस false;
    }

    // Align the buttons to the right/bottom.
    x = आकार_2.cx - (ButtonWidth + ButtonMargin) * messageboxdata->numbuttons;
    y = आकार_2.cy - ButtonHeight - ButtonMargin;
    क्रम (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        स्थिर अक्षर *buttontext;
        स्थिर SDL_Message_Box_Button_तथ्य *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        अगर (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_बायाँ_TO_दायाँ) {
            sdlButton = &messageboxdata->buttons[i];
        } अन्यथा {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        अगर (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            अगर (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->text);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        अगर (!buttontext || !AddDialogButton(dialog, x, y, ButtonWidth, ButtonHeight, buttontext, IDBUTTONINDEX0 + (पूर्णांक)(sdlButton - messageboxdata->buttons), isdefault)) {
            Free_Dialog_तथ्य(dialog);
            SDL_free(ampescape);
            वापस false;
        }

        x += ButtonWidth + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    अगर (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    rc = DialogBoxIndirectParam(शून्य, (DLGTEMPLATE *)dialog->lpDialog, ParentWindow, MessageBoxDialogProc, (LPARAM)messageboxdata);
    अगर (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        परिणाम = true;
    } अन्यथा अगर (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        परिणाम = true;
        *buttonID = -1;
    } अन्यथा {
        अगर (rc == 0) {
            SDL_SetError("Invalid parent window handle");
        } अन्यथा अगर (rc == -1) {
            SDL_SetError("The message box encountered an error.");
        } अन्यथा अगर (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_SetError("Invalid message box pointer in dialog procedure");
        } अन्यथा अगर (rc == IDINVALPTRDLGITEM) {
            SDL_SetError("Couldn't find dialog control of the default enter-key button");
        } अन्यथा {
            SDL_SetError("An unknown error occurred");
        }
        परिणाम = false;
    }

    Free_Dialog_तथ्य(dialog);
    वापस परिणाम;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
प्रकार HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(स्थिर TASKDIALOGCONFIG *pTaskConfig, पूर्णांक *pnButton, पूर्णांक *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
    HWND ParentWindow = शून्य;
    ब_अक्षर_प्रकार *wmessage;
    ब_अक्षर_प्रकार *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC pTaskDialogIndirect;
    HRESULT hr;
    अक्षर *ampescape = शून्य;
    माप_प्रकार ampescapesize = 0;
    पूर्णांक nButton;
    पूर्णांक nCancelButton;
    पूर्णांक i;
    bool परिणाम = false;

    अगर (SIZE_MAX / माप(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        वापस SDL_OutOfMemory();
    }

    HMODULE hUser32 = GetModuleHandle(TEXT("user32.dll"));
    प्रकार DPI_AWARENESS_CONTEXT (WINAPI *pfnSetThreadDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    pfnSetThreadDpiAwarenessContext pSetThreadDpiAwarenessContext = (pfnSetThreadDpiAwarenessContext)GetProcAddress(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT previous_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    अगर (pSetThreadDpiAwarenessContext) {
        previous_context = pSetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = LoadLibrary(TEXT("comctl32.dll"));
    अगर (!hComctl32) {
        परिणाम = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        जाओ done;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    pTaskDialogIndirect = (TASKDIALOGINDIRECTPROC)GetProcAddress(hComctl32, "TaskDialogIndirect");
    अगर (!pTaskDialogIndirect) {
        FreeLibrary(hComctl32);
        परिणाम = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        जाओ done;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    अगर (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    wtitle = WIN_UTF8ToStringW(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cb_आकार = माप(TASKDIALOGCONFIG);
    TaskConfig.hwndParent = ParentWindow;
    TaskConfig.dwFlags = TDF_आकार_TO_CONTENT;
    TaskConfig.pszWindowTitle = wtitle;
    अगर (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } अन्यथा अगर (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } अन्यथा अगर (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } अन्यथा {
        TaskConfig.pszMainIcon = शून्य;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(माप(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    क्रम (i = 0; i < messageboxdata->numbuttons; i++) {
        स्थिर अक्षर *buttontext;
        अगर (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_बायाँ_TO_दायाँ) {
            pButton = &pButtons[i];
        } अन्यथा {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        अगर (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } अन्यथा {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].text);
        अगर (!buttontext) {
            पूर्णांक j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            क्रम (j = 0; j < i; j++) {
                SDL_free((ब_अक्षर_प्रकार *)pButtons[j].pszButtonText);
            }
            SDL_free(pButtons);
            वापस false;
        }
        pButton->pszButtonText = WIN_UTF8ToStringW(buttontext);
        अगर (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = pTaskDialogIndirect(&TaskConfig, &nButton, शून्य, शून्य);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    क्रम (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((ब_अक्षर_प्रकार *)pButtons[i].pszButtonText);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    अगर (SUCCEEDED(hr)) {
        अगर (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } अन्यथा अगर (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } अन्यथा {
            *buttonID = -1;
        }
        परिणाम = true;
    } अन्यथा {
        // We failed showing the Task Dialog, use the old message box!
        परिणाम = WIN_ShowOldMessageBox(messageboxdata, buttonID);
    }

done:
    अगर (pSetThreadDpiAwarenessContext) {
        pSetThreadDpiAwarenessContext(previous_context);
    }
    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS

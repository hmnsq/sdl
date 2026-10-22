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
#अन्तर्भाव "SDL_internal.h"

#जर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ifdef HAVE_LIMITS_H
#अन्तर्भाव <limits.h>
#endif
#ifndef SIZE_MAX
#define SIZE_MAX ((माप_प्रकार)-1)
#endif

#अन्तर्भाव "../../core/windows/SDL_windows.h"

#अन्तर्भाव "SDL_windowsvideo.h"

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

प्रकारव्याख्या HRESULT(CALLBACK *PFTASKDIALOGCALLBACK)(HWND hwnd, UINT संदेश, WPARAM wParam, LPARAM lParam, LONG_PTR lpRefData);

गणना _TASKDIALOG_FLAGS
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
प्रकारव्याख्या पूर्णांक TASKDIALOG_FLAGS; // Note: _TASKDIALOG_FLAGS is an int

प्रकारव्याख्या गणना _TASKDIALOG_MESSAGES
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

प्रकारव्याख्या गणना _TASKDIALOG_NOTIFICATIONS
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

प्रकारव्याख्या गणना _TASKDIALOG_ELEMENTS
{
    TDE_CONTENT,
    TDE_EXPANDED_INFORMATION,
    TDE_FOOTER,
    TDE_MAIN_INSTRUCTION
} TASKDIALOG_ELEMENTS;

प्रकारव्याख्या गणना _TASKDIALOG_ICON_ELEMENTS
{
    TDIE_ICON_MAIN,
    TDIE_ICON_FOOTER
} TASKDIALOG_ICON_ELEMENTS;

#define TD_WARNING_ICON     MAKEINTRESOURCEW(-1)
#define TD_ERROR_ICON       MAKEINTRESOURCEW(-2)
#define TD_INFORMATION_ICON MAKEINTRESOURCEW(-3)
#define TD_SHIELD_ICON      MAKEINTRESOURCEW(-4)

गणना _TASKDIALOG_COMMON_BUTTON_FLAGS
{
    TDCBF_OK_BUTTON = 0x0001,     // selected control return value IDOK
    TDCBF_YES_BUTTON = 0x0002,    // selected control return value IDYES
    TDCBF_NO_BUTTON = 0x0004,     // selected control return value IDNO
    TDCBF_CANCEL_BUTTON = 0x0008, // selected control return value IDCANCEL
    TDCBF_RETRY_BUTTON = 0x0010,  // selected control return value IDRETRY
    TDCBF_CLOSE_BUTTON = 0x0020   // selected control return value IDCLOSE
};
प्रकारव्याख्या पूर्णांक TASKDIALOG_COMMON_BUTTON_FLAGS; // Note: _TASKDIALOG_COMMON_BUTTON_FLAGS is an int

#pragma pack(ढकला, 1)

प्रकारव्याख्या संरचना _TASKDIALOG_BUTTON
{
    पूर्णांक nButtonID;
    PCWSTR pszButtonText;
} TASKDIALOG_BUTTON;

प्रकारव्याख्या संरचना _TASKDIALOGCONFIG
{
    UINT cbSize;
    HWND hwndParent;                                // incorrectly named, this is the owner window, not a parent.
    HINSTANCE hInstance;                            // used for MAKEINTRESOURCE() strings
    TASKDIALOG_FLAGS dwFlags;                       // TASKDIALOG_FLAGS (TDF_XXX) flags
    TASKDIALOG_COMMON_BUTTON_FLAGS dwCommonButtons; // TASKDIALOG_COMMON_BUTTON (TDCBF_XXX) flags
    PCWSTR pszWindowTitle;                          // string or MAKEINTRESOURCE()
    संघ
    {
        HICON hMainIcon;
        PCWSTR pszMainIcon;
    } /*DUMMYUNIONNAME*/;
    PCWSTR pszMainInstruction;
    PCWSTR pszContent;
    UINT cButtons;
    स्थिरांक TASKDIALOG_BUTTON *pButtons;
    पूर्णांक nDefaultButton;
    UINT cRadioButtons;
    स्थिरांक TASKDIALOG_BUTTON *pRadioButtons;
    पूर्णांक nDefaultRadioButton;
    PCWSTR pszVerificationText;
    PCWSTR pszExpandedInformation;
    PCWSTR pszExpandedControlText;
    PCWSTR pszCollapsedControlText;
    संघ
    {
        HICON hFooterIcon;
        PCWSTR pszFooterIcon;
    } /*DUMMYUNIONNAME2*/;
    PCWSTR pszFooter;
    PFTASKDIALOGCALLBACK pfCallback;
    LONG_PTR lpCallbackData;
    UINT cxWidth; // width of the Task Dialog's client area in DLU's. If 0, Task Dialog will calculate the ideal width.
} TASKDIALOGCONFIG;

प्रकारव्याख्या संरचना
{
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD c_Dlg_वस्तुसंच;
    लघु x;
    लघु y;
    लघु cx;
    लघु cy;
} DLGTEMPLATEEX;

प्रकारव्याख्या संरचना
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

#pragma pack(काढा)

प्रकारव्याख्या संरचना
{
    DLGTEMPLATEEX *lpDialog;
    शून्य *data;
    माप_प्रकार size;
    माप_प्रकार used;
    WORD numbuttons;
} WIN_DialogData;

स्थिर bool GetButtonIndex(स्थिरांक SDL_MessageBoxData *messageboxdata, SDL_MessageBoxButtonFlags flags, माप_प्रकार *i)
{
    साठी (*i = 0; *i < (माप_प्रकार)messageboxdata->numbuttons; ++*i) {
        जर (messageboxdata->buttons[*i].flags & flags) {
            परत true;
        }
    }
    परत false;
}

स्थिर INT_PTR CALLBACK MessageBoxDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    स्थिरांक SDL_MessageBoxData *messageboxdata;
    माप_प्रकार buttonindex;

    निवड (iMessage) {
    स्थिती WM_INITDIALOG:
        जर (lParam == 0) {
            EndDialog(hDlg, IDINVALPTRINIT);
            परत TRUE;
        }
        messageboxdata = (स्थिरांक SDL_MessageBoxData *)lParam;
        SetWindowLongPtr(hDlg, GWLP_USERDATA, lParam);

        जर (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            // Focus on the first default return-key button
            HWND buttonctl = GetDlgItem(hDlg, (पूर्णांक)(IDBUTTONINDEX0 + buttonindex));
            जर (!buttonctl) {
                EndDialog(hDlg, IDINVALPTRDLGITEM);
            }
            PostMessage(hDlg, WM_NEXTDLGCTL, (WPARAM)buttonctl, TRUE);
        } अन्यथा {
            // Give the focus to the dialog window instead
            SetFocus(hDlg);
        }
        परत FALSE;
    स्थिती WM_SETFOCUS:
        messageboxdata = (स्थिरांक SDL_MessageBoxData *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        जर (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRSETFOCUS);
            परत TRUE;
        }

        // Let the default button be focused if there is one. Otherwise, prevent any initial focus.
        जर (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
            परत FALSE;
        }
        परत TRUE;
    स्थिती WM_COMMAND:
        messageboxdata = (स्थिरांक SDL_MessageBoxData *)GetWindowLongPtr(hDlg, GWLP_USERDATA);
        जर (!messageboxdata) {
            EndDialog(hDlg, IDINVALPTRCOMMAND);
            परत TRUE;
        }

        // Return the ID of the button that was pushed
        जर (wParam == IDOK) {
            जर (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            }
        } अन्यथा जर (wParam == IDCANCEL) {
            जर (GetButtonIndex(messageboxdata, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, &buttonindex)) {
                EndDialog(hDlg, IDBUTTONINDEX0 + buttonindex);
            } अन्यथा {
                // Closing of window was requested by user or system. It would be rude not to comply.
                EndDialog(hDlg, IDCLOSED);
            }
        } अन्यथा जर (wParam >= IDBUTTONINDEX0 && (पूर्णांक)wParam - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
            EndDialog(hDlg, wParam);
        }
        परत TRUE;

    पूर्वनिर्धारित:
        थांबा;
    }
    परत FALSE;
}

स्थिर bool ExpandDialogSpace(WIN_DialogData *dialog, माप_प्रकार space)
{
    // Growing memory in 64 KiB steps.
    स्थिरांक माप_प्रकार sizestep = 0x10000;
    माप_प्रकार size = dialog->size;

    जर (size == 0) {
        // Start with 4 KiB or a multiple of 64 KiB to fit the data.
        size = 0x1000;
        जर (SIZE_MAX - sizestep < space) {
            size = space;
        } अन्यथा जर (space > size) {
            size = (space + sizestep) & ~(sizestep - 1);
        }
    } अन्यथा जर (SIZE_MAX - dialog->used < space) {
        SDL_OutOfMemory();
        परत false;
    } अन्यथा जर (SIZE_MAX - (dialog->used + space) < sizestep) {
        // Close to the maximum.
        size = dialog->used + space;
    } अन्यथा जर (size < dialog->used + space) {
        // Round up to the next 64 KiB block.
        size = dialog->used + space;
        size += sizestep - size % sizestep;
    }

    जर (size > dialog->size) {
        शून्य *data = SDL_realloc(dialog->data, size);
        जर (!data) {
            परत false;
        }
        dialog->data = data;
        dialog->size = size;
        dialog->lpDialog = (DLGTEMPLATEEX *)dialog->data;
    }
    परत true;
}

स्थिर bool AlignDialogData(WIN_DialogData *dialog, माप_प्रकार size)
{
    माप_प्रकार padding = (dialog->used % size);

    जर (!ExpandDialogSpace(dialog, padding)) {
        परत false;
    }

    dialog->used += padding;

    परत true;
}

स्थिर bool AddDialogData(WIN_DialogData *dialog, स्थिरांक शून्य *data, माप_प्रकार size)
{
    जर (!ExpandDialogSpace(dialog, size)) {
        परत false;
    }

    SDL_memcpy((Uint8 *)dialog->data + dialog->used, data, size);
    dialog->used += size;

    परत true;
}

स्थिर bool AddDialogString(WIN_DialogData *dialog, स्थिरांक अक्षर *string)
{
    WCHAR *wstring;
    WCHAR *p;
    माप_प्रकार मोजणी;
    bool status;

    जर (!string) {
        string = "";
    }

    wstring = WIN_UTF8ToStringW(string);
    जर (!wstring) {
        परत false;
    }

    // Find out how many characters we have, including null terminator
    मोजणी = 0;
    साठी (p = wstring; *p; ++p) {
        ++मोजणी;
    }
    ++मोजणी;

    status = AddDialogData(dialog, wstring, मोजणी * आकार(WCHAR));
    SDL_free(wstring);
    परत status;
}

स्थिर पूर्णांक s_BaseUnitsX;
स्थिर पूर्णांक s_BaseUnitsY;
स्थिर शून्य Vec2ToDLU(लघु *x, लघु *y)
{
    SDL_assert(s_BaseUnitsX != 0); // we init in WIN_ShowMessageBox(), which is the only public function...

    *x = (लघु)MulDiv(*x, 4, s_BaseUnitsX);
    *y = (लघु)MulDiv(*y, 8, s_BaseUnitsY);
}

स्थिर bool AddDialogControl(WIN_DialogData *dialog, WORD type, DWORD style, DWORD exStyle, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, पूर्णांक id, स्थिरांक अक्षर *caption, WORD ordinal)
{
    DLGITEMTEMPLATEEX item;
    WORD marker = 0xFFFF;
    WORD extraData = 0;

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

    जर (!AlignDialogData(dialog, आकार(DWORD))) {
        परत false;
    }
    जर (!AddDialogData(dialog, &item, आकार(item))) {
        परत false;
    }
    जर (!AddDialogData(dialog, &marker, आकार(marker))) {
        परत false;
    }
    जर (!AddDialogData(dialog, &type, आकार(type))) {
        परत false;
    }
    जर (type == DLGITEMTYPEBUTTON || (type == DLGITEMTYPESTATIC && caption)) {
        जर (!AddDialogString(dialog, caption)) {
            परत false;
        }
    } अन्यथा {
        जर (!AddDialogData(dialog, &marker, आकार(marker))) {
            परत false;
        }
        जर (!AddDialogData(dialog, &ordinal, आकार(ordinal))) {
            परत false;
        }
    }
    जर (!AddDialogData(dialog, &extraData, आकार(extraData))) {
        परत false;
    }
    जर (type == DLGITEMTYPEBUTTON) {
        dialog->numbuttons++;
    }
    ++dialog->lpDialog->c_Dlg_वस्तुसंच;

    परत true;
}

स्थिर bool AddDialogStaticText(WIN_DialogData *dialog, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, स्थिरांक अक्षर *text)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_डावा | SS_NOPREFIX | SS_EDITCONTROL | WS_GROUP;
    परत AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -1, text, 0);
}

स्थिर bool AddDialogStaticIcon(WIN_DialogData *dialog, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, Uint16 ordinal)
{
    DWORD style = WS_VISIBLE | WS_CHILD | SS_ICON | WS_GROUP;
    परत AddDialogControl(dialog, DLGITEMTYPESTATIC, style, 0, x, y, w, h, -2, रिक्त, ordinal);
}

स्थिर bool AddDialogButton(WIN_DialogData *dialog, पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h, स्थिरांक अक्षर *text, पूर्णांक id, bool isDefault)
{
    DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP;
    जर (isDefault) {
        style |= BS_DEFPUSHBUTTON;
    } अन्यथा {
        style |= BS_PUSHBUTTON;
    }
    // The first button marks the start of the group.
    जर (dialog->numbuttons == 0) {
        style |= WS_GROUP;
    }
    परत AddDialogControl(dialog, DLGITEMTYPEBUTTON, style, 0, x, y, w, h, id, text, 0);
}

स्थिर शून्य FreeDialogData(WIN_DialogData *dialog)
{
    SDL_free(dialog->data);
    SDL_free(dialog);
}

स्थिर WIN_DialogData *CreateDialogData(पूर्णांक w, पूर्णांक h, स्थिरांक अक्षर *caption)
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
    dialogTemplate.cx = (लघु)w;
    dialogTemplate.cy = (लघु)h;
    Vec2ToDLU(&dialogTemplate.cx, &dialogTemplate.cy);

    dialog = (WIN_DialogData *)SDL_calloc(1, आकार(*dialog));
    जर (!dialog) {
        परत रिक्त;
    }

    जर (!AddDialogData(dialog, &dialogTemplate, आकार(dialogTemplate))) {
        FreeDialogData(dialog);
        परत रिक्त;
    }

    // No menu
    WordToPass = 0;
    जर (!AddDialogData(dialog, &WordToPass, 2)) {
        FreeDialogData(dialog);
        परत रिक्त;
    }

    // No custom class
    जर (!AddDialogData(dialog, &WordToPass, 2)) {
        FreeDialogData(dialog);
        परत रिक्त;
    }

    // title
    जर (!AddDialogString(dialog, caption)) {
        FreeDialogData(dialog);
        परत रिक्त;
    }

    // Font stuff
    {
        /*
         * We want to use the system messagebox font.
         */
        BYTE ToPass;

        NONCLIENTMETRICSA NCM;
        NCM.cbSize = आकार(NCM);
        SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, 0, &NCM, 0);

        // Font size - convert to logical font size for dialog parameter.
        {
            HDC ScreenDC = GetDC(रिक्त);
            पूर्णांक LogicalPixelsY = GetDeviceCaps(ScreenDC, LOGPIXELSY);
            जर (!LogicalPixelsY) {
                LogicalPixelsY = 72; // This can happen if the application runs out of GDI handles
            }

            WordToPass = (WORD)(-72 * NCM.lfMessageFont.lfHeight / LogicalPixelsY);
            ReleaseDC(रिक्त, ScreenDC);
        }

        जर (!AddDialogData(dialog, &WordToPass, 2)) {
            FreeDialogData(dialog);
            परत रिक्त;
        }

        // Font weight
        WordToPass = (WORD)NCM.lfMessageFont.lfWeight;
        जर (!AddDialogData(dialog, &WordToPass, 2)) {
            FreeDialogData(dialog);
            परत रिक्त;
        }

        // italic?
        ToPass = NCM.lfMessageFont.lfItalic;
        जर (!AddDialogData(dialog, &ToPass, 1)) {
            FreeDialogData(dialog);
            परत रिक्त;
        }

        // charset?
        ToPass = NCM.lfMessageFont.lfCharSet;
        जर (!AddDialogData(dialog, &ToPass, 1)) {
            FreeDialogData(dialog);
            परत रिक्त;
        }

        // font typeface.
        जर (!AddDialogString(dialog, NCM.lfMessageFont.lfFaceName)) {
            FreeDialogData(dialog);
            परत रिक्त;
        }
    }

    परत dialog;
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
स्थिर स्थिरांक अक्षर *EscapeAmpersands(अक्षर **dst, माप_प्रकार *dstlen, स्थिरांक अक्षर *src)
{
    अक्षर *newdst;
    माप_प्रकार ampcount = 0;
    माप_प्रकार srclen = 0;

    जर (!src) {
        परत रिक्त;
    }

    पर्यंत (src[srclen]) {
        जर (src[srclen] == '&') {
            ampcount++;
        }
        srclen++;
    }
    srclen++;

    जर (ampcount == 0) {
        // Nothing to do.
        परत src;
    }
    जर (SIZE_MAX - srclen < ampcount) {
        परत रिक्त;
    }
    जर (!*dst || *dstlen < srclen + ampcount) {
        // Allocating extra space in case the next strings are a bit longer.
        माप_प्रकार extraspace = SIZE_MAX - (srclen + ampcount);
        जर (extraspace > 512) {
            extraspace = 512;
        }
        *dstlen = srclen + ampcount + extraspace;
        SDL_free(*dst);
        *dst = रिक्त;
        newdst = (अक्षर *)SDL_malloc(*dstlen);
        जर (!newdst) {
            परत रिक्त;
        }
        *dst = newdst;
    } अन्यथा {
        newdst = *dst;
    }

    // The escape character is the ampersand itself.
    पर्यंत (srclen--) {
        जर (*src == '&') {
            *newdst++ = '&';
        }
        *newdst++ = *src++;
    }

    परत *dst;
}

स्थिर दशांश WIN_GetContentScale(शून्य)
{
    पूर्णांक dpi = 0;

#जर 0 // We don't know what monitor the dialog will be shown on
    UINT hdpi_uint, vdpi_uint;
    जर (GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &hdpi_uint, &vdpi_uint) == S_OK) {
        dpi = (पूर्णांक)hdpi_uint;
    }
#endif
    जर (dpi == 0) {
        // Window 8.0 and below: same DPI for all monitors
        HDC hdc = GetDC(रिक्त);
        जर (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(रिक्त, hdc);
        }
    }
    जर (dpi == 0) {
        // Safe default
        dpi = USER_DEFAULT_SCREEN_DPI;
    }
    परत dpi / (दशांश)USER_DEFAULT_SCREEN_DPI;
}

// This function is called if a Task Dialog is unsupported.
स्थिर bool WIN_ShowOldMessageBox(स्थिरांक SDL_MessageBoxData *messageboxdata, पूर्णांक *buttonID)
{
    WIN_DialogData *dialog;
    पूर्णांक i, x, y;
    HFONT DialogFont;
    SIZE Size;
    RECT TextSize;
    ब_अक्षर_प्रकार *wmessage;
    TEXTMETRIC TM;
    HDC FontDC;
    INT_PTR rc;
    अक्षर *ampescape = रिक्त;
    माप_प्रकार ampescapesize = 0;
    Uint16 defbuttoncount = 0;
    Uint16 icon = 0;
    bool result;

    HWND ParentWindow = रिक्त;

    स्थिरांक दशांश scale = WIN_GetContentScale();
    स्थिरांक पूर्णांक ButtonWidth = (पूर्णांक)SDL_roundf(88 * scale);
    स्थिरांक पूर्णांक ButtonHeight = (पूर्णांक)SDL_roundf(26 * scale);
    स्थिरांक पूर्णांक TextMargin = (पूर्णांक)SDL_roundf(16 * scale);
    स्थिरांक पूर्णांक ButtonMargin = (पूर्णांक)SDL_roundf(12 * scale);
    स्थिरांक पूर्णांक IconWidth = GetSystemMetrics(SM_CXICON);
    स्थिरांक पूर्णांक IconHeight = GetSystemMetrics(SM_CYICON);
    स्थिरांक पूर्णांक IconMargin = (पूर्णांक)SDL_roundf(20 * scale);

    जर (messageboxdata->numbuttons > MAX_BUTTONS) {
        परत SDL_SetError("Number of buttons exceeds limit of %d", MAX_BUTTONS);
    }

    निवड (messageboxdata->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    स्थिती SDL_MESSAGEBOX_ERROR:
        icon = (Uint16)(माप_प्रकार)IDI_ERROR;
        थांबा;
    स्थिती SDL_MESSAGEBOX_WARNING:
        icon = (Uint16)(माप_प्रकार)IDI_WARNING;
        थांबा;
    स्थिती SDL_MESSAGEBOX_INFORMATION:
        icon = (Uint16)(माप_प्रकार)IDI_INFORMATION;
        थांबा;
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
        NCM.cbSize = आकार(NCM);
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
    DrawTextW(FontDC, wmessage, -1, &TextSize, DT_CALCRECT | DT_डावा | DT_NOPREFIX | DT_EDITCONTROL);

    // Add margins and some padding for hangs, etc.
    TextSize.डावा += TextMargin;
    TextSize.उजवा += TextMargin + 2;
    TextSize.शीर्ष += TextMargin;
    TextSize.bottom += TextMargin + 2;

    // Done with the DC, and the string
    DeleteDC(FontDC);
    SDL_free(wmessage);

    // Increase the size of the dialog by some border spacing around the text.
    Size.cx = TextSize.उजवा - TextSize.डावा;
    Size.cy = TextSize.bottom - TextSize.शीर्ष;
    Size.cx += TextMargin * 2;
    Size.cy += TextMargin * 2;

    // Make dialog wider and shift text over for the icon.
    जर (icon) {
        Size.cx += IconMargin + IconWidth;
        TextSize.डावा += IconMargin + IconWidth;
        TextSize.उजवा += IconMargin + IconWidth;
    }

    // Ensure the size is wide enough for all of the buttons.
    जर (Size.cx < (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin) {
        Size.cx = (LONG)messageboxdata->numbuttons * (ButtonWidth + ButtonMargin) + ButtonMargin;
    }

    // Reset the height to the icon size if it is actually bigger than the text.
    जर (icon && Size.cy < (LONG)IconMargin * 2 + IconHeight) {
        Size.cy = (LONG)IconMargin * 2 + IconHeight;
    }

    // Add vertical space for the buttons and border.
    Size.cy += ButtonHeight + TextMargin;

    dialog = CreateDialogData(Size.cx, Size.cy, messageboxdata->title);
    जर (!dialog) {
        परत false;
    }

    जर (icon && !AddDialogStaticIcon(dialog, IconMargin, IconMargin, IconWidth, IconHeight, icon)) {
        FreeDialogData(dialog);
        परत false;
    }

    जर (!AddDialogStaticText(dialog, TextSize.डावा, TextSize.शीर्ष, TextSize.उजवा - TextSize.डावा, TextSize.bottom - TextSize.शीर्ष, messageboxdata->message)) {
        FreeDialogData(dialog);
        परत false;
    }

    // Align the buttons to the right/bottom.
    x = Size.cx - (ButtonWidth + ButtonMargin) * messageboxdata->numbuttons;
    y = Size.cy - ButtonHeight - ButtonMargin;
    साठी (i = 0; i < messageboxdata->numbuttons; i++) {
        bool isdefault = false;
        स्थिरांक अक्षर *buttontext;
        स्थिरांक SDL_MessageBoxButtonData *sdlButton;

        /* We always have to create the dialog buttons from left to right
         * so that the tab order is correct.  Select the info to use
         * depending on which order was requested. */
        जर (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_डावा_TO_उजवा) {
            sdlButton = &messageboxdata->buttons[i];
        } अन्यथा {
            sdlButton = &messageboxdata->buttons[messageboxdata->numbuttons - 1 - i];
        }

        जर (sdlButton->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            defbuttoncount++;
            जर (defbuttoncount == 1) {
                isdefault = true;
            }
        }

        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, sdlButton->text);
        /* Make sure to provide the correct ID to keep buttons indexed in the
         * same order as how they are in messageboxdata. */
        जर (!buttontext || !AddDialogButton(dialog, x, y, ButtonWidth, ButtonHeight, buttontext, IDBUTTONINDEX0 + (पूर्णांक)(sdlButton - messageboxdata->buttons), isdefault)) {
            FreeDialogData(dialog);
            SDL_free(ampescape);
            परत false;
        }

        x += ButtonWidth + ButtonMargin;
    }
    SDL_free(ampescape);

    /* If we have a parent window, get the Instance and HWND for them
     * so that our little dialog gets exclusive focus at all times. */
    जर (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    rc = DialogBoxIndirectParam(रिक्त, (DLGTEMPLATE *)dialog->lpDialog, ParentWindow, MessageBoxDialogProc, (LPARAM)messageboxdata);
    जर (rc >= IDBUTTONINDEX0 && rc - IDBUTTONINDEX0 < messageboxdata->numbuttons) {
        *buttonID = messageboxdata->buttons[rc - IDBUTTONINDEX0].buttonID;
        result = true;
    } अन्यथा जर (rc == IDCLOSED) {
        // Dialog window closed by user or system.
        // This could use a special return code.
        result = true;
        *buttonID = -1;
    } अन्यथा {
        जर (rc == 0) {
            SDL_SetError("Invalid parent window handle");
        } अन्यथा जर (rc == -1) {
            SDL_SetError("The message box encountered an error.");
        } अन्यथा जर (rc == IDINVALPTRINIT || rc == IDINVALPTRSETFOCUS || rc == IDINVALPTRCOMMAND) {
            SDL_SetError("Invalid message box pointer in dialog procedure");
        } अन्यथा जर (rc == IDINVALPTRDLGITEM) {
            SDL_SetError("Couldn't find dialog control of the default enter-key button");
        } अन्यथा {
            SDL_SetError("An unknown error occurred");
        }
        result = false;
    }

    FreeDialogData(dialog);
    परत result;
}

/* TaskDialogIndirect procedure
 * This is because SDL targets Windows XP (0x501), so this is not defined in the platform SDK.
 */
/* *INDENT-OFF* */ // clang-format off
प्रकारव्याख्या HRESULT (FAR WINAPI *TASKDIALOGINDIRECTPROC)(स्थिरांक TASKDIALOGCONFIG *pTaskConfig, पूर्णांक *pnButton, पूर्णांक *pnRadioButton, BOOL *pfVerificationFlagChecked);
/* *INDENT-ON* */ // clang-format on

bool WIN_ShowMessageBox(स्थिरांक SDL_MessageBoxData *messageboxdata, पूर्णांक *buttonID)
{
    HWND ParentWindow = रिक्त;
    ब_अक्षर_प्रकार *wmessage;
    ब_अक्षर_प्रकार *wtitle;
    TASKDIALOGCONFIG TaskConfig;
    TASKDIALOG_BUTTON *pButtons;
    TASKDIALOG_BUTTON *pButton;
    HMODULE hComctl32;
    TASKDIALOGINDIRECTPROC pTaskDialogIndirect;
    HRESULT hr;
    अक्षर *ampescape = रिक्त;
    माप_प्रकार ampescapesize = 0;
    पूर्णांक nButton;
    पूर्णांक nCancelButton;
    पूर्णांक i;
    bool result = false;

    जर (SIZE_MAX / आकार(TASKDIALOG_BUTTON) < messageboxdata->numbuttons) {
        परत SDL_OutOfMemory();
    }

    HMODULE hUser32 = GetModuleHandle(TEXT("user32.dll"));
    प्रकारव्याख्या DPI_AWARENESS_CONTEXT (WINAPI *pfnSetThreadDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    pfnSetThreadDpiAwarenessContext pSetThreadDpiAwarenessContext = (pfnSetThreadDpiAwarenessContext)GetProcAddress(hUser32, "SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT previous_context = DPI_AWARENESS_CONTEXT_UNAWARE;
    जर (pSetThreadDpiAwarenessContext) {
        previous_context = pSetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }

    // If we cannot load comctl32.dll use the old messagebox!
    hComctl32 = LoadLibrary(TEXT("comctl32.dll"));
    जर (!hComctl32) {
        result = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        जा done;
    }

    /* If TaskDialogIndirect doesn't exist use the old messagebox!
       This will fail prior to Windows Vista.
       The manifest file in the application may require targeting version 6 of comctl32.dll, even
       when we use LoadLibrary here!
       If you don't want to bother with manifests, put this #pragma in your app's source code somewhere:
       #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0'  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
     */
    pTaskDialogIndirect = (TASKDIALOGINDIRECTPROC)GetProcAddress(hComctl32, "TaskDialogIndirect");
    जर (!pTaskDialogIndirect) {
        FreeLibrary(hComctl32);
        result = WIN_ShowOldMessageBox(messageboxdata, buttonID);
        जा done;
    }

    /* If we have a parent window, get the Instance and HWND for them
       so that our little dialog gets exclusive focus at all times. */
    जर (messageboxdata->window) {
        ParentWindow = messageboxdata->window->internal->hwnd;
    }

    wmessage = WIN_UTF8ToStringW(messageboxdata->message);
    wtitle = WIN_UTF8ToStringW(messageboxdata->title);

    SDL_zero(TaskConfig);
    TaskConfig.cbSize = आकार(TASKDIALOGCONFIG);
    TaskConfig.hwndParent = ParentWindow;
    TaskConfig.dwFlags = TDF_SIZE_TO_CONTENT;
    TaskConfig.pszWindowTitle = wtitle;
    जर (messageboxdata->flags & SDL_MESSAGEBOX_ERROR) {
        TaskConfig.pszMainIcon = TD_ERROR_ICON;
    } अन्यथा जर (messageboxdata->flags & SDL_MESSAGEBOX_WARNING) {
        TaskConfig.pszMainIcon = TD_WARNING_ICON;
    } अन्यथा जर (messageboxdata->flags & SDL_MESSAGEBOX_INFORMATION) {
        TaskConfig.pszMainIcon = TD_INFORMATION_ICON;
    } अन्यथा {
        TaskConfig.pszMainIcon = रिक्त;
    }

    TaskConfig.pszContent = wmessage;
    TaskConfig.cButtons = messageboxdata->numbuttons;
    pButtons = (TASKDIALOG_BUTTON *)SDL_malloc(आकार(TASKDIALOG_BUTTON) * messageboxdata->numbuttons);
    TaskConfig.nDefaultButton = 0;
    nCancelButton = 0;
    साठी (i = 0; i < messageboxdata->numbuttons; i++) {
        स्थिरांक अक्षर *buttontext;
        जर (messageboxdata->flags & SDL_MESSAGEBOX_BUTTONS_डावा_TO_उजवा) {
            pButton = &pButtons[i];
        } अन्यथा {
            pButton = &pButtons[messageboxdata->numbuttons - 1 - i];
        }
        जर (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
            nCancelButton = messageboxdata->buttons[i].buttonID;
            pButton->nButtonID = IDCANCEL;
        } अन्यथा {
            pButton->nButtonID = IDBUTTONINDEX0 + i;
        }
        buttontext = EscapeAmpersands(&ampescape, &ampescapesize, messageboxdata->buttons[i].text);
        जर (!buttontext) {
            पूर्णांक j;
            FreeLibrary(hComctl32);
            SDL_free(ampescape);
            SDL_free(wmessage);
            SDL_free(wtitle);
            साठी (j = 0; j < i; j++) {
                SDL_free((ब_अक्षर_प्रकार *)pButtons[j].pszButtonText);
            }
            SDL_free(pButtons);
            परत false;
        }
        pButton->pszButtonText = WIN_UTF8ToStringW(buttontext);
        जर (messageboxdata->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
            TaskConfig.nDefaultButton = pButton->nButtonID;
        }
    }
    TaskConfig.pButtons = pButtons;

    // Show the Task Dialog
    hr = pTaskDialogIndirect(&TaskConfig, &nButton, रिक्त, रिक्त);

    // Free everything
    FreeLibrary(hComctl32);
    SDL_free(ampescape);
    SDL_free(wmessage);
    SDL_free(wtitle);
    साठी (i = 0; i < messageboxdata->numbuttons; i++) {
        SDL_free((ब_अक्षर_प्रकार *)pButtons[i].pszButtonText);
    }
    SDL_free(pButtons);

    // Check the Task Dialog was successful and give the result
    जर (SUCCEEDED(hr)) {
        जर (nButton == IDCANCEL) {
            *buttonID = nCancelButton;
        } अन्यथा जर (nButton >= IDBUTTONINDEX0 && nButton < IDBUTTONINDEX0 + messageboxdata->numbuttons) {
            *buttonID = messageboxdata->buttons[nButton - IDBUTTONINDEX0].buttonID;
        } अन्यथा {
            *buttonID = -1;
        }
        result = true;
    } अन्यथा {
        // We failed showing the Task Dialog, use the old message box!
        result = WIN_ShowOldMessageBox(messageboxdata, buttonID);
    }

done:
    जर (pSetThreadDpiAwarenessContext) {
        pSetThreadDpiAwarenessContext(previous_context);
    }
    परत result;
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

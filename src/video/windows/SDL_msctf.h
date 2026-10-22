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

#اگر_غیر_تعریف_شدہ SDL_msctf_h_
#تعریف_کرو SDL_msctf_h_

#شامل <unknwn.h>

#تعریف_کرو TF_INVALID_COOKIE            (0xffffffff)
#تعریف_کرو TF_IPSINK_FLAG_فعال        0x0001
#تعریف_کرو TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

قسمتعریف ساخت ITfThreadMgr ITfThreadMgr;
قسمتعریف ساخت ITfDocumentMgr ITfDocumentMgr;
قسمتعریف ساخت ITfClientId ITfClientId;

قسمتعریف ساخت IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
قسمتعریف ساخت IEnumTfFunctionProviders IEnumTfFunctionProviders;
قسمتعریف ساخت ITfFunctionProvider ITfFunctionProvider;
قسمتعریف ساخت ITfCompartmentMgr ITfCompartmentMgr;
قسمتعریف ساخت ITfContext ITfContext;
قسمتعریف ساخت IEnumTfContexts IEnumTfContexts;
قسمتعریف ساخت ITfUIElementSink ITfUIElementSink;
قسمتعریف ساخت ITfUIElement ITfUIElement;
قسمتعریف ساخت ITfUIElementMgr ITfUIElementMgr;
قسمتعریف ساخت IEnumTfUIElements IEnumTfUIElements;
قسمتعریف ساخت ITfThreadMgrEx ITfThreadMgrEx;
قسمتعریف ساخت ITfCandidateListUIElement ITfCandidateListUIElement;
قسمتعریف ساخت ITfReadingInformationUIElement ITfReadingInformationUIElement;
قسمتعریف ساخت ITf_داخلہ_Processor_Profile_Activation_Sink ITf_داخلہ_Processor_Profile_Activation_Sink;
قسمتعریف ساخت ITf_ماخذ ITf_ماخذ;

قسمتعریف DWORD TfClientId;
قسمتعریف DWORD TfEditCookie;

قسمتعریف ساخت ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *سیٹ_Focus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

ساخت ITfThreadMgr
{
    ثابت ساخت ITfThreadMgrVtbl *lpVtbl;
};

قسمتعریف ساخت ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *سیٹ_Focus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *Get_فعال_Flags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

ساخت ITfThreadMgrEx
{
    ثابت ساخت ITfThreadMgrExVtbl *lpVtbl;
};

قسمتعریف ساخت ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ڈالو_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *نکالو_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_چوٹی)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *Get_بنیاد)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

ساخت ITfDocumentMgr
{
    ثابت ساخت ITfDocumentMgrVtbl *lpVtbl;
};

قسمتعریف ساخت ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *انتہا_UIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

ساخت ITfUIElementSink
{
    ثابت ساخت ITfUIElementSinkVtbl *lpVtbl;
};

قسمتعریف ساخت ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *انتہا_UIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

ساخت ITfUIElementMgr
{
    ثابت ساخت ITfUIElementMgrVtbl *lpVtbl;
};

قسمتعریف ساخت ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_گنتی)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_صفحہ_اشاریہ)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *سیٹ_صفحہ_اشاریہ)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *Get_Current_صفحہ)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

ساخت ITfCandidateListUIElement
{
    ثابت ساخت ITfCandidateListUIElementVtbl *lpVtbl;
};

قسمتعریف ساخت ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_لمبائی)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_اشاریہ)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Is_Vertical_ترتیب_Preferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

ساخت ITfReadingInformationUIElement
{
    ثابت ساخت ITfReadingInformationUIElementVtbl *lpVtbl;
};

قسمتعریف ساخت ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

ساخت ITfUIElement
{
    ثابت ساخت ITfUIElementVtbl *lpVtbl;
};

قسمتعریف ساخت ITf_داخلہ_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_داخلہ_Processor_Profile_Activation_Sink *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITf_داخلہ_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_داخلہ_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_داخلہ_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_داخلہ_Processor_Profile_Activation_Sink_Vtbl;

ساخت ITf_داخلہ_Processor_Profile_Activation_Sink
{
    ثابت ساخت ITf_داخلہ_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

قسمتعریف ساخت ITf_ماخذ_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ماخذ *, REFIID, خالی **);
    ULONG (STDMETHODCALLTYPE *جوڑو_Ref)(ITf_ماخذ *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ماخذ *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITf_ماخذ *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITf_ماخذ *, DWORD);
} ITf_ماخذ_Vtbl;

ساخت ITf_ماخذ
{
    ثابت ساخت ITf_ماخذ_Vtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#اگر_ختم // SDL_msctf_h_

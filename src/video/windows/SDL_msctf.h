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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_msctf_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_msctf_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <unknwn.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TF_INVALID_COOKIE            (0xffffffff)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TF_IPSINK_FLAG_ਸਰਗਰਮ        0x0001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfThreadMgr ITfThreadMgr;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfDocumentMgr ITfDocumentMgr;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfClientId ITfClientId;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IEnumTfFunctionProviders IEnumTfFunctionProviders;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfFunctionProvider ITfFunctionProvider;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfCompartmentMgr ITfCompartmentMgr;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfContext ITfContext;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IEnumTfContexts IEnumTfContexts;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfUIElementSink ITfUIElementSink;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfUIElement ITfUIElement;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfUIElementMgr ITfUIElementMgr;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ IEnumTfUIElements IEnumTfUIElements;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfThreadMgrEx ITfThreadMgrEx;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfCandidateListUIElement ITfCandidateListUIElement;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfReadingInformationUIElement ITfReadingInformationUIElement;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITf_ਸਰੋਤ ITf_ਸਰੋਤ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ DWORD TfClientId;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ DWORD TfEditCookie;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *ਸੈੱਟ_Focus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

ਬਣਤਰ ITfThreadMgr
{
    ਅਚਲ ਬਣਤਰ ITfThreadMgrVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *ਸੈੱਟ_Focus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *Get_ਸਰਗਰਮ_Flags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

ਬਣਤਰ ITfThreadMgrEx
{
    ਅਚਲ ਬਣਤਰ ITfThreadMgrExVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ਧੱਕੋ_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *ਕੱਢੋ_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_ਸਿਖਰ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *Get_ਅਧਾਰ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

ਬਣਤਰ ITfDocumentMgr
{
    ਅਚਲ ਬਣਤਰ ITfDocumentMgrVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *ਸਿਰਾ_UIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

ਬਣਤਰ ITfUIElementSink
{
    ਅਚਲ ਬਣਤਰ ITfUIElementSinkVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *ਸਿਰਾ_UIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

ਬਣਤਰ ITfUIElementMgr
{
    ਅਚਲ ਬਣਤਰ ITfUIElementMgrVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_ਗਿਣਤੀ)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_ਪੰਨਾ_ਸੂਚਕਾਂਕ)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *ਸੈੱਟ_ਪੰਨਾ_ਸੂਚਕਾਂਕ)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *Get_Current_ਪੰਨਾ)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

ਬਣਤਰ ITfCandidateListUIElement
{
    ਅਚਲ ਬਣਤਰ ITfCandidateListUIElementVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_ਲੰਮਾਈ)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_ਸੂਚਕਾਂਕ)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Is_Vertical_ਕ੍ਰਮ_Preferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

ਬਣਤਰ ITfReadingInformationUIElement
{
    ਅਚਲ ਬਣਤਰ ITfReadingInformationUIElementVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

ਬਣਤਰ ITfUIElement
{
    ਅਚਲ ਬਣਤਰ ITfUIElementVtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink_Vtbl;

ਬਣਤਰ ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink
{
    ਅਚਲ ਬਣਤਰ ITf_ਨਿਵੇਸ਼_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ITf_ਸਰੋਤ_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ਸਰੋਤ *, REFIID, ਖਾਲੀ **);
    ULONG (STDMETHODCALLTYPE *ਜੋੜੋ_Ref)(ITf_ਸਰੋਤ *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ਸਰੋਤ *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITf_ਸਰੋਤ *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITf_ਸਰੋਤ *, DWORD);
} ITf_ਸਰੋਤ_Vtbl;

ਬਣਤਰ ITf_ਸਰੋਤ
{
    ਅਚਲ ਬਣਤਰ ITf_ਸਰੋਤ_Vtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#ਜੇ_ਅੰਤ // SDL_msctf_h_

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

#اگر_تعریف_نشده SDL_msctf_h_
#تعریف_کن SDL_msctf_h_

#ضمن <unknwn.h>

#تعریف_کن TF_INVALID_COOKIE            (0xffffffff)
#تعریف_کن TF_IPSINK_FLAG_فعال        0x0001
#تعریف_کن TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

تعريفنوع بنية ITfThreadMgr ITfThreadMgr;
تعريفنوع بنية ITfDocumentMgr ITfDocumentMgr;
تعريفنوع بنية ITfClientId ITfClientId;

تعريفنوع بنية IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
تعريفنوع بنية IEnumTfFunctionProviders IEnumTfFunctionProviders;
تعريفنوع بنية ITfFunctionProvider ITfFunctionProvider;
تعريفنوع بنية ITfCompartmentMgr ITfCompartmentMgr;
تعريفنوع بنية ITfContext ITfContext;
تعريفنوع بنية IEnumTfContexts IEnumTfContexts;
تعريفنوع بنية ITfUIElementSink ITfUIElementSink;
تعريفنوع بنية ITfUIElement ITfUIElement;
تعريفنوع بنية ITfUIElementMgr ITfUIElementMgr;
تعريفنوع بنية IEnumTfUIElements IEnumTfUIElements;
تعريفنوع بنية ITfThreadMgrEx ITfThreadMgrEx;
تعريفنوع بنية ITfCandidateListUIElement ITfCandidateListUIElement;
تعريفنوع بنية ITfReadingInformationUIElement ITfReadingInformationUIElement;
تعريفنوع بنية ITf_درون_داد_Processor_Profile_Activation_Sink ITf_درون_داد_Processor_Profile_Activation_Sink;
تعريفنوع بنية ITf_منبع ITf_منبع;

تعريفنوع DWORD TfClientId;
تعريفنوع DWORD TfEditCookie;

تعريفنوع بنية ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *مجموعه_Focus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

بنية ITfThreadMgr
{
    ثابت بنية ITfThreadMgrVtbl *lpVtbl;
};

تعريفنوع بنية ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *مجموعه_Focus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *Get_فعال_Flags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

بنية ITfThreadMgrEx
{
    ثابت بنية ITfThreadMgrExVtbl *lpVtbl;
};

تعريفنوع بنية ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *افزودن_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *برداشت_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_بالاترین)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *Get_پایه)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

بنية ITfDocumentMgr
{
    ثابت بنية ITfDocumentMgrVtbl *lpVtbl;
};

تعريفنوع بنية ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *انتها_UIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

بنية ITfUIElementSink
{
    ثابت بنية ITfUIElementSinkVtbl *lpVtbl;
};

تعريفنوع بنية ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *انتها_UIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

بنية ITfUIElementMgr
{
    ثابت بنية ITfUIElementMgrVtbl *lpVtbl;
};

تعريفنوع بنية ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_شمار)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_صفحه_شاخص)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *مجموعه_صفحه_شاخص)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *Get_Current_صفحه)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

بنية ITfCandidateListUIElement
{
    ثابت بنية ITfCandidateListUIElementVtbl *lpVtbl;
};

تعريفنوع بنية ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_درازی)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_شاخص)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Is_Vertical_ترتیب_Preferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

بنية ITfReadingInformationUIElement
{
    ثابت بنية ITfReadingInformationUIElementVtbl *lpVtbl;
};

تعريفنوع بنية ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

بنية ITfUIElement
{
    ثابت بنية ITfUIElementVtbl *lpVtbl;
};

تعريفنوع بنية ITf_درون_داد_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_درون_داد_Processor_Profile_Activation_Sink *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITf_درون_داد_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_درون_داد_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_درون_داد_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_درون_داد_Processor_Profile_Activation_Sink_Vtbl;

بنية ITf_درون_داد_Processor_Profile_Activation_Sink
{
    ثابت بنية ITf_درون_داد_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

تعريفنوع بنية ITf_منبع_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_منبع *, REFIID, فراغ **);
    ULONG (STDMETHODCALLTYPE *جمع_کن_Ref)(ITf_منبع *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_منبع *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITf_منبع *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITf_منبع *, DWORD);
} ITf_منبع_Vtbl;

بنية ITf_منبع
{
    ثابت بنية ITf_منبع_Vtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#پایان_اگر // SDL_msctf_h_

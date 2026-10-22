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

#ifndef SDL_msctf_h_
#define SDL_msctf_h_

#অন্তর্ভাৱ <unknwn.h>

#define TF_INVALID_COOKIE            (0xffffffff)
#define TF_IPSINK_FLAG_ACTIVE        0x0001
#define TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

প্রকারনির্দেশ সংরচনা ITfThreadMgr ITfThreadMgr;
প্রকারনির্দেশ সংরচনা ITfDocumentMgr ITfDocumentMgr;
প্রকারনির্দেশ সংরচনা ITfClientId ITfClientId;

প্রকারনির্দেশ সংরচনা IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
প্রকারনির্দেশ সংরচনা IEnumTfFunctionProviders IEnumTfFunctionProviders;
প্রকারনির্দেশ সংরচনা ITfFunctionProvider ITfFunctionProvider;
প্রকারনির্দেশ সংরচনা ITfCompartmentMgr ITfCompartmentMgr;
প্রকারনির্দেশ সংরচনা ITfContext ITfContext;
প্রকারনির্দেশ সংরচনা IEnumTfContexts IEnumTfContexts;
প্রকারনির্দেশ সংরচনা ITfUIElementSink ITfUIElementSink;
প্রকারনির্দেশ সংরচনা ITfUIElement ITfUIElement;
প্রকারনির্দেশ সংরচনা ITfUIElementMgr ITfUIElementMgr;
প্রকারনির্দেশ সংরচনা IEnumTfUIElements IEnumTfUIElements;
প্রকারনির্দেশ সংরচনা ITfThreadMgrEx ITfThreadMgrEx;
প্রকারনির্দেশ সংরচনা ITfCandidateListUIElement ITfCandidateListUIElement;
প্রকারনির্দেশ সংরচনা ITfReadingInformationUIElement ITfReadingInformationUIElement;
প্রকারনির্দেশ সংরচনা ITf_প্ৰবেশ_Processor_Profile_Activation_Sink ITf_প্ৰবেশ_Processor_Profile_Activation_Sink;
প্রকারনির্দেশ সংরচনা ITfSource ITfSource;

প্রকারনির্দেশ DWORD TfClientId;
প্রকারনির্দেশ DWORD TfEditCookie;

প্রকারনির্দেশ সংরচনা ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *SetFocus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

সংরচনা ITfThreadMgr
{
    ধ্রুৱ সংরচনা ITfThreadMgrVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *SetFocus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetActiveFlags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

সংরচনা ITfThreadMgrEx
{
    ধ্রুৱ সংরচনা ITfThreadMgrExVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ঠেলো_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *বেৰ_কৰো_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_শীৰ্ষ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetBase)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

সংরচনা ITfDocumentMgr
{
    ধ্রুৱ সংরচনা ITfDocumentMgrVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

সংরচনা ITfUIElementSink
{
    ধ্রুৱ সংরচনা ITfUIElementSinkVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

সংরচনা ITfUIElementMgr
{
    ধ্রুৱ সংরচনা ITfUIElementMgrVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_গুনতি)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *SetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *GetCurrentPage)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

সংরচনা ITfCandidateListUIElement
{
    ধ্রুৱ সংরচনা ITfCandidateListUIElementVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetMaxReadingStringLength)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetErrorIndex)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *IsVerticalOrderPreferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

সংরচনা ITfReadingInformationUIElement
{
    ধ্রুৱ সংরচনা ITfReadingInformationUIElementVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

সংরচনা ITfUIElement
{
    ধ্রুৱ সংরচনা ITfUIElementVtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITf_প্ৰবেশ_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_প্ৰবেশ_Processor_Profile_Activation_Sink *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITf_প্ৰবেশ_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_প্ৰবেশ_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_প্ৰবেশ_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_প্ৰবেশ_Processor_Profile_Activation_Sink_Vtbl;

সংরচনা ITf_প্ৰবেশ_Processor_Profile_Activation_Sink
{
    ধ্রুৱ সংরচনা ITf_প্ৰবেশ_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

প্রকারনির্দেশ সংরচনা ITfSourceVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfSource *, REFIID, শূন্য **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfSource *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfSource *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITfSource *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITfSource *, DWORD);
} ITfSourceVtbl;

সংরচনা ITfSource
{
    ধ্রুৱ সংরচনা ITfSourceVtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#endif // SDL_msctf_h_

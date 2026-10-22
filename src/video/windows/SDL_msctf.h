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

#నిర్వచితం_కాకపోతే SDL_msctf_h_
#నిర్వచించు SDL_msctf_h_

#అన్తర్భావ <unknwn.h>

#నిర్వచించు TF_INVALID_COOKIE            (0xffffffff)
#నిర్వచించు TF_IPSINK_FLAG_చురుకైన        0x0001
#నిర్వచించు TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

రకనిర్వచనం నిర్మాణం ITfThreadMgr ITfThreadMgr;
రకనిర్వచనం నిర్మాణం ITfDocumentMgr ITfDocumentMgr;
రకనిర్వచనం నిర్మాణం ITfClientId ITfClientId;

రకనిర్వచనం నిర్మాణం IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
రకనిర్వచనం నిర్మాణం IEnumTfFunctionProviders IEnumTfFunctionProviders;
రకనిర్వచనం నిర్మాణం ITfFunctionProvider ITfFunctionProvider;
రకనిర్వచనం నిర్మాణం ITfCompartmentMgr ITfCompartmentMgr;
రకనిర్వచనం నిర్మాణం ITfContext ITfContext;
రకనిర్వచనం నిర్మాణం IEnumTfContexts IEnumTfContexts;
రకనిర్వచనం నిర్మాణం ITfUIElementSink ITfUIElementSink;
రకనిర్వచనం నిర్మాణం ITfUIElement ITfUIElement;
రకనిర్వచనం నిర్మాణం ITfUIElementMgr ITfUIElementMgr;
రకనిర్వచనం నిర్మాణం IEnumTfUIElements IEnumTfUIElements;
రకనిర్వచనం నిర్మాణం ITfThreadMgrEx ITfThreadMgrEx;
రకనిర్వచనం నిర్మాణం ITfCandidateListUIElement ITfCandidateListUIElement;
రకనిర్వచనం నిర్మాణం ITfReadingInformationUIElement ITfReadingInformationUIElement;
రకనిర్వచనం నిర్మాణం ITf_ఆదానం_Processor_Profile_Activation_Sink ITf_ఆదానం_Processor_Profile_Activation_Sink;
రకనిర్వచనం నిర్మాణం ITf_ఆధారం ITf_ఆధారం;

రకనిర్వచనం DWORD TfClientId;
రకనిర్వచనం DWORD TfEditCookie;

రకనిర్వచనం నిర్మాణం ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *సమితి_Focus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

నిర్మాణం ITfThreadMgr
{
    స్థిరరాశి నిర్మాణం ITfThreadMgrVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *సమితి_Focus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *Get_చురుకైన_Flags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

నిర్మాణం ITfThreadMgrEx
{
    స్థిరరాశి నిర్మాణం ITfThreadMgrExVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *నెట్టు_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *తీయి_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_శిఖరం)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *Get_పునాది)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

నిర్మాణం ITfDocumentMgr
{
    స్థిరరాశి నిర్మాణం ITfDocumentMgrVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *చివర_UIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

నిర్మాణం ITfUIElementSink
{
    స్థిరరాశి నిర్మాణం ITfUIElementSinkVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *చివర_UIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

నిర్మాణం ITfUIElementMgr
{
    స్థిరరాశి నిర్మాణం ITfUIElementMgrVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_లెక్క)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_పుట_సూచీ)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *సమితి_పుట_సూచీ)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *Get_Current_పుట)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

నిర్మాణం ITfCandidateListUIElement
{
    స్థిరరాశి నిర్మాణం ITfCandidateListUIElementVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_నిడివి)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_సూచీ)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Is_Vertical_క్రమం_Preferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

నిర్మాణం ITfReadingInformationUIElement
{
    స్థిరరాశి నిర్మాణం ITfReadingInformationUIElementVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

నిర్మాణం ITfUIElement
{
    స్థిరరాశి నిర్మాణం ITfUIElementVtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITf_ఆదానం_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ఆదానం_Processor_Profile_Activation_Sink *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITf_ఆదానం_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ఆదానం_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_ఆదానం_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_ఆదానం_Processor_Profile_Activation_Sink_Vtbl;

నిర్మాణం ITf_ఆదానం_Processor_Profile_Activation_Sink
{
    స్థిరరాశి నిర్మాణం ITf_ఆదానం_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

రకనిర్వచనం నిర్మాణం ITf_ఆధారం_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ఆధారం *, REFIID, శూన్య **);
    ULONG (STDMETHODCALLTYPE *కూడు_Ref)(ITf_ఆధారం *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ఆధారం *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITf_ఆధారం *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITf_ఆధారం *, DWORD);
} ITf_ఆధారం_Vtbl;

నిర్మాణం ITf_ఆధారం
{
    స్థిరరాశి నిర్మాణం ITf_ఆధారం_Vtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#అయితే_ముగింపు // SDL_msctf_h_

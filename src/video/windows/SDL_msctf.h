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

#अन्तर्भाव <unknwn.h>

#define TF_INVALID_COOKIE            (0xffffffff)
#define TF_IPSINK_FLAG_ACTIVE        0x0001
#define TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

प्रकारव्याख्या संरचना ITfThreadMgr ITfThreadMgr;
प्रकारव्याख्या संरचना ITfDocumentMgr ITfDocumentMgr;
प्रकारव्याख्या संरचना ITfClientId ITfClientId;

प्रकारव्याख्या संरचना IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
प्रकारव्याख्या संरचना IEnumTfFunctionProviders IEnumTfFunctionProviders;
प्रकारव्याख्या संरचना ITfFunctionProvider ITfFunctionProvider;
प्रकारव्याख्या संरचना ITfCompartmentMgr ITfCompartmentMgr;
प्रकारव्याख्या संरचना ITfContext ITfContext;
प्रकारव्याख्या संरचना IEnumTfContexts IEnumTfContexts;
प्रकारव्याख्या संरचना ITfUIElementSink ITfUIElementSink;
प्रकारव्याख्या संरचना ITfUIElement ITfUIElement;
प्रकारव्याख्या संरचना ITfUIElementMgr ITfUIElementMgr;
प्रकारव्याख्या संरचना IEnumTfUIElements IEnumTfUIElements;
प्रकारव्याख्या संरचना ITfThreadMgrEx ITfThreadMgrEx;
प्रकारव्याख्या संरचना ITfCandidateListUIElement ITfCandidateListUIElement;
प्रकारव्याख्या संरचना ITfReadingInformationUIElement ITfReadingInformationUIElement;
प्रकारव्याख्या संरचना ITf_आदान_Processor_Profile_Activation_Sink ITf_आदान_Processor_Profile_Activation_Sink;
प्रकारव्याख्या संरचना ITfSource ITfSource;

प्रकारव्याख्या DWORD TfClientId;
प्रकारव्याख्या DWORD TfEditCookie;

प्रकारव्याख्या संरचना ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, शून्य **);
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

संरचना ITfThreadMgr
{
    स्थिरांक संरचना ITfThreadMgrVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, शून्य **);
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

संरचना ITfThreadMgrEx
{
    स्थिरांक संरचना ITfThreadMgrExVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ढकला_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *काढा_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_शीर्ष)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetBase)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

संरचना ITfDocumentMgr
{
    स्थिरांक संरचना ITfDocumentMgrVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

संरचना ITfUIElementSink
{
    स्थिरांक संरचना ITfUIElementSinkVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

संरचना ITfUIElementMgr
{
    स्थिरांक संरचना ITfUIElementMgrVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_मोजणी)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *SetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *GetCurrentPage)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

संरचना ITfCandidateListUIElement
{
    स्थिरांक संरचना ITfCandidateListUIElementVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, शून्य **);
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

संरचना ITfReadingInformationUIElement
{
    स्थिरांक संरचना ITfReadingInformationUIElementVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

संरचना ITfUIElement
{
    स्थिरांक संरचना ITfUIElementVtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITf_आदान_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_आदान_Processor_Profile_Activation_Sink *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITf_आदान_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_आदान_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_आदान_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_आदान_Processor_Profile_Activation_Sink_Vtbl;

संरचना ITf_आदान_Processor_Profile_Activation_Sink
{
    स्थिरांक संरचना ITf_आदान_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

प्रकारव्याख्या संरचना ITfSourceVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfSource *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfSource *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfSource *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITfSource *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITfSource *, DWORD);
} ITfSourceVtbl;

संरचना ITfSource
{
    स्थिरांक संरचना ITfSourceVtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#endif // SDL_msctf_h_

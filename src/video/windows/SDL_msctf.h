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

#यदि_अपरिभाषितम् SDL_msctf_h_
#परिभाषय SDL_msctf_h_

#अन्तर्भाव <unknwn.h>

#परिभाषय TF_INVALID_COOKIE            (0xffffffff)
#परिभाषय TF_IPSINK_FLAG_सक्रिय        0x0001
#परिभाषय TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

प्रकारनिर्देश संरचना ITfThreadMgr ITfThreadMgr;
प्रकारनिर्देश संरचना ITfDocumentMgr ITfDocumentMgr;
प्रकारनिर्देश संरचना ITfClientId ITfClientId;

प्रकारनिर्देश संरचना IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
प्रकारनिर्देश संरचना IEnumTfFunctionProviders IEnumTfFunctionProviders;
प्रकारनिर्देश संरचना ITfFunctionProvider ITfFunctionProvider;
प्रकारनिर्देश संरचना ITfCompartmentMgr ITfCompartmentMgr;
प्रकारनिर्देश संरचना ITfContext ITfContext;
प्रकारनिर्देश संरचना IEnumTfContexts IEnumTfContexts;
प्रकारनिर्देश संरचना ITfUIElementSink ITfUIElementSink;
प्रकारनिर्देश संरचना ITfUIElement ITfUIElement;
प्रकारनिर्देश संरचना ITfUIElementMgr ITfUIElementMgr;
प्रकारनिर्देश संरचना IEnumTfUIElements IEnumTfUIElements;
प्रकारनिर्देश संरचना ITfThreadMgrEx ITfThreadMgrEx;
प्रकारनिर्देश संरचना ITfCandidateListUIElement ITfCandidateListUIElement;
प्रकारनिर्देश संरचना ITfReadingInformationUIElement ITfReadingInformationUIElement;
प्रकारनिर्देश संरचना ITf_निवेशः_Processor_Profile_Activation_Sink ITf_निवेशः_Processor_Profile_Activation_Sink;
प्रकारनिर्देश संरचना ITfSource ITfSource;

प्रकारनिर्देश DWORD TfClientId;
प्रकारनिर्देश DWORD TfEditCookie;

प्रकारनिर्देश संरचना ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *समुच्चयः_Focus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

संरचना ITfThreadMgr
{
    ध्रुव संरचना ITfThreadMgrVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *समुच्चयः_Focus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *Get_सक्रिय_Flags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

संरचना ITfThreadMgrEx
{
    ध्रुव संरचना ITfThreadMgrExVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *प्रक्षिप_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *निष्कासय_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_शिखरम्)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *Get_आधारः)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

संरचना ITfDocumentMgr
{
    ध्रुव संरचना ITfDocumentMgrVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *अन्तः_UIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

संरचना ITfUIElementSink
{
    ध्रुव संरचना ITfUIElementSinkVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *अन्तः_UIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

संरचना ITfUIElementMgr
{
    ध्रुव संरचना ITfUIElementMgrVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_गणनम्)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Page_सूचकांक)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *समुच्चयः_Page_सूचकांक)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *GetCurrentPage)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

संरचना ITfCandidateListUIElement
{
    ध्रुव संरचना ITfCandidateListUIElementVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_दीर्घता)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_सूचकांक)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Is_Vertical_क्रमः_Preferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

संरचना ITfReadingInformationUIElement
{
    ध्रुव संरचना ITfReadingInformationUIElementVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

संरचना ITfUIElement
{
    ध्रुव संरचना ITfUIElementVtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITf_निवेशः_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_निवेशः_Processor_Profile_Activation_Sink *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITf_निवेशः_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_निवेशः_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_निवेशः_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_निवेशः_Processor_Profile_Activation_Sink_Vtbl;

संरचना ITf_निवेशः_Processor_Profile_Activation_Sink
{
    ध्रुव संरचना ITf_निवेशः_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

प्रकारनिर्देश संरचना ITfSourceVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfSource *, REFIID, शून्य **);
    ULONG (STDMETHODCALLTYPE *सङ्कलय_Ref)(ITfSource *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfSource *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITfSource *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITfSource *, DWORD);
} ITfSourceVtbl;

संरचना ITfSource
{
    ध्रुव संरचना ITfSourceVtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#यदि_अन्तः // SDL_msctf_h_

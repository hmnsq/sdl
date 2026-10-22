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

#ଅନ୍ତର୍ଭାଵ <unknwn.h>

#define TF_INVALID_COOKIE            (0xffffffff)
#define TF_IPSINK_FLAG_ACTIVE        0x0001
#define TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfThreadMgr ITfThreadMgr;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfDocumentMgr ITfDocumentMgr;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfClientId ITfClientId;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା IEnumTfFunctionProviders IEnumTfFunctionProviders;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfFunctionProvider ITfFunctionProvider;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfCompartmentMgr ITfCompartmentMgr;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfContext ITfContext;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା IEnumTfContexts IEnumTfContexts;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfUIElementSink ITfUIElementSink;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfUIElement ITfUIElement;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfUIElementMgr ITfUIElementMgr;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା IEnumTfUIElements IEnumTfUIElements;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfThreadMgrEx ITfThreadMgrEx;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfCandidateListUIElement ITfCandidateListUIElement;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfReadingInformationUIElement ITfReadingInformationUIElement;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITf_ନିବେଶ_Processor_Profile_Activation_Sink ITf_ନିବେଶ_Processor_Profile_Activation_Sink;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfSource ITfSource;

ପ୍ରକାରବ୍ୟାଖ୍ୟା DWORD TfClientId;
ପ୍ରକାରବ୍ୟାଖ୍ୟା DWORD TfEditCookie;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, ଶୂନ୍ୟ **);
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

ସଂରଚନା ITfThreadMgr
{
    ଅଚଳ ସଂରଚନା ITfThreadMgrVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, ଶୂନ୍ୟ **);
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

ସଂରଚନା ITfThreadMgrEx
{
    ଅଚଳ ସଂରଚନା ITfThreadMgrExVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ଠେଲ_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *କାଢ଼_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_ଶୀର୍ଷ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetBase)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

ସଂରଚନା ITfDocumentMgr
{
    ଅଚଳ ସଂରଚନା ITfDocumentMgrVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

ସଂରଚନା ITfUIElementSink
{
    ଅଚଳ ସଂରଚନା ITfUIElementSinkVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

ସଂରଚନା ITfUIElementMgr
{
    ଅଚଳ ସଂରଚନା ITfUIElementMgrVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_ଗଣନା)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *SetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *GetCurrentPage)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

ସଂରଚନା ITfCandidateListUIElement
{
    ଅଚଳ ସଂରଚନା ITfCandidateListUIElementVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, ଶୂନ୍ୟ **);
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

ସଂରଚନା ITfReadingInformationUIElement
{
    ଅଚଳ ସଂରଚନା ITfReadingInformationUIElementVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

ସଂରଚନା ITfUIElement
{
    ଅଚଳ ସଂରଚନା ITfUIElementVtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITf_ନିବେଶ_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ନିବେଶ_Processor_Profile_Activation_Sink *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITf_ନିବେଶ_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ନିବେଶ_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_ନିବେଶ_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_ନିବେଶ_Processor_Profile_Activation_Sink_Vtbl;

ସଂରଚନା ITf_ନିବେଶ_Processor_Profile_Activation_Sink
{
    ଅଚଳ ସଂରଚନା ITf_ନିବେଶ_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା ITfSourceVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfSource *, REFIID, ଶୂନ୍ୟ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfSource *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfSource *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITfSource *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITfSource *, DWORD);
} ITfSourceVtbl;

ସଂରଚନା ITfSource
{
    ଅଚଳ ସଂରଚନା ITfSourceVtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#endif // SDL_msctf_h_

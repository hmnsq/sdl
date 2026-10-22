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

#ಅನ್ತರ್ಭಾವ <unknwn.h>

#define TF_INVALID_COOKIE            (0xffffffff)
#define TF_IPSINK_FLAG_ACTIVE        0x0001
#define TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfThreadMgr ITfThreadMgr;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfDocumentMgr ITfDocumentMgr;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfClientId ITfClientId;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ IEnumTfFunctionProviders IEnumTfFunctionProviders;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfFunctionProvider ITfFunctionProvider;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfCompartmentMgr ITfCompartmentMgr;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfContext ITfContext;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ IEnumTfContexts IEnumTfContexts;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfUIElementSink ITfUIElementSink;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfUIElement ITfUIElement;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfUIElementMgr ITfUIElementMgr;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ IEnumTfUIElements IEnumTfUIElements;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfThreadMgrEx ITfThreadMgrEx;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfCandidateListUIElement ITfCandidateListUIElement;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfReadingInformationUIElement ITfReadingInformationUIElement;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfSource ITfSource;

ಪ್ರಕಾರನಿರ್ದೇಶ DWORD TfClientId;
ಪ್ರಕಾರನಿರ್ದೇಶ DWORD TfEditCookie;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, ಶೂನ್ಯ **);
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

ಸಂರಚನಾ ITfThreadMgr
{
    ಧ್ರುವ ಸಂರಚನಾ ITfThreadMgrVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, ಶೂನ್ಯ **);
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

ಸಂರಚನಾ ITfThreadMgrEx
{
    ಧ್ರುವ ಸಂರಚನಾ ITfThreadMgrExVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ತಳ್ಳು_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *ತೆಗೆ_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_ತುದಿ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetBase)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

ಸಂರಚನಾ ITfDocumentMgr
{
    ಧ್ರುವ ಸಂರಚನಾ ITfDocumentMgrVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

ಸಂರಚನಾ ITfUIElementSink
{
    ಧ್ರುವ ಸಂರಚನಾ ITfUIElementSinkVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

ಸಂರಚನಾ ITfUIElementMgr
{
    ಧ್ರುವ ಸಂರಚನಾ ITfUIElementMgrVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_ಎಣಿಕೆ)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *SetPageIndex)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *GetCurrentPage)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

ಸಂರಚನಾ ITfCandidateListUIElement
{
    ಧ್ರುವ ಸಂರಚನಾ ITfCandidateListUIElementVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, ಶೂನ್ಯ **);
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

ಸಂರಚನಾ ITfReadingInformationUIElement
{
    ಧ್ರುವ ಸಂರಚನಾ ITfReadingInformationUIElementVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

ಸಂರಚನಾ ITfUIElement
{
    ಧ್ರುವ ಸಂರಚನಾ ITfUIElementVtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink_Vtbl;

ಸಂರಚನಾ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink
{
    ಧ್ರುವ ಸಂರಚನಾ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ ITfSourceVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfSource *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfSource *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfSource *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITfSource *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITfSource *, DWORD);
} ITfSourceVtbl;

ಸಂರಚನಾ ITfSource
{
    ಧ್ರುವ ಸಂರಚನಾ ITfSourceVtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#endif // SDL_msctf_h_

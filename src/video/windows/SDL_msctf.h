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

#अगर_अघोषित SDL_msctf_h_
#घोषणा SDL_msctf_h_

#समावेश <unknwn.h>

#घोषणा TF_INVALID_COOKIE            (0xffffffff)
#घोषणा TF_IPSINK_FLAG_ACTIVE        0x0001
#घोषणा TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

प्रकार काष्ठा ITfThreadMgr ITfThreadMgr;
प्रकार काष्ठा ITfDocumentMgr ITfDocumentMgr;
प्रकार काष्ठा ITfClientId ITfClientId;

प्रकार काष्ठा IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
प्रकार काष्ठा IEnumTfFunctionProviders IEnumTfFunctionProviders;
प्रकार काष्ठा ITfFunctionProvider ITfFunctionProvider;
प्रकार काष्ठा ITfCompartmentMgr ITfCompartmentMgr;
प्रकार काष्ठा ITfContext ITfContext;
प्रकार काष्ठा IEnumTfContexts IEnumTfContexts;
प्रकार काष्ठा ITfUIElementSink ITfUIElementSink;
प्रकार काष्ठा ITfUIElement ITfUIElement;
प्रकार काष्ठा ITfUIElementMgr ITfUIElementMgr;
प्रकार काष्ठा IEnumTfUIElements IEnumTfUIElements;
प्रकार काष्ठा ITfThreadMgrEx ITfThreadMgrEx;
प्रकार काष्ठा ITfCandidateListUIElement ITfCandidateListUIElement;
प्रकार काष्ठा ITfReadingInformationUIElement ITfReadingInformationUIElement;
प्रकार काष्ठा ITf_निवेश_Processor_Profile_Activation_Sink ITf_निवेश_Processor_Profile_Activation_Sink;
प्रकार काष्ठा ITfSource ITfSource;

प्रकार DWORD TfClientId;
प्रकार DWORD TfEditCookie;

प्रकार काष्ठा ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, व्योम **);
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

काष्ठा ITfThreadMgr
{
    स्थिर काष्ठा ITfThreadMgrVtbl *lpVtbl;
};

प्रकार काष्ठा ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, व्योम **);
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

काष्ठा ITfThreadMgrEx
{
    स्थिर काष्ठा ITfThreadMgrExVtbl *lpVtbl;
};

प्रकार काष्ठा ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *धकेलो_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *निकालो_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_शीर्ष)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetBase)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

काष्ठा ITfDocumentMgr
{
    स्थिर काष्ठा ITfDocumentMgrVtbl *lpVtbl;
};

प्रकार काष्ठा ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

काष्ठा ITfUIElementSink
{
    स्थिर काष्ठा ITfUIElementSinkVtbl *lpVtbl;
};

प्रकार काष्ठा ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *EndUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

काष्ठा ITfUIElementMgr
{
    स्थिर काष्ठा ITfUIElementMgrVtbl *lpVtbl;
};

प्रकार काष्ठा ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfCandidateListUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfCandidateListUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfCandidateListUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfCandidateListUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfCandidateListUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfCandidateListUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfCandidateListUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetDocumentMgr)(ITfCandidateListUIElement *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *Get_गिनती)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetSelection)(ITfCandidateListUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfCandidateListUIElement *, UINT, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Page_सूचकांक)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *Set_Page_सूचकांक)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *GetCurrentPage)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

काष्ठा ITfCandidateListUIElement
{
    स्थिर काष्ठा ITfCandidateListUIElementVtbl *lpVtbl;
};

प्रकार काष्ठा ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_लंबाई)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_सूचकांक)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *IsVerticalOrderPreferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

काष्ठा ITfReadingInformationUIElement
{
    स्थिर काष्ठा ITfReadingInformationUIElementVtbl *lpVtbl;
};

प्रकार काष्ठा ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

काष्ठा ITfUIElement
{
    स्थिर काष्ठा ITfUIElementVtbl *lpVtbl;
};

प्रकार काष्ठा ITf_निवेश_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_निवेश_Processor_Profile_Activation_Sink *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITf_निवेश_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_निवेश_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_निवेश_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_निवेश_Processor_Profile_Activation_Sink_Vtbl;

काष्ठा ITf_निवेश_Processor_Profile_Activation_Sink
{
    स्थिर काष्ठा ITf_निवेश_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

प्रकार काष्ठा ITfSourceVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfSource *, REFIID, व्योम **);
    ULONG (STDMETHODCALLTYPE *AddRef)(ITfSource *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfSource *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITfSource *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITfSource *, DWORD);
} ITfSourceVtbl;

काष्ठा ITfSource
{
    स्थिर काष्ठा ITfSourceVtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#पूर्ण_अगर // SDL_msctf_h_

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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_msctf_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_msctf_h_

#ಅನ್ತರ್ಭಾವ <unknwn.h>

#ವ್ಯಾಖ್ಯಾನಿಸು TF_INVALID_COOKIE            (0xffffffff)
#ವ್ಯಾಖ್ಯಾನಿಸು TF_IPSINK_FLAG_ಸಕ್ರಿಯ        0x0001
#ವ್ಯಾಖ್ಯಾನಿಸು TF_TMAE_UIELEMENTENABLEDONLY 0x00000004

/* *INDENT-OFF* */ // clang-format off

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfThreadMgr ITfThreadMgr;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfDocumentMgr ITfDocumentMgr;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfClientId ITfClientId;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IEnumTfDocumentMgrs IEnumTfDocumentMgrs;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IEnumTfFunctionProviders IEnumTfFunctionProviders;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfFunctionProvider ITfFunctionProvider;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfCompartmentMgr ITfCompartmentMgr;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfContext ITfContext;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IEnumTfContexts IEnumTfContexts;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfUIElementSink ITfUIElementSink;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfUIElement ITfUIElement;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfUIElementMgr ITfUIElementMgr;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ IEnumTfUIElements IEnumTfUIElements;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfThreadMgrEx ITfThreadMgrEx;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfCandidateListUIElement ITfCandidateListUIElement;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfReadingInformationUIElement ITfReadingInformationUIElement;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITf_ಮೂಲ ITf_ಮೂಲ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ DWORD TfClientId;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ DWORD TfEditCookie;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfThreadMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgr *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfThreadMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgr *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgr *);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgr *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *ಗಣ_Focus)(ITfThreadMgr *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgr *, HWND, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgr *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgr *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgr *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgr *, ITfCompartmentMgr **);
} ITfThreadMgrVtbl;

ರಚನೆ ITfThreadMgr
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfThreadMgrVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfThreadMgrExVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfThreadMgrEx *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfThreadMgrEx *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *Activate)(ITfThreadMgrEx *, TfClientId *);
    HRESULT (STDMETHODCALLTYPE *Deactivate)(ITfThreadMgrEx *);
    HRESULT (STDMETHODCALLTYPE *CreateDocumentMgr)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *EnumDocumentMgrs)(ITfThreadMgrEx *, IEnumTfDocumentMgrs **);
    HRESULT (STDMETHODCALLTYPE *GetFocus)(ITfThreadMgrEx *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *ಗಣ_Focus)(ITfThreadMgrEx *, ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *AssociateFocus)(ITfThreadMgrEx *, ITfDocumentMgr *, ITfDocumentMgr **);
    HRESULT (STDMETHODCALLTYPE *IsThreadFocus)(ITfThreadMgrEx *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetFunctionProvider)(ITfThreadMgrEx *, REFCLSID, ITfFunctionProvider **);
    HRESULT (STDMETHODCALLTYPE *EnumFunctionProviders)(ITfThreadMgrEx *, IEnumTfFunctionProviders **);
    HRESULT (STDMETHODCALLTYPE *GetGlobalCompartment)(ITfThreadMgrEx *, ITfCompartmentMgr **);
    HRESULT (STDMETHODCALLTYPE *ActivateEx)(ITfThreadMgrEx *, TfClientId *, DWORD);
    HRESULT (STDMETHODCALLTYPE *Get_ಸಕ್ರಿಯ_Flags)(ITfThreadMgrEx *, DWORD *);
} ITfThreadMgrExVtbl;

ರಚನೆ ITfThreadMgrEx
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfThreadMgrExVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfDocumentMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfDocumentMgr *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfDocumentMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *CreateContext)(ITfDocumentMgr *, TfClientId, DWORD, IUnknown *, ITfContext **, TfEditCookie *);
    HRESULT (STDMETHODCALLTYPE *ತಳ್ಳು_2)(ITfDocumentMgr *, ITfContext *);
    HRESULT (STDMETHODCALLTYPE *ತೆಗೆ_2)(ITfDocumentMgr *);
    HRESULT (STDMETHODCALLTYPE *Get_ತುದಿ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *Get_ತಳ)(ITfDocumentMgr *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *EnumContexts)(ITfDocumentMgr *, IEnumTfContexts **);
} ITfDocumentMgrVtbl;

ರಚನೆ ITfDocumentMgr
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfDocumentMgrVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfUIElementSinkVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementSink *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfUIElementSink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementSink *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementSink *, DWORD, BOOL *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementSink *, DWORD);
    HRESULT (STDMETHODCALLTYPE *ಕೊನೆ_UIElement)(ITfUIElementSink *, DWORD);
} ITfUIElementSinkVtbl;

ರಚನೆ ITfUIElementSink
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfUIElementSinkVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfUIElementMgrVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElementMgr *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfUIElementMgr *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElementMgr *);
    HRESULT (STDMETHODCALLTYPE *BeginUIElement)(ITfUIElementMgr *, ITfUIElement *, BOOL *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UpdateUIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *ಕೊನೆ_UIElement)(ITfUIElementMgr *, DWORD);
    HRESULT (STDMETHODCALLTYPE *GetUIElement)(ITfUIElementMgr *, DWORD, ITfUIElement **);
    HRESULT (STDMETHODCALLTYPE *EnumUIElements)(ITfUIElementMgr *, IEnumTfUIElements **);
} ITfUIElementMgrVtbl;

ರಚನೆ ITfUIElementMgr
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfUIElementMgrVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfCandidateListUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfCandidateListUIElement *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfCandidateListUIElement *);
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
    HRESULT (STDMETHODCALLTYPE *Get_ಪುಟ_ಸೂಚ್ಯಂಕ)(ITfCandidateListUIElement *, UINT *, UINT, UINT *);
    HRESULT (STDMETHODCALLTYPE *ಗಣ_ಪುಟ_ಸೂಚ್ಯಂಕ)(ITfCandidateListUIElement *, UINT *, UINT);
    HRESULT (STDMETHODCALLTYPE *Get_Current_ಪುಟ)(ITfCandidateListUIElement *, UINT *);
} ITfCandidateListUIElementVtbl;

ರಚನೆ ITfCandidateListUIElement
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfCandidateListUIElementVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfReadingInformationUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfReadingInformationUIElement *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfReadingInformationUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfReadingInformationUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfReadingInformationUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfReadingInformationUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfReadingInformationUIElement *, BOOL *);
    HRESULT (STDMETHODCALLTYPE *GetUpdatedFlags)(ITfReadingInformationUIElement *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *GetContext)(ITfReadingInformationUIElement *, ITfContext **);
    HRESULT (STDMETHODCALLTYPE *GetString)(ITfReadingInformationUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *Get_Max_Reading_String_ಉದ್ದಳತೆ)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Get_Error_ಸೂಚ್ಯಂಕ)(ITfReadingInformationUIElement *, UINT *);
    HRESULT (STDMETHODCALLTYPE *Is_Vertical_ಕ್ರಮ_Preferred)(ITfReadingInformationUIElement *, BOOL *);
} ITfReadingInformationUIElementVtbl;

ರಚನೆ ITfReadingInformationUIElement
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfReadingInformationUIElementVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITfUIElementVtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITfUIElement *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITfUIElement *);
    ULONG (STDMETHODCALLTYPE *Release)(ITfUIElement *);
    HRESULT (STDMETHODCALLTYPE *GetDescription)(ITfUIElement *, BSTR *);
    HRESULT (STDMETHODCALLTYPE *GetGUID)(ITfUIElement *, GUID *);
    HRESULT (STDMETHODCALLTYPE *Show)(ITfUIElement *, BOOL);
    HRESULT (STDMETHODCALLTYPE *IsShown)(ITfUIElement *, BOOL *);
} ITfUIElementVtbl;

ರಚನೆ ITfUIElement
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITfUIElementVtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *);
    HRESULT (STDMETHODCALLTYPE *OnActivated)(ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink *, DWORD, LANGID, REFCLSID, REFGUID, REFGUID, HKL, DWORD);

} ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink_Vtbl;

ರಚನೆ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITf_ಒಳಹರಿವು_Processor_Profile_Activation_Sink_Vtbl *lpVtbl;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ITf_ಮೂಲ_Vtbl
{
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(ITf_ಮೂಲ *, REFIID, ಶೂನ್ಯ **);
    ULONG (STDMETHODCALLTYPE *ಕೂಡಿಸು_Ref)(ITf_ಮೂಲ *);
    ULONG (STDMETHODCALLTYPE *Release)(ITf_ಮೂಲ *);
    HRESULT (STDMETHODCALLTYPE *AdviseSink)(ITf_ಮೂಲ *, REFIID, IUnknown *, DWORD *);
    HRESULT (STDMETHODCALLTYPE *UnadviseSink)(ITf_ಮೂಲ *, DWORD);
} ITf_ಮೂಲ_Vtbl;

ರಚನೆ ITf_ಮೂಲ
{
    ಸ್ಥಿರಾಂಕ ರಚನೆ ITf_ಮೂಲ_Vtbl *lpVtbl;
};

/* *INDENT-ON* */ // clang-format on

#ಆದರೆ_ಅಂತ್ಯ // SDL_msctf_h_

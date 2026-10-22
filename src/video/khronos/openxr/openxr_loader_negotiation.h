#अगर_अघोषित OPENXR_LOADER_NEGOTIATION_H_
#घोषणा OPENXR_LOADER_NEGOTIATION_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#समावेश "openxr.h"

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#घोषणा XR_LOADER_VERSION_1_0 1

#घोषणा XR_CURRENT_LOADER_API_LAYER_VERSION 1


#घोषणा XR_CURRENT_LOADER_RUNTIME_VERSION 1


#घोषणा XR_LOADER_INFO_STRUCT_VERSION 1


#घोषणा XR_API_LAYER_INFO_STRUCT_VERSION 1


#घोषणा XR_RUNTIME_INFO_STRUCT_VERSION 1


#घोषणा XR_API_LAYER_अग्र_INFO_STRUCT_VERSION 1


#घोषणा XR_API_LAYER_CREATE_INFO_STRUCT_VERSION 1


#घोषणा XR_API_LAYER_MAX_SETTINGS_PATH_आकार 512


प्रकार क्रमागत XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_अग्र_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, स्थिर अक्षर* name, PFN_xrVoidFunction* function);

प्रकार काष्ठा XrApiLayerCreateInfo XrApiLayerCreateInfo;
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            स्थिर XrInstanceCreateInfo* info,
            स्थिर XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

प्रकार काष्ठा Xr_Api_Layer_अग्र_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    माप_प्रकार                          struct_आकार;
    अक्षर                            layerName[XR_MAX_API_LAYER_NAME_आकार];
    PFN_xrGetInstanceProcAddr       अग्र_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    अग्र_Create_Api_Layer_Instance;
    काष्ठा Xr_Api_Layer_अग्र_Info*      अग्र;
} Xr_Api_Layer_अग्र_Info;

प्रकार काष्ठा XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    माप_प्रकार                      struct_आकार;
    व्योम* XR_MAY_ALIAS          loaderInstance;
    अक्षर                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_आकार];
    Xr_Api_Layer_अग्र_Info*         अग्र_Info;
} XrApiLayerCreateInfo;

प्रकार काष्ठा XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    माप_प्रकार                          struct_आकार;
    uint32_t                        layerInterfaceVersion;
    XrVersion                       layerApiVersion;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

प्रकार काष्ठा XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    माप_प्रकार                      struct_आकार;
    uint32_t                    minInterfaceVersion;
    uint32_t                    maxInterfaceVersion;
    XrVersion                   minApiVersion;
    XrVersion                   maxApiVersion;
} XrNegotiateLoaderInfo;

प्रकार काष्ठा XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     structVersion;
    माप_प्रकार                       struct_आकार;
    uint32_t                     runtimeInterfaceVersion;
    XrVersion                    runtimeApiVersion;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(स्थिर XrInstanceCreateInfo* info, स्थिर XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(स्थिर XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
प्रकार Xr_परिणाम (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(स्थिर XrNegotiateLoaderInfo* loaderInfo, स्थिर अक्षर* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#अगर_अघोषित XR_NO_PROTOTYPES
#अगर_घोषित XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateApiLayerInstance(
    स्थिर XrInstanceCreateInfo*                 info,
    स्थिर XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    स्थिर XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    स्थिर XrNegotiateLoaderInfo*                loaderInfo,
    स्थिर अक्षर*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#पूर्ण_अगर /* XR_EXTENSION_PROTOTYPES */
#पूर्ण_अगर /* !XR_NO_PROTOTYPES */

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

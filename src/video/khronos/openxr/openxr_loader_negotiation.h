#ifndef OPENXR_LOADER_NEGOTIATION_H_
#define OPENXR_LOADER_NEGOTIATION_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#अन्तर्भाव "openxr.h"

#ifdef __cplusplus
बाह्य "C" {
#endif



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#define XR_LOADER_VERSION_1_0 1

#define XR_CURRENT_LOADER_API_LAYER_VERSION 1


#define XR_CURRENT_LOADER_RUNTIME_VERSION 1


#define XR_LOADER_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_INFO_STRUCT_VERSION 1


#define XR_RUNTIME_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_NEXT_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_CREATE_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_MAX_SETTINGS_PATH_SIZE 512


प्रकारव्याख्या गणना XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
प्रकारव्याख्या XrResult (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, स्थिरांक अक्षर* name, PFN_xrVoidFunction* function);

प्रकारव्याख्या संरचना XrApiLayerCreateInfo XrApiLayerCreateInfo;
प्रकारव्याख्या XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            स्थिरांक XrInstanceCreateInfo* info,
            स्थिरांक XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

प्रकारव्याख्या संरचना XrApiLayerNextInfo {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    माप_प्रकार                          structSize;
    अक्षर                            layerName[XR_MAX_API_LAYER_NAME_SIZE];
    PFN_xrGetInstanceProcAddr       nextGetInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    nextCreateApiLayerInstance;
    संरचना XrApiLayerNextInfo*      next;
} XrApiLayerNextInfo;

प्रकारव्याख्या संरचना XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    माप_प्रकार                      structSize;
    शून्य* XR_MAY_ALIAS          loaderInstance;
    अक्षर                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_SIZE];
    XrApiLayerNextInfo*         nextInfo;
} XrApiLayerCreateInfo;

प्रकारव्याख्या संरचना XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    माप_प्रकार                          structSize;
    uint32_t                        layerInterfaceVersion;
    XrVersion                       layerApiVersion;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

प्रकारव्याख्या संरचना XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    माप_प्रकार                      structSize;
    uint32_t                    minInterfaceVersion;
    uint32_t                    maxInterfaceVersion;
    XrVersion                   minApiVersion;
    XrVersion                   maxApiVersion;
} XrNegotiateLoaderInfo;

प्रकारव्याख्या संरचना XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     structVersion;
    माप_प्रकार                       structSize;
    uint32_t                     runtimeInterfaceVersion;
    XrVersion                    runtimeApiVersion;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

प्रकारव्याख्या XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(स्थिरांक XrInstanceCreateInfo* info, स्थिरांक XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
प्रकारव्याख्या XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(स्थिरांक XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
प्रकारव्याख्या XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(स्थिरांक XrNegotiateLoaderInfo* loaderInfo, स्थिरांक अक्षर* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateApiLayerInstance(
    स्थिरांक XrInstanceCreateInfo*                 info,
    स्थिरांक XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    स्थिरांक XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    स्थिरांक XrNegotiateLoaderInfo*                loaderInfo,
    स्थिरांक अक्षर*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */

#ifdef __cplusplus
}
#endif

#endif

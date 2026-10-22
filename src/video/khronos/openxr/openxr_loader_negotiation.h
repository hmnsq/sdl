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

#ಅನ್ತರ್ಭಾವ "openxr.h"

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
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


ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
ಪ್ರಕಾರನಿರ್ದೇಶ XrResult (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ಧ್ರುವ ವರ್ಣ* name, PFN_xrVoidFunction* function);

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XrApiLayerCreateInfo XrApiLayerCreateInfo;
ಪ್ರಕಾರನಿರ್ದೇಶ XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ಧ್ರುವ XrInstanceCreateInfo* info,
            ಧ್ರುವ XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XrApiLayerNextInfo {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          structSize;
    ವರ್ಣ                            layerName[XR_MAX_API_LAYER_NAME_SIZE];
    PFN_xrGetInstanceProcAddr       nextGetInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    nextCreateApiLayerInstance;
    ಸಂರಚನಾ XrApiLayerNextInfo*      next;
} XrApiLayerNextInfo;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      structSize;
    ಶೂನ್ಯ* XR_MAY_ALIAS          loaderInstance;
    ವರ್ಣ                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_SIZE];
    XrApiLayerNextInfo*         nextInfo;
} XrApiLayerCreateInfo;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          structSize;
    uint32_t                        layerInterfaceVersion;
    XrVersion                       layerApiVersion;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      structSize;
    uint32_t                    minInterfaceVersion;
    uint32_t                    maxInterfaceVersion;
    XrVersion                   minApiVersion;
    XrVersion                   maxApiVersion;
} XrNegotiateLoaderInfo;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     structVersion;
    size_t                       structSize;
    uint32_t                     runtimeInterfaceVersion;
    XrVersion                    runtimeApiVersion;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

ಪ್ರಕಾರನಿರ್ದೇಶ XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ಧ್ರುವ XrInstanceCreateInfo* info, ಧ್ರುವ XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
ಪ್ರಕಾರನಿರ್ದೇಶ XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ಧ್ರುವ XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
ಪ್ರಕಾರನಿರ್ದೇಶ XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ಧ್ರುವ XrNegotiateLoaderInfo* loaderInfo, ಧ್ರುವ ವರ್ಣ* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateApiLayerInstance(
    ಧ್ರುವ XrInstanceCreateInfo*                 info,
    ಧ್ರುವ XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ಧ್ರುವ XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ಧ್ರುವ XrNegotiateLoaderInfo*                loaderInfo,
    ಧ್ರುವ ವರ್ಣ*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */

#ifdef __cplusplus
}
#endif

#endif

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

#অন্তর্ভাৱ "openxr.h"

#ifdef __cplusplus
বাহ্য "C" {
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


প্রকারনির্দেশ গণনা XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
প্রকারনির্দেশ XrResult (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ধ্রুৱ ৱর্ণ* name, PFN_xrVoidFunction* function);

প্রকারনির্দেশ সংরচনা XrApiLayerCreateInfo XrApiLayerCreateInfo;
প্রকারনির্দেশ XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ধ্রুৱ XrInstanceCreateInfo* info,
            ধ্রুৱ XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

প্রকারনির্দেশ সংরচনা XrApiLayerNextInfo {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          structSize;
    ৱর্ণ                            layerName[XR_MAX_API_LAYER_NAME_SIZE];
    PFN_xrGetInstanceProcAddr       nextGetInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    nextCreateApiLayerInstance;
    সংরচনা XrApiLayerNextInfo*      next;
} XrApiLayerNextInfo;

প্রকারনির্দেশ সংরচনা XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      structSize;
    শূন্য* XR_MAY_ALIAS          loaderInstance;
    ৱর্ণ                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_SIZE];
    XrApiLayerNextInfo*         nextInfo;
} XrApiLayerCreateInfo;

প্রকারনির্দেশ সংরচনা XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          structSize;
    uint32_t                        layerInterfaceVersion;
    XrVersion                       layerApiVersion;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

প্রকারনির্দেশ সংরচনা XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      structSize;
    uint32_t                    minInterfaceVersion;
    uint32_t                    maxInterfaceVersion;
    XrVersion                   minApiVersion;
    XrVersion                   maxApiVersion;
} XrNegotiateLoaderInfo;

প্রকারনির্দেশ সংরচনা XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     structVersion;
    size_t                       structSize;
    uint32_t                     runtimeInterfaceVersion;
    XrVersion                    runtimeApiVersion;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

প্রকারনির্দেশ XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ধ্রুৱ XrInstanceCreateInfo* info, ধ্রুৱ XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
প্রকারনির্দেশ XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ধ্রুৱ XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
প্রকারনির্দেশ XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ধ্রুৱ XrNegotiateLoaderInfo* loaderInfo, ধ্রুৱ ৱর্ণ* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateApiLayerInstance(
    ধ্রুৱ XrInstanceCreateInfo*                 info,
    ধ্রুৱ XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ধ্রুৱ XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ধ্রুৱ XrNegotiateLoaderInfo*                loaderInfo,
    ধ্রুৱ ৱর্ণ*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */

#ifdef __cplusplus
}
#endif

#endif

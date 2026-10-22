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

#அந்தர்பாவ "openxr.h"

#ifdef __cplusplus
வெளி "C" {
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


வகைவரை எண்ணிக்கை XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
வகைவரை XrResult (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, மாறிலி எழுத்து* name, PFN_xrVoidFunction* function);

வகைவரை கட்டமைப்பு XrApiLayerCreateInfo XrApiLayerCreateInfo;
வகைவரை XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            மாறிலி XrInstanceCreateInfo* info,
            மாறிலி XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

வகைவரை கட்டமைப்பு XrApiLayerNextInfo {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          structSize;
    எழுத்து                            layerName[XR_MAX_API_LAYER_NAME_SIZE];
    PFN_xrGetInstanceProcAddr       nextGetInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    nextCreateApiLayerInstance;
    கட்டமைப்பு XrApiLayerNextInfo*      next;
} XrApiLayerNextInfo;

வகைவரை கட்டமைப்பு XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      structSize;
    வெறுமை* XR_MAY_ALIAS          loaderInstance;
    எழுத்து                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_SIZE];
    XrApiLayerNextInfo*         nextInfo;
} XrApiLayerCreateInfo;

வகைவரை கட்டமைப்பு XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          structSize;
    uint32_t                        layerInterfaceVersion;
    XrVersion                       layerApiVersion;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

வகைவரை கட்டமைப்பு XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      structSize;
    uint32_t                    minInterfaceVersion;
    uint32_t                    maxInterfaceVersion;
    XrVersion                   minApiVersion;
    XrVersion                   maxApiVersion;
} XrNegotiateLoaderInfo;

வகைவரை கட்டமைப்பு XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     structVersion;
    size_t                       structSize;
    uint32_t                     runtimeInterfaceVersion;
    XrVersion                    runtimeApiVersion;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

வகைவரை XrResult (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(மாறிலி XrInstanceCreateInfo* info, மாறிலி XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
வகைவரை XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(மாறிலி XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
வகைவரை XrResult (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(மாறிலி XrNegotiateLoaderInfo* loaderInfo, மாறிலி எழுத்து* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR XrResult XRAPI_CALL xrCreateApiLayerInstance(
    மாறிலி XrInstanceCreateInfo*                 info,
    மாறிலி XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    மாறிலி XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    மாறிலி XrNegotiateLoaderInfo*                loaderInfo,
    மாறிலி எழுத்து*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */

#ifdef __cplusplus
}
#endif

#endif

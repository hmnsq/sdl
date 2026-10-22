#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ OPENXR_LOADER_NEGOTIATION_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPENXR_LOADER_NEGOTIATION_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "openxr.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LOADER_ਸੰਸਕਰਣ_1_0 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_CURRENT_LOADER_API_LAYER_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_CURRENT_LOADER_RUNTIME_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_LOADER_INFO_STRUCT_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_API_LAYER_INFO_STRUCT_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_RUNTIME_INFO_STRUCT_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_API_LAYER_ਅਗਲਾ_INFO_STRUCT_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_API_LAYER_CREATE_INFO_STRUCT_ਸੰਸਕਰਣ 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XR_API_LAYER_MAX_SETTINGS_ਰਸਤਾ_ਮਾਪ 512


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_ਅਗਲਾ_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ਅਚਲ ਅੱਖਰ* name, PFN_xrVoidFunction* function);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrApiLayerCreateInfo XrApiLayerCreateInfo;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ਅਚਲ XrInstanceCreateInfo* info,
            ਅਚਲ XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Xr_Api_Layer_ਅਗਲਾ_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_ਸੰਸਕਰਣ;
    size_t                          struct_ਮਾਪ;
    ਅੱਖਰ                            layerName[XR_MAX_API_LAYER_NAME_ਮਾਪ];
    PFN_xrGetInstanceProcAddr       ਅਗਲਾ_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    ਅਗਲਾ_Create_Api_Layer_Instance;
    ਬਣਤਰ Xr_Api_Layer_ਅਗਲਾ_Info*      ਅਗਲਾ;
} Xr_Api_Layer_ਅਗਲਾ_Info;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_ਸੰਸਕਰਣ;
    size_t                      struct_ਮਾਪ;
    ਖਾਲੀ* XR_MAY_ALIAS          loaderInstance;
    ਅੱਖਰ                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_ਰਸਤਾ_ਮਾਪ];
    Xr_Api_Layer_ਅਗਲਾ_Info*         ਅਗਲਾ_Info;
} XrApiLayerCreateInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_ਸੰਸਕਰਣ;
    size_t                          struct_ਮਾਪ;
    uint32_t                        layer_Interface_ਸੰਸਕਰਣ;
    Xr_ਸੰਸਕਰਣ                       layer_Api_ਸੰਸਕਰਣ;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_ਸੰਸਕਰਣ;
    size_t                      struct_ਮਾਪ;
    uint32_t                    min_Interface_ਸੰਸਕਰਣ;
    uint32_t                    max_Interface_ਸੰਸਕਰਣ;
    Xr_ਸੰਸਕਰਣ                   min_Api_ਸੰਸਕਰਣ;
    Xr_ਸੰਸਕਰਣ                   max_Api_ਸੰਸਕਰਣ;
} XrNegotiateLoaderInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_ਸੰਸਕਰਣ;
    size_t                       struct_ਮਾਪ;
    uint32_t                     runtime_Interface_ਸੰਸਕਰਣ;
    Xr_ਸੰਸਕਰਣ                    runtime_Api_ਸੰਸਕਰਣ;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ਅਚਲ XrInstanceCreateInfo* info, ਅਚਲ XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ਅਚਲ XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Xr_ਨਤੀਜਾ (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ਅਚਲ XrNegotiateLoaderInfo* loaderInfo, ਅਚਲ ਅੱਖਰ* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ XR_NO_PROTOTYPES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrCreateApiLayerInstance(
    ਅਚਲ XrInstanceCreateInfo*                 info,
    ਅਚਲ XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ਅਚਲ XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_ਨਤੀਜਾ XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ਅਚਲ XrNegotiateLoaderInfo*                loaderInfo,
    ਅਚਲ ਅੱਖਰ*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#ਜੇ_ਅੰਤ /* XR_EXTENSION_PROTOTYPES */
#ਜੇ_ਅੰਤ /* !XR_NO_PROTOTYPES */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ

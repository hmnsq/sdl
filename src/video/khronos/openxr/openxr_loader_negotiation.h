#جيڪڏهن_وصف_نه_ٿيل OPENXR_LOADER_NEGOTIATION_H_
#وصف_ڪريو OPENXR_LOADER_NEGOTIATION_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#ضمن "openxr.h"

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو XR_LOADER_نسخو_1_0 1

#وصف_ڪريو XR_CURRENT_LOADER_API_LAYER_نسخو 1


#وصف_ڪريو XR_CURRENT_LOADER_RUNTIME_نسخو 1


#وصف_ڪريو XR_LOADER_INFO_STRUCT_نسخو 1


#وصف_ڪريو XR_API_LAYER_INFO_STRUCT_نسخو 1


#وصف_ڪريو XR_RUNTIME_INFO_STRUCT_نسخو 1


#وصف_ڪريو XR_API_LAYER_ايندڙ_INFO_STRUCT_نسخو 1


#وصف_ڪريو XR_API_LAYER_CREATE_INFO_STRUCT_نسخو 1


#وصف_ڪريو XR_API_LAYER_MAX_SETTINGS_رستو_سائيز 512


تعريفنوع تعداد XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_ايندڙ_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ثابت حرف* name, PFN_xrVoidFunction* function);

تعريفنوع بنية XrApiLayerCreateInfo XrApiLayerCreateInfo;
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ثابت XrInstanceCreateInfo* info,
            ثابت XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

تعريفنوع بنية Xr_Api_Layer_ايندڙ_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_نسخو;
    size_t                          struct_سائيز;
    حرف                            layerName[XR_MAX_API_LAYER_NAME_سائيز];
    PFN_xrGetInstanceProcAddr       ايندڙ_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    ايندڙ_Create_Api_Layer_Instance;
    بنية Xr_Api_Layer_ايندڙ_Info*      ايندڙ;
} Xr_Api_Layer_ايندڙ_Info;

تعريفنوع بنية XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_نسخو;
    size_t                      struct_سائيز;
    فراغ* XR_MAY_ALIAS          loaderInstance;
    حرف                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_رستو_سائيز];
    Xr_Api_Layer_ايندڙ_Info*         ايندڙ_Info;
} XrApiLayerCreateInfo;

تعريفنوع بنية XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_نسخو;
    size_t                          struct_سائيز;
    uint32_t                        layer_Interface_نسخو;
    Xr_نسخو                       layer_Api_نسخو;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

تعريفنوع بنية XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_نسخو;
    size_t                      struct_سائيز;
    uint32_t                    min_Interface_نسخو;
    uint32_t                    max_Interface_نسخو;
    Xr_نسخو                   min_Api_نسخو;
    Xr_نسخو                   max_Api_نسخو;
} XrNegotiateLoaderInfo;

تعريفنوع بنية XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_نسخو;
    size_t                       struct_سائيز;
    uint32_t                     runtime_Interface_نسخو;
    Xr_نسخو                    runtime_Api_نسخو;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ثابت XrInstanceCreateInfo* info, ثابت XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ثابت XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
تعريفنوع Xr_نتيجو (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ثابت XrNegotiateLoaderInfo* loaderInfo, ثابت حرف* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#جيڪڏهن_وصف_نه_ٿيل XR_NO_PROTOTYPES
#جيڪڏهن_وصف_ٿيل XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrCreateApiLayerInstance(
    ثابت XrInstanceCreateInfo*                 info,
    ثابت XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ثابت XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_نتيجو XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ثابت XrNegotiateLoaderInfo*                loaderInfo,
    ثابت حرف*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#جيڪڏهن_پورو /* XR_EXTENSION_PROTOTYPES */
#جيڪڏهن_پورو /* !XR_NO_PROTOTYPES */

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو

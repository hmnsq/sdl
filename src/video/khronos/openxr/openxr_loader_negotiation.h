#اگر_تعریف_نشده OPENXR_LOADER_NEGOTIATION_H_
#تعریف_کن OPENXR_LOADER_NEGOTIATION_H_ 1

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

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن XR_LOADER_نسخه_1_0 1

#تعریف_کن XR_CURRENT_LOADER_API_LAYER_نسخه 1


#تعریف_کن XR_CURRENT_LOADER_RUNTIME_نسخه 1


#تعریف_کن XR_LOADER_INFO_STRUCT_نسخه 1


#تعریف_کن XR_API_LAYER_INFO_STRUCT_نسخه 1


#تعریف_کن XR_RUNTIME_INFO_STRUCT_نسخه 1


#تعریف_کن XR_API_LAYER_بعدی_INFO_STRUCT_نسخه 1


#تعریف_کن XR_API_LAYER_CREATE_INFO_STRUCT_نسخه 1


#تعریف_کن XR_API_LAYER_MAX_SETTINGS_مسیر_اندازه 512


تعريفنوع تعداد XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_بعدی_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
تعريفنوع Xr_نتیجه (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ثابت حرف* name, PFN_xrVoidFunction* function);

تعريفنوع بنية XrApiLayerCreateInfo XrApiLayerCreateInfo;
تعريفنوع Xr_نتیجه (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ثابت XrInstanceCreateInfo* info,
            ثابت XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

تعريفنوع بنية Xr_Api_Layer_بعدی_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_نسخه;
    size_t                          struct_اندازه;
    حرف                            layerName[XR_MAX_API_LAYER_NAME_اندازه];
    PFN_xrGetInstanceProcAddr       بعدی_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    بعدی_Create_Api_Layer_Instance;
    بنية Xr_Api_Layer_بعدی_Info*      بعدی;
} Xr_Api_Layer_بعدی_Info;

تعريفنوع بنية XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_نسخه;
    size_t                      struct_اندازه;
    فراغ* XR_MAY_ALIAS          loaderInstance;
    حرف                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_مسیر_اندازه];
    Xr_Api_Layer_بعدی_Info*         بعدی_Info;
} XrApiLayerCreateInfo;

تعريفنوع بنية XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_نسخه;
    size_t                          struct_اندازه;
    uint32_t                        layer_Interface_نسخه;
    Xr_نسخه                       layer_Api_نسخه;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

تعريفنوع بنية XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_نسخه;
    size_t                      struct_اندازه;
    uint32_t                    min_Interface_نسخه;
    uint32_t                    max_Interface_نسخه;
    Xr_نسخه                   min_Api_نسخه;
    Xr_نسخه                   max_Api_نسخه;
} XrNegotiateLoaderInfo;

تعريفنوع بنية XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_نسخه;
    size_t                       struct_اندازه;
    uint32_t                     runtime_Interface_نسخه;
    Xr_نسخه                    runtime_Api_نسخه;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

تعريفنوع Xr_نتیجه (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ثابت XrInstanceCreateInfo* info, ثابت XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
تعريفنوع Xr_نتیجه (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ثابت XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
تعريفنوع Xr_نتیجه (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ثابت XrNegotiateLoaderInfo* loaderInfo, ثابت حرف* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#اگر_تعریف_نشده XR_NO_PROTOTYPES
#اگر_تعریف_شده XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجه XRAPI_CALL xrCreateApiLayerInstance(
    ثابت XrInstanceCreateInfo*                 info,
    ثابت XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_نتیجه XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ثابت XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_نتیجه XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ثابت XrNegotiateLoaderInfo*                loaderInfo,
    ثابت حرف*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#پایان_اگر /* XR_EXTENSION_PROTOTYPES */
#پایان_اگر /* !XR_NO_PROTOTYPES */

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر

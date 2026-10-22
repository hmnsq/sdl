#جے_بنا_تعریف OPENXR_LOADER_NEGOTIATION_H_
#تعریف_کرو OPENXR_LOADER_NEGOTIATION_H_ 1

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

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو XR_LOADER_نسخہ_1_0 1

#تعریف_کرو XR_CURRENT_LOADER_API_LAYER_نسخہ 1


#تعریف_کرو XR_CURRENT_LOADER_RUNTIME_نسخہ 1


#تعریف_کرو XR_LOADER_INFO_STRUCT_نسخہ 1


#تعریف_کرو XR_API_LAYER_INFO_STRUCT_نسخہ 1


#تعریف_کرو XR_RUNTIME_INFO_STRUCT_نسخہ 1


#تعریف_کرو XR_API_LAYER_اگلا_INFO_STRUCT_نسخہ 1


#تعریف_کرو XR_API_LAYER_CREATE_INFO_STRUCT_نسخہ 1


#تعریف_کرو XR_API_LAYER_MAX_SETTINGS_رستہ_ناپ 512


تعريفنوع تعداد XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_اگلا_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ثابت حرف* name, PFN_xrVoidFunction* function);

تعريفنوع بنية XrApiLayerCreateInfo XrApiLayerCreateInfo;
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ثابت XrInstanceCreateInfo* info,
            ثابت XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

تعريفنوع بنية Xr_Api_Layer_اگلا_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_نسخہ;
    size_t                          struct_ناپ;
    حرف                            layerName[XR_MAX_API_LAYER_NAME_ناپ];
    PFN_xrGetInstanceProcAddr       اگلا_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    اگلا_Create_Api_Layer_Instance;
    بنية Xr_Api_Layer_اگلا_Info*      اگلا;
} Xr_Api_Layer_اگلا_Info;

تعريفنوع بنية XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_نسخہ;
    size_t                      struct_ناپ;
    فراغ* XR_MAY_ALIAS          loaderInstance;
    حرف                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_رستہ_ناپ];
    Xr_Api_Layer_اگلا_Info*         اگلا_Info;
} XrApiLayerCreateInfo;

تعريفنوع بنية XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_نسخہ;
    size_t                          struct_ناپ;
    uint32_t                        layer_Interface_نسخہ;
    Xr_نسخہ                       layer_Api_نسخہ;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

تعريفنوع بنية XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_نسخہ;
    size_t                      struct_ناپ;
    uint32_t                    min_Interface_نسخہ;
    uint32_t                    max_Interface_نسخہ;
    Xr_نسخہ                   min_Api_نسخہ;
    Xr_نسخہ                   max_Api_نسخہ;
} XrNegotiateLoaderInfo;

تعريفنوع بنية XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_نسخہ;
    size_t                       struct_ناپ;
    uint32_t                     runtime_Interface_نسخہ;
    Xr_نسخہ                    runtime_Api_نسخہ;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ثابت XrInstanceCreateInfo* info, ثابت XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ثابت XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
تعريفنوع Xr_نتیجہ (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ثابت XrNegotiateLoaderInfo* loaderInfo, ثابت حرف* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#جے_بنا_تعریف XR_NO_PROTOTYPES
#جے_تعریف_شدہ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrCreateApiLayerInstance(
    ثابت XrInstanceCreateInfo*                 info,
    ثابت XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ثابت XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_نتیجہ XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ثابت XrNegotiateLoaderInfo*                loaderInfo,
    ثابت حرف*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#جے_انت /* XR_EXTENSION_PROTOTYPES */
#جے_انت /* !XR_NO_PROTOTYPES */

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت

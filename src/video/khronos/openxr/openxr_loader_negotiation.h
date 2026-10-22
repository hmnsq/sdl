#यदि_अपरिभाषितम् OPENXR_LOADER_NEGOTIATION_H_
#परिभाषय OPENXR_LOADER_NEGOTIATION_H_ 1

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

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#परिभाषय XR_LOADER_संस्करणम्_1_0 1

#परिभाषय XR_CURRENT_LOADER_API_LAYER_संस्करणम् 1


#परिभाषय XR_CURRENT_LOADER_RUNTIME_संस्करणम् 1


#परिभाषय XR_LOADER_INFO_STRUCT_संस्करणम् 1


#परिभाषय XR_API_LAYER_INFO_STRUCT_संस्करणम् 1


#परिभाषय XR_RUNTIME_INFO_STRUCT_संस्करणम् 1


#परिभाषय XR_API_LAYER_अग्र_INFO_STRUCT_संस्करणम् 1


#परिभाषय XR_API_LAYER_CREATE_INFO_STRUCT_संस्करणम् 1


#परिभाषय XR_API_LAYER_MAX_SETTINGS_मार्गः_आकार 512


प्रकारनिर्देश गणना XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_अग्र_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ध्रुव वर्ण* name, PFN_xrVoidFunction* function);

प्रकारनिर्देश संरचना XrApiLayerCreateInfo XrApiLayerCreateInfo;
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ध्रुव XrInstanceCreateInfo* info,
            ध्रुव XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

प्रकारनिर्देश संरचना Xr_Api_Layer_अग्र_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_संस्करणम्;
    size_t                          struct_आकार;
    वर्ण                            layerName[XR_MAX_API_LAYER_NAME_आकार];
    PFN_xrGetInstanceProcAddr       अग्र_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    अग्र_Create_Api_Layer_Instance;
    संरचना Xr_Api_Layer_अग्र_Info*      अग्र;
} Xr_Api_Layer_अग्र_Info;

प्रकारनिर्देश संरचना XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_संस्करणम्;
    size_t                      struct_आकार;
    शून्य* XR_MAY_ALIAS          loaderInstance;
    वर्ण                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_मार्गः_आकार];
    Xr_Api_Layer_अग्र_Info*         अग्र_Info;
} XrApiLayerCreateInfo;

प्रकारनिर्देश संरचना XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_संस्करणम्;
    size_t                          struct_आकार;
    uint32_t                        layer_Interface_संस्करणम्;
    Xr_संस्करणम्                       layer_Api_संस्करणम्;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

प्रकारनिर्देश संरचना XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_संस्करणम्;
    size_t                      struct_आकार;
    uint32_t                    min_Interface_संस्करणम्;
    uint32_t                    max_Interface_संस्करणम्;
    Xr_संस्करणम्                   min_Api_संस्करणम्;
    Xr_संस्करणम्                   max_Api_संस्करणम्;
} XrNegotiateLoaderInfo;

प्रकारनिर्देश संरचना XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_संस्करणम्;
    size_t                       struct_आकार;
    uint32_t                     runtime_Interface_संस्करणम्;
    Xr_संस्करणम्                    runtime_Api_संस्करणम्;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ध्रुव XrInstanceCreateInfo* info, ध्रुव XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ध्रुव XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
प्रकारनिर्देश Xr_परिणाम (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ध्रुव XrNegotiateLoaderInfo* loaderInfo, ध्रुव वर्ण* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#यदि_अपरिभाषितम् XR_NO_PROTOTYPES
#यदि_परिभाषितम् XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrCreateApiLayerInstance(
    ध्रुव XrInstanceCreateInfo*                 info,
    ध्रुव XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ध्रुव XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_परिणाम XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ध्रुव XrNegotiateLoaderInfo*                loaderInfo,
    ध्रुव वर्ण*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#यदि_अन्तः /* XR_EXTENSION_PROTOTYPES */
#यदि_अन्तः /* !XR_NO_PROTOTYPES */

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः

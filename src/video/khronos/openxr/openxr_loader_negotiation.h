#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ OPENXR_LOADER_NEGOTIATION_H_
#ವ್ಯಾಖ್ಯಾನಿಸು OPENXR_LOADER_NEGOTIATION_H_ 1

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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು XR_LOADER_ಆವೃತ್ತಿ_1_0 1

#ವ್ಯಾಖ್ಯಾನಿಸು XR_CURRENT_LOADER_API_LAYER_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_CURRENT_LOADER_RUNTIME_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_LOADER_INFO_STRUCT_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_API_LAYER_INFO_STRUCT_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_RUNTIME_INFO_STRUCT_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_API_LAYER_ಮುಂದಿನ_INFO_STRUCT_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_API_LAYER_CREATE_INFO_STRUCT_ಆವೃತ್ತಿ 1


#ವ್ಯಾಖ್ಯಾನಿಸು XR_API_LAYER_MAX_SETTINGS_ಮಾರ್ಗ_ಗಾತ್ರ 512


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_ಮುಂದಿನ_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* name, PFN_xrVoidFunction* function);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrApiLayerCreateInfo XrApiLayerCreateInfo;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ಸ್ಥಿರಾಂಕ XrInstanceCreateInfo* info,
            ಸ್ಥಿರಾಂಕ XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Xr_Api_Layer_ಮುಂದಿನ_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_ಆವೃತ್ತಿ;
    size_t                          struct_ಗಾತ್ರ;
    ಅಕ್ಷರ                            layerName[XR_MAX_API_LAYER_NAME_ಗಾತ್ರ];
    PFN_xrGetInstanceProcAddr       ಮುಂದಿನ_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    ಮುಂದಿನ_Create_Api_Layer_Instance;
    ರಚನೆ Xr_Api_Layer_ಮುಂದಿನ_Info*      ಮುಂದಿನ;
} Xr_Api_Layer_ಮುಂದಿನ_Info;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_ಆವೃತ್ತಿ;
    size_t                      struct_ಗಾತ್ರ;
    ಶೂನ್ಯ* XR_MAY_ALIAS          loaderInstance;
    ಅಕ್ಷರ                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_ಮಾರ್ಗ_ಗಾತ್ರ];
    Xr_Api_Layer_ಮುಂದಿನ_Info*         ಮುಂದಿನ_Info;
} XrApiLayerCreateInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_ಆವೃತ್ತಿ;
    size_t                          struct_ಗಾತ್ರ;
    uint32_t                        layer_Interface_ಆವೃತ್ತಿ;
    Xr_ಆವೃತ್ತಿ                       layer_Api_ಆವೃತ್ತಿ;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_ಆವೃತ್ತಿ;
    size_t                      struct_ಗಾತ್ರ;
    uint32_t                    min_Interface_ಆವೃತ್ತಿ;
    uint32_t                    max_Interface_ಆವೃತ್ತಿ;
    Xr_ಆವೃತ್ತಿ                   min_Api_ಆವೃತ್ತಿ;
    Xr_ಆವೃತ್ತಿ                   max_Api_ಆವೃತ್ತಿ;
} XrNegotiateLoaderInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_ಆವೃತ್ತಿ;
    size_t                       struct_ಗಾತ್ರ;
    uint32_t                     runtime_Interface_ಆವೃತ್ತಿ;
    Xr_ಆವೃತ್ತಿ                    runtime_Api_ಆವೃತ್ತಿ;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ಸ್ಥಿರಾಂಕ XrInstanceCreateInfo* info, ಸ್ಥಿರಾಂಕ XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ಸ್ಥಿರಾಂಕ XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Xr_ಫಲಿತಾಂಶ (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ಸ್ಥಿರಾಂಕ XrNegotiateLoaderInfo* loaderInfo, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ XR_NO_PROTOTYPES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrCreateApiLayerInstance(
    ಸ್ಥಿರಾಂಕ XrInstanceCreateInfo*                 info,
    ಸ್ಥಿರಾಂಕ XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ಸ್ಥಿರಾಂಕ XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_ಫಲಿತಾಂಶ XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ಸ್ಥಿರಾಂಕ XrNegotiateLoaderInfo*                loaderInfo,
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#ಆದರೆ_ಅಂತ್ಯ /* XR_EXTENSION_PROTOTYPES */
#ಆದರೆ_ಅಂತ್ಯ /* !XR_NO_PROTOTYPES */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

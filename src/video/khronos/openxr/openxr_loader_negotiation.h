#నిర్వచితం_కాకపోతే OPENXR_LOADER_NEGOTIATION_H_
#నిర్వచించు OPENXR_LOADER_NEGOTIATION_H_ 1

/*
** Copyright 2017-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#అన్తర్భావ "openxr.h"

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు XR_LOADER_సంస్కరణ_1_0 1

#నిర్వచించు XR_CURRENT_LOADER_API_LAYER_సంస్కరణ 1


#నిర్వచించు XR_CURRENT_LOADER_RUNTIME_సంస్కరణ 1


#నిర్వచించు XR_LOADER_INFO_STRUCT_సంస్కరణ 1


#నిర్వచించు XR_API_LAYER_INFO_STRUCT_సంస్కరణ 1


#నిర్వచించు XR_RUNTIME_INFO_STRUCT_సంస్కరణ 1


#నిర్వచించు XR_API_LAYER_తదుపరి_INFO_STRUCT_సంస్కరణ 1


#నిర్వచించు XR_API_LAYER_CREATE_INFO_STRUCT_సంస్కరణ 1


#నిర్వచించు XR_API_LAYER_MAX_SETTINGS_మార్గం_కొలత 512


రకనిర్వచనం గణన XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_తదుపరి_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, స్థిరరాశి అక్షరం* name, PFN_xrVoidFunction* function);

రకనిర్వచనం నిర్మాణం XrApiLayerCreateInfo XrApiLayerCreateInfo;
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            స్థిరరాశి XrInstanceCreateInfo* info,
            స్థిరరాశి XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

రకనిర్వచనం నిర్మాణం Xr_Api_Layer_తదుపరి_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_సంస్కరణ;
    size_t                          struct_కొలత;
    అక్షరం                            layerName[XR_MAX_API_LAYER_NAME_కొలత];
    PFN_xrGetInstanceProcAddr       తదుపరి_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    తదుపరి_Create_Api_Layer_Instance;
    నిర్మాణం Xr_Api_Layer_తదుపరి_Info*      తదుపరి;
} Xr_Api_Layer_తదుపరి_Info;

రకనిర్వచనం నిర్మాణం XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_సంస్కరణ;
    size_t                      struct_కొలత;
    శూన్య* XR_MAY_ALIAS          loaderInstance;
    అక్షరం                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_మార్గం_కొలత];
    Xr_Api_Layer_తదుపరి_Info*         తదుపరి_Info;
} XrApiLayerCreateInfo;

రకనిర్వచనం నిర్మాణం XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        struct_సంస్కరణ;
    size_t                          struct_కొలత;
    uint32_t                        layer_Interface_సంస్కరణ;
    Xr_సంస్కరణ                       layer_Api_సంస్కరణ;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

రకనిర్వచనం నిర్మాణం XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    struct_సంస్కరణ;
    size_t                      struct_కొలత;
    uint32_t                    min_Interface_సంస్కరణ;
    uint32_t                    max_Interface_సంస్కరణ;
    Xr_సంస్కరణ                   min_Api_సంస్కరణ;
    Xr_సంస్కరణ                   max_Api_సంస్కరణ;
} XrNegotiateLoaderInfo;

రకనిర్వచనం నిర్మాణం XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     struct_సంస్కరణ;
    size_t                       struct_కొలత;
    uint32_t                     runtime_Interface_సంస్కరణ;
    Xr_సంస్కరణ                    runtime_Api_సంస్కరణ;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(స్థిరరాశి XrInstanceCreateInfo* info, స్థిరరాశి XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(స్థిరరాశి XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
రకనిర్వచనం Xr_ఫలితం (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(స్థిరరాశి XrNegotiateLoaderInfo* loaderInfo, స్థిరరాశి అక్షరం* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#నిర్వచితం_కాకపోతే XR_NO_PROTOTYPES
#నిర్వచితమైతే XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrCreateApiLayerInstance(
    స్థిరరాశి XrInstanceCreateInfo*                 info,
    స్థిరరాశి XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    స్థిరరాశి XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_ఫలితం XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    స్థిరరాశి XrNegotiateLoaderInfo*                loaderInfo,
    స్థిరరాశి అక్షరం*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#అయితే_ముగింపు /* XR_EXTENSION_PROTOTYPES */
#అయితే_ముగింపు /* !XR_NO_PROTOTYPES */

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు

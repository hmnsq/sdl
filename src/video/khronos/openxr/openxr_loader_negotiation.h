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

#অন্তর্ভাব "openxr.h"

#ifdef __cplusplus
বাহ্যিক "C" {
#endif



// XR_LOADER_VERSION_1_0 is a preprocessor guard. Do not pass it to API calls.
#define XR_LOADER_VERSION_1_0 1

#define XR_CURRENT_LOADER_API_LAYER_VERSION 1


#define XR_CURRENT_LOADER_RUNTIME_VERSION 1


#define XR_LOADER_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_INFO_STRUCT_VERSION 1


#define XR_RUNTIME_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_পরবর্তী_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_CREATE_INFO_STRUCT_VERSION 1


#define XR_API_LAYER_MAX_SETTINGS_PATH_আকার 512


প্রকারলেখ গণনা XrLoaderInterfaceStructs {
    XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED = 0,
    XR_LOADER_INTERFACE_STRUCT_LOADER_INFO = 1,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST = 2,
    XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST = 3,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO = 4,
    XR_LOADER_INTERFACE_STRUCT_API_LAYER_পরবর্তী_INFO = 5,
    XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM = 0x7FFFFFFF
} XrLoaderInterfaceStructs;
প্রকারলেখ Xr_ফলাফল (XRAPI_PTR *PFN_xrGetInstanceProcAddr)(XrInstance instance, ধ্রুবক অক্ষর* name, PFN_xrVoidFunction* function);

প্রকারলেখ কাঠামো XrApiLayerCreateInfo XrApiLayerCreateInfo;
প্রকারলেখ Xr_ফলাফল (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(
            ধ্রুবক XrInstanceCreateInfo* info,
            ধ্রুবক XrApiLayerCreateInfo* apiLayerInfo,
            XrInstance* instance);

প্রকারলেখ কাঠামো Xr_Api_Layer_পরবর্তী_Info {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          struct_আকার;
    অক্ষর                            layerName[XR_MAX_API_LAYER_NAME_আকার];
    PFN_xrGetInstanceProcAddr       পরবর্তী_Get_Instance_Proc_Addr;
    PFN_xrCreateApiLayerInstance    পরবর্তী_Create_Api_Layer_Instance;
    কাঠামো Xr_Api_Layer_পরবর্তী_Info*      পরবর্তী;
} Xr_Api_Layer_পরবর্তী_Info;

প্রকারলেখ কাঠামো XrApiLayerCreateInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      struct_আকার;
    শূন্য* XR_MAY_ALIAS          loaderInstance;
    অক্ষর                        settings_file_location[XR_API_LAYER_MAX_SETTINGS_PATH_আকার];
    Xr_Api_Layer_পরবর্তী_Info*         পরবর্তী_Info;
} XrApiLayerCreateInfo;

প্রকারলেখ কাঠামো XrNegotiateApiLayerRequest {
    XrLoaderInterfaceStructs        structType;
    uint32_t                        structVersion;
    size_t                          struct_আকার;
    uint32_t                        layerInterfaceVersion;
    XrVersion                       layerApiVersion;
    PFN_xrGetInstanceProcAddr       getInstanceProcAddr;
    PFN_xrCreateApiLayerInstance    createApiLayerInstance;
} XrNegotiateApiLayerRequest;

প্রকারলেখ কাঠামো XrNegotiateLoaderInfo {
    XrLoaderInterfaceStructs    structType;
    uint32_t                    structVersion;
    size_t                      struct_আকার;
    uint32_t                    minInterfaceVersion;
    uint32_t                    maxInterfaceVersion;
    XrVersion                   minApiVersion;
    XrVersion                   maxApiVersion;
} XrNegotiateLoaderInfo;

প্রকারলেখ কাঠামো XrNegotiateRuntimeRequest {
    XrLoaderInterfaceStructs     structType;
    uint32_t                     structVersion;
    size_t                       struct_আকার;
    uint32_t                     runtimeInterfaceVersion;
    XrVersion                    runtimeApiVersion;
    PFN_xrGetInstanceProcAddr    getInstanceProcAddr;
} XrNegotiateRuntimeRequest;

প্রকারলেখ Xr_ফলাফল (XRAPI_PTR *PFN_xrCreateApiLayerInstance)(ধ্রুবক XrInstanceCreateInfo* info, ধ্রুবক XrApiLayerCreateInfo* layerInfo, XrInstance* instance);
প্রকারলেখ Xr_ফলাফল (XRAPI_PTR *PFN_xrNegotiateLoaderRuntimeInterface)(ধ্রুবক XrNegotiateLoaderInfo* loaderInfo, XrNegotiateRuntimeRequest* runtimeRequest);
প্রকারলেখ Xr_ফলাফল (XRAPI_PTR *PFN_xrNegotiateLoaderApiLayerInterface)(ধ্রুবক XrNegotiateLoaderInfo* loaderInfo, ধ্রুবক অক্ষর* layerName, XrNegotiateApiLayerRequest* apiLayerRequest);

#ifndef XR_NO_PROTOTYPES
#ifdef XR_EXTENSION_PROTOTYPES
XRAPI_ATTR Xr_ফলাফল XRAPI_CALL xrCreateApiLayerInstance(
    ধ্রুবক XrInstanceCreateInfo*                 info,
    ধ্রুবক XrApiLayerCreateInfo*                 layerInfo,
    XrInstance*                                 instance);

XRAPI_ATTR Xr_ফলাফল XRAPI_CALL xrNegotiateLoaderRuntimeInterface(
    ধ্রুবক XrNegotiateLoaderInfo*                loaderInfo,
    XrNegotiateRuntimeRequest*                  runtimeRequest);

XRAPI_ATTR Xr_ফলাফল XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
    ধ্রুবক XrNegotiateLoaderInfo*                loaderInfo,
    ধ্রুবক অক্ষর*                                 layerName,
    XrNegotiateApiLayerRequest*                 apiLayerRequest);
#endif /* XR_EXTENSION_PROTOTYPES */
#endif /* !XR_NO_PROTOTYPES */

#ifdef __cplusplus
}
#endif

#endif

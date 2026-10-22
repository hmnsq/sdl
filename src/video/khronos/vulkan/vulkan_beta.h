#ifndef VULKAN_BETA_H_
#define VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
বাহ্যিক "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

প্রকারলেখ কাঠামো VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           pointPolygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separateStencilMaskRef;
    VkBool32           shaderSampleRateInterpolationFunctions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellationPointMode;
    VkBool32           triangleFans;
    VkBool32           vertexAttributeAccessBeyondStride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

প্রকারলেখ কাঠামো VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           min_Vertex_প্রবেশ_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_সূচক_UNUSED_AMDX       (~0U)

প্রকারলেখ কাঠামো VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

প্রকারলেখ কাঠামো VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           max_Execution_Graph_Shader_Payload_আকার;
    uint32_t           max_Execution_Graph_Shader_Payload_গুনতি;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_গুনতি[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

প্রকারলেখ কাঠামো Vk_Execution_Graph_Pipeline_Scratch_আকার_AMDX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    Vk_Device_আকার       min_আকার;
    Vk_Device_আকার       max_আকার_2;
    Vk_Device_আকার       আকার_Granularity;
} Vk_Execution_Graph_Pipeline_Scratch_আকার_AMDX;

প্রকারলেখ কাঠামো VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ধ্রুবক শূন্য*                               p_পরবর্তী;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_গুনতি;
    ধ্রুবক VkPipelineShaderStageCreateInfo*    pStages;
    ধ্রুবক VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   base_Pipeline_সূচক;
} VkExecutionGraphPipelineCreateInfoAMDX;

প্রকারলেখ সংঘ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ধ্রুবক শূন্য*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

প্রকারলেখ কাঠামো VkDispatchGraphInfoAMDX {
    uint32_t                          গ্রন্থি_সূচক_2;
    uint32_t                          payload_গুনতি;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

প্রকারলেখ কাঠামো Vk_Dispatch_Graph_গুনতি_Info_AMDX {
    uint32_t                          গুনতি;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_গুনতি_Info_AMDX;

প্রকারলেখ কাঠামো Vk_Pipeline_Shader_Stage_গ্রন্থি_Create_Info_AMDX {
      VkStructureType    sType;
    ধ্রুবক শূন্য*          p_পরবর্তী;
    ধ্রুবক অক্ষর*          pName;
    uint32_t             সূচক;
} Vk_Pipeline_Shader_Stage_গ্রন্থি_Create_Info_AMDX;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_গুনতি, ধ্রুবক VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ধ্রুবক VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_Scratch_আকার_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, Vk_Execution_Graph_Pipeline_Scratch_আকার_AMDX*        p_আকার_Info);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_গ্রন্থি_সূচক_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ধ্রুবক Vk_Pipeline_Shader_Stage_গ্রন্থি_Create_Info_AMDX*  p_গ্রন্থি_Info, uint32_t*                                       p_গ্রন্থি_সূচক);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(Vk_Command_বাফার                                 command_বাফার, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, Vk_Device_আকার                                    scratch_আকার);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(Vk_Command_বাফার                                 command_বাফার, VkDeviceAddress                                 scratch, Vk_Device_আকার                                    scratch_আকার, ধ্রুবক Vk_Dispatch_Graph_গুনতি_Info_AMDX*             p_গুনতি_Info);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(Vk_Command_বাফার                                 command_বাফার, VkDeviceAddress                                 scratch, Vk_Device_আকার                                    scratch_আকার, ধ্রুবক Vk_Dispatch_Graph_গুনতি_Info_AMDX*             p_গুনতি_Info);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_গুনতি_AMDX)(Vk_Command_বাফার                                 command_বাফার, VkDeviceAddress                                 scratch, Vk_Device_আকার                                    scratch_আকার, VkDeviceAddress                                 গুনতি_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_গুনতি,
    ধ্রুবক VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Execution_Graph_Pipeline_Scratch_আকার_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    Vk_Execution_Graph_Pipeline_Scratch_আকার_AMDX*    p_আকার_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vk_Get_Execution_Graph_Pipeline_গ্রন্থি_সূচক_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ধ্রুবক Vk_Pipeline_Shader_Stage_গ্রন্থি_Create_Info_AMDX* p_গ্রন্থি_Info,
    uint32_t*                                   p_গ্রন্থি_সূচক);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    Vk_Command_বাফার                             command_বাফার,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    Vk_Device_আকার                                scratch_আকার);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdDispatchGraphAMDX(
    Vk_Command_বাফার                             command_বাফার,
    VkDeviceAddress                             scratch,
    Vk_Device_আকার                                scratch_আকার,
    ধ্রুবক Vk_Dispatch_Graph_গুনতি_Info_AMDX*         p_গুনতি_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    Vk_Command_বাফার                             command_বাফার,
    VkDeviceAddress                             scratch,
    Vk_Device_আকার                                scratch_আকার,
    ধ্রুবক Vk_Dispatch_Graph_গুনতি_Info_AMDX*         p_গুনতি_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_গুনতি_AMDX(
    Vk_Command_বাফার                             command_বাফার,
    VkDeviceAddress                             scratch,
    Vk_Device_আকার                                scratch_আকার,
    VkDeviceAddress                             গুনতি_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

প্রকারলেখ কাঠামো VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    size_t             তথ্য_আকার_2;
    ধ্রুবক শূন্য*        p_তথ্য;
} VkCudaModuleCreateInfoNV;

প্রকারলেখ কাঠামো VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    VkCudaModuleNV     module;
    ধ্রুবক অক্ষর*        pName;
} VkCudaFunctionCreateInfoNV;

প্রকারলেখ কাঠামো VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ধ্রুবক শূন্য*            p_পরবর্তী;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_গুনতি;
    ধ্রুবক শূন্য* ধ্রুবক *    pParams;
    size_t                 extra_গুনতি;
    ধ্রুবক শূন্য* ধ্রুবক *    pExtras;
} VkCudaLaunchInfoNV;

প্রকারলেখ কাঠামো VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

প্রকারলেখ কাঠামো VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ধ্রুবক VkCudaModuleCreateInfoNV* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_আকার, শূন্য* p_Cache_তথ্য);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ধ্রুবক VkCudaFunctionCreateInfoNV* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ধ্রুবক VkAllocationCallbacks* pAllocator);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ধ্রুবক VkAllocationCallbacks* pAllocator);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_বাফার command_বাফার, ধ্রুবক VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ধ্রুবক VkCudaModuleCreateInfoNV*             pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_আকার,
    শূন্য*                                       p_Cache_তথ্য);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ধ্রুবক VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ধ্রুবক VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ধ্রুবক VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_বাফার                             command_বাফার,
    ধ্রুবক VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

প্রকারলেখ গণনা VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

প্রকারলেখ কাঠামো VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

প্রকারলেখ কাঠামো VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

প্রকারলেখ কাঠামো VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    শূন্য*                               p_পরবর্তী;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacementVectorFormat;
    VkDeviceOrHostAddressConstKHR       displacement_Bias_And_Scale_বাফার;
    Vk_Device_আকার                        displacementBiasAndScaleStride;
    VkDeviceOrHostAddressConstKHR       displacement_Vector_বাফার;
    Vk_Device_আকার                        displacementVectorStride;
    VkDeviceOrHostAddressConstKHR       displacedMicromapPrimitiveFlags;
    Vk_Device_আকার                        displacedMicromapPrimitiveFlagsStride;
    Vk_সূচক_Type                         সূচক_Type;
    VkDeviceOrHostAddressConstKHR       সূচক_বাফার_2;
    Vk_Device_আকার                        সূচক_Stride;
    uint32_t                            baseTriangle;
    uint32_t                            usage_Counts_গুনতি;
    ধ্রুবক VkMicromapUsageEXT*           pUsageCounts;
    ধ্রুবক VkMicromapUsageEXT* ধ্রুবক*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

প্রকারলেখ গণনা VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

প্রকারলেখ কাঠামো VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

প্রকারলেখ কাঠামো Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_তথ্য_AMDX {
    VkStructureType                   sType;
    ধ্রুবক শূন্য*                       p_পরবর্তী;
    VkDeviceOrHostAddressConstKHR     compressed_তথ্য;
    Vk_Device_আকার                      তথ্য_আকার_2;
    uint32_t                          অঙ্ক_Triangles;
    uint32_t                          অঙ্ক_Vertices;
    uint32_t                          max_Primitive_সূচক;
    uint32_t                          max_Geometry_সূচক;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_তথ্য_AMDX;


#ifdef __cplusplus
}
#endif

#endif

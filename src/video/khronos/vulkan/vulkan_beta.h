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
خارجي "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    فراغ*              pNext;
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

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    فراغ*              pNext;
    uint32_t           min_Vertex_ماسوقن_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

تعريفنوع بنية VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    فراغ*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

تعريفنوع بنية VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    فراغ*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_کيراءن;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_کيراءن[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

تعريفنوع بنية VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    فراغ*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

تعريفنوع بنية VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ثابت فراغ*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_کيراءن;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

تعريفنوع اتحاد VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ثابت فراغ*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

تعريفنوع بنية VkDispatchGraphInfoAMDX {
    uint32_t                          نود_Index_2;
    uint32_t                          payload_کيراءن;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

تعريفنوع بنية Vk_Dispatch_Graph_کيراءن_Info_AMDX {
    uint32_t                          کيراءن;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_کيراءن_Info_AMDX;

تعريفنوع بنية Vk_Pipeline_Shader_Stage_نود_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت فراغ*          pNext;
    ثابت حرف*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_نود_Create_Info_AMDX;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_کيراءن, ثابت VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ثابت VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
تعريفنوع VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_نود_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ثابت Vk_Pipeline_Shader_Stage_نود_Create_Info_AMDX*  p_نود_Info, uint32_t*                                       p_نود_Index);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ثابت Vk_Dispatch_Graph_کيراءن_Info_AMDX*             p_کيراءن_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ثابت Vk_Dispatch_Graph_کيراءن_Info_AMDX*             p_کيراءن_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_کيراءن_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 کيراءن_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_کيراءن,
    ثابت VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_نود_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ثابت Vk_Pipeline_Shader_Stage_نود_Create_Info_AMDX* p_نود_Info,
    uint32_t*                                   p_نود_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ثابت Vk_Dispatch_Graph_کيراءن_Info_AMDX*         p_کيراءن_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ثابت Vk_Dispatch_Graph_کيراءن_Info_AMDX*         p_کيراءن_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_کيراءن_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             کيراءن_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

تعريفنوع بنية VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    size_t             dataSize;
    ثابت فراغ*        pData;
} VkCudaModuleCreateInfoNV;

تعريفنوع بنية VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    VkCudaModuleNV     module;
    ثابت حرف*        pName;
} VkCudaFunctionCreateInfoNV;

تعريفنوع بنية VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت فراغ*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_کيراءن;
    ثابت فراغ* ثابت *    pParams;
    size_t                 extra_کيراءن;
    ثابت فراغ* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    فراغ*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    فراغ*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, فراغ* pCacheData);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت VkAllocationCallbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت VkAllocationCallbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ثابت VkCudaModuleCreateInfoNV*             pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    فراغ*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

تعريفنوع تعداد VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    فراغ*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    فراغ*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

تعريفنوع بنية VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    فراغ*                               pNext;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacementVectorFormat;
    VkDeviceOrHostAddressConstKHR       displacementBiasAndScaleBuffer;
    VkDeviceSize                        displacementBiasAndScaleStride;
    VkDeviceOrHostAddressConstKHR       displacementVectorBuffer;
    VkDeviceSize                        displacementVectorStride;
    VkDeviceOrHostAddressConstKHR       displacedMicromapPrimitiveFlags;
    VkDeviceSize                        displacedMicromapPrimitiveFlagsStride;
    VkIndexType                         indexType;
    VkDeviceOrHostAddressConstKHR       indexBuffer;
    VkDeviceSize                        indexStride;
    uint32_t                            baseTriangle;
    uint32_t                            usage_Counts_کيراءن;
    ثابت VkMicromapUsageEXT*           pUsageCounts;
    ثابت VkMicromapUsageEXT* ثابت*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

تعريفنوع تعداد VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

تعريفنوع بنية VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    فراغ*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

تعريفنوع بنية VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    ثابت فراغ*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          اڠک_Triangles;
    uint32_t                          اڠک_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

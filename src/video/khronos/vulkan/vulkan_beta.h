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
বাহ্য "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

প্রকারনির্দেশ সংরচনা VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    শূন্য*              pNext;
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

প্রকারনির্দেশ সংরচনা VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint32_t           min_Vertex_প্ৰবেশ_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_গুনতি;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_গুনতি[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

প্রকারনির্দেশ সংরচনা VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

প্রকারনির্দেশ সংরচনা VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ধ্রুৱ শূন্য*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_গুনতি;
    ধ্রুৱ VkPipelineShaderStageCreateInfo*    pStages;
    ধ্রুৱ VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

প্রকারনির্দেশ সঙ্ঘ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ধ্রুৱ শূন্য*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

প্রকারনির্দেশ সংরচনা VkDispatchGraphInfoAMDX {
    uint32_t                          গ্ৰন্থি_Index_2;
    uint32_t                          payload_গুনতি;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

প্রকারনির্দেশ সংরচনা Vk_Dispatch_Graph_গুনতি_Info_AMDX {
    uint32_t                          গুনতি;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_গুনতি_Info_AMDX;

প্রকারনির্দেশ সংরচনা Vk_Pipeline_Shader_Stage_গ্ৰন্থি_Create_Info_AMDX {
      VkStructureType    sType;
    ধ্রুৱ শূন্য*          pNext;
    ধ্রুৱ ৱর্ণ*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_গ্ৰন্থি_Create_Info_AMDX;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_গুনতি, ধ্রুৱ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ধ্রুৱ VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_গ্ৰন্থি_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ধ্রুৱ Vk_Pipeline_Shader_Stage_গ্ৰন্থি_Create_Info_AMDX*  p_গ্ৰন্থি_Info, uint32_t*                                       p_গ্ৰন্থি_Index);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ধ্রুৱ Vk_Dispatch_Graph_গুনতি_Info_AMDX*             p_গুনতি_Info);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ধ্রুৱ Vk_Dispatch_Graph_গুনতি_Info_AMDX*             p_গুনতি_Info);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_গুনতি_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 গুনতি_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_গুনতি,
    ধ্রুৱ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_গ্ৰন্থি_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ধ্রুৱ Vk_Pipeline_Shader_Stage_গ্ৰন্থি_Create_Info_AMDX* p_গ্ৰন্থি_Info,
    uint32_t*                                   p_গ্ৰন্থি_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ধ্রুৱ Vk_Dispatch_Graph_গুনতি_Info_AMDX*         p_গুনতি_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ধ্রুৱ Vk_Dispatch_Graph_গুনতি_Info_AMDX*         p_গুনতি_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_গুনতি_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             গুনতি_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

প্রকারনির্দেশ সংরচনা VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ধ্রুৱ শূন্য*        pNext;
    size_t             dataSize;
    ধ্রুৱ শূন্য*        pData;
} VkCudaModuleCreateInfoNV;

প্রকারনির্দেশ সংরচনা VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ধ্রুৱ শূন্য*        pNext;
    VkCudaModuleNV     module;
    ধ্রুৱ ৱর্ণ*        pName;
} VkCudaFunctionCreateInfoNV;

প্রকারনির্দেশ সংরচনা VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ধ্রুৱ শূন্য*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_গুনতি;
    ধ্রুৱ শূন্য* ধ্রুৱ *    pParams;
    size_t                 extra_গুনতি;
    ধ্রুৱ শূন্য* ধ্রুৱ *    pExtras;
} VkCudaLaunchInfoNV;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ধ্রুৱ VkCudaModuleCreateInfoNV* pCreateInfo, ধ্রুৱ VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, শূন্য* pCacheData);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ধ্রুৱ VkCudaFunctionCreateInfoNV* pCreateInfo, ধ্রুৱ VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ধ্রুৱ VkAllocationCallbacks* pAllocator);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ধ্রুৱ VkAllocationCallbacks* pAllocator);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, ধ্রুৱ VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ধ্রুৱ VkCudaModuleCreateInfoNV*             pCreateInfo,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    শূন্য*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ধ্রুৱ VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ধ্রুৱ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    ধ্রুৱ VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

প্রকারনির্দেশ গণনা VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

প্রকারনির্দেশ সংরচনা VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    শূন্য*                               pNext;
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
    uint32_t                            usage_Counts_গুনতি;
    ধ্রুৱ VkMicromapUsageEXT*           pUsageCounts;
    ধ্রুৱ VkMicromapUsageEXT* ধ্রুৱ*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

প্রকারনির্দেশ গণনা VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

প্রকারনির্দেশ সংরচনা VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    শূন্য*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

প্রকারনির্দেশ সংরচনা VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    ধ্রুৱ শূন্য*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          অঙ্ক_Triangles;
    uint32_t                          অঙ্ক_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

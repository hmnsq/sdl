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
بیرونی "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

تعریفنوع ساختار VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    تهی*              pNext;
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

تعریفنوع ساختار VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    تهی*              pNext;
    uint32_t           min_Vertex_درون_داد_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

تعریفنوع ساختار VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    تهی*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

تعریفنوع ساختار VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    تهی*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_شمار;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_شمار[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

تعریفنوع ساختار VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    تهی*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

تعریفنوع ساختار VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ثابت تهی*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_شمار;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

تعریفنوع اجتماع VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ثابت تهی*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

تعریفنوع ساختار VkDispatchGraphInfoAMDX {
    uint32_t                          گره_Index_2;
    uint32_t                          payload_شمار;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

تعریفنوع ساختار Vk_Dispatch_Graph_شمار_Info_AMDX {
    uint32_t                          شمار;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_شمار_Info_AMDX;

تعریفنوع ساختار Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت تهی*          pNext;
    ثابت نویسه*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_شمار, ثابت VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ثابت VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
تعریفنوع VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_گره_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ثابت Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX*  p_گره_Info, uint32_t*                                       p_گره_Index);
تعریفنوع تهی (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
تعریفنوع تهی (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ثابت Vk_Dispatch_Graph_شمار_Info_AMDX*             p_شمار_Info);
تعریفنوع تهی (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ثابت Vk_Dispatch_Graph_شمار_Info_AMDX*             p_شمار_Info);
تعریفنوع تهی (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_شمار_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 شمار_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_شمار,
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
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_گره_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ثابت Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX* p_گره_Info,
    uint32_t*                                   p_گره_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ثابت Vk_Dispatch_Graph_شمار_Info_AMDX*         p_شمار_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ثابت Vk_Dispatch_Graph_شمار_Info_AMDX*         p_شمار_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_شمار_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             شمار_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

تعریفنوع ساختار VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    size_t             dataSize;
    ثابت تهی*        pData;
} VkCudaModuleCreateInfoNV;

تعریفنوع ساختار VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    VkCudaModuleNV     module;
    ثابت نویسه*        pName;
} VkCudaFunctionCreateInfoNV;

تعریفنوع ساختار VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت تهی*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_شمار;
    ثابت تهی* ثابت *    pParams;
    size_t                 extra_شمار;
    ثابت تهی* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

تعریفنوع ساختار VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    تهی*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

تعریفنوع ساختار VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    تهی*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, تهی* pCacheData);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
تعریفنوع تهی (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت VkAllocationCallbacks* pAllocator);
تعریفنوع تهی (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت VkAllocationCallbacks* pAllocator);
تعریفنوع تهی (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

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
    تهی*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

تعریفنوع شمارش VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

تعریفنوع ساختار VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    تهی*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

تعریفنوع ساختار VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    تهی*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

تعریفنوع ساختار VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    تهی*                               pNext;
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
    uint32_t                            usage_Counts_شمار;
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

تعریفنوع شمارش VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

تعریفنوع ساختار VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    تهی*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

تعریفنوع ساختار VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    ثابت تهی*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          رقم_Triangles;
    uint32_t                          رقم_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

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
ಬಾಹ್ಯ "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint32_t           min_Vertex_ಒಳಹರಿವು_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_ಎಣಿಕೆ;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_ಎಣಿಕೆ[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ಧ್ರುವ ಶೂನ್ಯ*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_ಎಣಿಕೆ;
    ಧ್ರುವ VkPipelineShaderStageCreateInfo*    pStages;
    ಧ್ರುವ VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಙ್ಘ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ಧ್ರುವ ಶೂನ್ಯ*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkDispatchGraphInfoAMDX {
    uint32_t                          ಗಂಟು_Index_2;
    uint32_t                          payload_ಎಣಿಕೆ;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Vk_Dispatch_Graph_ಎಣಿಕೆ_Info_AMDX {
    uint32_t                          ಎಣಿಕೆ;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_ಎಣಿಕೆ_Info_AMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX {
      VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*          pNext;
    ಧ್ರುವ ವರ್ಣ*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_ಎಣಿಕೆ, ಧ್ರುವ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ಧ್ರುವ VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_ಗಂಟು_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ಧ್ರುವ Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX*  p_ಗಂಟು_Info, uint32_t*                                       p_ಗಂಟು_Index);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ಧ್ರುವ Vk_Dispatch_Graph_ಎಣಿಕೆ_Info_AMDX*             p_ಎಣಿಕೆ_Info);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ಧ್ರುವ Vk_Dispatch_Graph_ಎಣಿಕೆ_Info_AMDX*             p_ಎಣಿಕೆ_Info);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_ಎಣಿಕೆ_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 ಎಣಿಕೆ_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_ಎಣಿಕೆ,
    ಧ್ರುವ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_ಗಂಟು_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ಧ್ರುವ Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX* p_ಗಂಟು_Info,
    uint32_t*                                   p_ಗಂಟು_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ಧ್ರುವ Vk_Dispatch_Graph_ಎಣಿಕೆ_Info_AMDX*         p_ಎಣಿಕೆ_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ಧ್ರುವ Vk_Dispatch_Graph_ಎಣಿಕೆ_Info_AMDX*         p_ಎಣಿಕೆ_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_ಎಣಿಕೆ_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             ಎಣಿಕೆ_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    size_t             dataSize;
    ಧ್ರುವ ಶೂನ್ಯ*        pData;
} VkCudaModuleCreateInfoNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    VkCudaModuleNV     module;
    ಧ್ರುವ ವರ್ಣ*        pName;
} VkCudaFunctionCreateInfoNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ಧ್ರುವ ಶೂನ್ಯ*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_ಎಣಿಕೆ;
    ಧ್ರುವ ಶೂನ್ಯ* ಧ್ರುವ *    pParams;
    size_t                 extra_ಎಣಿಕೆ;
    ಧ್ರುವ ಶೂನ್ಯ* ಧ್ರುವ *    pExtras;
} VkCudaLaunchInfoNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ಧ್ರುವ VkCudaModuleCreateInfoNV* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, ಶೂನ್ಯ* pCacheData);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ಧ್ರುವ VkCudaFunctionCreateInfoNV* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ಧ್ರುವ VkAllocationCallbacks* pAllocator);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ಧ್ರುವ VkAllocationCallbacks* pAllocator);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, ಧ್ರುವ VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ಧ್ರುವ VkCudaModuleCreateInfoNV*             pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    ಶೂನ್ಯ*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ಧ್ರುವ VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    ಧ್ರುವ VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    ಶೂನ್ಯ*                               pNext;
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
    uint32_t                            usage_Counts_ಎಣಿಕೆ;
    ಧ್ರುವ VkMicromapUsageEXT*           pUsageCounts;
    ಧ್ರುವ VkMicromapUsageEXT* ಧ್ರುವ*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    ಧ್ರುವ ಶೂನ್ಯ*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          ಅಂಕೆ_Triangles;
    uint32_t                          ಅಂಕೆ_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

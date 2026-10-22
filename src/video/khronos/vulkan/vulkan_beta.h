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
வெளி "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

வகைவரை கட்டமைப்பு VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    வெறுமை*              pNext;
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

வகைவரை கட்டமைப்பு VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint32_t           min_Vertex_உள்ளீடு_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

வகைவரை கட்டமைப்பு VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

வகைவரை கட்டமைப்பு VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_மொத்தம்;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_மொத்தம்[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

வகைவரை கட்டமைப்பு VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

வகைவரை கட்டமைப்பு VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    மாறிலி வெறுமை*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_மொத்தம்;
    மாறிலி VkPipelineShaderStageCreateInfo*    pStages;
    மாறிலி VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

வகைவரை ஒன்றிப்பு VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    மாறிலி வெறுமை*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

வகைவரை கட்டமைப்பு VkDispatchGraphInfoAMDX {
    uint32_t                          முனை_Index_2;
    uint32_t                          payload_மொத்தம்;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

வகைவரை கட்டமைப்பு Vk_Dispatch_Graph_மொத்தம்_Info_AMDX {
    uint32_t                          மொத்தம்;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_மொத்தம்_Info_AMDX;

வகைவரை கட்டமைப்பு Vk_Pipeline_Shader_Stage_முனை_Create_Info_AMDX {
      VkStructureType    sType;
    மாறிலி வெறுமை*          pNext;
    மாறிலி எழுத்து*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_முனை_Create_Info_AMDX;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_மொத்தம், மாறிலி VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, மாறிலி VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
வகைவரை VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
வகைவரை VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_முனை_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, மாறிலி Vk_Pipeline_Shader_Stage_முனை_Create_Info_AMDX*  p_முனை_Info, uint32_t*                                       p_முனை_Index);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, மாறிலி Vk_Dispatch_Graph_மொத்தம்_Info_AMDX*             p_மொத்தம்_Info);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, மாறிலி Vk_Dispatch_Graph_மொத்தம்_Info_AMDX*             p_மொத்தம்_Info);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_மொத்தம்_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 மொத்தம்_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_மொத்தம்,
    மாறிலி VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_முனை_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    மாறிலி Vk_Pipeline_Shader_Stage_முனை_Create_Info_AMDX* p_முனை_Info,
    uint32_t*                                   p_முனை_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    மாறிலி Vk_Dispatch_Graph_மொத்தம்_Info_AMDX*         p_மொத்தம்_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    மாறிலி Vk_Dispatch_Graph_மொத்தம்_Info_AMDX*         p_மொத்தம்_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_மொத்தம்_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             மொத்தம்_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

வகைவரை கட்டமைப்பு VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    size_t             dataSize;
    மாறிலி வெறுமை*        pData;
} VkCudaModuleCreateInfoNV;

வகைவரை கட்டமைப்பு VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    VkCudaModuleNV     module;
    மாறிலி எழுத்து*        pName;
} VkCudaFunctionCreateInfoNV;

வகைவரை கட்டமைப்பு VkCudaLaunchInfoNV {
    VkStructureType        sType;
    மாறிலி வெறுமை*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_மொத்தம்;
    மாறிலி வெறுமை* மாறிலி *    pParams;
    size_t                 extra_மொத்தம்;
    மாறிலி வெறுமை* மாறிலி *    pExtras;
} VkCudaLaunchInfoNV;

வகைவரை கட்டமைப்பு VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

வகைவரை கட்டமைப்பு VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, மாறிலி VkCudaModuleCreateInfoNV* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
வகைவரை VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, வெறுமை* pCacheData);
வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, மாறிலி VkCudaFunctionCreateInfoNV* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, மாறிலி VkAllocationCallbacks* pAllocator);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, மாறிலி VkAllocationCallbacks* pAllocator);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, மாறிலி VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    மாறிலி VkCudaModuleCreateInfoNV*             pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    வெறுமை*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    மாறிலி VkCudaFunctionCreateInfoNV*           pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    மாறிலி VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    மாறிலி VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    மாறிலி VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

வகைவரை எண்ணிக்கை VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

வகைவரை கட்டமைப்பு VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

வகைவரை கட்டமைப்பு VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

வகைவரை கட்டமைப்பு VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    வெறுமை*                               pNext;
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
    uint32_t                            usage_Counts_மொத்தம்;
    மாறிலி VkMicromapUsageEXT*           pUsageCounts;
    மாறிலி VkMicromapUsageEXT* மாறிலி*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

வகைவரை எண்ணிக்கை VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

வகைவரை கட்டமைப்பு VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    வெறுமை*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

வகைவரை கட்டமைப்பு VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    மாறிலி வெறுமை*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          இலக்கம்_Triangles;
    uint32_t                          இலக்கம்_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

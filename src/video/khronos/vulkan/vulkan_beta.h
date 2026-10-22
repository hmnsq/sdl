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
ബാഹ്യ "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

തരനിർവചനം ഘടന VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
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

തരനിർവചനം ഘടന VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint32_t           min_Vertex_നിവേശം_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

തരനിർവചനം ഘടന VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

തരനിർവചനം ഘടന VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_എണ്ണം;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_എണ്ണം[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

തരനിർവചനം ഘടന VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

തരനിർവചനം ഘടന VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    സ്ഥിരം ശൂന്യം*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_എണ്ണം;
    സ്ഥിരം VkPipelineShaderStageCreateInfo*    pStages;
    സ്ഥിരം VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

തരനിർവചനം സംഘം VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    സ്ഥിരം ശൂന്യം*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

തരനിർവചനം ഘടന VkDispatchGraphInfoAMDX {
    uint32_t                          കണ്ണി_Index_2;
    uint32_t                          payload_എണ്ണം;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

തരനിർവചനം ഘടന Vk_Dispatch_Graph_എണ്ണം_Info_AMDX {
    uint32_t                          എണ്ണം;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_എണ്ണം_Info_AMDX;

തരനിർവചനം ഘടന Vk_Pipeline_Shader_Stage_കണ്ണി_Create_Info_AMDX {
      VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*          pNext;
    സ്ഥിരം അക്ഷരം*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_കണ്ണി_Create_Info_AMDX;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_എണ്ണം, സ്ഥിരം VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, സ്ഥിരം VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_കണ്ണി_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, സ്ഥിരം Vk_Pipeline_Shader_Stage_കണ്ണി_Create_Info_AMDX*  p_കണ്ണി_Info, uint32_t*                                       p_കണ്ണി_Index);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, സ്ഥിരം Vk_Dispatch_Graph_എണ്ണം_Info_AMDX*             p_എണ്ണം_Info);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, സ്ഥിരം Vk_Dispatch_Graph_എണ്ണം_Info_AMDX*             p_എണ്ണം_Info);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_എണ്ണം_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 എണ്ണം_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_എണ്ണം,
    സ്ഥിരം VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_കണ്ണി_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    സ്ഥിരം Vk_Pipeline_Shader_Stage_കണ്ണി_Create_Info_AMDX* p_കണ്ണി_Info,
    uint32_t*                                   p_കണ്ണി_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    സ്ഥിരം Vk_Dispatch_Graph_എണ്ണം_Info_AMDX*         p_എണ്ണം_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    സ്ഥിരം Vk_Dispatch_Graph_എണ്ണം_Info_AMDX*         p_എണ്ണം_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_എണ്ണം_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             എണ്ണം_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

തരനിർവചനം ഘടന VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    size_t             dataSize;
    സ്ഥിരം ശൂന്യം*        pData;
} VkCudaModuleCreateInfoNV;

തരനിർവചനം ഘടന VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    VkCudaModuleNV     module;
    സ്ഥിരം അക്ഷരം*        pName;
} VkCudaFunctionCreateInfoNV;

തരനിർവചനം ഘടന VkCudaLaunchInfoNV {
    VkStructureType        sType;
    സ്ഥിരം ശൂന്യം*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_എണ്ണം;
    സ്ഥിരം ശൂന്യം* സ്ഥിരം *    pParams;
    size_t                 extra_എണ്ണം;
    സ്ഥിരം ശൂന്യം* സ്ഥിരം *    pExtras;
} VkCudaLaunchInfoNV;

തരനിർവചനം ഘടന VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

തരനിർവചനം ഘടന VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, സ്ഥിരം VkCudaModuleCreateInfoNV* pCreateInfo, സ്ഥിരം VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, ശൂന്യം* pCacheData);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, സ്ഥിരം VkCudaFunctionCreateInfoNV* pCreateInfo, സ്ഥിരം VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, സ്ഥിരം VkAllocationCallbacks* pAllocator);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, സ്ഥിരം VkAllocationCallbacks* pAllocator);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, സ്ഥിരം VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    സ്ഥിരം VkCudaModuleCreateInfoNV*             pCreateInfo,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    ശൂന്യം*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    സ്ഥിരം VkCudaFunctionCreateInfoNV*           pCreateInfo,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    സ്ഥിരം VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

തരനിർവചനം എണ്ണൽ VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

തരനിർവചനം ഘടന VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

തരനിർവചനം ഘടന VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

തരനിർവചനം ഘടന VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    ശൂന്യം*                               pNext;
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
    uint32_t                            usage_Counts_എണ്ണം;
    സ്ഥിരം VkMicromapUsageEXT*           pUsageCounts;
    സ്ഥിരം VkMicromapUsageEXT* സ്ഥിരം*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

തരനിർവചനം എണ്ണൽ VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

തരനിർവചനം ഘടന VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

തരനിർവചനം ഘടന VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    സ്ഥിരം ശൂന്യം*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          അക്കം_Triangles;
    uint32_t                          അക്കം_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

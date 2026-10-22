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
बाह्य "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

प्रकारनिर्देश संरचना VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    शून्य*              pNext;
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

प्रकारनिर्देश संरचना VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           min_Vertex_आदान_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

प्रकारनिर्देश संरचना VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

प्रकारनिर्देश संरचना VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_मोजणी;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_मोजणी[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

प्रकारनिर्देश संरचना VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

प्रकारनिर्देश संरचना VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ध्रुव शून्य*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_मोजणी;
    ध्रुव VkPipelineShaderStageCreateInfo*    pStages;
    ध्रुव VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

प्रकारनिर्देश सङ्घ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ध्रुव शून्य*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

प्रकारनिर्देश संरचना VkDispatchGraphInfoAMDX {
    uint32_t                          गाठ_Index_2;
    uint32_t                          payload_मोजणी;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

प्रकारनिर्देश संरचना Vk_Dispatch_Graph_मोजणी_Info_AMDX {
    uint32_t                          मोजणी;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_मोजणी_Info_AMDX;

प्रकारनिर्देश संरचना Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX {
      VkStructureType    sType;
    ध्रुव शून्य*          pNext;
    ध्रुव वर्ण*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_मोजणी, ध्रुव VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ध्रुव VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_गाठ_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ध्रुव Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX*  p_गाठ_Info, uint32_t*                                       p_गाठ_Index);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ध्रुव Vk_Dispatch_Graph_मोजणी_Info_AMDX*             p_मोजणी_Info);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ध्रुव Vk_Dispatch_Graph_मोजणी_Info_AMDX*             p_मोजणी_Info);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_मोजणी_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 मोजणी_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_मोजणी,
    ध्रुव VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_गाठ_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ध्रुव Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX* p_गाठ_Info,
    uint32_t*                                   p_गाठ_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ध्रुव Vk_Dispatch_Graph_मोजणी_Info_AMDX*         p_मोजणी_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ध्रुव Vk_Dispatch_Graph_मोजणी_Info_AMDX*         p_मोजणी_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_मोजणी_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             मोजणी_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

प्रकारनिर्देश संरचना VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    size_t             dataSize;
    ध्रुव शून्य*        pData;
} VkCudaModuleCreateInfoNV;

प्रकारनिर्देश संरचना VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    VkCudaModuleNV     module;
    ध्रुव वर्ण*        pName;
} VkCudaFunctionCreateInfoNV;

प्रकारनिर्देश संरचना VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ध्रुव शून्य*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_मोजणी;
    ध्रुव शून्य* ध्रुव *    pParams;
    size_t                 extra_मोजणी;
    ध्रुव शून्य* ध्रुव *    pExtras;
} VkCudaLaunchInfoNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ध्रुव VkCudaModuleCreateInfoNV* pCreateInfo, ध्रुव VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, शून्य* pCacheData);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ध्रुव VkCudaFunctionCreateInfoNV* pCreateInfo, ध्रुव VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ध्रुव VkAllocationCallbacks* pAllocator);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ध्रुव VkAllocationCallbacks* pAllocator);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, ध्रुव VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ध्रुव VkCudaModuleCreateInfoNV*             pCreateInfo,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    शून्य*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ध्रुव VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ध्रुव VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ध्रुव VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    ध्रुव VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

प्रकारनिर्देश गणना VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

प्रकारनिर्देश संरचना VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    शून्य*                               pNext;
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
    uint32_t                            usage_Counts_मोजणी;
    ध्रुव VkMicromapUsageEXT*           pUsageCounts;
    ध्रुव VkMicromapUsageEXT* ध्रुव*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

प्रकारनिर्देश गणना VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

प्रकारनिर्देश संरचना VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

प्रकारनिर्देश संरचना VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    ध्रुव शून्य*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          अंक_Triangles;
    uint32_t                          अंक_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

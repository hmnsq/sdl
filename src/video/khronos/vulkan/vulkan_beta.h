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

प्रकारव्याख्या संरचना VkPhysicalDevicePortabilitySubsetFeaturesKHR {
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

प्रकारव्याख्या संरचना VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           min_Vertex_आदान_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

प्रकारव्याख्या संरचना VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

प्रकारव्याख्या संरचना VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
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

प्रकारव्याख्या संरचना VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

प्रकारव्याख्या संरचना VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    स्थिरांक शून्य*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_मोजणी;
    स्थिरांक VkPipelineShaderStageCreateInfo*    pStages;
    स्थिरांक VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

प्रकारव्याख्या संघ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    स्थिरांक शून्य*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

प्रकारव्याख्या संरचना VkDispatchGraphInfoAMDX {
    uint32_t                          गाठ_Index_2;
    uint32_t                          payload_मोजणी;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

प्रकारव्याख्या संरचना Vk_Dispatch_Graph_मोजणी_Info_AMDX {
    uint32_t                          मोजणी;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_मोजणी_Info_AMDX;

प्रकारव्याख्या संरचना Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX {
      VkStructureType    sType;
    स्थिरांक शून्य*          pNext;
    स्थिरांक अक्षर*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_मोजणी, स्थिरांक VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, स्थिरांक VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_गाठ_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, स्थिरांक Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX*  p_गाठ_Info, uint32_t*                                       p_गाठ_Index);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, स्थिरांक Vk_Dispatch_Graph_मोजणी_Info_AMDX*             p_मोजणी_Info);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, स्थिरांक Vk_Dispatch_Graph_मोजणी_Info_AMDX*             p_मोजणी_Info);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_मोजणी_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 मोजणी_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_मोजणी,
    स्थिरांक VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
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
    स्थिरांक Vk_Pipeline_Shader_Stage_गाठ_Create_Info_AMDX* p_गाठ_Info,
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
    स्थिरांक Vk_Dispatch_Graph_मोजणी_Info_AMDX*         p_मोजणी_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    स्थिरांक Vk_Dispatch_Graph_मोजणी_Info_AMDX*         p_मोजणी_Info);
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

प्रकारव्याख्या संरचना VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    स्थिरांक शून्य*        pNext;
    माप_प्रकार             dataSize;
    स्थिरांक शून्य*        pData;
} VkCudaModuleCreateInfoNV;

प्रकारव्याख्या संरचना VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    स्थिरांक शून्य*        pNext;
    VkCudaModuleNV     module;
    स्थिरांक अक्षर*        pName;
} VkCudaFunctionCreateInfoNV;

प्रकारव्याख्या संरचना VkCudaLaunchInfoNV {
    VkStructureType        sType;
    स्थिरांक शून्य*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    माप_प्रकार                 param_मोजणी;
    स्थिरांक शून्य* स्थिरांक *    pParams;
    माप_प्रकार                 extra_मोजणी;
    स्थिरांक शून्य* स्थिरांक *    pExtras;
} VkCudaLaunchInfoNV;

प्रकारव्याख्या संरचना VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

प्रकारव्याख्या संरचना VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, स्थिरांक VkCudaModuleCreateInfoNV* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, माप_प्रकार* pCacheSize, शून्य* pCacheData);
प्रकारव्याख्या VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, स्थिरांक VkCudaFunctionCreateInfoNV* pCreateInfo, स्थिरांक VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, स्थिरांक VkAllocationCallbacks* pAllocator);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, स्थिरांक VkAllocationCallbacks* pAllocator);
प्रकारव्याख्या शून्य (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, स्थिरांक VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    स्थिरांक VkCudaModuleCreateInfoNV*             pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    माप_प्रकार*                                     pCacheSize,
    शून्य*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    स्थिरांक VkCudaFunctionCreateInfoNV*           pCreateInfo,
    स्थिरांक VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    स्थिरांक VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    स्थिरांक VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    स्थिरांक VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

प्रकारव्याख्या गणना VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

प्रकारव्याख्या संरचना VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

प्रकारव्याख्या संरचना VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

प्रकारव्याख्या संरचना VkAccelerationStructureTrianglesDisplacementMicromapNV {
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
    स्थिरांक VkMicromapUsageEXT*           pUsageCounts;
    स्थिरांक VkMicromapUsageEXT* स्थिरांक*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

प्रकारव्याख्या गणना VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

प्रकारव्याख्या संरचना VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    शून्य*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

प्रकारव्याख्या संरचना VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    स्थिरांक शून्य*                       pNext;
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

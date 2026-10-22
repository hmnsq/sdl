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
બાહ્ય "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    શૂન્ય*              pNext;
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

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           min_Vertex_આગત_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_ગણતરી;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_ગણતરી[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

પ્રકારવ્યાખ્યા સંરચના VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

પ્રકારવ્યાખ્યા સંરચના VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    અચલ શૂન્ય*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_ગણતરી;
    અચલ VkPipelineShaderStageCreateInfo*    pStages;
    અચલ VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

પ્રકારવ્યાખ્યા સંઘ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    અચલ શૂન્ય*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

પ્રકારવ્યાખ્યા સંરચના VkDispatchGraphInfoAMDX {
    uint32_t                          ગાંઠ_Index_2;
    uint32_t                          payload_ગણતરી;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

પ્રકારવ્યાખ્યા સંરચના Vk_Dispatch_Graph_ગણતરી_Info_AMDX {
    uint32_t                          ગણતરી;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_ગણતરી_Info_AMDX;

પ્રકારવ્યાખ્યા સંરચના Vk_Pipeline_Shader_Stage_ગાંઠ_Create_Info_AMDX {
      VkStructureType    sType;
    અચલ શૂન્ય*          pNext;
    અચલ અક્ષર*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_ગાંઠ_Create_Info_AMDX;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_ગણતરી, અચલ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, અચલ VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_ગાંઠ_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, અચલ Vk_Pipeline_Shader_Stage_ગાંઠ_Create_Info_AMDX*  p_ગાંઠ_Info, uint32_t*                                       p_ગાંઠ_Index);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, અચલ Vk_Dispatch_Graph_ગણતરી_Info_AMDX*             p_ગણતરી_Info);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, અચલ Vk_Dispatch_Graph_ગણતરી_Info_AMDX*             p_ગણતરી_Info);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_ગણતરી_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 ગણતરી_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_ગણતરી,
    અચલ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_ગાંઠ_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    અચલ Vk_Pipeline_Shader_Stage_ગાંઠ_Create_Info_AMDX* p_ગાંઠ_Info,
    uint32_t*                                   p_ગાંઠ_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    અચલ Vk_Dispatch_Graph_ગણતરી_Info_AMDX*         p_ગણતરી_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    અચલ Vk_Dispatch_Graph_ગણતરી_Info_AMDX*         p_ગણતરી_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_ગણતરી_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             ગણતરી_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

પ્રકારવ્યાખ્યા સંરચના VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    size_t             dataSize;
    અચલ શૂન્ય*        pData;
} VkCudaModuleCreateInfoNV;

પ્રકારવ્યાખ્યા સંરચના VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    VkCudaModuleNV     module;
    અચલ અક્ષર*        pName;
} VkCudaFunctionCreateInfoNV;

પ્રકારવ્યાખ્યા સંરચના VkCudaLaunchInfoNV {
    VkStructureType        sType;
    અચલ શૂન્ય*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_ગણતરી;
    અચલ શૂન્ય* અચલ *    pParams;
    size_t                 extra_ગણતરી;
    અચલ શૂન્ય* અચલ *    pExtras;
} VkCudaLaunchInfoNV;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, અચલ VkCudaModuleCreateInfoNV* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, શૂન્ય* pCacheData);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, અચલ VkCudaFunctionCreateInfoNV* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, અચલ VkAllocationCallbacks* pAllocator);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, અચલ VkAllocationCallbacks* pAllocator);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, અચલ VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    અચલ VkCudaModuleCreateInfoNV*             pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    શૂન્ય*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    અચલ VkCudaFunctionCreateInfoNV*           pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    અચલ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    અચલ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    અચલ VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

પ્રકારવ્યાખ્યા ગણના VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

પ્રકારવ્યાખ્યા સંરચના VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    શૂન્ય*                               pNext;
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
    uint32_t                            usage_Counts_ગણતરી;
    અચલ VkMicromapUsageEXT*           pUsageCounts;
    અચલ VkMicromapUsageEXT* અચલ*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

પ્રકારવ્યાખ્યા ગણના VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

પ્રકારવ્યાખ્યા સંરચના VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

પ્રકારવ્યાખ્યા સંરચના VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    અચલ શૂન્ય*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          અંક_Triangles;
    uint32_t                          અંક_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

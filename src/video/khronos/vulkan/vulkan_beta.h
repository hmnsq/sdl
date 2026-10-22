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
ବାହ୍ୟ "C" {
#endif



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_portability_subset 1

#define VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           min_Vertex_ନିବେଶ_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_shader_enqueue 1

#define VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#define VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#define VK_SHADER_INDEX_UNUSED_AMDX       (~0U)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           maxExecutionGraphShaderPayloadSize;
    uint32_t           max_Execution_Graph_Shader_Payload_ଗଣନା;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_ଗଣନା[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExecutionGraphPipelineScratchSizeAMDX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkDeviceSize       minSize;
    VkDeviceSize       maxSize;
    VkDeviceSize       sizeGranularity;
} VkExecutionGraphPipelineScratchSizeAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ଅଚଳ ଶୂନ୍ୟ*                               pNext;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_ଗଣନା;
    ଅଚଳ VkPipelineShaderStageCreateInfo*    pStages;
    ଅଚଳ VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   basePipelineIndex;
} VkExecutionGraphPipelineCreateInfoAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂଘ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    ଅଚଳ ଶୂନ୍ୟ*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkDispatchGraphInfoAMDX {
    uint32_t                          ଗଣ୍ଠି_Index_2;
    uint32_t                          payload_ଗଣନା;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Vk_Dispatch_Graph_ଗଣନା_Info_AMDX {
    uint32_t                          ଗଣନା_2;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_ଗଣନା_Info_AMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Vk_Pipeline_Shader_Stage_ଗଣ୍ଠି_Create_Info_AMDX {
      VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*          pNext;
    ଅଚଳ ଅକ୍ଷର*          pName;
    uint32_t             index;
} Vk_Pipeline_Shader_Stage_ଗଣ୍ଠି_Create_Info_AMDX;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_ଗଣନା, ଅଚଳ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ଅଚଳ VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetExecutionGraphPipelineScratchSizeAMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, VkExecutionGraphPipelineScratchSizeAMDX*        pSizeInfo);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_ଗଣ୍ଠି_Index_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ଅଚଳ Vk_Pipeline_Shader_Stage_ଗଣ୍ଠି_Create_Info_AMDX*  p_ଗଣ୍ଠି_Info, uint32_t*                                       p_ଗଣ୍ଠି_Index);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(VkCommandBuffer                                 commandBuffer, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ଅଚଳ Vk_Dispatch_Graph_ଗଣନା_Info_AMDX*             p_ଗଣନା_Info);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, ଅଚଳ Vk_Dispatch_Graph_ଗଣନା_Info_AMDX*             p_ଗଣନା_Info);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_ଗଣନା_AMDX)(VkCommandBuffer                                 commandBuffer, VkDeviceAddress                                 scratch, VkDeviceSize                                    scratchSize, VkDeviceAddress                                 ଗଣନା_Info);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_ଗଣନା,
    ଅଚଳ VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetExecutionGraphPipelineScratchSizeAMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    VkExecutionGraphPipelineScratchSizeAMDX*    pSizeInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vk_Get_Execution_Graph_Pipeline_ଗଣ୍ଠି_Index_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ଅଚଳ Vk_Pipeline_Shader_Stage_ଗଣ୍ଠି_Create_Info_AMDX* p_ଗଣ୍ଠି_Info,
    uint32_t*                                   p_ଗଣ୍ଠି_Index);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    VkCommandBuffer                             commandBuffer,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkCmdDispatchGraphAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ଅଚଳ Vk_Dispatch_Graph_ଗଣନା_Info_AMDX*         p_ଗଣନା_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    ଅଚଳ Vk_Dispatch_Graph_ଗଣନା_Info_AMDX*         p_ଗଣନା_Info);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_ଗଣନା_AMDX(
    VkCommandBuffer                             commandBuffer,
    VkDeviceAddress                             scratch,
    VkDeviceSize                                scratchSize,
    VkDeviceAddress                             ଗଣନା_Info);
#endif
#endif


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#define VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#define VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    size_t             dataSize;
    ଅଚଳ ଶୂନ୍ୟ*        pData;
} VkCudaModuleCreateInfoNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    VkCudaModuleNV     module;
    ଅଚଳ ଅକ୍ଷର*        pName;
} VkCudaFunctionCreateInfoNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ଅଚଳ ଶୂନ୍ୟ*            pNext;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    size_t                 param_ଗଣନା;
    ଅଚଳ ଶୂନ୍ୟ* ଅଚଳ *    pParams;
    size_t                 extra_ଗଣନା;
    ଅଚଳ ଶୂନ୍ୟ* ଅଚଳ *    pExtras;
} VkCudaLaunchInfoNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ଅଚଳ VkCudaModuleCreateInfoNV* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* pCacheSize, ଶୂନ୍ୟ* pCacheData);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ଅଚଳ VkCudaFunctionCreateInfoNV* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ଅଚଳ VkAllocationCallbacks* pAllocator);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ଅଚଳ VkAllocationCallbacks* pAllocator);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(VkCommandBuffer commandBuffer, ଅଚଳ VkCudaLaunchInfoNV* pLaunchInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ଅଚଳ VkCudaModuleCreateInfoNV*             pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     pCacheSize,
    ଶୂନ୍ୟ*                                       pCacheData);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ଅଚଳ VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ଅଚଳ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ଅଚଳ VkAllocationCallbacks*                pAllocator);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    VkCommandBuffer                             commandBuffer,
    ଅଚଳ VkCudaLaunchInfoNV*                   pLaunchInfo);
#endif
#endif


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_displacement_micromap 1

#define VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#define VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    ଶୂନ୍ୟ*                               pNext;
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
    uint32_t                            usage_Counts_ଗଣନା;
    ଅଚଳ VkMicromapUsageEXT*           pUsageCounts;
    ଅଚଳ VkMicromapUsageEXT* ଅଚଳ*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#define VK_AMDX_dense_geometry_format 1

#define VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#define VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#define VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX {
    VkStructureType                   sType;
    ଅଚଳ ଶୂନ୍ୟ*                       pNext;
    VkDeviceOrHostAddressConstKHR     compressedData;
    VkDeviceSize                      dataSize;
    uint32_t                          ଅଙ୍କ_Triangles;
    uint32_t                          ଅଙ୍କ_Vertices;
    uint32_t                          maxPrimitiveIndex;
    uint32_t                          maxGeometryIndex;
    VkCompressedTriangleFormatAMDX    format;
} VkAccelerationStructureDenseGeometryFormatTrianglesDataAMDX;


#ifdef __cplusplus
}
#endif

#endif

#अगर_अघोषित VULKAN_BETA_H_
#घोषणा VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_portability_subset 1

#घोषणा VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION 1
#घोषणा VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

प्रकार काष्ठा VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    व्योम*              p_अग्र;
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

प्रकार काष्ठा VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           min_Vertex_निवेश_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_AMDX_shader_enqueue 1

#घोषणा VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION 2
#घोषणा VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#घोषणा VK_SHADER_सूचकांक_UNUSED_AMDX       (~0U)

प्रकार काष्ठा VkPhysicalDeviceShaderEnqueueFeaturesAMDX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           shaderEnqueue;
    VkBool32           shaderMeshEnqueue;
} VkPhysicalDeviceShaderEnqueueFeaturesAMDX;

प्रकार काष्ठा VkPhysicalDeviceShaderEnqueuePropertiesAMDX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           maxExecutionGraphDepth;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           max_Execution_Graph_Shader_Payload_आकार;
    uint32_t           max_Execution_Graph_Shader_Payload_गिनती;
    uint32_t           executionGraphDispatchAddressAlignment;
    uint32_t           max_Execution_Graph_Workgroup_गिनती[3];
    uint32_t           maxExecutionGraphWorkgroups;
} VkPhysicalDeviceShaderEnqueuePropertiesAMDX;

प्रकार काष्ठा Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    Vk_Device_आकार       min_आकार;
    Vk_Device_आकार       max_आकार_2;
    Vk_Device_आकार       आकार_Granularity;
} Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX;

प्रकार काष्ठा VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    स्थिर व्योम*                               p_अग्र;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_गिनती;
    स्थिर VkPipelineShaderStageCreateInfo*    pStages;
    स्थिर VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                basePipelineHandle;
    int32_t                                   base_Pipeline_सूचकांक;
} VkExecutionGraphPipelineCreateInfoAMDX;

प्रकार जोड़ VkDeviceOrHostAddressConstAMDX {
    VkDeviceAddress    deviceAddress;
    स्थिर व्योम*        hostAddress;
} VkDeviceOrHostAddressConstAMDX;

प्रकार काष्ठा VkDispatchGraphInfoAMDX {
    uint32_t                          गाँठ_सूचकांक_2;
    uint32_t                          payload_गिनती;
    VkDeviceOrHostAddressConstAMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

प्रकार काष्ठा Vk_Dispatch_Graph_गिनती_Info_AMDX {
    uint32_t                          गिनती;
    VkDeviceOrHostAddressConstAMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_गिनती_Info_AMDX;

प्रकार काष्ठा Vk_Pipeline_Shader_Stage_गाँठ_Create_Info_AMDX {
      VkStructureType    sType;
    स्थिर व्योम*          p_अग्र;
    स्थिर अक्षर*          pName;
    uint32_t             सूचकांक;
} Vk_Pipeline_Shader_Stage_गाँठ_Create_Info_AMDX;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_गिनती, स्थिर VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, स्थिर VkAllocationCallbacks*    pAllocator, VkPipeline*               pPipelines);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_Scratch_आकार_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX*        p_आकार_Info);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_गाँठ_सूचकांक_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, स्थिर Vk_Pipeline_Shader_Stage_गाँठ_Create_Info_AMDX*  p_गाँठ_Info, uint32_t*                                       p_गाँठ_सूचकांक);
प्रकार व्योम (VKAPI_PTR *PFN_vkCmdInitializeGraphScratchMemoryAMDX)(Vk_Command_बफर                                 command_बफर, VkPipeline                                      executionGraph, VkDeviceAddress                                 scratch, Vk_Device_आकार                                    scratch_आकार);
प्रकार व्योम (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(Vk_Command_बफर                                 command_बफर, VkDeviceAddress                                 scratch, Vk_Device_आकार                                    scratch_आकार, स्थिर Vk_Dispatch_Graph_गिनती_Info_AMDX*             p_गिनती_Info);
प्रकार व्योम (VKAPI_PTR *PFN_vkCmdDispatchGraphIndirectAMDX)(Vk_Command_बफर                                 command_बफर, VkDeviceAddress                                 scratch, Vk_Device_आकार                                    scratch_आकार, स्थिर Vk_Dispatch_Graph_गिनती_Info_AMDX*             p_गिनती_Info);
प्रकार व्योम (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_Indirect_गिनती_AMDX)(Vk_Command_बफर                                 command_बफर, VkDeviceAddress                                 scratch, Vk_Device_आकार                                    scratch_आकार, VkDeviceAddress                                 गिनती_Info);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_गिनती,
    स्थिर VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Execution_Graph_Pipeline_Scratch_आकार_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX*    p_आकार_Info);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Execution_Graph_Pipeline_गाँठ_सूचकांक_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    स्थिर Vk_Pipeline_Shader_Stage_गाँठ_Create_Info_AMDX* p_गाँठ_Info,
    uint32_t*                                   p_गाँठ_सूचकांक);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkCmdInitializeGraphScratchMemoryAMDX(
    Vk_Command_बफर                             command_बफर,
    VkPipeline                                  executionGraph,
    VkDeviceAddress                             scratch,
    Vk_Device_आकार                                scratch_आकार);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkCmdDispatchGraphAMDX(
    Vk_Command_बफर                             command_बफर,
    VkDeviceAddress                             scratch,
    Vk_Device_आकार                                scratch_आकार,
    स्थिर Vk_Dispatch_Graph_गिनती_Info_AMDX*         p_गिनती_Info);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkCmdDispatchGraphIndirectAMDX(
    Vk_Command_बफर                             command_बफर,
    VkDeviceAddress                             scratch,
    Vk_Device_आकार                                scratch_आकार,
    स्थिर Vk_Dispatch_Graph_गिनती_Info_AMDX*         p_गिनती_Info);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vk_Cmd_Dispatch_Graph_Indirect_गिनती_AMDX(
    Vk_Command_बफर                             command_बफर,
    VkDeviceAddress                             scratch,
    Vk_Device_आकार                                scratch_आकार,
    VkDeviceAddress                             गिनती_Info);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#घोषणा VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION 2
#घोषणा VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

प्रकार काष्ठा VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    माप_प्रकार             तथ्य_आकार_2;
    स्थिर व्योम*        p_तथ्य;
} VkCudaModuleCreateInfoNV;

प्रकार काष्ठा VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    VkCudaModuleNV     module;
    स्थिर अक्षर*        pName;
} VkCudaFunctionCreateInfoNV;

प्रकार काष्ठा VkCudaLaunchInfoNV {
    VkStructureType        sType;
    स्थिर व्योम*            p_अग्र;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               blockDimX;
    uint32_t               blockDimY;
    uint32_t               blockDimZ;
    uint32_t               sharedMemBytes;
    माप_प्रकार                 param_गिनती;
    स्थिर व्योम* स्थिर *    pParams;
    माप_प्रकार                 extra_गिनती;
    स्थिर व्योम* स्थिर *    pExtras;
} VkCudaLaunchInfoNV;

प्रकार काष्ठा VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

प्रकार काष्ठा VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, स्थिर VkCudaModuleCreateInfoNV* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkCudaModuleNV* pModule);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, माप_प्रकार* p_Cache_आकार, व्योम* p_Cache_तथ्य);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, स्थिर VkCudaFunctionCreateInfoNV* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkCudaFunctionNV* pFunction);
प्रकार व्योम (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, स्थिर VkAllocationCallbacks* pAllocator);
प्रकार व्योम (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, स्थिर VkAllocationCallbacks* pAllocator);
प्रकार व्योम (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_बफर command_बफर, स्थिर VkCudaLaunchInfoNV* pLaunchInfo);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    स्थिर VkCudaModuleCreateInfoNV*             pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    माप_प्रकार*                                     p_Cache_आकार,
    व्योम*                                       p_Cache_तथ्य);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    स्थिर VkCudaFunctionCreateInfoNV*           pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    स्थिर VkAllocationCallbacks*                pAllocator);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    स्थिर VkAllocationCallbacks*                pAllocator);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_बफर                             command_बफर,
    स्थिर VkCudaLaunchInfoNV*                   pLaunchInfo);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_NV_displacement_micromap 1

#घोषणा VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION 2
#घोषणा VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

प्रकार क्रमागत VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_BYTES_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_BYTES_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_BYTES_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

प्रकार काष्ठा VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

प्रकार काष्ठा VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

प्रकार काष्ठा VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    व्योम*                               p_अग्र;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacementVectorFormat;
    VkDeviceOrHostAddressConstKHR       displacement_Bias_And_Scale_बफर;
    Vk_Device_आकार                        displacementBiasAndScaleStride;
    VkDeviceOrHostAddressConstKHR       displacement_Vector_बफर;
    Vk_Device_आकार                        displacementVectorStride;
    VkDeviceOrHostAddressConstKHR       displacedMicromapPrimitiveFlags;
    Vk_Device_आकार                        displacedMicromapPrimitiveFlagsStride;
    Vk_सूचकांक_Type                         सूचकांक_Type;
    VkDeviceOrHostAddressConstKHR       सूचकांक_बफर_2;
    Vk_Device_आकार                        सूचकांक_Stride;
    uint32_t                            baseTriangle;
    uint32_t                            usage_Counts_गिनती;
    स्थिर VkMicromapUsageEXT*           pUsageCounts;
    स्थिर VkMicromapUsageEXT* स्थिर*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_AMDX_dense_geometry_format 1

#घोषणा VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION 1
#घोषणा VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#घोषणा VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#घोषणा VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

प्रकार क्रमागत VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

प्रकार काष्ठा VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

प्रकार काष्ठा Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_तथ्य_AMDX {
    VkStructureType                   sType;
    स्थिर व्योम*                       p_अग्र;
    VkDeviceOrHostAddressConstKHR     compressed_तथ्य;
    Vk_Device_आकार                      तथ्य_आकार_2;
    uint32_t                          अंक_Triangles;
    uint32_t                          अंक_Vertices;
    uint32_t                          max_Primitive_सूचकांक;
    uint32_t                          max_Geometry_सूचकांक;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_तथ्य_AMDX;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

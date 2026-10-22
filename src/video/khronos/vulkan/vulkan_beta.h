#यदि_अपरिभाषितम् VULKAN_BETA_H_
#परिभाषय VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_portability_subset 1

#परिभाषय VK_KHR_PORTABILITY_SUBSET_SPEC_संस्करणम् 1
#परिभाषय VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

प्रकारनिर्देश संरचना VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           pointPolygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_आवरणम्_Ref;
    VkBool32           shader_Sample_दरः_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_Point_बहुलकम्;
    VkBool32           triangleFans;
    VkBool32           vertexAttributeAccessBeyondStride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

प्रकारनिर्देश संरचना VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           min_Vertex_निवेशः_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_AMDX_shader_पङ्क्तौ_निक्षिप 1

#परिभाषय VK_AMDX_SHADER_पङ्क्तौ_निक्षिप_SPEC_संस्करणम् 2
#परिभाषय VK_AMDX_SHADER_पङ्क्तौ_निक्षिप_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#परिभाषय VK_SHADER_सूचकांक_अप्रयुक्तम्_AMDX       (~0U)

प्रकारनिर्देश संरचना Vk_Physical_Device_Shader_पङ्क्तौ_निक्षिप_Features_AMDX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           shader_पङ्क्तौ_निक्षिप;
    VkBool32           shader_Mesh_पङ्क्तौ_निक्षिप;
} Vk_Physical_Device_Shader_पङ्क्तौ_निक्षिप_Features_AMDX;

प्रकारनिर्देश संरचना Vk_Physical_Device_Shader_पङ्क्तौ_निक्षिप_Properties_AMDX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           max_Execution_Graph_गभीरता;
    uint32_t           maxExecutionGraphShaderOutputNodes;
    uint32_t           max_Execution_Graph_Shader_Payload_आकार;
    uint32_t           max_Execution_Graph_Shader_Payload_गणनम्;
    uint32_t           execution_Graph_Dispatch_स्थानाङ्कः_Alignment;
    uint32_t           max_Execution_Graph_Workgroup_गणनम्[3];
    uint32_t           maxExecutionGraphWorkgroups;
} Vk_Physical_Device_Shader_पङ्क्तौ_निक्षिप_Properties_AMDX;

प्रकारनिर्देश संरचना Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    Vk_Device_आकार       min_आकार;
    Vk_Device_आकार       max_आकार_2;
    Vk_Device_आकार       आकार_Granularity;
} Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX;

प्रकारनिर्देश संरचना VkExecutionGraphPipelineCreateInfoAMDX {
    VkStructureType                           sType;
    ध्रुव शून्य*                               p_अग्र;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_गणनम्;
    ध्रुव VkPipelineShaderStageCreateInfo*    pStages;
    ध्रुव VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                आधारः_Pipeline_Handle;
    int32_t                                   आधारः_Pipeline_सूचकांक;
} VkExecutionGraphPipelineCreateInfoAMDX;

प्रकारनिर्देश सङ्घ Vk_Device_Or_Host_स्थानाङ्कः_Const_AMDX {
    Vk_Device_स्थानाङ्कः    device_स्थानाङ्कः;
    ध्रुव शून्य*        host_स्थानाङ्कः;
} Vk_Device_Or_Host_स्थानाङ्कः_Const_AMDX;

प्रकारनिर्देश संरचना VkDispatchGraphInfoAMDX {
    uint32_t                          ग्रन्थिः_सूचकांक_2;
    uint32_t                          payload_गणनम्;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} VkDispatchGraphInfoAMDX;

प्रकारनिर्देश संरचना Vk_Dispatch_Graph_गणनम्_Info_AMDX {
    uint32_t                          गणनम्;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_Graph_गणनम्_Info_AMDX;

प्रकारनिर्देश संरचना Vk_Pipeline_Shader_Stage_ग्रन्थिः_Create_Info_AMDX {
      VkStructureType    sType;
    ध्रुव शून्य*          p_अग्र;
    ध्रुव वर्ण*          pName;
    uint32_t             सूचकांक;
} Vk_Pipeline_Shader_Stage_ग्रन्थिः_Create_Info_AMDX;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateExecutionGraphPipelinesAMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_गणनम्, ध्रुव VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos, ध्रुव Vk_आवण्टनम्_Callbacks*    pAllocator, VkPipeline*               pPipelines);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_Scratch_आकार_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX*        p_आकार_Info);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Execution_Graph_Pipeline_ग्रन्थिः_सूचकांक_AMDX)(VkDevice                                        device, VkPipeline                                      executionGraph, ध्रुव Vk_Pipeline_Shader_Stage_ग्रन्थिः_Create_Info_AMDX*  p_ग्रन्थिः_Info, uint32_t*                                       p_ग्रन्थिः_सूचकांक);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vk_Cmd_Initialize_Graph_Scratch_स्मृतिः_AMDX)(Vk_Command_बफर                                 command_बफर, VkPipeline                                      executionGraph, Vk_Device_स्थानाङ्कः                                 scratch, Vk_Device_आकार                                    scratch_आकार);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkCmdDispatchGraphAMDX)(Vk_Command_बफर                                 command_बफर, Vk_Device_स्थानाङ्कः                                 scratch, Vk_Device_आकार                                    scratch_आकार, ध्रुव Vk_Dispatch_Graph_गणनम्_Info_AMDX*             p_गणनम्_Info);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_परोक्षम्_AMDX)(Vk_Command_बफर                                 command_बफर, Vk_Device_स्थानाङ्कः                                 scratch, Vk_Device_आकार                                    scratch_आकार, ध्रुव Vk_Dispatch_Graph_गणनम्_Info_AMDX*             p_गणनम्_Info);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vk_Cmd_Dispatch_Graph_परोक्षम्_गणनम्_AMDX)(Vk_Command_बफर                                 command_बफर, Vk_Device_स्थानाङ्कः                                 scratch, Vk_Device_आकार                                    scratch_आकार, Vk_Device_स्थानाङ्कः                                 गणनम्_Info);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateExecutionGraphPipelinesAMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_गणनम्,
    ध्रुव VkExecutionGraphPipelineCreateInfoAMDX* pCreateInfos,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Execution_Graph_Pipeline_Scratch_आकार_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    Vk_Execution_Graph_Pipeline_Scratch_आकार_AMDX*    p_आकार_Info);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Execution_Graph_Pipeline_ग्रन्थिः_सूचकांक_AMDX(
    VkDevice                                    device,
    VkPipeline                                  executionGraph,
    ध्रुव Vk_Pipeline_Shader_Stage_ग्रन्थिः_Create_Info_AMDX* p_ग्रन्थिः_Info,
    uint32_t*                                   p_ग्रन्थिः_सूचकांक);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vk_Cmd_Initialize_Graph_Scratch_स्मृतिः_AMDX(
    Vk_Command_बफर                             command_बफर,
    VkPipeline                                  executionGraph,
    Vk_Device_स्थानाङ्कः                             scratch,
    Vk_Device_आकार                                scratch_आकार);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdDispatchGraphAMDX(
    Vk_Command_बफर                             command_बफर,
    Vk_Device_स्थानाङ्कः                             scratch,
    Vk_Device_आकार                                scratch_आकार,
    ध्रुव Vk_Dispatch_Graph_गणनम्_Info_AMDX*         p_गणनम्_Info);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vk_Cmd_Dispatch_Graph_परोक्षम्_AMDX(
    Vk_Command_बफर                             command_बफर,
    Vk_Device_स्थानाङ्कः                             scratch,
    Vk_Device_आकार                                scratch_आकार,
    ध्रुव Vk_Dispatch_Graph_गणनम्_Info_AMDX*         p_गणनम्_Info);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vk_Cmd_Dispatch_Graph_परोक्षम्_गणनम्_AMDX(
    Vk_Command_बफर                             command_बफर,
    Vk_Device_स्थानाङ्कः                             scratch,
    Vk_Device_आकार                                scratch_आकार,
    Vk_Device_स्थानाङ्कः                             गणनम्_Info);
#यदि_अन्तः
#यदि_अन्तः


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#परिभाषय VK_NV_CUDA_KERNEL_LAUNCH_SPEC_संस्करणम् 2
#परिभाषय VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

प्रकारनिर्देश संरचना VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    size_t             दत्त_आकार_2;
    ध्रुव शून्य*        p_दत्त;
} VkCudaModuleCreateInfoNV;

प्रकारनिर्देश संरचना VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    VkCudaModuleNV     module;
    ध्रुव वर्ण*        pName;
} VkCudaFunctionCreateInfoNV;

प्रकारनिर्देश संरचना VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ध्रुव शून्य*            p_अग्र;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               खण्डम्_Dim_X;
    uint32_t               खण्डम्_Dim_Y;
    uint32_t               खण्डम्_Dim_Z;
    uint32_t               shared_Mem_अष्टकानि;
    size_t                 param_गणनम्;
    ध्रुव शून्य* ध्रुव *    pParams;
    size_t                 extra_गणनम्;
    ध्रुव शून्य* ध्रुव *    pExtras;
} VkCudaLaunchInfoNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ध्रुव VkCudaModuleCreateInfoNV* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkCudaModuleNV* pModule);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_आकार, शून्य* p_Cache_दत्त);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ध्रुव VkCudaFunctionCreateInfoNV* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_बफर command_बफर, ध्रुव VkCudaLaunchInfoNV* pLaunchInfo);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ध्रुव VkCudaModuleCreateInfoNV*             pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_आकार,
    शून्य*                                       p_Cache_दत्त);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ध्रुव VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_बफर                             command_बफर,
    ध्रुव VkCudaLaunchInfoNV*                   pLaunchInfo);
#यदि_अन्तः
#यदि_अन्तः


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_NV_displacement_micromap 1

#परिभाषय VK_NV_DISPLACEMENT_MICROMAP_SPEC_संस्करणम् 2
#परिभाषय VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

प्रकारनिर्देश गणना VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_अष्टकानि_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_अष्टकानि_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_अष्टकानि_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

प्रकारनिर्देश संरचना VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

प्रकारनिर्देश संरचना VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    शून्य*                               p_अग्र;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_सदिशम्_Format;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_KHR       displacement_Bias_And_Scale_बफर;
    Vk_Device_आकार                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_KHR       displacement_सदिशम्_बफर;
    Vk_Device_आकार                        displacement_सदिशम्_Stride;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_आकार                        displacedMicromapPrimitiveFlagsStride;
    Vk_सूचकांक_Type                         सूचकांक_Type;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_KHR       सूचकांक_बफर_2;
    Vk_Device_आकार                        सूचकांक_Stride;
    uint32_t                            आधारः_Triangle;
    uint32_t                            usage_Counts_गणनम्;
    ध्रुव VkMicromapUsageEXT*           pUsageCounts;
    ध्रुव VkMicromapUsageEXT* ध्रुव*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_AMDX_dense_geometry_format 1

#परिभाषय VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_संस्करणम् 1
#परिभाषय VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#परिभाषय VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#परिभाषय VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

प्रकारनिर्देश गणना VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

प्रकारनिर्देश संरचना VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

प्रकारनिर्देश संरचना Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_दत्त_AMDX {
    VkStructureType                   sType;
    ध्रुव शून्य*                       p_अग्र;
    Vk_Device_Or_Host_स्थानाङ्कः_Const_KHR     compressed_दत्त;
    Vk_Device_आकार                      दत्त_आकार_2;
    uint32_t                          अङ्कः_Triangles;
    uint32_t                          अङ्कः_Vertices;
    uint32_t                          max_Primitive_सूचकांक;
    uint32_t                          max_Geometry_सूचकांक;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_दत्त_AMDX;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः

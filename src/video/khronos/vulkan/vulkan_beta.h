#నిర్వచితం_కాకపోతే VULKAN_BETA_H_
#నిర్వచించు VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_portability_subset 1

#నిర్వచించు VK_KHR_PORTABILITY_SUBSET_SPEC_సంస్కరణ 1
#నిర్వచించు VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

రకనిర్వచనం నిర్మాణం VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           బిందువు_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_ముసుగు_Ref;
    VkBool32           shader_Sample_రేటు_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_బిందువు_బహుళకం;
    VkBool32           triangleFans;
    VkBool32           శీర్షం_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

రకనిర్వచనం నిర్మాణం VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           min_శీర్షం_ఆదానం_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_AMDX_shader_వరుసలో_చేర్చు 1

#నిర్వచించు VK_AMDX_SHADER_వరుసలో_చేర్చు_SPEC_సంస్కరణ 2
#నిర్వచించు VK_AMDX_SHADER_వరుసలో_చేర్చు_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#నిర్వచించు VK_SHADER_సూచీ_వాడని_AMDX       (~0U)

రకనిర్వచనం నిర్మాణం Vk_Physical_Device_Shader_వరుసలో_చేర్చు_Features_AMDX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           shader_వరుసలో_చేర్చు;
    VkBool32           shader_Mesh_వరుసలో_చేర్చు;
} Vk_Physical_Device_Shader_వరుసలో_చేర్చు_Features_AMDX;

రకనిర్వచనం నిర్మాణం Vk_Physical_Device_Shader_వరుసలో_చేర్చు_Properties_AMDX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           max_Execution_లేఖాచిత్రం_లోతు;
    uint32_t           max_Execution_లేఖాచిత్రం_Shader_Output_Nodes;
    uint32_t           max_Execution_లేఖాచిత్రం_Shader_Payload_కొలత;
    uint32_t           max_Execution_లేఖాచిత్రం_Shader_Payload_లెక్క;
    uint32_t           execution_లేఖాచిత్రం_Dispatch_చిరునామా_Alignment;
    uint32_t           max_Execution_లేఖాచిత్రం_Workgroup_లెక్క[3];
    uint32_t           max_Execution_లేఖాచిత్రం_Workgroups;
} Vk_Physical_Device_Shader_వరుసలో_చేర్చు_Properties_AMDX;

రకనిర్వచనం నిర్మాణం Vk_Execution_లేఖాచిత్రం_Pipeline_Scratch_కొలత_AMDX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    Vk_Device_కొలత       min_కొలత;
    Vk_Device_కొలత       max_కొలత_2;
    Vk_Device_కొలత       కొలత_Granularity;
} Vk_Execution_లేఖాచిత్రం_Pipeline_Scratch_కొలత_AMDX;

రకనిర్వచనం నిర్మాణం Vk_Execution_లేఖాచిత్రం_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    స్థిరరాశి శూన్య*                               p_తదుపరి;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_లెక్క;
    స్థిరరాశి VkPipelineShaderStageCreateInfo*    pStages;
    స్థిరరాశి VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                పునాది_Pipeline_Handle;
    int32_t                                   పునాది_Pipeline_సూచీ;
} Vk_Execution_లేఖాచిత్రం_Pipeline_Create_Info_AMDX;

రకనిర్వచనం సంఘం Vk_Device_Or_Host_చిరునామా_Const_AMDX {
    Vk_Device_చిరునామా    device_చిరునామా;
    స్థిరరాశి శూన్య*        host_చిరునామా;
} Vk_Device_Or_Host_చిరునామా_Const_AMDX;

రకనిర్వచనం నిర్మాణం Vk_Dispatch_లేఖాచిత్రం_Info_AMDX {
    uint32_t                          కణుపు_సూచీ_2;
    uint32_t                          payload_లెక్క;
    Vk_Device_Or_Host_చిరునామా_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_లేఖాచిత్రం_Info_AMDX;

రకనిర్వచనం నిర్మాణం Vk_Dispatch_లేఖాచిత్రం_లెక్క_Info_AMDX {
    uint32_t                          లెక్క;
    Vk_Device_Or_Host_చిరునామా_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_లేఖాచిత్రం_లెక్క_Info_AMDX;

రకనిర్వచనం నిర్మాణం Vk_Pipeline_Shader_Stage_కణుపు_Create_Info_AMDX {
      VkStructureType    sType;
    స్థిరరాశి శూన్య*          p_తదుపరి;
    స్థిరరాశి అక్షరం*          pName;
    uint32_t             సూచీ;
} Vk_Pipeline_Shader_Stage_కణుపు_Create_Info_AMDX;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Create_Execution_లేఖాచిత్రం_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_లెక్క, స్థిరరాశి Vk_Execution_లేఖాచిత్రం_Pipeline_Create_Info_AMDX* pCreateInfos, స్థిరరాశి Vk_కేటాయింపు_Callbacks*    pAllocator, VkPipeline*               pPipelines);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_Execution_లేఖాచిత్రం_Pipeline_Scratch_కొలత_AMDX)(VkDevice                                        device, VkPipeline                                      execution_లేఖాచిత్రం, Vk_Execution_లేఖాచిత్రం_Pipeline_Scratch_కొలత_AMDX*        p_కొలత_Info);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_Execution_లేఖాచిత్రం_Pipeline_కణుపు_సూచీ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_లేఖాచిత్రం, స్థిరరాశి Vk_Pipeline_Shader_Stage_కణుపు_Create_Info_AMDX*  p_కణుపు_Info, uint32_t*                                       p_కణుపు_సూచీ);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vk_Cmd_Initialize_లేఖాచిత్రం_Scratch_జ్ఞాపకం_AMDX)(Vk_Command_బఫరు                                 command_బఫరు, VkPipeline                                      execution_లేఖాచిత్రం, Vk_Device_చిరునామా                                 scratch, Vk_Device_కొలత                                    scratch_కొలత);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vk_Cmd_Dispatch_లేఖాచిత్రం_AMDX)(Vk_Command_బఫరు                                 command_బఫరు, Vk_Device_చిరునామా                                 scratch, Vk_Device_కొలత                                    scratch_కొలత, స్థిరరాశి Vk_Dispatch_లేఖాచిత్రం_లెక్క_Info_AMDX*             p_లెక్క_Info);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vk_Cmd_Dispatch_లేఖాచిత్రం_పరోక్ష_AMDX)(Vk_Command_బఫరు                                 command_బఫరు, Vk_Device_చిరునామా                                 scratch, Vk_Device_కొలత                                    scratch_కొలత, స్థిరరాశి Vk_Dispatch_లేఖాచిత్రం_లెక్క_Info_AMDX*             p_లెక్క_Info);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vk_Cmd_Dispatch_లేఖాచిత్రం_పరోక్ష_లెక్క_AMDX)(Vk_Command_బఫరు                                 command_బఫరు, Vk_Device_చిరునామా                                 scratch, Vk_Device_కొలత                                    scratch_కొలత, Vk_Device_చిరునామా                                 లెక్క_Info);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Create_Execution_లేఖాచిత్రం_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_లెక్క,
    స్థిరరాశి Vk_Execution_లేఖాచిత్రం_Pipeline_Create_Info_AMDX* pCreateInfos,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_Execution_లేఖాచిత్రం_Pipeline_Scratch_కొలత_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_లేఖాచిత్రం,
    Vk_Execution_లేఖాచిత్రం_Pipeline_Scratch_కొలత_AMDX*    p_కొలత_Info);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_Execution_లేఖాచిత్రం_Pipeline_కణుపు_సూచీ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_లేఖాచిత్రం,
    స్థిరరాశి Vk_Pipeline_Shader_Stage_కణుపు_Create_Info_AMDX* p_కణుపు_Info,
    uint32_t*                                   p_కణుపు_సూచీ);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vk_Cmd_Initialize_లేఖాచిత్రం_Scratch_జ్ఞాపకం_AMDX(
    Vk_Command_బఫరు                             command_బఫరు,
    VkPipeline                                  execution_లేఖాచిత్రం,
    Vk_Device_చిరునామా                             scratch,
    Vk_Device_కొలత                                scratch_కొలత);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vk_Cmd_Dispatch_లేఖాచిత్రం_AMDX(
    Vk_Command_బఫరు                             command_బఫరు,
    Vk_Device_చిరునామా                             scratch,
    Vk_Device_కొలత                                scratch_కొలత,
    స్థిరరాశి Vk_Dispatch_లేఖాచిత్రం_లెక్క_Info_AMDX*         p_లెక్క_Info);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vk_Cmd_Dispatch_లేఖాచిత్రం_పరోక్ష_AMDX(
    Vk_Command_బఫరు                             command_బఫరు,
    Vk_Device_చిరునామా                             scratch,
    Vk_Device_కొలత                                scratch_కొలత,
    స్థిరరాశి Vk_Dispatch_లేఖాచిత్రం_లెక్క_Info_AMDX*         p_లెక్క_Info);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vk_Cmd_Dispatch_లేఖాచిత్రం_పరోక్ష_లెక్క_AMDX(
    Vk_Command_బఫరు                             command_బఫరు,
    Vk_Device_చిరునామా                             scratch,
    Vk_Device_కొలత                                scratch_కొలత,
    Vk_Device_చిరునామా                             లెక్క_Info);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#నిర్వచించు VK_NV_CUDA_KERNEL_LAUNCH_SPEC_సంస్కరణ 2
#నిర్వచించు VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

రకనిర్వచనం నిర్మాణం VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    size_t             దత్తాంశం_కొలత_2;
    స్థిరరాశి శూన్య*        p_దత్తాంశం;
} VkCudaModuleCreateInfoNV;

రకనిర్వచనం నిర్మాణం VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    VkCudaModuleNV     module;
    స్థిరరాశి అక్షరం*        pName;
} VkCudaFunctionCreateInfoNV;

రకనిర్వచనం నిర్మాణం VkCudaLaunchInfoNV {
    VkStructureType        sType;
    స్థిరరాశి శూన్య*            p_తదుపరి;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               ఖండం_Dim_X;
    uint32_t               ఖండం_Dim_Y;
    uint32_t               ఖండం_Dim_Z;
    uint32_t               shared_Mem_బైట్లు;
    size_t                 param_లెక్క;
    స్థిరరాశి శూన్య* స్థిరరాశి *    pParams;
    size_t                 extra_లెక్క;
    స్థిరరాశి శూన్య* స్థిరరాశి *    pExtras;
} VkCudaLaunchInfoNV;

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, స్థిరరాశి VkCudaModuleCreateInfoNV* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkCudaModuleNV* pModule);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_కొలత, శూన్య* p_Cache_దత్తాంశం);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, స్థిరరాశి VkCudaFunctionCreateInfoNV* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_బఫరు command_బఫరు, స్థిరరాశి VkCudaLaunchInfoNV* pLaunchInfo);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    స్థిరరాశి VkCudaModuleCreateInfoNV*             pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_కొలత,
    శూన్య*                                       p_Cache_దత్తాంశం);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    స్థిరరాశి VkCudaFunctionCreateInfoNV*           pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_బఫరు                             command_బఫరు,
    స్థిరరాశి VkCudaLaunchInfoNV*                   pLaunchInfo);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_NV_displacement_micromap 1

#నిర్వచించు VK_NV_DISPLACEMENT_MICROMAP_SPEC_సంస్కరణ 2
#నిర్వచించు VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

రకనిర్వచనం గణన VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_బైట్లు_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_బైట్లు_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_బైట్లు_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

రకనిర్వచనం నిర్మాణం VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    శూన్య*                               p_తదుపరి;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_సదిశ_Format;
    Vk_Device_Or_Host_చిరునామా_Const_KHR       displacement_Bias_And_Scale_బఫరు;
    Vk_Device_కొలత                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_చిరునామా_Const_KHR       displacement_సదిశ_బఫరు;
    Vk_Device_కొలత                        displacement_సదిశ_Stride;
    Vk_Device_Or_Host_చిరునామా_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_కొలత                        displacedMicromapPrimitiveFlagsStride;
    Vk_సూచీ_Type                         సూచీ_Type;
    Vk_Device_Or_Host_చిరునామా_Const_KHR       సూచీ_బఫరు_2;
    Vk_Device_కొలత                        సూచీ_Stride;
    uint32_t                            పునాది_Triangle;
    uint32_t                            usage_Counts_లెక్క;
    స్థిరరాశి VkMicromapUsageEXT*           pUsageCounts;
    స్థిరరాశి VkMicromapUsageEXT* స్థిరరాశి*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_AMDX_dense_geometry_format 1

#నిర్వచించు VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_సంస్కరణ 1
#నిర్వచించు VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#నిర్వచించు VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#నిర్వచించు VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

రకనిర్వచనం గణన VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

రకనిర్వచనం నిర్మాణం VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

రకనిర్వచనం నిర్మాణం Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_దత్తాంశం_AMDX {
    VkStructureType                   sType;
    స్థిరరాశి శూన్య*                       p_తదుపరి;
    Vk_Device_Or_Host_చిరునామా_Const_KHR     compressed_దత్తాంశం;
    Vk_Device_కొలత                      దత్తాంశం_కొలత_2;
    uint32_t                          అంకె_Triangles;
    uint32_t                          అంకె_Vertices;
    uint32_t                          max_Primitive_సూచీ;
    uint32_t                          max_Geometry_సూచీ;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_దత్తాంశం_AMDX;


#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు

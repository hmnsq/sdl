#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_BETA_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_portability_subset 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_PORTABILITY_SUBSET_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           ਬਿੰਦੂ_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_ਨਕਾਬ_Ref;
    VkBool32           shader_Sample_ਦਰ_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_ਬਿੰਦੂ_ਬਹੁਲਕ;
    VkBool32           triangleFans;
    VkBool32           ਸ਼ੀਰਸ਼_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           min_ਸ਼ੀਰਸ਼_ਨਿਵੇਸ਼_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_AMDX_shader_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_AMDX_SHADER_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_SPEC_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_AMDX_SHADER_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_SHADER_ਸੂਚਕਾਂਕ_ਅਣਵਰਤਿਆ_AMDX       (~0U)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Physical_Device_Shader_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Features_AMDX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           shader_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ;
    VkBool32           shader_Mesh_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ;
} Vk_Physical_Device_Shader_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Features_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Physical_Device_Shader_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Properties_AMDX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           max_Execution_ਗ੍ਰਾਫ_ਡੂੰਘਾਈ;
    uint32_t           max_Execution_ਗ੍ਰਾਫ_Shader_Output_Nodes;
    uint32_t           max_Execution_ਗ੍ਰਾਫ_Shader_Payload_ਮਾਪ;
    uint32_t           max_Execution_ਗ੍ਰਾਫ_Shader_Payload_ਗਿਣਤੀ;
    uint32_t           execution_ਗ੍ਰਾਫ_Dispatch_ਪਤਾ_Alignment;
    uint32_t           max_Execution_ਗ੍ਰਾਫ_Workgroup_ਗਿਣਤੀ[3];
    uint32_t           max_Execution_ਗ੍ਰਾਫ_Workgroups;
} Vk_Physical_Device_Shader_ਕਤਾਰ_ਵਿੱਚ_ਪਾਓ_Properties_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Scratch_ਮਾਪ_AMDX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    Vk_Device_ਮਾਪ       min_ਮਾਪ;
    Vk_Device_ਮਾਪ       max_ਮਾਪ_2;
    Vk_Device_ਮਾਪ       ਮਾਪ_Granularity;
} Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Scratch_ਮਾਪ_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ਅਚਲ ਖਾਲੀ*                               p_ਅਗਲਾ;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_ਗਿਣਤੀ;
    ਅਚਲ VkPipelineShaderStageCreateInfo*    pStages;
    ਅਚਲ VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                ਅਧਾਰ_Pipeline_Handle;
    int32_t                                   ਅਧਾਰ_Pipeline_ਸੂਚਕਾਂਕ;
} Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Create_Info_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਸੰਘ Vk_Device_Or_Host_ਪਤਾ_Const_AMDX {
    Vk_Device_ਪਤਾ    device_ਪਤਾ;
    ਅਚਲ ਖਾਲੀ*        host_ਪਤਾ;
} Vk_Device_Or_Host_ਪਤਾ_Const_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Dispatch_ਗ੍ਰਾਫ_Info_AMDX {
    uint32_t                          ਗੰਢ_ਸੂਚਕਾਂਕ_2;
    uint32_t                          payload_ਗਿਣਤੀ;
    Vk_Device_Or_Host_ਪਤਾ_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_ਗ੍ਰਾਫ_Info_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Dispatch_ਗ੍ਰਾਫ_ਗਿਣਤੀ_Info_AMDX {
    uint32_t                          ਗਿਣਤੀ_2;
    Vk_Device_Or_Host_ਪਤਾ_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_ਗ੍ਰਾਫ_ਗਿਣਤੀ_Info_AMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Pipeline_Shader_Stage_ਗੰਢ_Create_Info_AMDX {
      VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*          p_ਅਗਲਾ;
    ਅਚਲ ਅੱਖਰ*          pName;
    uint32_t             ਸੂਚਕਾਂਕ;
} Vk_Pipeline_Shader_Stage_ਗੰਢ_Create_Info_AMDX;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Create_Execution_ਗ੍ਰਾਫ_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_ਗਿਣਤੀ, ਅਚਲ Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Create_Info_AMDX* pCreateInfos, ਅਚਲ Vk_ਵੰਡ_Callbacks*    pAllocator, VkPipeline*               pPipelines);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_Execution_ਗ੍ਰਾਫ_Pipeline_Scratch_ਮਾਪ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_ਗ੍ਰਾਫ, Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Scratch_ਮਾਪ_AMDX*        p_ਮਾਪ_Info);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_Execution_ਗ੍ਰਾਫ_Pipeline_ਗੰਢ_ਸੂਚਕਾਂਕ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_ਗ੍ਰਾਫ, ਅਚਲ Vk_Pipeline_Shader_Stage_ਗੰਢ_Create_Info_AMDX*  p_ਗੰਢ_Info, uint32_t*                                       p_ਗੰਢ_ਸੂਚਕਾਂਕ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vk_Cmd_Initialize_ਗ੍ਰਾਫ_Scratch_ਸਮ੍ਰਿਤੀ_AMDX)(Vk_Command_ਬਫਰ                                 command_ਬਫਰ, VkPipeline                                      execution_ਗ੍ਰਾਫ, Vk_Device_ਪਤਾ                                 scratch, Vk_Device_ਮਾਪ                                    scratch_ਮਾਪ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ਗ੍ਰਾਫ_AMDX)(Vk_Command_ਬਫਰ                                 command_ਬਫਰ, Vk_Device_ਪਤਾ                                 scratch, Vk_Device_ਮਾਪ                                    scratch_ਮਾਪ, ਅਚਲ Vk_Dispatch_ਗ੍ਰਾਫ_ਗਿਣਤੀ_Info_AMDX*             p_ਗਿਣਤੀ_Info);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ਗ੍ਰਾਫ_ਅਸਿੱਧਾ_AMDX)(Vk_Command_ਬਫਰ                                 command_ਬਫਰ, Vk_Device_ਪਤਾ                                 scratch, Vk_Device_ਮਾਪ                                    scratch_ਮਾਪ, ਅਚਲ Vk_Dispatch_ਗ੍ਰਾਫ_ਗਿਣਤੀ_Info_AMDX*             p_ਗਿਣਤੀ_Info);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ਗ੍ਰਾਫ_ਅਸਿੱਧਾ_ਗਿਣਤੀ_AMDX)(Vk_Command_ਬਫਰ                                 command_ਬਫਰ, Vk_Device_ਪਤਾ                                 scratch, Vk_Device_ਮਾਪ                                    scratch_ਮਾਪ, Vk_Device_ਪਤਾ                                 ਗਿਣਤੀ_Info);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Create_Execution_ਗ੍ਰਾਫ_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_ਗਿਣਤੀ,
    ਅਚਲ Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Create_Info_AMDX* pCreateInfos,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_Execution_ਗ੍ਰਾਫ_Pipeline_Scratch_ਮਾਪ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_ਗ੍ਰਾਫ,
    Vk_Execution_ਗ੍ਰਾਫ_Pipeline_Scratch_ਮਾਪ_AMDX*    p_ਮਾਪ_Info);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_Execution_ਗ੍ਰਾਫ_Pipeline_ਗੰਢ_ਸੂਚਕਾਂਕ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_ਗ੍ਰਾਫ,
    ਅਚਲ Vk_Pipeline_Shader_Stage_ਗੰਢ_Create_Info_AMDX* p_ਗੰਢ_Info,
    uint32_t*                                   p_ਗੰਢ_ਸੂਚਕਾਂਕ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vk_Cmd_Initialize_ਗ੍ਰਾਫ_Scratch_ਸਮ੍ਰਿਤੀ_AMDX(
    Vk_Command_ਬਫਰ                             command_ਬਫਰ,
    VkPipeline                                  execution_ਗ੍ਰਾਫ,
    Vk_Device_ਪਤਾ                             scratch,
    Vk_Device_ਮਾਪ                                scratch_ਮਾਪ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vk_Cmd_Dispatch_ਗ੍ਰਾਫ_AMDX(
    Vk_Command_ਬਫਰ                             command_ਬਫਰ,
    Vk_Device_ਪਤਾ                             scratch,
    Vk_Device_ਮਾਪ                                scratch_ਮਾਪ,
    ਅਚਲ Vk_Dispatch_ਗ੍ਰਾਫ_ਗਿਣਤੀ_Info_AMDX*         p_ਗਿਣਤੀ_Info);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vk_Cmd_Dispatch_ਗ੍ਰਾਫ_ਅਸਿੱਧਾ_AMDX(
    Vk_Command_ਬਫਰ                             command_ਬਫਰ,
    Vk_Device_ਪਤਾ                             scratch,
    Vk_Device_ਮਾਪ                                scratch_ਮਾਪ,
    ਅਚਲ Vk_Dispatch_ਗ੍ਰਾਫ_ਗਿਣਤੀ_Info_AMDX*         p_ਗਿਣਤੀ_Info);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vk_Cmd_Dispatch_ਗ੍ਰਾਫ_ਅਸਿੱਧਾ_ਗਿਣਤੀ_AMDX(
    Vk_Command_ਬਫਰ                             command_ਬਫਰ,
    Vk_Device_ਪਤਾ                             scratch,
    Vk_Device_ਮਾਪ                                scratch_ਮਾਪ,
    Vk_Device_ਪਤਾ                             ਗਿਣਤੀ_Info);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_CUDA_KERNEL_LAUNCH_SPEC_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    size_t             ਅੰਕੜੇ_ਮਾਪ_2;
    ਅਚਲ ਖਾਲੀ*        p_ਅੰਕੜੇ;
} VkCudaModuleCreateInfoNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    VkCudaModuleNV     module;
    ਅਚਲ ਅੱਖਰ*        pName;
} VkCudaFunctionCreateInfoNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ਅਚਲ ਖਾਲੀ*            p_ਅਗਲਾ;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               ਖੰਡ_Dim_X;
    uint32_t               ਖੰਡ_Dim_Y;
    uint32_t               ਖੰਡ_Dim_Z;
    uint32_t               shared_Mem_ਬਾਈਟਾਂ;
    size_t                 param_ਗਿਣਤੀ;
    ਅਚਲ ਖਾਲੀ* ਅਚਲ *    pParams;
    size_t                 extra_ਗਿਣਤੀ;
    ਅਚਲ ਖਾਲੀ* ਅਚਲ *    pExtras;
} VkCudaLaunchInfoNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ਅਚਲ VkCudaModuleCreateInfoNV* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkCudaModuleNV* pModule);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_ਮਾਪ, ਖਾਲੀ* p_Cache_ਅੰਕੜੇ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ਅਚਲ VkCudaFunctionCreateInfoNV* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_ਬਫਰ command_ਬਫਰ, ਅਚਲ VkCudaLaunchInfoNV* pLaunchInfo);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ਅਚਲ VkCudaModuleCreateInfoNV*             pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_ਮਾਪ,
    ਖਾਲੀ*                                       p_Cache_ਅੰਕੜੇ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ਅਚਲ VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_ਬਫਰ                             command_ਬਫਰ,
    ਅਚਲ VkCudaLaunchInfoNV*                   pLaunchInfo);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_displacement_micromap 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_DISPLACEMENT_MICROMAP_SPEC_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_ਬਾਈਟਾਂ_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_ਬਾਈਟਾਂ_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_ਬਾਈਟਾਂ_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    ਖਾਲੀ*                               p_ਅਗਲਾ;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_ਸਦਿਸ਼_Format;
    Vk_Device_Or_Host_ਪਤਾ_Const_KHR       displacement_Bias_And_Scale_ਬਫਰ;
    Vk_Device_ਮਾਪ                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_ਪਤਾ_Const_KHR       displacement_ਸਦਿਸ਼_ਬਫਰ;
    Vk_Device_ਮਾਪ                        displacement_ਸਦਿਸ਼_Stride;
    Vk_Device_Or_Host_ਪਤਾ_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_ਮਾਪ                        displacedMicromapPrimitiveFlagsStride;
    Vk_ਸੂਚਕਾਂਕ_Type                         ਸੂਚਕਾਂਕ_Type;
    Vk_Device_Or_Host_ਪਤਾ_Const_KHR       ਸੂਚਕਾਂਕ_ਬਫਰ_2;
    Vk_Device_ਮਾਪ                        ਸੂਚਕਾਂਕ_Stride;
    uint32_t                            ਅਧਾਰ_Triangle;
    uint32_t                            usage_Counts_ਗਿਣਤੀ;
    ਅਚਲ VkMicromapUsageEXT*           pUsageCounts;
    ਅਚਲ VkMicromapUsageEXT* ਅਚਲ*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_AMDX_dense_geometry_format 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_ਅੰਕੜੇ_AMDX {
    VkStructureType                   sType;
    ਅਚਲ ਖਾਲੀ*                       p_ਅਗਲਾ;
    Vk_Device_Or_Host_ਪਤਾ_Const_KHR     compressed_ਅੰਕੜੇ;
    Vk_Device_ਮਾਪ                      ਅੰਕੜੇ_ਮਾਪ_2;
    uint32_t                          ਅੰਕ_Triangles;
    uint32_t                          ਅੰਕ_Vertices;
    uint32_t                          max_Primitive_ਸੂਚਕਾਂਕ;
    uint32_t                          max_Geometry_ਸੂਚਕਾਂਕ;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_ਅੰਕੜੇ_AMDX;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ

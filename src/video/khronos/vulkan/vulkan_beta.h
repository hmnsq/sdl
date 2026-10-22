#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_BETA_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_portability_subset 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_PORTABILITY_SUBSET_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           ಬಿಂದು_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_ಮುಖವಾಡ_Ref;
    VkBool32           shader_Sample_ದರ_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_ಬಿಂದು_ಬಹುಲಕ;
    VkBool32           triangleFans;
    VkBool32           ಶೃಂಗ_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           min_ಶೃಂಗ_ಒಳಹರಿವು_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_AMDX_shader_ಸರತಿಗೆ_ಸೇರಿಸು 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_AMDX_SHADER_ಸರತಿಗೆ_ಸೇರಿಸು_SPEC_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು VK_AMDX_SHADER_ಸರತಿಗೆ_ಸೇರಿಸು_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#ವ್ಯಾಖ್ಯಾನಿಸು VK_SHADER_ಸೂಚ್ಯಂಕ_ಬಳಸದ_AMDX       (~0U)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Physical_Device_Shader_ಸರತಿಗೆ_ಸೇರಿಸು_Features_AMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           shader_ಸರತಿಗೆ_ಸೇರಿಸು;
    VkBool32           shader_Mesh_ಸರತಿಗೆ_ಸೇರಿಸು;
} Vk_Physical_Device_Shader_ಸರತಿಗೆ_ಸೇರಿಸು_Features_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Physical_Device_Shader_ಸರತಿಗೆ_ಸೇರಿಸು_Properties_AMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           max_Execution_ನಕ್ಷೆ_ಆಳ;
    uint32_t           max_Execution_ನಕ್ಷೆ_Shader_Output_Nodes;
    uint32_t           max_Execution_ನಕ್ಷೆ_Shader_Payload_ಗಾತ್ರ;
    uint32_t           max_Execution_ನಕ್ಷೆ_Shader_Payload_ಎಣಿಕೆ;
    uint32_t           execution_ನಕ್ಷೆ_Dispatch_ವಿಳಾಸ_Alignment;
    uint32_t           max_Execution_ನಕ್ಷೆ_Workgroup_ಎಣಿಕೆ[3];
    uint32_t           max_Execution_ನಕ್ಷೆ_Workgroups;
} Vk_Physical_Device_Shader_ಸರತಿಗೆ_ಸೇರಿಸು_Properties_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Execution_ನಕ್ಷೆ_Pipeline_Scratch_ಗಾತ್ರ_AMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    Vk_Device_ಗಾತ್ರ       min_ಗಾತ್ರ;
    Vk_Device_ಗಾತ್ರ       max_ಗಾತ್ರ_2;
    Vk_Device_ಗಾತ್ರ       ಗಾತ್ರ_Granularity;
} Vk_Execution_ನಕ್ಷೆ_Pipeline_Scratch_ಗಾತ್ರ_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Execution_ನಕ್ಷೆ_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                               p_ಮುಂದಿನ;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ VkPipelineShaderStageCreateInfo*    pStages;
    ಸ್ಥಿರಾಂಕ VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                ತಳ_Pipeline_Handle;
    int32_t                                   ತಳ_Pipeline_ಸೂಚ್ಯಂಕ;
} Vk_Execution_ನಕ್ಷೆ_Pipeline_Create_Info_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ Vk_Device_Or_Host_ವಿಳಾಸ_Const_AMDX {
    Vk_Device_ವಿಳಾಸ    device_ವಿಳಾಸ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        host_ವಿಳಾಸ;
} Vk_Device_Or_Host_ವಿಳಾಸ_Const_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Dispatch_ನಕ್ಷೆ_Info_AMDX {
    uint32_t                          ಗಂಟು_ಸೂಚ್ಯಂಕ_2;
    uint32_t                          payload_ಎಣಿಕೆ;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_ನಕ್ಷೆ_Info_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Dispatch_ನಕ್ಷೆ_ಎಣಿಕೆ_Info_AMDX {
    uint32_t                          ಎಣಿಕೆ_2;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_ನಕ್ಷೆ_ಎಣಿಕೆ_Info_AMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX {
      VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*          p_ಮುಂದಿನ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*          pName;
    uint32_t             ಸೂಚ್ಯಂಕ;
} Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Create_Execution_ನಕ್ಷೆ_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_ಎಣಿಕೆ, ಸ್ಥಿರಾಂಕ Vk_Execution_ನಕ್ಷೆ_Pipeline_Create_Info_AMDX* pCreateInfos, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*    pAllocator, VkPipeline*               pPipelines);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_Execution_ನಕ್ಷೆ_Pipeline_Scratch_ಗಾತ್ರ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_ನಕ್ಷೆ, Vk_Execution_ನಕ್ಷೆ_Pipeline_Scratch_ಗಾತ್ರ_AMDX*        p_ಗಾತ್ರ_Info);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_Execution_ನಕ್ಷೆ_Pipeline_ಗಂಟು_ಸೂಚ್ಯಂಕ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_ನಕ್ಷೆ, ಸ್ಥಿರಾಂಕ Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX*  p_ಗಂಟು_Info, uint32_t*                                       p_ಗಂಟು_ಸೂಚ್ಯಂಕ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vk_Cmd_Initialize_ನಕ್ಷೆ_Scratch_ಸ್ಮರಣೆ_AMDX)(Vk_Command_ಬಫರ್                                 command_ಬಫರ್, VkPipeline                                      execution_ನಕ್ಷೆ, Vk_Device_ವಿಳಾಸ                                 scratch, Vk_Device_ಗಾತ್ರ                                    scratch_ಗಾತ್ರ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ನಕ್ಷೆ_AMDX)(Vk_Command_ಬಫರ್                                 command_ಬಫರ್, Vk_Device_ವಿಳಾಸ                                 scratch, Vk_Device_ಗಾತ್ರ                                    scratch_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ Vk_Dispatch_ನಕ್ಷೆ_ಎಣಿಕೆ_Info_AMDX*             p_ಎಣಿಕೆ_Info);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ನಕ್ಷೆ_ಪರೋಕ್ಷ_AMDX)(Vk_Command_ಬಫರ್                                 command_ಬಫರ್, Vk_Device_ವಿಳಾಸ                                 scratch, Vk_Device_ಗಾತ್ರ                                    scratch_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ Vk_Dispatch_ನಕ್ಷೆ_ಎಣಿಕೆ_Info_AMDX*             p_ಎಣಿಕೆ_Info);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ನಕ್ಷೆ_ಪರೋಕ್ಷ_ಎಣಿಕೆ_AMDX)(Vk_Command_ಬಫರ್                                 command_ಬಫರ್, Vk_Device_ವಿಳಾಸ                                 scratch, Vk_Device_ಗಾತ್ರ                                    scratch_ಗಾತ್ರ, Vk_Device_ವಿಳಾಸ                                 ಎಣಿಕೆ_Info);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Create_Execution_ನಕ್ಷೆ_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_ಎಣಿಕೆ,
    ಸ್ಥಿರಾಂಕ Vk_Execution_ನಕ್ಷೆ_Pipeline_Create_Info_AMDX* pCreateInfos,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_Execution_ನಕ್ಷೆ_Pipeline_Scratch_ಗಾತ್ರ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_ನಕ್ಷೆ,
    Vk_Execution_ನಕ್ಷೆ_Pipeline_Scratch_ಗಾತ್ರ_AMDX*    p_ಗಾತ್ರ_Info);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_Execution_ನಕ್ಷೆ_Pipeline_ಗಂಟು_ಸೂಚ್ಯಂಕ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_ನಕ್ಷೆ,
    ಸ್ಥಿರಾಂಕ Vk_Pipeline_Shader_Stage_ಗಂಟು_Create_Info_AMDX* p_ಗಂಟು_Info,
    uint32_t*                                   p_ಗಂಟು_ಸೂಚ್ಯಂಕ);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vk_Cmd_Initialize_ನಕ್ಷೆ_Scratch_ಸ್ಮರಣೆ_AMDX(
    Vk_Command_ಬಫರ್                             command_ಬಫರ್,
    VkPipeline                                  execution_ನಕ್ಷೆ,
    Vk_Device_ವಿಳಾಸ                             scratch,
    Vk_Device_ಗಾತ್ರ                                scratch_ಗಾತ್ರ);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vk_Cmd_Dispatch_ನಕ್ಷೆ_AMDX(
    Vk_Command_ಬಫರ್                             command_ಬಫರ್,
    Vk_Device_ವಿಳಾಸ                             scratch,
    Vk_Device_ಗಾತ್ರ                                scratch_ಗಾತ್ರ,
    ಸ್ಥಿರಾಂಕ Vk_Dispatch_ನಕ್ಷೆ_ಎಣಿಕೆ_Info_AMDX*         p_ಎಣಿಕೆ_Info);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vk_Cmd_Dispatch_ನಕ್ಷೆ_ಪರೋಕ್ಷ_AMDX(
    Vk_Command_ಬಫರ್                             command_ಬಫರ್,
    Vk_Device_ವಿಳಾಸ                             scratch,
    Vk_Device_ಗಾತ್ರ                                scratch_ಗಾತ್ರ,
    ಸ್ಥಿರಾಂಕ Vk_Dispatch_ನಕ್ಷೆ_ಎಣಿಕೆ_Info_AMDX*         p_ಎಣಿಕೆ_Info);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vk_Cmd_Dispatch_ನಕ್ಷೆ_ಪರೋಕ್ಷ_ಎಣಿಕೆ_AMDX(
    Vk_Command_ಬಫರ್                             command_ಬಫರ್,
    Vk_Device_ವಿಳಾಸ                             scratch,
    Vk_Device_ಗಾತ್ರ                                scratch_ಗಾತ್ರ,
    Vk_Device_ವಿಳಾಸ                             ಎಣಿಕೆ_Info);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_CUDA_KERNEL_LAUNCH_SPEC_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    size_t             ದತ್ತಾಂಶ_ಗಾತ್ರ_2;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ದತ್ತಾಂಶ;
} VkCudaModuleCreateInfoNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    VkCudaModuleNV     module;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*        pName;
} VkCudaFunctionCreateInfoNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*            p_ಮುಂದಿನ;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               ಖಂಡ_Dim_X;
    uint32_t               ಖಂಡ_Dim_Y;
    uint32_t               ಖಂಡ_Dim_Z;
    uint32_t               shared_Mem_ಬೈಟುಗಳು;
    size_t                 param_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* ಸ್ಥಿರಾಂಕ *    pParams;
    size_t                 extra_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* ಸ್ಥಿರಾಂಕ *    pExtras;
} VkCudaLaunchInfoNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ಸ್ಥಿರಾಂಕ VkCudaModuleCreateInfoNV* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkCudaModuleNV* pModule);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_ಗಾತ್ರ, ಶೂನ್ಯ* p_Cache_ದತ್ತಾಂಶ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ಸ್ಥಿರಾಂಕ VkCudaFunctionCreateInfoNV* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_ಬಫರ್ command_ಬಫರ್, ಸ್ಥಿರಾಂಕ VkCudaLaunchInfoNV* pLaunchInfo);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkCudaModuleCreateInfoNV*             pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_ಗಾತ್ರ,
    ಶೂನ್ಯ*                                       p_Cache_ದತ್ತಾಂಶ);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_ಬಫರ್                             command_ಬಫರ್,
    ಸ್ಥಿರಾಂಕ VkCudaLaunchInfoNV*                   pLaunchInfo);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_displacement_micromap 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_DISPLACEMENT_MICROMAP_SPEC_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_ಬೈಟುಗಳು_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_ಬೈಟುಗಳು_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_ಬೈಟುಗಳು_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    ಶೂನ್ಯ*                               p_ಮುಂದಿನ;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_ಸದಿಶ_Format;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_KHR       displacement_Bias_And_Scale_ಬಫರ್;
    Vk_Device_ಗಾತ್ರ                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_KHR       displacement_ಸದಿಶ_ಬಫರ್;
    Vk_Device_ಗಾತ್ರ                        displacement_ಸದಿಶ_Stride;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_ಗಾತ್ರ                        displacedMicromapPrimitiveFlagsStride;
    Vk_ಸೂಚ್ಯಂಕ_Type                         ಸೂಚ್ಯಂಕ_Type;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_KHR       ಸೂಚ್ಯಂಕ_ಬಫರ್_2;
    Vk_Device_ಗಾತ್ರ                        ಸೂಚ್ಯಂಕ_Stride;
    uint32_t                            ತಳ_Triangle;
    uint32_t                            usage_Counts_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ VkMicromapUsageEXT*           pUsageCounts;
    ಸ್ಥಿರಾಂಕ VkMicromapUsageEXT* ಸ್ಥಿರಾಂಕ*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_AMDX_dense_geometry_format 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#ವ್ಯಾಖ್ಯಾನಿಸು VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#ವ್ಯಾಖ್ಯಾನಿಸು VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_ದತ್ತಾಂಶ_AMDX {
    VkStructureType                   sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                       p_ಮುಂದಿನ;
    Vk_Device_Or_Host_ವಿಳಾಸ_Const_KHR     compressed_ದತ್ತಾಂಶ;
    Vk_Device_ಗಾತ್ರ                      ದತ್ತಾಂಶ_ಗಾತ್ರ_2;
    uint32_t                          ಅಂಕೆ_Triangles;
    uint32_t                          ಅಂಕೆ_Vertices;
    uint32_t                          max_Primitive_ಸೂಚ್ಯಂಕ;
    uint32_t                          max_Geometry_ಸೂಚ್ಯಂಕ;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_ದತ್ತಾಂಶ_AMDX;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

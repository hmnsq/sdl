#که_نه_تعریف_شوی VULKAN_BETA_H_
#تعریف_کړه VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_portability_subset 1

#تعریف_کړه VK_KHR_PORTABILITY_SUBSET_SPEC_نسخه 1
#تعریف_کړه VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           ټکی_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_ماسک_Ref;
    VkBool32           shader_Sample_شرح_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_ټکی_ډېرپېښ;
    VkBool32           triangleFans;
    VkBool32           راس_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           min_راس_ننوت_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_AMDX_shader_کتار_ته_ورزیاتول 1

#تعریف_کړه VK_AMDX_SHADER_کتار_ته_ورزیاتول_SPEC_نسخه 2
#تعریف_کړه VK_AMDX_SHADER_کتار_ته_ورزیاتول_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#تعریف_کړه VK_SHADER_شاخص_ناکارول_شوی_AMDX       (~0U)

تعريفنوع بنية Vk_Physical_Device_Shader_کتار_ته_ورزیاتول_Features_AMDX {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           shader_کتار_ته_ورزیاتول;
    VkBool32           shader_Mesh_کتار_ته_ورزیاتول;
} Vk_Physical_Device_Shader_کتار_ته_ورزیاتول_Features_AMDX;

تعريفنوع بنية Vk_Physical_Device_Shader_کتار_ته_ورزیاتول_Properties_AMDX {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           max_Execution_ګراف_ژوروالی;
    uint32_t           max_Execution_ګراف_Shader_Output_Nodes;
    uint32_t           max_Execution_ګراف_Shader_Payload_اندازه;
    uint32_t           max_Execution_ګراف_Shader_Payload_شمېر;
    uint32_t           execution_ګراف_Dispatch_پته_Alignment;
    uint32_t           max_Execution_ګراف_Workgroup_شمېر[3];
    uint32_t           max_Execution_ګراف_Workgroups;
} Vk_Physical_Device_Shader_کتار_ته_ورزیاتول_Properties_AMDX;

تعريفنوع بنية Vk_Execution_ګراف_Pipeline_Scratch_اندازه_AMDX {
    VkStructureType    sType;
    فراغ*              p_بل;
    Vk_Device_اندازه       min_اندازه;
    Vk_Device_اندازه       max_اندازه_2;
    Vk_Device_اندازه       اندازه_Granularity;
} Vk_Execution_ګراف_Pipeline_Scratch_اندازه_AMDX;

تعريفنوع بنية Vk_Execution_ګراف_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ثابت فراغ*                               p_بل;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_شمېر;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                بنسټ_Pipeline_Handle;
    int32_t                                   بنسټ_Pipeline_شاخص;
} Vk_Execution_ګراف_Pipeline_Create_Info_AMDX;

تعريفنوع اتحاد Vk_Device_Or_Host_پته_Const_AMDX {
    Vk_Device_پته    device_پته;
    ثابت فراغ*        host_پته;
} Vk_Device_Or_Host_پته_Const_AMDX;

تعريفنوع بنية Vk_Dispatch_ګراف_Info_AMDX {
    uint32_t                          غوټه_شاخص_2;
    uint32_t                          payload_شمېر;
    Vk_Device_Or_Host_پته_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_ګراف_Info_AMDX;

تعريفنوع بنية Vk_Dispatch_ګراف_شمېر_Info_AMDX {
    uint32_t                          شمېر;
    Vk_Device_Or_Host_پته_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_ګراف_شمېر_Info_AMDX;

تعريفنوع بنية Vk_Pipeline_Shader_Stage_غوټه_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت فراغ*          p_بل;
    ثابت حرف*          pName;
    uint32_t             شاخص;
} Vk_Pipeline_Shader_Stage_غوټه_Create_Info_AMDX;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Create_Execution_ګراف_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_شمېر, ثابت Vk_Execution_ګراف_Pipeline_Create_Info_AMDX* pCreateInfos, ثابت Vk_ویش_Callbacks*    pAllocator, VkPipeline*               pPipelines);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_Execution_ګراف_Pipeline_Scratch_اندازه_AMDX)(VkDevice                                        device, VkPipeline                                      execution_ګراف, Vk_Execution_ګراف_Pipeline_Scratch_اندازه_AMDX*        p_اندازه_Info);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_Execution_ګراف_Pipeline_غوټه_شاخص_AMDX)(VkDevice                                        device, VkPipeline                                      execution_ګراف, ثابت Vk_Pipeline_Shader_Stage_غوټه_Create_Info_AMDX*  p_غوټه_Info, uint32_t*                                       p_غوټه_شاخص);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Initialize_ګراف_Scratch_حافظه_AMDX)(Vk_Command_بفر                                 command_بفر, VkPipeline                                      execution_ګراف, Vk_Device_پته                                 scratch, Vk_Device_اندازه                                    scratch_اندازه);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ګراف_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پته                                 scratch, Vk_Device_اندازه                                    scratch_اندازه, ثابت Vk_Dispatch_ګراف_شمېر_Info_AMDX*             p_شمېر_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ګراف_غیرمستقیم_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پته                                 scratch, Vk_Device_اندازه                                    scratch_اندازه, ثابت Vk_Dispatch_ګراف_شمېر_Info_AMDX*             p_شمېر_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_ګراف_غیرمستقیم_شمېر_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پته                                 scratch, Vk_Device_اندازه                                    scratch_اندازه, Vk_Device_پته                                 شمېر_Info);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Create_Execution_ګراف_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_شمېر,
    ثابت Vk_Execution_ګراف_Pipeline_Create_Info_AMDX* pCreateInfos,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_Execution_ګراف_Pipeline_Scratch_اندازه_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_ګراف,
    Vk_Execution_ګراف_Pipeline_Scratch_اندازه_AMDX*    p_اندازه_Info);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_Execution_ګراف_Pipeline_غوټه_شاخص_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_ګراف,
    ثابت Vk_Pipeline_Shader_Stage_غوټه_Create_Info_AMDX* p_غوټه_Info,
    uint32_t*                                   p_غوټه_شاخص);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Initialize_ګراف_Scratch_حافظه_AMDX(
    Vk_Command_بفر                             command_بفر,
    VkPipeline                                  execution_ګراف,
    Vk_Device_پته                             scratch,
    Vk_Device_اندازه                                scratch_اندازه);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_ګراف_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پته                             scratch,
    Vk_Device_اندازه                                scratch_اندازه,
    ثابت Vk_Dispatch_ګراف_شمېر_Info_AMDX*         p_شمېر_Info);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_ګراف_غیرمستقیم_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پته                             scratch,
    Vk_Device_اندازه                                scratch_اندازه,
    ثابت Vk_Dispatch_ګراف_شمېر_Info_AMDX*         p_شمېر_Info);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_ګراف_غیرمستقیم_شمېر_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پته                             scratch,
    Vk_Device_اندازه                                scratch_اندازه,
    Vk_Device_پته                             شمېر_Info);
#د_که_پای
#د_که_پای


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#تعریف_کړه VK_NV_CUDA_KERNEL_LAUNCH_SPEC_نسخه 2
#تعریف_کړه VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

تعريفنوع بنية VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    size_t             معلومات_اندازه_2;
    ثابت فراغ*        p_معلومات;
} VkCudaModuleCreateInfoNV;

تعريفنوع بنية VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    VkCudaModuleNV     module;
    ثابت حرف*        pName;
} VkCudaFunctionCreateInfoNV;

تعريفنوع بنية VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت فراغ*            p_بل;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               بلاک_Dim_X;
    uint32_t               بلاک_Dim_Y;
    uint32_t               بلاک_Dim_Z;
    uint32_t               shared_Mem_بایټونه;
    size_t                 param_شمېر;
    ثابت فراغ* ثابت *    pParams;
    size_t                 extra_شمېر;
    ثابت فراغ* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkCudaModuleNV* pModule);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_اندازه, فراغ* p_Cache_معلومات);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت Vk_ویش_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت Vk_ویش_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_بفر command_بفر, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ثابت VkCudaModuleCreateInfoNV*             pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_اندازه,
    فراغ*                                       p_Cache_معلومات);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت Vk_ویش_Callbacks*                pAllocator);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت Vk_ویش_Callbacks*                pAllocator);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_بفر                             command_بفر,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#د_که_پای
#د_که_پای


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_NV_displacement_micromap 1

#تعریف_کړه VK_NV_DISPLACEMENT_MICROMAP_SPEC_نسخه 2
#تعریف_کړه VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

تعريفنوع تعداد VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_بایټونه_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_بایټونه_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_بایټونه_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

تعريفنوع بنية VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    فراغ*                               p_بل;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_ویکټور_Format;
    Vk_Device_Or_Host_پته_Const_KHR       displacement_Bias_And_Scale_بفر;
    Vk_Device_اندازه                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_پته_Const_KHR       displacement_ویکټور_بفر;
    Vk_Device_اندازه                        displacement_ویکټور_Stride;
    Vk_Device_Or_Host_پته_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_اندازه                        displacedMicromapPrimitiveFlagsStride;
    Vk_شاخص_Type                         شاخص_Type;
    Vk_Device_Or_Host_پته_Const_KHR       شاخص_بفر_2;
    Vk_Device_اندازه                        شاخص_Stride;
    uint32_t                            بنسټ_Triangle;
    uint32_t                            usage_Counts_شمېر;
    ثابت VkMicromapUsageEXT*           pUsageCounts;
    ثابت VkMicromapUsageEXT* ثابت*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_AMDX_dense_geometry_format 1

#تعریف_کړه VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_نسخه 1
#تعریف_کړه VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#تعریف_کړه VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#تعریف_کړه VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

تعريفنوع تعداد VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

تعريفنوع بنية VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

تعريفنوع بنية Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_معلومات_AMDX {
    VkStructureType                   sType;
    ثابت فراغ*                       p_بل;
    Vk_Device_Or_Host_پته_Const_KHR     compressed_معلومات;
    Vk_Device_اندازه                      معلومات_اندازه_2;
    uint32_t                          عدد_Triangles;
    uint32_t                          عدد_Vertices;
    uint32_t                          max_Primitive_شاخص;
    uint32_t                          max_Geometry_شاخص;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_معلومات_AMDX;


#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای

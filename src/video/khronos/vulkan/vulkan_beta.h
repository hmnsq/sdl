#جيڪڏهن_وصف_نه_ٿيل VULKAN_BETA_H_
#وصف_ڪريو VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_portability_subset 1

#وصف_ڪريو VK_KHR_PORTABILITY_SUBSET_SPEC_نسخو 1
#وصف_ڪريو VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           نقطو_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_نقاب_Ref;
    VkBool32           shader_Sample_شرح_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_نقطو_گهڻائي;
    VkBool32           triangleFans;
    VkBool32           راس_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           min_راس_داخلا_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_AMDX_shader_قطار_اندر_وجهو 1

#وصف_ڪريو VK_AMDX_SHADER_قطار_اندر_وجهو_SPEC_نسخو 2
#وصف_ڪريو VK_AMDX_SHADER_قطار_اندر_وجهو_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#وصف_ڪريو VK_SHADER_اشاريو_اڻ_استعمال_ٿيل_AMDX       (~0U)

تعريفنوع بنية Vk_Physical_Device_Shader_قطار_اندر_وجهو_Features_AMDX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           shader_قطار_اندر_وجهو;
    VkBool32           shader_Mesh_قطار_اندر_وجهو;
} Vk_Physical_Device_Shader_قطار_اندر_وجهو_Features_AMDX;

تعريفنوع بنية Vk_Physical_Device_Shader_قطار_اندر_وجهو_Properties_AMDX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           max_Execution_گراف_اونهائي;
    uint32_t           max_Execution_گراف_Shader_Output_Nodes;
    uint32_t           max_Execution_گراف_Shader_Payload_سائيز;
    uint32_t           max_Execution_گراف_Shader_Payload_ڳڻپ;
    uint32_t           execution_گراف_Dispatch_پتو_Alignment;
    uint32_t           max_Execution_گراف_Workgroup_ڳڻپ[3];
    uint32_t           max_Execution_گراف_Workgroups;
} Vk_Physical_Device_Shader_قطار_اندر_وجهو_Properties_AMDX;

تعريفنوع بنية Vk_Execution_گراف_Pipeline_Scratch_سائيز_AMDX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    Vk_Device_سائيز       min_سائيز;
    Vk_Device_سائيز       max_سائيز_2;
    Vk_Device_سائيز       سائيز_Granularity;
} Vk_Execution_گراف_Pipeline_Scratch_سائيز_AMDX;

تعريفنوع بنية Vk_Execution_گراف_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ثابت فراغ*                               p_ايندڙ;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_ڳڻپ;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                بنياد_Pipeline_Handle;
    int32_t                                   بنياد_Pipeline_اشاريو;
} Vk_Execution_گراف_Pipeline_Create_Info_AMDX;

تعريفنوع اتحاد Vk_Device_Or_Host_پتو_Const_AMDX {
    Vk_Device_پتو    device_پتو;
    ثابت فراغ*        host_پتو;
} Vk_Device_Or_Host_پتو_Const_AMDX;

تعريفنوع بنية Vk_Dispatch_گراف_Info_AMDX {
    uint32_t                          ڳنڍ_اشاريو_2;
    uint32_t                          payload_ڳڻپ;
    Vk_Device_Or_Host_پتو_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_گراف_Info_AMDX;

تعريفنوع بنية Vk_Dispatch_گراف_ڳڻپ_Info_AMDX {
    uint32_t                          ڳڻپ;
    Vk_Device_Or_Host_پتو_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_گراف_ڳڻپ_Info_AMDX;

تعريفنوع بنية Vk_Pipeline_Shader_Stage_ڳنڍ_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت فراغ*          p_ايندڙ;
    ثابت حرف*          pName;
    uint32_t             اشاريو;
} Vk_Pipeline_Shader_Stage_ڳنڍ_Create_Info_AMDX;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Create_Execution_گراف_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_ڳڻپ, ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos, ثابت Vk_ورهاست_Callbacks*    pAllocator, VkPipeline*               pPipelines);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_Scratch_سائيز_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, Vk_Execution_گراف_Pipeline_Scratch_سائيز_AMDX*        p_سائيز_Info);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_ڳنڍ_اشاريو_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, ثابت Vk_Pipeline_Shader_Stage_ڳنڍ_Create_Info_AMDX*  p_ڳنڍ_Info, uint32_t*                                       p_ڳنڍ_اشاريو);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Initialize_گراف_Scratch_يادگيري_AMDX)(Vk_Command_بفر                                 command_بفر, VkPipeline                                      execution_گراف, Vk_Device_پتو                                 scratch, Vk_Device_سائيز                                    scratch_سائيز);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتو                                 scratch, Vk_Device_سائيز                                    scratch_سائيز, ثابت Vk_Dispatch_گراف_ڳڻپ_Info_AMDX*             p_ڳڻپ_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_اڻسڌو_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتو                                 scratch, Vk_Device_سائيز                                    scratch_سائيز, ثابت Vk_Dispatch_گراف_ڳڻپ_Info_AMDX*             p_ڳڻپ_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_اڻسڌو_ڳڻپ_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتو                                 scratch, Vk_Device_سائيز                                    scratch_سائيز, Vk_Device_پتو                                 ڳڻپ_Info);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Create_Execution_گراف_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_ڳڻپ,
    ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_Execution_گراف_Pipeline_Scratch_سائيز_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    Vk_Execution_گراف_Pipeline_Scratch_سائيز_AMDX*    p_سائيز_Info);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_Execution_گراف_Pipeline_ڳنڍ_اشاريو_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    ثابت Vk_Pipeline_Shader_Stage_ڳنڍ_Create_Info_AMDX* p_ڳنڍ_Info,
    uint32_t*                                   p_ڳنڍ_اشاريو);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Initialize_گراف_Scratch_يادگيري_AMDX(
    Vk_Command_بفر                             command_بفر,
    VkPipeline                                  execution_گراف,
    Vk_Device_پتو                             scratch,
    Vk_Device_سائيز                                scratch_سائيز);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتو                             scratch,
    Vk_Device_سائيز                                scratch_سائيز,
    ثابت Vk_Dispatch_گراف_ڳڻپ_Info_AMDX*         p_ڳڻپ_Info);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_اڻسڌو_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتو                             scratch,
    Vk_Device_سائيز                                scratch_سائيز,
    ثابت Vk_Dispatch_گراف_ڳڻپ_Info_AMDX*         p_ڳڻپ_Info);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_اڻسڌو_ڳڻپ_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتو                             scratch,
    Vk_Device_سائيز                                scratch_سائيز,
    Vk_Device_پتو                             ڳڻپ_Info);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#وصف_ڪريو VK_NV_CUDA_KERNEL_LAUNCH_SPEC_نسخو 2
#وصف_ڪريو VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

تعريفنوع بنية VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    size_t             معلومات_سائيز_2;
    ثابت فراغ*        p_معلومات;
} VkCudaModuleCreateInfoNV;

تعريفنوع بنية VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    VkCudaModuleNV     module;
    ثابت حرف*        pName;
} VkCudaFunctionCreateInfoNV;

تعريفنوع بنية VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت فراغ*            p_ايندڙ;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               بلاڪ_Dim_X;
    uint32_t               بلاڪ_Dim_Y;
    uint32_t               بلاڪ_Dim_Z;
    uint32_t               shared_Mem_بائيٽون;
    size_t                 param_ڳڻپ;
    ثابت فراغ* ثابت *    pParams;
    size_t                 extra_ڳڻپ;
    ثابت فراغ* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkCudaModuleNV* pModule);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_سائيز, فراغ* p_Cache_معلومات);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت Vk_ورهاست_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت Vk_ورهاست_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_بفر command_بفر, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ثابت VkCudaModuleCreateInfoNV*             pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_سائيز,
    فراغ*                                       p_Cache_معلومات);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت Vk_ورهاست_Callbacks*                pAllocator);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت Vk_ورهاست_Callbacks*                pAllocator);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_بفر                             command_بفر,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_NV_displacement_micromap 1

#وصف_ڪريو VK_NV_DISPLACEMENT_MICROMAP_SPEC_نسخو 2
#وصف_ڪريو VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

تعريفنوع تعداد VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_بائيٽون_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_بائيٽون_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_بائيٽون_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

تعريفنوع بنية VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    فراغ*                               p_ايندڙ;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_ويڪٽر_Format;
    Vk_Device_Or_Host_پتو_Const_KHR       displacement_Bias_And_Scale_بفر;
    Vk_Device_سائيز                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_پتو_Const_KHR       displacement_ويڪٽر_بفر;
    Vk_Device_سائيز                        displacement_ويڪٽر_Stride;
    Vk_Device_Or_Host_پتو_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_سائيز                        displacedMicromapPrimitiveFlagsStride;
    Vk_اشاريو_Type                         اشاريو_Type;
    Vk_Device_Or_Host_پتو_Const_KHR       اشاريو_بفر_2;
    Vk_Device_سائيز                        اشاريو_Stride;
    uint32_t                            بنياد_Triangle;
    uint32_t                            usage_Counts_ڳڻپ;
    ثابت VkMicromapUsageEXT*           pUsageCounts;
    ثابت VkMicromapUsageEXT* ثابت*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_AMDX_dense_geometry_format 1

#وصف_ڪريو VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_نسخو 1
#وصف_ڪريو VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#وصف_ڪريو VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#وصف_ڪريو VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

تعريفنوع تعداد VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

تعريفنوع بنية VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

تعريفنوع بنية Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_معلومات_AMDX {
    VkStructureType                   sType;
    ثابت فراغ*                       p_ايندڙ;
    Vk_Device_Or_Host_پتو_Const_KHR     compressed_معلومات;
    Vk_Device_سائيز                      معلومات_سائيز_2;
    uint32_t                          انگ_Triangles;
    uint32_t                          انگ_Vertices;
    uint32_t                          max_Primitive_اشاريو;
    uint32_t                          max_Geometry_اشاريو;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_معلومات_AMDX;


#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو

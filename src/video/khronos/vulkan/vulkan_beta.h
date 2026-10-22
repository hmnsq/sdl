#اگر_تعریف_نشده VULKAN_BETA_H_
#تعریف_کن VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_portability_subset 1

#تعریف_کن VK_KHR_PORTABILITY_SUBSET_SPEC_نسخه 1
#تعریف_کن VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           نقطه_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_ماسک_Ref;
    VkBool32           shader_Sample_نرخ_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_نقطه_نما;
    VkBool32           triangleFans;
    VkBool32           رأس_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           min_رأس_درون_داد_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_AMDX_shader_افزودن_به_صف 1

#تعریف_کن VK_AMDX_SHADER_افزودن_به_صف_SPEC_نسخه 2
#تعریف_کن VK_AMDX_SHADER_افزودن_به_صف_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#تعریف_کن VK_SHADER_شاخص_استفادهنشده_AMDX       (~0U)

تعريفنوع بنية Vk_Physical_Device_Shader_افزودن_به_صف_Features_AMDX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           shader_افزودن_به_صف;
    VkBool32           shader_Mesh_افزودن_به_صف;
} Vk_Physical_Device_Shader_افزودن_به_صف_Features_AMDX;

تعريفنوع بنية Vk_Physical_Device_Shader_افزودن_به_صف_Properties_AMDX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           max_Execution_گراف_عمق;
    uint32_t           max_Execution_گراف_Shader_Output_Nodes;
    uint32_t           max_Execution_گراف_Shader_Payload_اندازه;
    uint32_t           max_Execution_گراف_Shader_Payload_شمار;
    uint32_t           execution_گراف_Dispatch_آدرس_Alignment;
    uint32_t           max_Execution_گراف_Workgroup_شمار[3];
    uint32_t           max_Execution_گراف_Workgroups;
} Vk_Physical_Device_Shader_افزودن_به_صف_Properties_AMDX;

تعريفنوع بنية Vk_Execution_گراف_Pipeline_Scratch_اندازه_AMDX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    Vk_Device_اندازه       min_اندازه;
    Vk_Device_اندازه       max_اندازه_2;
    Vk_Device_اندازه       اندازه_Granularity;
} Vk_Execution_گراف_Pipeline_Scratch_اندازه_AMDX;

تعريفنوع بنية Vk_Execution_گراف_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ثابت فراغ*                               p_بعدی;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_شمار;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                پایه_Pipeline_Handle;
    int32_t                                   پایه_Pipeline_شاخص;
} Vk_Execution_گراف_Pipeline_Create_Info_AMDX;

تعريفنوع اتحاد Vk_Device_Or_Host_آدرس_Const_AMDX {
    Vk_Device_آدرس    device_آدرس;
    ثابت فراغ*        host_آدرس;
} Vk_Device_Or_Host_آدرس_Const_AMDX;

تعريفنوع بنية Vk_Dispatch_گراف_Info_AMDX {
    uint32_t                          گره_شاخص_2;
    uint32_t                          payload_شمار;
    Vk_Device_Or_Host_آدرس_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_گراف_Info_AMDX;

تعريفنوع بنية Vk_Dispatch_گراف_شمار_Info_AMDX {
    uint32_t                          شمار;
    Vk_Device_Or_Host_آدرس_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_گراف_شمار_Info_AMDX;

تعريفنوع بنية Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت فراغ*          p_بعدی;
    ثابت حرف*          pName;
    uint32_t             شاخص;
} Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Create_Execution_گراف_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_شمار, ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos, ثابت Vk_تخصیص_Callbacks*    pAllocator, VkPipeline*               pPipelines);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_Scratch_اندازه_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, Vk_Execution_گراف_Pipeline_Scratch_اندازه_AMDX*        p_اندازه_Info);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_گره_شاخص_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, ثابت Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX*  p_گره_Info, uint32_t*                                       p_گره_شاخص);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Initialize_گراف_Scratch_حافظه_AMDX)(Vk_Command_میانگیر                                 command_میانگیر, VkPipeline                                      execution_گراف, Vk_Device_آدرس                                 scratch, Vk_Device_اندازه                                    scratch_اندازه);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_AMDX)(Vk_Command_میانگیر                                 command_میانگیر, Vk_Device_آدرس                                 scratch, Vk_Device_اندازه                                    scratch_اندازه, ثابت Vk_Dispatch_گراف_شمار_Info_AMDX*             p_شمار_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_غیرمستقیم_AMDX)(Vk_Command_میانگیر                                 command_میانگیر, Vk_Device_آدرس                                 scratch, Vk_Device_اندازه                                    scratch_اندازه, ثابت Vk_Dispatch_گراف_شمار_Info_AMDX*             p_شمار_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_غیرمستقیم_شمار_AMDX)(Vk_Command_میانگیر                                 command_میانگیر, Vk_Device_آدرس                                 scratch, Vk_Device_اندازه                                    scratch_اندازه, Vk_Device_آدرس                                 شمار_Info);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Create_Execution_گراف_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_شمار,
    ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_Execution_گراف_Pipeline_Scratch_اندازه_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    Vk_Execution_گراف_Pipeline_Scratch_اندازه_AMDX*    p_اندازه_Info);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_Execution_گراف_Pipeline_گره_شاخص_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    ثابت Vk_Pipeline_Shader_Stage_گره_Create_Info_AMDX* p_گره_Info,
    uint32_t*                                   p_گره_شاخص);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Initialize_گراف_Scratch_حافظه_AMDX(
    Vk_Command_میانگیر                             command_میانگیر,
    VkPipeline                                  execution_گراف,
    Vk_Device_آدرس                             scratch,
    Vk_Device_اندازه                                scratch_اندازه);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_AMDX(
    Vk_Command_میانگیر                             command_میانگیر,
    Vk_Device_آدرس                             scratch,
    Vk_Device_اندازه                                scratch_اندازه,
    ثابت Vk_Dispatch_گراف_شمار_Info_AMDX*         p_شمار_Info);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_غیرمستقیم_AMDX(
    Vk_Command_میانگیر                             command_میانگیر,
    Vk_Device_آدرس                             scratch,
    Vk_Device_اندازه                                scratch_اندازه,
    ثابت Vk_Dispatch_گراف_شمار_Info_AMDX*         p_شمار_Info);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_غیرمستقیم_شمار_AMDX(
    Vk_Command_میانگیر                             command_میانگیر,
    Vk_Device_آدرس                             scratch,
    Vk_Device_اندازه                                scratch_اندازه,
    Vk_Device_آدرس                             شمار_Info);
#پایان_اگر
#پایان_اگر


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#تعریف_کن VK_NV_CUDA_KERNEL_LAUNCH_SPEC_نسخه 2
#تعریف_کن VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

تعريفنوع بنية VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    size_t             داده_اندازه_2;
    ثابت فراغ*        p_داده;
} VkCudaModuleCreateInfoNV;

تعريفنوع بنية VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    VkCudaModuleNV     module;
    ثابت حرف*        pName;
} VkCudaFunctionCreateInfoNV;

تعريفنوع بنية VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت فراغ*            p_بعدی;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               بلوک_Dim_X;
    uint32_t               بلوک_Dim_Y;
    uint32_t               بلوک_Dim_Z;
    uint32_t               shared_Mem_بایتها;
    size_t                 param_شمار;
    ثابت فراغ* ثابت *    pParams;
    size_t                 extra_شمار;
    ثابت فراغ* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkCudaModuleNV* pModule);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_اندازه, فراغ* p_Cache_داده);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت Vk_تخصیص_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت Vk_تخصیص_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_میانگیر command_میانگیر, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ثابت VkCudaModuleCreateInfoNV*             pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_اندازه,
    فراغ*                                       p_Cache_داده);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت Vk_تخصیص_Callbacks*                pAllocator);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت Vk_تخصیص_Callbacks*                pAllocator);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_میانگیر                             command_میانگیر,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#پایان_اگر
#پایان_اگر


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_NV_displacement_micromap 1

#تعریف_کن VK_NV_DISPLACEMENT_MICROMAP_SPEC_نسخه 2
#تعریف_کن VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

تعريفنوع تعداد VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_بایتها_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_بایتها_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_بایتها_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

تعريفنوع بنية VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    فراغ*                               p_بعدی;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_وکتور_Format;
    Vk_Device_Or_Host_آدرس_Const_KHR       displacement_Bias_And_Scale_میانگیر;
    Vk_Device_اندازه                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_آدرس_Const_KHR       displacement_وکتور_میانگیر;
    Vk_Device_اندازه                        displacement_وکتور_Stride;
    Vk_Device_Or_Host_آدرس_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_اندازه                        displacedMicromapPrimitiveFlagsStride;
    Vk_شاخص_Type                         شاخص_Type;
    Vk_Device_Or_Host_آدرس_Const_KHR       شاخص_میانگیر_2;
    Vk_Device_اندازه                        شاخص_Stride;
    uint32_t                            پایه_Triangle;
    uint32_t                            usage_Counts_شمار;
    ثابت VkMicromapUsageEXT*           pUsageCounts;
    ثابت VkMicromapUsageEXT* ثابت*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_AMDX_dense_geometry_format 1

#تعریف_کن VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_نسخه 1
#تعریف_کن VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#تعریف_کن VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#تعریف_کن VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

تعريفنوع تعداد VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

تعريفنوع بنية VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

تعريفنوع بنية Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_داده_AMDX {
    VkStructureType                   sType;
    ثابت فراغ*                       p_بعدی;
    Vk_Device_Or_Host_آدرس_Const_KHR     compressed_داده;
    Vk_Device_اندازه                      داده_اندازه_2;
    uint32_t                          رقم_Triangles;
    uint32_t                          رقم_Vertices;
    uint32_t                          max_Primitive_شاخص;
    uint32_t                          max_Geometry_شاخص;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_داده_AMDX;


#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر

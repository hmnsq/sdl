#جے_بنا_تعریف VULKAN_BETA_H_
#تعریف_کرو VULKAN_BETA_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_portability_subset 1

#تعریف_کرو VK_KHR_PORTABILITY_SUBSET_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           constantAlphaColorBlendFactors;
    VkBool32           events;
    VkBool32           imageViewFormatReinterpretation;
    VkBool32           imageViewFormatSwizzle;
    VkBool32           imageView2DOn3DImage;
    VkBool32           multisampleArrayImage;
    VkBool32           mutableComparisonSamplers;
    VkBool32           نقطہ_Polygons;
    VkBool32           samplerMipLodBias;
    VkBool32           separate_Stencil_نقاب_Ref;
    VkBool32           shader_Sample_شرح_Interpolation_Functions;
    VkBool32           tessellationIsolines;
    VkBool32           tessellation_نقطہ_منوال;
    VkBool32           triangleFans;
    VkBool32           راس_Attribute_Access_Beyond_Stride;
} VkPhysicalDevicePortabilitySubsetFeaturesKHR;

تعريفنوع بنية VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           min_راس_داخلہ_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_AMDX_shader_قطار_وچ_پاؤ 1

#تعریف_کرو VK_AMDX_SHADER_قطار_وچ_پاؤ_SPEC_نسخہ 2
#تعریف_کرو VK_AMDX_SHADER_قطار_وچ_پاؤ_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#تعریف_کرو VK_SHADER_اشاریہ_بن_ورتیا_AMDX       (~0U)

تعريفنوع بنية Vk_Physical_Device_Shader_قطار_وچ_پاؤ_Features_AMDX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           shader_قطار_وچ_پاؤ;
    VkBool32           shader_Mesh_قطار_وچ_پاؤ;
} Vk_Physical_Device_Shader_قطار_وچ_پاؤ_Features_AMDX;

تعريفنوع بنية Vk_Physical_Device_Shader_قطار_وچ_پاؤ_Properties_AMDX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           max_Execution_گراف_ڈونگھائی;
    uint32_t           max_Execution_گراف_Shader_Output_Nodes;
    uint32_t           max_Execution_گراف_Shader_Payload_ناپ;
    uint32_t           max_Execution_گراف_Shader_Payload_گنتی;
    uint32_t           execution_گراف_Dispatch_پتہ_Alignment;
    uint32_t           max_Execution_گراف_Workgroup_گنتی[3];
    uint32_t           max_Execution_گراف_Workgroups;
} Vk_Physical_Device_Shader_قطار_وچ_پاؤ_Properties_AMDX;

تعريفنوع بنية Vk_Execution_گراف_Pipeline_Scratch_ناپ_AMDX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    Vk_Device_ناپ       min_ناپ;
    Vk_Device_ناپ       max_ناپ_2;
    Vk_Device_ناپ       ناپ_Granularity;
} Vk_Execution_گراف_Pipeline_Scratch_ناپ_AMDX;

تعريفنوع بنية Vk_Execution_گراف_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ثابت فراغ*                               p_اگلا;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_گنتی;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                ادھار_Pipeline_Handle;
    int32_t                                   ادھار_Pipeline_اشاریہ;
} Vk_Execution_گراف_Pipeline_Create_Info_AMDX;

تعريفنوع اتحاد Vk_Device_Or_Host_پتہ_Const_AMDX {
    Vk_Device_پتہ    device_پتہ;
    ثابت فراغ*        host_پتہ;
} Vk_Device_Or_Host_پتہ_Const_AMDX;

تعريفنوع بنية Vk_Dispatch_گراف_Info_AMDX {
    uint32_t                          گرہ_اشاریہ_2;
    uint32_t                          payload_گنتی;
    Vk_Device_Or_Host_پتہ_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_گراف_Info_AMDX;

تعريفنوع بنية Vk_Dispatch_گراف_گنتی_Info_AMDX {
    uint32_t                          گنتی;
    Vk_Device_Or_Host_پتہ_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_گراف_گنتی_Info_AMDX;

تعريفنوع بنية Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت فراغ*          p_اگلا;
    ثابت حرف*          pName;
    uint32_t             اشاریہ;
} Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_Execution_گراف_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_گنتی, ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos, ثابت Vk_ونڈ_Callbacks*    pAllocator, VkPipeline*               pPipelines);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_Scratch_ناپ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, Vk_Execution_گراف_Pipeline_Scratch_ناپ_AMDX*        p_ناپ_Info);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_گرہ_اشاریہ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, ثابت Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX*  p_گرہ_Info, uint32_t*                                       p_گرہ_اشاریہ);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Initialize_گراف_Scratch_حافظہ_AMDX)(Vk_Command_بفر                                 command_بفر, VkPipeline                                      execution_گراف, Vk_Device_پتہ                                 scratch, Vk_Device_ناپ                                    scratch_ناپ);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتہ                                 scratch, Vk_Device_ناپ                                    scratch_ناپ, ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*             p_گنتی_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_اسدھا_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتہ                                 scratch, Vk_Device_ناپ                                    scratch_ناپ, ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*             p_گنتی_Info);
تعريفنوع فراغ (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_اسدھا_گنتی_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتہ                                 scratch, Vk_Device_ناپ                                    scratch_ناپ, Vk_Device_پتہ                                 گنتی_Info);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_Execution_گراف_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_گنتی,
    ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Execution_گراف_Pipeline_Scratch_ناپ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    Vk_Execution_گراف_Pipeline_Scratch_ناپ_AMDX*    p_ناپ_Info);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Execution_گراف_Pipeline_گرہ_اشاریہ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    ثابت Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX* p_گرہ_Info,
    uint32_t*                                   p_گرہ_اشاریہ);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Initialize_گراف_Scratch_حافظہ_AMDX(
    Vk_Command_بفر                             command_بفر,
    VkPipeline                                  execution_گراف,
    Vk_Device_پتہ                             scratch,
    Vk_Device_ناپ                                scratch_ناپ);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتہ                             scratch,
    Vk_Device_ناپ                                scratch_ناپ,
    ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*         p_گنتی_Info);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_اسدھا_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتہ                             scratch,
    Vk_Device_ناپ                                scratch_ناپ,
    ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*         p_گنتی_Info);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vk_Cmd_Dispatch_گراف_اسدھا_گنتی_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتہ                             scratch,
    Vk_Device_ناپ                                scratch_ناپ,
    Vk_Device_پتہ                             گنتی_Info);
#جے_انت
#جے_انت


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#تعریف_کرو VK_NV_CUDA_KERNEL_LAUNCH_SPEC_نسخہ 2
#تعریف_کرو VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

تعريفنوع بنية VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    size_t             انکڑے_ناپ_2;
    ثابت فراغ*        p_انکڑے;
} VkCudaModuleCreateInfoNV;

تعريفنوع بنية VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    VkCudaModuleNV     module;
    ثابت حرف*        pName;
} VkCudaFunctionCreateInfoNV;

تعريفنوع بنية VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت فراغ*            p_اگلا;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               بلاک_Dim_X;
    uint32_t               بلاک_Dim_Y;
    uint32_t               بلاک_Dim_Z;
    uint32_t               shared_Mem_بائٹاں;
    size_t                 param_گنتی;
    ثابت فراغ* ثابت *    pParams;
    size_t                 extra_گنتی;
    ثابت فراغ* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkCudaModuleNV* pModule);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_ناپ, فراغ* p_Cache_انکڑے);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت Vk_ونڈ_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت Vk_ونڈ_Callbacks* pAllocator);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_بفر command_بفر, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ثابت VkCudaModuleCreateInfoNV*             pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_ناپ,
    فراغ*                                       p_Cache_انکڑے);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت Vk_ونڈ_Callbacks*                pAllocator);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت Vk_ونڈ_Callbacks*                pAllocator);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_بفر                             command_بفر,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#جے_انت
#جے_انت


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_displacement_micromap 1

#تعریف_کرو VK_NV_DISPLACEMENT_MICROMAP_SPEC_نسخہ 2
#تعریف_کرو VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

تعريفنوع تعداد VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_بائٹاں_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_بائٹاں_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_بائٹاں_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

تعريفنوع بنية VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

تعريفنوع بنية VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    فراغ*                               p_اگلا;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_سمتیہ_Format;
    Vk_Device_Or_Host_پتہ_Const_KHR       displacement_Bias_And_Scale_بفر;
    Vk_Device_ناپ                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_پتہ_Const_KHR       displacement_سمتیہ_بفر;
    Vk_Device_ناپ                        displacement_سمتیہ_Stride;
    Vk_Device_Or_Host_پتہ_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_ناپ                        displacedMicromapPrimitiveFlagsStride;
    Vk_اشاریہ_Type                         اشاریہ_Type;
    Vk_Device_Or_Host_پتہ_Const_KHR       اشاریہ_بفر_2;
    Vk_Device_ناپ                        اشاریہ_Stride;
    uint32_t                            ادھار_Triangle;
    uint32_t                            usage_Counts_گنتی;
    ثابت VkMicromapUsageEXT*           pUsageCounts;
    ثابت VkMicromapUsageEXT* ثابت*    ppUsageCounts;
    VkMicromapEXT                       micromap;
} VkAccelerationStructureTrianglesDisplacementMicromapNV;



// VK_AMDX_dense_geometry_format is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_AMDX_dense_geometry_format 1

#تعریف_کرو VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_نسخہ 1
#تعریف_کرو VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME "VK_AMDX_dense_geometry_format"
#تعریف_کرو VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX 128U
#تعریف_کرو VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX 128U

تعريفنوع تعداد VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

تعريفنوع بنية VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

تعريفنوع بنية Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_انکڑے_AMDX {
    VkStructureType                   sType;
    ثابت فراغ*                       p_اگلا;
    Vk_Device_Or_Host_پتہ_Const_KHR     compressed_انکڑے;
    Vk_Device_ناپ                      انکڑے_ناپ_2;
    uint32_t                          عدد_Triangles;
    uint32_t                          عدد_Vertices;
    uint32_t                          max_Primitive_اشاریہ;
    uint32_t                          max_Geometry_اشاریہ;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_انکڑے_AMDX;


#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت

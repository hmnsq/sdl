#اگر_غیر_تعریف_شدہ VULKAN_BETA_H_
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


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_KHR_portability_subset is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_portability_subset 1

#تعریف_کرو VK_KHR_PORTABILITY_SUBSET_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

قسمتعریف ساخت VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType    sType;
    خالی*              p_اگلا;
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

قسمتعریف ساخت VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           min_راس_داخلہ_Binding_Stride_Alignment;
} VkPhysicalDevicePortabilitySubsetPropertiesKHR;



// VK_AMDX_shader_enqueue is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_AMDX_shader_قطار_میں_ڈالو 1

#تعریف_کرو VK_AMDX_SHADER_قطار_میں_ڈالو_SPEC_نسخہ 2
#تعریف_کرو VK_AMDX_SHADER_قطار_میں_ڈالو_EXTENSION_NAME "VK_AMDX_shader_enqueue"
#تعریف_کرو VK_SHADER_اشاریہ_غیر_مستعمل_AMDX       (~0U)

قسمتعریف ساخت Vk_Physical_Device_Shader_قطار_میں_ڈالو_Features_AMDX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           shader_قطار_میں_ڈالو;
    VkBool32           shader_Mesh_قطار_میں_ڈالو;
} Vk_Physical_Device_Shader_قطار_میں_ڈالو_Features_AMDX;

قسمتعریف ساخت Vk_Physical_Device_Shader_قطار_میں_ڈالو_Properties_AMDX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           max_Execution_گراف_گہرائی;
    uint32_t           max_Execution_گراف_Shader_Output_Nodes;
    uint32_t           max_Execution_گراف_Shader_Payload_سائز;
    uint32_t           max_Execution_گراف_Shader_Payload_گنتی;
    uint32_t           execution_گراف_Dispatch_پتہ_Alignment;
    uint32_t           max_Execution_گراف_Workgroup_گنتی[3];
    uint32_t           max_Execution_گراف_Workgroups;
} Vk_Physical_Device_Shader_قطار_میں_ڈالو_Properties_AMDX;

قسمتعریف ساخت Vk_Execution_گراف_Pipeline_Scratch_سائز_AMDX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    Vk_Device_سائز       min_سائز;
    Vk_Device_سائز       max_سائز_2;
    Vk_Device_سائز       سائز_Granularity;
} Vk_Execution_گراف_Pipeline_Scratch_سائز_AMDX;

قسمتعریف ساخت Vk_Execution_گراف_Pipeline_Create_Info_AMDX {
    VkStructureType                           sType;
    ثابت خالی*                               p_اگلا;
    VkPipelineCreateFlags                     flags;
    uint32_t                                  stage_گنتی;
    ثابت VkPipelineShaderStageCreateInfo*    pStages;
    ثابت VkPipelineLibraryCreateInfoKHR*     pLibraryInfo;
    VkPipelineLayout                          layout;
    VkPipeline                                بنیاد_Pipeline_Handle;
    int32_t                                   بنیاد_Pipeline_اشاریہ;
} Vk_Execution_گراف_Pipeline_Create_Info_AMDX;

قسمتعریف اتحاد Vk_Device_Or_Host_پتہ_Const_AMDX {
    Vk_Device_پتہ    device_پتہ;
    ثابت خالی*        host_پتہ;
} Vk_Device_Or_Host_پتہ_Const_AMDX;

قسمتعریف ساخت Vk_Dispatch_گراف_Info_AMDX {
    uint32_t                          گرہ_اشاریہ_2;
    uint32_t                          payload_گنتی;
    Vk_Device_Or_Host_پتہ_Const_AMDX    payloads;
    uint64_t                          payloadStride;
} Vk_Dispatch_گراف_Info_AMDX;

قسمتعریف ساخت Vk_Dispatch_گراف_گنتی_Info_AMDX {
    uint32_t                          گنتی;
    Vk_Device_Or_Host_پتہ_Const_AMDX    infos;
    uint64_t                          stride;
} Vk_Dispatch_گراف_گنتی_Info_AMDX;

قسمتعریف ساخت Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX {
      VkStructureType    sType;
    ثابت خالی*          p_اگلا;
    ثابت حرف*          pName;
    uint32_t             اشاریہ;
} Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Create_Execution_گراف_Pipelines_AMDX)(VkDevice                                        device, VkPipelineCache pipelineCache, uint32_t                                        create_Info_گنتی, ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos, ثابت Vk_تخصیص_Callbacks*    pAllocator, VkPipeline*               pPipelines);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_Scratch_سائز_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, Vk_Execution_گراف_Pipeline_Scratch_سائز_AMDX*        p_سائز_Info);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Execution_گراف_Pipeline_گرہ_اشاریہ_AMDX)(VkDevice                                        device, VkPipeline                                      execution_گراف, ثابت Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX*  p_گرہ_Info, uint32_t*                                       p_گرہ_اشاریہ);
قسمتعریف خالی (VKAPI_PTR *PFN_vk_Cmd_Initialize_گراف_Scratch_حافظہ_AMDX)(Vk_Command_بفر                                 command_بفر, VkPipeline                                      execution_گراف, Vk_Device_پتہ                                 scratch, Vk_Device_سائز                                    scratch_سائز);
قسمتعریف خالی (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتہ                                 scratch, Vk_Device_سائز                                    scratch_سائز, ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*             p_گنتی_Info);
قسمتعریف خالی (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_بالواسطہ_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتہ                                 scratch, Vk_Device_سائز                                    scratch_سائز, ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*             p_گنتی_Info);
قسمتعریف خالی (VKAPI_PTR *PFN_vk_Cmd_Dispatch_گراف_بالواسطہ_گنتی_AMDX)(Vk_Command_بفر                                 command_بفر, Vk_Device_پتہ                                 scratch, Vk_Device_سائز                                    scratch_سائز, Vk_Device_پتہ                                 گنتی_Info);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Create_Execution_گراف_Pipelines_AMDX(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    create_Info_گنتی,
    ثابت Vk_Execution_گراف_Pipeline_Create_Info_AMDX* pCreateInfos,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Execution_گراف_Pipeline_Scratch_سائز_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    Vk_Execution_گراف_Pipeline_Scratch_سائز_AMDX*    p_سائز_Info);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Execution_گراف_Pipeline_گرہ_اشاریہ_AMDX(
    VkDevice                                    device,
    VkPipeline                                  execution_گراف,
    ثابت Vk_Pipeline_Shader_Stage_گرہ_Create_Info_AMDX* p_گرہ_Info,
    uint32_t*                                   p_گرہ_اشاریہ);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vk_Cmd_Initialize_گراف_Scratch_حافظہ_AMDX(
    Vk_Command_بفر                             command_بفر,
    VkPipeline                                  execution_گراف,
    Vk_Device_پتہ                             scratch,
    Vk_Device_سائز                                scratch_سائز);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vk_Cmd_Dispatch_گراف_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتہ                             scratch,
    Vk_Device_سائز                                scratch_سائز,
    ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*         p_گنتی_Info);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vk_Cmd_Dispatch_گراف_بالواسطہ_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتہ                             scratch,
    Vk_Device_سائز                                scratch_سائز,
    ثابت Vk_Dispatch_گراف_گنتی_Info_AMDX*         p_گنتی_Info);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vk_Cmd_Dispatch_گراف_بالواسطہ_گنتی_AMDX(
    Vk_Command_بفر                             command_بفر,
    Vk_Device_پتہ                             scratch,
    Vk_Device_سائز                                scratch_سائز,
    Vk_Device_پتہ                             گنتی_Info);
#اگر_ختم
#اگر_ختم


// VK_NV_cuda_kernel_launch is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_cuda_kernel_launch 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaModuleNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCudaFunctionNV)

#تعریف_کرو VK_NV_CUDA_KERNEL_LAUNCH_SPEC_نسخہ 2
#تعریف_کرو VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME "VK_NV_cuda_kernel_launch"

قسمتعریف ساخت VkCudaModuleCreateInfoNV {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    size_t             ڈیٹا_سائز_2;
    ثابت خالی*        p_ڈیٹا;
} VkCudaModuleCreateInfoNV;

قسمتعریف ساخت VkCudaFunctionCreateInfoNV {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    VkCudaModuleNV     module;
    ثابت حرف*        pName;
} VkCudaFunctionCreateInfoNV;

قسمتعریف ساخت VkCudaLaunchInfoNV {
    VkStructureType        sType;
    ثابت خالی*            p_اگلا;
    VkCudaFunctionNV       function;
    uint32_t               gridDimX;
    uint32_t               gridDimY;
    uint32_t               gridDimZ;
    uint32_t               بلاک_Dim_X;
    uint32_t               بلاک_Dim_Y;
    uint32_t               بلاک_Dim_Z;
    uint32_t               shared_Mem_بائٹیں;
    size_t                 param_گنتی;
    ثابت خالی* ثابت *    pParams;
    size_t                 extra_گنتی;
    ثابت خالی* ثابت *    pExtras;
} VkCudaLaunchInfoNV;

قسمتعریف ساخت VkPhysicalDeviceCudaKernelLaunchFeaturesNV {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           cudaKernelLaunchFeatures;
} VkPhysicalDeviceCudaKernelLaunchFeaturesNV;

قسمتعریف ساخت VkPhysicalDeviceCudaKernelLaunchPropertiesNV {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           computeCapabilityMinor;
    uint32_t           computeCapabilityMajor;
} VkPhysicalDeviceCudaKernelLaunchPropertiesNV;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateCudaModuleNV)(VkDevice device, ثابت VkCudaModuleCreateInfoNV* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkCudaModuleNV* pModule);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkGetCudaModuleCacheNV)(VkDevice device, VkCudaModuleNV module, size_t* p_Cache_سائز, خالی* p_Cache_ڈیٹا);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateCudaFunctionNV)(VkDevice device, ثابت VkCudaFunctionCreateInfoNV* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkCudaFunctionNV* pFunction);
قسمتعریف خالی (VKAPI_PTR *PFN_vkDestroyCudaModuleNV)(VkDevice device, VkCudaModuleNV module, ثابت Vk_تخصیص_Callbacks* pAllocator);
قسمتعریف خالی (VKAPI_PTR *PFN_vkDestroyCudaFunctionNV)(VkDevice device, VkCudaFunctionNV function, ثابت Vk_تخصیص_Callbacks* pAllocator);
قسمتعریف خالی (VKAPI_PTR *PFN_vkCmdCudaLaunchKernelNV)(Vk_Command_بفر command_بفر, ثابت VkCudaLaunchInfoNV* pLaunchInfo);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateCudaModuleNV(
    VkDevice                                    device,
    ثابت VkCudaModuleCreateInfoNV*             pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkCudaModuleNV*                             pModule);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetCudaModuleCacheNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    size_t*                                     p_Cache_سائز,
    خالی*                                       p_Cache_ڈیٹا);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateCudaFunctionNV(
    VkDevice                                    device,
    ثابت VkCudaFunctionCreateInfoNV*           pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkCudaFunctionNV*                           pFunction);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vkDestroyCudaModuleNV(
    VkDevice                                    device,
    VkCudaModuleNV                              module,
    ثابت Vk_تخصیص_Callbacks*                pAllocator);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vkDestroyCudaFunctionNV(
    VkDevice                                    device,
    VkCudaFunctionNV                            function,
    ثابت Vk_تخصیص_Callbacks*                pAllocator);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vkCmdCudaLaunchKernelNV(
    Vk_Command_بفر                             command_بفر,
    ثابت VkCudaLaunchInfoNV*                   pLaunchInfo);
#اگر_ختم
#اگر_ختم


// VK_NV_displacement_micromap is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_displacement_micromap 1

#تعریف_کرو VK_NV_DISPLACEMENT_MICROMAP_SPEC_نسخہ 2
#تعریف_کرو VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME "VK_NV_displacement_micromap"

قسمتعریف شمار VkDisplacementMicromapFormatNV {
    VK_DISPLACEMENT_MICROMAP_FORMAT_64_TRIANGLES_64_بائٹیں_NV = 1,
    VK_DISPLACEMENT_MICROMAP_FORMAT_256_TRIANGLES_128_بائٹیں_NV = 2,
    VK_DISPLACEMENT_MICROMAP_FORMAT_1024_TRIANGLES_128_بائٹیں_NV = 3,
    VK_DISPLACEMENT_MICROMAP_FORMAT_MAX_ENUM_NV = 0x7FFFFFFF
} VkDisplacementMicromapFormatNV;

قسمتعریف ساخت VkPhysicalDeviceDisplacementMicromapFeaturesNV {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           displacementMicromap;
} VkPhysicalDeviceDisplacementMicromapFeaturesNV;

قسمتعریف ساخت VkPhysicalDeviceDisplacementMicromapPropertiesNV {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           maxDisplacementMicromapSubdivisionLevel;
} VkPhysicalDeviceDisplacementMicromapPropertiesNV;

قسمتعریف ساخت VkAccelerationStructureTrianglesDisplacementMicromapNV {
    VkStructureType                     sType;
    خالی*                               p_اگلا;
    VkFormat                            displacementBiasAndScaleFormat;
    VkFormat                            displacement_سمتیہ_Format;
    Vk_Device_Or_Host_پتہ_Const_KHR       displacement_Bias_And_Scale_بفر;
    Vk_Device_سائز                        displacementBiasAndScaleStride;
    Vk_Device_Or_Host_پتہ_Const_KHR       displacement_سمتیہ_بفر;
    Vk_Device_سائز                        displacement_سمتیہ_Stride;
    Vk_Device_Or_Host_پتہ_Const_KHR       displacedMicromapPrimitiveFlags;
    Vk_Device_سائز                        displacedMicromapPrimitiveFlagsStride;
    Vk_اشاریہ_Type                         اشاریہ_Type;
    Vk_Device_Or_Host_پتہ_Const_KHR       اشاریہ_بفر_2;
    Vk_Device_سائز                        اشاریہ_Stride;
    uint32_t                            بنیاد_Triangle;
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

قسمتعریف شمار VkCompressedTriangleFormatAMDX {
    VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_AMDX = 0,
    VK_COMPRESSED_TRIANGLE_FORMAT_MAX_ENUM_AMDX = 0x7FFFFFFF
} VkCompressedTriangleFormatAMDX;

قسمتعریف ساخت VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           denseGeometryFormat;
} VkPhysicalDeviceDenseGeometryFormatFeaturesAMDX;

قسمتعریف ساخت Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_ڈیٹا_AMDX {
    VkStructureType                   sType;
    ثابت خالی*                       p_اگلا;
    Vk_Device_Or_Host_پتہ_Const_KHR     compressed_ڈیٹا;
    Vk_Device_سائز                      ڈیٹا_سائز_2;
    uint32_t                          عدد_Triangles;
    uint32_t                          عدد_Vertices;
    uint32_t                          max_Primitive_اشاریہ;
    uint32_t                          max_Geometry_اشاریہ;
    VkCompressedTriangleFormatAMDX    format;
} Vk_Acceleration_Structure_Dense_Geometry_Format_Triangles_ڈیٹا_AMDX;


#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم

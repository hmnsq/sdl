#अगर_अघोषित VULKAN_OHOS_H_
#घोषणा VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_OHOS_external_memory 1

काष्ठा OH_Native_बफर;

#घोषणा VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION 1
#घोषणा VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME "VK_OHOS_external_memory"

प्रकार काष्ठा Vk_Native_बफर_Usage_OHOS {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint64_t           OHOSNative_बफर_Usage;
} Vk_Native_बफर_Usage_OHOS;

प्रकार काष्ठा Vk_Native_बफर_Properties_OHOS {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    Vk_Device_आकार       allocation_आकार;
    uint32_t           memoryTypeBits;
} Vk_Native_बफर_Properties_OHOS;

प्रकार काष्ठा Vk_Native_बफर_Format_Properties_OHOS {
    VkStructureType                  sType;
    व्योम*                            p_अग्र;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_Native_बफर_Format_Properties_OHOS;

प्रकार काष्ठा Vk_Import_Native_बफर_Info_OHOS {
    VkStructureType            sType;
    स्थिर व्योम*                p_अग्र;
    काष्ठा OH_Native_बफर*    बफर_2;
} Vk_Import_Native_बफर_Info_OHOS;

प्रकार काष्ठा Vk_Memory_Get_Native_बफर_Info_OHOS {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    VkDeviceMemory     memory;
} Vk_Memory_Get_Native_बफर_Info_OHOS;

प्रकार काष्ठा VkExternalFormatOHOS {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Native_बफर_Properties_OHOS)(VkDevice device, स्थिर काष्ठा OH_Native_बफर* बफर_2, Vk_Native_बफर_Properties_OHOS* pProperties);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Memory_Native_बफर_OHOS)(VkDevice device, स्थिर Vk_Memory_Get_Native_बफर_Info_OHOS* pInfo, काष्ठा OH_Native_बफर** p_बफर);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Native_बफर_Properties_OHOS(
    VkDevice                                    device,
    स्थिर काष्ठा OH_Native_बफर*               बफर_2,
    Vk_Native_बफर_Properties_OHOS*               pProperties);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Memory_Native_बफर_OHOS(
    VkDevice                                    device,
    स्थिर Vk_Memory_Get_Native_बफर_Info_OHOS*      pInfo,
    काष्ठा OH_Native_बफर**                    p_बफर);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_OHOS_surface 1

प्रकार काष्ठा NativeWindow OHNativeWindow;

#घोषणा VK_OHOS_SURFACE_SPEC_VERSION      1
#घोषणा VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

प्रकार VkFlags VkSurfaceCreateFlagsOHOS;

प्रकार काष्ठा VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    स्थिर व्योम*                 p_अग्र;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNativeWindow*             window;
} VkSurfaceCreateInfoOHOS;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, स्थिर VkSurfaceCreateInfoOHOS* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    स्थिर VkSurfaceCreateInfoOHOS*              pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

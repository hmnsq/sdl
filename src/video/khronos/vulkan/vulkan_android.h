#अगर_अघोषित VULKAN_ANDROID_H_
#घोषणा VULKAN_ANDROID_H_ 1

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



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_android_surface 1

काष्ठा ANativeWindow;

#घोषणा VK_KHR_ANDROID_SURFACE_SPEC_VERSION 6
#घोषणा VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

प्रकार VkFlags VkAndroidSurfaceCreateFlagsKHR;

प्रकार काष्ठा VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    स्थिर व्योम*                       p_अग्र;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    काष्ठा ANativeWindow*             window;
} VkAndroidSurfaceCreateInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, स्थिर VkAndroidSurfaceCreateInfoKHR* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    स्थिर VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_ANDROID_external_memory_android_hardware_बफर 1

काष्ठा AHardware_बफर;

#घोषणा VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_बफर_SPEC_VERSION 5
#घोषणा VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_बफर_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

प्रकार काष्ठा Vk_Android_Hardware_बफर_Usage_ANDROID {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint64_t           android_Hardware_बफर_Usage;
} Vk_Android_Hardware_बफर_Usage_ANDROID;

प्रकार काष्ठा Vk_Android_Hardware_बफर_Properties_ANDROID {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    Vk_Device_आकार       allocation_आकार;
    uint32_t           memoryTypeBits;
} Vk_Android_Hardware_बफर_Properties_ANDROID;

प्रकार काष्ठा Vk_Android_Hardware_बफर_Format_Properties_ANDROID {
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
} Vk_Android_Hardware_बफर_Format_Properties_ANDROID;

प्रकार काष्ठा Vk_Import_Android_Hardware_बफर_Info_ANDROID {
    VkStructureType            sType;
    स्थिर व्योम*                p_अग्र;
    काष्ठा AHardware_बफर*    बफर_2;
} Vk_Import_Android_Hardware_बफर_Info_ANDROID;

प्रकार काष्ठा Vk_Memory_Get_Android_Hardware_बफर_Info_ANDROID {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    VkDeviceMemory     memory;
} Vk_Memory_Get_Android_Hardware_बफर_Info_ANDROID;

प्रकार काष्ठा VkExternalFormatANDROID {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

प्रकार काष्ठा Vk_Android_Hardware_बफर_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    व्योम*                            p_अग्र;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggestedXChromaOffset;
    VkChromaLocation                 suggestedYChromaOffset;
} Vk_Android_Hardware_बफर_Format_Properties2_ANDROID;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Android_Hardware_बफर_Properties_ANDROID)(VkDevice device, स्थिर काष्ठा AHardware_बफर* बफर_2, Vk_Android_Hardware_बफर_Properties_ANDROID* pProperties);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Memory_Android_Hardware_बफर_ANDROID)(VkDevice device, स्थिर Vk_Memory_Get_Android_Hardware_बफर_Info_ANDROID* pInfo, काष्ठा AHardware_बफर** p_बफर);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Android_Hardware_बफर_Properties_ANDROID(
    VkDevice                                    device,
    स्थिर काष्ठा AHardware_बफर*               बफर_2,
    Vk_Android_Hardware_बफर_Properties_ANDROID*   pProperties);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Memory_Android_Hardware_बफर_ANDROID(
    VkDevice                                    device,
    स्थिर Vk_Memory_Get_Android_Hardware_बफर_Info_ANDROID* pInfo,
    काष्ठा AHardware_बफर**                    p_बफर);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_ANDROID_external_format_resolve 1

#घोषणा VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION 1
#घोषणा VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

प्रकार काष्ठा VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

प्रकार काष्ठा VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    व्योम*               p_अग्र;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    externalFormatResolveChromaOffsetX;
    VkChromaLocation    externalFormatResolveChromaOffsetY;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

प्रकार काष्ठा Vk_Android_Hardware_बफर_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_बफर_Format_Resolve_Properties_ANDROID;


#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

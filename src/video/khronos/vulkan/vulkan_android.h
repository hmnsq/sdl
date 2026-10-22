#यदि_अपरिभाषितम् VULKAN_ANDROID_H_
#परिभाषय VULKAN_ANDROID_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_KHR_android_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_android_surface 1

संरचना ANative_गवाक्षः;

#परिभाषय VK_KHR_ANDROID_SURFACE_SPEC_संस्करणम् 6
#परिभाषय VK_KHR_ANDROID_SURFACE_EXTENSION_NAME "VK_KHR_android_surface"

प्रकारनिर्देश VkFlags VkAndroidSurfaceCreateFlagsKHR;

प्रकारनिर्देश संरचना VkAndroidSurfaceCreateInfoKHR {
    VkStructureType                   sType;
    ध्रुव शून्य*                       p_अग्र;
    VkAndroidSurfaceCreateFlagsKHR    flags;
    संरचना ANative_गवाक्षः*             गवाक्षः;
} VkAndroidSurfaceCreateInfoKHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateAndroidSurfaceKHR)(VkInstance instance, ध्रुव VkAndroidSurfaceCreateInfoKHR* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateAndroidSurfaceKHR(
    VkInstance                                  instance,
    ध्रुव VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः


// VK_ANDROID_external_memory_android_hardware_buffer is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_ANDROID_external_स्मृतिः_android_hardware_बफर 1

संरचना AHardware_बफर;

#परिभाषय VK_ANDROID_EXTERNAL_स्मृतिः_ANDROID_HARDWARE_बफर_SPEC_संस्करणम् 5
#परिभाषय VK_ANDROID_EXTERNAL_स्मृतिः_ANDROID_HARDWARE_बफर_EXTENSION_NAME "VK_ANDROID_external_memory_android_hardware_buffer"

प्रकारनिर्देश संरचना Vk_Android_Hardware_बफर_Usage_ANDROID {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint64_t           android_Hardware_बफर_Usage;
} Vk_Android_Hardware_बफर_Usage_ANDROID;

प्रकारनिर्देश संरचना Vk_Android_Hardware_बफर_Properties_ANDROID {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    Vk_Device_आकार       आवण्टनम्_आकार;
    uint32_t           स्मृतिः_Type_द्वयङ्काः;
} Vk_Android_Hardware_बफर_Properties_ANDROID;

प्रकारनिर्देश संरचना Vk_Android_Hardware_बफर_Format_Properties_ANDROID {
    VkStructureType                  sType;
    शून्य*                            p_अग्र;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_विस्थापनम्;
    VkChromaLocation                 suggested_YChroma_विस्थापनम्;
} Vk_Android_Hardware_बफर_Format_Properties_ANDROID;

प्रकारनिर्देश संरचना Vk_Import_Android_Hardware_बफर_Info_ANDROID {
    VkStructureType            sType;
    ध्रुव शून्य*                p_अग्र;
    संरचना AHardware_बफर*    बफर_2;
} Vk_Import_Android_Hardware_बफर_Info_ANDROID;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Get_Android_Hardware_बफर_Info_ANDROID {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    Vk_Device_स्मृतिः     स्मृतिः;
} Vk_स्मृतिः_Get_Android_Hardware_बफर_Info_ANDROID;

प्रकारनिर्देश संरचना VkExternalFormatANDROID {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint64_t           externalFormat;
} VkExternalFormatANDROID;

प्रकारनिर्देश संरचना Vk_Android_Hardware_बफर_Format_Properties2_ANDROID {
    VkStructureType                  sType;
    शून्य*                            p_अग्र;
    VkFormat                         format;
    uint64_t                         externalFormat;
    VkFormatFeatureFlags2            formatFeatures;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_विस्थापनम्;
    VkChromaLocation                 suggested_YChroma_विस्थापनम्;
} Vk_Android_Hardware_बफर_Format_Properties2_ANDROID;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Android_Hardware_बफर_Properties_ANDROID)(VkDevice device, ध्रुव संरचना AHardware_बफर* बफर_2, Vk_Android_Hardware_बफर_Properties_ANDROID* pProperties);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Android_Hardware_बफर_ANDROID)(VkDevice device, ध्रुव Vk_स्मृतिः_Get_Android_Hardware_बफर_Info_ANDROID* pInfo, संरचना AHardware_बफर** p_बफर);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Android_Hardware_बफर_Properties_ANDROID(
    VkDevice                                    device,
    ध्रुव संरचना AHardware_बफर*               बफर_2,
    Vk_Android_Hardware_बफर_Properties_ANDROID*   pProperties);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Android_Hardware_बफर_ANDROID(
    VkDevice                                    device,
    ध्रुव Vk_स्मृतिः_Get_Android_Hardware_बफर_Info_ANDROID* pInfo,
    संरचना AHardware_बफर**                    p_बफर);
#यदि_अन्तः
#यदि_अन्तः


// VK_ANDROID_external_format_resolve is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_ANDROID_external_format_resolve 1

#परिभाषय VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_संस्करणम् 1
#परिभाषय VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME "VK_ANDROID_external_format_resolve"

प्रकारनिर्देश संरचना VkPhysicalDeviceExternalFormatResolveFeaturesANDROID {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           externalFormatResolve;
} VkPhysicalDeviceExternalFormatResolveFeaturesANDROID;

प्रकारनिर्देश संरचना VkPhysicalDeviceExternalFormatResolvePropertiesANDROID {
    VkStructureType     sType;
    शून्य*               p_अग्र;
    VkBool32            nullColorAttachmentWithExternalFormatResolve;
    VkChromaLocation    external_Format_Resolve_Chroma_विस्थापनम्_X;
    VkChromaLocation    external_Format_Resolve_Chroma_विस्थापनम्_Y;
} VkPhysicalDeviceExternalFormatResolvePropertiesANDROID;

प्रकारनिर्देश संरचना Vk_Android_Hardware_बफर_Format_Resolve_Properties_ANDROID {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkFormat           colorAttachmentFormat;
} Vk_Android_Hardware_बफर_Format_Resolve_Properties_ANDROID;


#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः

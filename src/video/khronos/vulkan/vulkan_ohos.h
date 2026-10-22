#यदि_अपरिभाषितम् VULKAN_OHOS_H_
#परिभाषय VULKAN_OHOS_H_ 1

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



// VK_OHOS_external_memory is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_OHOS_external_स्मृतिः 1

संरचना OH_Native_बफर;

#परिभाषय VK_OHOS_EXTERNAL_स्मृतिः_SPEC_संस्करणम् 1
#परिभाषय VK_OHOS_EXTERNAL_स्मृतिः_EXTENSION_NAME "VK_OHOS_external_memory"

प्रकारनिर्देश संरचना Vk_Native_बफर_Usage_OHOS {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint64_t           OHOSNative_बफर_Usage;
} Vk_Native_बफर_Usage_OHOS;

प्रकारनिर्देश संरचना Vk_Native_बफर_Properties_OHOS {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    Vk_Device_आकार       आवण्टनम्_आकार;
    uint32_t           स्मृतिः_Type_द्वयङ्काः;
} Vk_Native_बफर_Properties_OHOS;

प्रकारनिर्देश संरचना Vk_Native_बफर_Format_Properties_OHOS {
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
} Vk_Native_बफर_Format_Properties_OHOS;

प्रकारनिर्देश संरचना Vk_Import_Native_बफर_Info_OHOS {
    VkStructureType            sType;
    ध्रुव शून्य*                p_अग्र;
    संरचना OH_Native_बफर*    बफर_2;
} Vk_Import_Native_बफर_Info_OHOS;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Get_Native_बफर_Info_OHOS {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    Vk_Device_स्मृतिः     स्मृतिः;
} Vk_स्मृतिः_Get_Native_बफर_Info_OHOS;

प्रकारनिर्देश संरचना VkExternalFormatOHOS {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint64_t           externalFormat;
} VkExternalFormatOHOS;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Native_बफर_Properties_OHOS)(VkDevice device, ध्रुव संरचना OH_Native_बफर* बफर_2, Vk_Native_बफर_Properties_OHOS* pProperties);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Native_बफर_OHOS)(VkDevice device, ध्रुव Vk_स्मृतिः_Get_Native_बफर_Info_OHOS* pInfo, संरचना OH_Native_बफर** p_बफर);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Native_बफर_Properties_OHOS(
    VkDevice                                    device,
    ध्रुव संरचना OH_Native_बफर*               बफर_2,
    Vk_Native_बफर_Properties_OHOS*               pProperties);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Native_बफर_OHOS(
    VkDevice                                    device,
    ध्रुव Vk_स्मृतिः_Get_Native_बफर_Info_OHOS*      pInfo,
    संरचना OH_Native_बफर**                    p_बफर);
#यदि_अन्तः
#यदि_अन्तः


// VK_OHOS_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_OHOS_surface 1

प्रकारनिर्देश संरचना Native_गवाक्षः OHNative_गवाक्षः;

#परिभाषय VK_OHOS_SURFACE_SPEC_संस्करणम्      1
#परिभाषय VK_OHOS_SURFACE_EXTENSION_NAME    "VK_OHOS_surface"

प्रकारनिर्देश VkFlags VkSurfaceCreateFlagsOHOS;

प्रकारनिर्देश संरचना VkSurfaceCreateInfoOHOS {
    VkStructureType             sType;
    ध्रुव शून्य*                 p_अग्र;
    VkSurfaceCreateFlagsOHOS    flags;
    OHNative_गवाक्षः*             गवाक्षः;
} VkSurfaceCreateInfoOHOS;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateSurfaceOHOS)(VkInstance instance, ध्रुव VkSurfaceCreateInfoOHOS* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateSurfaceOHOS(
    VkInstance                                  instance,
    ध्रुव VkSurfaceCreateInfoOHOS*              pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः

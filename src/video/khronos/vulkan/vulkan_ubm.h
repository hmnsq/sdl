#अगर_अघोषित VULKAN_UBM_H_
#घोषणा VULKAN_UBM_H_ 1

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



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_SEC_ubm_surface 1

#घोषणा VK_SEC_UBM_SURFACE_SPEC_VERSION   1
#घोषणा VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

प्रकार VkFlags VkUbmSurfaceCreateFlagsSEC;

प्रकार काष्ठा VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    स्थिर व्योम*                   p_अग्र;
    VkUbmSurfaceCreateFlagsSEC    flags;
    काष्ठा ubm_device*            device;
    काष्ठा ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, स्थिर VkUbmSurfaceCreateInfoSEC* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकार VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक, काष्ठा ubm_device* device);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    स्थिर VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक,
    काष्ठा ubm_device*                          device);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

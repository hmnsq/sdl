#నిర్వచితం_కాకపోతే VULKAN_UBM_H_
#నిర్వచించు VULKAN_UBM_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// VK_SEC_ubm_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_SEC_ubm_surface 1

#నిర్వచించు VK_SEC_UBM_SURFACE_SPEC_సంస్కరణ   1
#నిర్వచించు VK_SEC_UBM_SURFACE_EXTENSION_NAME "VK_SEC_ubm_surface"

రకనిర్వచనం VkFlags VkUbmSurfaceCreateFlagsSEC;

రకనిర్వచనం నిర్మాణం VkUbmSurfaceCreateInfoSEC {
    VkStructureType               sType;
    స్థిరరాశి శూన్య*                   p_తదుపరి;
    VkUbmSurfaceCreateFlagsSEC    flags;
    నిర్మాణం ubm_device*            device;
    నిర్మాణం ubm_surface*           surface;
} VkUbmSurfaceCreateInfoSEC;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateUbmSurfaceSEC)(VkInstance instance, స్థిరరాశి VkUbmSurfaceCreateInfoSEC* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ, నిర్మాణం ubm_device* device);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateUbmSurfaceSEC(
    VkInstance                                  instance,
    స్థిరరాశి VkUbmSurfaceCreateInfoSEC*            pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceUbmPresentationSupportSEC(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ,
    నిర్మాణం ubm_device*                          device);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు

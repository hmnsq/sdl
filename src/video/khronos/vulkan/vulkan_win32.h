#నిర్వచితం_కాకపోతే VULKAN_WIN32_H_
#నిర్వచించు VULKAN_WIN32_H_ 1

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



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_win32_surface 1

#నిర్వచించు VK_KHR_WIN32_SURFACE_SPEC_సంస్కరణ 6
#నిర్వచించు VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

రకనిర్వచనం VkFlags VkWin32SurfaceCreateFlagsKHR;

రకనిర్వచనం నిర్మాణం VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    స్థిరరాశి శూన్య*                     p_తదుపరి;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, స్థిరరాశి VkWin32SurfaceCreateInfoKHR* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
రకనిర్వచనం VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t వరుస_Family_సూచీ);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    స్థిరరాశి VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    వరుస_Family_సూచీ);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_external_జ్ఞాపకం_win32 1

#నిర్వచించు VK_KHR_EXTERNAL_జ్ఞాపకం_WIN32_SPEC_సంస్కరణ 1
#నిర్వచించు VK_KHR_EXTERNAL_జ్ఞాపకం_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

రకనిర్వచనం నిర్మాణం Vk_Import_జ్ఞాపకం_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_జ్ఞాపకం_Win32_Handle_Info_KHR;

రకనిర్వచనం నిర్మాణం Vk_Export_జ్ఞాపకం_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    స్థిరరాశి శూన్య*                   p_తదుపరి;
    స్థిరరాశి SECURITY_లక్షణాలు*    p_లక్షణాలు;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_జ్ఞాపకం_Win32_Handle_Info_KHR;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           జ్ఞాపకం_Type_బిట్లు;
} Vk_జ్ఞాపకం_Win32_Handle_Properties_KHR;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_Device_జ్ఞాపకం                        జ్ఞాపకం;
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు    handleType;
} Vk_జ్ఞాపకం_Get_Win32_Handle_Info_KHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Win32_Handle_KHR)(VkDevice device, స్థిరరాశి Vk_జ్ఞాపకం_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు handleType, HANDLE handle, Vk_జ్ఞాపకం_Win32_Handle_Properties_KHR* p_జ్ఞాపకం_Win32_Handle_Properties);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Win32_Handle_KHR(
    VkDevice                                    device,
    స్థిరరాశి Vk_జ్ఞాపకం_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు          handleType,
    HANDLE                                      handle,
    Vk_జ్ఞాపకం_Win32_Handle_Properties_KHR*           p_జ్ఞాపకం_Win32_Handle_Properties);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_win32_keyed_mutex 1

#నిర్వచించు VK_KHR_WIN32_KEYED_MUTEX_SPEC_సంస్కరణ 1
#నిర్వచించు VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

రకనిర్వచనం నిర్మాణం VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    స్థిరరాశి శూన్య*              p_తదుపరి;
    uint32_t                 acquire_లెక్క;
    స్థిరరాశి Vk_Device_జ్ఞాపకం*    pAcquireSyncs;
    స్థిరరాశి uint64_t*          p_Acquire_కీలకాలు;
    స్థిరరాశి uint32_t*          pAcquireTimeouts;
    uint32_t                 release_లెక్క;
    స్థిరరాశి Vk_Device_జ్ఞాపకం*    pReleaseSyncs;
    స్థిరరాశి uint64_t*          p_Release_కీలకాలు;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_external_semaphore_win32 1

#నిర్వచించు VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_సంస్కరణ 1
#నిర్వచించు VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

రకనిర్వచనం నిర్మాణం VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    స్థిరరాశి శూన్య*                              p_తదుపరి;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_బిట్లు    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

రకనిర్వచనం నిర్మాణం VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    స్థిరరాశి శూన్య*                   p_తదుపరి;
    స్థిరరాశి SECURITY_లక్షణాలు*    p_లక్షణాలు;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

రకనిర్వచనం నిర్మాణం VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    uint32_t           wait_Semaphore_విలువలు_లెక్క;
    స్థిరరాశి uint64_t*    p_Wait_Semaphore_విలువలు;
    uint32_t           signal_Semaphore_విలువలు_లెక్క;
    స్థిరరాశి uint64_t*    p_Signal_Semaphore_విలువలు;
} VkD3D12FenceSubmitInfoKHR;

రకనిర్వచనం నిర్మాణం VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    స్థిరరాశి శూన్య*                              p_తదుపరి;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_బిట్లు    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, స్థిరరాశి VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, స్థిరరాశి VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    స్థిరరాశి VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    స్థిరరాశి VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_KHR_external_fence_win32 1

#నిర్వచించు VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_సంస్కరణ 1
#నిర్వచించు VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

రకనిర్వచనం నిర్మాణం VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    స్థిరరాశి శూన్య*                          p_తదుపరి;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_బిట్లు    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

రకనిర్వచనం నిర్మాణం VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    స్థిరరాశి శూన్య*                   p_తదుపరి;
    స్థిరరాశి SECURITY_లక్షణాలు*    p_లక్షణాలు;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

రకనిర్వచనం నిర్మాణం VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    స్థిరరాశి శూన్య*                          p_తదుపరి;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_బిట్లు    handleType;
} VkFenceGetWin32HandleInfoKHR;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, స్థిరరాశి VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, స్థిరరాశి VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    స్థిరరాశి VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    స్థిరరాశి VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_NV_external_జ్ఞాపకం_win32 1

#నిర్వచించు VK_NV_EXTERNAL_జ్ఞాపకం_WIN32_SPEC_సంస్కరణ 1
#నిర్వచించు VK_NV_EXTERNAL_జ్ఞాపకం_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

రకనిర్వచనం నిర్మాణం Vk_Import_జ్ఞాపకం_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    స్థిరరాశి శూన్య*                          p_తదుపరి;
    Vk_External_జ్ఞాపకం_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_జ్ఞాపకం_Win32_Handle_Info_NV;

రకనిర్వచనం నిర్మాణం Vk_Export_జ్ఞాపకం_Win32_Handle_Info_NV {
    VkStructureType               sType;
    స్థిరరాశి శూన్య*                   p_తదుపరి;
    స్థిరరాశి SECURITY_లక్షణాలు*    p_లక్షణాలు;
    DWORD                         dwAccess;
} Vk_Export_జ్ఞాపకం_Win32_Handle_Info_NV;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Win32_Handle_NV)(VkDevice device, Vk_Device_జ్ఞాపకం జ్ఞాపకం, Vk_External_జ్ఞాపకం_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_జ్ఞాపకం                              జ్ఞాపకం,
    Vk_External_జ్ఞాపకం_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_NV_win32_keyed_mutex 1

#నిర్వచించు VK_NV_WIN32_KEYED_MUTEX_SPEC_సంస్కరణ 2
#నిర్వచించు VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

రకనిర్వచనం నిర్మాణం VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    స్థిరరాశి శూన్య*              p_తదుపరి;
    uint32_t                 acquire_లెక్క;
    స్థిరరాశి Vk_Device_జ్ఞాపకం*    pAcquireSyncs;
    స్థిరరాశి uint64_t*          p_Acquire_కీలకాలు;
    స్థిరరాశి uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_లెక్క;
    స్థిరరాశి Vk_Device_జ్ఞాపకం*    pReleaseSyncs;
    స్థిరరాశి uint64_t*          p_Release_కీలకాలు;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_EXT_నిండిన_screen_exclusive 1

#నిర్వచించు VK_EXT_నిండిన_SCREEN_EXCLUSIVE_SPEC_సంస్కరణ 4
#నిర్వచించు VK_EXT_నిండిన_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

రకనిర్వచనం గణన Vk_నిండిన_Screen_Exclusive_EXT {
    VK_నిండిన_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_నిండిన_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_నిండిన_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_నిండిన_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_నిండిన_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_నిండిన_Screen_Exclusive_EXT;

రకనిర్వచనం నిర్మాణం Vk_Surface_నిండిన_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    శూన్య*                       p_తదుపరి;
    Vk_నిండిన_Screen_Exclusive_EXT    నిండిన_Screen_Exclusive;
} Vk_Surface_నిండిన_Screen_Exclusive_Info_EXT;

రకనిర్వచనం నిర్మాణం Vk_Surface_Capabilities_నిండిన_Screen_Exclusive_EXT {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    VkBool32           నిండిన_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_నిండిన_Screen_Exclusive_EXT;

రకనిర్వచనం నిర్మాణం Vk_Surface_నిండిన_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    HMONITOR           hmonitor;
} Vk_Surface_నిండిన_Screen_Exclusive_Win32_Info_EXT;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, స్థిరరాశి VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_బహుళకం_లెక్క, Vk_Present_బహుళకం_KHR* pPresentModes);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Acquire_నిండిన_Screen_Exclusive_బహుళకం_EXT)(VkDevice device, VkSwapchainKHR swapchain);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Release_నిండిన_Screen_Exclusive_బహుళకం_EXT)(VkDevice device, VkSwapchainKHR swapchain);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_Device_సమూహం_Surface_Present_Modes2_EXT)(VkDevice device, స్థిరరాశి VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_సమూహం_Present_బహుళకం_Flags_KHR* pModes);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    స్థిరరాశి VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_బహుళకం_లెక్క,
    Vk_Present_బహుళకం_KHR*                           pPresentModes);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Acquire_నిండిన_Screen_Exclusive_బహుళకం_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Release_నిండిన_Screen_Exclusive_బహుళకం_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_Device_సమూహం_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    స్థిరరాశి VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_సమూహం_Present_బహుళకం_Flags_KHR*           pModes);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_NV_acquire_winrt_display 1

#నిర్వచించు VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_సంస్కరణ 1
#నిర్వచించు VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు

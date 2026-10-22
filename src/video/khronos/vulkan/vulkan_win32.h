#यदि_अपरिभाषितम् VULKAN_WIN32_H_
#परिभाषय VULKAN_WIN32_H_ 1

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



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_win32_surface 1

#परिभाषय VK_KHR_WIN32_SURFACE_SPEC_संस्करणम् 6
#परिभाषय VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

प्रकारनिर्देश VkFlags VkWin32SurfaceCreateFlagsKHR;

प्रकारनिर्देश संरचना VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ध्रुव शून्य*                     p_अग्र;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ध्रुव VkWin32SurfaceCreateInfoKHR* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकारनिर्देश VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ध्रुव VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक);
#यदि_अन्तः
#यदि_अन्तः


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_external_स्मृतिः_win32 1

#परिभाषय VK_KHR_EXTERNAL_स्मृतिः_WIN32_SPEC_संस्करणम् 1
#परिभाषय VK_KHR_EXTERNAL_स्मृतिः_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

प्रकारनिर्देश संरचना Vk_Import_स्मृतिः_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_स्मृतिः_Win32_Handle_Info_KHR;

प्रकारनिर्देश संरचना Vk_Export_स्मृतिः_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    ध्रुव SECURITY_गुणाः*    p_गुणाः;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_स्मृतिः_Win32_Handle_Info_KHR;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           स्मृतिः_Type_द्वयङ्काः;
} Vk_स्मृतिः_Win32_Handle_Properties_KHR;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_Device_स्मृतिः                        स्मृतिः;
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः    handleType;
} Vk_स्मृतिः_Get_Win32_Handle_Info_KHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Win32_Handle_KHR)(VkDevice device, ध्रुव Vk_स्मृतिः_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः handleType, HANDLE handle, Vk_स्मृतिः_Win32_Handle_Properties_KHR* p_स्मृतिः_Win32_Handle_Properties);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Win32_Handle_KHR(
    VkDevice                                    device,
    ध्रुव Vk_स्मृतिः_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः          handleType,
    HANDLE                                      handle,
    Vk_स्मृतिः_Win32_Handle_Properties_KHR*           p_स्मृतिः_Win32_Handle_Properties);
#यदि_अन्तः
#यदि_अन्तः


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_win32_keyed_mutex 1

#परिभाषय VK_KHR_WIN32_KEYED_MUTEX_SPEC_संस्करणम् 1
#परिभाषय VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

प्रकारनिर्देश संरचना VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ध्रुव शून्य*              p_अग्र;
    uint32_t                 acquire_गणनम्;
    ध्रुव Vk_Device_स्मृतिः*    pAcquireSyncs;
    ध्रुव uint64_t*          p_Acquire_कुञ्चिकाः;
    ध्रुव uint32_t*          pAcquireTimeouts;
    uint32_t                 release_गणनम्;
    ध्रुव Vk_Device_स्मृतिः*    pReleaseSyncs;
    ध्रुव uint64_t*          p_Release_कुञ्चिकाः;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_external_semaphore_win32 1

#परिभाषय VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_संस्करणम् 1
#परिभाषय VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

प्रकारनिर्देश संरचना VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ध्रुव शून्य*                              p_अग्र;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_द्वयङ्काः    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

प्रकारनिर्देश संरचना VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    ध्रुव SECURITY_गुणाः*    p_गुणाः;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

प्रकारनिर्देश संरचना VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    uint32_t           wait_Semaphore_मानानि_गणनम्;
    ध्रुव uint64_t*    p_Wait_Semaphore_मानानि;
    uint32_t           signal_Semaphore_मानानि_गणनम्;
    ध्रुव uint64_t*    p_Signal_Semaphore_मानानि;
} VkD3D12FenceSubmitInfoKHR;

प्रकारनिर्देश संरचना VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ध्रुव शून्य*                              p_अग्र;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_द्वयङ्काः    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ध्रुव VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ध्रुव VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ध्रुव VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ध्रुव VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#यदि_अन्तः
#यदि_अन्तः


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_KHR_external_fence_win32 1

#परिभाषय VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_संस्करणम् 1
#परिभाषय VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

प्रकारनिर्देश संरचना VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ध्रुव शून्य*                          p_अग्र;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_द्वयङ्काः    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

प्रकारनिर्देश संरचना VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    ध्रुव SECURITY_गुणाः*    p_गुणाः;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

प्रकारनिर्देश संरचना VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ध्रुव शून्य*                          p_अग्र;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_द्वयङ्काः    handleType;
} VkFenceGetWin32HandleInfoKHR;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ध्रुव VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ध्रुव VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ध्रुव VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ध्रुव VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#यदि_अन्तः
#यदि_अन्तः


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_NV_external_स्मृतिः_win32 1

#परिभाषय VK_NV_EXTERNAL_स्मृतिः_WIN32_SPEC_संस्करणम् 1
#परिभाषय VK_NV_EXTERNAL_स्मृतिः_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

प्रकारनिर्देश संरचना Vk_Import_स्मृतिः_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ध्रुव शून्य*                          p_अग्र;
    Vk_External_स्मृतिः_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_स्मृतिः_Win32_Handle_Info_NV;

प्रकारनिर्देश संरचना Vk_Export_स्मृतिः_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ध्रुव शून्य*                   p_अग्र;
    ध्रुव SECURITY_गुणाः*    p_गुणाः;
    DWORD                         dwAccess;
} Vk_Export_स्मृतिः_Win32_Handle_Info_NV;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Win32_Handle_NV)(VkDevice device, Vk_Device_स्मृतिः स्मृतिः, Vk_External_स्मृतिः_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_स्मृतिः                              स्मृतिः,
    Vk_External_स्मृतिः_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#यदि_अन्तः
#यदि_अन्तः


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_NV_win32_keyed_mutex 1

#परिभाषय VK_NV_WIN32_KEYED_MUTEX_SPEC_संस्करणम् 2
#परिभाषय VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

प्रकारनिर्देश संरचना VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ध्रुव शून्य*              p_अग्र;
    uint32_t                 acquire_गणनम्;
    ध्रुव Vk_Device_स्मृतिः*    pAcquireSyncs;
    ध्रुव uint64_t*          p_Acquire_कुञ्चिकाः;
    ध्रुव uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_गणनम्;
    ध्रुव Vk_Device_स्मृतिः*    pReleaseSyncs;
    ध्रुव uint64_t*          p_Release_कुञ्चिकाः;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_EXT_पूर्णम्_screen_exclusive 1

#परिभाषय VK_EXT_पूर्णम्_SCREEN_EXCLUSIVE_SPEC_संस्करणम् 4
#परिभाषय VK_EXT_पूर्णम्_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

प्रकारनिर्देश गणना Vk_पूर्णम्_Screen_Exclusive_EXT {
    VK_पूर्णम्_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_पूर्णम्_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_पूर्णम्_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_पूर्णम्_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_पूर्णम्_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_पूर्णम्_Screen_Exclusive_EXT;

प्रकारनिर्देश संरचना Vk_Surface_पूर्णम्_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    शून्य*                       p_अग्र;
    Vk_पूर्णम्_Screen_Exclusive_EXT    पूर्णम्_Screen_Exclusive;
} Vk_Surface_पूर्णम्_Screen_Exclusive_Info_EXT;

प्रकारनिर्देश संरचना Vk_Surface_Capabilities_पूर्णम्_Screen_Exclusive_EXT {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    VkBool32           पूर्णम्_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_पूर्णम्_Screen_Exclusive_EXT;

प्रकारनिर्देश संरचना Vk_Surface_पूर्णम्_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    HMONITOR           hmonitor;
} Vk_Surface_पूर्णम्_Screen_Exclusive_Win32_Info_EXT;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ध्रुव VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_बहुलकम्_गणनम्, Vk_Present_बहुलकम्_KHR* pPresentModes);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Acquire_पूर्णम्_Screen_Exclusive_बहुलकम्_EXT)(VkDevice device, VkSwapchainKHR swapchain);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Release_पूर्णम्_Screen_Exclusive_बहुलकम्_EXT)(VkDevice device, VkSwapchainKHR swapchain);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_Device_गणः_Surface_Present_Modes2_EXT)(VkDevice device, ध्रुव VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_गणः_Present_बहुलकम्_Flags_KHR* pModes);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ध्रुव VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_बहुलकम्_गणनम्,
    Vk_Present_बहुलकम्_KHR*                           pPresentModes);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Acquire_पूर्णम्_Screen_Exclusive_बहुलकम्_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Release_पूर्णम्_Screen_Exclusive_बहुलकम्_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_Device_गणः_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ध्रुव VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_गणः_Present_बहुलकम्_Flags_KHR*           pModes);
#यदि_अन्तः
#यदि_अन्तः


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_NV_acquire_winrt_display 1

#परिभाषय VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_संस्करणम् 1
#परिभाषय VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः

#अगर_अघोषित VULKAN_WIN32_H_
#घोषणा VULKAN_WIN32_H_ 1

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



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_win32_surface 1

#घोषणा VK_KHR_WIN32_SURFACE_SPEC_VERSION 6
#घोषणा VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

प्रकार VkFlags VkWin32SurfaceCreateFlagsKHR;

प्रकार काष्ठा VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    स्थिर व्योम*                     p_अग्र;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, स्थिर VkWin32SurfaceCreateInfoKHR* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
प्रकार VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_सूचकांक);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    स्थिर VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_सूचकांक);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_external_memory_win32 1

#घोषणा VK_KHR_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#घोषणा VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

प्रकार काष्ठा VkImportMemoryWin32HandleInfoKHR {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} VkImportMemoryWin32HandleInfoKHR;

प्रकार काष्ठा VkExportMemoryWin32HandleInfoKHR {
    VkStructureType               sType;
    स्थिर व्योम*                   p_अग्र;
    स्थिर SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportMemoryWin32HandleInfoKHR;

प्रकार काष्ठा VkMemoryWin32HandlePropertiesKHR {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           memoryTypeBits;
} VkMemoryWin32HandlePropertiesKHR;

प्रकार काष्ठा VkMemoryGetWin32HandleInfoKHR {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetWin32HandleInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryWin32HandleKHR)(VkDevice device, स्थिर VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryWin32HandlePropertiesKHR)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryWin32HandleKHR(
    VkDevice                                    device,
    स्थिर VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryWin32HandlePropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    HANDLE                                      handle,
    VkMemoryWin32HandlePropertiesKHR*           pMemoryWin32HandleProperties);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_win32_keyed_mutex 1

#घोषणा VK_KHR_WIN32_KEYED_MUTEX_SPEC_VERSION 1
#घोषणा VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

प्रकार काष्ठा VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    स्थिर व्योम*              p_अग्र;
    uint32_t                 acquire_गिनती;
    स्थिर VkDeviceMemory*    pAcquireSyncs;
    स्थिर uint64_t*          p_Acquire_कुंजियाँ;
    स्थिर uint32_t*          pAcquireTimeouts;
    uint32_t                 release_गिनती;
    स्थिर VkDeviceMemory*    pReleaseSyncs;
    स्थिर uint64_t*          p_Release_कुंजियाँ;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_external_semaphore_win32 1

#घोषणा VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION 1
#घोषणा VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

प्रकार काष्ठा VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    स्थिर व्योम*                              p_अग्र;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

प्रकार काष्ठा VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    स्थिर व्योम*                   p_अग्र;
    स्थिर SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

प्रकार काष्ठा VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    uint32_t           wait_Semaphore_मूल्यावली_गिनती;
    स्थिर uint64_t*    p_Wait_Semaphore_मूल्यावली;
    uint32_t           signal_Semaphore_मूल्यावली_गिनती;
    स्थिर uint64_t*    p_Signal_Semaphore_मूल्यावली;
} VkD3D12FenceSubmitInfoKHR;

प्रकार काष्ठा VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    स्थिर व्योम*                              p_अग्र;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, स्थिर VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, स्थिर VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    स्थिर VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    स्थिर VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_KHR_external_fence_win32 1

#घोषणा VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_VERSION 1
#घोषणा VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

प्रकार काष्ठा VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    स्थिर व्योम*                          p_अग्र;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    VkExternalFenceHandleTypeFlagBits    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

प्रकार काष्ठा VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    स्थिर व्योम*                   p_अग्र;
    स्थिर SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

प्रकार काष्ठा VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    स्थिर व्योम*                          p_अग्र;
    VkFence                              fence;
    VkExternalFenceHandleTypeFlagBits    handleType;
} VkFenceGetWin32HandleInfoKHR;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, स्थिर VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, स्थिर VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    स्थिर VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    स्थिर VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_NV_external_memory_win32 1

#घोषणा VK_NV_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#घोषणा VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

प्रकार काष्ठा VkImportMemoryWin32HandleInfoNV {
    VkStructureType                      sType;
    स्थिर व्योम*                          p_अग्र;
    VkExternalMemoryHandleTypeFlagsNV    handleType;
    HANDLE                               handle;
} VkImportMemoryWin32HandleInfoNV;

प्रकार काष्ठा VkExportMemoryWin32HandleInfoNV {
    VkStructureType               sType;
    स्थिर व्योम*                   p_अग्र;
    स्थिर SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
} VkExportMemoryWin32HandleInfoNV;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryWin32HandleNV)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryWin32HandleNV(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkExternalMemoryHandleTypeFlagsNV           handleType,
    HANDLE*                                     pHandle);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_NV_win32_keyed_mutex 1

#घोषणा VK_NV_WIN32_KEYED_MUTEX_SPEC_VERSION 2
#घोषणा VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

प्रकार काष्ठा VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    स्थिर व्योम*              p_अग्र;
    uint32_t                 acquire_गिनती;
    स्थिर VkDeviceMemory*    pAcquireSyncs;
    स्थिर uint64_t*          p_Acquire_कुंजियाँ;
    स्थिर uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_गिनती;
    स्थिर VkDeviceMemory*    pReleaseSyncs;
    स्थिर uint64_t*          p_Release_कुंजियाँ;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_EXT_full_screen_exclusive 1

#घोषणा VK_EXT_FULL_SCREEN_EXCLUSIVE_SPEC_VERSION 4
#घोषणा VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

प्रकार क्रमागत VkFullScreenExclusiveEXT {
    VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_FULL_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkFullScreenExclusiveEXT;

प्रकार काष्ठा VkSurfaceFullScreenExclusiveInfoEXT {
    VkStructureType             sType;
    व्योम*                       p_अग्र;
    VkFullScreenExclusiveEXT    fullScreenExclusive;
} VkSurfaceFullScreenExclusiveInfoEXT;

प्रकार काष्ठा VkSurfaceCapabilitiesFullScreenExclusiveEXT {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    VkBool32           fullScreenExclusiveSupported;
} VkSurfaceCapabilitiesFullScreenExclusiveEXT;

प्रकार काष्ठा VkSurfaceFullScreenExclusiveWin32InfoEXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    HMONITOR           hmonitor;
} VkSurfaceFullScreenExclusiveWin32InfoEXT;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, स्थिर VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_Mode_गिनती, VkPresentModeKHR* pPresentModes);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkAcquireFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkReleaseFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetDeviceGroupSurfacePresentModes2EXT)(VkDevice device, स्थिर VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    स्थिर VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_Mode_गिनती,
    VkPresentModeKHR*                           pPresentModes);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkAcquireFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkReleaseFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetDeviceGroupSurfacePresentModes2EXT(
    VkDevice                                    device,
    स्थिर VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkDeviceGroupPresentModeFlagsKHR*           pModes);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_NV_acquire_winrt_display 1

#घोषणा VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_VERSION 1
#घोषणा VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

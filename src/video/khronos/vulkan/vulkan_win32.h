#ifndef VULKAN_WIN32_H_
#define VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_win32_surface 1

#define VK_KHR_WIN32_SURFACE_SPEC_VERSION 6
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkWin32SurfaceCreateFlagsKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ಧ್ರುವ ಶೂನ್ಯ*                     pNext;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ಧ್ರುವ VkWin32SurfaceCreateInfoKHR* pCreateInfo, ಧ್ರುವ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರನಿರ್ದೇಶ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ಧ್ರುವ VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ಧ್ರುವ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex);
#endif
#endif


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_memory_win32 1

#define VK_KHR_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportMemoryWin32HandleInfoKHR {
    VkStructureType                       sType;
    ಧ್ರುವ ಶೂನ್ಯ*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} VkImportMemoryWin32HandleInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExportMemoryWin32HandleInfoKHR {
    VkStructureType               sType;
    ಧ್ರುವ ಶೂನ್ಯ*                   pNext;
    ಧ್ರುವ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportMemoryWin32HandleInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkMemoryWin32HandlePropertiesKHR {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryWin32HandlePropertiesKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkMemoryGetWin32HandleInfoKHR {
    VkStructureType                       sType;
    ಧ್ರುವ ಶೂನ್ಯ*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetWin32HandleInfoKHR;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleKHR)(VkDevice device, ಧ್ರುವ VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandlePropertiesKHR)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHR(
    VkDevice                                    device,
    ಧ್ರುವ VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandlePropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    HANDLE                                      handle,
    VkMemoryWin32HandlePropertiesKHR*           pMemoryWin32HandleProperties);
#endif
#endif


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_win32_keyed_mutex 1

#define VK_KHR_WIN32_KEYED_MUTEX_SPEC_VERSION 1
#define VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ಧ್ರುವ ಶೂನ್ಯ*              pNext;
    uint32_t                 acquire_ಎಣಿಕೆ;
    ಧ್ರುವ VkDeviceMemory*    pAcquireSyncs;
    ಧ್ರುವ uint64_t*          p_Acquire_ಕೀಲಿಗಳು;
    ಧ್ರುವ uint32_t*          pAcquireTimeouts;
    uint32_t                 release_ಎಣಿಕೆ;
    ಧ್ರುವ VkDeviceMemory*    pReleaseSyncs;
    ಧ್ರುವ uint64_t*          p_Release_ಕೀಲಿಗಳು;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore_win32 1

#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ಧ್ರುವ ಶೂನ್ಯ*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ಧ್ರುವ ಶೂನ್ಯ*                   pNext;
    ಧ್ರುವ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    uint32_t           wait_Semaphore_ಮೌಲ್ಯಗಳು_ಎಣಿಕೆ;
    ಧ್ರುವ uint64_t*    p_Wait_Semaphore_ಮೌಲ್ಯಗಳು;
    uint32_t           signal_Semaphore_ಮೌಲ್ಯಗಳು_ಎಣಿಕೆ;
    ಧ್ರುವ uint64_t*    p_Signal_Semaphore_ಮೌಲ್ಯಗಳು;
} VkD3D12FenceSubmitInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ಧ್ರುವ ಶೂನ್ಯ*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ಧ್ರುವ VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ಧ್ರುವ VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ಧ್ರುವ VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ಧ್ರುವ VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence_win32 1

#define VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ಧ್ರುವ ಶೂನ್ಯ*                          pNext;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    VkExternalFenceHandleTypeFlagBits    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ಧ್ರುವ ಶೂನ್ಯ*                   pNext;
    ಧ್ರುವ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ಧ್ರುವ ಶೂನ್ಯ*                          pNext;
    VkFence                              fence;
    VkExternalFenceHandleTypeFlagBits    handleType;
} VkFenceGetWin32HandleInfoKHR;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ಧ್ರುವ VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ಧ್ರುವ VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ಧ್ರುವ VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ಧ್ರುವ VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory_win32 1

#define VK_NV_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkImportMemoryWin32HandleInfoNV {
    VkStructureType                      sType;
    ಧ್ರುವ ಶೂನ್ಯ*                          pNext;
    VkExternalMemoryHandleTypeFlagsNV    handleType;
    HANDLE                               handle;
} VkImportMemoryWin32HandleInfoNV;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkExportMemoryWin32HandleInfoNV {
    VkStructureType               sType;
    ಧ್ರುವ ಶೂನ್ಯ*                   pNext;
    ಧ್ರುವ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
} VkExportMemoryWin32HandleInfoNV;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleNV)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleNV(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkExternalMemoryHandleTypeFlagsNV           handleType,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_win32_keyed_mutex 1

#define VK_NV_WIN32_KEYED_MUTEX_SPEC_VERSION 2
#define VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ಧ್ರುವ ಶೂನ್ಯ*              pNext;
    uint32_t                 acquire_ಎಣಿಕೆ;
    ಧ್ರುವ VkDeviceMemory*    pAcquireSyncs;
    ಧ್ರುವ uint64_t*          p_Acquire_ಕೀಲಿಗಳು;
    ಧ್ರುವ uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_ಎಣಿಕೆ;
    ಧ್ರುವ VkDeviceMemory*    pReleaseSyncs;
    ಧ್ರುವ uint64_t*          p_Release_ಕೀಲಿಗಳು;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_full_screen_exclusive 1

#define VK_EXT_FULL_SCREEN_EXCLUSIVE_SPEC_VERSION 4
#define VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkFullScreenExclusiveEXT {
    VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_FULL_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkFullScreenExclusiveEXT;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSurfaceFullScreenExclusiveInfoEXT {
    VkStructureType             sType;
    ಶೂನ್ಯ*                       pNext;
    VkFullScreenExclusiveEXT    fullScreenExclusive;
} VkSurfaceFullScreenExclusiveInfoEXT;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSurfaceCapabilitiesFullScreenExclusiveEXT {
    VkStructureType    sType;
    ಶೂನ್ಯ*              pNext;
    VkBool32           fullScreenExclusiveSupported;
} VkSurfaceCapabilitiesFullScreenExclusiveEXT;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkSurfaceFullScreenExclusiveWin32InfoEXT {
    VkStructureType    sType;
    ಧ್ರುವ ಶೂನ್ಯ*        pNext;
    HMONITOR           hmonitor;
} VkSurfaceFullScreenExclusiveWin32InfoEXT;


ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ಧ್ರುವ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_Mode_ಎಣಿಕೆ, VkPresentModeKHR* pPresentModes);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkAcquireFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkReleaseFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetDeviceGroupSurfacePresentModes2EXT)(VkDevice device, ಧ್ರುವ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ಧ್ರುವ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_Mode_ಎಣಿಕೆ,
    VkPresentModeKHR*                           pPresentModes);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkAcquireFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkReleaseFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupSurfacePresentModes2EXT(
    VkDevice                                    device,
    ಧ್ರುವ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkDeviceGroupPresentModeFlagsKHR*           pModes);
#endif
#endif


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_acquire_winrt_display 1

#define VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_VERSION 1
#define VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

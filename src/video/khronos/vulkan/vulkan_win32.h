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
বাহ্যিক "C" {
#endif



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_win32_surface 1

#define VK_KHR_WIN32_SURFACE_SPEC_VERSION 6
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

প্রকারলেখ VkFlags VkWin32SurfaceCreateFlagsKHR;

প্রকারলেখ কাঠামো VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ধ্রুবক শূন্য*                     p_পরবর্তী;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ধ্রুবক VkWin32SurfaceCreateInfoKHR* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
প্রকারলেখ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queue_Family_সূচক);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ধ্রুবক VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queue_Family_সূচক);
#endif
#endif


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_memory_win32 1

#define VK_KHR_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

প্রকারলেখ কাঠামো VkImportMemoryWin32HandleInfoKHR {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} VkImportMemoryWin32HandleInfoKHR;

প্রকারলেখ কাঠামো VkExportMemoryWin32HandleInfoKHR {
    VkStructureType               sType;
    ধ্রুবক শূন্য*                   p_পরবর্তী;
    ধ্রুবক SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportMemoryWin32HandleInfoKHR;

প্রকারলেখ কাঠামো VkMemoryWin32HandlePropertiesKHR {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           memoryTypeBits;
} VkMemoryWin32HandlePropertiesKHR;

প্রকারলেখ কাঠামো VkMemoryGetWin32HandleInfoKHR {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetWin32HandleInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryWin32HandleKHR)(VkDevice device, ধ্রুবক VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryWin32HandlePropertiesKHR)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryWin32HandleKHR(
    VkDevice                                    device,
    ধ্রুবক VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryWin32HandlePropertiesKHR(
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

প্রকারলেখ কাঠামো VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ধ্রুবক শূন্য*              p_পরবর্তী;
    uint32_t                 acquire_গুনতি;
    ধ্রুবক VkDeviceMemory*    pAcquireSyncs;
    ধ্রুবক uint64_t*          p_Acquire_চাবিগুলি;
    ধ্রুবক uint32_t*          pAcquireTimeouts;
    uint32_t                 release_গুনতি;
    ধ্রুবক VkDeviceMemory*    pReleaseSyncs;
    ধ্রুবক uint64_t*          p_Release_চাবিগুলি;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore_win32 1

#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

প্রকারলেখ কাঠামো VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ধ্রুবক শূন্য*                              p_পরবর্তী;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

প্রকারলেখ কাঠামো VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ধ্রুবক শূন্য*                   p_পরবর্তী;
    ধ্রুবক SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

প্রকারলেখ কাঠামো VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    uint32_t           wait_Semaphore_মানসমূহ_গুনতি;
    ধ্রুবক uint64_t*    p_Wait_Semaphore_মানসমূহ;
    uint32_t           signal_Semaphore_মানসমূহ_গুনতি;
    ধ্রুবক uint64_t*    p_Signal_Semaphore_মানসমূহ;
} VkD3D12FenceSubmitInfoKHR;

প্রকারলেখ কাঠামো VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ধ্রুবক শূন্য*                              p_পরবর্তী;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ধ্রুবক VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ধ্রুবক VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ধ্রুবক VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ধ্রুবক VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence_win32 1

#define VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

প্রকারলেখ কাঠামো VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ধ্রুবক শূন্য*                          p_পরবর্তী;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    VkExternalFenceHandleTypeFlagBits    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

প্রকারলেখ কাঠামো VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ধ্রুবক শূন্য*                   p_পরবর্তী;
    ধ্রুবক SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

প্রকারলেখ কাঠামো VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ধ্রুবক শূন্য*                          p_পরবর্তী;
    VkFence                              fence;
    VkExternalFenceHandleTypeFlagBits    handleType;
} VkFenceGetWin32HandleInfoKHR;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ধ্রুবক VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ধ্রুবক VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ধ্রুবক VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ধ্রুবক VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory_win32 1

#define VK_NV_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

প্রকারলেখ কাঠামো VkImportMemoryWin32HandleInfoNV {
    VkStructureType                      sType;
    ধ্রুবক শূন্য*                          p_পরবর্তী;
    VkExternalMemoryHandleTypeFlagsNV    handleType;
    HANDLE                               handle;
} VkImportMemoryWin32HandleInfoNV;

প্রকারলেখ কাঠামো VkExportMemoryWin32HandleInfoNV {
    VkStructureType               sType;
    ধ্রুবক শূন্য*                   p_পরবর্তী;
    ধ্রুবক SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
} VkExportMemoryWin32HandleInfoNV;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryWin32HandleNV)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryWin32HandleNV(
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

প্রকারলেখ কাঠামো VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ধ্রুবক শূন্য*              p_পরবর্তী;
    uint32_t                 acquire_গুনতি;
    ধ্রুবক VkDeviceMemory*    pAcquireSyncs;
    ধ্রুবক uint64_t*          p_Acquire_চাবিগুলি;
    ধ্রুবক uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_গুনতি;
    ধ্রুবক VkDeviceMemory*    pReleaseSyncs;
    ধ্রুবক uint64_t*          p_Release_চাবিগুলি;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_full_screen_exclusive 1

#define VK_EXT_FULL_SCREEN_EXCLUSIVE_SPEC_VERSION 4
#define VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

প্রকারলেখ গণনা VkFullScreenExclusiveEXT {
    VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_FULL_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkFullScreenExclusiveEXT;

প্রকারলেখ কাঠামো VkSurfaceFullScreenExclusiveInfoEXT {
    VkStructureType             sType;
    শূন্য*                       p_পরবর্তী;
    VkFullScreenExclusiveEXT    fullScreenExclusive;
} VkSurfaceFullScreenExclusiveInfoEXT;

প্রকারলেখ কাঠামো VkSurfaceCapabilitiesFullScreenExclusiveEXT {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    VkBool32           fullScreenExclusiveSupported;
} VkSurfaceCapabilitiesFullScreenExclusiveEXT;

প্রকারলেখ কাঠামো VkSurfaceFullScreenExclusiveWin32InfoEXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    HMONITOR           hmonitor;
} VkSurfaceFullScreenExclusiveWin32InfoEXT;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ধ্রুবক VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_Mode_গুনতি, VkPresentModeKHR* pPresentModes);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkAcquireFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkReleaseFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetDeviceGroupSurfacePresentModes2EXT)(VkDevice device, ধ্রুবক VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ধ্রুবক VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_Mode_গুনতি,
    VkPresentModeKHR*                           pPresentModes);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkAcquireFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkReleaseFullScreenExclusiveModeEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetDeviceGroupSurfacePresentModes2EXT(
    VkDevice                                    device,
    ধ্রুবক VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkDeviceGroupPresentModeFlagsKHR*           pModes);
#endif
#endif


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_acquire_winrt_display 1

#define VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_VERSION 1
#define VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

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
બાહ્ય "C" {
#endif



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_win32_surface 1

#define VK_KHR_WIN32_SURFACE_SPEC_VERSION 6
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

પ્રકારવ્યાખ્યા VkFlags VkWin32SurfaceCreateFlagsKHR;

પ્રકારવ્યાખ્યા સંરચના VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    અચલ શૂન્ય*                     pNext;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, અચલ VkWin32SurfaceCreateInfoKHR* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
પ્રકારવ્યાખ્યા VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    અચલ VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
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

પ્રકારવ્યાખ્યા સંરચના VkImportMemoryWin32HandleInfoKHR {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} VkImportMemoryWin32HandleInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkExportMemoryWin32HandleInfoKHR {
    VkStructureType               sType;
    અચલ શૂન્ય*                   pNext;
    અચલ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportMemoryWin32HandleInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkMemoryWin32HandlePropertiesKHR {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryWin32HandlePropertiesKHR;

પ્રકારવ્યાખ્યા સંરચના VkMemoryGetWin32HandleInfoKHR {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetWin32HandleInfoKHR;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleKHR)(VkDevice device, અચલ VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandlePropertiesKHR)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHR(
    VkDevice                                    device,
    અચલ VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
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

પ્રકારવ્યાખ્યા સંરચના VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    અચલ શૂન્ય*              pNext;
    uint32_t                 acquire_ગણતરી;
    અચલ VkDeviceMemory*    pAcquireSyncs;
    અચલ uint64_t*          p_Acquire_ચાવીઓ;
    અચલ uint32_t*          pAcquireTimeouts;
    uint32_t                 release_ગણતરી;
    અચલ VkDeviceMemory*    pReleaseSyncs;
    અચલ uint64_t*          p_Release_ચાવીઓ;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore_win32 1

#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

પ્રકારવ્યાખ્યા સંરચના VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    અચલ શૂન્ય*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    અચલ શૂન્ય*                   pNext;
    અચલ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    uint32_t           wait_Semaphore_કિંમતો_ગણતરી;
    અચલ uint64_t*    p_Wait_Semaphore_કિંમતો;
    uint32_t           signal_Semaphore_કિંમતો_ગણતરી;
    અચલ uint64_t*    p_Signal_Semaphore_કિંમતો;
} VkD3D12FenceSubmitInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    અચલ શૂન્ય*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, અચલ VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, અચલ VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    અચલ VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    અચલ VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence_win32 1

#define VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

પ્રકારવ્યાખ્યા સંરચના VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    અચલ શૂન્ય*                          pNext;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    VkExternalFenceHandleTypeFlagBits    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    અચલ શૂન્ય*                   pNext;
    અચલ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

પ્રકારવ્યાખ્યા સંરચના VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    અચલ શૂન્ય*                          pNext;
    VkFence                              fence;
    VkExternalFenceHandleTypeFlagBits    handleType;
} VkFenceGetWin32HandleInfoKHR;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, અચલ VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, અચલ VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    અચલ VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    અચલ VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory_win32 1

#define VK_NV_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

પ્રકારવ્યાખ્યા સંરચના VkImportMemoryWin32HandleInfoNV {
    VkStructureType                      sType;
    અચલ શૂન્ય*                          pNext;
    VkExternalMemoryHandleTypeFlagsNV    handleType;
    HANDLE                               handle;
} VkImportMemoryWin32HandleInfoNV;

પ્રકારવ્યાખ્યા સંરચના VkExportMemoryWin32HandleInfoNV {
    VkStructureType               sType;
    અચલ શૂન્ય*                   pNext;
    અચલ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
} VkExportMemoryWin32HandleInfoNV;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleNV)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);

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

પ્રકારવ્યાખ્યા સંરચના VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    અચલ શૂન્ય*              pNext;
    uint32_t                 acquire_ગણતરી;
    અચલ VkDeviceMemory*    pAcquireSyncs;
    અચલ uint64_t*          p_Acquire_ચાવીઓ;
    અચલ uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_ગણતરી;
    અચલ VkDeviceMemory*    pReleaseSyncs;
    અચલ uint64_t*          p_Release_ચાવીઓ;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_full_screen_exclusive 1

#define VK_EXT_FULL_SCREEN_EXCLUSIVE_SPEC_VERSION 4
#define VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

પ્રકારવ્યાખ્યા ગણના VkFullScreenExclusiveEXT {
    VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_FULL_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkFullScreenExclusiveEXT;

પ્રકારવ્યાખ્યા સંરચના VkSurfaceFullScreenExclusiveInfoEXT {
    VkStructureType             sType;
    શૂન્ય*                       pNext;
    VkFullScreenExclusiveEXT    fullScreenExclusive;
} VkSurfaceFullScreenExclusiveInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkSurfaceCapabilitiesFullScreenExclusiveEXT {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    VkBool32           fullScreenExclusiveSupported;
} VkSurfaceCapabilitiesFullScreenExclusiveEXT;

પ્રકારવ્યાખ્યા સંરચના VkSurfaceFullScreenExclusiveWin32InfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    HMONITOR           hmonitor;
} VkSurfaceFullScreenExclusiveWin32InfoEXT;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, અચલ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_Mode_ગણતરી, VkPresentModeKHR* pPresentModes);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkAcquireFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkReleaseFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetDeviceGroupSurfacePresentModes2EXT)(VkDevice device, અચલ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    અચલ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_Mode_ગણતરી,
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
    અચલ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkDeviceGroupPresentModeFlagsKHR*           pModes);
#endif
#endif


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_acquire_winrt_display 1

#define VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_VERSION 1
#define VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

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

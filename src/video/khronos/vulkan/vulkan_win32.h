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
ବାହ୍ୟ "C" {
#endif



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_win32_surface 1

#define VK_KHR_WIN32_SURFACE_SPEC_VERSION 6
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkWin32SurfaceCreateFlagsKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ଅଚଳ ଶୂନ୍ୟ*                     pNext;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ଅଚଳ VkWin32SurfaceCreateInfoKHR* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ଅଚଳ VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMemoryWin32HandleInfoKHR {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} VkImportMemoryWin32HandleInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMemoryWin32HandleInfoKHR {
    VkStructureType               sType;
    ଅଚଳ ଶୂନ୍ୟ*                   pNext;
    ଅଚଳ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportMemoryWin32HandleInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryWin32HandlePropertiesKHR {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryWin32HandlePropertiesKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryGetWin32HandleInfoKHR {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetWin32HandleInfoKHR;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleKHR)(VkDevice device, ଅଚଳ VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandlePropertiesKHR)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHR(
    VkDevice                                    device,
    ଅଚଳ VkMemoryGetWin32HandleInfoKHR*        pGetWin32HandleInfo,
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ଅଚଳ ଶୂନ୍ୟ*              pNext;
    uint32_t                 acquire_ଗଣନା;
    ଅଚଳ VkDeviceMemory*    pAcquireSyncs;
    ଅଚଳ uint64_t*          p_Acquire_ଚାବିଗୁଡ଼ିକ;
    ଅଚଳ uint32_t*          pAcquireTimeouts;
    uint32_t                 release_ଗଣନା;
    ଅଚଳ VkDeviceMemory*    pReleaseSyncs;
    ଅଚଳ uint64_t*          p_Release_ଚାବିଗୁଡ଼ିକ;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_semaphore_win32 1

#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ଅଚଳ ଶୂନ୍ୟ*                              pNext;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ଅଚଳ ଶୂନ୍ୟ*                   pNext;
    ଅଚଳ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    uint32_t           wait_Semaphore_ମୂଲ୍ୟଗୁଡ଼ିକ_ଗଣନା;
    ଅଚଳ uint64_t*    p_Wait_Semaphore_ମୂଲ୍ୟଗୁଡ଼ିକ;
    uint32_t           signal_Semaphore_ମୂଲ୍ୟଗୁଡ଼ିକ_ଗଣନା;
    ଅଚଳ uint64_t*    p_Signal_Semaphore_ମୂଲ୍ୟଗୁଡ଼ିକ;
} VkD3D12FenceSubmitInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ଅଚଳ ଶୂନ୍ୟ*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagBits    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ଅଚଳ VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ଅଚଳ VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ଅଚଳ VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ଅଚଳ VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_KHR_external_fence_win32 1

#define VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_VERSION 1
#define VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ଅଚଳ ଶୂନ୍ୟ*                          pNext;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    VkExternalFenceHandleTypeFlagBits    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ଅଚଳ ଶୂନ୍ୟ*                   pNext;
    ଅଚଳ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ଅଚଳ ଶୂନ୍ୟ*                          pNext;
    VkFence                              fence;
    VkExternalFenceHandleTypeFlagBits    handleType;
} VkFenceGetWin32HandleInfoKHR;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ଅଚଳ VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ଅଚଳ VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ଅଚଳ VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ଅଚଳ VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#endif
#endif


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_external_memory_win32 1

#define VK_NV_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMemoryWin32HandleInfoNV {
    VkStructureType                      sType;
    ଅଚଳ ଶୂନ୍ୟ*                          pNext;
    VkExternalMemoryHandleTypeFlagsNV    handleType;
    HANDLE                               handle;
} VkImportMemoryWin32HandleInfoNV;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMemoryWin32HandleInfoNV {
    VkStructureType               sType;
    ଅଚଳ ଶୂନ୍ୟ*                   pNext;
    ଅଚଳ SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
} VkExportMemoryWin32HandleInfoNV;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleNV)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);

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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ଅଚଳ ଶୂନ୍ୟ*              pNext;
    uint32_t                 acquire_ଗଣନା;
    ଅଚଳ VkDeviceMemory*    pAcquireSyncs;
    ଅଚଳ uint64_t*          p_Acquire_ଚାବିଗୁଡ଼ିକ;
    ଅଚଳ uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_ଗଣନା;
    ଅଚଳ VkDeviceMemory*    pReleaseSyncs;
    ଅଚଳ uint64_t*          p_Release_ଚାବିଗୁଡ଼ିକ;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_full_screen_exclusive 1

#define VK_EXT_FULL_SCREEN_EXCLUSIVE_SPEC_VERSION 4
#define VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkFullScreenExclusiveEXT {
    VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_FULL_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkFullScreenExclusiveEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSurfaceFullScreenExclusiveInfoEXT {
    VkStructureType             sType;
    ଶୂନ୍ୟ*                       pNext;
    VkFullScreenExclusiveEXT    fullScreenExclusive;
} VkSurfaceFullScreenExclusiveInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSurfaceCapabilitiesFullScreenExclusiveEXT {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    VkBool32           fullScreenExclusiveSupported;
} VkSurfaceCapabilitiesFullScreenExclusiveEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkSurfaceFullScreenExclusiveWin32InfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    HMONITOR           hmonitor;
} VkSurfaceFullScreenExclusiveWin32InfoEXT;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ଅଚଳ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_Mode_ଗଣନା, VkPresentModeKHR* pPresentModes);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkAcquireFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkReleaseFullScreenExclusiveModeEXT)(VkDevice device, VkSwapchainKHR swapchain);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetDeviceGroupSurfacePresentModes2EXT)(VkDevice device, ଅଚଳ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ଅଚଳ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_Mode_ଗଣନା,
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
    ଅଚଳ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkDeviceGroupPresentModeFlagsKHR*           pModes);
#endif
#endif


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#define VK_NV_acquire_winrt_display 1

#define VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_VERSION 1
#define VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

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

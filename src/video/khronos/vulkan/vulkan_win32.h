#جيڪڏهن_وصف_نه_ٿيل VULKAN_WIN32_H_
#وصف_ڪريو VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_win32_surface 1

#وصف_ڪريو VK_KHR_WIN32_SURFACE_SPEC_نسخو 6
#وصف_ڪريو VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

تعريفنوع VkFlags VkWin32SurfaceCreateFlagsKHR;

تعريفنوع بنية VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ثابت فراغ*                     p_ايندڙ;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ثابت VkWin32SurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاريو);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاريو);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_external_يادگيري_win32 1

#وصف_ڪريو VK_KHR_EXTERNAL_يادگيري_WIN32_SPEC_نسخو 1
#وصف_ڪريو VK_KHR_EXTERNAL_يادگيري_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

تعريفنوع بنية Vk_Import_يادگيري_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_External_يادگيري_Handle_Type_Flag_بٽ    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_يادگيري_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_Export_يادگيري_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_ايندڙ;
    ثابت SECURITY_خاصيتون*    p_خاصيتون;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_يادگيري_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_يادگيري_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           يادگيري_Type_بٽ;
} Vk_يادگيري_Win32_Handle_Properties_KHR;

تعريفنوع بنية Vk_يادگيري_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_Device_يادگيري                        يادگيري;
    Vk_External_يادگيري_Handle_Type_Flag_بٽ    handleType;
} Vk_يادگيري_Get_Win32_Handle_Info_KHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Win32_Handle_KHR)(VkDevice device, ثابت Vk_يادگيري_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_يادگيري_Handle_Type_Flag_بٽ handleType, HANDLE handle, Vk_يادگيري_Win32_Handle_Properties_KHR* p_يادگيري_Win32_Handle_Properties);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Win32_Handle_KHR(
    VkDevice                                    device,
    ثابت Vk_يادگيري_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_يادگيري_Handle_Type_Flag_بٽ          handleType,
    HANDLE                                      handle,
    Vk_يادگيري_Win32_Handle_Properties_KHR*           p_يادگيري_Win32_Handle_Properties);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_win32_keyed_mutex 1

#وصف_ڪريو VK_KHR_WIN32_KEYED_MUTEX_SPEC_نسخو 1
#وصف_ڪريو VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ثابت فراغ*              p_ايندڙ;
    uint32_t                 acquire_ڳڻپ;
    ثابت Vk_Device_يادگيري*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_ڪنجيون;
    ثابت uint32_t*          pAcquireTimeouts;
    uint32_t                 release_ڳڻپ;
    ثابت Vk_Device_يادگيري*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_ڪنجيون;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_external_semaphore_win32 1

#وصف_ڪريو VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_نسخو 1
#وصف_ڪريو VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

تعريفنوع بنية VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_ايندڙ;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بٽ    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_ايندڙ;
    ثابت SECURITY_خاصيتون*    p_خاصيتون;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    uint32_t           wait_Semaphore_قدرون_ڳڻپ;
    ثابت uint64_t*    p_Wait_Semaphore_قدرون;
    uint32_t           signal_Semaphore_قدرون_ڳڻپ;
    ثابت uint64_t*    p_Signal_Semaphore_قدرون;
} VkD3D12FenceSubmitInfoKHR;

تعريفنوع بنية VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_ايندڙ;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بٽ    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_KHR_external_fence_win32 1

#وصف_ڪريو VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_نسخو 1
#وصف_ڪريو VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

تعريفنوع بنية VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_ايندڙ;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_بٽ    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_ايندڙ;
    ثابت SECURITY_خاصيتون*    p_خاصيتون;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_ايندڙ;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_بٽ    handleType;
} VkFenceGetWin32HandleInfoKHR;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ثابت VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ثابت VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_NV_external_يادگيري_win32 1

#وصف_ڪريو VK_NV_EXTERNAL_يادگيري_WIN32_SPEC_نسخو 1
#وصف_ڪريو VK_NV_EXTERNAL_يادگيري_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

تعريفنوع بنية Vk_Import_يادگيري_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ثابت فراغ*                          p_ايندڙ;
    Vk_External_يادگيري_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_يادگيري_Win32_Handle_Info_NV;

تعريفنوع بنية Vk_Export_يادگيري_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ثابت فراغ*                   p_ايندڙ;
    ثابت SECURITY_خاصيتون*    p_خاصيتون;
    DWORD                         dwAccess;
} Vk_Export_يادگيري_Win32_Handle_Info_NV;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Win32_Handle_NV)(VkDevice device, Vk_Device_يادگيري يادگيري, Vk_External_يادگيري_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_يادگيري                              يادگيري,
    Vk_External_يادگيري_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_NV_win32_keyed_mutex 1

#وصف_ڪريو VK_NV_WIN32_KEYED_MUTEX_SPEC_نسخو 2
#وصف_ڪريو VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ثابت فراغ*              p_ايندڙ;
    uint32_t                 acquire_ڳڻپ;
    ثابت Vk_Device_يادگيري*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_ڪنجيون;
    ثابت uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_ڳڻپ;
    ثابت Vk_Device_يادگيري*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_ڪنجيون;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_EXT_ڀريل_screen_exclusive 1

#وصف_ڪريو VK_EXT_ڀريل_SCREEN_EXCLUSIVE_SPEC_نسخو 4
#وصف_ڪريو VK_EXT_ڀريل_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

تعريفنوع تعداد Vk_ڀريل_Screen_Exclusive_EXT {
    VK_ڀريل_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_ڀريل_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_ڀريل_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_ڀريل_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_ڀريل_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_ڀريل_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_ڀريل_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    فراغ*                       p_ايندڙ;
    Vk_ڀريل_Screen_Exclusive_EXT    ڀريل_Screen_Exclusive;
} Vk_Surface_ڀريل_Screen_Exclusive_Info_EXT;

تعريفنوع بنية Vk_Surface_Capabilities_ڀريل_Screen_Exclusive_EXT {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    VkBool32           ڀريل_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_ڀريل_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_ڀريل_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    HMONITOR           hmonitor;
} Vk_Surface_ڀريل_Screen_Exclusive_Win32_Info_EXT;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_گهڻائي_ڳڻپ, Vk_Present_گهڻائي_KHR* pPresentModes);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Acquire_ڀريل_Screen_Exclusive_گهڻائي_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Release_ڀريل_Screen_Exclusive_گهڻائي_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_Device_گروهه_Surface_Present_Modes2_EXT)(VkDevice device, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_گروهه_Present_گهڻائي_Flags_KHR* pModes);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_گهڻائي_ڳڻپ,
    Vk_Present_گهڻائي_KHR*                           pPresentModes);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Acquire_ڀريل_Screen_Exclusive_گهڻائي_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Release_ڀريل_Screen_Exclusive_گهڻائي_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_Device_گروهه_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_گروهه_Present_گهڻائي_Flags_KHR*           pModes);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_NV_acquire_winrt_display 1

#وصف_ڪريو VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_نسخو 1
#وصف_ڪريو VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو

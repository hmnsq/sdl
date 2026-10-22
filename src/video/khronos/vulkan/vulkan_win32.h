#جے_بنا_تعریف VULKAN_WIN32_H_
#تعریف_کرو VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_win32_surface 1

#تعریف_کرو VK_KHR_WIN32_SURFACE_SPEC_نسخہ 6
#تعریف_کرو VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

تعريفنوع VkFlags VkWin32SurfaceCreateFlagsKHR;

تعريفنوع بنية VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ثابت فراغ*                     p_اگلا;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ثابت VkWin32SurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ);
#جے_انت
#جے_انت


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_external_حافظہ_win32 1

#تعریف_کرو VK_KHR_EXTERNAL_حافظہ_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_EXTERNAL_حافظہ_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

تعريفنوع بنية Vk_Import_حافظہ_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_حافظہ_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_Export_حافظہ_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    ثابت SECURITY_گن*    p_گن;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_حافظہ_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_حافظہ_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           حافظہ_Type_بٹ;
} Vk_حافظہ_Win32_Handle_Properties_KHR;

تعريفنوع بنية Vk_حافظہ_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_Device_حافظہ                        حافظہ;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
} Vk_حافظہ_Get_Win32_Handle_Info_KHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Win32_Handle_KHR)(VkDevice device, ثابت Vk_حافظہ_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_حافظہ_Handle_Type_Flag_بٹ handleType, HANDLE handle, Vk_حافظہ_Win32_Handle_Properties_KHR* p_حافظہ_Win32_Handle_Properties);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Win32_Handle_KHR(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_حافظہ_Handle_Type_Flag_بٹ          handleType,
    HANDLE                                      handle,
    Vk_حافظہ_Win32_Handle_Properties_KHR*           p_حافظہ_Win32_Handle_Properties);
#جے_انت
#جے_انت


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_win32_keyed_mutex 1

#تعریف_کرو VK_KHR_WIN32_KEYED_MUTEX_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ثابت فراغ*              p_اگلا;
    uint32_t                 acquire_گنتی;
    ثابت Vk_Device_حافظہ*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیدیں;
    ثابت uint32_t*          pAcquireTimeouts;
    uint32_t                 release_گنتی;
    ثابت Vk_Device_حافظہ*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیدیں;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_external_semaphore_win32 1

#تعریف_کرو VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

تعريفنوع بنية VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_اگلا;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    ثابت SECURITY_گن*    p_گن;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    uint32_t           wait_Semaphore_اقدار_گنتی;
    ثابت uint64_t*    p_Wait_Semaphore_اقدار;
    uint32_t           signal_Semaphore_اقدار_گنتی;
    ثابت uint64_t*    p_Signal_Semaphore_اقدار;
} VkD3D12FenceSubmitInfoKHR;

تعريفنوع بنية VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_اگلا;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#جے_انت
#جے_انت


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_external_fence_win32 1

#تعریف_کرو VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

تعريفنوع بنية VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_اگلا;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_بٹ    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    ثابت SECURITY_گن*    p_گن;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_اگلا;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_بٹ    handleType;
} VkFenceGetWin32HandleInfoKHR;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ثابت VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ثابت VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#جے_انت
#جے_انت


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_external_حافظہ_win32 1

#تعریف_کرو VK_NV_EXTERNAL_حافظہ_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_NV_EXTERNAL_حافظہ_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

تعريفنوع بنية Vk_Import_حافظہ_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ثابت فراغ*                          p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_حافظہ_Win32_Handle_Info_NV;

تعريفنوع بنية Vk_Export_حافظہ_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ثابت فراغ*                   p_اگلا;
    ثابت SECURITY_گن*    p_گن;
    DWORD                         dwAccess;
} Vk_Export_حافظہ_Win32_Handle_Info_NV;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Win32_Handle_NV)(VkDevice device, Vk_Device_حافظہ حافظہ, Vk_External_حافظہ_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_حافظہ                              حافظہ,
    Vk_External_حافظہ_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#جے_انت
#جے_انت


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_win32_keyed_mutex 1

#تعریف_کرو VK_NV_WIN32_KEYED_MUTEX_SPEC_نسخہ 2
#تعریف_کرو VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ثابت فراغ*              p_اگلا;
    uint32_t                 acquire_گنتی;
    ثابت Vk_Device_حافظہ*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیدیں;
    ثابت uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_گنتی;
    ثابت Vk_Device_حافظہ*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیدیں;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_بھریا_screen_exclusive 1

#تعریف_کرو VK_EXT_بھریا_SCREEN_EXCLUSIVE_SPEC_نسخہ 4
#تعریف_کرو VK_EXT_بھریا_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

تعريفنوع تعداد Vk_بھریا_Screen_Exclusive_EXT {
    VK_بھریا_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_بھریا_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_بھریا_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_بھریا_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_بھریا_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_بھریا_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_بھریا_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    فراغ*                       p_اگلا;
    Vk_بھریا_Screen_Exclusive_EXT    بھریا_Screen_Exclusive;
} Vk_Surface_بھریا_Screen_Exclusive_Info_EXT;

تعريفنوع بنية Vk_Surface_Capabilities_بھریا_Screen_Exclusive_EXT {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    VkBool32           بھریا_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_بھریا_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_بھریا_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    HMONITOR           hmonitor;
} Vk_Surface_بھریا_Screen_Exclusive_Win32_Info_EXT;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_منوال_گنتی, Vk_Present_منوال_KHR* pPresentModes);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Acquire_بھریا_Screen_Exclusive_منوال_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Release_بھریا_Screen_Exclusive_منوال_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Device_گروہ_Surface_Present_Modes2_EXT)(VkDevice device, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_گروہ_Present_منوال_Flags_KHR* pModes);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_منوال_گنتی,
    Vk_Present_منوال_KHR*                           pPresentModes);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Acquire_بھریا_Screen_Exclusive_منوال_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Release_بھریا_Screen_Exclusive_منوال_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Device_گروہ_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_گروہ_Present_منوال_Flags_KHR*           pModes);
#جے_انت
#جے_انت


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_acquire_winrt_display 1

#تعریف_کرو VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_نسخہ 1
#تعریف_کرو VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت

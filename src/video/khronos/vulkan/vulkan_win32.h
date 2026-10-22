#اگر_غیر_تعریف_شدہ VULKAN_WIN32_H_
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


#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_win32_surface 1

#تعریف_کرو VK_KHR_WIN32_SURFACE_SPEC_نسخہ 6
#تعریف_کرو VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

قسمتعریف VkFlags VkWin32SurfaceCreateFlagsKHR;

قسمتعریف ساخت VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ثابت خالی*                     p_اگلا;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ثابت VkWin32SurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
قسمتعریف VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t قطار_Family_اشاریہ);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    قطار_Family_اشاریہ);
#اگر_ختم
#اگر_ختم


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_external_حافظہ_win32 1

#تعریف_کرو VK_KHR_EXTERNAL_حافظہ_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_EXTERNAL_حافظہ_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

قسمتعریف ساخت Vk_Import_حافظہ_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_حافظہ_Win32_Handle_Info_KHR;

قسمتعریف ساخت Vk_Export_حافظہ_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    ثابت SECURITY_اوصاف*    p_اوصاف;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_حافظہ_Win32_Handle_Info_KHR;

قسمتعریف ساخت Vk_حافظہ_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           حافظہ_Type_بٹ;
} Vk_حافظہ_Win32_Handle_Properties_KHR;

قسمتعریف ساخت Vk_حافظہ_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_Device_حافظہ                        حافظہ;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
} Vk_حافظہ_Get_Win32_Handle_Info_KHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Win32_Handle_KHR)(VkDevice device, ثابت Vk_حافظہ_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_حافظہ_Handle_Type_Flag_بٹ handleType, HANDLE handle, Vk_حافظہ_Win32_Handle_Properties_KHR* p_حافظہ_Win32_Handle_Properties);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Win32_Handle_KHR(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_حافظہ_Handle_Type_Flag_بٹ          handleType,
    HANDLE                                      handle,
    Vk_حافظہ_Win32_Handle_Properties_KHR*           p_حافظہ_Win32_Handle_Properties);
#اگر_ختم
#اگر_ختم


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_win32_keyed_mutex 1

#تعریف_کرو VK_KHR_WIN32_KEYED_MUTEX_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

قسمتعریف ساخت VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ثابت خالی*              p_اگلا;
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

قسمتعریف ساخت VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت خالی*                              p_اگلا;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

قسمتعریف ساخت VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    ثابت SECURITY_اوصاف*    p_اوصاف;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

قسمتعریف ساخت VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    uint32_t           wait_Semaphore_اقدار_گنتی;
    ثابت uint64_t*    p_Wait_Semaphore_اقدار;
    uint32_t           signal_Semaphore_اقدار_گنتی;
    ثابت uint64_t*    p_Signal_Semaphore_اقدار;
} VkD3D12FenceSubmitInfoKHR;

قسمتعریف ساخت VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت خالی*                              p_اگلا;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بٹ    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#اگر_ختم
#اگر_ختم


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_KHR_external_fence_win32 1

#تعریف_کرو VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

قسمتعریف ساخت VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت خالی*                          p_اگلا;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_بٹ    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

قسمتعریف ساخت VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    ثابت SECURITY_اوصاف*    p_اوصاف;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

قسمتعریف ساخت VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت خالی*                          p_اگلا;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_بٹ    handleType;
} VkFenceGetWin32HandleInfoKHR;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ثابت VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ثابت VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#اگر_ختم
#اگر_ختم


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_external_حافظہ_win32 1

#تعریف_کرو VK_NV_EXTERNAL_حافظہ_WIN32_SPEC_نسخہ 1
#تعریف_کرو VK_NV_EXTERNAL_حافظہ_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

قسمتعریف ساخت Vk_Import_حافظہ_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ثابت خالی*                          p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_حافظہ_Win32_Handle_Info_NV;

قسمتعریف ساخت Vk_Export_حافظہ_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ثابت خالی*                   p_اگلا;
    ثابت SECURITY_اوصاف*    p_اوصاف;
    DWORD                         dwAccess;
} Vk_Export_حافظہ_Win32_Handle_Info_NV;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Win32_Handle_NV)(VkDevice device, Vk_Device_حافظہ حافظہ, Vk_External_حافظہ_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_حافظہ                              حافظہ,
    Vk_External_حافظہ_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#اگر_ختم
#اگر_ختم


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_win32_keyed_mutex 1

#تعریف_کرو VK_NV_WIN32_KEYED_MUTEX_SPEC_نسخہ 2
#تعریف_کرو VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

قسمتعریف ساخت VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ثابت خالی*              p_اگلا;
    uint32_t                 acquire_گنتی;
    ثابت Vk_Device_حافظہ*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیدیں;
    ثابت uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_گنتی;
    ثابت Vk_Device_حافظہ*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیدیں;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_بھرا_screen_exclusive 1

#تعریف_کرو VK_EXT_بھرا_SCREEN_EXCLUSIVE_SPEC_نسخہ 4
#تعریف_کرو VK_EXT_بھرا_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

قسمتعریف شمار Vk_بھرا_Screen_Exclusive_EXT {
    VK_بھرا_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_بھرا_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_بھرا_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_بھرا_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_بھرا_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_بھرا_Screen_Exclusive_EXT;

قسمتعریف ساخت Vk_Surface_بھرا_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    خالی*                       p_اگلا;
    Vk_بھرا_Screen_Exclusive_EXT    بھرا_Screen_Exclusive;
} Vk_Surface_بھرا_Screen_Exclusive_Info_EXT;

قسمتعریف ساخت Vk_Surface_Capabilities_بھرا_Screen_Exclusive_EXT {
    VkStructureType    sType;
    خالی*              p_اگلا;
    VkBool32           بھرا_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_بھرا_Screen_Exclusive_EXT;

قسمتعریف ساخت Vk_Surface_بھرا_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    HMONITOR           hmonitor;
} Vk_Surface_بھرا_Screen_Exclusive_Win32_Info_EXT;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_منوال_گنتی, Vk_Present_منوال_KHR* pPresentModes);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Acquire_بھرا_Screen_Exclusive_منوال_EXT)(VkDevice device, VkSwapchainKHR swapchain);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Release_بھرا_Screen_Exclusive_منوال_EXT)(VkDevice device, VkSwapchainKHR swapchain);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_Device_گروہ_Surface_Present_Modes2_EXT)(VkDevice device, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_گروہ_Present_منوال_Flags_KHR* pModes);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_منوال_گنتی,
    Vk_Present_منوال_KHR*                           pPresentModes);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Acquire_بھرا_Screen_Exclusive_منوال_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Release_بھرا_Screen_Exclusive_منوال_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_Device_گروہ_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_گروہ_Present_منوال_Flags_KHR*           pModes);
#اگر_ختم
#اگر_ختم


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_NV_acquire_winrt_display 1

#تعریف_کرو VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_نسخہ 1
#تعریف_کرو VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم

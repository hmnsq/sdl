#اگر_تعریف_نشده VULKAN_WIN32_H_
#تعریف_کن VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_win32_surface 1

#تعریف_کن VK_KHR_WIN32_SURFACE_SPEC_نسخه 6
#تعریف_کن VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

تعريفنوع VkFlags VkWin32SurfaceCreateFlagsKHR;

تعريفنوع بنية VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ثابت فراغ*                     p_بعدی;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ثابت VkWin32SurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t صف_Family_شاخص);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    صف_Family_شاخص);
#پایان_اگر
#پایان_اگر


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_external_حافظه_win32 1

#تعریف_کن VK_KHR_EXTERNAL_حافظه_WIN32_SPEC_نسخه 1
#تعریف_کن VK_KHR_EXTERNAL_حافظه_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

تعريفنوع بنية Vk_Import_حافظه_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_External_حافظه_Handle_Type_Flag_بیتها    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_حافظه_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_Export_حافظه_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    ثابت SECURITY_صفات*    p_صفات;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_حافظه_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_حافظه_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           حافظه_Type_بیتها;
} Vk_حافظه_Win32_Handle_Properties_KHR;

تعريفنوع بنية Vk_حافظه_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_Device_حافظه                        حافظه;
    Vk_External_حافظه_Handle_Type_Flag_بیتها    handleType;
} Vk_حافظه_Get_Win32_Handle_Info_KHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Win32_Handle_KHR)(VkDevice device, ثابت Vk_حافظه_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_حافظه_Handle_Type_Flag_بیتها handleType, HANDLE handle, Vk_حافظه_Win32_Handle_Properties_KHR* p_حافظه_Win32_Handle_Properties);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Win32_Handle_KHR(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_حافظه_Handle_Type_Flag_بیتها          handleType,
    HANDLE                                      handle,
    Vk_حافظه_Win32_Handle_Properties_KHR*           p_حافظه_Win32_Handle_Properties);
#پایان_اگر
#پایان_اگر


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_win32_keyed_mutex 1

#تعریف_کن VK_KHR_WIN32_KEYED_MUTEX_SPEC_نسخه 1
#تعریف_کن VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ثابت فراغ*              p_بعدی;
    uint32_t                 acquire_شمار;
    ثابت Vk_Device_حافظه*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیدها;
    ثابت uint32_t*          pAcquireTimeouts;
    uint32_t                 release_شمار;
    ثابت Vk_Device_حافظه*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیدها;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_external_semaphore_win32 1

#تعریف_کن VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_نسخه 1
#تعریف_کن VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

تعريفنوع بنية VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بعدی;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بیتها    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    ثابت SECURITY_صفات*    p_صفات;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    uint32_t           wait_Semaphore_مقادیر_شمار;
    ثابت uint64_t*    p_Wait_Semaphore_مقادیر;
    uint32_t           signal_Semaphore_مقادیر_شمار;
    ثابت uint64_t*    p_Signal_Semaphore_مقادیر;
} VkD3D12FenceSubmitInfoKHR;

تعريفنوع بنية VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بعدی;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بیتها    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#پایان_اگر
#پایان_اگر


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_KHR_external_fence_win32 1

#تعریف_کن VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_نسخه 1
#تعریف_کن VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

تعريفنوع بنية VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_بعدی;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_بیتها    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    ثابت SECURITY_صفات*    p_صفات;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_بعدی;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_بیتها    handleType;
} VkFenceGetWin32HandleInfoKHR;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ثابت VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ثابت VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#پایان_اگر
#پایان_اگر


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_NV_external_حافظه_win32 1

#تعریف_کن VK_NV_EXTERNAL_حافظه_WIN32_SPEC_نسخه 1
#تعریف_کن VK_NV_EXTERNAL_حافظه_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

تعريفنوع بنية Vk_Import_حافظه_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ثابت فراغ*                          p_بعدی;
    Vk_External_حافظه_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_حافظه_Win32_Handle_Info_NV;

تعريفنوع بنية Vk_Export_حافظه_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ثابت فراغ*                   p_بعدی;
    ثابت SECURITY_صفات*    p_صفات;
    DWORD                         dwAccess;
} Vk_Export_حافظه_Win32_Handle_Info_NV;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Win32_Handle_NV)(VkDevice device, Vk_Device_حافظه حافظه, Vk_External_حافظه_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_حافظه                              حافظه,
    Vk_External_حافظه_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#پایان_اگر
#پایان_اگر


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_NV_win32_keyed_mutex 1

#تعریف_کن VK_NV_WIN32_KEYED_MUTEX_SPEC_نسخه 2
#تعریف_کن VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ثابت فراغ*              p_بعدی;
    uint32_t                 acquire_شمار;
    ثابت Vk_Device_حافظه*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیدها;
    ثابت uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_شمار;
    ثابت Vk_Device_حافظه*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیدها;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_EXT_پر_screen_exclusive 1

#تعریف_کن VK_EXT_پر_SCREEN_EXCLUSIVE_SPEC_نسخه 4
#تعریف_کن VK_EXT_پر_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

تعريفنوع تعداد Vk_پر_Screen_Exclusive_EXT {
    VK_پر_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_پر_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_پر_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_پر_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_پر_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_پر_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_پر_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    فراغ*                       p_بعدی;
    Vk_پر_Screen_Exclusive_EXT    پر_Screen_Exclusive;
} Vk_Surface_پر_Screen_Exclusive_Info_EXT;

تعريفنوع بنية Vk_Surface_Capabilities_پر_Screen_Exclusive_EXT {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    VkBool32           پر_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_پر_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_پر_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    HMONITOR           hmonitor;
} Vk_Surface_پر_Screen_Exclusive_Win32_Info_EXT;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_نما_شمار, Vk_Present_نما_KHR* pPresentModes);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Acquire_پر_Screen_Exclusive_نما_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Release_پر_Screen_Exclusive_نما_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_Device_گروه_Surface_Present_Modes2_EXT)(VkDevice device, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_گروه_Present_نما_Flags_KHR* pModes);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_نما_شمار,
    Vk_Present_نما_KHR*                           pPresentModes);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Acquire_پر_Screen_Exclusive_نما_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Release_پر_Screen_Exclusive_نما_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_Device_گروه_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_گروه_Present_نما_Flags_KHR*           pModes);
#پایان_اگر
#پایان_اگر


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_NV_acquire_winrt_display 1

#تعریف_کن VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_نسخه 1
#تعریف_کن VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر

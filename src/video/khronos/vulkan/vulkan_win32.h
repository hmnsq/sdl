#که_نه_تعریف_شوی VULKAN_WIN32_H_
#تعریف_کړه VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_win32_surface 1

#تعریف_کړه VK_KHR_WIN32_SURFACE_SPEC_نسخه 6
#تعریف_کړه VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

تعريفنوع VkFlags VkWin32SurfaceCreateFlagsKHR;

تعريفنوع بنية VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ثابت فراغ*                     p_بل;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ثابت VkWin32SurfaceCreateInfoKHR* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
تعريفنوع VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t کتار_Family_شاخص);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ثابت VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    کتار_Family_شاخص);
#د_که_پای
#د_که_پای


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_external_حافظه_win32 1

#تعریف_کړه VK_KHR_EXTERNAL_حافظه_WIN32_SPEC_نسخه 1
#تعریف_کړه VK_KHR_EXTERNAL_حافظه_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

تعريفنوع بنية Vk_Import_حافظه_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_External_حافظه_Handle_Type_Flag_بټونه    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_حافظه_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_Export_حافظه_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بل;
    ثابت SECURITY_ځانګړتیاوې*    p_ځانګړتیاوې;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_حافظه_Win32_Handle_Info_KHR;

تعريفنوع بنية Vk_حافظه_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           حافظه_Type_بټونه;
} Vk_حافظه_Win32_Handle_Properties_KHR;

تعريفنوع بنية Vk_حافظه_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_Device_حافظه                        حافظه;
    Vk_External_حافظه_Handle_Type_Flag_بټونه    handleType;
} Vk_حافظه_Get_Win32_Handle_Info_KHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Win32_Handle_KHR)(VkDevice device, ثابت Vk_حافظه_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_حافظه_Handle_Type_Flag_بټونه handleType, HANDLE handle, Vk_حافظه_Win32_Handle_Properties_KHR* p_حافظه_Win32_Handle_Properties);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Win32_Handle_KHR(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_حافظه_Handle_Type_Flag_بټونه          handleType,
    HANDLE                                      handle,
    Vk_حافظه_Win32_Handle_Properties_KHR*           p_حافظه_Win32_Handle_Properties);
#د_که_پای
#د_که_پای


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_win32_keyed_mutex 1

#تعریف_کړه VK_KHR_WIN32_KEYED_MUTEX_SPEC_نسخه 1
#تعریف_کړه VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ثابت فراغ*              p_بل;
    uint32_t                 acquire_شمېر;
    ثابت Vk_Device_حافظه*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیګانې;
    ثابت uint32_t*          pAcquireTimeouts;
    uint32_t                 release_شمېر;
    ثابت Vk_Device_حافظه*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیګانې;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_external_semaphore_win32 1

#تعریف_کړه VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_نسخه 1
#تعریف_کړه VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

تعريفنوع بنية VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بل;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_بټونه    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بل;
    ثابت SECURITY_ځانګړتیاوې*    p_ځانګړتیاوې;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

تعريفنوع بنية VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    uint32_t           wait_Semaphore_ارزښتونه_شمېر;
    ثابت uint64_t*    p_Wait_Semaphore_ارزښتونه;
    uint32_t           signal_Semaphore_ارزښتونه_شمېر;
    ثابت uint64_t*    p_Signal_Semaphore_ارزښتونه;
} VkD3D12FenceSubmitInfoKHR;

تعريفنوع بنية VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ثابت فراغ*                              p_بل;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_بټونه    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ثابت VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#د_که_پای
#د_که_پای


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_KHR_external_fence_win32 1

#تعریف_کړه VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_نسخه 1
#تعریف_کړه VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

تعريفنوع بنية VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_بل;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_بټونه    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ثابت فراغ*                   p_بل;
    ثابت SECURITY_ځانګړتیاوې*    p_ځانګړتیاوې;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

تعريفنوع بنية VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ثابت فراغ*                          p_بل;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_بټونه    handleType;
} VkFenceGetWin32HandleInfoKHR;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ثابت VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ثابت VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ثابت VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#د_که_پای
#د_که_پای


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_NV_external_حافظه_win32 1

#تعریف_کړه VK_NV_EXTERNAL_حافظه_WIN32_SPEC_نسخه 1
#تعریف_کړه VK_NV_EXTERNAL_حافظه_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

تعريفنوع بنية Vk_Import_حافظه_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ثابت فراغ*                          p_بل;
    Vk_External_حافظه_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_حافظه_Win32_Handle_Info_NV;

تعريفنوع بنية Vk_Export_حافظه_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ثابت فراغ*                   p_بل;
    ثابت SECURITY_ځانګړتیاوې*    p_ځانګړتیاوې;
    DWORD                         dwAccess;
} Vk_Export_حافظه_Win32_Handle_Info_NV;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Win32_Handle_NV)(VkDevice device, Vk_Device_حافظه حافظه, Vk_External_حافظه_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_حافظه                              حافظه,
    Vk_External_حافظه_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#د_که_پای
#د_که_پای


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_NV_win32_keyed_mutex 1

#تعریف_کړه VK_NV_WIN32_KEYED_MUTEX_SPEC_نسخه 2
#تعریف_کړه VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

تعريفنوع بنية VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ثابت فراغ*              p_بل;
    uint32_t                 acquire_شمېر;
    ثابت Vk_Device_حافظه*    pAcquireSyncs;
    ثابت uint64_t*          p_Acquire_کلیګانې;
    ثابت uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_شمېر;
    ثابت Vk_Device_حافظه*    pReleaseSyncs;
    ثابت uint64_t*          p_Release_کلیګانې;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_EXT_ډک_screen_exclusive 1

#تعریف_کړه VK_EXT_ډک_SCREEN_EXCLUSIVE_SPEC_نسخه 4
#تعریف_کړه VK_EXT_ډک_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

تعريفنوع تعداد Vk_ډک_Screen_Exclusive_EXT {
    VK_ډک_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_ډک_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_ډک_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_ډک_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_ډک_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_ډک_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_ډک_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    فراغ*                       p_بل;
    Vk_ډک_Screen_Exclusive_EXT    ډک_Screen_Exclusive;
} Vk_Surface_ډک_Screen_Exclusive_Info_EXT;

تعريفنوع بنية Vk_Surface_Capabilities_ډک_Screen_Exclusive_EXT {
    VkStructureType    sType;
    فراغ*              p_بل;
    VkBool32           ډک_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_ډک_Screen_Exclusive_EXT;

تعريفنوع بنية Vk_Surface_ډک_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    HMONITOR           hmonitor;
} Vk_Surface_ډک_Screen_Exclusive_Win32_Info_EXT;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_ډېرپېښ_شمېر, Vk_Present_ډېرپېښ_KHR* pPresentModes);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Acquire_ډک_Screen_Exclusive_ډېرپېښ_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Release_ډک_Screen_Exclusive_ډېرپېښ_EXT)(VkDevice device, VkSwapchainKHR swapchain);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_Device_ډله_Surface_Present_Modes2_EXT)(VkDevice device, ثابت VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_ډله_Present_ډېرپېښ_Flags_KHR* pModes);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_ډېرپېښ_شمېر,
    Vk_Present_ډېرپېښ_KHR*                           pPresentModes);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Acquire_ډک_Screen_Exclusive_ډېرپېښ_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Release_ډک_Screen_Exclusive_ډېرپېښ_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_Device_ډله_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ثابت VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_ډله_Present_ډېرپېښ_Flags_KHR*           pModes);
#د_که_پای
#د_که_پای


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_NV_acquire_winrt_display 1

#تعریف_کړه VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_نسخه 1
#تعریف_کړه VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای

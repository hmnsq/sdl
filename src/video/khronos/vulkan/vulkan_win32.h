#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_WIN32_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_win32_surface 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_WIN32_SURFACE_SPEC_ਸੰਸਕਰਣ 6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkWin32SurfaceCreateFlagsKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ਅਚਲ ਖਾਲੀ*                     p_ਅਗਲਾ;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ਅਚਲ VkWin32SurfaceCreateInfoKHR* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ਅਚਲ VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_external_ਸਮ੍ਰਿਤੀ_win32 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_EXTERNAL_ਸਮ੍ਰਿਤੀ_WIN32_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_EXTERNAL_ਸਮ੍ਰਿਤੀ_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Export_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    ਅਚਲ SECURITY_ਗੁਣ*    p_ਗੁਣ;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
} Vk_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties_KHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_Device_ਸਮ੍ਰਿਤੀ                        ਸਮ੍ਰਿਤੀ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ    handleType;
} Vk_ਸਮ੍ਰਿਤੀ_Get_Win32_Handle_Info_KHR;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_KHR)(VkDevice device, ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ handleType, HANDLE handle, Vk_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties_KHR* p_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_KHR(
    VkDevice                                    device,
    ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ          handleType,
    HANDLE                                      handle,
    Vk_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties_KHR*           p_ਸਮ੍ਰਿਤੀ_Win32_Handle_Properties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_win32_keyed_mutex 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_WIN32_KEYED_MUTEX_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ਅਚਲ ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t                 acquire_ਗਿਣਤੀ;
    ਅਚਲ Vk_Device_ਸਮ੍ਰਿਤੀ*    pAcquireSyncs;
    ਅਚਲ uint64_t*          p_Acquire_ਕੁੰਜੀਆਂ;
    ਅਚਲ uint32_t*          pAcquireTimeouts;
    uint32_t                 release_ਗਿਣਤੀ;
    ਅਚਲ Vk_Device_ਸਮ੍ਰਿਤੀ*    pReleaseSyncs;
    ਅਚਲ uint64_t*          p_Release_ਕੁੰਜੀਆਂ;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_external_semaphore_win32 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ਅਚਲ ਖਾਲੀ*                              p_ਅਗਲਾ;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_ਬਿੱਟ    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    ਅਚਲ SECURITY_ਗੁਣ*    p_ਗੁਣ;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    uint32_t           wait_Semaphore_ਮੁੱਲਾਂ_ਗਿਣਤੀ;
    ਅਚਲ uint64_t*    p_Wait_Semaphore_ਮੁੱਲਾਂ;
    uint32_t           signal_Semaphore_ਮੁੱਲਾਂ_ਗਿਣਤੀ;
    ਅਚਲ uint64_t*    p_Signal_Semaphore_ਮੁੱਲਾਂ;
} VkD3D12FenceSubmitInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ਅਚਲ ਖਾਲੀ*                              p_ਅਗਲਾ;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_ਬਿੱਟ    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ਅਚਲ VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ਅਚਲ VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ਅਚਲ VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ਅਚਲ VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_external_fence_win32 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ਅਚਲ ਖਾਲੀ*                          p_ਅਗਲਾ;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_ਬਿੱਟ    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    ਅਚਲ SECURITY_ਗੁਣ*    p_ਗੁਣ;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ਅਚਲ ਖਾਲੀ*                          p_ਅਗਲਾ;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_ਬਿੱਟ    handleType;
} VkFenceGetWin32HandleInfoKHR;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ਅਚਲ VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ਅਚਲ VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ਅਚਲ VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ਅਚਲ VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_external_ਸਮ੍ਰਿਤੀ_win32 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_EXTERNAL_ਸਮ੍ਰਿਤੀ_WIN32_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_EXTERNAL_ਸਮ੍ਰਿਤੀ_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ਅਚਲ ਖਾਲੀ*                          p_ਅਗਲਾ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_NV;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Export_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ਅਚਲ ਖਾਲੀ*                   p_ਅਗਲਾ;
    ਅਚਲ SECURITY_ਗੁਣ*    p_ਗੁਣ;
    DWORD                         dwAccess;
} Vk_Export_ਸਮ੍ਰਿਤੀ_Win32_Handle_Info_NV;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_NV)(VkDevice device, Vk_Device_ਸਮ੍ਰਿਤੀ ਸਮ੍ਰਿਤੀ, Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_ਸਮ੍ਰਿਤੀ                              ਸਮ੍ਰਿਤੀ,
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_win32_keyed_mutex 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_WIN32_KEYED_MUTEX_SPEC_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ਅਚਲ ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t                 acquire_ਗਿਣਤੀ;
    ਅਚਲ Vk_Device_ਸਮ੍ਰਿਤੀ*    pAcquireSyncs;
    ਅਚਲ uint64_t*          p_Acquire_ਕੁੰਜੀਆਂ;
    ਅਚਲ uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_ਗਿਣਤੀ;
    ਅਚਲ Vk_Device_ਸਮ੍ਰਿਤੀ*    pReleaseSyncs;
    ਅਚਲ uint64_t*          p_Release_ਕੁੰਜੀਆਂ;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_ਭਰਿਆ_screen_exclusive 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_ਭਰਿਆ_SCREEN_EXCLUSIVE_SPEC_ਸੰਸਕਰਣ 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_ਭਰਿਆ_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Vk_ਭਰਿਆ_Screen_Exclusive_EXT {
    VK_ਭਰਿਆ_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_ਭਰਿਆ_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_ਭਰਿਆ_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_ਭਰਿਆ_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_ਭਰਿਆ_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_ਭਰਿਆ_Screen_Exclusive_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Surface_ਭਰਿਆ_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    ਖਾਲੀ*                       p_ਅਗਲਾ;
    Vk_ਭਰਿਆ_Screen_Exclusive_EXT    ਭਰਿਆ_Screen_Exclusive;
} Vk_Surface_ਭਰਿਆ_Screen_Exclusive_Info_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Surface_Capabilities_ਭਰਿਆ_Screen_Exclusive_EXT {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    VkBool32           ਭਰਿਆ_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_ਭਰਿਆ_Screen_Exclusive_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Surface_ਭਰਿਆ_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    HMONITOR           hmonitor;
} Vk_Surface_ਭਰਿਆ_Screen_Exclusive_Win32_Info_EXT;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ਅਚਲ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_ਬਹੁਲਕ_ਗਿਣਤੀ, Vk_Present_ਬਹੁਲਕ_KHR* pPresentModes);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Acquire_ਭਰਿਆ_Screen_Exclusive_ਬਹੁਲਕ_EXT)(VkDevice device, VkSwapchainKHR swapchain);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Release_ਭਰਿਆ_Screen_Exclusive_ਬਹੁਲਕ_EXT)(VkDevice device, VkSwapchainKHR swapchain);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_Device_ਸਮੂਹ_Surface_Present_Modes2_EXT)(VkDevice device, ਅਚਲ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_ਸਮੂਹ_Present_ਬਹੁਲਕ_Flags_KHR* pModes);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ਅਚਲ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_ਬਹੁਲਕ_ਗਿਣਤੀ,
    Vk_Present_ਬਹੁਲਕ_KHR*                           pPresentModes);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Acquire_ਭਰਿਆ_Screen_Exclusive_ਬਹੁਲਕ_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Release_ਭਰਿਆ_Screen_Exclusive_ਬਹੁਲਕ_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_Device_ਸਮੂਹ_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ਅਚਲ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_ਸਮੂਹ_Present_ਬਹੁਲਕ_Flags_KHR*           pModes);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_acquire_winrt_display 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ

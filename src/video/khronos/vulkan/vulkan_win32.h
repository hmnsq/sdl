#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_WIN32_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_WIN32_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ



// VK_KHR_win32_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_win32_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_WIN32_SURFACE_SPEC_ಆವೃತ್ತಿ 6
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkWin32SurfaceCreateFlagsKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                     p_ಮುಂದಿನ;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateWin32SurfaceKHR)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkWin32SurfaceCreateInfoKHR* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkBool32 (VKAPI_PTR *PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)(VkPhysicalDevice physicalDevice, uint32_t ಸರತಿ_Family_ಸೂಚ್ಯಂಕ);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateWin32SurfaceKHR(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    ಸರತಿ_Family_ಸೂಚ್ಯಂಕ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_KHR_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_external_ಸ್ಮರಣೆ_win32 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_EXTERNAL_ಸ್ಮರಣೆ_WIN32_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_EXTERNAL_ಸ್ಮರಣೆ_WIN32_EXTENSION_NAME "VK_KHR_external_memory_win32"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_ಸ್ಮರಣೆ_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
    HANDLE                                handle;
    LPCWSTR                               name;
} Vk_Import_ಸ್ಮರಣೆ_Win32_Handle_Info_KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Export_ಸ್ಮರಣೆ_Win32_Handle_Info_KHR {
    VkStructureType               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   p_ಮುಂದಿನ;
    ಸ್ಥಿರಾಂಕ SECURITY_ಗುಣಲಕ್ಷಣಗಳು*    p_ಗುಣಲಕ್ಷಣಗಳು;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} Vk_Export_ಸ್ಮರಣೆ_Win32_Handle_Info_KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Win32_Handle_Properties_KHR {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
} Vk_ಸ್ಮರಣೆ_Win32_Handle_Properties_KHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Get_Win32_Handle_Info_KHR {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_Device_ಸ್ಮರಣೆ                        ಸ್ಮರಣೆ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
} Vk_ಸ್ಮರಣೆ_Get_Win32_Handle_Info_KHR;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Win32_Handle_KHR)(VkDevice device, ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Win32_Handle_Info_KHR* pGetWin32HandleInfo, HANDLE* pHandle);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Win32_Handle_Properties_KHR)(VkDevice device, Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು handleType, HANDLE handle, Vk_ಸ್ಮರಣೆ_Win32_Handle_Properties_KHR* p_ಸ್ಮರಣೆ_Win32_Handle_Properties);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Win32_Handle_KHR(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Win32_Handle_Info_KHR*        pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Win32_Handle_Properties_KHR(
    VkDevice                                    device,
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು          handleType,
    HANDLE                                      handle,
    Vk_ಸ್ಮರಣೆ_Win32_Handle_Properties_KHR*           p_ಸ್ಮರಣೆ_Win32_Handle_Properties);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_KHR_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_win32_keyed_mutex 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_WIN32_KEYED_MUTEX_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHR_win32_keyed_mutex"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t                 acquire_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ Vk_Device_ಸ್ಮರಣೆ*    pAcquireSyncs;
    ಸ್ಥಿರಾಂಕ uint64_t*          p_Acquire_ಕೀಲಿಗಳು;
    ಸ್ಥಿರಾಂಕ uint32_t*          pAcquireTimeouts;
    uint32_t                 release_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ Vk_Device_ಸ್ಮರಣೆ*    pReleaseSyncs;
    ಸ್ಥಿರಾಂಕ uint64_t*          p_Release_ಕೀಲಿಗಳು;
} VkWin32KeyedMutexAcquireReleaseInfoKHR;



// VK_KHR_external_semaphore_win32 is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_external_semaphore_win32 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHR_external_semaphore_win32"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType                          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                              p_ಮುಂದಿನ;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
    HANDLE                                   handle;
    LPCWSTR                                  name;
} VkImportSemaphoreWin32HandleInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   p_ಮುಂದಿನ;
    ಸ್ಥಿರಾಂಕ SECURITY_ಗುಣಲಕ್ಷಣಗಳು*    p_ಗುಣಲಕ್ಷಣಗಳು;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkD3D12FenceSubmitInfoKHR {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    uint32_t           wait_Semaphore_ಮೌಲ್ಯಗಳು_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ uint64_t*    p_Wait_Semaphore_ಮೌಲ್ಯಗಳು;
    uint32_t           signal_Semaphore_ಮೌಲ್ಯಗಳು_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ uint64_t*    p_Signal_Semaphore_ಮೌಲ್ಯಗಳು;
} VkD3D12FenceSubmitInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType                          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                              p_ಮುಂದಿನ;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
} VkSemaphoreGetWin32HandleInfoKHR;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHR)(VkDevice device, ಸ್ಥಿರಾಂಕ VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHR)(VkDevice device, ಸ್ಥಿರಾಂಕ VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkImportSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkImportSemaphoreWin32HandleInfoKHR*  pImportSemaphoreWin32HandleInfo);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkGetSemaphoreWin32HandleKHR(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkSemaphoreGetWin32HandleInfoKHR*     pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_KHR_external_fence_win32 is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_external_fence_win32 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME "VK_KHR_external_fence_win32"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImportFenceWin32HandleInfoKHR {
    VkStructureType                      sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                          p_ಮುಂದಿನ;
    VkFence                              fence;
    VkFenceImportFlags                   flags;
    Vk_External_Fence_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
    HANDLE                               handle;
    LPCWSTR                              name;
} VkImportFenceWin32HandleInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportFenceWin32HandleInfoKHR {
    VkStructureType               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   p_ಮುಂದಿನ;
    ಸ್ಥಿರಾಂಕ SECURITY_ಗುಣಲಕ್ಷಣಗಳು*    p_ಗುಣಲಕ್ಷಣಗಳು;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportFenceWin32HandleInfoKHR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkFenceGetWin32HandleInfoKHR {
    VkStructureType                      sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                          p_ಮುಂದಿನ;
    VkFence                              fence;
    Vk_External_Fence_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
} VkFenceGetWin32HandleInfoKHR;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkImportFenceWin32HandleKHR)(VkDevice device, ಸ್ಥಿರಾಂಕ VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkGetFenceWin32HandleKHR)(VkDevice device, ಸ್ಥಿರಾಂಕ VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkImportFenceWin32HandleKHR(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkImportFenceWin32HandleInfoKHR*      pImportFenceWin32HandleInfo);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkGetFenceWin32HandleKHR(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkFenceGetWin32HandleInfoKHR*         pGetWin32HandleInfo,
    HANDLE*                                     pHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_NV_external_memory_win32 is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_external_ಸ್ಮರಣೆ_win32 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_EXTERNAL_ಸ್ಮರಣೆ_WIN32_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_EXTERNAL_ಸ್ಮರಣೆ_WIN32_EXTENSION_NAME "VK_NV_external_memory_win32"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_ಸ್ಮರಣೆ_Win32_Handle_Info_NV {
    VkStructureType                      sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                          p_ಮುಂದಿನ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags_NV    handleType;
    HANDLE                               handle;
} Vk_Import_ಸ್ಮರಣೆ_Win32_Handle_Info_NV;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Export_ಸ್ಮರಣೆ_Win32_Handle_Info_NV {
    VkStructureType               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                   p_ಮುಂದಿನ;
    ಸ್ಥಿರಾಂಕ SECURITY_ಗುಣಲಕ್ಷಣಗಳು*    p_ಗುಣಲಕ್ಷಣಗಳು;
    DWORD                         dwAccess;
} Vk_Export_ಸ್ಮರಣೆ_Win32_Handle_Info_NV;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Win32_Handle_NV)(VkDevice device, Vk_Device_ಸ್ಮರಣೆ ಸ್ಮರಣೆ, Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags_NV handleType, HANDLE* pHandle);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Win32_Handle_NV(
    VkDevice                                    device,
    Vk_Device_ಸ್ಮರಣೆ                              ಸ್ಮರಣೆ,
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flags_NV           handleType,
    HANDLE*                                     pHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_NV_win32_keyed_mutex is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_win32_keyed_mutex 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_WIN32_KEYED_MUTEX_SPEC_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_NV_win32_keyed_mutex"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t                 acquire_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ Vk_Device_ಸ್ಮರಣೆ*    pAcquireSyncs;
    ಸ್ಥಿರಾಂಕ uint64_t*          p_Acquire_ಕೀಲಿಗಳು;
    ಸ್ಥಿರಾಂಕ uint32_t*          pAcquireTimeoutMilliseconds;
    uint32_t                 release_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ Vk_Device_ಸ್ಮರಣೆ*    pReleaseSyncs;
    ಸ್ಥಿರಾಂಕ uint64_t*          p_Release_ಕೀಲಿಗಳು;
} VkWin32KeyedMutexAcquireReleaseInfoNV;



// VK_EXT_full_screen_exclusive is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_ತುಂಬಿದ_screen_exclusive 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_ತುಂಬಿದ_SCREEN_EXCLUSIVE_SPEC_ಆವೃತ್ತಿ 4
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_ತುಂಬಿದ_SCREEN_EXCLUSIVE_EXTENSION_NAME "VK_EXT_full_screen_exclusive"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Vk_ತುಂಬಿದ_Screen_Exclusive_EXT {
    VK_ತುಂಬಿದ_SCREEN_EXCLUSIVE_DEFAULT_EXT = 0,
    VK_ತುಂಬಿದ_SCREEN_EXCLUSIVE_ALLOWED_EXT = 1,
    VK_ತುಂಬಿದ_SCREEN_EXCLUSIVE_DISALLOWED_EXT = 2,
    VK_ತುಂಬಿದ_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = 3,
    VK_ತುಂಬಿದ_SCREEN_EXCLUSIVE_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_ತುಂಬಿದ_Screen_Exclusive_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Surface_ತುಂಬಿದ_Screen_Exclusive_Info_EXT {
    VkStructureType             sType;
    ಶೂನ್ಯ*                       p_ಮುಂದಿನ;
    Vk_ತುಂಬಿದ_Screen_Exclusive_EXT    ತುಂಬಿದ_Screen_Exclusive;
} Vk_Surface_ತುಂಬಿದ_Screen_Exclusive_Info_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Surface_Capabilities_ತುಂಬಿದ_Screen_Exclusive_EXT {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkBool32           ತುಂಬಿದ_Screen_Exclusive_Supported;
} Vk_Surface_Capabilities_ತುಂಬಿದ_Screen_Exclusive_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Surface_ತುಂಬಿದ_Screen_Exclusive_Win32_Info_EXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    HMONITOR           hmonitor;
} Vk_Surface_ತುಂಬಿದ_Screen_Exclusive_Win32_Info_EXT;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT)(VkPhysicalDevice physicalDevice, ಸ್ಥಿರಾಂಕ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* p_Present_ಬಹುಲಕ_ಎಣಿಕೆ, Vk_Present_ಬಹುಲಕ_KHR* pPresentModes);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Acquire_ತುಂಬಿದ_Screen_Exclusive_ಬಹುಲಕ_EXT)(VkDevice device, VkSwapchainKHR swapchain);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Release_ತುಂಬಿದ_Screen_Exclusive_ಬಹುಲಕ_EXT)(VkDevice device, VkSwapchainKHR swapchain);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_Device_ಗುಂಪು_Surface_Present_Modes2_EXT)(VkDevice device, ಸ್ಥಿರಾಂಕ VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, Vk_Device_ಗುಂಪು_Present_ಬಹುಲಕ_Flags_KHR* pModes);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice                            physicalDevice,
    ಸ್ಥಿರಾಂಕ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   p_Present_ಬಹುಲಕ_ಎಣಿಕೆ,
    Vk_Present_ಬಹುಲಕ_KHR*                           pPresentModes);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Acquire_ತುಂಬಿದ_Screen_Exclusive_ಬಹುಲಕ_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Release_ತುಂಬಿದ_Screen_Exclusive_ಬಹುಲಕ_EXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_Device_ಗುಂಪು_Surface_Present_Modes2_EXT(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    Vk_Device_ಗುಂಪು_Present_ಬಹುಲಕ_Flags_KHR*           pModes);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_NV_acquire_winrt_display is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_acquire_winrt_display 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME "VK_NV_acquire_winrt_display"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkAcquireWinrtDisplayNV)(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkGetWinrtDisplayNV)(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkAcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkGetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

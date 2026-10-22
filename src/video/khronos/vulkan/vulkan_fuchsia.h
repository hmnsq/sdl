#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_FUCHSIA_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_FUCHSIA_H_ 1

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



// VK_FUCHSIA_imagepipe_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_imagepipe_surface 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME "VK_FUCHSIA_imagepipe_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkImagePipeSurfaceCreateFlagsFUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType                         sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                             p_ಮುಂದಿನ;
    VkImagePipeSurfaceCreateFlagsFUCHSIA    flags;
    zx_handle_t                             imagePipeHandle;
} VkImagePipeSurfaceCreateInfoFUCHSIA;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateImagePipeSurfaceFUCHSIA)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkImagePipeSurfaceCreateInfoFUCHSIA*  pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_FUCHSIA_external_memory is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_external_ಸ್ಮರಣೆ 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_EXTERNAL_ಸ್ಮರಣೆ_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_EXTERNAL_ಸ್ಮರಣೆ_EXTENSION_NAME "VK_FUCHSIA_external_memory"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_ಸ್ಮರಣೆ_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
    zx_handle_t                           handle;
} Vk_Import_ಸ್ಮರಣೆ_Zircon_Handle_Info_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Zircon_Handle_Properties_FUCHSIA {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
} Vk_ಸ್ಮರಣೆ_Zircon_Handle_Properties_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Get_Zircon_Handle_Info_FUCHSIA {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_Device_ಸ್ಮರಣೆ                        ಸ್ಮರಣೆ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
} Vk_ಸ್ಮರಣೆ_Get_Zircon_Handle_Info_FUCHSIA;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Zircon_Handle_FUCHSIA)(VkDevice device, ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Zircon_Handle_Info_FUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Zircon_Handle_Properties_FUCHSIA)(VkDevice device, Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು handleType, zx_handle_t zirconHandle, Vk_ಸ್ಮರಣೆ_Zircon_Handle_Properties_FUCHSIA* p_ಸ್ಮರಣೆ_Zircon_Handle_Properties);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Zircon_Handle_FUCHSIA(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Zircon_Handle_Info_FUCHSIA*   pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Zircon_Handle_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು          handleType,
    zx_handle_t                                 zirconHandle,
    Vk_ಸ್ಮರಣೆ_Zircon_Handle_Properties_FUCHSIA*      p_ಸ್ಮರಣೆ_Zircon_Handle_Properties);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_FUCHSIA_external_semaphore is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_external_semaphore 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_FUCHSIA_external_semaphore"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                              p_ಮುಂದಿನ;
    VkSemaphore                              semaphore;
    VkSemaphoreImportFlags                   flags;
    Vk_External_Semaphore_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
    zx_handle_t                              zirconHandle;
} VkImportSemaphoreZirconHandleInfoFUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType                          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                              p_ಮುಂದಿನ;
    VkSemaphore                              semaphore;
    Vk_External_Semaphore_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
} VkSemaphoreGetZirconHandleInfoFUCHSIA;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkImportSemaphoreZirconHandleFUCHSIA)(VkDevice device, ಸ್ಥಿರಾಂಕ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkGetSemaphoreZirconHandleFUCHSIA)(VkDevice device, ಸ್ಥಿರಾಂಕ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkImportSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkGetSemaphoreZirconHandleFUCHSIA(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo,
    zx_handle_t*                                pZirconHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_FUCHSIA_buffer_collection is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_ಬಫರ್_collection 1

VK_DEFINE_NON_DISPATCHABLE_HANDLE(Vk_ಬಫರ್_Collection_FUCHSIA)

#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_ಬಫರ್_COLLECTION_SPEC_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು VK_FUCHSIA_ಬಫರ್_COLLECTION_EXTENSION_NAME "VK_FUCHSIA_buffer_collection"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkImageFormatConstraintsFlagsFUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Vk_Image_Constraints_Info_Flag_ಬಿಟ್ಟುಗಳು_FUCHSIA {
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_RARELY_FUCHSIA = 0x00000001,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_READ_OFTEN_FUCHSIA = 0x00000002,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_RARELY_FUCHSIA = 0x00000004,
    VK_IMAGE_CONSTRAINTS_INFO_CPU_WRITE_OFTEN_FUCHSIA = 0x00000008,
    VK_IMAGE_CONSTRAINTS_INFO_PROTECTED_OPTIONAL_FUCHSIA = 0x00000010,
    VK_IMAGE_CONSTRAINTS_INFO_FLAG_ಬಿಟ್ಟುಗಳು_MAX_ENUM_FUCHSIA = 0x7FFFFFFF
} Vk_Image_Constraints_Info_Flag_ಬಿಟ್ಟುಗಳು_FUCHSIA;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkImageConstraintsInfoFlagsFUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಬಫರ್_Collection_Create_Info_FUCHSIA {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    zx_handle_t        collectionToken;
} Vk_ಬಫರ್_Collection_Create_Info_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_ಸ್ಮರಣೆ_ಬಫರ್_Collection_FUCHSIA {
    VkStructureType              sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                  p_ಮುಂದಿನ;
    Vk_ಬಫರ್_Collection_FUCHSIA    collection;
    uint32_t                     ಸೂಚ್ಯಂಕ;
} Vk_Import_ಸ್ಮರಣೆ_ಬಫರ್_Collection_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಬಫರ್_Collection_Image_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                  p_ಮುಂದಿನ;
    Vk_ಬಫರ್_Collection_FUCHSIA    collection;
    uint32_t                     ಸೂಚ್ಯಂಕ;
} Vk_ಬಫರ್_Collection_Image_Create_Info_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಬಫರ್_Collection_Constraints_Info_FUCHSIA {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    uint32_t           min_ಬಫರ್_ಎಣಿಕೆ;
    uint32_t           max_ಬಫರ್_ಎಣಿಕೆ;
    uint32_t           min_ಬಫರ್_ಎಣಿಕೆ_For_Camping;
    uint32_t           min_ಬಫರ್_ಎಣಿಕೆ_For_Dedicated_Slack;
    uint32_t           min_ಬಫರ್_ಎಣಿಕೆ_For_Shared_Slack;
} Vk_ಬಫರ್_Collection_Constraints_Info_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಬಫರ್_Constraints_Info_FUCHSIA {
    VkStructureType                             sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                                 p_ಮುಂದಿನ;
    Vk_ಬಫರ್_Create_Info                          createInfo;
    VkFormatFeatureFlags                        requiredFormatFeatures;
    Vk_ಬಫರ್_Collection_Constraints_Info_FUCHSIA    ಬಫರ್_Collection_Constraints;
} Vk_ಬಫರ್_Constraints_Info_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಬಫರ್_Collection_ಬಫರ್_Create_Info_FUCHSIA {
    VkStructureType              sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                  p_ಮುಂದಿನ;
    Vk_ಬಫರ್_Collection_FUCHSIA    collection;
    uint32_t                     ಸೂಚ್ಯಂಕ;
} Vk_ಬಫರ್_Collection_ಬಫರ್_Create_Info_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkSysmemColorSpaceFUCHSIA {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    uint32_t           colorSpace;
} VkSysmemColorSpaceFUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಬಫರ್_Collection_Properties_FUCHSIA {
    VkStructureType                  sType;
    ಶೂನ್ಯ*                            p_ಮುಂದಿನ;
    uint32_t                         ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
    uint32_t                         ಬಫರ್_ಎಣಿಕೆ;
    uint32_t                         create_Info_ಸೂಚ್ಯಂಕ;
    uint64_t                         sysmemPixelFormat;
    VkFormatFeatureFlags             formatFeatures;
    VkSysmemColorSpaceFUCHSIA        sysmem_Color_Space_ಸೂಚ್ಯಂಕ;
    VkComponentMapping               samplerYcbcrConversionComponents;
    VkSamplerYcbcrModelConversion    suggestedYcbcrModel;
    VkSamplerYcbcrRange              suggestedYcbcrRange;
    VkChromaLocation                 suggested_XChroma_ಸ್ಥಾನಾಂತರ;
    VkChromaLocation                 suggested_YChroma_ಸ್ಥಾನಾಂತರ;
} Vk_ಬಫರ್_Collection_Properties_FUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImageFormatConstraintsInfoFUCHSIA {
    VkStructureType                         sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                             p_ಮುಂದಿನ;
    VkImageCreateInfo                       imageCreateInfo;
    VkFormatFeatureFlags                    requiredFormatFeatures;
    VkImageFormatConstraintsFlagsFUCHSIA    flags;
    uint64_t                                sysmemPixelFormat;
    uint32_t                                color_Space_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ VkSysmemColorSpaceFUCHSIA*        pColorSpaces;
} VkImageFormatConstraintsInfoFUCHSIA;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImageConstraintsInfoFUCHSIA {
    VkStructureType                               sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                                   p_ಮುಂದಿನ;
    uint32_t                                      format_Constraints_ಎಣಿಕೆ;
    ಸ್ಥಿರಾಂಕ VkImageFormatConstraintsInfoFUCHSIA*    pFormatConstraints;
    Vk_ಬಫರ್_Collection_Constraints_Info_FUCHSIA      ಬಫರ್_Collection_Constraints;
    VkImageConstraintsInfoFlagsFUCHSIA            flags;
} VkImageConstraintsInfoFUCHSIA;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Create_ಬಫರ್_Collection_FUCHSIA)(VkDevice device, ಸ್ಥಿರಾಂಕ Vk_ಬಫರ್_Collection_Create_Info_FUCHSIA* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, Vk_ಬಫರ್_Collection_FUCHSIA* pCollection);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_ಗಣ_ಬಫರ್_Collection_Image_Constraints_FUCHSIA)(VkDevice device, Vk_ಬಫರ್_Collection_FUCHSIA collection, ಸ್ಥಿರಾಂಕ VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_ಗಣ_ಬಫರ್_Collection_ಬಫರ್_Constraints_FUCHSIA)(VkDevice device, Vk_ಬಫರ್_Collection_FUCHSIA collection, ಸ್ಥಿರಾಂಕ Vk_ಬಫರ್_Constraints_Info_FUCHSIA* p_ಬಫರ್_Constraints_Info);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vk_Destroy_ಬಫರ್_Collection_FUCHSIA)(VkDevice device, Vk_ಬಫರ್_Collection_FUCHSIA collection, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಬಫರ್_Collection_Properties_FUCHSIA)(VkDevice device, Vk_ಬಫರ್_Collection_FUCHSIA collection, Vk_ಬಫರ್_Collection_Properties_FUCHSIA* pProperties);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Create_ಬಫರ್_Collection_FUCHSIA(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ Vk_ಬಫರ್_Collection_Create_Info_FUCHSIA*  pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    Vk_ಬಫರ್_Collection_FUCHSIA*                  pCollection);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_ಗಣ_ಬಫರ್_Collection_Image_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_ಬಫರ್_Collection_FUCHSIA                   collection,
    ಸ್ಥಿರಾಂಕ VkImageConstraintsInfoFUCHSIA*        pImageConstraintsInfo);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_ಗಣ_ಬಫರ್_Collection_ಬಫರ್_Constraints_FUCHSIA(
    VkDevice                                    device,
    Vk_ಬಫರ್_Collection_FUCHSIA                   collection,
    ಸ್ಥಿರಾಂಕ Vk_ಬಫರ್_Constraints_Info_FUCHSIA*       p_ಬಫರ್_Constraints_Info);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vk_Destroy_ಬಫರ್_Collection_FUCHSIA(
    VkDevice                                    device,
    Vk_ಬಫರ್_Collection_FUCHSIA                   collection,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಬಫರ್_Collection_Properties_FUCHSIA(
    VkDevice                                    device,
    Vk_ಬಫರ್_Collection_FUCHSIA                   collection,
    Vk_ಬಫರ್_Collection_Properties_FUCHSIA*        pProperties);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

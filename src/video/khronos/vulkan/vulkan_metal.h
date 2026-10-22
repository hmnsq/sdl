#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VULKAN_METAL_H_
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_METAL_H_ 1

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



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_metal_surface 1

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__
@class CAMetalLayer;
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ CAMetalLayer;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_UNSAFE_UNRETAINED
#ಆದರೆ defined(__OBJC__) && defined(__has_feature)
#ಆದರೆ __has_feature(objc_arc)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು SDL_UNSAFE_UNRETAINED
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_UNSAFE_UNRETAINED __unsafe_unretained
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_METAL_SURFACE_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkMetalSurfaceCreateFlagsEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                     p_ಮುಂದಿನ;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ಸ್ಥಿರಾಂಕ CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ಸ್ಥಿರಾಂಕ VkMetalSurfaceCreateInfoEXT* pCreateInfo, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ಸ್ಥಿರಾಂಕ VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_metal_objects 1

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__
@protocol MTLDevice;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __unsafe_unretained id<MTLDevice> MTLDevice_id;
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ* MTLDevice_id;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__
@protocol MTLCommand_ಸರತಿ;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __unsafe_unretained id<MTLCommand_ಸರತಿ> MTLCommand_ಸರತಿ_id;
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ* MTLCommand_ಸರತಿ_id;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__
@protocol MTLBuffer;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ* MTLBuffer_id;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__
@protocol MTLTexture;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __unsafe_unretained id<MTLTexture> MTLTexture_id;
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ* MTLTexture_id;
#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ __IOSurface* IOSurfaceRef;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __OBJC__
#ಸೂಚನೆ clang diagnostic ತಳ್ಳು
#ಸೂಚನೆ clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#ಸೂಚನೆ clang diagnostic ತೆಗೆ
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ* MTLSharedEvent_id;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_METAL_OBJECTS_SPEC_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Vk_Export_Metal_Object_Type_Flag_ಬಿಟ್ಟುಗಳು_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_ಬಿಟ್_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_ಸರತಿ_ಬಿಟ್_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_ಬಫರ್_ಬಿಟ್_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_ಬಿಟ್_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_ಬಿಟ್_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_ಬಿಟ್_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_ಬಿಟ್ಟುಗಳು_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_ಬಿಟ್ಟುಗಳು_EXT;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkExportMetalObjectTypeFlagsEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_Export_Metal_Object_Type_Flag_ಬಿಟ್ಟುಗಳು_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
} VkExportMetalObjectsInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Export_Metal_Command_ಸರತಿ_Info_EXT {
    VkStructureType       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*           p_ಮುಂದಿನ;
    Vk_ಸರತಿ               ಸರತಿ;
    MTLCommand_ಸರತಿ_id    mtl_Command_ಸರತಿ;
} Vk_Export_Metal_Command_ಸರತಿ_Info_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Export_Metal_ಬಫರ್_Info_EXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    Vk_Device_ಸ್ಮರಣೆ     ಸ್ಮರಣೆ;
    MTLBuffer_id       mtl_ಬಫರ್;
} Vk_Export_Metal_ಬಫರ್_Info_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_Metal_ಬಫರ್_Info_EXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    MTLBuffer_id       mtl_ಬಫರ್;
} Vk_Import_Metal_ಬಫರ್_Info_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    VkImage                  image;
    VkImageView              imageView;
    Vk_ಬಫರ್_View             ಬಫರ್_View;
    Vk_Image_Aspect_Flag_ಬಿಟ್ಟುಗಳು    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    Vk_Image_Aspect_Flag_ಬಿಟ್ಟುಗಳು    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*        p_ಮುಂದಿನ;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*          p_ಮುಂದಿನ;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*          p_ಮುಂದಿನ;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ಶೂನ್ಯ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_external_ಸ್ಮರಣೆ_metal 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_EXTERNAL_ಸ್ಮರಣೆ_METAL_SPEC_ಆವೃತ್ತಿ 1
#ವ್ಯಾಖ್ಯಾನಿಸು VK_EXT_EXTERNAL_ಸ್ಮರಣೆ_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Import_ಸ್ಮರಣೆ_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
    ಶೂನ್ಯ*                                 handle;
} Vk_Import_ಸ್ಮರಣೆ_Metal_Handle_Info_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    ಶೂನ್ಯ*              p_ಮುಂದಿನ;
    uint32_t           ಸ್ಮರಣೆ_Type_ಬಿಟ್ಟುಗಳು;
} Vk_ಸ್ಮರಣೆ_Metal_Handle_Properties_EXT;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_ಸ್ಮರಣೆ_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                           p_ಮುಂದಿನ;
    Vk_Device_ಸ್ಮರಣೆ                        ಸ್ಮರಣೆ;
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು    handleType;
} Vk_ಸ್ಮರಣೆ_Get_Metal_Handle_Info_EXT;


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Metal_Handle_EXT)(VkDevice device, ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, ಶೂನ್ಯ** pHandle);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Get_ಸ್ಮರಣೆ_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು handleType, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* pHandle, Vk_ಸ್ಮರಣೆ_Metal_Handle_Properties_EXT* p_ಸ್ಮರಣೆ_Metal_Handle_Properties);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_NO_PROTOTYPES

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Metal_Handle_EXT(
    VkDevice                                    device,
    ಸ್ಥಿರಾಂಕ Vk_ಸ್ಮರಣೆ_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    ಶೂನ್ಯ**                                      pHandle);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Get_ಸ್ಮರಣೆ_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_ಸ್ಮರಣೆ_Handle_Type_Flag_ಬಿಟ್ಟುಗಳು          handleType,
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*                                 pHandle,
    Vk_ಸ್ಮರಣೆ_Metal_Handle_Properties_EXT*           p_ಸ್ಮರಣೆ_Metal_Handle_Properties);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

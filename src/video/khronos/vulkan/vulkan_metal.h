#جيڪڏهن_وصف_نه_ٿيل VULKAN_METAL_H_
#وصف_ڪريو VULKAN_METAL_H_ 1

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



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_EXT_metal_surface 1

#جيڪڏهن_وصف_ٿيل __OBJC__
@class CAMetalLayer;
#وإلا
تعريفنوع فراغ CAMetalLayer;
#جيڪڏهن_پورو

#وصف_ڪريو SDL_UNSAFE_UNRETAINED
#إذا defined(__OBJC__) && defined(__has_feature)
#إذا __has_feature(objc_arc)
#وصف_رد SDL_UNSAFE_UNRETAINED
#وصف_ڪريو SDL_UNSAFE_UNRETAINED __unsafe_unretained
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#وصف_ڪريو VK_EXT_METAL_SURFACE_SPEC_نسخو 1
#وصف_ڪريو VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

تعريفنوع VkFlags VkMetalSurfaceCreateFlagsEXT;

تعريفنوع بنية VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت فراغ*                     p_ايندڙ;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت Vk_ورهاست_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ثابت VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ثابت Vk_ورهاست_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_EXT_metal_objects 1

#جيڪڏهن_وصف_ٿيل __OBJC__
@protocol MTLDevice;
تعريفنوع __unsafe_unretained id<MTLDevice> MTLDevice_id;
#وإلا
تعريفنوع فراغ* MTLDevice_id;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل __OBJC__
@protocol MTLCommand_قطار;
تعريفنوع __unsafe_unretained id<MTLCommand_قطار> MTLCommand_قطار_id;
#وإلا
تعريفنوع فراغ* MTLCommand_قطار_id;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل __OBJC__
@protocol MTLBuffer;
تعريفنوع __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#وإلا
تعريفنوع فراغ* MTLBuffer_id;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل __OBJC__
@protocol MTLTexture;
تعريفنوع __unsafe_unretained id<MTLTexture> MTLTexture_id;
#وإلا
تعريفنوع فراغ* MTLTexture_id;
#جيڪڏهن_پورو
تعريفنوع بنية __IOSurface* IOSurfaceRef;
#جيڪڏهن_وصف_ٿيل __OBJC__
#هدايت clang diagnostic ڌڪو
#هدايت clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
تعريفنوع __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#هدايت clang diagnostic ڪڍو
#وإلا
تعريفنوع فراغ* MTLSharedEvent_id;
#جيڪڏهن_پورو

#وصف_ڪريو VK_EXT_METAL_OBJECTS_SPEC_نسخو 2
#وصف_ڪريو VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

تعريفنوع تعداد Vk_Export_Metal_Object_Type_Flag_بٽ_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_ٻٽو_انگ_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_قطار_ٻٽو_انگ_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_بفر_ٻٽو_انگ_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_ٻٽو_انگ_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_ٻٽو_انگ_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_ٻٽو_انگ_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_بٽ_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_بٽ_EXT;
تعريفنوع VkFlags VkExportMetalObjectTypeFlagsEXT;

تعريفنوع بنية VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_Export_Metal_Object_Type_Flag_بٽ_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

تعريفنوع بنية VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
} VkExportMetalObjectsInfoEXT;

تعريفنوع بنية VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

تعريفنوع بنية Vk_Export_Metal_Command_قطار_Info_EXT {
    VkStructureType       sType;
    ثابت فراغ*           p_ايندڙ;
    Vk_قطار               قطار;
    MTLCommand_قطار_id    mtl_Command_قطار;
} Vk_Export_Metal_Command_قطار_Info_EXT;

تعريفنوع بنية Vk_Export_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    Vk_Device_يادگيري     يادگيري;
    MTLBuffer_id       mtl_بفر;
} Vk_Export_Metal_بفر_Info_EXT;

تعريفنوع بنية Vk_Import_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    MTLBuffer_id       mtl_بفر;
} Vk_Import_Metal_بفر_Info_EXT;

تعريفنوع بنية VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_ايندڙ;
    VkImage                  image;
    VkImageView              imageView;
    Vk_بفر_View             بفر_View;
    Vk_Image_Aspect_Flag_بٽ    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

تعريفنوع بنية VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_ايندڙ;
    Vk_Image_Aspect_Flag_بٽ    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

تعريفنوع بنية VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_ايندڙ;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_ايندڙ;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

تعريفنوع بنية VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_ايندڙ;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


تعريفنوع فراغ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#جيڪڏهن_پورو
#جيڪڏهن_پورو


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#وصف_ڪريو VK_EXT_external_يادگيري_metal 1

#وصف_ڪريو VK_EXT_EXTERNAL_يادگيري_METAL_SPEC_نسخو 1
#وصف_ڪريو VK_EXT_EXTERNAL_يادگيري_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

تعريفنوع بنية Vk_Import_يادگيري_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_External_يادگيري_Handle_Type_Flag_بٽ    handleType;
    فراغ*                                 handle;
} Vk_Import_يادگيري_Metal_Handle_Info_EXT;

تعريفنوع بنية Vk_يادگيري_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    فراغ*              p_ايندڙ;
    uint32_t           يادگيري_Type_بٽ;
} Vk_يادگيري_Metal_Handle_Properties_EXT;

تعريفنوع بنية Vk_يادگيري_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_ايندڙ;
    Vk_Device_يادگيري                        يادگيري;
    Vk_External_يادگيري_Handle_Type_Flag_بٽ    handleType;
} Vk_يادگيري_Get_Metal_Handle_Info_EXT;


تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Metal_Handle_EXT)(VkDevice device, ثابت Vk_يادگيري_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, فراغ** pHandle);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Get_يادگيري_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_يادگيري_Handle_Type_Flag_بٽ handleType, ثابت فراغ* pHandle, Vk_يادگيري_Metal_Handle_Properties_EXT* p_يادگيري_Metal_Handle_Properties);

#جيڪڏهن_وصف_نه_ٿيل VK_NO_PROTOTYPES

#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Metal_Handle_EXT(
    VkDevice                                    device,
    ثابت Vk_يادگيري_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    فراغ**                                      pHandle);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Get_يادگيري_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_يادگيري_Handle_Type_Flag_بٽ          handleType,
    ثابت فراغ*                                 pHandle,
    Vk_يادگيري_Metal_Handle_Properties_EXT*           p_يادگيري_Metal_Handle_Properties);
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو

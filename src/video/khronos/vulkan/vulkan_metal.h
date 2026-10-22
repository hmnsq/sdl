#که_نه_تعریف_شوی VULKAN_METAL_H_
#تعریف_کړه VULKAN_METAL_H_ 1

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



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_EXT_metal_surface 1

#که_تعریف_شوی __OBJC__
@class CAMetalLayer;
#وإلا
تعريفنوع فراغ CAMetalLayer;
#د_که_پای

#تعریف_کړه SDL_UNSAFE_UNRETAINED
#إذا defined(__OBJC__) && defined(__has_feature)
#إذا __has_feature(objc_arc)
#تعریف_لغوه SDL_UNSAFE_UNRETAINED
#تعریف_کړه SDL_UNSAFE_UNRETAINED __unsafe_unretained
#د_که_پای
#د_که_پای

#تعریف_کړه VK_EXT_METAL_SURFACE_SPEC_نسخه 1
#تعریف_کړه VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

تعريفنوع VkFlags VkMetalSurfaceCreateFlagsEXT;

تعريفنوع بنية VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت فراغ*                     p_بل;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت Vk_ویش_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ثابت VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ثابت Vk_ویش_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#د_که_پای
#د_که_پای


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_EXT_metal_objects 1

#که_تعریف_شوی __OBJC__
@protocol MTLDevice;
تعريفنوع __unsafe_unretained id<MTLDevice> MTLDevice_id;
#وإلا
تعريفنوع فراغ* MTLDevice_id;
#د_که_پای
#که_تعریف_شوی __OBJC__
@protocol MTLCommand_کتار;
تعريفنوع __unsafe_unretained id<MTLCommand_کتار> MTLCommand_کتار_id;
#وإلا
تعريفنوع فراغ* MTLCommand_کتار_id;
#د_که_پای
#که_تعریف_شوی __OBJC__
@protocol MTLBuffer;
تعريفنوع __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#وإلا
تعريفنوع فراغ* MTLBuffer_id;
#د_که_پای
#که_تعریف_شوی __OBJC__
@protocol MTLTexture;
تعريفنوع __unsafe_unretained id<MTLTexture> MTLTexture_id;
#وإلا
تعريفنوع فراغ* MTLTexture_id;
#د_که_پای
تعريفنوع بنية __IOSurface* IOSurfaceRef;
#که_تعریف_شوی __OBJC__
#لارښوونه clang diagnostic ټېل
#لارښوونه clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
تعريفنوع __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#لارښوونه clang diagnostic راوباسه
#وإلا
تعريفنوع فراغ* MTLSharedEvent_id;
#د_که_پای

#تعریف_کړه VK_EXT_METAL_OBJECTS_SPEC_نسخه 2
#تعریف_کړه VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

تعريفنوع تعداد Vk_Export_Metal_Object_Type_Flag_بټونه_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_بټ_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_کتار_بټ_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_بفر_بټ_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_بټ_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_بټ_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_بټ_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_بټونه_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_بټونه_EXT;
تعريفنوع VkFlags VkExportMetalObjectTypeFlagsEXT;

تعريفنوع بنية VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_Export_Metal_Object_Type_Flag_بټونه_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

تعريفنوع بنية VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
} VkExportMetalObjectsInfoEXT;

تعريفنوع بنية VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

تعريفنوع بنية Vk_Export_Metal_Command_کتار_Info_EXT {
    VkStructureType       sType;
    ثابت فراغ*           p_بل;
    Vk_کتار               کتار;
    MTLCommand_کتار_id    mtl_Command_کتار;
} Vk_Export_Metal_Command_کتار_Info_EXT;

تعريفنوع بنية Vk_Export_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    Vk_Device_حافظه     حافظه;
    MTLBuffer_id       mtl_بفر;
} Vk_Export_Metal_بفر_Info_EXT;

تعريفنوع بنية Vk_Import_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    MTLBuffer_id       mtl_بفر;
} Vk_Import_Metal_بفر_Info_EXT;

تعريفنوع بنية VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_بل;
    VkImage                  image;
    VkImageView              imageView;
    Vk_بفر_View             بفر_View;
    Vk_Image_Aspect_Flag_بټونه    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

تعريفنوع بنية VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_بل;
    Vk_Image_Aspect_Flag_بټونه    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

تعريفنوع بنية VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بل;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_بل;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

تعريفنوع بنية VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_بل;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


تعريفنوع فراغ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#د_که_پای
#د_که_پای


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#تعریف_کړه VK_EXT_external_حافظه_metal 1

#تعریف_کړه VK_EXT_EXTERNAL_حافظه_METAL_SPEC_نسخه 1
#تعریف_کړه VK_EXT_EXTERNAL_حافظه_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

تعريفنوع بنية Vk_Import_حافظه_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_External_حافظه_Handle_Type_Flag_بټونه    handleType;
    فراغ*                                 handle;
} Vk_Import_حافظه_Metal_Handle_Info_EXT;

تعريفنوع بنية Vk_حافظه_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    فراغ*              p_بل;
    uint32_t           حافظه_Type_بټونه;
} Vk_حافظه_Metal_Handle_Properties_EXT;

تعريفنوع بنية Vk_حافظه_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بل;
    Vk_Device_حافظه                        حافظه;
    Vk_External_حافظه_Handle_Type_Flag_بټونه    handleType;
} Vk_حافظه_Get_Metal_Handle_Info_EXT;


تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Metal_Handle_EXT)(VkDevice device, ثابت Vk_حافظه_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, فراغ** pHandle);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Get_حافظه_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_حافظه_Handle_Type_Flag_بټونه handleType, ثابت فراغ* pHandle, Vk_حافظه_Metal_Handle_Properties_EXT* p_حافظه_Metal_Handle_Properties);

#که_نه_تعریف_شوی VK_NO_PROTOTYPES

#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Metal_Handle_EXT(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    فراغ**                                      pHandle);
#د_که_پای
#که_نه_تعریف_شوی VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Get_حافظه_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_حافظه_Handle_Type_Flag_بټونه          handleType,
    ثابت فراغ*                                 pHandle,
    Vk_حافظه_Metal_Handle_Properties_EXT*           p_حافظه_Metal_Handle_Properties);
#د_که_پای
#د_که_پای

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای

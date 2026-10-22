#اگر_غیر_تعریف_شدہ VULKAN_METAL_H_
#تعریف_کرو VULKAN_METAL_H_ 1

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



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_metal_surface 1

#اگر_تعریف_شدہ __OBJC__
@class CAMetalLayer;
#ورنہ
قسمتعریف خالی CAMetalLayer;
#اگر_ختم

#تعریف_کرو SDL_UNSAFE_UNRETAINED
#اگر defined(__OBJC__) && defined(__has_feature)
#اگر __has_feature(objc_arc)
#تعریف_منسوخ SDL_UNSAFE_UNRETAINED
#تعریف_کرو SDL_UNSAFE_UNRETAINED __unsafe_unretained
#اگر_ختم
#اگر_ختم

#تعریف_کرو VK_EXT_METAL_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

قسمتعریف VkFlags VkMetalSurfaceCreateFlagsEXT;

قسمتعریف ساخت VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت خالی*                     p_اگلا;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ثابت VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#اگر_ختم
#اگر_ختم


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_metal_objects 1

#اگر_تعریف_شدہ __OBJC__
@protocol MTLDevice;
قسمتعریف __unsafe_unretained id<MTLDevice> MTLDevice_id;
#ورنہ
قسمتعریف خالی* MTLDevice_id;
#اگر_ختم
#اگر_تعریف_شدہ __OBJC__
@protocol MTLCommand_قطار;
قسمتعریف __unsafe_unretained id<MTLCommand_قطار> MTLCommand_قطار_id;
#ورنہ
قسمتعریف خالی* MTLCommand_قطار_id;
#اگر_ختم
#اگر_تعریف_شدہ __OBJC__
@protocol MTLBuffer;
قسمتعریف __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#ورنہ
قسمتعریف خالی* MTLBuffer_id;
#اگر_ختم
#اگر_تعریف_شدہ __OBJC__
@protocol MTLTexture;
قسمتعریف __unsafe_unretained id<MTLTexture> MTLTexture_id;
#ورنہ
قسمتعریف خالی* MTLTexture_id;
#اگر_ختم
قسمتعریف ساخت __IOSurface* IOSurfaceRef;
#اگر_تعریف_شدہ __OBJC__
#ہدایت clang diagnostic ڈالو
#ہدایت clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
قسمتعریف __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#ہدایت clang diagnostic نکالو
#ورنہ
قسمتعریف خالی* MTLSharedEvent_id;
#اگر_ختم

#تعریف_کرو VK_EXT_METAL_OBJECTS_SPEC_نسخہ 2
#تعریف_کرو VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

قسمتعریف شمار Vk_Export_Metal_Object_Type_Flag_بٹ_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_ثنائی_ہندسہ_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_قطار_ثنائی_ہندسہ_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_بفر_ثنائی_ہندسہ_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_ثنائی_ہندسہ_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_ثنائی_ہندسہ_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_ثنائی_ہندسہ_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_بٹ_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_بٹ_EXT;
قسمتعریف VkFlags VkExportMetalObjectTypeFlagsEXT;

قسمتعریف ساخت VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_Export_Metal_Object_Type_Flag_بٹ_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

قسمتعریف ساخت VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
} VkExportMetalObjectsInfoEXT;

قسمتعریف ساخت VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

قسمتعریف ساخت Vk_Export_Metal_Command_قطار_Info_EXT {
    VkStructureType       sType;
    ثابت خالی*           p_اگلا;
    Vk_قطار               قطار;
    MTLCommand_قطار_id    mtl_Command_قطار;
} Vk_Export_Metal_Command_قطار_Info_EXT;

قسمتعریف ساخت Vk_Export_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    Vk_Device_حافظہ     حافظہ;
    MTLBuffer_id       mtl_بفر;
} Vk_Export_Metal_بفر_Info_EXT;

قسمتعریف ساخت Vk_Import_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    MTLBuffer_id       mtl_بفر;
} Vk_Import_Metal_بفر_Info_EXT;

قسمتعریف ساخت VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت خالی*              p_اگلا;
    VkImage                  image;
    VkImageView              imageView;
    Vk_بفر_View             بفر_View;
    Vk_Image_Aspect_Flag_بٹ    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

قسمتعریف ساخت VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت خالی*              p_اگلا;
    Vk_Image_Aspect_Flag_بٹ    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

قسمتعریف ساخت VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

قسمتعریف ساخت VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت خالی*        p_اگلا;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

قسمتعریف ساخت VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت خالی*          p_اگلا;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

قسمتعریف ساخت VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت خالی*          p_اگلا;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


قسمتعریف خالی (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR خالی VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#اگر_ختم
#اگر_ختم


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_external_حافظہ_metal 1

#تعریف_کرو VK_EXT_EXTERNAL_حافظہ_METAL_SPEC_نسخہ 1
#تعریف_کرو VK_EXT_EXTERNAL_حافظہ_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

قسمتعریف ساخت Vk_Import_حافظہ_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
    خالی*                                 handle;
} Vk_Import_حافظہ_Metal_Handle_Info_EXT;

قسمتعریف ساخت Vk_حافظہ_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    خالی*              p_اگلا;
    uint32_t           حافظہ_Type_بٹ;
} Vk_حافظہ_Metal_Handle_Properties_EXT;

قسمتعریف ساخت Vk_حافظہ_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت خالی*                           p_اگلا;
    Vk_Device_حافظہ                        حافظہ;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
} Vk_حافظہ_Get_Metal_Handle_Info_EXT;


قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Metal_Handle_EXT)(VkDevice device, ثابت Vk_حافظہ_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, خالی** pHandle);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_حافظہ_Handle_Type_Flag_بٹ handleType, ثابت خالی* pHandle, Vk_حافظہ_Metal_Handle_Properties_EXT* p_حافظہ_Metal_Handle_Properties);

#اگر_غیر_تعریف_شدہ VK_NO_PROTOTYPES

#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Metal_Handle_EXT(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    خالی**                                      pHandle);
#اگر_ختم
#اگر_غیر_تعریف_شدہ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_حافظہ_Handle_Type_Flag_بٹ          handleType,
    ثابت خالی*                                 pHandle,
    Vk_حافظہ_Metal_Handle_Properties_EXT*           p_حافظہ_Metal_Handle_Properties);
#اگر_ختم
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم

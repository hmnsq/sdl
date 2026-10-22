#جے_بنا_تعریف VULKAN_METAL_H_
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


#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_metal_surface 1

#جے_تعریف_شدہ __OBJC__
@class CAMetalLayer;
#وإلا
تعريفنوع فراغ CAMetalLayer;
#جے_انت

#تعریف_کرو SDL_UNSAFE_UNRETAINED
#إذا defined(__OBJC__) && defined(__has_feature)
#إذا __has_feature(objc_arc)
#تعریف_رد SDL_UNSAFE_UNRETAINED
#تعریف_کرو SDL_UNSAFE_UNRETAINED __unsafe_unretained
#جے_انت
#جے_انت

#تعریف_کرو VK_EXT_METAL_SURFACE_SPEC_نسخہ 1
#تعریف_کرو VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

تعريفنوع VkFlags VkMetalSurfaceCreateFlagsEXT;

تعريفنوع بنية VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت فراغ*                     p_اگلا;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت Vk_ونڈ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ثابت VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ثابت Vk_ونڈ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#جے_انت
#جے_انت


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_metal_objects 1

#جے_تعریف_شدہ __OBJC__
@protocol MTLDevice;
تعريفنوع __unsafe_unretained id<MTLDevice> MTLDevice_id;
#وإلا
تعريفنوع فراغ* MTLDevice_id;
#جے_انت
#جے_تعریف_شدہ __OBJC__
@protocol MTLCommand_قطار;
تعريفنوع __unsafe_unretained id<MTLCommand_قطار> MTLCommand_قطار_id;
#وإلا
تعريفنوع فراغ* MTLCommand_قطار_id;
#جے_انت
#جے_تعریف_شدہ __OBJC__
@protocol MTLBuffer;
تعريفنوع __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#وإلا
تعريفنوع فراغ* MTLBuffer_id;
#جے_انت
#جے_تعریف_شدہ __OBJC__
@protocol MTLTexture;
تعريفنوع __unsafe_unretained id<MTLTexture> MTLTexture_id;
#وإلا
تعريفنوع فراغ* MTLTexture_id;
#جے_انت
تعريفنوع بنية __IOSurface* IOSurfaceRef;
#جے_تعریف_شدہ __OBJC__
#ہدایت clang diagnostic ڈالو
#ہدایت clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
تعريفنوع __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#ہدایت clang diagnostic نکالو
#وإلا
تعريفنوع فراغ* MTLSharedEvent_id;
#جے_انت

#تعریف_کرو VK_EXT_METAL_OBJECTS_SPEC_نسخہ 2
#تعریف_کرو VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

تعريفنوع تعداد Vk_Export_Metal_Object_Type_Flag_بٹ_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_ثنائی_ہندسہ_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_قطار_ثنائی_ہندسہ_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_بفر_ثنائی_ہندسہ_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_ثنائی_ہندسہ_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_ثنائی_ہندسہ_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_ثنائی_ہندسہ_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_بٹ_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_بٹ_EXT;
تعريفنوع VkFlags VkExportMetalObjectTypeFlagsEXT;

تعريفنوع بنية VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_Export_Metal_Object_Type_Flag_بٹ_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

تعريفنوع بنية VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
} VkExportMetalObjectsInfoEXT;

تعريفنوع بنية VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

تعريفنوع بنية Vk_Export_Metal_Command_قطار_Info_EXT {
    VkStructureType       sType;
    ثابت فراغ*           p_اگلا;
    Vk_قطار               قطار;
    MTLCommand_قطار_id    mtl_Command_قطار;
} Vk_Export_Metal_Command_قطار_Info_EXT;

تعريفنوع بنية Vk_Export_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    Vk_Device_حافظہ     حافظہ;
    MTLBuffer_id       mtl_بفر;
} Vk_Export_Metal_بفر_Info_EXT;

تعريفنوع بنية Vk_Import_Metal_بفر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    MTLBuffer_id       mtl_بفر;
} Vk_Import_Metal_بفر_Info_EXT;

تعريفنوع بنية VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_اگلا;
    VkImage                  image;
    VkImageView              imageView;
    Vk_بفر_View             بفر_View;
    Vk_Image_Aspect_Flag_بٹ    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

تعريفنوع بنية VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_اگلا;
    Vk_Image_Aspect_Flag_بٹ    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

تعريفنوع بنية VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_اگلا;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_اگلا;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

تعريفنوع بنية VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_اگلا;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


تعريفنوع فراغ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#جے_انت
#جے_انت


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#تعریف_کرو VK_EXT_external_حافظہ_metal 1

#تعریف_کرو VK_EXT_EXTERNAL_حافظہ_METAL_SPEC_نسخہ 1
#تعریف_کرو VK_EXT_EXTERNAL_حافظہ_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

تعريفنوع بنية Vk_Import_حافظہ_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
    فراغ*                                 handle;
} Vk_Import_حافظہ_Metal_Handle_Info_EXT;

تعريفنوع بنية Vk_حافظہ_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    فراغ*              p_اگلا;
    uint32_t           حافظہ_Type_بٹ;
} Vk_حافظہ_Metal_Handle_Properties_EXT;

تعريفنوع بنية Vk_حافظہ_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_اگلا;
    Vk_Device_حافظہ                        حافظہ;
    Vk_External_حافظہ_Handle_Type_Flag_بٹ    handleType;
} Vk_حافظہ_Get_Metal_Handle_Info_EXT;


تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Metal_Handle_EXT)(VkDevice device, ثابت Vk_حافظہ_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, فراغ** pHandle);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Get_حافظہ_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_حافظہ_Handle_Type_Flag_بٹ handleType, ثابت فراغ* pHandle, Vk_حافظہ_Metal_Handle_Properties_EXT* p_حافظہ_Metal_Handle_Properties);

#جے_بنا_تعریف VK_NO_PROTOTYPES

#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Metal_Handle_EXT(
    VkDevice                                    device,
    ثابت Vk_حافظہ_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    فراغ**                                      pHandle);
#جے_انت
#جے_بنا_تعریف VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Get_حافظہ_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_حافظہ_Handle_Type_Flag_بٹ          handleType,
    ثابت فراغ*                                 pHandle,
    Vk_حافظہ_Metal_Handle_Properties_EXT*           p_حافظہ_Metal_Handle_Properties);
#جے_انت
#جے_انت

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت

#اگر_تعریف_نشده VULKAN_METAL_H_
#تعریف_کن VULKAN_METAL_H_ 1

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



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_EXT_metal_surface 1

#اگر_تعریف_شده __OBJC__
@class CAMetalLayer;
#وإلا
تعريفنوع فراغ CAMetalLayer;
#پایان_اگر

#تعریف_کن SDL_UNSAFE_UNRETAINED
#إذا defined(__OBJC__) && defined(__has_feature)
#إذا __has_feature(objc_arc)
#لغو_تعریف SDL_UNSAFE_UNRETAINED
#تعریف_کن SDL_UNSAFE_UNRETAINED __unsafe_unretained
#پایان_اگر
#پایان_اگر

#تعریف_کن VK_EXT_METAL_SURFACE_SPEC_نسخه 1
#تعریف_کن VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

تعريفنوع VkFlags VkMetalSurfaceCreateFlagsEXT;

تعريفنوع بنية VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت فراغ*                     p_بعدی;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت Vk_تخصیص_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ثابت VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ثابت Vk_تخصیص_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#پایان_اگر
#پایان_اگر


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_EXT_metal_objects 1

#اگر_تعریف_شده __OBJC__
@protocol MTLDevice;
تعريفنوع __unsafe_unretained id<MTLDevice> MTLDevice_id;
#وإلا
تعريفنوع فراغ* MTLDevice_id;
#پایان_اگر
#اگر_تعریف_شده __OBJC__
@protocol MTLCommand_صف;
تعريفنوع __unsafe_unretained id<MTLCommand_صف> MTLCommand_صف_id;
#وإلا
تعريفنوع فراغ* MTLCommand_صف_id;
#پایان_اگر
#اگر_تعریف_شده __OBJC__
@protocol MTLBuffer;
تعريفنوع __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#وإلا
تعريفنوع فراغ* MTLBuffer_id;
#پایان_اگر
#اگر_تعریف_شده __OBJC__
@protocol MTLTexture;
تعريفنوع __unsafe_unretained id<MTLTexture> MTLTexture_id;
#وإلا
تعريفنوع فراغ* MTLTexture_id;
#پایان_اگر
تعريفنوع بنية __IOSurface* IOSurfaceRef;
#اگر_تعریف_شده __OBJC__
#رهنمود clang diagnostic افزودن
#رهنمود clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
تعريفنوع __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#رهنمود clang diagnostic برداشت
#وإلا
تعريفنوع فراغ* MTLSharedEvent_id;
#پایان_اگر

#تعریف_کن VK_EXT_METAL_OBJECTS_SPEC_نسخه 2
#تعریف_کن VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

تعريفنوع تعداد Vk_Export_Metal_Object_Type_Flag_بیتها_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_بیت_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_صف_بیت_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_میانگیر_بیت_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_بیت_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_بیت_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_بیت_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_بیتها_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_بیتها_EXT;
تعريفنوع VkFlags VkExportMetalObjectTypeFlagsEXT;

تعريفنوع بنية VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_Export_Metal_Object_Type_Flag_بیتها_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

تعريفنوع بنية VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
} VkExportMetalObjectsInfoEXT;

تعريفنوع بنية VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

تعريفنوع بنية Vk_Export_Metal_Command_صف_Info_EXT {
    VkStructureType       sType;
    ثابت فراغ*           p_بعدی;
    Vk_صف               صف;
    MTLCommand_صف_id    mtl_Command_صف;
} Vk_Export_Metal_Command_صف_Info_EXT;

تعريفنوع بنية Vk_Export_Metal_میانگیر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    Vk_Device_حافظه     حافظه;
    MTLBuffer_id       mtl_میانگیر;
} Vk_Export_Metal_میانگیر_Info_EXT;

تعريفنوع بنية Vk_Import_Metal_میانگیر_Info_EXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    MTLBuffer_id       mtl_میانگیر;
} Vk_Import_Metal_میانگیر_Info_EXT;

تعريفنوع بنية VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_بعدی;
    VkImage                  image;
    VkImageView              imageView;
    Vk_میانگیر_View             میانگیر_View;
    Vk_Image_Aspect_Flag_بیتها    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

تعريفنوع بنية VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              p_بعدی;
    Vk_Image_Aspect_Flag_بیتها    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

تعريفنوع بنية VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        p_بعدی;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_بعدی;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

تعريفنوع بنية VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          p_بعدی;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


تعريفنوع فراغ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#پایان_اگر
#پایان_اگر


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#تعریف_کن VK_EXT_external_حافظه_metal 1

#تعریف_کن VK_EXT_EXTERNAL_حافظه_METAL_SPEC_نسخه 1
#تعریف_کن VK_EXT_EXTERNAL_حافظه_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

تعريفنوع بنية Vk_Import_حافظه_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_External_حافظه_Handle_Type_Flag_بیتها    handleType;
    فراغ*                                 handle;
} Vk_Import_حافظه_Metal_Handle_Info_EXT;

تعريفنوع بنية Vk_حافظه_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    فراغ*              p_بعدی;
    uint32_t           حافظه_Type_بیتها;
} Vk_حافظه_Metal_Handle_Properties_EXT;

تعريفنوع بنية Vk_حافظه_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ثابت فراغ*                           p_بعدی;
    Vk_Device_حافظه                        حافظه;
    Vk_External_حافظه_Handle_Type_Flag_بیتها    handleType;
} Vk_حافظه_Get_Metal_Handle_Info_EXT;


تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Metal_Handle_EXT)(VkDevice device, ثابت Vk_حافظه_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, فراغ** pHandle);
تعريفنوع Vk_نتیجه (VKAPI_PTR *PFN_vk_Get_حافظه_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_حافظه_Handle_Type_Flag_بیتها handleType, ثابت فراغ* pHandle, Vk_حافظه_Metal_Handle_Properties_EXT* p_حافظه_Metal_Handle_Properties);

#اگر_تعریف_نشده VK_NO_PROTOTYPES

#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Metal_Handle_EXT(
    VkDevice                                    device,
    ثابت Vk_حافظه_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    فراغ**                                      pHandle);
#پایان_اگر
#اگر_تعریف_نشده VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_نتیجه VKAPI_CALL vk_Get_حافظه_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_حافظه_Handle_Type_Flag_بیتها          handleType,
    ثابت فراغ*                                 pHandle,
    Vk_حافظه_Metal_Handle_Properties_EXT*           p_حافظه_Metal_Handle_Properties);
#پایان_اگر
#پایان_اگر

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر

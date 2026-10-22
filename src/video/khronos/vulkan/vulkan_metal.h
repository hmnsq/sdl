#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VULKAN_METAL_H_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_METAL_H_ 1

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



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_metal_surface 1

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__
@class CAMetalLayer;
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ CAMetalLayer;
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_UNSAFE_UNRETAINED
#ਜੇ defined(__OBJC__) && defined(__has_feature)
#ਜੇ __has_feature(objc_arc)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ SDL_UNSAFE_UNRETAINED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_UNSAFE_UNRETAINED __unsafe_unretained
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_METAL_SURFACE_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkMetalSurfaceCreateFlagsEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ਅਚਲ ਖਾਲੀ*                     p_ਅਗਲਾ;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ਅਚਲ CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ਅਚਲ VkMetalSurfaceCreateInfoEXT* pCreateInfo, ਅਚਲ Vk_ਵੰਡ_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ਅਚਲ VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ਅਚਲ Vk_ਵੰਡ_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_metal_objects 1

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__
@protocol MTLDevice;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __unsafe_unretained id<MTLDevice> MTLDevice_id;
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ* MTLDevice_id;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__
@protocol MTLCommand_ਕਤਾਰ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __unsafe_unretained id<MTLCommand_ਕਤਾਰ> MTLCommand_ਕਤਾਰ_id;
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ* MTLCommand_ਕਤਾਰ_id;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__
@protocol MTLBuffer;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ* MTLBuffer_id;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__
@protocol MTLTexture;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __unsafe_unretained id<MTLTexture> MTLTexture_id;
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ* MTLTexture_id;
#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ __IOSurface* IOSurfaceRef;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __OBJC__
#ਹਦਾਇਤ clang diagnostic ਧੱਕੋ
#ਹਦਾਇਤ clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#ਹਦਾਇਤ clang diagnostic ਕੱਢੋ
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ* MTLSharedEvent_id;
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_METAL_OBJECTS_SPEC_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Vk_Export_Metal_Object_Type_Flag_ਬਿੱਟ_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_ਕਤਾਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_ਦੋਆਧਾਰੀ_ਅੰਕ_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_ਬਿੱਟ_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_ਬਿੱਟ_EXT;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkExportMetalObjectTypeFlagsEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_Export_Metal_Object_Type_Flag_ਬਿੱਟ_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
} VkExportMetalObjectsInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Export_Metal_Command_ਕਤਾਰ_Info_EXT {
    VkStructureType       sType;
    ਅਚਲ ਖਾਲੀ*           p_ਅਗਲਾ;
    Vk_ਕਤਾਰ               ਕਤਾਰ;
    MTLCommand_ਕਤਾਰ_id    mtl_Command_ਕਤਾਰ;
} Vk_Export_Metal_Command_ਕਤਾਰ_Info_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Export_Metal_ਬਫਰ_Info_EXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    Vk_Device_ਸਮ੍ਰਿਤੀ     ਸਮ੍ਰਿਤੀ;
    MTLBuffer_id       mtl_ਬਫਰ;
} Vk_Export_Metal_ਬਫਰ_Info_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_Metal_ਬਫਰ_Info_EXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    MTLBuffer_id       mtl_ਬਫਰ;
} Vk_Import_Metal_ਬਫਰ_Info_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ਅਚਲ ਖਾਲੀ*              p_ਅਗਲਾ;
    VkImage                  image;
    VkImageView              imageView;
    Vk_ਬਫਰ_View             ਬਫਰ_View;
    Vk_Image_Aspect_Flag_ਬਿੱਟ    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ਅਚਲ ਖਾਲੀ*              p_ਅਗਲਾ;
    Vk_Image_Aspect_Flag_ਬਿੱਟ    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ਅਚਲ ਖਾਲੀ*        p_ਅਗਲਾ;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ਅਚਲ ਖਾਲੀ*          p_ਅਗਲਾ;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ਅਚਲ ਖਾਲੀ*          p_ਅਗਲਾ;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ਖਾਲੀ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_external_ਸਮ੍ਰਿਤੀ_metal 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_EXTERNAL_ਸਮ੍ਰਿਤੀ_METAL_SPEC_ਸੰਸਕਰਣ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_EXT_EXTERNAL_ਸਮ੍ਰਿਤੀ_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Import_ਸਮ੍ਰਿਤੀ_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ    handleType;
    ਖਾਲੀ*                                 handle;
} Vk_Import_ਸਮ੍ਰਿਤੀ_Metal_Handle_Info_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    ਖਾਲੀ*              p_ਅਗਲਾ;
    uint32_t           ਸਮ੍ਰਿਤੀ_Type_ਬਿੱਟ;
} Vk_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties_EXT;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_ਸਮ੍ਰਿਤੀ_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ਅਚਲ ਖਾਲੀ*                           p_ਅਗਲਾ;
    Vk_Device_ਸਮ੍ਰਿਤੀ                        ਸਮ੍ਰਿਤੀ;
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ    handleType;
} Vk_ਸਮ੍ਰਿਤੀ_Get_Metal_Handle_Info_EXT;


ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Metal_Handle_EXT)(VkDevice device, ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, ਖਾਲੀ** pHandle);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Get_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ handleType, ਅਚਲ ਖਾਲੀ* pHandle, Vk_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties_EXT* p_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_NO_PROTOTYPES

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Metal_Handle_EXT(
    VkDevice                                    device,
    ਅਚਲ Vk_ਸਮ੍ਰਿਤੀ_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    ਖਾਲੀ**                                      pHandle);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Get_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_ਸਮ੍ਰਿਤੀ_Handle_Type_Flag_ਬਿੱਟ          handleType,
    ਅਚਲ ਖਾਲੀ*                                 pHandle,
    Vk_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties_EXT*           p_ਸਮ੍ਰਿਤੀ_Metal_Handle_Properties);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ

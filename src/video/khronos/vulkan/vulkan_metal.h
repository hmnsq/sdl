#अगर_अघोषित VULKAN_METAL_H_
#घोषणा VULKAN_METAL_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_EXT_metal_surface 1

#अगर_घोषित __OBJC__
@class CAMetalLayer;
#अन्यथा
प्रकार व्योम CAMetalLayer;
#पूर्ण_अगर

#घोषणा SDL_UNSAFE_UNRETAINED
#अगर defined(__OBJC__) && defined(__has_feature)
#अगर __has_feature(objc_arc)
#अघोषित SDL_UNSAFE_UNRETAINED
#घोषणा SDL_UNSAFE_UNRETAINED __unsafe_unretained
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#घोषणा VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

प्रकार VkFlags VkMetalSurfaceCreateFlagsEXT;

प्रकार काष्ठा VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    स्थिर व्योम*                     p_अग्र;
    VkMetalSurfaceCreateFlagsEXT    flags;
    स्थिर CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, स्थिर VkMetalSurfaceCreateInfoEXT* pCreateInfo, स्थिर VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    स्थिर VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    स्थिर VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_EXT_metal_objects 1

#अगर_घोषित __OBJC__
@protocol MTLDevice;
प्रकार __unsafe_unretained id<MTLDevice> MTLDevice_id;
#अन्यथा
प्रकार व्योम* MTLDevice_id;
#पूर्ण_अगर
#अगर_घोषित __OBJC__
@protocol MTLCommandQueue;
प्रकार __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#अन्यथा
प्रकार व्योम* MTLCommandQueue_id;
#पूर्ण_अगर
#अगर_घोषित __OBJC__
@protocol MTLBuffer;
प्रकार __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#अन्यथा
प्रकार व्योम* MTLBuffer_id;
#पूर्ण_अगर
#अगर_घोषित __OBJC__
@protocol MTLTexture;
प्रकार __unsafe_unretained id<MTLTexture> MTLTexture_id;
#अन्यथा
प्रकार व्योम* MTLTexture_id;
#पूर्ण_अगर
प्रकार काष्ठा __IOSurface* IOSurfaceRef;
#अगर_घोषित __OBJC__
#आशय clang diagnostic धकेलो
#आशय clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
प्रकार __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#आशय clang diagnostic निकालो
#अन्यथा
प्रकार व्योम* MTLSharedEvent_id;
#पूर्ण_अगर

#घोषणा VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#घोषणा VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

प्रकार क्रमागत VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_बफर_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
प्रकार VkFlags VkExportMetalObjectTypeFlagsEXT;

प्रकार काष्ठा VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

प्रकार काष्ठा VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
} VkExportMetalObjectsInfoEXT;

प्रकार काष्ठा VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

प्रकार काष्ठा VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    स्थिर व्योम*           p_अग्र;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

प्रकार काष्ठा Vk_Export_Metal_बफर_Info_EXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtl_बफर;
} Vk_Export_Metal_बफर_Info_EXT;

प्रकार काष्ठा Vk_Import_Metal_बफर_Info_EXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    MTLBuffer_id       mtl_बफर;
} Vk_Import_Metal_बफर_Info_EXT;

प्रकार काष्ठा VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    स्थिर व्योम*              p_अग्र;
    VkImage                  image;
    VkImageView              imageView;
    Vk_बफर_View             बफर_View;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

प्रकार काष्ठा VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    स्थिर व्योम*              p_अग्र;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

प्रकार काष्ठा VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

प्रकार काष्ठा VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    स्थिर व्योम*        p_अग्र;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

प्रकार काष्ठा VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    स्थिर व्योम*          p_अग्र;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

प्रकार काष्ठा VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    स्थिर व्योम*          p_अग्र;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


प्रकार व्योम (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR व्योम VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#पूर्ण_अगर
#पूर्ण_अगर


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#घोषणा VK_EXT_external_memory_metal 1

#घोषणा VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#घोषणा VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

प्रकार काष्ठा VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    व्योम*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

प्रकार काष्ठा VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    व्योम*              p_अग्र;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

प्रकार काष्ठा VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    स्थिर व्योम*                           p_अग्र;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, स्थिर VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, व्योम** pHandle);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, स्थिर व्योम* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#अगर_अघोषित VK_NO_PROTOTYPES

#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    स्थिर VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    व्योम**                                      pHandle);
#पूर्ण_अगर
#अगर_अघोषित VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    स्थिर व्योम*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर

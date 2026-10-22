#ifndef VULKAN_METAL_H_
#define VULKAN_METAL_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#ifdef __cplusplus
বাহ্যিক "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#অন্যথা
প্রকারলেখ শূন্য CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#যদি defined(__OBJC__) && defined(__has_feature)
#যদি __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

প্রকারলেখ VkFlags VkMetalSurfaceCreateFlagsEXT;

প্রকারলেখ কাঠামো VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ধ্রুবক শূন্য*                     p_পরবর্তী;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ধ্রুবক CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ধ্রুবক VkMetalSurfaceCreateInfoEXT* pCreateInfo, ধ্রুবক VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ধ্রুবক VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ধ্রুবক VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
প্রকারলেখ __unsafe_unretained id<MTLDevice> MTLDevice_id;
#অন্যথা
প্রকারলেখ শূন্য* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
প্রকারলেখ __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#অন্যথা
প্রকারলেখ শূন্য* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
প্রকারলেখ __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#অন্যথা
প্রকারলেখ শূন্য* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
প্রকারলেখ __unsafe_unretained id<MTLTexture> MTLTexture_id;
#অন্যথা
প্রকারলেখ শূন্য* MTLTexture_id;
#endif
প্রকারলেখ কাঠামো __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic ঠেলো
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
প্রকারলেখ __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic বের_করো
#অন্যথা
প্রকারলেখ শূন্য* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

প্রকারলেখ গণনা VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_বাফার_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
প্রকারলেখ VkFlags VkExportMetalObjectTypeFlagsEXT;

প্রকারলেখ কাঠামো VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

প্রকারলেখ কাঠামো VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
} VkExportMetalObjectsInfoEXT;

প্রকারলেখ কাঠামো VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

প্রকারলেখ কাঠামো VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ধ্রুবক শূন্য*           p_পরবর্তী;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

প্রকারলেখ কাঠামো Vk_Export_Metal_বাফার_Info_EXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtl_বাফার;
} Vk_Export_Metal_বাফার_Info_EXT;

প্রকারলেখ কাঠামো Vk_Import_Metal_বাফার_Info_EXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    MTLBuffer_id       mtl_বাফার;
} Vk_Import_Metal_বাফার_Info_EXT;

প্রকারলেখ কাঠামো VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ধ্রুবক শূন্য*              p_পরবর্তী;
    VkImage                  image;
    VkImageView              imageView;
    Vk_বাফার_View             বাফার_View;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

প্রকারলেখ কাঠামো VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ধ্রুবক শূন্য*              p_পরবর্তী;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

প্রকারলেখ কাঠামো VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

প্রকারলেখ কাঠামো VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ধ্রুবক শূন্য*        p_পরবর্তী;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

প্রকারলেখ কাঠামো VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ধ্রুবক শূন্য*          p_পরবর্তী;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

প্রকারলেখ কাঠামো VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ধ্রুবক শূন্য*          p_পরবর্তী;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR শূন্য VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

প্রকারলেখ কাঠামো VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    শূন্য*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

প্রকারলেখ কাঠামো VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    শূন্য*              p_পরবর্তী;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

প্রকারলেখ কাঠামো VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    ধ্রুবক শূন্য*                           p_পরবর্তী;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, ধ্রুবক VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, শূন্য** pHandle);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, ধ্রুবক শূন্য* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    ধ্রুবক VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    শূন্য**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    ধ্রুবক শূন্য*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

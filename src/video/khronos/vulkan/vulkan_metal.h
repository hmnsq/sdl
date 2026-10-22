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
بیرونی "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#وگرنه
تعریفنوع تهی CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#اگر defined(__OBJC__) && defined(__has_feature)
#اگر __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

تعریفنوع VkFlags VkMetalSurfaceCreateFlagsEXT;

تعریفنوع ساختار VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت تهی*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ثابت VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ثابت VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
تعریفنوع __unsafe_unretained id<MTLDevice> MTLDevice_id;
#وگرنه
تعریفنوع تهی* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
تعریفنوع __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#وگرنه
تعریفنوع تهی* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
تعریفنوع __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#وگرنه
تعریفنوع تهی* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
تعریفنوع __unsafe_unretained id<MTLTexture> MTLTexture_id;
#وگرنه
تعریفنوع تهی* MTLTexture_id;
#endif
تعریفنوع ساختار __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic افزودن
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
تعریفنوع __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic برداشت
#وگرنه
تعریفنوع تهی* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

تعریفنوع شمارش VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
تعریفنوع VkFlags VkExportMetalObjectTypeFlagsEXT;

تعریفنوع ساختار VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت تهی*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

تعریفنوع ساختار VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت تهی*        pNext;
} VkExportMetalObjectsInfoEXT;

تعریفنوع ساختار VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

تعریفنوع ساختار VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ثابت تهی*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

تعریفنوع ساختار VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

تعریفنوع ساختار VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

تعریفنوع ساختار VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت تهی*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

تعریفنوع ساختار VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت تهی*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

تعریفنوع ساختار VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

تعریفنوع ساختار VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت تهی*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

تعریفنوع ساختار VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت تهی*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

تعریفنوع ساختار VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت تهی*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


تعریفنوع تهی (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR تهی VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

تعریفنوع ساختار VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    ثابت تهی*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    تهی*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

تعریفنوع ساختار VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    تهی*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

تعریفنوع ساختار VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    ثابت تهی*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, ثابت VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, تهی** pHandle);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, ثابت تهی* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    ثابت VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    تهی**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    ثابت تهی*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

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
বাহ্য "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#অন্যথা
প্রকারনির্দেশ শূন্য CAMetalLayer;
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

প্রকারনির্দেশ VkFlags VkMetalSurfaceCreateFlagsEXT;

প্রকারনির্দেশ সংরচনা VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ধ্রুব শূন্য*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ধ্রুব CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ধ্রুব VkMetalSurfaceCreateInfoEXT* pCreateInfo, ধ্রুব VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ধ্রুব VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ধ্রুব VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
প্রকারনির্দেশ __unsafe_unretained id<MTLDevice> MTLDevice_id;
#অন্যথা
প্রকারনির্দেশ শূন্য* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
প্রকারনির্দেশ __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#অন্যথা
প্রকারনির্দেশ শূন্য* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
প্রকারনির্দেশ __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#অন্যথা
প্রকারনির্দেশ শূন্য* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
প্রকারনির্দেশ __unsafe_unretained id<MTLTexture> MTLTexture_id;
#অন্যথা
প্রকারনির্দেশ শূন্য* MTLTexture_id;
#endif
প্রকারনির্দেশ সংরচনা __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic ঠেলো
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
প্রকারনির্দেশ __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic বের_করো
#অন্যথা
প্রকারনির্দেশ শূন্য* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

প্রকারনির্দেশ গণনা VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
প্রকারনির্দেশ VkFlags VkExportMetalObjectTypeFlagsEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ধ্রুব শূন্য*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
} VkExportMetalObjectsInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ধ্রুব শূন্য*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

প্রকারনির্দেশ সংরচনা VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ধ্রুব শূন্য*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

প্রকারনির্দেশ সংরচনা VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ধ্রুব শূন্য*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

প্রকারনির্দেশ সংরচনা VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ধ্রুব শূন্য*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

প্রকারনির্দেশ সংরচনা VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ধ্রুব শূন্য*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

প্রকারনির্দেশ সংরচনা VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ধ্রুব শূন্য*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

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

প্রকারনির্দেশ সংরচনা VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    ধ্রুব শূন্য*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    শূন্য*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

প্রকারনির্দেশ সংরচনা VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    শূন্য*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

প্রকারনির্দেশ সংরচনা VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    ধ্রুব শূন্য*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, ধ্রুব VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, শূন্য** pHandle);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, ধ্রুব শূন্য* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    ধ্রুব VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    শূন্য**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    ধ্রুব শূন্য*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

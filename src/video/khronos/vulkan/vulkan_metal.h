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
خارجي "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#وإلا
تعريفنوع فراغ CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#إذا defined(__OBJC__) && defined(__has_feature)
#إذا __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

تعريفنوع VkFlags VkMetalSurfaceCreateFlagsEXT;

تعريفنوع بنية VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ثابت فراغ*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ثابت CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ثابت VkMetalSurfaceCreateInfoEXT* pCreateInfo, ثابت VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

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
تعريفنوع __unsafe_unretained id<MTLDevice> MTLDevice_id;
#وإلا
تعريفنوع فراغ* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
تعريفنوع __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#وإلا
تعريفنوع فراغ* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
تعريفنوع __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#وإلا
تعريفنوع فراغ* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
تعريفنوع __unsafe_unretained id<MTLTexture> MTLTexture_id;
#وإلا
تعريفنوع فراغ* MTLTexture_id;
#endif
تعريفنوع بنية __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic ادفع
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
تعريفنوع __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic اسحب
#وإلا
تعريفنوع فراغ* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

تعريفنوع تعداد VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
تعريفنوع VkFlags VkExportMetalObjectTypeFlagsEXT;

تعريفنوع بنية VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

تعريفنوع بنية VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
} VkExportMetalObjectsInfoEXT;

تعريفنوع بنية VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

تعريفنوع بنية VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ثابت فراغ*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

تعريفنوع بنية VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

تعريفنوع بنية VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

تعريفنوع بنية VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

تعريفنوع بنية VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ثابت فراغ*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

تعريفنوع بنية VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ثابت فراغ*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

تعريفنوع بنية VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

تعريفنوع بنية VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ثابت فراغ*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


تعريفنوع فراغ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR فراغ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

تعريفنوع بنية VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    فراغ*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

تعريفنوع بنية VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    فراغ*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

تعريفنوع بنية VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    ثابت فراغ*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, ثابت VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, فراغ** pHandle);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, ثابت فراغ* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    ثابت VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    فراغ**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    ثابت فراغ*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

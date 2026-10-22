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
ബാഹ്യ "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#അല്ലെങ്കിൽ
തരനിർവചനം ശൂന്യം CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#എങ്കിൽ defined(__OBJC__) && defined(__has_feature)
#എങ്കിൽ __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

തരനിർവചനം VkFlags VkMetalSurfaceCreateFlagsEXT;

തരനിർവചനം ഘടന VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    സ്ഥിരം ശൂന്യം*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    സ്ഥിരം CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, സ്ഥിരം VkMetalSurfaceCreateInfoEXT* pCreateInfo, സ്ഥിരം VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    സ്ഥിരം VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    സ്ഥിരം VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
തരനിർവചനം __unsafe_unretained id<MTLDevice> MTLDevice_id;
#അല്ലെങ്കിൽ
തരനിർവചനം ശൂന്യം* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
തരനിർവചനം __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#അല്ലെങ്കിൽ
തരനിർവചനം ശൂന്യം* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
തരനിർവചനം __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#അല്ലെങ്കിൽ
തരനിർവചനം ശൂന്യം* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
തരനിർവചനം __unsafe_unretained id<MTLTexture> MTLTexture_id;
#അല്ലെങ്കിൽ
തരനിർവചനം ശൂന്യം* MTLTexture_id;
#endif
തരനിർവചനം ഘടന __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic തള്ളുക
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
തരനിർവചനം __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic എടുക്കുക
#അല്ലെങ്കിൽ
തരനിർവചനം ശൂന്യം* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

തരനിർവചനം എണ്ണൽ VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
തരനിർവചനം VkFlags VkExportMetalObjectTypeFlagsEXT;

തരനിർവചനം ഘടന VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    സ്ഥിരം ശൂന്യം*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

തരനിർവചനം ഘടന VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
} VkExportMetalObjectsInfoEXT;

തരനിർവചനം ഘടന VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

തരനിർവചനം ഘടന VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    സ്ഥിരം ശൂന്യം*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

തരനിർവചനം ഘടന VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

തരനിർവചനം ഘടന VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

തരനിർവചനം ഘടന VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    സ്ഥിരം ശൂന്യം*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

തരനിർവചനം ഘടന VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    സ്ഥിരം ശൂന്യം*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

തരനിർവചനം ഘടന VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

തരനിർവചനം ഘടന VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    സ്ഥിരം ശൂന്യം*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

തരനിർവചനം ഘടന VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    സ്ഥിരം ശൂന്യം*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

തരനിർവചനം ഘടന VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    സ്ഥിരം ശൂന്യം*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ശൂന്യം VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

തരനിർവചനം ഘടന VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    സ്ഥിരം ശൂന്യം*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    ശൂന്യം*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

തരനിർവചനം ഘടന VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    ശൂന്യം*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

തരനിർവചനം ഘടന VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    സ്ഥിരം ശൂന്യം*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, സ്ഥിരം VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, ശൂന്യം** pHandle);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, സ്ഥിരം ശൂന്യം* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    സ്ഥിരം VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    ശൂന്യം**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    സ്ഥിരം ശൂന്യം*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

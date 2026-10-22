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
வெளி "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#இல்லையெனில்
வகைவரை வெறுமை CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#எனில் defined(__OBJC__) && defined(__has_feature)
#எனில் __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

வகைவரை VkFlags VkMetalSurfaceCreateFlagsEXT;

வகைவரை கட்டமைப்பு VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    மாறிலி வெறுமை*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    மாறிலி CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


வகைவரை VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, மாறிலி VkMetalSurfaceCreateInfoEXT* pCreateInfo, மாறிலி VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    மாறிலி VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    மாறிலி VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
வகைவரை __unsafe_unretained id<MTLDevice> MTLDevice_id;
#இல்லையெனில்
வகைவரை வெறுமை* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
வகைவரை __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#இல்லையெனில்
வகைவரை வெறுமை* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
வகைவரை __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#இல்லையெனில்
வகைவரை வெறுமை* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
வகைவரை __unsafe_unretained id<MTLTexture> MTLTexture_id;
#இல்லையெனில்
வகைவரை வெறுமை* MTLTexture_id;
#endif
வகைவரை கட்டமைப்பு __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic தள்ளு
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
வகைவரை __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic எடு
#இல்லையெனில்
வகைவரை வெறுமை* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

வகைவரை எண்ணிக்கை VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
வகைவரை VkFlags VkExportMetalObjectTypeFlagsEXT;

வகைவரை கட்டமைப்பு VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    மாறிலி வெறுமை*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
} VkExportMetalObjectsInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    மாறிலி வெறுமை*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

வகைவரை கட்டமைப்பு VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    மாறிலி வெறுமை*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

வகைவரை கட்டமைப்பு VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    மாறிலி வெறுமை*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

வகைவரை கட்டமைப்பு VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    மாறிலி வெறுமை*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

வகைவரை கட்டமைப்பு VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    மாறிலி வெறுமை*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

வகைவரை கட்டமைப்பு VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    மாறிலி வெறுமை*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


வகைவரை வெறுமை (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR வெறுமை VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

வகைவரை கட்டமைப்பு VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    மாறிலி வெறுமை*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    வெறுமை*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

வகைவரை கட்டமைப்பு VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    வெறுமை*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

வகைவரை கட்டமைப்பு VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    மாறிலி வெறுமை*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


வகைவரை VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, மாறிலி VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, வெறுமை** pHandle);
வகைவரை VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, மாறிலி வெறுமை* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    மாறிலி VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    வெறுமை**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    மாறிலி வெறுமை*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

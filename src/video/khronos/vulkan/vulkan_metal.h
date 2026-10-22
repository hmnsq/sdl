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
बाह्य "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#अञ्ञथा
प्रकारनिर्देश शून्य CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#सचे defined(__OBJC__) && defined(__has_feature)
#सचे __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

प्रकारनिर्देश VkFlags VkMetalSurfaceCreateFlagsEXT;

प्रकारनिर्देश संरचना VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ध्रुव शून्य*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ध्रुव CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ध्रुव VkMetalSurfaceCreateInfoEXT* pCreateInfo, ध्रुव VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ध्रुव VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ध्रुव VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
प्रकारनिर्देश __unsafe_unretained id<MTLDevice> MTLDevice_id;
#अञ्ञथा
प्रकारनिर्देश शून्य* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
प्रकारनिर्देश __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#अञ्ञथा
प्रकारनिर्देश शून्य* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
प्रकारनिर्देश __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#अञ्ञथा
प्रकारनिर्देश शून्य* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
प्रकारनिर्देश __unsafe_unretained id<MTLTexture> MTLTexture_id;
#अञ्ञथा
प्रकारनिर्देश शून्य* MTLTexture_id;
#endif
प्रकारनिर्देश संरचना __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic प्रक्षिप
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
प्रकारनिर्देश __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic निष्कासय
#अञ्ञथा
प्रकारनिर्देश शून्य* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

प्रकारनिर्देश गणना VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
प्रकारनिर्देश VkFlags VkExportMetalObjectTypeFlagsEXT;

प्रकारनिर्देश संरचना VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ध्रुव शून्य*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
} VkExportMetalObjectsInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ध्रुव शून्य*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ध्रुव शून्य*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ध्रुव शून्य*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ध्रुव शून्य*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ध्रुव शून्य*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

प्रकारनिर्देश संरचना VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    ध्रुव शून्य*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    शून्य*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

प्रकारनिर्देश संरचना VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    शून्य*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

प्रकारनिर्देश संरचना VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    ध्रुव शून्य*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, ध्रुव VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, शून्य** pHandle);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, ध्रुव शून्य* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    ध्रुव VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    शून्य**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    ध्रुव शून्य*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

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
ବାହ୍ୟ "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#ଯଦି defined(__OBJC__) && defined(__has_feature)
#ଯଦି __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkMetalSurfaceCreateFlagsEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ଅଚଳ ଶୂନ୍ୟ*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ଅଚଳ CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ଅଚଳ VkMetalSurfaceCreateInfoEXT* pCreateInfo, ଅଚଳ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ଅଚଳ VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ଅଚଳ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
ପ୍ରକାରବ୍ୟାଖ୍ୟା __unsafe_unretained id<MTLDevice> MTLDevice_id;
#ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
ପ୍ରକାରବ୍ୟାଖ୍ୟା __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
ପ୍ରକାରବ୍ୟାଖ୍ୟା __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
ପ୍ରକାରବ୍ୟାଖ୍ୟା __unsafe_unretained id<MTLTexture> MTLTexture_id;
#ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ* MTLTexture_id;
#endif
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic ଠେଲ
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
ପ୍ରକାରବ୍ୟାଖ୍ୟା __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic କାଢ଼
#ଅନ୍ୟଥା
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkExportMetalObjectTypeFlagsEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
} VkExportMetalObjectsInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ଅଚଳ ଶୂନ୍ୟ*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ଅଚଳ ଶୂନ୍ୟ*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ଅଚଳ ଶୂନ୍ୟ*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ଅଚଳ ଶୂନ୍ୟ*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ଅଚଳ ଶୂନ୍ୟ*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ଅଚଳ ଶୂନ୍ୟ*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR ଶୂନ୍ୟ VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    ଶୂନ୍ୟ*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    ଶୂନ୍ୟ*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    ଅଚଳ ଶୂନ୍ୟ*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, ଅଚଳ VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, ଶୂନ୍ୟ** pHandle);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, ଅଚଳ ଶୂନ୍ୟ* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    ଅଚଳ VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    ଶୂନ୍ୟ**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    ଅଚଳ ଶୂନ୍ୟ*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

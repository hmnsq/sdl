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
બાહ્ય "C" {
#endif



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_surface 1

#ifdef __OBJC__
@class CAMetalLayer;
#નહીંતર
પ્રકારવ્યાખ્યા શૂન્ય CAMetalLayer;
#endif

#define SDL_UNSAFE_UNRETAINED
#જો defined(__OBJC__) && defined(__has_feature)
#જો __has_feature(objc_arc)
#undef SDL_UNSAFE_UNRETAINED
#define SDL_UNSAFE_UNRETAINED __unsafe_unretained
#endif
#endif

#define VK_EXT_METAL_SURFACE_SPEC_VERSION 1
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

પ્રકારવ્યાખ્યા VkFlags VkMetalSurfaceCreateFlagsEXT;

પ્રકારવ્યાખ્યા સંરચના VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    અચલ શૂન્ય*                     pNext;
    VkMetalSurfaceCreateFlagsEXT    flags;
    અચલ CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, અચલ VkMetalSurfaceCreateInfoEXT* pCreateInfo, અચલ VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    અચલ VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    અચલ VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#endif
#endif


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_metal_objects 1

#ifdef __OBJC__
@protocol MTLDevice;
પ્રકારવ્યાખ્યા __unsafe_unretained id<MTLDevice> MTLDevice_id;
#નહીંતર
પ્રકારવ્યાખ્યા શૂન્ય* MTLDevice_id;
#endif
#ifdef __OBJC__
@protocol MTLCommandQueue;
પ્રકારવ્યાખ્યા __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#નહીંતર
પ્રકારવ્યાખ્યા શૂન્ય* MTLCommandQueue_id;
#endif
#ifdef __OBJC__
@protocol MTLBuffer;
પ્રકારવ્યાખ્યા __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#નહીંતર
પ્રકારવ્યાખ્યા શૂન્ય* MTLBuffer_id;
#endif
#ifdef __OBJC__
@protocol MTLTexture;
પ્રકારવ્યાખ્યા __unsafe_unretained id<MTLTexture> MTLTexture_id;
#નહીંતર
પ્રકારવ્યાખ્યા શૂન્ય* MTLTexture_id;
#endif
પ્રકારવ્યાખ્યા સંરચના __IOSurface* IOSurfaceRef;
#ifdef __OBJC__
#pragma clang diagnostic ધકેલો
#pragma clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
પ્રકારવ્યાખ્યા __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#pragma clang diagnostic કાઢો
#નહીંતર
પ્રકારવ્યાખ્યા શૂન્ય* MTLSharedEvent_id;
#endif

#define VK_EXT_METAL_OBJECTS_SPEC_VERSION 2
#define VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

પ્રકારવ્યાખ્યા ગણના VkExportMetalObjectTypeFlagBitsEXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_BUFFER_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkExportMetalObjectTypeFlagBitsEXT;
પ્રકારવ્યાખ્યા VkFlags VkExportMetalObjectTypeFlagsEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkExportMetalObjectTypeFlagBitsEXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
} VkExportMetalObjectsInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    અચલ શૂન્ય*           pNext;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalBufferInfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    VkDeviceMemory     memory;
    MTLBuffer_id       mtlBuffer;
} VkExportMetalBufferInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkImportMetalBufferInfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    MTLBuffer_id       mtlBuffer;
} VkImportMetalBufferInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    અચલ શૂન્ય*              pNext;
    VkImage                  image;
    VkImageView              imageView;
    VkBufferView             bufferView;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    અચલ શૂન્ય*              pNext;
    VkImageAspectFlagBits    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    અચલ શૂન્ય*        pNext;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    અચલ શૂન્ય*          pNext;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    અચલ શૂન્ય*          pNext;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR શૂન્ય VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#endif
#endif


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#define VK_EXT_external_memory_metal 1

#define VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION 1
#define VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

પ્રકારવ્યાખ્યા સંરચના VkImportMemoryMetalHandleInfoEXT {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkExternalMemoryHandleTypeFlagBits    handleType;
    શૂન્ય*                                 handle;
} VkImportMemoryMetalHandleInfoEXT;

પ્રકારવ્યાખ્યા સંરચના VkMemoryMetalHandlePropertiesEXT {
    VkStructureType    sType;
    શૂન્ય*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryMetalHandlePropertiesEXT;

પ્રકારવ્યાખ્યા સંરચના VkMemoryGetMetalHandleInfoEXT {
    VkStructureType                       sType;
    અચલ શૂન્ય*                           pNext;
    VkDeviceMemory                        memory;
    VkExternalMemoryHandleTypeFlagBits    handleType;
} VkMemoryGetMetalHandleInfoEXT;


પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandleEXT)(VkDevice device, અચલ VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, શૂન્ય** pHandle);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkGetMemoryMetalHandlePropertiesEXT)(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, અચલ શૂન્ય* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties);

#ifndef VK_NO_PROTOTYPES

#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandleEXT(
    VkDevice                                    device,
    અચલ VkMemoryGetMetalHandleInfoEXT*        pGetMetalHandleInfo,
    શૂન્ય**                                      pHandle);
#endif
#ifndef VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryMetalHandlePropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    અચલ શૂન્ય*                                 pHandle,
    VkMemoryMetalHandlePropertiesEXT*           pMemoryMetalHandleProperties);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

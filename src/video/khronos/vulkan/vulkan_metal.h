#यदि_अपरिभाषितम् VULKAN_METAL_H_
#परिभाषय VULKAN_METAL_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_EXT_metal_surface 1

#यदि_परिभाषितम् __OBJC__
@class CAMetalLayer;
#अन्यथा
प्रकारनिर्देश शून्य CAMetalLayer;
#यदि_अन्तः

#परिभाषय SDL_UNSAFE_UNRETAINED
#यदि defined(__OBJC__) && defined(__has_feature)
#यदि __has_feature(objc_arc)
#अपरिभाषय SDL_UNSAFE_UNRETAINED
#परिभाषय SDL_UNSAFE_UNRETAINED __unsafe_unretained
#यदि_अन्तः
#यदि_अन्तः

#परिभाषय VK_EXT_METAL_SURFACE_SPEC_संस्करणम् 1
#परिभाषय VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

प्रकारनिर्देश VkFlags VkMetalSurfaceCreateFlagsEXT;

प्रकारनिर्देश संरचना VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    ध्रुव शून्य*                     p_अग्र;
    VkMetalSurfaceCreateFlagsEXT    flags;
    ध्रुव CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, ध्रुव VkMetalSurfaceCreateInfoEXT* pCreateInfo, ध्रुव Vk_आवण्टनम्_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    ध्रुव VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    ध्रुव Vk_आवण्टनम्_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#यदि_अन्तः
#यदि_अन्तः


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_EXT_metal_objects 1

#यदि_परिभाषितम् __OBJC__
@protocol MTLDevice;
प्रकारनिर्देश __unsafe_unretained id<MTLDevice> MTLDevice_id;
#अन्यथा
प्रकारनिर्देश शून्य* MTLDevice_id;
#यदि_अन्तः
#यदि_परिभाषितम् __OBJC__
@protocol MTLCommandQueue;
प्रकारनिर्देश __unsafe_unretained id<MTLCommandQueue> MTLCommandQueue_id;
#अन्यथा
प्रकारनिर्देश शून्य* MTLCommandQueue_id;
#यदि_अन्तः
#यदि_परिभाषितम् __OBJC__
@protocol MTLBuffer;
प्रकारनिर्देश __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#अन्यथा
प्रकारनिर्देश शून्य* MTLBuffer_id;
#यदि_अन्तः
#यदि_परिभाषितम् __OBJC__
@protocol MTLTexture;
प्रकारनिर्देश __unsafe_unretained id<MTLTexture> MTLTexture_id;
#अन्यथा
प्रकारनिर्देश शून्य* MTLTexture_id;
#यदि_अन्तः
प्रकारनिर्देश संरचना __IOSurface* IOSurfaceRef;
#यदि_परिभाषितम् __OBJC__
#निर्देशः clang diagnostic प्रक्षिप
#निर्देशः clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
प्रकारनिर्देश __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#निर्देशः clang diagnostic निष्कासय
#अन्यथा
प्रकारनिर्देश शून्य* MTLSharedEvent_id;
#यदि_अन्तः

#परिभाषय VK_EXT_METAL_OBJECTS_SPEC_संस्करणम् 2
#परिभाषय VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

प्रकारनिर्देश गणना Vk_Export_Metal_Object_Type_Flag_द्वयङ्काः_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_BIT_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_QUEUE_BIT_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_बफर_BIT_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_BIT_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_BIT_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_BIT_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_द्वयङ्काः_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_द्वयङ्काः_EXT;
प्रकारनिर्देश VkFlags VkExportMetalObjectTypeFlagsEXT;

प्रकारनिर्देश संरचना VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_Export_Metal_Object_Type_Flag_द्वयङ्काः_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
} VkExportMetalObjectsInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalCommandQueueInfoEXT {
    VkStructureType       sType;
    ध्रुव शून्य*           p_अग्र;
    VkQueue               queue;
    MTLCommandQueue_id    mtlCommandQueue;
} VkExportMetalCommandQueueInfoEXT;

प्रकारनिर्देश संरचना Vk_Export_Metal_बफर_Info_EXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    Vk_Device_स्मृतिः     स्मृतिः;
    MTLBuffer_id       mtl_बफर;
} Vk_Export_Metal_बफर_Info_EXT;

प्रकारनिर्देश संरचना Vk_Import_Metal_बफर_Info_EXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    MTLBuffer_id       mtl_बफर;
} Vk_Import_Metal_बफर_Info_EXT;

प्रकारनिर्देश संरचना VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    ध्रुव शून्य*              p_अग्र;
    VkImage                  image;
    VkImageView              imageView;
    Vk_बफर_View             बफर_View;
    Vk_Image_Aspect_Flag_द्वयङ्काः    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    ध्रुव शून्य*              p_अग्र;
    Vk_Image_Aspect_Flag_द्वयङ्काः    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    ध्रुव शून्य*        p_अग्र;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

प्रकारनिर्देश संरचना VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ध्रुव शून्य*          p_अग्र;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

प्रकारनिर्देश संरचना VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    ध्रुव शून्य*          p_अग्र;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR शून्य VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#यदि_अन्तः
#यदि_अन्तः


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#परिभाषय VK_EXT_external_स्मृतिः_metal 1

#परिभाषय VK_EXT_EXTERNAL_स्मृतिः_METAL_SPEC_संस्करणम् 1
#परिभाषय VK_EXT_EXTERNAL_स्मृतिः_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

प्रकारनिर्देश संरचना Vk_Import_स्मृतिः_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः    handleType;
    शून्य*                                 handle;
} Vk_Import_स्मृतिः_Metal_Handle_Info_EXT;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    शून्य*              p_अग्र;
    uint32_t           स्मृतिः_Type_द्वयङ्काः;
} Vk_स्मृतिः_Metal_Handle_Properties_EXT;

प्रकारनिर्देश संरचना Vk_स्मृतिः_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    ध्रुव शून्य*                           p_अग्र;
    Vk_Device_स्मृतिः                        स्मृतिः;
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः    handleType;
} Vk_स्मृतिः_Get_Metal_Handle_Info_EXT;


प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Metal_Handle_EXT)(VkDevice device, ध्रुव Vk_स्मृतिः_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, शून्य** pHandle);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Get_स्मृतिः_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः handleType, ध्रुव शून्य* pHandle, Vk_स्मृतिः_Metal_Handle_Properties_EXT* p_स्मृतिः_Metal_Handle_Properties);

#यदि_अपरिभाषितम् VK_NO_PROTOTYPES

#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Metal_Handle_EXT(
    VkDevice                                    device,
    ध्रुव Vk_स्मृतिः_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    शून्य**                                      pHandle);
#यदि_अन्तः
#यदि_अपरिभाषितम् VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Get_स्मृतिः_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_स्मृतिः_Handle_Type_Flag_द्वयङ्काः          handleType,
    ध्रुव शून्य*                                 pHandle,
    Vk_स्मृतिः_Metal_Handle_Properties_EXT*           p_स्मृतिः_Metal_Handle_Properties);
#यदि_अन्तः
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः

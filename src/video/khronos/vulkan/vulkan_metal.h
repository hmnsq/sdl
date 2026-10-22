#నిర్వచితం_కాకపోతే VULKAN_METAL_H_
#నిర్వచించు VULKAN_METAL_H_ 1

/*
** Copyright 2015-2026 The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/


#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు



// VK_EXT_metal_surface is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_EXT_metal_surface 1

#నిర్వచితమైతే __OBJC__
@class CAMetalLayer;
#లేకపోతే
రకనిర్వచనం శూన్య CAMetalLayer;
#అయితే_ముగింపు

#నిర్వచించు SDL_UNSAFE_UNRETAINED
#ఒకవేళ defined(__OBJC__) && defined(__has_feature)
#ఒకవేళ __has_feature(objc_arc)
#నిర్వచనం_రద్దు SDL_UNSAFE_UNRETAINED
#నిర్వచించు SDL_UNSAFE_UNRETAINED __unsafe_unretained
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచించు VK_EXT_METAL_SURFACE_SPEC_సంస్కరణ 1
#నిర్వచించు VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

రకనిర్వచనం VkFlags VkMetalSurfaceCreateFlagsEXT;

రకనిర్వచనం నిర్మాణం VkMetalSurfaceCreateInfoEXT {
    VkStructureType                 sType;
    స్థిరరాశి శూన్య*                     p_తదుపరి;
    VkMetalSurfaceCreateFlagsEXT    flags;
    స్థిరరాశి CAMetalLayer SDL_UNSAFE_UNRETAINED *pLayer;
} VkMetalSurfaceCreateInfoEXT;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkCreateMetalSurfaceEXT)(VkInstance instance, స్థిరరాశి VkMetalSurfaceCreateInfoEXT* pCreateInfo, స్థిరరాశి Vk_కేటాయింపు_Callbacks* pAllocator, VkSurfaceKHR* pSurface);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vkCreateMetalSurfaceEXT(
    VkInstance                                  instance,
    స్థిరరాశి VkMetalSurfaceCreateInfoEXT*          pCreateInfo,
    స్థిరరాశి Vk_కేటాయింపు_Callbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_EXT_metal_objects is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_EXT_metal_objects 1

#నిర్వచితమైతే __OBJC__
@protocol MTLDevice;
రకనిర్వచనం __unsafe_unretained id<MTLDevice> MTLDevice_id;
#లేకపోతే
రకనిర్వచనం శూన్య* MTLDevice_id;
#అయితే_ముగింపు
#నిర్వచితమైతే __OBJC__
@protocol MTLCommand_వరుస;
రకనిర్వచనం __unsafe_unretained id<MTLCommand_వరుస> MTLCommand_వరుస_id;
#లేకపోతే
రకనిర్వచనం శూన్య* MTLCommand_వరుస_id;
#అయితే_ముగింపు
#నిర్వచితమైతే __OBJC__
@protocol MTLBuffer;
రకనిర్వచనం __unsafe_unretained id<MTLBuffer> MTLBuffer_id;
#లేకపోతే
రకనిర్వచనం శూన్య* MTLBuffer_id;
#అయితే_ముగింపు
#నిర్వచితమైతే __OBJC__
@protocol MTLTexture;
రకనిర్వచనం __unsafe_unretained id<MTLTexture> MTLTexture_id;
#లేకపోతే
రకనిర్వచనం శూన్య* MTLTexture_id;
#అయితే_ముగింపు
రకనిర్వచనం నిర్మాణం __IOSurface* IOSurfaceRef;
#నిర్వచితమైతే __OBJC__
#సూచన clang diagnostic నెట్టు
#సూచన clang diagnostic ignored "-Wunguarded-availability"
@protocol MTLSharedEvent;
రకనిర్వచనం __unsafe_unretained id<MTLSharedEvent> MTLSharedEvent_id;
#సూచన clang diagnostic తీయి
#లేకపోతే
రకనిర్వచనం శూన్య* MTLSharedEvent_id;
#అయితే_ముగింపు

#నిర్వచించు VK_EXT_METAL_OBJECTS_SPEC_సంస్కరణ 2
#నిర్వచించు VK_EXT_METAL_OBJECTS_EXTENSION_NAME "VK_EXT_metal_objects"

రకనిర్వచనం గణన Vk_Export_Metal_Object_Type_Flag_బిట్లు_EXT {
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_DEVICE_బిట్టు_EXT = 0x00000001,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_COMMAND_వరుస_బిట్టు_EXT = 0x00000002,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_బఫరు_బిట్టు_EXT = 0x00000004,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_TEXTURE_బిట్టు_EXT = 0x00000008,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_IOSURFACE_బిట్టు_EXT = 0x00000010,
    VK_EXPORT_METAL_OBJECT_TYPE_METAL_SHARED_EVENT_బిట్టు_EXT = 0x00000020,
    VK_EXPORT_METAL_OBJECT_TYPE_FLAG_బిట్లు_MAX_ENUM_EXT = 0x7FFFFFFF
} Vk_Export_Metal_Object_Type_Flag_బిట్లు_EXT;
రకనిర్వచనం VkFlags VkExportMetalObjectTypeFlagsEXT;

రకనిర్వచనం నిర్మాణం VkExportMetalObjectCreateInfoEXT {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_Export_Metal_Object_Type_Flag_బిట్లు_EXT    exportObjectType;
} VkExportMetalObjectCreateInfoEXT;

రకనిర్వచనం నిర్మాణం VkExportMetalObjectsInfoEXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
} VkExportMetalObjectsInfoEXT;

రకనిర్వచనం నిర్మాణం VkExportMetalDeviceInfoEXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    MTLDevice_id       mtlDevice;
} VkExportMetalDeviceInfoEXT;

రకనిర్వచనం నిర్మాణం Vk_Export_Metal_Command_వరుస_Info_EXT {
    VkStructureType       sType;
    స్థిరరాశి శూన్య*           p_తదుపరి;
    Vk_వరుస               వరుస;
    MTLCommand_వరుస_id    mtl_Command_వరుస;
} Vk_Export_Metal_Command_వరుస_Info_EXT;

రకనిర్వచనం నిర్మాణం Vk_Export_Metal_బఫరు_Info_EXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    Vk_Device_జ్ఞాపకం     జ్ఞాపకం;
    MTLBuffer_id       mtl_బఫరు;
} Vk_Export_Metal_బఫరు_Info_EXT;

రకనిర్వచనం నిర్మాణం Vk_Import_Metal_బఫరు_Info_EXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    MTLBuffer_id       mtl_బఫరు;
} Vk_Import_Metal_బఫరు_Info_EXT;

రకనిర్వచనం నిర్మాణం VkExportMetalTextureInfoEXT {
    VkStructureType          sType;
    స్థిరరాశి శూన్య*              p_తదుపరి;
    VkImage                  image;
    VkImageView              imageView;
    Vk_బఫరు_View             బఫరు_View;
    Vk_Image_Aspect_Flag_బిట్లు    plane;
    MTLTexture_id            mtlTexture;
} VkExportMetalTextureInfoEXT;

రకనిర్వచనం నిర్మాణం VkImportMetalTextureInfoEXT {
    VkStructureType          sType;
    స్థిరరాశి శూన్య*              p_తదుపరి;
    Vk_Image_Aspect_Flag_బిట్లు    plane;
    MTLTexture_id            mtlTexture;
} VkImportMetalTextureInfoEXT;

రకనిర్వచనం నిర్మాణం VkExportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    VkImage            image;
    IOSurfaceRef       ioSurface;
} VkExportMetalIOSurfaceInfoEXT;

రకనిర్వచనం నిర్మాణం VkImportMetalIOSurfaceInfoEXT {
    VkStructureType    sType;
    స్థిరరాశి శూన్య*        p_తదుపరి;
    IOSurfaceRef       ioSurface;
} VkImportMetalIOSurfaceInfoEXT;

రకనిర్వచనం నిర్మాణం VkExportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    స్థిరరాశి శూన్య*          p_తదుపరి;
    VkSemaphore          semaphore;
    VkEvent              event;
    MTLSharedEvent_id    mtlSharedEvent;
} VkExportMetalSharedEventInfoEXT;

రకనిర్వచనం నిర్మాణం VkImportMetalSharedEventInfoEXT {
    VkStructureType      sType;
    స్థిరరాశి శూన్య*          p_తదుపరి;
    MTLSharedEvent_id    mtlSharedEvent;
} VkImportMetalSharedEventInfoEXT;


రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vkExportMetalObjectsEXT)(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR శూన్య VKAPI_CALL vkExportMetalObjectsEXT(
    VkDevice                                    device,
    VkExportMetalObjectsInfoEXT*                pMetalObjectsInfo);
#అయితే_ముగింపు
#అయితే_ముగింపు


// VK_EXT_external_memory_metal is a preprocessor guard. Do not pass it to API calls.
#నిర్వచించు VK_EXT_external_జ్ఞాపకం_metal 1

#నిర్వచించు VK_EXT_EXTERNAL_జ్ఞాపకం_METAL_SPEC_సంస్కరణ 1
#నిర్వచించు VK_EXT_EXTERNAL_జ్ఞాపకం_METAL_EXTENSION_NAME "VK_EXT_external_memory_metal"

రకనిర్వచనం నిర్మాణం Vk_Import_జ్ఞాపకం_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు    handleType;
    శూన్య*                                 handle;
} Vk_Import_జ్ఞాపకం_Metal_Handle_Info_EXT;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Metal_Handle_Properties_EXT {
    VkStructureType    sType;
    శూన్య*              p_తదుపరి;
    uint32_t           జ్ఞాపకం_Type_బిట్లు;
} Vk_జ్ఞాపకం_Metal_Handle_Properties_EXT;

రకనిర్వచనం నిర్మాణం Vk_జ్ఞాపకం_Get_Metal_Handle_Info_EXT {
    VkStructureType                       sType;
    స్థిరరాశి శూన్య*                           p_తదుపరి;
    Vk_Device_జ్ఞాపకం                        జ్ఞాపకం;
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు    handleType;
} Vk_జ్ఞాపకం_Get_Metal_Handle_Info_EXT;


రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Metal_Handle_EXT)(VkDevice device, స్థిరరాశి Vk_జ్ఞాపకం_Get_Metal_Handle_Info_EXT* pGetMetalHandleInfo, శూన్య** pHandle);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Get_జ్ఞాపకం_Metal_Handle_Properties_EXT)(VkDevice device, Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు handleType, స్థిరరాశి శూన్య* pHandle, Vk_జ్ఞాపకం_Metal_Handle_Properties_EXT* p_జ్ఞాపకం_Metal_Handle_Properties);

#నిర్వచితం_కాకపోతే VK_NO_PROTOTYPES

#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Metal_Handle_EXT(
    VkDevice                                    device,
    స్థిరరాశి Vk_జ్ఞాపకం_Get_Metal_Handle_Info_EXT*        pGetMetalHandleInfo,
    శూన్య**                                      pHandle);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే VK_ONLY_EXPORTED_PROTOTYPES
VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Get_జ్ఞాపకం_Metal_Handle_Properties_EXT(
    VkDevice                                    device,
    Vk_External_జ్ఞాపకం_Handle_Type_Flag_బిట్లు          handleType,
    స్థిరరాశి శూన్య*                                 pHandle,
    Vk_జ్ఞాపకం_Metal_Handle_Properties_EXT*           p_జ్ఞాపకం_Metal_Handle_Properties);
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు

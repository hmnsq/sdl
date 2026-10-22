/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#pragma once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#অন্তর্ভাব "vulkan_core.h"

#define MAX_অঙ্ক_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#define CURRENT_LOADER_LAYER_INTERFACE_VERSION 2
#define MIN_SUPPORTED_LOADER_LAYER_INTERFACE_VERSION 1

#define VK_CURRENT_CHAIN_VERSION 1

// Typedef for use in the interfaces below
#ifndef IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
প্রকারলেখ PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ধ্রুবক অক্ষর* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
প্রকারলেখ গণনা VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
প্রকারলেখ কাঠামো VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    শূন্য *p_পরবর্তী;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
প্রকারলেখ Vk_ফলাফল(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
প্রকারলেখ গণনা VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_তথ্য_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

প্রকারলেখ কাঠামো VkLayerInstanceLink_ {
    কাঠামো VkLayerInstanceLink_ *p_পরবর্তী;
    PFN_vkGetInstanceProcAddr pfn_পরবর্তী_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_পরবর্তী_Get_Physical_Device_Proc_Addr;
} VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */
প্রকারলেখ কাঠামো VkLayerDeviceInfo_ {
    শূন্য *device_info;
    PFN_vkGetInstanceProcAddr pfn_পরবর্তী_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Set_Instance_Loader_তথ্য)(VkInstance instance,
        শূন্য *object);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vk_Set_Device_Loader_তথ্য)(VkDevice device,
        শূন্য *object);
প্রকারলেখ Vk_ফলাফল (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ধ্রুবক VkDeviceCreateInfo *pCreateInfo,
						      ধ্রুবক VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *পরবর্তী_GDPA);
প্রকারলেখ শূন্য (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ধ্রুবক VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

প্রকারলেখ গণনা VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
প্রকারলেখ VkFlags VkLoaderFeatureFlags;

প্রকারলেখ কাঠামো {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ধ্রুবক শূন্য *p_পরবর্তী;
    VkLayerFunction function;
    সংঘ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_Set_Instance_Loader_তথ্য pfn_Set_Instance_Loader_তথ্য;
        কাঠামো {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

প্রকারলেখ কাঠামো VkLayerDeviceLink_ {
    কাঠামো VkLayerDeviceLink_ *p_পরবর্তী;
    PFN_vkGetInstanceProcAddr pfn_পরবর্তী_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_পরবর্তী_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

প্রকারলেখ কাঠামো {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ধ্রুবক শূন্য *p_পরবর্তী;
    VkLayerFunction function;
    সংঘ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_Set_Device_Loader_তথ্য pfn_Set_Device_Loader_তথ্য;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
বাহ্যিক "C" {
#endif

VKAPI_ATTR Vk_ফলাফল VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

প্রকারলেখ গণনা VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

প্রকারলেখ কাঠামো VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t আকার_2;
} VkChainHeader;

প্রকারলেখ কাঠামো VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    Vk_ফলাফল(VKAPI_PTR *pfn_পরবর্তী_Layer)(ধ্রুবক কাঠামো VkEnumerateInstanceExtensionPropertiesChain *, ধ্রুবক অক্ষর *, uint32_t *,
                                      VkExtensionProperties *);
    ধ্রুবক কাঠামো VkEnumerateInstanceExtensionPropertiesChain *p_পরবর্তী_Link;

#যদি defined(__cplusplus)
    অন্তঃরেখ Vk_ফলাফল CallDown(ধ্রুবক অক্ষর *pLayerName, uint32_t *p_Property_গুনতি, VkExtensionProperties *pProperties) ধ্রুবক {
        ফেরত pfn_পরবর্তী_Layer(p_পরবর্তী_Link, pLayerName, p_Property_গুনতি, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

প্রকারলেখ কাঠামো VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    Vk_ফলাফল(VKAPI_PTR *pfn_পরবর্তী_Layer)(ধ্রুবক কাঠামো VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ধ্রুবক কাঠামো VkEnumerateInstanceLayerPropertiesChain *p_পরবর্তী_Link;

#যদি defined(__cplusplus)
    অন্তঃরেখ Vk_ফলাফল CallDown(uint32_t *p_Property_গুনতি, VkLayerProperties *pProperties) ধ্রুবক {
        ফেরত pfn_পরবর্তী_Layer(p_পরবর্তী_Link, p_Property_গুনতি, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

প্রকারলেখ কাঠামো VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    Vk_ফলাফল(VKAPI_PTR *pfn_পরবর্তী_Layer)(ধ্রুবক কাঠামো VkEnumerateInstanceVersionChain *, uint32_t *);
    ধ্রুবক কাঠামো VkEnumerateInstanceVersionChain *p_পরবর্তী_Link;

#যদি defined(__cplusplus)
    অন্তঃরেখ Vk_ফলাফল CallDown(uint32_t *pApiVersion) ধ্রুবক {
        ফেরত pfn_পরবর্তী_Layer(p_পরবর্তী_Link, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

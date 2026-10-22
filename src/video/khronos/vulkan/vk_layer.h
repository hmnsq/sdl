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

#شامل "vulkan_core.h"

#define MAX_رقم_UNKNOWN_EXTS 250

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
تعریفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت نویسه* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
تعریفنوع شمارش VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
تعریفنوع ساختار VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    تهی *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
تعریفنوع VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
تعریفنوع VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
تعریفنوع شمارش VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

تعریفنوع ساختار VkLayerInstanceLink_ {
    ساختار VkLayerInstanceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnNextGetPhysicalDeviceProcAddr;
} VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */
تعریفنوع ساختار VkLayerDeviceInfo_ {
    تهی *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

تعریفنوع VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        تهی *object);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        تهی *object);
تعریفنوع VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ثابت VkDeviceCreateInfo *pCreateInfo,
						      ثابت VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
تعریفنوع تهی (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ثابت VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

تعریفنوع شمارش VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
تعریفنوع VkFlags VkLoaderFeatureFlags;

تعریفنوع ساختار {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ثابت تهی *pNext;
    VkLayerFunction function;
    اجتماع {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        ساختار {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

تعریفنوع ساختار VkLayerDeviceLink_ {
    ساختار VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

تعریفنوع ساختار {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ثابت تهی *pNext;
    VkLayerFunction function;
    اجتماع {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
بیرونی "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

تعریفنوع شمارش VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

تعریفنوع ساختار VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

تعریفنوع ساختار VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ثابت ساختار VkEnumerateInstanceExtensionPropertiesChain *, ثابت نویسه *, uint32_t *,
                                      VkExtensionProperties *);
    ثابت ساختار VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#اگر defined(__cplusplus)
    درونخطی VkResult CallDown(ثابت نویسه *pLayerName, uint32_t *p_Property_شمار, VkExtensionProperties *pProperties) ثابت {
        بازگشت pfnNextLayer(pNextLink, pLayerName, p_Property_شمار, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

تعریفنوع ساختار VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ثابت ساختار VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ثابت ساختار VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#اگر defined(__cplusplus)
    درونخطی VkResult CallDown(uint32_t *p_Property_شمار, VkLayerProperties *pProperties) ثابت {
        بازگشت pfnNextLayer(pNextLink, p_Property_شمار, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

تعریفنوع ساختار VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ثابت ساختار VkEnumerateInstanceVersionChain *, uint32_t *);
    ثابت ساختار VkEnumerateInstanceVersionChain *pNextLink;

#اگر defined(__cplusplus)
    درونخطی VkResult CallDown(uint32_t *pApiVersion) ثابت {
        بازگشت pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

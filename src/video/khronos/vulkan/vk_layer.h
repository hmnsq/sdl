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
প্রকারনির্দেশ PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ধ্রুব বর্ণ* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
প্রকারনির্দেশ গণনা VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
প্রকারনির্দেশ সংরচনা VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    শূন্য *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
প্রকারনির্দেশ VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
প্রকারনির্দেশ গণনা VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

প্রকারনির্দেশ সংরচনা VkLayerInstanceLink_ {
    সংরচনা VkLayerInstanceLink_ *pNext;
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
প্রকারনির্দেশ সংরচনা VkLayerDeviceInfo_ {
    শূন্য *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        শূন্য *object);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        শূন্য *object);
প্রকারনির্দেশ VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ধ্রুব VkDeviceCreateInfo *pCreateInfo,
						      ধ্রুব VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
প্রকারনির্দেশ শূন্য (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ধ্রুব VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

প্রকারনির্দেশ গণনা VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
প্রকারনির্দেশ VkFlags VkLoaderFeatureFlags;

প্রকারনির্দেশ সংরচনা {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ধ্রুব শূন্য *pNext;
    VkLayerFunction function;
    সঙ্ঘ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        সংরচনা {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

প্রকারনির্দেশ সংরচনা VkLayerDeviceLink_ {
    সংরচনা VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

প্রকারনির্দেশ সংরচনা {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ধ্রুব শূন্য *pNext;
    VkLayerFunction function;
    সঙ্ঘ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
বাহ্য "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

প্রকারনির্দেশ গণনা VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

প্রকারনির্দেশ সংরচনা VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

প্রকারনির্দেশ সংরচনা VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ধ্রুব সংরচনা VkEnumerateInstanceExtensionPropertiesChain *, ধ্রুব বর্ণ *, uint32_t *,
                                      VkExtensionProperties *);
    ধ্রুব সংরচনা VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#যদি defined(__cplusplus)
    অন্তঃস্থ VkResult CallDown(ধ্রুব বর্ণ *pLayerName, uint32_t *p_Property_গুনতি, VkExtensionProperties *pProperties) ধ্রুব {
        প্রত্যাগম pfnNextLayer(pNextLink, pLayerName, p_Property_গুনতি, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

প্রকারনির্দেশ সংরচনা VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ধ্রুব সংরচনা VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ধ্রুব সংরচনা VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#যদি defined(__cplusplus)
    অন্তঃস্থ VkResult CallDown(uint32_t *p_Property_গুনতি, VkLayerProperties *pProperties) ধ্রুব {
        প্রত্যাগম pfnNextLayer(pNextLink, p_Property_গুনতি, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

প্রকারনির্দেশ সংরচনা VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ধ্রুব সংরচনা VkEnumerateInstanceVersionChain *, uint32_t *);
    ধ্রুব সংরচনা VkEnumerateInstanceVersionChain *pNextLink;

#যদি defined(__cplusplus)
    অন্তঃস্থ VkResult CallDown(uint32_t *pApiVersion) ধ্রুব {
        প্রত্যাগম pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

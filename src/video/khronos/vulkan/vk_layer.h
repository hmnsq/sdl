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

#അന്തര്ഭാവ "vulkan_core.h"

#define MAX_അക്കം_UNKNOWN_EXTS 250

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
തരനിർവചനം PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, സ്ഥിരം അക്ഷരം* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
തരനിർവചനം എണ്ണൽ VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
തരനിർവചനം ഘടന VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    ശൂന്യം *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
തരനിർവചനം VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
തരനിർവചനം എണ്ണൽ VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

തരനിർവചനം ഘടന VkLayerInstanceLink_ {
    ഘടന VkLayerInstanceLink_ *pNext;
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
തരനിർവചനം ഘടന VkLayerDeviceInfo_ {
    ശൂന്യം *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        ശൂന്യം *object);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        ശൂന്യം *object);
തരനിർവചനം VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, സ്ഥിരം VkDeviceCreateInfo *pCreateInfo,
						      സ്ഥിരം VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
തരനിർവചനം ശൂന്യം (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, സ്ഥിരം VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

തരനിർവചനം എണ്ണൽ VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
തരനിർവചനം VkFlags VkLoaderFeatureFlags;

തരനിർവചനം ഘടന {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    സ്ഥിരം ശൂന്യം *pNext;
    VkLayerFunction function;
    സംഘം {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        ഘടന {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

തരനിർവചനം ഘടന VkLayerDeviceLink_ {
    ഘടന VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

തരനിർവചനം ഘടന {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    സ്ഥിരം ശൂന്യം *pNext;
    VkLayerFunction function;
    സംഘം {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

തരനിർവചനം എണ്ണൽ VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

തരനിർവചനം ഘടന VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

തരനിർവചനം ഘടന VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(സ്ഥിരം ഘടന VkEnumerateInstanceExtensionPropertiesChain *, സ്ഥിരം അക്ഷരം *, uint32_t *,
                                      VkExtensionProperties *);
    സ്ഥിരം ഘടന VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#എങ്കിൽ defined(__cplusplus)
    വരിയിൽ VkResult CallDown(സ്ഥിരം അക്ഷരം *pLayerName, uint32_t *p_Property_എണ്ണം, VkExtensionProperties *pProperties) സ്ഥിരം {
        തിരികെ pfnNextLayer(pNextLink, pLayerName, p_Property_എണ്ണം, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

തരനിർവചനം ഘടന VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(സ്ഥിരം ഘടന VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    സ്ഥിരം ഘടന VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#എങ്കിൽ defined(__cplusplus)
    വരിയിൽ VkResult CallDown(uint32_t *p_Property_എണ്ണം, VkLayerProperties *pProperties) സ്ഥിരം {
        തിരികെ pfnNextLayer(pNextLink, p_Property_എണ്ണം, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

തരനിർവചനം ഘടന VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(സ്ഥിരം ഘടന VkEnumerateInstanceVersionChain *, uint32_t *);
    സ്ഥിരം ഘടന VkEnumerateInstanceVersionChain *pNextLink;

#എങ്കിൽ defined(__cplusplus)
    വരിയിൽ VkResult CallDown(uint32_t *pApiVersion) സ്ഥിരം {
        തിരികെ pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

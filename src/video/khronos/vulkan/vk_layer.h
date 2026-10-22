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

#अन्तर्भाव "vulkan_core.h"

#define MAX_अङ्क_UNKNOWN_EXTS 250

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
प्रकारनिर्देश PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, अचर वर्ण* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
प्रकारनिर्देश गणना VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
प्रकारनिर्देश संरचना VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    शून्य *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
प्रकारनिर्देश VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
प्रकारनिर्देश गणना VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

प्रकारनिर्देश संरचना VkLayerInstanceLink_ {
    संरचना VkLayerInstanceLink_ *pNext;
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
प्रकारनिर्देश संरचना VkLayerDeviceInfo_ {
    शून्य *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        शून्य *object);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        शून्य *object);
प्रकारनिर्देश VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, अचर VkDeviceCreateInfo *pCreateInfo,
						      अचर VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, अचर VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

प्रकारनिर्देश गणना VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
प्रकारनिर्देश VkFlags VkLoaderFeatureFlags;

प्रकारनिर्देश संरचना {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    अचर शून्य *pNext;
    VkLayerFunction function;
    सङ्घ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        संरचना {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

प्रकारनिर्देश संरचना VkLayerDeviceLink_ {
    संरचना VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

प्रकारनिर्देश संरचना {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    अचर शून्य *pNext;
    VkLayerFunction function;
    सङ्घ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
बाह्य "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

प्रकारनिर्देश गणना VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

प्रकारनिर्देश संरचना VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

प्रकारनिर्देश संरचना VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(अचर संरचना VkEnumerateInstanceExtensionPropertiesChain *, अचर वर्ण *, uint32_t *,
                                      VkExtensionProperties *);
    अचर संरचना VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#यदि defined(__cplusplus)
    अन्तःस्थ VkResult CallDown(अचर वर्ण *pLayerName, uint32_t *p_Property_गन्ती, VkExtensionProperties *pProperties) अचर {
        फर्काऊ pfnNextLayer(pNextLink, pLayerName, p_Property_गन्ती, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

प्रकारनिर्देश संरचना VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(अचर संरचना VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    अचर संरचना VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#यदि defined(__cplusplus)
    अन्तःस्थ VkResult CallDown(uint32_t *p_Property_गन्ती, VkLayerProperties *pProperties) अचर {
        फर्काऊ pfnNextLayer(pNextLink, p_Property_गन्ती, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

प्रकारनिर्देश संरचना VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(अचर संरचना VkEnumerateInstanceVersionChain *, uint32_t *);
    अचर संरचना VkEnumerateInstanceVersionChain *pNextLink;

#यदि defined(__cplusplus)
    अन्तःस्थ VkResult CallDown(uint32_t *pApiVersion) अचर {
        फर्काऊ pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

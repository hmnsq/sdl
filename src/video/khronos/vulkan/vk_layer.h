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

#ضمن "vulkan_core.h"

#define MAX_اڠک_UNKNOWN_EXTS 250

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
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
تعريفنوع تعداد VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
تعريفنوع بنية VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    فراغ *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
تعريفنوع VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
تعريفنوع VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
تعريفنوع تعداد VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

تعريفنوع بنية VkLayerInstanceLink_ {
    بنية VkLayerInstanceLink_ *pNext;
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
تعريفنوع بنية VkLayerDeviceInfo_ {
    فراغ *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

تعريفنوع VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        فراغ *object);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        فراغ *object);
تعريفنوع VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ثابت VkDeviceCreateInfo *pCreateInfo,
						      ثابت VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ثابت VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

تعريفنوع تعداد VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
تعريفنوع VkFlags VkLoaderFeatureFlags;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ثابت فراغ *pNext;
    VkLayerFunction function;
    اتحاد {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        بنية {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

تعريفنوع بنية VkLayerDeviceLink_ {
    بنية VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ثابت فراغ *pNext;
    VkLayerFunction function;
    اتحاد {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
خارجي "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

تعريفنوع تعداد VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

تعريفنوع بنية VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

تعريفنوع بنية VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *, ثابت حرف *, uint32_t *,
                                      VkExtensionProperties *);
    ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#إذا defined(__cplusplus)
    مضمن VkResult CallDown(ثابت حرف *pLayerName, uint32_t *p_Property_کيراءن, VkExtensionProperties *pProperties) ثابت {
        أرجع pfnNextLayer(pNextLink, pLayerName, p_Property_کيراءن, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

تعريفنوع بنية VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ثابت بنية VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ثابت بنية VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#إذا defined(__cplusplus)
    مضمن VkResult CallDown(uint32_t *p_Property_کيراءن, VkLayerProperties *pProperties) ثابت {
        أرجع pfnNextLayer(pNextLink, p_Property_کيراءن, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

تعريفنوع بنية VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ثابت بنية VkEnumerateInstanceVersionChain *, uint32_t *);
    ثابت بنية VkEnumerateInstanceVersionChain *pNextLink;

#إذا defined(__cplusplus)
    مضمن VkResult CallDown(uint32_t *pApiVersion) ثابت {
        أرجع pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

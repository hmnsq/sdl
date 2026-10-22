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

#ಅನ್ತರ್ಭಾವ "vulkan_core.h"

#define MAX_ಅಂಕೆ_UNKNOWN_EXTS 250

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
ಪ್ರಕಾರನಿರ್ದೇಶ PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ಧ್ರುವ ವರ್ಣ* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    ಶೂನ್ಯ *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkLayerInstanceLink_ {
    ಸಂರಚನಾ VkLayerInstanceLink_ *pNext;
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
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkLayerDeviceInfo_ {
    ಶೂನ್ಯ *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        ಶೂನ್ಯ *object);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        ಶೂನ್ಯ *object);
ಪ್ರಕಾರನಿರ್ದೇಶ VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ಧ್ರುವ VkDeviceCreateInfo *pCreateInfo,
						      ಧ್ರುವ VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ಧ್ರುವ VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
ಪ್ರಕಾರನಿರ್ದೇಶ VkFlags VkLoaderFeatureFlags;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ಧ್ರುವ ಶೂನ್ಯ *pNext;
    VkLayerFunction function;
    ಸಙ್ಘ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        ಸಂರಚನಾ {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkLayerDeviceLink_ {
    ಸಂರಚನಾ VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ಧ್ರುವ ಶೂನ್ಯ *pNext;
    VkLayerFunction function;
    ಸಙ್ಘ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ಧ್ರುವ ಸಂರಚನಾ VkEnumerateInstanceExtensionPropertiesChain *, ಧ್ರುವ ವರ್ಣ *, uint32_t *,
                                      VkExtensionProperties *);
    ಧ್ರುವ ಸಂರಚನಾ VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#ಯದಿ defined(__cplusplus)
    ಅನ್ತಃಸ್ಥ VkResult CallDown(ಧ್ರುವ ವರ್ಣ *pLayerName, uint32_t *p_Property_ಎಣಿಕೆ, VkExtensionProperties *pProperties) ಧ್ರುವ {
        ಪ್ರತ್ಯಾಗಮ pfnNextLayer(pNextLink, pLayerName, p_Property_ಎಣಿಕೆ, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ಧ್ರುವ ಸಂರಚನಾ VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ಧ್ರುವ ಸಂರಚನಾ VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#ಯದಿ defined(__cplusplus)
    ಅನ್ತಃಸ್ಥ VkResult CallDown(uint32_t *p_Property_ಎಣಿಕೆ, VkLayerProperties *pProperties) ಧ್ರುವ {
        ಪ್ರತ್ಯಾಗಮ pfnNextLayer(pNextLink, p_Property_ಎಣಿಕೆ, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ಧ್ರುವ ಸಂರಚನಾ VkEnumerateInstanceVersionChain *, uint32_t *);
    ಧ್ರುವ ಸಂರಚನಾ VkEnumerateInstanceVersionChain *pNextLink;

#ಯದಿ defined(__cplusplus)
    ಅನ್ತಃಸ್ಥ VkResult CallDown(uint32_t *pApiVersion) ಧ್ರುವ {
        ಪ್ರತ್ಯಾಗಮ pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

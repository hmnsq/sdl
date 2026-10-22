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

#அந்தர்பாவ "vulkan_core.h"

#define MAX_இலக்கம்_UNKNOWN_EXTS 250

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
வகைவரை PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, மாறிலி எழுத்து* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
வகைவரை எண்ணிக்கை VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
வகைவரை கட்டமைப்பு VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    வெறுமை *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
வகைவரை VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
வகைவரை VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
வகைவரை எண்ணிக்கை VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

வகைவரை கட்டமைப்பு VkLayerInstanceLink_ {
    கட்டமைப்பு VkLayerInstanceLink_ *pNext;
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
வகைவரை கட்டமைப்பு VkLayerDeviceInfo_ {
    வெறுமை *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

வகைவரை VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        வெறுமை *object);
வகைவரை VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        வெறுமை *object);
வகைவரை VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, மாறிலி VkDeviceCreateInfo *pCreateInfo,
						      மாறிலி VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
வகைவரை வெறுமை (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, மாறிலி VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

வகைவரை எண்ணிக்கை VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
வகைவரை VkFlags VkLoaderFeatureFlags;

வகைவரை கட்டமைப்பு {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    மாறிலி வெறுமை *pNext;
    VkLayerFunction function;
    ஒன்றிப்பு {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        கட்டமைப்பு {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

வகைவரை கட்டமைப்பு VkLayerDeviceLink_ {
    கட்டமைப்பு VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

வகைவரை கட்டமைப்பு {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    மாறிலி வெறுமை *pNext;
    VkLayerFunction function;
    ஒன்றிப்பு {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
வெளி "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

வகைவரை எண்ணிக்கை VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

வகைவரை கட்டமைப்பு VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

வகைவரை கட்டமைப்பு VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(மாறிலி கட்டமைப்பு VkEnumerateInstanceExtensionPropertiesChain *, மாறிலி எழுத்து *, uint32_t *,
                                      VkExtensionProperties *);
    மாறிலி கட்டமைப்பு VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#எனில் defined(__cplusplus)
    உள்வரி VkResult CallDown(மாறிலி எழுத்து *pLayerName, uint32_t *p_Property_மொத்தம், VkExtensionProperties *pProperties) மாறிலி {
        திரும்பு pfnNextLayer(pNextLink, pLayerName, p_Property_மொத்தம், pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

வகைவரை கட்டமைப்பு VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(மாறிலி கட்டமைப்பு VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    மாறிலி கட்டமைப்பு VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#எனில் defined(__cplusplus)
    உள்வரி VkResult CallDown(uint32_t *p_Property_மொத்தம், VkLayerProperties *pProperties) மாறிலி {
        திரும்பு pfnNextLayer(pNextLink, p_Property_மொத்தம், pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

வகைவரை கட்டமைப்பு VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(மாறிலி கட்டமைப்பு VkEnumerateInstanceVersionChain *, uint32_t *);
    மாறிலி கட்டமைப்பு VkEnumerateInstanceVersionChain *pNextLink;

#எனில் defined(__cplusplus)
    உள்வரி VkResult CallDown(uint32_t *pApiVersion) மாறிலி {
        திரும்பு pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

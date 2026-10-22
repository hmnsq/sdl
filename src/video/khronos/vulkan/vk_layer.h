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

#અન્તર્ભાવ "vulkan_core.h"

#define MAX_અંક_UNKNOWN_EXTS 250

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
પ્રકારવ્યાખ્યા PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, અચલ અક્ષર* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
પ્રકારવ્યાખ્યા ગણના VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
પ્રકારવ્યાખ્યા સંરચના VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    શૂન્ય *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
પ્રકારવ્યાખ્યા VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
પ્રકારવ્યાખ્યા ગણના VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

પ્રકારવ્યાખ્યા સંરચના VkLayerInstanceLink_ {
    સંરચના VkLayerInstanceLink_ *pNext;
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
પ્રકારવ્યાખ્યા સંરચના VkLayerDeviceInfo_ {
    શૂન્ય *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        શૂન્ય *object);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        શૂન્ય *object);
પ્રકારવ્યાખ્યા VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, અચલ VkDeviceCreateInfo *pCreateInfo,
						      અચલ VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
પ્રકારવ્યાખ્યા શૂન્ય (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, અચલ VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

પ્રકારવ્યાખ્યા ગણના VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
પ્રકારવ્યાખ્યા VkFlags VkLoaderFeatureFlags;

પ્રકારવ્યાખ્યા સંરચના {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    અચલ શૂન્ય *pNext;
    VkLayerFunction function;
    સંઘ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        સંરચના {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

પ્રકારવ્યાખ્યા સંરચના VkLayerDeviceLink_ {
    સંરચના VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

પ્રકારવ્યાખ્યા સંરચના {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    અચલ શૂન્ય *pNext;
    VkLayerFunction function;
    સંઘ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
બાહ્ય "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

પ્રકારવ્યાખ્યા ગણના VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

પ્રકારવ્યાખ્યા સંરચના VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

પ્રકારવ્યાખ્યા સંરચના VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(અચલ સંરચના VkEnumerateInstanceExtensionPropertiesChain *, અચલ અક્ષર *, uint32_t *,
                                      VkExtensionProperties *);
    અચલ સંરચના VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#જો defined(__cplusplus)
    અંતઃરેખ VkResult CallDown(અચલ અક્ષર *pLayerName, uint32_t *p_Property_ગણતરી, VkExtensionProperties *pProperties) અચલ {
        પાછા pfnNextLayer(pNextLink, pLayerName, p_Property_ગણતરી, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

પ્રકારવ્યાખ્યા સંરચના VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(અચલ સંરચના VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    અચલ સંરચના VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#જો defined(__cplusplus)
    અંતઃરેખ VkResult CallDown(uint32_t *p_Property_ગણતરી, VkLayerProperties *pProperties) અચલ {
        પાછા pfnNextLayer(pNextLink, p_Property_ગણતરી, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

પ્રકારવ્યાખ્યા સંરચના VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(અચલ સંરચના VkEnumerateInstanceVersionChain *, uint32_t *);
    અચલ સંરચના VkEnumerateInstanceVersionChain *pNextLink;

#જો defined(__cplusplus)
    અંતઃરેખ VkResult CallDown(uint32_t *pApiVersion) અચલ {
        પાછા pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

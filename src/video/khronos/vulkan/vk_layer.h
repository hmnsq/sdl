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

#ଅନ୍ତର୍ଭାଵ "vulkan_core.h"

#define MAX_ଅଙ୍କ_UNKNOWN_EXTS 250

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
ପ୍ରକାରବ୍ୟାଖ୍ୟା PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ଅଚଳ ଅକ୍ଷର* pName);
#define IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#endif

// Version negotiation values
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    ଶୂନ୍ୟ *pNext;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_DATA_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkLayerInstanceLink_ {
    ସଂରଚନା VkLayerInstanceLink_ *pNext;
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
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkLayerDeviceInfo_ {
    ଶୂନ୍ୟ *device_info;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerDeviceInfo;

ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkSetInstanceLoaderData)(VkInstance instance,
        ଶୂନ୍ୟ *object);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkSetDeviceLoaderData)(VkDevice device,
        ଶୂନ୍ୟ *object);
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkResult (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ଅଚଳ VkDeviceCreateInfo *pCreateInfo,
						      ଅଚଳ VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *nextGDPA);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ଅଚଳ VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
ପ୍ରକାରବ୍ୟାଖ୍ୟା VkFlags VkLoaderFeatureFlags;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ଅଚଳ ଶୂନ୍ୟ *pNext;
    VkLayerFunction function;
    ସଂଘ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
        ସଂରଚନା {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkLayerDeviceLink_ {
    ସଂରଚନା VkLayerDeviceLink_ *pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ଅଚଳ ଶୂନ୍ୟ *pNext;
    VkLayerFunction function;
    ସଂଘ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t size;
} VkChainHeader;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ଅଚଳ ସଂରଚନା VkEnumerateInstanceExtensionPropertiesChain *, ଅଚଳ ଅକ୍ଷର *, uint32_t *,
                                      VkExtensionProperties *);
    ଅଚଳ ସଂରଚନା VkEnumerateInstanceExtensionPropertiesChain *pNextLink;

#ଯଦି defined(__cplusplus)
    ଧାଡ଼ିଭିତରେ VkResult CallDown(ଅଚଳ ଅକ୍ଷର *pLayerName, uint32_t *p_Property_ଗଣନା, VkExtensionProperties *pProperties) ଅଚଳ {
        ଫେରନ୍ତୁ pfnNextLayer(pNextLink, pLayerName, p_Property_ଗଣନା, pProperties);
    }
#endif
} VkEnumerateInstanceExtensionPropertiesChain;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ଅଚଳ ସଂରଚନା VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ଅଚଳ ସଂରଚନା VkEnumerateInstanceLayerPropertiesChain *pNextLink;

#ଯଦି defined(__cplusplus)
    ଧାଡ଼ିଭିତରେ VkResult CallDown(uint32_t *p_Property_ଗଣନା, VkLayerProperties *pProperties) ଅଚଳ {
        ଫେରନ୍ତୁ pfnNextLayer(pNextLink, p_Property_ଗଣନା, pProperties);
    }
#endif
} VkEnumerateInstanceLayerPropertiesChain;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    VkResult(VKAPI_PTR *pfnNextLayer)(ଅଚଳ ସଂରଚନା VkEnumerateInstanceVersionChain *, uint32_t *);
    ଅଚଳ ସଂରଚନା VkEnumerateInstanceVersionChain *pNextLink;

#ଯଦି defined(__cplusplus)
    ଧାଡ଼ିଭିତରେ VkResult CallDown(uint32_t *pApiVersion) ଅଚଳ {
        ଫେରନ୍ତୁ pfnNextLayer(pNextLink, pApiVersion);
    }
#endif
} VkEnumerateInstanceVersionChain;

#ifdef __cplusplus
}
#endif

/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#ਹਦਾਇਤ once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "vulkan_core.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਅੰਕ_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURRENT_LOADER_LAYER_INTERFACE_ਸੰਸਕਰਣ 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_SUPPORTED_LOADER_LAYER_INTERFACE_ਸੰਸਕਰਣ 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VK_CURRENT_CHAIN_ਸੰਸਕਰਣ 1

// Typedef for use in the interfaces below
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
ਕਿਸਮਪਰਿਭਾਸ਼ਾ PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ਅਚਲ ਅੱਖਰ* pName);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#ਜੇ_ਅੰਤ

// Version negotiation values
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    ਖਾਲੀ *p_ਅਗਲਾ;
    uint32_t loader_Layer_Interface_ਸੰਸਕਰਣ;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_ਸੰਸਕਰਣ)(VkNegotiateLayerInterface *p_ਸੰਸਕਰਣ_Struct);

// Function prototype for unknown physical device extension command
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_ਅੰਕੜੇ_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkLayerInstanceLink_ {
    ਬਣਤਰ VkLayerInstanceLink_ *p_ਅਗਲਾ;
    PFN_vkGetInstanceProcAddr pfn_ਅਗਲਾ_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_ਅਗਲਾ_Get_Physical_Device_Proc_Addr;
} VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkLayerDeviceInfo_ {
    ਖਾਲੀ *device_info;
    PFN_vkGetInstanceProcAddr pfn_ਅਗਲਾ_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_ਸੈੱਟ_Instance_Loader_ਅੰਕੜੇ)(VkInstance instance,
        ਖਾਲੀ *object);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vk_ਸੈੱਟ_Device_Loader_ਅੰਕੜੇ)(VkDevice device,
        ਖਾਲੀ *object);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Vk_ਨਤੀਜਾ (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ਅਚਲ VkDeviceCreateInfo *pCreateInfo,
						      ਅਚਲ Vk_ਵੰਡ_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *ਅਗਲਾ_GDPA);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ਅਚਲ Vk_ਵੰਡ_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Vk_Loader_Feasture_Flag_ਬਿੱਟ {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_ਛਾਂਟੀ = 0x00000001,
} Vk_Loader_Flag_ਬਿੱਟ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ VkFlags VkLoaderFeatureFlags;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ਅਚਲ ਖਾਲੀ *p_ਅਗਲਾ;
    VkLayerFunction function;
    ਸੰਘ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_ਸੈੱਟ_Instance_Loader_ਅੰਕੜੇ pfn_ਸੈੱਟ_Instance_Loader_ਅੰਕੜੇ;
        ਬਣਤਰ {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkLayerDeviceLink_ {
    ਬਣਤਰ VkLayerDeviceLink_ *p_ਅਗਲਾ;
    PFN_vkGetInstanceProcAddr pfn_ਅਗਲਾ_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_ਅਗਲਾ_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ਅਚਲ ਖਾਲੀ *p_ਅਗਲਾ;
    VkLayerFunction function;
    ਸੰਘ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_ਸੈੱਟ_Device_Loader_ਅੰਕੜੇ pfn_ਸੈੱਟ_Device_Loader_ਅੰਕੜੇ;
    } u;
} VkLayerDeviceCreateInfo;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

VKAPI_ATTR Vk_ਨਤੀਜਾ VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_ਸੰਸਕਰਣ(VkNegotiateLayerInterface *p_ਸੰਸਕਰਣ_Struct);

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_ਸੰਸਕਰਣ = 3,
} VkChainType;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Chain_ਸਿਰਲੇਖ {
    VkChainType type;
    uint32_t ਸੰਸਕਰਣ;
    uint32_t ਮਾਪ;
} Vk_Chain_ਸਿਰਲੇਖ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
    Vk_ਨਤੀਜਾ(VKAPI_PTR *pfn_ਅਗਲਾ_Layer)(ਅਚਲ ਬਣਤਰ VkEnumerateInstanceExtensionPropertiesChain *, ਅਚਲ ਅੱਖਰ *, uint32_t *,
                                      VkExtensionProperties *);
    ਅਚਲ ਬਣਤਰ VkEnumerateInstanceExtensionPropertiesChain *p_ਅਗਲਾ_Link;

#ਜੇ defined(__cplusplus)
    ਸਤਰਅੰਦਰ Vk_ਨਤੀਜਾ Call_ਥੱਲੇ(ਅਚਲ ਅੱਖਰ *pLayerName, uint32_t *p_Property_ਗਿਣਤੀ, VkExtensionProperties *pProperties) ਅਚਲ {
        ਵਾਪਸ pfn_ਅਗਲਾ_Layer(p_ਅਗਲਾ_Link, pLayerName, p_Property_ਗਿਣਤੀ, pProperties);
    }
#ਜੇ_ਅੰਤ
} VkEnumerateInstanceExtensionPropertiesChain;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
    Vk_ਨਤੀਜਾ(VKAPI_PTR *pfn_ਅਗਲਾ_Layer)(ਅਚਲ ਬਣਤਰ VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ਅਚਲ ਬਣਤਰ VkEnumerateInstanceLayerPropertiesChain *p_ਅਗਲਾ_Link;

#ਜੇ defined(__cplusplus)
    ਸਤਰਅੰਦਰ Vk_ਨਤੀਜਾ Call_ਥੱਲੇ(uint32_t *p_Property_ਗਿਣਤੀ, VkLayerProperties *pProperties) ਅਚਲ {
        ਵਾਪਸ pfn_ਅਗਲਾ_Layer(p_ਅਗਲਾ_Link, p_Property_ਗਿਣਤੀ, pProperties);
    }
#ਜੇ_ਅੰਤ
} VkEnumerateInstanceLayerPropertiesChain;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Vk_Enumerate_Instance_ਸੰਸਕਰਣ_Chain {
    Vk_Chain_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
    Vk_ਨਤੀਜਾ(VKAPI_PTR *pfn_ਅਗਲਾ_Layer)(ਅਚਲ ਬਣਤਰ Vk_Enumerate_Instance_ਸੰਸਕਰਣ_Chain *, uint32_t *);
    ਅਚਲ ਬਣਤਰ Vk_Enumerate_Instance_ਸੰਸਕਰਣ_Chain *p_ਅਗਲਾ_Link;

#ਜੇ defined(__cplusplus)
    ਸਤਰਅੰਦਰ Vk_ਨਤੀਜਾ Call_ਥੱਲੇ(uint32_t *p_Api_ਸੰਸਕਰਣ) ਅਚਲ {
        ਵਾਪਸ pfn_ਅਗਲਾ_Layer(p_ਅਗਲਾ_Link, p_Api_ਸੰਸਕਰਣ);
    }
#ਜੇ_ਅੰਤ
} Vk_Enumerate_Instance_ਸੰਸਕਰਣ_Chain;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

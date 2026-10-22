/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#ಸೂಚನೆ once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#ಅನ್ತರ್ಭಾವ "vulkan_core.h"

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ಅಂಕೆ_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#ವ್ಯಾಖ್ಯಾನಿಸು CURRENT_LOADER_LAYER_INTERFACE_ಆವೃತ್ತಿ 2
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_SUPPORTED_LOADER_LAYER_INTERFACE_ಆವೃತ್ತಿ 1

#ವ್ಯಾಖ್ಯಾನಿಸು VK_CURRENT_CHAIN_ಆವೃತ್ತಿ 1

// Typedef for use in the interfaces below
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* pName);
#ವ್ಯಾಖ್ಯಾನಿಸು IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#ಆದರೆ_ಅಂತ್ಯ

// Version negotiation values
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    ಶೂನ್ಯ *p_ಮುಂದಿನ;
    uint32_t loader_Layer_Interface_ಆವೃತ್ತಿ;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_ಆವೃತ್ತಿ)(VkNegotiateLayerInterface *p_ಆವೃತ್ತಿ_Struct);

// Function prototype for unknown physical device extension command
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_ದತ್ತಾಂಶ_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkLayerInstanceLink_ {
    ರಚನೆ VkLayerInstanceLink_ *p_ಮುಂದಿನ;
    PFN_vkGetInstanceProcAddr pfn_ಮುಂದಿನ_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_ಮುಂದಿನ_Get_Physical_Device_Proc_Addr;
} VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkLayerDeviceInfo_ {
    ಶೂನ್ಯ *device_info;
    PFN_vkGetInstanceProcAddr pfn_ಮುಂದಿನ_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_ಗಣ_Instance_Loader_ದತ್ತಾಂಶ)(VkInstance instance,
        ಶೂನ್ಯ *object);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vk_ಗಣ_Device_Loader_ದತ್ತಾಂಶ)(VkDevice device,
        ಶೂನ್ಯ *object);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Vk_ಫಲಿತಾಂಶ (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ಸ್ಥಿರಾಂಕ VkDeviceCreateInfo *pCreateInfo,
						      ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *ಮುಂದಿನ_GDPA);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ಸ್ಥಿರಾಂಕ Vk_ಹಂಚಿಕೆ_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Vk_Loader_Feasture_Flag_ಬಿಟ್ಟುಗಳು {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_ವಿಂಗಡಣೆ = 0x00000001,
} Vk_Loader_Flag_ಬಿಟ್ಟುಗಳು;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ VkFlags VkLoaderFeatureFlags;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಮುಂದಿನ;
    VkLayerFunction function;
    ಒಕ್ಕೂಟ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_ಗಣ_Instance_Loader_ದತ್ತಾಂಶ pfn_ಗಣ_Instance_Loader_ದತ್ತಾಂಶ;
        ರಚನೆ {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkLayerDeviceLink_ {
    ರಚನೆ VkLayerDeviceLink_ *p_ಮುಂದಿನ;
    PFN_vkGetInstanceProcAddr pfn_ಮುಂದಿನ_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_ಮುಂದಿನ_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಮುಂದಿನ;
    VkLayerFunction function;
    ಒಕ್ಕೂಟ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_ಗಣ_Device_Loader_ದತ್ತಾಂಶ pfn_ಗಣ_Device_Loader_ದತ್ತಾಂಶ;
    } u;
} VkLayerDeviceCreateInfo;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

VKAPI_ATTR Vk_ಫಲಿತಾಂಶ VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_ಆವೃತ್ತಿ(VkNegotiateLayerInterface *p_ಆವೃತ್ತಿ_Struct);

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_ಆವೃತ್ತಿ = 3,
} VkChainType;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Chain_ಶೀರ್ಷಿಕೆ {
    VkChainType type;
    uint32_t ಆವೃತ್ತಿ;
    uint32_t ಗಾತ್ರ_2;
} Vk_Chain_ಶೀರ್ಷಿಕೆ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
    Vk_ಫಲಿತಾಂಶ(VKAPI_PTR *pfn_ಮುಂದಿನ_Layer)(ಸ್ಥಿರಾಂಕ ರಚನೆ VkEnumerateInstanceExtensionPropertiesChain *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, uint32_t *,
                                      VkExtensionProperties *);
    ಸ್ಥಿರಾಂಕ ರಚನೆ VkEnumerateInstanceExtensionPropertiesChain *p_ಮುಂದಿನ_Link;

#ಆದರೆ defined(__cplusplus)
    ಸಾಲೊಳಗೆ Vk_ಫಲಿತಾಂಶ Call_ಕೆಳಕ್ಕೆ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pLayerName, uint32_t *p_Property_ಎಣಿಕೆ, VkExtensionProperties *pProperties) ಸ್ಥಿರಾಂಕ {
        ಹಿಂತಿರುಗಿ pfn_ಮುಂದಿನ_Layer(p_ಮುಂದಿನ_Link, pLayerName, p_Property_ಎಣಿಕೆ, pProperties);
    }
#ಆದರೆ_ಅಂತ್ಯ
} VkEnumerateInstanceExtensionPropertiesChain;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
    Vk_ಫಲಿತಾಂಶ(VKAPI_PTR *pfn_ಮುಂದಿನ_Layer)(ಸ್ಥಿರಾಂಕ ರಚನೆ VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ಸ್ಥಿರಾಂಕ ರಚನೆ VkEnumerateInstanceLayerPropertiesChain *p_ಮುಂದಿನ_Link;

#ಆದರೆ defined(__cplusplus)
    ಸಾಲೊಳಗೆ Vk_ಫಲಿತಾಂಶ Call_ಕೆಳಕ್ಕೆ(uint32_t *p_Property_ಎಣಿಕೆ, VkLayerProperties *pProperties) ಸ್ಥಿರಾಂಕ {
        ಹಿಂತಿರುಗಿ pfn_ಮುಂದಿನ_Layer(p_ಮುಂದಿನ_Link, p_Property_ಎಣಿಕೆ, pProperties);
    }
#ಆದರೆ_ಅಂತ್ಯ
} VkEnumerateInstanceLayerPropertiesChain;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Vk_Enumerate_Instance_ಆವೃತ್ತಿ_Chain {
    Vk_Chain_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
    Vk_ಫಲಿತಾಂಶ(VKAPI_PTR *pfn_ಮುಂದಿನ_Layer)(ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_Enumerate_Instance_ಆವೃತ್ತಿ_Chain *, uint32_t *);
    ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_Enumerate_Instance_ಆವೃತ್ತಿ_Chain *p_ಮುಂದಿನ_Link;

#ಆದರೆ defined(__cplusplus)
    ಸಾಲೊಳಗೆ Vk_ಫಲಿತಾಂಶ Call_ಕೆಳಕ್ಕೆ(uint32_t *p_Api_ಆವೃತ್ತಿ) ಸ್ಥಿರಾಂಕ {
        ಹಿಂತಿರುಗಿ pfn_ಮುಂದಿನ_Layer(p_ಮುಂದಿನ_Link, p_Api_ಆವೃತ್ತಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ
} Vk_Enumerate_Instance_ಆವೃತ್ತಿ_Chain;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

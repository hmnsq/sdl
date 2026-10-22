/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#निर्देशः once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#अन्तर्भाव "vulkan_core.h"

#परिभाषय MAX_अङ्कः_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#परिभाषय CURRENT_LOADER_LAYER_INTERFACE_संस्करणम् 2
#परिभाषय MIN_SUPPORTED_LOADER_LAYER_INTERFACE_संस्करणम् 1

#परिभाषय VK_CURRENT_CHAIN_संस्करणम् 1

// Typedef for use in the interfaces below
#यदि_अपरिभाषितम् IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
प्रकारनिर्देश PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ध्रुव वर्ण* pName);
#परिभाषय IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#यदि_अन्तः

// Version negotiation values
प्रकारनिर्देश गणना VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
प्रकारनिर्देश संरचना VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    शून्य *p_अग्र;
    uint32_t loader_Layer_Interface_संस्करणम्;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_संस्करणम्)(VkNegotiateLayerInterface *p_संस्करणम्_Struct);

// Function prototype for unknown physical device extension command
प्रकारनिर्देश Vk_परिणाम(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
प्रकारनिर्देश गणना VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_दत्त_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

प्रकारनिर्देश संरचना VkLayerInstanceLink_ {
    संरचना VkLayerInstanceLink_ *p_अग्र;
    PFN_vkGetInstanceProcAddr pfn_अग्र_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_अग्र_Get_Physical_Device_Proc_Addr;
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
    PFN_vkGetInstanceProcAddr pfn_अग्र_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_समुच्चयः_Instance_Loader_दत्त)(VkInstance instance,
        शून्य *object);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vk_समुच्चयः_Device_Loader_दत्त)(VkDevice device,
        शून्य *object);
प्रकारनिर्देश Vk_परिणाम (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ध्रुव VkDeviceCreateInfo *pCreateInfo,
						      ध्रुव Vk_आवण्टनम्_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *अग्र_GDPA);
प्रकारनिर्देश शून्य (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ध्रुव Vk_आवण्टनम्_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

प्रकारनिर्देश गणना Vk_Loader_Feasture_Flag_द्वयङ्काः {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_क्रमणम् = 0x00000001,
} Vk_Loader_Flag_द्वयङ्काः;
प्रकारनिर्देश VkFlags VkLoaderFeatureFlags;

प्रकारनिर्देश संरचना {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ध्रुव शून्य *p_अग्र;
    VkLayerFunction function;
    सङ्घ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_समुच्चयः_Instance_Loader_दत्त pfn_समुच्चयः_Instance_Loader_दत्त;
        संरचना {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

प्रकारनिर्देश संरचना VkLayerDeviceLink_ {
    संरचना VkLayerDeviceLink_ *p_अग्र;
    PFN_vkGetInstanceProcAddr pfn_अग्र_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_अग्र_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

प्रकारनिर्देश संरचना {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ध्रुव शून्य *p_अग्र;
    VkLayerFunction function;
    सङ्घ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_समुच्चयः_Device_Loader_दत्त pfn_समुच्चयः_Device_Loader_दत्त;
    } u;
} VkLayerDeviceCreateInfo;

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

VKAPI_ATTR Vk_परिणाम VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_संस्करणम्(VkNegotiateLayerInterface *p_संस्करणम्_Struct);

प्रकारनिर्देश गणना VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_संस्करणम् = 3,
} VkChainType;

प्रकारनिर्देश संरचना Vk_Chain_शीर्षकम् {
    VkChainType type;
    uint32_t संस्करणम्;
    uint32_t आकार;
} Vk_Chain_शीर्षकम्;

प्रकारनिर्देश संरचना VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_शीर्षकम् शीर्षकम्;
    Vk_परिणाम(VKAPI_PTR *pfn_अग्र_Layer)(ध्रुव संरचना VkEnumerateInstanceExtensionPropertiesChain *, ध्रुव वर्ण *, uint32_t *,
                                      VkExtensionProperties *);
    ध्रुव संरचना VkEnumerateInstanceExtensionPropertiesChain *p_अग्र_Link;

#यदि defined(__cplusplus)
    अन्तःस्थ Vk_परिणाम Call_अधस्तात्(ध्रुव वर्ण *pLayerName, uint32_t *p_Property_गणनम्, VkExtensionProperties *pProperties) ध्रुव {
        प्रत्यागम pfn_अग्र_Layer(p_अग्र_Link, pLayerName, p_Property_गणनम्, pProperties);
    }
#यदि_अन्तः
} VkEnumerateInstanceExtensionPropertiesChain;

प्रकारनिर्देश संरचना VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_शीर्षकम् शीर्षकम्;
    Vk_परिणाम(VKAPI_PTR *pfn_अग्र_Layer)(ध्रुव संरचना VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ध्रुव संरचना VkEnumerateInstanceLayerPropertiesChain *p_अग्र_Link;

#यदि defined(__cplusplus)
    अन्तःस्थ Vk_परिणाम Call_अधस्तात्(uint32_t *p_Property_गणनम्, VkLayerProperties *pProperties) ध्रुव {
        प्रत्यागम pfn_अग्र_Layer(p_अग्र_Link, p_Property_गणनम्, pProperties);
    }
#यदि_अन्तः
} VkEnumerateInstanceLayerPropertiesChain;

प्रकारनिर्देश संरचना Vk_Enumerate_Instance_संस्करणम्_Chain {
    Vk_Chain_शीर्षकम् शीर्षकम्;
    Vk_परिणाम(VKAPI_PTR *pfn_अग्र_Layer)(ध्रुव संरचना Vk_Enumerate_Instance_संस्करणम्_Chain *, uint32_t *);
    ध्रुव संरचना Vk_Enumerate_Instance_संस्करणम्_Chain *p_अग्र_Link;

#यदि defined(__cplusplus)
    अन्तःस्थ Vk_परिणाम Call_अधस्तात्(uint32_t *p_Api_संस्करणम्) ध्रुव {
        प्रत्यागम pfn_अग्र_Layer(p_अग्र_Link, p_Api_संस्करणम्);
    }
#यदि_अन्तः
} Vk_Enumerate_Instance_संस्करणम्_Chain;

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

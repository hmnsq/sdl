/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#आशय once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#समावेश "vulkan_core.h"

#घोषणा MAX_अंक_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#घोषणा CURRENT_LOADER_LAYER_INTERFACE_VERSION 2
#घोषणा MIN_SUPPORTED_LOADER_LAYER_INTERFACE_VERSION 1

#घोषणा VK_CURRENT_CHAIN_VERSION 1

// Typedef for use in the interfaces below
#अगर_अघोषित IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
प्रकार PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, स्थिर अक्षर* pName);
#घोषणा IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#पूर्ण_अगर

// Version negotiation values
प्रकार क्रमागत VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
प्रकार काष्ठा VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    व्योम *p_अग्र;
    uint32_t loaderLayerInterfaceVersion;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkNegotiateLoaderLayerInterfaceVersion)(VkNegotiateLayerInterface *pVersionStruct);

// Function prototype for unknown physical device extension command
प्रकार Vk_परिणाम(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
प्रकार क्रमागत VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_तथ्य_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

प्रकार काष्ठा VkLayerInstanceLink_ {
    काष्ठा VkLayerInstanceLink_ *p_अग्र;
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
प्रकार काष्ठा VkLayerDeviceInfo_ {
    व्योम *device_info;
    PFN_vkGetInstanceProcAddr pfn_अग्र_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Set_Instance_Loader_तथ्य)(VkInstance instance,
        व्योम *object);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vk_Set_Device_Loader_तथ्य)(VkDevice device,
        व्योम *object);
प्रकार Vk_परिणाम (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, स्थिर VkDeviceCreateInfo *pCreateInfo,
						      स्थिर VkAllocationCallbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *अग्र_GDPA);
प्रकार व्योम (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, स्थिर VkAllocationCallbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

प्रकार क्रमागत VkLoaderFeastureFlagBits {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_SORTING = 0x00000001,
} VkLoaderFlagBits;
प्रकार VkFlags VkLoaderFeatureFlags;

प्रकार काष्ठा {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    स्थिर व्योम *p_अग्र;
    VkLayerFunction function;
    जोड़ {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_Set_Instance_Loader_तथ्य pfn_Set_Instance_Loader_तथ्य;
        काष्ठा {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

प्रकार काष्ठा VkLayerDeviceLink_ {
    काष्ठा VkLayerDeviceLink_ *p_अग्र;
    PFN_vkGetInstanceProcAddr pfn_अग्र_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_अग्र_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

प्रकार काष्ठा {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    स्थिर व्योम *p_अग्र;
    VkLayerFunction function;
    जोड़ {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_Set_Device_Loader_तथ्य pfn_Set_Device_Loader_तथ्य;
    } u;
} VkLayerDeviceCreateInfo;

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

VKAPI_ATTR Vk_परिणाम VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface *pVersionStruct);

प्रकार क्रमागत VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_VERSION = 3,
} VkChainType;

प्रकार काष्ठा VkChainHeader {
    VkChainType type;
    uint32_t version;
    uint32_t आकार;
} VkChainHeader;

प्रकार काष्ठा VkEnumerateInstanceExtensionPropertiesChain {
    VkChainHeader header;
    Vk_परिणाम(VKAPI_PTR *pfn_अग्र_Layer)(स्थिर काष्ठा VkEnumerateInstanceExtensionPropertiesChain *, स्थिर अक्षर *, uint32_t *,
                                      VkExtensionProperties *);
    स्थिर काष्ठा VkEnumerateInstanceExtensionPropertiesChain *p_अग्र_Link;

#अगर defined(__cplusplus)
    अंतरभूत Vk_परिणाम CallDown(स्थिर अक्षर *pLayerName, uint32_t *p_Property_गिनती, VkExtensionProperties *pProperties) स्थिर {
        वापस pfn_अग्र_Layer(p_अग्र_Link, pLayerName, p_Property_गिनती, pProperties);
    }
#पूर्ण_अगर
} VkEnumerateInstanceExtensionPropertiesChain;

प्रकार काष्ठा VkEnumerateInstanceLayerPropertiesChain {
    VkChainHeader header;
    Vk_परिणाम(VKAPI_PTR *pfn_अग्र_Layer)(स्थिर काष्ठा VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    स्थिर काष्ठा VkEnumerateInstanceLayerPropertiesChain *p_अग्र_Link;

#अगर defined(__cplusplus)
    अंतरभूत Vk_परिणाम CallDown(uint32_t *p_Property_गिनती, VkLayerProperties *pProperties) स्थिर {
        वापस pfn_अग्र_Layer(p_अग्र_Link, p_Property_गिनती, pProperties);
    }
#पूर्ण_अगर
} VkEnumerateInstanceLayerPropertiesChain;

प्रकार काष्ठा VkEnumerateInstanceVersionChain {
    VkChainHeader header;
    Vk_परिणाम(VKAPI_PTR *pfn_अग्र_Layer)(स्थिर काष्ठा VkEnumerateInstanceVersionChain *, uint32_t *);
    स्थिर काष्ठा VkEnumerateInstanceVersionChain *p_अग्र_Link;

#अगर defined(__cplusplus)
    अंतरभूत Vk_परिणाम CallDown(uint32_t *pApiVersion) स्थिर {
        वापस pfn_अग्र_Layer(p_अग्र_Link, pApiVersion);
    }
#पूर्ण_अगर
} VkEnumerateInstanceVersionChain;

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

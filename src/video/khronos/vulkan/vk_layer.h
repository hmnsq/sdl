/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#సూచన once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#అన్తర్భావ "vulkan_core.h"

#నిర్వచించు MAX_అంకె_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#నిర్వచించు CURRENT_LOADER_LAYER_INTERFACE_సంస్కరణ 2
#నిర్వచించు MIN_SUPPORTED_LOADER_LAYER_INTERFACE_సంస్కరణ 1

#నిర్వచించు VK_CURRENT_CHAIN_సంస్కరణ 1

// Typedef for use in the interfaces below
#నిర్వచితం_కాకపోతే IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
రకనిర్వచనం PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, స్థిరరాశి అక్షరం* pName);
#నిర్వచించు IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#అయితే_ముగింపు

// Version negotiation values
రకనిర్వచనం గణన VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
రకనిర్వచనం నిర్మాణం VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    శూన్య *p_తదుపరి;
    uint32_t loader_Layer_Interface_సంస్కరణ;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_సంస్కరణ)(VkNegotiateLayerInterface *p_సంస్కరణ_Struct);

// Function prototype for unknown physical device extension command
రకనిర్వచనం Vk_ఫలితం(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
రకనిర్వచనం గణన VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_దత్తాంశం_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

రకనిర్వచనం నిర్మాణం VkLayerInstanceLink_ {
    నిర్మాణం VkLayerInstanceLink_ *p_తదుపరి;
    PFN_vkGetInstanceProcAddr pfn_తదుపరి_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_తదుపరి_Get_Physical_Device_Proc_Addr;
} VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */
రకనిర్వచనం నిర్మాణం VkLayerDeviceInfo_ {
    శూన్య *device_info;
    PFN_vkGetInstanceProcAddr pfn_తదుపరి_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_సమితి_Instance_Loader_దత్తాంశం)(VkInstance instance,
        శూన్య *object);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vk_సమితి_Device_Loader_దత్తాంశం)(VkDevice device,
        శూన్య *object);
రకనిర్వచనం Vk_ఫలితం (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, స్థిరరాశి VkDeviceCreateInfo *pCreateInfo,
						      స్థిరరాశి Vk_కేటాయింపు_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *తదుపరి_GDPA);
రకనిర్వచనం శూన్య (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, స్థిరరాశి Vk_కేటాయింపు_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

రకనిర్వచనం గణన Vk_Loader_Feasture_Flag_బిట్లు {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_క్రమీకరణ = 0x00000001,
} Vk_Loader_Flag_బిట్లు;
రకనిర్వచనం VkFlags VkLoaderFeatureFlags;

రకనిర్వచనం నిర్మాణం {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    స్థిరరాశి శూన్య *p_తదుపరి;
    VkLayerFunction function;
    సంఘం {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_సమితి_Instance_Loader_దత్తాంశం pfn_సమితి_Instance_Loader_దత్తాంశం;
        నిర్మాణం {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

రకనిర్వచనం నిర్మాణం VkLayerDeviceLink_ {
    నిర్మాణం VkLayerDeviceLink_ *p_తదుపరి;
    PFN_vkGetInstanceProcAddr pfn_తదుపరి_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_తదుపరి_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

రకనిర్వచనం నిర్మాణం {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    స్థిరరాశి శూన్య *p_తదుపరి;
    VkLayerFunction function;
    సంఘం {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_సమితి_Device_Loader_దత్తాంశం pfn_సమితి_Device_Loader_దత్తాంశం;
    } u;
} VkLayerDeviceCreateInfo;

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

VKAPI_ATTR Vk_ఫలితం VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_సంస్కరణ(VkNegotiateLayerInterface *p_సంస్కరణ_Struct);

రకనిర్వచనం గణన VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_సంస్కరణ = 3,
} VkChainType;

రకనిర్వచనం నిర్మాణం Vk_Chain_శీర్షిక {
    VkChainType type;
    uint32_t సంస్కరణ;
    uint32_t కొలత;
} Vk_Chain_శీర్షిక;

రకనిర్వచనం నిర్మాణం VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_శీర్షిక శీర్షిక;
    Vk_ఫలితం(VKAPI_PTR *pfn_తదుపరి_Layer)(స్థిరరాశి నిర్మాణం VkEnumerateInstanceExtensionPropertiesChain *, స్థిరరాశి అక్షరం *, uint32_t *,
                                      VkExtensionProperties *);
    స్థిరరాశి నిర్మాణం VkEnumerateInstanceExtensionPropertiesChain *p_తదుపరి_Link;

#ఒకవేళ defined(__cplusplus)
    అంతఃవరుస Vk_ఫలితం Call_కిందికి(స్థిరరాశి అక్షరం *pLayerName, uint32_t *p_Property_లెక్క, VkExtensionProperties *pProperties) స్థిరరాశి {
        తిరిగి pfn_తదుపరి_Layer(p_తదుపరి_Link, pLayerName, p_Property_లెక్క, pProperties);
    }
#అయితే_ముగింపు
} VkEnumerateInstanceExtensionPropertiesChain;

రకనిర్వచనం నిర్మాణం VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_శీర్షిక శీర్షిక;
    Vk_ఫలితం(VKAPI_PTR *pfn_తదుపరి_Layer)(స్థిరరాశి నిర్మాణం VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    స్థిరరాశి నిర్మాణం VkEnumerateInstanceLayerPropertiesChain *p_తదుపరి_Link;

#ఒకవేళ defined(__cplusplus)
    అంతఃవరుస Vk_ఫలితం Call_కిందికి(uint32_t *p_Property_లెక్క, VkLayerProperties *pProperties) స్థిరరాశి {
        తిరిగి pfn_తదుపరి_Layer(p_తదుపరి_Link, p_Property_లెక్క, pProperties);
    }
#అయితే_ముగింపు
} VkEnumerateInstanceLayerPropertiesChain;

రకనిర్వచనం నిర్మాణం Vk_Enumerate_Instance_సంస్కరణ_Chain {
    Vk_Chain_శీర్షిక శీర్షిక;
    Vk_ఫలితం(VKAPI_PTR *pfn_తదుపరి_Layer)(స్థిరరాశి నిర్మాణం Vk_Enumerate_Instance_సంస్కరణ_Chain *, uint32_t *);
    స్థిరరాశి నిర్మాణం Vk_Enumerate_Instance_సంస్కరణ_Chain *p_తదుపరి_Link;

#ఒకవేళ defined(__cplusplus)
    అంతఃవరుస Vk_ఫలితం Call_కిందికి(uint32_t *p_Api_సంస్కరణ) స్థిరరాశి {
        తిరిగి pfn_తదుపరి_Layer(p_తదుపరి_Link, p_Api_సంస్కరణ);
    }
#అయితే_ముగింపు
} Vk_Enumerate_Instance_సంస్కరణ_Chain;

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

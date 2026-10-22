/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#ہدایت once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#شامل "vulkan_core.h"

#تعریف_کرو MAX_عدد_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#تعریف_کرو CURRENT_LOADER_LAYER_INTERFACE_نسخہ 2
#تعریف_کرو MIN_SUPPORTED_LOADER_LAYER_INTERFACE_نسخہ 1

#تعریف_کرو VK_CURRENT_CHAIN_نسخہ 1

// Typedef for use in the interfaces below
#اگر_غیر_تعریف_شدہ IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
قسمتعریف PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#تعریف_کرو IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#اگر_ختم

// Version negotiation values
قسمتعریف شمار VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
قسمتعریف ساخت VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    خالی *p_اگلا;
    uint32_t loader_Layer_Interface_نسخہ;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_نسخہ)(VkNegotiateLayerInterface *p_نسخہ_Struct);

// Function prototype for unknown physical device extension command
قسمتعریف Vk_نتیجہ(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
قسمتعریف شمار VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_ڈیٹا_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

قسمتعریف ساخت VkLayerInstanceLink_ {
    ساخت VkLayerInstanceLink_ *p_اگلا;
    PFN_vkGetInstanceProcAddr pfn_اگلا_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_اگلا_Get_Physical_Device_Proc_Addr;
} VkLayerInstanceLink;

/*
 * When creating the device chain the loader needs to pass
 * down information about it's device structure needed at
 * the end of the chain. Passing the data via the
 * VkLayerDeviceInfo avoids issues with finding the
 * exact instance being used.
 */
قسمتعریف ساخت VkLayerDeviceInfo_ {
    خالی *device_info;
    PFN_vkGetInstanceProcAddr pfn_اگلا_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_Instance_Loader_ڈیٹا)(VkInstance instance,
        خالی *object);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_Device_Loader_ڈیٹا)(VkDevice device,
        خالی *object);
قسمتعریف Vk_نتیجہ (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ثابت VkDeviceCreateInfo *pCreateInfo,
						      ثابت Vk_تخصیص_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *اگلا_GDPA);
قسمتعریف خالی (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ثابت Vk_تخصیص_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

قسمتعریف شمار Vk_Loader_Feasture_Flag_بٹ {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_ترتیب_کاری = 0x00000001,
} Vk_Loader_Flag_بٹ;
قسمتعریف VkFlags VkLoaderFeatureFlags;

قسمتعریف ساخت {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ثابت خالی *p_اگلا;
    VkLayerFunction function;
    اتحاد {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_سیٹ_Instance_Loader_ڈیٹا pfn_سیٹ_Instance_Loader_ڈیٹا;
        ساخت {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

قسمتعریف ساخت VkLayerDeviceLink_ {
    ساخت VkLayerDeviceLink_ *p_اگلا;
    PFN_vkGetInstanceProcAddr pfn_اگلا_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_اگلا_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

قسمتعریف ساخت {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ثابت خالی *p_اگلا;
    VkLayerFunction function;
    اتحاد {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_سیٹ_Device_Loader_ڈیٹا pfn_سیٹ_Device_Loader_ڈیٹا;
    } u;
} VkLayerDeviceCreateInfo;

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_نسخہ(VkNegotiateLayerInterface *p_نسخہ_Struct);

قسمتعریف شمار VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_نسخہ = 3,
} VkChainType;

قسمتعریف ساخت Vk_Chain_سرخی {
    VkChainType type;
    uint32_t نسخہ;
    uint32_t سائز;
} Vk_Chain_سرخی;

قسمتعریف ساخت VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_سرخی سرخی;
    Vk_نتیجہ(VKAPI_PTR *pfn_اگلا_Layer)(ثابت ساخت VkEnumerateInstanceExtensionPropertiesChain *, ثابت حرف *, uint32_t *,
                                      VkExtensionProperties *);
    ثابت ساخت VkEnumerateInstanceExtensionPropertiesChain *p_اگلا_Link;

#اگر defined(__cplusplus)
    اندرونی Vk_نتیجہ Call_نیچے_کو(ثابت حرف *pLayerName, uint32_t *p_Property_گنتی, VkExtensionProperties *pProperties) ثابت {
        واپس pfn_اگلا_Layer(p_اگلا_Link, pLayerName, p_Property_گنتی, pProperties);
    }
#اگر_ختم
} VkEnumerateInstanceExtensionPropertiesChain;

قسمتعریف ساخت VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_سرخی سرخی;
    Vk_نتیجہ(VKAPI_PTR *pfn_اگلا_Layer)(ثابت ساخت VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ثابت ساخت VkEnumerateInstanceLayerPropertiesChain *p_اگلا_Link;

#اگر defined(__cplusplus)
    اندرونی Vk_نتیجہ Call_نیچے_کو(uint32_t *p_Property_گنتی, VkLayerProperties *pProperties) ثابت {
        واپس pfn_اگلا_Layer(p_اگلا_Link, p_Property_گنتی, pProperties);
    }
#اگر_ختم
} VkEnumerateInstanceLayerPropertiesChain;

قسمتعریف ساخت Vk_Enumerate_Instance_نسخہ_Chain {
    Vk_Chain_سرخی سرخی;
    Vk_نتیجہ(VKAPI_PTR *pfn_اگلا_Layer)(ثابت ساخت Vk_Enumerate_Instance_نسخہ_Chain *, uint32_t *);
    ثابت ساخت Vk_Enumerate_Instance_نسخہ_Chain *p_اگلا_Link;

#اگر defined(__cplusplus)
    اندرونی Vk_نتیجہ Call_نیچے_کو(uint32_t *p_Api_نسخہ) ثابت {
        واپس pfn_اگلا_Layer(p_اگلا_Link, p_Api_نسخہ);
    }
#اگر_ختم
} Vk_Enumerate_Instance_نسخہ_Chain;

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

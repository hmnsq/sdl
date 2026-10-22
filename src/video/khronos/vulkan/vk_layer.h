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

#ضمن "vulkan_core.h"

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
#جے_بنا_تعریف IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#تعریف_کرو IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#جے_انت

// Version negotiation values
تعريفنوع تعداد VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
تعريفنوع بنية VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    فراغ *p_اگلا;
    uint32_t loader_Layer_Interface_نسخہ;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_نسخہ)(VkNegotiateLayerInterface *p_نسخہ_Struct);

// Function prototype for unknown physical device extension command
تعريفنوع Vk_نتیجہ(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
تعريفنوع تعداد VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_انکڑے_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

تعريفنوع بنية VkLayerInstanceLink_ {
    بنية VkLayerInstanceLink_ *p_اگلا;
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
تعريفنوع بنية VkLayerDeviceInfo_ {
    فراغ *device_info;
    PFN_vkGetInstanceProcAddr pfn_اگلا_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_Instance_Loader_انکڑے)(VkInstance instance,
        فراغ *object);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vk_سیٹ_Device_Loader_انکڑے)(VkDevice device,
        فراغ *object);
تعريفنوع Vk_نتیجہ (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ثابت VkDeviceCreateInfo *pCreateInfo,
						      ثابت Vk_ونڈ_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *اگلا_GDPA);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ثابت Vk_ونڈ_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

تعريفنوع تعداد Vk_Loader_Feasture_Flag_بٹ {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_چھانٹی = 0x00000001,
} Vk_Loader_Flag_بٹ;
تعريفنوع VkFlags VkLoaderFeatureFlags;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ثابت فراغ *p_اگلا;
    VkLayerFunction function;
    اتحاد {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_سیٹ_Instance_Loader_انکڑے pfn_سیٹ_Instance_Loader_انکڑے;
        بنية {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

تعريفنوع بنية VkLayerDeviceLink_ {
    بنية VkLayerDeviceLink_ *p_اگلا;
    PFN_vkGetInstanceProcAddr pfn_اگلا_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_اگلا_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ثابت فراغ *p_اگلا;
    VkLayerFunction function;
    اتحاد {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_سیٹ_Device_Loader_انکڑے pfn_سیٹ_Device_Loader_انکڑے;
    } u;
} VkLayerDeviceCreateInfo;

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

VKAPI_ATTR Vk_نتیجہ VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_نسخہ(VkNegotiateLayerInterface *p_نسخہ_Struct);

تعريفنوع تعداد VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_نسخہ = 3,
} VkChainType;

تعريفنوع بنية Vk_Chain_سرخی {
    VkChainType type;
    uint32_t نسخہ;
    uint32_t ناپ;
} Vk_Chain_سرخی;

تعريفنوع بنية VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_سرخی سرخی;
    Vk_نتیجہ(VKAPI_PTR *pfn_اگلا_Layer)(ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *, ثابت حرف *, uint32_t *,
                                      VkExtensionProperties *);
    ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *p_اگلا_Link;

#إذا defined(__cplusplus)
    مضمن Vk_نتیجہ Call_تھلے(ثابت حرف *pLayerName, uint32_t *p_Property_گنتی, VkExtensionProperties *pProperties) ثابت {
        أرجع pfn_اگلا_Layer(p_اگلا_Link, pLayerName, p_Property_گنتی, pProperties);
    }
#جے_انت
} VkEnumerateInstanceExtensionPropertiesChain;

تعريفنوع بنية VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_سرخی سرخی;
    Vk_نتیجہ(VKAPI_PTR *pfn_اگلا_Layer)(ثابت بنية VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ثابت بنية VkEnumerateInstanceLayerPropertiesChain *p_اگلا_Link;

#إذا defined(__cplusplus)
    مضمن Vk_نتیجہ Call_تھلے(uint32_t *p_Property_گنتی, VkLayerProperties *pProperties) ثابت {
        أرجع pfn_اگلا_Layer(p_اگلا_Link, p_Property_گنتی, pProperties);
    }
#جے_انت
} VkEnumerateInstanceLayerPropertiesChain;

تعريفنوع بنية Vk_Enumerate_Instance_نسخہ_Chain {
    Vk_Chain_سرخی سرخی;
    Vk_نتیجہ(VKAPI_PTR *pfn_اگلا_Layer)(ثابت بنية Vk_Enumerate_Instance_نسخہ_Chain *, uint32_t *);
    ثابت بنية Vk_Enumerate_Instance_نسخہ_Chain *p_اگلا_Link;

#إذا defined(__cplusplus)
    مضمن Vk_نتیجہ Call_تھلے(uint32_t *p_Api_نسخہ) ثابت {
        أرجع pfn_اگلا_Layer(p_اگلا_Link, p_Api_نسخہ);
    }
#جے_انت
} Vk_Enumerate_Instance_نسخہ_Chain;

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#هدايت once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#ضمن "vulkan_core.h"

#وصف_ڪريو MAX_انگ_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#وصف_ڪريو CURRENT_LOADER_LAYER_INTERFACE_نسخو 2
#وصف_ڪريو MIN_SUPPORTED_LOADER_LAYER_INTERFACE_نسخو 1

#وصف_ڪريو VK_CURRENT_CHAIN_نسخو 1

// Typedef for use in the interfaces below
#جيڪڏهن_وصف_نه_ٿيل IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#وصف_ڪريو IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#جيڪڏهن_پورو

// Version negotiation values
تعريفنوع تعداد VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
تعريفنوع بنية VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    فراغ *p_ايندڙ;
    uint32_t loader_Layer_Interface_نسخو;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_نسخو)(VkNegotiateLayerInterface *p_نسخو_Struct);

// Function prototype for unknown physical device extension command
تعريفنوع Vk_نتيجو(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

/* Sub type of structure for instance and device loader ext of CreateInfo.
 * When sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
 * or sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
 * then VkLayerFunction indicates struct type pointed to by pNext
 */
تعريفنوع تعداد VkLayerFunction_ {
    VK_LAYER_LINK_INFO = 0,
    VK_LOADER_معلومات_CALLBACK = 1,
    VK_LOADER_LAYER_CREATE_DEVICE_CALLBACK = 2,
    VK_LOADER_FEATURES = 3,
} VkLayerFunction;

تعريفنوع بنية VkLayerInstanceLink_ {
    بنية VkLayerInstanceLink_ *p_ايندڙ;
    PFN_vkGetInstanceProcAddr pfn_ايندڙ_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_ايندڙ_Get_Physical_Device_Proc_Addr;
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
    PFN_vkGetInstanceProcAddr pfn_ايندڙ_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_سيٽ_Instance_Loader_معلومات)(VkInstance instance,
        فراغ *object);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vk_سيٽ_Device_Loader_معلومات)(VkDevice device,
        فراغ *object);
تعريفنوع Vk_نتيجو (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ثابت VkDeviceCreateInfo *pCreateInfo,
						      ثابت Vk_ورهاست_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *ايندڙ_GDPA);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ثابت Vk_ورهاست_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

تعريفنوع تعداد Vk_Loader_Feasture_Flag_بٽ {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_ترتيب_ڏيڻ = 0x00000001,
} Vk_Loader_Flag_بٽ;
تعريفنوع VkFlags VkLoaderFeatureFlags;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ثابت فراغ *p_ايندڙ;
    VkLayerFunction function;
    اتحاد {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_سيٽ_Instance_Loader_معلومات pfn_سيٽ_Instance_Loader_معلومات;
        بنية {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

تعريفنوع بنية VkLayerDeviceLink_ {
    بنية VkLayerDeviceLink_ *p_ايندڙ;
    PFN_vkGetInstanceProcAddr pfn_ايندڙ_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_ايندڙ_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ثابت فراغ *p_ايندڙ;
    VkLayerFunction function;
    اتحاد {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_سيٽ_Device_Loader_معلومات pfn_سيٽ_Device_Loader_معلومات;
    } u;
} VkLayerDeviceCreateInfo;

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

VKAPI_ATTR Vk_نتيجو VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_نسخو(VkNegotiateLayerInterface *p_نسخو_Struct);

تعريفنوع تعداد VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_نسخو = 3,
} VkChainType;

تعريفنوع بنية Vk_Chain_سرو {
    VkChainType type;
    uint32_t نسخو;
    uint32_t سائيز;
} Vk_Chain_سرو;

تعريفنوع بنية VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_سرو سرو;
    Vk_نتيجو(VKAPI_PTR *pfn_ايندڙ_Layer)(ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *, ثابت حرف *, uint32_t *,
                                      VkExtensionProperties *);
    ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *p_ايندڙ_Link;

#إذا defined(__cplusplus)
    مضمن Vk_نتيجو Call_هيٺ_ڏانهن(ثابت حرف *pLayerName, uint32_t *p_Property_ڳڻپ, VkExtensionProperties *pProperties) ثابت {
        أرجع pfn_ايندڙ_Layer(p_ايندڙ_Link, pLayerName, p_Property_ڳڻپ, pProperties);
    }
#جيڪڏهن_پورو
} VkEnumerateInstanceExtensionPropertiesChain;

تعريفنوع بنية VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_سرو سرو;
    Vk_نتيجو(VKAPI_PTR *pfn_ايندڙ_Layer)(ثابت بنية VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ثابت بنية VkEnumerateInstanceLayerPropertiesChain *p_ايندڙ_Link;

#إذا defined(__cplusplus)
    مضمن Vk_نتيجو Call_هيٺ_ڏانهن(uint32_t *p_Property_ڳڻپ, VkLayerProperties *pProperties) ثابت {
        أرجع pfn_ايندڙ_Layer(p_ايندڙ_Link, p_Property_ڳڻپ, pProperties);
    }
#جيڪڏهن_پورو
} VkEnumerateInstanceLayerPropertiesChain;

تعريفنوع بنية Vk_Enumerate_Instance_نسخو_Chain {
    Vk_Chain_سرو سرو;
    Vk_نتيجو(VKAPI_PTR *pfn_ايندڙ_Layer)(ثابت بنية Vk_Enumerate_Instance_نسخو_Chain *, uint32_t *);
    ثابت بنية Vk_Enumerate_Instance_نسخو_Chain *p_ايندڙ_Link;

#إذا defined(__cplusplus)
    مضمن Vk_نتيجو Call_هيٺ_ڏانهن(uint32_t *p_Api_نسخو) ثابت {
        أرجع pfn_ايندڙ_Layer(p_ايندڙ_Link, p_Api_نسخو);
    }
#جيڪڏهن_پورو
} Vk_Enumerate_Instance_نسخو_Chain;

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

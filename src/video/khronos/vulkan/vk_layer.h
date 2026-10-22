/*
 * Copyright 2015-2023 The Khronos Group Inc.
 * Copyright 2015-2023 Valve Corporation
 * Copyright 2015-2023 LunarG, Inc.
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 */
#لارښوونه once

/* Need to define dispatch table
 * Core struct can then have ptr to dispatch table at the top
 * Along with object ptrs for current and next OBJ
 */

#ضمن "vulkan_core.h"

#تعریف_کړه MAX_عدد_UNKNOWN_EXTS 250

 // Loader-Layer version negotiation API.  Versions add the following features:
 //   Versions 0/1 - Initial.  Doesn't support vk_layerGetPhysicalDeviceProcAddr
 //                  or vk_icdNegotiateLoaderLayerInterfaceVersion.
 //   Version 2    - Add support for vk_layerGetPhysicalDeviceProcAddr and
 //                  vk_icdNegotiateLoaderLayerInterfaceVersion.
#تعریف_کړه CURRENT_LOADER_LAYER_INTERFACE_نسخه 2
#تعریف_کړه MIN_SUPPORTED_LOADER_LAYER_INTERFACE_نسخه 1

#تعریف_کړه VK_CURRENT_CHAIN_نسخه 1

// Typedef for use in the interfaces below
#که_نه_تعریف_شوی IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
تعريفنوع PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, ثابت حرف* pName);
#تعریف_کړه IS_DEFINED_PFN_GetPhysicalDeviceProcAddr
#د_که_پای

// Version negotiation values
تعريفنوع تعداد VkNegotiateLayerStructType {
    LAYER_NEGOTIATE_UNINTIALIZED = 0,
    LAYER_NEGOTIATE_INTERFACE_STRUCT = 1,
} VkNegotiateLayerStructType;

// Version negotiation structures
تعريفنوع بنية VkNegotiateLayerInterface {
    VkNegotiateLayerStructType sType;
    فراغ *p_بل;
    uint32_t loader_Layer_Interface_نسخه;
    PFN_vkGetInstanceProcAddr pfnGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr;
    PFN_GetPhysicalDeviceProcAddr pfnGetPhysicalDeviceProcAddr;
} VkNegotiateLayerInterface;

// Version negotiation functions
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_Negotiate_Loader_Layer_Interface_نسخه)(VkNegotiateLayerInterface *p_نسخه_Struct);

// Function prototype for unknown physical device extension command
تعريفنوع Vk_پایله(VKAPI_PTR *PFN_PhysDevExt)(VkPhysicalDevice phys_device);

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
    بنية VkLayerInstanceLink_ *p_بل;
    PFN_vkGetInstanceProcAddr pfn_بل_Get_Instance_Proc_Addr;
    PFN_GetPhysicalDeviceProcAddr pfn_بل_Get_Physical_Device_Proc_Addr;
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
    PFN_vkGetInstanceProcAddr pfn_بل_Get_Instance_Proc_Addr;
} VkLayerDeviceInfo;

تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_سېټ_Instance_Loader_معلومات)(VkInstance instance,
        فراغ *object);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vk_سېټ_Device_Loader_معلومات)(VkDevice device,
        فراغ *object);
تعريفنوع Vk_پایله (VKAPI_PTR *PFN_vkLayerCreateDevice)(VkInstance instance, VkPhysicalDevice physicalDevice, ثابت VkDeviceCreateInfo *pCreateInfo,
						      ثابت Vk_ویش_Callbacks *pAllocator, VkDevice *pDevice, PFN_vkGetInstanceProcAddr layerGIPA, PFN_vkGetDeviceProcAddr *بل_GDPA);
تعريفنوع فراغ (VKAPI_PTR *PFN_vkLayerDestroyDevice)(VkDevice physicalDevice, ثابت Vk_ویش_Callbacks *pAllocator, PFN_vkDestroyDevice destroyFunction);

تعريفنوع تعداد Vk_Loader_Feasture_Flag_بټونه {
    VK_LOADER_FEATURE_PHYSICAL_DEVICE_ترتیبونه = 0x00000001,
} Vk_Loader_Flag_بټونه;
تعريفنوع VkFlags VkLoaderFeatureFlags;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    ثابت فراغ *p_بل;
    VkLayerFunction function;
    اتحاد {
        VkLayerInstanceLink *pLayerInfo;
        PFN_vk_سېټ_Instance_Loader_معلومات pfn_سېټ_Instance_Loader_معلومات;
        بنية {
	        PFN_vkLayerCreateDevice pfnLayerCreateDevice;
	        PFN_vkLayerDestroyDevice pfnLayerDestroyDevice;
	    } layerDevice;
        VkLoaderFeatureFlags loaderFeatures;
    } u;
} VkLayerInstanceCreateInfo;

تعريفنوع بنية VkLayerDeviceLink_ {
    بنية VkLayerDeviceLink_ *p_بل;
    PFN_vkGetInstanceProcAddr pfn_بل_Get_Instance_Proc_Addr;
    PFN_vkGetDeviceProcAddr pfn_بل_Get_Device_Proc_Addr;
} VkLayerDeviceLink;

تعريفنوع بنية {
    VkStructureType sType; // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    ثابت فراغ *p_بل;
    VkLayerFunction function;
    اتحاد {
        VkLayerDeviceLink *pLayerInfo;
        PFN_vk_سېټ_Device_Loader_معلومات pfn_سېټ_Device_Loader_معلومات;
    } u;
} VkLayerDeviceCreateInfo;

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

VKAPI_ATTR Vk_پایله VKAPI_CALL vk_Negotiate_Loader_Layer_Interface_نسخه(VkNegotiateLayerInterface *p_نسخه_Struct);

تعريفنوع تعداد VkChainType {
    VK_CHAIN_TYPE_UNKNOWN = 0,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES = 1,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES = 2,
    VK_CHAIN_TYPE_ENUMERATE_INSTANCE_نسخه = 3,
} VkChainType;

تعريفنوع بنية Vk_Chain_سرلیک {
    VkChainType type;
    uint32_t نسخه;
    uint32_t اندازه;
} Vk_Chain_سرلیک;

تعريفنوع بنية VkEnumerateInstanceExtensionPropertiesChain {
    Vk_Chain_سرلیک سرلیک;
    Vk_پایله(VKAPI_PTR *pfn_بل_Layer)(ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *, ثابت حرف *, uint32_t *,
                                      VkExtensionProperties *);
    ثابت بنية VkEnumerateInstanceExtensionPropertiesChain *p_بل_Link;

#إذا defined(__cplusplus)
    مضمن Vk_پایله Call_ښکته(ثابت حرف *pLayerName, uint32_t *p_Property_شمېر, VkExtensionProperties *pProperties) ثابت {
        أرجع pfn_بل_Layer(p_بل_Link, pLayerName, p_Property_شمېر, pProperties);
    }
#د_که_پای
} VkEnumerateInstanceExtensionPropertiesChain;

تعريفنوع بنية VkEnumerateInstanceLayerPropertiesChain {
    Vk_Chain_سرلیک سرلیک;
    Vk_پایله(VKAPI_PTR *pfn_بل_Layer)(ثابت بنية VkEnumerateInstanceLayerPropertiesChain *, uint32_t *, VkLayerProperties *);
    ثابت بنية VkEnumerateInstanceLayerPropertiesChain *p_بل_Link;

#إذا defined(__cplusplus)
    مضمن Vk_پایله Call_ښکته(uint32_t *p_Property_شمېر, VkLayerProperties *pProperties) ثابت {
        أرجع pfn_بل_Layer(p_بل_Link, p_Property_شمېر, pProperties);
    }
#د_که_پای
} VkEnumerateInstanceLayerPropertiesChain;

تعريفنوع بنية Vk_Enumerate_Instance_نسخه_Chain {
    Vk_Chain_سرلیک سرلیک;
    Vk_پایله(VKAPI_PTR *pfn_بل_Layer)(ثابت بنية Vk_Enumerate_Instance_نسخه_Chain *, uint32_t *);
    ثابت بنية Vk_Enumerate_Instance_نسخه_Chain *p_بل_Link;

#إذا defined(__cplusplus)
    مضمن Vk_پایله Call_ښکته(uint32_t *p_Api_نسخه) ثابت {
        أرجع pfn_بل_Layer(p_بل_Link, p_Api_نسخه);
    }
#د_که_پای
} Vk_Enumerate_Instance_نسخه_Chain;

#که_تعریف_شوی __cplusplus
}
#د_که_پای

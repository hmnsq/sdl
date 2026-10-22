/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vulkan_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VULKAN

ਅਚਲ ਅੱਖਰ *SDL_Vulkan_Get_ਨਤੀਜਾ_String(Vk_ਨਤੀਜਾ ਨਤੀਜਾ)
{
    ਚੋਣ ((ਪੂਰਨ)ਨਤੀਜਾ) {
    ਹਾਲਤ VK_SUCCESS:
        ਵਾਪਸ "VK_SUCCESS";
    ਹਾਲਤ VK_NOT_READY:
        ਵਾਪਸ "VK_NOT_READY";
    ਹਾਲਤ VK_TIMEOUT:
        ਵਾਪਸ "VK_TIMEOUT";
    ਹਾਲਤ VK_EVENT_ਸੈੱਟ:
        ਵਾਪਸ "VK_EVENT_SET";
    ਹਾਲਤ VK_EVENT_RESET:
        ਵਾਪਸ "VK_EVENT_RESET";
    ਹਾਲਤ VK_INCOMPLETE:
        ਵਾਪਸ "VK_INCOMPLETE";
    ਹਾਲਤ VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_HOST_ਸਮ੍ਰਿਤੀ:
        ਵਾਪਸ "VK_ERROR_OUT_OF_HOST_MEMORY";
    ਹਾਲਤ VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_DEVICE_ਸਮ੍ਰਿਤੀ:
        ਵਾਪਸ "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    ਹਾਲਤ VK_ERROR_INITIALIZATION_FAILED:
        ਵਾਪਸ "VK_ERROR_INITIALIZATION_FAILED";
    ਹਾਲਤ VK_ERROR_DEVICE_ਗੁਆਚਾ:
        ਵਾਪਸ "VK_ERROR_DEVICE_LOST";
    ਹਾਲਤ VK_ERROR_ਸਮ੍ਰਿਤੀ_MAP_FAILED:
        ਵਾਪਸ "VK_ERROR_MEMORY_MAP_FAILED";
    ਹਾਲਤ VK_ERROR_LAYER_NOT_PRESENT:
        ਵਾਪਸ "VK_ERROR_LAYER_NOT_PRESENT";
    ਹਾਲਤ VK_ERROR_EXTENSION_NOT_PRESENT:
        ਵਾਪਸ "VK_ERROR_EXTENSION_NOT_PRESENT";
    ਹਾਲਤ VK_ERROR_FEATURE_NOT_PRESENT:
        ਵਾਪਸ "VK_ERROR_FEATURE_NOT_PRESENT";
    ਹਾਲਤ VK_ERROR_INCOMPATIBLE_DRIVER:
        ਵਾਪਸ "VK_ERROR_INCOMPATIBLE_DRIVER";
    ਹਾਲਤ VK_ERROR_TOO_MANY_OBJECTS:
        ਵਾਪਸ "VK_ERROR_TOO_MANY_OBJECTS";
    ਹਾਲਤ VK_ERROR_FORMAT_NOT_SUPPORTED:
        ਵਾਪਸ "VK_ERROR_FORMAT_NOT_SUPPORTED";
    ਹਾਲਤ VK_ERROR_FRAGMENTED_POOL:
        ਵਾਪਸ "VK_ERROR_FRAGMENTED_POOL";
    ਹਾਲਤ VK_ERROR_UNKNOWN:
        ਵਾਪਸ "VK_ERROR_UNKNOWN";
    ਹਾਲਤ VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_POOL_ਸਮ੍ਰਿਤੀ:
        ਵਾਪਸ "VK_ERROR_OUT_OF_POOL_MEMORY";
    ਹਾਲਤ VK_ERROR_INVALID_EXTERNAL_HANDLE:
        ਵਾਪਸ "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    ਹਾਲਤ VK_ERROR_FRAGMENTATION:
        ਵਾਪਸ "VK_ERROR_FRAGMENTATION";
    ਹਾਲਤ VK_ERROR_INVALID_OPAQUE_CAPTURE_ਪਤਾ:
        ਵਾਪਸ "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    ਹਾਲਤ VK_ERROR_SURFACE_ਗੁਆਚਾ_KHR:
        ਵਾਪਸ "VK_ERROR_SURFACE_LOST_KHR";
    ਹਾਲਤ VK_ERROR_NATIVE_ਖਿੜਕੀ_ਵਿੱਚ_USE_KHR:
        ਵਾਪਸ "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    ਹਾਲਤ VK_SUBOPTIMAL_KHR:
        ਵਾਪਸ "VK_SUBOPTIMAL_KHR";
    ਹਾਲਤ VK_ERROR_ਬਾਹਰਲਾ_ਦਾ_DATE_KHR:
        ਵਾਪਸ "VK_ERROR_OUT_OF_DATE_KHR";
    ਹਾਲਤ VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        ਵਾਪਸ "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    ਹਾਲਤ VK_ERROR_VALIDATION_FAILED_EXT:
        ਵਾਪਸ "VK_ERROR_VALIDATION_FAILED_EXT";
    ਹਾਲਤ VK_ERROR_INVALID_SHADER_NV:
        ਵਾਪਸ "VK_ERROR_INVALID_SHADER_NV";
#ਜੇ VK_ਸਿਰਲੇਖ_ਸੰਸਕਰਣ >= 135 && VK_ਸਿਰਲੇਖ_ਸੰਸਕਰਣ < 162
    ਹਾਲਤ VK_ERROR_INCOMPATIBLE_ਸੰਸਕਰਣ_KHR:
        ਵਾਪਸ "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#ਜੇ_ਅੰਤ
    ਹਾਲਤ VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        ਵਾਪਸ "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    ਹਾਲਤ VK_ERROR_NOT_PERMITTED_EXT:
        ਵਾਪਸ "VK_ERROR_NOT_PERMITTED_EXT";
    ਹਾਲਤ VK_ERROR_ਭਰਿਆ_SCREEN_EXCLUSIVE_ਬਹੁਲਕ_ਗੁਆਚਾ_EXT:
        ਵਾਪਸ "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    ਹਾਲਤ VK_THREAD_IDLE_KHR:
        ਵਾਪਸ "VK_THREAD_IDLE_KHR";
    ਹਾਲਤ VK_THREAD_ਪੂਰਾ_KHR:
        ਵਾਪਸ "VK_THREAD_DONE_KHR";
    ਹਾਲਤ VK_OPERATION_DEFERRED_KHR:
        ਵਾਪਸ "VK_OPERATION_DEFERRED_KHR";
    ਹਾਲਤ VK_OPERATION_NOT_DEFERRED_KHR:
        ਵਾਪਸ "VK_OPERATION_NOT_DEFERRED_KHR";
    ਹਾਲਤ VK_PIPELINE_COMPILE_REQUIRED_EXT:
        ਵਾਪਸ "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    ਮੂਲ:
        ਰੋਕੋ;
    }
    ਜੇ (ਨਤੀਜਾ < 0) {
        ਵਾਪਸ "VK_ERROR_<Unknown>";
    }
    ਵਾਪਸ "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ਗਿਣਤੀ)
{
    Uint32 ਗਿਣਤੀ_2 = 0;
    Vk_ਨਤੀਜਾ rc = vkEnumerateInstanceExtensionProperties(ਨਿਰਾ, &ਗਿਣਤੀ_2, ਨਿਰਾ);
    VkExtensionProperties *ਨਤੀਜਾ;

    ਜੇ (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_ਸੈੱਟ_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_ਨਤੀਜਾ_String(rc),
            (ਪੂਰਨ)rc);
        ਵਾਪਸ ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (rc != VK_SUCCESS) {
        SDL_ਸੈੱਟ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ਨਤੀਜਾ_String(rc),
            (ਪੂਰਨ)rc);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (ਗਿਣਤੀ_2 == 0) {
        ਨਤੀਜਾ = (VkExtensionProperties *)SDL_calloc(1, ਆਕਾਰ(VkExtensionProperties)); // so we can return non-null
    } ਨਹੀਂਤਾਂ {
        ਨਤੀਜਾ = (VkExtensionProperties *)SDL_calloc(ਗਿਣਤੀ_2, ਆਕਾਰ(VkExtensionProperties));
    }

    ਜੇ (!ਨਤੀਜਾ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    rc = vkEnumerateInstanceExtensionProperties(ਨਿਰਾ, &ਗਿਣਤੀ_2, ਨਤੀਜਾ);
    ਜੇ (rc != VK_SUCCESS) {
        SDL_ਸੈੱਟ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ਨਤੀਜਾ_String(rc),
            (ਪੂਰਨ)rc);
        SDL_free(ਨਤੀਜਾ);
        ਵਾਪਸ ਨਿਰਾ;
    }
    *extension_ਗਿਣਤੀ = ਗਿਣਤੀ_2;
    ਵਾਪਸ ਨਤੀਜਾ;
}

// Alpha modes, in order of preference
ਸਥਿਰ ਅਚਲ Vk_Display_Plane_Alpha_Flag_ਬਿੱਟ_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,
    VK_DISPLAY_PLANE_ALPHA_ਪ੍ਰਤੀ_PIXEL_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,
    VK_DISPLAY_PLANE_ALPHA_ਪ੍ਰਤੀ_PIXEL_PREMULTIPLIED_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(ਖਾਲੀ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_ਬਹੁਲਕ_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_ਨਤੀਜਾ rc;
    uint32_t physical_Device_ਗਿਣਤੀ = 0;
    VkPhysicalDevice *physicalDevices = ਨਿਰਾ;
    uint32_t physical_Device_ਸੂਚਕਾਂਕ;
    ਅਚਲ ਅੱਖਰ *chosenDisplayId;
    ਪੂਰਨ displayId = 0; // Counting from physical device 0, display 0

    ਜੇ (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_ਬਹੁਲਕ_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_ਸੈੱਟ_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        ਜਾਓ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    ਜੇ (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ਗਿਣਤੀ, ਨਿਰਾ);
    ਜੇ (rc != VK_SUCCESS) {
        SDL_ਸੈੱਟ_Error("Could not enumerate Vulkan physical devices");
        ਜਾਓ error;
    }

    ਜੇ (physical_Device_ਗਿਣਤੀ == 0) {
        SDL_ਸੈੱਟ_Error("No Vulkan physical devices");
        ਜਾਓ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(ਆਕਾਰ(VkPhysicalDevice) * physical_Device_ਗਿਣਤੀ);
    ਜੇ (!physicalDevices) {
        ਜਾਓ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ਗਿਣਤੀ, physicalDevices);
    ਜੇ (rc != VK_SUCCESS) {
        SDL_ਸੈੱਟ_Error("Error enumerating physical devices");
        ਜਾਓ error;
    }

    ਲਈ (physical_Device_ਸੂਚਕਾਂਕ = 0; physical_Device_ਸੂਚਕਾਂਕ < physical_Device_ਗਿਣਤੀ; physical_Device_ਸੂਚਕਾਂਕ++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_ਸੂਚਕਾਂਕ];
        uint32_t display_Properties_ਗਿਣਤੀ = 0;
        VkDisplayPropertiesKHR *displayProperties = ਨਿਰਾ;
        uint32_t display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ = 0;
        Vk_Display_ਬਹੁਲਕ_Properties_KHR *display_ਬਹੁਲਕ_Properties = ਨਿਰਾ;
        ਪੂਰਨ ਉੱਤਮ_ਮੇਲ_ਸੂਚਕਾਂਕ = -1;
        uint32_t refresh_ਦਰ_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_ਗਿਣਤੀ = 0;
        ਪੂਰਨ plane_ਸੂਚਕਾਂਕ = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ਨਿਰਾ;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ਗਿਣਤੀ, ਨਿਰਾ);
        ਜੇ (rc != VK_SUCCESS || display_Properties_ਗਿਣਤੀ == 0) {
            // This device has no physical device display properties, move on to next.
            ਜਾਰੀ;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_ਸੂਚਕਾਂਕ, display_Properties_ਗਿਣਤੀ);

        ਜੇ (displayId < 0 || (uint32_t)displayId >= display_Properties_ਗਿਣਤੀ) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_ਗਿਣਤੀ;
            ਜਾਰੀ;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(ਆਕਾਰ(VkDisplayPropertiesKHR) * display_Properties_ਗਿਣਤੀ);
        ਜੇ (!displayProperties) {
            ਜਾਓ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ਗਿਣਤੀ, displayProperties);
        ਜੇ (rc != VK_SUCCESS || display_Properties_ਗਿਣਤੀ == 0) {
            SDL_free(displayProperties);
            SDL_ਸੈੱਟ_Error("Error enumerating physical device displays");
            ਜਾਓ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.ਚੌੜਾਈ, extent.ਉਚਾਈ);

        SDL_free(displayProperties);
        displayProperties = ਨਿਰਾ;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_ਬਹੁਲਕ_Properties_KHR(physicalDevice, display, &display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ, ਨਿਰਾ);
        ਜੇ (rc != VK_SUCCESS || display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ == 0) {
            SDL_ਸੈੱਟ_Error("Error enumerating display modes");
            ਜਾਓ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ);

        display_ਬਹੁਲਕ_Properties = (Vk_Display_ਬਹੁਲਕ_Properties_KHR *)SDL_malloc(ਆਕਾਰ(Vk_Display_ਬਹੁਲਕ_Properties_KHR) * display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ);
        ਜੇ (!display_ਬਹੁਲਕ_Properties) {
            ਜਾਓ error;
        }

        rc = vk_Get_Display_ਬਹੁਲਕ_Properties_KHR(physicalDevice, display, &display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ, display_ਬਹੁਲਕ_Properties);
        ਜੇ (rc != VK_SUCCESS || display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ == 0) {
            SDL_ਸੈੱਟ_Error("Error enumerating display modes");
            SDL_free(display_ਬਹੁਲਕ_Properties);
            ਜਾਓ error;
        }

        // Try to find a display mode that matches the native resolution
        ਲਈ (i = 0; i < display_ਬਹੁਲਕ_Properties_ਗਿਣਤੀ; ++i) {
            ਜੇ (display_ਬਹੁਲਕ_Properties[i].parameters.visibleRegion.ਚੌੜਾਈ == extent.ਚੌੜਾਈ &&
                display_ਬਹੁਲਕ_Properties[i].parameters.visibleRegion.ਉਚਾਈ == extent.ਉਚਾਈ &&
                display_ਬਹੁਲਕ_Properties[i].parameters.refresh_ਦਰ_2 > refresh_ਦਰ_2) {
                ਉੱਤਮ_ਮੇਲ_ਸੂਚਕਾਂਕ = i;
                refresh_ਦਰ_2 = display_ਬਹੁਲਕ_Properties[i].parameters.refresh_ਦਰ_2;
            }
        }

        ਜੇ (ਉੱਤਮ_ਮੇਲ_ਸੂਚਕਾਂਕ < 0) {
            SDL_ਸੈੱਟ_Error("Found no matching display mode");
            SDL_free(display_ਬਹੁਲਕ_Properties);
            ਜਾਓ error;
        }

        SDL_zero(createInfo);
        createInfo.display_ਬਹੁਲਕ = display_ਬਹੁਲਕ_Properties[ਉੱਤਮ_ਮੇਲ_ਸੂਚਕਾਂਕ].display_ਬਹੁਲਕ;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_ਬਹੁਲਕ_Properties[ਉੱਤਮ_ਮੇਲ_ਸੂਚਕਾਂਕ].parameters.visibleRegion.ਚੌੜਾਈ,
                     display_ਬਹੁਲਕ_Properties[ਉੱਤਮ_ਮੇਲ_ਸੂਚਕਾਂਕ].parameters.visibleRegion.ਉਚਾਈ,
                     refresh_ਦਰ_2);

        SDL_free(display_ਬਹੁਲਕ_Properties);
        display_ਬਹੁਲਕ_Properties = ਨਿਰਾ;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ਗਿਣਤੀ, ਨਿਰਾ);
        ਜੇ (rc != VK_SUCCESS || display_Plane_Properties_ਗਿਣਤੀ == 0) {
            SDL_ਸੈੱਟ_Error("Error enumerating display planes");
            ਜਾਓ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_ਗਿਣਤੀ);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(ਆਕਾਰ(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_ਗਿਣਤੀ);
        ਜੇ (!displayPlaneProperties) {
            ਜਾਓ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ਗਿਣਤੀ, displayPlaneProperties);
        ਜੇ (rc != VK_SUCCESS || display_Plane_Properties_ਗਿਣਤੀ == 0) {
            SDL_ਸੈੱਟ_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            ਜਾਓ error;
        }

        ਲਈ (i = 0; i < display_Plane_Properties_ਗਿਣਤੀ; ++i) {
            uint32_t plane_Supported_Displays_ਗਿਣਤੀ = 0;
            VkDisplayKHR *planeSupportedDisplays = ਨਿਰਾ;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            ਜੇ (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                ਜਾਰੀ;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ਗਿਣਤੀ, ਨਿਰਾ);
            ਜੇ (rc != VK_SUCCESS || plane_Supported_Displays_ਗਿਣਤੀ == 0) {
                ਜਾਰੀ; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_ਗਿਣਤੀ);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(ਆਕਾਰ(VkDisplayKHR) * plane_Supported_Displays_ਗਿਣਤੀ);
            ਜੇ (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                ਜਾਓ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ਗਿਣਤੀ, planeSupportedDisplays);
            ਜੇ (rc != VK_SUCCESS || plane_Supported_Displays_ਗਿਣਤੀ == 0) {
                SDL_ਸੈੱਟ_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                ਜਾਓ error;
            }

            ਲਈ (j = 0; j < plane_Supported_Displays_ਗਿਣਤੀ && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ਨਿਰਾ;

            ਜੇ (j == plane_Supported_Displays_ਗਿਣਤੀ) {
                // This display is not supported for this plane, move on.
                ਜਾਰੀ;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_ਬਹੁਲਕ, i, &planeCaps);
            ਜੇ (rc != VK_SUCCESS) {
                SDL_ਸੈੱਟ_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                ਜਾਓ error;
            }

            // Check if plane fulfills extent requirements.
            ਜੇ (extent.ਚੌੜਾਈ >= planeCaps.minDstExtent.ਚੌੜਾਈ && extent.ਉਚਾਈ >= planeCaps.minDstExtent.ਉਚਾਈ &&
                extent.ਚੌੜਾਈ <= planeCaps.maxDstExtent.ਚੌੜਾਈ && extent.ਉਚਾਈ <= planeCaps.maxDstExtent.ਉਚਾਈ) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.ਚੌੜਾਈ, planeCaps.minDstExtent.ਉਚਾਈ,
                             planeCaps.maxDstExtent.ਚੌੜਾਈ, planeCaps.maxDstExtent.ਉਚਾਈ);
                plane_ਸੂਚਕਾਂਕ = i;
                ਰੋਕੋ;
            }
        }

        ਜੇ (plane_ਸੂਚਕਾਂਕ < 0) {
            SDL_ਸੈੱਟ_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            ਜਾਓ error;
        }

        createInfo.plane_ਸੂਚਕਾਂਕ = plane_ਸੂਚਕਾਂਕ;
        createInfo.plane_ਢੇਰ_ਸੂਚਕਾਂਕ = displayPlaneProperties[plane_ਸੂਚਕਾਂਕ].current_ਢੇਰ_ਸੂਚਕਾਂਕ;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ਨਿਰਾ;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_ਬਹੁਲਕ = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
        ਲਈ (i = 0; i < SDL_arraysize(alphaModes); i++) {
            ਜੇ (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_ਬਹੁਲਕ = alphaModes[i];
                ਰੋਕੋ;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_ਬਹੁਲਕ);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        ਰੋਕੋ;
    }

    SDL_free(physicalDevices);
    physicalDevices = ਨਿਰਾ;

    ਜੇ (physical_Device_ਸੂਚਕਾਂਕ == physical_Device_ਗਿਣਤੀ) {
        SDL_ਸੈੱਟ_Error("No usable displays found or requested display out of range");
        ਜਾਓ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_ਪਛਾਣ_ਤੱਤ_ਦੋਆਧਾਰੀ_ਅੰਕ_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    ਜੇ (rc != VK_SUCCESS) {
        SDL_ਸੈੱਟ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_ਨਤੀਜਾ_String(rc));
        ਜਾਓ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    ਵਾਪਸ true;

error:
    SDL_free(physicalDevices);
    ਵਾਪਸ false;
}

ਖਾਲੀ SDL_Vulkan_Destroy_Surface_ਅੰਦਰੂਨੀ(ਖਾਲੀ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    ਜੇ (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#ਜੇ_ਅੰਤ

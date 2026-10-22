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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "SDL_vulkan_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VULKAN

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(Vk_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ)
{
    ಆಯ್ಕೆ ((ಪೂರ್ಣಾಂಕ)ಫಲಿತಾಂಶ) {
    ಸ್ಥಿತಿ VK_SUCCESS:
        ಹಿಂತಿರುಗಿ "VK_SUCCESS";
    ಸ್ಥಿತಿ VK_NOT_READY:
        ಹಿಂತಿರುಗಿ "VK_NOT_READY";
    ಸ್ಥಿತಿ VK_TIMEOUT:
        ಹಿಂತಿರುಗಿ "VK_TIMEOUT";
    ಸ್ಥಿತಿ VK_EVENT_ಗಣ:
        ಹಿಂತಿರುಗಿ "VK_EVENT_SET";
    ಸ್ಥಿತಿ VK_EVENT_RESET:
        ಹಿಂತಿರುಗಿ "VK_EVENT_RESET";
    ಸ್ಥಿತಿ VK_INCOMPLETE:
        ಹಿಂತಿರುಗಿ "VK_INCOMPLETE";
    ಸ್ಥಿತಿ VK_ERROR_ಹೊರಹೋಗು_ದ_HOST_ಸ್ಮರಣೆ:
        ಹಿಂತಿರುಗಿ "VK_ERROR_OUT_OF_HOST_MEMORY";
    ಸ್ಥಿತಿ VK_ERROR_ಹೊರಹೋಗು_ದ_DEVICE_ಸ್ಮರಣೆ:
        ಹಿಂತಿರುಗಿ "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    ಸ್ಥಿತಿ VK_ERROR_INITIALIZATION_FAILED:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INITIALIZATION_FAILED";
    ಸ್ಥಿತಿ VK_ERROR_DEVICE_ಕಳೆದುಹೋದ:
        ಹಿಂತಿರುಗಿ "VK_ERROR_DEVICE_LOST";
    ಸ್ಥಿತಿ VK_ERROR_ಸ್ಮರಣೆ_MAP_FAILED:
        ಹಿಂತಿರುಗಿ "VK_ERROR_MEMORY_MAP_FAILED";
    ಸ್ಥಿತಿ VK_ERROR_LAYER_NOT_PRESENT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_LAYER_NOT_PRESENT";
    ಸ್ಥಿತಿ VK_ERROR_EXTENSION_NOT_PRESENT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_EXTENSION_NOT_PRESENT";
    ಸ್ಥಿತಿ VK_ERROR_FEATURE_NOT_PRESENT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_FEATURE_NOT_PRESENT";
    ಸ್ಥಿತಿ VK_ERROR_INCOMPATIBLE_DRIVER:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INCOMPATIBLE_DRIVER";
    ಸ್ಥಿತಿ VK_ERROR_TOO_MANY_OBJECTS:
        ಹಿಂತಿರುಗಿ "VK_ERROR_TOO_MANY_OBJECTS";
    ಸ್ಥಿತಿ VK_ERROR_FORMAT_NOT_SUPPORTED:
        ಹಿಂತಿರುಗಿ "VK_ERROR_FORMAT_NOT_SUPPORTED";
    ಸ್ಥಿತಿ VK_ERROR_FRAGMENTED_POOL:
        ಹಿಂತಿರುಗಿ "VK_ERROR_FRAGMENTED_POOL";
    ಸ್ಥಿತಿ VK_ERROR_UNKNOWN:
        ಹಿಂತಿರುಗಿ "VK_ERROR_UNKNOWN";
    ಸ್ಥಿತಿ VK_ERROR_ಹೊರಹೋಗು_ದ_POOL_ಸ್ಮರಣೆ:
        ಹಿಂತಿರುಗಿ "VK_ERROR_OUT_OF_POOL_MEMORY";
    ಸ್ಥಿತಿ VK_ERROR_INVALID_EXTERNAL_HANDLE:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    ಸ್ಥಿತಿ VK_ERROR_FRAGMENTATION:
        ಹಿಂತಿರುಗಿ "VK_ERROR_FRAGMENTATION";
    ಸ್ಥಿತಿ VK_ERROR_INVALID_OPAQUE_CAPTURE_ವಿಳಾಸ:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    ಸ್ಥಿತಿ VK_ERROR_SURFACE_ಕಳೆದುಹೋದ_KHR:
        ಹಿಂತಿರುಗಿ "VK_ERROR_SURFACE_LOST_KHR";
    ಸ್ಥಿತಿ VK_ERROR_NATIVE_ಕಿಟಕಿ_ಒಳ_USE_KHR:
        ಹಿಂತಿರುಗಿ "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    ಸ್ಥಿತಿ VK_SUBOPTIMAL_KHR:
        ಹಿಂತಿರುಗಿ "VK_SUBOPTIMAL_KHR";
    ಸ್ಥಿತಿ VK_ERROR_ಹೊರಹೋಗು_ದ_DATE_KHR:
        ಹಿಂತಿರುಗಿ "VK_ERROR_OUT_OF_DATE_KHR";
    ಸ್ಥಿತಿ VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    ಸ್ಥಿತಿ VK_ERROR_VALIDATION_FAILED_EXT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_VALIDATION_FAILED_EXT";
    ಸ್ಥಿತಿ VK_ERROR_INVALID_SHADER_NV:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INVALID_SHADER_NV";
#ಆದರೆ VK_ಶೀರ್ಷಿಕೆ_ಆವೃತ್ತಿ >= 135 && VK_ಶೀರ್ಷಿಕೆ_ಆವೃತ್ತಿ < 162
    ಸ್ಥಿತಿ VK_ERROR_INCOMPATIBLE_ಆವೃತ್ತಿ_KHR:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    ಸ್ಥಿತಿ VK_ERROR_NOT_PERMITTED_EXT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_NOT_PERMITTED_EXT";
    ಸ್ಥಿತಿ VK_ERROR_ತುಂಬಿದ_SCREEN_EXCLUSIVE_ಬಹುಲಕ_ಕಳೆದುಹೋದ_EXT:
        ಹಿಂತಿರುಗಿ "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    ಸ್ಥಿತಿ VK_THREAD_IDLE_KHR:
        ಹಿಂತಿರುಗಿ "VK_THREAD_IDLE_KHR";
    ಸ್ಥಿತಿ VK_THREAD_ಮುಗಿದ_KHR:
        ಹಿಂತಿರುಗಿ "VK_THREAD_DONE_KHR";
    ಸ್ಥಿತಿ VK_OPERATION_DEFERRED_KHR:
        ಹಿಂತಿರುಗಿ "VK_OPERATION_DEFERRED_KHR";
    ಸ್ಥಿತಿ VK_OPERATION_NOT_DEFERRED_KHR:
        ಹಿಂತಿರುಗಿ "VK_OPERATION_NOT_DEFERRED_KHR";
    ಸ್ಥಿತಿ VK_PIPELINE_COMPILE_REQUIRED_EXT:
        ಹಿಂತಿರುಗಿ "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (ಫಲಿತಾಂಶ < 0) {
        ಹಿಂತಿರುಗಿ "VK_ERROR_<Unknown>";
    }
    ಹಿಂತಿರುಗಿ "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ಎಣಿಕೆ)
{
    Uint32 ಎಣಿಕೆ_2 = 0;
    Vk_ಫಲಿತಾಂಶ rc = vkEnumerateInstanceExtensionProperties(ಖಾಲಿ, &ಎಣಿಕೆ_2, ಖಾಲಿ);
    VkExtensionProperties *ಫಲಿತಾಂಶ;

    ಆದರೆ (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_ಗಣ_Error(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(rc),
            (ಪೂರ್ಣಾಂಕ)rc);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rc != VK_SUCCESS) {
        SDL_ಗಣ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(rc),
            (ಪೂರ್ಣಾಂಕ)rc);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (ಎಣಿಕೆ_2 == 0) {
        ಫಲಿತಾಂಶ = (VkExtensionProperties *)SDL_calloc(1, ಗಾತ್ರ(VkExtensionProperties)); // so we can return non-null
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಫಲಿತಾಂಶ = (VkExtensionProperties *)SDL_calloc(ಎಣಿಕೆ_2, ಗಾತ್ರ(VkExtensionProperties));
    }

    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    rc = vkEnumerateInstanceExtensionProperties(ಖಾಲಿ, &ಎಣಿಕೆ_2, ಫಲಿತಾಂಶ);
    ಆದರೆ (rc != VK_SUCCESS) {
        SDL_ಗಣ_Error(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(rc),
            (ಪೂರ್ಣಾಂಕ)rc);
        SDL_free(ಫಲಿತಾಂಶ);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    *extension_ಎಣಿಕೆ = ಎಣಿಕೆ_2;
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

// Alpha modes, in order of preference
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Vk_Display_Plane_Alpha_Flag_ಬಿಟ್ಟುಗಳು_KHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_ಬಿಟ್_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_ಬಿಟ್_KHR,
    VK_DISPLAY_PLANE_ALPHA_ಪ್ರತಿ_PIXEL_ಬಿಟ್_KHR,
    VK_DISPLAY_PLANE_ALPHA_ಪ್ರತಿ_PIXEL_PREMULTIPLIED_ಬಿಟ್_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(ಶೂನ್ಯ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#ವ್ಯಾಖ್ಯಾನಿಸು VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vk_Get_Display_ಬಹುಲಕ_Properties_KHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    Vk_ಫಲಿತಾಂಶ rc;
    uint32_t physical_Device_ಎಣಿಕೆ = 0;
    VkPhysicalDevice *physicalDevices = ಖಾಲಿ;
    uint32_t physical_Device_ಸೂಚ್ಯಂಕ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *chosenDisplayId;
    ಪೂರ್ಣಾಂಕ displayId = 0; // Counting from physical device 0, display 0

    ಆದರೆ (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vk_Get_Display_ಬಹುಲಕ_Properties_KHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_ಗಣ_Error(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        ಹೋಗು error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    ಆದರೆ (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ಎಣಿಕೆ, ಖಾಲಿ);
    ಆದರೆ (rc != VK_SUCCESS) {
        SDL_ಗಣ_Error("Could not enumerate Vulkan physical devices");
        ಹೋಗು error;
    }

    ಆದರೆ (physical_Device_ಎಣಿಕೆ == 0) {
        SDL_ಗಣ_Error("No Vulkan physical devices");
        ಹೋಗು error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(ಗಾತ್ರ(VkPhysicalDevice) * physical_Device_ಎಣಿಕೆ);
    ಆದರೆ (!physicalDevices) {
        ಹೋಗು error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ಎಣಿಕೆ, physicalDevices);
    ಆದರೆ (rc != VK_SUCCESS) {
        SDL_ಗಣ_Error("Error enumerating physical devices");
        ಹೋಗು error;
    }

    ಗಾಗಿ (physical_Device_ಸೂಚ್ಯಂಕ = 0; physical_Device_ಸೂಚ್ಯಂಕ < physical_Device_ಎಣಿಕೆ; physical_Device_ಸೂಚ್ಯಂಕ++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_ಸೂಚ್ಯಂಕ];
        uint32_t display_Properties_ಎಣಿಕೆ = 0;
        VkDisplayPropertiesKHR *displayProperties = ಖಾಲಿ;
        uint32_t display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ = 0;
        Vk_Display_ಬಹುಲಕ_Properties_KHR *display_ಬಹುಲಕ_Properties = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ ಉತ್ತಮ_ಹೊಂದಿಕೆ_ಸೂಚ್ಯಂಕ = -1;
        uint32_t refresh_ದರ_2 = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_ಎಣಿಕೆ = 0;
        ಪೂರ್ಣಾಂಕ plane_ಸೂಚ್ಯಂಕ = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ಖಾಲಿ;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ಎಣಿಕೆ, ಖಾಲಿ);
        ಆದರೆ (rc != VK_SUCCESS || display_Properties_ಎಣಿಕೆ == 0) {
            // This device has no physical device display properties, move on to next.
            ಮುಂದುವರಿ;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_ಸೂಚ್ಯಂಕ, display_Properties_ಎಣಿಕೆ);

        ಆದರೆ (displayId < 0 || (uint32_t)displayId >= display_Properties_ಎಣಿಕೆ) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_ಎಣಿಕೆ;
            ಮುಂದುವರಿ;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(ಗಾತ್ರ(VkDisplayPropertiesKHR) * display_Properties_ಎಣಿಕೆ);
        ಆದರೆ (!displayProperties) {
            ಹೋಗು error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ಎಣಿಕೆ, displayProperties);
        ಆದರೆ (rc != VK_SUCCESS || display_Properties_ಎಣಿಕೆ == 0) {
            SDL_free(displayProperties);
            SDL_ಗಣ_Error("Error enumerating physical device displays");
            ಹೋಗು error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.ಅಗಲ, extent.ಎತ್ತರ);

        SDL_free(displayProperties);
        displayProperties = ಖಾಲಿ;

        // Get display mode properties for the chosen display
        rc = vk_Get_Display_ಬಹುಲಕ_Properties_KHR(physicalDevice, display, &display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ, ಖಾಲಿ);
        ಆದರೆ (rc != VK_SUCCESS || display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ == 0) {
            SDL_ಗಣ_Error("Error enumerating display modes");
            ಹೋಗು error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ);

        display_ಬಹುಲಕ_Properties = (Vk_Display_ಬಹುಲಕ_Properties_KHR *)SDL_malloc(ಗಾತ್ರ(Vk_Display_ಬಹುಲಕ_Properties_KHR) * display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ);
        ಆದರೆ (!display_ಬಹುಲಕ_Properties) {
            ಹೋಗು error;
        }

        rc = vk_Get_Display_ಬಹುಲಕ_Properties_KHR(physicalDevice, display, &display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ, display_ಬಹುಲಕ_Properties);
        ಆದರೆ (rc != VK_SUCCESS || display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ == 0) {
            SDL_ಗಣ_Error("Error enumerating display modes");
            SDL_free(display_ಬಹುಲಕ_Properties);
            ಹೋಗು error;
        }

        // Try to find a display mode that matches the native resolution
        ಗಾಗಿ (i = 0; i < display_ಬಹುಲಕ_Properties_ಎಣಿಕೆ; ++i) {
            ಆದರೆ (display_ಬಹುಲಕ_Properties[i].parameters.visibleRegion.ಅಗಲ == extent.ಅಗಲ &&
                display_ಬಹುಲಕ_Properties[i].parameters.visibleRegion.ಎತ್ತರ == extent.ಎತ್ತರ &&
                display_ಬಹುಲಕ_Properties[i].parameters.refresh_ದರ_2 > refresh_ದರ_2) {
                ಉತ್ತಮ_ಹೊಂದಿಕೆ_ಸೂಚ್ಯಂಕ = i;
                refresh_ದರ_2 = display_ಬಹುಲಕ_Properties[i].parameters.refresh_ದರ_2;
            }
        }

        ಆದರೆ (ಉತ್ತಮ_ಹೊಂದಿಕೆ_ಸೂಚ್ಯಂಕ < 0) {
            SDL_ಗಣ_Error("Found no matching display mode");
            SDL_free(display_ಬಹುಲಕ_Properties);
            ಹೋಗು error;
        }

        SDL_zero(createInfo);
        createInfo.display_ಬಹುಲಕ = display_ಬಹುಲಕ_Properties[ಉತ್ತಮ_ಹೊಂದಿಕೆ_ಸೂಚ್ಯಂಕ].display_ಬಹುಲಕ;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     display_ಬಹುಲಕ_Properties[ಉತ್ತಮ_ಹೊಂದಿಕೆ_ಸೂಚ್ಯಂಕ].parameters.visibleRegion.ಅಗಲ,
                     display_ಬಹುಲಕ_Properties[ಉತ್ತಮ_ಹೊಂದಿಕೆ_ಸೂಚ್ಯಂಕ].parameters.visibleRegion.ಎತ್ತರ,
                     refresh_ದರ_2);

        SDL_free(display_ಬಹುಲಕ_Properties);
        display_ಬಹುಲಕ_Properties = ಖಾಲಿ;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ಎಣಿಕೆ, ಖಾಲಿ);
        ಆದರೆ (rc != VK_SUCCESS || display_Plane_Properties_ಎಣಿಕೆ == 0) {
            SDL_ಗಣ_Error("Error enumerating display planes");
            ಹೋಗು error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_ಎಣಿಕೆ);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(ಗಾತ್ರ(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_ಎಣಿಕೆ);
        ಆದರೆ (!displayPlaneProperties) {
            ಹೋಗು error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ಎಣಿಕೆ, displayPlaneProperties);
        ಆದರೆ (rc != VK_SUCCESS || display_Plane_Properties_ಎಣಿಕೆ == 0) {
            SDL_ಗಣ_Error("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            ಹೋಗು error;
        }

        ಗಾಗಿ (i = 0; i < display_Plane_Properties_ಎಣಿಕೆ; ++i) {
            uint32_t plane_Supported_Displays_ಎಣಿಕೆ = 0;
            VkDisplayKHR *planeSupportedDisplays = ಖಾಲಿ;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            ಆದರೆ (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                ಮುಂದುವರಿ;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ಎಣಿಕೆ, ಖಾಲಿ);
            ಆದರೆ (rc != VK_SUCCESS || plane_Supported_Displays_ಎಣಿಕೆ == 0) {
                ಮುಂದುವರಿ; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_ಎಣಿಕೆ);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(ಗಾತ್ರ(VkDisplayKHR) * plane_Supported_Displays_ಎಣಿಕೆ);
            ಆದರೆ (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                ಹೋಗು error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ಎಣಿಕೆ, planeSupportedDisplays);
            ಆದರೆ (rc != VK_SUCCESS || plane_Supported_Displays_ಎಣಿಕೆ == 0) {
                SDL_ಗಣ_Error("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                ಹೋಗು error;
            }

            ಗಾಗಿ (j = 0; j < plane_Supported_Displays_ಎಣಿಕೆ && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ಖಾಲಿ;

            ಆದರೆ (j == plane_Supported_Displays_ಎಣಿಕೆ) {
                // This display is not supported for this plane, move on.
                ಮುಂದುವರಿ;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.display_ಬಹುಲಕ, i, &planeCaps);
            ಆದರೆ (rc != VK_SUCCESS) {
                SDL_ಗಣ_Error("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                ಹೋಗು error;
            }

            // Check if plane fulfills extent requirements.
            ಆದರೆ (extent.ಅಗಲ >= planeCaps.minDstExtent.ಅಗಲ && extent.ಎತ್ತರ >= planeCaps.minDstExtent.ಎತ್ತರ &&
                extent.ಅಗಲ <= planeCaps.maxDstExtent.ಅಗಲ && extent.ಎತ್ತರ <= planeCaps.maxDstExtent.ಎತ್ತರ) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.ಅಗಲ, planeCaps.minDstExtent.ಎತ್ತರ,
                             planeCaps.maxDstExtent.ಅಗಲ, planeCaps.maxDstExtent.ಎತ್ತರ);
                plane_ಸೂಚ್ಯಂಕ = i;
                ನಿಲ್ಲಿಸು;
            }
        }

        ಆದರೆ (plane_ಸೂಚ್ಯಂಕ < 0) {
            SDL_ಗಣ_Error("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            ಹೋಗು error;
        }

        createInfo.plane_ಸೂಚ್ಯಂಕ = plane_ಸೂಚ್ಯಂಕ;
        createInfo.plane_ರಾಶಿ_ಸೂಚ್ಯಂಕ = displayPlaneProperties[plane_ಸೂಚ್ಯಂಕ].current_ರಾಶಿ_ಸೂಚ್ಯಂಕ;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ಖಾಲಿ;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alpha_ಬಹುಲಕ = VK_DISPLAY_PLANE_ALPHA_OPAQUE_ಬಿಟ್_KHR;
        ಗಾಗಿ (i = 0; i < SDL_arraysize(alphaModes); i++) {
            ಆದರೆ (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alpha_ಬಹುಲಕ = alphaModes[i];
                ನಿಲ್ಲಿಸು;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alpha_ಬಹುಲಕ);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        ನಿಲ್ಲಿಸು;
    }

    SDL_free(physicalDevices);
    physicalDevices = ಖಾಲಿ;

    ಆದರೆ (physical_Device_ಸೂಚ್ಯಂಕ == physical_Device_ಎಣಿಕೆ) {
        SDL_ಗಣ_Error("No usable displays found or requested display out of range");
        ಹೋಗು error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_ತಟಸ್ಥ_ಬಿಟ್_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    ಆದರೆ (rc != VK_SUCCESS) {
        SDL_ಗಣ_Error("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_ಫಲಿತಾಂಶ_String(rc));
        ಹೋಗು error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    ಹಿಂತಿರುಗಿ true;

error:
    SDL_free(physicalDevices);
    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ SDL_Vulkan_Destroy_Surface_ಆಂತರಿಕ(ಶೂನ್ಯ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    ಆದರೆ (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#ಆದರೆ_ಅಂತ್ಯ

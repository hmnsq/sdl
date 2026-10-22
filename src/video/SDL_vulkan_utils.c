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

#ifdef SDL_VIDEO_VULKAN

ಧ್ರುವ ವರ್ಣ *SDL_Vulkan_GetResultString(VkResult result)
{
    ವಿಕಲ್ಪ ((ಪೂರ್ಣಾಙ್ಕ)result) {
    ಪಕ್ಷ VK_SUCCESS:
        ಪ್ರತ್ಯಾಗಮ "VK_SUCCESS";
    ಪಕ್ಷ VK_NOT_READY:
        ಪ್ರತ್ಯಾಗಮ "VK_NOT_READY";
    ಪಕ್ಷ VK_TIMEOUT:
        ಪ್ರತ್ಯಾಗಮ "VK_TIMEOUT";
    ಪಕ್ಷ VK_EVENT_SET:
        ಪ್ರತ್ಯಾಗಮ "VK_EVENT_SET";
    ಪಕ್ಷ VK_EVENT_RESET:
        ಪ್ರತ್ಯಾಗಮ "VK_EVENT_RESET";
    ಪಕ್ಷ VK_INCOMPLETE:
        ಪ್ರತ್ಯಾಗಮ "VK_INCOMPLETE";
    ಪಕ್ಷ VK_ERROR_OUT_OF_HOST_MEMORY:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_OUT_OF_HOST_MEMORY";
    ಪಕ್ಷ VK_ERROR_OUT_OF_DEVICE_MEMORY:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    ಪಕ್ಷ VK_ERROR_INITIALIZATION_FAILED:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INITIALIZATION_FAILED";
    ಪಕ್ಷ VK_ERROR_DEVICE_LOST:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_DEVICE_LOST";
    ಪಕ್ಷ VK_ERROR_MEMORY_MAP_FAILED:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_MEMORY_MAP_FAILED";
    ಪಕ್ಷ VK_ERROR_LAYER_NOT_PRESENT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_LAYER_NOT_PRESENT";
    ಪಕ್ಷ VK_ERROR_EXTENSION_NOT_PRESENT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_EXTENSION_NOT_PRESENT";
    ಪಕ್ಷ VK_ERROR_FEATURE_NOT_PRESENT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_FEATURE_NOT_PRESENT";
    ಪಕ್ಷ VK_ERROR_INCOMPATIBLE_DRIVER:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INCOMPATIBLE_DRIVER";
    ಪಕ್ಷ VK_ERROR_TOO_MANY_OBJECTS:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_TOO_MANY_OBJECTS";
    ಪಕ್ಷ VK_ERROR_FORMAT_NOT_SUPPORTED:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_FORMAT_NOT_SUPPORTED";
    ಪಕ್ಷ VK_ERROR_FRAGMENTED_POOL:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_FRAGMENTED_POOL";
    ಪಕ್ಷ VK_ERROR_UNKNOWN:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_UNKNOWN";
    ಪಕ್ಷ VK_ERROR_OUT_OF_POOL_MEMORY:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_OUT_OF_POOL_MEMORY";
    ಪಕ್ಷ VK_ERROR_INVALID_EXTERNAL_HANDLE:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    ಪಕ್ಷ VK_ERROR_FRAGMENTATION:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_FRAGMENTATION";
    ಪಕ್ಷ VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    ಪಕ್ಷ VK_ERROR_SURFACE_LOST_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_SURFACE_LOST_KHR";
    ಪಕ್ಷ VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    ಪಕ್ಷ VK_SUBOPTIMAL_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_SUBOPTIMAL_KHR";
    ಪಕ್ಷ VK_ERROR_OUT_OF_DATE_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_OUT_OF_DATE_KHR";
    ಪಕ್ಷ VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    ಪಕ್ಷ VK_ERROR_VALIDATION_FAILED_EXT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_VALIDATION_FAILED_EXT";
    ಪಕ್ಷ VK_ERROR_INVALID_SHADER_NV:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INVALID_SHADER_NV";
#ಯದಿ VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    ಪಕ್ಷ VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    ಪಕ್ಷ VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    ಪಕ್ಷ VK_ERROR_NOT_PERMITTED_EXT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_NOT_PERMITTED_EXT";
    ಪಕ್ಷ VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    ಪಕ್ಷ VK_THREAD_IDLE_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_THREAD_IDLE_KHR";
    ಪಕ್ಷ VK_THREAD_DONE_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_THREAD_DONE_KHR";
    ಪಕ್ಷ VK_OPERATION_DEFERRED_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_OPERATION_DEFERRED_KHR";
    ಪಕ್ಷ VK_OPERATION_NOT_DEFERRED_KHR:
        ಪ್ರತ್ಯಾಗಮ "VK_OPERATION_NOT_DEFERRED_KHR";
    ಪಕ್ಷ VK_PIPELINE_COMPILE_REQUIRED_EXT:
        ಪ್ರತ್ಯಾಗಮ "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
    ಯದಿ (result < 0) {
        ಪ್ರತ್ಯಾಗಮ "VK_ERROR_<Unknown>";
    }
    ಪ್ರತ್ಯಾಗಮ "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ಎಣಿಕೆ)
{
    Uint32 ಎಣಿಕೆ = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(ರಿಕ್ತ, &ಎಣಿಕೆ, ರಿಕ್ತ);
    VkExtensionProperties *result;

    ಯದಿ (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (ಪೂರ್ಣಾಙ್ಕ)rc);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    } ಅನ್ಯಥಾ ಯದಿ (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (ಪೂರ್ಣಾಙ್ಕ)rc);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (ಎಣಿಕೆ == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, ಪರಿಮಾಣ(VkExtensionProperties)); // so we can return non-null
    } ಅನ್ಯಥಾ {
        result = (VkExtensionProperties *)SDL_calloc(ಎಣಿಕೆ, ಪರಿಮಾಣ(VkExtensionProperties));
    }

    ಯದಿ (!result) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    rc = vkEnumerateInstanceExtensionProperties(ರಿಕ್ತ, &ಎಣಿಕೆ, result);
    ಯದಿ (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (ಪೂರ್ಣಾಙ್ಕ)rc);
        SDL_free(result);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    *extension_ಎಣಿಕೆ = ಎಣಿಕೆ;
    ಪ್ರತ್ಯಾಗಮ result;
}

// Alpha modes, in order of preference
ಸ್ಥಿರ ಧ್ರುವ VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(ಶೂನ್ಯ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator,
                                      VkSurfaceKHR *surface)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
#define VULKAN_INSTANCE_FUNCTION(name) \
    PFN_##name name = (PFN_##name)vkGetInstanceProcAddr((VkInstance)instance, #name)
    VULKAN_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayModePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR);
    VULKAN_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR);
    VULKAN_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR);
#undef VULKAN_INSTANCE_FUNCTION
    VkDisplaySurfaceCreateInfoKHR createInfo;
    VkResult rc;
    uint32_t physical_Device_ಎಣಿಕೆ = 0;
    VkPhysicalDevice *physicalDevices = ರಿಕ್ತ;
    uint32_t physicalDeviceIndex;
    ಧ್ರುವ ವರ್ಣ *chosenDisplayId;
    ಪೂರ್ಣಾಙ್ಕ displayId = 0; // Counting from physical device 0, display 0

    ಯದಿ (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        ಗಚ್ಛ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    ಯದಿ (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ಎಣಿಕೆ, ರಿಕ್ತ);
    ಯದಿ (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        ಗಚ್ಛ error;
    }

    ಯದಿ (physical_Device_ಎಣಿಕೆ == 0) {
        SDL_SetError("No Vulkan physical devices");
        ಗಚ್ಛ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(ಪರಿಮಾಣ(VkPhysicalDevice) * physical_Device_ಎಣಿಕೆ);
    ಯದಿ (!physicalDevices) {
        ಗಚ್ಛ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ಎಣಿಕೆ, physicalDevices);
    ಯದಿ (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        ಗಚ್ಛ error;
    }

    ಪ್ರತಿ (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_ಎಣಿಕೆ; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_ಎಣಿಕೆ = 0;
        VkDisplayPropertiesKHR *displayProperties = ರಿಕ್ತ;
        uint32_t display_Mode_Properties_ಎಣಿಕೆ = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = ರಿಕ್ತ;
        ಪೂರ್ಣಾಙ್ಕ bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_ಎಣಿಕೆ = 0;
        ಪೂರ್ಣಾಙ್ಕ planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ರಿಕ್ತ;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ಎಣಿಕೆ, ರಿಕ್ತ);
        ಯದಿ (rc != VK_SUCCESS || display_Properties_ಎಣಿಕೆ == 0) {
            // This device has no physical device display properties, move on to next.
            ಅನುವರ್ತ;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_ಎಣಿಕೆ);

        ಯದಿ (displayId < 0 || (uint32_t)displayId >= display_Properties_ಎಣಿಕೆ) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_ಎಣಿಕೆ;
            ಅನುವರ್ತ;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(ಪರಿಮಾಣ(VkDisplayPropertiesKHR) * display_Properties_ಎಣಿಕೆ);
        ಯದಿ (!displayProperties) {
            ಗಚ್ಛ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ಎಣಿಕೆ, displayProperties);
        ಯದಿ (rc != VK_SUCCESS || display_Properties_ಎಣಿಕೆ == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            ಗಚ್ಛ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = ರಿಕ್ತ;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_ಎಣಿಕೆ, ರಿಕ್ತ);
        ಯದಿ (rc != VK_SUCCESS || display_Mode_Properties_ಎಣಿಕೆ == 0) {
            SDL_SetError("Error enumerating display modes");
            ಗಚ್ಛ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_ಎಣಿಕೆ);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(ಪರಿಮಾಣ(VkDisplayModePropertiesKHR) * display_Mode_Properties_ಎಣಿಕೆ);
        ಯದಿ (!displayModeProperties) {
            ಗಚ್ಛ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_ಎಣಿಕೆ, displayModeProperties);
        ಯದಿ (rc != VK_SUCCESS || display_Mode_Properties_ಎಣಿಕೆ == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            ಗಚ್ಛ error;
        }

        // Try to find a display mode that matches the native resolution
        ಪ್ರತಿ (i = 0; i < display_Mode_Properties_ಎಣಿಕೆ; ++i) {
            ಯದಿ (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        ಯದಿ (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            ಗಚ್ಛ error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = ರಿಕ್ತ;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ಎಣಿಕೆ, ರಿಕ್ತ);
        ಯದಿ (rc != VK_SUCCESS || display_Plane_Properties_ಎಣಿಕೆ == 0) {
            SDL_SetError("Error enumerating display planes");
            ಗಚ್ಛ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_ಎಣಿಕೆ);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(ಪರಿಮಾಣ(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_ಎಣಿಕೆ);
        ಯದಿ (!displayPlaneProperties) {
            ಗಚ್ಛ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ಎಣಿಕೆ, displayPlaneProperties);
        ಯದಿ (rc != VK_SUCCESS || display_Plane_Properties_ಎಣಿಕೆ == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            ಗಚ್ಛ error;
        }

        ಪ್ರತಿ (i = 0; i < display_Plane_Properties_ಎಣಿಕೆ; ++i) {
            uint32_t plane_Supported_Displays_ಎಣಿಕೆ = 0;
            VkDisplayKHR *planeSupportedDisplays = ರಿಕ್ತ;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            ಯದಿ (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                ಅನುವರ್ತ;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ಎಣಿಕೆ, ರಿಕ್ತ);
            ಯದಿ (rc != VK_SUCCESS || plane_Supported_Displays_ಎಣಿಕೆ == 0) {
                ಅನುವರ್ತ; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_ಎಣಿಕೆ);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(ಪರಿಮಾಣ(VkDisplayKHR) * plane_Supported_Displays_ಎಣಿಕೆ);
            ಯದಿ (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                ಗಚ್ಛ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ಎಣಿಕೆ, planeSupportedDisplays);
            ಯದಿ (rc != VK_SUCCESS || plane_Supported_Displays_ಎಣಿಕೆ == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                ಗಚ್ಛ error;
            }

            ಪ್ರತಿ (j = 0; j < plane_Supported_Displays_ಎಣಿಕೆ && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ರಿಕ್ತ;

            ಯದಿ (j == plane_Supported_Displays_ಎಣಿಕೆ) {
                // This display is not supported for this plane, move on.
                ಅನುವರ್ತ;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            ಯದಿ (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                ಗಚ್ಛ error;
            }

            // Check if plane fulfills extent requirements.
            ಯದಿ (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                ಭಙ್ಗ;
            }
        }

        ಯದಿ (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            ಗಚ್ಛ error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_ರಾಶಿ_Index = displayPlaneProperties[planeIndex].current_ರಾಶಿ_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ರಿಕ್ತ;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        ಪ್ರತಿ (i = 0; i < SDL_arraysize(alphaModes); i++) {
            ಯದಿ (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                ಭಙ್ಗ;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        ಭಙ್ಗ;
    }

    SDL_free(physicalDevices);
    physicalDevices = ರಿಕ್ತ;

    ಯದಿ (physicalDeviceIndex == physical_Device_ಎಣಿಕೆ) {
        SDL_SetError("No usable displays found or requested display out of range");
        ಗಚ್ಛ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    ಯದಿ (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        ಗಚ್ಛ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    ಪ್ರತ್ಯಾಗಮ true;

error:
    SDL_free(physicalDevices);
    ಪ್ರತ್ಯಾಗಮ false;
}

ಶೂನ್ಯ SDL_Vulkan_DestroySurface_Internal(ಶೂನ್ಯ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    ಯದಿ (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

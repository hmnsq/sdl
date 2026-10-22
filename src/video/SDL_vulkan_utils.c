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
#அந்தர்பாவ "SDL_internal.h"

#அந்தர்பாவ "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

மாறிலி எழுத்து *SDL_Vulkan_GetResultString(VkResult result)
{
    தேர்வு ((முழு)result) {
    நிலை VK_SUCCESS:
        திரும்பு "VK_SUCCESS";
    நிலை VK_NOT_READY:
        திரும்பு "VK_NOT_READY";
    நிலை VK_TIMEOUT:
        திரும்பு "VK_TIMEOUT";
    நிலை VK_EVENT_SET:
        திரும்பு "VK_EVENT_SET";
    நிலை VK_EVENT_RESET:
        திரும்பு "VK_EVENT_RESET";
    நிலை VK_INCOMPLETE:
        திரும்பு "VK_INCOMPLETE";
    நிலை VK_ERROR_OUT_OF_HOST_MEMORY:
        திரும்பு "VK_ERROR_OUT_OF_HOST_MEMORY";
    நிலை VK_ERROR_OUT_OF_DEVICE_MEMORY:
        திரும்பு "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    நிலை VK_ERROR_INITIALIZATION_FAILED:
        திரும்பு "VK_ERROR_INITIALIZATION_FAILED";
    நிலை VK_ERROR_DEVICE_LOST:
        திரும்பு "VK_ERROR_DEVICE_LOST";
    நிலை VK_ERROR_MEMORY_MAP_FAILED:
        திரும்பு "VK_ERROR_MEMORY_MAP_FAILED";
    நிலை VK_ERROR_LAYER_NOT_PRESENT:
        திரும்பு "VK_ERROR_LAYER_NOT_PRESENT";
    நிலை VK_ERROR_EXTENSION_NOT_PRESENT:
        திரும்பு "VK_ERROR_EXTENSION_NOT_PRESENT";
    நிலை VK_ERROR_FEATURE_NOT_PRESENT:
        திரும்பு "VK_ERROR_FEATURE_NOT_PRESENT";
    நிலை VK_ERROR_INCOMPATIBLE_DRIVER:
        திரும்பு "VK_ERROR_INCOMPATIBLE_DRIVER";
    நிலை VK_ERROR_TOO_MANY_OBJECTS:
        திரும்பு "VK_ERROR_TOO_MANY_OBJECTS";
    நிலை VK_ERROR_FORMAT_NOT_SUPPORTED:
        திரும்பு "VK_ERROR_FORMAT_NOT_SUPPORTED";
    நிலை VK_ERROR_FRAGMENTED_POOL:
        திரும்பு "VK_ERROR_FRAGMENTED_POOL";
    நிலை VK_ERROR_UNKNOWN:
        திரும்பு "VK_ERROR_UNKNOWN";
    நிலை VK_ERROR_OUT_OF_POOL_MEMORY:
        திரும்பு "VK_ERROR_OUT_OF_POOL_MEMORY";
    நிலை VK_ERROR_INVALID_EXTERNAL_HANDLE:
        திரும்பு "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    நிலை VK_ERROR_FRAGMENTATION:
        திரும்பு "VK_ERROR_FRAGMENTATION";
    நிலை VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        திரும்பு "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    நிலை VK_ERROR_SURFACE_LOST_KHR:
        திரும்பு "VK_ERROR_SURFACE_LOST_KHR";
    நிலை VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        திரும்பு "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    நிலை VK_SUBOPTIMAL_KHR:
        திரும்பு "VK_SUBOPTIMAL_KHR";
    நிலை VK_ERROR_OUT_OF_DATE_KHR:
        திரும்பு "VK_ERROR_OUT_OF_DATE_KHR";
    நிலை VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        திரும்பு "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    நிலை VK_ERROR_VALIDATION_FAILED_EXT:
        திரும்பு "VK_ERROR_VALIDATION_FAILED_EXT";
    நிலை VK_ERROR_INVALID_SHADER_NV:
        திரும்பு "VK_ERROR_INVALID_SHADER_NV";
#எனில் VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    நிலை VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        திரும்பு "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    நிலை VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        திரும்பு "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    நிலை VK_ERROR_NOT_PERMITTED_EXT:
        திரும்பு "VK_ERROR_NOT_PERMITTED_EXT";
    நிலை VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        திரும்பு "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    நிலை VK_THREAD_IDLE_KHR:
        திரும்பு "VK_THREAD_IDLE_KHR";
    நிலை VK_THREAD_DONE_KHR:
        திரும்பு "VK_THREAD_DONE_KHR";
    நிலை VK_OPERATION_DEFERRED_KHR:
        திரும்பு "VK_OPERATION_DEFERRED_KHR";
    நிலை VK_OPERATION_NOT_DEFERRED_KHR:
        திரும்பு "VK_OPERATION_NOT_DEFERRED_KHR";
    நிலை VK_PIPELINE_COMPILE_REQUIRED_EXT:
        திரும்பு "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    இயல்பு:
        நிறுத்து;
    }
    எனில் (result < 0) {
        திரும்பு "VK_ERROR_<Unknown>";
    }
    திரும்பு "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_மொத்தம்)
{
    Uint32 மொத்தம் = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(வெற்று, &மொத்தம், வெற்று);
    VkExtensionProperties *result;

    எனில் (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (முழு)rc);
        திரும்பு வெற்று;
    } இல்லையெனில் எனில் (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (முழு)rc);
        திரும்பு வெற்று;
    }

    எனில் (மொத்தம் == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, அளவு(VkExtensionProperties)); // so we can return non-null
    } இல்லையெனில் {
        result = (VkExtensionProperties *)SDL_calloc(மொத்தம், அளவு(VkExtensionProperties));
    }

    எனில் (!result) {
        திரும்பு வெற்று;
    }

    rc = vkEnumerateInstanceExtensionProperties(வெற்று, &மொத்தம், result);
    எனில் (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (முழு)rc);
        SDL_free(result);
        திரும்பு வெற்று;
    }
    *extension_மொத்தம் = மொத்தம்;
    திரும்பு result;
}

// Alpha modes, in order of preference
நிலையான மாறிலி VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(வெறுமை *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_மொத்தம் = 0;
    VkPhysicalDevice *physicalDevices = வெற்று;
    uint32_t physicalDeviceIndex;
    மாறிலி எழுத்து *chosenDisplayId;
    முழு displayId = 0; // Counting from physical device 0, display 0

    எனில் (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        செல் error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    எனில் (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_மொத்தம், வெற்று);
    எனில் (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        செல் error;
    }

    எனில் (physical_Device_மொத்தம் == 0) {
        SDL_SetError("No Vulkan physical devices");
        செல் error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(அளவு(VkPhysicalDevice) * physical_Device_மொத்தம்);
    எனில் (!physicalDevices) {
        செல் error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_மொத்தம், physicalDevices);
    எனில் (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        செல் error;
    }

    க்கு (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_மொத்தம்; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_மொத்தம் = 0;
        VkDisplayPropertiesKHR *displayProperties = வெற்று;
        uint32_t display_Mode_Properties_மொத்தம் = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = வெற்று;
        முழு bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_மொத்தம் = 0;
        முழு planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = வெற்று;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_மொத்தம், வெற்று);
        எனில் (rc != VK_SUCCESS || display_Properties_மொத்தம் == 0) {
            // This device has no physical device display properties, move on to next.
            தொடர்;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_மொத்தம்);

        எனில் (displayId < 0 || (uint32_t)displayId >= display_Properties_மொத்தம்) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_மொத்தம்;
            தொடர்;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(அளவு(VkDisplayPropertiesKHR) * display_Properties_மொத்தம்);
        எனில் (!displayProperties) {
            செல் error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_மொத்தம், displayProperties);
        எனில் (rc != VK_SUCCESS || display_Properties_மொத்தம் == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            செல் error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = வெற்று;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_மொத்தம், வெற்று);
        எனில் (rc != VK_SUCCESS || display_Mode_Properties_மொத்தம் == 0) {
            SDL_SetError("Error enumerating display modes");
            செல் error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_மொத்தம்);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(அளவு(VkDisplayModePropertiesKHR) * display_Mode_Properties_மொத்தம்);
        எனில் (!displayModeProperties) {
            செல் error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_மொத்தம், displayModeProperties);
        எனில் (rc != VK_SUCCESS || display_Mode_Properties_மொத்தம் == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            செல் error;
        }

        // Try to find a display mode that matches the native resolution
        க்கு (i = 0; i < display_Mode_Properties_மொத்தம்; ++i) {
            எனில் (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        எனில் (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            செல் error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = வெற்று;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_மொத்தம், வெற்று);
        எனில் (rc != VK_SUCCESS || display_Plane_Properties_மொத்தம் == 0) {
            SDL_SetError("Error enumerating display planes");
            செல் error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_மொத்தம்);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(அளவு(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_மொத்தம்);
        எனில் (!displayPlaneProperties) {
            செல் error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_மொத்தம், displayPlaneProperties);
        எனில் (rc != VK_SUCCESS || display_Plane_Properties_மொத்தம் == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            செல் error;
        }

        க்கு (i = 0; i < display_Plane_Properties_மொத்தம்; ++i) {
            uint32_t plane_Supported_Displays_மொத்தம் = 0;
            VkDisplayKHR *planeSupportedDisplays = வெற்று;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            எனில் (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                தொடர்;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_மொத்தம், வெற்று);
            எனில் (rc != VK_SUCCESS || plane_Supported_Displays_மொத்தம் == 0) {
                தொடர்; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_மொத்தம்);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(அளவு(VkDisplayKHR) * plane_Supported_Displays_மொத்தம்);
            எனில் (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                செல் error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_மொத்தம், planeSupportedDisplays);
            எனில் (rc != VK_SUCCESS || plane_Supported_Displays_மொத்தம் == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                செல் error;
            }

            க்கு (j = 0; j < plane_Supported_Displays_மொத்தம் && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = வெற்று;

            எனில் (j == plane_Supported_Displays_மொத்தம்) {
                // This display is not supported for this plane, move on.
                தொடர்;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            எனில் (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                செல் error;
            }

            // Check if plane fulfills extent requirements.
            எனில் (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                நிறுத்து;
            }
        }

        எனில் (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            செல் error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_அடுக்கு_Index = displayPlaneProperties[planeIndex].current_அடுக்கு_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = வெற்று;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        க்கு (i = 0; i < SDL_arraysize(alphaModes); i++) {
            எனில் (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                நிறுத்து;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        நிறுத்து;
    }

    SDL_free(physicalDevices);
    physicalDevices = வெற்று;

    எனில் (physicalDeviceIndex == physical_Device_மொத்தம்) {
        SDL_SetError("No usable displays found or requested display out of range");
        செல் error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    எனில் (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        செல் error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    திரும்பு true;

error:
    SDL_free(physicalDevices);
    திரும்பு false;
}

வெறுமை SDL_Vulkan_DestroySurface_Internal(வெறுமை *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    எனில் (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

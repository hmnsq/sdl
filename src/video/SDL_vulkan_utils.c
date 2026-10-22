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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

ध्रुव वर्ण *SDL_Vulkan_GetResultString(VkResult result)
{
    विकल्प ((पूर्णाङ्क)result) {
    पक्ष VK_SUCCESS:
        प्रत्यागम "VK_SUCCESS";
    पक्ष VK_NOT_READY:
        प्रत्यागम "VK_NOT_READY";
    पक्ष VK_TIMEOUT:
        प्रत्यागम "VK_TIMEOUT";
    पक्ष VK_EVENT_SET:
        प्रत्यागम "VK_EVENT_SET";
    पक्ष VK_EVENT_RESET:
        प्रत्यागम "VK_EVENT_RESET";
    पक्ष VK_INCOMPLETE:
        प्रत्यागम "VK_INCOMPLETE";
    पक्ष VK_ERROR_OUT_OF_HOST_MEMORY:
        प्रत्यागम "VK_ERROR_OUT_OF_HOST_MEMORY";
    पक्ष VK_ERROR_OUT_OF_DEVICE_MEMORY:
        प्रत्यागम "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    पक्ष VK_ERROR_INITIALIZATION_FAILED:
        प्रत्यागम "VK_ERROR_INITIALIZATION_FAILED";
    पक्ष VK_ERROR_DEVICE_LOST:
        प्रत्यागम "VK_ERROR_DEVICE_LOST";
    पक्ष VK_ERROR_MEMORY_MAP_FAILED:
        प्रत्यागम "VK_ERROR_MEMORY_MAP_FAILED";
    पक्ष VK_ERROR_LAYER_NOT_PRESENT:
        प्रत्यागम "VK_ERROR_LAYER_NOT_PRESENT";
    पक्ष VK_ERROR_EXTENSION_NOT_PRESENT:
        प्रत्यागम "VK_ERROR_EXTENSION_NOT_PRESENT";
    पक्ष VK_ERROR_FEATURE_NOT_PRESENT:
        प्रत्यागम "VK_ERROR_FEATURE_NOT_PRESENT";
    पक्ष VK_ERROR_INCOMPATIBLE_DRIVER:
        प्रत्यागम "VK_ERROR_INCOMPATIBLE_DRIVER";
    पक्ष VK_ERROR_TOO_MANY_OBJECTS:
        प्रत्यागम "VK_ERROR_TOO_MANY_OBJECTS";
    पक्ष VK_ERROR_FORMAT_NOT_SUPPORTED:
        प्रत्यागम "VK_ERROR_FORMAT_NOT_SUPPORTED";
    पक्ष VK_ERROR_FRAGMENTED_POOL:
        प्रत्यागम "VK_ERROR_FRAGMENTED_POOL";
    पक्ष VK_ERROR_UNKNOWN:
        प्रत्यागम "VK_ERROR_UNKNOWN";
    पक्ष VK_ERROR_OUT_OF_POOL_MEMORY:
        प्रत्यागम "VK_ERROR_OUT_OF_POOL_MEMORY";
    पक्ष VK_ERROR_INVALID_EXTERNAL_HANDLE:
        प्रत्यागम "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    पक्ष VK_ERROR_FRAGMENTATION:
        प्रत्यागम "VK_ERROR_FRAGMENTATION";
    पक्ष VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        प्रत्यागम "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    पक्ष VK_ERROR_SURFACE_LOST_KHR:
        प्रत्यागम "VK_ERROR_SURFACE_LOST_KHR";
    पक्ष VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        प्रत्यागम "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    पक्ष VK_SUBOPTIMAL_KHR:
        प्रत्यागम "VK_SUBOPTIMAL_KHR";
    पक्ष VK_ERROR_OUT_OF_DATE_KHR:
        प्रत्यागम "VK_ERROR_OUT_OF_DATE_KHR";
    पक्ष VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        प्रत्यागम "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    पक्ष VK_ERROR_VALIDATION_FAILED_EXT:
        प्रत्यागम "VK_ERROR_VALIDATION_FAILED_EXT";
    पक्ष VK_ERROR_INVALID_SHADER_NV:
        प्रत्यागम "VK_ERROR_INVALID_SHADER_NV";
#जइ VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    पक्ष VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        प्रत्यागम "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    पक्ष VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        प्रत्यागम "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    पक्ष VK_ERROR_NOT_PERMITTED_EXT:
        प्रत्यागम "VK_ERROR_NOT_PERMITTED_EXT";
    पक्ष VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        प्रत्यागम "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    पक्ष VK_THREAD_IDLE_KHR:
        प्रत्यागम "VK_THREAD_IDLE_KHR";
    पक्ष VK_THREAD_DONE_KHR:
        प्रत्यागम "VK_THREAD_DONE_KHR";
    पक्ष VK_OPERATION_DEFERRED_KHR:
        प्रत्यागम "VK_OPERATION_DEFERRED_KHR";
    पक्ष VK_OPERATION_NOT_DEFERRED_KHR:
        प्रत्यागम "VK_OPERATION_NOT_DEFERRED_KHR";
    पक्ष VK_PIPELINE_COMPILE_REQUIRED_EXT:
        प्रत्यागम "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    स्वभाव:
        भङ्ग;
    }
    जइ (result < 0) {
        प्रत्यागम "VK_ERROR_<Unknown>";
    }
    प्रत्यागम "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_गणनम्)
{
    Uint32 गणनम् = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(रिक्त, &गणनम्, रिक्त);
    VkExtensionProperties *result;

    जइ (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णाङ्क)rc);
        प्रत्यागम रिक्त;
    } अण्णहा जइ (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णाङ्क)rc);
        प्रत्यागम रिक्त;
    }

    जइ (गणनम् == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, परिमाण(VkExtensionProperties)); // so we can return non-null
    } अण्णहा {
        result = (VkExtensionProperties *)SDL_calloc(गणनम्, परिमाण(VkExtensionProperties));
    }

    जइ (!result) {
        प्रत्यागम रिक्त;
    }

    rc = vkEnumerateInstanceExtensionProperties(रिक्त, &गणनम्, result);
    जइ (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णाङ्क)rc);
        SDL_free(result);
        प्रत्यागम रिक्त;
    }
    *extension_गणनम् = गणनम्;
    प्रत्यागम result;
}

// Alpha modes, in order of preference
स्थिर ध्रुव VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(शून्य *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ध्रुव संरचना VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_गणनम् = 0;
    VkPhysicalDevice *physicalDevices = रिक्त;
    uint32_t physicalDeviceIndex;
    ध्रुव वर्ण *chosenDisplayId;
    पूर्णाङ्क displayId = 0; // Counting from physical device 0, display 0

    जइ (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        गच्छ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    जइ (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गणनम्, रिक्त);
    जइ (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        गच्छ error;
    }

    जइ (physical_Device_गणनम् == 0) {
        SDL_SetError("No Vulkan physical devices");
        गच्छ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(परिमाण(VkPhysicalDevice) * physical_Device_गणनम्);
    जइ (!physicalDevices) {
        गच्छ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गणनम्, physicalDevices);
    जइ (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        गच्छ error;
    }

    प्रति (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_गणनम्; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_गणनम् = 0;
        VkDisplayPropertiesKHR *displayProperties = रिक्त;
        uint32_t display_Mode_Properties_गणनम् = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = रिक्त;
        पूर्णाङ्क bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_गणनम् = 0;
        पूर्णाङ्क planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = रिक्त;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गणनम्, रिक्त);
        जइ (rc != VK_SUCCESS || display_Properties_गणनम् == 0) {
            // This device has no physical device display properties, move on to next.
            अनुवर्त;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_गणनम्);

        जइ (displayId < 0 || (uint32_t)displayId >= display_Properties_गणनम्) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_गणनम्;
            अनुवर्त;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(परिमाण(VkDisplayPropertiesKHR) * display_Properties_गणनम्);
        जइ (!displayProperties) {
            गच्छ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गणनम्, displayProperties);
        जइ (rc != VK_SUCCESS || display_Properties_गणनम् == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            गच्छ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = रिक्त;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_गणनम्, रिक्त);
        जइ (rc != VK_SUCCESS || display_Mode_Properties_गणनम् == 0) {
            SDL_SetError("Error enumerating display modes");
            गच्छ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_गणनम्);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(परिमाण(VkDisplayModePropertiesKHR) * display_Mode_Properties_गणनम्);
        जइ (!displayModeProperties) {
            गच्छ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_गणनम्, displayModeProperties);
        जइ (rc != VK_SUCCESS || display_Mode_Properties_गणनम् == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            गच्छ error;
        }

        // Try to find a display mode that matches the native resolution
        प्रति (i = 0; i < display_Mode_Properties_गणनम्; ++i) {
            जइ (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        जइ (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            गच्छ error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = रिक्त;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गणनम्, रिक्त);
        जइ (rc != VK_SUCCESS || display_Plane_Properties_गणनम् == 0) {
            SDL_SetError("Error enumerating display planes");
            गच्छ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_गणनम्);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(परिमाण(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_गणनम्);
        जइ (!displayPlaneProperties) {
            गच्छ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गणनम्, displayPlaneProperties);
        जइ (rc != VK_SUCCESS || display_Plane_Properties_गणनम् == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            गच्छ error;
        }

        प्रति (i = 0; i < display_Plane_Properties_गणनम्; ++i) {
            uint32_t plane_Supported_Displays_गणनम् = 0;
            VkDisplayKHR *planeSupportedDisplays = रिक्त;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            जइ (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                अनुवर्त;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गणनम्, रिक्त);
            जइ (rc != VK_SUCCESS || plane_Supported_Displays_गणनम् == 0) {
                अनुवर्त; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_गणनम्);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(परिमाण(VkDisplayKHR) * plane_Supported_Displays_गणनम्);
            जइ (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गणनम्, planeSupportedDisplays);
            जइ (rc != VK_SUCCESS || plane_Supported_Displays_गणनम् == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            प्रति (j = 0; j < plane_Supported_Displays_गणनम् && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = रिक्त;

            जइ (j == plane_Supported_Displays_गणनम्) {
                // This display is not supported for this plane, move on.
                अनुवर्त;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            जइ (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            // Check if plane fulfills extent requirements.
            जइ (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                भङ्ग;
            }
        }

        जइ (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            गच्छ error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_राशिः_Index = displayPlaneProperties[planeIndex].current_राशिः_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = रिक्त;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        प्रति (i = 0; i < SDL_arraysize(alphaModes); i++) {
            जइ (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                भङ्ग;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        भङ्ग;
    }

    SDL_free(physicalDevices);
    physicalDevices = रिक्त;

    जइ (physicalDeviceIndex == physical_Device_गणनम्) {
        SDL_SetError("No usable displays found or requested display out of range");
        गच्छ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    जइ (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        गच्छ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    प्रत्यागम true;

error:
    SDL_free(physicalDevices);
    प्रत्यागम false;
}

शून्य SDL_Vulkan_DestroySurface_Internal(शून्य *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ध्रुव संरचना VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    जइ (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

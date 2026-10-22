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

अचर वर्ण *SDL_Vulkan_GetResultString(VkResult result)
{
    विकल्प ((पूर्णाङ्क)result) {
    पक्ष VK_SUCCESS:
        फर्काऊ "VK_SUCCESS";
    पक्ष VK_NOT_READY:
        फर्काऊ "VK_NOT_READY";
    पक्ष VK_TIMEOUT:
        फर्काऊ "VK_TIMEOUT";
    पक्ष VK_EVENT_SET:
        फर्काऊ "VK_EVENT_SET";
    पक्ष VK_EVENT_RESET:
        फर्काऊ "VK_EVENT_RESET";
    पक्ष VK_INCOMPLETE:
        फर्काऊ "VK_INCOMPLETE";
    पक्ष VK_ERROR_OUT_OF_HOST_MEMORY:
        फर्काऊ "VK_ERROR_OUT_OF_HOST_MEMORY";
    पक्ष VK_ERROR_OUT_OF_DEVICE_MEMORY:
        फर्काऊ "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    पक्ष VK_ERROR_INITIALIZATION_FAILED:
        फर्काऊ "VK_ERROR_INITIALIZATION_FAILED";
    पक्ष VK_ERROR_DEVICE_LOST:
        फर्काऊ "VK_ERROR_DEVICE_LOST";
    पक्ष VK_ERROR_MEMORY_MAP_FAILED:
        फर्काऊ "VK_ERROR_MEMORY_MAP_FAILED";
    पक्ष VK_ERROR_LAYER_NOT_PRESENT:
        फर्काऊ "VK_ERROR_LAYER_NOT_PRESENT";
    पक्ष VK_ERROR_EXTENSION_NOT_PRESENT:
        फर्काऊ "VK_ERROR_EXTENSION_NOT_PRESENT";
    पक्ष VK_ERROR_FEATURE_NOT_PRESENT:
        फर्काऊ "VK_ERROR_FEATURE_NOT_PRESENT";
    पक्ष VK_ERROR_INCOMPATIBLE_DRIVER:
        फर्काऊ "VK_ERROR_INCOMPATIBLE_DRIVER";
    पक्ष VK_ERROR_TOO_MANY_OBJECTS:
        फर्काऊ "VK_ERROR_TOO_MANY_OBJECTS";
    पक्ष VK_ERROR_FORMAT_NOT_SUPPORTED:
        फर्काऊ "VK_ERROR_FORMAT_NOT_SUPPORTED";
    पक्ष VK_ERROR_FRAGMENTED_POOL:
        फर्काऊ "VK_ERROR_FRAGMENTED_POOL";
    पक्ष VK_ERROR_UNKNOWN:
        फर्काऊ "VK_ERROR_UNKNOWN";
    पक्ष VK_ERROR_OUT_OF_POOL_MEMORY:
        फर्काऊ "VK_ERROR_OUT_OF_POOL_MEMORY";
    पक्ष VK_ERROR_INVALID_EXTERNAL_HANDLE:
        फर्काऊ "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    पक्ष VK_ERROR_FRAGMENTATION:
        फर्काऊ "VK_ERROR_FRAGMENTATION";
    पक्ष VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        फर्काऊ "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    पक्ष VK_ERROR_SURFACE_LOST_KHR:
        फर्काऊ "VK_ERROR_SURFACE_LOST_KHR";
    पक्ष VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        फर्काऊ "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    पक्ष VK_SUBOPTIMAL_KHR:
        फर्काऊ "VK_SUBOPTIMAL_KHR";
    पक्ष VK_ERROR_OUT_OF_DATE_KHR:
        फर्काऊ "VK_ERROR_OUT_OF_DATE_KHR";
    पक्ष VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        फर्काऊ "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    पक्ष VK_ERROR_VALIDATION_FAILED_EXT:
        फर्काऊ "VK_ERROR_VALIDATION_FAILED_EXT";
    पक्ष VK_ERROR_INVALID_SHADER_NV:
        फर्काऊ "VK_ERROR_INVALID_SHADER_NV";
#यदि VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    पक्ष VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        फर्काऊ "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    पक्ष VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        फर्काऊ "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    पक्ष VK_ERROR_NOT_PERMITTED_EXT:
        फर्काऊ "VK_ERROR_NOT_PERMITTED_EXT";
    पक्ष VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        फर्काऊ "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    पक्ष VK_THREAD_IDLE_KHR:
        फर्काऊ "VK_THREAD_IDLE_KHR";
    पक्ष VK_THREAD_DONE_KHR:
        फर्काऊ "VK_THREAD_DONE_KHR";
    पक्ष VK_OPERATION_DEFERRED_KHR:
        फर्काऊ "VK_OPERATION_DEFERRED_KHR";
    पक्ष VK_OPERATION_NOT_DEFERRED_KHR:
        फर्काऊ "VK_OPERATION_NOT_DEFERRED_KHR";
    पक्ष VK_PIPELINE_COMPILE_REQUIRED_EXT:
        फर्काऊ "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    स्वभाव:
        रोक;
    }
    यदि (result < 0) {
        फर्काऊ "VK_ERROR_<Unknown>";
    }
    फर्काऊ "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_गन्ती)
{
    Uint32 गन्ती = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(रिक्त, &गन्ती, रिक्त);
    VkExtensionProperties *result;

    यदि (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णाङ्क)rc);
        फर्काऊ रिक्त;
    } अन्यथा यदि (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णाङ्क)rc);
        फर्काऊ रिक्त;
    }

    यदि (गन्ती == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, परिमाण(VkExtensionProperties)); // so we can return non-null
    } अन्यथा {
        result = (VkExtensionProperties *)SDL_calloc(गन्ती, परिमाण(VkExtensionProperties));
    }

    यदि (!result) {
        फर्काऊ रिक्त;
    }

    rc = vkEnumerateInstanceExtensionProperties(रिक्त, &गन्ती, result);
    यदि (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णाङ्क)rc);
        SDL_free(result);
        फर्काऊ रिक्त;
    }
    *extension_गन्ती = गन्ती;
    फर्काऊ result;
}

// Alpha modes, in order of preference
स्थिर अचर VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(शून्य *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      अचर संरचना VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_गन्ती = 0;
    VkPhysicalDevice *physicalDevices = रिक्त;
    uint32_t physicalDeviceIndex;
    अचर वर्ण *chosenDisplayId;
    पूर्णाङ्क displayId = 0; // Counting from physical device 0, display 0

    यदि (!vkEnumeratePhysicalDevices ||
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
    यदि (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गन्ती, रिक्त);
    यदि (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        गच्छ error;
    }

    यदि (physical_Device_गन्ती == 0) {
        SDL_SetError("No Vulkan physical devices");
        गच्छ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(परिमाण(VkPhysicalDevice) * physical_Device_गन्ती);
    यदि (!physicalDevices) {
        गच्छ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_गन्ती, physicalDevices);
    यदि (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        गच्छ error;
    }

    लागि (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_गन्ती; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_गन्ती = 0;
        VkDisplayPropertiesKHR *displayProperties = रिक्त;
        uint32_t display_Mode_Properties_गन्ती = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = रिक्त;
        पूर्णाङ्क bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_गन्ती = 0;
        पूर्णाङ्क planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = रिक्त;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गन्ती, रिक्त);
        यदि (rc != VK_SUCCESS || display_Properties_गन्ती == 0) {
            // This device has no physical device display properties, move on to next.
            जारी;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_गन्ती);

        यदि (displayId < 0 || (uint32_t)displayId >= display_Properties_गन्ती) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_गन्ती;
            जारी;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(परिमाण(VkDisplayPropertiesKHR) * display_Properties_गन्ती);
        यदि (!displayProperties) {
            गच्छ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_गन्ती, displayProperties);
        यदि (rc != VK_SUCCESS || display_Properties_गन्ती == 0) {
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
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_गन्ती, रिक्त);
        यदि (rc != VK_SUCCESS || display_Mode_Properties_गन्ती == 0) {
            SDL_SetError("Error enumerating display modes");
            गच्छ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_गन्ती);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(परिमाण(VkDisplayModePropertiesKHR) * display_Mode_Properties_गन्ती);
        यदि (!displayModeProperties) {
            गच्छ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_गन्ती, displayModeProperties);
        यदि (rc != VK_SUCCESS || display_Mode_Properties_गन्ती == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            गच्छ error;
        }

        // Try to find a display mode that matches the native resolution
        लागि (i = 0; i < display_Mode_Properties_गन्ती; ++i) {
            यदि (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        यदि (bestMatchIndex < 0) {
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
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गन्ती, रिक्त);
        यदि (rc != VK_SUCCESS || display_Plane_Properties_गन्ती == 0) {
            SDL_SetError("Error enumerating display planes");
            गच्छ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_गन्ती);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(परिमाण(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_गन्ती);
        यदि (!displayPlaneProperties) {
            गच्छ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_गन्ती, displayPlaneProperties);
        यदि (rc != VK_SUCCESS || display_Plane_Properties_गन्ती == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            गच्छ error;
        }

        लागि (i = 0; i < display_Plane_Properties_गन्ती; ++i) {
            uint32_t plane_Supported_Displays_गन्ती = 0;
            VkDisplayKHR *planeSupportedDisplays = रिक्त;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            यदि (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                जारी;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गन्ती, रिक्त);
            यदि (rc != VK_SUCCESS || plane_Supported_Displays_गन्ती == 0) {
                जारी; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_गन्ती);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(परिमाण(VkDisplayKHR) * plane_Supported_Displays_गन्ती);
            यदि (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_गन्ती, planeSupportedDisplays);
            यदि (rc != VK_SUCCESS || plane_Supported_Displays_गन्ती == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            लागि (j = 0; j < plane_Supported_Displays_गन्ती && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = रिक्त;

            यदि (j == plane_Supported_Displays_गन्ती) {
                // This display is not supported for this plane, move on.
                जारी;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            यदि (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                गच्छ error;
            }

            // Check if plane fulfills extent requirements.
            यदि (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                रोक;
            }
        }

        यदि (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            गच्छ error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_थाक_Index = displayPlaneProperties[planeIndex].current_थाक_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = रिक्त;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        लागि (i = 0; i < SDL_arraysize(alphaModes); i++) {
            यदि (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                रोक;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        रोक;
    }

    SDL_free(physicalDevices);
    physicalDevices = रिक्त;

    यदि (physicalDeviceIndex == physical_Device_गन्ती) {
        SDL_SetError("No usable displays found or requested display out of range");
        गच्छ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    यदि (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        गच्छ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    फर्काऊ true;

error:
    SDL_free(physicalDevices);
    फर्काऊ false;
}

शून्य SDL_Vulkan_DestroySurface_Internal(शून्य *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        अचर संरचना VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    यदि (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

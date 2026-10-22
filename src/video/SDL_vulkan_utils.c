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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

ଅଚଳ ଅକ୍ଷର *SDL_Vulkan_GetResultString(VkResult result)
{
    ବାଛ ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)result) {
    ସ୍ଥିତି VK_SUCCESS:
        ଫେରନ୍ତୁ "VK_SUCCESS";
    ସ୍ଥିତି VK_NOT_READY:
        ଫେରନ୍ତୁ "VK_NOT_READY";
    ସ୍ଥିତି VK_TIMEOUT:
        ଫେରନ୍ତୁ "VK_TIMEOUT";
    ସ୍ଥିତି VK_EVENT_SET:
        ଫେରନ୍ତୁ "VK_EVENT_SET";
    ସ୍ଥିତି VK_EVENT_RESET:
        ଫେରନ୍ତୁ "VK_EVENT_RESET";
    ସ୍ଥିତି VK_INCOMPLETE:
        ଫେରନ୍ତୁ "VK_INCOMPLETE";
    ସ୍ଥିତି VK_ERROR_OUT_OF_HOST_MEMORY:
        ଫେରନ୍ତୁ "VK_ERROR_OUT_OF_HOST_MEMORY";
    ସ୍ଥିତି VK_ERROR_OUT_OF_DEVICE_MEMORY:
        ଫେରନ୍ତୁ "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    ସ୍ଥିତି VK_ERROR_INITIALIZATION_FAILED:
        ଫେରନ୍ତୁ "VK_ERROR_INITIALIZATION_FAILED";
    ସ୍ଥିତି VK_ERROR_DEVICE_LOST:
        ଫେରନ୍ତୁ "VK_ERROR_DEVICE_LOST";
    ସ୍ଥିତି VK_ERROR_MEMORY_MAP_FAILED:
        ଫେରନ୍ତୁ "VK_ERROR_MEMORY_MAP_FAILED";
    ସ୍ଥିତି VK_ERROR_LAYER_NOT_PRESENT:
        ଫେରନ୍ତୁ "VK_ERROR_LAYER_NOT_PRESENT";
    ସ୍ଥିତି VK_ERROR_EXTENSION_NOT_PRESENT:
        ଫେରନ୍ତୁ "VK_ERROR_EXTENSION_NOT_PRESENT";
    ସ୍ଥିତି VK_ERROR_FEATURE_NOT_PRESENT:
        ଫେରନ୍ତୁ "VK_ERROR_FEATURE_NOT_PRESENT";
    ସ୍ଥିତି VK_ERROR_INCOMPATIBLE_DRIVER:
        ଫେରନ୍ତୁ "VK_ERROR_INCOMPATIBLE_DRIVER";
    ସ୍ଥିତି VK_ERROR_TOO_MANY_OBJECTS:
        ଫେରନ୍ତୁ "VK_ERROR_TOO_MANY_OBJECTS";
    ସ୍ଥିତି VK_ERROR_FORMAT_NOT_SUPPORTED:
        ଫେରନ୍ତୁ "VK_ERROR_FORMAT_NOT_SUPPORTED";
    ସ୍ଥିତି VK_ERROR_FRAGMENTED_POOL:
        ଫେରନ୍ତୁ "VK_ERROR_FRAGMENTED_POOL";
    ସ୍ଥିତି VK_ERROR_UNKNOWN:
        ଫେରନ୍ତୁ "VK_ERROR_UNKNOWN";
    ସ୍ଥିତି VK_ERROR_OUT_OF_POOL_MEMORY:
        ଫେରନ୍ତୁ "VK_ERROR_OUT_OF_POOL_MEMORY";
    ସ୍ଥିତି VK_ERROR_INVALID_EXTERNAL_HANDLE:
        ଫେରନ୍ତୁ "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    ସ୍ଥିତି VK_ERROR_FRAGMENTATION:
        ଫେରନ୍ତୁ "VK_ERROR_FRAGMENTATION";
    ସ୍ଥିତି VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        ଫେରନ୍ତୁ "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    ସ୍ଥିତି VK_ERROR_SURFACE_LOST_KHR:
        ଫେରନ୍ତୁ "VK_ERROR_SURFACE_LOST_KHR";
    ସ୍ଥିତି VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        ଫେରନ୍ତୁ "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    ସ୍ଥିତି VK_SUBOPTIMAL_KHR:
        ଫେରନ୍ତୁ "VK_SUBOPTIMAL_KHR";
    ସ୍ଥିତି VK_ERROR_OUT_OF_DATE_KHR:
        ଫେରନ୍ତୁ "VK_ERROR_OUT_OF_DATE_KHR";
    ସ୍ଥିତି VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        ଫେରନ୍ତୁ "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    ସ୍ଥିତି VK_ERROR_VALIDATION_FAILED_EXT:
        ଫେରନ୍ତୁ "VK_ERROR_VALIDATION_FAILED_EXT";
    ସ୍ଥିତି VK_ERROR_INVALID_SHADER_NV:
        ଫେରନ୍ତୁ "VK_ERROR_INVALID_SHADER_NV";
#ଯଦି VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    ସ୍ଥିତି VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        ଫେରନ୍ତୁ "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    ସ୍ଥିତି VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        ଫେରନ୍ତୁ "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    ସ୍ଥିତି VK_ERROR_NOT_PERMITTED_EXT:
        ଫେରନ୍ତୁ "VK_ERROR_NOT_PERMITTED_EXT";
    ସ୍ଥିତି VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        ଫେରନ୍ତୁ "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    ସ୍ଥିତି VK_THREAD_IDLE_KHR:
        ଫେରନ୍ତୁ "VK_THREAD_IDLE_KHR";
    ସ୍ଥିତି VK_THREAD_DONE_KHR:
        ଫେରନ୍ତୁ "VK_THREAD_DONE_KHR";
    ସ୍ଥିତି VK_OPERATION_DEFERRED_KHR:
        ଫେରନ୍ତୁ "VK_OPERATION_DEFERRED_KHR";
    ସ୍ଥିତି VK_OPERATION_NOT_DEFERRED_KHR:
        ଫେରନ୍ତୁ "VK_OPERATION_NOT_DEFERRED_KHR";
    ସ୍ଥିତି VK_PIPELINE_COMPILE_REQUIRED_EXT:
        ଫେରନ୍ତୁ "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
    ଯଦି (result < 0) {
        ଫେରନ୍ତୁ "VK_ERROR_<Unknown>";
    }
    ଫେରନ୍ତୁ "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ଗଣନା)
{
    Uint32 ଗଣନା_2 = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(ଖାଲି, &ଗଣନା_2, ଖାଲି);
    VkExtensionProperties *result;

    ଯଦି (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc);
        ଫେରନ୍ତୁ ଖାଲି;
    } ଅନ୍ୟଥା ଯଦି (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (ଗଣନା_2 == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, ଆକାର(VkExtensionProperties)); // so we can return non-null
    } ଅନ୍ୟଥା {
        result = (VkExtensionProperties *)SDL_calloc(ଗଣନା_2, ଆକାର(VkExtensionProperties));
    }

    ଯଦି (!result) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    rc = vkEnumerateInstanceExtensionProperties(ଖାଲି, &ଗଣନା_2, result);
    ଯଦି (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc);
        SDL_free(result);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    *extension_ଗଣନା = ଗଣନା_2;
    ଫେରନ୍ତୁ result;
}

// Alpha modes, in order of preference
ସ୍ଥିର ଅଚଳ VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(ଶୂନ୍ୟ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_ଗଣନା = 0;
    VkPhysicalDevice *physicalDevices = ଖାଲି;
    uint32_t physicalDeviceIndex;
    ଅଚଳ ଅକ୍ଷର *chosenDisplayId;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା displayId = 0; // Counting from physical device 0, display 0

    ଯଦି (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        ଯାଅ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    ଯଦି (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ଗଣନା, ଖାଲି);
    ଯଦି (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        ଯାଅ error;
    }

    ଯଦି (physical_Device_ଗଣନା == 0) {
        SDL_SetError("No Vulkan physical devices");
        ଯାଅ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(ଆକାର(VkPhysicalDevice) * physical_Device_ଗଣନା);
    ଯଦି (!physicalDevices) {
        ଯାଅ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ଗଣନା, physicalDevices);
    ଯଦି (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        ଯାଅ error;
    }

    ପାଇଁ (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_ଗଣନା; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_ଗଣନା = 0;
        VkDisplayPropertiesKHR *displayProperties = ଖାଲି;
        uint32_t display_Mode_Properties_ଗଣନା = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = ଖାଲି;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_ଗଣନା = 0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ଖାଲି;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ଗଣନା, ଖାଲି);
        ଯଦି (rc != VK_SUCCESS || display_Properties_ଗଣନା == 0) {
            // This device has no physical device display properties, move on to next.
            ଜାରି;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_ଗଣନା);

        ଯଦି (displayId < 0 || (uint32_t)displayId >= display_Properties_ଗଣନା) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_ଗଣନା;
            ଜାରି;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(ଆକାର(VkDisplayPropertiesKHR) * display_Properties_ଗଣନା);
        ଯଦି (!displayProperties) {
            ଯାଅ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ଗଣନା, displayProperties);
        ଯଦି (rc != VK_SUCCESS || display_Properties_ଗଣନା == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            ଯାଅ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = ଖାଲି;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_ଗଣନା, ଖାଲି);
        ଯଦି (rc != VK_SUCCESS || display_Mode_Properties_ଗଣନା == 0) {
            SDL_SetError("Error enumerating display modes");
            ଯାଅ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_ଗଣନା);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(ଆକାର(VkDisplayModePropertiesKHR) * display_Mode_Properties_ଗଣନା);
        ଯଦି (!displayModeProperties) {
            ଯାଅ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_ଗଣନା, displayModeProperties);
        ଯଦି (rc != VK_SUCCESS || display_Mode_Properties_ଗଣନା == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            ଯାଅ error;
        }

        // Try to find a display mode that matches the native resolution
        ପାଇଁ (i = 0; i < display_Mode_Properties_ଗଣନା; ++i) {
            ଯଦି (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        ଯଦି (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            ଯାଅ error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = ଖାଲି;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ଗଣନା, ଖାଲି);
        ଯଦି (rc != VK_SUCCESS || display_Plane_Properties_ଗଣନା == 0) {
            SDL_SetError("Error enumerating display planes");
            ଯାଅ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_ଗଣନା);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(ଆକାର(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_ଗଣନା);
        ଯଦି (!displayPlaneProperties) {
            ଯାଅ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ଗଣନା, displayPlaneProperties);
        ଯଦି (rc != VK_SUCCESS || display_Plane_Properties_ଗଣନା == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            ଯାଅ error;
        }

        ପାଇଁ (i = 0; i < display_Plane_Properties_ଗଣନା; ++i) {
            uint32_t plane_Supported_Displays_ଗଣନା = 0;
            VkDisplayKHR *planeSupportedDisplays = ଖାଲି;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            ଯଦି (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                ଜାରି;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ଗଣନା, ଖାଲି);
            ଯଦି (rc != VK_SUCCESS || plane_Supported_Displays_ଗଣନା == 0) {
                ଜାରି; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_ଗଣନା);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(ଆକାର(VkDisplayKHR) * plane_Supported_Displays_ଗଣନା);
            ଯଦି (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                ଯାଅ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ଗଣନା, planeSupportedDisplays);
            ଯଦି (rc != VK_SUCCESS || plane_Supported_Displays_ଗଣନା == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                ଯାଅ error;
            }

            ପାଇଁ (j = 0; j < plane_Supported_Displays_ଗଣନା && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ଖାଲି;

            ଯଦି (j == plane_Supported_Displays_ଗଣନା) {
                // This display is not supported for this plane, move on.
                ଜାରି;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            ଯଦି (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                ଯାଅ error;
            }

            // Check if plane fulfills extent requirements.
            ଯଦି (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                ଭାଙ୍ଗ;
            }
        }

        ଯଦି (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            ଯାଅ error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_ଗଦା_Index = displayPlaneProperties[planeIndex].current_ଗଦା_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ଖାଲି;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        ପାଇଁ (i = 0; i < SDL_arraysize(alphaModes); i++) {
            ଯଦି (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                ଭାଙ୍ଗ;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        ଭାଙ୍ଗ;
    }

    SDL_free(physicalDevices);
    physicalDevices = ଖାଲି;

    ଯଦି (physicalDeviceIndex == physical_Device_ଗଣନା) {
        SDL_SetError("No usable displays found or requested display out of range");
        ଯାଅ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    ଯଦି (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        ଯାଅ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    ଫେରନ୍ତୁ true;

error:
    SDL_free(physicalDevices);
    ଫେରନ୍ତୁ false;
}

ଶୂନ୍ୟ SDL_Vulkan_DestroySurface_Internal(ଶୂନ୍ୟ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    ଯଦି (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

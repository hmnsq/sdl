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
#অন্তর্ভাব "SDL_internal.h"

#অন্তর্ভাব "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

ধ্রুব বর্ণ *SDL_Vulkan_GetResultString(VkResult result)
{
    বিকল্প ((পূর্ণাঙ্ক)result) {
    পক্ষ VK_SUCCESS:
        প্রত্যাগম "VK_SUCCESS";
    পক্ষ VK_NOT_READY:
        প্রত্যাগম "VK_NOT_READY";
    পক্ষ VK_TIMEOUT:
        প্রত্যাগম "VK_TIMEOUT";
    পক্ষ VK_EVENT_SET:
        প্রত্যাগম "VK_EVENT_SET";
    পক্ষ VK_EVENT_RESET:
        প্রত্যাগম "VK_EVENT_RESET";
    পক্ষ VK_INCOMPLETE:
        প্রত্যাগম "VK_INCOMPLETE";
    পক্ষ VK_ERROR_OUT_OF_HOST_MEMORY:
        প্রত্যাগম "VK_ERROR_OUT_OF_HOST_MEMORY";
    পক্ষ VK_ERROR_OUT_OF_DEVICE_MEMORY:
        প্রত্যাগম "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    পক্ষ VK_ERROR_INITIALIZATION_FAILED:
        প্রত্যাগম "VK_ERROR_INITIALIZATION_FAILED";
    পক্ষ VK_ERROR_DEVICE_LOST:
        প্রত্যাগম "VK_ERROR_DEVICE_LOST";
    পক্ষ VK_ERROR_MEMORY_MAP_FAILED:
        প্রত্যাগম "VK_ERROR_MEMORY_MAP_FAILED";
    পক্ষ VK_ERROR_LAYER_NOT_PRESENT:
        প্রত্যাগম "VK_ERROR_LAYER_NOT_PRESENT";
    পক্ষ VK_ERROR_EXTENSION_NOT_PRESENT:
        প্রত্যাগম "VK_ERROR_EXTENSION_NOT_PRESENT";
    পক্ষ VK_ERROR_FEATURE_NOT_PRESENT:
        প্রত্যাগম "VK_ERROR_FEATURE_NOT_PRESENT";
    পক্ষ VK_ERROR_INCOMPATIBLE_DRIVER:
        প্রত্যাগম "VK_ERROR_INCOMPATIBLE_DRIVER";
    পক্ষ VK_ERROR_TOO_MANY_OBJECTS:
        প্রত্যাগম "VK_ERROR_TOO_MANY_OBJECTS";
    পক্ষ VK_ERROR_FORMAT_NOT_SUPPORTED:
        প্রত্যাগম "VK_ERROR_FORMAT_NOT_SUPPORTED";
    পক্ষ VK_ERROR_FRAGMENTED_POOL:
        প্রত্যাগম "VK_ERROR_FRAGMENTED_POOL";
    পক্ষ VK_ERROR_UNKNOWN:
        প্রত্যাগম "VK_ERROR_UNKNOWN";
    পক্ষ VK_ERROR_OUT_OF_POOL_MEMORY:
        প্রত্যাগম "VK_ERROR_OUT_OF_POOL_MEMORY";
    পক্ষ VK_ERROR_INVALID_EXTERNAL_HANDLE:
        প্রত্যাগম "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    পক্ষ VK_ERROR_FRAGMENTATION:
        প্রত্যাগম "VK_ERROR_FRAGMENTATION";
    পক্ষ VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        প্রত্যাগম "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    পক্ষ VK_ERROR_SURFACE_LOST_KHR:
        প্রত্যাগম "VK_ERROR_SURFACE_LOST_KHR";
    পক্ষ VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        প্রত্যাগম "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    পক্ষ VK_SUBOPTIMAL_KHR:
        প্রত্যাগম "VK_SUBOPTIMAL_KHR";
    পক্ষ VK_ERROR_OUT_OF_DATE_KHR:
        প্রত্যাগম "VK_ERROR_OUT_OF_DATE_KHR";
    পক্ষ VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        প্রত্যাগম "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    পক্ষ VK_ERROR_VALIDATION_FAILED_EXT:
        প্রত্যাগম "VK_ERROR_VALIDATION_FAILED_EXT";
    পক্ষ VK_ERROR_INVALID_SHADER_NV:
        প্রত্যাগম "VK_ERROR_INVALID_SHADER_NV";
#যদি VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    পক্ষ VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        প্রত্যাগম "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    পক্ষ VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        প্রত্যাগম "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    পক্ষ VK_ERROR_NOT_PERMITTED_EXT:
        প্রত্যাগম "VK_ERROR_NOT_PERMITTED_EXT";
    পক্ষ VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        প্রত্যাগম "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    পক্ষ VK_THREAD_IDLE_KHR:
        প্রত্যাগম "VK_THREAD_IDLE_KHR";
    পক্ষ VK_THREAD_DONE_KHR:
        প্রত্যাগম "VK_THREAD_DONE_KHR";
    পক্ষ VK_OPERATION_DEFERRED_KHR:
        প্রত্যাগম "VK_OPERATION_DEFERRED_KHR";
    পক্ষ VK_OPERATION_NOT_DEFERRED_KHR:
        প্রত্যাগম "VK_OPERATION_NOT_DEFERRED_KHR";
    পক্ষ VK_PIPELINE_COMPILE_REQUIRED_EXT:
        প্রত্যাগম "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    স্বভাব:
        ভঙ্গ;
    }
    যদি (result < 0) {
        প্রত্যাগম "VK_ERROR_<Unknown>";
    }
    প্রত্যাগম "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_গুনতি)
{
    Uint32 গুনতি = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(রিক্ত, &গুনতি, রিক্ত);
    VkExtensionProperties *result;

    যদি (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (পূর্ণাঙ্ক)rc);
        প্রত্যাগম রিক্ত;
    } অন্যথা যদি (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (পূর্ণাঙ্ক)rc);
        প্রত্যাগম রিক্ত;
    }

    যদি (গুনতি == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, পরিমাণ(VkExtensionProperties)); // so we can return non-null
    } অন্যথা {
        result = (VkExtensionProperties *)SDL_calloc(গুনতি, পরিমাণ(VkExtensionProperties));
    }

    যদি (!result) {
        প্রত্যাগম রিক্ত;
    }

    rc = vkEnumerateInstanceExtensionProperties(রিক্ত, &গুনতি, result);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (পূর্ণাঙ্ক)rc);
        SDL_free(result);
        প্রত্যাগম রিক্ত;
    }
    *extension_গুনতি = গুনতি;
    প্রত্যাগম result;
}

// Alpha modes, in order of preference
স্থির ধ্রুব VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(শূন্য *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ধ্রুব সংরচনা VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_গুনতি = 0;
    VkPhysicalDevice *physicalDevices = রিক্ত;
    uint32_t physicalDeviceIndex;
    ধ্রুব বর্ণ *chosenDisplayId;
    পূর্ণাঙ্ক displayId = 0; // Counting from physical device 0, display 0

    যদি (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        গচ্ছ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    যদি (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_গুনতি, রিক্ত);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        গচ্ছ error;
    }

    যদি (physical_Device_গুনতি == 0) {
        SDL_SetError("No Vulkan physical devices");
        গচ্ছ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(পরিমাণ(VkPhysicalDevice) * physical_Device_গুনতি);
    যদি (!physicalDevices) {
        গচ্ছ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_গুনতি, physicalDevices);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        গচ্ছ error;
    }

    প্রতি (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_গুনতি; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_গুনতি = 0;
        VkDisplayPropertiesKHR *displayProperties = রিক্ত;
        uint32_t display_Mode_Properties_গুনতি = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = রিক্ত;
        পূর্ণাঙ্ক bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_গুনতি = 0;
        পূর্ণাঙ্ক planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = রিক্ত;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_গুনতি, রিক্ত);
        যদি (rc != VK_SUCCESS || display_Properties_গুনতি == 0) {
            // This device has no physical device display properties, move on to next.
            অনুবর্ত;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_গুনতি);

        যদি (displayId < 0 || (uint32_t)displayId >= display_Properties_গুনতি) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_গুনতি;
            অনুবর্ত;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(পরিমাণ(VkDisplayPropertiesKHR) * display_Properties_গুনতি);
        যদি (!displayProperties) {
            গচ্ছ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_গুনতি, displayProperties);
        যদি (rc != VK_SUCCESS || display_Properties_গুনতি == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            গচ্ছ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = রিক্ত;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_গুনতি, রিক্ত);
        যদি (rc != VK_SUCCESS || display_Mode_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display modes");
            গচ্ছ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_গুনতি);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(পরিমাণ(VkDisplayModePropertiesKHR) * display_Mode_Properties_গুনতি);
        যদি (!displayModeProperties) {
            গচ্ছ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_গুনতি, displayModeProperties);
        যদি (rc != VK_SUCCESS || display_Mode_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            গচ্ছ error;
        }

        // Try to find a display mode that matches the native resolution
        প্রতি (i = 0; i < display_Mode_Properties_গুনতি; ++i) {
            যদি (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        যদি (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            গচ্ছ error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = রিক্ত;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_গুনতি, রিক্ত);
        যদি (rc != VK_SUCCESS || display_Plane_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display planes");
            গচ্ছ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_গুনতি);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(পরিমাণ(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_গুনতি);
        যদি (!displayPlaneProperties) {
            গচ্ছ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_গুনতি, displayPlaneProperties);
        যদি (rc != VK_SUCCESS || display_Plane_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            গচ্ছ error;
        }

        প্রতি (i = 0; i < display_Plane_Properties_গুনতি; ++i) {
            uint32_t plane_Supported_Displays_গুনতি = 0;
            VkDisplayKHR *planeSupportedDisplays = রিক্ত;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            যদি (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                অনুবর্ত;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_গুনতি, রিক্ত);
            যদি (rc != VK_SUCCESS || plane_Supported_Displays_গুনতি == 0) {
                অনুবর্ত; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_গুনতি);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(পরিমাণ(VkDisplayKHR) * plane_Supported_Displays_গুনতি);
            যদি (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                গচ্ছ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_গুনতি, planeSupportedDisplays);
            যদি (rc != VK_SUCCESS || plane_Supported_Displays_গুনতি == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                গচ্ছ error;
            }

            প্রতি (j = 0; j < plane_Supported_Displays_গুনতি && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = রিক্ত;

            যদি (j == plane_Supported_Displays_গুনতি) {
                // This display is not supported for this plane, move on.
                অনুবর্ত;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            যদি (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                গচ্ছ error;
            }

            // Check if plane fulfills extent requirements.
            যদি (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                ভঙ্গ;
            }
        }

        যদি (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            গচ্ছ error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_স্তূপ_Index = displayPlaneProperties[planeIndex].current_স্তূপ_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = রিক্ত;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        প্রতি (i = 0; i < SDL_arraysize(alphaModes); i++) {
            যদি (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                ভঙ্গ;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        ভঙ্গ;
    }

    SDL_free(physicalDevices);
    physicalDevices = রিক্ত;

    যদি (physicalDeviceIndex == physical_Device_গুনতি) {
        SDL_SetError("No usable displays found or requested display out of range");
        গচ্ছ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        গচ্ছ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    প্রত্যাগম true;

error:
    SDL_free(physicalDevices);
    প্রত্যাগম false;
}

শূন্য SDL_Vulkan_DestroySurface_Internal(শূন্য *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ধ্রুব সংরচনা VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    যদি (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

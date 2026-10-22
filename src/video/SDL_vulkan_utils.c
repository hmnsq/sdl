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

ধ্রুবক অক্ষর *SDL_Vulkan_Get_ফলাফল_String(Vk_ফলাফল ফলাফল)
{
    নির্বাচন ((পূর্ণসংখ্যা)ফলাফল) {
    ক্ষেত্র VK_SUCCESS:
        ফেরত "VK_SUCCESS";
    ক্ষেত্র VK_NOT_READY:
        ফেরত "VK_NOT_READY";
    ক্ষেত্র VK_TIMEOUT:
        ফেরত "VK_TIMEOUT";
    ক্ষেত্র VK_EVENT_SET:
        ফেরত "VK_EVENT_SET";
    ক্ষেত্র VK_EVENT_RESET:
        ফেরত "VK_EVENT_RESET";
    ক্ষেত্র VK_INCOMPLETE:
        ফেরত "VK_INCOMPLETE";
    ক্ষেত্র VK_ERROR_OUT_OF_HOST_MEMORY:
        ফেরত "VK_ERROR_OUT_OF_HOST_MEMORY";
    ক্ষেত্র VK_ERROR_OUT_OF_DEVICE_MEMORY:
        ফেরত "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    ক্ষেত্র VK_ERROR_INITIALIZATION_FAILED:
        ফেরত "VK_ERROR_INITIALIZATION_FAILED";
    ক্ষেত্র VK_ERROR_DEVICE_LOST:
        ফেরত "VK_ERROR_DEVICE_LOST";
    ক্ষেত্র VK_ERROR_MEMORY_MAP_FAILED:
        ফেরত "VK_ERROR_MEMORY_MAP_FAILED";
    ক্ষেত্র VK_ERROR_LAYER_NOT_PRESENT:
        ফেরত "VK_ERROR_LAYER_NOT_PRESENT";
    ক্ষেত্র VK_ERROR_EXTENSION_NOT_PRESENT:
        ফেরত "VK_ERROR_EXTENSION_NOT_PRESENT";
    ক্ষেত্র VK_ERROR_FEATURE_NOT_PRESENT:
        ফেরত "VK_ERROR_FEATURE_NOT_PRESENT";
    ক্ষেত্র VK_ERROR_INCOMPATIBLE_DRIVER:
        ফেরত "VK_ERROR_INCOMPATIBLE_DRIVER";
    ক্ষেত্র VK_ERROR_TOO_MANY_OBJECTS:
        ফেরত "VK_ERROR_TOO_MANY_OBJECTS";
    ক্ষেত্র VK_ERROR_FORMAT_NOT_SUPPORTED:
        ফেরত "VK_ERROR_FORMAT_NOT_SUPPORTED";
    ক্ষেত্র VK_ERROR_FRAGMENTED_POOL:
        ফেরত "VK_ERROR_FRAGMENTED_POOL";
    ক্ষেত্র VK_ERROR_UNKNOWN:
        ফেরত "VK_ERROR_UNKNOWN";
    ক্ষেত্র VK_ERROR_OUT_OF_POOL_MEMORY:
        ফেরত "VK_ERROR_OUT_OF_POOL_MEMORY";
    ক্ষেত্র VK_ERROR_INVALID_EXTERNAL_HANDLE:
        ফেরত "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    ক্ষেত্র VK_ERROR_FRAGMENTATION:
        ফেরত "VK_ERROR_FRAGMENTATION";
    ক্ষেত্র VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        ফেরত "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    ক্ষেত্র VK_ERROR_SURFACE_LOST_KHR:
        ফেরত "VK_ERROR_SURFACE_LOST_KHR";
    ক্ষেত্র VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        ফেরত "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    ক্ষেত্র VK_SUBOPTIMAL_KHR:
        ফেরত "VK_SUBOPTIMAL_KHR";
    ক্ষেত্র VK_ERROR_OUT_OF_DATE_KHR:
        ফেরত "VK_ERROR_OUT_OF_DATE_KHR";
    ক্ষেত্র VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        ফেরত "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    ক্ষেত্র VK_ERROR_VALIDATION_FAILED_EXT:
        ফেরত "VK_ERROR_VALIDATION_FAILED_EXT";
    ক্ষেত্র VK_ERROR_INVALID_SHADER_NV:
        ফেরত "VK_ERROR_INVALID_SHADER_NV";
#যদি VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    ক্ষেত্র VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        ফেরত "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    ক্ষেত্র VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        ফেরত "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    ক্ষেত্র VK_ERROR_NOT_PERMITTED_EXT:
        ফেরত "VK_ERROR_NOT_PERMITTED_EXT";
    ক্ষেত্র VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        ফেরত "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    ক্ষেত্র VK_THREAD_IDLE_KHR:
        ফেরত "VK_THREAD_IDLE_KHR";
    ক্ষেত্র VK_THREAD_DONE_KHR:
        ফেরত "VK_THREAD_DONE_KHR";
    ক্ষেত্র VK_OPERATION_DEFERRED_KHR:
        ফেরত "VK_OPERATION_DEFERRED_KHR";
    ক্ষেত্র VK_OPERATION_NOT_DEFERRED_KHR:
        ফেরত "VK_OPERATION_NOT_DEFERRED_KHR";
    ক্ষেত্র VK_PIPELINE_COMPILE_REQUIRED_EXT:
        ফেরত "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    পূর্বনির্ধারিত:
        বিরতি;
    }
    যদি (ফলাফল < 0) {
        ফেরত "VK_ERROR_<Unknown>";
    }
    ফেরত "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_গুনতি)
{
    Uint32 গুনতি = 0;
    Vk_ফলাফল rc = vkEnumerateInstanceExtensionProperties(ফাঁকা, &গুনতি, ফাঁকা);
    VkExtensionProperties *ফলাফল;

    যদি (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_Get_ফলাফল_String(rc),
            (পূর্ণসংখ্যা)rc);
        ফেরত ফাঁকা;
    } অন্যথা যদি (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ফলাফল_String(rc),
            (পূর্ণসংখ্যা)rc);
        ফেরত ফাঁকা;
    }

    যদি (গুনতি == 0) {
        ফলাফল = (VkExtensionProperties *)SDL_calloc(1, আকার(VkExtensionProperties)); // so we can return non-null
    } অন্যথা {
        ফলাফল = (VkExtensionProperties *)SDL_calloc(গুনতি, আকার(VkExtensionProperties));
    }

    যদি (!ফলাফল) {
        ফেরত ফাঁকা;
    }

    rc = vkEnumerateInstanceExtensionProperties(ফাঁকা, &গুনতি, ফলাফল);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_Get_ফলাফল_String(rc),
            (পূর্ণসংখ্যা)rc);
        SDL_free(ফলাফল);
        ফেরত ফাঁকা;
    }
    *extension_গুনতি = গুনতি;
    ফেরত ফলাফল;
}

// Alpha modes, in order of preference
স্থির ধ্রুবক VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(শূন্য *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ধ্রুবক কাঠামো VkAllocationCallbacks *allocator,
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
    Vk_ফলাফল rc;
    uint32_t physical_Device_গুনতি = 0;
    VkPhysicalDevice *physicalDevices = ফাঁকা;
    uint32_t physical_Device_সূচক;
    ধ্রুবক অক্ষর *chosenDisplayId;
    পূর্ণসংখ্যা displayId = 0; // Counting from physical device 0, display 0

    যদি (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        যাও error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    যদি (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_গুনতি, ফাঁকা);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        যাও error;
    }

    যদি (physical_Device_গুনতি == 0) {
        SDL_SetError("No Vulkan physical devices");
        যাও error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(আকার(VkPhysicalDevice) * physical_Device_গুনতি);
    যদি (!physicalDevices) {
        যাও error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_গুনতি, physicalDevices);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        যাও error;
    }

    জন্য (physical_Device_সূচক = 0; physical_Device_সূচক < physical_Device_গুনতি; physical_Device_সূচক++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physical_Device_সূচক];
        uint32_t display_Properties_গুনতি = 0;
        VkDisplayPropertiesKHR *displayProperties = ফাঁকা;
        uint32_t display_Mode_Properties_গুনতি = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = ফাঁকা;
        পূর্ণসংখ্যা best_Match_সূচক = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_গুনতি = 0;
        পূর্ণসংখ্যা plane_সূচক = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ফাঁকা;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_গুনতি, ফাঁকা);
        যদি (rc != VK_SUCCESS || display_Properties_গুনতি == 0) {
            // This device has no physical device display properties, move on to next.
            চালু;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physical_Device_সূচক, display_Properties_গুনতি);

        যদি (displayId < 0 || (uint32_t)displayId >= display_Properties_গুনতি) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_গুনতি;
            চালু;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(আকার(VkDisplayPropertiesKHR) * display_Properties_গুনতি);
        যদি (!displayProperties) {
            যাও error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_গুনতি, displayProperties);
        যদি (rc != VK_SUCCESS || display_Properties_গুনতি == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            যাও error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = ফাঁকা;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_গুনতি, ফাঁকা);
        যদি (rc != VK_SUCCESS || display_Mode_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display modes");
            যাও error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_গুনতি);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(আকার(VkDisplayModePropertiesKHR) * display_Mode_Properties_গুনতি);
        যদি (!displayModeProperties) {
            যাও error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_গুনতি, displayModeProperties);
        যদি (rc != VK_SUCCESS || display_Mode_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            যাও error;
        }

        // Try to find a display mode that matches the native resolution
        জন্য (i = 0; i < display_Mode_Properties_গুনতি; ++i) {
            যদি (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                best_Match_সূচক = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        যদি (best_Match_সূচক < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            যাও error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[best_Match_সূচক].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[best_Match_সূচক].parameters.visibleRegion.width,
                     displayModeProperties[best_Match_সূচক].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = ফাঁকা;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_গুনতি, ফাঁকা);
        যদি (rc != VK_SUCCESS || display_Plane_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display planes");
            যাও error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_গুনতি);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(আকার(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_গুনতি);
        যদি (!displayPlaneProperties) {
            যাও error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_গুনতি, displayPlaneProperties);
        যদি (rc != VK_SUCCESS || display_Plane_Properties_গুনতি == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            যাও error;
        }

        জন্য (i = 0; i < display_Plane_Properties_গুনতি; ++i) {
            uint32_t plane_Supported_Displays_গুনতি = 0;
            VkDisplayKHR *planeSupportedDisplays = ফাঁকা;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            যদি (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                চালু;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_গুনতি, ফাঁকা);
            যদি (rc != VK_SUCCESS || plane_Supported_Displays_গুনতি == 0) {
                চালু; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_গুনতি);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(আকার(VkDisplayKHR) * plane_Supported_Displays_গুনতি);
            যদি (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                যাও error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_গুনতি, planeSupportedDisplays);
            যদি (rc != VK_SUCCESS || plane_Supported_Displays_গুনতি == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                যাও error;
            }

            জন্য (j = 0; j < plane_Supported_Displays_গুনতি && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ফাঁকা;

            যদি (j == plane_Supported_Displays_গুনতি) {
                // This display is not supported for this plane, move on.
                চালু;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            যদি (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                যাও error;
            }

            // Check if plane fulfills extent requirements.
            যদি (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                plane_সূচক = i;
                বিরতি;
            }
        }

        যদি (plane_সূচক < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            যাও error;
        }

        createInfo.plane_সূচক = plane_সূচক;
        createInfo.plane_স্তূপ_সূচক = displayPlaneProperties[plane_সূচক].current_স্তূপ_সূচক;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ফাঁকা;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        জন্য (i = 0; i < SDL_arraysize(alphaModes); i++) {
            যদি (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                বিরতি;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        বিরতি;
    }

    SDL_free(physicalDevices);
    physicalDevices = ফাঁকা;

    যদি (physical_Device_সূচক == physical_Device_গুনতি) {
        SDL_SetError("No usable displays found or requested display out of range");
        যাও error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    যদি (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_Get_ফলাফল_String(rc));
        যাও error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    ফেরত true;

error:
    SDL_free(physicalDevices);
    ফেরত false;
}

শূন্য SDL_Vulkan_DestroySurface_Internal(শূন্য *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ধ্রুবক কাঠামো VkAllocationCallbacks *allocator)
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

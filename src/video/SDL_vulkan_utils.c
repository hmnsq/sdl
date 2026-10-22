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
#شامل "SDL_internal.h"

#شامل "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

ثابت نویسه *SDL_Vulkan_GetResultString(VkResult result)
{
    انتخاب ((صحیح)result) {
    حالت VK_SUCCESS:
        بازگشت "VK_SUCCESS";
    حالت VK_NOT_READY:
        بازگشت "VK_NOT_READY";
    حالت VK_TIMEOUT:
        بازگشت "VK_TIMEOUT";
    حالت VK_EVENT_SET:
        بازگشت "VK_EVENT_SET";
    حالت VK_EVENT_RESET:
        بازگشت "VK_EVENT_RESET";
    حالت VK_INCOMPLETE:
        بازگشت "VK_INCOMPLETE";
    حالت VK_ERROR_OUT_OF_HOST_MEMORY:
        بازگشت "VK_ERROR_OUT_OF_HOST_MEMORY";
    حالت VK_ERROR_OUT_OF_DEVICE_MEMORY:
        بازگشت "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    حالت VK_ERROR_INITIALIZATION_FAILED:
        بازگشت "VK_ERROR_INITIALIZATION_FAILED";
    حالت VK_ERROR_DEVICE_LOST:
        بازگشت "VK_ERROR_DEVICE_LOST";
    حالت VK_ERROR_MEMORY_MAP_FAILED:
        بازگشت "VK_ERROR_MEMORY_MAP_FAILED";
    حالت VK_ERROR_LAYER_NOT_PRESENT:
        بازگشت "VK_ERROR_LAYER_NOT_PRESENT";
    حالت VK_ERROR_EXTENSION_NOT_PRESENT:
        بازگشت "VK_ERROR_EXTENSION_NOT_PRESENT";
    حالت VK_ERROR_FEATURE_NOT_PRESENT:
        بازگشت "VK_ERROR_FEATURE_NOT_PRESENT";
    حالت VK_ERROR_INCOMPATIBLE_DRIVER:
        بازگشت "VK_ERROR_INCOMPATIBLE_DRIVER";
    حالت VK_ERROR_TOO_MANY_OBJECTS:
        بازگشت "VK_ERROR_TOO_MANY_OBJECTS";
    حالت VK_ERROR_FORMAT_NOT_SUPPORTED:
        بازگشت "VK_ERROR_FORMAT_NOT_SUPPORTED";
    حالت VK_ERROR_FRAGMENTED_POOL:
        بازگشت "VK_ERROR_FRAGMENTED_POOL";
    حالت VK_ERROR_UNKNOWN:
        بازگشت "VK_ERROR_UNKNOWN";
    حالت VK_ERROR_OUT_OF_POOL_MEMORY:
        بازگشت "VK_ERROR_OUT_OF_POOL_MEMORY";
    حالت VK_ERROR_INVALID_EXTERNAL_HANDLE:
        بازگشت "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    حالت VK_ERROR_FRAGMENTATION:
        بازگشت "VK_ERROR_FRAGMENTATION";
    حالت VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        بازگشت "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    حالت VK_ERROR_SURFACE_LOST_KHR:
        بازگشت "VK_ERROR_SURFACE_LOST_KHR";
    حالت VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        بازگشت "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    حالت VK_SUBOPTIMAL_KHR:
        بازگشت "VK_SUBOPTIMAL_KHR";
    حالت VK_ERROR_OUT_OF_DATE_KHR:
        بازگشت "VK_ERROR_OUT_OF_DATE_KHR";
    حالت VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        بازگشت "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    حالت VK_ERROR_VALIDATION_FAILED_EXT:
        بازگشت "VK_ERROR_VALIDATION_FAILED_EXT";
    حالت VK_ERROR_INVALID_SHADER_NV:
        بازگشت "VK_ERROR_INVALID_SHADER_NV";
#اگر VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    حالت VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        بازگشت "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    حالت VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        بازگشت "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    حالت VK_ERROR_NOT_PERMITTED_EXT:
        بازگشت "VK_ERROR_NOT_PERMITTED_EXT";
    حالت VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        بازگشت "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    حالت VK_THREAD_IDLE_KHR:
        بازگشت "VK_THREAD_IDLE_KHR";
    حالت VK_THREAD_DONE_KHR:
        بازگشت "VK_THREAD_DONE_KHR";
    حالت VK_OPERATION_DEFERRED_KHR:
        بازگشت "VK_OPERATION_DEFERRED_KHR";
    حالت VK_OPERATION_NOT_DEFERRED_KHR:
        بازگشت "VK_OPERATION_NOT_DEFERRED_KHR";
    حالت VK_PIPELINE_COMPILE_REQUIRED_EXT:
        بازگشت "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    پیشفرض:
        بشکن;
    }
    اگر (result < 0) {
        بازگشت "VK_ERROR_<Unknown>";
    }
    بازگشت "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_شمار)
{
    Uint32 شمار = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(پوچ, &شمار, پوچ);
    VkExtensionProperties *result;

    اگر (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (صحیح)rc);
        بازگشت پوچ;
    } وگرنه اگر (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (صحیح)rc);
        بازگشت پوچ;
    }

    اگر (شمار == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, اندازه(VkExtensionProperties)); // so we can return non-null
    } وگرنه {
        result = (VkExtensionProperties *)SDL_calloc(شمار, اندازه(VkExtensionProperties));
    }

    اگر (!result) {
        بازگشت پوچ;
    }

    rc = vkEnumerateInstanceExtensionProperties(پوچ, &شمار, result);
    اگر (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (صحیح)rc);
        SDL_free(result);
        بازگشت پوچ;
    }
    *extension_شمار = شمار;
    بازگشت result;
}

// Alpha modes, in order of preference
ایستا ثابت VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(تهی *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ثابت ساختار VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_شمار = 0;
    VkPhysicalDevice *physicalDevices = پوچ;
    uint32_t physicalDeviceIndex;
    ثابت نویسه *chosenDisplayId;
    صحیح displayId = 0; // Counting from physical device 0, display 0

    اگر (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        برو error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    اگر (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_شمار, پوچ);
    اگر (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        برو error;
    }

    اگر (physical_Device_شمار == 0) {
        SDL_SetError("No Vulkan physical devices");
        برو error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(اندازه(VkPhysicalDevice) * physical_Device_شمار);
    اگر (!physicalDevices) {
        برو error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_شمار, physicalDevices);
    اگر (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        برو error;
    }

    برای (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_شمار; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_شمار = 0;
        VkDisplayPropertiesKHR *displayProperties = پوچ;
        uint32_t display_Mode_Properties_شمار = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = پوچ;
        صحیح bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_شمار = 0;
        صحیح planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = پوچ;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_شمار, پوچ);
        اگر (rc != VK_SUCCESS || display_Properties_شمار == 0) {
            // This device has no physical device display properties, move on to next.
            ادامه;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_شمار);

        اگر (displayId < 0 || (uint32_t)displayId >= display_Properties_شمار) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_شمار;
            ادامه;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(اندازه(VkDisplayPropertiesKHR) * display_Properties_شمار);
        اگر (!displayProperties) {
            برو error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_شمار, displayProperties);
        اگر (rc != VK_SUCCESS || display_Properties_شمار == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            برو error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = پوچ;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_شمار, پوچ);
        اگر (rc != VK_SUCCESS || display_Mode_Properties_شمار == 0) {
            SDL_SetError("Error enumerating display modes");
            برو error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_شمار);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(اندازه(VkDisplayModePropertiesKHR) * display_Mode_Properties_شمار);
        اگر (!displayModeProperties) {
            برو error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_شمار, displayModeProperties);
        اگر (rc != VK_SUCCESS || display_Mode_Properties_شمار == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            برو error;
        }

        // Try to find a display mode that matches the native resolution
        برای (i = 0; i < display_Mode_Properties_شمار; ++i) {
            اگر (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        اگر (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            برو error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = پوچ;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_شمار, پوچ);
        اگر (rc != VK_SUCCESS || display_Plane_Properties_شمار == 0) {
            SDL_SetError("Error enumerating display planes");
            برو error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_شمار);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(اندازه(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_شمار);
        اگر (!displayPlaneProperties) {
            برو error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_شمار, displayPlaneProperties);
        اگر (rc != VK_SUCCESS || display_Plane_Properties_شمار == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            برو error;
        }

        برای (i = 0; i < display_Plane_Properties_شمار; ++i) {
            uint32_t plane_Supported_Displays_شمار = 0;
            VkDisplayKHR *planeSupportedDisplays = پوچ;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            اگر (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                ادامه;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_شمار, پوچ);
            اگر (rc != VK_SUCCESS || plane_Supported_Displays_شمار == 0) {
                ادامه; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_شمار);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(اندازه(VkDisplayKHR) * plane_Supported_Displays_شمار);
            اگر (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                برو error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_شمار, planeSupportedDisplays);
            اگر (rc != VK_SUCCESS || plane_Supported_Displays_شمار == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                برو error;
            }

            برای (j = 0; j < plane_Supported_Displays_شمار && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = پوچ;

            اگر (j == plane_Supported_Displays_شمار) {
                // This display is not supported for this plane, move on.
                ادامه;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            اگر (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                برو error;
            }

            // Check if plane fulfills extent requirements.
            اگر (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                بشکن;
            }
        }

        اگر (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            برو error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_پشته_Index = displayPlaneProperties[planeIndex].current_پشته_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = پوچ;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        برای (i = 0; i < SDL_arraysize(alphaModes); i++) {
            اگر (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                بشکن;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        بشکن;
    }

    SDL_free(physicalDevices);
    physicalDevices = پوچ;

    اگر (physicalDeviceIndex == physical_Device_شمار) {
        SDL_SetError("No usable displays found or requested display out of range");
        برو error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    اگر (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        برو error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    بازگشت true;

error:
    SDL_free(physicalDevices);
    بازگشت false;
}

تهی SDL_Vulkan_DestroySurface_Internal(تهی *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ثابت ساختار VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    اگر (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

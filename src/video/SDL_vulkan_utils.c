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
#ضمن "SDL_internal.h"

#ضمن "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

ثابت حرف *SDL_Vulkan_GetResultString(VkResult result)
{
    بدل ((صحيح)result) {
    حالة VK_SUCCESS:
        החזר "VK_SUCCESS";
    حالة VK_NOT_READY:
        החזר "VK_NOT_READY";
    حالة VK_TIMEOUT:
        החזר "VK_TIMEOUT";
    حالة VK_EVENT_SET:
        החזר "VK_EVENT_SET";
    حالة VK_EVENT_RESET:
        החזר "VK_EVENT_RESET";
    حالة VK_INCOMPLETE:
        החזר "VK_INCOMPLETE";
    حالة VK_ERROR_OUT_OF_HOST_MEMORY:
        החזר "VK_ERROR_OUT_OF_HOST_MEMORY";
    حالة VK_ERROR_OUT_OF_DEVICE_MEMORY:
        החזר "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    حالة VK_ERROR_INITIALIZATION_FAILED:
        החזר "VK_ERROR_INITIALIZATION_FAILED";
    حالة VK_ERROR_DEVICE_LOST:
        החזר "VK_ERROR_DEVICE_LOST";
    حالة VK_ERROR_MEMORY_MAP_FAILED:
        החזר "VK_ERROR_MEMORY_MAP_FAILED";
    حالة VK_ERROR_LAYER_NOT_PRESENT:
        החזר "VK_ERROR_LAYER_NOT_PRESENT";
    حالة VK_ERROR_EXTENSION_NOT_PRESENT:
        החזר "VK_ERROR_EXTENSION_NOT_PRESENT";
    حالة VK_ERROR_FEATURE_NOT_PRESENT:
        החזר "VK_ERROR_FEATURE_NOT_PRESENT";
    حالة VK_ERROR_INCOMPATIBLE_DRIVER:
        החזר "VK_ERROR_INCOMPATIBLE_DRIVER";
    حالة VK_ERROR_TOO_MANY_OBJECTS:
        החזר "VK_ERROR_TOO_MANY_OBJECTS";
    حالة VK_ERROR_FORMAT_NOT_SUPPORTED:
        החזר "VK_ERROR_FORMAT_NOT_SUPPORTED";
    حالة VK_ERROR_FRAGMENTED_POOL:
        החזר "VK_ERROR_FRAGMENTED_POOL";
    حالة VK_ERROR_UNKNOWN:
        החזר "VK_ERROR_UNKNOWN";
    حالة VK_ERROR_OUT_OF_POOL_MEMORY:
        החזר "VK_ERROR_OUT_OF_POOL_MEMORY";
    حالة VK_ERROR_INVALID_EXTERNAL_HANDLE:
        החזר "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    حالة VK_ERROR_FRAGMENTATION:
        החזר "VK_ERROR_FRAGMENTATION";
    حالة VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        החזר "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    حالة VK_ERROR_SURFACE_LOST_KHR:
        החזר "VK_ERROR_SURFACE_LOST_KHR";
    حالة VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        החזר "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    حالة VK_SUBOPTIMAL_KHR:
        החזר "VK_SUBOPTIMAL_KHR";
    حالة VK_ERROR_OUT_OF_DATE_KHR:
        החזר "VK_ERROR_OUT_OF_DATE_KHR";
    حالة VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        החזר "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    حالة VK_ERROR_VALIDATION_FAILED_EXT:
        החזר "VK_ERROR_VALIDATION_FAILED_EXT";
    حالة VK_ERROR_INVALID_SHADER_NV:
        החזר "VK_ERROR_INVALID_SHADER_NV";
#אם VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    حالة VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        החזר "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    حالة VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        החזר "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    حالة VK_ERROR_NOT_PERMITTED_EXT:
        החזר "VK_ERROR_NOT_PERMITTED_EXT";
    حالة VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        החזר "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    حالة VK_THREAD_IDLE_KHR:
        החזר "VK_THREAD_IDLE_KHR";
    حالة VK_THREAD_DONE_KHR:
        החזר "VK_THREAD_DONE_KHR";
    حالة VK_OPERATION_DEFERRED_KHR:
        החזר "VK_OPERATION_DEFERRED_KHR";
    حالة VK_OPERATION_NOT_DEFERRED_KHR:
        החזר "VK_OPERATION_NOT_DEFERRED_KHR";
    حالة VK_PIPELINE_COMPILE_REQUIRED_EXT:
        החזר "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    افتراضي:
        اكسر;
    }
    אם (result < 0) {
        החזר "VK_ERROR_<Unknown>";
    }
    החזר "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extensionCount)
{
    Uint32 count = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(عدم, &count, عدم);
    VkExtensionProperties *result;

    אם (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (صحيح)rc);
        החזר عدم;
    } אחרת אם (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (صحيح)rc);
        החזר عدم;
    }

    אם (count == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, حجم(VkExtensionProperties)); // so we can return non-null
    } אחרת {
        result = (VkExtensionProperties *)SDL_calloc(count, حجم(VkExtensionProperties));
    }

    אם (!result) {
        החזר عدم;
    }

    rc = vkEnumerateInstanceExtensionProperties(عدم, &count, result);
    אם (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (صحيح)rc);
        SDL_free(result);
        החזר عدم;
    }
    *extensionCount = count;
    החזר result;
}

// Alpha modes, in order of preference
ساكن ثابت VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(فراغ *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      ثابت بنية VkAllocationCallbacks *allocator,
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
    uint32_t physicalDeviceCount = 0;
    VkPhysicalDevice *physicalDevices = عدم;
    uint32_t physicalDeviceIndex;
    ثابت حرف *chosenDisplayId;
    صحيح displayId = 0; // Counting from physical device 0, display 0

    אם (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        اذهب error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    אם (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, عدم);
    אם (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        اذهب error;
    }

    אם (physicalDeviceCount == 0) {
        SDL_SetError("No Vulkan physical devices");
        اذهب error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(حجم(VkPhysicalDevice) * physicalDeviceCount);
    אם (!physicalDevices) {
        اذهب error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);
    אם (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        اذهب error;
    }

    עבור (physicalDeviceIndex = 0; physicalDeviceIndex < physicalDeviceCount; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t displayPropertiesCount = 0;
        VkDisplayPropertiesKHR *displayProperties = عدم;
        uint32_t displayModePropertiesCount = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = عدم;
        صحيح bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t displayPlanePropertiesCount = 0;
        صحيح planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = عدم;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, عدم);
        אם (rc != VK_SUCCESS || displayPropertiesCount == 0) {
            // This device has no physical device display properties, move on to next.
            استمر;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, displayPropertiesCount);

        אם (displayId < 0 || (uint32_t)displayId >= displayPropertiesCount) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= displayPropertiesCount;
            استمر;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(حجم(VkDisplayPropertiesKHR) * displayPropertiesCount);
        אם (!displayProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, displayProperties);
        אם (rc != VK_SUCCESS || displayPropertiesCount == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            اذهب error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = عدم;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &displayModePropertiesCount, عدم);
        אם (rc != VK_SUCCESS || displayModePropertiesCount == 0) {
            SDL_SetError("Error enumerating display modes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", displayModePropertiesCount);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(حجم(VkDisplayModePropertiesKHR) * displayModePropertiesCount);
        אם (!displayModeProperties) {
            اذهب error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &displayModePropertiesCount, displayModeProperties);
        אם (rc != VK_SUCCESS || displayModePropertiesCount == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            اذهب error;
        }

        // Try to find a display mode that matches the native resolution
        עבור (i = 0; i < displayModePropertiesCount; ++i) {
            אם (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        אם (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            اذهب error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = عدم;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesCount, عدم);
        אם (rc != VK_SUCCESS || displayPlanePropertiesCount == 0) {
            SDL_SetError("Error enumerating display planes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", displayPlanePropertiesCount);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * displayPlanePropertiesCount);
        אם (!displayPlaneProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesCount, displayPlaneProperties);
        אם (rc != VK_SUCCESS || displayPlanePropertiesCount == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        עבור (i = 0; i < displayPlanePropertiesCount; ++i) {
            uint32_t planeSupportedDisplaysCount = 0;
            VkDisplayKHR *planeSupportedDisplays = عدم;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            אם (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                استمر;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &planeSupportedDisplaysCount, عدم);
            אם (rc != VK_SUCCESS || planeSupportedDisplaysCount == 0) {
                استمر; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, planeSupportedDisplaysCount);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * planeSupportedDisplaysCount);
            אם (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &planeSupportedDisplaysCount, planeSupportedDisplays);
            אם (rc != VK_SUCCESS || planeSupportedDisplaysCount == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            עבור (j = 0; j < planeSupportedDisplaysCount && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = عدم;

            אם (j == planeSupportedDisplaysCount) {
                // This display is not supported for this plane, move on.
                استمر;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            אם (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            // Check if plane fulfills extent requirements.
            אם (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                اكسر;
            }
        }

        אם (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.planeStackIndex = displayPlaneProperties[planeIndex].currentStackIndex;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = عدم;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        עבור (i = 0; i < SDL_arraysize(alphaModes); i++) {
            אם (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                اكسر;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        اكسر;
    }

    SDL_free(physicalDevices);
    physicalDevices = عدم;

    אם (physicalDeviceIndex == physicalDeviceCount) {
        SDL_SetError("No usable displays found or requested display out of range");
        اذهب error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    אם (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        اذهب error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    החזר true;

error:
    SDL_free(physicalDevices);
    החזר false;
}

فراغ SDL_Vulkan_DestroySurface_Internal(فراغ *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        ثابت بنية VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    אם (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

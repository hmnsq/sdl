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
#include "SDL_internal.h"

#include "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

const char *SDL_Vulkan_GetResultString(VkResult result)
{
    switch ((整数)result) {
    case VK_SUCCESS:
        返回 "VK_SUCCESS";
    case VK_NOT_READY:
        返回 "VK_NOT_READY";
    case VK_TIMEOUT:
        返回 "VK_TIMEOUT";
    case VK_EVENT_SET:
        返回 "VK_EVENT_SET";
    case VK_EVENT_RESET:
        返回 "VK_EVENT_RESET";
    case VK_INCOMPLETE:
        返回 "VK_INCOMPLETE";
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        返回 "VK_ERROR_OUT_OF_HOST_MEMORY";
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        返回 "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    case VK_ERROR_INITIALIZATION_FAILED:
        返回 "VK_ERROR_INITIALIZATION_FAILED";
    case VK_ERROR_DEVICE_LOST:
        返回 "VK_ERROR_DEVICE_LOST";
    case VK_ERROR_MEMORY_MAP_FAILED:
        返回 "VK_ERROR_MEMORY_MAP_FAILED";
    case VK_ERROR_LAYER_NOT_PRESENT:
        返回 "VK_ERROR_LAYER_NOT_PRESENT";
    case VK_ERROR_EXTENSION_NOT_PRESENT:
        返回 "VK_ERROR_EXTENSION_NOT_PRESENT";
    case VK_ERROR_FEATURE_NOT_PRESENT:
        返回 "VK_ERROR_FEATURE_NOT_PRESENT";
    case VK_ERROR_INCOMPATIBLE_DRIVER:
        返回 "VK_ERROR_INCOMPATIBLE_DRIVER";
    case VK_ERROR_TOO_MANY_OBJECTS:
        返回 "VK_ERROR_TOO_MANY_OBJECTS";
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
        返回 "VK_ERROR_FORMAT_NOT_SUPPORTED";
    case VK_ERROR_FRAGMENTED_POOL:
        返回 "VK_ERROR_FRAGMENTED_POOL";
    case VK_ERROR_UNKNOWN:
        返回 "VK_ERROR_UNKNOWN";
    case VK_ERROR_OUT_OF_POOL_MEMORY:
        返回 "VK_ERROR_OUT_OF_POOL_MEMORY";
    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
        返回 "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    case VK_ERROR_FRAGMENTATION:
        返回 "VK_ERROR_FRAGMENTATION";
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        返回 "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    case VK_ERROR_SURFACE_LOST_KHR:
        返回 "VK_ERROR_SURFACE_LOST_KHR";
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        返回 "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    case VK_SUBOPTIMAL_KHR:
        返回 "VK_SUBOPTIMAL_KHR";
    case VK_ERROR_OUT_OF_DATE_KHR:
        返回 "VK_ERROR_OUT_OF_DATE_KHR";
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        返回 "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    case VK_ERROR_VALIDATION_FAILED_EXT:
        返回 "VK_ERROR_VALIDATION_FAILED_EXT";
    case VK_ERROR_INVALID_SHADER_NV:
        返回 "VK_ERROR_INVALID_SHADER_NV";
#如果 VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    case VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        返回 "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        返回 "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    case VK_ERROR_NOT_PERMITTED_EXT:
        返回 "VK_ERROR_NOT_PERMITTED_EXT";
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        返回 "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    case VK_THREAD_IDLE_KHR:
        返回 "VK_THREAD_IDLE_KHR";
    case VK_THREAD_DONE_KHR:
        返回 "VK_THREAD_DONE_KHR";
    case VK_OPERATION_DEFERRED_KHR:
        返回 "VK_OPERATION_DEFERRED_KHR";
    case VK_OPERATION_NOT_DEFERRED_KHR:
        返回 "VK_OPERATION_NOT_DEFERRED_KHR";
    case VK_PIPELINE_COMPILE_REQUIRED_EXT:
        返回 "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    default:
        break;
    }
    如果 (result < 0) {
        返回 "VK_ERROR_<Unknown>";
    }
    返回 "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extensionCount)
{
    Uint32 count = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(NULL, &count, NULL);
    VkExtensionProperties *result;

    如果 (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (整数)rc);
        返回 NULL;
    } 否则 如果 (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (整数)rc);
        返回 NULL;
    }

    如果 (count == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, sizeof(VkExtensionProperties)); // so we can return non-null
    } 否则 {
        result = (VkExtensionProperties *)SDL_calloc(count, sizeof(VkExtensionProperties));
    }

    如果 (!result) {
        返回 NULL;
    }

    rc = vkEnumerateInstanceExtensionProperties(NULL, &count, result);
    如果 (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (整数)rc);
        SDL_free(result);
        返回 NULL;
    }
    *extensionCount = count;
    返回 result;
}

// Alpha modes, in order of preference
static const VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(void *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      const struct VkAllocationCallbacks *allocator,
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
    VkPhysicalDevice *physicalDevices = NULL;
    uint32_t physicalDeviceIndex;
    const char *chosenDisplayId;
    整数 displayId = 0; // Counting from physical device 0, display 0

    如果 (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        goto error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    如果 (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, NULL);
    如果 (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        goto error;
    }

    如果 (physicalDeviceCount == 0) {
        SDL_SetError("No Vulkan physical devices");
        goto error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(sizeof(VkPhysicalDevice) * physicalDeviceCount);
    如果 (!physicalDevices) {
        goto error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);
    如果 (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        goto error;
    }

    为 (physicalDeviceIndex = 0; physicalDeviceIndex < physicalDeviceCount; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t displayPropertiesCount = 0;
        VkDisplayPropertiesKHR *displayProperties = NULL;
        uint32_t displayModePropertiesCount = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = NULL;
        整数 bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t displayPlanePropertiesCount = 0;
        整数 planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = NULL;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, NULL);
        如果 (rc != VK_SUCCESS || displayPropertiesCount == 0) {
            // This device has no physical device display properties, move on to next.
            continue;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, displayPropertiesCount);

        如果 (displayId < 0 || (uint32_t)displayId >= displayPropertiesCount) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= displayPropertiesCount;
            continue;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(sizeof(VkDisplayPropertiesKHR) * displayPropertiesCount);
        如果 (!displayProperties) {
            goto error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, displayProperties);
        如果 (rc != VK_SUCCESS || displayPropertiesCount == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            goto error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = NULL;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &displayModePropertiesCount, NULL);
        如果 (rc != VK_SUCCESS || displayModePropertiesCount == 0) {
            SDL_SetError("Error enumerating display modes");
            goto error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", displayModePropertiesCount);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(sizeof(VkDisplayModePropertiesKHR) * displayModePropertiesCount);
        如果 (!displayModeProperties) {
            goto error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &displayModePropertiesCount, displayModeProperties);
        如果 (rc != VK_SUCCESS || displayModePropertiesCount == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            goto error;
        }

        // Try to find a display mode that matches the native resolution
        为 (i = 0; i < displayModePropertiesCount; ++i) {
            如果 (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        如果 (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            goto error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = NULL;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesCount, NULL);
        如果 (rc != VK_SUCCESS || displayPlanePropertiesCount == 0) {
            SDL_SetError("Error enumerating display planes");
            goto error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", displayPlanePropertiesCount);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(sizeof(VkDisplayPlanePropertiesKHR) * displayPlanePropertiesCount);
        如果 (!displayPlaneProperties) {
            goto error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesCount, displayPlaneProperties);
        如果 (rc != VK_SUCCESS || displayPlanePropertiesCount == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            goto error;
        }

        为 (i = 0; i < displayPlanePropertiesCount; ++i) {
            uint32_t planeSupportedDisplaysCount = 0;
            VkDisplayKHR *planeSupportedDisplays = NULL;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            如果 (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                continue;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &planeSupportedDisplaysCount, NULL);
            如果 (rc != VK_SUCCESS || planeSupportedDisplaysCount == 0) {
                continue; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, planeSupportedDisplaysCount);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(sizeof(VkDisplayKHR) * planeSupportedDisplaysCount);
            如果 (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                goto error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &planeSupportedDisplaysCount, planeSupportedDisplays);
            如果 (rc != VK_SUCCESS || planeSupportedDisplaysCount == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                goto error;
            }

            为 (j = 0; j < planeSupportedDisplaysCount && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = NULL;

            如果 (j == planeSupportedDisplaysCount) {
                // This display is not supported for this plane, move on.
                continue;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            如果 (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                goto error;
            }

            // Check if plane fulfills extent requirements.
            如果 (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                break;
            }
        }

        如果 (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            goto error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.planeStackIndex = displayPlaneProperties[planeIndex].currentStackIndex;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = NULL;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        为 (i = 0; i < SDL_arraysize(alphaModes); i++) {
            如果 (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                break;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        break;
    }

    SDL_free(physicalDevices);
    physicalDevices = NULL;

    如果 (physicalDeviceIndex == physicalDeviceCount) {
        SDL_SetError("No usable displays found or requested display out of range");
        goto error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    如果 (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        goto error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    返回 true;

error:
    SDL_free(physicalDevices);
    返回 false;
}

void SDL_Vulkan_DestroySurface_Internal(void *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        const struct VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    如果 (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

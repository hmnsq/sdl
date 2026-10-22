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

const var_na *SDL_Vulkan_GetResultString(VkResult result)
{
    switch ((จำนวนเต็ม)result) {
    pak_sa VK_SUCCESS:
        คืน "VK_SUCCESS";
    pak_sa VK_NOT_READY:
        คืน "VK_NOT_READY";
    pak_sa VK_TIMEOUT:
        คืน "VK_TIMEOUT";
    pak_sa VK_EVENT_SET:
        คืน "VK_EVENT_SET";
    pak_sa VK_EVENT_RESET:
        คืน "VK_EVENT_RESET";
    pak_sa VK_INCOMPLETE:
        คืน "VK_INCOMPLETE";
    pak_sa VK_ERROR_OUT_OF_HOST_MEMORY:
        คืน "VK_ERROR_OUT_OF_HOST_MEMORY";
    pak_sa VK_ERROR_OUT_OF_DEVICE_MEMORY:
        คืน "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    pak_sa VK_ERROR_INITIALIZATION_FAILED:
        คืน "VK_ERROR_INITIALIZATION_FAILED";
    pak_sa VK_ERROR_DEVICE_LOST:
        คืน "VK_ERROR_DEVICE_LOST";
    pak_sa VK_ERROR_MEMORY_MAP_FAILED:
        คืน "VK_ERROR_MEMORY_MAP_FAILED";
    pak_sa VK_ERROR_LAYER_NOT_PRESENT:
        คืน "VK_ERROR_LAYER_NOT_PRESENT";
    pak_sa VK_ERROR_EXTENSION_NOT_PRESENT:
        คืน "VK_ERROR_EXTENSION_NOT_PRESENT";
    pak_sa VK_ERROR_FEATURE_NOT_PRESENT:
        คืน "VK_ERROR_FEATURE_NOT_PRESENT";
    pak_sa VK_ERROR_INCOMPATIBLE_DRIVER:
        คืน "VK_ERROR_INCOMPATIBLE_DRIVER";
    pak_sa VK_ERROR_TOO_MANY_OBJECTS:
        คืน "VK_ERROR_TOO_MANY_OBJECTS";
    pak_sa VK_ERROR_FORMAT_NOT_SUPPORTED:
        คืน "VK_ERROR_FORMAT_NOT_SUPPORTED";
    pak_sa VK_ERROR_FRAGMENTED_POOL:
        คืน "VK_ERROR_FRAGMENTED_POOL";
    pak_sa VK_ERROR_UNKNOWN:
        คืน "VK_ERROR_UNKNOWN";
    pak_sa VK_ERROR_OUT_OF_POOL_MEMORY:
        คืน "VK_ERROR_OUT_OF_POOL_MEMORY";
    pak_sa VK_ERROR_INVALID_EXTERNAL_HANDLE:
        คืน "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    pak_sa VK_ERROR_FRAGMENTATION:
        คืน "VK_ERROR_FRAGMENTATION";
    pak_sa VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        คืน "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    pak_sa VK_ERROR_SURFACE_LOST_KHR:
        คืน "VK_ERROR_SURFACE_LOST_KHR";
    pak_sa VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        คืน "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    pak_sa VK_SUBOPTIMAL_KHR:
        คืน "VK_SUBOPTIMAL_KHR";
    pak_sa VK_ERROR_OUT_OF_DATE_KHR:
        คืน "VK_ERROR_OUT_OF_DATE_KHR";
    pak_sa VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        คืน "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    pak_sa VK_ERROR_VALIDATION_FAILED_EXT:
        คืน "VK_ERROR_VALIDATION_FAILED_EXT";
    pak_sa VK_ERROR_INVALID_SHADER_NV:
        คืน "VK_ERROR_INVALID_SHADER_NV";
#ถ้า VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    pak_sa VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        คืน "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    pak_sa VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        คืน "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    pak_sa VK_ERROR_NOT_PERMITTED_EXT:
        คืน "VK_ERROR_NOT_PERMITTED_EXT";
    pak_sa VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        คืน "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    pak_sa VK_THREAD_IDLE_KHR:
        คืน "VK_THREAD_IDLE_KHR";
    pak_sa VK_THREAD_DONE_KHR:
        คืน "VK_THREAD_DONE_KHR";
    pak_sa VK_OPERATION_DEFERRED_KHR:
        คืน "VK_OPERATION_DEFERRED_KHR";
    pak_sa VK_OPERATION_NOT_DEFERRED_KHR:
        คืน "VK_OPERATION_NOT_DEFERRED_KHR";
    pak_sa VK_PIPELINE_COMPILE_REQUIRED_EXT:
        คืน "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    default:
        bha_nga;
    }
    ถ้า (result < 0) {
        คืน "VK_ERROR_<Unknown>";
    }
    คืน "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extensionCount)
{
    Uint32 count = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(NULL, &count, NULL);
    VkExtensionProperties *result;

    ถ้า (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (จำนวนเต็ม)rc);
        คืน NULL;
    } มิฉะนั้น ถ้า (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (จำนวนเต็ม)rc);
        คืน NULL;
    }

    ถ้า (count == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, parimaa_na(VkExtensionProperties)); // so we can return non-null
    } มิฉะนั้น {
        result = (VkExtensionProperties *)SDL_calloc(count, parimaa_na(VkExtensionProperties));
    }

    ถ้า (!result) {
        คืน NULL;
    }

    rc = vkEnumerateInstanceExtensionProperties(NULL, &count, result);
    ถ้า (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (จำนวนเต็ม)rc);
        SDL_free(result);
        คืน NULL;
    }
    *extensionCount = count;
    คืน result;
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
                                      const sa_nracanaa VkAllocationCallbacks *allocator,
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
    const var_na *chosenDisplayId;
    จำนวนเต็ม displayId = 0; // Counting from physical device 0, display 0

    ถ้า (!vkEnumeratePhysicalDevices ||
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
    ถ้า (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, NULL);
    ถ้า (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        goto error;
    }

    ถ้า (physicalDeviceCount == 0) {
        SDL_SetError("No Vulkan physical devices");
        goto error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(parimaa_na(VkPhysicalDevice) * physicalDeviceCount);
    ถ้า (!physicalDevices) {
        goto error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);
    ถ้า (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        goto error;
    }

    สำหรับ (physicalDeviceIndex = 0; physicalDeviceIndex < physicalDeviceCount; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t displayPropertiesCount = 0;
        VkDisplayPropertiesKHR *displayProperties = NULL;
        uint32_t displayModePropertiesCount = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = NULL;
        จำนวนเต็ม bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t displayPlanePropertiesCount = 0;
        จำนวนเต็ม planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = NULL;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, NULL);
        ถ้า (rc != VK_SUCCESS || displayPropertiesCount == 0) {
            // This device has no physical device display properties, move on to next.
            continue;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, displayPropertiesCount);

        ถ้า (displayId < 0 || (uint32_t)displayId >= displayPropertiesCount) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= displayPropertiesCount;
            continue;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(parimaa_na(VkDisplayPropertiesKHR) * displayPropertiesCount);
        ถ้า (!displayProperties) {
            goto error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &displayPropertiesCount, displayProperties);
        ถ้า (rc != VK_SUCCESS || displayPropertiesCount == 0) {
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
        ถ้า (rc != VK_SUCCESS || displayModePropertiesCount == 0) {
            SDL_SetError("Error enumerating display modes");
            goto error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", displayModePropertiesCount);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(parimaa_na(VkDisplayModePropertiesKHR) * displayModePropertiesCount);
        ถ้า (!displayModeProperties) {
            goto error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &displayModePropertiesCount, displayModeProperties);
        ถ้า (rc != VK_SUCCESS || displayModePropertiesCount == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            goto error;
        }

        // Try to find a display mode that matches the native resolution
        สำหรับ (i = 0; i < displayModePropertiesCount; ++i) {
            ถ้า (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        ถ้า (bestMatchIndex < 0) {
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
        ถ้า (rc != VK_SUCCESS || displayPlanePropertiesCount == 0) {
            SDL_SetError("Error enumerating display planes");
            goto error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", displayPlanePropertiesCount);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(parimaa_na(VkDisplayPlanePropertiesKHR) * displayPlanePropertiesCount);
        ถ้า (!displayPlaneProperties) {
            goto error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &displayPlanePropertiesCount, displayPlaneProperties);
        ถ้า (rc != VK_SUCCESS || displayPlanePropertiesCount == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            goto error;
        }

        สำหรับ (i = 0; i < displayPlanePropertiesCount; ++i) {
            uint32_t planeSupportedDisplaysCount = 0;
            VkDisplayKHR *planeSupportedDisplays = NULL;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            ถ้า (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                continue;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &planeSupportedDisplaysCount, NULL);
            ถ้า (rc != VK_SUCCESS || planeSupportedDisplaysCount == 0) {
                continue; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, planeSupportedDisplaysCount);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(parimaa_na(VkDisplayKHR) * planeSupportedDisplaysCount);
            ถ้า (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                goto error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &planeSupportedDisplaysCount, planeSupportedDisplays);
            ถ้า (rc != VK_SUCCESS || planeSupportedDisplaysCount == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                goto error;
            }

            สำหรับ (j = 0; j < planeSupportedDisplaysCount && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = NULL;

            ถ้า (j == planeSupportedDisplaysCount) {
                // This display is not supported for this plane, move on.
                continue;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            ถ้า (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                goto error;
            }

            // Check if plane fulfills extent requirements.
            ถ้า (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                bha_nga;
            }
        }

        ถ้า (planeIndex < 0) {
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
        สำหรับ (i = 0; i < SDL_arraysize(alphaModes); i++) {
            ถ้า (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                bha_nga;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        bha_nga;
    }

    SDL_free(physicalDevices);
    physicalDevices = NULL;

    ถ้า (physicalDeviceIndex == physicalDeviceCount) {
        SDL_SetError("No usable displays found or requested display out of range");
        goto error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    ถ้า (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        goto error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    คืน true;

error:
    SDL_free(physicalDevices);
    คืน false;
}

void SDL_Vulkan_DestroySurface_Internal(void *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        const sa_nracanaa VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    ถ้า (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

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
#અન્તર્ભાવ "SDL_internal.h"

#અન્તર્ભાવ "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

અચલ અક્ષર *SDL_Vulkan_GetResultString(VkResult result)
{
    પસંદગી ((પૂર્ણાંક)result) {
    સ્થિતિ VK_SUCCESS:
        પાછા "VK_SUCCESS";
    સ્થિતિ VK_NOT_READY:
        પાછા "VK_NOT_READY";
    સ્થિતિ VK_TIMEOUT:
        પાછા "VK_TIMEOUT";
    સ્થિતિ VK_EVENT_SET:
        પાછા "VK_EVENT_SET";
    સ્થિતિ VK_EVENT_RESET:
        પાછા "VK_EVENT_RESET";
    સ્થિતિ VK_INCOMPLETE:
        પાછા "VK_INCOMPLETE";
    સ્થિતિ VK_ERROR_OUT_OF_HOST_MEMORY:
        પાછા "VK_ERROR_OUT_OF_HOST_MEMORY";
    સ્થિતિ VK_ERROR_OUT_OF_DEVICE_MEMORY:
        પાછા "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    સ્થિતિ VK_ERROR_INITIALIZATION_FAILED:
        પાછા "VK_ERROR_INITIALIZATION_FAILED";
    સ્થિતિ VK_ERROR_DEVICE_LOST:
        પાછા "VK_ERROR_DEVICE_LOST";
    સ્થિતિ VK_ERROR_MEMORY_MAP_FAILED:
        પાછા "VK_ERROR_MEMORY_MAP_FAILED";
    સ્થિતિ VK_ERROR_LAYER_NOT_PRESENT:
        પાછા "VK_ERROR_LAYER_NOT_PRESENT";
    સ્થિતિ VK_ERROR_EXTENSION_NOT_PRESENT:
        પાછા "VK_ERROR_EXTENSION_NOT_PRESENT";
    સ્થિતિ VK_ERROR_FEATURE_NOT_PRESENT:
        પાછા "VK_ERROR_FEATURE_NOT_PRESENT";
    સ્થિતિ VK_ERROR_INCOMPATIBLE_DRIVER:
        પાછા "VK_ERROR_INCOMPATIBLE_DRIVER";
    સ્થિતિ VK_ERROR_TOO_MANY_OBJECTS:
        પાછા "VK_ERROR_TOO_MANY_OBJECTS";
    સ્થિતિ VK_ERROR_FORMAT_NOT_SUPPORTED:
        પાછા "VK_ERROR_FORMAT_NOT_SUPPORTED";
    સ્થિતિ VK_ERROR_FRAGMENTED_POOL:
        પાછા "VK_ERROR_FRAGMENTED_POOL";
    સ્થિતિ VK_ERROR_UNKNOWN:
        પાછા "VK_ERROR_UNKNOWN";
    સ્થિતિ VK_ERROR_OUT_OF_POOL_MEMORY:
        પાછા "VK_ERROR_OUT_OF_POOL_MEMORY";
    સ્થિતિ VK_ERROR_INVALID_EXTERNAL_HANDLE:
        પાછા "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    સ્થિતિ VK_ERROR_FRAGMENTATION:
        પાછા "VK_ERROR_FRAGMENTATION";
    સ્થિતિ VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        પાછા "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    સ્થિતિ VK_ERROR_SURFACE_LOST_KHR:
        પાછા "VK_ERROR_SURFACE_LOST_KHR";
    સ્થિતિ VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        પાછા "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    સ્થિતિ VK_SUBOPTIMAL_KHR:
        પાછા "VK_SUBOPTIMAL_KHR";
    સ્થિતિ VK_ERROR_OUT_OF_DATE_KHR:
        પાછા "VK_ERROR_OUT_OF_DATE_KHR";
    સ્થિતિ VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        પાછા "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    સ્થિતિ VK_ERROR_VALIDATION_FAILED_EXT:
        પાછા "VK_ERROR_VALIDATION_FAILED_EXT";
    સ્થિતિ VK_ERROR_INVALID_SHADER_NV:
        પાછા "VK_ERROR_INVALID_SHADER_NV";
#જો VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    સ્થિતિ VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        પાછા "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    સ્થિતિ VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        પાછા "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    સ્થિતિ VK_ERROR_NOT_PERMITTED_EXT:
        પાછા "VK_ERROR_NOT_PERMITTED_EXT";
    સ્થિતિ VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        પાછા "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    સ્થિતિ VK_THREAD_IDLE_KHR:
        પાછા "VK_THREAD_IDLE_KHR";
    સ્થિતિ VK_THREAD_DONE_KHR:
        પાછા "VK_THREAD_DONE_KHR";
    સ્થિતિ VK_OPERATION_DEFERRED_KHR:
        પાછા "VK_OPERATION_DEFERRED_KHR";
    સ્થિતિ VK_OPERATION_NOT_DEFERRED_KHR:
        પાછા "VK_OPERATION_NOT_DEFERRED_KHR";
    સ્થિતિ VK_PIPELINE_COMPILE_REQUIRED_EXT:
        પાછા "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    મૂળભૂત:
        તોડો;
    }
    જો (result < 0) {
        પાછા "VK_ERROR_<Unknown>";
    }
    પાછા "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_ગણતરી)
{
    Uint32 ગણતરી = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(ખાલી, &ગણતરી, ખાલી);
    VkExtensionProperties *result;

    જો (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (પૂર્ણાંક)rc);
        પાછા ખાલી;
    } નહીંતર જો (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (પૂર્ણાંક)rc);
        પાછા ખાલી;
    }

    જો (ગણતરી == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, કદ(VkExtensionProperties)); // so we can return non-null
    } નહીંતર {
        result = (VkExtensionProperties *)SDL_calloc(ગણતરી, કદ(VkExtensionProperties));
    }

    જો (!result) {
        પાછા ખાલી;
    }

    rc = vkEnumerateInstanceExtensionProperties(ખાલી, &ગણતરી, result);
    જો (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (પૂર્ણાંક)rc);
        SDL_free(result);
        પાછા ખાલી;
    }
    *extension_ગણતરી = ગણતરી;
    પાછા result;
}

// Alpha modes, in order of preference
સ્થિર અચલ VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(શૂન્ય *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      અચલ સંરચના VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_ગણતરી = 0;
    VkPhysicalDevice *physicalDevices = ખાલી;
    uint32_t physicalDeviceIndex;
    અચલ અક્ષર *chosenDisplayId;
    પૂર્ણાંક displayId = 0; // Counting from physical device 0, display 0

    જો (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        જાઓ error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    જો (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ગણતરી, ખાલી);
    જો (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        જાઓ error;
    }

    જો (physical_Device_ગણતરી == 0) {
        SDL_SetError("No Vulkan physical devices");
        જાઓ error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(કદ(VkPhysicalDevice) * physical_Device_ગણતરી);
    જો (!physicalDevices) {
        જાઓ error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_ગણતરી, physicalDevices);
    જો (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        જાઓ error;
    }

    માટે (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_ગણતરી; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_ગણતરી = 0;
        VkDisplayPropertiesKHR *displayProperties = ખાલી;
        uint32_t display_Mode_Properties_ગણતરી = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = ખાલી;
        પૂર્ણાંક bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_ગણતરી = 0;
        પૂર્ણાંક planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ખાલી;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ગણતરી, ખાલી);
        જો (rc != VK_SUCCESS || display_Properties_ગણતરી == 0) {
            // This device has no physical device display properties, move on to next.
            ચાલુ;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_ગણતરી);

        જો (displayId < 0 || (uint32_t)displayId >= display_Properties_ગણતરી) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_ગણતરી;
            ચાલુ;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(કદ(VkDisplayPropertiesKHR) * display_Properties_ગણતરી);
        જો (!displayProperties) {
            જાઓ error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_ગણતરી, displayProperties);
        જો (rc != VK_SUCCESS || display_Properties_ગણતરી == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            જાઓ error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = ખાલી;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_ગણતરી, ખાલી);
        જો (rc != VK_SUCCESS || display_Mode_Properties_ગણતરી == 0) {
            SDL_SetError("Error enumerating display modes");
            જાઓ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_ગણતરી);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(કદ(VkDisplayModePropertiesKHR) * display_Mode_Properties_ગણતરી);
        જો (!displayModeProperties) {
            જાઓ error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_ગણતરી, displayModeProperties);
        જો (rc != VK_SUCCESS || display_Mode_Properties_ગણતરી == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            જાઓ error;
        }

        // Try to find a display mode that matches the native resolution
        માટે (i = 0; i < display_Mode_Properties_ગણતરી; ++i) {
            જો (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        જો (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            જાઓ error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = ખાલી;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ગણતરી, ખાલી);
        જો (rc != VK_SUCCESS || display_Plane_Properties_ગણતરી == 0) {
            SDL_SetError("Error enumerating display planes");
            જાઓ error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_ગણતરી);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(કદ(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_ગણતરી);
        જો (!displayPlaneProperties) {
            જાઓ error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_ગણતરી, displayPlaneProperties);
        જો (rc != VK_SUCCESS || display_Plane_Properties_ગણતરી == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            જાઓ error;
        }

        માટે (i = 0; i < display_Plane_Properties_ગણતરી; ++i) {
            uint32_t plane_Supported_Displays_ગણતરી = 0;
            VkDisplayKHR *planeSupportedDisplays = ખાલી;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            જો (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                ચાલુ;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ગણતરી, ખાલી);
            જો (rc != VK_SUCCESS || plane_Supported_Displays_ગણતરી == 0) {
                ચાલુ; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_ગણતરી);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(કદ(VkDisplayKHR) * plane_Supported_Displays_ગણતરી);
            જો (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                જાઓ error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_ગણતરી, planeSupportedDisplays);
            જો (rc != VK_SUCCESS || plane_Supported_Displays_ગણતરી == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                જાઓ error;
            }

            માટે (j = 0; j < plane_Supported_Displays_ગણતરી && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ખાલી;

            જો (j == plane_Supported_Displays_ગણતરી) {
                // This display is not supported for this plane, move on.
                ચાલુ;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            જો (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                જાઓ error;
            }

            // Check if plane fulfills extent requirements.
            જો (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                તોડો;
            }
        }

        જો (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            જાઓ error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_ઢગલો_Index = displayPlaneProperties[planeIndex].current_ઢગલો_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ખાલી;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        માટે (i = 0; i < SDL_arraysize(alphaModes); i++) {
            જો (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                તોડો;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        તોડો;
    }

    SDL_free(physicalDevices);
    physicalDevices = ખાલી;

    જો (physicalDeviceIndex == physical_Device_ગણતરી) {
        SDL_SetError("No usable displays found or requested display out of range");
        જાઓ error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    જો (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        જાઓ error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    પાછા true;

error:
    SDL_free(physicalDevices);
    પાછા false;
}

શૂન્ય SDL_Vulkan_DestroySurface_Internal(શૂન્ય *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        અચલ સંરચના VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    જો (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

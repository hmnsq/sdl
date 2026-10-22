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
#അന്തര്ഭാവ "SDL_internal.h"

#അന്തര്ഭാവ "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

സ്ഥിരം അക്ഷരം *SDL_Vulkan_GetResultString(VkResult result)
{
    തിരഞ്ഞെടുപ്പ് ((പൂർണ്ണസംഖ്യ)result) {
    അവസ്ഥ VK_SUCCESS:
        തിരികെ "VK_SUCCESS";
    അവസ്ഥ VK_NOT_READY:
        തിരികെ "VK_NOT_READY";
    അവസ്ഥ VK_TIMEOUT:
        തിരികെ "VK_TIMEOUT";
    അവസ്ഥ VK_EVENT_SET:
        തിരികെ "VK_EVENT_SET";
    അവസ്ഥ VK_EVENT_RESET:
        തിരികെ "VK_EVENT_RESET";
    അവസ്ഥ VK_INCOMPLETE:
        തിരികെ "VK_INCOMPLETE";
    അവസ്ഥ VK_ERROR_OUT_OF_HOST_MEMORY:
        തിരികെ "VK_ERROR_OUT_OF_HOST_MEMORY";
    അവസ്ഥ VK_ERROR_OUT_OF_DEVICE_MEMORY:
        തിരികെ "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    അവസ്ഥ VK_ERROR_INITIALIZATION_FAILED:
        തിരികെ "VK_ERROR_INITIALIZATION_FAILED";
    അവസ്ഥ VK_ERROR_DEVICE_LOST:
        തിരികെ "VK_ERROR_DEVICE_LOST";
    അവസ്ഥ VK_ERROR_MEMORY_MAP_FAILED:
        തിരികെ "VK_ERROR_MEMORY_MAP_FAILED";
    അവസ്ഥ VK_ERROR_LAYER_NOT_PRESENT:
        തിരികെ "VK_ERROR_LAYER_NOT_PRESENT";
    അവസ്ഥ VK_ERROR_EXTENSION_NOT_PRESENT:
        തിരികെ "VK_ERROR_EXTENSION_NOT_PRESENT";
    അവസ്ഥ VK_ERROR_FEATURE_NOT_PRESENT:
        തിരികെ "VK_ERROR_FEATURE_NOT_PRESENT";
    അവസ്ഥ VK_ERROR_INCOMPATIBLE_DRIVER:
        തിരികെ "VK_ERROR_INCOMPATIBLE_DRIVER";
    അവസ്ഥ VK_ERROR_TOO_MANY_OBJECTS:
        തിരികെ "VK_ERROR_TOO_MANY_OBJECTS";
    അവസ്ഥ VK_ERROR_FORMAT_NOT_SUPPORTED:
        തിരികെ "VK_ERROR_FORMAT_NOT_SUPPORTED";
    അവസ്ഥ VK_ERROR_FRAGMENTED_POOL:
        തിരികെ "VK_ERROR_FRAGMENTED_POOL";
    അവസ്ഥ VK_ERROR_UNKNOWN:
        തിരികെ "VK_ERROR_UNKNOWN";
    അവസ്ഥ VK_ERROR_OUT_OF_POOL_MEMORY:
        തിരികെ "VK_ERROR_OUT_OF_POOL_MEMORY";
    അവസ്ഥ VK_ERROR_INVALID_EXTERNAL_HANDLE:
        തിരികെ "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    അവസ്ഥ VK_ERROR_FRAGMENTATION:
        തിരികെ "VK_ERROR_FRAGMENTATION";
    അവസ്ഥ VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        തിരികെ "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    അവസ്ഥ VK_ERROR_SURFACE_LOST_KHR:
        തിരികെ "VK_ERROR_SURFACE_LOST_KHR";
    അവസ്ഥ VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        തിരികെ "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    അവസ്ഥ VK_SUBOPTIMAL_KHR:
        തിരികെ "VK_SUBOPTIMAL_KHR";
    അവസ്ഥ VK_ERROR_OUT_OF_DATE_KHR:
        തിരികെ "VK_ERROR_OUT_OF_DATE_KHR";
    അവസ്ഥ VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        തിരികെ "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    അവസ്ഥ VK_ERROR_VALIDATION_FAILED_EXT:
        തിരികെ "VK_ERROR_VALIDATION_FAILED_EXT";
    അവസ്ഥ VK_ERROR_INVALID_SHADER_NV:
        തിരികെ "VK_ERROR_INVALID_SHADER_NV";
#എങ്കിൽ VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    അവസ്ഥ VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        തിരികെ "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    അവസ്ഥ VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        തിരികെ "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    അവസ്ഥ VK_ERROR_NOT_PERMITTED_EXT:
        തിരികെ "VK_ERROR_NOT_PERMITTED_EXT";
    അവസ്ഥ VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        തിരികെ "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    അവസ്ഥ VK_THREAD_IDLE_KHR:
        തിരികെ "VK_THREAD_IDLE_KHR";
    അവസ്ഥ VK_THREAD_DONE_KHR:
        തിരികെ "VK_THREAD_DONE_KHR";
    അവസ്ഥ VK_OPERATION_DEFERRED_KHR:
        തിരികെ "VK_OPERATION_DEFERRED_KHR";
    അവസ്ഥ VK_OPERATION_NOT_DEFERRED_KHR:
        തിരികെ "VK_OPERATION_NOT_DEFERRED_KHR";
    അവസ്ഥ VK_PIPELINE_COMPILE_REQUIRED_EXT:
        തിരികെ "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
    എങ്കിൽ (result < 0) {
        തിരികെ "VK_ERROR_<Unknown>";
    }
    തിരികെ "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_എണ്ണം)
{
    Uint32 എണ്ണം = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(ശൂന്യ, &എണ്ണം, ശൂന്യ);
    VkExtensionProperties *result;

    എങ്കിൽ (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (പൂർണ്ണസംഖ്യ)rc);
        തിരികെ ശൂന്യ;
    } അല്ലെങ്കിൽ എങ്കിൽ (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (പൂർണ്ണസംഖ്യ)rc);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (എണ്ണം == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, വലുപ്പം(VkExtensionProperties)); // so we can return non-null
    } അല്ലെങ്കിൽ {
        result = (VkExtensionProperties *)SDL_calloc(എണ്ണം, വലുപ്പം(VkExtensionProperties));
    }

    എങ്കിൽ (!result) {
        തിരികെ ശൂന്യ;
    }

    rc = vkEnumerateInstanceExtensionProperties(ശൂന്യ, &എണ്ണം, result);
    എങ്കിൽ (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (പൂർണ്ണസംഖ്യ)rc);
        SDL_free(result);
        തിരികെ ശൂന്യ;
    }
    *extension_എണ്ണം = എണ്ണം;
    തിരികെ result;
}

// Alpha modes, in order of preference
സ്ഥിതം സ്ഥിരം VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(ശൂന്യം *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      സ്ഥിരം ഘടന VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_എണ്ണം = 0;
    VkPhysicalDevice *physicalDevices = ശൂന്യ;
    uint32_t physicalDeviceIndex;
    സ്ഥിരം അക്ഷരം *chosenDisplayId;
    പൂർണ്ണസംഖ്യ displayId = 0; // Counting from physical device 0, display 0

    എങ്കിൽ (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        പോകുക error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    എങ്കിൽ (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_എണ്ണം, ശൂന്യ);
    എങ്കിൽ (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        പോകുക error;
    }

    എങ്കിൽ (physical_Device_എണ്ണം == 0) {
        SDL_SetError("No Vulkan physical devices");
        പോകുക error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(വലുപ്പം(VkPhysicalDevice) * physical_Device_എണ്ണം);
    എങ്കിൽ (!physicalDevices) {
        പോകുക error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_എണ്ണം, physicalDevices);
    എങ്കിൽ (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        പോകുക error;
    }

    വേണ്ടി (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_എണ്ണം; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_എണ്ണം = 0;
        VkDisplayPropertiesKHR *displayProperties = ശൂന്യ;
        uint32_t display_Mode_Properties_എണ്ണം = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = ശൂന്യ;
        പൂർണ്ണസംഖ്യ bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_എണ്ണം = 0;
        പൂർണ്ണസംഖ്യ planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = ശൂന്യ;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_എണ്ണം, ശൂന്യ);
        എങ്കിൽ (rc != VK_SUCCESS || display_Properties_എണ്ണം == 0) {
            // This device has no physical device display properties, move on to next.
            തുടരുക;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_എണ്ണം);

        എങ്കിൽ (displayId < 0 || (uint32_t)displayId >= display_Properties_എണ്ണം) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_എണ്ണം;
            തുടരുക;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(വലുപ്പം(VkDisplayPropertiesKHR) * display_Properties_എണ്ണം);
        എങ്കിൽ (!displayProperties) {
            പോകുക error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_എണ്ണം, displayProperties);
        എങ്കിൽ (rc != VK_SUCCESS || display_Properties_എണ്ണം == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            പോകുക error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = ശൂന്യ;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_എണ്ണം, ശൂന്യ);
        എങ്കിൽ (rc != VK_SUCCESS || display_Mode_Properties_എണ്ണം == 0) {
            SDL_SetError("Error enumerating display modes");
            പോകുക error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_എണ്ണം);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(വലുപ്പം(VkDisplayModePropertiesKHR) * display_Mode_Properties_എണ്ണം);
        എങ്കിൽ (!displayModeProperties) {
            പോകുക error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_എണ്ണം, displayModeProperties);
        എങ്കിൽ (rc != VK_SUCCESS || display_Mode_Properties_എണ്ണം == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            പോകുക error;
        }

        // Try to find a display mode that matches the native resolution
        വേണ്ടി (i = 0; i < display_Mode_Properties_എണ്ണം; ++i) {
            എങ്കിൽ (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        എങ്കിൽ (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            പോകുക error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = ശൂന്യ;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_എണ്ണം, ശൂന്യ);
        എങ്കിൽ (rc != VK_SUCCESS || display_Plane_Properties_എണ്ണം == 0) {
            SDL_SetError("Error enumerating display planes");
            പോകുക error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_എണ്ണം);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(വലുപ്പം(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_എണ്ണം);
        എങ്കിൽ (!displayPlaneProperties) {
            പോകുക error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_എണ്ണം, displayPlaneProperties);
        എങ്കിൽ (rc != VK_SUCCESS || display_Plane_Properties_എണ്ണം == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            പോകുക error;
        }

        വേണ്ടി (i = 0; i < display_Plane_Properties_എണ്ണം; ++i) {
            uint32_t plane_Supported_Displays_എണ്ണം = 0;
            VkDisplayKHR *planeSupportedDisplays = ശൂന്യ;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            എങ്കിൽ (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                തുടരുക;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_എണ്ണം, ശൂന്യ);
            എങ്കിൽ (rc != VK_SUCCESS || plane_Supported_Displays_എണ്ണം == 0) {
                തുടരുക; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_എണ്ണം);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(വലുപ്പം(VkDisplayKHR) * plane_Supported_Displays_എണ്ണം);
            എങ്കിൽ (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                പോകുക error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_എണ്ണം, planeSupportedDisplays);
            എങ്കിൽ (rc != VK_SUCCESS || plane_Supported_Displays_എണ്ണം == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                പോകുക error;
            }

            വേണ്ടി (j = 0; j < plane_Supported_Displays_എണ്ണം && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = ശൂന്യ;

            എങ്കിൽ (j == plane_Supported_Displays_എണ്ണം) {
                // This display is not supported for this plane, move on.
                തുടരുക;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            എങ്കിൽ (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                പോകുക error;
            }

            // Check if plane fulfills extent requirements.
            എങ്കിൽ (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                നിർത്തുക;
            }
        }

        എങ്കിൽ (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            പോകുക error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_അട്ടി_Index = displayPlaneProperties[planeIndex].current_അട്ടി_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = ശൂന്യ;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        വേണ്ടി (i = 0; i < SDL_arraysize(alphaModes); i++) {
            എങ്കിൽ (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                നിർത്തുക;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        നിർത്തുക;
    }

    SDL_free(physicalDevices);
    physicalDevices = ശൂന്യ;

    എങ്കിൽ (physicalDeviceIndex == physical_Device_എണ്ണം) {
        SDL_SetError("No usable displays found or requested display out of range");
        പോകുക error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    എങ്കിൽ (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        പോകുക error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    തിരികെ true;

error:
    SDL_free(physicalDevices);
    തിരികെ false;
}

ശൂന്യം SDL_Vulkan_DestroySurface_Internal(ശൂന്യം *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        സ്ഥിരം ഘടന VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    എങ്കിൽ (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

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
        أرجع "VK_SUCCESS";
    حالة VK_NOT_READY:
        أرجع "VK_NOT_READY";
    حالة VK_TIMEOUT:
        أرجع "VK_TIMEOUT";
    حالة VK_EVENT_SET:
        أرجع "VK_EVENT_SET";
    حالة VK_EVENT_RESET:
        أرجع "VK_EVENT_RESET";
    حالة VK_INCOMPLETE:
        أرجع "VK_INCOMPLETE";
    حالة VK_ERROR_OUT_OF_HOST_MEMORY:
        أرجع "VK_ERROR_OUT_OF_HOST_MEMORY";
    حالة VK_ERROR_OUT_OF_DEVICE_MEMORY:
        أرجع "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    حالة VK_ERROR_INITIALIZATION_FAILED:
        أرجع "VK_ERROR_INITIALIZATION_FAILED";
    حالة VK_ERROR_DEVICE_LOST:
        أرجع "VK_ERROR_DEVICE_LOST";
    حالة VK_ERROR_MEMORY_MAP_FAILED:
        أرجع "VK_ERROR_MEMORY_MAP_FAILED";
    حالة VK_ERROR_LAYER_NOT_PRESENT:
        أرجع "VK_ERROR_LAYER_NOT_PRESENT";
    حالة VK_ERROR_EXTENSION_NOT_PRESENT:
        أرجع "VK_ERROR_EXTENSION_NOT_PRESENT";
    حالة VK_ERROR_FEATURE_NOT_PRESENT:
        أرجع "VK_ERROR_FEATURE_NOT_PRESENT";
    حالة VK_ERROR_INCOMPATIBLE_DRIVER:
        أرجع "VK_ERROR_INCOMPATIBLE_DRIVER";
    حالة VK_ERROR_TOO_MANY_OBJECTS:
        أرجع "VK_ERROR_TOO_MANY_OBJECTS";
    حالة VK_ERROR_FORMAT_NOT_SUPPORTED:
        أرجع "VK_ERROR_FORMAT_NOT_SUPPORTED";
    حالة VK_ERROR_FRAGMENTED_POOL:
        أرجع "VK_ERROR_FRAGMENTED_POOL";
    حالة VK_ERROR_UNKNOWN:
        أرجع "VK_ERROR_UNKNOWN";
    حالة VK_ERROR_OUT_OF_POOL_MEMORY:
        أرجع "VK_ERROR_OUT_OF_POOL_MEMORY";
    حالة VK_ERROR_INVALID_EXTERNAL_HANDLE:
        أرجع "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    حالة VK_ERROR_FRAGMENTATION:
        أرجع "VK_ERROR_FRAGMENTATION";
    حالة VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        أرجع "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    حالة VK_ERROR_SURFACE_LOST_KHR:
        أرجع "VK_ERROR_SURFACE_LOST_KHR";
    حالة VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        أرجع "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    حالة VK_SUBOPTIMAL_KHR:
        أرجع "VK_SUBOPTIMAL_KHR";
    حالة VK_ERROR_OUT_OF_DATE_KHR:
        أرجع "VK_ERROR_OUT_OF_DATE_KHR";
    حالة VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        أرجع "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    حالة VK_ERROR_VALIDATION_FAILED_EXT:
        أرجع "VK_ERROR_VALIDATION_FAILED_EXT";
    حالة VK_ERROR_INVALID_SHADER_NV:
        أرجع "VK_ERROR_INVALID_SHADER_NV";
#إذا VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    حالة VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        أرجع "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    حالة VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        أرجع "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    حالة VK_ERROR_NOT_PERMITTED_EXT:
        أرجع "VK_ERROR_NOT_PERMITTED_EXT";
    حالة VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        أرجع "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    حالة VK_THREAD_IDLE_KHR:
        أرجع "VK_THREAD_IDLE_KHR";
    حالة VK_THREAD_DONE_KHR:
        أرجع "VK_THREAD_DONE_KHR";
    حالة VK_OPERATION_DEFERRED_KHR:
        أرجع "VK_OPERATION_DEFERRED_KHR";
    حالة VK_OPERATION_NOT_DEFERRED_KHR:
        أرجع "VK_OPERATION_NOT_DEFERRED_KHR";
    حالة VK_PIPELINE_COMPILE_REQUIRED_EXT:
        أرجع "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    افتراضي:
        اكسر;
    }
    إذا (result < 0) {
        أرجع "VK_ERROR_<Unknown>";
    }
    أرجع "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_کيراءن)
{
    Uint32 کيراءن = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(عدم, &کيراءن, عدم);
    VkExtensionProperties *result;

    إذا (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (صحيح)rc);
        أرجع عدم;
    } وإلا إذا (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (صحيح)rc);
        أرجع عدم;
    }

    إذا (کيراءن == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, حجم(VkExtensionProperties)); // so we can return non-null
    } وإلا {
        result = (VkExtensionProperties *)SDL_calloc(کيراءن, حجم(VkExtensionProperties));
    }

    إذا (!result) {
        أرجع عدم;
    }

    rc = vkEnumerateInstanceExtensionProperties(عدم, &کيراءن, result);
    إذا (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (صحيح)rc);
        SDL_free(result);
        أرجع عدم;
    }
    *extension_کيراءن = کيراءن;
    أرجع result;
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
    uint32_t physical_Device_کيراءن = 0;
    VkPhysicalDevice *physicalDevices = عدم;
    uint32_t physicalDeviceIndex;
    ثابت حرف *chosenDisplayId;
    صحيح displayId = 0; // Counting from physical device 0, display 0

    إذا (!vkEnumeratePhysicalDevices ||
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
    إذا (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_کيراءن, عدم);
    إذا (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        اذهب error;
    }

    إذا (physical_Device_کيراءن == 0) {
        SDL_SetError("No Vulkan physical devices");
        اذهب error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(حجم(VkPhysicalDevice) * physical_Device_کيراءن);
    إذا (!physicalDevices) {
        اذهب error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_کيراءن, physicalDevices);
    إذا (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        اذهب error;
    }

    لكل (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_کيراءن; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_کيراءن = 0;
        VkDisplayPropertiesKHR *displayProperties = عدم;
        uint32_t display_Mode_Properties_کيراءن = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = عدم;
        صحيح bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_کيراءن = 0;
        صحيح planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = عدم;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_کيراءن, عدم);
        إذا (rc != VK_SUCCESS || display_Properties_کيراءن == 0) {
            // This device has no physical device display properties, move on to next.
            استمر;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_کيراءن);

        إذا (displayId < 0 || (uint32_t)displayId >= display_Properties_کيراءن) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_کيراءن;
            استمر;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(حجم(VkDisplayPropertiesKHR) * display_Properties_کيراءن);
        إذا (!displayProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_کيراءن, displayProperties);
        إذا (rc != VK_SUCCESS || display_Properties_کيراءن == 0) {
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
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_کيراءن, عدم);
        إذا (rc != VK_SUCCESS || display_Mode_Properties_کيراءن == 0) {
            SDL_SetError("Error enumerating display modes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_کيراءن);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(حجم(VkDisplayModePropertiesKHR) * display_Mode_Properties_کيراءن);
        إذا (!displayModeProperties) {
            اذهب error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_کيراءن, displayModeProperties);
        إذا (rc != VK_SUCCESS || display_Mode_Properties_کيراءن == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            اذهب error;
        }

        // Try to find a display mode that matches the native resolution
        لكل (i = 0; i < display_Mode_Properties_کيراءن; ++i) {
            إذا (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        إذا (bestMatchIndex < 0) {
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
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_کيراءن, عدم);
        إذا (rc != VK_SUCCESS || display_Plane_Properties_کيراءن == 0) {
            SDL_SetError("Error enumerating display planes");
            اذهب error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_کيراءن);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(حجم(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_کيراءن);
        إذا (!displayPlaneProperties) {
            اذهب error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_کيراءن, displayPlaneProperties);
        إذا (rc != VK_SUCCESS || display_Plane_Properties_کيراءن == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        لكل (i = 0; i < display_Plane_Properties_کيراءن; ++i) {
            uint32_t plane_Supported_Displays_کيراءن = 0;
            VkDisplayKHR *planeSupportedDisplays = عدم;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            إذا (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                استمر;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_کيراءن, عدم);
            إذا (rc != VK_SUCCESS || plane_Supported_Displays_کيراءن == 0) {
                استمر; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_کيراءن);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(حجم(VkDisplayKHR) * plane_Supported_Displays_کيراءن);
            إذا (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_کيراءن, planeSupportedDisplays);
            إذا (rc != VK_SUCCESS || plane_Supported_Displays_کيراءن == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            لكل (j = 0; j < plane_Supported_Displays_کيراءن && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = عدم;

            إذا (j == plane_Supported_Displays_کيراءن) {
                // This display is not supported for this plane, move on.
                استمر;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            إذا (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                اذهب error;
            }

            // Check if plane fulfills extent requirements.
            إذا (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                اكسر;
            }
        }

        إذا (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            اذهب error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_تيندنن_Index = displayPlaneProperties[planeIndex].current_تيندنن_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = عدم;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        لكل (i = 0; i < SDL_arraysize(alphaModes); i++) {
            إذا (planeCaps.supportedAlpha & alphaModes[i]) {
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

    إذا (physicalDeviceIndex == physical_Device_کيراءن) {
        SDL_SetError("No usable displays found or requested display out of range");
        اذهب error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    إذا (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        اذهب error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    أرجع true;

error:
    SDL_free(physicalDevices);
    أرجع false;
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

    إذا (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif

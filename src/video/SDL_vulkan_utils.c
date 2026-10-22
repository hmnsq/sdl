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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_vulkan_internal.h"

#ifdef SDL_VIDEO_VULKAN

स्थिरांक अक्षर *SDL_Vulkan_GetResultString(VkResult result)
{
    निवड ((पूर्णांक)result) {
    स्थिती VK_SUCCESS:
        परत "VK_SUCCESS";
    स्थिती VK_NOT_READY:
        परत "VK_NOT_READY";
    स्थिती VK_TIMEOUT:
        परत "VK_TIMEOUT";
    स्थिती VK_EVENT_SET:
        परत "VK_EVENT_SET";
    स्थिती VK_EVENT_RESET:
        परत "VK_EVENT_RESET";
    स्थिती VK_INCOMPLETE:
        परत "VK_INCOMPLETE";
    स्थिती VK_ERROR_OUT_OF_HOST_MEMORY:
        परत "VK_ERROR_OUT_OF_HOST_MEMORY";
    स्थिती VK_ERROR_OUT_OF_DEVICE_MEMORY:
        परत "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    स्थिती VK_ERROR_INITIALIZATION_FAILED:
        परत "VK_ERROR_INITIALIZATION_FAILED";
    स्थिती VK_ERROR_DEVICE_LOST:
        परत "VK_ERROR_DEVICE_LOST";
    स्थिती VK_ERROR_MEMORY_MAP_FAILED:
        परत "VK_ERROR_MEMORY_MAP_FAILED";
    स्थिती VK_ERROR_LAYER_NOT_PRESENT:
        परत "VK_ERROR_LAYER_NOT_PRESENT";
    स्थिती VK_ERROR_EXTENSION_NOT_PRESENT:
        परत "VK_ERROR_EXTENSION_NOT_PRESENT";
    स्थिती VK_ERROR_FEATURE_NOT_PRESENT:
        परत "VK_ERROR_FEATURE_NOT_PRESENT";
    स्थिती VK_ERROR_INCOMPATIBLE_DRIVER:
        परत "VK_ERROR_INCOMPATIBLE_DRIVER";
    स्थिती VK_ERROR_TOO_MANY_OBJECTS:
        परत "VK_ERROR_TOO_MANY_OBJECTS";
    स्थिती VK_ERROR_FORMAT_NOT_SUPPORTED:
        परत "VK_ERROR_FORMAT_NOT_SUPPORTED";
    स्थिती VK_ERROR_FRAGMENTED_POOL:
        परत "VK_ERROR_FRAGMENTED_POOL";
    स्थिती VK_ERROR_UNKNOWN:
        परत "VK_ERROR_UNKNOWN";
    स्थिती VK_ERROR_OUT_OF_POOL_MEMORY:
        परत "VK_ERROR_OUT_OF_POOL_MEMORY";
    स्थिती VK_ERROR_INVALID_EXTERNAL_HANDLE:
        परत "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    स्थिती VK_ERROR_FRAGMENTATION:
        परत "VK_ERROR_FRAGMENTATION";
    स्थिती VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        परत "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    स्थिती VK_ERROR_SURFACE_LOST_KHR:
        परत "VK_ERROR_SURFACE_LOST_KHR";
    स्थिती VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        परत "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    स्थिती VK_SUBOPTIMAL_KHR:
        परत "VK_SUBOPTIMAL_KHR";
    स्थिती VK_ERROR_OUT_OF_DATE_KHR:
        परत "VK_ERROR_OUT_OF_DATE_KHR";
    स्थिती VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        परत "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    स्थिती VK_ERROR_VALIDATION_FAILED_EXT:
        परत "VK_ERROR_VALIDATION_FAILED_EXT";
    स्थिती VK_ERROR_INVALID_SHADER_NV:
        परत "VK_ERROR_INVALID_SHADER_NV";
#जर VK_HEADER_VERSION >= 135 && VK_HEADER_VERSION < 162
    स्थिती VK_ERROR_INCOMPATIBLE_VERSION_KHR:
        परत "VK_ERROR_INCOMPATIBLE_VERSION_KHR";
#endif
    स्थिती VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        परत "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    स्थिती VK_ERROR_NOT_PERMITTED_EXT:
        परत "VK_ERROR_NOT_PERMITTED_EXT";
    स्थिती VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        परत "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    स्थिती VK_THREAD_IDLE_KHR:
        परत "VK_THREAD_IDLE_KHR";
    स्थिती VK_THREAD_DONE_KHR:
        परत "VK_THREAD_DONE_KHR";
    स्थिती VK_OPERATION_DEFERRED_KHR:
        परत "VK_OPERATION_DEFERRED_KHR";
    स्थिती VK_OPERATION_NOT_DEFERRED_KHR:
        परत "VK_OPERATION_NOT_DEFERRED_KHR";
    स्थिती VK_PIPELINE_COMPILE_REQUIRED_EXT:
        परत "VK_PIPELINE_COMPILE_REQUIRED_EXT";
    पूर्वनिर्धारित:
        थांबा;
    }
    जर (result < 0) {
        परत "VK_ERROR_<Unknown>";
    }
    परत "VK_<Unknown>";
}

VkExtensionProperties *SDL_Vulkan_CreateInstanceExtensionsList(
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties,
    Uint32 *extension_मोजणी)
{
    Uint32 मोजणी = 0;
    VkResult rc = vkEnumerateInstanceExtensionProperties(रिक्त, &मोजणी, रिक्त);
    VkExtensionProperties *result;

    जर (rc == VK_ERROR_INCOMPATIBLE_DRIVER) {
        // Avoid the ERR_MAX_STRLEN limit by passing part of the message as a string argument.
        SDL_SetError(
            "You probably don't have a working Vulkan driver installed. %s %s %s(%d)",
            "Getting Vulkan extensions failed:",
            "vkEnumerateInstanceExtensionProperties returned",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णांक)rc);
        परत रिक्त;
    } अन्यथा जर (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णांक)rc);
        परत रिक्त;
    }

    जर (मोजणी == 0) {
        result = (VkExtensionProperties *)SDL_calloc(1, आकार(VkExtensionProperties)); // so we can return non-null
    } अन्यथा {
        result = (VkExtensionProperties *)SDL_calloc(मोजणी, आकार(VkExtensionProperties));
    }

    जर (!result) {
        परत रिक्त;
    }

    rc = vkEnumerateInstanceExtensionProperties(रिक्त, &मोजणी, result);
    जर (rc != VK_SUCCESS) {
        SDL_SetError(
            "Getting Vulkan extensions failed: vkEnumerateInstanceExtensionProperties returned "
            "%s(%d)",
            SDL_Vulkan_GetResultString(rc),
            (पूर्णांक)rc);
        SDL_free(result);
        परत रिक्त;
    }
    *extension_मोजणी = मोजणी;
    परत result;
}

// Alpha modes, in order of preference
स्थिर स्थिरांक VkDisplayPlaneAlphaFlagBitsKHR alphaModes[4] = {
    VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR,
    VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR,
};

bool SDL_Vulkan_Display_CreateSurface(शून्य *vkGetInstanceProcAddr_,
                                      VkInstance instance,
                                      स्थिरांक संरचना VkAllocationCallbacks *allocator,
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
    uint32_t physical_Device_मोजणी = 0;
    VkPhysicalDevice *physicalDevices = रिक्त;
    uint32_t physicalDeviceIndex;
    स्थिरांक अक्षर *chosenDisplayId;
    पूर्णांक displayId = 0; // Counting from physical device 0, display 0

    जर (!vkEnumeratePhysicalDevices ||
        !vkGetPhysicalDeviceDisplayPropertiesKHR ||
        !vkGetDisplayModePropertiesKHR ||
        !vkGetPhysicalDeviceDisplayPlanePropertiesKHR ||
        !vkGetDisplayPlaneCapabilitiesKHR ||
        !vkGetDisplayPlaneSupportedDisplaysKHR ||
        !vkCreateDisplayPlaneSurfaceKHR) {
        SDL_SetError(VK_KHR_DISPLAY_EXTENSION_NAME " extension is not enabled in the Vulkan instance.");
        जा error;
    }
    chosenDisplayId = SDL_GetHint(SDL_HINT_VULKAN_DISPLAY);
    जर (chosenDisplayId) {
        displayId = SDL_atoi(chosenDisplayId);
    }

    // Enumerate physical devices
    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_मोजणी, रिक्त);
    जर (rc != VK_SUCCESS) {
        SDL_SetError("Could not enumerate Vulkan physical devices");
        जा error;
    }

    जर (physical_Device_मोजणी == 0) {
        SDL_SetError("No Vulkan physical devices");
        जा error;
    }

    physicalDevices = (VkPhysicalDevice *)SDL_malloc(आकार(VkPhysicalDevice) * physical_Device_मोजणी);
    जर (!physicalDevices) {
        जा error;
    }

    rc = vkEnumeratePhysicalDevices(instance, &physical_Device_मोजणी, physicalDevices);
    जर (rc != VK_SUCCESS) {
        SDL_SetError("Error enumerating physical devices");
        जा error;
    }

    साठी (physicalDeviceIndex = 0; physicalDeviceIndex < physical_Device_मोजणी; physicalDeviceIndex++) {
        VkPhysicalDevice physicalDevice = physicalDevices[physicalDeviceIndex];
        uint32_t display_Properties_मोजणी = 0;
        VkDisplayPropertiesKHR *displayProperties = रिक्त;
        uint32_t display_Mode_Properties_मोजणी = 0;
        VkDisplayModePropertiesKHR *displayModeProperties = रिक्त;
        पूर्णांक bestMatchIndex = -1;
        uint32_t refreshRate = 0;
        uint32_t i;
        uint32_t display_Plane_Properties_मोजणी = 0;
        पूर्णांक planeIndex = -1;
        VkDisplayKHR display;
        VkDisplayPlanePropertiesKHR *displayPlaneProperties = रिक्त;
        VkExtent2D extent;
        VkDisplayPlaneCapabilitiesKHR planeCaps = { 0 };

        // Get information about the physical displays
        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_मोजणी, रिक्त);
        जर (rc != VK_SUCCESS || display_Properties_मोजणी == 0) {
            // This device has no physical device display properties, move on to next.
            सुरूठेवा;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display properties for device %u: %u",
                     physicalDeviceIndex, display_Properties_मोजणी);

        जर (displayId < 0 || (uint32_t)displayId >= display_Properties_मोजणी) {
            // Display id specified was higher than number of available displays, move to next physical device.
            displayId -= display_Properties_मोजणी;
            सुरूठेवा;
        }

        displayProperties = (VkDisplayPropertiesKHR *)SDL_malloc(आकार(VkDisplayPropertiesKHR) * display_Properties_मोजणी);
        जर (!displayProperties) {
            जा error;
        }

        rc = vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &display_Properties_मोजणी, displayProperties);
        जर (rc != VK_SUCCESS || display_Properties_मोजणी == 0) {
            SDL_free(displayProperties);
            SDL_SetError("Error enumerating physical device displays");
            जा error;
        }

        display = displayProperties[displayId].display;
        extent = displayProperties[displayId].physicalResolution;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Display: %s Native resolution: %ux%u",
                     displayProperties[displayId].displayName, extent.width, extent.height);

        SDL_free(displayProperties);
        displayProperties = रिक्त;

        // Get display mode properties for the chosen display
        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_मोजणी, रिक्त);
        जर (rc != VK_SUCCESS || display_Mode_Properties_मोजणी == 0) {
            SDL_SetError("Error enumerating display modes");
            जा error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display modes: %u", display_Mode_Properties_मोजणी);

        displayModeProperties = (VkDisplayModePropertiesKHR *)SDL_malloc(आकार(VkDisplayModePropertiesKHR) * display_Mode_Properties_मोजणी);
        जर (!displayModeProperties) {
            जा error;
        }

        rc = vkGetDisplayModePropertiesKHR(physicalDevice, display, &display_Mode_Properties_मोजणी, displayModeProperties);
        जर (rc != VK_SUCCESS || display_Mode_Properties_मोजणी == 0) {
            SDL_SetError("Error enumerating display modes");
            SDL_free(displayModeProperties);
            जा error;
        }

        // Try to find a display mode that matches the native resolution
        साठी (i = 0; i < display_Mode_Properties_मोजणी; ++i) {
            जर (displayModeProperties[i].parameters.visibleRegion.width == extent.width &&
                displayModeProperties[i].parameters.visibleRegion.height == extent.height &&
                displayModeProperties[i].parameters.refreshRate > refreshRate) {
                bestMatchIndex = i;
                refreshRate = displayModeProperties[i].parameters.refreshRate;
            }
        }

        जर (bestMatchIndex < 0) {
            SDL_SetError("Found no matching display mode");
            SDL_free(displayModeProperties);
            जा error;
        }

        SDL_zero(createInfo);
        createInfo.displayMode = displayModeProperties[bestMatchIndex].displayMode;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Matching mode %ux%u with refresh rate %u",
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.width,
                     displayModeProperties[bestMatchIndex].parameters.visibleRegion.height,
                     refreshRate);

        SDL_free(displayModeProperties);
        displayModeProperties = रिक्त;

        // Try to find a plane index that supports our display
        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_मोजणी, रिक्त);
        जर (rc != VK_SUCCESS || display_Plane_Properties_मोजणी == 0) {
            SDL_SetError("Error enumerating display planes");
            जा error;
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of display planes: %u", display_Plane_Properties_मोजणी);

        displayPlaneProperties = (VkDisplayPlanePropertiesKHR *)SDL_malloc(आकार(VkDisplayPlanePropertiesKHR) * display_Plane_Properties_मोजणी);
        जर (!displayPlaneProperties) {
            जा error;
        }

        rc = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, &display_Plane_Properties_मोजणी, displayPlaneProperties);
        जर (rc != VK_SUCCESS || display_Plane_Properties_मोजणी == 0) {
            SDL_SetError("Error enumerating display plane properties");
            SDL_free(displayPlaneProperties);
            जा error;
        }

        साठी (i = 0; i < display_Plane_Properties_मोजणी; ++i) {
            uint32_t plane_Supported_Displays_मोजणी = 0;
            VkDisplayKHR *planeSupportedDisplays = रिक्त;
            uint32_t j;

            // Check if plane is attached to a display, if not, continue.
            जर (displayPlaneProperties[i].currentDisplay == VK_NULL_HANDLE) {
                सुरूठेवा;
            }

            // Check supported displays for this plane.
            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_मोजणी, रिक्त);
            जर (rc != VK_SUCCESS || plane_Supported_Displays_मोजणी == 0) {
                सुरूठेवा; // No supported displays, on to next plane.
            }

            SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Number of supported displays for plane %u: %u", i, plane_Supported_Displays_मोजणी);

            planeSupportedDisplays = (VkDisplayKHR *)SDL_malloc(आकार(VkDisplayKHR) * plane_Supported_Displays_मोजणी);
            जर (!planeSupportedDisplays) {
                SDL_free(displayPlaneProperties);
                जा error;
            }

            rc = vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, i, &plane_Supported_Displays_मोजणी, planeSupportedDisplays);
            जर (rc != VK_SUCCESS || plane_Supported_Displays_मोजणी == 0) {
                SDL_SetError("Error enumerating supported displays, or no supported displays");
                SDL_free(planeSupportedDisplays);
                SDL_free(displayPlaneProperties);
                जा error;
            }

            साठी (j = 0; j < plane_Supported_Displays_मोजणी && planeSupportedDisplays[j] != display; ++j) {
            }

            SDL_free(planeSupportedDisplays);
            planeSupportedDisplays = रिक्त;

            जर (j == plane_Supported_Displays_मोजणी) {
                // This display is not supported for this plane, move on.
                सुरूठेवा;
            }

            rc = vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, createInfo.displayMode, i, &planeCaps);
            जर (rc != VK_SUCCESS) {
                SDL_SetError("Error getting display plane capabilities");
                SDL_free(displayPlaneProperties);
                जा error;
            }

            // Check if plane fulfills extent requirements.
            जर (extent.width >= planeCaps.minDstExtent.width && extent.height >= planeCaps.minDstExtent.height &&
                extent.width <= planeCaps.maxDstExtent.width && extent.height <= planeCaps.maxDstExtent.height) {
                // If it does, choose this plane.
                SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Choosing plane %u, minimum extent %ux%u maximum extent %ux%u", i,
                             planeCaps.minDstExtent.width, planeCaps.minDstExtent.height,
                             planeCaps.maxDstExtent.width, planeCaps.maxDstExtent.height);
                planeIndex = i;
                थांबा;
            }
        }

        जर (planeIndex < 0) {
            SDL_SetError("No plane supports the selected resolution");
            SDL_free(displayPlaneProperties);
            जा error;
        }

        createInfo.planeIndex = planeIndex;
        createInfo.plane_चळत_Index = displayPlaneProperties[planeIndex].current_चळत_Index;
        SDL_free(displayPlaneProperties);
        displayPlaneProperties = रिक्त;

        // Find a supported alpha mode. Not all planes support OPAQUE
        createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
        साठी (i = 0; i < SDL_arraysize(alphaModes); i++) {
            जर (planeCaps.supportedAlpha & alphaModes[i]) {
                createInfo.alphaMode = alphaModes[i];
                थांबा;
            }
        }
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Chose alpha mode 0x%x", createInfo.alphaMode);

        // Found a match, finally! Fill in extent, and break from loop
        createInfo.imageExtent = extent;
        थांबा;
    }

    SDL_free(physicalDevices);
    physicalDevices = रिक्त;

    जर (physicalDeviceIndex == physical_Device_मोजणी) {
        SDL_SetError("No usable displays found or requested display out of range");
        जा error;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;

    rc = vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, allocator, surface);
    जर (rc != VK_SUCCESS) {
        SDL_SetError("vkCreateDisplayPlaneSurfaceKHR failed: %s", SDL_Vulkan_GetResultString(rc));
        जा error;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "vulkandisplay: Created surface");
    परत true;

error:
    SDL_free(physicalDevices);
    परत false;
}

शून्य SDL_Vulkan_DestroySurface_Internal(शून्य *vkGetInstanceProcAddr_,
                                        VkInstance instance,
                                        VkSurfaceKHR surface,
                                        स्थिरांक संरचना VkAllocationCallbacks *allocator)
{
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)vkGetInstanceProcAddr_;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR =
        (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(
            instance,
            "vkDestroySurfaceKHR");

    जर (vkDestroySurfaceKHR) {
        vkDestroySurfaceKHR(instance, surface, allocator);
    }
}

#endif
